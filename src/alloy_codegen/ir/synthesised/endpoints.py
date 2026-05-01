"""Signal endpoints — typed peripheral-side signal identities.

Each peripheral instance exposes a set of signals (``tx``, ``rx``,
``mosi``, ``scl``, ``ain0``, …).  The endpoint dataclass carries the
canonical id codegen uses to refer to the signal across pin candidates,
DMA bindings, IRQ assertions, and trait macros.

Synthesised from ``peripherals[].pin_options`` keys + the template's
declared signal set.
"""

from __future__ import annotations

from dataclasses import dataclass
from typing import Literal

Direction = Literal["in", "out", "io", "analog"]


@dataclass(frozen=True, slots=True)
class SignalEndpoint:
    """One peripheral signal identity."""

    endpoint_id: str
    peripheral: str
    peripheral_class: str       # e.g. ``usart``, ``spi``, ``twim``, ``adc``
    signal: str                 # ``tx``, ``rx``, ``mosi``, ``scl``, ``ch0``, ``ain0`` …
    direction: Direction | None = None
