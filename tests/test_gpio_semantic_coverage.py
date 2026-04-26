"""GPIO-semantic coverage gate.

Implements the validation-and-gates spec scenario added by
``fill-gpio-semantic-gaps``: every admitted family MUST emit at least one
``GpioSemanticTraits<PinId::...>`` specialization with ``kPresent = true``.

The gate is exercised against the per-family fixture-source contexts so
the test is hermetic (no network access required for AVR-DA / SAME70
DFP downloads).
"""

from __future__ import annotations

from collections.abc import Iterable

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _gpio_present_count(context: ExecutionContext, device: str) -> int:
    result = run_emit(PipelineScope(device=device), context)
    suffix = f"/{device}/driver_semantics/gpio.hpp"
    artifact = next(
        (a for a in result.payload.artifacts if a.path.endswith(suffix)),
        None,
    )
    assert artifact is not None, f"no gpio.hpp emitted for {device}"
    # The primary template carries `kPresent = false`; specializations flip it
    # to `kPresent = true;`.  Counting that exact substring under the
    # specialization-only forms gives the populated-pin count.
    return artifact.content.count("kPresent = true;")


def _check_devices(context: ExecutionContext, devices: Iterable[str]) -> None:
    for device in devices:
        count = _gpio_present_count(context, device)
        assert count >= 1, (
            f"family coverage gate failed: no GpioSemanticTraits<PinId::*> "
            f"specializations with kPresent = true emitted for '{device}'"
        )


def test_gpio_coverage_gate_stm32g0(execution_context: ExecutionContext) -> None:
    _check_devices(execution_context, ("stm32g071rb",))


def test_gpio_coverage_gate_stm32f4(execution_context: ExecutionContext) -> None:
    _check_devices(execution_context, ("stm32f401re", "stm32f405rg"))


def test_gpio_coverage_gate_same70(microchip_execution_context: ExecutionContext) -> None:
    _check_devices(microchip_execution_context, ("atsame70n21b", "atsame70q21b"))


def test_gpio_coverage_gate_avr_da(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    _check_devices(microchip_avr_da_execution_context, ("avr128da32",))


def test_gpio_coverage_gate_imxrt1060(nxp_execution_context: ExecutionContext) -> None:
    _check_devices(nxp_execution_context, ("mimxrt1062", "mimxrt1064"))


def test_gpio_coverage_gate_espressif(
    espressif_execution_context: ExecutionContext,
) -> None:
    _check_devices(espressif_execution_context, ("esp32", "esp32c3", "esp32s3"))


def test_gpio_coverage_gate_rp2040(
    rp2040_execution_context: ExecutionContext,
) -> None:
    """Mandatory after `complete-rp2040-semantics` Phase A populates
    `device.gpio_pins` for RP2040 from the FUNCSEL table."""
    _check_devices(rp2040_execution_context, ("rp2040", "pico"))
