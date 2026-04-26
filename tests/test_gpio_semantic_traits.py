"""Tests for the populated GpioSemanticTraits AF fields.

Covers the contract added by the ``fill-gpio-semantic-gaps`` change. The
test scope is currently STM32G0 (Phase A); each subsequent phase will add
its family's coverage here.

The ``execution_context`` fixture provides a *minimal* stm32-open-pin-data
slice (only a subset of pins; see ``tests/fixtures/stm32-open-pin-data``),
so these assertions intentionally target pins that are present in that
slice (PA0, PB6) rather than the canonical Nucleo LED pin PA5 (which is
covered end-to-end via the regenerated golden ``gpio.hpp``).
"""

from __future__ import annotations

import re

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_gpio_hpp(context: ExecutionContext, device: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    artifact = next(
        a for a in result.payload.artifacts if a.path.endswith(f"/{device}/driver_semantics/gpio.hpp")
    )
    return artifact.content


def _struct_block(content: str, header: str) -> str:
    match = re.search(rf"struct {re.escape(header)} \{{(.*?)\n}};", content, re.DOTALL)
    assert match is not None, f"missing struct: {header}"
    return match.group(1)


def test_primary_template_carries_zero_defaulted_af_fields(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_gpio_hpp(execution_context, "stm32g071rb")

    primary = _struct_block(content, "GpioSemanticTraits")
    assert "static constexpr std::uint32_t kPortOffset = 0u;" in primary
    assert "static constexpr std::uint32_t kPinIndex = 0u;" in primary
    assert "static constexpr std::uint8_t kMaxAltFunction = 0u;" in primary
    assert "static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};" in primary


def test_stm32g071rb_pa0_specialization_records_port_topology(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_gpio_hpp(execution_context, "stm32g071rb")

    pa0 = _struct_block(content, "GpioSemanticTraits<PinId::PA0>")
    assert "static constexpr bool kPresent = true;" in pa0
    assert "static constexpr std::uint32_t kPortOffset = 0x00000000u;" in pa0  # GPIOA base
    assert "static constexpr std::uint32_t kPinIndex = 0u;" in pa0


def test_stm32g071rb_pb6_specialization_records_distinct_port_offset(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_gpio_hpp(execution_context, "stm32g071rb")

    pb6 = _struct_block(content, "GpioSemanticTraits<PinId::PB6>")
    # GPIOB is +0x400 from GPIOA on STM32 (4 KiB stride).
    assert "static constexpr std::uint32_t kPortOffset = 0x00000400u;" in pb6
    assert "static constexpr std::uint32_t kPinIndex = 6u;" in pb6
    # PB6 has at least one alternate function in the test OPD slice.
    assert "kValidAltFunctions = {{0u}};" in pb6


def test_stm32g071rb_emits_at_least_one_present_specialization(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_gpio_hpp(execution_context, "stm32g071rb")
    assert content.count("kPresent = true;") >= 1


# --- Phase B: STM32F4 ----------------------------------------------------


def test_stm32f401re_emits_populated_gpio_specializations(
    execution_context: ExecutionContext,
) -> None:
    """STM32F4 reuses the Phase A normalizer; verify it produces ``kPresent =
    true`` specializations populated with real port-offset / pin-index data
    for the same fixture-source slice that covers F401RE."""
    content = _emit_gpio_hpp(execution_context, "stm32f401re")

    primary = _struct_block(content, "GpioSemanticTraits")
    assert "static constexpr std::uint32_t kPortOffset = 0u;" in primary
    assert "static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};" in primary

    # The test OPD slice exposes a small set of pins for STM32F4 (PA2/3/9/10).
    # PA9 is the USART1_TX pin on Nucleo-F401RE; we use it as the smoke
    # check since it is guaranteed to carry alt-function entries.
    pa9 = _struct_block(content, "GpioSemanticTraits<PinId::PA9>")
    assert "static constexpr bool kPresent = true;" in pa9
    assert "static constexpr std::uint32_t kPortOffset = 0x00000000u;" in pa9  # GPIOA base
    assert "static constexpr std::uint32_t kPinIndex = 9u;" in pa9
    assert "kValidAltFunctions = {{" in pa9  # non-empty array literal


def test_stm32f405rg_pa3_records_port_topology(
    execution_context: ExecutionContext,
) -> None:
    """STM32F405 reuses the same emitter path; verify a port-A pin renders
    with the expected zero offset and bit index."""
    content = _emit_gpio_hpp(execution_context, "stm32f405rg")

    pa3 = _struct_block(content, "GpioSemanticTraits<PinId::PA3>")
    assert "static constexpr std::uint32_t kPortOffset = 0x00000000u;" in pa3
    assert "static constexpr std::uint32_t kPinIndex = 3u;" in pa3


# --- Phase C: Espressif (ESP32 classic / C3 / S3) ------------------------


def test_esp32c3_gpio_pins_emit_kpresent_with_io_matrix_signal_index(
    espressif_execution_context: ExecutionContext,
) -> None:
    """ESP32 has a single GPIO peripheral; alt-function numbers carry the
    IO-matrix signal index (e.g. SPI2_MISO = signal 63 on C3).  Verify the
    primary template carries the new ``kIsInputOnly`` field and that GPIO2
    on C3 reports a populated AF list with ``kIsInputOnly = false``."""
    content = _emit_gpio_hpp(espressif_execution_context, "esp32c3")

    primary = _struct_block(content, "GpioSemanticTraits")
    assert "static constexpr bool kIsInputOnly = false;" in primary

    gpio2 = _struct_block(content, "GpioSemanticTraits<PinId::GPIO2>")
    assert "static constexpr bool kPresent = true;" in gpio2
    assert "static constexpr std::uint32_t kPinIndex = 2u;" in gpio2
    assert "static constexpr bool kIsInputOnly = false;" in gpio2
    # SPI2_MISO routes through IO matrix signal 63 on ESP32-C3 — present
    # in the test gpio_sig_map.h slice.
    assert "kValidAltFunctions = {{63u}};" in gpio2


def test_esp32_classic_input_only_pads_marked(
    espressif_execution_context: ExecutionContext,
) -> None:
    """GPIO34..39 on the classic ESP32 are physically input-only.  When such
    a pad appears in the test slice, its specialization MUST carry
    ``kIsInputOnly = true``; otherwise (slice doesn't include those pads)
    this assertion is vacuously satisfied."""
    content = _emit_gpio_hpp(espressif_execution_context, "esp32")

    for pad in (34, 35, 36, 37, 38, 39):
        header = f"GpioSemanticTraits<PinId::GPIO{pad}>"
        if header not in content:
            continue
        block = _struct_block(content, header)
        assert "static constexpr bool kIsInputOnly = true;" in block, (
            f"GPIO{pad} on classic ESP32 must be input-only"
        )
