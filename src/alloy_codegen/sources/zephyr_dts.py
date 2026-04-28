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

Currently registered compatible maps: ``nordic``, ``renesas``,
``ti``, ``atmel``, ``ambiq``, ``infineon``, ``silabs``,
``espressif``.  These are *vocabulary* — admitting a device
still requires a registered :class:`VendorAdapter` and goldens.
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
# Cross-vendor generic compatibles.  Every vendor map merges with
# this so ARM-core bindings (NVIC, SysTick) don't have to be
# redeclared per vendor.  Keep this short and only put compatibles
# here whose semantics are identical across every Zephyr vendor.
_GENERIC_COMPATIBLE_MAP: dict[str, str] = {
    "arm,armv6m-nvic": "nvic",
    "arm,armv7m-nvic": "nvic",
    "arm,armv8m-nvic": "nvic",
    "arm,armv8.1m-nvic": "nvic",
    "arm,v6m-systick": "systick",
    "arm,v7m-systick": "systick",
    "arm,v8m-systick": "systick",
}


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

# Renesas RA family (Cortex-M4 / M33 SoCs).  Bindings live under
# Zephyr's ``dts/arm/renesas/ra*/``.
RENESAS_RA_COMPATIBLE_MAP: dict[str, str] = {
    "renesas,ra-sci-uart": "uart",
    "renesas,ra-uart-sci-b": "uart",
    "renesas,ra-sci-i2c": "i2c",
    "renesas,ra-iic": "i2c",
    "renesas,ra-spi": "spi",
    "renesas,ra-spi-b": "spi",
    "renesas,ra-adc": "adc",
    "renesas,ra-gpt-pwm": "pwm",
    "renesas,ra-gpt-timer": "timer",
    "renesas,ra-agt-timer": "timer",
    "renesas,ra-ioport": "gpio",
    "renesas,ra-wdt": "watchdog",
    "renesas,ra-iwdt": "watchdog",
    "renesas,ra-cgc": "clock",
    "renesas,ra-dac": "dac",
    "renesas,ra-canfd": "can",
}

# TI tiva-c, CC13xx, CC26xx (Cortex-M3 / M4F SoCs).
TI_COMPATIBLE_MAP: dict[str, str] = {
    "ti,cc13xx-cc26xx-uart": "uart",
    "ti,cc32xx-uart": "uart",
    "ti,stellaris-uart": "uart",
    "ti,cc13xx-cc26xx-spi": "spi",
    "ti,cc32xx-spi": "spi",
    "ti,cc13xx-cc26xx-i2c": "i2c",
    "ti,cc32xx-i2c": "i2c",
    "ti,cc13xx-cc26xx-adc": "adc",
    "ti,cc13xx-cc26xx-timer": "timer",
    "ti,cc13xx-cc26xx-timer-pwm": "pwm",
    "ti,cc13xx-cc26xx-gpio": "gpio",
    "ti,cc32xx-gpio": "gpio",
    "ti,cc13xx-cc26xx-watchdog": "watchdog",
    "ti,cc13xx-cc26xx-pinctrl": "pinctrl",
}

# Atmel SAMD/SAML series (Cortex-M0+ / M4F).  Note these are the
# Microchip-acquired Atmel SoCs; Zephyr keeps the ``atmel,`` prefix
# for historical reasons.
ATMEL_COMPATIBLE_MAP: dict[str, str] = {
    "atmel,sam0-uart": "uart",
    "atmel,sam0-spi": "spi",
    "atmel,sam0-i2c": "i2c",
    "atmel,sam0-adc": "adc",
    "atmel,sam0-tcc-pwm": "pwm",
    "atmel,sam0-tc32": "timer",
    "atmel,sam0-gpio": "gpio",
    "atmel,sam0-wdt": "watchdog",
    "atmel,sam0-rtc": "rtc",
    "atmel,sam0-dac": "dac",
    "atmel,sam0-trng": "rng",
    "atmel,sam0-can": "can",
}

# Ambiq Apollo series (Apollo3 / Apollo4 — Cortex-M4F).  Apollo's
# IOM peripheral is a unified SPI/I2C controller; map to ``i2c``
# by default since DTS instances pick a mode at the binding layer.
AMBIQ_COMPATIBLE_MAP: dict[str, str] = {
    "ambiq,uart": "uart",
    "ambiq,iom": "i2c",
    "ambiq,spid": "spi",
    "ambiq,adc": "adc",
    "ambiq,ctimer": "timer",
    "ambiq,stimer": "timer",
    "ambiq,gpio": "gpio",
    "ambiq,wdt": "watchdog",
    "ambiq,mspi": "spi",
    "ambiq,rtc": "rtc",
}

# Infineon XMC4xxx + PSoC6 (cat1) families.
INFINEON_COMPATIBLE_MAP: dict[str, str] = {
    "infineon,xmc4xxx-uart": "uart",
    "infineon,xmc4xxx-spi": "spi",
    "infineon,xmc4xxx-i2c": "i2c",
    "infineon,xmc4xxx-vadc": "adc",
    "infineon,xmc4xxx-ccu4-pwm": "pwm",
    "infineon,xmc4xxx-ccu4-timer": "timer",
    "infineon,xmc4xxx-gpio": "gpio",
    "infineon,xmc4xxx-wdt": "watchdog",
    "infineon,cat1-uart": "uart",
    "infineon,cat1-spi": "spi",
    "infineon,cat1-i2c": "i2c",
    "infineon,cat1-adc": "adc",
    "infineon,cat1-counter": "timer",
    "infineon,cat1-gpio": "gpio",
    "infineon,cat1-watchdog": "watchdog",
}

# SiLabs gecko series (EFR32 / EFM32 — Cortex-M0+/M4F/M33).
SILABS_COMPATIBLE_MAP: dict[str, str] = {
    "silabs,gecko-usart": "uart",
    "silabs,gecko-eusart": "uart",
    "silabs,gecko-leuart": "uart",
    "silabs,gecko-i2c": "i2c",
    "silabs,gecko-spi-usart": "spi",
    "silabs,gecko-iadc": "adc",
    "silabs,gecko-adc": "adc",
    "silabs,gecko-timer": "timer",
    "silabs,gecko-letimer": "timer",
    "silabs,gecko-pwm": "pwm",
    "silabs,gecko-gpio": "gpio",
    "silabs,gecko-wdog": "watchdog",
    "silabs,gecko-rtcc": "rtc",
    "silabs,gecko-trng": "rng",
}

# Espressif ESP32 series (Xtensa LX6/LX7, RISC-V on C-series).
ESPRESSIF_COMPATIBLE_MAP: dict[str, str] = {
    "espressif,esp32-uart": "uart",
    "espressif,esp32-usb-serial": "uart",
    "espressif,esp32-spi": "spi",
    "espressif,esp32-i2c": "i2c",
    "espressif,esp32-adc": "adc",
    "espressif,esp32-mcpwm": "pwm",
    "espressif,esp32-ledc": "pwm",
    "espressif,esp32-timer": "timer",
    "espressif,esp32-rtc-timer": "timer",
    "espressif,esp32-gpio": "gpio",
    "espressif,esp32-watchdog": "watchdog",
    "espressif,esp32-rmt": "rmt",
    "espressif,esp32-twai": "can",
    "espressif,esp32-dac": "dac",
}


# Per-vendor registry.  When extending Zephyr DTS support to a new
# vendor, append a mapping here.  ``compatible_map_for_vendor``
# returns the union of ``_GENERIC_COMPATIBLE_MAP`` and the entry
# below, so ARM-core bindings (NVIC, SysTick) do not have to be
# redeclared per vendor.
COMPATIBLE_MAPS: dict[str, dict[str, str]] = {
    "nordic": NORDIC_COMPATIBLE_MAP,
    "renesas": RENESAS_RA_COMPATIBLE_MAP,
    "ti": TI_COMPATIBLE_MAP,
    "atmel": ATMEL_COMPATIBLE_MAP,
    "ambiq": AMBIQ_COMPATIBLE_MAP,
    "infineon": INFINEON_COMPATIBLE_MAP,
    "silabs": SILABS_COMPATIBLE_MAP,
    "espressif": ESPRESSIF_COMPATIBLE_MAP,
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
    """Return the compatible→ip-name map for a vendor.

    The result is the union of :data:`_GENERIC_COMPATIBLE_MAP`
    (cross-vendor ARM-core bindings) and the per-vendor map
    registered in :data:`COMPATIBLE_MAPS`.
    """
    mapping = COMPATIBLE_MAPS.get(vendor)
    if mapping is None:
        raise StageExecutionError(
            f"No Zephyr compatible map registered for vendor {vendor!r}.  "
            f"Known vendors: {sorted(COMPATIBLE_MAPS)}"
        )
    return {**_GENERIC_COMPATIBLE_MAP, **mapping}


__all__ = [
    "AMBIQ_COMPATIBLE_MAP",
    "ATMEL_COMPATIBLE_MAP",
    "COMPATIBLE_MAPS",
    "ESPRESSIF_COMPATIBLE_MAP",
    "INFINEON_COMPATIBLE_MAP",
    "NORDIC_COMPATIBLE_MAP",
    "RENESAS_RA_COMPATIBLE_MAP",
    "SILABS_COMPATIBLE_MAP",
    "SOURCE_ID",
    "TI_COMPATIBLE_MAP",
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
