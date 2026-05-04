"""Emit a GNU LD linker script from a v2.1 :class:`CanonicalDevice`.

Demonstrates end-to-end consumption of the v2.1 IR:

* `memory[]` regions feed `MEMORY` blocks (with `address_space` and
  `backing` distinguishing Harvard chips and external XIP flash).
* `identity.core.multicore` drives per-core `_estack` symbols on
  dual-core chips.
* `memory[].alias` resolves to the conventional ``code`` / ``data``
  aliases the C runtime expects.

For ARM Cortex-M devices (armv6-m / armv7-m / armv7e-m / armv8-m) a
complete ``SECTIONS`` block is emitted with the symbol names consumed
by ``alloy::arch::cortex_m::startup.hpp``:

  ``_sidata`` / ``_sdata`` / ``_edata``  — .data copy (flash → RAM)
  ``_sbss``   / ``_ebss``                — .bss zero-fill range
  ``__init_array_start/end``             — C++ static constructors
  ``__stack_top`` (alias of ``_estack``) — initial SP in vector table
"""

from __future__ import annotations

from alloy_codegen.ir.v2_1 import CanonicalDevice, MemoryRegion

# ISA prefixes that identify ARM Cortex-M cores.
_ARM_CM_ISA = ("armv6-m", "armv7-m", "armv7e-m", "armv8-m")


def _is_arm_cortex_m(device: CanonicalDevice) -> bool:
    isa = device.identity.core.isa or ""
    return any(isa.startswith(p) for p in _ARM_CM_ISA)


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
        out.append(f"_estack     = ORIGIN({data_region.id}) + LENGTH({data_region.id});")
        # ARM Cortex-M vector table slot 0 expects __stack_top.
        if _is_arm_cortex_m(device):
            out.append(f"__stack_top = _estack;")

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


def _emit_sections_arm(code_id: str, data_id: str) -> list[str]:
    """Full SECTIONS block for ARM Cortex-M.

    Symbol names match ``alloy::arch::cortex_m::startup.hpp``:
    ``_sidata``, ``_sdata``, ``_edata``, ``_sbss``, ``_ebss``,
    ``__init_array_start/end``.
    """
    c = code_id
    d = data_id
    return [
        "SECTIONS",
        "{",
        f"    /* Vector table — must be first in {c}. */",
        f"    .isr_vector :",
        f"    {{",
        f"        . = ALIGN(4);",
        f"        KEEP(*(.isr_vector))",
        f"        . = ALIGN(4);",
        f"    }} > {c}",
        "",
        f"    .text :",
        f"    {{",
        f"        . = ALIGN(4);",
        f"        *(.text*)",
        f"        *(.rodata*)",
        f"        *(.glue_7)",
        f"        *(.glue_7t)",
        f"        *(.eh_frame)",
        f"        KEEP (*(.init))",
        f"        KEEP (*(.fini))",
        f"        . = ALIGN(4);",
        f"        _etext = .;",
        f"    }} > {c}",
        "",
        f"    /* ARM exception unwinding tables. */",
        f"    .ARM.extab :",
        f"    {{",
        f"        . = ALIGN(4);",
        f"        *(.ARM.extab* .gnu.linkonce.armextab.*)",
        f"        . = ALIGN(4);",
        f"    }} > {c}",
        "",
        f"    .ARM :",
        f"    {{",
        f"        . = ALIGN(4);",
        f"        __exidx_start = .;",
        f"        *(.ARM.exidx*)",
        f"        __exidx_end = .;",
        f"        . = ALIGN(4);",
        f"    }} > {c}",
        "",
        f"    /* C++ static-constructor / destructor tables. */",
        f"    .init_array :",
        f"    {{",
        f"        . = ALIGN(4);",
        f"        PROVIDE_HIDDEN (__init_array_start = .);",
        f"        KEEP (*(SORT(.init_array.*)))",
        f"        KEEP (*(.init_array*))",
        f"        PROVIDE_HIDDEN (__init_array_end = .);",
        f"        . = ALIGN(4);",
        f"    }} > {c}",
        "",
        f"    .fini_array :",
        f"    {{",
        f"        . = ALIGN(4);",
        f"        PROVIDE_HIDDEN (__fini_array_start = .);",
        f"        KEEP (*(SORT(.fini_array.*)))",
        f"        KEEP (*(.fini_array*))",
        f"        PROVIDE_HIDDEN (__fini_array_end = .);",
        f"        . = ALIGN(4);",
        f"    }} > {c}",
        "",
        f"    /* _sidata = LMA of .data (load address in {c}). */",
        f"    _sidata = LOADADDR(.data);",
        "",
        f"    .data :",
        f"    {{",
        f"        . = ALIGN(4);",
        f"        _sdata = .;",
        f"        *(.data*)",
        f"        . = ALIGN(4);",
        f"        _edata = .;",
        f"    }} > {d} AT> {c}",
        "",
        f"    .bss (NOLOAD) :",
        f"    {{",
        f"        . = ALIGN(4);",
        f"        _sbss = .;",
        f"        __bss_start__ = _sbss;",
        f"        *(.bss*)",
        f"        *(COMMON)",
        f"        . = ALIGN(4);",
        f"        _ebss = .;",
        f"        __bss_end__ = _ebss;",
        f"    }} > {d}",
        "",
        f"    /* Heap start — referenced by _sbrk in syscalls. */",
        f"    PROVIDE (_end  = .);",
        f"    PROVIDE (end   = .);",
        f"    PROVIDE (__heap_start = .);",
        "",
        f"    /* ELF build-attributes (no runtime impact). */",
        f"    .ARM.attributes 0 : {{ *(.ARM.attributes) }}",
        "}",
    ]


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

    if _is_arm_cortex_m(device):
        code_region = next((r for r in device.memory if r.alias == "code"), None)
        data_region = next((r for r in device.memory if r.alias == "data"), None)
        if code_region is not None and data_region is not None:
            lines.append("")
            lines.extend(_emit_sections_arm(code_region.id, data_region.id))

    lines.append("")
    return "\n".join(lines) + "\n"
