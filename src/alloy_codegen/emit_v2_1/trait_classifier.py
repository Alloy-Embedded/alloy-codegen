"""Trait classifier — picks which rich-metadata helper an instance
or template needs in :mod:`peripheral_traits.py`.

The base ``peripheral_traits.h`` shape (``kBaseAddress``, IRQ list,
RCC refs, etc.) lives in the existing per-instance namespace.  The
foundational pass on ``extend-peripheral-traits-with-rich-metadata``
adds three optional sub-blocks gated on this classifier:

* ``InstanceTraitKind.ADC``  — the instance is an ADC and the IR
  carries factory calibration / external-trigger maps.
* ``InstanceTraitKind.I2C``  — the instance is an I²C and the IR
  carries pre-computed timing presets.
* ``TemplateTraitKind.TIMER`` — the template carries any of the
  matrix fields (``trigger_sources``, ``master_outputs``,
  ``deadtime_options``, ``break_inputs``, ``waveform_modes``,
  ``counter_bits_options``).

Adding a new shape (e.g. ``SAI`` for audio) adds one enum value
and one branch here; the emitter dispatcher reads ``classify_*``
and skips when the result is ``NONE``.
"""

from __future__ import annotations

from enum import Enum, auto

from alloy_codegen.ir.v2_1 import PeripheralInstance, Template


class InstanceTraitKind(Enum):
    """Which rich-metadata block (if any) a peripheral instance
    deserves in the emitted ``peripheral_traits.h``."""

    NONE = auto()
    ADC = auto()
    I2C = auto()


class TemplateTraitKind(Enum):
    """Which rich-metadata block a template deserves."""

    NONE = auto()
    TIMER = auto()


# Templates whose name lower-cases to one of these strings carry
# ADC / I²C semantics.  Includes the canonical name plus the
# common synonyms the ST data team uses.
_ADC_TEMPLATE_NAMES = frozenset({
    "adc",          # generic
    "adc_v3",       # G0 / G4
    "adc_v4",       # H7
    "saradc",       # ESP32 successive-approximation ADC
    "afec",         # SAM E70 / V71 analog front-end controller
    "sar",
})

_I2C_TEMPLATE_NAMES = frozenset({
    "i2c",
    "i2c_v1",       # F1/F2/F4 (CCR + TRISE)
    "i2c_v2",       # F0/F3/G0/G4/H7 (TIMINGR)
    "twihs",        # SAM E70/V71 I²C-compatible
    "twi",          # SAMD/L (TWI mode of SERCOM)
})


def classify_instance(per: PeripheralInstance) -> InstanceTraitKind:
    """Pick the rich-metadata kind for one peripheral instance.

    Decision is **template-name-first** (covers 95% of the corpus)
    plus a payload check so we don't emit empty trait blocks.
    """
    template = (per.template or "").lower()

    if template in _ADC_TEMPLATE_NAMES:
        if per.calibration is not None or per.external_triggers:
            return InstanceTraitKind.ADC
        # Fall through — ADC-shaped template but YAML carries no
        # rich metadata yet; the base namespace covers it.
        return InstanceTraitKind.NONE

    if template in _I2C_TEMPLATE_NAMES:
        if per.timing_presets:
            return InstanceTraitKind.I2C
        return InstanceTraitKind.NONE

    return InstanceTraitKind.NONE


def classify_template(template: Template) -> TemplateTraitKind:
    """Pick the rich-metadata kind for a template.

    A template counts as ``TIMER`` when **any** of the timer-
    matrix fields is populated.  Empty fields (the default for
    most non-timer templates) → ``NONE``.
    """
    if (
        template.trigger_sources
        or template.master_outputs
        or template.deadtime_options
        or template.break_inputs
        or template.waveform_modes
        or template.counter_bits_options
    ):
        return TemplateTraitKind.TIMER
    return TemplateTraitKind.NONE


__all__ = [
    "InstanceTraitKind",
    "TemplateTraitKind",
    "classify_instance",
    "classify_template",
]
