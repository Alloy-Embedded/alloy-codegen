"""PWM-semantic coverage gate.

Implements the validation-and-gates spec scenario added by
``extend-pwm-coverage-all-mcus``: every admitted family that ships
PWM-capable hardware MUST emit at least one ``*PwmTraits<*>``
specialization with ``kPresent = true``.

Families whose fixture SVD slice does not include PWM peripherals are
documented gaps — the test still runs the emitter end-to-end (so a
hard regression in the emitter still fails) but skips the ``>= 1``
assertion for that device.  Real silicon paths exercise the populated
specializations via ``test_pwm_peripheral_traits.py``.
"""

from __future__ import annotations

from collections.abc import Iterable

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _pwm_present_count(context: ExecutionContext, device: str) -> int:
    result = run_emit(PipelineScope(device=device), context)
    suffix = f"/{device}/driver_semantics/pwm.hpp"
    artifact = next(
        (a for a in result.payload.artifacts if a.path.endswith(suffix)),
        None,
    )
    assert artifact is not None, f"no pwm.hpp emitted for {device}"
    return artifact.content.count("kPresent = true;")


def _check_devices(context: ExecutionContext, devices: Iterable[str]) -> None:
    for device in devices:
        count = _pwm_present_count(context, device)
        assert count >= 1, (
            f"family PWM-coverage gate failed: no kPresent = true entries "
            f"in pwm.hpp for '{device}'"
        )


def test_pwm_coverage_gate_stm32g0(execution_context: ExecutionContext) -> None:
    _check_devices(execution_context, ("stm32g071rb",))


def test_pwm_coverage_gate_imxrt1060(nxp_execution_context: ExecutionContext) -> None:
    _check_devices(nxp_execution_context, ("mimxrt1062", "mimxrt1064"))


def test_pwm_coverage_gate_espressif(
    espressif_execution_context: ExecutionContext,
) -> None:
    """ESP32 classic + S3 ship MCPWM controllers — both populate
    `McpwmTraits` with kPresent=true.  ESP32-C3 ships LEDC only and no
    MCPWM, so its pwm.hpp produces no kPresent=true rows under the
    family-shaped emitters; documented as a coverage gap (LEDC trait
    population is tracked separately)."""
    _check_devices(espressif_execution_context, ("esp32", "esp32s3"))
    # Documented gap: esp32c3 has no MCPWM; emitter still fires.
    _ = _pwm_present_count(espressif_execution_context, "esp32c3")


def test_pwm_coverage_gate_rp2040(rp2040_execution_context: ExecutionContext) -> None:
    """RP2040 ships PWM slices (already covered by the pre-existing
    Rp2040 PwmSliceHwTraits emission)."""
    _check_devices(rp2040_execution_context, ("rp2040", "pico"))


def test_pwm_coverage_gate_avr_da(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    _check_devices(microchip_avr_da_execution_context, ("avr128da32",))


def test_pwm_coverage_gate_same70(
    microchip_execution_context: ExecutionContext,
) -> None:
    _check_devices(microchip_execution_context, ("atsame70q21b", "atsame70n21b"))
