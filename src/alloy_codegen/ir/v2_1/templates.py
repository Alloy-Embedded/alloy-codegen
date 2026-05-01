"""IP-block templates — register layouts defined ONCE per IP version.

Every chip with multiple instances of a peripheral (3× USART, 4×
TIMER, …) saves hundreds of lines by referencing a template instead
of re-emitting the layout per instance.

Mirrors ``$defs/template``, ``template_register``, ``template_field``.
"""

from __future__ import annotations

from dataclasses import dataclass, field
from typing import Literal

RegisterAccess = Literal["ro", "rw", "wo"]


@dataclass(frozen=True, slots=True)
class TemplateRegister:
    """One register slot in a template."""

    offset: int
    access: RegisterAccess | None = None
    stride: int | None = None
    count: int | None = None
    role: str | None = None


@dataclass(frozen=True, slots=True)
class TemplateField:
    """One bit / bit-range field in a template register.

    `bit` (single) and `bits` (range, 2-tuple `[low, high]`) are
    mutually exclusive at parse time but both modelled as optional
    for ergonomic construction.
    """

    bit: int | None = None
    bits: tuple[int, int] | None = None
    enum: dict[str, int] = field(default_factory=dict)
    access: RegisterAccess | None = None


@dataclass(frozen=True, slots=True)
class Template:
    """One IP-block template.

    `extends` (e.g. ``timer_advanced extends timer_general``) is a
    soft inheritance hint; codegen merges parent + child template
    fields at consume time.

    `fields` is the **opt-in subset** — codegen contracts that the
    listed names are bit-key-able.  Bits codegen never touches stay
    in the upstream SVD / ATDF (reachable via ``provenance.primary``).

    `trigger_sources` / `master_outputs` / `waveform_modes` are
    timer-specific maps.  `deadtime_options` and `break_inputs`
    materialise advanced-timer features.
    """

    capabilities: tuple[str, ...] = field(default_factory=tuple)
    capabilities_extra: tuple[str, ...] = field(default_factory=tuple)
    options: dict[str, object] = field(default_factory=dict)
    registers: dict[str, TemplateRegister] = field(default_factory=dict)
    registers_extra: dict[str, TemplateRegister] = field(default_factory=dict)
    fields: dict[str, TemplateField] = field(default_factory=dict)
    fields_extra: dict[str, TemplateField] = field(default_factory=dict)
    extends: str | None = None
    max_clock: str | None = None
    max_baud: int | None = None
    pins_per_port: int | None = None
    speeds_mhz: tuple[int, ...] = field(default_factory=tuple)
    channels: int | None = None
    counter_bits: int | None = None
    counter_bits_options: tuple[int, ...] = field(default_factory=tuple)
    trigger_sources: dict[str, int] = field(default_factory=dict)
    master_outputs: dict[str, int] = field(default_factory=dict)
    waveform_modes: dict[str, int] = field(default_factory=dict)
    deadtime_options: tuple[dict[str, object], ...] = field(default_factory=tuple)
    break_inputs: tuple[str, ...] = field(default_factory=tuple)
    notes: str | None = None
    extra: dict[str, object] = field(default_factory=dict)
    """Catch-all for vendor-specific template extensions
    (`function_select_count`, `state_machines`, `instruction_memory_words`,
    `slice_count`, `channels_per_slice`, `dreq_tx`, `iomux_*`, …)."""
