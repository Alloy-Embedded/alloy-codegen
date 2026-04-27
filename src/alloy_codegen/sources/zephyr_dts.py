"""Zephyr DTS source adapter.

Added by ``ingest-zephyr-dts-as-source``.

Parses Zephyr device-tree files (``*.dts``) using ``devicetree.dtlib``
and projects them into the alloy-codegen :class:`RawDeviceDocument`
shape (peripherals + interrupts).  This is the cross-vendor spine
that unblocks Nordic, Renesas, TI, Infineon, Ambiq, etc. through
one adapter — Zephyr's ``dts/<arch>/<vendor>/`` tree carries all
of them with normalised peripheral/interrupt/clock data.

The adapter is **structural only** for v1: it extracts peripheral
instances, IRQ lines, and memory regions.  Pinctrl groups and
clock-tree edges are out of scope for the initial Nordic nRF52
admission and land in follow-up changes (the proposal explicitly
calls them out as best-effort and deferred).

Initial admission target: ``nordic/nrf52``.  Other Zephyr-covered
families plug in by registering a vendor adapter and providing a
small compatible→ip-name mapping override.
"""

from __future__ import annotations

import hashlib
import re
from collections.abc import Callable
from dataclasses import dataclass, field
from pathlib import Path

from devicetree import dtlib

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.raw import (
    RawDeviceDocument,
    RawInterrupt,
    RawPeripheral,
)

SOURCE_ID = "zephyr-dts"

# Zephyr's device-tree compatible strings are dot-separated
# vendor-prefixed identifiers (e.g. ``nordic,nrf-uart``,
# ``arm,armv7m-nvic``).  We map a curated subset to canonical alloy
# IP names + peripheral-class hints.  Unmapped compatibles are
# **skipped** (the adapter logs and continues — DTS is intentionally
# permissive about new compatibles, and silent-skip is safer than
# fail-on-unknown for a source that grows weekly upstream).
NORDIC_COMPATIBLE_MAP: dict[str, str] = {
    "nordic,nrf-uart": "uart",
    "nordic,nrf-uarte": "uart",
    "nordic,nrf-spi": "spi",
    "nordic,nrf-spim": "spi",
    "nordic,nrf-spis": "spi",
    "nordic,nrf-twi": "i2c",
    "nordic,nrf-twim": "i2c",
    "nordic,nrf-twis": "i2c",
    "nordic,nrf-saadc": "adc",
    "nordic,nrf-rtc": "rtc",
    "nordic,nrf-timer": "timer",
    "nordic,nrf-pwm": "pwm",
    "nordic,nrf-gpio": "gpio",
    "nordic,nrf-gpiote": "gpiote",
    "nordic,nrf-clock": "clock",
    "nordic,nrf-power": "power",
    "nordic,nrf-wdt": "watchdog",
    "nordic,nrf-temp": "temp_sensor",
    "nordic,nrf-rng": "rng",
    "nordic,nrf-ecb": "ecb",
    "nordic,nrf-egu": "egu",
    "nordic,nrf-radio": "radio",
}

# Per-vendor registry.  When extending Zephyr DTS support to a new
# vendor (Renesas, TI, Infineon, Ambiq, …), append a mapping here.
COMPATIBLE_MAPS: dict[str, dict[str, str]] = {
    "nordic": NORDIC_COMPATIBLE_MAP,
}


# ---------------------------------------------------------------------------
# Source-root resolution
# ---------------------------------------------------------------------------


def ensure_source_root(context: ExecutionContext) -> Path:
    """Resolve the configured ``zephyr-dts`` source root.

    Unlike ``cmsis-svd-data``, this adapter does **not** clone Zephyr
    on demand — Zephyr is a 200+ MB repo and downloading it
    transparently surprises CI.  The user MUST set
    ``ALLOY_CODEGEN_SOURCE_ZEPHYR_DTS_ROOT`` (or pass
    ``zephyr-dts`` via :class:`ExecutionContext` overrides) to
    point at a local checkout.
    """
    configured_root = context.source_root_for(SOURCE_ID)
    if configured_root is None:
        raise StageExecutionError(
            "zephyr-dts source root is not configured.  Set "
            "ALLOY_CODEGEN_SOURCE_ZEPHYR_DTS_ROOT or pass "
            "source_overrides={'zephyr-dts': <path>} to point at a "
            "Zephyr checkout (or a snapshotted DTS subtree)."
        )
    if not configured_root.exists():
        raise StageExecutionError(f"zephyr-dts source root does not exist: {configured_root}")
    return configured_root


# Layout assumption: ``<zephyr-dts-root>/<vendor>/<device>.dts``.
# The real Zephyr tree is ``dts/<arch>/<vendor>/<device>.dts`` —
# adapters that consume the upstream layout can pre-flatten via a
# symlink or pass the ``dts/<arch>`` subtree directly.
def resolve_dts_path(
    context: ExecutionContext,
    *,
    vendor: str,
    family: str,
    device: str,
) -> Path:
    """Resolve the ``.dts`` file path for a device."""
    root = ensure_source_root(context)
    # Try a few layout candidates so callers can either snapshot
    # ``dts/arm/<vendor>/`` or use a flat ``<vendor>/<device>.dts``.
    candidates = (
        root / vendor / f"{device}.dts",
        root / family / f"{device}.dts",
        root / f"{device}.dts",
    )
    for candidate in candidates:
        if candidate.exists():
            return candidate
    searched = "\n  ".join(str(c) for c in candidates)
    raise StageExecutionError(
        f"No zephyr-dts file found for {vendor}/{family}/{device}. Searched:\n  {searched}"
    )


def source_revision(root: Path) -> str:
    """Best-effort revision string for fetch provenance.

    If the root is a git checkout, return ``HEAD``.  Otherwise hash
    the directory listing so two runs against an identical snapshot
    produce identical revisions.
    """
    git_dir = root / ".git"
    if git_dir.exists():
        head = git_dir / "HEAD"
        if head.exists():
            return f"git-head:{head.read_text(encoding='utf-8').strip()[:40]}"
    digest = hashlib.sha256()
    for path in sorted(root.rglob("*.dts")):
        digest.update(str(path.relative_to(root)).encode("utf-8"))
        digest.update(b"\0")
        digest.update(path.read_bytes())
    return f"content-sha256:{digest.hexdigest()[:16]}"


# ---------------------------------------------------------------------------
# DTS parsing
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class ZephyrDtsMemoryRegion:
    """A memory region extracted from a DTS ``memory@<addr>`` node."""

    name: str
    base_address: int
    size_bytes: int
    compatible: str


@dataclass(frozen=True, slots=True)
class ZephyrDeviceDocument:
    """All structural facts the adapter pulls out of one DTS file."""

    device_name: str
    raw: RawDeviceDocument
    memories: tuple[ZephyrDtsMemoryRegion, ...] = field(default_factory=tuple)
    skipped_compatibles: tuple[str, ...] = field(default_factory=tuple)


_INSTANCE_LABEL_RE = re.compile(r"^([a-z]+)(\d+)$")


def peripheral_instance_index(label: str | None, fallback_name: str) -> int:
    """Best-effort instance number derivation from a Zephyr label.

    Zephyr conventions: nodes carry numeric labels like ``uart0``,
    ``spi2``, ``twi1``.  Strip the alpha prefix and parse the digits.
    Falls back to 0 when the label is non-numeric.
    """
    target = label or fallback_name
    match = _INSTANCE_LABEL_RE.match(target.lower())
    if match is None:
        return 0
    return int(match.group(2))


def _read_compat(node: dtlib.Node) -> tuple[str, ...]:
    """Return the ``compatible`` strings on a node (empty if absent)."""
    prop = node.props.get("compatible")
    if prop is None:
        return ()
    return tuple(prop.to_strings())


def _read_reg_pairs(node: dtlib.Node) -> tuple[tuple[int, int], ...]:
    """Decode a ``reg`` property as a flat list of ``(addr, size)``
    cells, assuming the canonical 1-cell address + 1-cell size that
    Zephyr SoC files use under ``soc/``."""
    prop = node.props.get("reg")
    if prop is None:
        return ()
    nums = prop.to_nums()
    if len(nums) % 2 != 0:
        return ()
    return tuple((nums[i], nums[i + 1]) for i in range(0, len(nums), 2))


def _read_interrupts(node: dtlib.Node) -> tuple[tuple[int, int], ...]:
    """Decode a node's ``interrupts`` property as ``(line, prio)`` pairs.

    Zephyr nRF SoC bindings use a 2-cell interrupt specifier
    ``<line priority>``.  Other Zephyr SoCs may use 3-cell specs;
    the adapter reads pairs and the caller can ignore the priority.
    """
    prop = node.props.get("interrupts")
    if prop is None:
        return ()
    nums = prop.to_nums()
    if len(nums) % 2 != 0:
        return ()
    return tuple((nums[i], nums[i + 1]) for i in range(0, len(nums), 2))


def _node_label(node: dtlib.Node) -> str | None:
    return node.labels[0] if node.labels else None


def _peripheral_canonical_name(label: str | None, fallback_name: str) -> str:
    """Canonical PERIPHERAL name for the IR (e.g. ``UART0``)."""
    target = (label or fallback_name).upper()
    # Zephyr labels look like "uart0"/"twi1" — uppercase them.  If
    # the node has no label, fall back to the unit-address form.
    return target


def parse_zephyr_device_document(
    dts_path: Path,
    *,
    compatible_map: dict[str, str],
    extra_compatible_filter: Callable[[str], bool] | None = None,
) -> ZephyrDeviceDocument:
    """Parse one DTS file into a structural device document.

    ``compatible_map`` maps Zephyr ``compatible`` strings to alloy
    IP-name canonical strings.  Nodes whose first compatible is
    not in the map (and not accepted by ``extra_compatible_filter``)
    are skipped — their compatibles are recorded in
    :attr:`ZephyrDeviceDocument.skipped_compatibles` for diagnostics.

    Memory regions are extracted from any node whose first
    compatible is ``mmio-sram`` or contains ``memory`` (covers
    Zephyr's ``mmio-sram`` and vendor-specific flash bindings).
    """
    if not dts_path.exists():
        raise StageExecutionError(f"DTS file not found: {dts_path}")

    dt = dtlib.DT(str(dts_path))
    peripherals: list[RawPeripheral] = []
    interrupts: list[RawInterrupt] = []
    memories: list[ZephyrDtsMemoryRegion] = []
    skipped: set[str] = set()

    for node in dt.root.node_iter():
        compatibles = _read_compat(node)
        if not compatibles:
            continue
        first = compatibles[0]

        # Memory regions: collect from any binding that names a
        # memory-like region.  Zephyr uses ``mmio-sram`` for RAM,
        # ``soc-nv-flash`` / ``zephyr,memory-region`` /
        # ``<vendor>,nvm`` etc. for flash; we accept the union.
        memory_compatibles = {
            "mmio-sram",
            "soc-nv-flash",
            "zephyr,memory-region",
            "fixed-partitions",
        }
        is_memory_node = (
            first in memory_compatibles
            or any(c in memory_compatibles for c in compatibles)
            or "memory" in node.name
            or "flash" in node.name
        )
        if is_memory_node:
            for base, size in _read_reg_pairs(node):
                memories.append(
                    ZephyrDtsMemoryRegion(
                        name=_node_label(node) or node.name,
                        base_address=base,
                        size_bytes=size,
                        compatible=first,
                    )
                )
            continue

        # Skip the root + bus parents (no peripheral semantics).
        if first in ("simple-bus", "syscon"):
            continue

        ip_name = compatible_map.get(first)
        if ip_name is None:
            if extra_compatible_filter is not None and extra_compatible_filter(first):
                ip_name = first.split(",", 1)[-1].replace("-", "_")
            else:
                skipped.add(first)
                continue

        reg_pairs = _read_reg_pairs(node)
        if not reg_pairs:
            # Some pseudo-peripherals (e.g. ``nordic,nrf-clock`` on
            # some SoCs) carry no reg.  Skip them — they have no
            # base address to project into the IR.
            continue
        base_address = reg_pairs[0][0]

        label = _node_label(node)
        peripheral_name = _peripheral_canonical_name(label, node.name)
        peripherals.append(
            RawPeripheral(
                name=peripheral_name,
                base_address=base_address,
                registers=(),  # DTS does not carry a register tree.
            )
        )

        for line, _priority in _read_interrupts(node):
            del _priority  # priority cell not used yet
            interrupts.append(
                RawInterrupt(
                    name=f"{peripheral_name}_IRQ",
                    line=line,
                    peripheral=peripheral_name,
                )
            )

    # Sort for determinism.
    peripherals.sort(key=lambda p: (p.base_address, p.name))
    interrupts.sort(key=lambda i: (i.line, i.name))
    memories.sort(key=lambda m: (m.base_address, m.name))

    raw = RawDeviceDocument(
        device_name=dts_path.stem.lower(),
        description=f"Zephyr DTS source: {dts_path.name}",
        svd_version=None,
        peripherals=tuple(peripherals),
        interrupts=tuple(interrupts),
    )
    return ZephyrDeviceDocument(
        device_name=dts_path.stem.lower(),
        raw=raw,
        memories=tuple(memories),
        skipped_compatibles=tuple(sorted(skipped)),
    )


# ---------------------------------------------------------------------------
# Fetch records (vendor-adapter contract)
# ---------------------------------------------------------------------------


ZEPHYR_REMOTE = "https://github.com/zephyrproject-rtos/zephyr.git"


def fetch_records(
    execution_context: ExecutionContext,
    scope: PipelineScope,
) -> tuple[dict[str, str], ...]:
    """Resolve upstream DTS records for the requested scope."""
    validated_scope = scope.validate_supported()
    root = ensure_source_root(execution_context)
    revision = source_revision(root)
    vendor = validated_scope.resolved_vendor()
    family = validated_scope.resolved_family()
    records: list[dict[str, str]] = []
    for device_name in validated_scope.resolved_device_names():
        local_path = resolve_dts_path(
            execution_context, vendor=vendor, family=family, device=device_name
        )
        records.append(
            {
                "source_id": SOURCE_ID,
                "target_device": device_name,
                "origin_url": ZEPHYR_REMOTE,
                "revision": revision,
                "local_path": str(local_path),
                "upstream_path": str(local_path.relative_to(root)),
            }
        )
    return tuple(records)


def compatible_map_for_vendor(vendor: str) -> dict[str, str]:
    """Return the compatible→ip-name map for a vendor."""
    mapping = COMPATIBLE_MAPS.get(vendor)
    if mapping is None:
        raise StageExecutionError(
            f"No Zephyr compatible map registered for vendor {vendor!r}.  "
            f"Known vendors: {sorted(COMPATIBLE_MAPS)}"
        )
    return mapping


__all__ = [
    "COMPATIBLE_MAPS",
    "NORDIC_COMPATIBLE_MAP",
    "SOURCE_ID",
    "ZEPHYR_REMOTE",
    "ZephyrDeviceDocument",
    "ZephyrDtsMemoryRegion",
    "compatible_map_for_vendor",
    "ensure_source_root",
    "fetch_records",
    "parse_zephyr_device_document",
    "peripheral_instance_index",
    "resolve_dts_path",
    "source_revision",
]
