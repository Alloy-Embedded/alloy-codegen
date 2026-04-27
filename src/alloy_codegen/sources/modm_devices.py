"""modm-devices STM32 enrichment adapter (ingest-modm-devices-as-source).

modm-io's `modm-devices` repository carries already-normalized AF
tables, clock-tree topology, DMA request matrices, and signal
mappings for ~3500 STM32 variants — extracted from CubeMX XML and
ST reference manual PDFs by `modm-data`.

This adapter consumes
``modm-devices/devices/stm32/<family>/<part>.xml`` and produces
typed enrichment payloads the alloy normalize stage layers on top
of CMSIS-SVD + STM32 open-pin-data, but **below** family + device
patches.  Merge precedence:

    cmsis-svd  <  stm32-open-pin-data  <  modm-devices
                <  family-patch  <  device-patch

The integration is gap-fill, not replacement.  modm contributes
fields that the open sources lack (clock graph edges, DMA request
matrix); CMSIS-SVD wins on registers, STM32 open-pin-data wins on
package-specific pinouts.

The adapter is opt-in per device: pass an explicit
``modm-devices`` source-override path to ``ExecutionContext`` to
enable enrichment.  When the override is missing, ``load_enrichment``
returns ``None`` and the pipeline behaves identically to today's
non-enriched flow.

Source pinning: every load checks ``data/source_pins.toml`` for
the recorded SHA; a drift fails with a clear message unless the
caller passes ``accept_stale_sources=True``.
"""

from __future__ import annotations

import xml.etree.ElementTree as ET
from dataclasses import dataclass
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.scope import PipelineScope


@dataclass(frozen=True, slots=True)
class ModmClockEdge:
    """One clock-tree edge contributed by modm-devices.

    ``source`` and ``target`` are modm's normalized node ids
    (``hsi16``, ``pll_r``, ``sysclk``, ``hclk``, ...).
    """

    source: str
    target: str
    multiplier: int | None = None
    divisor: int | None = None


@dataclass(frozen=True, slots=True)
class ModmDmaRequest:
    """One DMA request entry contributed by modm-devices."""

    peripheral: str
    signal: str  # "TX" | "RX" | "" for unidirectional
    request_value: int


@dataclass(frozen=True, slots=True)
class ModmSignalAf:
    """One per-pin alternate-function row contributed by modm-devices."""

    pin: str  # e.g. "PA0"
    peripheral: str
    signal: str
    af_number: int


@dataclass(frozen=True, slots=True)
class ModmEnrichment:
    """Aggregated enrichment payload for one device.

    ``provenance`` carries the modm-devices SHA the import was
    pinned against — the resolved IR records this on every leaf
    derived from modm so reviewers can audit the source.
    """

    device: str
    family: str
    clock_edges: tuple[ModmClockEdge, ...] = ()
    dma_requests: tuple[ModmDmaRequest, ...] = ()
    signal_afs: tuple[ModmSignalAf, ...] = ()
    provenance_sha: str = ""

    def to_dict(self) -> dict[str, object]:
        return {
            "device": self.device,
            "family": self.family,
            "clock_edges": [
                {"source": e.source, "target": e.target,
                 "multiplier": e.multiplier, "divisor": e.divisor}
                for e in self.clock_edges
            ],
            "dma_requests": [
                {"peripheral": d.peripheral, "signal": d.signal,
                 "request_value": d.request_value}
                for d in self.dma_requests
            ],
            "signal_afs": [
                {"pin": s.pin, "peripheral": s.peripheral,
                 "signal": s.signal, "af_number": s.af_number}
                for s in self.signal_afs
            ],
            "provenance_sha": self.provenance_sha,
        }


def _parse_modm_xml(path: Path) -> tuple[
    tuple[ModmClockEdge, ...],
    tuple[ModmDmaRequest, ...],
    tuple[ModmSignalAf, ...],
]:
    """Parse one modm-devices XML into typed enrichment tuples.

    The modm schema groups peripheral facts under ``<driver>`` blocks
    and per-pin signals under ``<gpio>``.  We extract the three
    enrichment surfaces alloy currently lacks coverage for:
    clock-graph edges, DMA request matrix, and AF signal mappings.
    """
    tree = ET.parse(path)
    root = tree.getroot()

    clock_edges: list[ModmClockEdge] = []
    dma_requests: list[ModmDmaRequest] = []
    signal_afs: list[ModmSignalAf] = []

    # Find the device element (modm wraps content in <device> or
    # <devices><device>...).
    device_elements = list(root.iter("device"))
    if not device_elements:
        device_elements = [root]

    for device in device_elements:
        for driver in device.iter("driver"):
            driver_name = driver.attrib.get("name", "").lower()
            if driver_name == "rcc":
                # Modm's RCC clock-tree: <signal source="hsi16" target="sysclk"/>
                for edge in driver.iter("signal"):
                    src = edge.attrib.get("source", "")
                    tgt = edge.attrib.get("target", "")
                    if src and tgt:
                        mul_raw = edge.attrib.get("multiplier")
                        div_raw = edge.attrib.get("divisor")
                        try:
                            mul = int(mul_raw) if mul_raw is not None else None
                        except ValueError:
                            mul = None
                        try:
                            div = int(div_raw) if div_raw is not None else None
                        except ValueError:
                            div = None
                        clock_edges.append(
                            ModmClockEdge(source=src, target=tgt, multiplier=mul, divisor=div)
                        )
            elif driver_name == "dma":
                # <request name="USART1_RX" peripheral="USART1" signal="RX" channel="50"/>
                for request in driver.iter("request"):
                    peripheral = request.attrib.get("peripheral", "")
                    signal = request.attrib.get("signal", "")
                    try:
                        channel = int(request.attrib.get("channel", "0"))
                    except ValueError:
                        channel = 0
                    if peripheral:
                        dma_requests.append(
                            ModmDmaRequest(
                                peripheral=peripheral,
                                signal=signal,
                                request_value=channel,
                            )
                        )
            elif driver_name == "gpio":
                # <gpio port="A" pin="0">
                #   <signal driver="usart" instance="2" name="cts" af="1"/>
                # </gpio>
                for gpio in driver.iter("gpio"):
                    port = gpio.attrib.get("port", "").upper()
                    try:
                        pin_num = int(gpio.attrib.get("pin", "0"))
                    except ValueError:
                        continue
                    pin_label = f"P{port}{pin_num}"
                    for signal in gpio.iter("signal"):
                        peri_driver = signal.attrib.get("driver", "")
                        instance = signal.attrib.get("instance", "")
                        signal_name = signal.attrib.get("name", "")
                        try:
                            af = int(signal.attrib.get("af", "0"))
                        except ValueError:
                            continue
                        peripheral = (
                            f"{peri_driver.upper()}{instance}" if peri_driver else ""
                        )
                        if peripheral and signal_name:
                            signal_afs.append(
                                ModmSignalAf(
                                    pin=pin_label,
                                    peripheral=peripheral,
                                    signal=signal_name,
                                    af_number=af,
                                )
                            )

    return tuple(clock_edges), tuple(dma_requests), tuple(signal_afs)


def _modm_xml_path(
    context: ExecutionContext,
    *,
    family: str,
    device: str,
) -> Path | None:
    """Resolve the modm-devices XML path for a given STM32 device.

    Returns ``None`` when no ``modm-devices`` source override is
    configured — the caller treats this as "skip enrichment".
    """
    root = context.source_root_for("modm-devices")
    if root is None:
        return None
    candidate = Path(root) / "devices" / "stm32" / family.removeprefix("stm32") / f"{device}.xml"
    if candidate.exists():
        return candidate
    # Some modm trees nest by part-stem (g071) and per-package suffix.
    short_family = family.removeprefix("stm32")
    short_device = device.removeprefix("stm32")
    candidate = Path(root) / "devices" / "stm32" / short_family / f"{short_device}.xml"
    if candidate.exists():
        return candidate
    return None


def load_enrichment(
    context: ExecutionContext,
    *,
    vendor: str,
    family: str,
    device: str,
    accept_stale_sources: bool = False,
) -> ModmEnrichment | None:
    """Load + parse the modm-devices XML for one STM32 device.

    Returns ``None`` when no ``modm-devices`` source override is
    configured, when the requested family is not ``st``, or when
    the XML file is missing — non-fatal because modm coverage is
    opt-in per family.

    Validates the source pin recorded in ``data/source_pins.toml``;
    raises ``StageExecutionError`` on drift unless the caller passes
    ``accept_stale_sources=True``.
    """
    if vendor != "st":
        return None
    xml_path = _modm_xml_path(context, family=family, device=device)
    if xml_path is None:
        return None
    # Source-pin check (best-effort).
    root = context.source_root_for("modm-devices")
    if root is not None:
        validate_modm_source_pin(
            modm_root=Path(root),
            accept_stale_sources=accept_stale_sources,
        )
    clock_edges, dma_requests, signal_afs = _parse_modm_xml(xml_path)
    pin_sha = _read_modm_pin_sha()
    return ModmEnrichment(
        device=device,
        family=family,
        clock_edges=clock_edges,
        dma_requests=dma_requests,
        signal_afs=signal_afs,
        provenance_sha=pin_sha,
    )


def apply_modm_enrichment(
    device: object, enrichment: ModmEnrichment | None
) -> object:
    """Layer the modm enrichment onto a partially-built canonical IR.

    ``device`` is a ``CanonicalDeviceIR`` (typed as ``object`` here
    to avoid a hard import dependency on the IR module — the
    enrichment is a thin layer that only touches ``dma_requests``).
    ``enrichment`` is the parsed modm payload, or ``None`` to
    short-circuit (no override path configured).

    Precedence order: ``cmsis-svd < stm32-open-pin-data <
    modm-devices < family-patch < device-patch``.  We sit *below*
    the patches: only DMA requests that the device IR does not
    already carry are gap-filled from modm.  Patch-supplied values
    are never overwritten.
    """
    if enrichment is None:
        return device
    import dataclasses

    from alloy_codegen.ir.model import (
        DmaRequestDefinition,
        Provenance,
    )

    existing_keys = {
        (dr.controller, dr.request_line, dr.peripheral or "", dr.signal or "")
        for dr in getattr(device, "dma_requests", ())
    }
    additions: list[DmaRequestDefinition] = []
    for req in enrichment.dma_requests:
        # modm doesn't carry an explicit controller name for STM32
        # DMAMUX-class chips (every request lands on the single DMA
        # mux); we use "DMA1" as the canonical default — the patch
        # tier wins anyway when it disagrees.
        controller = "DMA1"
        request_line = f"DMAMUX_REQ_{req.request_value:03d}"
        key = (controller, request_line, req.peripheral, req.signal or "")
        if key in existing_keys:
            continue
        provenance = Provenance(
            source_id="modm-devices",
            source_path=None,
            patch_ids=("modm-devices@" + (enrichment.provenance_sha or "unpinned"),),
        )
        additions.append(
            DmaRequestDefinition(
                controller=controller,
                request_line=request_line,
                peripheral=req.peripheral,
                signal=req.signal or None,
                provenance=provenance,
                channel_index=None,
                request_value=req.request_value,
                channel_selector=None,
            )
        )
    if not additions:
        return device
    return dataclasses.replace(
        device,
        dma_requests=tuple(getattr(device, "dma_requests", ())) + tuple(additions),
    )


def fetch_records(
    context: ExecutionContext, scope: PipelineScope
) -> tuple[dict[str, str], ...]:
    """Source-manifest fetch entry for modm-devices.

    Returns one record per device when an override path is set, so
    the source manifest tracks which modm SHA the import used.
    Returns an empty tuple when no override is configured (modm
    enrichment is opt-in per workstation).
    """
    validated = scope.validate_supported()
    if validated.resolved_vendor() != "st":
        return ()
    root = context.source_root_for("modm-devices")
    if root is None:
        return ()
    family = validated.resolved_family()
    pin_sha = _read_modm_pin_sha()
    records: list[dict[str, str]] = []
    for device in validated.resolved_device_names():
        xml_path = _modm_xml_path(context, family=family, device=device)
        if xml_path is None:
            continue
        records.append(
            {
                "source_id": "modm-devices",
                "target_device": device,
                "origin_url": "https://github.com/modm-io/modm-devices",
                "revision": pin_sha,
                "local_path": str(xml_path),
                "upstream_path": (
                    f"devices/stm32/{family.removeprefix('stm32')}/{xml_path.name}"
                ),
            }
        )
    return tuple(records)


# ---------------------------------------------------------------------------
# Source-pin tracking (data/source_pins.toml)
# ---------------------------------------------------------------------------


def _source_pins_path() -> Path:
    return Path(__file__).resolve().parents[3] / "data" / "source_pins.toml"


def _read_modm_pin_sha() -> str:
    """Return the SHA recorded for ``modm_devices`` in
    ``data/source_pins.toml``.  Empty string when the file is
    missing or the section is absent."""
    import tomllib

    path = _source_pins_path()
    if not path.exists():
        return ""
    payload = tomllib.loads(path.read_text())
    section = payload.get("modm_devices") or {}
    return str(section.get("sha", ""))


def validate_modm_source_pin(
    *,
    modm_root: Path,
    accept_stale_sources: bool = False,
) -> None:
    """Compare the modm-devices checkout's git HEAD against the SHA
    pinned in ``data/source_pins.toml``.  Raise ``StageExecutionError``
    on drift unless ``accept_stale_sources`` is true.

    Best-effort: when git is missing or the modm root is not a git
    checkout, we assume the on-disk content matches the pin and
    return silently.  The check is meaningful only for real
    upstream syncs."""
    expected = _read_modm_pin_sha()
    if not expected:
        # No pin recorded yet → first ingest, accept whatever the
        # caller has on disk.
        return
    import subprocess

    try:
        out = subprocess.run(
            ["git", "rev-parse", "HEAD"],
            cwd=modm_root,
            capture_output=True,
            text=True,
            check=False,
        )
    except (FileNotFoundError, OSError):
        return
    if out.returncode != 0:
        return
    actual = out.stdout.strip()
    if actual == expected:
        return
    if accept_stale_sources:
        return
    raise StageExecutionError(
        f"modm-devices source-pin drift: data/source_pins.toml pins {expected!r} "
        f"but checkout at {modm_root} is {actual!r}.  Update the pin or pass "
        f"--accept-stale-sources to override."
    )
