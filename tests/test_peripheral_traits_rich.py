"""Unit tests for the foundational pass on
``extend-peripheral-traits-with-rich-metadata``.

Covers:

* ``trait_classifier.classify_instance`` and ``classify_template``
  pick the right kinds for ADC / I²C / timer instances and
  templates.
* ``emit_peripheral_traits`` emits the new sub-namespaces inside
  the existing per-instance / per-template namespaces:
    - ``calibration::{vrefint, ts_cal_low, ts_cal_high}`` for
      STM32 ADCs that carry factory calibration metadata.
    - ``external_triggers::{regular, injected}`` rows for STM32
      ADCs that carry external-trigger maps.
    - ``timing_presets::kRows`` for I²C instances with
      pre-computed presets (synthetic — current YAML ships none).
    - ``trigger_sources``, ``master_outputs``, ``deadtime_options``,
      ``break_inputs`` for timer-class templates that carry the
      matrix.
* Templates and instances without rich metadata receive no
  sub-namespace (so the file stays small for chips that don't
  populate it yet).
"""

from __future__ import annotations

from dataclasses import replace

from alloy_codegen.emit_v2_1 import emit_peripheral_traits
from alloy_codegen.emit_v2_1.trait_classifier import (
    InstanceTraitKind,
    TemplateTraitKind,
    classify_instance,
    classify_template,
)
from alloy_codegen.ir.v2_1 import (
    I2cTimingPreset,
    PeripheralInstance,
    Template,
)
from alloy_codegen.sources.alloy_devices_yml import load_with_synthesis


# ---------------------------------------------------------------------------
# Trait classifier
# ---------------------------------------------------------------------------


def test_classify_instance_recognises_adc_only_when_payload_populated() -> None:
    canonical, _ = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    adc = next(p for p in canonical.peripherals if p.template == "adc")
    assert classify_instance(adc) == InstanceTraitKind.ADC
    # Strip the calibration + triggers payloads — classifier degrades
    # to NONE so we don't emit empty trait blocks.
    bare_adc = replace(adc, calibration=None, external_triggers={})
    assert classify_instance(bare_adc) == InstanceTraitKind.NONE


def test_classify_instance_recognises_i2c_only_when_presets_populated() -> None:
    canonical, _ = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    i2c = next(p for p in canonical.peripherals if p.template == "i2c")
    # Today's G0 YAML carries no timing_presets — classifier returns NONE.
    assert classify_instance(i2c) == InstanceTraitKind.NONE
    # Synthesise a single preset row to flip the classifier.
    enriched = replace(i2c, timing_presets=(
        I2cTimingPreset(speed="100kHz", source_clock="pclk1", timingr=0x10707DBC),
    ))
    assert classify_instance(enriched) == InstanceTraitKind.I2C


def test_classify_template_recognises_timer_when_matrix_populated() -> None:
    canonical, _ = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    advanced = canonical.templates.get("timer_advanced")
    assert advanced is not None
    assert classify_template(advanced) == TemplateTraitKind.TIMER

    # An empty template (no timer-matrix fields) → NONE.
    bare = Template()
    assert classify_template(bare) == TemplateTraitKind.NONE


def test_classify_instance_falls_through_to_none_for_unknown_template() -> None:
    bare = PeripheralInstance(id="unknown", template="some_random_ip")
    assert classify_instance(bare) == InstanceTraitKind.NONE


# ---------------------------------------------------------------------------
# emit_peripheral_traits — ADC factory calibration
# ---------------------------------------------------------------------------


def test_emit_peripheral_traits_includes_adc_calibration_block() -> None:
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    text = emit_peripheral_traits(canonical, syn)

    # The ADC namespace contains a calibration sub-namespace with
    # the expected ROM-address constants from the YAML.
    adc_start = text.find("namespace adc {")
    adc_end = text.find("}  // namespace adc", adc_start)
    adc_block = text[adc_start:adc_end]
    assert "namespace calibration" in adc_block
    assert "namespace vrefint" in adc_block
    assert "kRomAddr   = 0x1FFF75AAu" in adc_block
    assert "namespace ts_cal_low" in adc_block
    assert "namespace ts_cal_high" in adc_block


def test_emit_peripheral_traits_includes_adc_external_triggers() -> None:
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    text = emit_peripheral_traits(canonical, syn)
    adc_start = text.find("namespace adc {")
    adc_end = text.find("}  // namespace adc", adc_start)
    adc_block = text[adc_start:adc_end]

    assert "namespace external_triggers" in adc_block
    assert "namespace regular" in adc_block
    # Spot-check a known row: tim1_trgo2 with extsel=0.
    assert '{ "tim1_trgo2", 0, -1, "rising" },' in adc_block


# ---------------------------------------------------------------------------
# emit_peripheral_traits — I²C timing presets
# ---------------------------------------------------------------------------


def test_emit_peripheral_traits_skips_i2c_when_no_presets() -> None:
    """Today's G0 YAML carries no timing presets — we must NOT
    emit an empty timing_presets sub-namespace (saves ~6 lines
    of no-value-add output per I²C instance)."""
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    text = emit_peripheral_traits(canonical, syn)
    i2c_start = text.find("namespace i2c1 {")
    i2c_end = text.find("}  // namespace i2c1", i2c_start)
    assert "namespace timing_presets" not in text[i2c_start:i2c_end]


def test_emit_peripheral_traits_emits_i2c_presets_when_synthetic() -> None:
    """Inject a timing_presets row into the IR via dataclass.replace
    and confirm the emitter lands the kRows table.  (Once
    alloy-devices-yml carries presets, this is the same shape the
    live emitter produces.)"""
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    enriched_pers = tuple(
        replace(p, timing_presets=(
            I2cTimingPreset(speed="400kHz", source_clock="pclk1", timingr=0x00602173),
            I2cTimingPreset(speed="1MHz", source_clock="pclk1", timingr=0x00200818),
        )) if p.id == "i2c1" else p
        for p in canonical.peripherals
    )
    enriched = replace(canonical, peripherals=enriched_pers)
    text = emit_peripheral_traits(enriched, syn)
    i2c_start = text.find("namespace i2c1 {")
    i2c_end = text.find("}  // namespace i2c1", i2c_start)
    i2c_block = text[i2c_start:i2c_end]

    assert "namespace timing_presets" in i2c_block
    assert "kCount = 2" in i2c_block
    assert "0x00602173u" in i2c_block
    assert "0x00200818u" in i2c_block


# ---------------------------------------------------------------------------
# emit_peripheral_traits — Timer matrix
# ---------------------------------------------------------------------------


def test_emit_peripheral_traits_includes_timer_matrix() -> None:
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    text = emit_peripheral_traits(canonical, syn)
    advanced_start = text.find("namespace template_timer_advanced {")
    advanced_end = text.find("}  // namespace template_timer_advanced", advanced_start)
    block = text[advanced_start:advanced_end]
    assert "namespace trigger_sources" in block
    assert "itr0 = 0" in block
    assert "namespace master_outputs" in block
    assert "reset = 0" in block
    assert "namespace deadtime_options" in block
    assert "{ 0, 7, 1270 }," in block
    assert "namespace break_inputs" in block
    assert "bkin = 0" in block
    assert "bkin2 = 1" in block


def test_basic_timer_template_has_no_timer_matrix() -> None:
    """A template without trigger_sources / master_outputs / etc.
    receives no timer-matrix block (no value, just clutter)."""
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    # ``timer_basic`` (TIM6/TIM7) has no matrix on G0.
    basic = canonical.templates.get("timer_basic")
    if basic is None:
        return  # family doesn't ship a basic timer template; skip
    assert classify_template(basic) == TemplateTraitKind.NONE
    text = emit_peripheral_traits(canonical, syn)
    basic_start = text.find("namespace template_timer_basic {")
    if basic_start == -1:
        return  # template exists in IR but emitter sorted-skipped; ok
    basic_end = text.find("}  // namespace template_timer_basic", basic_start)
    block = text[basic_start:basic_end]
    assert "namespace trigger_sources" not in block
    assert "namespace master_outputs" not in block
