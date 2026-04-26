"""Tests for the structured PioSemanticTraits / StateMachineSemanticTraits emission.

Covers the contract added by the ``define-pio-semantic-struct`` change:
- Primary ``PioSemanticTraits<PioId>`` template carries zero-valued defaults so
  families without PIO hardware remain zero-cost.
- RP2040 emits one specialization per PIO block (Pio0, Pio1) with topology
  fields populated from ``patches/raspberrypi/rp2040/pio.json``.
- ``StateMachineSemanticTraits<PioId, Sm>`` specializations encode per-SM
  DREQ values as ``dreq_{tx,rx}_base + sm_index``.
"""

from __future__ import annotations

import re
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_pio_hpp(context: ExecutionContext, device: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    artifact = next(
        a for a in result.payload.artifacts if a.path.endswith(f"/{device}/driver_semantics/pio.hpp")
    )
    return artifact.content


def test_non_pio_family_emits_only_primary_template_with_zero_defaults(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_pio_hpp(execution_context, "stm32g071rb")

    assert "enum class PioId : std::uint8_t {\n  None = 0,\n};" in content
    assert "template<PioId Id>\nstruct PioSemanticTraits {" in content
    assert "static constexpr bool kPresent = false;" in content
    assert "static constexpr std::uint8_t kStateMachineCount = 0;" in content
    assert "static constexpr std::uint32_t kBaseAddress = 0;" in content
    # No specializations emitted for families without PIO hardware.
    assert "struct PioSemanticTraits<PioId::" not in content
    assert "struct StateMachineSemanticTraits<PioId::" not in content
    assert "std::array<PioId, 0> kPioSemanticPeripherals = {};" in content


def _extract_struct_block(content: str, header: str) -> str:
    """Return the body of a ``struct <header>`` declaration up to the closing brace."""
    match = re.search(rf"struct {re.escape(header)} \{{(.*?)\n}};", content, re.DOTALL)
    assert match is not None, f"missing struct: {header}"
    return match.group(1)


def test_rp2040_emits_populated_pio_specializations(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit_pio_hpp(rp2040_execution_context, "rp2040")

    assert "Pio0 = 0," in content
    assert "Pio1 = 1," in content

    pio0 = _extract_struct_block(content, "PioSemanticTraits<PioId::Pio0>")
    assert "static constexpr bool kPresent = true;" in pio0
    assert "static constexpr std::uint8_t kStateMachineCount = 4;" in pio0
    assert "static constexpr std::uint8_t kInstructionMemoryDepth = 32;" in pio0
    assert "static constexpr std::uint8_t kTxFifoDepth = 4;" in pio0
    assert "static constexpr std::uint8_t kRxFifoDepth = 4;" in pio0
    assert "static constexpr std::uint8_t kGpioBase = 0;" in pio0
    assert "static constexpr std::uint8_t kGpioCount = 30;" in pio0
    assert "static constexpr std::uint32_t kBaseAddress = 0x50200000u;" in pio0
    assert "static constexpr std::uint8_t kDreqTx = 0;" in pio0
    assert "static constexpr std::uint8_t kDreqRx = 4;" in pio0

    pio1 = _extract_struct_block(content, "PioSemanticTraits<PioId::Pio1>")
    assert "static constexpr std::uint32_t kBaseAddress = 0x50300000u;" in pio1
    assert "static constexpr std::uint8_t kDreqTx = 8;" in pio1
    assert "static constexpr std::uint8_t kDreqRx = 12;" in pio1


def test_rp2040_emits_per_state_machine_dreq_specializations(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit_pio_hpp(rp2040_execution_context, "rp2040")

    # 4 specializations per block × 2 blocks = 8 state-machine specializations.
    sm_matches = re.findall(r"struct StateMachineSemanticTraits<PioId::Pio[01], \d+>", content)
    assert len(sm_matches) == 8

    # Spot-check per-SM DREQ derivation: dreq_{tx,rx} = base + sm_index.
    pio0_sm3 = _extract_struct_block(content, "StateMachineSemanticTraits<PioId::Pio0, 3>")
    assert "kDreqTx = 3;" in pio0_sm3
    assert "kDreqRx = 7;" in pio0_sm3

    pio1_sm2 = _extract_struct_block(content, "StateMachineSemanticTraits<PioId::Pio1, 2>")
    assert "kDreqTx = 10;" in pio1_sm2
    assert "kDreqRx = 14;" in pio1_sm2


def test_rp2040_pio_hpp_matches_golden(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit_pio_hpp(rp2040_execution_context, "rp2040")
    golden = (
        Path(__file__).parent
        / "fixtures"
        / "emitted"
        / "rp2040"
        / "generated"
        / "runtime"
        / "devices"
        / "rp2040"
        / "driver_semantics"
        / "pio.hpp"
    ).read_text(encoding="utf-8")
    assert content == golden
