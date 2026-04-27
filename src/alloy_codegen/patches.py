"""Patch loading for bootstrap device metadata."""

from __future__ import annotations

import json
from dataclasses import dataclass
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError


@dataclass(frozen=True, slots=True)
class MemoryPatch:
    """Memory metadata supplied by a patch document."""

    name: str
    kind: str
    base_address: int
    size_bytes: int
    access: str
    address_space: str | None = None


@dataclass(frozen=True, slots=True)
class PinSignalPatch:
    """One curated signal attached to a pin."""

    function: str
    peripheral: str | None
    signal: str | None
    af_number: int | None


@dataclass(frozen=True, slots=True)
class PinPatch:
    """Curated pin metadata supplied by a patch document."""

    name: str
    port: str | None
    number: int
    signals: tuple[PinSignalPatch, ...]


@dataclass(frozen=True, slots=True)
class PeripheralPatch:
    """Curated peripheral metadata supplied by a patch document."""

    name: str
    rcc_enable_signal: str | None
    rcc_reset_signal: str | None
    ip_version: str | None


@dataclass(frozen=True, slots=True)
class PackagePatch:
    """Family-level package metadata."""

    name: str
    pin_count: int


@dataclass(frozen=True, slots=True)
class PinCatalogEntry:
    """Family-level pin identity metadata."""

    name: str
    port: str | None
    number: int
    packages: tuple[str, ...]


@dataclass(frozen=True, slots=True)
class PinSignalCatalogEntry:
    """Family-level named alternate-function signal entry."""

    signal_id: str
    pin_name: str
    signal: PinSignalPatch


@dataclass(frozen=True, slots=True)
class RegisterFieldPatch:
    """Curated register-field metadata used when upstream sources omit bitfields."""

    peripheral: str
    register_name: str
    name: str
    bit_offset: int
    bit_width: int
    access: str | None


@dataclass(frozen=True, slots=True)
class RegisterPatch:
    """Curated register metadata used when upstream sources omit control blocks."""

    peripheral: str
    name: str
    offset_bytes: int
    access: str | None
    size_bits: int | None
    base_address: int | None = None


@dataclass(frozen=True, slots=True)
class DmaControllerPatch:
    """Curated DMA controller metadata supplied by a patch document."""

    controller: str
    channel_count: int | None
    version: str | None


@dataclass(frozen=True, slots=True)
class ClockNodePatch:
    """Curated clock-tree node metadata supplied by a patch document."""

    node_id: str
    kind: str
    parent: str | None
    selector: str | None


@dataclass(frozen=True, slots=True)
class ClockSelectorPatch:
    """Curated clock source-selector metadata supplied by a patch document."""

    selector_id: str
    parent_options: tuple[str, ...]
    register_target: str | None


@dataclass(frozen=True, slots=True)
class ClockGatePatch:
    """Curated clock-gate metadata supplied by a patch document."""

    gate_id: str
    peripheral: str | None
    enable_signal: str
    parent_node: str | None


@dataclass(frozen=True, slots=True)
class ResetPatch:
    """Curated reset descriptor metadata supplied by a patch document."""

    reset_id: str
    peripheral: str | None
    reset_signal: str
    active_level: str | None


@dataclass(frozen=True, slots=True)
class PeripheralClockBindingPatch:
    """Curated peripheral-to-clock/reset binding metadata."""

    peripheral: str
    clock_gate_id: str | None
    reset_id: str | None
    selector_id: str | None


@dataclass(frozen=True, slots=True)
class InterruptPatch:
    """Curated interrupt metadata supplied by a patch document."""

    name: str
    line: int
    peripheral: str | None
    alias_names: tuple[str, ...] = ()


@dataclass(frozen=True, slots=True)
class SystemClockProfilePatch:
    """Curated system clock bring-up profile metadata."""

    profile_id: str
    kind: str
    source_kind: str
    sysclk_hz: int
    hclk_hz: int | None = None
    apb1_hz: int | None = None
    apb2_hz: int | None = None
    pclk_hz: int | None = None
    source_hz: int | None = None
    ahb_prescaler: int | None = None
    apb1_prescaler: int | None = None
    apb2_prescaler: int | None = None
    oscillator_startup_cycles: int | None = None
    mck_prescaler: int | None = None
    cpu_prescaler: int | None = None
    ipg_prescaler: int | None = None
    pll_m: int | None = None
    pll_n: int | None = None
    pll_p: int | None = None
    pll_q: int | None = None
    pll_r: int | None = None
    flash_latency: int | None = None


@dataclass(frozen=True, slots=True)
class FamilyPatchCatalog:
    """Family-level curated catalog used by device overlays."""

    patch_id: str
    packages: tuple[PackagePatch, ...]
    pins: tuple[PinCatalogEntry, ...]
    peripherals: tuple[PeripheralPatch, ...]
    pin_signals: tuple[PinSignalCatalogEntry, ...]
    registers: tuple[RegisterPatch, ...]
    register_fields: tuple[RegisterFieldPatch, ...]
    clock_nodes: tuple[ClockNodePatch, ...]
    clock_selectors: tuple[ClockSelectorPatch, ...]
    clock_gates: tuple[ClockGatePatch, ...]
    resets: tuple[ResetPatch, ...]
    peripheral_clock_bindings: tuple[PeripheralClockBindingPatch, ...]
    system_clock_profiles: tuple[SystemClockProfilePatch, ...]
    dma_controllers: tuple[DmaControllerPatch, ...]
    dma_requests: tuple[DmaRequestCatalogEntry, ...]
    # Optional one-line caveat surfaced by the auto-generated alloy-devices
    # README under "Coverage caveats".  Sourced from
    # ``family.json::__source_notes::__readme_caveat`` — families without the
    # field are silently omitted from the caveats section.  See
    # ``add-publication-scale-features``.
    readme_caveat: str | None = None
    # Multicore topology block from ``family.json::multicore_topology``
    # (added by ``expose-xtensa-dual-core-facts``).  Single-core families
    # carry ``None`` here and downstream consumers default to ``"single_core"``
    # at IR-build time.  Asymmetric Xtensa families (ESP32 classic, ESP32-S3)
    # populate the block with the APP_CPU control register name in
    # ``"PERIPHERAL.REGISTER"`` form — the normalizer resolves it to a typed
    # ``register_id`` after register filtering.
    multicore_topology: MulticoreTopologyPatch | None = None
    # USB controller hardware-feature blocks (added by
    # ``add-usb-semantic-traits``).  Empty tuple for families without USB.
    # The normalizer mirrors each entry into a ``UsbControllerDescriptor``
    # on the device IR.
    usb_controllers: tuple[UsbControllerPatch, ...] = ()
    # Hardware-feature blocks added by ``fill-espressif-semantic-gaps``.
    # Empty for families without explicit overlay; populated for ESP32 /
    # ESP32-C3 / ESP32-S3.
    uart_peripherals: tuple[UartPeripheralPatch, ...] = ()
    spi_peripherals: tuple[SpiPeripheralPatch, ...] = ()
    adc_units: tuple[AdcUnitPatch, ...] = ()
    timer_units: tuple[TimerUnitPatch, ...] = ()
    ledc: LedcPatch | None = None
    dma_channels: tuple[DmaChannelPatch, ...] = ()
    # RP2040 PWM slices (added by ``complete-rp2040-semantics``).
    pwm_slices: tuple[PwmSlicePatch, ...] = ()


@dataclass(frozen=True, slots=True)
class UartPeripheralPatch:
    peripheral_id: str
    base_address: int
    fifo_depth: int
    tx_signal_idx: int | None = None
    rx_signal_idx: int | None = None
    supports_dma: bool = False
    valid_tx_pins: tuple[int, ...] = ()
    valid_rx_pins: tuple[int, ...] = ()
    valid_cts_pins: tuple[int, ...] = ()
    valid_rts_pins: tuple[int, ...] = ()
    dreq_tx: int | None = None
    dreq_rx: int | None = None


@dataclass(frozen=True, slots=True)
class SpiPeripheralPatch:
    peripheral_id: str
    base_address: int
    max_clock_hz: int
    mosi_out_signal: int | None = None
    miso_in_signal: int | None = None
    clk_out_signal: int | None = None
    cs_out_signal: int | None = None
    has_iomux_fast_path: bool = False
    iomux_mosi_pin: int | None = None
    iomux_miso_pin: int | None = None
    iomux_clk_pin: int | None = None
    iomux_cs_pin: int | None = None
    supports_dma: bool = False
    valid_mosi_pins: tuple[int, ...] = ()
    valid_miso_pins: tuple[int, ...] = ()
    valid_clk_pins: tuple[int, ...] = ()
    valid_cs_pins: tuple[int, ...] = ()
    dreq_tx: int | None = None
    dreq_rx: int | None = None


@dataclass(frozen=True, slots=True)
class AdcUnitPatch:
    unit_id: str
    channel_count: int
    resolution_bits: int
    conflicts_with_wifi: bool = False
    channel_pins: tuple[int, ...] = ()
    base_address: int = 0
    supports_fifo: bool = False
    fifo_depth: int = 0
    dreq: int | None = None


@dataclass(frozen=True, slots=True)
class TimerUnitPatch:
    timer_id: str
    group_idx: int
    timer_idx: int
    base_address: int
    bits: int
    clock_sources: tuple[str, ...] = ()
    alarm_count: int = 0
    alarm_dreqs: tuple[int, ...] = ()


@dataclass(frozen=True, slots=True)
class LedcPatch:
    base_address: int
    channel_count: int
    resolution_bits: int
    clock_sources: tuple[str, ...] = ()
    output_signals: tuple[int, ...] = ()


@dataclass(frozen=True, slots=True)
class DmaChannelPatch:
    channel_id: str
    channel_index: int
    is_gdma: bool
    max_transfer_bytes: int = 0
    peripheral_requests: tuple[tuple[str, int], ...] = ()
    base_address: int = 0
    max_transfer_count: int = 0
    supports_chaining: bool = False
    supports_byte_swap: bool = False


@dataclass(frozen=True, slots=True)
class PwmSlicePatch:
    slice_index: int
    channel_a_pin: int
    channel_b_pin: int
    counter_bits: int = 16
    clock_div_min_q4: int = 16
    clock_div_max_q4: int = 4096


@dataclass(frozen=True, slots=True)
class UsbControllerPatch:
    """USB controller hardware-feature block carried in family.json.

    The fields mirror ``UsbControllerDescriptor`` on the IR — patch parsing
    is intentionally a thin pass-through so the normalizer doesn't have to
    re-derive these facts from SVD/ATDF (USB hardware shape doesn't fit
    cleanly into the upstream register descriptions).
    """

    controller_id: str
    base_address: int
    endpoint_count: int
    supports_high_speed: bool = False
    supports_host_mode: bool = False
    supports_dma: bool = False
    crystalless: bool = False
    dpram_base_address: int | None = None
    dpram_size_bytes: int | None = None
    dma_channel_count: int = 0
    dm_pin: str | None = None
    dp_pin: str | None = None
    clock_source: str | None = None


@dataclass(frozen=True, slots=True)
class AppCpuControlPlanePatch:
    """APP_CPU release sequence carried in ``family.json::multicore_topology``.

    ``register`` and ``register_secondary`` are ``"PERIPHERAL.REGISTER"``
    strings; the normalizer resolves them to typed ``register_id`` values.
    """

    register: str
    operation: str
    start_vector_symbol: str
    register_secondary: str | None = None


@dataclass(frozen=True, slots=True)
class MulticoreTopologyPatch:
    """Family-level multicore topology block.

    ``topology`` maps to the IR ``MulticoreTopology`` enum:
    ``"single-core"`` → ``"single_core"``,
    ``"symmetric-dual-core"`` → ``"symmetric_dual_core"``,
    ``"xtensa-asymmetric-dual-core"`` → ``"xtensa_asymmetric_dual_core"``.
    """

    topology: str
    core_count: int
    app_cpu_control_plane: AppCpuControlPlanePatch | None = None


@dataclass(frozen=True, slots=True)
class DmaRequestPatch:
    """Curated DMA routing metadata supplied by a patch document."""

    controller: str
    request_line: str
    peripheral: str | None
    signal: str | None
    channel_index: int | None = None
    request_value: int | None = None
    channel_selector: int | None = None


@dataclass(frozen=True, slots=True)
class DmaRequestCatalogEntry:
    """Family-level named DMA route entry."""

    request_id: str
    request: DmaRequestPatch


# ---------------------------------------------------------------------------
# ADC Tier 2/3/4 patch types (added by add-adc-tier-2-3-4-data)
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class AdcInternalChannelPatch:
    """One internal ADC channel (TempSensor / VrefInt / VBat / opamp / dac)."""

    peripheral: str
    kind: str  # internal channel kind (matches InternalAdcChannelKind enum)
    channel_index: int


@dataclass(frozen=True, slots=True)
class AdcCalibrationDataPointPatch:
    """One factory-calibration data point (e.g. STM32 VREFINT_CAL)."""

    peripheral: str
    kind: str  # AdcCalibrationKind enum entry name
    address: int
    size_bits: int
    semantic_constant: int  # °C for ts_cal_*, mV for vrefint_cal, etc.


@dataclass(frozen=True, slots=True)
class AdcCalibrationContextPatch:
    """Global calibration context (cal temperatures, ref voltages)."""

    peripheral: str
    cal_temp_low_celsius: int
    cal_temp_high_celsius: int
    cal_voltage_mv: int
    vrefint_nominal_mv: int


@dataclass(frozen=True, slots=True)
class AdcResolutionOptionPatch:
    """One supported resolution + the field value that selects it."""

    peripheral: str
    bits: int
    field_value: int


@dataclass(frozen=True, slots=True)
class AdcSampleTimeOptionPatch:
    """One sample-time option (cycles in Q8.8 fixed-point) + field value."""

    peripheral: str
    cycles_q8: int
    field_value: int


@dataclass(frozen=True, slots=True)
class AdcOversamplingOptionPatch:
    """One oversampling ratio + the field value that selects it."""

    peripheral: str
    ratio: int
    field_value: int


@dataclass(frozen=True, slots=True)
class AdcExternalTriggerPatch:
    """One external trigger source (timer/EXTI) + EXTSEL field value."""

    peripheral: str
    source: str  # AdcExternalTriggerSource enum entry name
    extsel_value: int
    default_polarity: int = 1  # 0=disabled, 1=rising (default), 2=falling, 3=both


# ---------------------------------------------------------------------------
# UART + SPI Tier 2/3/4 patch types (added by add-uart-spi-tier-2-3-4-data)
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class PeripheralMaxClockPatch:
    """Datasheet-sourced peripheral input-clock ceiling (added by
    ``add-kernel-clock-traits``).  E.g. ``USART1`` → ``84_000_000`` Hz on
    STM32F4, ``42_000_000`` Hz on STM32G0 PCLK1 peripherals."""

    peripheral: str
    max_clock_hz: int


@dataclass(frozen=True, slots=True)
class UartBaudClockSourcePatch:
    """One UART baud-rate clock source + the field value that selects it."""

    peripheral: str
    source: str  # UartBaudClockSource enum entry (e.g. "pclk", "hsi16")
    field_value: int


@dataclass(frozen=True, slots=True)
class UartBaudOversamplingOptionPatch:
    """8x / 16x oversampling (OVER8 field on STM32, OSR field on LPUART)."""

    peripheral: str
    ratio: int  # 8 or 16
    field_value: int


@dataclass(frozen=True, slots=True)
class UartFifoTriggerOptionPatch:
    """One FIFO trigger level (e.g. 1/4 / 1/2 / 3/4 / full → field value)."""

    peripheral: str
    fraction_q8: int  # Q8.8 fixed-point fraction (Q8(1/4)=64, Q8(1/2)=128, Q8(1)=256)
    field_value: int


@dataclass(frozen=True, slots=True)
class UartDataBitsOptionPatch:
    """One supported data-bits option + the M0/M1 field combination."""

    peripheral: str
    bits: int  # 5 / 6 / 7 / 8 / 9
    m0_value: int = 0
    m1_value: int = 0


@dataclass(frozen=True, slots=True)
class UartParityOptionPatch:
    """One parity option (none / even / odd / mark / space)."""

    peripheral: str
    parity: str  # UartParity enum entry
    pce_value: int  # parity control enable bit
    ps_value: int = 0  # parity select bit


@dataclass(frozen=True, slots=True)
class UartStopBitsOptionPatch:
    """One stop-bits option (½ / 1 / 1½ / 2)."""

    peripheral: str
    stop_bits_q8: int  # Q8.8 fixed-point: Q8(0.5)=128, Q8(1)=256, Q8(2)=512
    field_value: int


@dataclass(frozen=True, slots=True)
class UartModeFlagsPatch:
    """Per-UART mode capability flags (one block per peripheral)."""

    peripheral: str
    supports_lin: bool = False
    supports_irda: bool = False
    supports_smartcard: bool = False
    supports_half_duplex: bool = False
    supports_synchronous: bool = False
    supports_auto_baud: bool = False
    supports_wake_from_stop: bool = False


@dataclass(frozen=True, slots=True)
class SpiBaudPrescalerOptionPatch:
    """One SPI baud-rate prescaler option (e.g. STM32 BR /2../256)."""

    peripheral: str
    divisor: int  # 2, 4, 8, 16, 32, 64, 128, 256
    field_value: int


@dataclass(frozen=True, slots=True)
class SpiFrameSizeOptionPatch:
    """One supported SPI frame size in bits + the DS / DFF field value."""

    peripheral: str
    bits: int  # 4..32 depending on family
    field_value: int


@dataclass(frozen=True, slots=True)
class SpiFifoThresholdOptionPatch:
    """One SPI FIFO threshold (8-bit / 16-bit on STM32 FRXTH)."""

    peripheral: str
    threshold_bits: int  # 8 or 16
    field_value: int


@dataclass(frozen=True, slots=True)
class SpiModeFlagsPatch:
    """Per-SPI mode capability flags (one block per peripheral)."""

    peripheral: str
    supports_crc: bool = False
    supports_ti_frame: bool = False
    supports_motorola_frame: bool = True  # Most SPIs are Motorola by default
    supports_i2s_submode: bool = False
    supports_bidirectional_3wire: bool = False
    supports_lsb_first: bool = False
    supports_nss_hw_management: bool = False


@dataclass(frozen=True, slots=True)
class I2cSpeedOptionPatch:
    """One supported I2C bus speed (added by ``add-i2c-tier-2-3-4-data``).

    ``speed_hz`` is the bus frequency the peripheral can clock at
    (100'000 / 400'000 / 1'000'000 typical).  ``mode`` is the modm-style
    speed-class label (``standard`` / ``fast`` / ``fast_plus``).
    """

    peripheral: str
    speed_hz: int
    mode: str  # "standard" | "fast" | "fast_plus" | "high_speed"


@dataclass(frozen=True, slots=True)
class I2cTimingPresetPatch:
    """Precomputed TIMINGR / CWGR value for one (peripheral, source clock,
    target speed) triple.  Lets the alloy HAL pick the right register
    value at compile time without a runtime calculator."""

    peripheral: str
    speed_hz: int
    source_clock_hz: int
    timingr_value: int


@dataclass(frozen=True, slots=True)
class I2cModeFlagsPatch:
    """Per-I2C mode capability flags (one block per peripheral)."""

    peripheral: str
    supports_smbus: bool = False
    supports_pmbus: bool = False
    supports_dma: bool = False
    supports_slave: bool = True
    supports_dual_address: bool = False
    supports_general_call: bool = False
    supports_7bit_addressing: bool = True
    supports_10bit_addressing: bool = False


@dataclass(frozen=True, slots=True)
class TimerPrescalerOptionPatch:
    """Per-timer prescaler limits (added by ``add-timer-tier-2-3-4-data``)."""

    peripheral: str
    max_prescaler: int  # 0xFFFF for 16-bit PSC, 0xFFFFFFFF for 32-bit
    max_auto_reload: int = 0  # 0 = same as max_prescaler


@dataclass(frozen=True, slots=True)
class TimerTriggerSourcePatch:
    """One timer trigger-source row (ITRx / ETR / TI1F / ...)."""

    peripheral: str
    source: str  # "itr0" | "itr1" | ... | "etr" | "ti1f_ed" | "ti1fp1" | "ti2fp2"
    field_value: int


@dataclass(frozen=True, slots=True)
class TimerMasterOutputPatch:
    """One timer master-output (TRGO) source binding."""

    peripheral: str
    source: str  # "reset" | "enable" | "update" | "compare_pulse" | "oc1ref".."oc4ref"
    field_value: int


@dataclass(frozen=True, slots=True)
class TimerModeFlagsPatch:
    """Per-timer capability flags."""

    peripheral: str
    supports_dma_burst: bool = False
    supports_repetition_counter: bool = False
    supports_xor_input: bool = False


@dataclass(frozen=True, slots=True)
class PwmDeadtimeOptionPatch:
    """One PWM deadtime DTPSC prescaler option (added by
    ``add-pwm-tier-2-3-4-data``)."""

    peripheral: str
    prescaler_field_value: int
    count_bits: int = 8
    max_ns: int = 0


@dataclass(frozen=True, slots=True)
class PwmAlignmentOptionPatch:
    """One supported PWM counter alignment (edge / center-up /
    center-down / center-up-down)."""

    peripheral: str
    alignment: str  # "edge" | "center_up" | "center_down" | "center_up_down"
    field_value: int


@dataclass(frozen=True, slots=True)
class PwmBreakInputPatch:
    """One PWM break-input descriptor (BKIN, BKIN2, FAULT0..3, ...)."""

    peripheral: str
    input_id: str  # "bkin" | "bkin2" | "fault0" | ...
    polarity_field_value: int = 0
    enable_field_value: int = 1


@dataclass(frozen=True, slots=True)
class PwmModeFlagsPatch:
    """Per-PWM capability flags."""

    peripheral: str
    supports_deadtime: bool = False
    supports_break_input: bool = False
    supports_complementary_outputs: bool = False
    supports_asymmetric_pwm: bool = False
    supports_combined_pwm: bool = False


@dataclass(frozen=True, slots=True)
class DevicePatch:
    """Patch document for one bootstrap device."""

    patch_id: str
    family_patch_id: str | None
    device: str
    svd_file: str | None
    pin_data_file: str | None
    package: str
    pin_count: int
    core: str
    summary: str
    memories: tuple[MemoryPatch, ...]
    peripherals: tuple[PeripheralPatch, ...]
    registers: tuple[RegisterPatch, ...]
    register_fields: tuple[RegisterFieldPatch, ...]
    pins: tuple[PinPatch, ...]
    clock_nodes: tuple[ClockNodePatch, ...]
    clock_selectors: tuple[ClockSelectorPatch, ...]
    clock_gates: tuple[ClockGatePatch, ...]
    resets: tuple[ResetPatch, ...]
    peripheral_clock_bindings: tuple[PeripheralClockBindingPatch, ...]
    interrupts: tuple[InterruptPatch, ...]
    system_clock_profiles: tuple[SystemClockProfilePatch, ...]
    dma_controllers: tuple[DmaControllerPatch, ...]
    dma_requests: tuple[DmaRequestPatch, ...]
    # ADC Tier 2/3/4 (added by add-adc-tier-2-3-4-data).  All optional —
    # families that don't curate ADC config carry empty tuples and the
    # AdcSemanticTraits fields default to empty arrays.
    adc_internal_channels: tuple[AdcInternalChannelPatch, ...] = ()
    adc_calibration_data_points: tuple[AdcCalibrationDataPointPatch, ...] = ()
    adc_calibration_context: AdcCalibrationContextPatch | None = None
    adc_resolution_options: tuple[AdcResolutionOptionPatch, ...] = ()
    adc_sample_time_options: tuple[AdcSampleTimeOptionPatch, ...] = ()
    adc_oversampling_options: tuple[AdcOversamplingOptionPatch, ...] = ()
    adc_external_triggers: tuple[AdcExternalTriggerPatch, ...] = ()
    adc_max_clock_hz: int = 0
    # UART + SPI Tier 2/3/4 (added by add-uart-spi-tier-2-3-4-data).  All
    # optional — families that don't curate UART/SPI config carry empty
    # tuples and the *SemanticTraits fields default to empty arrays.
    uart_baud_clock_sources: tuple[UartBaudClockSourcePatch, ...] = ()
    uart_baud_oversampling_options: tuple[UartBaudOversamplingOptionPatch, ...] = ()
    uart_fifo_trigger_options: tuple[UartFifoTriggerOptionPatch, ...] = ()
    uart_data_bits_options: tuple[UartDataBitsOptionPatch, ...] = ()
    uart_parity_options: tuple[UartParityOptionPatch, ...] = ()
    uart_stop_bits_options: tuple[UartStopBitsOptionPatch, ...] = ()
    uart_mode_flags: tuple[UartModeFlagsPatch, ...] = ()
    uart_max_baud_hz: int = 0
    spi_baud_prescaler_options: tuple[SpiBaudPrescalerOptionPatch, ...] = ()
    spi_frame_size_options: tuple[SpiFrameSizeOptionPatch, ...] = ()
    spi_fifo_threshold_options: tuple[SpiFifoThresholdOptionPatch, ...] = ()
    spi_mode_flags: tuple[SpiModeFlagsPatch, ...] = ()
    # Per-peripheral input-clock ceiling (added by ``add-kernel-clock-traits``).
    peripheral_max_clock_hz: tuple[PeripheralMaxClockPatch, ...] = ()
    # add-timer-tier-2-3-4-data
    timer_prescaler_options: tuple[TimerPrescalerOptionPatch, ...] = ()
    timer_trigger_sources: tuple[TimerTriggerSourcePatch, ...] = ()
    timer_master_outputs: tuple[TimerMasterOutputPatch, ...] = ()
    timer_mode_flags: tuple[TimerModeFlagsPatch, ...] = ()
    # I2C Tier 2/3/4 (added by ``add-i2c-tier-2-3-4-data``).
    i2c_speed_options: tuple[I2cSpeedOptionPatch, ...] = ()
    i2c_timing_presets: tuple[I2cTimingPresetPatch, ...] = ()
    i2c_mode_flags: tuple[I2cModeFlagsPatch, ...] = ()
    # add-pwm-tier-2-3-4-data
    pwm_deadtime_options: tuple[PwmDeadtimeOptionPatch, ...] = ()
    pwm_alignment_options: tuple[PwmAlignmentOptionPatch, ...] = ()
    pwm_break_inputs: tuple[PwmBreakInputPatch, ...] = ()
    pwm_mode_flags: tuple[PwmModeFlagsPatch, ...] = ()

    def to_dict(self) -> dict[str, object]:
        return {
            "patch_id": self.patch_id,
            "family_patch_id": self.family_patch_id,
            "device": self.device,
            "svd_file": self.svd_file,
            "pin_data_file": self.pin_data_file,
            "package": self.package,
            "pin_count": self.pin_count,
            "core": self.core,
            "summary": self.summary,
            "memories": [
                {
                    "name": memory.name,
                    "kind": memory.kind,
                    "base_address": memory.base_address,
                    "size_bytes": memory.size_bytes,
                    "access": memory.access,
                }
                for memory in self.memories
            ],
            "peripherals": [
                {
                    "name": peripheral.name,
                    "rcc_enable_signal": peripheral.rcc_enable_signal,
                    "rcc_reset_signal": peripheral.rcc_reset_signal,
                }
                for peripheral in self.peripherals
            ],
            "registers": [
                {
                    "peripheral": register.peripheral,
                    "name": register.name,
                    "offset_bytes": register.offset_bytes,
                    "access": register.access,
                    "size_bits": register.size_bits,
                    "base_address": register.base_address,
                }
                for register in self.registers
            ],
            "register_fields": [
                {
                    "peripheral": field.peripheral,
                    "register_name": field.register_name,
                    "name": field.name,
                    "bit_offset": field.bit_offset,
                    "bit_width": field.bit_width,
                    "access": field.access,
                }
                for field in self.register_fields
            ],
            "pins": [
                {
                    "name": pin.name,
                    "port": pin.port,
                    "number": pin.number,
                    "signals": [
                        {
                            "function": signal.function,
                            "peripheral": signal.peripheral,
                            "signal": signal.signal,
                            "af_number": signal.af_number,
                        }
                        for signal in pin.signals
                    ],
                }
                for pin in self.pins
            ],
            "clock_nodes": [
                {
                    "node_id": node.node_id,
                    "kind": node.kind,
                    "parent": node.parent,
                    "selector": node.selector,
                }
                for node in self.clock_nodes
            ],
            "clock_selectors": [
                {
                    "selector_id": selector.selector_id,
                    "parent_options": list(selector.parent_options),
                    "register_target": selector.register_target,
                }
                for selector in self.clock_selectors
            ],
            "clock_gates": [
                {
                    "gate_id": gate.gate_id,
                    "peripheral": gate.peripheral,
                    "enable_signal": gate.enable_signal,
                    "parent_node": gate.parent_node,
                }
                for gate in self.clock_gates
            ],
            "resets": [
                {
                    "reset_id": reset.reset_id,
                    "peripheral": reset.peripheral,
                    "reset_signal": reset.reset_signal,
                    "active_level": reset.active_level,
                }
                for reset in self.resets
            ],
            "peripheral_clock_bindings": [
                {
                    "peripheral": binding.peripheral,
                    "clock_gate_id": binding.clock_gate_id,
                    "reset_id": binding.reset_id,
                    "selector_id": binding.selector_id,
                }
                for binding in self.peripheral_clock_bindings
            ],
            "interrupts": [
                {
                    "name": interrupt.name,
                    "line": interrupt.line,
                    "peripheral": interrupt.peripheral,
                    "alias_names": list(interrupt.alias_names),
                }
                for interrupt in self.interrupts
            ],
            "system_clock_profiles": [
                {
                    "profile_id": profile.profile_id,
                    "kind": profile.kind,
                    "source_kind": profile.source_kind,
                    "sysclk_hz": profile.sysclk_hz,
                    "hclk_hz": profile.hclk_hz,
                    "apb1_hz": profile.apb1_hz,
                    "apb2_hz": profile.apb2_hz,
                    "pclk_hz": profile.pclk_hz,
                    "source_hz": profile.source_hz,
                    "ahb_prescaler": profile.ahb_prescaler,
                    "apb1_prescaler": profile.apb1_prescaler,
                    "apb2_prescaler": profile.apb2_prescaler,
                    "oscillator_startup_cycles": profile.oscillator_startup_cycles,
                    "mck_prescaler": profile.mck_prescaler,
                    "cpu_prescaler": profile.cpu_prescaler,
                    "ipg_prescaler": profile.ipg_prescaler,
                    "pll_m": profile.pll_m,
                    "pll_n": profile.pll_n,
                    "pll_p": profile.pll_p,
                    "pll_q": profile.pll_q,
                    "pll_r": profile.pll_r,
                    "flash_latency": profile.flash_latency,
                }
                for profile in self.system_clock_profiles
            ],
            "dma_controllers": [
                {
                    "controller": controller.controller,
                    "channel_count": controller.channel_count,
                    "version": controller.version,
                }
                for controller in self.dma_controllers
            ],
            "dma_requests": [
                {
                    "controller": request.controller,
                    "request_line": request.request_line,
                    "peripheral": request.peripheral,
                    "signal": request.signal,
                    "channel_index": request.channel_index,
                    "request_value": request.request_value,
                    "channel_selector": request.channel_selector,
                }
                for request in self.dma_requests
            ],
        }


def family_patch_file_path(context: ExecutionContext, *, vendor: str, family: str) -> Path:
    """Resolve the family-level patch catalog path."""
    return context.patch_root / vendor / family / "family.json"


def patch_file_path(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> Path:
    """Resolve the patch path for one device."""
    return context.patch_root / vendor / family / "devices" / f"{device_name}.json"


# ---------------------------------------------------------------------------
# Board support package (add-board-support-package-emitter)
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class NamedPinPatch:
    """One named board pin (LED, BUTTON, debug-UART signal, ...)."""

    name: str  # canonical name, e.g. "LED_GREEN" / "BUTTON_USER" / "UART_DBG_TX"
    pin: str  # device pin label, e.g. "PA5" / "GP25"
    polarity: str = "active_high"  # "active_high" | "active_low"
    peripheral: str | None = None  # for debug peripheral signals
    signal: str | None = None  # "TX" | "RX" | "MOSI" | ...


@dataclass(frozen=True, slots=True)
class ExternalOscillatorPatch:
    """External oscillator wiring on the board (HSE, LSE, ...)."""

    kind: str  # "hse" | "lse" | "extal" | ...
    frequency_hz: int
    source: str = ""  # "st-link-mco" | "crystal" | ...


@dataclass(frozen=True, slots=True)
class BoardPatch:
    """One board overlay JSON document."""

    board_id: str
    device: str
    package: str
    summary: str = ""
    named_pins: tuple[NamedPinPatch, ...] = ()
    default_clock_profile: str = ""
    external_oscillators: tuple[ExternalOscillatorPatch, ...] = ()


def board_patch_dir(context: ExecutionContext, *, vendor: str, family: str) -> Path:
    return context.patch_root / vendor / family / "boards"


def _parse_named_pin_patch(payload: dict[str, object]) -> NamedPinPatch:
    return NamedPinPatch(
        name=str(payload["name"]),
        pin=str(payload["pin"]),
        polarity=str(payload.get("polarity", "active_high")),
        peripheral=str(payload["peripheral"]) if payload.get("peripheral") is not None else None,
        signal=str(payload["signal"]) if payload.get("signal") is not None else None,
    )


def _parse_external_oscillator_patch(payload: dict[str, object]) -> ExternalOscillatorPatch:
    return ExternalOscillatorPatch(
        kind=str(payload["kind"]),
        frequency_hz=int(payload["frequency_hz"]),  # type: ignore[arg-type]
        source=str(payload.get("source", "")),
    )


def _parse_board_patch(payload: dict[str, object]) -> BoardPatch:
    return BoardPatch(
        board_id=str(payload["board_id"]),
        device=str(payload["device"]),
        package=str(payload["package"]),
        summary=str(payload.get("summary", "")),
        named_pins=tuple(
            _parse_named_pin_patch(item)  # type: ignore[arg-type]
            for item in payload.get("named_pins", ())  # type: ignore[union-attr]
        ),
        default_clock_profile=str(payload.get("default_clock_profile", "")),
        external_oscillators=tuple(
            _parse_external_oscillator_patch(item)  # type: ignore[arg-type]
            for item in payload.get("external_oscillators", ())  # type: ignore[union-attr]
        ),
    )


def load_board_patches(
    context: ExecutionContext, *, vendor: str, family: str, device: str
) -> tuple[BoardPatch, ...]:
    """Load every board.json under ``patches/<vendor>/<family>/boards/`` whose
    ``device`` field matches the requested device.  Returns an empty tuple
    when the directory is missing or has no matching boards."""
    boards_dir = board_patch_dir(context, vendor=vendor, family=family)
    if not boards_dir.exists():
        return ()
    boards: list[BoardPatch] = []
    for path in sorted(boards_dir.glob("*.json")):
        payload = json.loads(path.read_text())
        board = _parse_board_patch(payload)  # type: ignore[arg-type]
        if board.device == device:
            boards.append(board)
    return tuple(boards)


def _parse_pin_signal(payload: dict[str, object]) -> PinSignalPatch:
    return PinSignalPatch(
        function=str(payload["function"]),
        peripheral=str(payload["peripheral"]) if payload.get("peripheral") is not None else None,
        signal=str(payload["signal"]) if payload.get("signal") is not None else None,
        af_number=int(payload["af_number"]) if payload.get("af_number") is not None else None,
    )


def _default_gpio_signal(*, port: str | None, number: int) -> PinSignalPatch | None:
    if port is None:
        return None
    return PinSignalPatch(
        function="gpio",
        peripheral=f"GPIO{port}",
        signal=f"IN{number}",
        af_number=None,
    )


def _parse_peripheral_patch(payload: dict[str, object]) -> PeripheralPatch:
    return PeripheralPatch(
        name=str(payload["name"]),
        rcc_enable_signal=(
            str(payload["rcc_enable_signal"])
            if payload.get("rcc_enable_signal") is not None
            else None
        ),
        rcc_reset_signal=(
            str(payload["rcc_reset_signal"])
            if payload.get("rcc_reset_signal") is not None
            else None
        ),
        ip_version=(str(payload["ip_version"]) if payload.get("ip_version") is not None else None),
    )


def _parse_package_patch(payload: dict[str, object]) -> PackagePatch:
    return PackagePatch(
        name=str(payload["name"]),
        pin_count=int(payload["pin_count"]),
    )


def _parse_pin_catalog_entry(payload: dict[str, object]) -> PinCatalogEntry:
    return PinCatalogEntry(
        name=str(payload["name"]),
        port=str(payload["port"]) if payload.get("port") is not None else None,
        number=int(payload["number"]),
        packages=tuple(str(package) for package in payload.get("packages", ())),
    )


def _parse_pin_signal_catalog_entry(payload: dict[str, object]) -> PinSignalCatalogEntry:
    return PinSignalCatalogEntry(
        signal_id=str(payload["signal_id"]),
        pin_name=str(payload["pin_name"]),
        signal=_parse_pin_signal(payload),
    )


def _parse_register_field_patch(payload: dict[str, object]) -> RegisterFieldPatch:
    return RegisterFieldPatch(
        peripheral=str(payload["peripheral"]),
        register_name=str(payload["register_name"]),
        name=str(payload["name"]),
        bit_offset=int(payload["bit_offset"]),
        bit_width=int(payload.get("bit_width", 1)),
        access=str(payload["access"]) if payload.get("access") is not None else None,
    )


def _parse_register_patch(payload: dict[str, object]) -> RegisterPatch:
    return RegisterPatch(
        peripheral=str(payload["peripheral"]),
        name=str(payload["name"]),
        offset_bytes=int(payload["offset_bytes"]),
        access=str(payload["access"]) if payload.get("access") is not None else None,
        size_bits=int(payload["size_bits"]) if payload.get("size_bits") is not None else None,
        base_address=(
            int(payload["base_address"]) if payload.get("base_address") is not None else None
        ),
    )


def _parse_dma_request_patch(payload: dict[str, object]) -> DmaRequestPatch:
    return DmaRequestPatch(
        controller=str(payload["controller"]),
        request_line=str(payload["request_line"]),
        peripheral=str(payload["peripheral"]) if payload.get("peripheral") is not None else None,
        signal=str(payload["signal"]) if payload.get("signal") is not None else None,
        channel_index=(
            int(payload["channel_index"]) if payload.get("channel_index") is not None else None
        ),
        request_value=(
            int(payload["request_value"]) if payload.get("request_value") is not None else None
        ),
        channel_selector=(
            int(payload["channel_selector"])
            if payload.get("channel_selector") is not None
            else None
        ),
    )


def _parse_dma_request_catalog_entry(payload: dict[str, object]) -> DmaRequestCatalogEntry:
    return DmaRequestCatalogEntry(
        request_id=str(payload["request_id"]),
        request=_parse_dma_request_patch(payload),
    )


def _parse_dma_controller_patch(payload: dict[str, object]) -> DmaControllerPatch:
    return DmaControllerPatch(
        controller=str(payload["controller"]),
        channel_count=(
            int(payload["channel_count"]) if payload.get("channel_count") is not None else None
        ),
        version=str(payload["version"]) if payload.get("version") is not None else None,
    )


def _parse_clock_node_patch(payload: dict[str, object]) -> ClockNodePatch:
    return ClockNodePatch(
        node_id=str(payload["node_id"]),
        kind=str(payload["kind"]),
        parent=str(payload["parent"]) if payload.get("parent") is not None else None,
        selector=str(payload["selector"]) if payload.get("selector") is not None else None,
    )


def _parse_clock_selector_patch(payload: dict[str, object]) -> ClockSelectorPatch:
    return ClockSelectorPatch(
        selector_id=str(payload["selector_id"]),
        parent_options=tuple(str(option) for option in payload.get("parent_options", ())),
        register_target=(
            str(payload["register_target"]) if payload.get("register_target") is not None else None
        ),
    )


def _parse_clock_gate_patch(payload: dict[str, object]) -> ClockGatePatch:
    return ClockGatePatch(
        gate_id=str(payload["gate_id"]),
        peripheral=str(payload["peripheral"]) if payload.get("peripheral") is not None else None,
        enable_signal=str(payload["enable_signal"]),
        parent_node=str(payload["parent_node"]) if payload.get("parent_node") is not None else None,
    )


def _parse_reset_patch(payload: dict[str, object]) -> ResetPatch:
    return ResetPatch(
        reset_id=str(payload["reset_id"]),
        peripheral=str(payload["peripheral"]) if payload.get("peripheral") is not None else None,
        reset_signal=str(payload["reset_signal"]),
        active_level=(
            str(payload["active_level"]) if payload.get("active_level") is not None else None
        ),
    )


def _parse_peripheral_clock_binding_patch(
    payload: dict[str, object],
) -> PeripheralClockBindingPatch:
    return PeripheralClockBindingPatch(
        peripheral=str(payload["peripheral"]),
        clock_gate_id=(
            str(payload["clock_gate_id"]) if payload.get("clock_gate_id") is not None else None
        ),
        reset_id=str(payload["reset_id"]) if payload.get("reset_id") is not None else None,
        selector_id=(
            str(payload["selector_id"]) if payload.get("selector_id") is not None else None
        ),
    )


def _parse_interrupt_patch(payload: dict[str, object]) -> InterruptPatch:
    return InterruptPatch(
        name=str(payload["name"]),
        line=int(payload["line"]),
        peripheral=str(payload["peripheral"]) if payload.get("peripheral") is not None else None,
        alias_names=tuple(str(name) for name in payload.get("alias_names", ())),
    )


def _parse_system_clock_profile_patch(payload: dict[str, object]) -> SystemClockProfilePatch:
    return SystemClockProfilePatch(
        profile_id=str(payload["profile_id"]),
        kind=str(payload["kind"]),
        source_kind=str(payload["source_kind"]),
        sysclk_hz=int(payload["sysclk_hz"]),
        hclk_hz=int(payload["hclk_hz"]) if payload.get("hclk_hz") is not None else None,
        apb1_hz=int(payload["apb1_hz"]) if payload.get("apb1_hz") is not None else None,
        apb2_hz=int(payload["apb2_hz"]) if payload.get("apb2_hz") is not None else None,
        pclk_hz=int(payload["pclk_hz"]) if payload.get("pclk_hz") is not None else None,
        source_hz=int(payload["source_hz"]) if payload.get("source_hz") is not None else None,
        ahb_prescaler=(
            int(payload["ahb_prescaler"]) if payload.get("ahb_prescaler") is not None else None
        ),
        apb1_prescaler=(
            int(payload["apb1_prescaler"]) if payload.get("apb1_prescaler") is not None else None
        ),
        apb2_prescaler=(
            int(payload["apb2_prescaler"]) if payload.get("apb2_prescaler") is not None else None
        ),
        oscillator_startup_cycles=(
            int(payload["oscillator_startup_cycles"])
            if payload.get("oscillator_startup_cycles") is not None
            else None
        ),
        mck_prescaler=(
            int(payload["mck_prescaler"]) if payload.get("mck_prescaler") is not None else None
        ),
        cpu_prescaler=(
            int(payload["cpu_prescaler"]) if payload.get("cpu_prescaler") is not None else None
        ),
        ipg_prescaler=(
            int(payload["ipg_prescaler"]) if payload.get("ipg_prescaler") is not None else None
        ),
        pll_m=int(payload["pll_m"]) if payload.get("pll_m") is not None else None,
        pll_n=int(payload["pll_n"]) if payload.get("pll_n") is not None else None,
        pll_p=int(payload["pll_p"]) if payload.get("pll_p") is not None else None,
        pll_q=int(payload["pll_q"]) if payload.get("pll_q") is not None else None,
        pll_r=int(payload["pll_r"]) if payload.get("pll_r") is not None else None,
        flash_latency=(
            int(payload["flash_latency"]) if payload.get("flash_latency") is not None else None
        ),
    )


def load_family_patch_catalog(
    context: ExecutionContext, *, vendor: str, family: str
) -> FamilyPatchCatalog:
    """Load the family patch catalog for the given vendor/family."""
    patch_path = family_patch_file_path(context, vendor=vendor, family=family)
    if not patch_path.exists():
        raise StageExecutionError(f"Missing family patch catalog: {patch_path}")

    payload = json.loads(patch_path.read_text())
    return FamilyPatchCatalog(
        patch_id=payload["patch_id"],
        packages=tuple(_parse_package_patch(item) for item in payload.get("packages", ())),
        pins=tuple(_parse_pin_catalog_entry(item) for item in payload.get("pins", ())),
        peripherals=tuple(_parse_peripheral_patch(item) for item in payload.get("peripherals", ())),
        pin_signals=tuple(
            _parse_pin_signal_catalog_entry(item) for item in payload.get("pin_signals", ())
        ),
        registers=tuple(_parse_register_patch(item) for item in payload.get("registers", ())),
        register_fields=tuple(
            _parse_register_field_patch(item) for item in payload.get("register_fields", ())
        ),
        clock_nodes=tuple(_parse_clock_node_patch(item) for item in payload.get("clock_nodes", ())),
        clock_selectors=tuple(
            _parse_clock_selector_patch(item) for item in payload.get("clock_selectors", ())
        ),
        clock_gates=tuple(_parse_clock_gate_patch(item) for item in payload.get("clock_gates", ())),
        resets=tuple(_parse_reset_patch(item) for item in payload.get("resets", ())),
        peripheral_clock_bindings=tuple(
            _parse_peripheral_clock_binding_patch(item)
            for item in payload.get("peripheral_clock_bindings", ())
        ),
        system_clock_profiles=tuple(
            _parse_system_clock_profile_patch(item)
            for item in payload.get("system_clock_profiles", ())
        ),
        dma_controllers=tuple(
            _parse_dma_controller_patch(item) for item in payload.get("dma_controllers", ())
        ),
        dma_requests=tuple(
            _parse_dma_request_catalog_entry(item) for item in payload.get("dma_requests", ())
        ),
        readme_caveat=_extract_readme_caveat(payload),
        multicore_topology=_parse_multicore_topology_patch(payload.get("multicore_topology")),
        usb_controllers=tuple(
            entry
            for entry in (
                _parse_usb_controller_patch(item) for item in payload.get("usb_controllers", ())
            )
            if entry is not None
        ),
        # Espressif hardware-feature blocks (added by
        # ``fill-espressif-semantic-gaps``).
        uart_peripherals=tuple(
            entry
            for entry in (
                _parse_uart_peripheral_patch(item) for item in payload.get("uart_peripherals", ())
            )
            if entry is not None
        ),
        spi_peripherals=tuple(
            entry
            for entry in (
                _parse_spi_peripheral_patch(item) for item in payload.get("spi_peripherals", ())
            )
            if entry is not None
        ),
        adc_units=tuple(
            entry
            for entry in (_parse_adc_unit_patch(item) for item in payload.get("adc_units", ()))
            if entry is not None
        ),
        timer_units=tuple(
            entry
            for entry in (_parse_timer_unit_patch(item) for item in payload.get("timer_units", ()))
            if entry is not None
        ),
        ledc=_parse_ledc_patch(payload.get("ledc")),
        dma_channels=tuple(
            entry
            for entry in (
                _parse_dma_channel_patch(item) for item in payload.get("dma_channels", ())
            )
            if entry is not None
        ),
    )


def _opt_int(payload: dict, key: str) -> int | None:
    value = payload.get(key)
    return value if isinstance(value, int) else None


def _flag(payload: dict, key: str) -> bool:
    return bool(payload.get(key, False))


def _parse_uart_peripheral_patch(payload: object) -> UartPeripheralPatch | None:
    if not isinstance(payload, dict):
        return None
    pid = payload.get("peripheral_id")
    base = payload.get("base_address")
    fifo = payload.get("fifo_depth")
    if not isinstance(pid, str) or not isinstance(base, int) or not isinstance(fifo, int):
        return None
    return UartPeripheralPatch(
        peripheral_id=pid,
        base_address=base,
        fifo_depth=fifo,
        tx_signal_idx=_opt_int(payload, "tx_signal_idx"),
        rx_signal_idx=_opt_int(payload, "rx_signal_idx"),
        supports_dma=_flag(payload, "supports_dma"),
    )


def _parse_spi_peripheral_patch(payload: object) -> SpiPeripheralPatch | None:
    if not isinstance(payload, dict):
        return None
    pid = payload.get("peripheral_id")
    base = payload.get("base_address")
    max_clock = payload.get("max_clock_hz")
    if not isinstance(pid, str) or not isinstance(base, int) or not isinstance(max_clock, int):
        return None
    return SpiPeripheralPatch(
        peripheral_id=pid,
        base_address=base,
        max_clock_hz=max_clock,
        mosi_out_signal=_opt_int(payload, "mosi_out_signal"),
        miso_in_signal=_opt_int(payload, "miso_in_signal"),
        clk_out_signal=_opt_int(payload, "clk_out_signal"),
        cs_out_signal=_opt_int(payload, "cs_out_signal"),
        has_iomux_fast_path=_flag(payload, "has_iomux_fast_path"),
        iomux_mosi_pin=_opt_int(payload, "iomux_mosi_pin"),
        iomux_miso_pin=_opt_int(payload, "iomux_miso_pin"),
        iomux_clk_pin=_opt_int(payload, "iomux_clk_pin"),
        iomux_cs_pin=_opt_int(payload, "iomux_cs_pin"),
        supports_dma=_flag(payload, "supports_dma"),
    )


def _parse_adc_unit_patch(payload: object) -> AdcUnitPatch | None:
    if not isinstance(payload, dict):
        return None
    uid = payload.get("unit_id")
    cc = payload.get("channel_count")
    rb = payload.get("resolution_bits")
    if not isinstance(uid, str) or not isinstance(cc, int) or not isinstance(rb, int):
        return None
    pins = payload.get("channel_pins") or ()
    pins_tuple = tuple(p for p in pins if isinstance(p, int)) if isinstance(pins, list) else ()
    return AdcUnitPatch(
        unit_id=uid,
        channel_count=cc,
        resolution_bits=rb,
        conflicts_with_wifi=_flag(payload, "conflicts_with_wifi"),
        channel_pins=pins_tuple,
    )


def _parse_timer_unit_patch(payload: object) -> TimerUnitPatch | None:
    if not isinstance(payload, dict):
        return None
    tid = payload.get("timer_id")
    gi = payload.get("group_idx")
    ti = payload.get("timer_idx")
    base = payload.get("base_address")
    bits = payload.get("bits")
    if not all(isinstance(v, (str, int)) for v in (tid, gi, ti, base, bits)):
        return None
    if not isinstance(tid, str):
        return None
    sources = payload.get("clock_sources") or ()
    sources_tuple = (
        tuple(s for s in sources if isinstance(s, str)) if isinstance(sources, list) else ()
    )
    return TimerUnitPatch(
        timer_id=tid,
        group_idx=int(gi),  # type: ignore[arg-type]
        timer_idx=int(ti),  # type: ignore[arg-type]
        base_address=int(base),  # type: ignore[arg-type]
        bits=int(bits),  # type: ignore[arg-type]
        clock_sources=sources_tuple,
    )


def _parse_ledc_patch(payload: object) -> LedcPatch | None:
    if not isinstance(payload, dict):
        return None
    base = payload.get("base_address")
    cc = payload.get("channel_count")
    rb = payload.get("resolution_bits")
    if not isinstance(base, int) or not isinstance(cc, int) or not isinstance(rb, int):
        return None
    sources = payload.get("clock_sources") or ()
    out_signals = payload.get("output_signals") or ()
    return LedcPatch(
        base_address=base,
        channel_count=cc,
        resolution_bits=rb,
        clock_sources=tuple(s for s in sources if isinstance(s, str))
        if isinstance(sources, list)
        else (),
        output_signals=tuple(s for s in out_signals if isinstance(s, int))
        if isinstance(out_signals, list)
        else (),
    )


def _parse_dma_channel_patch(payload: object) -> DmaChannelPatch | None:
    if not isinstance(payload, dict):
        return None
    cid = payload.get("channel_id")
    ci = payload.get("channel_index")
    is_gdma = payload.get("is_gdma")
    if not isinstance(cid, str) or not isinstance(ci, int) or not isinstance(is_gdma, bool):
        return None
    requests = payload.get("peripheral_requests") or {}
    requests_tuple: tuple[tuple[str, int], ...] = ()
    if isinstance(requests, dict):
        requests_tuple = tuple(
            (k, v) for k, v in requests.items() if isinstance(k, str) and isinstance(v, int)
        )
    return DmaChannelPatch(
        channel_id=cid,
        channel_index=ci,
        is_gdma=is_gdma,
        max_transfer_bytes=payload.get("max_transfer_bytes", 0)
        if isinstance(payload.get("max_transfer_bytes", 0), int)
        else 0,
        peripheral_requests=requests_tuple,
    )


def _parse_usb_controller_patch(payload: object) -> UsbControllerPatch | None:
    """Parse one ``family.json::usb_controllers[*]`` entry."""
    if not isinstance(payload, dict):
        return None
    controller_id = payload.get("controller_id")
    base_address = payload.get("base_address")
    endpoint_count = payload.get("endpoint_count")
    if (
        not isinstance(controller_id, str)
        or not isinstance(base_address, int)
        or not isinstance(endpoint_count, int)
    ):
        return None

    def _opt_int(key: str) -> int | None:
        value = payload.get(key)
        return value if isinstance(value, int) else None

    def _opt_str(key: str) -> str | None:
        value = payload.get(key)
        return value if isinstance(value, str) else None

    def _flag(key: str) -> bool:
        return bool(payload.get(key, False))

    return UsbControllerPatch(
        controller_id=controller_id,
        base_address=base_address,
        endpoint_count=endpoint_count,
        supports_high_speed=_flag("supports_high_speed"),
        supports_host_mode=_flag("supports_host_mode"),
        supports_dma=_flag("supports_dma"),
        crystalless=_flag("crystalless"),
        dpram_base_address=_opt_int("dpram_base_address"),
        dpram_size_bytes=_opt_int("dpram_size_bytes"),
        dma_channel_count=payload.get("dma_channel_count", 0)
        if isinstance(payload.get("dma_channel_count", 0), int)
        else 0,
        dm_pin=_opt_str("dm_pin"),
        dp_pin=_opt_str("dp_pin"),
        clock_source=_opt_str("clock_source"),
    )


def _parse_multicore_topology_patch(
    payload: object,
) -> MulticoreTopologyPatch | None:
    """Parse `family.json::multicore_topology` block when present."""
    if not isinstance(payload, dict):
        return None
    topology_value = payload.get("topology")
    core_count = payload.get("core_count")
    if not isinstance(topology_value, str) or not isinstance(core_count, int):
        return None
    app_cpu_payload = payload.get("app_cpu_control_plane")
    app_cpu = None
    if isinstance(app_cpu_payload, dict):
        register_value = app_cpu_payload.get("register")
        operation_value = app_cpu_payload.get("operation")
        start_vector_value = app_cpu_payload.get("start_vector_symbol")
        register_secondary_value = app_cpu_payload.get("register_secondary")
        if (
            isinstance(register_value, str)
            and isinstance(operation_value, str)
            and isinstance(start_vector_value, str)
        ):
            app_cpu = AppCpuControlPlanePatch(
                register=register_value,
                operation=operation_value,
                start_vector_symbol=start_vector_value,
                register_secondary=(
                    register_secondary_value if isinstance(register_secondary_value, str) else None
                ),
            )
    return MulticoreTopologyPatch(
        topology=topology_value,
        core_count=core_count,
        app_cpu_control_plane=app_cpu,
    )


def _extract_readme_caveat(payload: dict[str, object]) -> str | None:
    """Pull `__source_notes.__readme_caveat` from a family.json payload.

    Returns ``None`` when the field is absent, malformed, or empty.
    Used by the auto-generated alloy-devices README to surface known coverage
    limitations per family.  See ``add-publication-scale-features``.
    """
    notes = payload.get("__source_notes")
    if not isinstance(notes, dict):
        return None
    caveat = notes.get("__readme_caveat")
    if not isinstance(caveat, str):
        return None
    text = caveat.strip()
    return text or None


def _resolve_peripheral_patch(
    *,
    item: object,
    catalog: dict[str, PeripheralPatch],
) -> PeripheralPatch:
    if isinstance(item, str):
        if item not in catalog:
            raise StageExecutionError(f"Unknown peripheral reference in patch overlay: {item}")
        return catalog[item]

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid peripheral patch entry: {item!r}")

    name = str(item["name"])
    base = catalog.get(name)
    if base is None:
        return _parse_peripheral_patch(item)

    return PeripheralPatch(
        name=name,
        rcc_enable_signal=(
            str(item["rcc_enable_signal"])
            if item.get("rcc_enable_signal") is not None
            else base.rcc_enable_signal
        ),
        rcc_reset_signal=(
            str(item["rcc_reset_signal"])
            if item.get("rcc_reset_signal") is not None
            else base.rcc_reset_signal
        ),
        ip_version=(
            str(item["ip_version"]) if item.get("ip_version") is not None else base.ip_version
        ),
    )


def _resolve_package_patch(
    *,
    package_name: str,
    catalog: dict[str, PackagePatch],
) -> PackagePatch:
    package = catalog.get(package_name)
    if package is None:
        raise StageExecutionError(f"Unknown package reference in patch overlay: {package_name}")
    return package


def _normalize_alternate_signal_entries(
    *,
    payload: dict[str, object],
    port: str | None,
    number: int,
    pin_name: str,
    signal_catalog: dict[str, PinSignalCatalogEntry] | None = None,
) -> tuple[PinSignalPatch, ...]:
    signal_refs = payload.get("signal_refs", ())
    if not isinstance(signal_refs, list | tuple):
        raise StageExecutionError(f"Invalid pin signal reference list for {payload['name']!r}.")

    alternate_signal_entries = payload.get("alternate_signals")
    if alternate_signal_entries is None:
        alternate_signal_entries = payload.get("signals", ())
    if not isinstance(alternate_signal_entries, list | tuple):
        raise StageExecutionError(f"Invalid pin signal list for {payload['name']!r}.")

    default_gpio = _default_gpio_signal(port=port, number=number)
    alternate_signals: list[PinSignalPatch] = []
    for signal_ref in signal_refs:
        if signal_catalog is None:
            raise StageExecutionError(
                f"Pin signal reference requires a family catalog: {signal_ref!r}"
            )
        if not isinstance(signal_ref, str):
            raise StageExecutionError(
                f"Invalid pin signal reference for {payload['name']!r}: {signal_ref!r}"
            )
        catalog_entry = signal_catalog.get(signal_ref)
        if catalog_entry is None:
            raise StageExecutionError(f"Unknown pin signal reference: {signal_ref}")
        if catalog_entry.pin_name != pin_name:
            raise StageExecutionError(
                f"Pin signal reference {signal_ref!r} targets {catalog_entry.pin_name}, "
                f"not {pin_name}."
            )
        if default_gpio is not None and catalog_entry.signal == default_gpio:
            continue
        alternate_signals.append(catalog_entry.signal)

    for entry in alternate_signal_entries:
        if not isinstance(entry, dict):
            raise StageExecutionError(
                f"Invalid pin signal entry for {payload['name']!r}: {entry!r}"
            )
        signal = _parse_pin_signal(entry)
        if default_gpio is not None and signal == default_gpio:
            continue
        alternate_signals.append(signal)
    return tuple(alternate_signals)


def _resolve_pin_patch(
    *,
    payload: dict[str, object],
    package_name: str,
    catalog: dict[str, PinCatalogEntry],
    signal_catalog: dict[str, PinSignalCatalogEntry],
) -> PinPatch:
    pin_name = str(payload["name"])
    base_entry = catalog.get(pin_name)
    if base_entry is None:
        raise StageExecutionError(f"Unknown pin reference in patch overlay: {pin_name}")
    if base_entry.packages and package_name not in base_entry.packages:
        raise StageExecutionError(
            f"Pin {pin_name} is not declared for package {package_name} in the family catalog."
        )

    port = str(payload["port"]) if payload.get("port") is not None else base_entry.port
    number = int(payload["number"]) if payload.get("number") is not None else base_entry.number
    alternate_signals = _normalize_alternate_signal_entries(
        payload=payload,
        port=port,
        number=number,
        pin_name=pin_name,
        signal_catalog=signal_catalog,
    )
    default_signal = _default_gpio_signal(port=port, number=number)
    signals = alternate_signals if default_signal is None else (default_signal, *alternate_signals)
    return PinPatch(
        name=pin_name,
        port=port,
        number=number,
        signals=signals,
    )


def _resolve_pin_count(
    *,
    payload: dict[str, object],
    package: PackagePatch,
) -> int:
    if "pin_count" not in payload:
        return package.pin_count

    declared_pin_count = int(payload["pin_count"])
    if declared_pin_count != package.pin_count:
        raise StageExecutionError(
            f"Pin count mismatch for package {package.name}: "
            f"overlay={declared_pin_count}, catalog={package.pin_count}."
        )
    return declared_pin_count


def _resolve_dma_request(
    *,
    item: object,
    catalog: dict[str, DmaRequestCatalogEntry],
) -> DmaRequestPatch:
    if isinstance(item, str):
        catalog_entry = catalog.get(item)
        if catalog_entry is None:
            raise StageExecutionError(f"Unknown DMA request reference in patch overlay: {item}")
        return catalog_entry.request

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid DMA request patch entry: {item!r}")
    return _parse_dma_request_patch(item)


def _resolve_dma_controller(
    *,
    item: object,
    catalog: dict[str, DmaControllerPatch],
) -> DmaControllerPatch:
    if isinstance(item, str):
        controller = catalog.get(item)
        if controller is None:
            raise StageExecutionError(f"Unknown DMA controller reference in patch overlay: {item}")
        return controller

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid DMA controller patch entry: {item!r}")

    controller_name = str(item["controller"])
    base = catalog.get(controller_name)
    if base is None:
        return _parse_dma_controller_patch(item)

    return DmaControllerPatch(
        controller=controller_name,
        channel_count=(
            int(item["channel_count"])
            if item.get("channel_count") is not None
            else base.channel_count
        ),
        version=str(item["version"]) if item.get("version") is not None else base.version,
    )


def _resolve_clock_node(
    *,
    item: object,
    catalog: dict[str, ClockNodePatch],
) -> ClockNodePatch:
    if isinstance(item, str):
        node = catalog.get(item)
        if node is None:
            raise StageExecutionError(f"Unknown clock node reference in patch overlay: {item}")
        return node

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid clock node patch entry: {item!r}")

    node_id = str(item["node_id"])
    base = catalog.get(node_id)
    if base is None:
        return _parse_clock_node_patch(item)

    return ClockNodePatch(
        node_id=node_id,
        kind=str(item["kind"]) if item.get("kind") is not None else base.kind,
        parent=str(item["parent"]) if item.get("parent") is not None else base.parent,
        selector=str(item["selector"]) if item.get("selector") is not None else base.selector,
    )


def _resolve_clock_selector(
    *,
    item: object,
    catalog: dict[str, ClockSelectorPatch],
) -> ClockSelectorPatch:
    if isinstance(item, str):
        selector = catalog.get(item)
        if selector is None:
            raise StageExecutionError(f"Unknown clock selector reference in patch overlay: {item}")
        return selector

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid clock selector patch entry: {item!r}")

    selector_id = str(item["selector_id"])
    base = catalog.get(selector_id)
    if base is None:
        return _parse_clock_selector_patch(item)

    return ClockSelectorPatch(
        selector_id=selector_id,
        parent_options=(
            tuple(str(option) for option in item["parent_options"])
            if item.get("parent_options") is not None
            else base.parent_options
        ),
        register_target=(
            str(item["register_target"])
            if item.get("register_target") is not None
            else base.register_target
        ),
    )


def _resolve_clock_gate(
    *,
    item: object,
    catalog: dict[str, ClockGatePatch],
) -> ClockGatePatch:
    if isinstance(item, str):
        gate = catalog.get(item)
        if gate is None:
            raise StageExecutionError(f"Unknown clock gate reference in patch overlay: {item}")
        return gate

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid clock gate patch entry: {item!r}")

    gate_id = str(item["gate_id"])
    base = catalog.get(gate_id)
    if base is None:
        return _parse_clock_gate_patch(item)

    return ClockGatePatch(
        gate_id=gate_id,
        peripheral=(
            str(item["peripheral"]) if item.get("peripheral") is not None else base.peripheral
        ),
        enable_signal=(
            str(item["enable_signal"])
            if item.get("enable_signal") is not None
            else base.enable_signal
        ),
        parent_node=(
            str(item["parent_node"]) if item.get("parent_node") is not None else base.parent_node
        ),
    )


def _resolve_reset(
    *,
    item: object,
    catalog: dict[str, ResetPatch],
) -> ResetPatch:
    if isinstance(item, str):
        reset = catalog.get(item)
        if reset is None:
            raise StageExecutionError(f"Unknown reset reference in patch overlay: {item}")
        return reset

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid reset patch entry: {item!r}")

    reset_id = str(item["reset_id"])
    base = catalog.get(reset_id)
    if base is None:
        return _parse_reset_patch(item)

    return ResetPatch(
        reset_id=reset_id,
        peripheral=(
            str(item["peripheral"]) if item.get("peripheral") is not None else base.peripheral
        ),
        reset_signal=(
            str(item["reset_signal"]) if item.get("reset_signal") is not None else base.reset_signal
        ),
        active_level=(
            str(item["active_level"]) if item.get("active_level") is not None else base.active_level
        ),
    )


def _resolve_peripheral_clock_binding(
    *,
    item: object,
    catalog: dict[str, PeripheralClockBindingPatch],
) -> PeripheralClockBindingPatch:
    if isinstance(item, str):
        binding = catalog.get(item)
        if binding is None:
            raise StageExecutionError(
                f"Unknown peripheral clock binding reference in patch overlay: {item}"
            )
        return binding

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid peripheral clock binding patch entry: {item!r}")

    peripheral = str(item["peripheral"])
    base = catalog.get(peripheral)
    if base is None:
        return _parse_peripheral_clock_binding_patch(item)

    return PeripheralClockBindingPatch(
        peripheral=peripheral,
        clock_gate_id=(
            str(item["clock_gate_id"])
            if item.get("clock_gate_id") is not None
            else base.clock_gate_id
        ),
        reset_id=str(item["reset_id"]) if item.get("reset_id") is not None else base.reset_id,
        selector_id=(
            str(item["selector_id"]) if item.get("selector_id") is not None else base.selector_id
        ),
    )


def _parse_pin_patch(payload: dict[str, object]) -> PinPatch:
    port = str(payload["port"]) if payload.get("port") is not None else None
    number = int(payload["number"])
    alternate_signals = _normalize_alternate_signal_entries(
        payload=payload,
        port=port,
        number=number,
        pin_name=str(payload["name"]),
    )
    default_signal = _default_gpio_signal(port=port, number=number)
    signals = alternate_signals if default_signal is None else (default_signal, *alternate_signals)
    return PinPatch(
        name=str(payload["name"]),
        port=port,
        number=number,
        signals=signals,
    )


def load_device_patch(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> DevicePatch:
    """Load one device patch document."""
    patch_path = patch_file_path(context, device_name, vendor=vendor, family=family)
    if not patch_path.exists():
        raise StageExecutionError(f"Missing patch document: {patch_path}")

    family_catalog = load_family_patch_catalog(context, vendor=vendor, family=family)
    package_catalog_by_name = {package.name: package for package in family_catalog.packages}
    pin_catalog_by_name = {pin.name: pin for pin in family_catalog.pins}
    signal_catalog_by_id = {signal.signal_id: signal for signal in family_catalog.pin_signals}
    clock_node_catalog_by_id = {node.node_id: node for node in family_catalog.clock_nodes}
    clock_selector_catalog_by_id = {
        selector.selector_id: selector for selector in family_catalog.clock_selectors
    }
    clock_gate_catalog_by_id = {gate.gate_id: gate for gate in family_catalog.clock_gates}
    reset_catalog_by_id = {reset.reset_id: reset for reset in family_catalog.resets}
    peripheral_clock_binding_catalog_by_peripheral = {
        binding.peripheral: binding for binding in family_catalog.peripheral_clock_bindings
    }
    dma_controller_catalog_by_name = {
        controller.controller: controller for controller in family_catalog.dma_controllers
    }
    dma_catalog_by_id = {request.request_id: request for request in family_catalog.dma_requests}
    catalog_by_name = {peripheral.name: peripheral for peripheral in family_catalog.peripherals}
    register_field_catalog_by_key = {
        (field.peripheral, field.register_name, field.name): field
        for field in family_catalog.register_fields
    }
    register_catalog_by_key = {
        (register.peripheral, register.name): register for register in family_catalog.registers
    }
    payload = json.loads(patch_path.read_text())
    package = _resolve_package_patch(
        package_name=payload["package"],
        catalog=package_catalog_by_name,
    )
    return DevicePatch(
        patch_id=payload["patch_id"],
        family_patch_id=family_catalog.patch_id,
        device=payload["device"],
        svd_file=str(payload["svd_file"]) if payload.get("svd_file") is not None else None,
        pin_data_file=(
            str(payload["pin_data_file"]) if payload.get("pin_data_file") is not None else None
        ),
        package=package.name,
        pin_count=_resolve_pin_count(payload=payload, package=package),
        core=payload["core"],
        summary=payload["summary"],
        memories=tuple(
            MemoryPatch(
                name=item["name"],
                kind=item["kind"],
                base_address=item["base_address"],
                size_bytes=item["size_bytes"],
                access=item["access"],
                address_space=item.get("address_space"),
            )
            for item in payload.get("memories", ())
        ),
        peripherals=tuple(
            {
                peripheral.name: peripheral
                for peripheral in (
                    *family_catalog.peripherals,
                    *(
                        _resolve_peripheral_patch(item=item, catalog=catalog_by_name)
                        for item in payload.get("peripherals", ())
                    ),
                )
            }.values()
        ),
        registers=tuple(
            {
                (register.peripheral, register.name): register
                for register in (
                    *family_catalog.registers,
                    *(
                        register_catalog_by_key.get(
                            (str(item["peripheral"]), str(item["name"])),
                            _parse_register_patch(item),
                        )
                        for item in payload.get("registers", ())
                    ),
                )
            }.values()
        ),
        register_fields=tuple(
            {
                (field.peripheral, field.register_name, field.name): field
                for field in (
                    *family_catalog.register_fields,
                    *(
                        register_field_catalog_by_key.get(
                            (
                                str(item["peripheral"]),
                                str(item["register_name"]),
                                str(item["name"]),
                            ),
                            _parse_register_field_patch(item),
                        )
                        for item in payload.get("register_fields", ())
                    ),
                )
            }.values()
        ),
        pins=tuple(
            (
                _resolve_pin_patch(
                    payload=item,
                    package_name=package.name,
                    catalog=pin_catalog_by_name,
                    signal_catalog=signal_catalog_by_id,
                )
                if "port" not in item or "number" not in item
                else _parse_pin_patch(item)
            )
            for item in payload.get("pins", ())
        ),
        clock_nodes=tuple(
            {
                node.node_id: node
                for node in (
                    *family_catalog.clock_nodes,
                    *(
                        _resolve_clock_node(item=item, catalog=clock_node_catalog_by_id)
                        for item in payload.get("clock_nodes", payload.get("clock_node_refs", ()))
                    ),
                )
            }.values()
        ),
        clock_selectors=tuple(
            {
                selector.selector_id: selector
                for selector in (
                    *family_catalog.clock_selectors,
                    *(
                        _resolve_clock_selector(
                            item=item,
                            catalog=clock_selector_catalog_by_id,
                        )
                        for item in payload.get(
                            "clock_selectors",
                            payload.get("clock_selector_refs", ()),
                        )
                    ),
                )
            }.values()
        ),
        clock_gates=tuple(
            {
                gate.gate_id: gate
                for gate in (
                    *family_catalog.clock_gates,
                    *(
                        _resolve_clock_gate(item=item, catalog=clock_gate_catalog_by_id)
                        for item in payload.get("clock_gates", payload.get("clock_gate_refs", ()))
                    ),
                )
            }.values()
        ),
        resets=tuple(
            {
                reset.reset_id: reset
                for reset in (
                    *family_catalog.resets,
                    *(
                        _resolve_reset(item=item, catalog=reset_catalog_by_id)
                        for item in payload.get("resets", payload.get("reset_refs", ()))
                    ),
                )
            }.values()
        ),
        peripheral_clock_bindings=tuple(
            {
                binding.peripheral: binding
                for binding in (
                    *family_catalog.peripheral_clock_bindings,
                    *(
                        _resolve_peripheral_clock_binding(
                            item=item,
                            catalog=peripheral_clock_binding_catalog_by_peripheral,
                        )
                        for item in payload.get(
                            "peripheral_clock_bindings",
                            payload.get("peripheral_clock_binding_refs", ()),
                        )
                    ),
                )
            }.values()
        ),
        interrupts=tuple(_parse_interrupt_patch(item) for item in payload.get("interrupts", ())),
        system_clock_profiles=tuple(
            {
                profile.profile_id: profile
                for profile in (
                    *family_catalog.system_clock_profiles,
                    *(
                        _parse_system_clock_profile_patch(item)
                        for item in payload.get("system_clock_profiles", ())
                    ),
                )
            }.values()
        ),
        dma_controllers=tuple(
            {
                controller.controller: controller
                for controller in (
                    *family_catalog.dma_controllers,
                    *(
                        _resolve_dma_controller(
                            item=item,
                            catalog=dma_controller_catalog_by_name,
                        )
                        for item in payload.get(
                            "dma_controllers",
                            payload.get("dma_controller_refs", ()),
                        )
                    ),
                )
            }.values()
        ),
        dma_requests=tuple(
            _resolve_dma_request(
                item=item,
                catalog=dma_catalog_by_id,
            )
            for item in payload.get("dma_requests", payload.get("dma_request_refs", ()))
        ),
        adc_internal_channels=tuple(
            _parse_adc_internal_channel_patch(item)
            for item in payload.get("adc_internal_channels", ())
        ),
        adc_calibration_data_points=tuple(
            _parse_adc_calibration_data_point_patch(item)
            for item in payload.get("adc_calibration_data_points", ())
        ),
        adc_calibration_context=(
            _parse_adc_calibration_context_patch(payload["adc_calibration_context"])
            if payload.get("adc_calibration_context") is not None
            else None
        ),
        adc_resolution_options=tuple(
            _parse_adc_resolution_option_patch(item)
            for item in payload.get("adc_resolution_options", ())
        ),
        adc_sample_time_options=tuple(
            _parse_adc_sample_time_option_patch(item)
            for item in payload.get("adc_sample_time_options", ())
        ),
        adc_oversampling_options=tuple(
            _parse_adc_oversampling_option_patch(item)
            for item in payload.get("adc_oversampling_options", ())
        ),
        adc_external_triggers=tuple(
            _parse_adc_external_trigger_patch(item)
            for item in payload.get("adc_external_triggers", ())
        ),
        adc_max_clock_hz=int(payload.get("adc_max_clock_hz", 0) or 0),
        uart_baud_clock_sources=tuple(
            _parse_uart_baud_clock_source_patch(item)
            for item in payload.get("uart_baud_clock_sources", ())
        ),
        uart_baud_oversampling_options=tuple(
            _parse_uart_baud_oversampling_option_patch(item)
            for item in payload.get("uart_baud_oversampling_options", ())
        ),
        uart_fifo_trigger_options=tuple(
            _parse_uart_fifo_trigger_option_patch(item)
            for item in payload.get("uart_fifo_trigger_options", ())
        ),
        uart_data_bits_options=tuple(
            _parse_uart_data_bits_option_patch(item)
            for item in payload.get("uart_data_bits_options", ())
        ),
        uart_parity_options=tuple(
            _parse_uart_parity_option_patch(item) for item in payload.get("uart_parity_options", ())
        ),
        uart_stop_bits_options=tuple(
            _parse_uart_stop_bits_option_patch(item)
            for item in payload.get("uart_stop_bits_options", ())
        ),
        uart_mode_flags=tuple(
            _parse_uart_mode_flags_patch(item) for item in payload.get("uart_mode_flags", ())
        ),
        uart_max_baud_hz=int(payload.get("uart_max_baud_hz", 0) or 0),
        spi_baud_prescaler_options=tuple(
            _parse_spi_baud_prescaler_option_patch(item)
            for item in payload.get("spi_baud_prescaler_options", ())
        ),
        spi_frame_size_options=tuple(
            _parse_spi_frame_size_option_patch(item)
            for item in payload.get("spi_frame_size_options", ())
        ),
        spi_fifo_threshold_options=tuple(
            _parse_spi_fifo_threshold_option_patch(item)
            for item in payload.get("spi_fifo_threshold_options", ())
        ),
        spi_mode_flags=tuple(
            _parse_spi_mode_flags_patch(item) for item in payload.get("spi_mode_flags", ())
        ),
        peripheral_max_clock_hz=tuple(
            _parse_peripheral_max_clock_patch(item)
            for item in payload.get("peripheral_max_clock_hz", ())
        ),
        timer_prescaler_options=tuple(
            _parse_timer_prescaler_option_patch(item)
            for item in payload.get("timer_prescaler_options", ())
        ),
        timer_trigger_sources=tuple(
            _parse_timer_trigger_source_patch(item)
            for item in payload.get("timer_trigger_sources", ())
        ),
        timer_master_outputs=tuple(
            _parse_timer_master_output_patch(item)
            for item in payload.get("timer_master_outputs", ())
        ),
        timer_mode_flags=tuple(
            _parse_timer_mode_flags_patch(item) for item in payload.get("timer_mode_flags", ())
        ),
        i2c_speed_options=tuple(
            _parse_i2c_speed_option_patch(item) for item in payload.get("i2c_speed_options", ())
        ),
        i2c_timing_presets=tuple(
            _parse_i2c_timing_preset_patch(item) for item in payload.get("i2c_timing_presets", ())
        ),
        i2c_mode_flags=tuple(
            _parse_i2c_mode_flags_patch(item) for item in payload.get("i2c_mode_flags", ())
        ),
        pwm_deadtime_options=tuple(
            _parse_pwm_deadtime_option_patch(item)
            for item in payload.get("pwm_deadtime_options", ())
        ),
        pwm_alignment_options=tuple(
            _parse_pwm_alignment_option_patch(item)
            for item in payload.get("pwm_alignment_options", ())
        ),
        pwm_break_inputs=tuple(
            _parse_pwm_break_input_patch(item) for item in payload.get("pwm_break_inputs", ())
        ),
        pwm_mode_flags=tuple(
            _parse_pwm_mode_flags_patch(item) for item in payload.get("pwm_mode_flags", ())
        ),
    )


def _parse_i2c_speed_option_patch(payload: dict[str, object]) -> I2cSpeedOptionPatch:
    return I2cSpeedOptionPatch(
        peripheral=str(payload["peripheral"]),
        speed_hz=int(payload["speed_hz"]),  # type: ignore[arg-type]
        mode=str(payload.get("mode", "standard")),
    )


def _parse_i2c_timing_preset_patch(payload: dict[str, object]) -> I2cTimingPresetPatch:
    return I2cTimingPresetPatch(
        peripheral=str(payload["peripheral"]),
        speed_hz=int(payload["speed_hz"]),  # type: ignore[arg-type]
        source_clock_hz=int(payload["source_clock_hz"]),  # type: ignore[arg-type]
        timingr_value=int(payload["timingr_value"]),  # type: ignore[arg-type]
    )


def _parse_i2c_mode_flags_patch(payload: dict[str, object]) -> I2cModeFlagsPatch:
    return I2cModeFlagsPatch(
        peripheral=str(payload["peripheral"]),
        supports_smbus=bool(payload.get("supports_smbus", False)),
        supports_pmbus=bool(payload.get("supports_pmbus", False)),
        supports_dma=bool(payload.get("supports_dma", False)),
        supports_slave=bool(payload.get("supports_slave", True)),
        supports_dual_address=bool(payload.get("supports_dual_address", False)),
        supports_general_call=bool(payload.get("supports_general_call", False)),
        supports_7bit_addressing=bool(payload.get("supports_7bit_addressing", True)),
        supports_10bit_addressing=bool(payload.get("supports_10bit_addressing", False)),
    )


def _parse_pwm_deadtime_option_patch(payload: dict[str, object]) -> PwmDeadtimeOptionPatch:
    return PwmDeadtimeOptionPatch(
        peripheral=str(payload["peripheral"]),
        prescaler_field_value=int(payload["prescaler_field_value"]),  # type: ignore[arg-type]
        count_bits=int(payload.get("count_bits", 8)),  # type: ignore[arg-type]
        max_ns=int(payload.get("max_ns", 0)),  # type: ignore[arg-type]
    )


def _parse_pwm_alignment_option_patch(payload: dict[str, object]) -> PwmAlignmentOptionPatch:
    return PwmAlignmentOptionPatch(
        peripheral=str(payload["peripheral"]),
        alignment=str(payload["alignment"]),
        field_value=int(payload["field_value"]),  # type: ignore[arg-type]
    )


def _parse_pwm_break_input_patch(payload: dict[str, object]) -> PwmBreakInputPatch:
    return PwmBreakInputPatch(
        peripheral=str(payload["peripheral"]),
        input_id=str(payload["input_id"]),
        polarity_field_value=int(payload.get("polarity_field_value", 0)),  # type: ignore[arg-type]
        enable_field_value=int(payload.get("enable_field_value", 1)),  # type: ignore[arg-type]
    )


def _parse_pwm_mode_flags_patch(payload: dict[str, object]) -> PwmModeFlagsPatch:
    return PwmModeFlagsPatch(
        peripheral=str(payload["peripheral"]),
        supports_deadtime=bool(payload.get("supports_deadtime", False)),
        supports_break_input=bool(payload.get("supports_break_input", False)),
        supports_complementary_outputs=bool(payload.get("supports_complementary_outputs", False)),
        supports_asymmetric_pwm=bool(payload.get("supports_asymmetric_pwm", False)),
        supports_combined_pwm=bool(payload.get("supports_combined_pwm", False)),
    )


def _parse_peripheral_max_clock_patch(
    payload: dict[str, object],
) -> PeripheralMaxClockPatch:
    return PeripheralMaxClockPatch(
        peripheral=str(payload["peripheral"]),
        max_clock_hz=int(payload["max_clock_hz"]),  # type: ignore[arg-type]
    )


def _parse_timer_prescaler_option_patch(payload: dict[str, object]) -> TimerPrescalerOptionPatch:
    return TimerPrescalerOptionPatch(
        peripheral=str(payload["peripheral"]),
        max_prescaler=int(payload["max_prescaler"]),  # type: ignore[arg-type]
        max_auto_reload=int(payload.get("max_auto_reload", 0)),  # type: ignore[arg-type]
    )


def _parse_timer_trigger_source_patch(payload: dict[str, object]) -> TimerTriggerSourcePatch:
    return TimerTriggerSourcePatch(
        peripheral=str(payload["peripheral"]),
        source=str(payload["source"]),
        field_value=int(payload["field_value"]),  # type: ignore[arg-type]
    )


def _parse_timer_master_output_patch(payload: dict[str, object]) -> TimerMasterOutputPatch:
    return TimerMasterOutputPatch(
        peripheral=str(payload["peripheral"]),
        source=str(payload["source"]),
        field_value=int(payload["field_value"]),  # type: ignore[arg-type]
    )


def _parse_timer_mode_flags_patch(payload: dict[str, object]) -> TimerModeFlagsPatch:
    return TimerModeFlagsPatch(
        peripheral=str(payload["peripheral"]),
        supports_dma_burst=bool(payload.get("supports_dma_burst", False)),
        supports_repetition_counter=bool(payload.get("supports_repetition_counter", False)),
        supports_xor_input=bool(payload.get("supports_xor_input", False)),
    )


def _parse_adc_internal_channel_patch(payload: dict[str, object]) -> AdcInternalChannelPatch:
    return AdcInternalChannelPatch(
        peripheral=str(payload["peripheral"]),
        kind=str(payload["kind"]),
        channel_index=int(payload["channel_index"]),
    )


def _parse_adc_calibration_data_point_patch(
    payload: dict[str, object],
) -> AdcCalibrationDataPointPatch:
    address = payload["address"]
    if isinstance(address, str):
        address_int = int(address, 0)
    else:
        address_int = int(address)
    return AdcCalibrationDataPointPatch(
        peripheral=str(payload["peripheral"]),
        kind=str(payload["kind"]),
        address=address_int,
        size_bits=int(payload["size_bits"]),
        semantic_constant=int(payload["semantic_constant"]),
    )


def _parse_adc_calibration_context_patch(
    payload: dict[str, object],
) -> AdcCalibrationContextPatch:
    return AdcCalibrationContextPatch(
        peripheral=str(payload["peripheral"]),
        cal_temp_low_celsius=int(payload["cal_temp_low_celsius"]),
        cal_temp_high_celsius=int(payload["cal_temp_high_celsius"]),
        cal_voltage_mv=int(payload["cal_voltage_mv"]),
        vrefint_nominal_mv=int(payload["vrefint_nominal_mv"]),
    )


def _parse_adc_resolution_option_patch(payload: dict[str, object]) -> AdcResolutionOptionPatch:
    return AdcResolutionOptionPatch(
        peripheral=str(payload["peripheral"]),
        bits=int(payload["bits"]),
        field_value=int(payload["field_value"]),
    )


def _parse_adc_sample_time_option_patch(payload: dict[str, object]) -> AdcSampleTimeOptionPatch:
    return AdcSampleTimeOptionPatch(
        peripheral=str(payload["peripheral"]),
        cycles_q8=int(payload["cycles_q8"]),
        field_value=int(payload["field_value"]),
    )


def _parse_adc_oversampling_option_patch(
    payload: dict[str, object],
) -> AdcOversamplingOptionPatch:
    return AdcOversamplingOptionPatch(
        peripheral=str(payload["peripheral"]),
        ratio=int(payload["ratio"]),
        field_value=int(payload["field_value"]),
    )


def _parse_adc_external_trigger_patch(payload: dict[str, object]) -> AdcExternalTriggerPatch:
    return AdcExternalTriggerPatch(
        peripheral=str(payload["peripheral"]),
        source=str(payload["source"]),
        extsel_value=int(payload["extsel_value"]),
        default_polarity=int(payload.get("default_polarity", 1) or 1),
    )


# ---------------------------------------------------------------------------
# UART + SPI Tier 2/3/4 parsers (added by add-uart-spi-tier-2-3-4-data)
# ---------------------------------------------------------------------------


def _parse_uart_baud_clock_source_patch(
    payload: dict[str, object],
) -> UartBaudClockSourcePatch:
    return UartBaudClockSourcePatch(
        peripheral=str(payload["peripheral"]),
        source=str(payload["source"]),
        field_value=int(payload["field_value"]),
    )


def _parse_uart_baud_oversampling_option_patch(
    payload: dict[str, object],
) -> UartBaudOversamplingOptionPatch:
    return UartBaudOversamplingOptionPatch(
        peripheral=str(payload["peripheral"]),
        ratio=int(payload["ratio"]),
        field_value=int(payload["field_value"]),
    )


def _parse_uart_fifo_trigger_option_patch(
    payload: dict[str, object],
) -> UartFifoTriggerOptionPatch:
    return UartFifoTriggerOptionPatch(
        peripheral=str(payload["peripheral"]),
        fraction_q8=int(payload["fraction_q8"]),
        field_value=int(payload["field_value"]),
    )


def _parse_uart_data_bits_option_patch(
    payload: dict[str, object],
) -> UartDataBitsOptionPatch:
    return UartDataBitsOptionPatch(
        peripheral=str(payload["peripheral"]),
        bits=int(payload["bits"]),
        m0_value=int(payload.get("m0_value", 0) or 0),
        m1_value=int(payload.get("m1_value", 0) or 0),
    )


def _parse_uart_parity_option_patch(
    payload: dict[str, object],
) -> UartParityOptionPatch:
    return UartParityOptionPatch(
        peripheral=str(payload["peripheral"]),
        parity=str(payload["parity"]),
        pce_value=int(payload["pce_value"]),
        ps_value=int(payload.get("ps_value", 0) or 0),
    )


def _parse_uart_stop_bits_option_patch(
    payload: dict[str, object],
) -> UartStopBitsOptionPatch:
    return UartStopBitsOptionPatch(
        peripheral=str(payload["peripheral"]),
        stop_bits_q8=int(payload["stop_bits_q8"]),
        field_value=int(payload["field_value"]),
    )


def _parse_uart_mode_flags_patch(payload: dict[str, object]) -> UartModeFlagsPatch:
    return UartModeFlagsPatch(
        peripheral=str(payload["peripheral"]),
        supports_lin=bool(payload.get("supports_lin", False)),
        supports_irda=bool(payload.get("supports_irda", False)),
        supports_smartcard=bool(payload.get("supports_smartcard", False)),
        supports_half_duplex=bool(payload.get("supports_half_duplex", False)),
        supports_synchronous=bool(payload.get("supports_synchronous", False)),
        supports_auto_baud=bool(payload.get("supports_auto_baud", False)),
        supports_wake_from_stop=bool(payload.get("supports_wake_from_stop", False)),
    )


def _parse_spi_baud_prescaler_option_patch(
    payload: dict[str, object],
) -> SpiBaudPrescalerOptionPatch:
    return SpiBaudPrescalerOptionPatch(
        peripheral=str(payload["peripheral"]),
        divisor=int(payload["divisor"]),
        field_value=int(payload["field_value"]),
    )


def _parse_spi_frame_size_option_patch(
    payload: dict[str, object],
) -> SpiFrameSizeOptionPatch:
    return SpiFrameSizeOptionPatch(
        peripheral=str(payload["peripheral"]),
        bits=int(payload["bits"]),
        field_value=int(payload["field_value"]),
    )


def _parse_spi_fifo_threshold_option_patch(
    payload: dict[str, object],
) -> SpiFifoThresholdOptionPatch:
    return SpiFifoThresholdOptionPatch(
        peripheral=str(payload["peripheral"]),
        threshold_bits=int(payload["threshold_bits"]),
        field_value=int(payload["field_value"]),
    )


def _parse_spi_mode_flags_patch(payload: dict[str, object]) -> SpiModeFlagsPatch:
    return SpiModeFlagsPatch(
        peripheral=str(payload["peripheral"]),
        supports_crc=bool(payload.get("supports_crc", False)),
        supports_ti_frame=bool(payload.get("supports_ti_frame", False)),
        supports_motorola_frame=bool(payload.get("supports_motorola_frame", True)),
        supports_i2s_submode=bool(payload.get("supports_i2s_submode", False)),
        supports_bidirectional_3wire=bool(payload.get("supports_bidirectional_3wire", False)),
        supports_lsb_first=bool(payload.get("supports_lsb_first", False)),
        supports_nss_hw_management=bool(payload.get("supports_nss_hw_management", False)),
    )
