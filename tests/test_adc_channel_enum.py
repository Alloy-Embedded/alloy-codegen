"""Tests for the typed `AdcChannelOf<P>` per-peripheral channel enum.

Covers the contract added by the ``add-adc-channel-typed-enum`` change.
Scope: every device whose ADC schema is currently published (ST stm32g0,
NXP iMXRT, Microchip AVR-DA) plus the empty-fallback posture for
``kPresent=false`` devices (Espressif esp32 / esp32c3, RaspberryPi
rp2040).

The ``execution_context`` fixture provides STM32G0 access; the espressif
and rp2040 contexts wrap the appropriate SVD overrides.
"""

from __future__ import annotations

import re

import pytest

from alloy_codegen.context import ExecutionContext
from alloy_codegen.runtime_driver_semantics import (
    _ADC_INTERNAL_KIND_ENUMERATOR_NAME,
    AdcInternalChannel,
    AdcSemanticRow,
    _adc_channel_manifest,
    _invalid_field_ref,
    _invalid_indexed_field_ref,
    _invalid_register_ref,
)
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit

# ---------- emit-based tests --------------------------------------------------

def _emit_adc_hpp(context: ExecutionContext, scope: PipelineScope, device: str) -> str:
    result = run_emit(scope, context)
    suffix = f"/{device}/driver_semantics/adc.hpp"
    artifact = next(a for a in result.payload.artifacts if a.path.endswith(suffix))
    return artifact.content


def _channel_block(content: str, peripheral: str) -> str:
    """Return the body of ``AdcChannelOf<PeripheralId::<P>>::type``."""
    pattern = (
        rf"struct AdcChannelOf<PeripheralId::{re.escape(peripheral)}> \{{\s*"
        rf"enum class type : std::uint8_t \{{(.*?)\}};"
    )
    match = re.search(pattern, content, re.DOTALL)
    assert match is not None, f"missing AdcChannelOf<PeripheralId::{peripheral}>"
    return match.group(1)


def _enumerators(block: str) -> dict[str, int]:
    """Parse ``Name = N u,`` lines into a {name: index} map."""
    out: dict[str, int] = {}
    for line in block.splitlines():
        m = re.match(r"\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(\d+)u,\s*$", line)
        if m:
            out[m.group(1)] = int(m.group(2))
    return out


# ---------- ST STM32G0 (ADC1: 19 channels + TempSensor + Vrefint + VBat) -----

def test_stm32g071rb_adc_channel_enum_carries_ordinals_and_named_aliases(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_adc_hpp(
        execution_context,
        PipelineScope(device="stm32g071rb"),
        "stm32g071rb",
    )
    block = _channel_block(content, "ADC1")
    members = _enumerators(block)

    # Ordinal members CH0..CH18 cover the published kChannelCount=19.
    for i in range(19):
        assert f"CH{i}" in members, f"missing ordinal CH{i}"
        assert members[f"CH{i}"] == i

    # Named internal aliases at the descriptor's published indices.
    assert members["TempSensor"] == 12
    assert members["Vrefint"] == 13
    assert members["VBat"] == 14


def test_stm32g071rb_emits_alias_template_after_specializations(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_adc_hpp(
        execution_context,
        PipelineScope(device="stm32g071rb"),
        "stm32g071rb",
    )
    # The convenience alias is what consumers spell in HAL code.
    assert "template<PeripheralId Id>" in content
    assert "using AdcChannel = typename AdcChannelOf<Id>::type;" in content


def test_stm32g071rb_has_empty_primary_template(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_adc_hpp(
        execution_context,
        PipelineScope(device="stm32g071rb"),
        "stm32g071rb",
    )
    # Empty-fallback primary template is always emitted so consumers
    # behind ``if constexpr (kPresent)`` gates compile cleanly on
    # backends without an ADC.
    assert re.search(
        r"template<PeripheralId Id>\s*\nstruct AdcChannelOf \{\s*"
        r"enum class type : std::uint8_t \{\};\s*\};",
        content,
    ) is not None, "empty-fallback AdcChannelOf primary template missing"


# ---------- Microchip AVR-DA (ADC0: 22 channels + TempSensor) -----------------

def test_avr128da32_adc_channel_enum_emits_temp_sensor_alias(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    content = _emit_adc_hpp(
        microchip_avr_da_execution_context,
        PipelineScope(vendor="microchip", family="avr-da", device="avr128da32"),
        "avr128da32",
    )
    block = _channel_block(content, "ADC0")
    members = _enumerators(block)

    # AVR-DA publishes a TempSensor internal channel.
    assert "TempSensor" in members
    # And ordinal members are present.
    assert "CH0" in members and members["CH0"] == 0


# ---------- NXP iMXRT (ADC1+ADC2 distinct types) ------------------------------

def test_mimxrt1062_adc_emits_distinct_channel_enums_per_peripheral(
    nxp_execution_context: ExecutionContext,
) -> None:
    content = _emit_adc_hpp(
        nxp_execution_context,
        PipelineScope(vendor="nxp", family="imxrt1060", device="mimxrt1062"),
        "mimxrt1062",
    )
    # Both peripherals get their own AdcChannelOf<...> specialization.
    assert "struct AdcChannelOf<PeripheralId::ADC1>" in content
    assert "struct AdcChannelOf<PeripheralId::ADC2>" in content


# ---------- Empty-fallback posture for kPresent=false devices ----------------

def test_esp32_emits_primary_template_and_sens_specialization(
    espressif_execution_context: ExecutionContext,
) -> None:
    content = _emit_adc_hpp(
        espressif_execution_context,
        PipelineScope(vendor="espressif", family="esp32", device="esp32"),
        "esp32",
    )
    # The empty primary template MUST always be emitted so consumers
    # behind ``if constexpr (kPresent)`` gates compile cleanly when
    # they target a peripheral that has no specialization.
    assert re.search(
        r"template<PeripheralId Id>\s*\nstruct AdcChannelOf \{\s*"
        r"enum class type : std::uint8_t \{\};\s*\};",
        content,
    ) is not None
    # ESP32's ADC peripheral is exposed as `SENS` — confirm the
    # specialization with ordinal members lands when the schema is
    # published (the descriptor publishes kPresent=true today).
    assert "struct AdcChannelOf<PeripheralId::SENS>" in content
    assert "using AdcChannel = typename AdcChannelOf<Id>::type;" in content


def test_rp2040_emits_primary_template_and_adc_specialization(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit_adc_hpp(
        rp2040_execution_context,
        PipelineScope(vendor="raspberrypi", family="rp2040", device="rp2040"),
        "rp2040",
    )
    # Empty primary template still required.
    assert re.search(
        r"template<PeripheralId Id>\s*\nstruct AdcChannelOf \{\s*"
        r"enum class type : std::uint8_t \{\};\s*\};",
        content,
    ) is not None
    # RP2040 publishes its ADC peripheral as `PeripheralId::ADC`.
    assert "struct AdcChannelOf<PeripheralId::ADC>" in content
    assert "using AdcChannel = typename AdcChannelOf<Id>::type;" in content


# ---------- Closed name-table contract --------------------------------------

def test_internal_kind_enumerator_name_table_is_closed_set() -> None:
    """The closed kind set MUST match the set declared in
    `InternalAdcChannelKind` (the C++ enum emitted in `common.hpp`).

    A new kind landing in the IR without a corresponding enumerator
    name in this table would silently lose its named alias — the CI
    gate enforced here catches that drift.
    """
    declared_kinds = {
        "temperature_sensor",
        "vrefint",
        "vbat",
        "opamp_output",
        "dac_output",
    }
    assert set(_ADC_INTERNAL_KIND_ENUMERATOR_NAME.keys()) == declared_kinds, (
        "InternalAdcChannelKind set drifted from the emitter name table; "
        "update _ADC_INTERNAL_KIND_ENUMERATOR_NAME and the doc in "
        "openspec/changes/add-adc-channel-typed-enum/design.md"
    )


# ---------- Manifest helper unit tests --------------------------------------

def _row(channel_count: int, internal: tuple[AdcInternalChannel, ...] = ()) -> AdcSemanticRow:
    """Construct a minimal AdcSemanticRow for manifest unit testing."""
    return AdcSemanticRow(
        peripheral_name="ADC1",
        schema_id="schema_test",
        channel_count=channel_count,
        result_bits=12,
        has_dma=False,
        has_hardware_trigger=False,
        has_channel_bitmask_select=False,
        control_reg=_invalid_register_ref(),
        status_reg=_invalid_register_ref(),
        config_reg=_invalid_register_ref(),
        sample_time_reg=_invalid_register_ref(),
        sequence_reg=_invalid_register_ref(),
        data_reg=_invalid_register_ref(),
        enable_field=_invalid_field_ref(),
        disable_field=_invalid_field_ref(),
        ready_field=_invalid_field_ref(),
        start_field=_invalid_field_ref(),
        stop_field=_invalid_field_ref(),
        continuous_field=_invalid_field_ref(),
        resolution_field=_invalid_field_ref(),
        align_field=_invalid_field_ref(),
        dma_enable_field=_invalid_field_ref(),
        dma_mode_field=_invalid_field_ref(),
        external_trigger_enable_field=_invalid_field_ref(),
        external_trigger_select_field=_invalid_field_ref(),
        end_of_conversion_field=_invalid_field_ref(),
        end_of_sequence_field=_invalid_field_ref(),
        overrun_field=_invalid_field_ref(),
        data_field=_invalid_field_ref(),
        channel_select_field=_invalid_field_ref(),
        channel_bit_pattern=_invalid_indexed_field_ref(),
        channel_enable_pattern=_invalid_indexed_field_ref(),
        channel_disable_pattern=_invalid_indexed_field_ref(),
        channel_status_pattern=_invalid_indexed_field_ref(),
        internal_channels=internal,
    )


def test_manifest_lists_ordinal_then_named_aliases() -> None:
    row = _row(
        channel_count=4,
        internal=(
            AdcInternalChannel(kind="vrefint", channel_index=2),
            AdcInternalChannel(kind="temperature_sensor", channel_index=3),
        ),
    )
    manifest = _adc_channel_manifest(row)
    names = [name for (name, _) in manifest]
    assert names == ["CH0", "CH1", "CH2", "CH3", "Vrefint", "TempSensor"]
    indices = {name: idx for (name, idx) in manifest}
    assert indices["Vrefint"] == 2
    assert indices["TempSensor"] == 3


def test_manifest_skips_unknown_kind() -> None:
    row = _row(
        channel_count=2,
        internal=(
            AdcInternalChannel(kind="some_future_kind", channel_index=1),
        ),
    )
    manifest = _adc_channel_manifest(row)
    names = [name for (name, _) in manifest]
    # No alias for the unknown kind; only ordinal members survive.
    assert names == ["CH0", "CH1"]


def test_manifest_fails_on_duplicate_alias() -> None:
    row = _row(
        channel_count=4,
        internal=(
            AdcInternalChannel(kind="vrefint", channel_index=2),
            # Same alias name pointing at a different index → emit-time bug.
            AdcInternalChannel(kind="vrefint", channel_index=3),
        ),
    )
    with pytest.raises(ValueError, match="duplicate enumerator name 'Vrefint'"):
        _adc_channel_manifest(row)


def test_manifest_idempotent_for_same_internal_index() -> None:
    """Two entries with the same kind AND the same index are coalesced."""
    row = _row(
        channel_count=2,
        internal=(
            AdcInternalChannel(kind="vrefint", channel_index=1),
            AdcInternalChannel(kind="vrefint", channel_index=1),
        ),
    )
    manifest = _adc_channel_manifest(row)
    names = [name for (name, _) in manifest]
    assert names == ["CH0", "CH1", "Vrefint"]
