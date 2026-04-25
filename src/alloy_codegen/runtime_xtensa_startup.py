"""Generated runtime startup for dual-core Xtensa devices (ESP32, ESP32-S3).

The Xtensa families admitted by alloy-codegen — ESP32 (LX6) and ESP32-S3
(LX7) — are dual-core SoCs.  This emitter models them as such: it produces
two vector tables (``_vectors_cpu0[]`` / ``_vectors_cpu1[]``), two reset
entry points (``Reset_Handler`` for PRO_CPU and ``Reset_Handler_CPU1`` for
APP_CPU), and a ``bring_up_app_cpu()`` primitive that the application calls
when it wants the second core running.

Affinity routing of *individual* peripheral interrupts (``esp_intr_alloc``
behaviour) and inter-core synchronization primitives (IPI senders, queues,
spinlocks) are explicitly out of scope for the bootstrap contract — those
are framework concerns and applications use esp-idf or a hand-rolled layer
to provide them.

The ESP32-S3 ROM bootloader does most of the Xtensa-specific work for
PRO_CPU before our generated startup runs:

- initialises the PRO-CPU stack pointer;
- sets PRO_CPU's ``VECBASE`` to a fixed in-ROM address;
- loads the app image from flash into IRAM/DRAM;
- transfers control to ``call_start_cpu0`` in the application image.

After ROM transfers control to ``Reset_Handler`` we clear ``.bss``, copy
``.data``, call ``SystemInit``, run C++ ctors, and tail-call ``main()``.
``Reset_Handler_CPU1`` skips static init (already done by PRO_CPU) and
either calls a weak ``app_main_cpu1()`` if the application defines one or
spins in ``Default_Handler``.

Host smoke builds (``ALLOY_CODEGEN_HOST_SMOKE``) compile with a generic
``c++`` and see the same portable C / C++ body; they do not exercise any
Xtensa-specific attributes or sections.
"""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR, VectorSlotDescriptor
from alloy_codegen.reporting import EmittedArtifact

from .emission import _cpp_artifact, _device_generated_path


def _is_xtensa_device(device: CanonicalDeviceIR) -> bool:
    return device.identity.core.lower().startswith("xtensa")


def _bring_up_app_cpu_body(device: CanonicalDeviceIR) -> tuple[str, ...]:
    """Return the C++ body lines for ``bring_up_app_cpu()``.

    The function differs by family:

    - **ESP32 classic (LX6)**: writes ``DPORT.APPCPU_CTRL_B`` bit 0 to
      release APP_CPU.  ROM has already configured APP_CPU's VECBASE to
      ``Reset_Handler_CPU1``-equivalent; we just unhold it.
    - **ESP32-S3 (LX7)**: enables ``SYSTEM.CORE_1_CONTROL_0.CLKGATE_EN``
      then clears ``SYSTEM.CORE_1_CONTROL_1.RUNSTALL`` to let APP_CPU
      execute.

    On host smoke builds the body is empty (the registers don't exist).
    """
    core = device.identity.core.lower()
    if core == "xtensa-lx6":
        return (
            "    // ESP32 classic: write DPORT.APPCPU_CTRL_B bit 0 (APPCPU_CLKGATE_EN)",
            "    // to release APP_CPU from reset.  ROM has already pointed APP_CPU's",
            "    // VECBASE at the application image; this just unholds it.",
            "    auto* const dport_appcpu_ctrl_b = reinterpret_cast<volatile std::uint32_t*>(",
            "        0x3FF0'0030u);",
            "    *dport_appcpu_ctrl_b = 1u;",
        )
    if core == "xtensa-lx7":
        return (
            "    // ESP32-S3: clock-gate APP_CPU then clear its runstall.",
            "    auto* const sys_core_1_ctrl_0 = reinterpret_cast<volatile std::uint32_t*>(",
            "        0x6000'8000u + 0x0DCu);  // SYSTEM.CORE_1_CONTROL_0",
            "    auto* const sys_core_1_ctrl_1 = reinterpret_cast<volatile std::uint32_t*>(",
            "        0x6000'8000u + 0x0E0u);  // SYSTEM.CORE_1_CONTROL_1",
            "    *sys_core_1_ctrl_0 |= (1u << 1);   // CONTROL_CORE_1_CLKGATE_EN",
            "    *sys_core_1_ctrl_1 &= ~(1u << 0);  // CONTROL_CORE_1_RUNSTALL",
        )
    # Unknown Xtensa core: keep emission deterministic but document the gap.
    return (
        f"    // No bring-up sequence registered for core '{device.identity.core}'.",
        "    // Application must implement APP_CPU release manually.",
    )


def _vector_table_rows(
    *,
    slots: list[VectorSlotDescriptor],
    target_core: str,
) -> list[str]:
    """Build the rows of one ``_vectors_cpuN[]`` table.

    ``shared`` slots appear in both per-core tables.  Slots are ordered by
    slot index and missing slots get ``nullptr`` rows so debuggers see a
    contiguous symbol table.
    """
    affine = [
        slot
        for slot in slots
        if slot.core_affinity == target_core or slot.core_affinity == "shared"
    ]
    if not affine:
        return ["    nullptr,"]
    max_slot = max(slot.slot for slot in affine)
    by_slot = {slot.slot: slot for slot in affine}
    rows: list[str] = []
    for index in range(max_slot + 1):
        existing = by_slot.get(index)
        if existing is None:
            rows.append("    nullptr,")
        else:
            rows.append(f"    {existing.symbol_name},")
    return rows


def emit_xtensa_startup_source(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit a startup.cpp for a Xtensa device (ESP32 LX6 / ESP32-S3 LX7).

    The emitter is dual-core-aware: each device's vector slots carry a
    ``core_affinity`` field that partitions them between PRO_CPU and APP_CPU.
    Two vector tables, two reset entry points, and a ``bring_up_app_cpu()``
    primitive are emitted.  Affinity routing of individual interrupts and
    inter-core synchronization primitives are NOT emitted — applications
    layer those concerns on top via esp-idf or hand-rolled code.

    Unlike the Cortex-M emitter this file:

    - Does NOT place a ``_vectors[]`` function-pointer table at address 0.
      Xtensa uses ``VECBASE`` to point exception vectors at internal ROM by
      default; the ROM bootloader owns those vectors for PRO_CPU.
      ``bring_up_app_cpu()`` is the bridge that lets APP_CPU start running
      against the application image.
    - Does NOT emit ``__attribute__((interrupt))`` on peripheral handlers.
      Xtensa uses framework-specific macros (``esp_intr_alloc``) provided by
      esp-idf at the application layer; the bootstrap startup only supplies
      weak ``*_IRQHandler`` stubs defaulting to Default_Handler.
    """
    sorted_slots = sorted(device.vector_slots, key=lambda slot: slot.slot)
    peripheral_symbols = sorted(
        {
            slot.symbol_name
            for slot in sorted_slots
            if slot.slot >= 16 and slot.symbol_name != "Reset_Handler"
        }
    )

    cpu0_rows = _vector_table_rows(slots=sorted_slots, target_core="cpu0")
    cpu1_rows = _vector_table_rows(slots=sorted_slots, target_core="cpu1")

    bringup_body = _bring_up_app_cpu_body(device)

    content = "\n".join(
        [
            "#include <cstdint>",
            "",
            f'#include "../../runtime/devices/{device.identity.device}/startup.hpp"',
            "",
            "// Dual-core Xtensa control plane (ESP32 LX6 / ESP32-S3 LX7):",
            "//   * The ROM bootloader owns PRO_CPU's VECBASE and initial stack setup.",
            "//   * This generated file provides BSS/data init, C++ ctor dispatch,",
            "//     main() entry, weak peripheral IRQ stubs, AND APP_CPU bring-up.",
            "//   * Per-core vector tables are exposed for inspection and for linker",
            "//     scripts that map them into the per-core VECBASE regions.",
            "//   * Inter-core synchronization (IPI senders, spinlocks, queues) is",
            "//     intentionally NOT modelled here — applications layer those on top",
            "//     via esp-idf or a hand-rolled IPC layer.",
            "",
            'extern "C" {',
            "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
            "std::uint32_t __stack_top = 0u;",
            "std::uint32_t __stack_top_cpu1 = 0u;",
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
            "extern std::uint32_t __stack_top_cpu1;",
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
            "// Weak hook applications can override to run code on APP_CPU after",
            "// bring_up_app_cpu() releases it.  The default empty implementation",
            "// returns immediately, after which Reset_Handler_CPU1 falls into",
            "// Default_Handler.",
            "void app_main_cpu1() __attribute__((weak));",
            "void app_main_cpu1() {}",
            "",
            "[[noreturn]] void Default_Handler() {",
            "    while (true) {}",
            "}",
            "",
            # Weak handler stubs.  Xtensa does not have a portable
            # ``__attribute__((interrupt))`` that works with `c++` on the
            # host; the ESP32 toolchain provides framework macros to promote
            # application-level handlers.  Leaving the attribute off here
            # keeps the bootstrap portable.
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
            "// PRO_CPU entry — runs after the ROM bootloader transfers control to",
            "// the application image.  VECBASE, stack, and cache have already been",
            "// set up by ROM code for this core.",
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
            "// APP_CPU entry — invoked after bring_up_app_cpu() releases the second",
            "// core.  Static init has already been performed by PRO_CPU; this entry",
            "// only dispatches into the optional weak app_main_cpu1() hook and then",
            "// stops.  Applications that want richer cpu1 behaviour override that",
            "// hook (e.g. by linking against esp-idf or providing their own).",
            "[[noreturn]] void Reset_Handler_CPU1() {",
            "    app_main_cpu1();",
            "    Default_Handler();",
            "}",
            "",
            "// Application-callable bring-up routine.  Not invoked from",
            "// Reset_Handler; PRO_CPU calls this when it wants APP_CPU running.",
            "void bring_up_app_cpu() {",
            "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
            "    // Host smoke: registers don't exist in this address space.",
            "    return;",
            "#else",
            *bringup_body,
            "#endif",
            "}",
            "",
            "// Per-core vector tables.  Xtensa uses VECBASE per core; linker scripts",
            "// for real targets place these in distinct sections so each core's",
            "// VECBASE points to its own table.  Host smoke builds keep the symbols",
            "// reachable for inspection but skip the section attribute.",
            "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
            "__attribute__((used))",
            "#else",
            '__attribute__((section(".xtensa_vectors_cpu0"), used))',
            "#endif",
            "void (*const _vectors_cpu0[])() = {",
            *cpu0_rows,
            "};",
            "",
            "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
            "__attribute__((used))",
            "#else",
            '__attribute__((section(".xtensa_vectors_cpu1"), used))',
            "#endif",
            "void (*const _vectors_cpu1[])() = {",
            *cpu1_rows,
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
