"""Tier 2/3/4 data shapes — projection of the canonical YAML's
patch-baked fields into typed dataclasses.

Pre-pivot these dataclasses lived in
``alloy_codegen.patches`` (deleted by
``consume-alloy-devices-yml-as-canonical-input`` Phase 3).  They
are kept here as the *shape* that the IR's ``tuple[X, ...]``
fields project YAML mappings onto when ``from_primitive`` parses
``data/devices/...yml``.
"""

from __future__ import annotations

from dataclasses import dataclass

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
