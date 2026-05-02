"""Synthesised clock-program steps — one program per
:class:`alloy_codegen.ir.v2_1.ClockProfile`.

The IR already carries ``clock.domains[*].select_register`` and
friends, but **the order of writes** (and the spin-loops between
them) is per-vendor protocol.  Rather than teach every emitter
that protocol, we lower each profile to a vendor-agnostic
``tuple[ClockProgramStep, ...]`` here; the emitter then walks
the tuple and lowers each step to one or two C statements.

A backend (``alloy_codegen.emit_v2_1.clock_backends.<vendor>``) is
the only place that knows e.g. "STM32 needs PLLON, then spin on
PLLRDY, then SW=PLL, then spin on SWS".  The synthesiser dispatches
to the backend by ``device.identity.vendor``; the resulting
``ClockProgramStep`` tuple is what every emitter reads.
"""

from __future__ import annotations

from dataclasses import dataclass
from typing import Literal

# The kinds the lowering layer needs to express.  Keep this list
# small and additive — every backend either emits one of these or
# raises ``StageExecutionError`` at synthesis time.
ClockStepKind = Literal[
    "write_field",      # rmw of `register`'s `field` to `value`
    "write_register",   # full-word write to `register` of `value`
    "set_bits",         # `register |= value`
    "clear_bits",       # `register &= ~value`
    "spin_until",       # spin on `register & mask == expected`
    "barrier_dsb",      # __DSB()
    "barrier_isb",      # __ISB()
    "flash_latency",    # specialised FLASH wait-state programming
]


@dataclass(frozen=True, slots=True)
class ClockProgramStep:
    """One vendor-agnostic step in a clock-profile program.

    Backend lowering rules:

    * ``write_field``: emitter writes ``(reg & ~field_mask) |
      ((value << field_shift) & field_mask)`` to ``register_addr``.
      ``register_id`` / ``field_id`` round-trip the typed refs so
      regenerated headers can label the write site.
    * ``spin_until``: emitter writes a bounded
      ``alloy_clock_spin_until`` call; ``mask`` and ``expected``
      are the second and third arguments.
    * ``barrier_*``: zero-arg memory barrier; ``register_addr``
      and friends are unused.
    * ``flash_latency``: emitter consults
      ``device.identity.flash_wait_states`` (or a backend-specific
      fallback) to compute the right WS for the **target** HCLK
      carried in ``value``, then writes it through.

    ``comment`` is a short free-form string the emitter pastes
    above the lowered statement so the regenerated source is
    auditable line-by-line against the reference manual.  It is
    intentionally a label, not a runtime payload (consistent with
    the artifact-contract zero-string rule which only forbids
    *runtime-consumed* strings).
    """

    kind: ClockStepKind
    register_id: str | None = None
    field_id: str | None = None
    register_addr: int | None = None
    field_mask: int | None = None
    field_shift: int | None = None
    value: int = 0
    expected: int | None = None
    comment: str = ""
