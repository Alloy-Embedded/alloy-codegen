"""Route operations — concrete bit-flips emitted by the codegen.

A `RouteOperation` is the typed runtime contract: ``(target_ref_kind,
target_ref_id)`` selects WHAT to operate on; ``(value_ref_kind,
value_ref_id, value_int)`` selects the value; ``register_id`` /
``register_field_id`` pin the bit being touched.

These are NOT serialised to disk in v2.1 — they are derived from the
:class:`CanonicalDevice` at codegen time by
:func:`alloy_codegen.ir.synthesised.builder.build_synthesised`.
"""

from __future__ import annotations

from dataclasses import dataclass
from typing import Literal

OperationKind = Literal[
    "set-bit",
    "clear-bit",
    "write-value",
    "write-selector",
    "fire-task",                  # Nordic — TASKS_HFCLKSTART etc.
]
TargetRefKind = Literal[
    "clock-gate",
    "reset",
    "pin",
    "selector",
    "register-field",
    "task",
]
ValueRefKind = Literal["int", "selector", "register-field", "literal"]


@dataclass(frozen=True, slots=True)
class RouteOperation:
    """One concrete hardware operation."""

    operation_id: str
    kind: OperationKind
    target_ref_kind: TargetRefKind
    target_ref_id: str
    register_id: str | None = None
    register_field_id: str | None = None
    value_ref_kind: ValueRefKind | None = None
    value_ref_id: str | None = None
    value_int: int | None = None
    subject_kind: str | None = None        # peripheral / clock-domain / startup
    subject_id: str | None = None
    schema_id: str | None = None
    """Optional vendor-IP schema tag (legacy v1 carried these as
    ``alloy.clock.st-rcc-g0-v1-0``).  Synthesised here from the
    peripheral's `template + ip_version`."""
