"""``ClockBackend`` Protocol — one adapter per vendor.

Each backend lowers a single :class:`ClockProfile` to a
deterministic tuple of vendor-agnostic
:class:`ClockProgramStep` rows.  The synthesiser picks a
backend by ``device.identity.vendor``; the
:class:`alloy_codegen.emit_v2_1.runtime_init` emitter walks
the lowered tuple and writes one or two C statements per row.

Adding a new vendor adds one module under
``alloy_codegen.emit_v2_1.clock_backends`` and one entry in
:func:`registry`; the emitter never branches on vendor.
"""

from __future__ import annotations

from typing import Protocol, runtime_checkable

from alloy_codegen.ir.synthesised.clock_program import ClockProgramStep
from alloy_codegen.ir.v2_1 import CanonicalDevice, ClockProfile


@runtime_checkable
class ClockBackend(Protocol):
    """One vendor-specific lowering layer.

    ``emit_profile`` is the only method.  Implementations MUST be
    pure and deterministic; given the same ``profile`` and
    ``device`` they MUST return identical ``ClockProgramStep``
    tuples on every call (same Python version, same OS, same
    machine).

    Implementations SHOULD raise
    :class:`alloy_codegen.errors.StageExecutionError` when
    ``profile`` declares a ``sysclk_source`` / ``hclk_hz``
    combination unreachable from ``device.clock``.  Returning an
    empty tuple is reserved for "no-op profile" (e.g. the post-
    reset profile on chips where reset already lands at the
    target — an empty body still compiles).
    """

    def emit_profile(
        self,
        profile: ClockProfile,
        device: CanonicalDevice,
    ) -> tuple[ClockProgramStep, ...]:
        ...
