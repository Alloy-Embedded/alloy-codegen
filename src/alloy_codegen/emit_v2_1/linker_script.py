"""Emit a GNU LD linker script from a v2.1 :class:`CanonicalDevice`.

Demonstrates end-to-end consumption of the v2.1 IR:

* `memory[]` regions feed `MEMORY` blocks (with `address_space` and
  `backing` distinguishing Harvard chips and external XIP flash).
* `identity.core.multicore` drives per-core `_estack` symbols on
  dual-core chips.
* `memory[].alias` resolves to the conventional ``code`` / ``data``
  aliases the C runtime expects.

Output format follows the layout shipped with most CMSIS templates:

```
ENTRY(Reset_Handler)

MEMORY {
    flash (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
    sram  (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

_estack    = ORIGIN(sram) + LENGTH(sram);
_sram_size = LENGTH(sram);
```

This is a minimal viable emitter — it lays down the skeleton; section
placement (`.text`, `.data`, `.bss`, …) is left to the C runtime
boilerplate that is not chip-specific.
"""

from __future__ import annotations

from alloy_codegen.ir.v2_1 import CanonicalDevice, MemoryRegion


def _format_size(size: str) -> str:
    """Pass through the human-readable size string.

    The schema enforces ``<int|float>(B|KB|MB|GB)`` already, and GNU
    LD speaks the same language (``K`` / ``M`` are accepted, ``KB``
    works on modern lds; we strip the trailing ``B`` to be safe).
    """
    return size.rstrip("B").upper() if size.endswith(("KB", "MB", "GB")) else size


def _format_origin(base: int) -> str:
    return f"0x{base:08X}"


def _emit_memory_block(regions: tuple[MemoryRegion, ...]) -> list[str]:
    out = ["MEMORY {"]
    name_width = max(len(r.id) for r in regions)
    for region in regions:
        if region.role in {"factory-rom", "factory-rom-data", "otp",
                            "configuration-bits", "protection-bits", "factory-info-config"}:
            # Read-only factory regions: declare them so user code
            # can refer to symbols, but never place sections there.
            out.append(
                f"    {region.id:<{name_width}} ({region.access})"
                f" : ORIGIN = {_format_origin(region.base)}, LENGTH = {_format_size(region.size)}"
                f"  /* {region.role} — declared, no section placement */"
            )
            continue
        comment = ""
        if region.address_space == "program":
            comment = "  /* Harvard program space */"
        elif region.address_space in {"data", "instruction"}:
            comment = f"  /* Harvard {region.address_space} space */"
        elif region.backing == "external-spi-flash":
            comment = "  /* XIP-mapped external SPI flash */"
        elif region.backing == "external-qspi-flash":
            comment = "  /* XIP-mapped external QSPI flash */"
        out.append(
            f"    {region.id:<{name_width}} ({region.access})"
            f" : ORIGIN = {_format_origin(region.base)}, LENGTH = {_format_size(region.size)}{comment}"
        )
    out.append("}")
    return out


def _emit_aliases_and_symbols(device: CanonicalDevice) -> list[str]:
    out: list[str] = []
    code_region = next((r for r in device.memory if r.alias == "code"), None)
    data_region = next((r for r in device.memory if r.alias == "data"), None)

    if data_region is not None:
        out.append(f"_estack    = ORIGIN({data_region.id}) + LENGTH({data_region.id});")

    # Per-core stacks for dual-core chips.
    if device.identity.core.multicore is not None:
        for core in device.identity.core.multicore.cores:
            scratch_id = (
                f"sram_bank{4 if core.role == 'primary' or core.role == 'pro_cpu' else 5}"
            )
            scratch_region = next(
                (r for r in device.memory if r.id == scratch_id), None
            )
            if scratch_region is not None:
                out.append(
                    f"_estack_{core.id} = ORIGIN({scratch_region.id})"
                    f" + LENGTH({scratch_region.id});"
                )

    if code_region is not None:
        out.append(f"_text_origin = ORIGIN({code_region.id});")
        out.append(f"_text_length = LENGTH({code_region.id});")
    return out


def emit_linker_script(device: CanonicalDevice) -> str:
    """Render a GNU LD linker script for ``device``."""
    lines = [
        f"/* Linker script for {device.identity.vendor}/{device.identity.family}/{device.identity.device}",
        " *",
        f" * Core: {device.identity.core.name} ({device.identity.core.bits}-bit, "
        f"{device.identity.core.isa})",
    ]
    if device.identity.description:
        for desc_line in device.identity.description.splitlines():
            lines.append(f" * {desc_line}".rstrip())
    lines.append(" *")
    lines.append(f" * Schema: {device.schema}")
    lines.append(f" * Provenance: {device.provenance.primary}")
    lines.append(" */")
    lines.append("")
    lines.append("ENTRY(Reset_Handler)")
    lines.append("")
    lines.extend(_emit_memory_block(device.memory))
    lines.append("")
    lines.extend(_emit_aliases_and_symbols(device))
    lines.append("")
    return "\n".join(lines) + "\n"
