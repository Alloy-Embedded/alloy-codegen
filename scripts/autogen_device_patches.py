"""Auto-generate a device patch JSON skeleton from CMSIS-SVD (+
optional CMSIS-Pack PDSC).

Added by ``autogen-device-patches-from-svd`` — cuts the manual
per-device patch surface from ~180 LOC to ~30 LOC of human review.

The generator extracts the mechanical 80% of a device patch:

* Identity (``device``, ``svd_file``, ``core`` when ``<cpu>`` is
  present in the SVD).
* Peripheral instance list (sorted by name).
* Interrupt vector table (sorted by line, then name).
* Memory regions (only when a CMSIS-Pack PDSC is supplied — SVD
  alone has no flash/sram declaration).

Fields the generator cannot derive ship as ``"TODO_REVIEW"``
sentinels and are also recorded under the top-level
``"$todo_review"`` array so a reviewer can see at a glance what is
unfinished.

The output is byte-deterministic given the same inputs: keys are
emitted in a fixed order, lists are sorted, JSON is dumped with
``indent=2`` and ``ensure_ascii=False``.

CLI:

    python -m scripts.autogen_device_patches \\
        --vendor st --family stm32g0 --device stm32g071rb \\
        --svd path/to/STM32G071.svd \\
        [--pack path/to/pack.pdsc] \\
        [--out path/to/devices/stm32g071rb.json]

If ``--out`` is omitted the JSON is written to stdout.
"""

from __future__ import annotations

import argparse
import json
import sys
import xml.etree.ElementTree as ET
from collections.abc import Iterable
from dataclasses import dataclass
from pathlib import Path

# Make the repo's ``src`` importable when the script is run via
# ``python scripts/autogen_device_patches.py``.
_REPO_ROOT = Path(__file__).resolve().parents[1]
_SRC = _REPO_ROOT / "src"
if str(_SRC) not in sys.path:
    sys.path.insert(0, str(_SRC))

from alloy_codegen.sources.cmsis_svd import (  # noqa: E402  — sys.path tweak above
    parse_raw_device_document,
)

GENERATOR_VERSION = 1
TODO_SENTINEL = "TODO_REVIEW"

# Tier 2/3/4 fields the generator cannot synthesise from SVD/PDSC
# alone.  Emitted as empty lists with a top-level ``$todo_review``
# entry so the reviewer knows to populate them.
TIER_234_LIST_FIELDS: tuple[str, ...] = (
    # ADC
    "adc_internal_channels",
    "adc_calibration_data_points",
    "adc_resolution_options",
    "adc_sample_time_options",
    "adc_oversampling_options",
    "adc_external_triggers",
    # Clock profiles
    "system_clock_profiles",
    # DMA
    "dma_request_refs",
    # UART
    "uart_baud_clock_sources",
    "uart_baud_oversampling_options",
    "uart_fifo_trigger_options",
    "uart_data_bits_options",
    "uart_parity_options",
    "uart_stop_bits_options",
    "uart_mode_flags",
    # SPI
    "spi_baud_prescaler_options",
    "spi_frame_size_options",
    "spi_fifo_threshold_options",
    "spi_mode_flags",
    # Timer / PWM
    "timer_prescaler_options",
    "timer_trigger_sources",
    "timer_master_outputs",
    "timer_mode_flags",
    "pwm_deadtime_options",
    "pwm_alignment_options",
    "pwm_break_inputs",
    "pwm_mode_flags",
    # I2C
    "i2c_speed_options",
    "i2c_timing_presets",
    "i2c_mode_flags",
    # Cross-peripheral
    "peripheral_max_clock_hz",
)

# Hand-curated fields the reviewer must fill in.  Their default
# values are sentinel strings or ``null`` per type.
TIER_234_SCALAR_FIELDS: tuple[tuple[str, object], ...] = (
    ("uart_max_baud_hz", None),
    ("adc_max_clock_hz", None),
    ("adc_calibration_context", None),
)


@dataclass(frozen=True)
class CpuInfo:
    name: str | None
    revision: str | None
    fpu: bool


def _parse_cpu(svd_path: Path) -> CpuInfo:
    """Extract the ``<cpu>`` block from an SVD if present."""
    root = ET.parse(svd_path).getroot()
    cpu = root.find("cpu")
    if cpu is None:
        return CpuInfo(name=None, revision=None, fpu=False)
    name = cpu.findtext("name")
    revision = cpu.findtext("revision")
    fpu = (cpu.findtext("fpuPresent") or "false").strip().lower() == "true"
    return CpuInfo(
        name=name.strip() if name else None,
        revision=revision.strip() if revision else None,
        fpu=fpu,
    )


# Map SVD ``<cpu><name>`` values to alloy-codegen canonical core
# strings (the values that already appear in admitted patches).
_CPU_NAME_TO_CORE = {
    "CM0": "cortex-m0",
    "CM0PLUS": "cortex-m0plus",
    "CM0+": "cortex-m0plus",
    "CM3": "cortex-m3",
    "CM4": "cortex-m4",
    "CM7": "cortex-m7",
    "CM23": "cortex-m23",
    "CM33": "cortex-m33",
    "CM55": "cortex-m55",
}


def _resolve_core(cpu: CpuInfo) -> str | None:
    """Best-effort SVD CPU → alloy-codegen core string."""
    if cpu.name is None:
        return None
    base = _CPU_NAME_TO_CORE.get(cpu.name.upper())
    if base is None:
        return None
    if cpu.fpu and base in {"cortex-m4", "cortex-m7"}:
        return f"{base}f"
    return base


def _parse_pdsc_memories(pdsc_path: Path, device: str) -> list[dict]:
    """Extract `<memory>` regions for a device from a CMSIS-Pack
    PDSC.  Best-effort — PDSC schemas vary across vendors."""
    root = ET.parse(pdsc_path).getroot()
    memories: list[dict] = []
    # PDSCs declare memory both at family level (in ``<memory>``
    # elements directly under ``<device>``) and under
    # ``<environment>`` / ``<book>`` etc.  We accept any
    # ``<memory>`` whose ancestor ``<device>`` matches the requested
    # device name (case-insensitive).
    for device_node in root.iter("device"):
        dev_name = (device_node.get("Dname") or device_node.get("name") or "").lower()
        if device.lower() not in dev_name:
            continue
        for memory in device_node.iter("memory"):
            mem_name = (memory.get("name") or memory.get("id") or "").strip()
            start = memory.get("start") or memory.get("address")
            size = memory.get("size")
            access = memory.get("access") or ""
            if not (mem_name and start and size):
                continue
            try:
                base_address = int(start, 0)
                size_bytes = int(size, 0)
            except ValueError:
                continue
            kind_lower = mem_name.lower()
            if "flash" in kind_lower or "rom" in kind_lower:
                kind = "flash"
            elif "ram" in kind_lower:
                kind = "sram"
            else:
                kind = TODO_SENTINEL
            memories.append(
                {
                    "name": mem_name.lower(),
                    "kind": kind,
                    "base_address": base_address,
                    "size_bytes": size_bytes,
                    "access": access.lower() or TODO_SENTINEL,
                }
            )
    # Deterministic order: by base address ascending.
    memories.sort(key=lambda m: (m["base_address"], m["name"]))
    return memories


def _peripheral_names(raw_peripherals: Iterable) -> list[str]:
    return sorted({periph.name for periph in raw_peripherals})


def _interrupt_rows(raw_interrupts: Iterable) -> list[dict]:
    rows = [
        {
            "name": irq.name,
            "line": irq.line,
            "peripheral": irq.peripheral or TODO_SENTINEL,
        }
        for irq in raw_interrupts
    ]
    rows.sort(key=lambda r: (r["line"], r["name"]))
    return rows


def build_patch(
    *,
    vendor: str,
    family: str,
    device: str,
    svd_path: Path,
    pack_path: Path | None,
) -> dict:
    """Build the autogen patch dict for one device."""
    raw_doc = parse_raw_device_document(svd_path)
    cpu = _parse_cpu(svd_path)
    core = _resolve_core(cpu)

    todo_review: list[str] = []

    if core is None:
        core_value: object = TODO_SENTINEL
        todo_review.append("core")
    else:
        core_value = core

    memories = _parse_pdsc_memories(pack_path, device) if pack_path else []
    if not memories:
        todo_review.append("memories")

    if pack_path is None:
        todo_review.append("package")
        package_value: object = TODO_SENTINEL
    else:
        package_value = TODO_SENTINEL  # PDSC carries package candidates; pick is human
        todo_review.append("package")

    # The pin-data file is vendor-specific (STM32 open-pin-data,
    # Microchip ATDF, NXP MEX, etc.).  Generator cannot synthesise it.
    todo_review.append("pin_data_file")
    todo_review.append("summary")

    todo_review.extend(TIER_234_LIST_FIELDS)
    todo_review.extend(name for name, _ in TIER_234_SCALAR_FIELDS)
    todo_review.sort()

    patch: dict[str, object] = {
        "patch_id": f"{vendor}-{family}-{device}-autogen-bootstrap",
        "$autogen": {
            "generator": "scripts/autogen_device_patches.py",
            "generator_version": GENERATOR_VERSION,
            "svd_file": svd_path.name,
            "pack_file": pack_path.name if pack_path else None,
        },
        "$todo_review": todo_review,
        "device": device,
        "svd_file": svd_path.name,
        "pin_data_file": TODO_SENTINEL,
        "package": package_value,
        "core": core_value,
        "summary": (
            f"TODO_REVIEW: autogenerated bootstrap patch for "
            f"{vendor}/{family}/{device}.  Replace this summary "
            "with a human-authored device description."
        ),
        "memories": memories,
        "peripherals": _peripheral_names(raw_doc.peripherals),
        "interrupts": _interrupt_rows(raw_doc.interrupts),
    }

    # Tier 2/3/4 placeholders: empty lists for collection-shaped
    # fields; sentinel scalars otherwise.
    for name in TIER_234_LIST_FIELDS:
        patch[name] = []
    for name, default in TIER_234_SCALAR_FIELDS:
        patch[name] = default

    return patch


def emit_json(patch: dict) -> str:
    """Serialise the patch as deterministic JSON text."""
    return json.dumps(patch, indent=2, ensure_ascii=False) + "\n"


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        prog="autogen_device_patches",
        description=(
            "Generate a device patch JSON skeleton from CMSIS-SVD "
            "(+ optional CMSIS-Pack PDSC)."
        ),
    )
    parser.add_argument("--vendor", required=True)
    parser.add_argument("--family", required=True)
    parser.add_argument("--device", required=True)
    parser.add_argument("--svd", required=True, type=Path)
    parser.add_argument(
        "--pack",
        type=Path,
        default=None,
        help="Optional CMSIS-Pack PDSC path; when given, memory "
        "regions are extracted from it.",
    )
    parser.add_argument(
        "--out",
        type=Path,
        default=None,
        help="Output JSON path; defaults to stdout.",
    )
    args = parser.parse_args(argv)

    if not args.svd.exists():
        parser.error(f"SVD file not found: {args.svd}")
    if args.pack is not None and not args.pack.exists():
        parser.error(f"PDSC file not found: {args.pack}")

    patch = build_patch(
        vendor=args.vendor,
        family=args.family,
        device=args.device,
        svd_path=args.svd,
        pack_path=args.pack,
    )
    text = emit_json(patch)
    if args.out is None:
        sys.stdout.write(text)
    else:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(text, encoding="utf-8")
    return 0


if __name__ == "__main__":  # pragma: no cover
    raise SystemExit(main())
