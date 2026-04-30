"""PWM driver-semantic emitter (STM32 / Microchip / NXP / RP2040 / AVR-DA / SAME70).

Imports the shared ``_stm_timer_pwm_traits_block`` from
``runtime_driver/timer.py``.

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass
from typing import Any

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from ..emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _std_array_lines,
)
from ..runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
)
from .common import (
    RuntimeFieldRef,
    RuntimeRegisterRef,
    _context,
    _field_ref_expr,
    _invalid_field_ref,
    _invalid_register_ref,
    _manual_field_ref,
    _register_ref_expr,
    _render_typed_option_enum_block,
    _resolve_field_ref,
    _resolve_register_ref,
    _schema_ref_expr,
    _SemanticContext,
)
from .timer import _st_timer_counter_bits, _stm_timer_pwm_traits_block

PWM_DRIVER_HEADER = "driver_semantics/pwm.hpp"


@dataclass(frozen=True, slots=True)
class PwmSemanticRow:
    """PWM semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    counter_bits: int
    channel_count: int
    has_complementary_outputs: bool
    has_deadtime: bool
    has_fault_input: bool
    has_center_aligned: bool
    has_synchronized_update: bool
    control_reg: RuntimeRegisterRef
    output_enable_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    clock_reg: RuntimeRegisterRef
    sync_reg: RuntimeRegisterRef
    master_output_enable_field: RuntimeFieldRef
    load_field: RuntimeFieldRef
    clear_load_field: RuntimeFieldRef
    clock_prescaler_field: RuntimeFieldRef
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented
    # Tier 2/3/4 facts (add-pwm-tier-2-3-4-data).
    max_prescaler: int = 0
    max_period: int = 0
    deadtime_options: tuple[
        tuple[int, int, int], ...
    ] = ()  # (prescaler_field_value, count_bits, max_ns)
    supported_alignments: tuple[tuple[str, int], ...] = ()  # (alignment, field_value)
    break_inputs: tuple[
        tuple[str, int, int], ...
    ] = ()  # (input_id, polarity_field_value, enable_field_value)
    supports_deadtime: bool = False
    supports_break_input: bool = False
    supports_complementary_outputs: bool = False
    supports_asymmetric_pwm: bool = False
    supports_combined_pwm: bool = False


@dataclass(frozen=True, slots=True)
class PwmChannelSemanticRow:
    """PWM channel semantic trait payload keyed by peripheral/channel index."""

    peripheral_name: str
    channel_index: int
    supports_complementary_output: bool
    supports_deadtime: bool
    control_reg: RuntimeRegisterRef
    compare_reg: RuntimeRegisterRef
    secondary_compare_reg: RuntimeRegisterRef
    period_reg: RuntimeRegisterRef
    deadtime_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    interrupt_enable_field: RuntimeFieldRef
    interrupt_flag_field: RuntimeFieldRef
    mode_field: RuntimeFieldRef
    polarity_field: RuntimeFieldRef
    complementary_output_enable_field: RuntimeFieldRef
    center_aligned_field: RuntimeFieldRef
    period_field: RuntimeFieldRef
    duty_field: RuntimeFieldRef
    deadtime_rise_field: RuntimeFieldRef
    deadtime_fall_field: RuntimeFieldRef


def _build_pwm_typed_enum_blocks(rows: tuple[PwmSemanticRow, ...]) -> list[str]:
    """Render PWM typed-option enum blocks (alignment / break input)."""
    align_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    break_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    for row in rows:
        if row.is_stub:
            continue
        peripheral_id = _enum_identifier(row.peripheral_name)
        alignments = tuple(
            (str(name), idx) for idx, (name, _fv) in enumerate(row.supported_alignments)
        )
        if alignments:
            align_entries.append((peripheral_id, alignments))
        breaks = tuple(
            (str(input_id), idx) for idx, (input_id, _pol, _en) in enumerate(row.break_inputs)
        )
        if breaks:
            break_entries.append((peripheral_id, breaks))

    lines: list[str] = []
    for spec in (
        ("PwmAlignmentOf", "PwmAlignment", align_entries),
        ("PwmBreakInputOf", "PwmBreakInput", break_entries),
    ):
        template_name, alias_name, entries = spec
        if not any(e for _, e in entries):
            continue
        lines.append(
            f"// add-typed-peripheral-enums-everywhere: typed {template_name} per peripheral."
        )
        lines.extend(
            _render_typed_option_enum_block(
                template_name=template_name,
                alias_name=alias_name,
                peripheral_entries=tuple(entries),
            )
        )
    return lines


# _render_adc_channel_enum_block → runtime_driver/adc.py


# _adc_calibration_data_point_expr → runtime_driver/adc.py


# _adc_calibration_context_expr → runtime_driver/adc.py


# _adc_resolution_option_expr → runtime_driver/adc.py


# _adc_sample_time_option_expr → runtime_driver/adc.py


# _adc_oversampling_option_expr → runtime_driver/adc.py


# _adc_external_trigger_expr → runtime_driver/adc.py


# _adc_dma_binding_expr → runtime_driver/adc.py


# _adc_dma_mode_option_expr → runtime_driver/adc.py


def _st_pwm_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> PwmSemanticRow:
    advanced_timer = peripheral_name in {"TIM1", "TIM8"}
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return PwmSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=_st_timer_counter_bits(peripheral_name),
        channel_count=4,
        has_complementary_outputs=advanced_timer,
        has_deadtime=advanced_timer,
        has_fault_input=advanced_timer,
        has_center_aligned=True,
        has_synchronized_update=True,
        control_reg=reg("CR1", 0x00),
        output_enable_reg=reg("CCER", 0x20),
        status_reg=reg("SR", 0x10),
        clock_reg=reg("PSC", 0x28),
        sync_reg=reg("EGR", 0x14),
        master_output_enable_field=(
            field("BDTR", ("MOE",), 0x44, 15) if advanced_timer else _invalid_field_ref(base)
        ),
        load_field=field("EGR", ("UG",), 0x14, 0),
        clear_load_field=_invalid_field_ref(base),
        clock_prescaler_field=field("PSC", ("PSC",), 0x28, 0, 16),
    )


def _st_pwm_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[PwmChannelSemanticRow, ...]:
    advanced_timer = peripheral_name in {"TIM1", "TIM8"}
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    rows: list[PwmChannelSemanticRow] = []
    for channel_index in range(4):
        channel_number = channel_index + 1
        mode_register_name = "CCMR1_INPUT" if channel_index < 2 else "CCMR2_INPUT"
        mode_register_offset = 0x18 if channel_index < 2 else 0x1C
        slot_offset = 0 if channel_index % 2 == 0 else 8
        compare_offset = 0x34 + (channel_index * 0x04)
        rows.append(
            PwmChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_complementary_output=advanced_timer and channel_index < 3,
                supports_deadtime=advanced_timer,
                control_reg=reg(mode_register_name, mode_register_offset),
                compare_reg=reg(f"CCR{channel_number}", compare_offset),
                secondary_compare_reg=_invalid_register_ref(base),
                period_reg=reg("ARR", 0x2C),
                deadtime_reg=reg("BDTR", 0x44) if advanced_timer else _invalid_register_ref(base),
                enable_field=field("CCER", (f"CC{channel_number}E",), 0x20, channel_index * 4),
                interrupt_enable_field=field(
                    "DIER",
                    (f"CC{channel_number}IE",),
                    0x0C,
                    channel_number,
                ),
                interrupt_flag_field=field(
                    "SR",
                    (f"CC{channel_number}IF",),
                    0x10,
                    channel_number,
                ),
                mode_field=field(
                    mode_register_name,
                    (f"OC{channel_number}M",),
                    mode_register_offset,
                    4 + slot_offset,
                    3,
                ),
                polarity_field=field(
                    "CCER",
                    (f"CC{channel_number}P",),
                    0x20,
                    1 + (channel_index * 4),
                ),
                complementary_output_enable_field=(
                    field(
                        "CCER",
                        (f"CC{channel_number}NE",),
                        0x20,
                        2 + (channel_index * 4),
                    )
                    if advanced_timer and channel_index < 3
                    else _invalid_field_ref(base)
                ),
                center_aligned_field=field("CR1", ("CMS",), 0x00, 5, 2),
                period_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="ARR",
                    register_offset=0x2C,
                    bit_offset=0,
                    bit_width=_st_timer_counter_bits(peripheral_name),
                ),
                duty_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"CCR{channel_number}",
                    register_offset=compare_offset,
                    bit_offset=0,
                    bit_width=_st_timer_counter_bits(peripheral_name),
                ),
                deadtime_rise_field=(
                    field("BDTR", ("DTG",), 0x44, 0, 8)
                    if advanced_timer
                    else _invalid_field_ref(base)
                ),
                deadtime_fall_field=(
                    field("BDTR", ("DTG",), 0x44, 0, 8)
                    if advanced_timer
                    else _invalid_field_ref(base)
                ),
            )
        )
    return tuple(rows)


def _microchip_pwm_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> PwmSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return PwmSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=24,
        channel_count=4,
        has_complementary_outputs=True,
        has_deadtime=True,
        has_fault_input=True,
        has_center_aligned=True,
        has_synchronized_update=True,
        control_reg=reg("CLK", 0x00),
        output_enable_reg=reg("ENA", 0x04),
        status_reg=reg("SR", 0x0C),
        clock_reg=reg("CLK", 0x00),
        sync_reg=reg("SCUC", 0x28),
        master_output_enable_field=_invalid_field_ref(base),
        load_field=field("SCUC", ("UPDULOCK",), 0x28, 0),
        clear_load_field=_invalid_field_ref(base),
        clock_prescaler_field=field("CLK", ("PREA",), 0x00, 8, 4),
    )


def _microchip_pwm_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[PwmChannelSemanticRow, ...]:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    rows: list[PwmChannelSemanticRow] = []
    for channel_index in range(4):
        stride = channel_index * 0x20
        rows.append(
            PwmChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_complementary_output=True,
                supports_deadtime=True,
                control_reg=reg(f"CMR{channel_index}", 0x200 + stride),
                compare_reg=reg(f"CDTY{channel_index}", 0x204 + stride),
                secondary_compare_reg=_invalid_register_ref(base),
                period_reg=reg(f"CPRD{channel_index}", 0x20C + stride),
                deadtime_reg=reg(f"DT{channel_index}", 0x218 + stride),
                enable_field=field("ENA", (f"CHID{channel_index}",), 0x04, channel_index),
                interrupt_enable_field=field(
                    "IER1",
                    (f"CHID{channel_index}",),
                    0x10,
                    channel_index,
                ),
                interrupt_flag_field=field(
                    "ISR1",
                    (f"CHID{channel_index}",),
                    0x1C,
                    channel_index,
                ),
                mode_field=field(
                    f"CMR{channel_index}",
                    ("CPRE",),
                    0x200 + stride,
                    0,
                    4,
                ),
                polarity_field=field(
                    f"CMR{channel_index}",
                    ("CPOL",),
                    0x200 + stride,
                    9,
                ),
                complementary_output_enable_field=_invalid_field_ref(base),
                center_aligned_field=field(
                    f"CMR{channel_index}",
                    ("CALG",),
                    0x200 + stride,
                    8,
                ),
                period_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"CPRD{channel_index}",
                    register_offset=0x20C + stride,
                    bit_offset=0,
                    bit_width=24,
                ),
                duty_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"CDTY{channel_index}",
                    register_offset=0x204 + stride,
                    bit_offset=0,
                    bit_width=24,
                ),
                deadtime_rise_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"DT{channel_index}",
                    register_offset=0x218 + stride,
                    bit_offset=16,
                    bit_width=16,
                ),
                deadtime_fall_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"DT{channel_index}",
                    register_offset=0x218 + stride,
                    bit_offset=0,
                    bit_width=16,
                ),
            )
        )
    return tuple(rows)


def _nxp_pwm_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> PwmSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return PwmSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=16,
        channel_count=4,
        has_complementary_outputs=True,
        has_deadtime=True,
        has_fault_input=True,
        has_center_aligned=True,
        has_synchronized_update=True,
        control_reg=reg("MCTRL", 0x188),
        output_enable_reg=reg("OUTEN", 0x180),
        status_reg=reg("FSTS0", 0x18E),
        clock_reg=_invalid_register_ref(base),
        sync_reg=reg("MCTRL", 0x188),
        master_output_enable_field=_invalid_field_ref(base),
        load_field=field("MCTRL", ("LDOK",), 0x188, 0, 4),
        clear_load_field=field("MCTRL", ("CLDOK",), 0x188, 4, 4),
        clock_prescaler_field=_invalid_field_ref(base),
    )


def _nxp_pwm_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[PwmChannelSemanticRow, ...]:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    rows: list[PwmChannelSemanticRow] = []
    for channel_index in range(4):
        stride = channel_index * 0x60
        rows.append(
            PwmChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_complementary_output=True,
                supports_deadtime=True,
                control_reg=reg(f"SM{channel_index}CTRL", 0x06 + stride),
                compare_reg=reg(f"SM{channel_index}VAL2", 0x10 + stride),
                secondary_compare_reg=reg(f"SM{channel_index}VAL3", 0x12 + stride),
                period_reg=reg(f"SM{channel_index}VAL1", 0x0C + stride),
                deadtime_reg=reg(f"SM{channel_index}DTCNT0", 0x28 + stride),
                enable_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="OUTEN",
                    register_offset=0x180,
                    bit_offset=8 + channel_index,
                ),
                interrupt_enable_field=_invalid_field_ref(base),
                interrupt_flag_field=_invalid_field_ref(base),
                mode_field=_invalid_field_ref(base),
                polarity_field=_invalid_field_ref(base),
                complementary_output_enable_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="OUTEN",
                    register_offset=0x180,
                    bit_offset=4 + channel_index,
                ),
                center_aligned_field=_invalid_field_ref(base),
                period_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"SM{channel_index}VAL1",
                    register_offset=0x0C + stride,
                    bit_offset=0,
                    bit_width=16,
                ),
                duty_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"SM{channel_index}VAL2",
                    register_offset=0x10 + stride,
                    bit_offset=0,
                    bit_width=16,
                ),
                deadtime_rise_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"SM{channel_index}DTCNT0",
                    register_offset=0x28 + stride,
                    bit_offset=0,
                    bit_width=16,
                ),
                deadtime_fall_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"SM{channel_index}DTCNT1",
                    register_offset=0x2A + stride,
                    bit_offset=0,
                    bit_width=16,
                ),
            )
        )
    return tuple(rows)


def _build_pwm_rows(
    context: _SemanticContext,
) -> tuple[tuple[PwmSemanticRow, ...], tuple[PwmChannelSemanticRow, ...]]:
    pwm_rows: list[PwmSemanticRow] = []
    channel_rows: list[PwmChannelSemanticRow] = []
    timer_candidates = context.runtime_peripherals_by_class.get("timer", ())
    dedicated_pwm_candidates = context.runtime_peripherals_by_class.get("pwm", ())

    for peripheral in timer_candidates:
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.timer.st-"):
            pwm_rows.append(
                _st_pwm_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(_st_pwm_channel_rows(context, peripheral_name=peripheral.name))
        # Non-ST timers (NXP GPT, RP2040 TIMER, etc.) are handled in their own
        # timer builder and should NOT emit PWM rows here.

    for peripheral in dedicated_pwm_candidates:
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id == "alloy.pwm.microchip-pwm-y":
            pwm_rows.append(
                _microchip_pwm_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(
                _microchip_pwm_channel_rows(context, peripheral_name=peripheral.name)
            )
        elif schema_id == "alloy.pwm.nxp-pwm":
            pwm_rows.append(
                _nxp_pwm_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(_nxp_pwm_channel_rows(context, peripheral_name=peripheral.name))
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (PwmSemanticTraits<PeripheralId::) is satisfied for devices whose
            # dedicated PWM IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            pwm_rows.append(
                PwmSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    counter_bits=0,
                    channel_count=0,
                    has_complementary_outputs=False,
                    has_deadtime=False,
                    has_fault_input=False,
                    has_center_aligned=False,
                    has_synchronized_update=False,
                    control_reg=invalid_reg,
                    output_enable_reg=invalid_reg,
                    status_reg=invalid_reg,
                    clock_reg=invalid_reg,
                    sync_reg=invalid_reg,
                    master_output_enable_field=invalid_field,
                    load_field=invalid_field,
                    clear_load_field=invalid_field,
                    clock_prescaler_field=invalid_field,
                    is_stub=True,
                )
            )
            # Add a single stub channel row so the artifact contract check for
            # PwmChannelSemanticTraits<PeripheralId:: is satisfied.
            channel_rows.append(
                PwmChannelSemanticRow(
                    peripheral_name=peripheral.name,
                    channel_index=0,
                    supports_complementary_output=False,
                    supports_deadtime=False,
                    control_reg=invalid_reg,
                    compare_reg=invalid_reg,
                    secondary_compare_reg=invalid_reg,
                    period_reg=invalid_reg,
                    deadtime_reg=invalid_reg,
                    enable_field=invalid_field,
                    interrupt_enable_field=invalid_field,
                    interrupt_flag_field=invalid_field,
                    mode_field=invalid_field,
                    polarity_field=invalid_field,
                    complementary_output_enable_field=invalid_field,
                    center_aligned_field=invalid_field,
                    period_field=invalid_field,
                    duty_field=invalid_field,
                    deadtime_rise_field=invalid_field,
                    deadtime_fall_field=invalid_field,
                )
            )
    enriched_pwm_rows = _enrich_pwm_tier234(context, tuple(pwm_rows))
    return tuple(enriched_pwm_rows), tuple(channel_rows)  # type: ignore[return-value]


def _enrich_pwm_tier234(
    context: _SemanticContext,
    rows: tuple[object, ...],
) -> tuple[object, ...]:
    """add-pwm-tier-2-3-4-data: thread Tier 2/3/4 facts onto each PWM
    row from the device patch's `pwm_*` tuples + the matching
    `timer_prescaler_options` (PWM uses the same PSC range as its
    backing timer)."""
    import dataclasses as _dc

    device = context.device
    flags_by_peripheral = {
        getattr(p, "peripheral", ""): p for p in getattr(device, "pwm_mode_flags", ())
    }
    deadtime_by_peripheral: dict[str, list[tuple[int, int, int]]] = {}
    for d in getattr(device, "pwm_deadtime_options", ()):
        deadtime_by_peripheral.setdefault(getattr(d, "peripheral", ""), []).append(
            (
                int(getattr(d, "prescaler_field_value", 0)),
                int(getattr(d, "count_bits", 8)),
                int(getattr(d, "max_ns", 0)),
            )
        )
    alignments_by_peripheral: dict[str, list[tuple[str, int]]] = {}
    for a in getattr(device, "pwm_alignment_options", ()):
        alignments_by_peripheral.setdefault(getattr(a, "peripheral", ""), []).append(
            (getattr(a, "alignment", ""), int(getattr(a, "field_value", 0)))
        )
    breaks_by_peripheral: dict[str, list[tuple[str, int, int]]] = {}
    for b in getattr(device, "pwm_break_inputs", ()):
        breaks_by_peripheral.setdefault(getattr(b, "peripheral", ""), []).append(
            (
                getattr(b, "input_id", ""),
                int(getattr(b, "polarity_field_value", 0)),
                int(getattr(b, "enable_field_value", 1)),
            )
        )
    psc_by_peripheral = {
        getattr(p, "peripheral", ""): p for p in getattr(device, "timer_prescaler_options", ())
    }
    enriched: list[object] = []
    for row in rows:
        peripheral = getattr(row, "peripheral_name", None)
        if peripheral is None:
            enriched.append(row)
            continue
        kw: dict[str, Any] = {}
        psc = psc_by_peripheral.get(peripheral)
        if psc is not None:
            kw["max_prescaler"] = int(getattr(psc, "max_prescaler", 0))
            ar = int(getattr(psc, "max_auto_reload", 0))
            kw["max_period"] = ar if ar else int(getattr(psc, "max_prescaler", 0))
        if peripheral in deadtime_by_peripheral:
            kw["deadtime_options"] = tuple(deadtime_by_peripheral[peripheral])
        if peripheral in alignments_by_peripheral:
            kw["supported_alignments"] = tuple(alignments_by_peripheral[peripheral])
        if peripheral in breaks_by_peripheral:
            kw["break_inputs"] = tuple(breaks_by_peripheral[peripheral])
        flg = flags_by_peripheral.get(peripheral)
        if flg is not None:
            kw["supports_deadtime"] = bool(getattr(flg, "supports_deadtime", False))
            kw["supports_break_input"] = bool(getattr(flg, "supports_break_input", False))
            kw["supports_complementary_outputs"] = bool(
                getattr(flg, "supports_complementary_outputs", False)
            )
            kw["supports_asymmetric_pwm"] = bool(getattr(flg, "supports_asymmetric_pwm", False))
            kw["supports_combined_pwm"] = bool(getattr(flg, "supports_combined_pwm", False))
        if not kw:
            enriched.append(row)
            continue
        # pyright: ignore[reportArgumentType] — row is duck-typed via the
        # `tuple[Any, ...]` parameter from _emit_peripheral_semantics_header;
        # at runtime it is always a PwmSemanticRow dataclass instance.
        enriched.append(_dc.replace(row, **kw))  # pyright: ignore[reportArgumentType]
    return tuple(enriched)


def _pwm_specialization_builder(context: _SemanticContext):
    def _build(row: PwmSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                "  static constexpr std::uint32_t kCounterBits = 0u;",
                "  static constexpr std::uint32_t kChannelCount = 0u;",
                "  static constexpr bool kHasComplementaryOutputs = false;",
                "  static constexpr bool kHasDeadtime = false;",
                "  static constexpr bool kHasFaultInput = false;",
                "  static constexpr bool kHasCenterAligned = false;",
                "  static constexpr bool kHasSynchronizedUpdate = false;",
                "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kOutputEnableRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kClockRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSyncRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kMasterOutputEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kLoadField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearLoadField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClockPrescalerField = kInvalidFieldRef;",
                *_pwm_tier234_lines(row),
            ]
        register_members = {
            "kControlRegister": row.control_reg,
            "kOutputEnableRegister": row.output_enable_reg,
            "kStatusRegister": row.status_reg,
            "kClockRegister": row.clock_reg,
            "kSyncRegister": row.sync_reg,
        }
        field_members = {
            "kMasterOutputEnableField": row.master_output_enable_field,
            "kLoadField": row.load_field,
            "kClearLoadField": row.clear_load_field,
            "kClockPrescalerField": row.clock_prescaler_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr std::uint32_t kCounterBits = {row.counter_bits}u;",
            f"  static constexpr std::uint32_t kChannelCount = {row.channel_count}u;",
            "  static constexpr bool kHasComplementaryOutputs = "
            + ("true" if row.has_complementary_outputs else "false")
            + ";",
            f"  static constexpr bool kHasDeadtime = {'true' if row.has_deadtime else 'false'};",
            "  static constexpr bool kHasFaultInput = "
            + ("true" if row.has_fault_input else "false")
            + ";",
            "  static constexpr bool kHasCenterAligned = "
            + ("true" if row.has_center_aligned else "false")
            + ";",
            "  static constexpr bool kHasSynchronizedUpdate = "
            + ("true" if row.has_synchronized_update else "false")
            + ";",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        lines.extend(_pwm_tier234_lines(row))
        return lines

    return _build


def _pwm_lut_struct_lines() -> list[str]:
    """Per-class hardware-LUT struct.  Carries every scalar +
    register / field reference; variable-length tier 2/3/4 arrays
    stay on the per-instance specialisation."""
    return [
        "struct PwmHardwareLut {",
        "  BackendSchemaId schema_id;",
        "  std::uint32_t counter_bits;",
        "  std::uint32_t channel_count;",
        "  bool has_complementary_outputs;",
        "  bool has_deadtime;",
        "  bool has_fault_input;",
        "  bool has_center_aligned;",
        "  bool has_synchronized_update;",
        "  RuntimeRegisterRef control_register;",
        "  RuntimeRegisterRef output_enable_register;",
        "  RuntimeRegisterRef status_register;",
        "  RuntimeRegisterRef clock_register;",
        "  RuntimeRegisterRef sync_register;",
        "  RuntimeFieldRef master_output_enable_field;",
        "  RuntimeFieldRef load_field;",
        "  RuntimeFieldRef clear_load_field;",
        "  RuntimeFieldRef clock_prescaler_field;",
        "  std::uint32_t max_prescaler;",
        "  std::uint32_t max_period;",
        "  bool supports_deadtime;",
        "  bool supports_break_input;",
        "  bool supports_complementary_outputs;",
        "  bool supports_asymmetric_pwm;",
        "  bool supports_combined_pwm;",
        "};",
        "",
    ]


def _pwm_lut_table_lines(
    context: _SemanticContext,
    rows: list[PwmSemanticRow],
) -> list[str]:
    """Render the ``inline constexpr std::array<PwmHardwareLut, N>``
    table indexed by the same ordering as the per-instance
    specialisations."""
    lines: list[str] = [
        f"inline constexpr std::array<PwmHardwareLut, {len(rows)}> kPwmHardwareLut = {{{{",
    ]
    for row in rows:
        lines.append(
            "  {"
            f"{_schema_ref_expr(context, row.schema_id)}, "
            f"{row.counter_bits}u, "
            f"{row.channel_count}u, "
            f"{'true' if row.has_complementary_outputs else 'false'}, "
            f"{'true' if row.has_deadtime else 'false'}, "
            f"{'true' if row.has_fault_input else 'false'}, "
            f"{'true' if row.has_center_aligned else 'false'}, "
            f"{'true' if row.has_synchronized_update else 'false'}, "
            f"{_register_ref_expr(row.control_reg)}, "
            f"{_register_ref_expr(row.output_enable_reg)}, "
            f"{_register_ref_expr(row.status_reg)}, "
            f"{_register_ref_expr(row.clock_reg)}, "
            f"{_register_ref_expr(row.sync_reg)}, "
            f"{_field_ref_expr(row.master_output_enable_field)}, "
            f"{_field_ref_expr(row.load_field)}, "
            f"{_field_ref_expr(row.clear_load_field)}, "
            f"{_field_ref_expr(row.clock_prescaler_field)}, "
            f"{row.max_prescaler}u, "
            f"{row.max_period}u, "
            f"{'true' if row.supports_deadtime else 'false'}, "
            f"{'true' if row.supports_break_input else 'false'}, "
            f"{'true' if row.supports_complementary_outputs else 'false'}, "
            f"{'true' if row.supports_asymmetric_pwm else 'false'}, "
            f"{'true' if row.supports_combined_pwm else 'false'}"
            "},"
        )
    lines.append("}};")
    lines.append("")
    return lines


def _pwm_traits_base_lines(row_count: int) -> list[str]:
    """The shared base that pulls every fact from
    ``kPwmHardwareLut[Index]``.  Per-instance specialisations
    inherit from one of ``PwmTraitsBase<0..N-1>`` so consumers
    keep the existing ``PwmSemanticTraits<P>::kField`` reading
    surface."""
    del row_count  # Single template for every index — no fanout.
    return [
        "template<std::size_t Index>",
        "struct PwmTraitsBase {",
        "  static constexpr auto& kFacts = kPwmHardwareLut[Index];",
        "  static constexpr bool kPresent = true;",
        "  static constexpr BackendSchemaId kSchemaId = kFacts.schema_id;",
        "  static constexpr std::uint32_t kCounterBits = kFacts.counter_bits;",
        "  static constexpr std::uint32_t kChannelCount = kFacts.channel_count;",
        "  static constexpr bool kHasComplementaryOutputs = kFacts.has_complementary_outputs;",
        "  static constexpr bool kHasDeadtime = kFacts.has_deadtime;",
        "  static constexpr bool kHasFaultInput = kFacts.has_fault_input;",
        "  static constexpr bool kHasCenterAligned = kFacts.has_center_aligned;",
        "  static constexpr bool kHasSynchronizedUpdate = kFacts.has_synchronized_update;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kFacts.control_register;",
        "  static constexpr RuntimeRegisterRef kOutputEnableRegister = kFacts.output_enable_register;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kFacts.status_register;",
        "  static constexpr RuntimeRegisterRef kClockRegister = kFacts.clock_register;",
        "  static constexpr RuntimeRegisterRef kSyncRegister = kFacts.sync_register;",
        "  static constexpr RuntimeFieldRef kMasterOutputEnableField = kFacts.master_output_enable_field;",
        "  static constexpr RuntimeFieldRef kLoadField = kFacts.load_field;",
        "  static constexpr RuntimeFieldRef kClearLoadField = kFacts.clear_load_field;",
        "  static constexpr RuntimeFieldRef kClockPrescalerField = kFacts.clock_prescaler_field;",
        "  static constexpr std::uint32_t kMaxPrescaler = kFacts.max_prescaler;",
        "  static constexpr std::uint32_t kMaxPeriod = kFacts.max_period;",
        "  static constexpr bool kSupportsDeadtime = kFacts.supports_deadtime;",
        "  static constexpr bool kSupportsBreakInput = kFacts.supports_break_input;",
        "  static constexpr bool kSupportsComplementaryOutputs = kFacts.supports_complementary_outputs;",
        "  static constexpr bool kSupportsAsymmetricPwm = kFacts.supports_asymmetric_pwm;",
        "  static constexpr bool kSupportsCombinedPwm = kFacts.supports_combined_pwm;",
        "};",
        "",
    ]


def _pwm_per_instance_array_lines(row: PwmSemanticRow) -> list[str]:
    """Variable-length tier 2/3/4 arrays — these stay on the
    per-instance specialisation since their sizes differ across
    instances."""

    def _u8_array(name: str, items: tuple[int, ...]) -> str:
        if not items:
            return f"  static constexpr std::array<std::uint8_t, 0> {name} = {{}};"
        values = ", ".join(f"{v}u" for v in items)
        return (
            f"  static constexpr std::array<std::uint8_t, {len(items)}> {name} = {{{{{values}}}}};"
        )

    deadtime_psc = tuple(p for p, _bits, _ns in row.deadtime_options)
    alignment_vals = tuple(v for _name, v in row.supported_alignments)
    break_polarity = tuple(p for _id, p, _e in row.break_inputs)
    return [
        _u8_array("kDeadtimeOptions", deadtime_psc),
        _u8_array("kSupportedAlignments", alignment_vals),
        _u8_array("kBreakInputs", break_polarity),
    ]


def _pwm_tier234_lines(row: PwmSemanticRow) -> list[str]:
    """add-pwm-tier-2-3-4-data: max prescaler/period + deadtime / alignment /
    break-input arrays + capability flag constexprs."""

    def _u8_array(name: str, items: tuple[int, ...]) -> str:
        if not items:
            return f"  static constexpr std::array<std::uint8_t, 0> {name} = {{}};"
        values = ", ".join(f"{v}u" for v in items)
        return (
            f"  static constexpr std::array<std::uint8_t, {len(items)}> {name} = {{{{{values}}}}};"
        )

    deadtime_psc = tuple(p for p, _bits, _ns in row.deadtime_options)
    alignment_vals = tuple(v for _name, v in row.supported_alignments)
    break_polarity = tuple(p for _id, p, _e in row.break_inputs)
    return [
        f"  static constexpr std::uint32_t kMaxPrescaler = {row.max_prescaler}u;",
        f"  static constexpr std::uint32_t kMaxPeriod = {row.max_period}u;",
        _u8_array("kDeadtimeOptions", deadtime_psc),
        _u8_array("kSupportedAlignments", alignment_vals),
        _u8_array("kBreakInputs", break_polarity),
        f"  static constexpr bool kSupportsDeadtime = {'true' if row.supports_deadtime else 'false'};",
        f"  static constexpr bool kSupportsBreakInput = {'true' if row.supports_break_input else 'false'};",
        f"  static constexpr bool kSupportsComplementaryOutputs = {'true' if row.supports_complementary_outputs else 'false'};",
        f"  static constexpr bool kSupportsAsymmetricPwm = {'true' if row.supports_asymmetric_pwm else 'false'};",
        f"  static constexpr bool kSupportsCombinedPwm = {'true' if row.supports_combined_pwm else 'false'};",
    ]


def _pwm_channel_specialization_lines(
    channel_rows: tuple[PwmChannelSemanticRow, ...],
) -> list[str]:
    """Emit per-channel trait specialisations using the shared-LUT
    pattern.  All channel facts are fixed-size scalars / register +
    field refs, so the entire row goes into the LUT and the
    per-channel specialisation collapses to a one-line inheritance.
    """
    lines = [
        "template<PeripheralId Id, std::size_t ChannelIndex>",
        "struct PwmChannelSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr bool kSupportsComplementaryOutput = false;",
        "  static constexpr bool kSupportsDeadtime = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCompareRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeadtimeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPeriodField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDutyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDeadtimeRiseField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDeadtimeFallField = kInvalidFieldRef;",
        "};",
        "",
    ]
    if not channel_rows:
        return lines

    # Per-class LUT struct.
    lines.extend(
        [
            "struct PwmChannelHardwareLut {",
            "  bool supports_complementary_output;",
            "  bool supports_deadtime;",
            "  RuntimeRegisterRef control_register;",
            "  RuntimeRegisterRef compare_register;",
            "  RuntimeRegisterRef secondary_compare_register;",
            "  RuntimeRegisterRef period_register;",
            "  RuntimeRegisterRef deadtime_register;",
            "  RuntimeFieldRef enable_field;",
            "  RuntimeFieldRef interrupt_enable_field;",
            "  RuntimeFieldRef interrupt_flag_field;",
            "  RuntimeFieldRef mode_field;",
            "  RuntimeFieldRef polarity_field;",
            "  RuntimeFieldRef complementary_output_enable_field;",
            "  RuntimeFieldRef center_aligned_field;",
            "  RuntimeFieldRef period_field;",
            "  RuntimeFieldRef duty_field;",
            "  RuntimeFieldRef deadtime_rise_field;",
            "  RuntimeFieldRef deadtime_fall_field;",
            "};",
            "",
            f"inline constexpr std::array<PwmChannelHardwareLut, {len(channel_rows)}> "
            "kPwmChannelHardwareLut = {{",
        ]
    )
    for row in channel_rows:
        lines.append(
            "  {"
            f"{'true' if row.supports_complementary_output else 'false'}, "
            f"{'true' if row.supports_deadtime else 'false'}, "
            f"{_register_ref_expr(row.control_reg)}, "
            f"{_register_ref_expr(row.compare_reg)}, "
            f"{_register_ref_expr(row.secondary_compare_reg)}, "
            f"{_register_ref_expr(row.period_reg)}, "
            f"{_register_ref_expr(row.deadtime_reg)}, "
            f"{_field_ref_expr(row.enable_field)}, "
            f"{_field_ref_expr(row.interrupt_enable_field)}, "
            f"{_field_ref_expr(row.interrupt_flag_field)}, "
            f"{_field_ref_expr(row.mode_field)}, "
            f"{_field_ref_expr(row.polarity_field)}, "
            f"{_field_ref_expr(row.complementary_output_enable_field)}, "
            f"{_field_ref_expr(row.center_aligned_field)}, "
            f"{_field_ref_expr(row.period_field)}, "
            f"{_field_ref_expr(row.duty_field)}, "
            f"{_field_ref_expr(row.deadtime_rise_field)}, "
            f"{_field_ref_expr(row.deadtime_fall_field)}"
            "},"
        )
    lines.append("}};")
    lines.append("")

    # Shared base — one template, every per-channel specialisation
    # inherits from one instance of it.
    lines.extend(
        [
            "template<std::size_t Index>",
            "struct PwmChannelTraitsBase {",
            "  static constexpr auto& kFacts = kPwmChannelHardwareLut[Index];",
            "  static constexpr bool kPresent = true;",
            "  static constexpr bool kSupportsComplementaryOutput = kFacts.supports_complementary_output;",
            "  static constexpr bool kSupportsDeadtime = kFacts.supports_deadtime;",
            "  static constexpr RuntimeRegisterRef kControlRegister = kFacts.control_register;",
            "  static constexpr RuntimeRegisterRef kCompareRegister = kFacts.compare_register;",
            "  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kFacts.secondary_compare_register;",
            "  static constexpr RuntimeRegisterRef kPeriodRegister = kFacts.period_register;",
            "  static constexpr RuntimeRegisterRef kDeadtimeRegister = kFacts.deadtime_register;",
            "  static constexpr RuntimeFieldRef kEnableField = kFacts.enable_field;",
            "  static constexpr RuntimeFieldRef kInterruptEnableField = kFacts.interrupt_enable_field;",
            "  static constexpr RuntimeFieldRef kInterruptFlagField = kFacts.interrupt_flag_field;",
            "  static constexpr RuntimeFieldRef kModeField = kFacts.mode_field;",
            "  static constexpr RuntimeFieldRef kPolarityField = kFacts.polarity_field;",
            "  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kFacts.complementary_output_enable_field;",
            "  static constexpr RuntimeFieldRef kCenterAlignedField = kFacts.center_aligned_field;",
            "  static constexpr RuntimeFieldRef kPeriodField = kFacts.period_field;",
            "  static constexpr RuntimeFieldRef kDutyField = kFacts.duty_field;",
            "  static constexpr RuntimeFieldRef kDeadtimeRiseField = kFacts.deadtime_rise_field;",
            "  static constexpr RuntimeFieldRef kDeadtimeFallField = kFacts.deadtime_fall_field;",
            "};",
            "",
        ]
    )
    for index, row in enumerate(channel_rows):
        peripheral_id = _enum_identifier(row.peripheral_name)
        lines.append(
            f"template<> struct PwmChannelSemanticTraits<PeripheralId::{peripheral_id}, "
            f"{row.channel_index}u> : PwmChannelTraitsBase<{index}> {{}};"
        )
    lines.append("")
    return lines


def _pwm_slice_hw_traits_block(device: CanonicalDeviceIR) -> list[str]:
    if not device.rp2040_pwm_slice_hw:
        return [
            "// complete-rp2040-semantics Phase D: per-slice PWM HW facts.",
            "template<std::uint8_t SliceIndex>",
            "struct PwmSliceHwTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint8_t kChannelAPin = 0u;",
            "  static constexpr std::uint8_t kChannelBPin = 0u;",
            "  static constexpr std::uint8_t kCounterBits = 0u;",
            "  static constexpr std::uint16_t kClockDivMinQ4 = 0u;",
            "  static constexpr std::uint16_t kClockDivMaxQ4 = 0u;",
            "};",
            "",
        ]
    lines = [
        "// complete-rp2040-semantics Phase D: per-slice PWM HW facts.",
        "template<std::uint8_t SliceIndex>",
        "struct PwmSliceHwTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr std::uint8_t kChannelAPin = 0u;",
        "  static constexpr std::uint8_t kChannelBPin = 0u;",
        "  static constexpr std::uint8_t kCounterBits = 0u;",
        "  static constexpr std::uint16_t kClockDivMinQ4 = 0u;",
        "  static constexpr std::uint16_t kClockDivMaxQ4 = 0u;",
        "};",
        "",
    ]
    for ctrl in device.rp2040_pwm_slice_hw:
        lines.extend(
            [
                "template<>",
                f"struct PwmSliceHwTraits<{ctrl.slice_index}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint8_t kChannelAPin = {ctrl.channel_a_pin}u;",
                f"  static constexpr std::uint8_t kChannelBPin = {ctrl.channel_b_pin}u;",
                f"  static constexpr std::uint8_t kCounterBits = {ctrl.counter_bits}u;",
                f"  static constexpr std::uint16_t kClockDivMinQ4 = {ctrl.clock_div_min_q4}u;",
                f"  static constexpr std::uint16_t kClockDivMaxQ4 = {ctrl.clock_div_max_q4}u;",
                "};",
                "",
            ]
        )
    return lines


def _flex_pwm_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """extend-pwm-coverage-all-mcus Phase C: NXP iMXRT FlexPWM trait struct.

    iMXRT1060 ships ``PWM1``..``PWM4`` (4 submodules, paired A/B
    channels, complementary outputs, dead-time, fault input,
    force-init).  Per-submodule pad arrays are Phase-C-deferred —
    initial emission carries empty pad tuples; consumer concept
    checks rely on the silicon-fixed flag fields.
    """
    lines = [
        "// extend-pwm-coverage-all-mcus Phase C: NXP iMXRT FlexPWM facts.",
        "enum class RuntimeFlexPwmId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.flex_pwm_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeFlexPwmId Id>",
            "struct FlexPwmTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint8_t kSubmoduleCount = 0u;",
            "  static constexpr bool kPairedChannels = false;",
            "  static constexpr bool kSupportsComplementary = false;",
            "  static constexpr bool kSupportsDeadtime = false;",
            "  static constexpr bool kSupportsFaultInput = false;",
            "  static constexpr bool kSupportsForceInitialization = false;",
            "};",
            "",
        ]
    )
    for ctrl in device.flex_pwm_peripherals:
        lines.extend(
            [
                "template<>",
                f"struct FlexPwmTraits<RuntimeFlexPwmId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint8_t kSubmoduleCount = {ctrl.submodule_count}u;",
                f"  static constexpr bool kPairedChannels = {'true' if ctrl.paired_channels else 'false'};",
                f"  static constexpr bool kSupportsComplementary = {'true' if ctrl.supports_complementary else 'false'};",
                f"  static constexpr bool kSupportsDeadtime = {'true' if ctrl.supports_deadtime else 'false'};",
                f"  static constexpr bool kSupportsFaultInput = {'true' if ctrl.supports_fault_input else 'false'};",
                f"  static constexpr bool kSupportsForceInitialization = {'true' if ctrl.supports_force_initialization else 'false'};",
                "};",
                "",
            ]
        )
    return lines


def _mcpwm_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """extend-pwm-coverage-all-mcus Phase B: Espressif MCPWM trait struct.

    Emits a `RuntimeMcpwmId` enum + `McpwmTraits<RuntimeMcpwmId>`
    template populated from `device.mcpwm_peripherals`.  ESP32 classic
    + S3 ship two MCPWM peripherals each; ESP32-C3 ships none (the
    descriptor list is empty there and only the primary template
    fires).
    """
    lines = [
        "// extend-pwm-coverage-all-mcus Phase B: Espressif MCPWM facts.",
        "enum class RuntimeMcpwmId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.mcpwm_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeMcpwmId Id>",
            "struct McpwmTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint8_t kTimerCount = 0u;",
            "  static constexpr std::uint8_t kOutputSignalCount = 0u;",
            "  static constexpr std::array<std::uint16_t, 0> kGpioMatrixSignals = {};",
            "  static constexpr std::array<std::uint16_t, 0> kCaptureSignals = {};",
            "  static constexpr bool kSupportsDeadtime = false;",
            "  static constexpr bool kSupportsCarrierModulation = false;",
            "  static constexpr bool kSupportsFaultInput = false;",
            "};",
            "",
        ]
    )

    def _signal_array(name: str, signals: tuple[int, ...]) -> str:
        if not signals:
            return f"  static constexpr std::array<std::uint16_t, 0> {name} = {{}};"
        items = ", ".join(f"{s}u" for s in signals)
        return f"  static constexpr std::array<std::uint16_t, {len(signals)}> {name} = {{{items}}};"

    for ctrl in device.mcpwm_peripherals:
        lines.extend(
            [
                "template<>",
                f"struct McpwmTraits<RuntimeMcpwmId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint8_t kTimerCount = {ctrl.timer_count}u;",
                f"  static constexpr std::uint8_t kOutputSignalCount = {ctrl.output_signal_count}u;",
                _signal_array("kGpioMatrixSignals", ctrl.gpio_matrix_signals),
                _signal_array("kCaptureSignals", ctrl.capture_signals),
                f"  static constexpr bool kSupportsDeadtime = {'true' if ctrl.supports_deadtime else 'false'};",
                f"  static constexpr bool kSupportsCarrierModulation = {'true' if ctrl.supports_carrier_modulation else 'false'};",
                f"  static constexpr bool kSupportsFaultInput = {'true' if ctrl.supports_fault_input else 'false'};",
                "};",
                "",
            ]
        )
    return lines


def _avr_da_tca_pwm_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """extend-pwm-coverage-all-mcus Phase D: AVR-DA TCA PWM trait struct.

    Microchip AVR-DA exposes a single TCA0 routed via PORTMUX; emit a
    `RuntimeAvrDaTcaPwmId` enum + `AvrDaTcaPwmTraits` template.  Pad
    lists use the typed `PinId` enum so no string literals leak into
    the runtime C++ output.
    """
    lines = [
        "// extend-pwm-coverage-all-mcus Phase D: Microchip AVR-DA TCA PWM facts.",
        "enum class RuntimeAvrDaTcaPwmId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.avr_da_tca_pwm_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeAvrDaTcaPwmId Id>",
            "struct AvrDaTcaPwmTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::array<PinId, 0> kDefaultChannelPins = {};",
            "  static constexpr std::uint8_t kSplitModeChannels = 0u;",
            "  static constexpr std::uint8_t kSingleModeChannels = 0u;",
            "  static constexpr std::uint8_t kCounterBits = 0u;",
            "  static constexpr bool kPortmuxAlt = false;",
            "};",
            "",
        ]
    )

    def _pad_array(name: str, pads: tuple[str, ...]) -> str:
        if not pads:
            return f"  static constexpr std::array<PinId, 0> {name} = {{}};"
        items = ", ".join(f"PinId::{_enum_identifier(p)}" for p in pads)
        return f"  static constexpr std::array<PinId, {len(pads)}> {name} = {{{items}}};"

    for ctrl in device.avr_da_tca_pwm_peripherals:
        lines.extend(
            [
                "template<>",
                f"struct AvrDaTcaPwmTraits<RuntimeAvrDaTcaPwmId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                _pad_array("kDefaultChannelPins", ctrl.default_channel_pins),
                f"  static constexpr std::uint8_t kSplitModeChannels = {ctrl.split_mode_channels}u;",
                f"  static constexpr std::uint8_t kSingleModeChannels = {ctrl.single_mode_channels}u;",
                f"  static constexpr std::uint8_t kCounterBits = {ctrl.counter_bits}u;",
                f"  static constexpr bool kPortmuxAlt = {'true' if ctrl.portmux_alt else 'false'};",
                "};",
                "",
            ]
        )
    return lines


def _same70_pwm_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """extend-pwm-coverage-all-mcus Phase D: SAM E70 PWM + TC trait struct.

    Emits a `RuntimeSame70PwmKind` enum (Pwm / Tc) plus a
    `RuntimeSame70PwmId` enum + `Same70PwmTraits` template populated
    from `device.same70_pwm_peripherals`.  Per-channel pad mapping is
    Phase-D-deferred (left empty); silicon-fixed flag fields suffice
    for consumer concept checks in this pass.
    """
    lines = [
        "// extend-pwm-coverage-all-mcus Phase D: Microchip SAM E70 PWM/TC facts.",
        "enum class RuntimeSame70PwmKind : std::uint8_t {",
        "  None = 0,",
        "  Pwm = 1,",
        "  Tc = 2,",
        "};",
        "",
        "enum class RuntimeSame70PwmId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.same70_pwm_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeSame70PwmId Id>",
            "struct Same70PwmTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr RuntimeSame70PwmKind kKind = RuntimeSame70PwmKind::None;",
            "  static constexpr std::uint8_t kChannelCount = 0u;",
            "  static constexpr bool kSupportsDeadTime = false;",
            "  static constexpr bool kSupportsFaultInput = false;",
            "  static constexpr bool kSupportsDma = false;",
            "};",
            "",
        ]
    )

    _kind_token = {
        "pwm": "RuntimeSame70PwmKind::Pwm",
        "tc": "RuntimeSame70PwmKind::Tc",
    }

    for ctrl in device.same70_pwm_peripherals:
        kind_enum = _kind_token.get(ctrl.kind, "RuntimeSame70PwmKind::None")
        lines.extend(
            [
                "template<>",
                f"struct Same70PwmTraits<RuntimeSame70PwmId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr RuntimeSame70PwmKind kKind = {kind_enum};",
                f"  static constexpr std::uint8_t kChannelCount = {ctrl.channel_count}u;",
                f"  static constexpr bool kSupportsDeadTime = {'true' if ctrl.supports_dead_time else 'false'};",
                f"  static constexpr bool kSupportsFaultInput = {'true' if ctrl.supports_fault_input else 'false'};",
                f"  static constexpr bool kSupportsDma = {'true' if ctrl.supports_dma else 'false'};",
                "};",
                "",
            ]
        )
    return lines


# _i2c_peripheral_traits_block → runtime_driver/i2c.py


# _adc_peripheral_traits_block → runtime_driver/adc.py


# emit_runtime_driver_dma_semantics_header → runtime_driver/dma.py


def emit_runtime_driver_pwm_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit ``pwm.hpp`` using the shared-LUT pattern introduced by
    ``reduce-cpp-header-bloat-via-shared-luts``.

    The per-instance trait specialisation now extends a shared
    ``PwmTraitsBase<N>`` template that pulls every scalar /
    register / field fact from a single
    ``inline constexpr std::array<PwmHardwareLut, N>`` table.
    The remaining per-instance body carries only the
    variable-length tier 2/3/4 arrays.  Public reading API
    (``PwmSemanticTraits<P>::kField``) stays byte-compatible
    with consumers thanks to template inheritance.
    """
    context = _context(device)
    pwm_rows, channel_rows = _build_pwm_rows(context)
    trait_lines = [
        "template<PeripheralId Id>",
        "struct PwmSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr std::uint32_t kCounterBits = 0u;",
        "  static constexpr std::uint32_t kChannelCount = 0u;",
        "  static constexpr bool kHasComplementaryOutputs = false;",
        "  static constexpr bool kHasDeadtime = false;",
        "  static constexpr bool kHasFaultInput = false;",
        "  static constexpr bool kHasCenterAligned = false;",
        "  static constexpr bool kHasSynchronizedUpdate = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kOutputEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kClockRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSyncRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kMasterOutputEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kLoadField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearLoadField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClockPrescalerField = kInvalidFieldRef;",
        # Tier 2/3/4 facts (add-pwm-tier-2-3-4-data).
        "  static constexpr std::uint32_t kMaxPrescaler = 0u;",
        "  static constexpr std::uint32_t kMaxPeriod = 0u;",
        "  static constexpr std::array<std::uint8_t, 0> kDeadtimeOptions = {};",
        "  static constexpr std::array<std::uint8_t, 0> kSupportedAlignments = {};",
        "  static constexpr std::array<std::uint8_t, 0> kBreakInputs = {};",
        "  static constexpr bool kSupportsDeadtime = false;",
        "  static constexpr bool kSupportsBreakInput = false;",
        "  static constexpr bool kSupportsComplementaryOutputs = false;",
        "  static constexpr bool kSupportsAsymmetricPwm = false;",
        "  static constexpr bool kSupportsCombinedPwm = false;",
        "};",
        "",
    ]
    # Real (non-stub) rows go through the LUT path; stubs keep
    # their bespoke kPresent=false specialisation since they
    # don't carry meaningful facts.
    real_rows = [row for row in pwm_rows if not row.is_stub]
    stub_rows = [row for row in pwm_rows if row.is_stub]
    pwm_peripheral_rows: list[str] = [
        f"  PeripheralId::{_enum_identifier(row.peripheral_name)}," for row in real_rows
    ]
    if real_rows:
        trait_lines.extend(_pwm_lut_struct_lines())
        trait_lines.extend(_pwm_lut_table_lines(context, real_rows))
        trait_lines.extend(_pwm_traits_base_lines(len(real_rows)))
        for index, row in enumerate(real_rows):
            peripheral_id = _enum_identifier(row.peripheral_name)
            trait_lines.extend(
                [
                    "template<>",
                    f"struct PwmSemanticTraits<PeripheralId::{peripheral_id}> "
                    f": PwmTraitsBase<{index}> {{",
                    *_pwm_per_instance_array_lines(row),
                    "};",
                    "",
                ]
            )
    specialization_builder = _pwm_specialization_builder(context)
    for row in stub_rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        trait_lines.extend(
            [
                "template<>",
                f"struct PwmSemanticTraits<PeripheralId::{peripheral_id}> {{",
                *specialization_builder(row),
                "};",
                "",
            ]
        )
    pwm_typed_blocks = _build_pwm_typed_enum_blocks(pwm_rows)
    body = "\n".join(
        [
            *trait_lines,
            *_pwm_channel_specialization_lines(channel_rows),
            *_std_array_lines(
                type_name="PeripheralId",
                variable_name="kPwmSemanticPeripherals",
                row_lines=pwm_peripheral_rows,
            ),
            "",
            *_pwm_slice_hw_traits_block(device),
            "",
            *_stm_timer_pwm_traits_block(device),
            "",
            *_mcpwm_traits_block(device),
            "",
            *_flex_pwm_traits_block(device),
            "",
            *_avr_da_tca_pwm_traits_block(device),
            "",
            *_same70_pwm_traits_block(device),
            *(("",) if pwm_typed_blocks else ()),
            *pwm_typed_blocks,
        ]
    )
    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        body,
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstddef>",
            "#include <cstdint>",
            '#include "common.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            PWM_DRIVER_HEADER,
        ),
        content=content,
    )


# PIO emitter migrated to ``runtime_driver/pio.py`` —
# see top-of-file ``from .runtime_driver.pio import …`` re-export.


__all__ = [
    "PWM_DRIVER_HEADER",
    "PwmChannelSemanticRow",
    "PwmSemanticRow",
    "emit_runtime_driver_pwm_semantics_header",
]
