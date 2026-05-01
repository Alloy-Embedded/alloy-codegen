"""Top-level provenance — v2.1 has no per-row provenance.

Mirrors ``$defs/provenance`` in the schema.
"""

from __future__ import annotations

from dataclasses import dataclass, field
from datetime import date
from typing import Literal

AuthoredBy = Literal["hand", "auto", "auto+hand"]


@dataclass(frozen=True, slots=True)
class Provenance:
    """Single device-level provenance block.

    `primary` is a colon-separated source-id (``"cmsis-svd:STM32F103"``,
    ``"atmel-atdf:ATmega328P"``, …).  `secondary` lists enrichment
    sources in priority order.  Per-row provenance was retired in v2.1
    — the merge engine's `field_provenance` map is rebuilt at parse
    time from the section paths each enrichment supplied.
    """

    primary: str
    authored: AuthoredBy = "auto"
    authored_on: str | date | None = None
    secondary: tuple[str, ...] = field(default_factory=tuple)
    notes: str | None = None
    extra: dict[str, object] = field(default_factory=dict)
