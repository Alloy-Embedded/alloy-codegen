# ruff: noqa: E501

"""Runtime-lite driver semantic emission helpers.

This layer sits above runtime-lite facts. It publishes schema-aware semantic
traits that Alloy drivers can consume directly without scanning reflection
tables or rediscovering register meanings in the runtime.
"""

from __future__ import annotations

import re
from dataclasses import dataclass

from alloy_codegen.ir.model import (
    CanonicalDeviceIR,
    ConnectionCandidate,
    GpioPinDescriptor,
    PeripheralInstance,
    PinDefinition,
    RegisterDescriptor,
    RegisterFieldDescriptor,
)
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _collect_runtime_semantics_catalog,
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _semantic_enum_ref,
    _std_array_lines,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_dma_bindings,
    runtime_lite_peripheral_class_name,
)

GPIO_DRIVER_HEADER = "driver_semantics/gpio.hpp"
I2C_DRIVER_HEADER = "driver_semantics/i2c.hpp"
SPI_DRIVER_HEADER = "driver_semantics/spi.hpp"
UART_DRIVER_HEADER = "driver_semantics/uart.hpp"
DMA_DRIVER_HEADER = "driver_semantics/dma.hpp"
TIMER_DRIVER_HEADER = "driver_semantics/timer.hpp"
PWM_DRIVER_HEADER = "driver_semantics/pwm.hpp"
ADC_DRIVER_HEADER = "driver_semantics/adc.hpp"
DAC_DRIVER_HEADER = "driver_semantics/dac.hpp"
RTC_DRIVER_HEADER = "driver_semantics/rtc.hpp"
WATCHDOG_DRIVER_HEADER = "driver_semantics/watchdog.hpp"
CAN_DRIVER_HEADER = "driver_semantics/can.hpp"
ETH_DRIVER_HEADER = "driver_semantics/eth.hpp"
USB_DRIVER_HEADER = "driver_semantics/usb.hpp"
QSPI_DRIVER_HEADER = "driver_semantics/qspi.hpp"
SDMMC_DRIVER_HEADER = "driver_semantics/sdmmc.hpp"
COMMON_DRIVER_HEADER = "driver_semantics/common.hpp"
PIO_DRIVER_HEADER = "driver_semantics/pio.hpp"

_IO_SIGNAL_PATTERN = re.compile(r"^io(?P<index>\d+)$", re.IGNORECASE)


@dataclass(frozen=True, slots=True)
class RuntimeRegisterRef:
    """One runtime driver register reference."""

    register_id: str | None
    base_address: int
    offset_bytes: int
    valid: bool


@dataclass(frozen=True, slots=True)
class RuntimeFieldRef:
    """One runtime driver field reference."""

    field_id: str | None
    register: RuntimeRegisterRef
    bit_offset: int
    bit_width: int
    valid: bool


@dataclass(frozen=True, slots=True)
class RuntimeIndexedFieldRef:
    """One indexed runtime field reference pattern."""

    base_address: int
    base_offset_bytes: int
    stride_bytes: int
    bit_offset: int
    bit_width: int
    bit_stride_bits: int
    valid: bool


@dataclass(frozen=True, slots=True)
class GpioSemanticRow:
    """GPIO semantic trait payload keyed by pin."""

    pin_name: str
    peripheral_name: str
    schema_id: str
    line_index: int
    mode_field: RuntimeFieldRef
    direction_field: RuntimeFieldRef
    output_type_field: RuntimeFieldRef
    pull_field: RuntimeFieldRef
    input_field: RuntimeFieldRef
    output_value_field: RuntimeFieldRef
    output_set_field: RuntimeFieldRef
    output_reset_field: RuntimeFieldRef
    pio_enable_field: RuntimeFieldRef
    pio_output_enable_field: RuntimeFieldRef
    pio_output_disable_field: RuntimeFieldRef
    pio_set_field: RuntimeFieldRef
    pio_clear_field: RuntimeFieldRef
    pio_input_state_field: RuntimeFieldRef
    pio_drive_enable_field: RuntimeFieldRef
    pio_drive_disable_field: RuntimeFieldRef
    pio_pull_up_enable_field: RuntimeFieldRef
    pio_pull_up_disable_field: RuntimeFieldRef
    pio_pull_down_enable_field: RuntimeFieldRef
    pio_pull_down_disable_field: RuntimeFieldRef


@dataclass(frozen=True, slots=True)
class UartSemanticRow:
    """UART semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    cr1_reg: RuntimeRegisterRef
    cr2_reg: RuntimeRegisterRef
    brr_reg: RuntimeRegisterRef
    isr_reg: RuntimeRegisterRef
    rdr_reg: RuntimeRegisterRef
    tdr_reg: RuntimeRegisterRef
    sr_reg: RuntimeRegisterRef
    dr_reg: RuntimeRegisterRef
    cr_reg: RuntimeRegisterRef
    mr_reg: RuntimeRegisterRef
    brgr_reg: RuntimeRegisterRef
    thr_reg: RuntimeRegisterRef
    us_cr_reg: RuntimeRegisterRef
    us_mr_reg: RuntimeRegisterRef
    us_brgr_reg: RuntimeRegisterRef
    us_thr_reg: RuntimeRegisterRef
    ue_field: RuntimeFieldRef
    re_field: RuntimeFieldRef
    te_field: RuntimeFieldRef
    pce_field: RuntimeFieldRef
    ps_field: RuntimeFieldRef
    m0_field: RuntimeFieldRef
    m1_field: RuntimeFieldRef
    m_field: RuntimeFieldRef
    stop_field: RuntimeFieldRef
    tdr_field: RuntimeFieldRef
    rdr_field: RuntimeFieldRef
    txe_isr_field: RuntimeFieldRef
    rxne_isr_field: RuntimeFieldRef
    tc_isr_field: RuntimeFieldRef
    txe_sr_field: RuntimeFieldRef
    rxne_sr_field: RuntimeFieldRef
    tc_sr_field: RuntimeFieldRef
    dr_field: RuntimeFieldRef
    rstrx_field: RuntimeFieldRef
    rsttx_field: RuntimeFieldRef
    rxdis_field: RuntimeFieldRef
    txdis_field: RuntimeFieldRef
    rststa_field: RuntimeFieldRef
    par_field: RuntimeFieldRef
    chmode_field: RuntimeFieldRef
    cd_field: RuntimeFieldRef
    rxen_field: RuntimeFieldRef
    txen_field: RuntimeFieldRef
    txrdy_field: RuntimeFieldRef
    rxrdy_field: RuntimeFieldRef
    txempty_field: RuntimeFieldRef
    txchr_field: RuntimeFieldRef
    rxchr_field: RuntimeFieldRef
    us_rstrx_field: RuntimeFieldRef
    us_rsttx_field: RuntimeFieldRef
    us_rxdis_field: RuntimeFieldRef
    us_txdis_field: RuntimeFieldRef
    us_rststa_field: RuntimeFieldRef
    us_usart_mode_field: RuntimeFieldRef
    us_usclks_field: RuntimeFieldRef
    us_chrl_field: RuntimeFieldRef
    us_cd_field: RuntimeFieldRef
    us_rxen_field: RuntimeFieldRef
    us_txen_field: RuntimeFieldRef
    us_txrdy_field: RuntimeFieldRef
    us_rxrdy_field: RuntimeFieldRef
    us_txempty_field: RuntimeFieldRef
    us_txchr_field: RuntimeFieldRef
    us_rxchr_field: RuntimeFieldRef
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented


@dataclass(frozen=True, slots=True)
class I2cSemanticRow:
    """I2C semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    cr1_reg: RuntimeRegisterRef
    cr2_reg: RuntimeRegisterRef
    ccr_reg: RuntimeRegisterRef
    trise_reg: RuntimeRegisterRef
    sr1_reg: RuntimeRegisterRef
    sr2_reg: RuntimeRegisterRef
    dr_reg: RuntimeRegisterRef
    icr_reg: RuntimeRegisterRef
    cr_reg: RuntimeRegisterRef
    mmr_reg: RuntimeRegisterRef
    iadr_reg: RuntimeRegisterRef
    cwgr_reg: RuntimeRegisterRef
    sr_reg: RuntimeRegisterRef
    rhr_reg: RuntimeRegisterRef
    thr_reg: RuntimeRegisterRef
    pe_field: RuntimeFieldRef
    ack_field: RuntimeFieldRef
    start_field: RuntimeFieldRef
    stop_field: RuntimeFieldRef
    freq_field: RuntimeFieldRef
    ccr_field: RuntimeFieldRef
    fs_field: RuntimeFieldRef
    duty_field: RuntimeFieldRef
    trise_field: RuntimeFieldRef
    sb_field: RuntimeFieldRef
    addr_field: RuntimeFieldRef
    txe_field: RuntimeFieldRef
    rxne_field: RuntimeFieldRef
    btf_field: RuntimeFieldRef
    af_field: RuntimeFieldRef
    berr_field: RuntimeFieldRef
    arlo_field: RuntimeFieldRef
    busy_field: RuntimeFieldRef
    dr_data_field: RuntimeFieldRef
    sadd_field: RuntimeFieldRef
    rd_wrn_field: RuntimeFieldRef
    nbytes_field: RuntimeFieldRef
    autoend_field: RuntimeFieldRef
    txis_field: RuntimeFieldRef
    tc_field: RuntimeFieldRef
    stopf_field: RuntimeFieldRef
    txdata_field: RuntimeFieldRef
    rxdata_field: RuntimeFieldRef
    nackf_field: RuntimeFieldRef
    berr_isr_field: RuntimeFieldRef
    arlo_isr_field: RuntimeFieldRef
    stopcf_field: RuntimeFieldRef
    nackcf_field: RuntimeFieldRef
    berrcf_field: RuntimeFieldRef
    arlocf_field: RuntimeFieldRef
    msen_field: RuntimeFieldRef
    msdis_field: RuntimeFieldRef
    svdis_field: RuntimeFieldRef
    swrst_field: RuntimeFieldRef
    iadrsz_field: RuntimeFieldRef
    mread_field: RuntimeFieldRef
    dadr_field: RuntimeFieldRef
    iadr_field: RuntimeFieldRef
    cldiv_field: RuntimeFieldRef
    chdiv_field: RuntimeFieldRef
    ckdiv_field: RuntimeFieldRef
    hold_field: RuntimeFieldRef
    txcomp_field: RuntimeFieldRef
    rxrdy_field: RuntimeFieldRef
    txrdy_field: RuntimeFieldRef
    nack_field: RuntimeFieldRef
    arblst_field: RuntimeFieldRef
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented


@dataclass(frozen=True, slots=True)
class SpiSemanticRow:
    """SPI semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    cr1_reg: RuntimeRegisterRef
    cr2_reg: RuntimeRegisterRef
    sr_reg: RuntimeRegisterRef
    dr_reg: RuntimeRegisterRef
    cr_reg: RuntimeRegisterRef
    mr_reg: RuntimeRegisterRef
    csr_reg: RuntimeRegisterRef
    tdr_reg: RuntimeRegisterRef
    rdr_reg: RuntimeRegisterRef
    cpha_field: RuntimeFieldRef
    cpol_field: RuntimeFieldRef
    mstr_field: RuntimeFieldRef
    br_field: RuntimeFieldRef
    spe_field: RuntimeFieldRef
    lsbfirst_field: RuntimeFieldRef
    ssi_field: RuntimeFieldRef
    ssm_field: RuntimeFieldRef
    dff_field: RuntimeFieldRef
    ds_field: RuntimeFieldRef
    frxth_field: RuntimeFieldRef
    txe_field: RuntimeFieldRef
    rxne_field: RuntimeFieldRef
    bsy_field: RuntimeFieldRef
    dr_data_field: RuntimeFieldRef
    spien_field: RuntimeFieldRef
    spidis_field: RuntimeFieldRef
    swrst_field: RuntimeFieldRef
    ps_field: RuntimeFieldRef
    pcsdec_field: RuntimeFieldRef
    modfdis_field: RuntimeFieldRef
    pcs_field: RuntimeFieldRef
    dlybcs_field: RuntimeFieldRef
    ncpha_field: RuntimeFieldRef
    bits_field: RuntimeFieldRef
    scbr_field: RuntimeFieldRef
    dlybs_field: RuntimeFieldRef
    dlybct_field: RuntimeFieldRef
    tdre_field: RuntimeFieldRef
    rdrf_field: RuntimeFieldRef
    txempty_field: RuntimeFieldRef
    td_field: RuntimeFieldRef
    tdr_pcs_field: RuntimeFieldRef
    rd_field: RuntimeFieldRef
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented


@dataclass(frozen=True, slots=True)
class DmaSemanticRow:
    """DMA semantic trait payload keyed by binding peripheral/signal."""

    peripheral_name: str
    signal_name: str
    binding_id: str
    controller_name: str
    request_line: str
    route_id: str
    conflict_group: str | None
    controller_schema_id: str | None
    router_name: str | None
    router_schema_id: str | None
    channel_index: int | None
    request_value: int | None
    channel_selector: int | None
    route_selector_field: RuntimeIndexedFieldRef


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


@dataclass(frozen=True, slots=True)
class AdcDmaModeOption:
    """One DMA mode (one_shot|circular) + the field value that selects it."""

    mode: str  # "one_shot" | "circular"
    field_value: int


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


@dataclass(frozen=True, slots=True)
class DacSemanticRow:
    """DAC semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    channel_count: int
    has_hardware_trigger: bool
    has_dma: bool
    control_reg: RuntimeRegisterRef
    mode_reg: RuntimeRegisterRef
    trigger_reg: RuntimeRegisterRef
    channel_enable_reg: RuntimeRegisterRef
    channel_disable_reg: RuntimeRegisterRef
    channel_status_reg: RuntimeRegisterRef
    data_reg: RuntimeRegisterRef
    software_reset_field: RuntimeFieldRef
    word_mode_field: RuntimeFieldRef
    prescaler_field: RuntimeFieldRef
    channel_enable_pattern: RuntimeIndexedFieldRef
    channel_disable_pattern: RuntimeIndexedFieldRef
    channel_ready_pattern: RuntimeIndexedFieldRef
    trigger_enable_pattern: RuntimeIndexedFieldRef
    trigger_select_pattern: RuntimeIndexedFieldRef
    data_pattern: RuntimeIndexedFieldRef


@dataclass(frozen=True, slots=True)
class DacChannelSemanticRow:
    """DAC channel semantic trait payload keyed by peripheral/channel index."""

    peripheral_name: str
    channel_index: int
    enable_field: RuntimeFieldRef
    disable_field: RuntimeFieldRef
    ready_field: RuntimeFieldRef
    trigger_enable_field: RuntimeFieldRef
    trigger_select_field: RuntimeFieldRef
    data_field: RuntimeFieldRef


@dataclass(frozen=True, slots=True)
class RtcSemanticRow:
    """RTC semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    has_calendar: bool
    has_alarm: bool
    has_write_protection: bool
    control_reg: RuntimeRegisterRef
    mode_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    time_reg: RuntimeRegisterRef
    date_reg: RuntimeRegisterRef
    alarm_time_reg: RuntimeRegisterRef
    alarm_date_reg: RuntimeRegisterRef
    interrupt_enable_reg: RuntimeRegisterRef
    interrupt_disable_reg: RuntimeRegisterRef
    interrupt_mask_reg: RuntimeRegisterRef
    clear_reg: RuntimeRegisterRef
    write_protect_reg: RuntimeRegisterRef
    prescaler_reg: RuntimeRegisterRef
    hour_mode_field: RuntimeFieldRef
    init_field: RuntimeFieldRef
    init_ready_field: RuntimeFieldRef
    shadow_bypass_field: RuntimeFieldRef
    update_time_field: RuntimeFieldRef
    update_calendar_field: RuntimeFieldRef
    update_ack_field: RuntimeFieldRef
    alarm_enable_field: RuntimeFieldRef
    alarm_interrupt_enable_field: RuntimeFieldRef
    second_interrupt_enable_field: RuntimeFieldRef
    time_event_interrupt_enable_field: RuntimeFieldRef
    calendar_event_interrupt_enable_field: RuntimeFieldRef
    status_alarm_field: RuntimeFieldRef
    status_second_field: RuntimeFieldRef
    status_time_event_field: RuntimeFieldRef
    status_calendar_event_field: RuntimeFieldRef
    status_tamper_error_field: RuntimeFieldRef
    clear_alarm_field: RuntimeFieldRef
    clear_second_field: RuntimeFieldRef
    clear_time_event_field: RuntimeFieldRef
    clear_calendar_event_field: RuntimeFieldRef
    clear_tamper_error_field: RuntimeFieldRef
    write_protect_key_field: RuntimeFieldRef
    write_protect_disable_key0: int
    write_protect_disable_key1: int
    write_protect_enable_key: int
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented


@dataclass(frozen=True, slots=True)
class WatchdogSemanticRow:
    """Watchdog semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    has_window: bool
    control_reg: RuntimeRegisterRef
    config_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    prescaler_reg: RuntimeRegisterRef
    reload_reg: RuntimeRegisterRef
    window_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    disable_field: RuntimeFieldRef
    restart_field: RuntimeFieldRef
    key_field: RuntimeFieldRef
    timeout_field: RuntimeFieldRef
    window_field: RuntimeFieldRef
    prescaler_field: RuntimeFieldRef
    early_warning_interrupt_enable_field: RuntimeFieldRef
    reset_enable_field: RuntimeFieldRef
    status_prescaler_update_field: RuntimeFieldRef
    status_reload_update_field: RuntimeFieldRef
    status_window_update_field: RuntimeFieldRef
    status_timeout_field: RuntimeFieldRef
    status_error_field: RuntimeFieldRef
    required_config_field: RuntimeFieldRef
    required_config_value: int
    start_key_value: int
    refresh_key_value: int
    unlock_key_value: int
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented


@dataclass(frozen=True, slots=True)
class CanSemanticRow:
    """CAN/FDCAN semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    has_flexible_data_rate: bool
    control_reg: RuntimeRegisterRef
    nominal_timing_reg: RuntimeRegisterRef
    data_timing_reg: RuntimeRegisterRef
    test_reg: RuntimeRegisterRef
    error_counter_reg: RuntimeRegisterRef
    protocol_status_reg: RuntimeRegisterRef
    interrupt_reg: RuntimeRegisterRef
    interrupt_enable_reg: RuntimeRegisterRef
    interrupt_line_select_reg: RuntimeRegisterRef
    interrupt_line_enable_reg: RuntimeRegisterRef
    global_filter_reg: RuntimeRegisterRef
    standard_filter_config_reg: RuntimeRegisterRef
    extended_filter_config_reg: RuntimeRegisterRef
    extended_id_mask_reg: RuntimeRegisterRef
    rx_fifo0_config_reg: RuntimeRegisterRef
    rx_fifo0_status_reg: RuntimeRegisterRef
    rx_fifo0_ack_reg: RuntimeRegisterRef
    tx_buffer_config_reg: RuntimeRegisterRef
    tx_fifo_queue_status_reg: RuntimeRegisterRef
    tx_buffer_add_request_reg: RuntimeRegisterRef
    tx_buffer_pending_reg: RuntimeRegisterRef
    tx_event_fifo_config_reg: RuntimeRegisterRef
    tx_event_fifo_status_reg: RuntimeRegisterRef
    tx_event_fifo_ack_reg: RuntimeRegisterRef
    init_field: RuntimeFieldRef
    config_enable_field: RuntimeFieldRef
    restricted_operation_field: RuntimeFieldRef
    restricted_operation_ack_field: RuntimeFieldRef
    bus_monitor_field: RuntimeFieldRef
    fd_operation_enable_field: RuntimeFieldRef
    bit_rate_switch_enable_field: RuntimeFieldRef
    nominal_prescaler_field: RuntimeFieldRef
    nominal_time_seg1_field: RuntimeFieldRef
    nominal_time_seg2_field: RuntimeFieldRef
    nominal_sync_jump_width_field: RuntimeFieldRef
    data_prescaler_field: RuntimeFieldRef
    data_time_seg1_field: RuntimeFieldRef
    data_time_seg2_field: RuntimeFieldRef
    data_sync_jump_width_field: RuntimeFieldRef
    rx_fifo0_new_interrupt_field: RuntimeFieldRef
    tx_complete_interrupt_field: RuntimeFieldRef
    tx_event_fifo_new_interrupt_field: RuntimeFieldRef
    rx_fifo0_new_interrupt_enable_field: RuntimeFieldRef
    tx_complete_interrupt_enable_field: RuntimeFieldRef
    tx_event_fifo_new_interrupt_enable_field: RuntimeFieldRef
    rx_fifo0_fill_level_field: RuntimeFieldRef
    rx_fifo0_get_index_field: RuntimeFieldRef
    rx_fifo0_message_lost_field: RuntimeFieldRef
    rx_fifo0_ack_index_field: RuntimeFieldRef
    tx_fifo_queue_put_index_field: RuntimeFieldRef
    tx_fifo_queue_free_level_field: RuntimeFieldRef
    tx_buffer_add_request_pattern: RuntimeIndexedFieldRef
    tx_buffer_pending_pattern: RuntimeIndexedFieldRef


@dataclass(frozen=True, slots=True)
class EthSemanticRow:
    """Ethernet MAC semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    supports_mii: bool
    supports_rmii: bool
    has_dma_engine: bool
    has_statistics_counters: bool
    control_reg: RuntimeRegisterRef
    config_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    user_io_reg: RuntimeRegisterRef
    dma_config_reg: RuntimeRegisterRef
    tx_status_reg: RuntimeRegisterRef
    rx_status_reg: RuntimeRegisterRef
    interrupt_status_reg: RuntimeRegisterRef
    interrupt_enable_reg: RuntimeRegisterRef
    interrupt_disable_reg: RuntimeRegisterRef
    interrupt_mask_reg: RuntimeRegisterRef
    rx_descriptor_base_reg: RuntimeRegisterRef
    tx_descriptor_base_reg: RuntimeRegisterRef
    rx_enable_field: RuntimeFieldRef
    tx_enable_field: RuntimeFieldRef
    management_port_enable_field: RuntimeFieldRef
    clear_statistics_field: RuntimeFieldRef
    write_enable_statistics_field: RuntimeFieldRef
    tx_start_field: RuntimeFieldRef
    speed_field: RuntimeFieldRef
    full_duplex_field: RuntimeFieldRef
    mdc_clock_divider_field: RuntimeFieldRef
    rmii_enable_field: RuntimeFieldRef
    management_done_field: RuntimeFieldRef
    rx_complete_interrupt_field: RuntimeFieldRef
    tx_complete_interrupt_field: RuntimeFieldRef
    rx_complete_interrupt_enable_field: RuntimeFieldRef
    tx_complete_interrupt_enable_field: RuntimeFieldRef
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented


@dataclass(frozen=True, slots=True)
class UsbSemanticRow:
    """USB semantic trait payload keyed by peripheral.

    Hardware-feature fields (added by ``add-usb-semantic-traits``) carry the
    static silicon facts (base address, packet memory, endpoint count,
    speed/host capabilities, fixed pin assignments) sourced from
    ``Device.usb_controllers``.  ``hardware_present`` is ``False`` for rows
    derived only from register inspection — those rows still emit register
    references but the alloy HAL's ``kPresent`` predicate stays ``false``
    until a ``UsbControllerDescriptor`` is admitted for the peripheral.
    """

    peripheral_name: str
    schema_id: str | None
    supports_device_mode: bool
    supports_host_mode: bool
    has_dedicated_endpoint_config: bool
    has_clock_freeze: bool
    control_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    interrupt_status_reg: RuntimeRegisterRef
    interrupt_mask_reg: RuntimeRegisterRef
    device_control_reg: RuntimeRegisterRef
    device_status_reg: RuntimeRegisterRef
    device_interrupt_status_reg: RuntimeRegisterRef
    device_interrupt_mask_reg: RuntimeRegisterRef
    device_interrupt_enable_reg: RuntimeRegisterRef
    device_interrupt_disable_reg: RuntimeRegisterRef
    host_control_reg: RuntimeRegisterRef
    host_status_reg: RuntimeRegisterRef
    host_interrupt_status_reg: RuntimeRegisterRef
    host_interrupt_mask_reg: RuntimeRegisterRef
    host_interrupt_enable_reg: RuntimeRegisterRef
    host_interrupt_disable_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    freeze_clock_field: RuntimeFieldRef
    force_device_mode_field: RuntimeFieldRef
    force_host_mode_field: RuntimeFieldRef
    mode_status_field: RuntimeFieldRef
    soft_disconnect_field: RuntimeFieldRef
    remote_wakeup_field: RuntimeFieldRef
    address_enable_field: RuntimeFieldRef
    address_field: RuntimeFieldRef
    clock_usable_field: RuntimeFieldRef
    hardware_present: bool = False
    base_address: int = 0
    endpoint_count: int = 0
    supports_high_speed: bool = False
    supports_dma: bool = False
    crystalless: bool = False
    dpram_base_address: int | None = None
    dpram_size_bytes: int | None = None
    dma_channel_count: int = 0
    dm_pin: str | None = None
    dp_pin: str | None = None
    clock_source: str | None = None


@dataclass(frozen=True, slots=True)
class QspiSemanticRow:
    """QSPI semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    supports_spi_mode: bool
    supports_memory_mode: bool
    has_scrambling: bool
    has_dma: bool
    control_reg: RuntimeRegisterRef
    mode_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    interrupt_enable_reg: RuntimeRegisterRef
    interrupt_disable_reg: RuntimeRegisterRef
    interrupt_mask_reg: RuntimeRegisterRef
    serial_clock_reg: RuntimeRegisterRef
    instruction_address_reg: RuntimeRegisterRef
    instruction_code_reg: RuntimeRegisterRef
    instruction_frame_reg: RuntimeRegisterRef
    scrambling_mode_reg: RuntimeRegisterRef
    scrambling_key_reg: RuntimeRegisterRef
    receive_data_reg: RuntimeRegisterRef
    transmit_data_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    disable_field: RuntimeFieldRef
    software_reset_field: RuntimeFieldRef
    last_transfer_field: RuntimeFieldRef
    enabled_status_field: RuntimeFieldRef
    serial_memory_mode_field: RuntimeFieldRef
    chip_select_mode_field: RuntimeFieldRef
    bits_per_transfer_field: RuntimeFieldRef
    receive_ready_field: RuntimeFieldRef
    transmit_ready_field: RuntimeFieldRef
    transmit_empty_field: RuntimeFieldRef
    receive_ready_interrupt_enable_field: RuntimeFieldRef
    transmit_ready_interrupt_enable_field: RuntimeFieldRef
    transmit_empty_interrupt_enable_field: RuntimeFieldRef
    serial_clock_baud_rate_field: RuntimeFieldRef
    instruction_field: RuntimeFieldRef
    address_field: RuntimeFieldRef
    width_field: RuntimeFieldRef
    instruction_enable_field: RuntimeFieldRef
    address_enable_field: RuntimeFieldRef
    option_enable_field: RuntimeFieldRef
    data_enable_field: RuntimeFieldRef
    transfer_type_field: RuntimeFieldRef
    continuous_read_mode_field: RuntimeFieldRef
    dummy_cycles_field: RuntimeFieldRef
    scrambling_enable_field: RuntimeFieldRef


@dataclass(frozen=True, slots=True)
class SdmmcSemanticRow:
    """SD/MMC semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    supports_1bit: bool
    supports_4bit: bool
    supports_8bit: bool
    has_dma: bool
    control_reg: RuntimeRegisterRef
    mode_reg: RuntimeRegisterRef
    data_timeout_reg: RuntimeRegisterRef
    sd_card_reg: RuntimeRegisterRef
    argument_reg: RuntimeRegisterRef
    command_reg: RuntimeRegisterRef
    block_reg: RuntimeRegisterRef
    completion_timeout_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    interrupt_enable_reg: RuntimeRegisterRef
    interrupt_disable_reg: RuntimeRegisterRef
    interrupt_mask_reg: RuntimeRegisterRef
    dma_reg: RuntimeRegisterRef
    config_reg: RuntimeRegisterRef
    read_data_reg: RuntimeRegisterRef
    write_data_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    disable_field: RuntimeFieldRef
    power_save_enable_field: RuntimeFieldRef
    power_save_disable_field: RuntimeFieldRef
    software_reset_field: RuntimeFieldRef
    clock_divider_field: RuntimeFieldRef
    power_save_divider_field: RuntimeFieldRef
    read_proof_field: RuntimeFieldRef
    write_proof_field: RuntimeFieldRef
    slot_select_field: RuntimeFieldRef
    bus_width_field: RuntimeFieldRef
    argument_field: RuntimeFieldRef
    command_index_field: RuntimeFieldRef
    response_type_field: RuntimeFieldRef
    special_command_field: RuntimeFieldRef
    open_drain_field: RuntimeFieldRef
    max_latency_field: RuntimeFieldRef
    transfer_command_field: RuntimeFieldRef
    transfer_direction_field: RuntimeFieldRef
    transfer_type_field: RuntimeFieldRef
    sdio_interrupt_command_field: RuntimeFieldRef
    atacs_field: RuntimeFieldRef
    block_count_field: RuntimeFieldRef
    block_length_field: RuntimeFieldRef
    command_ready_field: RuntimeFieldRef
    rx_ready_field: RuntimeFieldRef
    tx_ready_field: RuntimeFieldRef
    transfer_done_field: RuntimeFieldRef
    not_busy_field: RuntimeFieldRef
    dma_enable_field: RuntimeFieldRef


@dataclass(frozen=True, slots=True)
class TimerSemanticRow:
    """Timer semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    counter_bits: int
    channel_count: int
    has_compare: bool
    has_capture: bool
    has_encoder: bool
    has_pwm: bool
    has_one_pulse: bool
    has_center_aligned: bool
    has_complementary_outputs: bool
    has_deadtime: bool
    has_break_input: bool
    control_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    event_reg: RuntimeRegisterRef
    counter_reg: RuntimeRegisterRef
    prescaler_reg: RuntimeRegisterRef
    period_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    disable_field: RuntimeFieldRef
    module_disable_field: RuntimeFieldRef
    software_reset_field: RuntimeFieldRef
    start_field: RuntimeFieldRef
    stop_field: RuntimeFieldRef
    update_interrupt_enable_field: RuntimeFieldRef
    update_flag_field: RuntimeFieldRef
    update_generation_field: RuntimeFieldRef
    prescaler_field: RuntimeFieldRef
    period_field: RuntimeFieldRef
    one_pulse_field: RuntimeFieldRef
    center_aligned_field: RuntimeFieldRef
    auto_reload_preload_field: RuntimeFieldRef
    clock_source_field: RuntimeFieldRef
    encoder_mode_field: RuntimeFieldRef
    encoder_enable_field: RuntimeFieldRef
    encoder_position_enable_field: RuntimeFieldRef
    encoder_speed_enable_field: RuntimeFieldRef
    encoder_phase_edge_field: RuntimeFieldRef
    direction_field: RuntimeFieldRef
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented


@dataclass(frozen=True, slots=True)
class TimerChannelSemanticRow:
    """Timer channel semantic trait payload keyed by peripheral/channel index."""

    peripheral_name: str
    channel_index: int
    supports_compare: bool
    supports_capture: bool
    supports_encoder_input: bool
    supports_pwm: bool
    supports_complementary_output: bool
    control_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    compare_reg: RuntimeRegisterRef
    secondary_compare_reg: RuntimeRegisterRef
    period_reg: RuntimeRegisterRef
    counter_reg: RuntimeRegisterRef
    capture_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    interrupt_enable_field: RuntimeFieldRef
    interrupt_flag_field: RuntimeFieldRef
    mode_field: RuntimeFieldRef
    preload_field: RuntimeFieldRef
    output_enable_field: RuntimeFieldRef
    output_polarity_field: RuntimeFieldRef
    complementary_output_enable_field: RuntimeFieldRef
    capture_select_field: RuntimeFieldRef


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


@dataclass(frozen=True, slots=True)
class _SemanticContext:
    device: CanonicalDeviceIR
    semantics_catalog: dict[str, dict[str, str]]
    peripheral_by_name: dict[str, PeripheralInstance]
    pin_by_name: dict[str, PinDefinition]
    register_by_key: dict[tuple[str, str], RegisterDescriptor]
    field_by_key: dict[tuple[str, str, str], RegisterFieldDescriptor]
    gpio_candidate_by_pin: dict[str, ConnectionCandidate]
    candidate_peripherals_by_class: dict[str, tuple[PeripheralInstance, ...]]
    runtime_peripherals_by_class: dict[str, tuple[PeripheralInstance, ...]]


def _driver_semantics_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    paths: list[str] = []
    for device in devices:
        device_name = device.identity.device
        paths.extend(
            (
                _device_runtime_generated_path(family_dir, device_name, COMMON_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, GPIO_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, UART_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, I2C_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, SPI_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, DMA_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, TIMER_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, PWM_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, ADC_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, DAC_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, RTC_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, WATCHDOG_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, CAN_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, ETH_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, USB_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, QSPI_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, SDMMC_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, PIO_DRIVER_HEADER),
            )
        )
    return tuple(paths)


def runtime_driver_semantics_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return _driver_semantics_paths(family_dir=family_dir, devices=devices)


def _context(device: CanonicalDeviceIR) -> _SemanticContext:
    peripheral_by_name = {peripheral.name: peripheral for peripheral in device.peripherals}
    pin_by_name = {pin.name: pin for pin in device.pins}
    register_by_key = {
        (register.peripheral, register.name.upper()): register for register in device.registers
    }
    field_by_key = {
        (
            register_field.peripheral,
            register_field.register_name.upper(),
            register_field.name.upper(),
        ): register_field
        for register_field in device.register_fields
    }
    gpio_candidates = sorted(
        (
            candidate
            for candidate in device.connection_candidates
            if candidate.peripheral in peripheral_by_name
            and runtime_lite_peripheral_class_name(peripheral_by_name[candidate.peripheral].ip_name)
            == "gpio"
        ),
        key=lambda item: item.candidate_id,
    )
    gpio_candidate_by_pin: dict[str, ConnectionCandidate] = {}
    for candidate in gpio_candidates:
        gpio_candidate_by_pin.setdefault(candidate.pin, candidate)

    candidate_peripherals: dict[str, list[PeripheralInstance]] = {}
    seen: set[tuple[str, str]] = set()
    for candidate in sorted(device.connection_candidates, key=lambda item: item.candidate_id):
        peripheral = peripheral_by_name.get(candidate.peripheral)
        if peripheral is None:
            continue
        peripheral_class = runtime_lite_peripheral_class_name(peripheral.ip_name)
        key = (peripheral_class, peripheral.name)
        if key in seen:
            continue
        seen.add(key)
        candidate_peripherals.setdefault(peripheral_class, []).append(peripheral)

    runtime_peripherals: dict[str, list[PeripheralInstance]] = {}
    for peripheral in sorted(device.peripherals, key=lambda item: item.name):
        peripheral_class = runtime_lite_peripheral_class_name(peripheral.ip_name)
        runtime_peripherals.setdefault(peripheral_class, []).append(peripheral)
    return _SemanticContext(
        device=device,
        semantics_catalog=_collect_runtime_semantics_catalog((device,)),
        peripheral_by_name=peripheral_by_name,
        pin_by_name=pin_by_name,
        register_by_key=register_by_key,
        field_by_key=field_by_key,
        gpio_candidate_by_pin=gpio_candidate_by_pin,
        candidate_peripherals_by_class={
            name: tuple(sorted(peripherals, key=lambda item: item.name))
            for name, peripherals in candidate_peripherals.items()
        },
        runtime_peripherals_by_class={
            name: tuple(sorted(peripherals, key=lambda item: item.name))
            for name, peripherals in runtime_peripherals.items()
        },
    )


def _invalid_register_ref(base_address: int = 0) -> RuntimeRegisterRef:
    return RuntimeRegisterRef(
        register_id=None, base_address=base_address, offset_bytes=0, valid=False
    )


def _invalid_field_ref(base_address: int = 0) -> RuntimeFieldRef:
    return RuntimeFieldRef(
        field_id=None,
        register=_invalid_register_ref(base_address),
        bit_offset=0,
        bit_width=0,
        valid=False,
    )


def _invalid_indexed_field_ref(base_address: int = 0) -> RuntimeIndexedFieldRef:
    return RuntimeIndexedFieldRef(
        base_address=base_address,
        base_offset_bytes=0,
        stride_bytes=0,
        bit_offset=0,
        bit_width=0,
        bit_stride_bits=0,
        valid=False,
    )


def _indexed_field_ref(
    *,
    base_address: int,
    base_offset_bytes: int,
    stride_bytes: int,
    bit_offset: int,
    bit_width: int,
    bit_stride_bits: int = 0,
) -> RuntimeIndexedFieldRef:
    return RuntimeIndexedFieldRef(
        base_address=base_address,
        base_offset_bytes=base_offset_bytes,
        stride_bytes=stride_bytes,
        bit_offset=bit_offset,
        bit_width=bit_width,
        bit_stride_bits=bit_stride_bits,
        valid=True,
    )


def _resolve_register_ref(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_name: str,
    fallback_offset: int | None = None,
) -> RuntimeRegisterRef:
    peripheral = context.peripheral_by_name.get(peripheral_name)
    if peripheral is None:
        return _invalid_register_ref()
    register = context.register_by_key.get((peripheral_name, register_name.upper()))
    if register is not None:
        return RuntimeRegisterRef(
            register_id=register.register_id,
            base_address=peripheral.base_address,
            offset_bytes=register.offset_bytes,
            valid=True,
        )
    if fallback_offset is None:
        return _invalid_register_ref(peripheral.base_address)
    return RuntimeRegisterRef(
        register_id=None,
        base_address=peripheral.base_address,
        offset_bytes=fallback_offset,
        valid=True,
    )


def _resolve_field_ref(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_name: str,
    field_names: tuple[str, ...],
    fallback_register_offset: int | None = None,
    fallback_bit_offset: int | None = None,
    fallback_bit_width: int | None = None,
) -> RuntimeFieldRef:
    for field_name in field_names:
        field = context.field_by_key.get(
            (peripheral_name, register_name.upper(), field_name.upper())
        )
        if field is None:
            continue
        register_ref = _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
        )
        return RuntimeFieldRef(
            field_id=field.field_id,
            register=register_ref,
            bit_offset=field.bit_offset,
            bit_width=field.bit_width,
            valid=True,
        )

    register_ref = _resolve_register_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_name,
        fallback_offset=fallback_register_offset,
    )
    if not register_ref.valid or fallback_bit_offset is None or fallback_bit_width is None:
        return _invalid_field_ref(register_ref.base_address)
    return RuntimeFieldRef(
        field_id=None,
        register=register_ref,
        bit_offset=fallback_bit_offset,
        bit_width=fallback_bit_width,
        valid=True,
    )


def _resolve_register_ref_any(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_names: tuple[str, ...],
    fallback_offset: int | None = None,
) -> RuntimeRegisterRef:
    for register_name in register_names:
        register_ref = _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
        )
        if register_ref.valid and register_ref.register_id is not None:
            return register_ref
    if not register_names:
        return _invalid_register_ref()
    return _resolve_register_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_names[0],
        fallback_offset=fallback_offset,
    )


def _resolve_field_ref_any(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_names: tuple[str, ...],
    field_names: tuple[str, ...],
    fallback_register_offset: int | None = None,
    fallback_bit_offset: int | None = None,
    fallback_bit_width: int | None = None,
) -> RuntimeFieldRef:
    for register_name in register_names:
        field_ref = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
        )
        if field_ref.valid and field_ref.field_id is not None:
            return field_ref
    if not register_names:
        return _invalid_field_ref()
    return _resolve_field_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_names[0],
        field_names=field_names,
        fallback_register_offset=fallback_register_offset,
        fallback_bit_offset=fallback_bit_offset,
        fallback_bit_width=fallback_bit_width,
    )


def _manual_field_ref(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_name: str,
    register_offset: int,
    bit_offset: int,
    bit_width: int = 1,
) -> RuntimeFieldRef:
    register_ref = _resolve_register_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_name,
        fallback_offset=register_offset,
    )
    if not register_ref.valid:
        return _invalid_field_ref(register_ref.base_address)
    return RuntimeFieldRef(
        field_id=None,
        register=register_ref,
        bit_offset=bit_offset,
        bit_width=bit_width,
        valid=True,
    )


def _field_ref_expr(field_ref: RuntimeFieldRef) -> str:
    if not field_ref.valid:
        return "kInvalidFieldRef"
    register_expr = _register_ref_expr(field_ref.register)
    field_id = (
        "FieldId::none"
        if field_ref.field_id is None
        else f"FieldId::{_enum_identifier(field_ref.field_id)}"
    )
    return (
        f"RuntimeFieldRef{{{field_id}, {register_expr}, "
        f"{field_ref.bit_offset}u, {field_ref.bit_width}u, true}}"
    )


def _indexed_field_ref_expr(field_ref: RuntimeIndexedFieldRef) -> str:
    if not field_ref.valid:
        return "kInvalidIndexedFieldRef"
    return (
        "RuntimeIndexedFieldRef{"
        f"0x{field_ref.base_address:08X}u, "
        f"{field_ref.base_offset_bytes}u, "
        f"{field_ref.stride_bytes}u, "
        f"{field_ref.bit_offset}u, "
        f"{field_ref.bit_width}u, "
        f"{field_ref.bit_stride_bits}u, "
        "true}"
    )


def _register_ref_expr(register_ref: RuntimeRegisterRef) -> str:
    if not register_ref.valid:
        return "kInvalidRegisterRef"
    register_id = (
        "RegisterId::none"
        if register_ref.register_id is None
        else f"RegisterId::{_enum_identifier(register_ref.register_id)}"
    )
    return (
        f"RuntimeRegisterRef{{{register_id}, "
        f"0x{register_ref.base_address:08X}u, {register_ref.offset_bytes}u, true}}"
    )


# ---------------------------------------------------------------------------
# ADC trait helpers (Tier 2/3/4 — added by add-full-adc-coverage)
# ---------------------------------------------------------------------------


def _adc_internal_channel_expr(channel: AdcInternalChannel) -> str:
    return (
        "InternalAdcChannel{"
        f"InternalAdcChannelKind::{channel.kind}, "
        f"{channel.channel_index}u, true}}"
    )


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


def _render_array_lines(
    *,
    cpp_type: str,
    array_name: str,
    count_name: str,
    items: tuple[object, ...],
    expr_fn,  # type: ignore[no-untyped-def]
) -> list[str]:
    """Render a paired ``static constexpr std::uint32_t kCount`` +
    ``static constexpr std::array<T, N> kArray = { ... };`` declaration."""
    lines: list[str] = [
        f"  static constexpr std::uint32_t {count_name} = {len(items)}u;",
    ]
    if not items:
        lines.append(f"  static constexpr std::array<{cpp_type}, 0> {array_name} = {{}};")
        return lines
    item_lines = [f"    {expr_fn(item)}," for item in items]
    lines.append(f"  static constexpr std::array<{cpp_type}, {len(items)}> {array_name} = {{{{")
    lines.extend(item_lines)
    lines.append("  }};")
    return lines


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


def _schema_ref_expr(context: _SemanticContext, schema_id: str | None) -> str:
    return _semantic_enum_ref(
        "BackendSchemaId",
        context.semantics_catalog["backend_schema_enum_map"],
        schema_id,
    )


def _peripheral_ref(peripheral_name: str | None) -> str:
    if peripheral_name is None:
        return "PeripheralId::none"
    return f"PeripheralId::{_enum_identifier(peripheral_name)}"


def _pin_ref(pin_name: str) -> str:
    return f"PinId::{_enum_identifier(pin_name)}"


def _line_index_from_candidate(
    context: _SemanticContext, candidate: ConnectionCandidate
) -> int | None:
    pin = context.pin_by_name.get(candidate.pin)
    if pin is not None and pin.number >= 0:
        return pin.number
    match = _IO_SIGNAL_PATTERN.match(candidate.signal)
    if match is not None:
        return int(match.group("index"), 10)
    return None


def _st_gpio_semantics(
    context: _SemanticContext,
    *,
    pin_name: str,
    peripheral_name: str,
    schema_id: str,
    line_index: int,
) -> GpioSemanticRow:
    return GpioSemanticRow(
        pin_name=pin_name,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        line_index=line_index,
        mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MODER",
            field_names=(f"MODE{line_index}", f"MODER{line_index}"),
            fallback_register_offset=0x00,
            fallback_bit_offset=line_index * 2,
            fallback_bit_width=2,
        ),
        direction_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        output_type_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="OTYPER",
            field_names=(f"OT{line_index}", f"OT_{line_index}", f"OT{line_index}"),
            fallback_register_offset=0x04,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        pull_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PUPDR",
            field_names=(f"PUPD{line_index}", f"PUPDR{line_index}"),
            fallback_register_offset=0x0C,
            fallback_bit_offset=line_index * 2,
            fallback_bit_width=2,
        ),
        input_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IDR",
            field_names=(f"IDR{line_index}", f"ID{line_index}"),
            fallback_register_offset=0x10,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_value_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ODR",
            field_names=(f"ODR{line_index}", f"OD{line_index}"),
            fallback_register_offset=0x14,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_set_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BSRR",
            field_names=(f"BS{line_index}",),
            fallback_register_offset=0x18,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_reset_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BSRR",
            field_names=(f"BR{line_index}",),
            fallback_register_offset=0x18,
            fallback_bit_offset=16 + line_index,
            fallback_bit_width=1,
        ),
        pio_enable_field=_invalid_field_ref(),
        pio_output_enable_field=_invalid_field_ref(),
        pio_output_disable_field=_invalid_field_ref(),
        pio_set_field=_invalid_field_ref(),
        pio_clear_field=_invalid_field_ref(),
        pio_input_state_field=_invalid_field_ref(),
        pio_drive_enable_field=_invalid_field_ref(),
        pio_drive_disable_field=_invalid_field_ref(),
        pio_pull_up_enable_field=_invalid_field_ref(),
        pio_pull_up_disable_field=_invalid_field_ref(),
        pio_pull_down_enable_field=_invalid_field_ref(),
        pio_pull_down_disable_field=_invalid_field_ref(),
    )


def _microchip_gpio_semantics(
    context: _SemanticContext,
    *,
    pin_name: str,
    peripheral_name: str,
    schema_id: str,
    line_index: int,
) -> GpioSemanticRow:
    field_name = f"P{line_index}"

    def pio(register_name: str, offset: int) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=offset,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        )

    return GpioSemanticRow(
        pin_name=pin_name,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        line_index=line_index,
        mode_field=_invalid_field_ref(),
        direction_field=_invalid_field_ref(),
        output_type_field=_invalid_field_ref(),
        pull_field=_invalid_field_ref(),
        input_field=_invalid_field_ref(),
        output_value_field=_invalid_field_ref(),
        output_set_field=_invalid_field_ref(),
        output_reset_field=_invalid_field_ref(),
        pio_enable_field=pio("PER", 0x000),
        pio_output_enable_field=pio("OER", 0x010),
        pio_output_disable_field=pio("ODR", 0x014),
        pio_set_field=pio("SODR", 0x030),
        pio_clear_field=pio("CODR", 0x034),
        pio_input_state_field=pio("PDSR", 0x03C),
        pio_drive_enable_field=pio("MDER", 0x050),
        pio_drive_disable_field=pio("MDDR", 0x054),
        pio_pull_up_enable_field=pio("PUER", 0x064),
        pio_pull_up_disable_field=pio("PUDR", 0x060),
        pio_pull_down_enable_field=pio("PPDER", 0x094),
        pio_pull_down_disable_field=pio("PPDDR", 0x090),
    )


def _nxp_gpio_semantics(
    context: _SemanticContext,
    *,
    pin_name: str,
    peripheral_name: str,
    schema_id: str,
    line_index: int,
) -> GpioSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address
    return GpioSemanticRow(
        pin_name=pin_name,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        line_index=line_index,
        mode_field=_invalid_field_ref(base),
        direction_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="GDIR",
            field_names=("DATA", f"IO{line_index:02d}"),
            fallback_register_offset=0x04,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_type_field=_invalid_field_ref(base),
        pull_field=_invalid_field_ref(base),
        input_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PSR",
            field_names=("DATA", f"IO{line_index:02d}"),
            fallback_register_offset=0x08,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_value_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DR",
            field_names=("DATA", f"IO{line_index:02d}"),
            fallback_register_offset=0x00,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_set_field=_invalid_field_ref(base),
        output_reset_field=_invalid_field_ref(base),
        pio_enable_field=_invalid_field_ref(base),
        pio_output_enable_field=_invalid_field_ref(base),
        pio_output_disable_field=_invalid_field_ref(base),
        pio_set_field=_invalid_field_ref(base),
        pio_clear_field=_invalid_field_ref(base),
        pio_input_state_field=_invalid_field_ref(base),
        pio_drive_enable_field=_invalid_field_ref(base),
        pio_drive_disable_field=_invalid_field_ref(base),
        pio_pull_up_enable_field=_invalid_field_ref(base),
        pio_pull_up_disable_field=_invalid_field_ref(base),
        pio_pull_down_enable_field=_invalid_field_ref(base),
        pio_pull_down_disable_field=_invalid_field_ref(base),
    )


def _build_gpio_rows(context: _SemanticContext) -> tuple[GpioSemanticRow, ...]:
    rows: list[GpioSemanticRow] = []
    for pin_name, candidate in sorted(context.gpio_candidate_by_pin.items()):
        peripheral = context.peripheral_by_name.get(candidate.peripheral)
        if peripheral is None or peripheral.backend_schema_id is None:
            continue
        line_index = _line_index_from_candidate(context, candidate)
        if line_index is None:
            continue
        schema_id = peripheral.backend_schema_id
        if schema_id in {
            "alloy.gpio.st-stm32g07x-gpio-v1-0",
            "alloy.gpio.st-stm32f4x-gpio-v1-0",
        }:
            rows.append(
                _st_gpio_semantics(
                    context,
                    pin_name=pin_name,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    line_index=line_index,
                )
            )
        elif schema_id == "alloy.gpio.microchip-pio-v":
            rows.append(
                _microchip_gpio_semantics(
                    context,
                    pin_name=pin_name,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    line_index=line_index,
                )
            )
        elif schema_id == "alloy.gpio.nxp-imxrt-gpio-v1":
            rows.append(
                _nxp_gpio_semantics(
                    context,
                    pin_name=pin_name,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    line_index=line_index,
                )
            )
    return tuple(rows)


def _microchip_uart_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
    usart_prefix: str = "",
) -> UartSemanticRow:
    prefix = usart_prefix

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str, field_name: str, offset: int, bit_offset: int, bit_width: int = 1
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(context.peripheral_by_name[peripheral_name].base_address)
    empty_field = _invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address)
    is_usart = bool(prefix)
    return UartSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=empty_reg,
        brr_reg=empty_reg,
        isr_reg=empty_reg,
        rdr_reg=empty_reg,
        tdr_reg=empty_reg,
        sr_reg=empty_reg,
        dr_reg=empty_reg,
        cr_reg=reg(f"{prefix}CR" if is_usart else "CR", 0x00),
        mr_reg=reg(f"{prefix}MR" if is_usart else "MR", 0x04),
        brgr_reg=reg(f"{prefix}BRGR" if is_usart else "BRGR", 0x20 if is_usart else 0x20),
        thr_reg=reg(f"{prefix}THR" if is_usart else "THR", 0x1C),
        us_cr_reg=reg("US_CR_LIN_MODE", 0x00) if is_usart else empty_reg,
        us_mr_reg=reg("US_MR_SPI_MODE", 0x04) if is_usart else empty_reg,
        us_brgr_reg=reg("US_BRGR", 0x20) if is_usart else empty_reg,
        us_thr_reg=reg("US_THR", 0x1C) if is_usart else empty_reg,
        ue_field=empty_field,
        re_field=empty_field,
        te_field=empty_field,
        pce_field=empty_field,
        ps_field=empty_field,
        m0_field=empty_field,
        m1_field=empty_field,
        m_field=empty_field,
        stop_field=empty_field,
        tdr_field=empty_field,
        rdr_field=empty_field,
        txe_isr_field=empty_field,
        rxne_isr_field=empty_field,
        tc_isr_field=empty_field,
        txe_sr_field=empty_field,
        rxne_sr_field=empty_field,
        tc_sr_field=empty_field,
        dr_field=empty_field,
        rstrx_field=field("CR", "RSTRX", 0x00, 2) if not is_usart else empty_field,
        rsttx_field=field("CR", "RSTTX", 0x00, 3) if not is_usart else empty_field,
        rxdis_field=field("CR", "RXDIS", 0x00, 5) if not is_usart else empty_field,
        txdis_field=field("CR", "TXDIS", 0x00, 7) if not is_usart else empty_field,
        rststa_field=field("CR", "RSTSTA", 0x00, 8) if not is_usart else empty_field,
        par_field=field("MR", "PAR", 0x04, 9, 3) if not is_usart else empty_field,
        chmode_field=field("MR", "CHMODE", 0x04, 14, 2) if not is_usart else empty_field,
        cd_field=field("BRGR", "CD", 0x20, 0, 16) if not is_usart else empty_field,
        rxen_field=field("CR", "RXEN", 0x00, 4) if not is_usart else empty_field,
        txen_field=field("CR", "TXEN", 0x00, 6) if not is_usart else empty_field,
        txrdy_field=field("SR", "TXRDY", 0x14, 1) if not is_usart else empty_field,
        rxrdy_field=field("SR", "RXRDY", 0x14, 0) if not is_usart else empty_field,
        txempty_field=field("SR", "TXEMPTY", 0x14, 9) if not is_usart else empty_field,
        txchr_field=field("THR", "TXCHR", 0x1C, 0, 9) if not is_usart else empty_field,
        rxchr_field=field("RHR", "RXCHR", 0x18, 0, 9) if not is_usart else empty_field,
        us_rstrx_field=field("US_CR_LIN_MODE", "RSTRX", 0x00, 2) if is_usart else empty_field,
        us_rsttx_field=field("US_CR_LIN_MODE", "RSTTX", 0x00, 3) if is_usart else empty_field,
        us_rxdis_field=field("US_CR_LIN_MODE", "RXDIS", 0x00, 5) if is_usart else empty_field,
        us_txdis_field=field("US_CR_LIN_MODE", "TXDIS", 0x00, 7) if is_usart else empty_field,
        us_rststa_field=field("US_CR_LIN_MODE", "RSTSTA", 0x00, 8) if is_usart else empty_field,
        us_usart_mode_field=field("US_MR_SPI_MODE", "USART_MODE", 0x04, 0, 4)
        if is_usart
        else empty_field,
        us_usclks_field=field("US_MR_SPI_MODE", "USCLKS", 0x04, 4, 2) if is_usart else empty_field,
        us_chrl_field=field("US_MR_SPI_MODE", "CHRL", 0x04, 6, 2) if is_usart else empty_field,
        us_cd_field=field("US_BRGR", "CD", 0x20, 0, 16) if is_usart else empty_field,
        us_rxen_field=field("US_CR_LIN_MODE", "RXEN", 0x00, 4) if is_usart else empty_field,
        us_txen_field=field("US_CR_LIN_MODE", "TXEN", 0x00, 6) if is_usart else empty_field,
        us_txrdy_field=field("US_CSR_LIN_MODE", "TXRDY", 0x14, 1) if is_usart else empty_field,
        us_rxrdy_field=field("US_CSR_LIN_MODE", "RXRDY", 0x14, 0) if is_usart else empty_field,
        us_txempty_field=field("US_CSR_LIN_MODE", "TXEMPTY", 0x14, 9) if is_usart else empty_field,
        us_txchr_field=field("US_THR", "TXCHR", 0x1C, 0, 9) if is_usart else empty_field,
        us_rxchr_field=field("US_RHR", "RXCHR", 0x18, 0, 9) if is_usart else empty_field,
    )


def _st_uart_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
    f4_layout: bool,
) -> UartSemanticRow:
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
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return UartSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=reg("CR1", 0x0C if f4_layout else 0x00),
        cr2_reg=reg("CR2", 0x10 if f4_layout else 0x04),
        brr_reg=reg("BRR", 0x08 if f4_layout else 0x0C),
        isr_reg=reg("ISR", 0x1C) if not f4_layout else empty_reg,
        rdr_reg=reg("RDR", 0x24) if not f4_layout else empty_reg,
        tdr_reg=reg("TDR", 0x28) if not f4_layout else empty_reg,
        sr_reg=reg("SR", 0x00) if f4_layout else empty_reg,
        dr_reg=reg("DR", 0x04) if f4_layout else empty_reg,
        cr_reg=empty_reg,
        mr_reg=empty_reg,
        brgr_reg=empty_reg,
        thr_reg=empty_reg,
        us_cr_reg=empty_reg,
        us_mr_reg=empty_reg,
        us_brgr_reg=empty_reg,
        us_thr_reg=empty_reg,
        ue_field=field("CR1", ("UE",), 0x0C if f4_layout else 0x00, 0),
        re_field=field("CR1", ("RE",), 0x0C if f4_layout else 0x00, 2),
        te_field=field("CR1", ("TE",), 0x0C if f4_layout else 0x00, 3),
        pce_field=field("CR1", ("PCE",), 0x0C if f4_layout else 0x00, 10),
        ps_field=field("CR1", ("PS",), 0x0C if f4_layout else 0x00, 9),
        m0_field=field("CR1", ("M0",), 0x00, 12) if not f4_layout else empty_field,
        m1_field=field("CR1", ("M1",), 0x00, 28) if not f4_layout else empty_field,
        m_field=field("CR1", ("M",), 0x0C, 12) if f4_layout else empty_field,
        stop_field=field("CR2", ("STOP",), 0x10 if f4_layout else 0x04, 12, 2),
        tdr_field=field("TDR", ("TDR", "TXDATA"), 0x28, 0, 9) if not f4_layout else empty_field,
        rdr_field=field("RDR", ("RDR", "RXDATA"), 0x24, 0, 9) if not f4_layout else empty_field,
        txe_isr_field=field("ISR", ("TXE_TXFNF", "TXE"), 0x1C, 7) if not f4_layout else empty_field,
        rxne_isr_field=field("ISR", ("RXNE_RXFNE", "RXNE"), 0x1C, 5)
        if not f4_layout
        else empty_field,
        tc_isr_field=field("ISR", ("TC",), 0x1C, 6) if not f4_layout else empty_field,
        txe_sr_field=field("SR", ("TXE",), 0x00, 7) if f4_layout else empty_field,
        rxne_sr_field=field("SR", ("RXNE",), 0x00, 5) if f4_layout else empty_field,
        tc_sr_field=field("SR", ("TC",), 0x00, 6) if f4_layout else empty_field,
        dr_field=field("DR", ("DR",), 0x04, 0, 9) if f4_layout else empty_field,
        rstrx_field=empty_field,
        rsttx_field=empty_field,
        rxdis_field=empty_field,
        txdis_field=empty_field,
        rststa_field=empty_field,
        par_field=empty_field,
        chmode_field=empty_field,
        cd_field=empty_field,
        rxen_field=empty_field,
        txen_field=empty_field,
        txrdy_field=empty_field,
        rxrdy_field=empty_field,
        txempty_field=empty_field,
        txchr_field=empty_field,
        rxchr_field=empty_field,
        us_rstrx_field=empty_field,
        us_rsttx_field=empty_field,
        us_rxdis_field=empty_field,
        us_txdis_field=empty_field,
        us_rststa_field=empty_field,
        us_usart_mode_field=empty_field,
        us_usclks_field=empty_field,
        us_chrl_field=empty_field,
        us_cd_field=empty_field,
        us_rxen_field=empty_field,
        us_txen_field=empty_field,
        us_txrdy_field=empty_field,
        us_rxrdy_field=empty_field,
        us_txempty_field=empty_field,
        us_txchr_field=empty_field,
        us_rxchr_field=empty_field,
    )


def _nxp_uart_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> UartSemanticRow:
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
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return UartSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=empty_reg,
        brr_reg=empty_reg,
        isr_reg=empty_reg,
        rdr_reg=empty_reg,
        tdr_reg=empty_reg,
        sr_reg=empty_reg,
        dr_reg=empty_reg,
        cr_reg=empty_reg,
        mr_reg=empty_reg,
        brgr_reg=empty_reg,
        thr_reg=empty_reg,
        us_cr_reg=empty_reg,
        us_mr_reg=empty_reg,
        us_brgr_reg=empty_reg,
        us_thr_reg=empty_reg,
        ue_field=field("CTRL", ("UARTEN",), 0x18, 0),
        re_field=field("CTRL", ("RE",), 0x18, 18),
        te_field=field("CTRL", ("TE",), 0x18, 19),
        pce_field=field("CTRL", ("PE",), 0x18, 1),
        ps_field=field("CTRL", ("PT",), 0x18, 0),
        m0_field=empty_field,
        m1_field=empty_field,
        m_field=field("CTRL", ("M", "M7"), 0x18, 4),
        stop_field=field("BAUD", ("SBNS",), 0x10, 13),
        tdr_field=field("DATA", ("TDATA", "DATA"), 0x1C, 0, 10),
        rdr_field=field("DATA", ("RDATA", "DATA"), 0x1C, 0, 10),
        txe_isr_field=field("STAT", ("TDRE",), 0x14, 23),
        rxne_isr_field=field("STAT", ("RDRF",), 0x14, 21),
        tc_isr_field=field("STAT", ("TC",), 0x14, 22),
        txe_sr_field=empty_field,
        rxne_sr_field=empty_field,
        tc_sr_field=empty_field,
        dr_field=empty_field,
        rstrx_field=empty_field,
        rsttx_field=empty_field,
        rxdis_field=empty_field,
        txdis_field=empty_field,
        rststa_field=empty_field,
        par_field=empty_field,
        chmode_field=empty_field,
        cd_field=field("BAUD", ("SBR",), 0x10, 0, 13),
        rxen_field=empty_field,
        txen_field=empty_field,
        txrdy_field=empty_field,
        rxrdy_field=empty_field,
        txempty_field=empty_field,
        txchr_field=empty_field,
        rxchr_field=empty_field,
        us_rstrx_field=empty_field,
        us_rsttx_field=empty_field,
        us_rxdis_field=empty_field,
        us_txdis_field=empty_field,
        us_rststa_field=empty_field,
        us_usart_mode_field=empty_field,
        us_usclks_field=empty_field,
        us_chrl_field=empty_field,
        us_cd_field=empty_field,
        us_rxen_field=empty_field,
        us_txen_field=empty_field,
        us_txrdy_field=empty_field,
        us_rxrdy_field=empty_field,
        us_txempty_field=empty_field,
        us_txchr_field=empty_field,
        us_rxchr_field=empty_field,
    )


def _build_uart_rows(context: _SemanticContext) -> tuple[UartSemanticRow, ...]:
    # Hardware-feature lookup added by ``fill-espressif-semantic-gaps``: a
    # stub row whose peripheral has a ``UartPeripheralDescriptor`` is
    # promoted out of stub status so it lands in ``kUartSemanticPeripherals``
    # (consumers iterating the array see hardware-feature-only entries).
    uart_hw_ids = {u.peripheral_id for u in context.device.uart_peripherals}

    def _has_register(peripheral_name: str, register_name: str) -> bool:
        return (peripheral_name, register_name.upper()) in context.register_by_key

    def _st_uart_uses_f4_layout(peripheral: PeripheralInstance) -> bool:
        schema_id = (peripheral.backend_schema_id or "").lower()
        ip_version = (peripheral.ip_version or "").lower()
        tokens = (schema_id, ip_version)
        if any("sci2" in token or "usart-f4" in token or "usart_f4" in token for token in tokens):
            return True
        if any("sci3" in token or "usart-v3" in token or "usart_v3" in token for token in tokens):
            return False
        has_isr_style = any(
            _has_register(peripheral.name, register_name) for register_name in ("ISR", "RDR", "TDR")
        )
        if has_isr_style:
            return False
        has_sr_style = _has_register(peripheral.name, "SR") and _has_register(peripheral.name, "DR")
        if has_sr_style:
            return True
        return False

    rows: list[UartSemanticRow] = []
    candidate_peripherals = list(context.candidate_peripherals_by_class.get("uart", ()))
    candidate_names = {p.name for p in candidate_peripherals}
    for peripheral in sorted(context.device.peripherals, key=lambda item: item.name):
        if peripheral.name in uart_hw_ids and peripheral.name not in candidate_names:
            candidate_peripherals.append(peripheral)
    for peripheral in candidate_peripherals:
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.uart.st-"):
            rows.append(
                _st_uart_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    f4_layout=_st_uart_uses_f4_layout(peripheral),
                )
            )
        elif schema_id == "alloy.uart.microchip-uart-r":
            rows.append(
                _microchip_uart_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id == "alloy.uart.microchip-usart-zw":
            rows.append(
                _microchip_uart_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    usart_prefix="US_",
                )
            )
        elif schema_id == "alloy.uart.nxp-lpuart-v1":
            rows.append(
                _nxp_uart_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (UartSemanticTraits<PeripheralId::) is satisfied for devices whose
            # UART IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            rows.append(
                UartSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    cr1_reg=invalid_reg,
                    cr2_reg=invalid_reg,
                    brr_reg=invalid_reg,
                    isr_reg=invalid_reg,
                    rdr_reg=invalid_reg,
                    tdr_reg=invalid_reg,
                    sr_reg=invalid_reg,
                    dr_reg=invalid_reg,
                    cr_reg=invalid_reg,
                    mr_reg=invalid_reg,
                    brgr_reg=invalid_reg,
                    thr_reg=invalid_reg,
                    us_cr_reg=invalid_reg,
                    us_mr_reg=invalid_reg,
                    us_brgr_reg=invalid_reg,
                    us_thr_reg=invalid_reg,
                    ue_field=invalid_field,
                    re_field=invalid_field,
                    te_field=invalid_field,
                    pce_field=invalid_field,
                    ps_field=invalid_field,
                    m0_field=invalid_field,
                    m1_field=invalid_field,
                    m_field=invalid_field,
                    stop_field=invalid_field,
                    tdr_field=invalid_field,
                    rdr_field=invalid_field,
                    txe_isr_field=invalid_field,
                    rxne_isr_field=invalid_field,
                    tc_isr_field=invalid_field,
                    txe_sr_field=invalid_field,
                    rxne_sr_field=invalid_field,
                    tc_sr_field=invalid_field,
                    dr_field=invalid_field,
                    rstrx_field=invalid_field,
                    rsttx_field=invalid_field,
                    rxdis_field=invalid_field,
                    txdis_field=invalid_field,
                    rststa_field=invalid_field,
                    par_field=invalid_field,
                    chmode_field=invalid_field,
                    cd_field=invalid_field,
                    rxen_field=invalid_field,
                    txen_field=invalid_field,
                    txrdy_field=invalid_field,
                    rxrdy_field=invalid_field,
                    txempty_field=invalid_field,
                    txchr_field=invalid_field,
                    rxchr_field=invalid_field,
                    us_rstrx_field=invalid_field,
                    us_rsttx_field=invalid_field,
                    us_rxdis_field=invalid_field,
                    us_txdis_field=invalid_field,
                    us_rststa_field=invalid_field,
                    us_usart_mode_field=invalid_field,
                    us_usclks_field=invalid_field,
                    us_chrl_field=invalid_field,
                    us_cd_field=invalid_field,
                    us_rxen_field=invalid_field,
                    us_txen_field=invalid_field,
                    us_txrdy_field=invalid_field,
                    us_rxrdy_field=invalid_field,
                    us_txempty_field=invalid_field,
                    us_txchr_field=invalid_field,
                    us_rxchr_field=invalid_field,
                    is_stub=peripheral.name not in uart_hw_ids,
                )
            )
    return tuple(rows)


def _st_i2c_v1_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str, field_name: str, reg_offset: int, bit_offset: int, bit_width: int = 1
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=reg("CR1", 0x00),
        cr2_reg=reg("CR2", 0x04),
        ccr_reg=reg("CCR", 0x1C),
        trise_reg=reg("TRISE", 0x20),
        sr1_reg=reg("SR1", 0x14),
        sr2_reg=reg("SR2", 0x18),
        dr_reg=reg("DR", 0x10),
        icr_reg=empty_reg,
        cr_reg=empty_reg,
        mmr_reg=empty_reg,
        iadr_reg=empty_reg,
        cwgr_reg=empty_reg,
        sr_reg=empty_reg,
        rhr_reg=empty_reg,
        thr_reg=empty_reg,
        pe_field=field("CR1", "PE", 0x00, 0),
        ack_field=field("CR1", "ACK", 0x00, 10),
        start_field=field("CR1", "START", 0x00, 8),
        stop_field=field("CR1", "STOP", 0x00, 9),
        freq_field=field("CR2", "FREQ", 0x04, 0, 6),
        ccr_field=field("CCR", "CCR", 0x1C, 0, 12),
        fs_field=field("CCR", "F_S", 0x1C, 15),
        duty_field=field("CCR", "DUTY", 0x1C, 14),
        trise_field=field("TRISE", "TRISE", 0x20, 0, 6),
        sb_field=field("SR1", "SB", 0x14, 0),
        addr_field=field("SR1", "ADDR", 0x14, 1),
        txe_field=field("SR1", "TxE", 0x14, 7),
        rxne_field=field("SR1", "RxNE", 0x14, 6),
        btf_field=field("SR1", "BTF", 0x14, 2),
        af_field=field("SR1", "AF", 0x14, 10),
        berr_field=field("SR1", "BERR", 0x14, 8),
        arlo_field=field("SR1", "ARLO", 0x14, 9),
        busy_field=field("SR2", "BUSY", 0x18, 1),
        dr_data_field=field("DR", "DR", 0x10, 0, 8),
        sadd_field=empty_field,
        rd_wrn_field=empty_field,
        nbytes_field=empty_field,
        autoend_field=empty_field,
        txis_field=empty_field,
        tc_field=empty_field,
        stopf_field=empty_field,
        txdata_field=empty_field,
        rxdata_field=empty_field,
        nackf_field=empty_field,
        berr_isr_field=empty_field,
        arlo_isr_field=empty_field,
        stopcf_field=empty_field,
        nackcf_field=empty_field,
        berrcf_field=empty_field,
        arlocf_field=empty_field,
        msen_field=empty_field,
        msdis_field=empty_field,
        svdis_field=empty_field,
        swrst_field=empty_field,
        iadrsz_field=empty_field,
        mread_field=empty_field,
        dadr_field=empty_field,
        iadr_field=empty_field,
        cldiv_field=empty_field,
        chdiv_field=empty_field,
        ckdiv_field=empty_field,
        hold_field=empty_field,
        txcomp_field=empty_field,
        rxrdy_field=empty_field,
        txrdy_field=empty_field,
        nack_field=empty_field,
        arblst_field=empty_field,
    )


def _st_i2c_v2_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=reg("CR2", 0x04),
        ccr_reg=empty_reg,
        trise_reg=empty_reg,
        sr1_reg=empty_reg,
        sr2_reg=empty_reg,
        dr_reg=empty_reg,
        icr_reg=reg("ICR", 0x20),
        cr_reg=empty_reg,
        mmr_reg=empty_reg,
        iadr_reg=empty_reg,
        cwgr_reg=empty_reg,
        sr_reg=empty_reg,
        rhr_reg=empty_reg,
        thr_reg=empty_reg,
        pe_field=empty_field,
        ack_field=empty_field,
        start_field=field("CR2", ("START",), 0x04, 13),
        stop_field=empty_field,
        freq_field=empty_field,
        ccr_field=empty_field,
        fs_field=empty_field,
        duty_field=empty_field,
        trise_field=empty_field,
        sb_field=empty_field,
        addr_field=empty_field,
        txe_field=empty_field,
        rxne_field=empty_field,
        btf_field=empty_field,
        af_field=empty_field,
        berr_field=empty_field,
        arlo_field=empty_field,
        busy_field=empty_field,
        dr_data_field=empty_field,
        sadd_field=field("CR2", ("SADD",), 0x04, 0, 10),
        rd_wrn_field=field("CR2", ("RD_WRN",), 0x04, 10),
        nbytes_field=field("CR2", ("NBYTES",), 0x04, 16, 8),
        autoend_field=field("CR2", ("AUTOEND",), 0x04, 25),
        txis_field=field("ISR", ("TXIS",), 0x1C, 1),
        tc_field=field("ISR", ("TC",), 0x1C, 6),
        stopf_field=field("ISR", ("STOPF",), 0x1C, 5),
        txdata_field=field("TXDR", ("TXDATA",), 0x28, 0, 8),
        rxdata_field=field("RXDR", ("RXDATA",), 0x24, 0, 8),
        nackf_field=field("ISR", ("NACKF",), 0x1C, 4),
        berr_isr_field=field("ISR", ("BERR",), 0x1C, 8),
        arlo_isr_field=field("ISR", ("ARLO",), 0x1C, 9),
        stopcf_field=field("ICR", ("STOPCF",), 0x20, 5),
        nackcf_field=field("ICR", ("NACKCF",), 0x20, 4),
        berrcf_field=field("ICR", ("BERRCF",), 0x20, 8),
        arlocf_field=field("ICR", ("ARLOCF",), 0x20, 9),
        msen_field=empty_field,
        msdis_field=empty_field,
        svdis_field=empty_field,
        swrst_field=empty_field,
        iadrsz_field=empty_field,
        mread_field=empty_field,
        dadr_field=empty_field,
        iadr_field=empty_field,
        cldiv_field=empty_field,
        chdiv_field=empty_field,
        ckdiv_field=empty_field,
        hold_field=empty_field,
        txcomp_field=empty_field,
        rxrdy_field=empty_field,
        txrdy_field=empty_field,
        nack_field=empty_field,
        arblst_field=empty_field,
    )


def _microchip_i2c_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str, field_name: str, reg_offset: int, bit_offset: int, bit_width: int = 1
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=empty_reg,
        ccr_reg=empty_reg,
        trise_reg=empty_reg,
        sr1_reg=empty_reg,
        sr2_reg=empty_reg,
        dr_reg=empty_reg,
        icr_reg=empty_reg,
        cr_reg=reg("CR", 0x00),
        mmr_reg=reg("MMR", 0x04),
        iadr_reg=reg("IADR", 0x0C),
        cwgr_reg=reg("CWGR", 0x10),
        sr_reg=reg("SR", 0x20),
        rhr_reg=reg("RHR", 0x30),
        thr_reg=reg("THR", 0x34),
        pe_field=empty_field,
        ack_field=empty_field,
        # TWIHS CR is a write-only "action" register: writing START=1 issues
        # a START condition, writing STOP=1 issues a STOP, and the bits are
        # self-clearing. Expose them as bit-0/bit-1 single-bit fields so the
        # HAL backend can drive them through rt::write_register(cr, ...) /
        # rt::modify_field(start/stop, 1u) instead of typing raw masks.
        start_field=field("CR", "START", 0x00, 0),
        stop_field=field("CR", "STOP", 0x00, 1),
        freq_field=empty_field,
        ccr_field=empty_field,
        fs_field=empty_field,
        duty_field=empty_field,
        trise_field=empty_field,
        sb_field=empty_field,
        addr_field=empty_field,
        txe_field=empty_field,
        rxne_field=empty_field,
        btf_field=empty_field,
        af_field=empty_field,
        berr_field=empty_field,
        arlo_field=empty_field,
        busy_field=empty_field,
        dr_data_field=empty_field,
        sadd_field=empty_field,
        rd_wrn_field=empty_field,
        nbytes_field=empty_field,
        autoend_field=empty_field,
        txis_field=empty_field,
        tc_field=empty_field,
        stopf_field=empty_field,
        txdata_field=field("THR", "TXDATA", 0x34, 0, 8),
        rxdata_field=field("RHR", "RXDATA", 0x30, 0, 8),
        nackf_field=empty_field,
        berr_isr_field=empty_field,
        arlo_isr_field=empty_field,
        stopcf_field=empty_field,
        nackcf_field=empty_field,
        berrcf_field=empty_field,
        arlocf_field=empty_field,
        msen_field=field("CR", "MSEN", 0x00, 2),
        msdis_field=field("CR", "MSDIS", 0x00, 3),
        svdis_field=field("CR", "SVDIS", 0x00, 5),
        swrst_field=field("CR", "SWRST", 0x00, 7),
        iadrsz_field=field("MMR", "IADRSZ", 0x04, 8, 2),
        mread_field=field("MMR", "MREAD", 0x04, 12),
        dadr_field=field("MMR", "DADR", 0x04, 16, 7),
        iadr_field=field("IADR", "IADR", 0x0C, 0, 24),
        cldiv_field=field("CWGR", "CLDIV", 0x10, 0, 8),
        chdiv_field=field("CWGR", "CHDIV", 0x10, 8, 8),
        ckdiv_field=field("CWGR", "CKDIV", 0x10, 16, 3),
        hold_field=field("CWGR", "HOLD", 0x10, 24, 5),
        txcomp_field=field("SR", "TXCOMP", 0x20, 0),
        rxrdy_field=field("SR", "RXRDY", 0x20, 1),
        txrdy_field=field("SR", "TXRDY", 0x20, 2),
        nack_field=field("SR", "NACK", 0x20, 8),
        arblst_field=field("SR", "ARBLST", 0x20, 9),
    )


def _nxp_i2c_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=empty_reg,
        ccr_reg=empty_reg,
        trise_reg=empty_reg,
        sr1_reg=empty_reg,
        sr2_reg=empty_reg,
        dr_reg=empty_reg,
        icr_reg=empty_reg,
        cr_reg=reg("MCR", 0x10),
        mmr_reg=reg("MCFGR1", 0x24),
        iadr_reg=empty_reg,
        cwgr_reg=reg("MCCR0", 0x48),
        sr_reg=reg("MSR", 0x14),
        rhr_reg=reg("MRDR", 0x70),
        thr_reg=reg("MTDR", 0x60),
        pe_field=empty_field,
        ack_field=empty_field,
        start_field=field("MTDR", ("CMD",), 0x60, 8, 3),
        stop_field=field("MTDR", ("CMD",), 0x60, 8, 3),
        freq_field=field("MCFGR1", ("PRESCALE",), 0x24, 8, 3),
        ccr_field=empty_field,
        fs_field=empty_field,
        duty_field=empty_field,
        trise_field=empty_field,
        sb_field=empty_field,
        addr_field=empty_field,
        txe_field=empty_field,
        rxne_field=empty_field,
        btf_field=empty_field,
        af_field=empty_field,
        berr_field=empty_field,
        arlo_field=empty_field,
        busy_field=field("MSR", ("BBF",), 0x14, 25),
        dr_data_field=empty_field,
        sadd_field=field("MTDR", ("DATA",), 0x60, 0, 8),
        rd_wrn_field=empty_field,
        nbytes_field=empty_field,
        autoend_field=empty_field,
        txis_field=field("MSR", ("TDF",), 0x14, 0),
        tc_field=field("MSR", ("SDF",), 0x14, 9),
        stopf_field=field("MSR", ("SDF",), 0x14, 9),
        txdata_field=field("MTDR", ("DATA",), 0x60, 0, 8),
        rxdata_field=field("MRDR", ("DATA",), 0x70, 0, 8),
        nackf_field=field("MSR", ("NDF",), 0x14, 10),
        berr_isr_field=field("MSR", ("FEF",), 0x14, 12),
        arlo_isr_field=field("MSR", ("ALF",), 0x14, 11),
        stopcf_field=empty_field,
        nackcf_field=empty_field,
        berrcf_field=empty_field,
        arlocf_field=empty_field,
        msen_field=field("MCR", ("MEN",), 0x10, 0),
        msdis_field=empty_field,
        svdis_field=empty_field,
        swrst_field=field("MCR", ("RST",), 0x10, 1),
        iadrsz_field=empty_field,
        mread_field=empty_field,
        dadr_field=empty_field,
        iadr_field=empty_field,
        cldiv_field=field("MCCR0", ("CLKLO",), 0x48, 0, 6),
        chdiv_field=field("MCCR0", ("CLKHI",), 0x48, 8, 6),
        ckdiv_field=field("MCFGR1", ("PRESCALE",), 0x24, 8, 3),
        hold_field=field("MCCR0", ("SETHOLD",), 0x48, 16, 6),
        txcomp_field=field("MSR", ("SDF",), 0x14, 9),
        rxrdy_field=field("MSR", ("RDF",), 0x14, 1),
        txrdy_field=field("MSR", ("TDF",), 0x14, 0),
        nack_field=field("MSR", ("NDF",), 0x14, 10),
        arblst_field=field("MSR", ("ALF",), 0x14, 11),
    )


def _build_i2c_rows(context: _SemanticContext) -> tuple[I2cSemanticRow, ...]:
    rows: list[I2cSemanticRow] = []
    for peripheral in context.candidate_peripherals_by_class.get("i2c", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.i2c.st-") and "v1-5" in schema_id:
            rows.append(
                _st_i2c_v1_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id.startswith("alloy.i2c.st-"):
            rows.append(
                _st_i2c_v2_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id == "alloy.i2c.microchip-twihs-z":
            rows.append(
                _microchip_i2c_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id == "alloy.lpi2c1.nxp-lpi2c-v1":
            rows.append(_nxp_i2c_row(context, peripheral_name=peripheral.name, schema_id=schema_id))
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (I2cSemanticTraits<PeripheralId::) is satisfied for devices whose
            # I2C IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            rows.append(
                I2cSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    cr1_reg=invalid_reg,
                    cr2_reg=invalid_reg,
                    ccr_reg=invalid_reg,
                    trise_reg=invalid_reg,
                    sr1_reg=invalid_reg,
                    sr2_reg=invalid_reg,
                    dr_reg=invalid_reg,
                    icr_reg=invalid_reg,
                    cr_reg=invalid_reg,
                    mmr_reg=invalid_reg,
                    iadr_reg=invalid_reg,
                    cwgr_reg=invalid_reg,
                    sr_reg=invalid_reg,
                    rhr_reg=invalid_reg,
                    thr_reg=invalid_reg,
                    pe_field=invalid_field,
                    ack_field=invalid_field,
                    start_field=invalid_field,
                    stop_field=invalid_field,
                    freq_field=invalid_field,
                    ccr_field=invalid_field,
                    fs_field=invalid_field,
                    duty_field=invalid_field,
                    trise_field=invalid_field,
                    sb_field=invalid_field,
                    addr_field=invalid_field,
                    txe_field=invalid_field,
                    rxne_field=invalid_field,
                    btf_field=invalid_field,
                    af_field=invalid_field,
                    berr_field=invalid_field,
                    arlo_field=invalid_field,
                    busy_field=invalid_field,
                    dr_data_field=invalid_field,
                    sadd_field=invalid_field,
                    rd_wrn_field=invalid_field,
                    nbytes_field=invalid_field,
                    autoend_field=invalid_field,
                    txis_field=invalid_field,
                    tc_field=invalid_field,
                    stopf_field=invalid_field,
                    txdata_field=invalid_field,
                    rxdata_field=invalid_field,
                    nackf_field=invalid_field,
                    berr_isr_field=invalid_field,
                    arlo_isr_field=invalid_field,
                    stopcf_field=invalid_field,
                    nackcf_field=invalid_field,
                    berrcf_field=invalid_field,
                    arlocf_field=invalid_field,
                    msen_field=invalid_field,
                    msdis_field=invalid_field,
                    svdis_field=invalid_field,
                    swrst_field=invalid_field,
                    iadrsz_field=invalid_field,
                    mread_field=invalid_field,
                    dadr_field=invalid_field,
                    iadr_field=invalid_field,
                    cldiv_field=invalid_field,
                    chdiv_field=invalid_field,
                    ckdiv_field=invalid_field,
                    hold_field=invalid_field,
                    txcomp_field=invalid_field,
                    rxrdy_field=invalid_field,
                    txrdy_field=invalid_field,
                    nack_field=invalid_field,
                    arblst_field=invalid_field,
                    is_stub=True,
                )
            )
    return tuple(rows)


def _st_spi_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> SpiSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return SpiSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=reg("CR1", 0x00),
        cr2_reg=reg("CR2", 0x04),
        sr_reg=reg("SR", 0x08),
        dr_reg=reg("DR", 0x0C),
        cr_reg=_invalid_register_ref(base),
        mr_reg=_invalid_register_ref(base),
        csr_reg=_invalid_register_ref(base),
        tdr_reg=_invalid_register_ref(base),
        rdr_reg=_invalid_register_ref(base),
        cpha_field=field("CR1", ("CPHA",), 0x00, 0),
        cpol_field=field("CR1", ("CPOL",), 0x00, 1),
        mstr_field=field("CR1", ("MSTR",), 0x00, 2),
        br_field=field("CR1", ("BR",), 0x00, 3, 3),
        spe_field=field("CR1", ("SPE",), 0x00, 6),
        lsbfirst_field=field("CR1", ("LSBFIRST",), 0x00, 7),
        ssi_field=field("CR1", ("SSI",), 0x00, 8),
        ssm_field=field("CR1", ("SSM",), 0x00, 9),
        dff_field=field("CR1", ("DFF",), 0x00, 11),
        ds_field=field("CR2", ("DS",), 0x04, 8, 4),
        frxth_field=field("CR2", ("FRXTH",), 0x04, 12),
        txe_field=field("SR", ("TXE",), 0x08, 1),
        rxne_field=field("SR", ("RXNE",), 0x08, 0),
        bsy_field=field("SR", ("BSY",), 0x08, 7),
        dr_data_field=field("DR", ("DR",), 0x0C, 0, 16),
        spien_field=_invalid_field_ref(base),
        spidis_field=_invalid_field_ref(base),
        swrst_field=_invalid_field_ref(base),
        ps_field=_invalid_field_ref(base),
        pcsdec_field=_invalid_field_ref(base),
        modfdis_field=_invalid_field_ref(base),
        pcs_field=_invalid_field_ref(base),
        dlybcs_field=_invalid_field_ref(base),
        ncpha_field=_invalid_field_ref(base),
        bits_field=_invalid_field_ref(base),
        scbr_field=_invalid_field_ref(base),
        dlybs_field=_invalid_field_ref(base),
        dlybct_field=_invalid_field_ref(base),
        tdre_field=_invalid_field_ref(base),
        rdrf_field=_invalid_field_ref(base),
        txempty_field=_invalid_field_ref(base),
        td_field=_invalid_field_ref(base),
        tdr_pcs_field=_invalid_field_ref(base),
        rd_field=_invalid_field_ref(base),
    )


def _microchip_spi_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> SpiSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str, field_name: str, reg_offset: int, bit_offset: int, bit_width: int = 1
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return SpiSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=_invalid_register_ref(base),
        cr2_reg=_invalid_register_ref(base),
        sr_reg=reg("SR", 0x10),
        dr_reg=_invalid_register_ref(base),
        cr_reg=reg("CR", 0x00),
        mr_reg=reg("MR", 0x04),
        csr_reg=reg("CSR[%s]", 0x30),
        tdr_reg=reg("TDR", 0x0C),
        rdr_reg=reg("RDR", 0x08),
        cpha_field=_invalid_field_ref(base),
        cpol_field=field("CSR[%s]", "CPOL", 0x30, 0),
        mstr_field=field("MR", "MSTR", 0x04, 0),
        br_field=_invalid_field_ref(base),
        spe_field=_invalid_field_ref(base),
        lsbfirst_field=_invalid_field_ref(base),
        ssi_field=_invalid_field_ref(base),
        ssm_field=_invalid_field_ref(base),
        dff_field=_invalid_field_ref(base),
        ds_field=_invalid_field_ref(base),
        frxth_field=_invalid_field_ref(base),
        txe_field=_invalid_field_ref(base),
        rxne_field=_invalid_field_ref(base),
        bsy_field=_invalid_field_ref(base),
        dr_data_field=_invalid_field_ref(base),
        spien_field=field("CR", "SPIEN", 0x00, 0),
        spidis_field=field("CR", "SPIDIS", 0x00, 1),
        swrst_field=field("CR", "SWRST", 0x00, 7),
        ps_field=field("MR", "PS", 0x04, 1),
        pcsdec_field=field("MR", "PCSDEC", 0x04, 2),
        modfdis_field=field("MR", "MODFDIS", 0x04, 4),
        pcs_field=field("MR", "PCS", 0x04, 16, 4),
        dlybcs_field=field("MR", "DLYBCS", 0x04, 24, 8),
        ncpha_field=field("CSR[%s]", "NCPHA", 0x30, 1),
        bits_field=field("CSR[%s]", "BITS", 0x30, 4, 4),
        scbr_field=field("CSR[%s]", "SCBR", 0x30, 8, 8),
        dlybs_field=field("CSR[%s]", "DLYBS", 0x30, 16, 8),
        dlybct_field=field("CSR[%s]", "DLYBCT", 0x30, 24, 8),
        tdre_field=field("SR", "TDRE", 0x10, 1),
        rdrf_field=field("SR", "RDRF", 0x10, 0),
        txempty_field=field("SR", "TXEMPTY", 0x10, 9),
        td_field=field("TDR", "TD", 0x0C, 0, 16),
        tdr_pcs_field=field("TDR", "PCS", 0x0C, 16, 4),
        rd_field=field("RDR", "RD", 0x08, 0, 16),
    )


def _nxp_spi_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> SpiSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return SpiSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=_invalid_register_ref(base),
        cr2_reg=_invalid_register_ref(base),
        sr_reg=reg("SR", 0x14),
        dr_reg=_invalid_register_ref(base),
        cr_reg=reg("CR", 0x10),
        mr_reg=reg("CFGR1", 0x24),
        csr_reg=reg("CCR", 0x40),
        tdr_reg=reg("TDR", 0x64),
        rdr_reg=reg("RDR", 0x74),
        cpha_field=field("TCR", ("CPHA",), 0x60, 30),
        cpol_field=field("TCR", ("CPOL",), 0x60, 31),
        mstr_field=field("CFGR1", ("MASTER",), 0x24, 0),
        br_field=field("TCR", ("PRESCALE",), 0x60, 27, 3),
        spe_field=field("CR", ("MEN",), 0x10, 0),
        lsbfirst_field=field("TCR", ("LSBF",), 0x60, 23),
        ssi_field=_invalid_field_ref(base),
        ssm_field=_invalid_field_ref(base),
        dff_field=_invalid_field_ref(base),
        ds_field=field("TCR", ("FRAMESZ",), 0x60, 0, 12),
        frxth_field=_invalid_field_ref(base),
        txe_field=field("SR", ("TDF",), 0x14, 0),
        rxne_field=field("SR", ("RDF",), 0x14, 1),
        bsy_field=field("SR", ("MBF",), 0x14, 24),
        dr_data_field=_invalid_field_ref(base),
        spien_field=_invalid_field_ref(base),
        spidis_field=_invalid_field_ref(base),
        swrst_field=field("CR", ("RST",), 0x10, 1),
        ps_field=_invalid_field_ref(base),
        pcsdec_field=_invalid_field_ref(base),
        modfdis_field=_invalid_field_ref(base),
        pcs_field=field("TCR", ("PCS",), 0x60, 24, 2),
        dlybcs_field=_invalid_field_ref(base),
        ncpha_field=_invalid_field_ref(base),
        bits_field=field("TCR", ("FRAMESZ",), 0x60, 0, 12),
        scbr_field=field("CCR", ("SCKDIV",), 0x40, 0, 8),
        dlybs_field=field("CCR", ("PCSSCK",), 0x40, 8, 8),
        dlybct_field=field("CCR", ("DBT",), 0x40, 16, 8),
        tdre_field=_invalid_field_ref(base),
        rdrf_field=_invalid_field_ref(base),
        txempty_field=_invalid_field_ref(base),
        td_field=field("TDR", ("TXDATA",), 0x64, 0, 32),
        tdr_pcs_field=_invalid_field_ref(base),
        rd_field=field("RDR", ("RXDATA",), 0x74, 0, 32),
    )


def _build_spi_rows(context: _SemanticContext) -> tuple[SpiSemanticRow, ...]:
    spi_hw_ids = {s.peripheral_id for s in context.device.spi_peripherals}
    rows: list[SpiSemanticRow] = []
    # Hardware-feature-only peripherals — admitted by ``device.spi_peripherals``
    # (added by ``fill-espressif-semantic-gaps``) but missing connection
    # candidates because the family overlay doesn't yet ship SPI pin
    # signal mappings.  Synthesize stub rows so the trait specialization
    # surfaces ``kPresent = true`` plus the hardware-feature constexprs.
    candidate_peripherals = list(context.candidate_peripherals_by_class.get("spi", ()))
    candidate_names = {p.name for p in candidate_peripherals}
    for peripheral in sorted(context.device.peripherals, key=lambda item: item.name):
        if peripheral.name in spi_hw_ids and peripheral.name not in candidate_names:
            candidate_peripherals.append(peripheral)
    for peripheral in candidate_peripherals:
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.spi.st-"):
            rows.append(_st_spi_row(context, peripheral_name=peripheral.name, schema_id=schema_id))
        elif schema_id == "alloy.spi.microchip-spi-zm":
            rows.append(
                _microchip_spi_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id == "alloy.spi.nxp-lpspi-v1":
            rows.append(_nxp_spi_row(context, peripheral_name=peripheral.name, schema_id=schema_id))
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (SpiSemanticTraits<PeripheralId::) is satisfied for devices whose
            # SPI IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            rows.append(
                SpiSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    cr1_reg=invalid_reg,
                    cr2_reg=invalid_reg,
                    sr_reg=invalid_reg,
                    dr_reg=invalid_reg,
                    cr_reg=invalid_reg,
                    mr_reg=invalid_reg,
                    csr_reg=invalid_reg,
                    tdr_reg=invalid_reg,
                    rdr_reg=invalid_reg,
                    cpha_field=invalid_field,
                    cpol_field=invalid_field,
                    mstr_field=invalid_field,
                    br_field=invalid_field,
                    spe_field=invalid_field,
                    lsbfirst_field=invalid_field,
                    ssi_field=invalid_field,
                    ssm_field=invalid_field,
                    dff_field=invalid_field,
                    ds_field=invalid_field,
                    frxth_field=invalid_field,
                    txe_field=invalid_field,
                    rxne_field=invalid_field,
                    bsy_field=invalid_field,
                    dr_data_field=invalid_field,
                    spien_field=invalid_field,
                    spidis_field=invalid_field,
                    swrst_field=invalid_field,
                    ps_field=invalid_field,
                    pcsdec_field=invalid_field,
                    modfdis_field=invalid_field,
                    pcs_field=invalid_field,
                    dlybcs_field=invalid_field,
                    ncpha_field=invalid_field,
                    bits_field=invalid_field,
                    scbr_field=invalid_field,
                    dlybs_field=invalid_field,
                    dlybct_field=invalid_field,
                    tdre_field=invalid_field,
                    rdrf_field=invalid_field,
                    txempty_field=invalid_field,
                    td_field=invalid_field,
                    tdr_pcs_field=invalid_field,
                    rd_field=invalid_field,
                    is_stub=peripheral.name not in spi_hw_ids,
                )
            )
    return tuple(rows)


def _resolve_dma_router_peripheral(context: _SemanticContext) -> PeripheralInstance | None:
    routers = tuple(
        peripheral
        for peripheral in sorted(context.peripheral_by_name.values(), key=lambda item: item.name)
        if runtime_lite_peripheral_class_name(peripheral.ip_name) == "dma-router"
    )
    if not routers:
        return None
    return routers[0]


def _build_dma_rows(context: _SemanticContext) -> tuple[DmaSemanticRow, ...]:
    runtime_peripheral_names = {
        peripheral.name
        for peripheral in context.peripheral_by_name.values()
        if runtime_lite_peripheral_class_name(peripheral.ip_name)
        in {
            "gpio",
            "uart",
            "i2c",
            "spi",
            "qspi",
            "sdmmc",
            "pwm",
            "adc",
            "dac",
            "dma",
            "dma-router",
        }
    }
    router = _resolve_dma_router_peripheral(context)
    rows: list[DmaSemanticRow] = []
    for binding in _runtime_lite_dma_bindings(context.device):
        if binding.peripheral not in runtime_peripheral_names or binding.signal is None:
            continue
        controller = context.peripheral_by_name.get(binding.controller)
        if controller is None:
            continue
        controller_schema_id = controller.backend_schema_id
        route_selector_field = _invalid_indexed_field_ref(controller.base_address)
        router_name: str | None = None
        router_schema_id: str | None = None
        if controller_schema_id == "alloy.dma.st-bdma-v1-0":
            if router is not None:
                router_name = router.name
                router_schema_id = router.backend_schema_id
                route_selector_field = _indexed_field_ref(
                    base_address=router.base_address,
                    base_offset_bytes=0x00,
                    stride_bytes=0x04,
                    bit_offset=0,
                    bit_width=8,
                )
        elif controller_schema_id == "alloy.dma.st-bdma-f4-v1-0":
            route_selector_field = _indexed_field_ref(
                base_address=controller.base_address,
                base_offset_bytes=0x10,
                stride_bytes=0x18,
                bit_offset=25,
                bit_width=3,
            )
        elif controller_schema_id == "alloy.dma.microchip-xdmac-k":
            route_selector_field = _indexed_field_ref(
                base_address=controller.base_address,
                base_offset_bytes=0x78,
                stride_bytes=0x40,
                bit_offset=24,
                bit_width=7,
            )
        rows.append(
            DmaSemanticRow(
                peripheral_name=binding.peripheral,
                signal_name=binding.signal,
                binding_id=binding.binding_id,
                controller_name=binding.controller,
                request_line=binding.request_line,
                route_id=binding.route_id,
                conflict_group=binding.conflict_group,
                controller_schema_id=controller_schema_id,
                router_name=router_name,
                router_schema_id=router_schema_id,
                channel_index=binding.channel_index,
                request_value=binding.request_value,
                channel_selector=binding.channel_selector,
                route_selector_field=route_selector_field,
            )
        )
    return tuple(rows)


def _peripheral_has_dma_binding(context: _SemanticContext, peripheral_name: str) -> bool:
    return any(
        binding.peripheral == peripheral_name
        for binding in _runtime_lite_dma_bindings(context.device)
    )


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
        controller_peri = getattr(binding, "controller", None) or getattr(
            binding, "controller_peripheral", None
        )
        controller_id = getattr(binding, "controller_id", None)
        binding_id = getattr(binding, "binding_id", None)
        request_value = getattr(binding, "request_value", None) or 0
        if controller_peri is None or controller_id is None or binding_id is None:
            continue
        bindings.append(
            AdcDmaBindingRow(
                controller_peripheral=str(controller_peri),
                controller_id=str(controller_id),
                binding_id=str(binding_id),
                request_value=int(request_value),
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


def _st_dac_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> DacSemanticRow:
    base_address = context.peripheral_by_name[peripheral_name].base_address
    prefixed_registers = (peripheral_name, "DAC_CR") in context.register_by_key
    register_prefix = "DAC_" if prefixed_registers else ""
    control_register_name = f"{register_prefix}CR"
    trigger_register_name = f"{register_prefix}SWTRGR"
    dual_data_register_name = f"{register_prefix}DHR12RD"
    data_register_name = dual_data_register_name
    dual_channel = (
        peripheral_name,
        dual_data_register_name.upper(),
    ) in context.register_by_key or (
        peripheral_name,
        f"{register_prefix}DHR12R2".upper(),
    ) in context.register_by_key
    channel_count = 2 if dual_channel else 1
    trigger_bit_offset = 1 if prefixed_registers else 2
    trigger_select_bit_offset = 2 if prefixed_registers else 3
    trigger_select_width = 4 if prefixed_registers else 3
    mode_register = (
        _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=f"{register_prefix}MCR",
            fallback_offset=0x3C,
        )
        if prefixed_registers
        else _invalid_register_ref(base_address)
    )
    return DacSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        channel_count=channel_count,
        has_hardware_trigger=True,
        has_dma=_peripheral_has_dma_binding(context, peripheral_name),
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            fallback_offset=0x00,
        ),
        mode_reg=mode_register,
        trigger_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=trigger_register_name,
            fallback_offset=0x04,
        ),
        channel_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            fallback_offset=0x00,
        ),
        channel_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            fallback_offset=0x00,
        ),
        channel_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=f"{register_prefix}SR",
            fallback_offset=0x34,
        ),
        data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=data_register_name,
            fallback_offset=0x20 if dual_channel else 0x08,
        ),
        software_reset_field=_invalid_field_ref(base_address),
        word_mode_field=_invalid_field_ref(base_address),
        prescaler_field=_invalid_field_ref(base_address),
        channel_enable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x00,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=16,
        ),
        channel_disable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x00,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=16,
        ),
        channel_ready_pattern=_invalid_indexed_field_ref(base_address),
        trigger_enable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x00,
            stride_bytes=0,
            bit_offset=trigger_bit_offset,
            bit_width=1,
            bit_stride_bits=16,
        ),
        trigger_select_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x00,
            stride_bytes=0,
            bit_offset=trigger_select_bit_offset,
            bit_width=trigger_select_width,
            bit_stride_bits=16,
        ),
        data_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x20 if dual_channel else 0x08,
            stride_bytes=0,
            bit_offset=0,
            bit_width=12,
            bit_stride_bits=16 if dual_channel else 0,
        ),
    )


def _st_dac_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[DacChannelSemanticRow, ...]:
    prefixed_registers = (peripheral_name, "DAC_CR") in context.register_by_key
    register_prefix = "DAC_" if prefixed_registers else ""
    channel_count = (
        2
        if (peripheral_name, f"{register_prefix}DHR12R2".upper()) in context.register_by_key
        else 1
    )
    trigger_select_width = 4 if prefixed_registers else 3
    rows: list[DacChannelSemanticRow] = []
    for channel_index in range(channel_count):
        channel_number = channel_index + 1
        register_offset = 0x08 + (channel_index * 0x0C)
        enable_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=f"{register_prefix}CR",
            field_names=(f"EN{channel_number}",),
            fallback_register_offset=0x00,
            fallback_bit_offset=channel_index * 16,
            fallback_bit_width=1,
        )
        rows.append(
            DacChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                enable_field=enable_field,
                disable_field=enable_field,
                ready_field=_invalid_field_ref(
                    context.peripheral_by_name[peripheral_name].base_address
                ),
                trigger_enable_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"{register_prefix}CR",
                    field_names=(f"TEN{channel_number}",),
                    fallback_register_offset=0x00,
                    fallback_bit_offset=(1 if prefixed_registers else 2) + (channel_index * 16),
                    fallback_bit_width=1,
                ),
                trigger_select_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"{register_prefix}CR",
                    field_names=(f"TSEL{channel_number}",),
                    fallback_register_offset=0x00,
                    fallback_bit_offset=(2 if prefixed_registers else 3) + (channel_index * 16),
                    fallback_bit_width=trigger_select_width,
                ),
                data_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"{register_prefix}DHR12R{channel_number}",
                    field_names=(f"DACC{channel_number}DHR",),
                    fallback_register_offset=register_offset,
                    fallback_bit_offset=0,
                    fallback_bit_width=12,
                ),
            )
        )
    return tuple(rows)


def _microchip_dac_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> DacSemanticRow:
    base_address = context.peripheral_by_name[peripheral_name].base_address
    return DacSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        channel_count=2,
        has_hardware_trigger=True,
        has_dma=_peripheral_has_dma_binding(context, peripheral_name),
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            fallback_offset=0x00,
        ),
        mode_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            fallback_offset=0x04,
        ),
        trigger_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TRIGR",
            fallback_offset=0x08,
        ),
        channel_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CHER",
            fallback_offset=0x10,
        ),
        channel_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CHDR",
            fallback_offset=0x14,
        ),
        channel_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CHSR",
            fallback_offset=0x18,
        ),
        data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CDR[%s]",
            fallback_offset=0x1C,
        ),
        software_reset_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("SWRST",),
            fallback_register_offset=0x00,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        word_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WORD",),
            fallback_register_offset=0x04,
            fallback_bit_offset=4,
            fallback_bit_width=1,
        ),
        prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("PRESCALER",),
            fallback_register_offset=0x04,
            fallback_bit_offset=24,
            fallback_bit_width=4,
        ),
        channel_enable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x10,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
        channel_disable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x14,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
        channel_ready_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x18,
            stride_bytes=0,
            bit_offset=16,
            bit_width=1,
            bit_stride_bits=1,
        ),
        trigger_enable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x08,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
        trigger_select_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x08,
            stride_bytes=0,
            bit_offset=4,
            bit_width=3,
            bit_stride_bits=4,
        ),
        data_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x1C,
            stride_bytes=0,
            bit_offset=0,
            bit_width=16,
            bit_stride_bits=16,
        ),
    )


def _microchip_dac_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[DacChannelSemanticRow, ...]:
    rows: list[DacChannelSemanticRow] = []
    for channel_index in range(2):
        rows.append(
            DacChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                enable_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="CHER",
                    field_names=(f"CH{channel_index}",),
                    fallback_register_offset=0x10,
                    fallback_bit_offset=channel_index,
                    fallback_bit_width=1,
                ),
                disable_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="CHDR",
                    field_names=(f"CH{channel_index}",),
                    fallback_register_offset=0x14,
                    fallback_bit_offset=channel_index,
                    fallback_bit_width=1,
                ),
                ready_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="CHSR",
                    field_names=(f"DACRDY{channel_index}",),
                    fallback_register_offset=0x18,
                    fallback_bit_offset=16 + channel_index,
                    fallback_bit_width=1,
                ),
                trigger_enable_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="TRIGR",
                    field_names=(f"TRGEN{channel_index}",),
                    fallback_register_offset=0x08,
                    fallback_bit_offset=channel_index,
                    fallback_bit_width=1,
                ),
                trigger_select_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="TRIGR",
                    field_names=(f"TRGSEL{channel_index}",),
                    fallback_register_offset=0x08,
                    fallback_bit_offset=4 + (channel_index * 4),
                    fallback_bit_width=3,
                ),
                data_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="CDR[%s]",
                    field_names=(f"DATA{channel_index}",),
                    fallback_register_offset=0x1C,
                    fallback_bit_offset=channel_index * 16,
                    fallback_bit_width=16,
                ),
            )
        )
    return tuple(rows)


def _build_dac_rows(
    context: _SemanticContext,
) -> tuple[tuple[DacSemanticRow, ...], tuple[DacChannelSemanticRow, ...]]:
    rows: list[DacSemanticRow] = []
    channel_rows: list[DacChannelSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("dac", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.dac.st-"):
            rows.append(
                _st_dac_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(_st_dac_channel_rows(context, peripheral_name=peripheral.name))
        elif schema_id == "alloy.dac.microchip-dacc-e":
            rows.append(
                _microchip_dac_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(
                _microchip_dac_channel_rows(context, peripheral_name=peripheral.name)
            )
    return tuple(rows), tuple(channel_rows)


def _st_rtc_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> RtcSemanticRow:
    status_register_names = ("ICSR", "ISR")
    clear_register_names = ("SCR",)
    return RtcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_calendar=True,
        has_alarm=True,
        has_write_protection=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        mode_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        status_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
        ),
        time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TR",
        ),
        date_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DR",
        ),
        alarm_time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ALRMAR",
        ),
        alarm_date_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ALRMBR",
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        interrupt_disable_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        interrupt_mask_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        clear_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=clear_register_names,
        ),
        write_protect_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WPR",
        ),
        prescaler_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PRER",
        ),
        hour_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("FMT",),
        ),
        init_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
            field_names=("INIT",),
        ),
        init_ready_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
            field_names=("INITF",),
        ),
        shadow_bypass_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("BYPSHAD",),
        ),
        update_time_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        update_calendar_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        update_ack_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        alarm_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("ALRAE",),
        ),
        alarm_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("ALRAIE",),
        ),
        second_interrupt_enable_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        time_event_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("TSIE",),
        ),
        calendar_event_interrupt_enable_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_alarm_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
            field_names=("ALRAF",),
        ),
        status_second_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_time_event_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
            field_names=("TSF",),
        ),
        status_calendar_event_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_tamper_error_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
            field_names=("ITSF", "TAMP1F"),
        ),
        clear_alarm_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=clear_register_names,
            field_names=("CALRAF",),
        ),
        clear_second_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        clear_time_event_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=clear_register_names,
            field_names=("CTSF",),
        ),
        clear_calendar_event_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        clear_tamper_error_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=clear_register_names,
            field_names=("CITSF",),
        ),
        write_protect_key_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WPR",
            field_names=("KEY",),
        ),
        write_protect_disable_key0=0xCA,
        write_protect_disable_key1=0x53,
        write_protect_enable_key=0xFF,
    )


def _microchip_rtc_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> RtcSemanticRow:
    return RtcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_calendar=True,
        has_alarm=True,
        has_write_protection=False,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        mode_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
        ),
        time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TIMR",
        ),
        date_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CALR",
        ),
        alarm_time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TIMALR",
        ),
        alarm_date_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CALALR",
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
        ),
        interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IDR",
        ),
        interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IMR",
        ),
        clear_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
        ),
        write_protect_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        prescaler_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        hour_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("HRMOD",),
        ),
        init_field=_invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address),
        init_ready_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        shadow_bypass_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        update_time_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("UPDTIM",),
        ),
        update_calendar_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("UPDCAL",),
        ),
        update_ack_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("ACKUPD",),
        ),
        alarm_enable_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        alarm_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("ALREN",),
        ),
        second_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("SECEN",),
        ),
        time_event_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("TIMEN",),
        ),
        calendar_event_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("CALEN",),
        ),
        status_alarm_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("ALARM",),
        ),
        status_second_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("SEC",),
        ),
        status_time_event_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("TIMEV",),
        ),
        status_calendar_event_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("CALEV",),
        ),
        status_tamper_error_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("TDERR",),
        ),
        clear_alarm_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
            field_names=("ALRCLR",),
        ),
        clear_second_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
            field_names=("SECCLR",),
        ),
        clear_time_event_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
            field_names=("TIMCLR",),
        ),
        clear_calendar_event_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
            field_names=("CALCLR",),
        ),
        clear_tamper_error_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
            field_names=("TDERRCLR",),
        ),
        write_protect_key_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        write_protect_disable_key0=0,
        write_protect_disable_key1=0,
        write_protect_enable_key=0,
    )


def _build_rtc_rows(context: _SemanticContext) -> tuple[RtcSemanticRow, ...]:
    rows: list[RtcSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("rtc", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.rtc.st-"):
            rows.append(
                _st_rtc_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id.startswith("alloy.rtc.microchip-"):
            rows.append(
                _microchip_rtc_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (RtcSemanticTraits<PeripheralId::) is satisfied for devices whose
            # RTC IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            rows.append(
                RtcSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    has_calendar=False,
                    has_alarm=False,
                    has_write_protection=False,
                    control_reg=invalid_reg,
                    mode_reg=invalid_reg,
                    status_reg=invalid_reg,
                    time_reg=invalid_reg,
                    date_reg=invalid_reg,
                    alarm_time_reg=invalid_reg,
                    alarm_date_reg=invalid_reg,
                    interrupt_enable_reg=invalid_reg,
                    interrupt_disable_reg=invalid_reg,
                    interrupt_mask_reg=invalid_reg,
                    clear_reg=invalid_reg,
                    write_protect_reg=invalid_reg,
                    prescaler_reg=invalid_reg,
                    hour_mode_field=invalid_field,
                    init_field=invalid_field,
                    init_ready_field=invalid_field,
                    shadow_bypass_field=invalid_field,
                    update_time_field=invalid_field,
                    update_calendar_field=invalid_field,
                    update_ack_field=invalid_field,
                    alarm_enable_field=invalid_field,
                    alarm_interrupt_enable_field=invalid_field,
                    second_interrupt_enable_field=invalid_field,
                    time_event_interrupt_enable_field=invalid_field,
                    calendar_event_interrupt_enable_field=invalid_field,
                    status_alarm_field=invalid_field,
                    status_second_field=invalid_field,
                    status_time_event_field=invalid_field,
                    status_calendar_event_field=invalid_field,
                    status_tamper_error_field=invalid_field,
                    clear_alarm_field=invalid_field,
                    clear_second_field=invalid_field,
                    clear_time_event_field=invalid_field,
                    clear_calendar_event_field=invalid_field,
                    clear_tamper_error_field=invalid_field,
                    write_protect_key_field=invalid_field,
                    write_protect_disable_key0=0,
                    write_protect_disable_key1=0,
                    write_protect_enable_key=0,
                    is_stub=True,
                )
            )
    return tuple(rows)


def _mcan_register_ref(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_name: str,
    fallback_offset: int,
) -> RuntimeRegisterRef:
    return _resolve_register_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_name,
        fallback_offset=fallback_offset,
    )


def _mcan_field_ref(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_name: str,
    field_names: tuple[str, ...],
) -> RuntimeFieldRef:
    return _resolve_field_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_name,
        field_names=field_names,
    )


def _mcan_common_can_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> CanSemanticRow:
    peripheral = context.peripheral_by_name[peripheral_name]
    return CanSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_flexible_data_rate=True,
        control_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            fallback_offset=0x18,
        ),
        nominal_timing_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NBTP",
            fallback_offset=0x1C,
        ),
        data_timing_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DBTP",
            fallback_offset=0x0C,
        ),
        test_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TEST",
            fallback_offset=0x10,
        ),
        error_counter_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ECR",
            fallback_offset=0x40,
        ),
        protocol_status_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PSR",
            fallback_offset=0x44,
        ),
        interrupt_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IR",
            fallback_offset=0x50,
        ),
        interrupt_enable_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IE",
            fallback_offset=0x54,
        ),
        interrupt_line_select_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ILS",
            fallback_offset=0x58,
        ),
        interrupt_line_enable_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ILE",
            fallback_offset=0x5C,
        ),
        global_filter_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="GFC",
            fallback_offset=0x80,
        ),
        standard_filter_config_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SIDFC",
            fallback_offset=0x84,
        ),
        extended_filter_config_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="XIDFC",
            fallback_offset=0x88,
        ),
        extended_id_mask_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="XIDAM",
            fallback_offset=0x90,
        ),
        rx_fifo0_config_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0C",
            fallback_offset=0xA0,
        ),
        rx_fifo0_status_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0S",
            fallback_offset=0xA4,
        ),
        rx_fifo0_ack_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0A",
            fallback_offset=0xA8,
        ),
        tx_buffer_config_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXBC",
            fallback_offset=0xC0,
        ),
        tx_fifo_queue_status_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXFQS",
            fallback_offset=0xC4,
        ),
        tx_buffer_add_request_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXBAR",
            fallback_offset=0xD0,
        ),
        tx_buffer_pending_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXBRP",
            fallback_offset=0xCC,
        ),
        tx_event_fifo_config_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXEFC",
            fallback_offset=0xF0,
        ),
        tx_event_fifo_status_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXEFS",
            fallback_offset=0xF4,
        ),
        tx_event_fifo_ack_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXEFA",
            fallback_offset=0xF8,
        ),
        init_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("INIT",),
        ),
        config_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("CCE",),
        ),
        restricted_operation_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("CSR",),
        ),
        restricted_operation_ack_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("CSA",),
        ),
        bus_monitor_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("ASM",),
        ),
        fd_operation_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("FDOE",),
        ),
        bit_rate_switch_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("BRSE",),
        ),
        nominal_prescaler_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NBTP",
            field_names=("NBRP",),
        ),
        nominal_time_seg1_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NBTP",
            field_names=("NTSEG1",),
        ),
        nominal_time_seg2_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NBTP",
            field_names=("NTSEG2",),
        ),
        nominal_sync_jump_width_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NBTP",
            field_names=("NSJW",),
        ),
        data_prescaler_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DBTP",
            field_names=("DBRP",),
        ),
        data_time_seg1_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DBTP",
            field_names=("DTSEG1",),
        ),
        data_time_seg2_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DBTP",
            field_names=("DTSEG2",),
        ),
        data_sync_jump_width_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DBTP",
            field_names=("DSJW",),
        ),
        rx_fifo0_new_interrupt_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IR",
            field_names=("RF0N",),
        ),
        tx_complete_interrupt_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IR",
            field_names=("TC",),
        ),
        tx_event_fifo_new_interrupt_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IR",
            field_names=("TFE",),
        ),
        rx_fifo0_new_interrupt_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IE",
            field_names=("RF0NE",),
        ),
        tx_complete_interrupt_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IE",
            field_names=("TCE",),
        ),
        tx_event_fifo_new_interrupt_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IE",
            field_names=("TFEE", "TFEE0"),
        ),
        rx_fifo0_fill_level_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0S",
            field_names=("F0FL",),
        ),
        rx_fifo0_get_index_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0S",
            field_names=("F0GI",),
        ),
        rx_fifo0_message_lost_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0S",
            field_names=("RF0L",),
        ),
        rx_fifo0_ack_index_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0A",
            field_names=("F0AI",),
        ),
        tx_fifo_queue_put_index_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXFQS",
            field_names=("TFQPI",),
        ),
        tx_fifo_queue_free_level_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXFQS",
            field_names=("TFFL",),
        ),
        tx_buffer_add_request_pattern=_indexed_field_ref(
            base_address=peripheral.base_address,
            base_offset_bytes=0xD0,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
        tx_buffer_pending_pattern=_indexed_field_ref(
            base_address=peripheral.base_address,
            base_offset_bytes=0xCC,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
    )


def _st_fdcan_can_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> CanSemanticRow:
    return _mcan_common_can_row(
        context,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
    )


def _st_bxcan_can_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> CanSemanticRow:
    peripheral = context.peripheral_by_name[peripheral_name]
    return CanSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_flexible_data_rate=False,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            fallback_offset=0x0,
        ),
        nominal_timing_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            fallback_offset=0x1C,
        ),
        data_timing_reg=_invalid_register_ref(peripheral.base_address),
        test_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            fallback_offset=0x1C,
        ),
        error_counter_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ESR",
            fallback_offset=0x18,
        ),
        protocol_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MSR",
            fallback_offset=0x4,
        ),
        interrupt_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MSR",
            fallback_offset=0x4,
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            fallback_offset=0x14,
        ),
        interrupt_line_select_reg=_invalid_register_ref(peripheral.base_address),
        interrupt_line_enable_reg=_invalid_register_ref(peripheral.base_address),
        global_filter_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="FMR",
            fallback_offset=0x200,
        ),
        standard_filter_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="FM1R",
            fallback_offset=0x204,
        ),
        extended_filter_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="FS1R",
            fallback_offset=0x20C,
        ),
        extended_id_mask_reg=_invalid_register_ref(peripheral.base_address),
        rx_fifo0_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            fallback_offset=0x0C,
        ),
        rx_fifo0_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            fallback_offset=0x0C,
        ),
        rx_fifo0_ack_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            fallback_offset=0x0C,
        ),
        tx_buffer_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TSR",
            fallback_offset=0x08,
        ),
        tx_fifo_queue_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TSR",
            fallback_offset=0x08,
        ),
        tx_buffer_add_request_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TI0R",
            fallback_offset=0x180,
        ),
        tx_buffer_pending_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_config_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_status_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_ack_reg=_invalid_register_ref(peripheral.base_address),
        init_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            field_names=("INRQ",),
        ),
        config_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            field_names=("INRQ",),
        ),
        restricted_operation_field=_invalid_field_ref(peripheral.base_address),
        restricted_operation_ack_field=_invalid_field_ref(peripheral.base_address),
        bus_monitor_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            field_names=("SILM",),
        ),
        fd_operation_enable_field=_invalid_field_ref(peripheral.base_address),
        bit_rate_switch_enable_field=_invalid_field_ref(peripheral.base_address),
        nominal_prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            field_names=("BRP",),
        ),
        nominal_time_seg1_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            field_names=("TS1",),
        ),
        nominal_time_seg2_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            field_names=("TS2",),
        ),
        nominal_sync_jump_width_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            field_names=("SJW",),
        ),
        data_prescaler_field=_invalid_field_ref(peripheral.base_address),
        data_time_seg1_field=_invalid_field_ref(peripheral.base_address),
        data_time_seg2_field=_invalid_field_ref(peripheral.base_address),
        data_sync_jump_width_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_new_interrupt_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            field_names=("FMP0",),
        ),
        tx_complete_interrupt_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TSR",
            field_names=("TXOK0",),
        ),
        tx_event_fifo_new_interrupt_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_new_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("FMPIE0",),
        ),
        tx_complete_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("TMEIE",),
        ),
        tx_event_fifo_new_interrupt_enable_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_fill_level_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            field_names=("FMP0",),
        ),
        rx_fifo0_get_index_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_message_lost_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            field_names=("FOVR0",),
        ),
        rx_fifo0_ack_index_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            field_names=("RFOM0",),
        ),
        tx_fifo_queue_put_index_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TSR",
            field_names=("CODE",),
        ),
        tx_fifo_queue_free_level_field=_invalid_field_ref(peripheral.base_address),
        tx_buffer_add_request_pattern=_indexed_field_ref(
            base_address=peripheral.base_address,
            base_offset_bytes=0x180,
            stride_bytes=0x10,
            bit_offset=0,
            bit_width=1,
        ),
        tx_buffer_pending_pattern=_invalid_indexed_field_ref(peripheral.base_address),
    )


def _microchip_mcan_can_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> CanSemanticRow:
    return _mcan_common_can_row(
        context,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
    )


def _nxp_flexcan_can_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> CanSemanticRow:
    peripheral = context.peripheral_by_name[peripheral_name]
    fden_field = _resolve_field_ref(
        context,
        peripheral_name=peripheral_name,
        register_name="MCR",
        field_names=("FDEN",),
    )
    data_timing_reg = _resolve_register_ref(
        context,
        peripheral_name=peripheral_name,
        register_name="CBT",
    )
    bit_rate_switch_field = _resolve_field_ref(
        context,
        peripheral_name=peripheral_name,
        register_name="CBT",
        field_names=("BTF",),
    )
    has_flexible_data_rate = fden_field.valid or data_timing_reg.valid
    return CanSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_flexible_data_rate=has_flexible_data_rate,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            fallback_offset=0x0,
        ),
        nominal_timing_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            fallback_offset=0x4,
        ),
        data_timing_reg=data_timing_reg,
        test_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            fallback_offset=0x4,
        ),
        error_counter_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ECR",
            fallback_offset=0x1C,
        ),
        protocol_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ESR1",
            fallback_offset=0x20,
        ),
        interrupt_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IFLAG1", "ESR1"),
            fallback_offset=0x30,
        ),
        interrupt_enable_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IMASK1", "CTRL1"),
            fallback_offset=0x28,
        ),
        interrupt_line_select_reg=_invalid_register_ref(peripheral.base_address),
        interrupt_line_enable_reg=_invalid_register_ref(peripheral.base_address),
        global_filter_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXFGMASK",
            fallback_offset=0x48,
        ),
        standard_filter_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXMGMASK",
            fallback_offset=0x10,
        ),
        extended_filter_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RX14MASK",
            fallback_offset=0x14,
        ),
        extended_id_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RX15MASK",
            fallback_offset=0x18,
        ),
        rx_fifo0_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            fallback_offset=0x0,
        ),
        rx_fifo0_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXFIR",
            fallback_offset=0x4C,
        ),
        rx_fifo0_ack_reg=_invalid_register_ref(peripheral.base_address),
        tx_buffer_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            fallback_offset=0x0,
        ),
        tx_fifo_queue_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFLAG1",
            fallback_offset=0x30,
        ),
        tx_buffer_add_request_reg=_invalid_register_ref(peripheral.base_address),
        tx_buffer_pending_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_config_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_status_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_ack_reg=_invalid_register_ref(peripheral.base_address),
        init_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            field_names=("HALT",),
        ),
        config_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            field_names=("FRZ",),
        ),
        restricted_operation_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("LOM",),
        ),
        restricted_operation_ack_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            field_names=("FRZACK",),
        ),
        bus_monitor_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("LOM",),
        ),
        fd_operation_enable_field=fden_field,
        bit_rate_switch_enable_field=bit_rate_switch_field,
        nominal_prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("PRESDIV",),
        ),
        nominal_time_seg1_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("PSEG1",),
        ),
        nominal_time_seg2_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("PSEG2",),
        ),
        nominal_sync_jump_width_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("RJW",),
        ),
        data_prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CBT",
            field_names=("EPRESDIV",),
        ),
        data_time_seg1_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CBT",
            field_names=("EPSEG1",),
        ),
        data_time_seg2_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CBT",
            field_names=("EPSEG2",),
        ),
        data_sync_jump_width_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CBT",
            field_names=("ERJW",),
        ),
        rx_fifo0_new_interrupt_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IFLAG1",),
            field_names=("BUF5I", "BUF4TO1I", "BUF4TO0I"),
        ),
        tx_complete_interrupt_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IFLAG1",),
            field_names=("BUF0I", "BUF4TO0I"),
        ),
        tx_event_fifo_new_interrupt_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_new_interrupt_enable_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IMASK1",),
            field_names=("BUF31TO0M", "BUFLM"),
        ),
        tx_complete_interrupt_enable_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IMASK1",),
            field_names=("BUF31TO0M", "BUFLM"),
        ),
        tx_event_fifo_new_interrupt_enable_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_fill_level_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_get_index_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXFIR",
            field_names=("IDHIT",),
        ),
        rx_fifo0_message_lost_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_ack_index_field=_invalid_field_ref(peripheral.base_address),
        tx_fifo_queue_put_index_field=_invalid_field_ref(peripheral.base_address),
        tx_fifo_queue_free_level_field=_invalid_field_ref(peripheral.base_address),
        tx_buffer_add_request_pattern=_invalid_indexed_field_ref(peripheral.base_address),
        tx_buffer_pending_pattern=_invalid_indexed_field_ref(peripheral.base_address),
    )


def _build_can_rows(context: _SemanticContext) -> tuple[CanSemanticRow, ...]:
    rows: list[CanSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("can", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.fdcan.st-") or schema_id.startswith("alloy.can.st-fdcan"):
            rows.append(
                _st_fdcan_can_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id == "alloy.can.st-can" or schema_id.startswith("alloy.can.st-bxcan"):
            rows.append(
                _st_bxcan_can_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id.startswith("alloy.can.microchip-mcan-"):
            rows.append(
                _microchip_mcan_can_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id.startswith("alloy.can.nxp-can"):
            rows.append(
                _nxp_flexcan_can_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
    return tuple(rows)


def _microchip_gmac_eth_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> EthSemanticRow:
    return EthSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        supports_mii=True,
        supports_rmii=True,
        has_dma_engine=True,
        has_statistics_counters=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            fallback_offset=0x0000,
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCFGR",
            fallback_offset=0x0004,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NSR",
            fallback_offset=0x0008,
        ),
        user_io_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="UR",
            fallback_offset=0x000C,
        ),
        dma_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DCFGR",
            fallback_offset=0x0010,
        ),
        tx_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TSR",
            fallback_offset=0x0014,
        ),
        rx_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RSR",
            fallback_offset=0x0020,
        ),
        interrupt_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ISR",
            fallback_offset=0x0024,
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            fallback_offset=0x0028,
        ),
        interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IDR",
            fallback_offset=0x002C,
        ),
        interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IMR",
            fallback_offset=0x0030,
        ),
        rx_descriptor_base_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RBQB",
            fallback_offset=0x0018,
        ),
        tx_descriptor_base_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TBQB",
            fallback_offset=0x001C,
        ),
        rx_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("RXEN",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        tx_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("TXEN",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=3,
            fallback_bit_width=1,
        ),
        management_port_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("MPE",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=4,
            fallback_bit_width=1,
        ),
        clear_statistics_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("CLRSTAT",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=5,
            fallback_bit_width=1,
        ),
        write_enable_statistics_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("WESTAT",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        tx_start_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("TSTART",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=9,
            fallback_bit_width=1,
        ),
        speed_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCFGR",
            field_names=("SPD",),
            fallback_register_offset=0x0004,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        full_duplex_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCFGR",
            field_names=("FD",),
            fallback_register_offset=0x0004,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        mdc_clock_divider_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCFGR",
            field_names=("CLK",),
            fallback_register_offset=0x0004,
            fallback_bit_offset=10,
            fallback_bit_width=3,
        ),
        rmii_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="UR",
            field_names=("RMII",),
            fallback_register_offset=0x000C,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        management_done_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NSR",
            field_names=("IDLE",),
            fallback_register_offset=0x0008,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        rx_complete_interrupt_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ISR",
            field_names=("RCOMP",),
            fallback_register_offset=0x0024,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        tx_complete_interrupt_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ISR",
            field_names=("TCOMP",),
            fallback_register_offset=0x0024,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        rx_complete_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("RCOMP",),
            fallback_register_offset=0x0028,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        tx_complete_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("TCOMP",),
            fallback_register_offset=0x0028,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
    )


def _build_eth_rows(context: _SemanticContext) -> tuple[EthSemanticRow, ...]:
    rows: list[EthSemanticRow] = []
    handled: set[str] = set()
    for peripheral in context.runtime_peripherals_by_class.get("eth", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.gmac.microchip-") or schema_id.startswith(
            "alloy.eth.microchip-"
        ):
            rows.append(
                _microchip_gmac_eth_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            handled.add(peripheral.name)

    # Emit stub rows for ETH peripherals whose schema is not yet implemented so
    # the artifact contract (`EthSemanticTraits<PeripheralId::`) is satisfied.
    for peripheral in context.runtime_peripherals_by_class.get("eth", ()):
        if peripheral.name in handled:
            continue
        base = context.peripheral_by_name[peripheral.name].base_address
        invalid_reg = _invalid_register_ref(base)
        invalid_field = _invalid_field_ref(base)
        rows.append(
            EthSemanticRow(
                peripheral_name=peripheral.name,
                schema_id=peripheral.backend_schema_id or "",
                supports_mii=False,
                supports_rmii=False,
                has_dma_engine=False,
                has_statistics_counters=False,
                control_reg=invalid_reg,
                config_reg=invalid_reg,
                status_reg=invalid_reg,
                user_io_reg=invalid_reg,
                dma_config_reg=invalid_reg,
                tx_status_reg=invalid_reg,
                rx_status_reg=invalid_reg,
                interrupt_status_reg=invalid_reg,
                interrupt_enable_reg=invalid_reg,
                interrupt_disable_reg=invalid_reg,
                interrupt_mask_reg=invalid_reg,
                rx_descriptor_base_reg=invalid_reg,
                tx_descriptor_base_reg=invalid_reg,
                rx_enable_field=invalid_field,
                tx_enable_field=invalid_field,
                management_port_enable_field=invalid_field,
                clear_statistics_field=invalid_field,
                write_enable_statistics_field=invalid_field,
                tx_start_field=invalid_field,
                speed_field=invalid_field,
                full_duplex_field=invalid_field,
                mdc_clock_divider_field=invalid_field,
                rmii_enable_field=invalid_field,
                management_done_field=invalid_field,
                rx_complete_interrupt_field=invalid_field,
                tx_complete_interrupt_field=invalid_field,
                rx_complete_interrupt_enable_field=invalid_field,
                tx_complete_interrupt_enable_field=invalid_field,
                is_stub=True,
            )
        )
    return tuple(rows)


def _st_usb_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> UsbSemanticRow:
    peripheral = context.peripheral_by_name[peripheral_name]
    return UsbSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        supports_device_mode=True,
        supports_host_mode=True,
        has_dedicated_endpoint_config=True,
        has_clock_freeze=False,
        control_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GUSBCFG",),
            fallback_offset=0x0C,
        ),
        status_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GINTSTS",),
            fallback_offset=0x14,
        ),
        interrupt_status_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GINTSTS",),
            fallback_offset=0x14,
        ),
        interrupt_mask_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GINTMSK",),
            fallback_offset=0x18,
        ),
        device_control_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("DCTL",),
            fallback_offset=0x804,
        ),
        device_status_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("DSTS",),
            fallback_offset=0x808,
        ),
        device_interrupt_status_reg=_invalid_register_ref(peripheral.base_address),
        device_interrupt_mask_reg=_invalid_register_ref(peripheral.base_address),
        device_interrupt_enable_reg=_invalid_register_ref(peripheral.base_address),
        device_interrupt_disable_reg=_invalid_register_ref(peripheral.base_address),
        host_control_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("HCFG",),
            fallback_offset=0x400,
        ),
        host_status_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("HPRT", "HPRT0"),
            fallback_offset=0x440,
        ),
        host_interrupt_status_reg=_invalid_register_ref(peripheral.base_address),
        host_interrupt_mask_reg=_invalid_register_ref(peripheral.base_address),
        host_interrupt_enable_reg=_invalid_register_ref(peripheral.base_address),
        host_interrupt_disable_reg=_invalid_register_ref(peripheral.base_address),
        enable_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GCCFG",),
            field_names=("PWRDWN",),
            fallback_register_offset=0x38,
            fallback_bit_offset=16,
            fallback_bit_width=1,
        ),
        freeze_clock_field=_invalid_field_ref(peripheral.base_address),
        force_device_mode_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GUSBCFG",),
            field_names=("FDMOD",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=30,
            fallback_bit_width=1,
        ),
        force_host_mode_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GUSBCFG",),
            field_names=("FHMOD",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=29,
            fallback_bit_width=1,
        ),
        mode_status_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GINTSTS",),
            field_names=("CMOD",),
            fallback_register_offset=0x14,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        soft_disconnect_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("DCTL",),
            field_names=("SDIS",),
            fallback_register_offset=0x804,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        remote_wakeup_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("DCTL",),
            field_names=("RWUSIG",),
            fallback_register_offset=0x804,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        address_enable_field=_invalid_field_ref(peripheral.base_address),
        address_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("DCFG",),
            field_names=("DAD",),
            fallback_register_offset=0x800,
            fallback_bit_offset=4,
            fallback_bit_width=7,
        ),
        clock_usable_field=_invalid_field_ref(peripheral.base_address),
    )


def _microchip_usb_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> UsbSemanticRow:
    peripheral = context.peripheral_by_name[peripheral_name]
    return UsbSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        supports_device_mode=True,
        supports_host_mode=True,
        has_dedicated_endpoint_config=True,
        has_clock_freeze=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL",
            fallback_offset=0x0800,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            fallback_offset=0x0804,
        ),
        interrupt_status_reg=_invalid_register_ref(peripheral.base_address),
        interrupt_mask_reg=_invalid_register_ref(peripheral.base_address),
        device_control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVCTRL",
            fallback_offset=0x0000,
        ),
        device_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVISR",
            fallback_offset=0x0004,
        ),
        device_interrupt_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVISR",
            fallback_offset=0x0004,
        ),
        device_interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVIMR",
            fallback_offset=0x0010,
        ),
        device_interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVIER",
            fallback_offset=0x0018,
        ),
        device_interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVIDR",
            fallback_offset=0x0014,
        ),
        host_control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTCTRL",
            fallback_offset=0x0400,
        ),
        host_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTISR",
            fallback_offset=0x0404,
        ),
        host_interrupt_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTISR",
            fallback_offset=0x0404,
        ),
        host_interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTIMR",
            fallback_offset=0x0410,
        ),
        host_interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTIER",
            fallback_offset=0x0418,
        ),
        host_interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTIDR",
            fallback_offset=0x0414,
        ),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL",
            field_names=("USBE",),
            fallback_register_offset=0x0800,
            fallback_bit_offset=8,
            fallback_bit_width=1,
        ),
        freeze_clock_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL",
            field_names=("FRZCLK",),
            fallback_register_offset=0x0800,
            fallback_bit_offset=14,
            fallback_bit_width=1,
        ),
        force_device_mode_field=_invalid_field_ref(peripheral.base_address),
        force_host_mode_field=_invalid_field_ref(peripheral.base_address),
        mode_status_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL",
            field_names=("UIMOD",),
            fallback_register_offset=0x0800,
            fallback_bit_offset=25,
            fallback_bit_width=1,
        ),
        soft_disconnect_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVCTRL",
            field_names=("DETACH",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=8,
            fallback_bit_width=1,
        ),
        remote_wakeup_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVCTRL",
            field_names=("RMWKUP",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=9,
            fallback_bit_width=1,
        ),
        address_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVCTRL",
            field_names=("ADDEN",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        address_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVCTRL",
            field_names=("UADD",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=0,
            fallback_bit_width=7,
        ),
        clock_usable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("CLKUSABLE",),
            fallback_register_offset=0x0804,
            fallback_bit_offset=14,
            fallback_bit_width=1,
        ),
    )


def _build_usb_rows(context: _SemanticContext) -> tuple[UsbSemanticRow, ...]:
    # USB controller hardware-feature lookup (added by
    # ``add-usb-semantic-traits``).  Keyed by ``controller_id`` so the row
    # builder below can enrich each register-level row with the static
    # silicon facts (base address, endpoint count, packet memory, fixed
    # pin assignment) that drive the alloy ``UsbDeviceController<T>`` HAL.
    usb_hw_by_id = {
        usb.controller_id: usb for usb in context.device.usb_controllers
    }

    import dataclasses as _dc

    def _enrich(row: UsbSemanticRow) -> UsbSemanticRow:
        hw = usb_hw_by_id.get(row.peripheral_name)
        if hw is None:
            return row
        return _dc.replace(
            row,
            hardware_present=True,
            base_address=hw.base_address,
            endpoint_count=hw.endpoint_count,
            supports_high_speed=hw.supports_high_speed,
            supports_dma=hw.supports_dma,
            crystalless=hw.crystalless,
            dpram_base_address=hw.dpram_base_address,
            dpram_size_bytes=hw.dpram_size_bytes,
            dma_channel_count=hw.dma_channel_count,
            dm_pin=hw.dm_pin,
            dp_pin=hw.dp_pin,
            clock_source=hw.clock_source,
        )

    rows: list[UsbSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("usb", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.usb.st-") or schema_id.startswith("alloy.otg_fs.st-"):
            rows.append(
                _enrich(
                    _st_usb_row(
                        context,
                        peripheral_name=peripheral.name,
                        schema_id=schema_id,
                    )
                )
            )
        elif schema_id.startswith("alloy.usb.microchip-") or schema_id.startswith(
            "alloy.usbhs.microchip-"
        ):
            rows.append(
                _enrich(
                    _microchip_usb_row(
                        context,
                        peripheral_name=peripheral.name,
                        schema_id=schema_id,
                    )
                )
            )
    # Synthesize register-empty rows for hardware that has a USB controller
    # but no register-level schema yet (e.g. RP2040, ESP32-S3 OTG, where the
    # alloy.usb.* schema admission lands in a follow-on change).  These rows
    # surface ``kPresent = true`` to the alloy HAL so consumers see the
    # silicon facts even before the register schema is admitted.
    covered = {row.peripheral_name for row in rows}
    invalid_reg = _invalid_register_ref()
    invalid_field = _invalid_field_ref()
    runtime_peripheral_names = {
        peripheral.name
        for peripheral in context.runtime_peripherals_by_class.get("usb", ())
    }
    for hw in context.device.usb_controllers:
        if hw.controller_id in covered:
            continue
        # Skip synthesizing a row when the controller's peripheral is not
        # admitted to the runtime-lite ``PeripheralId`` enum — referencing a
        # missing enum value would break the published consumer-smoke build.
        # The USB hardware-feature facts still surface via the IR JSON; the
        # alloy HAL just can't pick them up by ``PeripheralId`` until the
        # peripheral itself is admitted (separate proposal).
        if hw.controller_id not in runtime_peripheral_names:
            continue
        peripheral = context.peripheral_by_name.get(hw.controller_id)
        schema_id = peripheral.backend_schema_id if peripheral is not None else None
        rows.append(
            UsbSemanticRow(
                peripheral_name=hw.controller_id,
                schema_id=schema_id,
                supports_device_mode=True,
                supports_host_mode=hw.supports_host_mode,
                has_dedicated_endpoint_config=False,
                has_clock_freeze=False,
                control_reg=invalid_reg,
                status_reg=invalid_reg,
                interrupt_status_reg=invalid_reg,
                interrupt_mask_reg=invalid_reg,
                device_control_reg=invalid_reg,
                device_status_reg=invalid_reg,
                device_interrupt_status_reg=invalid_reg,
                device_interrupt_mask_reg=invalid_reg,
                device_interrupt_enable_reg=invalid_reg,
                device_interrupt_disable_reg=invalid_reg,
                host_control_reg=invalid_reg,
                host_status_reg=invalid_reg,
                host_interrupt_status_reg=invalid_reg,
                host_interrupt_mask_reg=invalid_reg,
                host_interrupt_enable_reg=invalid_reg,
                host_interrupt_disable_reg=invalid_reg,
                enable_field=invalid_field,
                freeze_clock_field=invalid_field,
                force_device_mode_field=invalid_field,
                force_host_mode_field=invalid_field,
                mode_status_field=invalid_field,
                soft_disconnect_field=invalid_field,
                remote_wakeup_field=invalid_field,
                address_enable_field=invalid_field,
                address_field=invalid_field,
                clock_usable_field=invalid_field,
                hardware_present=True,
                base_address=hw.base_address,
                endpoint_count=hw.endpoint_count,
                supports_high_speed=hw.supports_high_speed,
                supports_dma=hw.supports_dma,
                crystalless=hw.crystalless,
                dpram_base_address=hw.dpram_base_address,
                dpram_size_bytes=hw.dpram_size_bytes,
                dma_channel_count=hw.dma_channel_count,
                dm_pin=hw.dm_pin,
                dp_pin=hw.dp_pin,
                clock_source=hw.clock_source,
            )
        )
    return tuple(rows)


def _microchip_qspi_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> QspiSemanticRow:
    has_dma = any(
        binding.peripheral == peripheral_name and binding.signal in {"RX", "TX"}
        for binding in _runtime_lite_dma_bindings(context.device)
    )
    return QspiSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        supports_spi_mode=True,
        supports_memory_mode=True,
        has_scrambling=True,
        has_dma=has_dma,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            fallback_offset=0x00,
        ),
        mode_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            fallback_offset=0x04,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            fallback_offset=0x10,
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            fallback_offset=0x14,
        ),
        interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IDR",
            fallback_offset=0x18,
        ),
        interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IMR",
            fallback_offset=0x1C,
        ),
        serial_clock_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCR",
            fallback_offset=0x20,
        ),
        instruction_address_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IAR",
            fallback_offset=0x30,
        ),
        instruction_code_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ICR",
            fallback_offset=0x34,
        ),
        instruction_frame_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            fallback_offset=0x38,
        ),
        scrambling_mode_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SMR",
            fallback_offset=0x40,
        ),
        scrambling_key_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SKR",
            fallback_offset=0x44,
        ),
        receive_data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RDR",
            fallback_offset=0x08,
        ),
        transmit_data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TDR",
            fallback_offset=0x0C,
        ),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("QSPIEN",),
            fallback_register_offset=0x00,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        disable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("QSPIDIS",),
            fallback_register_offset=0x00,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        software_reset_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("SWRST",),
            fallback_register_offset=0x00,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        last_transfer_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("LASTXFER",),
            fallback_register_offset=0x00,
            fallback_bit_offset=24,
            fallback_bit_width=1,
        ),
        enabled_status_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("QSPIENS",),
            fallback_register_offset=0x10,
            fallback_bit_offset=24,
            fallback_bit_width=1,
        ),
        serial_memory_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("SMM",),
            fallback_register_offset=0x04,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        chip_select_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("CSMODE",),
            fallback_register_offset=0x04,
            fallback_bit_offset=4,
            fallback_bit_width=2,
        ),
        bits_per_transfer_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("NBBITS",),
            fallback_register_offset=0x04,
            fallback_bit_offset=8,
            fallback_bit_width=4,
        ),
        receive_ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("RDRF",),
            fallback_register_offset=0x10,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        transmit_ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("TDRE",),
            fallback_register_offset=0x10,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        transmit_empty_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("TXEMPTY",),
            fallback_register_offset=0x10,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        receive_ready_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("RDRF",),
            fallback_register_offset=0x14,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        transmit_ready_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("TDRE",),
            fallback_register_offset=0x14,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        transmit_empty_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("TXEMPTY",),
            fallback_register_offset=0x14,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        serial_clock_baud_rate_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCR",
            field_names=("SCBR",),
            fallback_register_offset=0x20,
            fallback_bit_offset=8,
            fallback_bit_width=8,
        ),
        instruction_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ICR",
            field_names=("INST",),
            fallback_register_offset=0x34,
            fallback_bit_offset=0,
            fallback_bit_width=8,
        ),
        address_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IAR",
            field_names=("ADDR",),
            fallback_register_offset=0x30,
            fallback_bit_offset=0,
            fallback_bit_width=32,
        ),
        width_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("WIDTH",),
            fallback_register_offset=0x38,
            fallback_bit_offset=0,
            fallback_bit_width=3,
        ),
        instruction_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("INSTEN",),
            fallback_register_offset=0x38,
            fallback_bit_offset=4,
            fallback_bit_width=1,
        ),
        address_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("ADDREN",),
            fallback_register_offset=0x38,
            fallback_bit_offset=5,
            fallback_bit_width=1,
        ),
        option_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("OPTEN",),
            fallback_register_offset=0x38,
            fallback_bit_offset=6,
            fallback_bit_width=1,
        ),
        data_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("DATAEN",),
            fallback_register_offset=0x38,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        transfer_type_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("TFRTYP",),
            fallback_register_offset=0x38,
            fallback_bit_offset=12,
            fallback_bit_width=2,
        ),
        continuous_read_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("CRM",),
            fallback_register_offset=0x38,
            fallback_bit_offset=14,
            fallback_bit_width=1,
        ),
        dummy_cycles_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("NBDUM",),
            fallback_register_offset=0x38,
            fallback_bit_offset=16,
            fallback_bit_width=5,
        ),
        scrambling_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SMR",
            field_names=("SCREN",),
            fallback_register_offset=0x40,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
    )


def _build_qspi_rows(context: _SemanticContext) -> tuple[QspiSemanticRow, ...]:
    rows: list[QspiSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("qspi", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.qspi.microchip-"):
            rows.append(
                _microchip_qspi_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
    return tuple(rows)


def _microchip_hsmci_sdmmc_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> SdmmcSemanticRow:
    has_dma = any(
        binding.peripheral == peripheral_name and binding.signal in {"RX", "TX"}
        for binding in _runtime_lite_dma_bindings(context.device)
    )
    return SdmmcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        supports_1bit=True,
        supports_4bit=True,
        supports_8bit=False,
        has_dma=has_dma,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            fallback_offset=0x00,
        ),
        mode_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            fallback_offset=0x04,
        ),
        data_timeout_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DTOR",
            fallback_offset=0x08,
        ),
        sd_card_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SDCR",
            fallback_offset=0x0C,
        ),
        argument_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ARGR",
            fallback_offset=0x10,
        ),
        command_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            fallback_offset=0x14,
        ),
        block_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BLKR",
            fallback_offset=0x18,
        ),
        completion_timeout_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CSTOR",
            fallback_offset=0x1C,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            fallback_offset=0x40,
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            fallback_offset=0x44,
        ),
        interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IDR",
            fallback_offset=0x48,
        ),
        interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IMR",
            fallback_offset=0x4C,
        ),
        dma_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DMA",
            fallback_offset=0x50,
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFG",
            fallback_offset=0x54,
        ),
        read_data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RDR",
            fallback_offset=0x30,
        ),
        write_data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TDR",
            fallback_offset=0x34,
        ),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("MCIEN",),
            fallback_register_offset=0x00,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        disable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("MCIDIS",),
            fallback_register_offset=0x00,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        power_save_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("PWSEN",),
            fallback_register_offset=0x00,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        power_save_disable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("PWSDIS",),
            fallback_register_offset=0x00,
            fallback_bit_offset=3,
            fallback_bit_width=1,
        ),
        software_reset_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("SWRST",),
            fallback_register_offset=0x00,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        clock_divider_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("CLKDIV",),
            fallback_register_offset=0x04,
            fallback_bit_offset=0,
            fallback_bit_width=8,
        ),
        power_save_divider_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("PWSDIV",),
            fallback_register_offset=0x04,
            fallback_bit_offset=8,
            fallback_bit_width=3,
        ),
        read_proof_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("RDPROOF",),
            fallback_register_offset=0x04,
            fallback_bit_offset=11,
            fallback_bit_width=1,
        ),
        write_proof_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WRPROOF",),
            fallback_register_offset=0x04,
            fallback_bit_offset=12,
            fallback_bit_width=1,
        ),
        slot_select_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SDCR",
            field_names=("SDCSEL",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        bus_width_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SDCR",
            field_names=("SDCBUS",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=6,
            fallback_bit_width=2,
        ),
        argument_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ARGR",
            field_names=("ARG",),
            fallback_register_offset=0x10,
            fallback_bit_offset=0,
            fallback_bit_width=32,
        ),
        command_index_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("CMDNB",),
            fallback_register_offset=0x14,
            fallback_bit_offset=0,
            fallback_bit_width=6,
        ),
        response_type_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("RSPTYP",),
            fallback_register_offset=0x14,
            fallback_bit_offset=6,
            fallback_bit_width=2,
        ),
        special_command_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("SPCMD",),
            fallback_register_offset=0x14,
            fallback_bit_offset=8,
            fallback_bit_width=3,
        ),
        open_drain_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("OPDCMD",),
            fallback_register_offset=0x14,
            fallback_bit_offset=11,
            fallback_bit_width=1,
        ),
        max_latency_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("MAXLAT",),
            fallback_register_offset=0x14,
            fallback_bit_offset=12,
            fallback_bit_width=1,
        ),
        transfer_command_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("TRCMD",),
            fallback_register_offset=0x14,
            fallback_bit_offset=16,
            fallback_bit_width=2,
        ),
        transfer_direction_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("TRDIR",),
            fallback_register_offset=0x14,
            fallback_bit_offset=18,
            fallback_bit_width=1,
        ),
        transfer_type_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("TRTYP",),
            fallback_register_offset=0x14,
            fallback_bit_offset=19,
            fallback_bit_width=3,
        ),
        sdio_interrupt_command_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("IOSPCMD",),
            fallback_register_offset=0x14,
            fallback_bit_offset=24,
            fallback_bit_width=2,
        ),
        atacs_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("ATACS",),
            fallback_register_offset=0x14,
            fallback_bit_offset=26,
            fallback_bit_width=1,
        ),
        block_count_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BLKR",
            field_names=("BCNT",),
            fallback_register_offset=0x18,
            fallback_bit_offset=0,
            fallback_bit_width=16,
        ),
        block_length_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BLKR",
            field_names=("BLKLEN",),
            fallback_register_offset=0x18,
            fallback_bit_offset=16,
            fallback_bit_width=16,
        ),
        command_ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("CMDRDY",),
            fallback_register_offset=0x40,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        rx_ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("RXRDY",),
            fallback_register_offset=0x40,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        tx_ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("TXRDY",),
            fallback_register_offset=0x40,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        transfer_done_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("XFRDONE",),
            fallback_register_offset=0x40,
            fallback_bit_offset=27,
            fallback_bit_width=1,
        ),
        not_busy_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("NOTBUSY",),
            fallback_register_offset=0x40,
            fallback_bit_offset=5,
            fallback_bit_width=1,
        ),
        dma_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DMA",
            field_names=("DMAEN",),
            fallback_register_offset=0x50,
            fallback_bit_offset=8,
            fallback_bit_width=1,
        ),
    )


def _build_sdmmc_rows(context: _SemanticContext) -> tuple[SdmmcSemanticRow, ...]:
    rows: list[SdmmcSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("sdmmc", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.hsmci.microchip-"):
            rows.append(
                _microchip_hsmci_sdmmc_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
    return tuple(rows)


def _microchip_watchdog_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> WatchdogSemanticRow:
    is_reinforced = peripheral_name == "RSWDT"
    required_config_field = (
        _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("ALLONES",),
        )
        if is_reinforced
        else _invalid_field_ref()
    )
    return WatchdogSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_window=not is_reinforced,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
        ),
        prescaler_reg=_invalid_register_ref(),
        reload_reg=_invalid_register_ref(),
        window_reg=_invalid_register_ref(),
        enable_field=_invalid_field_ref(),
        disable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WDDIS",),
        ),
        restart_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("WDRSTT",),
        ),
        key_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("KEY",),
        ),
        timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WDV",),
        ),
        window_field=(
            _resolve_field_ref(
                context,
                peripheral_name=peripheral_name,
                register_name="MR",
                field_names=("WDD",),
            )
            if not is_reinforced
            else _invalid_field_ref()
        ),
        prescaler_field=_invalid_field_ref(),
        early_warning_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WDFIEN",),
        ),
        reset_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WDRSTEN",),
        ),
        status_prescaler_update_field=_invalid_field_ref(),
        status_reload_update_field=_invalid_field_ref(),
        status_window_update_field=_invalid_field_ref(),
        status_timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("WDUNF",),
        ),
        status_error_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("WDERR",),
        ),
        required_config_field=required_config_field,
        required_config_value=0xFFF if is_reinforced else 0,
        start_key_value=0,
        refresh_key_value=0xC4 if is_reinforced else 0xA5,
        unlock_key_value=0,
    )


def _nxp_wdog_watchdog_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> WatchdogSemanticRow:
    return WatchdogSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_window=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WRSR",
        ),
        prescaler_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        reload_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WSR",
        ),
        window_reg=_invalid_register_ref(context.peripheral_by_name[peripheral_name].base_address),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
            field_names=("WDE",),
        ),
        disable_field=_invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address),
        restart_field=_invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address),
        key_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WSR",
            field_names=("WSR",),
        ),
        timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
            field_names=("WT",),
        ),
        window_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
            field_names=("WDW",),
        ),
        prescaler_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        early_warning_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WICR",
            field_names=("WIE",),
        ),
        reset_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
            field_names=("SRS",),
        ),
        status_prescaler_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_reload_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_window_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WRSR",
            field_names=("TOUT",),
        ),
        status_error_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WRSR",
            field_names=("SFTW",),
        ),
        required_config_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        required_config_value=0,
        start_key_value=0,
        refresh_key_value=0x5555,
        unlock_key_value=0xC520,
    )


def _nxp_rtwdog_watchdog_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> WatchdogSemanticRow:
    return WatchdogSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_window=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
        ),
        prescaler_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        reload_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TOVAL",
        ),
        window_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WIN",
        ),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("EN",),
        ),
        disable_field=_invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address),
        restart_field=_invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address),
        key_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CNT",
            field_names=("CNTLOW",),
        ),
        timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TOVAL",
            field_names=("TOVALLOW",),
        ),
        window_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WIN",
            field_names=("WINLOW",),
        ),
        prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("PRES",),
        ),
        early_warning_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("INT",),
        ),
        reset_enable_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_prescaler_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_reload_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_window_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("FLG",),
        ),
        status_error_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        required_config_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("UPDATE",),
        ),
        required_config_value=1,
        start_key_value=0,
        refresh_key_value=0xA602,
        unlock_key_value=0xC520,
    )


def _st_iwdg_watchdog_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> WatchdogSemanticRow:
    window_field = _resolve_field_ref(
        context,
        peripheral_name=peripheral_name,
        register_name="WINR",
        field_names=("WIN",),
    )
    return WatchdogSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_window=window_field.valid,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="KR",
        ),
        config_reg=_invalid_register_ref(),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
        ),
        prescaler_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PR",
        ),
        reload_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RLR",
        ),
        window_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WINR",
        ),
        enable_field=_invalid_field_ref(),
        disable_field=_invalid_field_ref(),
        restart_field=_invalid_field_ref(),
        key_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="KR",
            field_names=("KEY",),
        ),
        timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RLR",
            field_names=("RL",),
        ),
        window_field=window_field,
        prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PR",
            field_names=("PR",),
        ),
        early_warning_interrupt_enable_field=_invalid_field_ref(),
        reset_enable_field=_invalid_field_ref(),
        status_prescaler_update_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("PVU",),
        ),
        status_reload_update_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("RVU",),
        ),
        status_window_update_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("WVU",),
        ),
        status_timeout_field=_invalid_field_ref(),
        status_error_field=_invalid_field_ref(),
        required_config_field=_invalid_field_ref(),
        required_config_value=0,
        start_key_value=0xCCCC,
        refresh_key_value=0xAAAA,
        unlock_key_value=0x5555,
    )


def _st_wwdg_watchdog_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> WatchdogSemanticRow:
    return WatchdogSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_window=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFR",
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
        ),
        prescaler_reg=_invalid_register_ref(),
        reload_reg=_invalid_register_ref(),
        window_reg=_invalid_register_ref(),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("WDGA",),
        ),
        disable_field=_invalid_field_ref(),
        restart_field=_invalid_field_ref(),
        key_field=_invalid_field_ref(),
        timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("T",),
        ),
        window_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFR",
            field_names=("W",),
        ),
        prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFR",
            field_names=("WDGTB",),
            fallback_register_offset=0x04,
            fallback_bit_offset=7,
            fallback_bit_width=2,
        ),
        early_warning_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFR",
            field_names=("EWI",),
        ),
        reset_enable_field=_invalid_field_ref(),
        status_prescaler_update_field=_invalid_field_ref(),
        status_reload_update_field=_invalid_field_ref(),
        status_window_update_field=_invalid_field_ref(),
        status_timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("EWIF",),
        ),
        status_error_field=_invalid_field_ref(),
        required_config_field=_invalid_field_ref(),
        required_config_value=0,
        start_key_value=0,
        refresh_key_value=0,
        unlock_key_value=0,
    )


def _build_watchdog_rows(context: _SemanticContext) -> tuple[WatchdogSemanticRow, ...]:
    rows: list[WatchdogSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("watchdog", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.watchdog.microchip-"):
            rows.append(
                _microchip_watchdog_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id.startswith("alloy.watchdog.st-iwdg"):
            rows.append(
                _st_iwdg_watchdog_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id.startswith("alloy.watchdog.st-wwdg"):
            rows.append(
                _st_wwdg_watchdog_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id == "alloy.watchdog.nxp-wdog":
            rows.append(
                _nxp_wdog_watchdog_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id == "alloy.watchdog.nxp-rtwdog":
            rows.append(
                _nxp_rtwdog_watchdog_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (WatchdogSemanticTraits<PeripheralId::) is satisfied for devices whose
            # Watchdog IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            rows.append(
                WatchdogSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    has_window=False,
                    control_reg=invalid_reg,
                    config_reg=invalid_reg,
                    status_reg=invalid_reg,
                    prescaler_reg=invalid_reg,
                    reload_reg=invalid_reg,
                    window_reg=invalid_reg,
                    enable_field=invalid_field,
                    disable_field=invalid_field,
                    restart_field=invalid_field,
                    key_field=invalid_field,
                    timeout_field=invalid_field,
                    window_field=invalid_field,
                    prescaler_field=invalid_field,
                    early_warning_interrupt_enable_field=invalid_field,
                    reset_enable_field=invalid_field,
                    status_prescaler_update_field=invalid_field,
                    status_reload_update_field=invalid_field,
                    status_window_update_field=invalid_field,
                    status_timeout_field=invalid_field,
                    status_error_field=invalid_field,
                    required_config_field=invalid_field,
                    required_config_value=0,
                    start_key_value=0,
                    refresh_key_value=0,
                    unlock_key_value=0,
                    is_stub=True,
                )
            )
    return tuple(rows)


def _st_timer_counter_bits(peripheral_name: str) -> int:
    return 32 if peripheral_name in {"TIM2", "TIM5"} else 16


def _st_timer_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> TimerSemanticRow:
    counter_bits = _st_timer_counter_bits(peripheral_name)
    advanced_timer = peripheral_name in {"TIM1", "TIM8"}

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

    base = context.peripheral_by_name[peripheral_name].base_address
    return TimerSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=counter_bits,
        channel_count=4,
        has_compare=True,
        has_capture=True,
        has_encoder=True,
        has_pwm=True,
        has_one_pulse=True,
        has_center_aligned=True,
        has_complementary_outputs=advanced_timer,
        has_deadtime=advanced_timer,
        has_break_input=advanced_timer,
        control_reg=reg("CR1", 0x00),
        status_reg=reg("SR", 0x10),
        event_reg=reg("EGR", 0x14),
        counter_reg=reg("CNT", 0x24),
        prescaler_reg=reg("PSC", 0x28),
        period_reg=reg("ARR", 0x2C),
        enable_field=field("CR1", ("CEN",), 0x00, 0),
        disable_field=_invalid_field_ref(base),
        module_disable_field=_invalid_field_ref(base),
        software_reset_field=_invalid_field_ref(base),
        start_field=_invalid_field_ref(base),
        stop_field=_invalid_field_ref(base),
        update_interrupt_enable_field=field("DIER", ("UIE",), 0x0C, 0),
        update_flag_field=field("SR", ("UIF",), 0x10, 0),
        update_generation_field=field("EGR", ("UG",), 0x14, 0),
        prescaler_field=field("PSC", ("PSC",), 0x28, 0, 16),
        period_field=field("ARR", ("ARR",), 0x2C, 0, counter_bits),
        one_pulse_field=field("CR1", ("OPM",), 0x00, 3),
        center_aligned_field=field("CR1", ("CMS",), 0x00, 5, 2),
        auto_reload_preload_field=field("CR1", ("ARPE",), 0x00, 7),
        clock_source_field=_invalid_field_ref(base),
        encoder_mode_field=field("SMCR", ("SMS",), 0x08, 0, 3),
        encoder_enable_field=_invalid_field_ref(base),
        encoder_position_enable_field=_invalid_field_ref(base),
        encoder_speed_enable_field=_invalid_field_ref(base),
        encoder_phase_edge_field=_invalid_field_ref(base),
        direction_field=field("CR1", ("DIR",), 0x00, 4),
    )


def _st_timer_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[TimerChannelSemanticRow, ...]:
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

    rows: list[TimerChannelSemanticRow] = []
    for channel_index in range(4):
        channel_number = channel_index + 1
        mode_register_name = "CCMR1_INPUT" if channel_index < 2 else "CCMR2_INPUT"
        mode_register_offset = 0x18 if channel_index < 2 else 0x1C
        slot_offset = 0 if channel_index % 2 == 0 else 8
        compare_offset = 0x34 + (channel_index * 0x04)
        rows.append(
            TimerChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_compare=True,
                supports_capture=True,
                supports_encoder_input=channel_index < 2,
                supports_pwm=True,
                supports_complementary_output=advanced_timer and channel_index < 3,
                control_reg=reg(mode_register_name, mode_register_offset),
                status_reg=reg("SR", 0x10),
                compare_reg=reg(f"CCR{channel_number}", compare_offset),
                secondary_compare_reg=_invalid_register_ref(base),
                period_reg=reg("ARR", 0x2C),
                counter_reg=reg("CNT", 0x24),
                capture_reg=reg(f"CCR{channel_number}", compare_offset),
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
                preload_field=field(
                    mode_register_name,
                    (f"OC{channel_number}PE",),
                    mode_register_offset,
                    3 + slot_offset,
                ),
                output_enable_field=field(
                    "CCER",
                    (f"CC{channel_number}E",),
                    0x20,
                    channel_index * 4,
                ),
                output_polarity_field=field(
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
                capture_select_field=field(
                    mode_register_name,
                    (f"CC{channel_number}S",),
                    mode_register_offset,
                    slot_offset,
                    2,
                ),
            )
        )
    return tuple(rows)


def _microchip_tc_timer_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> TimerSemanticRow:
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

    return TimerSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=32,
        channel_count=3,
        has_compare=True,
        has_capture=True,
        has_encoder=True,
        has_pwm=True,
        has_one_pulse=False,
        has_center_aligned=False,
        has_complementary_outputs=False,
        has_deadtime=False,
        has_break_input=False,
        control_reg=reg("CCR0", 0x00),
        status_reg=reg("SR0", 0x20),
        event_reg=reg("CCR0", 0x00),
        counter_reg=reg("CV0", 0x10),
        prescaler_reg=_invalid_register_ref(base),
        period_reg=reg("RC0", 0x1C),
        enable_field=field("CCR0", ("CLKEN",), 0x00, 0),
        disable_field=field("CCR0", ("CLKDIS",), 0x00, 1),
        module_disable_field=_invalid_field_ref(base),
        software_reset_field=_invalid_field_ref(base),
        start_field=field("CCR0", ("SWTRG",), 0x00, 2),
        stop_field=field("CCR0", ("CLKDIS",), 0x00, 1),
        update_interrupt_enable_field=field("IER0", ("CPCS",), 0x24, 4),
        update_flag_field=field("SR0", ("CPCS",), 0x20, 4),
        update_generation_field=field("CCR0", ("SWTRG",), 0x00, 2),
        prescaler_field=_invalid_field_ref(base),
        period_field=field("RC0", ("RC",), 0x1C, 0, 32),
        one_pulse_field=_invalid_field_ref(base),
        center_aligned_field=_invalid_field_ref(base),
        auto_reload_preload_field=_invalid_field_ref(base),
        clock_source_field=field("CMR0", ("TCCLKS",), 0x04, 0, 3),
        encoder_mode_field=_invalid_field_ref(base),
        encoder_enable_field=field("BMR", ("QDEN",), 0xC4, 8),
        encoder_position_enable_field=field("BMR", ("POSEN",), 0xC4, 9),
        encoder_speed_enable_field=field("BMR", ("SPEEDEN",), 0xC4, 10),
        encoder_phase_edge_field=field("BMR", ("EDGPHA",), 0xC4, 12),
        direction_field=field("QISR", ("DIR",), 0xD4, 8),
    )


def _microchip_tc_timer_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[TimerChannelSemanticRow, ...]:
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

    rows: list[TimerChannelSemanticRow] = []
    for channel_index in range(3):
        stride = channel_index * 0x40
        register_suffix = str(channel_index)
        rows.append(
            TimerChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_compare=True,
                supports_capture=True,
                supports_encoder_input=False,
                supports_pwm=True,
                supports_complementary_output=False,
                control_reg=reg(f"CCR{register_suffix}", 0x00 + stride),
                status_reg=reg(f"SR{register_suffix}", 0x20 + stride),
                compare_reg=reg(f"RA{register_suffix}", 0x14 + stride),
                secondary_compare_reg=reg(f"RB{register_suffix}", 0x18 + stride),
                period_reg=reg(f"RC{register_suffix}", 0x1C + stride),
                counter_reg=reg(f"CV{register_suffix}", 0x10 + stride),
                capture_reg=reg(f"RA{register_suffix}", 0x14 + stride),
                enable_field=field(f"CCR{register_suffix}", ("CLKEN",), 0x00 + stride, 0),
                interrupt_enable_field=field(
                    f"IER{register_suffix}",
                    ("CPCS",),
                    0x24 + stride,
                    4,
                ),
                interrupt_flag_field=field(
                    f"SR{register_suffix}",
                    ("CPCS",),
                    0x20 + stride,
                    4,
                ),
                mode_field=field(f"CMR{register_suffix}", ("WAVE",), 0x04 + stride, 15),
                preload_field=_invalid_field_ref(base),
                output_enable_field=_invalid_field_ref(base),
                output_polarity_field=_invalid_field_ref(base),
                complementary_output_enable_field=_invalid_field_ref(base),
                capture_select_field=_invalid_field_ref(base),
            )
        )
    return tuple(rows)


def _nxp_gpt_timer_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> TimerSemanticRow:
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

    return TimerSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=32,
        channel_count=1,
        has_compare=True,
        has_capture=True,
        has_encoder=False,
        has_pwm=False,
        has_one_pulse=False,
        has_center_aligned=False,
        has_complementary_outputs=False,
        has_deadtime=False,
        has_break_input=False,
        control_reg=reg("CR", 0x00),
        status_reg=reg("SR", 0x08),
        event_reg=reg("IR", 0x0C),
        counter_reg=reg("CNT", 0x24),
        prescaler_reg=reg("PR", 0x04),
        period_reg=reg("OCR1", 0x10),
        enable_field=field("CR", ("EN",), 0x00, 0),
        disable_field=_invalid_field_ref(base),
        module_disable_field=_invalid_field_ref(base),
        software_reset_field=field("CR", ("SWR",), 0x00, 15),
        start_field=_invalid_field_ref(base),
        stop_field=_invalid_field_ref(base),
        update_interrupt_enable_field=field("IR", ("OF1IE",), 0x0C, 0),
        update_flag_field=field("SR", ("OF1",), 0x08, 0),
        update_generation_field=_invalid_field_ref(base),
        prescaler_field=field("PR", ("PRESCALER",), 0x04, 0, 12),
        period_field=field("OCR1", ("OCR1",), 0x10, 0, 32),
        one_pulse_field=_invalid_field_ref(base),
        center_aligned_field=_invalid_field_ref(base),
        auto_reload_preload_field=_invalid_field_ref(base),
        clock_source_field=field("CR", ("CLKSRC",), 0x00, 6, 3),
        encoder_mode_field=_invalid_field_ref(base),
        encoder_enable_field=_invalid_field_ref(base),
        encoder_position_enable_field=_invalid_field_ref(base),
        encoder_speed_enable_field=_invalid_field_ref(base),
        encoder_phase_edge_field=_invalid_field_ref(base),
        direction_field=_invalid_field_ref(base),
    )


def _nxp_gpt_timer_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[TimerChannelSemanticRow, ...]:
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

    return (
        TimerChannelSemanticRow(
            peripheral_name=peripheral_name,
            channel_index=0,
            supports_compare=True,
            supports_capture=True,
            supports_encoder_input=False,
            supports_pwm=False,
            supports_complementary_output=False,
            control_reg=reg("CR", 0x00),
            status_reg=reg("SR", 0x08),
            compare_reg=reg("OCR1", 0x10),
            secondary_compare_reg=_invalid_register_ref(base),
            period_reg=reg("OCR1", 0x10),
            counter_reg=reg("CNT", 0x24),
            capture_reg=reg("ICR1", 0x1C),
            enable_field=field("CR", ("EN",), 0x00, 0),
            interrupt_enable_field=field("IR", ("OF1IE",), 0x0C, 0),
            interrupt_flag_field=field("SR", ("OF1",), 0x08, 0),
            mode_field=_invalid_field_ref(base),
            preload_field=_invalid_field_ref(base),
            output_enable_field=_invalid_field_ref(base),
            output_polarity_field=_invalid_field_ref(base),
            complementary_output_enable_field=_invalid_field_ref(base),
            capture_select_field=_invalid_field_ref(base),
        ),
    )


def _nxp_pit_timer_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> TimerSemanticRow:
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

    return TimerSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=32,
        channel_count=4,
        has_compare=False,
        has_capture=False,
        has_encoder=False,
        has_pwm=False,
        has_one_pulse=False,
        has_center_aligned=False,
        has_complementary_outputs=False,
        has_deadtime=False,
        has_break_input=False,
        control_reg=reg("TCTRL0", 0x108),
        status_reg=reg("TFLG0", 0x10C),
        event_reg=_invalid_register_ref(base),
        counter_reg=reg("CVAL0", 0x104),
        prescaler_reg=_invalid_register_ref(base),
        period_reg=reg("LDVAL0", 0x100),
        enable_field=field("TCTRL0", ("TEN",), 0x108, 0),
        disable_field=_invalid_field_ref(base),
        module_disable_field=field("MCR", ("MDIS",), 0x00, 1),
        software_reset_field=_invalid_field_ref(base),
        start_field=_invalid_field_ref(base),
        stop_field=_invalid_field_ref(base),
        update_interrupt_enable_field=field("TCTRL0", ("TIE",), 0x108, 1),
        update_flag_field=field("TFLG0", ("TIF",), 0x10C, 0),
        update_generation_field=_invalid_field_ref(base),
        prescaler_field=_invalid_field_ref(base),
        period_field=field("LDVAL0", ("TSV", "LDVAL"), 0x100, 0, 32),
        one_pulse_field=_invalid_field_ref(base),
        center_aligned_field=_invalid_field_ref(base),
        auto_reload_preload_field=_invalid_field_ref(base),
        clock_source_field=_invalid_field_ref(base),
        encoder_mode_field=_invalid_field_ref(base),
        encoder_enable_field=_invalid_field_ref(base),
        encoder_position_enable_field=_invalid_field_ref(base),
        encoder_speed_enable_field=_invalid_field_ref(base),
        encoder_phase_edge_field=_invalid_field_ref(base),
        direction_field=_invalid_field_ref(base),
    )


def _nxp_pit_timer_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[TimerChannelSemanticRow, ...]:
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

    rows: list[TimerChannelSemanticRow] = []
    for channel_index in range(4):
        base_offset = 0x100 + (channel_index * 0x10)
        rows.append(
            TimerChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_compare=False,
                supports_capture=False,
                supports_encoder_input=False,
                supports_pwm=False,
                supports_complementary_output=False,
                control_reg=reg(f"TCTRL{channel_index}", base_offset + 0x08),
                status_reg=reg(f"TFLG{channel_index}", base_offset + 0x0C),
                compare_reg=reg(f"LDVAL{channel_index}", base_offset + 0x00),
                secondary_compare_reg=_invalid_register_ref(base),
                period_reg=reg(f"LDVAL{channel_index}", base_offset + 0x00),
                counter_reg=reg(f"CVAL{channel_index}", base_offset + 0x04),
                capture_reg=_invalid_register_ref(base),
                enable_field=field(
                    f"TCTRL{channel_index}",
                    ("TEN",),
                    base_offset + 0x08,
                    0,
                ),
                interrupt_enable_field=field(
                    f"TCTRL{channel_index}",
                    ("TIE",),
                    base_offset + 0x08,
                    1,
                ),
                interrupt_flag_field=field(
                    f"TFLG{channel_index}",
                    ("TIF",),
                    base_offset + 0x0C,
                    0,
                ),
                mode_field=_invalid_field_ref(base),
                preload_field=_invalid_field_ref(base),
                output_enable_field=_invalid_field_ref(base),
                output_polarity_field=_invalid_field_ref(base),
                complementary_output_enable_field=_invalid_field_ref(base),
                capture_select_field=_invalid_field_ref(base),
            )
        )
    return tuple(rows)


def _build_timer_rows(
    context: _SemanticContext,
) -> tuple[tuple[TimerSemanticRow, ...], tuple[TimerChannelSemanticRow, ...]]:
    timer_rows: list[TimerSemanticRow] = []
    channel_rows: list[TimerChannelSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("timer", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.timer.st-"):
            timer_rows.append(
                _st_timer_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(_st_timer_channel_rows(context, peripheral_name=peripheral.name))
        elif schema_id == "alloy.timer.microchip-tc-zl":
            timer_rows.append(
                _microchip_tc_timer_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(
                _microchip_tc_timer_channel_rows(
                    context,
                    peripheral_name=peripheral.name,
                )
            )
        elif schema_id == "alloy.gpt.nxp-gpt":
            timer_rows.append(
                _nxp_gpt_timer_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(
                _nxp_gpt_timer_channel_rows(context, peripheral_name=peripheral.name)
            )
        elif schema_id == "alloy.pit.nxp-pit":
            timer_rows.append(
                _nxp_pit_timer_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(
                _nxp_pit_timer_channel_rows(context, peripheral_name=peripheral.name)
            )
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (TimerSemanticTraits<PeripheralId::) is satisfied for devices whose
            # Timer IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            timer_rows.append(
                TimerSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    counter_bits=0,
                    channel_count=0,
                    has_compare=False,
                    has_capture=False,
                    has_encoder=False,
                    has_pwm=False,
                    has_one_pulse=False,
                    has_center_aligned=False,
                    has_complementary_outputs=False,
                    has_deadtime=False,
                    has_break_input=False,
                    control_reg=invalid_reg,
                    status_reg=invalid_reg,
                    event_reg=invalid_reg,
                    counter_reg=invalid_reg,
                    prescaler_reg=invalid_reg,
                    period_reg=invalid_reg,
                    enable_field=invalid_field,
                    disable_field=invalid_field,
                    module_disable_field=invalid_field,
                    software_reset_field=invalid_field,
                    start_field=invalid_field,
                    stop_field=invalid_field,
                    update_interrupt_enable_field=invalid_field,
                    update_flag_field=invalid_field,
                    update_generation_field=invalid_field,
                    prescaler_field=invalid_field,
                    period_field=invalid_field,
                    one_pulse_field=invalid_field,
                    center_aligned_field=invalid_field,
                    auto_reload_preload_field=invalid_field,
                    clock_source_field=invalid_field,
                    encoder_mode_field=invalid_field,
                    encoder_enable_field=invalid_field,
                    encoder_position_enable_field=invalid_field,
                    encoder_speed_enable_field=invalid_field,
                    encoder_phase_edge_field=invalid_field,
                    direction_field=invalid_field,
                    is_stub=True,
                )
            )
            # Add a single stub channel row so the artifact contract check for
            # TimerChannelSemanticTraits<PeripheralId:: is satisfied.
            channel_rows.append(
                TimerChannelSemanticRow(
                    peripheral_name=peripheral.name,
                    channel_index=0,
                    supports_compare=False,
                    supports_capture=False,
                    supports_encoder_input=False,
                    supports_pwm=False,
                    supports_complementary_output=False,
                    control_reg=invalid_reg,
                    status_reg=invalid_reg,
                    compare_reg=invalid_reg,
                    secondary_compare_reg=invalid_reg,
                    period_reg=invalid_reg,
                    counter_reg=invalid_reg,
                    capture_reg=invalid_reg,
                    enable_field=invalid_field,
                    interrupt_enable_field=invalid_field,
                    interrupt_flag_field=invalid_field,
                    mode_field=invalid_field,
                    preload_field=invalid_field,
                    output_enable_field=invalid_field,
                    output_polarity_field=invalid_field,
                    complementary_output_enable_field=invalid_field,
                    capture_select_field=invalid_field,
                )
            )
    return tuple(timer_rows), tuple(channel_rows)


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
    return tuple(pwm_rows), tuple(channel_rows)


def _emit_driver_semantics_common_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    body = "\n".join(
        [
            "struct RuntimeRegisterRef {",
            "  RegisterId register_id = RegisterId::none;",
            "  std::uintptr_t base_address = 0u;",
            "  std::uint32_t offset_bytes = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct RuntimeFieldRef {",
            "  FieldId field_id = FieldId::none;",
            "  RuntimeRegisterRef reg{};",
            "  std::uint16_t bit_offset = 0u;",
            "  std::uint16_t bit_width = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct RuntimeIndexedFieldRef {",
            "  std::uintptr_t base_address = 0u;",
            "  std::uint32_t base_offset_bytes = 0u;",
            "  std::uint32_t stride_bytes = 0u;",
            "  std::uint16_t bit_offset = 0u;",
            "  std::uint16_t bit_width = 0u;",
            "  std::uint16_t bit_stride_bits = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "inline constexpr RuntimeRegisterRef kInvalidRegisterRef{};",
            "inline constexpr RuntimeFieldRef kInvalidFieldRef{};",
            "inline constexpr RuntimeIndexedFieldRef kInvalidIndexedFieldRef{};",
            "",
            "// ADC trait support types (added by add-full-adc-coverage).",
            "// Apps consuming the runtime use these to generate high-level helpers",
            "// like readTemperature() / readVdd() with full compile-time validation.",
            "enum class InternalAdcChannelKind : std::uint8_t {",
            "  none,",
            "  temperature_sensor,",
            "  vrefint,",
            "  vbat,",
            "  opamp_output,",
            "  dac_output,",
            "};",
            "",
            "enum class AdcCalibrationKind : std::uint8_t {",
            "  none,",
            "  vrefint_cal,",
            "  ts_cal_low,",
            "  ts_cal_high,",
            "  sigrow_sref,",
            "  sigrow_tempsense_low,",
            "  sigrow_tempsense_high,",
            "  efuse_init_code,",
            "};",
            "",
            "enum class AdcExternalTriggerSource : std::uint8_t {",
            "  none,",
            "  software,",
            "  tim1_cc1,",
            "  tim1_cc2,",
            "  tim1_cc3,",
            "  tim1_cc4,",
            "  tim1_trgo,",
            "  tim1_trgo2,",
            "  tim2_trgo,",
            "  tim3_trgo,",
            "  tim4_trgo,",
            "  tim6_trgo,",
            "  tim7_trgo,",
            "  tim15_trgo,",
            "  tim16_trgo,",
            "  exti11,",
            "  exti15,",
            "  gpt1_compare1,",
            "  gpt2_compare1,",
            "  xbar_in0,",
            "  xbar_in1,",
            "  pwm0_compare,",
            "  pwm1_compare,",
            "};",
            "",
            "enum class AdcDmaMode : std::uint8_t {",
            "  none,",
            "  one_shot,",
            "  circular,",
            "};",
            "",
            "struct InternalAdcChannel {",
            "  InternalAdcChannelKind kind = InternalAdcChannelKind::none;",
            "  std::uint32_t channel_index = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct CalibrationDataPoint {",
            "  AdcCalibrationKind kind = AdcCalibrationKind::none;",
            "  RuntimeRegisterRef location{};",
            "  std::int32_t semantic_constant = 0;",
            "  bool valid = false;",
            "};",
            "",
            "struct CalibrationContext {",
            "  std::int16_t cal_temp_low_celsius = 0;",
            "  std::int16_t cal_temp_high_celsius = 0;",
            "  std::uint16_t cal_voltage_mv = 0u;",
            "  std::uint16_t vrefint_nominal_mv = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcResolutionOption {",
            "  std::uint8_t bits = 0u;",
            "  std::uint8_t field_value = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcSampleTimeOption {",
            "  // ``cycles_q8`` carries the cycle count in Q8.8 fixed-point so",
            "  // fractional cycles (1.5, 7.5, ...) survive without floats.  Apps",
            "  // do ``cycles_q8 / 256.0f`` to recover a float, or compare integers.",
            "  // 32-bit holds up to 16.7M cycles which covers every documented",
            "  // ADC sample time across admitted vendors (STM32F4 ADC sample 480",
            "  // cycles → 122880 in Q8.8 fixed-point — exceeds uint16_t).",
            "  std::uint32_t cycles_q8 = 0u;",
            "  std::uint8_t field_value = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcOversamplingOption {",
            "  std::uint16_t ratio = 0u;",
            "  std::uint8_t field_value = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcExternalTrigger {",
            "  AdcExternalTriggerSource source = AdcExternalTriggerSource::none;",
            "  std::uint8_t extsel_value = 0u;",
            "  std::uint8_t exten_polarity_default = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcDmaBinding {",
            "  // Source ADC peripheral name + DMA controller / route descriptor.",
            "  // ``data_register`` mirrors the ADC trait's kDataRegister so DMA",
            "  // configuration code can pull the source address without a second",
            "  // lookup.  ``binding_id`` cross-references the existing",
            "  // ``DmaSemanticTraits`` table when the consumer wants the full",
            "  // DMA route/channel descriptor.",
            "  PeripheralId controller_peripheral = PeripheralId::none;",
            "  DmaControllerId controller_id = DmaControllerId::none;",
            "  DmaBindingId binding_id = DmaBindingId::none;",
            "  std::uint8_t request_value = 0u;",
            "  RuntimeRegisterRef data_register{};",
            "  std::uint8_t transfer_width_bits = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcDmaModeOption {",
            "  AdcDmaMode mode = AdcDmaMode::none;",
            "  std::uint8_t field_value = 0u;",
            "  bool valid = false;",
            "};",
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
            "#include <cstdint>",
            '#include "../peripheral_instances.hpp"',
            '#include "../registers.hpp"',
            '#include "../register_fields.hpp"',
            '#include "../dma_bindings.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            COMMON_DRIVER_HEADER,
        ),
        content=content,
    )


def _emit_gpio_semantics_header(*, family_dir: str, device: CanonicalDeviceIR) -> EmittedArtifact:
    context = _context(device)
    rows = _build_gpio_rows(context)
    # Map from PinId enum identifier → AF descriptor list, for the pin-AF
    # specializations contributed by ``fill-gpio-semantic-gaps``.
    af_pins_by_id: dict[str, GpioPinDescriptor] = {
        _enum_identifier(pin.pin_id): pin for pin in device.gpio_pins
    }
    trait_lines = [
        "template<PinId Id>",
        "struct GpioSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr PeripheralId kPeripheralId = PeripheralId::none;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr std::uint32_t kLineIndex = 0u;",
        "  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInputField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputValueField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputSetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputResetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioOutputEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioOutputDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioSetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioClearField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioInputStateField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioDriveEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioDriveDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullUpEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullUpDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullDownEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullDownDisableField = kInvalidFieldRef;",
        # Alternate-function topology (added by fill-gpio-semantic-gaps).
        "  static constexpr std::uint32_t kPortOffset = 0u;",
        "  static constexpr std::uint32_t kPinIndex = 0u;",
        "  static constexpr std::uint8_t kMaxAltFunction = 0u;",
        "  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};",
        "  static constexpr bool kIsInputOnly = false;",
        "};",
        "",
    ]
    def _af_lines(pin: GpioPinDescriptor | None) -> list[str]:
        if pin is None:
            return [
                "  static constexpr std::uint32_t kPortOffset = 0u;",
                "  static constexpr std::uint32_t kPinIndex = 0u;",
                "  static constexpr std::uint8_t kMaxAltFunction = 0u;",
                "  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};",
                "  static constexpr bool kIsInputOnly = false;",
            ]
        is_input_only = "true" if pin.is_input_only else "false"
        if not pin.alt_functions:
            return [
                f"  static constexpr std::uint32_t kPortOffset = {pin.port_offset:#010x}u;",
                f"  static constexpr std::uint32_t kPinIndex = {pin.pin_index}u;",
                "  static constexpr std::uint8_t kMaxAltFunction = 0u;",
                "  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};",
                f"  static constexpr bool kIsInputOnly = {is_input_only};",
            ]
        af_numbers = sorted({af.af_number for af in pin.alt_functions})
        af_array = ", ".join(f"{n}u" for n in af_numbers)
        return [
            f"  static constexpr std::uint32_t kPortOffset = {pin.port_offset:#010x}u;",
            f"  static constexpr std::uint32_t kPinIndex = {pin.pin_index}u;",
            f"  static constexpr std::uint8_t kMaxAltFunction = {max(af_numbers)}u;",
            (
                f"  static constexpr std::array<std::uint8_t, {len(af_numbers)}> "
                f"kValidAltFunctions = {{{{{af_array}}}}};"
            ),
            f"  static constexpr bool kIsInputOnly = {is_input_only};",
        ]

    pin_rows: list[str] = []
    consumed_pin_ids: set[str] = set()
    for row in rows:
        pin_id = _enum_identifier(row.pin_name)
        consumed_pin_ids.add(pin_id)
        trait_lines.extend(
            [
                "template<>",
                f"struct GpioSemanticTraits<PinId::{pin_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr PeripheralId kPeripheralId = {_peripheral_ref(row.peripheral_name)};",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                f"  static constexpr std::uint32_t kLineIndex = {row.line_index}u;",
                f"  static constexpr RuntimeFieldRef kModeField = {_field_ref_expr(row.mode_field)};",
                f"  static constexpr RuntimeFieldRef kDirectionField = {_field_ref_expr(row.direction_field)};",
                f"  static constexpr RuntimeFieldRef kOutputTypeField = {_field_ref_expr(row.output_type_field)};",
                f"  static constexpr RuntimeFieldRef kPullField = {_field_ref_expr(row.pull_field)};",
                f"  static constexpr RuntimeFieldRef kInputField = {_field_ref_expr(row.input_field)};",
                f"  static constexpr RuntimeFieldRef kOutputValueField = {_field_ref_expr(row.output_value_field)};",
                f"  static constexpr RuntimeFieldRef kOutputSetField = {_field_ref_expr(row.output_set_field)};",
                f"  static constexpr RuntimeFieldRef kOutputResetField = {_field_ref_expr(row.output_reset_field)};",
                f"  static constexpr RuntimeFieldRef kPioEnableField = {_field_ref_expr(row.pio_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioOutputEnableField = {_field_ref_expr(row.pio_output_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioOutputDisableField = {_field_ref_expr(row.pio_output_disable_field)};",
                f"  static constexpr RuntimeFieldRef kPioSetField = {_field_ref_expr(row.pio_set_field)};",
                f"  static constexpr RuntimeFieldRef kPioClearField = {_field_ref_expr(row.pio_clear_field)};",
                f"  static constexpr RuntimeFieldRef kPioInputStateField = {_field_ref_expr(row.pio_input_state_field)};",
                f"  static constexpr RuntimeFieldRef kPioDriveEnableField = {_field_ref_expr(row.pio_drive_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioDriveDisableField = {_field_ref_expr(row.pio_drive_disable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullUpEnableField = {_field_ref_expr(row.pio_pull_up_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullUpDisableField = {_field_ref_expr(row.pio_pull_up_disable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullDownEnableField = {_field_ref_expr(row.pio_pull_down_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullDownDisableField = {_field_ref_expr(row.pio_pull_down_disable_field)};",
                *_af_lines(af_pins_by_id.get(pin_id)),
                "};",
                "",
            ]
        )
        pin_rows.append(f"  PinId::{pin_id},")

    # AF-only specializations: pins that have alt-function topology but no
    # register-level GPIO row (typical for STM32G0 / STM32F4 today, where the
    # register-level GPIO emitter has not yet been wired up for the family).
    # These specializations expose ``kPresent = true`` and the four AF fields,
    # but leave register/field references invalid — alloy concept checks for
    # AF assignment use only the AF fields, so this is sufficient for the
    # ``add-gpio-hal`` compile-time pin-routing validation.
    for pin_id, pin in sorted(af_pins_by_id.items()):
        if pin_id in consumed_pin_ids:
            continue
        trait_lines.extend(
            [
                "template<>",
                f"struct GpioSemanticTraits<PinId::{pin_id}> {{",
                "  static constexpr bool kPresent = true;",
                "  static constexpr PeripheralId kPeripheralId = PeripheralId::none;",
                "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
                "  static constexpr std::uint32_t kLineIndex = 0u;",
                "  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kInputField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kOutputValueField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kOutputSetField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kOutputResetField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioOutputEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioOutputDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioSetField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioClearField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioInputStateField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioDriveEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioDriveDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioPullUpEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioPullUpDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioPullDownEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioPullDownDisableField = kInvalidFieldRef;",
                *_af_lines(pin),
                "};",
                "",
            ]
        )
        pin_rows.append(f"  PinId::{pin_id},")
    body = "\n".join(
        [
            *trait_lines,
            *_std_array_lines(
                type_name="PinId", variable_name="kGpioSemanticPins", row_lines=pin_rows
            ),
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
            "#include <cstdint>",
            '#include "common.hpp"',
            '#include "../pins.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, GPIO_DRIVER_HEADER),
        content=content,
    )


def _emit_peripheral_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
    header_name: str,
    trait_name: str,
    array_name: str,
    rows: tuple[
        (
            UartSemanticRow
            | I2cSemanticRow
            | SpiSemanticRow
            | AdcSemanticRow
            | DacSemanticRow
            | RtcSemanticRow
            | WatchdogSemanticRow
            | CanSemanticRow
            | EthSemanticRow
            | UsbSemanticRow
            | QspiSemanticRow
            | SdmmcSemanticRow
        ),
        ...,
    ],
    default_lines: list[str],
    specialization_builder,
    extra_body_lines: list[str] | None = None,
) -> EmittedArtifact:
    trait_lines = [
        "template<PeripheralId Id>",
        f"struct {trait_name} {{",
        *default_lines,
        "};",
        "",
    ]
    peripheral_rows: list[str] = []
    for row in rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        trait_lines.extend(
            [
                "template<>",
                f"struct {trait_name}<PeripheralId::{peripheral_id}> {{",
                *specialization_builder(row),
                "};",
                "",
            ]
        )
        if not getattr(row, "is_stub", False):
            peripheral_rows.append(f"  PeripheralId::{peripheral_id},")
    body_parts: list[str] = [
        *trait_lines,
        *_std_array_lines(
            type_name="PeripheralId",
            variable_name=array_name,
            row_lines=peripheral_rows,
        ),
    ]
    if extra_body_lines:
        body_parts.append("")
        body_parts.extend(extra_body_lines)
    body = "\n".join(body_parts)
    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        body,
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "common.hpp"',
            # ``../pins.hpp`` provides the typed ``PinId`` enum referenced by
            # USB ``kDmPin`` / ``kDpPin`` traits (added by
            # ``add-usb-semantic-traits``).  Other driver semantics headers
            # never use ``PinId`` so the include is a harmless extra but is
            # uniformly available across this layer.
            '#include "../pins.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, header_name),
        content=content,
    )


def _uart_specialization_builder(context: _SemanticContext):
    # Hardware-feature lookup added by ``fill-espressif-semantic-gaps``: when
    # the device IR carries a ``UartPeripheralDescriptor`` for a peripheral
    # whose register-level schema isn't admitted yet, the stub
    # specialization promotes ``kPresent`` to ``true`` and emits the
    # silicon facts (base address, FIFO depth, GPIO-matrix signal indices,
    # DMA support).  This keeps the alloy HAL's ``UartController<T>`` concept
    # workable on Espressif targets even before full register schemas land.
    uart_hw_by_id = {u.peripheral_id: u for u in context.device.uart_peripherals}

    def _hw_lines(row: UartSemanticRow) -> list[str]:
        hw = uart_hw_by_id.get(row.peripheral_name)
        if hw is None:
            base_address = 0
            peripheral = context.peripheral_by_name.get(row.peripheral_name)
            if peripheral is not None:
                base_address = peripheral.base_address
            return [
                "  static constexpr bool kHardwarePresent = false;",
                f"  static constexpr std::uintptr_t kBaseAddress = 0x{base_address:08X}u;",
                "  static constexpr std::uint16_t kFifoDepth = 0u;",
                "  static constexpr std::int16_t kTxSignalIdx = -1;",
                "  static constexpr std::int16_t kRxSignalIdx = -1;",
                "  static constexpr bool kSupportsDma = false;",
            ]
        # ``kBaseAddress`` is sourced from the peripheral IR (which mirrors
        # the SVD/ATDF) rather than the patch overlay so hand-typed patch
        # base addresses can never disagree with the silicon spec.  The
        # patch only carries hardware-feature facts the SVD doesn't
        # encode (FIFO depth, GPIO-matrix signal indices, DMA support).
        peripheral = context.peripheral_by_name.get(row.peripheral_name)
        base_address = peripheral.base_address if peripheral is not None else hw.base_address
        return [
            "  static constexpr bool kHardwarePresent = true;",
            f"  static constexpr std::uintptr_t kBaseAddress = 0x{base_address:08X}u;",
            f"  static constexpr std::uint16_t kFifoDepth = {hw.fifo_depth}u;",
            f"  static constexpr std::int16_t kTxSignalIdx = {hw.tx_signal_idx if hw.tx_signal_idx is not None else -1};",
            f"  static constexpr std::int16_t kRxSignalIdx = {hw.rx_signal_idx if hw.rx_signal_idx is not None else -1};",
            f"  static constexpr bool kSupportsDma = {'true' if hw.supports_dma else 'false'};",
        ]

    def _build(row: UartSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented.
            # ``kPresent`` flips to ``true`` when the device carries a
            # ``UartPeripheralDescriptor`` (added by
            # ``fill-espressif-semantic-gaps``) so the alloy HAL can drive
            # the controller via the hardware-feature constexprs even
            # without the register-level schema.
            kpresent = "true" if row.peripheral_name in uart_hw_by_id else "false"
            return [
                f"  static constexpr bool kPresent = {kpresent};",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                *_hw_lines(row),
                "  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kMrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kBrgrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kUsCrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kUsMrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kUsBrgrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kUsThrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kUeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kReField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPceField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kM0Field = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kM1Field = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kMField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTdrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRdrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxeIsrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxneIsrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTcIsrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxeSrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxneSrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTcSrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRstrxField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRsttxField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxdisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxdisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRststaField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kParField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kChmodeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCdField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxenField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxenField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxrdyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxrdyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxemptyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxchrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxchrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsRstrxField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsRsttxField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsRxdisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsTxdisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsRststaField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsUsartModeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsUsclksField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsChrlField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsCdField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsRxenField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsTxenField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsTxrdyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsRxrdyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsTxemptyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsTxchrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUsRxchrField = kInvalidFieldRef;",
            ]
        return [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            *_hw_lines(row),
            f"  static constexpr RuntimeRegisterRef kCr1Register = {_register_ref_expr(row.cr1_reg)};",
            f"  static constexpr RuntimeRegisterRef kCr2Register = {_register_ref_expr(row.cr2_reg)};",
            f"  static constexpr RuntimeRegisterRef kBrrRegister = {_register_ref_expr(row.brr_reg)};",
            f"  static constexpr RuntimeRegisterRef kIsrRegister = {_register_ref_expr(row.isr_reg)};",
            f"  static constexpr RuntimeRegisterRef kRdrRegister = {_register_ref_expr(row.rdr_reg)};",
            f"  static constexpr RuntimeRegisterRef kTdrRegister = {_register_ref_expr(row.tdr_reg)};",
            f"  static constexpr RuntimeRegisterRef kSrRegister = {_register_ref_expr(row.sr_reg)};",
            f"  static constexpr RuntimeRegisterRef kDrRegister = {_register_ref_expr(row.dr_reg)};",
            f"  static constexpr RuntimeRegisterRef kCrRegister = {_register_ref_expr(row.cr_reg)};",
            f"  static constexpr RuntimeRegisterRef kMrRegister = {_register_ref_expr(row.mr_reg)};",
            f"  static constexpr RuntimeRegisterRef kBrgrRegister = {_register_ref_expr(row.brgr_reg)};",
            f"  static constexpr RuntimeRegisterRef kThrRegister = {_register_ref_expr(row.thr_reg)};",
            f"  static constexpr RuntimeRegisterRef kUsCrRegister = {_register_ref_expr(row.us_cr_reg)};",
            f"  static constexpr RuntimeRegisterRef kUsMrRegister = {_register_ref_expr(row.us_mr_reg)};",
            f"  static constexpr RuntimeRegisterRef kUsBrgrRegister = {_register_ref_expr(row.us_brgr_reg)};",
            f"  static constexpr RuntimeRegisterRef kUsThrRegister = {_register_ref_expr(row.us_thr_reg)};",
            f"  static constexpr RuntimeFieldRef kUeField = {_field_ref_expr(row.ue_field)};",
            f"  static constexpr RuntimeFieldRef kReField = {_field_ref_expr(row.re_field)};",
            f"  static constexpr RuntimeFieldRef kTeField = {_field_ref_expr(row.te_field)};",
            f"  static constexpr RuntimeFieldRef kPceField = {_field_ref_expr(row.pce_field)};",
            f"  static constexpr RuntimeFieldRef kPsField = {_field_ref_expr(row.ps_field)};",
            f"  static constexpr RuntimeFieldRef kM0Field = {_field_ref_expr(row.m0_field)};",
            f"  static constexpr RuntimeFieldRef kM1Field = {_field_ref_expr(row.m1_field)};",
            f"  static constexpr RuntimeFieldRef kMField = {_field_ref_expr(row.m_field)};",
            f"  static constexpr RuntimeFieldRef kStopField = {_field_ref_expr(row.stop_field)};",
            f"  static constexpr RuntimeFieldRef kTdrField = {_field_ref_expr(row.tdr_field)};",
            f"  static constexpr RuntimeFieldRef kRdrField = {_field_ref_expr(row.rdr_field)};",
            f"  static constexpr RuntimeFieldRef kTxeIsrField = {_field_ref_expr(row.txe_isr_field)};",
            f"  static constexpr RuntimeFieldRef kRxneIsrField = {_field_ref_expr(row.rxne_isr_field)};",
            f"  static constexpr RuntimeFieldRef kTcIsrField = {_field_ref_expr(row.tc_isr_field)};",
            f"  static constexpr RuntimeFieldRef kTxeSrField = {_field_ref_expr(row.txe_sr_field)};",
            f"  static constexpr RuntimeFieldRef kRxneSrField = {_field_ref_expr(row.rxne_sr_field)};",
            f"  static constexpr RuntimeFieldRef kTcSrField = {_field_ref_expr(row.tc_sr_field)};",
            f"  static constexpr RuntimeFieldRef kDrField = {_field_ref_expr(row.dr_field)};",
            f"  static constexpr RuntimeFieldRef kRstrxField = {_field_ref_expr(row.rstrx_field)};",
            f"  static constexpr RuntimeFieldRef kRsttxField = {_field_ref_expr(row.rsttx_field)};",
            f"  static constexpr RuntimeFieldRef kRxdisField = {_field_ref_expr(row.rxdis_field)};",
            f"  static constexpr RuntimeFieldRef kTxdisField = {_field_ref_expr(row.txdis_field)};",
            f"  static constexpr RuntimeFieldRef kRststaField = {_field_ref_expr(row.rststa_field)};",
            f"  static constexpr RuntimeFieldRef kParField = {_field_ref_expr(row.par_field)};",
            f"  static constexpr RuntimeFieldRef kChmodeField = {_field_ref_expr(row.chmode_field)};",
            f"  static constexpr RuntimeFieldRef kCdField = {_field_ref_expr(row.cd_field)};",
            f"  static constexpr RuntimeFieldRef kRxenField = {_field_ref_expr(row.rxen_field)};",
            f"  static constexpr RuntimeFieldRef kTxenField = {_field_ref_expr(row.txen_field)};",
            f"  static constexpr RuntimeFieldRef kTxrdyField = {_field_ref_expr(row.txrdy_field)};",
            f"  static constexpr RuntimeFieldRef kRxrdyField = {_field_ref_expr(row.rxrdy_field)};",
            f"  static constexpr RuntimeFieldRef kTxemptyField = {_field_ref_expr(row.txempty_field)};",
            f"  static constexpr RuntimeFieldRef kTxchrField = {_field_ref_expr(row.txchr_field)};",
            f"  static constexpr RuntimeFieldRef kRxchrField = {_field_ref_expr(row.rxchr_field)};",
            f"  static constexpr RuntimeFieldRef kUsRstrxField = {_field_ref_expr(row.us_rstrx_field)};",
            f"  static constexpr RuntimeFieldRef kUsRsttxField = {_field_ref_expr(row.us_rsttx_field)};",
            f"  static constexpr RuntimeFieldRef kUsRxdisField = {_field_ref_expr(row.us_rxdis_field)};",
            f"  static constexpr RuntimeFieldRef kUsTxdisField = {_field_ref_expr(row.us_txdis_field)};",
            f"  static constexpr RuntimeFieldRef kUsRststaField = {_field_ref_expr(row.us_rststa_field)};",
            f"  static constexpr RuntimeFieldRef kUsUsartModeField = {_field_ref_expr(row.us_usart_mode_field)};",
            f"  static constexpr RuntimeFieldRef kUsUsclksField = {_field_ref_expr(row.us_usclks_field)};",
            f"  static constexpr RuntimeFieldRef kUsChrlField = {_field_ref_expr(row.us_chrl_field)};",
            f"  static constexpr RuntimeFieldRef kUsCdField = {_field_ref_expr(row.us_cd_field)};",
            f"  static constexpr RuntimeFieldRef kUsRxenField = {_field_ref_expr(row.us_rxen_field)};",
            f"  static constexpr RuntimeFieldRef kUsTxenField = {_field_ref_expr(row.us_txen_field)};",
            f"  static constexpr RuntimeFieldRef kUsTxrdyField = {_field_ref_expr(row.us_txrdy_field)};",
            f"  static constexpr RuntimeFieldRef kUsRxrdyField = {_field_ref_expr(row.us_rxrdy_field)};",
            f"  static constexpr RuntimeFieldRef kUsTxemptyField = {_field_ref_expr(row.us_txempty_field)};",
            f"  static constexpr RuntimeFieldRef kUsTxchrField = {_field_ref_expr(row.us_txchr_field)};",
            f"  static constexpr RuntimeFieldRef kUsRxchrField = {_field_ref_expr(row.us_rxchr_field)};",
        ]

    return _build


def _i2c_specialization_builder(context: _SemanticContext):
    def _build(row: I2cSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                "  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCcrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kTriseRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSr1Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSr2Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kIcrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kMmrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kIadrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCwgrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kRhrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kPeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAckField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kFreqField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCcrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kFsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDutyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTriseField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSbField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAddrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxneField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBtfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBerrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kArloField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBusyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDrDataField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSaddField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRdWrnField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kNbytesField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAutoendField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTcField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStopfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxdataField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxdataField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kNackfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBerrIsrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kArloIsrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStopcfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kNackcfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBerrcfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kArlocfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kMsenField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kMsdisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSvdisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSwrstField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kIadrszField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kMreadField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDadrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kIadrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCldivField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kChdivField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCkdivField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kHoldField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxcompField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxrdyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxrdyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kNackField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kArblstField = kInvalidFieldRef;",
            ]
        register_members = {
            "kCr1Register": row.cr1_reg,
            "kCr2Register": row.cr2_reg,
            "kCcrRegister": row.ccr_reg,
            "kTriseRegister": row.trise_reg,
            "kSr1Register": row.sr1_reg,
            "kSr2Register": row.sr2_reg,
            "kDrRegister": row.dr_reg,
            "kIcrRegister": row.icr_reg,
            "kCrRegister": row.cr_reg,
            "kMmrRegister": row.mmr_reg,
            "kIadrRegister": row.iadr_reg,
            "kCwgrRegister": row.cwgr_reg,
            "kSrRegister": row.sr_reg,
            "kRhrRegister": row.rhr_reg,
            "kThrRegister": row.thr_reg,
        }
        field_members = {
            "kPeField": row.pe_field,
            "kAckField": row.ack_field,
            "kStartField": row.start_field,
            "kStopField": row.stop_field,
            "kFreqField": row.freq_field,
            "kCcrField": row.ccr_field,
            "kFsField": row.fs_field,
            "kDutyField": row.duty_field,
            "kTriseField": row.trise_field,
            "kSbField": row.sb_field,
            "kAddrField": row.addr_field,
            "kTxeField": row.txe_field,
            "kRxneField": row.rxne_field,
            "kBtfField": row.btf_field,
            "kAfField": row.af_field,
            "kBerrField": row.berr_field,
            "kArloField": row.arlo_field,
            "kBusyField": row.busy_field,
            "kDrDataField": row.dr_data_field,
            "kSaddField": row.sadd_field,
            "kRdWrnField": row.rd_wrn_field,
            "kNbytesField": row.nbytes_field,
            "kAutoendField": row.autoend_field,
            "kTxisField": row.txis_field,
            "kTcField": row.tc_field,
            "kStopfField": row.stopf_field,
            "kTxdataField": row.txdata_field,
            "kRxdataField": row.rxdata_field,
            "kNackfField": row.nackf_field,
            "kBerrIsrField": row.berr_isr_field,
            "kArloIsrField": row.arlo_isr_field,
            "kStopcfField": row.stopcf_field,
            "kNackcfField": row.nackcf_field,
            "kBerrcfField": row.berrcf_field,
            "kArlocfField": row.arlocf_field,
            "kMsenField": row.msen_field,
            "kMsdisField": row.msdis_field,
            "kSvdisField": row.svdis_field,
            "kSwrstField": row.swrst_field,
            "kIadrszField": row.iadrsz_field,
            "kMreadField": row.mread_field,
            "kDadrField": row.dadr_field,
            "kIadrField": row.iadr_field,
            "kCldivField": row.cldiv_field,
            "kChdivField": row.chdiv_field,
            "kCkdivField": row.ckdiv_field,
            "kHoldField": row.hold_field,
            "kTxcompField": row.txcomp_field,
            "kRxrdyField": row.rxrdy_field,
            "kTxrdyField": row.txrdy_field,
            "kNackField": row.nack_field,
            "kArblstField": row.arblst_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        return lines

    return _build


def _spi_specialization_builder(context: _SemanticContext):
    # Hardware-feature lookup added by ``fill-espressif-semantic-gaps``.
    spi_hw_by_id = {s.peripheral_id: s for s in context.device.spi_peripherals}

    def _spi_hw_lines(row: SpiSemanticRow) -> list[str]:
        hw = spi_hw_by_id.get(row.peripheral_name)
        peripheral = context.peripheral_by_name.get(row.peripheral_name)
        base_address = peripheral.base_address if peripheral is not None else 0
        if hw is None:
            return [
                "  static constexpr bool kHardwarePresent = false;",
                f"  static constexpr std::uintptr_t kBaseAddress = 0x{base_address:08X}u;",
                "  static constexpr std::uint32_t kMaxClockHz = 0u;",
                "  static constexpr std::int16_t kMosiOutSignal = -1;",
                "  static constexpr std::int16_t kMisoInSignal = -1;",
                "  static constexpr std::int16_t kClkOutSignal = -1;",
                "  static constexpr std::int16_t kCsOutSignal = -1;",
                "  static constexpr bool kHasIomuxFastPath = false;",
                "  static constexpr std::int16_t kIomuxMosiPin = -1;",
                "  static constexpr std::int16_t kIomuxMisoPin = -1;",
                "  static constexpr std::int16_t kIomuxClkPin = -1;",
                "  static constexpr std::int16_t kIomuxCsPin = -1;",
                "  static constexpr bool kSupportsDma = false;",
            ]
        return [
            "  static constexpr bool kHardwarePresent = true;",
            f"  static constexpr std::uintptr_t kBaseAddress = 0x{base_address:08X}u;",
            f"  static constexpr std::uint32_t kMaxClockHz = {hw.max_clock_hz}u;",
            f"  static constexpr std::int16_t kMosiOutSignal = {hw.mosi_out_signal if hw.mosi_out_signal is not None else -1};",
            f"  static constexpr std::int16_t kMisoInSignal = {hw.miso_in_signal if hw.miso_in_signal is not None else -1};",
            f"  static constexpr std::int16_t kClkOutSignal = {hw.clk_out_signal if hw.clk_out_signal is not None else -1};",
            f"  static constexpr std::int16_t kCsOutSignal = {hw.cs_out_signal if hw.cs_out_signal is not None else -1};",
            f"  static constexpr bool kHasIomuxFastPath = {'true' if hw.has_iomux_fast_path else 'false'};",
            f"  static constexpr std::int16_t kIomuxMosiPin = {hw.iomux_mosi_pin if hw.iomux_mosi_pin is not None else -1};",
            f"  static constexpr std::int16_t kIomuxMisoPin = {hw.iomux_miso_pin if hw.iomux_miso_pin is not None else -1};",
            f"  static constexpr std::int16_t kIomuxClkPin = {hw.iomux_clk_pin if hw.iomux_clk_pin is not None else -1};",
            f"  static constexpr std::int16_t kIomuxCsPin = {hw.iomux_cs_pin if hw.iomux_cs_pin is not None else -1};",
            f"  static constexpr bool kSupportsDma = {'true' if hw.supports_dma else 'false'};",
        ]

    def _build(row: SpiSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented.
            # ``kPresent`` flips to ``true`` when the device IR carries an
            # ``SpiPeripheralDescriptor`` (added by
            # ``fill-espressif-semantic-gaps``).
            kpresent = "true" if row.peripheral_name in spi_hw_by_id else "false"
            return [
                f"  static constexpr bool kPresent = {kpresent};",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                *_spi_hw_lines(row),
                "  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kMrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCsrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kCphaField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCpolField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kMstrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSpeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kLsbfirstField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSsiField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSsmField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDffField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kFrxthField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxneField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBsyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDrDataField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSpienField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSpidisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSwrstField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPcsdecField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kModfdisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPcsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDlybcsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kNcphaField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBitsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kScbrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDlybsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDlybctField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTdreField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRdrfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxemptyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTdField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTdrPcsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRdField = kInvalidFieldRef;",
            ]
        register_members = {
            "kCr1Register": row.cr1_reg,
            "kCr2Register": row.cr2_reg,
            "kSrRegister": row.sr_reg,
            "kDrRegister": row.dr_reg,
            "kCrRegister": row.cr_reg,
            "kMrRegister": row.mr_reg,
            "kCsrRegister": row.csr_reg,
            "kTdrRegister": row.tdr_reg,
            "kRdrRegister": row.rdr_reg,
        }
        field_members = {
            "kCphaField": row.cpha_field,
            "kCpolField": row.cpol_field,
            "kMstrField": row.mstr_field,
            "kBrField": row.br_field,
            "kSpeField": row.spe_field,
            "kLsbfirstField": row.lsbfirst_field,
            "kSsiField": row.ssi_field,
            "kSsmField": row.ssm_field,
            "kDffField": row.dff_field,
            "kDsField": row.ds_field,
            "kFrxthField": row.frxth_field,
            "kTxeField": row.txe_field,
            "kRxneField": row.rxne_field,
            "kBsyField": row.bsy_field,
            "kDrDataField": row.dr_data_field,
            "kSpienField": row.spien_field,
            "kSpidisField": row.spidis_field,
            "kSwrstField": row.swrst_field,
            "kPsField": row.ps_field,
            "kPcsdecField": row.pcsdec_field,
            "kModfdisField": row.modfdis_field,
            "kPcsField": row.pcs_field,
            "kDlybcsField": row.dlybcs_field,
            "kNcphaField": row.ncpha_field,
            "kBitsField": row.bits_field,
            "kScbrField": row.scbr_field,
            "kDlybsField": row.dlybs_field,
            "kDlybctField": row.dlybct_field,
            "kTdreField": row.tdre_field,
            "kRdrfField": row.rdrf_field,
            "kTxemptyField": row.txempty_field,
            "kTdField": row.td_field,
            "kTdrPcsField": row.tdr_pcs_field,
            "kRdField": row.rd_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            *_spi_hw_lines(row),
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        return lines

    return _build


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
        return lines

    return _build


def _dac_specialization_builder(context: _SemanticContext):
    def _build(row: DacSemanticRow) -> list[str]:
        register_members = {
            "kControlRegister": row.control_reg,
            "kModeRegister": row.mode_reg,
            "kTriggerRegister": row.trigger_reg,
            "kChannelEnableRegister": row.channel_enable_reg,
            "kChannelDisableRegister": row.channel_disable_reg,
            "kChannelStatusRegister": row.channel_status_reg,
            "kDataRegister": row.data_reg,
        }
        field_members = {
            "kSoftwareResetField": row.software_reset_field,
            "kWordModeField": row.word_mode_field,
            "kPrescalerField": row.prescaler_field,
        }
        indexed_field_members = {
            "kChannelEnablePattern": row.channel_enable_pattern,
            "kChannelDisablePattern": row.channel_disable_pattern,
            "kChannelReadyPattern": row.channel_ready_pattern,
            "kTriggerEnablePattern": row.trigger_enable_pattern,
            "kTriggerSelectPattern": row.trigger_select_pattern,
            "kDataPattern": row.data_pattern,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr std::uint32_t kChannelCount = {row.channel_count}u;",
            "  static constexpr bool kHasHardwareTrigger = "
            + ("true" if row.has_hardware_trigger else "false")
            + ";",
            f"  static constexpr bool kHasDma = {'true' if row.has_dma else 'false'};",
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
        return lines

    return _build


def _dac_channel_specialization_lines(
    channel_rows: tuple[DacChannelSemanticRow, ...],
) -> list[str]:
    lines = [
        "template<PeripheralId Id, std::size_t ChannelIndex>",
        "struct DacChannelSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTriggerEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTriggerSelectField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataField = kInvalidFieldRef;",
        "};",
        "",
    ]
    for row in channel_rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        field_members = {
            "kEnableField": row.enable_field,
            "kDisableField": row.disable_field,
            "kReadyField": row.ready_field,
            "kTriggerEnableField": row.trigger_enable_field,
            "kTriggerSelectField": row.trigger_select_field,
            "kDataField": row.data_field,
        }
        lines.extend(
            [
                "template<>",
                f"struct DacChannelSemanticTraits<PeripheralId::{peripheral_id}, {row.channel_index}u> {{",
                "  static constexpr bool kPresent = true;",
            ]
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        lines.extend(["};", ""])
    return lines


def _rtc_specialization_builder(context: _SemanticContext):
    def _build(row: RtcSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                "  static constexpr bool kHasCalendar = false;",
                "  static constexpr bool kHasAlarm = false;",
                "  static constexpr bool kHasWriteProtection = false;",
                "  static constexpr std::uint32_t kWriteProtectDisableKey0 = 0u;",
                "  static constexpr std::uint32_t kWriteProtectDisableKey1 = 0u;",
                "  static constexpr std::uint32_t kWriteProtectEnableKey = 0u;",
                "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kTimeRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kDateRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kAlarmTimeRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kAlarmDateRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kClearRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kWriteProtectRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kHourModeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kInitReadyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kShadowBypassField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateTimeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateCalendarField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateAckField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAlarmEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAlarmInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSecondInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTimeEventInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCalendarEventInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusAlarmField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusSecondField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusTimeEventField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusCalendarEventField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusTamperErrorField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearAlarmField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearSecondField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearTimeEventField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearCalendarEventField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearTamperErrorField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kWriteProtectKeyField = kInvalidFieldRef;",
            ]
        register_members = {
            "kControlRegister": row.control_reg,
            "kModeRegister": row.mode_reg,
            "kStatusRegister": row.status_reg,
            "kTimeRegister": row.time_reg,
            "kDateRegister": row.date_reg,
            "kAlarmTimeRegister": row.alarm_time_reg,
            "kAlarmDateRegister": row.alarm_date_reg,
            "kInterruptEnableRegister": row.interrupt_enable_reg,
            "kInterruptDisableRegister": row.interrupt_disable_reg,
            "kInterruptMaskRegister": row.interrupt_mask_reg,
            "kClearRegister": row.clear_reg,
            "kWriteProtectRegister": row.write_protect_reg,
            "kPrescalerRegister": row.prescaler_reg,
        }
        field_members = {
            "kHourModeField": row.hour_mode_field,
            "kInitField": row.init_field,
            "kInitReadyField": row.init_ready_field,
            "kShadowBypassField": row.shadow_bypass_field,
            "kUpdateTimeField": row.update_time_field,
            "kUpdateCalendarField": row.update_calendar_field,
            "kUpdateAckField": row.update_ack_field,
            "kAlarmEnableField": row.alarm_enable_field,
            "kAlarmInterruptEnableField": row.alarm_interrupt_enable_field,
            "kSecondInterruptEnableField": row.second_interrupt_enable_field,
            "kTimeEventInterruptEnableField": row.time_event_interrupt_enable_field,
            "kCalendarEventInterruptEnableField": row.calendar_event_interrupt_enable_field,
            "kStatusAlarmField": row.status_alarm_field,
            "kStatusSecondField": row.status_second_field,
            "kStatusTimeEventField": row.status_time_event_field,
            "kStatusCalendarEventField": row.status_calendar_event_field,
            "kStatusTamperErrorField": row.status_tamper_error_field,
            "kClearAlarmField": row.clear_alarm_field,
            "kClearSecondField": row.clear_second_field,
            "kClearTimeEventField": row.clear_time_event_field,
            "kClearCalendarEventField": row.clear_calendar_event_field,
            "kClearTamperErrorField": row.clear_tamper_error_field,
            "kWriteProtectKeyField": row.write_protect_key_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr bool kHasCalendar = {'true' if row.has_calendar else 'false'};",
            f"  static constexpr bool kHasAlarm = {'true' if row.has_alarm else 'false'};",
            "  static constexpr bool kHasWriteProtection = "
            + ("true" if row.has_write_protection else "false")
            + ";",
            f"  static constexpr std::uint32_t kWriteProtectDisableKey0 = 0x{row.write_protect_disable_key0:08X}u;",
            f"  static constexpr std::uint32_t kWriteProtectDisableKey1 = 0x{row.write_protect_disable_key1:08X}u;",
            f"  static constexpr std::uint32_t kWriteProtectEnableKey = 0x{row.write_protect_enable_key:08X}u;",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        return lines

    return _build


def _watchdog_specialization_builder(context: _SemanticContext):
    def _build(row: WatchdogSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                "  static constexpr bool kHasWindow = false;",
                "  static constexpr std::uint32_t kRequiredConfigValue = 0u;",
                "  static constexpr std::uint32_t kStartKeyValue = 0u;",
                "  static constexpr std::uint32_t kRefreshKeyValue = 0u;",
                "  static constexpr std::uint32_t kUnlockKeyValue = 0u;",
                "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kReloadRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kWindowRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRestartField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kKeyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTimeoutField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kWindowField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEarlyWarningInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kResetEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusPrescalerUpdateField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusReloadUpdateField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusWindowUpdateField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusTimeoutField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusErrorField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRequiredConfigField = kInvalidFieldRef;",
            ]
        register_members = {
            "kControlRegister": row.control_reg,
            "kConfigRegister": row.config_reg,
            "kStatusRegister": row.status_reg,
            "kPrescalerRegister": row.prescaler_reg,
            "kReloadRegister": row.reload_reg,
            "kWindowRegister": row.window_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kDisableField": row.disable_field,
            "kRestartField": row.restart_field,
            "kKeyField": row.key_field,
            "kTimeoutField": row.timeout_field,
            "kWindowField": row.window_field,
            "kPrescalerField": row.prescaler_field,
            "kEarlyWarningInterruptEnableField": row.early_warning_interrupt_enable_field,
            "kResetEnableField": row.reset_enable_field,
            "kStatusPrescalerUpdateField": row.status_prescaler_update_field,
            "kStatusReloadUpdateField": row.status_reload_update_field,
            "kStatusWindowUpdateField": row.status_window_update_field,
            "kStatusTimeoutField": row.status_timeout_field,
            "kStatusErrorField": row.status_error_field,
            "kRequiredConfigField": row.required_config_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr bool kHasWindow = {'true' if row.has_window else 'false'};",
            f"  static constexpr std::uint32_t kRequiredConfigValue = 0x{row.required_config_value:08X}u;",
            f"  static constexpr std::uint32_t kStartKeyValue = 0x{row.start_key_value:08X}u;",
            f"  static constexpr std::uint32_t kRefreshKeyValue = 0x{row.refresh_key_value:08X}u;",
            f"  static constexpr std::uint32_t kUnlockKeyValue = 0x{row.unlock_key_value:08X}u;",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        return lines

    return _build


def _can_specialization_builder(context: _SemanticContext):
    def _build(row: CanSemanticRow) -> list[str]:
        register_members = {
            "kControlRegister": row.control_reg,
            "kNominalTimingRegister": row.nominal_timing_reg,
            "kDataTimingRegister": row.data_timing_reg,
            "kTestRegister": row.test_reg,
            "kErrorCounterRegister": row.error_counter_reg,
            "kProtocolStatusRegister": row.protocol_status_reg,
            "kInterruptRegister": row.interrupt_reg,
            "kInterruptEnableRegister": row.interrupt_enable_reg,
            "kInterruptLineSelectRegister": row.interrupt_line_select_reg,
            "kInterruptLineEnableRegister": row.interrupt_line_enable_reg,
            "kGlobalFilterRegister": row.global_filter_reg,
            "kStandardFilterConfigRegister": row.standard_filter_config_reg,
            "kExtendedFilterConfigRegister": row.extended_filter_config_reg,
            "kExtendedIdMaskRegister": row.extended_id_mask_reg,
            "kRxFifo0ConfigRegister": row.rx_fifo0_config_reg,
            "kRxFifo0StatusRegister": row.rx_fifo0_status_reg,
            "kRxFifo0AckRegister": row.rx_fifo0_ack_reg,
            "kTxBufferConfigRegister": row.tx_buffer_config_reg,
            "kTxFifoQueueStatusRegister": row.tx_fifo_queue_status_reg,
            "kTxBufferAddRequestRegister": row.tx_buffer_add_request_reg,
            "kTxBufferPendingRegister": row.tx_buffer_pending_reg,
            "kTxEventFifoConfigRegister": row.tx_event_fifo_config_reg,
            "kTxEventFifoStatusRegister": row.tx_event_fifo_status_reg,
            "kTxEventFifoAckRegister": row.tx_event_fifo_ack_reg,
        }
        field_members = {
            "kInitField": row.init_field,
            "kConfigEnableField": row.config_enable_field,
            "kRestrictedOperationField": row.restricted_operation_field,
            "kRestrictedOperationAckField": row.restricted_operation_ack_field,
            "kBusMonitorField": row.bus_monitor_field,
            "kFdOperationEnableField": row.fd_operation_enable_field,
            "kBitRateSwitchEnableField": row.bit_rate_switch_enable_field,
            "kNominalPrescalerField": row.nominal_prescaler_field,
            "kNominalTimeSeg1Field": row.nominal_time_seg1_field,
            "kNominalTimeSeg2Field": row.nominal_time_seg2_field,
            "kNominalSyncJumpWidthField": row.nominal_sync_jump_width_field,
            "kDataPrescalerField": row.data_prescaler_field,
            "kDataTimeSeg1Field": row.data_time_seg1_field,
            "kDataTimeSeg2Field": row.data_time_seg2_field,
            "kDataSyncJumpWidthField": row.data_sync_jump_width_field,
            "kRxFifo0NewInterruptField": row.rx_fifo0_new_interrupt_field,
            "kTxCompleteInterruptField": row.tx_complete_interrupt_field,
            "kTxEventFifoNewInterruptField": row.tx_event_fifo_new_interrupt_field,
            "kRxFifo0NewInterruptEnableField": row.rx_fifo0_new_interrupt_enable_field,
            "kTxCompleteInterruptEnableField": row.tx_complete_interrupt_enable_field,
            "kTxEventFifoNewInterruptEnableField": row.tx_event_fifo_new_interrupt_enable_field,
            "kRxFifo0FillLevelField": row.rx_fifo0_fill_level_field,
            "kRxFifo0GetIndexField": row.rx_fifo0_get_index_field,
            "kRxFifo0MessageLostField": row.rx_fifo0_message_lost_field,
            "kRxFifo0AckIndexField": row.rx_fifo0_ack_index_field,
            "kTxFifoQueuePutIndexField": row.tx_fifo_queue_put_index_field,
            "kTxFifoQueueFreeLevelField": row.tx_fifo_queue_free_level_field,
        }
        indexed_field_members = {
            "kTxBufferAddRequestPattern": row.tx_buffer_add_request_pattern,
            "kTxBufferPendingPattern": row.tx_buffer_pending_pattern,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            "  static constexpr bool kHasFlexibleDataRate = "
            + ("true" if row.has_flexible_data_rate else "false")
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
        return lines

    return _build


def _usb_pin_ref_expr(pin: str | None, *, known_pins: frozenset[str] | None = None) -> str:
    """Format a USB DM/DP pin reference as a typed ``PinId`` expression.

    Returns ``PinId::none`` for controllers with IO-matrix-routed pads
    (e.g. RP2040, where USB DP/DM are not on a fixed pin), AND when the
    pin is not present in the device's admitted ``PinId`` enum.  The
    latter handles the case where a USB controller's documented DM/DP
    pin is on a package variant that the current target's pin set
    doesn't admit (e.g. STM32F401RE without PA11/PA12 in the QFP
    pinout).
    """
    if pin is None:
        return "PinId::none"
    if known_pins is not None and pin not in known_pins:
        return "PinId::none"
    return f"PinId::{_enum_identifier(pin)}"


def _usb_specialization_builder(context: _SemanticContext):
    known_pins = frozenset(pin.name for pin in context.device.pins)

    def _build(row: UsbSemanticRow) -> list[str]:
        register_members = {
            "kControlRegister": row.control_reg,
            "kStatusRegister": row.status_reg,
            "kInterruptStatusRegister": row.interrupt_status_reg,
            "kInterruptMaskRegister": row.interrupt_mask_reg,
            "kDeviceControlRegister": row.device_control_reg,
            "kDeviceStatusRegister": row.device_status_reg,
            "kDeviceInterruptStatusRegister": row.device_interrupt_status_reg,
            "kDeviceInterruptMaskRegister": row.device_interrupt_mask_reg,
            "kDeviceInterruptEnableRegister": row.device_interrupt_enable_reg,
            "kDeviceInterruptDisableRegister": row.device_interrupt_disable_reg,
            "kHostControlRegister": row.host_control_reg,
            "kHostStatusRegister": row.host_status_reg,
            "kHostInterruptStatusRegister": row.host_interrupt_status_reg,
            "kHostInterruptMaskRegister": row.host_interrupt_mask_reg,
            "kHostInterruptEnableRegister": row.host_interrupt_enable_reg,
            "kHostInterruptDisableRegister": row.host_interrupt_disable_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kFreezeClockField": row.freeze_clock_field,
            "kForceDeviceModeField": row.force_device_mode_field,
            "kForceHostModeField": row.force_host_mode_field,
            "kModeStatusField": row.mode_status_field,
            "kSoftDisconnectField": row.soft_disconnect_field,
            "kRemoteWakeupField": row.remote_wakeup_field,
            "kAddressEnableField": row.address_enable_field,
            "kAddressField": row.address_field,
            "kClockUsableField": row.clock_usable_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            "  static constexpr bool kSupportsDeviceMode = "
            + ("true" if row.supports_device_mode else "false")
            + ";",
            "  static constexpr bool kSupportsHostMode = "
            + ("true" if row.supports_host_mode else "false")
            + ";",
            "  static constexpr bool kHasDedicatedEndpointConfig = "
            + ("true" if row.has_dedicated_endpoint_config else "false")
            + ";",
            "  static constexpr bool kHasClockFreeze = "
            + ("true" if row.has_clock_freeze else "false")
            + ";",
        ]
        # Hardware-feature constexprs (added by ``add-usb-semantic-traits``).
        # ``kHardwarePresent`` is the alloy HAL's ``UsbDeviceController<T>``
        # gate — it stays ``false`` for register-only rows that have no
        # ``UsbControllerDescriptor`` admitted yet.
        lines.append(
            "  static constexpr bool kHardwarePresent = "
            + ("true" if row.hardware_present else "false")
            + ";"
        )
        lines.append(
            f"  static constexpr std::uintptr_t kBaseAddress = 0x{row.base_address:08X}u;"
        )
        lines.append(
            f"  static constexpr std::uint16_t kEndpointCount = {row.endpoint_count}u;"
        )
        lines.append(
            "  static constexpr bool kSupportsHighSpeed = "
            + ("true" if row.supports_high_speed else "false")
            + ";"
        )
        lines.append(
            "  static constexpr bool kSupportsDma = "
            + ("true" if row.supports_dma else "false")
            + ";"
        )
        lines.append(
            "  static constexpr bool kCrystalless = "
            + ("true" if row.crystalless else "false")
            + ";"
        )
        dpram_base = (
            f"0x{row.dpram_base_address:08X}u" if row.dpram_base_address is not None else "0u"
        )
        dpram_size = row.dpram_size_bytes if row.dpram_size_bytes is not None else 0
        lines.append(
            f"  static constexpr std::uintptr_t kDpramBaseAddress = {dpram_base};"
        )
        lines.append(
            f"  static constexpr std::uint32_t kDpramSizeBytes = {dpram_size}u;"
        )
        lines.append(
            f"  static constexpr std::uint8_t kDmaChannelCount = {row.dma_channel_count}u;"
        )
        lines.append(
            f"  static constexpr PinId kDmPin = {_usb_pin_ref_expr(row.dm_pin, known_pins=known_pins)};"
        )
        lines.append(
            f"  static constexpr PinId kDpPin = {_usb_pin_ref_expr(row.dp_pin, known_pins=known_pins)};"
        )
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        return lines

    return _build


def _eth_specialization_builder(context: _SemanticContext):
    def _build(row: EthSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
                "  static constexpr bool kSupportsMii = false;",
                "  static constexpr bool kSupportsRmii = false;",
                "  static constexpr bool kHasDmaEngine = false;",
                "  static constexpr bool kHasStatisticsCounters = false;",
                "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kUserIoRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kDmaConfigRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kTxStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kRxStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kRxDescriptorBaseRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kTxDescriptorBaseRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kRxEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kManagementPortEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearStatisticsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kWriteEnableStatisticsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxStartField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSpeedField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kFullDuplexField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kMdcClockDividerField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRmiiEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kManagementDoneField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxCompleteInterruptField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxCompleteInterruptField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxCompleteInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = kInvalidFieldRef;",
            ]
        register_members = {
            "kControlRegister": row.control_reg,
            "kConfigRegister": row.config_reg,
            "kStatusRegister": row.status_reg,
            "kUserIoRegister": row.user_io_reg,
            "kDmaConfigRegister": row.dma_config_reg,
            "kTxStatusRegister": row.tx_status_reg,
            "kRxStatusRegister": row.rx_status_reg,
            "kInterruptStatusRegister": row.interrupt_status_reg,
            "kInterruptEnableRegister": row.interrupt_enable_reg,
            "kInterruptDisableRegister": row.interrupt_disable_reg,
            "kInterruptMaskRegister": row.interrupt_mask_reg,
            "kRxDescriptorBaseRegister": row.rx_descriptor_base_reg,
            "kTxDescriptorBaseRegister": row.tx_descriptor_base_reg,
        }
        field_members = {
            "kRxEnableField": row.rx_enable_field,
            "kTxEnableField": row.tx_enable_field,
            "kManagementPortEnableField": row.management_port_enable_field,
            "kClearStatisticsField": row.clear_statistics_field,
            "kWriteEnableStatisticsField": row.write_enable_statistics_field,
            "kTxStartField": row.tx_start_field,
            "kSpeedField": row.speed_field,
            "kFullDuplexField": row.full_duplex_field,
            "kMdcClockDividerField": row.mdc_clock_divider_field,
            "kRmiiEnableField": row.rmii_enable_field,
            "kManagementDoneField": row.management_done_field,
            "kRxCompleteInterruptField": row.rx_complete_interrupt_field,
            "kTxCompleteInterruptField": row.tx_complete_interrupt_field,
            "kRxCompleteInterruptEnableField": row.rx_complete_interrupt_enable_field,
            "kTxCompleteInterruptEnableField": row.tx_complete_interrupt_enable_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr bool kSupportsMii = {'true' if row.supports_mii else 'false'};",
            f"  static constexpr bool kSupportsRmii = {'true' if row.supports_rmii else 'false'};",
            f"  static constexpr bool kHasDmaEngine = {'true' if row.has_dma_engine else 'false'};",
            "  static constexpr bool kHasStatisticsCounters = "
            + ("true" if row.has_statistics_counters else "false")
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
        return lines

    return _build


def _qspi_specialization_builder(context: _SemanticContext):
    def _build(row: QspiSemanticRow) -> list[str]:
        register_members = {
            "kControlRegister": row.control_reg,
            "kModeRegister": row.mode_reg,
            "kStatusRegister": row.status_reg,
            "kInterruptEnableRegister": row.interrupt_enable_reg,
            "kInterruptDisableRegister": row.interrupt_disable_reg,
            "kInterruptMaskRegister": row.interrupt_mask_reg,
            "kSerialClockRegister": row.serial_clock_reg,
            "kInstructionAddressRegister": row.instruction_address_reg,
            "kInstructionCodeRegister": row.instruction_code_reg,
            "kInstructionFrameRegister": row.instruction_frame_reg,
            "kScramblingModeRegister": row.scrambling_mode_reg,
            "kScramblingKeyRegister": row.scrambling_key_reg,
            "kReceiveDataRegister": row.receive_data_reg,
            "kTransmitDataRegister": row.transmit_data_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kDisableField": row.disable_field,
            "kSoftwareResetField": row.software_reset_field,
            "kLastTransferField": row.last_transfer_field,
            "kEnabledStatusField": row.enabled_status_field,
            "kSerialMemoryModeField": row.serial_memory_mode_field,
            "kChipSelectModeField": row.chip_select_mode_field,
            "kBitsPerTransferField": row.bits_per_transfer_field,
            "kReceiveReadyField": row.receive_ready_field,
            "kTransmitReadyField": row.transmit_ready_field,
            "kTransmitEmptyField": row.transmit_empty_field,
            "kReceiveReadyInterruptEnableField": row.receive_ready_interrupt_enable_field,
            "kTransmitReadyInterruptEnableField": row.transmit_ready_interrupt_enable_field,
            "kTransmitEmptyInterruptEnableField": row.transmit_empty_interrupt_enable_field,
            "kSerialClockBaudRateField": row.serial_clock_baud_rate_field,
            "kInstructionField": row.instruction_field,
            "kAddressField": row.address_field,
            "kWidthField": row.width_field,
            "kInstructionEnableField": row.instruction_enable_field,
            "kAddressEnableField": row.address_enable_field,
            "kOptionEnableField": row.option_enable_field,
            "kDataEnableField": row.data_enable_field,
            "kTransferTypeField": row.transfer_type_field,
            "kContinuousReadModeField": row.continuous_read_mode_field,
            "kDummyCyclesField": row.dummy_cycles_field,
            "kScramblingEnableField": row.scrambling_enable_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            "  static constexpr bool kSupportsSpiMode = "
            + ("true" if row.supports_spi_mode else "false")
            + ";",
            "  static constexpr bool kSupportsMemoryMode = "
            + ("true" if row.supports_memory_mode else "false")
            + ";",
            f"  static constexpr bool kHasScrambling = {'true' if row.has_scrambling else 'false'};",
            f"  static constexpr bool kHasDma = {'true' if row.has_dma else 'false'};",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        return lines

    return _build


def _sdmmc_specialization_builder(context: _SemanticContext):
    def _build(row: SdmmcSemanticRow) -> list[str]:
        register_members = {
            "kControlRegister": row.control_reg,
            "kModeRegister": row.mode_reg,
            "kDataTimeoutRegister": row.data_timeout_reg,
            "kSdCardRegister": row.sd_card_reg,
            "kArgumentRegister": row.argument_reg,
            "kCommandRegister": row.command_reg,
            "kBlockRegister": row.block_reg,
            "kCompletionTimeoutRegister": row.completion_timeout_reg,
            "kStatusRegister": row.status_reg,
            "kInterruptEnableRegister": row.interrupt_enable_reg,
            "kInterruptDisableRegister": row.interrupt_disable_reg,
            "kInterruptMaskRegister": row.interrupt_mask_reg,
            "kDmaRegister": row.dma_reg,
            "kConfigRegister": row.config_reg,
            "kReadDataRegister": row.read_data_reg,
            "kWriteDataRegister": row.write_data_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kDisableField": row.disable_field,
            "kPowerSaveEnableField": row.power_save_enable_field,
            "kPowerSaveDisableField": row.power_save_disable_field,
            "kSoftwareResetField": row.software_reset_field,
            "kClockDividerField": row.clock_divider_field,
            "kPowerSaveDividerField": row.power_save_divider_field,
            "kReadProofField": row.read_proof_field,
            "kWriteProofField": row.write_proof_field,
            "kSlotSelectField": row.slot_select_field,
            "kBusWidthField": row.bus_width_field,
            "kArgumentField": row.argument_field,
            "kCommandIndexField": row.command_index_field,
            "kResponseTypeField": row.response_type_field,
            "kSpecialCommandField": row.special_command_field,
            "kOpenDrainField": row.open_drain_field,
            "kMaxLatencyField": row.max_latency_field,
            "kTransferCommandField": row.transfer_command_field,
            "kTransferDirectionField": row.transfer_direction_field,
            "kTransferTypeField": row.transfer_type_field,
            "kSdioInterruptCommandField": row.sdio_interrupt_command_field,
            "kAtacsField": row.atacs_field,
            "kBlockCountField": row.block_count_field,
            "kBlockLengthField": row.block_length_field,
            "kCommandReadyField": row.command_ready_field,
            "kRxReadyField": row.rx_ready_field,
            "kTxReadyField": row.tx_ready_field,
            "kTransferDoneField": row.transfer_done_field,
            "kNotBusyField": row.not_busy_field,
            "kDmaEnableField": row.dma_enable_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr bool kSupports1Bit = {'true' if row.supports_1bit else 'false'};",
            f"  static constexpr bool kSupports4Bit = {'true' if row.supports_4bit else 'false'};",
            f"  static constexpr bool kSupports8Bit = {'true' if row.supports_8bit else 'false'};",
            f"  static constexpr bool kHasDma = {'true' if row.has_dma else 'false'};",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        return lines

    return _build


def _timer_specialization_builder(context: _SemanticContext):
    def _build(row: TimerSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                "  static constexpr std::uint32_t kCounterBits = 0u;",
                "  static constexpr std::uint32_t kChannelCount = 0u;",
                "  static constexpr bool kHasCompare = false;",
                "  static constexpr bool kHasCapture = false;",
                "  static constexpr bool kHasEncoder = false;",
                "  static constexpr bool kHasPwm = false;",
                "  static constexpr bool kHasOnePulse = false;",
                "  static constexpr bool kHasCenterAligned = false;",
                "  static constexpr bool kHasComplementaryOutputs = false;",
                "  static constexpr bool kHasDeadtime = false;",
                "  static constexpr bool kHasBreakInput = false;",
                "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kEventRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kModuleDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateFlagField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateGenerationField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPeriodField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kOnePulseField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAutoReloadPreloadField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClockSourceField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEncoderModeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEncoderEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEncoderPositionEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEncoderSpeedEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEncoderPhaseEdgeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;",
            ]
        register_members = {
            "kControlRegister": row.control_reg,
            "kStatusRegister": row.status_reg,
            "kEventRegister": row.event_reg,
            "kCounterRegister": row.counter_reg,
            "kPrescalerRegister": row.prescaler_reg,
            "kPeriodRegister": row.period_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kDisableField": row.disable_field,
            "kModuleDisableField": row.module_disable_field,
            "kSoftwareResetField": row.software_reset_field,
            "kStartField": row.start_field,
            "kStopField": row.stop_field,
            "kUpdateInterruptEnableField": row.update_interrupt_enable_field,
            "kUpdateFlagField": row.update_flag_field,
            "kUpdateGenerationField": row.update_generation_field,
            "kPrescalerField": row.prescaler_field,
            "kPeriodField": row.period_field,
            "kOnePulseField": row.one_pulse_field,
            "kCenterAlignedField": row.center_aligned_field,
            "kAutoReloadPreloadField": row.auto_reload_preload_field,
            "kClockSourceField": row.clock_source_field,
            "kEncoderModeField": row.encoder_mode_field,
            "kEncoderEnableField": row.encoder_enable_field,
            "kEncoderPositionEnableField": row.encoder_position_enable_field,
            "kEncoderSpeedEnableField": row.encoder_speed_enable_field,
            "kEncoderPhaseEdgeField": row.encoder_phase_edge_field,
            "kDirectionField": row.direction_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr std::uint32_t kCounterBits = {row.counter_bits}u;",
            f"  static constexpr std::uint32_t kChannelCount = {row.channel_count}u;",
            f"  static constexpr bool kHasCompare = {'true' if row.has_compare else 'false'};",
            f"  static constexpr bool kHasCapture = {'true' if row.has_capture else 'false'};",
            f"  static constexpr bool kHasEncoder = {'true' if row.has_encoder else 'false'};",
            f"  static constexpr bool kHasPwm = {'true' if row.has_pwm else 'false'};",
            f"  static constexpr bool kHasOnePulse = {'true' if row.has_one_pulse else 'false'};",
            "  static constexpr bool kHasCenterAligned = "
            + ("true" if row.has_center_aligned else "false")
            + ";",
            "  static constexpr bool kHasComplementaryOutputs = "
            + ("true" if row.has_complementary_outputs else "false")
            + ";",
            f"  static constexpr bool kHasDeadtime = {'true' if row.has_deadtime else 'false'};",
            "  static constexpr bool kHasBreakInput = "
            + ("true" if row.has_break_input else "false")
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
        return lines

    return _build


def _timer_channel_specialization_lines(
    channel_rows: tuple[TimerChannelSemanticRow, ...],
) -> list[str]:
    lines = [
        "template<PeripheralId Id, std::size_t ChannelIndex>",
        "struct TimerChannelSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr bool kSupportsCompare = false;",
        "  static constexpr bool kSupportsCapture = false;",
        "  static constexpr bool kSupportsEncoderInput = false;",
        "  static constexpr bool kSupportsPwm = false;",
        "  static constexpr bool kSupportsComplementaryOutput = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCompareRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCaptureRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPreloadField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputPolarityField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCaptureSelectField = kInvalidFieldRef;",
        "};",
        "",
    ]
    for row in channel_rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        register_members = {
            "kControlRegister": row.control_reg,
            "kStatusRegister": row.status_reg,
            "kCompareRegister": row.compare_reg,
            "kSecondaryCompareRegister": row.secondary_compare_reg,
            "kPeriodRegister": row.period_reg,
            "kCounterRegister": row.counter_reg,
            "kCaptureRegister": row.capture_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kInterruptEnableField": row.interrupt_enable_field,
            "kInterruptFlagField": row.interrupt_flag_field,
            "kModeField": row.mode_field,
            "kPreloadField": row.preload_field,
            "kOutputEnableField": row.output_enable_field,
            "kOutputPolarityField": row.output_polarity_field,
            "kComplementaryOutputEnableField": row.complementary_output_enable_field,
            "kCaptureSelectField": row.capture_select_field,
        }
        lines.extend(
            [
                "template<>",
                f"struct TimerChannelSemanticTraits<PeripheralId::{peripheral_id}, {row.channel_index}u> {{",
                "  static constexpr bool kPresent = true;",
                "  static constexpr bool kSupportsCompare = "
                + ("true" if row.supports_compare else "false")
                + ";",
                "  static constexpr bool kSupportsCapture = "
                + ("true" if row.supports_capture else "false")
                + ";",
                "  static constexpr bool kSupportsEncoderInput = "
                + ("true" if row.supports_encoder_input else "false")
                + ";",
                "  static constexpr bool kSupportsPwm = "
                + ("true" if row.supports_pwm else "false")
                + ";",
                "  static constexpr bool kSupportsComplementaryOutput = "
                + ("true" if row.supports_complementary_output else "false")
                + ";",
            ]
        )
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        lines.extend(["};", ""])
    return lines


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
        return lines

    return _build


def _pwm_channel_specialization_lines(
    channel_rows: tuple[PwmChannelSemanticRow, ...],
) -> list[str]:
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
    for row in channel_rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        register_members = {
            "kControlRegister": row.control_reg,
            "kCompareRegister": row.compare_reg,
            "kSecondaryCompareRegister": row.secondary_compare_reg,
            "kPeriodRegister": row.period_reg,
            "kDeadtimeRegister": row.deadtime_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kInterruptEnableField": row.interrupt_enable_field,
            "kInterruptFlagField": row.interrupt_flag_field,
            "kModeField": row.mode_field,
            "kPolarityField": row.polarity_field,
            "kComplementaryOutputEnableField": row.complementary_output_enable_field,
            "kCenterAlignedField": row.center_aligned_field,
            "kPeriodField": row.period_field,
            "kDutyField": row.duty_field,
            "kDeadtimeRiseField": row.deadtime_rise_field,
            "kDeadtimeFallField": row.deadtime_fall_field,
        }
        lines.extend(
            [
                "template<>",
                f"struct PwmChannelSemanticTraits<PeripheralId::{peripheral_id}, {row.channel_index}u> {{",
                "  static constexpr bool kPresent = true;",
                "  static constexpr bool kSupportsComplementaryOutput = "
                + ("true" if row.supports_complementary_output else "false")
                + ";",
                "  static constexpr bool kSupportsDeadtime = "
                + ("true" if row.supports_deadtime else "false")
                + ";",
            ]
        )
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        lines.extend(["};", ""])
    return lines


def emit_runtime_driver_semantics_common_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    return _emit_driver_semantics_common_header(family_dir=family_dir, device=device)


def emit_runtime_driver_gpio_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    return _emit_gpio_semantics_header(family_dir=family_dir, device=device)


def _uart_peripheral_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """Emit the per-controller UART trait struct + array contributed by
    ``complete-rp2040-semantics`` Phase B.  When `device.rp2040_uart_peripherals`
    is empty (every family except RP2040 today) only the primary template
    is emitted with zero defaults — non-RP2040 specializations are not
    affected."""
    lines = [
        "// complete-rp2040-semantics Phase B: per-controller UART facts.",
        "enum class RuntimeUartId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.rp2040_uart_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeUartId Id>",
            "struct UartPeripheralTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint8_t kFifoDepth = 0u;",
            "  static constexpr std::uint8_t kDreqTx = 0u;",
            "  static constexpr std::uint8_t kDreqRx = 0u;",
            "  static constexpr std::array<std::uint8_t, 0> kValidTxPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidRxPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidCtsPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidRtsPins = {};",
            "};",
            "",
        ]
    )
    for ctrl in device.rp2040_uart_peripherals:
        def _arr(pads: tuple[int, ...]) -> str:
            if not pads:
                return f"  static constexpr std::array<std::uint8_t, 0> kPads = {{}};"
            return ", ".join(f"{p}u" for p in pads)
        lines.extend(
            [
                "template<>",
                f"struct UartPeripheralTraits<RuntimeUartId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint8_t kFifoDepth = {ctrl.fifo_depth}u;",
                f"  static constexpr std::uint8_t kDreqTx = {ctrl.dreq_tx}u;",
                f"  static constexpr std::uint8_t kDreqRx = {ctrl.dreq_rx}u;",
                (
                    f"  static constexpr std::array<std::uint8_t, {len(ctrl.valid_tx_pins)}>"
                    f" kValidTxPins = {{{{{_arr(ctrl.valid_tx_pins)}}}}};"
                    if ctrl.valid_tx_pins
                    else "  static constexpr std::array<std::uint8_t, 0> kValidTxPins = {};"
                ),
                (
                    f"  static constexpr std::array<std::uint8_t, {len(ctrl.valid_rx_pins)}>"
                    f" kValidRxPins = {{{{{_arr(ctrl.valid_rx_pins)}}}}};"
                    if ctrl.valid_rx_pins
                    else "  static constexpr std::array<std::uint8_t, 0> kValidRxPins = {};"
                ),
                (
                    f"  static constexpr std::array<std::uint8_t, {len(ctrl.valid_cts_pins)}>"
                    f" kValidCtsPins = {{{{{_arr(ctrl.valid_cts_pins)}}}}};"
                    if ctrl.valid_cts_pins
                    else "  static constexpr std::array<std::uint8_t, 0> kValidCtsPins = {};"
                ),
                (
                    f"  static constexpr std::array<std::uint8_t, {len(ctrl.valid_rts_pins)}>"
                    f" kValidRtsPins = {{{{{_arr(ctrl.valid_rts_pins)}}}}};"
                    if ctrl.valid_rts_pins
                    else "  static constexpr std::array<std::uint8_t, 0> kValidRtsPins = {};"
                ),
                "};",
                "",
            ]
        )
    return lines


def _dma_controller_hw_traits_block(device: CanonicalDeviceIR) -> list[str]:
    lines = [
        "// complete-rp2040-semantics Phase D: per-controller DMA HW facts.",
        "enum class RuntimeDmaCtrlId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.rp2040_dma_controller_hw, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeDmaCtrlId Id>",
            "struct DmaControllerHwTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint8_t kChannelCount = 0u;",
            "  static constexpr std::uint32_t kMaxTransferCount = 0u;",
            "  static constexpr bool kSupportsChaining = false;",
            "  static constexpr bool kSupportsByteSwap = false;",
            "};",
            "",
        ]
    )
    for ctrl in device.rp2040_dma_controller_hw:
        lines.extend(
            [
                "template<>",
                f"struct DmaControllerHwTraits<RuntimeDmaCtrlId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint8_t kChannelCount = {ctrl.channel_count}u;",
                f"  static constexpr std::uint32_t kMaxTransferCount = {ctrl.max_transfer_count:#010x}u;",
                f"  static constexpr bool kSupportsChaining = {'true' if ctrl.supports_chaining else 'false'};",
                f"  static constexpr bool kSupportsByteSwap = {'true' if ctrl.supports_byte_swap else 'false'};",
                "};",
                "",
            ]
        )
    return lines


def _timer_controller_hw_traits_block(device: CanonicalDeviceIR) -> list[str]:
    lines = [
        "// complete-rp2040-semantics Phase D: per-controller timer HW facts.",
        "enum class RuntimeTimerCtrlId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.rp2040_timer_controller_hw, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeTimerCtrlId Id>",
            "struct TimerControllerHwTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint8_t kCounterBits = 0u;",
            "  static constexpr std::uint8_t kAlarmCount = 0u;",
            "  static constexpr std::uint8_t kDreqAlarmBase = 0u;",
            "};",
            "",
        ]
    )
    for ctrl in device.rp2040_timer_controller_hw:
        lines.extend(
            [
                "template<>",
                f"struct TimerControllerHwTraits<RuntimeTimerCtrlId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint8_t kCounterBits = {ctrl.counter_bits}u;",
                f"  static constexpr std::uint8_t kAlarmCount = {ctrl.alarm_count}u;",
                f"  static constexpr std::uint8_t kDreqAlarmBase = {ctrl.dreq_alarm_base}u;",
                "};",
                "",
            ]
        )
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


def _spi_peripheral_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """Phase B sibling for SPI."""
    lines = [
        "// complete-rp2040-semantics Phase B: per-controller SPI facts.",
        "enum class RuntimeSpiId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.rp2040_spi_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeSpiId Id>",
            "struct SpiPeripheralTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint32_t kMaxClockHz = 0u;",
            "  static constexpr std::uint8_t kDreqTx = 0u;",
            "  static constexpr std::uint8_t kDreqRx = 0u;",
            "  static constexpr std::array<std::uint8_t, 0> kValidMosiPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidMisoPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidClkPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidCsPins = {};",
            "};",
            "",
        ]
    )
    def _arr(pads: tuple[int, ...]) -> str:
        return ", ".join(f"{p}u" for p in pads)

    for ctrl in device.rp2040_spi_peripherals:
        def _pad_line(name: str, pads: tuple[int, ...]) -> str:
            if not pads:
                return f"  static constexpr std::array<std::uint8_t, 0> {name} = {{}};"
            return (
                f"  static constexpr std::array<std::uint8_t, {len(pads)}> "
                f"{name} = {{{{{_arr(pads)}}}}};"
            )

        lines.extend(
            [
                "template<>",
                f"struct SpiPeripheralTraits<RuntimeSpiId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint32_t kMaxClockHz = {ctrl.max_clock_hz}u;",
                f"  static constexpr std::uint8_t kDreqTx = {ctrl.dreq_tx}u;",
                f"  static constexpr std::uint8_t kDreqRx = {ctrl.dreq_rx}u;",
                _pad_line("kValidMosiPins", ctrl.valid_mosi_pins),
                _pad_line("kValidMisoPins", ctrl.valid_miso_pins),
                _pad_line("kValidClkPins", ctrl.valid_clk_pins),
                _pad_line("kValidCsPins", ctrl.valid_cs_pins),
                "};",
                "",
            ]
        )
    return lines


def emit_runtime_driver_uart_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_uart_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        # Hardware-feature defaults (added by ``fill-espressif-semantic-gaps``).
        "  static constexpr bool kHardwarePresent = false;",
        "  static constexpr std::uintptr_t kBaseAddress = 0u;",
        "  static constexpr std::uint16_t kFifoDepth = 0u;",
        "  static constexpr std::int16_t kTxSignalIdx = -1;",
        "  static constexpr std::int16_t kRxSignalIdx = -1;",
        "  static constexpr bool kSupportsDma = false;",
        "  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kMrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kBrgrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kUsCrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kUsMrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kUsBrgrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kUsThrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kUeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kReField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPceField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kM0Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kM1Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTdrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRdrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxeIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxneIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTcIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxeSrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxneSrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTcSrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRstrxField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRsttxField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRststaField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kParField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kChmodeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCdField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxenField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxenField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxemptyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxchrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxchrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRstrxField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRsttxField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRxdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsTxdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRststaField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsUsartModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsUsclksField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsChrlField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsCdField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRxenField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsTxenField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsTxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsTxemptyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsTxchrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRxchrField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=UART_DRIVER_HEADER,
        trait_name="UartSemanticTraits",
        array_name="kUartSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_uart_specialization_builder(context),
        extra_body_lines=_uart_peripheral_traits_block(device),
    )


def emit_runtime_driver_i2c_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_i2c_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCcrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTriseRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSr1Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSr2Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kIcrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kMmrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kIadrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCwgrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRhrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kPeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAckField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFreqField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCcrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDutyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTriseField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSbField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAddrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxneField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBtfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBerrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArloField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBusyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDrDataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSaddField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRdWrnField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNbytesField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAutoendField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTcField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxdataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxdataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNackfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBerrIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArloIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopcfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNackcfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBerrcfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArlocfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMsenField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMsdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSvdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSwrstField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kIadrszField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMreadField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDadrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kIadrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCldivField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kChdivField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCkdivField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kHoldField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxcompField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNackField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArblstField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=I2C_DRIVER_HEADER,
        trait_name="I2cSemanticTraits",
        array_name="kI2cSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_i2c_specialization_builder(context),
    )


def emit_runtime_driver_spi_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_spi_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        # Hardware-feature defaults (added by ``fill-espressif-semantic-gaps``).
        "  static constexpr bool kHardwarePresent = false;",
        "  static constexpr std::uintptr_t kBaseAddress = 0u;",
        "  static constexpr std::uint32_t kMaxClockHz = 0u;",
        "  static constexpr std::int16_t kMosiOutSignal = -1;",
        "  static constexpr std::int16_t kMisoInSignal = -1;",
        "  static constexpr std::int16_t kClkOutSignal = -1;",
        "  static constexpr std::int16_t kCsOutSignal = -1;",
        "  static constexpr bool kHasIomuxFastPath = false;",
        "  static constexpr std::int16_t kIomuxMosiPin = -1;",
        "  static constexpr std::int16_t kIomuxMisoPin = -1;",
        "  static constexpr std::int16_t kIomuxClkPin = -1;",
        "  static constexpr std::int16_t kIomuxCsPin = -1;",
        "  static constexpr bool kSupportsDma = false;",
        "  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kMrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCsrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kCphaField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCpolField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMstrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSpeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kLsbfirstField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSsiField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSsmField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDffField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFrxthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxneField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBsyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDrDataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSpienField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSpidisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSwrstField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPcsdecField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kModfdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPcsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDlybcsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNcphaField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBitsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kScbrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDlybsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDlybctField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTdreField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRdrfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxemptyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTdField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTdrPcsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRdField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=SPI_DRIVER_HEADER,
        trait_name="SpiSemanticTraits",
        array_name="kSpiSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_spi_specialization_builder(context),
        extra_body_lines=_spi_peripheral_traits_block(device),
    )


def emit_runtime_driver_dma_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_dma_rows(context)
    trait_lines = [
        "template<PeripheralId Peripheral, SignalId Signal>",
        "struct DmaSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr DmaBindingId kBindingId = DmaBindingId::none;",
        "  static constexpr DmaControllerId kControllerId = DmaControllerId::none;",
        "  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::none;",
        "  static constexpr DmaRouteId kRouteId = DmaRouteId::none;",
        "  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;",
        "  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::none;",
        "  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;",
        "  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::none;",
        "  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;",
        "  static constexpr int kChannelIndex = -1;",
        "  static constexpr int kRequestValue = -1;",
        "  static constexpr int kChannelSelector = -1;",
        "  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;",
        "};",
        "",
    ]
    row_lines: list[str] = []
    for row in rows:
        signal_ref = _semantic_enum_ref(
            "SignalId",
            context.semantics_catalog["signal_enum_map"],
            row.signal_name,
        )
        trait_lines.extend(
            [
                "template<>",
                f"struct DmaSemanticTraits<PeripheralId::{_enum_identifier(row.peripheral_name)}, {signal_ref}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr DmaBindingId kBindingId = DmaBindingId::{_enum_identifier(row.binding_id)};",
                f"  static constexpr DmaControllerId kControllerId = DmaControllerId::{_enum_identifier(row.controller_name)};",
                f"  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::{_enum_identifier(row.request_line)};",
                f"  static constexpr DmaRouteId kRouteId = DmaRouteId::{_enum_identifier(row.route_id)};",
                "  static constexpr DmaConflictGroupId kConflictGroupId = "
                + (
                    "DmaConflictGroupId::none"
                    if row.conflict_group is None
                    else f"DmaConflictGroupId::{_enum_identifier(row.conflict_group)}"
                )
                + ";",
                f"  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::{_enum_identifier(row.controller_name)};",
                "  static constexpr PeripheralId kRouterPeripheralId = "
                + (
                    "PeripheralId::none"
                    if row.router_name is None
                    else f"PeripheralId::{_enum_identifier(row.router_name)}"
                )
                + ";",
                "  static constexpr BackendSchemaId kControllerSchemaId = "
                + _schema_ref_expr(context, row.controller_schema_id)
                + ";",
                "  static constexpr BackendSchemaId kRouterSchemaId = "
                + _schema_ref_expr(context, row.router_schema_id)
                + ";",
                f"  static constexpr int kChannelIndex = {row.channel_index if row.channel_index is not None else -1};",
                f"  static constexpr int kRequestValue = {row.request_value if row.request_value is not None else -1};",
                f"  static constexpr int kChannelSelector = {row.channel_selector if row.channel_selector is not None else -1};",
                "  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = "
                + _indexed_field_ref_expr(row.route_selector_field)
                + ";",
                "};",
                "",
            ]
        )
        row_lines.append(f"  PeripheralId::{_enum_identifier(row.peripheral_name)},")

    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        "\n".join(
            [
                *trait_lines,
                *_std_array_lines(
                    type_name="PeripheralId",
                    variable_name="kDmaSemanticPeripherals",
                    row_lines=row_lines,
                ),
                "",
                *_dma_controller_hw_traits_block(device),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "common.hpp"',
            '#include "../dma_bindings.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            DMA_DRIVER_HEADER,
        ),
        content=content,
    )


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
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=ADC_DRIVER_HEADER,
        trait_name="AdcSemanticTraits",
        array_name="kAdcSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_adc_specialization_builder(context),
        extra_body_lines=_adc_peripheral_traits_block(device),
    )


def emit_runtime_driver_dac_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    dac_rows, channel_rows = _build_dac_rows(context)
    trait_lines = [
        "template<PeripheralId Id>",
        "struct DacSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr std::uint32_t kChannelCount = 0u;",
        "  static constexpr bool kHasHardwareTrigger = false;",
        "  static constexpr bool kHasDma = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTriggerRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kChannelEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kChannelDisableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kChannelStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDataRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWordModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kChannelReadyPattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kTriggerEnablePattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kTriggerSelectPattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kDataPattern = kInvalidIndexedFieldRef;",
        "};",
        "",
    ]
    dac_peripheral_rows: list[str] = []
    specialization_builder = _dac_specialization_builder(context)
    for row in dac_rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        trait_lines.extend(
            [
                "template<>",
                f"struct DacSemanticTraits<PeripheralId::{peripheral_id}> {{",
                *specialization_builder(row),
                "};",
                "",
            ]
        )
        if not getattr(row, "is_stub", False):
            dac_peripheral_rows.append(f"  PeripheralId::{peripheral_id},")
    body = "\n".join(
        [
            *trait_lines,
            *_dac_channel_specialization_lines(channel_rows),
            *_std_array_lines(
                type_name="PeripheralId",
                variable_name="kDacSemanticPeripherals",
                row_lines=dac_peripheral_rows,
            ),
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
            DAC_DRIVER_HEADER,
        ),
        content=content,
    )


def emit_runtime_driver_rtc_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_rtc_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kHasCalendar = false;",
        "  static constexpr bool kHasAlarm = false;",
        "  static constexpr bool kHasWriteProtection = false;",
        "  static constexpr std::uint32_t kWriteProtectDisableKey0 = 0u;",
        "  static constexpr std::uint32_t kWriteProtectDisableKey1 = 0u;",
        "  static constexpr std::uint32_t kWriteProtectEnableKey = 0u;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTimeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDateRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kAlarmTimeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kAlarmDateRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kClearRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kWriteProtectRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kHourModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInitReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kShadowBypassField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateTimeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateCalendarField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateAckField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAlarmEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAlarmInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSecondInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTimeEventInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCalendarEventInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusAlarmField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusSecondField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusTimeEventField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusCalendarEventField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusTamperErrorField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearAlarmField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearSecondField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearTimeEventField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearCalendarEventField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearTamperErrorField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWriteProtectKeyField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=RTC_DRIVER_HEADER,
        trait_name="RtcSemanticTraits",
        array_name="kRtcSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_rtc_specialization_builder(context),
    )


def emit_runtime_driver_can_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_can_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kHasFlexibleDataRate = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kNominalTimingRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDataTimingRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTestRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kErrorCounterRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kProtocolStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptLineSelectRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptLineEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kGlobalFilterRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStandardFilterConfigRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kExtendedFilterConfigRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kExtendedIdMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRxFifo0ConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRxFifo0StatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRxFifo0AckRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxBufferConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxFifoQueueStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxBufferAddRequestRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxBufferPendingRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxEventFifoConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxEventFifoStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxEventFifoAckRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kConfigEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRestrictedOperationField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRestrictedOperationAckField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBusMonitorField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFdOperationEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBitRateSwitchEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNominalPrescalerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNominalTimeSeg1Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNominalTimeSeg2Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNominalSyncJumpWidthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataPrescalerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataTimeSeg1Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataTimeSeg2Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataSyncJumpWidthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0NewInterruptField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxCompleteInterruptField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0NewInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptEnableField = "
        "kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0FillLevelField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0GetIndexField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0MessageLostField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0AckIndexField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxFifoQueuePutIndexField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxFifoQueueFreeLevelField = kInvalidFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kTxBufferAddRequestPattern = "
        "kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kTxBufferPendingPattern = "
        "kInvalidIndexedFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=CAN_DRIVER_HEADER,
        trait_name="CanSemanticTraits",
        array_name="kCanSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_can_specialization_builder(context),
    )


def emit_runtime_driver_usb_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_usb_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kSupportsDeviceMode = false;",
        "  static constexpr bool kSupportsHostMode = false;",
        "  static constexpr bool kHasDedicatedEndpointConfig = false;",
        "  static constexpr bool kHasClockFreeze = false;",
        # Hardware-feature defaults (added by ``add-usb-semantic-traits``).
        "  static constexpr bool kHardwarePresent = false;",
        "  static constexpr std::uintptr_t kBaseAddress = 0u;",
        "  static constexpr std::uint16_t kEndpointCount = 0u;",
        "  static constexpr bool kSupportsHighSpeed = false;",
        "  static constexpr bool kSupportsDma = false;",
        "  static constexpr bool kCrystalless = false;",
        "  static constexpr std::uintptr_t kDpramBaseAddress = 0u;",
        "  static constexpr std::uint32_t kDpramSizeBytes = 0u;",
        "  static constexpr std::uint8_t kDmaChannelCount = 0u;",
        "  static constexpr PinId kDmPin = PinId::none;",
        "  static constexpr PinId kDpPin = PinId::none;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceInterruptStatusRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceInterruptEnableRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceInterruptDisableRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostInterruptStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostInterruptDisableRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFreezeClockField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kForceDeviceModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kForceHostModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kModeStatusField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSoftDisconnectField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRemoteWakeupField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAddressEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAddressField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClockUsableField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=USB_DRIVER_HEADER,
        trait_name="UsbSemanticTraits",
        array_name="kUsbSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_usb_specialization_builder(context),
    )


def emit_runtime_driver_eth_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_eth_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kSupportsMii = false;",
        "  static constexpr bool kSupportsRmii = false;",
        "  static constexpr bool kHasDmaEngine = false;",
        "  static constexpr bool kHasStatisticsCounters = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kUserIoRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDmaConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRxStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRxDescriptorBaseRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxDescriptorBaseRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kRxEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kManagementPortEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearStatisticsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWriteEnableStatisticsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxStartField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSpeedField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFullDuplexField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMdcClockDividerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRmiiEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kManagementDoneField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxCompleteInterruptField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxCompleteInterruptField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxCompleteInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=ETH_DRIVER_HEADER,
        trait_name="EthSemanticTraits",
        array_name="kEthSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_eth_specialization_builder(context),
    )


def emit_runtime_driver_qspi_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_qspi_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kSupportsSpiMode = false;",
        "  static constexpr bool kSupportsMemoryMode = false;",
        "  static constexpr bool kHasScrambling = false;",
        "  static constexpr bool kHasDma = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSerialClockRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInstructionAddressRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInstructionCodeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInstructionFrameRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kScramblingModeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kScramblingKeyRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kReceiveDataRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTransmitDataRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kLastTransferField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEnabledStatusField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSerialMemoryModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kChipSelectModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBitsPerTransferField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kReceiveReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransmitReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransmitEmptyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kReceiveReadyInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransmitReadyInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransmitEmptyInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSerialClockBaudRateField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInstructionField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAddressField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWidthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInstructionEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAddressEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOptionEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransferTypeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kContinuousReadModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDummyCyclesField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kScramblingEnableField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=QSPI_DRIVER_HEADER,
        trait_name="QspiSemanticTraits",
        array_name="kQspiSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_qspi_specialization_builder(context),
    )


def emit_runtime_driver_sdmmc_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_sdmmc_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kSupports1Bit = false;",
        "  static constexpr bool kSupports4Bit = false;",
        "  static constexpr bool kSupports8Bit = false;",
        "  static constexpr bool kHasDma = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDataTimeoutRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSdCardRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kArgumentRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCommandRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kBlockRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCompletionTimeoutRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDmaRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kReadDataRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kWriteDataRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPowerSaveEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPowerSaveDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClockDividerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPowerSaveDividerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kReadProofField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWriteProofField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSlotSelectField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBusWidthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArgumentField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCommandIndexField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kResponseTypeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSpecialCommandField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOpenDrainField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMaxLatencyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransferCommandField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransferDirectionField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransferTypeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSdioInterruptCommandField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAtacsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBlockCountField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBlockLengthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCommandReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransferDoneField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNotBusyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDmaEnableField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=SDMMC_DRIVER_HEADER,
        trait_name="SdmmcSemanticTraits",
        array_name="kSdmmcSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_sdmmc_specialization_builder(context),
    )


def emit_runtime_driver_watchdog_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_watchdog_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kHasWindow = false;",
        "  static constexpr std::uint32_t kRequiredConfigValue = 0u;",
        "  static constexpr std::uint32_t kStartKeyValue = 0u;",
        "  static constexpr std::uint32_t kRefreshKeyValue = 0u;",
        "  static constexpr std::uint32_t kUnlockKeyValue = 0u;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kReloadRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kWindowRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRestartField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kKeyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTimeoutField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWindowField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEarlyWarningInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kResetEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusPrescalerUpdateField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusReloadUpdateField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusWindowUpdateField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusTimeoutField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusErrorField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRequiredConfigField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=WATCHDOG_DRIVER_HEADER,
        trait_name="WatchdogSemanticTraits",
        array_name="kWatchdogSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_watchdog_specialization_builder(context),
    )


def emit_runtime_driver_timer_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    timer_rows, channel_rows = _build_timer_rows(context)
    trait_lines = [
        "template<PeripheralId Id>",
        "struct TimerSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr std::uint32_t kCounterBits = 0u;",
        "  static constexpr std::uint32_t kChannelCount = 0u;",
        "  static constexpr bool kHasCompare = false;",
        "  static constexpr bool kHasCapture = false;",
        "  static constexpr bool kHasEncoder = false;",
        "  static constexpr bool kHasPwm = false;",
        "  static constexpr bool kHasOnePulse = false;",
        "  static constexpr bool kHasCenterAligned = false;",
        "  static constexpr bool kHasComplementaryOutputs = false;",
        "  static constexpr bool kHasDeadtime = false;",
        "  static constexpr bool kHasBreakInput = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kEventRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kModuleDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateFlagField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateGenerationField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPeriodField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOnePulseField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAutoReloadPreloadField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClockSourceField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEncoderModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEncoderEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEncoderPositionEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEncoderSpeedEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEncoderPhaseEdgeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;",
        "};",
        "",
    ]
    timer_peripheral_rows: list[str] = []
    specialization_builder = _timer_specialization_builder(context)
    for row in timer_rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        trait_lines.extend(
            [
                "template<>",
                f"struct TimerSemanticTraits<PeripheralId::{peripheral_id}> {{",
                *specialization_builder(row),
                "};",
                "",
            ]
        )
        if not row.is_stub:
            timer_peripheral_rows.append(f"  PeripheralId::{peripheral_id},")
    body = "\n".join(
        [
            *trait_lines,
            *_timer_channel_specialization_lines(channel_rows),
            *_std_array_lines(
                type_name="PeripheralId",
                variable_name="kTimerSemanticPeripherals",
                row_lines=timer_peripheral_rows,
            ),
            "",
            *_timer_controller_hw_traits_block(device),
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
            TIMER_DRIVER_HEADER,
        ),
        content=content,
    )


def emit_runtime_driver_pwm_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
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
        "};",
        "",
    ]
    pwm_peripheral_rows: list[str] = []
    specialization_builder = _pwm_specialization_builder(context)
    for row in pwm_rows:
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
        if not row.is_stub:
            pwm_peripheral_rows.append(f"  PeripheralId::{peripheral_id},")
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


_PIO_TRAIT_FIELDS: tuple[tuple[str, str], ...] = (
    ("kStateMachineCount", "std::uint8_t"),
    ("kInstructionMemoryDepth", "std::uint8_t"),
    ("kTxFifoDepth", "std::uint8_t"),
    ("kRxFifoDepth", "std::uint8_t"),
    ("kGpioBase", "std::uint8_t"),
    ("kGpioCount", "std::uint8_t"),
    ("kBaseAddress", "std::uint32_t"),
    ("kDreqTx", "std::uint8_t"),
    ("kDreqRx", "std::uint8_t"),
)


def _pio_id_enum_lines(device: CanonicalDeviceIR) -> list[str]:
    if not device.pio_blocks:
        return [
            "enum class PioId : std::uint8_t {",
            "  None = 0,",
            "};",
            "",
        ]
    lines = ["enum class PioId : std::uint8_t {"]
    for index, block in enumerate(device.pio_blocks):
        lines.append(f"  {block.pio_id} = {index},")
    lines.append("};")
    lines.append("")
    return lines


def _pio_primary_trait_lines() -> list[str]:
    """Primary template: zero defaults so non-PIO families remain zero-cost."""
    body = [
        "template<PioId Id>",
        "struct PioSemanticTraits {",
        "  static constexpr bool kPresent = false;",
    ]
    for name, ctype in _PIO_TRAIT_FIELDS:
        body.append(f"  static constexpr {ctype} {name} = 0;")
    body.append("};")
    body.append("")
    return body


def _pio_specialization_lines(block) -> list[str]:
    return [
        "template<>",
        f"struct PioSemanticTraits<PioId::{block.pio_id}> {{",
        "  static constexpr bool kPresent = true;",
        f"  static constexpr std::uint8_t kStateMachineCount = {block.state_machine_count};",
        (
            f"  static constexpr std::uint8_t kInstructionMemoryDepth = "
            f"{block.instruction_memory_depth};"
        ),
        f"  static constexpr std::uint8_t kTxFifoDepth = {block.tx_fifo_depth};",
        f"  static constexpr std::uint8_t kRxFifoDepth = {block.rx_fifo_depth};",
        f"  static constexpr std::uint8_t kGpioBase = {block.gpio_base};",
        f"  static constexpr std::uint8_t kGpioCount = {block.gpio_count};",
        f"  static constexpr std::uint32_t kBaseAddress = {block.base_address:#010x}u;",
        f"  static constexpr std::uint8_t kDreqTx = {block.dreq_tx_base};",
        f"  static constexpr std::uint8_t kDreqRx = {block.dreq_rx_base};",
        "};",
        "",
    ]


def _state_machine_primary_trait_lines() -> list[str]:
    return [
        "template<PioId Pio, std::uint8_t Sm>",
        "struct StateMachineSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr std::uint8_t kDreqTx = 0;",
        "  static constexpr std::uint8_t kDreqRx = 0;",
        "};",
        "",
    ]


def _state_machine_specialization_lines(block) -> list[str]:
    # ``kDreqTx`` on the PIO trait is the SM0 base; per-SM consumers can also do
    # ``PioSemanticTraits<PioId::PioN>::kDreqTx + sm_index`` at compile time.
    lines: list[str] = []
    for sm in range(block.state_machine_count):
        lines.extend(
            [
                "template<>",
                f"struct StateMachineSemanticTraits<PioId::{block.pio_id}, {sm}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint8_t kDreqTx = {block.dreq_tx_base + sm};",
                f"  static constexpr std::uint8_t kDreqRx = {block.dreq_rx_base + sm};",
                "};",
                "",
            ]
        )
    return lines


def emit_runtime_driver_pio_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit ``driver_semantics/pio.hpp`` with structured PIO topology traits.

    The primary ``PioSemanticTraits<PioId>`` template carries zero-valued
    defaults so families without PIO hardware remain zero-cost.  Devices with
    populated ``device.pio_blocks`` (currently RP2040) get one specialization
    per block plus one ``StateMachineSemanticTraits<PioId, Sm>`` specialization
    per state machine, with per-SM DREQs derived as
    ``dreq_{tx,rx}_base + sm_index`` from the patch overlay.
    """
    body_lines: list[str] = []
    body_lines.extend(_pio_id_enum_lines(device))
    body_lines.extend(_pio_primary_trait_lines())
    for block in device.pio_blocks:
        body_lines.extend(_pio_specialization_lines(block))
    body_lines.extend(_state_machine_primary_trait_lines())
    for block in device.pio_blocks:
        body_lines.extend(_state_machine_specialization_lines(block))

    pio_id_rows = [f"  PioId::{block.pio_id}," for block in device.pio_blocks]
    body_lines.extend(
        _std_array_lines(
            type_name="PioId",
            variable_name="kPioSemanticPeripherals",
            row_lines=pio_id_rows,
        )
    )

    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "common.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, PIO_DRIVER_HEADER),
        content=content,
    )


__all__ = [
    "emit_runtime_driver_adc_semantics_header",
    "emit_runtime_driver_can_semantics_header",
    "emit_runtime_driver_dac_semantics_header",
    "emit_runtime_driver_dma_semantics_header",
    "emit_runtime_driver_eth_semantics_header",
    "emit_runtime_driver_gpio_semantics_header",
    "emit_runtime_driver_i2c_semantics_header",
    "emit_runtime_driver_pio_semantics_header",
    "emit_runtime_driver_qspi_semantics_header",
    "emit_runtime_driver_sdmmc_semantics_header",
    "emit_runtime_driver_usb_semantics_header",
    "emit_runtime_driver_rtc_semantics_header",
    "emit_runtime_driver_semantics_common_header",
    "emit_runtime_driver_spi_semantics_header",
    "emit_runtime_driver_timer_semantics_header",
    "emit_runtime_driver_uart_semantics_header",
    "emit_runtime_driver_pwm_semantics_header",
    "emit_runtime_driver_watchdog_semantics_header",
    "runtime_driver_semantics_required_paths",
]
