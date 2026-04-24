"""Generated runtime startup for RISC-V devices (e.g. ESP32-C3).

RISC-V uses a flat interrupt controller (CLIC / PLIC) rather than the ARM
Cortex-M vector table.  The startup contract differs in two key ways:

1. There is no "initial stack pointer" stored at vector table slot 0.  The
   stack pointer is initialised explicitly in early-startup assembly or C code.

2. The interrupt entry-point table (when used in vectored CLIC mode) is a flat
   array of function pointers indexed by hardware interrupt cause number, NOT
   by the ARM NVIC exception table layout.

This module emits:
- ``startup.cpp``     – Reset_Handler (BSS/data init, calls main())
- ``startup_vectors.cpp`` – thin wrapper that includes startup.hpp
"""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import _cpp_artifact, _device_generated_path

STARTUP_VECTORS_HEADER = "startup.hpp"


def _is_riscv_device(device: CanonicalDeviceIR) -> bool:
    core = device.identity.core.lower()
    return core.startswith("rv") or core == "riscv"


def emit_riscv_startup_source(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit a RISC-V startup.cpp that uses mtvec/CLIC conventions.

    Unlike the Cortex-M path:
    - No ARM-style ``_vectors[]`` placed at address 0 via the linker.
    - ``Reset_Handler`` initialises the stack pointer explicitly, then does
      the standard BSS-zero / data-copy / constructor-call / main() sequence.
    - Interrupt handlers are defined as ``__attribute__((interrupt))`` so the
      compiler emits proper RISC-V MRET-based return sequences.
    - The peripheral interrupt handlers are placed in a ``__attribute__((used))``
      table at ``.isr_vector`` so linker scripts that define that section work
      consistently across architectures.  The ESP32-C3 ROM bootloader initialises
      mtvec to the same address on startup.
    """
    slot_map = {vector_slot.slot: vector_slot.symbol_name for vector_slot in device.vector_slots}
    max_slot = max(slot_map) if slot_map else 0

    # RISC-V peripheral interrupt handlers (slots 16+)
    peripheral_symbols = sorted(
        {
            symbol_name
            for slot, symbol_name in slot_map.items()
            if slot >= 16
        }
    )

    vector_rows: list[str] = []
    for slot in range(max_slot + 1):
        symbol_name = slot_map.get(slot)
        if symbol_name is None:
            vector_rows.append("    nullptr,")
        elif slot == 0:
            # Slot 0 for RISC-V is the Reset_Handler (not __stack_top).
            vector_rows.append(f"    {symbol_name},")
        else:
            vector_rows.append(f"    {symbol_name},")

    content = "\n".join(
        [
            "#include <cstdint>",
            "",
            f'#include "../../runtime/devices/{device.identity.device}/startup.hpp"',
            "",
            'extern "C" {',
            "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
            "std::uint32_t __stack_top = 0u;",
            "std::uint32_t _sidata = 0u;",
            "std::uint32_t _sdata = 0u;",
            "std::uint32_t _edata = 0u;",
            "std::uint32_t _sbss = 0u;",
            "std::uint32_t _ebss = 0u;",
            "using InitFn = void (*)();",
            "InitFn __init_array_start[] = {nullptr};",
            "InitFn __init_array_end[] = {nullptr};",
            "#else",
            "extern std::uint32_t __stack_top;",
            "extern std::uint32_t _sidata;",
            "extern std::uint32_t _sdata;",
            "extern std::uint32_t _edata;",
            "extern std::uint32_t _sbss;",
            "extern std::uint32_t _ebss;",
            "extern void (*__init_array_start[])();",
            "extern void (*__init_array_end[])();",
            "#endif",
            "#if defined(__clang__)",
            "#pragma clang diagnostic push",
            '#pragma clang diagnostic ignored "-Wmain"',
            "#endif",
            "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
            "int alloy_codegen_host_smoke_entry();",
            "#else",
            "int main();",
            "#endif",
            "#if defined(__clang__)",
            "#pragma clang diagnostic pop",
            "#endif",
            "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
            "int alloy_codegen_host_smoke_entry() {",
            "    return 0;",
            "}",
            "#endif",
            "void SystemInit() __attribute__((weak));",
            "void SystemInit() {}",
            "",
            "[[noreturn]] void Default_Handler() {",
            "    while (true) {}",
            "}",
            "",
            # RISC-V interrupt handlers use `__attribute__((interrupt))` so the
            # compiler emits an MRET-based return sequence.  Host-only smoke
            # builds (ALLOY_CODEGEN_HOST_SMOKE) compile with a generic x86/arm
            # `c++` and reject the attribute with -Werror=unknown-attributes, so
            # we emit the attribute only for real embedded builds.
            *[
                line
                for symbol_name in peripheral_symbols
                for line in (
                    "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
                    f"void {symbol_name}() __attribute__((weak));",
                    "#else",
                    f"void {symbol_name}() __attribute__((weak, interrupt));",
                    "#endif",
                    f"void {symbol_name}() {{",
                    "    Default_Handler();",
                    "}",
                    "",
                )
            ],
            "// Reset_Handler is the RISC-V entry point invoked by the ROM bootloader.",
            "// It initialises the stack, clears BSS, copies initialised data, runs",
            "// C++ constructors, then calls main().",
            "[[noreturn]] void Reset_Handler() {",
            "    // Initialise stack pointer.",
            "#if !defined(ALLOY_CODEGEN_HOST_SMOKE)",
            "    __asm__ volatile(",
            '        "la sp, __stack_top\\n"',
            "    );",
            "#endif",
            "    auto* copy_source = &_sidata;",
            "    auto* copy_target = &_sdata;",
            "    while (copy_target < &_edata) {",
            "        *copy_target++ = *copy_source++;",
            "    }",
            "    auto* zero_target = &_sbss;",
            "    while (zero_target < &_ebss) {",
            "        *zero_target++ = 0u;",
            "    }",
            "    SystemInit();",
            "    for (auto ctor = __init_array_start; ctor < __init_array_end; ++ctor) {",
            "        if (*ctor != nullptr) {",
            "            (*ctor)();",
            "        }",
            "    }",
            "#if defined(__clang__)",
            "#pragma clang diagnostic push",
            '#pragma clang diagnostic ignored "-Wmain"',
            "#endif",
            "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
            "    static_cast<void>(alloy_codegen_host_smoke_entry());",
            "#else",
            "    static_cast<void>(main());",
            "#endif",
            "#if defined(__clang__)",
            "#pragma clang diagnostic pop",
            "#endif",
            "    Default_Handler();",
            "}",
            "",
            "// RISC-V vectored CLIC interrupt table.  mtvec is set to the base of",
            "// _vectors[] with MODE=1 (vectored) by the ROM bootloader or early startup.",
            "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
            "__attribute__((used))",
            "#else",
            '__attribute__((section(".isr_vector"), used))',
            "#endif",
            "void (*const _vectors[])() = {",
            *vector_rows,
            "};",
            "}",
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "startup.cpp"),
        content=content,
    )


def emit_riscv_startup_vectors_source(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit a thin startup_vectors.cpp wrapper for RISC-V devices."""
    content = "\n".join(
        [
            f'#include "../../runtime/devices/{device.identity.device}/startup.hpp"',
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "startup_vectors.cpp"),
        content=content,
    )
