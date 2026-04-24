"""Generated runtime startup for 8-bit AVR devices (e.g. AVR128DA32).

AVR has a fundamentally different startup contract than ARM Cortex-M and
RISC-V:

* The vector table lives in ``.section .vectors`` at the base of program
  flash and is a sequence of AVR ``jmp`` (or ``rjmp``) instructions, NOT a
  function-pointer array.  avr-gcc / avr-libc supplies ``crt<chip>.o`` that
  fills the table with jumps to weak ``__vector_N`` symbols, where ``N`` is
  the ATDF interrupt index.
* ``__vector_0`` is the reset vector.  avr-libc's crt0 provides a strong
  ``__vector_0`` that sets up the stack, zero-initialises .bss, copies .data
  from .rodata, runs ``.init_array`` entries, and tail-calls ``main()``.  In
  bootstrap generated output we therefore do NOT redeclare ``__vector_0`` —
  doing so would collide with crt0 at link time.
* Peripheral interrupts are named ``__vector_<line>`` (where ``<line>`` is
  the ATDF ``<interrupt index>`` attribute) and default to the ``__bad_interrupt``
  stub.  The codegen emits weak aliases from the canonical
  ``<NAME>_IRQHandler`` symbol to ``__vector_<line>`` so application code
  can reference either naming convention.

Host-only smoke builds (``ALLOY_CODEGEN_HOST_SMOKE``) compile with a
generic ``c++`` which knows nothing about AVR and would reject the
AVR-specific attributes.  The generated file guards every AVR-specific
line behind ``#if defined(__AVR__)``.
"""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import _cpp_artifact, _device_generated_path


def _is_avr_device(device: CanonicalDeviceIR) -> bool:
    return device.identity.core.lower().startswith("avr")


def emit_avr_startup_source(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit a startup.cpp for an AVR device.

    Unlike the Cortex-M / RISC-V emitters this file:

    - Does NOT redeclare ``__vector_0`` — avr-libc's crt0 owns reset.
    - Emits every peripheral interrupt twice:
      1. as a weak ``__vector_<line>()`` so avr-gcc's crt populates the
         ``.vectors`` section correctly;
      2. as a weak alias ``<NAME>_IRQHandler()`` pointing at the same
         default handler, so application code that references the IR's
         canonical handler names resolves.
    - Provides a host-compilable stub behind ``ALLOY_CODEGEN_HOST_SMOKE``
      so the Alloy consumer smoke can link the generated header without
      pulling in avr-libc.
    """
    # The IR's interrupt bindings carry the ATDF line (interrupt index).
    # Slot 0 is reset and owned by avr-libc crt0; we only emit handlers
    # for line > 0.
    handlers: list[tuple[int, str]] = sorted(
        {
            (binding.line, binding.symbol_name)
            for binding in device.interrupt_bindings
            if binding.symbol_name is not None and binding.line > 0
        }
    )

    content_lines: list[str] = [
        "#include <cstdint>",
        "",
        f'#include "../../runtime/devices/{device.identity.device}/startup.hpp"',
        "",
        "// AVR startup contract:",
        "//   * avr-libc's crt<chip>.o owns the reset vector (__vector_0) and the",
        "//     .vectors section; this file supplies only the weak peripheral",
        "//     handlers so unhandled interrupts trap cleanly.",
        "//   * Each entry is also aliased to the IR's canonical",
        "//     <NAME>_IRQHandler symbol so application code that references",
        "//     either convention resolves without link errors.",
        "",
        "#if defined(ALLOY_CODEGEN_HOST_SMOKE)",
        "// Host smoke build: provide stubs for the symbols the rest of the",
        "// runtime headers expect, but do not emit AVR-specific attributes.",
        'extern "C" {',
        "int alloy_codegen_host_smoke_entry();",
        "int alloy_codegen_host_smoke_entry() {",
        "    return 0;",
        "}",
        "}",
        "#elif defined(__AVR__)",
        'extern "C" {',
        "",
        "// Default trap — avr-libc supplies __bad_interrupt but we keep a local",
        "// symbol so the weak aliases below have a single target to point at.",
        "[[noreturn]] void Default_Handler() {",
        "    while (true) {}",
        "}",
        "",
    ]

    # Emit __vector_<line> weak symbols + canonical <NAME>_IRQHandler
    # aliases for every peripheral interrupt.
    for line, symbol_name in handlers:
        content_lines.extend(
            (
                f'void __vector_{line}() __attribute__((weak, alias("Default_Handler")));',
                f'void {symbol_name}() __attribute__((weak, alias("__vector_{line}")));',
            )
        )

    content_lines.extend(
        (
            "",
            '}  // extern "C"',
            "#else",
            "// Non-AVR target build: nothing to emit — avr-libc's crt0 is",
            "// AVR-specific and irrelevant when cross-compiling on the host.",
            "#endif",
            "",
        )
    )

    content = "\n".join(content_lines)
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "startup.cpp"),
        content=content,
    )


def emit_avr_startup_vectors_source(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit a thin startup_vectors.cpp wrapper for AVR devices.

    The real AVR vector table is owned by avr-libc's crt0 (see
    :func:`emit_avr_startup_source` for details).  This file only pulls
    in the runtime startup.hpp so the per-family emit plan stays uniform
    across architectures — the per-device ``startup_vectors.cpp`` path
    exists for every admitted family.
    """
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
