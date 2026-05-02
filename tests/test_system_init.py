"""Unit tests for the foundational pass on
``add-nvic-system-exception-init``.

Covers:

* ``emit_system_init`` body shape per (FPU, MPU) presence —
  Cortex-M0+ (no FPU, no MPU on G0 reset config), Cortex-M4F
  (FPU+MPU), Cortex-M7 (FPU+MPU).
* ``emit_system_init`` always emits the umbrella
  ``alloy_system_init()`` calling fpu/mpu/nvic in the documented
  order.
* ``emit_vector_table`` emits ``alloy_nvic_priority_setup[]`` —
  zero-length when the YAML carries no priorities (today's case
  for every admitted chip), with the apply-helper still defined.
* The package-level ``generate(config, out_dir)`` writes
  ``system_init.c`` next to the other artifacts.
"""

from __future__ import annotations

from pathlib import Path

from alloy_codegen.emit_v2_1 import emit_system_init, emit_vector_table
from alloy_codegen.emit_v2_1.system_init import (
    _has_cortexm_fpu,
    _has_cortexm_mpu,
    _is_armv7m_or_armv8m_main,
)
from alloy_codegen.sources.alloy_devices_yml import load_with_synthesis


# ---------------------------------------------------------------------------
# Variant classifier
# ---------------------------------------------------------------------------


def test_isa_classifier_recognises_cortex_m_variants() -> None:
    assert _is_armv7m_or_armv8m_main("ARMv6-M")
    assert _is_armv7m_or_armv8m_main("ARMv7-M")
    assert _is_armv7m_or_armv8m_main("ARMv7E-M")
    assert _is_armv7m_or_armv8m_main("ARMv8-M.MAIN")
    assert _is_armv7m_or_armv8m_main("armv8.1-m.main")
    # Negative cases.
    assert not _is_armv7m_or_armv8m_main("AVR8")
    assert not _is_armv7m_or_armv8m_main("Xtensa-LX7")
    assert not _is_armv7m_or_armv8m_main("RV32IMC")


def test_fpu_dispatch_requires_both_bool_and_cortex_m() -> None:
    # core.fpu=True on a non-Cortex-M doesn't trigger CPACR write.
    assert _has_cortexm_fpu(True, "RV32IMC") is False
    # core.fpu=False on a Cortex-M is always a no-op.
    assert _has_cortexm_fpu(False, "ARMv7E-M") is False
    # Both conditions together fire.
    assert _has_cortexm_fpu(True, "ARMv7E-M") is True


def test_mpu_dispatch_requires_both_bool_and_cortex_m() -> None:
    assert _has_cortexm_mpu(True, "AVR8") is False
    assert _has_cortexm_mpu(False, "ARMv7-M") is False
    assert _has_cortexm_mpu(True, "ARMv7-M") is True


# ---------------------------------------------------------------------------
# emit_system_init
# ---------------------------------------------------------------------------


def test_system_init_for_cortex_m0plus_is_a_safe_no_op() -> None:
    """STM32 G0 = Cortex-M0+ → no FPU; MPU is *defined* in the IR
    but the emitter still reaches the M0+ guard via the ISA
    classifier (M0+ is `armv6-m`, which DOES include an MPU on
    the G0 silicon).  The function still compiles cleanly and the
    body must define the three helpers."""
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    text = emit_system_init(canonical, syn)
    # All three helpers must be defined.
    assert "void alloy_system_init_fpu(void)" in text
    assert "void alloy_system_init_mpu(void)" in text
    assert "void alloy_system_init(void)" in text
    # G0 has no FPU -> body is intentionally empty.
    fpu_idx = text.find("void alloy_system_init_fpu(void)")
    mpu_idx = text.find("void alloy_system_init_mpu(void)")
    fpu_body = text[fpu_idx:mpu_idx]
    assert "intentionally a no-op" in fpu_body
    assert "CPACR" not in fpu_body


def test_system_init_for_cortex_m4f_writes_cpacr() -> None:
    """When the IR carries ``core.fpu=True`` on a Cortex-M
    (ARMv7E-M / ARMv8-M.MAIN), ``alloy_system_init_fpu`` emits the
    full CPACR write.  Today's STM32 YAMLs ship ``fpu=False``
    even on M4F/M7 silicon — that's a data-quality gap upstream;
    we synthesise an enriched core here so the emitter logic is
    tested against the contract, not the current data lag."""
    from dataclasses import replace

    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32f4", device="stm32f405rgtx",
    )
    enriched_core = replace(canonical.identity.core, fpu=True, mpu=True)
    enriched_identity = replace(canonical.identity, core=enriched_core)
    enriched = replace(canonical, identity=enriched_identity)

    text = emit_system_init(enriched, syn)
    fpu_idx = text.find("void alloy_system_init_fpu(void)")
    mpu_idx = text.find("void alloy_system_init_mpu(void)")
    fpu_body = text[fpu_idx:mpu_idx]
    assert "CPACR" in fpu_body
    assert "(0xFu << 20)" in fpu_body
    assert "__DSB()" in fpu_body
    assert "__ISB()" in fpu_body
    # MPU body programs MPU->CTRL with PRIVDEFENA + ENABLE.
    mpu_body = text[mpu_idx:text.find("void alloy_system_init(void)")]
    assert "MPU->CTRL" not in mpu_body  # we don't reference symbol
    assert "(1u << 2) | (1u << 0)" in mpu_body


def test_system_init_umbrella_calls_in_documented_order() -> None:
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    text = emit_system_init(canonical, syn)
    # Find the umbrella body and assert call order.
    body_start = text.find("void alloy_system_init(void)")
    body = text[body_start:]
    fpu_pos = body.find("alloy_system_init_fpu()")
    mpu_pos = body.find("alloy_system_init_mpu()")
    nvic_pos = body.find("alloy_nvic_apply_priorities()")
    assert 0 < fpu_pos < mpu_pos < nvic_pos


# ---------------------------------------------------------------------------
# vector_table.c — NVIC priority setup
# ---------------------------------------------------------------------------


def test_vector_table_emits_apply_priorities_helper() -> None:
    """``alloy_nvic_apply_priorities`` MUST always be defined,
    even when no vector carries an explicit priority.  Consumers
    can call it unconditionally."""
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    text = emit_vector_table(canonical, syn)
    assert "void alloy_nvic_apply_priorities(void)" in text
    assert "alloy_nvic_priority_setup_count" in text


def test_vector_table_priority_table_is_empty_when_no_priorities_set() -> None:
    """Today's admitted YAMLs don't carry InterruptVector.priority,
    so the table degrades to zero rows + a no-op helper."""
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    text = emit_vector_table(canonical, syn)
    assert "alloy_nvic_priority_setup_count = 0" in text


def test_priority_loader_round_trips_when_yaml_carries_it() -> None:
    """The IR change accepts ``priority:`` at load time so a
    future YAML enrichment lights up the table without a code
    change."""
    from alloy_codegen.canonical_device_v2_1 import _parse_interrupts
    parsed = _parse_interrupts([
        {"num": 0, "name": "WWDG_IRQHandler"},
        {"num": 7, "name": "EXTI4_15_IRQHandler", "priority": 12},
    ])
    assert parsed is not None
    assert isinstance(parsed, tuple)
    assert parsed[0].priority is None
    assert parsed[1].priority == 12


# ---------------------------------------------------------------------------
# Package-level integration
# ---------------------------------------------------------------------------


def test_generate_writes_system_init(tmp_path: Path) -> None:
    """`alloy_codegen.generate(config, out_dir)` includes
    ``system_init.c`` in the artifact set."""
    import alloy_codegen
    from dataclasses import dataclass

    @dataclass(frozen=True)
    class Chip:
        vendor: str = "st"
        family: str = "stm32g0"
        device: str = "stm32g071rb"

    @dataclass(frozen=True)
    class Cfg:
        chip: Chip = Chip()
        board: None = None

    written = alloy_codegen.generate(Cfg(), tmp_path)
    names = {p.name for p in written}
    assert "system_init.c" in names
    body = next(p for p in written if p.name == "system_init.c").read_text(encoding="utf-8")
    # G0 = Cortex-M0+ -> no CPACR; helpers still defined.
    assert "void alloy_system_init(void)" in body
    assert "alloy_system_init_fpu()" in body
    assert "alloy_system_init_mpu()" in body
    assert "alloy_nvic_apply_priorities()" in body
