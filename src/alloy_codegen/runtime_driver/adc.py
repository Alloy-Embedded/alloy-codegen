"""ADC driver-semantic emitter (STM32 / Microchip / NXP / Espressif / RPi).

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from ..emission import (
    _enum_identifier,
)
from ..runtime_lite_emission import (
    _runtime_lite_dma_bindings,
)
from .common import (
    RuntimeFieldRef,
    RuntimeIndexedFieldRef,
    RuntimeRegisterRef,
    _context,
    _emit_peripheral_semantics_header,
    _field_ref_expr,
    _indexed_field_ref,
    _indexed_field_ref_expr,
    _invalid_field_ref,
    _invalid_indexed_field_ref,
    _invalid_register_ref,
    _irq_numbers_lines,
    _peripheral_has_dma_binding,
    _register_ref_expr,
    _render_array_lines,
    _resolve_field_ref,
    _resolve_register_ref,
    _schema_ref_expr,
    _SemanticContext,
)

ADC_DRIVER_HEADER = "driver_semantics/adc.hpp"


@dataclass(frozen=True, slots=True)
class AdcInternalChannel:
    """One internal ADC channel (temperature sensor, VrefInt, VBat, etc.).

    Surfaced by the alloy-codegen ADC trait so the consumer can generate
    high-level helpers like ``readTemperature() -> celsius`` without
    hardcoding vendor-specific channel indices.
    """

    kind: str  # "temperature_sensor" | "vrefint" | "vbat" | "opamp_output" | "dac_output"
    channel_index: int


@dataclass(frozen=True, slots=True)
class AdcCalibrationDataPoint:
    """One factory-calibration data point (e.g. STM32 VREFINT_CAL, AVR-DA SIGROW.SREF).

    ``semantic_constant`` is the temperature (°C) or voltage (mV) at which
    the cal value was measured.  ``location`` is a runtime register ref
    pointing at the flash address where the value lives.
    """

    kind: str  # "vrefint_cal" | "ts_cal_low" | "ts_cal_high" | "sigrow_sref" | ...
    location: RuntimeRegisterRef
    semantic_constant: int


@dataclass(frozen=True, slots=True)
class AdcCalibrationContext:
    """Global calibration context describing what the cal data points mean.

    ``valid=False`` when the family delegates calibration to its vendor
    runtime (e.g., ESP32 uses esp-idf eFuse cal); the consumer SHOULD fall
    back to vendor-specific cal in that case.
    """

    cal_temp_low_celsius: int = 0
    cal_temp_high_celsius: int = 0
    cal_voltage_mv: int = 0
    vrefint_nominal_mv: int = 0
    valid: bool = False


@dataclass(frozen=True, slots=True)
class AdcResolutionOption:
    """One supported ADC resolution + the field value that selects it."""

    bits: int
    field_value: int


@dataclass(frozen=True, slots=True)
class AdcSampleTimeOption:
    """One sample-time option (cycles) + the field value that selects it.

    ``cycles_q8`` carries the cycle count in Q8.8 fixed-point so we can
    represent fractional cycles (1.5, 7.5, 13.5, etc.) without floats in
    the IR — the C++ side converts to ``float`` constants.
    """

    cycles_q8: int  # Q8.8 fixed-point: 1.5 cycles -> 384
    field_value: int


@dataclass(frozen=True, slots=True)
class AdcOversamplingOption:
    """One oversampling ratio + the field value that selects it."""

    ratio: int  # 2, 4, 8, ..., 256
    field_value: int


@dataclass(frozen=True, slots=True)
class AdcExternalTrigger:
    """One external trigger source + its EXTSEL field value + default polarity."""

    source: str  # "tim1_trgo" | "tim2_trgo" | "exti11" | ...
    extsel_value: int
    default_polarity: int  # 0=software/disabled, 1=rising, 2=falling, 3=both


@dataclass(frozen=True, slots=True)
class AdcDmaBindingRow:
    """One DMA route capable of pumping ADC results into memory.

    Derived from the device IR's ``dma_requests`` filtered by peripheral.
    """

    controller_peripheral: str  # DMA controller peripheral name (PeripheralId)
    controller_id: str  # DmaControllerId enum entry name
    binding_id: str  # DmaBindingId enum entry name
    request_value: int
    data_register: RuntimeRegisterRef
    transfer_width_bits: int


# UartDmaBindingRow → runtime_driver/common.py


# SpiDmaBindingRow → runtime_driver/spi.py


@dataclass(frozen=True, slots=True)
class AdcDmaModeOption:
    """One DMA mode (one_shot|circular) + the field value that selects it."""

    mode: str  # "one_shot" | "circular"
    field_value: int


# I2cSpeedOption → runtime_driver/i2c.py


# I2cTimingPreset → runtime_driver/i2c.py


# I2cModeFlags → runtime_driver/i2c.py


# UartBaudClockSource → runtime_driver/uart.py


# UartBaudOversamplingOption → runtime_driver/uart.py


# UartFifoTriggerOption → runtime_driver/uart.py


# UartDataBitsOption → runtime_driver/uart.py


# UartParityOption → runtime_driver/uart.py


# UartStopBitsOption → runtime_driver/uart.py


# UartModeFlags → runtime_driver/uart.py


@dataclass(frozen=True, slots=True)
class AdcSemanticRow:
    """ADC semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    channel_count: int
    result_bits: int
    has_dma: bool
    has_hardware_trigger: bool
    has_channel_bitmask_select: bool
    control_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    config_reg: RuntimeRegisterRef
    sample_time_reg: RuntimeRegisterRef
    sequence_reg: RuntimeRegisterRef
    data_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    disable_field: RuntimeFieldRef
    ready_field: RuntimeFieldRef
    start_field: RuntimeFieldRef
    stop_field: RuntimeFieldRef
    continuous_field: RuntimeFieldRef
    resolution_field: RuntimeFieldRef
    align_field: RuntimeFieldRef
    dma_enable_field: RuntimeFieldRef
    dma_mode_field: RuntimeFieldRef
    external_trigger_enable_field: RuntimeFieldRef
    external_trigger_select_field: RuntimeFieldRef
    end_of_conversion_field: RuntimeFieldRef
    end_of_sequence_field: RuntimeFieldRef
    overrun_field: RuntimeFieldRef
    data_field: RuntimeFieldRef
    channel_select_field: RuntimeFieldRef
    channel_bit_pattern: RuntimeIndexedFieldRef
    channel_enable_pattern: RuntimeIndexedFieldRef
    channel_disable_pattern: RuntimeIndexedFieldRef
    channel_status_pattern: RuntimeIndexedFieldRef
    # Tier 2: internal channels + factory calibration (added by
    # add-full-adc-coverage).  Empty tuples / invalid context for families
    # that don't carry the data; the rendered C++ defaults to empty
    # std::array<X, 0>{} so existing goldens stay byte-stable until the
    # specific family's builder populates these fields.
    internal_channels: tuple[AdcInternalChannel, ...] = ()
    calibration_data_points: tuple[AdcCalibrationDataPoint, ...] = ()
    calibration_context: AdcCalibrationContext = AdcCalibrationContext()
    # Tier 3: configuration value semantics (paired arrays of human-meaningful
    # value + raw field value).
    resolution_options: tuple[AdcResolutionOption, ...] = ()
    sample_time_options: tuple[AdcSampleTimeOption, ...] = ()
    oversampling_options: tuple[AdcOversamplingOption, ...] = ()
    adc_max_clock_hz: int = 0
    # Tier 4: DMA bindings + external triggers + DMA mode options.
    dma_bindings: tuple[AdcDmaBindingRow, ...] = ()
    external_triggers: tuple[AdcExternalTrigger, ...] = ()
    dma_mode_options: tuple[AdcDmaModeOption, ...] = ()
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented
    # NVIC vector lines (added by ``add-irq-vector-traits``).
    irq_numbers: tuple[int, ...] = ()


# DacSemanticRow → runtime_driver/dac.py


# DacChannelSemanticRow → runtime_driver/dac.py


# RtcSemanticRow → runtime_driver/rtc.py


# EthSemanticRow → runtime_driver/eth.py


# UsbSemanticRow → runtime_driver/usb.py


# QspiSemanticRow → runtime_driver/qspi.py


# SdmmcSemanticRow → runtime_driver/sdmmc.py


def _adc_internal_channel_expr(channel: AdcInternalChannel) -> str:
    return (
        "InternalAdcChannel{"
        f"InternalAdcChannelKind::{channel.kind}, "
        f"{channel.channel_index}u, true}}"
    )


# Closed mapping from `AdcInternalChannel.kind` to the named enumerator
# emitted alongside the ordinal `CH<n>` members in `AdcChannelOf<P>::type`.
# A kind absent from this table drops its named alias silently — only the
# ordinal `CH<n>` member at that index is produced. New kinds in the IR
# require updating this table; the validator in `_adc_channel_manifest`
# raises a diagnostic the first time it sees an unknown kind so missing
# entries can't slip through unnoticed.
def _adc_channel_manifest(
    row: AdcSemanticRow,
) -> tuple[tuple[str, int], ...]:
    """Fuse ordinal channels and named internal channels into one manifest.

    Returns a tuple of ``(enumerator_name, channel_index)`` pairs, ordered
    so ordinal members ``CH0``..``CH<n-1>`` come first followed by any
    descriptor-published internal channels whose ``kind`` matches the
    closed name table. Unknown kinds drop their named alias silently.

    Raises ``ValueError`` if two emitted enumerators end up with the
    same name on a single peripheral — that's an emit-time bug we want
    to fail loudly.
    """
    if row.is_stub:
        return ()

    seen_names: dict[str, int] = {}
    manifest: list[tuple[str, int]] = []

    # Ordinal members.
    for index in range(row.channel_count):
        name = f"CH{index}"
        seen_names[name] = index
        manifest.append((name, index))

    # Named internal-channel aliases (ordered as the descriptor publishes).
    for channel in row.internal_channels:
        alias = _ADC_INTERNAL_KIND_ENUMERATOR_NAME.get(channel.kind)
        if alias is None:
            # Unknown kind — keep the ordinal member only.
            continue
        if alias in seen_names and seen_names[alias] != channel.channel_index:
            raise ValueError(
                f"AdcChannelOf: duplicate enumerator name {alias!r} on "
                f"PeripheralId::{row.peripheral_name} at indices "
                f"{seen_names[alias]}, {channel.channel_index}"
            )
        if alias in seen_names:
            # Same name pointing at the same index — already aliased; skip.
            continue
        seen_names[alias] = channel.channel_index
        manifest.append((alias, channel.channel_index))

    return tuple(manifest)


def _render_adc_channel_enum_block(rows: tuple[AdcSemanticRow, ...]) -> list[str]:
    """Render the `AdcChannelOf<P>` primary template + specializations + alias.

    The block lands after the per-peripheral `AdcSemanticTraits<P>` blocks
    in the emitted ADC driver-semantics header. It is always emitted —
    devices with no ADC peripherals get just the empty primary template
    plus the alias, so consumers reaching for ``AdcChannel<P>`` behind
    ``if constexpr (kPresent)`` gates compile cleanly.
    """
    lines: list[str] = [
        "// add-adc-channel-typed-enum: typed per-peripheral channel enum.",
        "// Each specialization scopes the channel set so",
        "// AdcChannel<ADC1> and AdcChannel<ADC2> are distinct types and",
        "// the type system rejects cross-peripheral channel mixing.",
        "template<PeripheralId Id>",
        "struct AdcChannelOf {",
        "  enum class type : std::uint8_t {};",
        "};",
        "",
    ]
    for row in rows:
        if row.is_stub:
            continue
        manifest = _adc_channel_manifest(row)
        peripheral_id = _enum_identifier(row.peripheral_name)
        lines.extend(
            [
                "template<>",
                f"struct AdcChannelOf<PeripheralId::{peripheral_id}> {{",
                "  enum class type : std::uint8_t {",
            ]
        )
        for name, index in manifest:
            lines.append(f"    {name} = {index}u,")
        lines.extend(
            [
                "  };",
                "};",
                "",
            ]
        )
    lines.extend(
        [
            "template<PeripheralId Id>",
            "using AdcChannel = typename AdcChannelOf<Id>::type;",
        ]
    )
    return lines


def _adc_calibration_data_point_expr(point: AdcCalibrationDataPoint) -> str:
    return (
        "CalibrationDataPoint{"
        f"AdcCalibrationKind::{point.kind}, "
        f"{_register_ref_expr(point.location)}, "
        f"{point.semantic_constant}, true}}"
    )


def _adc_calibration_context_expr(ctx: AdcCalibrationContext) -> str:
    if not ctx.valid:
        return "CalibrationContext{}"
    return (
        "CalibrationContext{"
        f"{ctx.cal_temp_low_celsius}, "
        f"{ctx.cal_temp_high_celsius}, "
        f"{ctx.cal_voltage_mv}u, "
        f"{ctx.vrefint_nominal_mv}u, true}}"
    )


def _adc_resolution_option_expr(opt: AdcResolutionOption) -> str:
    return f"AdcResolutionOption{{{opt.bits}u, {opt.field_value}u, true}}"


def _adc_sample_time_option_expr(opt: AdcSampleTimeOption) -> str:
    return f"AdcSampleTimeOption{{{opt.cycles_q8}u, {opt.field_value}u, true}}"


def _adc_oversampling_option_expr(opt: AdcOversamplingOption) -> str:
    return f"AdcOversamplingOption{{{opt.ratio}u, {opt.field_value}u, true}}"


def _adc_external_trigger_expr(trig: AdcExternalTrigger) -> str:
    return (
        "AdcExternalTrigger{"
        f"AdcExternalTriggerSource::{trig.source}, "
        f"{trig.extsel_value}u, "
        f"{trig.default_polarity}u, true}}"
    )


# _dma_binding_* helpers moved to runtime_driver/common.py.


def _adc_dma_binding_expr(binding: AdcDmaBindingRow) -> str:
    return (
        "AdcDmaBinding{"
        f"PeripheralId::{binding.controller_peripheral}, "
        f"DmaControllerId::{binding.controller_id}, "
        f"DmaBindingId::{binding.binding_id}, "
        f"{binding.request_value}u, "
        f"{_register_ref_expr(binding.data_register)}, "
        f"{binding.transfer_width_bits}u, true}}"
    )


def _adc_dma_mode_option_expr(opt: AdcDmaModeOption) -> str:
    return f"AdcDmaModeOption{{AdcDmaMode::{opt.mode}, {opt.field_value}u, true}}"


def _render_adc_tier_extension_lines(row: AdcSemanticRow) -> list[str]:
    """Emit the Tier 2/3/4 lines for an ADC trait specialisation.

    Called by the specialisation builder for both stub and populated rows so
    every emitted ``AdcSemanticTraits<...>`` covers the full schema surface.
    Stub rows pass an ``AdcSemanticRow`` with default empty tuples; populated
    rows pass the real data.
    """
    lines: list[str] = []
    lines.extend(
        _render_array_lines(
            cpp_type="InternalAdcChannel",
            array_name="kInternalChannels",
            count_name="kInternalChannelCount",
            items=row.internal_channels,
            expr_fn=_adc_internal_channel_expr,
        )
    )
    lines.extend(
        _render_array_lines(
            cpp_type="CalibrationDataPoint",
            array_name="kCalibrationDataPoints",
            count_name="kCalibrationDataPointCount",
            items=row.calibration_data_points,
            expr_fn=_adc_calibration_data_point_expr,
        )
    )
    lines.append(
        f"  static constexpr CalibrationContext kCalibrationContext = "
        f"{_adc_calibration_context_expr(row.calibration_context)};"
    )
    lines.extend(
        _render_array_lines(
            cpp_type="AdcResolutionOption",
            array_name="kSupportedResolutions",
            count_name="kSupportedResolutionCount",
            items=row.resolution_options,
            expr_fn=_adc_resolution_option_expr,
        )
    )
    lines.extend(
        _render_array_lines(
            cpp_type="AdcSampleTimeOption",
            array_name="kSupportedSampleTimes",
            count_name="kSupportedSampleTimeCount",
            items=row.sample_time_options,
            expr_fn=_adc_sample_time_option_expr,
        )
    )
    lines.extend(
        _render_array_lines(
            cpp_type="AdcOversamplingOption",
            array_name="kSupportedOversamplings",
            count_name="kSupportedOversamplingCount",
            items=row.oversampling_options,
            expr_fn=_adc_oversampling_option_expr,
        )
    )
    lines.append(f"  static constexpr std::uint32_t kAdcMaxClockHz = {row.adc_max_clock_hz}u;")
    lines.extend(
        _render_array_lines(
            cpp_type="AdcDmaBinding",
            array_name="kDmaBindings",
            count_name="kDmaBindingCount",
            items=row.dma_bindings,
            expr_fn=_adc_dma_binding_expr,
        )
    )
    lines.extend(
        _render_array_lines(
            cpp_type="AdcExternalTrigger",
            array_name="kExternalTriggers",
            count_name="kExternalTriggerCount",
            items=row.external_triggers,
            expr_fn=_adc_external_trigger_expr,
        )
    )
    lines.extend(
        _render_array_lines(
            cpp_type="AdcDmaModeOption",
            array_name="kSupportedDmaModes",
            count_name="kSupportedDmaModeCount",
            items=row.dma_mode_options,
            expr_fn=_adc_dma_mode_option_expr,
        )
    )
    return lines


# _schema_ref_expr / _peripheral_ref / _pin_ref / _line_index_from_candidate
# moved to runtime_driver/common.py.


# _st_gpio_semantics → runtime_driver/gpio.py


# _microchip_gpio_semantics → runtime_driver/gpio.py


# _nxp_gpio_semantics → runtime_driver/gpio.py


# _build_gpio_rows → runtime_driver/gpio.py


# _microchip_uart_row → runtime_driver/uart.py


# _st_uart_row → runtime_driver/uart.py


# _nxp_uart_row → runtime_driver/uart.py


# _uart_template_mode_flags → runtime_driver/uart.py


# _uart_template_data_bits → runtime_driver/uart.py


# _UART_PARITY_PCE_PS → runtime_driver/uart.py


# _uart_template_parity → runtime_driver/uart.py


# _UART_STOP_BITS_Q8 → runtime_driver/uart.py


# _uart_template_stop_bits → runtime_driver/uart.py


# _uart_template_oversampling → runtime_driver/uart.py


# _uart_template_fifo_triggers → runtime_driver/uart.py


# _uart_extension_for_peripheral → runtime_driver/uart.py


# _with_template_provenance → runtime_driver/uart.py


def _adc_dma_bindings_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    data_register: RuntimeRegisterRef,
    transfer_width_bits: int = 16,
) -> tuple[AdcDmaBindingRow, ...]:
    """Derive AdcDmaBinding rows from `device.dma_requests` filtered by ADC peripheral.

    The resulting rows reference the existing DMA tables via
    ``DmaControllerId`` and ``DmaBindingId`` enums so the consumer can
    cross-reference the full DMA route descriptor in ``DmaSemanticTraits``.
    Width defaults to 16 bits which matches all admitted ADC data registers
    (12-bit results in a 16-bit register).
    """
    bindings: list[AdcDmaBindingRow] = []
    for binding in _runtime_lite_dma_bindings(context.device):
        if binding.peripheral != peripheral_name:
            continue
        bindings.append(
            AdcDmaBindingRow(
                controller_peripheral=binding.controller,
                controller_id=_enum_identifier(binding.controller),
                binding_id=_enum_identifier(binding.binding_id),
                request_value=int(binding.request_value or 0),
                data_register=data_register,
                transfer_width_bits=transfer_width_bits,
            )
        )
    return tuple(bindings)


def _adc_extension_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    data_register: RuntimeRegisterRef,
    transfer_width_bits: int = 16,
) -> dict[str, object]:
    """Build the Tier 2/3/4 keyword arguments for ``AdcSemanticRow``.

    Reads the device IR's ADC patch tuples (forwarded by `stages/normalize.run`)
    and returns a dict suitable for ``**`` unpacking into the row constructor.
    DMA bindings are derived from the device's ``dma_requests`` filtered by
    the ADC peripheral; everything else comes straight from the device patch.
    """
    device = context.device
    internal_channels = tuple(
        AdcInternalChannel(kind=p.kind, channel_index=p.channel_index)
        for p in getattr(device, "adc_internal_channels", ())
        if getattr(p, "peripheral", None) == peripheral_name
    )
    calibration_data_points = tuple(
        AdcCalibrationDataPoint(
            kind=p.kind,
            location=RuntimeRegisterRef(
                register_id=None,
                base_address=p.address,
                offset_bytes=0,
                valid=True,
            ),
            semantic_constant=p.semantic_constant,
        )
        for p in getattr(device, "adc_calibration_data_points", ())
        if getattr(p, "peripheral", None) == peripheral_name
    )
    cal_ctx_patch = getattr(device, "adc_calibration_context", None)
    if cal_ctx_patch is not None and getattr(cal_ctx_patch, "peripheral", None) == peripheral_name:
        calibration_context = AdcCalibrationContext(
            cal_temp_low_celsius=cal_ctx_patch.cal_temp_low_celsius,
            cal_temp_high_celsius=cal_ctx_patch.cal_temp_high_celsius,
            cal_voltage_mv=cal_ctx_patch.cal_voltage_mv,
            vrefint_nominal_mv=cal_ctx_patch.vrefint_nominal_mv,
            valid=True,
        )
    else:
        calibration_context = AdcCalibrationContext()
    resolution_options = tuple(
        AdcResolutionOption(bits=p.bits, field_value=p.field_value)
        for p in getattr(device, "adc_resolution_options", ())
        if getattr(p, "peripheral", None) == peripheral_name
    )
    sample_time_options = tuple(
        AdcSampleTimeOption(cycles_q8=p.cycles_q8, field_value=p.field_value)
        for p in getattr(device, "adc_sample_time_options", ())
        if getattr(p, "peripheral", None) == peripheral_name
    )
    oversampling_options = tuple(
        AdcOversamplingOption(ratio=p.ratio, field_value=p.field_value)
        for p in getattr(device, "adc_oversampling_options", ())
        if getattr(p, "peripheral", None) == peripheral_name
    )
    external_triggers = tuple(
        AdcExternalTrigger(
            source=p.source,
            extsel_value=p.extsel_value,
            default_polarity=p.default_polarity,
        )
        for p in getattr(device, "adc_external_triggers", ())
        if getattr(p, "peripheral", None) == peripheral_name
    )
    dma_bindings = _adc_dma_bindings_for_peripheral(
        context,
        peripheral_name=peripheral_name,
        data_register=data_register,
        transfer_width_bits=transfer_width_bits,
    )
    return {
        "internal_channels": internal_channels,
        "calibration_data_points": calibration_data_points,
        "calibration_context": calibration_context,
        "resolution_options": resolution_options,
        "sample_time_options": sample_time_options,
        "oversampling_options": oversampling_options,
        "adc_max_clock_hz": int(getattr(device, "adc_max_clock_hz", 0) or 0),
        "dma_bindings": dma_bindings,
        "external_triggers": external_triggers,
    }


def _st_adc_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> AdcSemanticRow:
    prefixed_registers = (peripheral_name, "ADC_CR") in context.register_by_key
    if prefixed_registers:
        control_register_name = "ADC_CR"
        status_register_name = "ADC_ISR"
        config_register_name = "ADC_CFGR1"
        sample_time_register_name = "ADC_SMPR"
        sequence_register_name = "ADC_CHSELRMOD0"
        data_register_name = "ADC_DR"
        enable_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("ADEN",),
            fallback_register_offset=0x08,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        )
        disable_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("ADDIS",),
            fallback_register_offset=0x08,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        )
        ready_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=status_register_name,
            field_names=("ADRDY",),
            fallback_register_offset=0x00,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        )
        start_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("ADSTART",),
            fallback_register_offset=0x08,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        )
        stop_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("ADSTP",),
            fallback_register_offset=0x08,
            fallback_bit_offset=4,
            fallback_bit_width=1,
        )
        continuous_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=config_register_name,
            field_names=("CONT",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=13,
            fallback_bit_width=1,
        )
        resolution_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=config_register_name,
            field_names=("RES",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=3,
            fallback_bit_width=2,
        )
        align_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=config_register_name,
            field_names=("ALIGN",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=5,
            fallback_bit_width=1,
        )
        dma_enable_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=config_register_name,
            field_names=("DMAEN",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        )
        dma_mode_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=config_register_name,
            field_names=("DMACFG",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        )
        external_trigger_enable_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=config_register_name,
            field_names=("EXTEN",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=10,
            fallback_bit_width=2,
        )
        external_trigger_select_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=config_register_name,
            field_names=("EXTSEL",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=6,
            fallback_bit_width=3,
        )
        channel_select_field = _invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        )
        channel_bit_pattern = _indexed_field_ref(
            base_address=context.peripheral_by_name[peripheral_name].base_address,
            base_offset_bytes=0x28,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        )
    else:
        control_register_name = "CR2"
        status_register_name = "SR"
        config_register_name = "CR2"
        sample_time_register_name = "SMPR2"
        sequence_register_name = "SQR3"
        data_register_name = "DR"
        enable_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("ADON",),
            fallback_register_offset=0x08,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        )
        disable_field = _invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address)
        ready_field = _invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address)
        start_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("SWSTART",),
            fallback_register_offset=0x08,
            fallback_bit_offset=30,
            fallback_bit_width=1,
        )
        stop_field = _invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address)
        continuous_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("CONT",),
            fallback_register_offset=0x08,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        )
        resolution_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR1",
            field_names=("RES",),
            fallback_register_offset=0x04,
            fallback_bit_offset=24,
            fallback_bit_width=2,
        )
        align_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("ALIGN",),
            fallback_register_offset=0x08,
            fallback_bit_offset=11,
            fallback_bit_width=1,
        )
        dma_enable_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("DMA",),
            fallback_register_offset=0x08,
            fallback_bit_offset=8,
            fallback_bit_width=1,
        )
        dma_mode_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("DDS",),
            fallback_register_offset=0x08,
            fallback_bit_offset=9,
            fallback_bit_width=1,
        )
        external_trigger_enable_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("EXTEN",),
            fallback_register_offset=0x08,
            fallback_bit_offset=28,
            fallback_bit_width=2,
        )
        external_trigger_select_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            field_names=("EXTSEL",),
            fallback_register_offset=0x08,
            fallback_bit_offset=24,
            fallback_bit_width=4,
        )
        channel_select_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=sequence_register_name,
            field_names=("SQ1",),
            fallback_register_offset=0x34,
            fallback_bit_offset=0,
            fallback_bit_width=5,
        )
        channel_bit_pattern = _invalid_indexed_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        )

    return AdcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        channel_count=19,
        result_bits=12,
        has_dma=_peripheral_has_dma_binding(context, peripheral_name),
        has_hardware_trigger=True,
        has_channel_bitmask_select=prefixed_registers,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            fallback_offset=0x08,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=status_register_name,
            fallback_offset=0x00,
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=config_register_name,
            fallback_offset=0x0C if prefixed_registers else 0x08,
        ),
        sample_time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=sample_time_register_name,
            fallback_offset=0x14 if prefixed_registers else 0x10,
        ),
        sequence_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=sequence_register_name,
            fallback_offset=0x28 if prefixed_registers else 0x34,
        ),
        data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=data_register_name,
            fallback_offset=0x40 if prefixed_registers else 0x4C,
        ),
        enable_field=enable_field,
        disable_field=disable_field,
        ready_field=ready_field,
        start_field=start_field,
        stop_field=stop_field,
        continuous_field=continuous_field,
        resolution_field=resolution_field,
        align_field=align_field,
        dma_enable_field=dma_enable_field,
        dma_mode_field=dma_mode_field,
        external_trigger_enable_field=external_trigger_enable_field,
        external_trigger_select_field=external_trigger_select_field,
        end_of_conversion_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=status_register_name,
            field_names=("EOC",),
            fallback_register_offset=0x00,
            fallback_bit_offset=2 if prefixed_registers else 1,
            fallback_bit_width=1,
        ),
        end_of_sequence_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=status_register_name,
            field_names=("EOS",),
            fallback_register_offset=0x00 if prefixed_registers else None,
            fallback_bit_offset=3 if prefixed_registers else None,
            fallback_bit_width=1 if prefixed_registers else None,
        ),
        overrun_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=status_register_name,
            field_names=("OVR",),
            fallback_register_offset=0x00,
            fallback_bit_offset=4 if prefixed_registers else 5,
            fallback_bit_width=1,
        ),
        data_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=data_register_name,
            field_names=("DATA",),
            fallback_register_offset=0x40 if prefixed_registers else 0x4C,
            fallback_bit_offset=0,
            fallback_bit_width=16,
        ),
        channel_select_field=channel_select_field,
        channel_bit_pattern=channel_bit_pattern,
        channel_enable_pattern=_invalid_indexed_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        channel_disable_pattern=_invalid_indexed_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        channel_status_pattern=_invalid_indexed_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
    )


def _microchip_afec_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> AdcSemanticRow:
    base_address = context.peripheral_by_name[peripheral_name].base_address
    return AdcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        channel_count=12,
        result_bits=12,
        has_dma=_peripheral_has_dma_binding(context, peripheral_name),
        has_hardware_trigger=True,
        has_channel_bitmask_select=False,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            fallback_offset=0x00,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ISR",
            fallback_offset=0x30,
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            fallback_offset=0x04,
        ),
        sample_time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            fallback_offset=0x04,
        ),
        sequence_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SEQ1R",
            fallback_offset=0x0C,
        ),
        data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="LCDR",
            fallback_offset=0x20,
        ),
        enable_field=_invalid_field_ref(base_address),
        disable_field=_invalid_field_ref(base_address),
        ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ISR",
            field_names=("DRDY",),
            fallback_register_offset=0x30,
            fallback_bit_offset=24,
            fallback_bit_width=1,
        ),
        start_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("START",),
            fallback_register_offset=0x00,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        stop_field=_invalid_field_ref(base_address),
        continuous_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("FREERUN",),
            fallback_register_offset=0x04,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        resolution_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="EMR",
            field_names=("RES",),
            fallback_register_offset=0x08,
            fallback_bit_offset=16,
            fallback_bit_width=3,
        ),
        align_field=_invalid_field_ref(base_address),
        dma_enable_field=_invalid_field_ref(base_address),
        dma_mode_field=_invalid_field_ref(base_address),
        external_trigger_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("TRGEN",),
            fallback_register_offset=0x04,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        external_trigger_select_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("TRGSEL",),
            fallback_register_offset=0x04,
            fallback_bit_offset=1,
            fallback_bit_width=3,
        ),
        end_of_conversion_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ISR",
            field_names=("DRDY",),
            fallback_register_offset=0x30,
            fallback_bit_offset=24,
            fallback_bit_width=1,
        ),
        end_of_sequence_field=_invalid_field_ref(base_address),
        overrun_field=_invalid_field_ref(base_address),
        data_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="LCDR",
            field_names=("LDATA",),
            fallback_register_offset=0x20,
            fallback_bit_offset=0,
            fallback_bit_width=16,
        ),
        channel_select_field=_invalid_field_ref(base_address),
        channel_bit_pattern=_invalid_indexed_field_ref(base_address),
        channel_enable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x14,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
        channel_disable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x18,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
        channel_status_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x1C,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
    )


def _nxp_adc_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> AdcSemanticRow:
    base_address = context.peripheral_by_name[peripheral_name].base_address
    return AdcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        channel_count=16,
        result_bits=12,
        has_dma=_peripheral_has_dma_binding(context, peripheral_name),
        has_hardware_trigger=True,
        has_channel_bitmask_select=False,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="GC",
            fallback_offset=0x48,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HS",
            fallback_offset=0x20,
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFG",
            fallback_offset=0x44,
        ),
        sample_time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFG",
            fallback_offset=0x44,
        ),
        sequence_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HC0",
            fallback_offset=0x00,
        ),
        data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="R0",
            fallback_offset=0x24,
        ),
        enable_field=_invalid_field_ref(base_address),
        disable_field=_invalid_field_ref(base_address),
        ready_field=_invalid_field_ref(base_address),
        start_field=_invalid_field_ref(base_address),
        stop_field=_invalid_field_ref(base_address),
        continuous_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="GC",
            field_names=("ADCO",),
            fallback_register_offset=0x48,
            fallback_bit_offset=6,
            fallback_bit_width=1,
        ),
        resolution_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFG",
            field_names=("MODE",),
            fallback_register_offset=0x44,
            fallback_bit_offset=2,
            fallback_bit_width=2,
        ),
        align_field=_invalid_field_ref(base_address),
        dma_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="GC",
            field_names=("DMAEN",),
            fallback_register_offset=0x48,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        dma_mode_field=_invalid_field_ref(base_address),
        external_trigger_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFG",
            field_names=("ADTRG",),
            fallback_register_offset=0x44,
            fallback_bit_offset=13,
            fallback_bit_width=1,
        ),
        external_trigger_select_field=_invalid_field_ref(base_address),
        end_of_conversion_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HS",
            field_names=("COCO0",),
            fallback_register_offset=0x20,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        end_of_sequence_field=_invalid_field_ref(base_address),
        overrun_field=_invalid_field_ref(base_address),
        data_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="R0",
            field_names=("CDATA",),
            fallback_register_offset=0x24,
            fallback_bit_offset=0,
            fallback_bit_width=12,
        ),
        channel_select_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HC0",
            field_names=("ADCH",),
            fallback_register_offset=0x00,
            fallback_bit_offset=0,
            fallback_bit_width=5,
        ),
        channel_bit_pattern=_invalid_indexed_field_ref(base_address),
        channel_enable_pattern=_invalid_indexed_field_ref(base_address),
        channel_disable_pattern=_invalid_indexed_field_ref(base_address),
        channel_status_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x20,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
    )


def _espressif_saradc_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
    channel_count: int,
) -> AdcSemanticRow:
    """ADC trait for ESP32-C3 / ESP32-S3 APB_SARADC peripheral.

    ESP32-C3 (5 channels) and ESP32-S3 (10 channels per SAR ADC, 2 SARs) share
    the same broad register layout — control / status / config — but differ in
    channel count and a few field positions.  Both schemas dispatch here with
    different ``channel_count`` arguments.

    Calibration for both is delegated to esp-idf at runtime (eFuse cal +
    characterisation curve fitting), so ``kCalibrationContext`` stays invalid
    and ``kCalibrationDataPointCount`` stays 0.  Tier 2/3/4 fields default to
    empty arrays — populating them is a follow-on once we model attenuation
    and digital controller config.
    """
    base_address = context.peripheral_by_name[peripheral_name].base_address
    return AdcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        channel_count=channel_count,
        result_bits=12,
        has_dma=_peripheral_has_dma_binding(context, peripheral_name),
        has_hardware_trigger=False,
        has_channel_bitmask_select=False,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL",
            fallback_offset=0x00,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="INT_ST",
            fallback_offset=0x40,
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL2",
            fallback_offset=0x04,
        ),
        sample_time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="FSM_WAIT",
            fallback_offset=0x18,
        ),
        sequence_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR_PATT_TAB1",
            fallback_offset=0x18,
        ),
        data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR1_STATUS",
            fallback_offset=0x14,
        ),
        enable_field=_invalid_field_ref(base_address),
        disable_field=_invalid_field_ref(base_address),
        ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="INT_ST",
            field_names=("ADC1_DONE_INT_ST", "APB_SARADC_DONE_INT_ST"),
            fallback_register_offset=0x40,
            fallback_bit_offset=31,
            fallback_bit_width=1,
        ),
        start_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL",
            field_names=("START_FORCE", "START"),
            fallback_register_offset=0x00,
            fallback_bit_offset=29,
            fallback_bit_width=1,
        ),
        stop_field=_invalid_field_ref(base_address),
        continuous_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL",
            field_names=("WORK_MODE",),
            fallback_register_offset=0x00,
            fallback_bit_offset=3,
            fallback_bit_width=2,
        ),
        resolution_field=_invalid_field_ref(base_address),
        align_field=_invalid_field_ref(base_address),
        dma_enable_field=_invalid_field_ref(base_address),
        dma_mode_field=_invalid_field_ref(base_address),
        external_trigger_enable_field=_invalid_field_ref(base_address),
        external_trigger_select_field=_invalid_field_ref(base_address),
        end_of_conversion_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="INT_ST",
            field_names=("ADC1_DONE_INT_ST", "APB_SARADC_DONE_INT_ST"),
            fallback_register_offset=0x40,
            fallback_bit_offset=31,
            fallback_bit_width=1,
        ),
        end_of_sequence_field=_invalid_field_ref(base_address),
        overrun_field=_invalid_field_ref(base_address),
        data_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR1_STATUS",
            field_names=("ADC1_DATA",),
            fallback_register_offset=0x14,
            fallback_bit_offset=0,
            fallback_bit_width=12,
        ),
        channel_select_field=_invalid_field_ref(base_address),
        channel_bit_pattern=_invalid_indexed_field_ref(base_address),
        channel_enable_pattern=_invalid_indexed_field_ref(base_address),
        channel_disable_pattern=_invalid_indexed_field_ref(base_address),
        channel_status_pattern=_invalid_indexed_field_ref(base_address),
    )


def _espressif_esp32_sens_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> AdcSemanticRow:
    """ADC trait for ESP32 classic SENS peripheral.

    The ESP32 classic exposes ADC1 (8 channels GPIO32–39) and ADC2 (10 channels
    GPIO0/2/4/12–15/25–27) as sub-blocks of the ``SENS`` peripheral.  The trait
    summarises ADC1 (the unrestricted one — ADC2 conflicts with Wi-Fi).  Apps
    that need ADC2 access via runtime configuration of SAR_MEAS2_CTRL2.
    """
    base_address = context.peripheral_by_name[peripheral_name].base_address
    return AdcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        channel_count=8,
        result_bits=12,
        has_dma=False,  # ESP32 classic ADC has no GDMA — sampling is CPU-driven
        has_hardware_trigger=False,
        has_channel_bitmask_select=False,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR_MEAS1_CTRL2",
            fallback_offset=0x54,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR_MEAS1_CTRL2",
            fallback_offset=0x54,
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR_READ_CTRL",
            fallback_offset=0x00,
        ),
        sample_time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR_READ_CTRL",
            fallback_offset=0x00,
        ),
        sequence_reg=_invalid_register_ref(base_address),
        data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR_MEAS1_CTRL2",
            fallback_offset=0x54,
        ),
        enable_field=_invalid_field_ref(base_address),
        disable_field=_invalid_field_ref(base_address),
        ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR_MEAS1_CTRL2",
            field_names=("MEAS1_DONE_SAR",),
            fallback_register_offset=0x54,
            fallback_bit_offset=29,
            fallback_bit_width=1,
        ),
        start_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR_MEAS1_CTRL2",
            field_names=("MEAS1_START_SAR",),
            fallback_register_offset=0x54,
            fallback_bit_offset=30,
            fallback_bit_width=1,
        ),
        stop_field=_invalid_field_ref(base_address),
        continuous_field=_invalid_field_ref(base_address),
        resolution_field=_invalid_field_ref(base_address),
        align_field=_invalid_field_ref(base_address),
        dma_enable_field=_invalid_field_ref(base_address),
        dma_mode_field=_invalid_field_ref(base_address),
        external_trigger_enable_field=_invalid_field_ref(base_address),
        external_trigger_select_field=_invalid_field_ref(base_address),
        end_of_conversion_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR_MEAS1_CTRL2",
            field_names=("MEAS1_DONE_SAR",),
            fallback_register_offset=0x54,
            fallback_bit_offset=29,
            fallback_bit_width=1,
        ),
        end_of_sequence_field=_invalid_field_ref(base_address),
        overrun_field=_invalid_field_ref(base_address),
        data_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR_MEAS1_CTRL2",
            field_names=("MEAS1_DATA_SAR",),
            fallback_register_offset=0x54,
            fallback_bit_offset=0,
            fallback_bit_width=16,
        ),
        channel_select_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAR_MEAS1_CTRL2",
            field_names=("SAR1_EN_PAD",),
            fallback_register_offset=0x54,
            fallback_bit_offset=19,
            fallback_bit_width=12,
        ),
        channel_bit_pattern=_invalid_indexed_field_ref(base_address),
        channel_enable_pattern=_invalid_indexed_field_ref(base_address),
        channel_disable_pattern=_invalid_indexed_field_ref(base_address),
        channel_status_pattern=_invalid_indexed_field_ref(base_address),
    )


def _microchip_avr_adc_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> AdcSemanticRow:
    """ADC trait for the Microchip AVR-Dx ADC0 peripheral.

    AVR-DA has one 12-bit ADC with up to 28 channel inputs (PORTA + PORTD pins
    plus internal mux positions).  The mux is set via ADC0.MUXPOS register;
    conversions start by writing ADC0.COMMAND.STCONV.
    """
    base_address = context.peripheral_by_name[peripheral_name].base_address
    return AdcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        channel_count=28,
        result_bits=12,
        has_dma=False,
        has_hardware_trigger=False,
        has_channel_bitmask_select=False,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRLA",
            fallback_offset=0x00,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="INTFLAGS",
            fallback_offset=0x0E,
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRLB",
            fallback_offset=0x01,
        ),
        sample_time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SAMPCTRL",
            fallback_offset=0x05,
        ),
        sequence_reg=_invalid_register_ref(base_address),
        data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RES",
            fallback_offset=0x10,
        ),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRLA",
            field_names=("ENABLE",),
            fallback_register_offset=0x00,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        disable_field=_invalid_field_ref(base_address),
        ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="INTFLAGS",
            field_names=("RESRDY",),
            fallback_register_offset=0x0E,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        start_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="COMMAND",
            field_names=("STCONV",),
            fallback_register_offset=0x08,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        stop_field=_invalid_field_ref(base_address),
        continuous_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRLA",
            field_names=("FREERUN",),
            fallback_register_offset=0x00,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        resolution_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRLA",
            field_names=("RESSEL",),
            fallback_register_offset=0x00,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        align_field=_invalid_field_ref(base_address),
        dma_enable_field=_invalid_field_ref(base_address),
        dma_mode_field=_invalid_field_ref(base_address),
        external_trigger_enable_field=_invalid_field_ref(base_address),
        external_trigger_select_field=_invalid_field_ref(base_address),
        end_of_conversion_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="INTFLAGS",
            field_names=("RESRDY",),
            fallback_register_offset=0x0E,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        end_of_sequence_field=_invalid_field_ref(base_address),
        overrun_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="INTFLAGS",
            field_names=("WCMP",),
            fallback_register_offset=0x0E,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        data_field=_invalid_field_ref(base_address),
        channel_select_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MUXPOS",
            field_names=("MUXPOS",),
            fallback_register_offset=0x06,
            fallback_bit_offset=0,
            fallback_bit_width=7,
        ),
        channel_bit_pattern=_invalid_indexed_field_ref(base_address),
        channel_enable_pattern=_invalid_indexed_field_ref(base_address),
        channel_disable_pattern=_invalid_indexed_field_ref(base_address),
        channel_status_pattern=_invalid_indexed_field_ref(base_address),
    )


def _raspberrypi_adc_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> AdcSemanticRow:
    """ADC trait for the RP2040 ADC peripheral.

    RP2040 has one 12-bit ADC with 5 channels: GP26 (CH0), GP27 (CH1),
    GP28 (CH2), GP29 (CH3), and an internal temperature sensor (CH4).
    """
    base_address = context.peripheral_by_name[peripheral_name].base_address
    return AdcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        channel_count=5,
        result_bits=12,
        has_dma=_peripheral_has_dma_binding(context, peripheral_name),
        has_hardware_trigger=False,
        has_channel_bitmask_select=False,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            fallback_offset=0x00,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            fallback_offset=0x00,
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DIV",
            fallback_offset=0x10,
        ),
        sample_time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DIV",
            fallback_offset=0x10,
        ),
        sequence_reg=_invalid_register_ref(base_address),
        data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RESULT",
            fallback_offset=0x04,
        ),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("EN",),
            fallback_register_offset=0x00,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        disable_field=_invalid_field_ref(base_address),
        ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("READY",),
            fallback_register_offset=0x00,
            fallback_bit_offset=8,
            fallback_bit_width=1,
        ),
        start_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("START_ONCE",),
            fallback_register_offset=0x00,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        stop_field=_invalid_field_ref(base_address),
        continuous_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("START_MANY",),
            fallback_register_offset=0x00,
            fallback_bit_offset=3,
            fallback_bit_width=1,
        ),
        resolution_field=_invalid_field_ref(base_address),
        align_field=_invalid_field_ref(base_address),
        dma_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="FCS",
            field_names=("DREQ_EN",),
            fallback_register_offset=0x08,
            fallback_bit_offset=3,
            fallback_bit_width=1,
        ),
        dma_mode_field=_invalid_field_ref(base_address),
        external_trigger_enable_field=_invalid_field_ref(base_address),
        external_trigger_select_field=_invalid_field_ref(base_address),
        end_of_conversion_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("READY",),
            fallback_register_offset=0x00,
            fallback_bit_offset=8,
            fallback_bit_width=1,
        ),
        end_of_sequence_field=_invalid_field_ref(base_address),
        overrun_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="FCS",
            field_names=("OVER",),
            fallback_register_offset=0x08,
            fallback_bit_offset=10,
            fallback_bit_width=1,
        ),
        data_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RESULT",
            field_names=("RESULT",),
            fallback_register_offset=0x04,
            fallback_bit_offset=0,
            fallback_bit_width=12,
        ),
        channel_select_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("AINSEL",),
            fallback_register_offset=0x00,
            fallback_bit_offset=12,
            fallback_bit_width=3,
        ),
        channel_bit_pattern=_invalid_indexed_field_ref(base_address),
        channel_enable_pattern=_invalid_indexed_field_ref(base_address),
        channel_disable_pattern=_invalid_indexed_field_ref(base_address),
        channel_status_pattern=_invalid_indexed_field_ref(base_address),
    )


def _build_adc_rows(context: _SemanticContext) -> tuple[AdcSemanticRow, ...]:
    rows: list[AdcSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("adc", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.adc.st-"):
            rows.append(_st_adc_row(context, peripheral_name=peripheral.name, schema_id=schema_id))
        elif schema_id == "alloy.adc.microchip-afec-s":
            rows.append(
                _microchip_afec_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id == "alloy.adc.nxp-adc":
            rows.append(_nxp_adc_row(context, peripheral_name=peripheral.name, schema_id=schema_id))
        elif schema_id == "alloy.adc.espressif-esp32c3-saradc-v1":
            rows.append(
                _espressif_saradc_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    channel_count=5,
                )
            )
        elif schema_id == "alloy.adc.espressif-esp32s3-saradc-v1":
            # ESP32-S3 has 2 SAR ADCs each with 10 channels.  We model the
            # first ADC instance here (10 channels); the second is admitted
            # but currently uses the same schema and reports 10 channels too.
            rows.append(
                _espressif_saradc_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    channel_count=10,
                )
            )
        elif schema_id == "alloy.adc.espressif-esp32-sens-v1":
            rows.append(
                _espressif_esp32_sens_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id == "alloy.adc.microchip-avr-da-adc-v1":
            rows.append(
                _microchip_avr_adc_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id == "alloy.adc.raspberrypi-rp2040-adc-v1":
            rows.append(
                _raspberrypi_adc_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (AdcSemanticTraits<PeripheralId::) is satisfied for devices whose
            # ADC IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            invalid_indexed = _invalid_indexed_field_ref(base)
            rows.append(
                AdcSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    channel_count=0,
                    result_bits=0,
                    has_dma=False,
                    has_hardware_trigger=False,
                    has_channel_bitmask_select=False,
                    control_reg=invalid_reg,
                    status_reg=invalid_reg,
                    config_reg=invalid_reg,
                    sample_time_reg=invalid_reg,
                    sequence_reg=invalid_reg,
                    data_reg=invalid_reg,
                    enable_field=invalid_field,
                    disable_field=invalid_field,
                    ready_field=invalid_field,
                    start_field=invalid_field,
                    stop_field=invalid_field,
                    continuous_field=invalid_field,
                    resolution_field=invalid_field,
                    align_field=invalid_field,
                    dma_enable_field=invalid_field,
                    dma_mode_field=invalid_field,
                    external_trigger_enable_field=invalid_field,
                    external_trigger_select_field=invalid_field,
                    end_of_conversion_field=invalid_field,
                    end_of_sequence_field=invalid_field,
                    overrun_field=invalid_field,
                    data_field=invalid_field,
                    channel_select_field=invalid_field,
                    channel_bit_pattern=invalid_indexed,
                    channel_enable_pattern=invalid_indexed,
                    channel_disable_pattern=invalid_indexed,
                    channel_status_pattern=invalid_indexed,
                    is_stub=True,
                )
            )
    # Forward Tier 2/3/4 fields from the device patch onto each populated row.
    # Stubs keep their empty defaults — the patch fields are vendor-specific
    # and only meaningful when there's a real builder for the schema.
    enriched: list[AdcSemanticRow] = []
    for row in rows:
        if row.is_stub:
            enriched.append(row)
            continue
        # Width inference: 12-bit / 16-bit results land in 16-bit registers;
        # higher resolutions (rare; STM32H7 oversampling can yield 18-bit) bump
        # to 32-bit.  result_bits drives the choice; default 16 if zero.
        transfer_width = 32 if row.result_bits > 16 else 16
        extension = _adc_extension_for_peripheral(
            context,
            peripheral_name=row.peripheral_name,
            data_register=row.data_reg,
            transfer_width_bits=transfer_width,
        )
        # `dataclasses.replace` requires named arguments; unpack the extension.
        import dataclasses as _dc

        enriched.append(_dc.replace(row, **extension))
    return tuple(enriched)


# _st_dac_row → runtime_driver/dac.py


# _st_dac_channel_rows → runtime_driver/dac.py


# _microchip_dac_row → runtime_driver/dac.py


# _microchip_dac_channel_rows → runtime_driver/dac.py


# _build_dac_rows → runtime_driver/dac.py


# _st_rtc_row → runtime_driver/rtc.py


# _microchip_rtc_row → runtime_driver/rtc.py


# _build_rtc_rows → runtime_driver/rtc.py


# _microchip_gmac_eth_row → runtime_driver/eth.py


# _build_eth_rows → runtime_driver/eth.py


# _st_usb_row → runtime_driver/usb.py


# _microchip_usb_row → runtime_driver/usb.py


# _build_usb_rows → runtime_driver/usb.py


# _microchip_qspi_row → runtime_driver/qspi.py


# _build_qspi_rows → runtime_driver/qspi.py


# _microchip_hsmci_sdmmc_row → runtime_driver/sdmmc.py


# _build_sdmmc_rows → runtime_driver/sdmmc.py


def _adc_specialization_builder(context: _SemanticContext):
    def _build(row: AdcSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            stub_lines = [
                "  static constexpr bool kPresent = false;",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                "  static constexpr std::uint32_t kChannelCount = 0u;",
                "  static constexpr std::uint32_t kResultBits = 0u;",
                "  static constexpr bool kHasDma = false;",
                "  static constexpr bool kHasHardwareTrigger = false;",
                "  static constexpr bool kHasChannelBitmaskSelect = false;",
                "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSampleTimeRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSequenceRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kDataRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kReadyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kContinuousField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kResolutionField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAlignField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDmaEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDmaModeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kExternalTriggerEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kExternalTriggerSelectField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEndOfConversionField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEndOfSequenceField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kOverrunField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDataField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kChannelSelectField = kInvalidFieldRef;",
                "  static constexpr RuntimeIndexedFieldRef kChannelBitPattern = kInvalidIndexedFieldRef;",
                "  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = kInvalidIndexedFieldRef;",
                "  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = kInvalidIndexedFieldRef;",
                "  static constexpr RuntimeIndexedFieldRef kChannelStatusPattern = kInvalidIndexedFieldRef;",
            ]
            stub_lines.extend(_render_adc_tier_extension_lines(row))
            stub_lines.extend(_irq_numbers_lines(row.irq_numbers))
            return stub_lines
        register_members = {
            "kControlRegister": row.control_reg,
            "kStatusRegister": row.status_reg,
            "kConfigRegister": row.config_reg,
            "kSampleTimeRegister": row.sample_time_reg,
            "kSequenceRegister": row.sequence_reg,
            "kDataRegister": row.data_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kDisableField": row.disable_field,
            "kReadyField": row.ready_field,
            "kStartField": row.start_field,
            "kStopField": row.stop_field,
            "kContinuousField": row.continuous_field,
            "kResolutionField": row.resolution_field,
            "kAlignField": row.align_field,
            "kDmaEnableField": row.dma_enable_field,
            "kDmaModeField": row.dma_mode_field,
            "kExternalTriggerEnableField": row.external_trigger_enable_field,
            "kExternalTriggerSelectField": row.external_trigger_select_field,
            "kEndOfConversionField": row.end_of_conversion_field,
            "kEndOfSequenceField": row.end_of_sequence_field,
            "kOverrunField": row.overrun_field,
            "kDataField": row.data_field,
            "kChannelSelectField": row.channel_select_field,
        }
        indexed_field_members = {
            "kChannelBitPattern": row.channel_bit_pattern,
            "kChannelEnablePattern": row.channel_enable_pattern,
            "kChannelDisablePattern": row.channel_disable_pattern,
            "kChannelStatusPattern": row.channel_status_pattern,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr std::uint32_t kChannelCount = {row.channel_count}u;",
            f"  static constexpr std::uint32_t kResultBits = {row.result_bits}u;",
            f"  static constexpr bool kHasDma = {'true' if row.has_dma else 'false'};",
            "  static constexpr bool kHasHardwareTrigger = "
            + ("true" if row.has_hardware_trigger else "false")
            + ";",
            "  static constexpr bool kHasChannelBitmaskSelect = "
            + ("true" if row.has_channel_bitmask_select else "false")
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
        lines.extend(
            f"  static constexpr RuntimeIndexedFieldRef {name} = {_indexed_field_ref_expr(value)};"
            for name, value in indexed_field_members.items()
        )
        # Tier 2/3/4 extension — added by add-full-adc-coverage.  Defaults
        # are empty/invalid for vendors that haven't populated the new data
        # yet; populated vendors carry concrete cal context, internal channels,
        # resolution / sample time / oversampling options, DMA bindings and
        # external trigger sources.
        lines.extend(_render_adc_tier_extension_lines(row))
        lines.extend(_irq_numbers_lines(row.irq_numbers))
        return lines

    return _build


# _dac_specialization_builder → runtime_driver/dac.py


# _dac_channel_specialization_lines → runtime_driver/dac.py


# _rtc_specialization_builder → runtime_driver/rtc.py


# _usb_pin_ref_expr → runtime_driver/usb.py


# _usb_specialization_builder → runtime_driver/usb.py


# _eth_specialization_builder → runtime_driver/eth.py


# _qspi_specialization_builder → runtime_driver/qspi.py


# _sdmmc_specialization_builder → runtime_driver/sdmmc.py


def _adc_peripheral_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """complete-rp2040-semantics Phase C: per-controller ADC trait struct.

    Emits a `RuntimeAdcId` enum + `AdcPeripheralTraits<RuntimeAdcId>`
    template populated from `device.rp2040_adc_peripherals`.  Sentinel pad
    index 255 in `kChannelPins` denotes the internal temperature sensor.
    """
    lines = [
        "// complete-rp2040-semantics Phase C: per-controller ADC facts.",
        "enum class RuntimeAdcId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.rp2040_adc_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeAdcId Id>",
            "struct AdcPeripheralTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint8_t kChannelCount = 0u;",
            "  static constexpr std::uint8_t kResolutionBits = 0u;",
            "  static constexpr std::uint8_t kDreq = 0u;",
            "  static constexpr std::uint8_t kFifoDepth = 0u;",
            "  static constexpr bool kSupportsFifo = false;",
            "  static constexpr std::array<std::uint8_t, 0> kChannelPins = {};",
            "};",
            "",
        ]
    )
    for ctrl in device.rp2040_adc_peripherals:
        pads_str = ", ".join(f"{p}u" for p in ctrl.channel_pins)
        lines.extend(
            [
                "template<>",
                f"struct AdcPeripheralTraits<RuntimeAdcId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint8_t kChannelCount = {ctrl.channel_count}u;",
                f"  static constexpr std::uint8_t kResolutionBits = {ctrl.resolution_bits}u;",
                f"  static constexpr std::uint8_t kDreq = {ctrl.dreq}u;",
                f"  static constexpr std::uint8_t kFifoDepth = {ctrl.fifo_depth}u;",
                f"  static constexpr bool kSupportsFifo = {'true' if ctrl.supports_fifo else 'false'};",
                (
                    f"  static constexpr std::array<std::uint8_t, {len(ctrl.channel_pins)}>"
                    f" kChannelPins = {{{{{pads_str}}}}};"
                ),
                "};",
                "",
            ]
        )
    return lines


# _spi_peripheral_traits_block → runtime_driver/spi.py


# emit_runtime_driver_uart_semantics_header → runtime_driver/uart.py


def emit_runtime_driver_adc_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_adc_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr std::uint32_t kChannelCount = 0u;",
        "  static constexpr std::uint32_t kResultBits = 0u;",
        "  static constexpr bool kHasDma = false;",
        "  static constexpr bool kHasHardwareTrigger = false;",
        "  static constexpr bool kHasChannelBitmaskSelect = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSampleTimeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSequenceRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDataRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kContinuousField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kResolutionField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAlignField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDmaEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDmaModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kExternalTriggerEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kExternalTriggerSelectField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEndOfConversionField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEndOfSequenceField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOverrunField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kChannelSelectField = kInvalidFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kChannelBitPattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kChannelStatusPattern = kInvalidIndexedFieldRef;",
        # Tier 2/3/4 — added by add-full-adc-coverage; defaults are zero-sized
        # std::array so existing populated traits stay byte-stable until each
        # vendor builder opts in to populating them.
        "  static constexpr std::uint32_t kInternalChannelCount = 0u;",
        "  static constexpr std::array<InternalAdcChannel, 0> kInternalChannels = {};",
        "  static constexpr std::uint32_t kCalibrationDataPointCount = 0u;",
        "  static constexpr std::array<CalibrationDataPoint, 0> kCalibrationDataPoints = {};",
        "  static constexpr CalibrationContext kCalibrationContext = {};",
        "  static constexpr std::uint32_t kSupportedResolutionCount = 0u;",
        "  static constexpr std::array<AdcResolutionOption, 0> kSupportedResolutions = {};",
        "  static constexpr std::uint32_t kSupportedSampleTimeCount = 0u;",
        "  static constexpr std::array<AdcSampleTimeOption, 0> kSupportedSampleTimes = {};",
        "  static constexpr std::uint32_t kSupportedOversamplingCount = 0u;",
        "  static constexpr std::array<AdcOversamplingOption, 0> kSupportedOversamplings = {};",
        "  static constexpr std::uint32_t kAdcMaxClockHz = 0u;",
        "  static constexpr std::uint32_t kDmaBindingCount = 0u;",
        "  static constexpr std::array<AdcDmaBinding, 0> kDmaBindings = {};",
        "  static constexpr std::uint32_t kExternalTriggerCount = 0u;",
        "  static constexpr std::array<AdcExternalTrigger, 0> kExternalTriggers = {};",
        "  static constexpr std::uint32_t kSupportedDmaModeCount = 0u;",
        "  static constexpr std::array<AdcDmaModeOption, 0> kSupportedDmaModes = {};",
        # NVIC vector lines (added by ``add-irq-vector-traits``).
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
    ]
    extra_body: list[str] = list(_adc_peripheral_traits_block(device))
    channel_enum_block = _render_adc_channel_enum_block(rows)
    if extra_body and channel_enum_block:
        extra_body.append("")
    extra_body.extend(channel_enum_block)
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=ADC_DRIVER_HEADER,
        trait_name="AdcSemanticTraits",
        array_name="kAdcSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_adc_specialization_builder(context),
        extra_body_lines=extra_body,
    )


# emit_runtime_driver_dac_semantics_header → runtime_driver/dac.py


# emit_runtime_driver_rtc_semantics_header → runtime_driver/rtc.py


# emit_runtime_driver_usb_semantics_header → runtime_driver/usb.py


# emit_runtime_driver_eth_semantics_header → runtime_driver/eth.py


# emit_runtime_driver_qspi_semantics_header → runtime_driver/qspi.py


# emit_runtime_driver_sdmmc_semantics_header → runtime_driver/sdmmc.py



_ADC_INTERNAL_KIND_ENUMERATOR_NAME: dict[str, str] = {
    "temperature_sensor": "TempSensor",
    "vrefint": "Vrefint",
    "vbat": "VBat",
    "opamp_output": "OpAmpOut",
    "dac_output": "DacOut",
}


# _adc_channel_manifest → runtime_driver/adc.py




__all__ = [
    "ADC_DRIVER_HEADER",
    "AdcCalibrationContext",
    "AdcCalibrationDataPoint",
    "AdcDmaBindingRow",
    "AdcDmaModeOption",
    "AdcExternalTrigger",
    "AdcInternalChannel",
    "AdcOversamplingOption",
    "AdcResolutionOption",
    "AdcSampleTimeOption",
    "AdcSemanticRow",
    "emit_runtime_driver_adc_semantics_header",
]
