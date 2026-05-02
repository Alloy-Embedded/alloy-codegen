"""Emit ``system_init.c`` — typed Cortex-M bring-up helpers.

Foundational pass on the ``add-nvic-system-exception-init``
proposal.  Produces three runtime-lite helpers per device:

* ``alloy_system_init_fpu(void)`` — programs ``SCB->CPACR``
  (CP10 + CP11 full access) when the chip carries an FPU; empty
  body otherwise so consumers can call it unconditionally.
* ``alloy_system_init_mpu(void)`` — enables the MPU with
  ``PRIVDEFENA=1`` when the chip carries one; empty body
  otherwise.  Per-region configuration is intentionally out of
  scope (application-specific).
* ``alloy_system_init(void)`` — umbrella that calls
  ``_fpu()`` → ``_mpu()`` → ``alloy_nvic_apply_priorities()``
  in that order.  Documented to be called once at the top of
  ``Reset_Handler`` before C++ static init.

Backwards-compat note: the IR still carries
``core.fpu: bool`` / ``core.mpu: bool``.  This emitter derives
the FPU variant from ``(core.fpu, core.isa)``:

* ARMv7E-M (M4/M7) with fpu=True  → FPV4_SP_D16 / FPV5_*
  (same CPACR write — both use CP10/CP11)
* ARMv8-M.MAIN (M33/M55/M85) with fpu=True → FPV5_*
* All other ISAs / fpu=False → no-op body.

Once IR promotes ``core.fpu`` to a typed enum (proposal Tasks 1.2
+ 1.3), this dispatch swaps to a direct enum match.
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised import SynthesisedDevice
from alloy_codegen.ir.v2_1 import CanonicalDevice


def _is_armv7m_or_armv8m_main(isa: str) -> bool:
    """Cortex-M cores that have a CPACR + MPU."""
    isa = isa.lower()
    return any(
        token in isa for token in (
            "armv6-m", "armv7-m", "armv7e-m", "armv8-m", "armv8.1-m",
        )
    )


def _has_cortexm_mpu(core_mpu: bool, isa: str) -> bool:
    """Programmable MPU exists.  ARMv7-M / ARMv8-M PMSA shapes
    the same `MPU->CTRL` register layout for the bits this
    foundational helper writes."""
    return bool(core_mpu) and _is_armv7m_or_armv8m_main(isa)


def _has_cortexm_fpu(core_fpu: bool, isa: str) -> bool:
    """FPU enable lives in ``SCB->CPACR`` for ARMv7E-M (M4F, M7)
    and ARMv8-M FP variants.  The bit layout is identical across
    these — CP10/CP11 in bits [23:20]."""
    return bool(core_fpu) and _is_armv7m_or_armv8m_main(isa)


def emit_system_init(device: CanonicalDevice, _synthesised: SynthesisedDevice) -> str:
    """Render ``system_init.c`` for ``device``."""
    core = device.identity.core
    has_fpu = _has_cortexm_fpu(core.fpu, core.isa)
    has_mpu = _has_cortexm_mpu(core.mpu, core.isa)

    lines: list[str] = [
        "/* system_init.c",
        " *",
        f" * {device.identity.vendor}/{device.identity.family}/{device.identity.device}"
        f" — generated from {device.schema}",
        " *",
        f" * Core: {core.name} ({core.isa})",
        f" * FPU:  {'enabled (CP10/CP11)' if has_fpu else 'absent'}",
        f" * MPU:  {'enabled (PRIVDEFENA)' if has_mpu else 'absent'}",
        " *",
        " * Three helpers that may be called unconditionally — empty",
        " * bodies on chips that lack the feature so consumers don't",
        " * need #ifdef HAS_FPU / HAS_MPU guards.",
        " *",
        " * Documented call ordering (runtime-lite contract):",
        " *",
        " *   alloy_system_init_fpu()        // before C++ static init",
        " *   <C++ static initialisers run>",
        " *   alloy_system_init_mpu()        // before peripheral bring-up",
        " *   alloy_nvic_apply_priorities()  // before any IRQ enable",
        " *",
        " * The umbrella alloy_system_init() satisfies all three when",
        " * called once at the top of Reset_Handler.",
        " */",
        "#include <stdint.h>",
        "",
        "#ifndef ALLOY_SCB_BASE",
        "#define ALLOY_SCB_BASE  0xE000ED00u",
        "#endif",
        "#ifndef ALLOY_MPU_BASE",
        "#define ALLOY_MPU_BASE  0xE000ED90u",
        "#endif",
        "",
        "#ifndef __DSB",
        "#define __DSB() __asm__ volatile (\"dsb\" ::: \"memory\")",
        "#endif",
        "#ifndef __ISB",
        "#define __ISB() __asm__ volatile (\"isb\" ::: \"memory\")",
        "#endif",
        "",
        "extern void alloy_nvic_apply_priorities(void);",
        "",
    ]

    # ---- FPU helper -------------------------------------------------
    lines.append("void alloy_system_init_fpu(void) {")
    if has_fpu:
        lines.extend([
            "    /* CPACR: grant full access to CP10 and CP11 (FPU coprocessors). */",
            "    volatile uint32_t * const cpacr = (uint32_t *)(ALLOY_SCB_BASE + 0x88u);",
            "    *cpacr |= (0xFu << 20);",
            "    __DSB();",
            "    __ISB();",
        ])
    else:
        lines.append("    /* No FPU on this core — function intentionally a no-op. */")
    lines.append("}")
    lines.append("")

    # ---- MPU helper -------------------------------------------------
    lines.append("void alloy_system_init_mpu(void) {")
    if has_mpu:
        lines.extend([
            "    /* MPU->TYPE.DREGION reports the number of regions; bail if 0. */",
            "    volatile uint32_t * const mpu_type = (uint32_t *)(ALLOY_MPU_BASE + 0x00u);",
            "    volatile uint32_t * const mpu_ctrl = (uint32_t *)(ALLOY_MPU_BASE + 0x04u);",
            "    if (((*mpu_type >> 8) & 0xFFu) == 0u) {",
            "        return;  /* MPU implemented in spec but no regions — skip. */",
            "    }",
            "    /* PRIVDEFENA=1 (privileged code keeps the default map),",
            "     * ENABLE=1.  Region descriptors are app-specific and stay",
            "     * the consumer's responsibility. */",
            "    *mpu_ctrl = (1u << 2) | (1u << 0);",
            "    __DSB();",
            "    __ISB();",
        ])
    else:
        lines.append("    /* No MPU on this core — function intentionally a no-op. */")
    lines.append("}")
    lines.append("")

    # ---- Umbrella ---------------------------------------------------
    lines.extend([
        "void alloy_system_init(void) {",
        "    alloy_system_init_fpu();",
        "    alloy_system_init_mpu();",
        "    alloy_nvic_apply_priorities();",
        "}",
        "",
    ])
    return "\n".join(lines)


__all__ = ["emit_system_init"]
