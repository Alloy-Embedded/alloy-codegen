"""Peripheral instance dataclasses + ADC / I²C extension types.

Mirrors ``$defs/peripheral`` and the per-IP extension subkeys
(``calibration``, ``external_triggers``, ``timing_presets``,
``trigger_source_peers``).
"""

from __future__ import annotations

from dataclasses import dataclass, field
from typing import Literal

CalibrationKind = Literal["vrefint", "ts_cal_low", "ts_cal_high"]


@dataclass(frozen=True, slots=True)
class PeripheralRcc:
    """Clock-enable + reset register references for one peripheral."""

    en: str | None = None
    rst: str | None = None
    extra: dict[str, object] = field(default_factory=dict)


@dataclass(frozen=True, slots=True)
class PeripheralIrq:
    """One NVIC IRQ slot bound to a peripheral.

    A peripheral can have multiple IRQs (TIM1 has 4; I²C has 2 — EV
    + ER).  In that case the on-disk YAML uses an array shape; the IR
    always normalises to a tuple of :class:`PeripheralIrq`.
    """

    num: int
    name: str


@dataclass(frozen=True, slots=True)
class PeripheralDmaChannel:
    """One DMA endpoint (TX or RX) of a peripheral."""

    ctrl: str | None = None
    channel: int | None = None
    dreq: int | None = None
    extra: dict[str, object] = field(default_factory=dict)


@dataclass(frozen=True, slots=True)
class PeripheralDma:
    """`peripherals[].dma` block."""

    tx: PeripheralDmaChannel | None = None
    rx: PeripheralDmaChannel | None = None
    shared: str | None = None
    extra: dict[str, object] = field(default_factory=dict)


# ---------------------------------------------------------------------------
# Pin-option polymorphism — three families per the v2.1 audit.
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class PinOptionFixed:
    """One concrete (pin, alt-function-or-remap) candidate for a
    fixed-AF or function-select chip (STM32, AVR, RP2040)."""

    pin: str
    remap: int | None = None        # STM32 F1 remap index
    func: int | None = None         # RP2040 function-select value
    pinned: bool = True


@dataclass(frozen=True, slots=True)
class PinOptionMatrix:
    """ESP32-style — any GPIO via the GPIO matrix."""

    matrix: bool = True
    default: str | None = None
    fast_path: str | None = None


@dataclass(frozen=True, slots=True)
class PinOptionPsel:
    """Nordic-style — any GPIO via the PSEL register field."""

    psel: bool = True


# ---------------------------------------------------------------------------
# STM32-specific extensions.
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class CalibrationDataPoint:
    """One factory-burned ADC calibration constant (TS_CAL1 etc)."""

    rom_addr: int
    size_bits: int = 16
    nominal_mv: float | None = None
    temp_celsius: float | None = None
    vdda_calibration: float | None = None
    description: str | None = None


@dataclass(frozen=True, slots=True)
class AdcCalibration:
    """Per-instance ADC calibration block (STM32 only)."""

    vrefint: CalibrationDataPoint | None = None
    ts_cal_low: CalibrationDataPoint | None = None
    ts_cal_high: CalibrationDataPoint | None = None
    ts_slope_uv_per_c: float | None = None


@dataclass(frozen=True, slots=True)
class ExternalTrigger:
    """One ADC external-trigger source binding."""

    source: str
    extsel: int | None = None
    jextsel: int | None = None
    polarity: str | None = None


@dataclass(frozen=True, slots=True)
class I2cTimingPreset:
    """One precomputed TIMINGR / CCR+TRISE row."""

    speed: str
    source_clock: str
    timingr: int | None = None     # F0/F3/G0/G4/H7 use TIMINGR
    ccr: int | None = None          # F1/F2/F4 use CCR
    trise: int | None = None        # F1/F2/F4 use TRISE


# ---------------------------------------------------------------------------
# Peripheral instance.
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class PeripheralInstance:
    """One concrete silicon peripheral instance."""

    id: str
    template: str
    base: int | None = None
    bus: str | None = None
    ip_version: str | None = None
    alias: str | None = None
    clock_source: str | None = None
    max_clock_override: str | None = None
    rcc: PeripheralRcc | None = None
    irq: tuple[PeripheralIrq, ...] = field(default_factory=tuple)
    dma: PeripheralDma | None = None
    pin_options: dict[str, object] = field(default_factory=dict)
    """Map ``signal -> PinOption{Fixed|Matrix|Psel} | tuple[PinOptionFixed, ...]``.
    The parser dispatches on the dict / list / object shape per the
    schema's `oneOf`."""
    pin_count: int | None = None
    pinned: bool = True
    mutex_group: str | None = None
    power_reduction: dict[str, object] | None = None
    calibration: AdcCalibration | None = None
    external_triggers: dict[str, tuple[ExternalTrigger, ...]] = field(default_factory=dict)
    timing_presets: tuple[I2cTimingPreset, ...] = field(default_factory=tuple)
    trigger_source_peers: dict[str, str] = field(default_factory=dict)
    channels: dict[str, object] = field(default_factory=dict)
    counter_bits_default: int | None = None
    capabilities_extra: tuple[str, ...] = field(default_factory=tuple)
    conflicts_with: tuple[str, ...] = field(default_factory=tuple)
    notes: str | None = None
    extra: dict[str, object] = field(default_factory=dict)
