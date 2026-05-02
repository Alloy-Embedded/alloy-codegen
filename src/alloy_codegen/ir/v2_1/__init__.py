"""Canonical Device IR — schema ``alloy.device.v2.1``.

Added by ``adopt-canonical-device-v2-1``.

The IR is a faithful Python projection of the v2.1 YAML schema (see
``schema/canonical_device_v2_1/alloy-device-v2_1.schema.json``).
Every dataclass is frozen + slotted so equality is structural and the
trees are pickle-cheap.

Public surface — re-exports from the eight per-section modules so
callers import from one place:

* :class:`Identity`, :class:`Core`, :class:`Multicore`,
  :class:`MulticoreCore`
* :class:`MemoryRegion`
* :class:`Oscillator`, :class:`PLLConfig`, :class:`ClockDomain`,
  :class:`ClockProfile`, :class:`SelectRegister`, :class:`SelectTask`,
  :class:`Clock`
* :class:`Template`, :class:`TemplateRegister`, :class:`TemplateField`
* :class:`PeripheralInstance`, :class:`PeripheralRcc`,
  :class:`PeripheralIrq`, :class:`PeripheralDma`, :class:`PinOptionFixed`,
  :class:`PinOptionMatrix`, :class:`PinOptionPsel`,
  :class:`AdcCalibration`, :class:`CalibrationDataPoint`,
  :class:`ExternalTrigger`, :class:`I2cTimingPreset`
* :class:`Pin`, :data:`PIN_CONSTRAINT_ALLOWED`
* :class:`InterruptVector`, :class:`InterruptMatrix`,
  :class:`InterruptPeripheralSource`
* :class:`Provenance`
* :class:`CanonicalDevice` — the top-level aggregate
"""

from __future__ import annotations

from alloy_codegen.ir.v2_1.clock import (
    Clock,
    ClockDomain,
    ClockProfile,
    Oscillator,
    PLLConfig,
    SelectRegister,
    SelectTask,
)
from alloy_codegen.ir.v2_1.device import CanonicalDevice
from alloy_codegen.ir.v2_1.identity import (
    Core,
    FlashLatencyEntry,
    Identity,
    Multicore,
    MulticoreCore,
)
from alloy_codegen.ir.v2_1.interrupts import (
    InterruptMatrix,
    InterruptPeripheralSource,
    InterruptVector,
)
from alloy_codegen.ir.v2_1.memory import MemoryRegion
from alloy_codegen.ir.v2_1.peripherals import (
    AdcCalibration,
    CalibrationDataPoint,
    ExternalTrigger,
    I2cTimingPreset,
    PeripheralDma,
    PeripheralInstance,
    PeripheralIrq,
    PeripheralRcc,
    PinOptionFixed,
    PinOptionMatrix,
    PinOptionPsel,
)
from alloy_codegen.ir.v2_1.pinout import PIN_CONSTRAINT_ALLOWED, Pin
from alloy_codegen.ir.v2_1.provenance import Provenance
from alloy_codegen.ir.v2_1.templates import (
    Template,
    TemplateField,
    TemplateRegister,
)

CANONICAL_SCHEMA = "alloy.device.v2.1"
"""The exact value the YAML's top-level ``schema:`` key MUST hold."""


__all__ = [
    "CANONICAL_SCHEMA",
    "AdcCalibration",
    "CalibrationDataPoint",
    "CanonicalDevice",
    "Clock",
    "ClockDomain",
    "ClockProfile",
    "Core",
    "ExternalTrigger",
    "FlashLatencyEntry",
    "I2cTimingPreset",
    "Identity",
    "InterruptMatrix",
    "InterruptPeripheralSource",
    "InterruptVector",
    "MemoryRegion",
    "Multicore",
    "MulticoreCore",
    "Oscillator",
    "PIN_CONSTRAINT_ALLOWED",
    "PLLConfig",
    "PeripheralDma",
    "PeripheralInstance",
    "PeripheralIrq",
    "PeripheralRcc",
    "Pin",
    "PinOptionFixed",
    "PinOptionMatrix",
    "PinOptionPsel",
    "Provenance",
    "SelectRegister",
    "SelectTask",
    "Template",
    "TemplateField",
    "TemplateRegister",
]
