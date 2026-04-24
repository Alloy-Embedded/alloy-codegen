"""Generated runtime startup for Xtensa devices (e.g. ESP32-S3).

The first admitted Xtensa device is ESP32-S3, a dual-core Xtensa LX7 SoC.
This bootstrap emitter takes the **single-core-perspective** documented in
the add-espressif-esp32-target design (Decision 4 of Phase 4):

* the generated artifact describes the control plane of core 0 only;
* core-1 startup sequencing and inter-core coordination are out of scope
  for this first cut — no AFFINITY / OWNERSHIP primitives are emitted;
* `INTERRUPT_CORE1` and its children are filtered out of the canonical
  IR upstream (see `_build_esp32_device_ir`), so the vector table here
  never references them.

The ESP32-S3 ROM bootloader does most of the Xtensa-specific work:

- initialises the PRO-CPU (core 0) stack pointer;
- sets `VECBASE` to a fixed in-ROM address;
- loads the app image from flash into IRAM/DRAM;
- transfers control to `call_start_cpu0` in the application image.

Our generated startup therefore only needs to run AFTER the ROM has
transferred control.  It clears .bss, copies .data, calls SystemInit,
runs C++ constructors, and tail-calls main() — no Xtensa ASM required
for the first-cut bootstrap.

Host smoke builds (`ALLOY_CODEGEN_HOST_SMOKE`) compile with a generic
`c++` and see the same portable C / C++ body; they do not exercise any
Xtensa-specific attributes or sections.
"""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import _cpp_artifact, _device_generated_path


def _is_xtensa_device(device: CanonicalDeviceIR) -> bool:
    return device.identity.core.lower().startswith("xtensa")


def emit_xtensa_startup_source(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit a startup.cpp for a Xtensa device (ESP32-S3, single-core-perspective).

    Unlike the Cortex-M emitter this file:

    - Does NOT place a ``_vectors[]`` function-pointer table at address 0.
      Xtensa uses ``VECBASE`` to point the exception vectors at internal
      ROM by default; the ESP32-S3 ROM bootloader owns those vectors.
    - Does NOT emit ``__attribute__((interrupt))`` on peripheral handlers.
      Xtensa uses ``__attribute__((naked))`` or framework-specific macros
      (``esp_intr_alloc``/``ISR``) that are provided by esp-idf when an
      application is linked against it; the bootstrap startup only
      supplies weak ``*_IRQHandler`` stubs defaulting to Default_Handler.
    - Is single-core-perspective: no core-1 bring-up, no affinity.
    """
    slot_map = {vector_slot.slot: vector_slot.symbol_name for vector_slot in device.vector_slots}
    # The connector-model baseline for Xtensa is just ``(0, "Reset_Handler")`` —
    # peripheral interrupts land at slot 16+.  Pull their symbols out for
    # the weak-handler block.
    peripheral_symbols = sorted(
        {symbol_name for slot, symbol_name in slot_map.items() if slot >= 16}
    )

    content = "\n".join(
        [
            "#include <cstdint>",
            "",
            f'#include "../../runtime/devices/{device.identity.device}/startup.hpp"',
            "",
            "// ESP32-S3 / Xtensa LX7 single-core-perspective startup.",
            "//   * The ROM bootloader owns VECBASE and initial stack setup.",
            "//   * This generated file provides BSS/data init, C++ ctor dispatch,",
            "//     main() entry, and weak peripheral IRQ stubs.",
            "//   * core-1 bring-up and inter-core primitives are intentionally",
            "//     NOT modelled in this first-cut bootstrap.",
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
            # Weak handler stubs.  Xtensa does not have a portable
            # ``__attribute__((interrupt))`` that works with `c++` on the
            # host; the ESP32-S3 toolchain provides framework macros to
            # promote application-level handlers.  Leaving the attribute
            # off here keeps the bootstrap portable.
            *[
                line
                for symbol_name in peripheral_symbols
                for line in (
                    f"void {symbol_name}() __attribute__((weak));",
                    f"void {symbol_name}() {{",
                    "    Default_Handler();",
                    "}",
                    "",
                )
            ],
            "// Reset_Handler runs after the ESP32-S3 ROM bootloader has",
            "// transferred control to the application image.  VECBASE,",
            "// stack, and cache have already been set up by ROM code.",
            "[[noreturn]] void Reset_Handler() {",
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
            "// Informational vector table — not used by the ESP32-S3 ROM,",
            "// which routes exceptions through VECBASE in ROM.  Kept for",
            "// debugger symbol-resolution parity with ARM/RISC-V emitters.",
            "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
            "__attribute__((used))",
            "#else",
            '__attribute__((section(".xtensa_vectors_info"), used))',
            "#endif",
            "void (*const _vectors_info[])() = {",
            "    Reset_Handler,",
            "};",
            "}",
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "startup.cpp"),
        content=content,
    )


def emit_xtensa_startup_vectors_source(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit a thin ``startup_vectors.cpp`` wrapper for Xtensa devices."""
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
