"""Clock-tree dataclasses.

Mirrors ``$defs/oscillator``, ``pll_config``, ``clock_domain``,
``clock_profile``, and ``select_register``.

Profiles are first-class in v2.1 — codegen recipes name them
(``pll-hse-72mhz``, ``radio-ready``, ``low-power-32k``) instead of
re-deriving the multiplier table from raw frequencies.
"""

from __future__ import annotations

from dataclasses import dataclass, field
from typing import Literal

OscillatorKind = Literal[
    "rc-internal", "rc",
    "crystal-external", "crystal-internal",
    "synthesised",
]
ProfileKind = Literal[
    "post-reset", "recommended", "alternative", "low-power", "safe",
]


@dataclass(frozen=True, slots=True)
class Oscillator:
    """One clock source — internal RC, external crystal, or
    synthesised (e.g. nRF52 ``lfsynth`` from HFCLK)."""

    freq: str
    kind: OscillatorKind
    tolerance: str | None = None
    range: tuple[str, str] | None = None
    purpose: str | None = None
    optional: bool = False
    source: str | None = None


@dataclass(frozen=True, slots=True)
class PLLConfig:
    """One PLL definition.  Schema is intentionally loose — every
    vendor expresses PLL math differently (multiplier vs VCO + post-
    divs), so we capture whichever subset is meaningful."""

    input_sources: tuple[str, ...] = field(default_factory=tuple)
    multiplier_range: tuple[int, int] | None = None
    outputs: tuple[str, ...] = field(default_factory=tuple)
    max_output: str | None = None
    vco_range: tuple[str, str] | None = None
    vco_output_target: str | None = None
    post_divs: tuple[int, ...] = field(default_factory=tuple)
    post_div_chain: tuple[int, ...] = field(default_factory=tuple)
    output: str | None = None


@dataclass(frozen=True, slots=True)
class SelectRegister:
    """Register-encoded mux selection — the standard ARM / AVR /
    ESP32 / RP2040 model.  Codegen writes
    ``<reg>.<field> = encoding[<source-name>]``."""

    reg: str
    field: str
    encoding: dict[str, int]


@dataclass(frozen=True, slots=True)
class SelectTask:
    """Task-driven mux selection — Nordic's HFCLK switch fires a
    task instead of writing a register field.  ``status`` is the
    register Codegen polls to confirm the switch landed."""

    on: str
    off: str | None = None
    status: str | None = None


@dataclass(frozen=True, slots=True)
class ClockDomain:
    """One clock domain (sysclk, hclk, pclk1, …).

    Either `source` (single fixed) or `sources` (selectable list)
    is required — never both.  `select_register` / `select_task` /
    `auxsrc_register` / `prescaler_register` carry the mux record so
    codegen knows what to write.
    """

    id: str
    source: str | None = None
    sources: tuple[str, ...] = field(default_factory=tuple)
    prescalers: tuple[float, ...] = field(default_factory=tuple)
    max: str | None = None
    default: str | None = None
    target_freq: str | None = None
    purpose: str | None = None
    notes: str | None = None
    select_register: SelectRegister | None = None
    auxsrc_register: SelectRegister | None = None
    prescaler_register: SelectRegister | None = None
    select_task: SelectTask | None = None


@dataclass(frozen=True, slots=True)
class ClockProfile:
    """A named system-clock recipe.

    Required fields are the four codegen always asks for:
    ``id``, ``kind``, ``sysclk``, ``sysclk_source``.  The other
    *known* fields (``hclk_hz``, ``pclk_hz``, PLL coefficients,
    optional FLASH latency override) are first-class so the
    synthesised IR can lower them to register writes without
    string-key lookups.  Anything else stays in :attr:`extra`.
    """

    id: str
    kind: ProfileKind
    sysclk: str
    sysclk_source: str

    # Promoted from extra so the ClockBackend lowering layer
    # can read them as typed attributes.  ``hclk_hz``/``pclk_hz``
    # are integers (Hz) and authoritative for the running
    # frequency on the AHB / APB buses.  PLL coefficients are
    # whichever subset the family uses (STM32 G0 needs M/N/R;
    # STM32 H7 has M/N/R/P/Q/Frac; nRF52 doesn't carry any).
    hclk_hz: int | None = None
    pclk_hz: int | None = None
    pclk2_hz: int | None = None
    pll_m: int | None = None
    pll_n: int | None = None
    pll_r: int | None = None
    pll_p: int | None = None
    pll_q: int | None = None
    pll_frac: int | None = None
    flash_latency_hz: int | None = None

    extra: dict[str, object] = field(default_factory=dict)


@dataclass(frozen=True, slots=True)
class Clock:
    """Top-level ``clock:`` block."""

    oscillators: dict[str, Oscillator]
    domains: tuple[ClockDomain, ...]
    pll: dict[str, PLLConfig] = field(default_factory=dict)
    profiles: tuple[ClockProfile, ...] = field(default_factory=tuple)
    reset_state: dict[str, object] = field(default_factory=dict)
