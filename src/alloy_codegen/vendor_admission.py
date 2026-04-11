"""Helpers for foundational vendor-admission gates."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Final

FOUNDATIONAL_FAMILIES: Final[tuple[tuple[str, str], ...]] = (
    ("st", "stm32g0"),
    ("st", "stm32f4"),
    ("microchip", "same70"),
    ("nxp", "imxrt1060"),
)

STABLE_CYCLE_FAMILIES: Final[tuple[tuple[str, str], ...]] = (
    ("st", "stm32f4"),
    ("microchip", "same70"),
    ("nxp", "imxrt1060"),
)


@dataclass(frozen=True, slots=True)
class FoundationalFamilyStatus:
    """Admission-facing completeness state for one foundational family."""

    vendor: str
    family: str
    all_devices_publishable: bool
    draft_system_descriptor_domains: tuple[str, ...]
    stable_publication_cycles: int
    published_without_exceptions: bool = True

    @property
    def key(self) -> tuple[str, str]:
        return (self.vendor.lower(), self.family.lower())

    @property
    def contract_complete(self) -> bool:
        return (
            self.all_devices_publishable
            and not self.draft_system_descriptor_domains
            and self.published_without_exceptions
        )

    @property
    def requires_stable_cycles(self) -> bool:
        return self.key in STABLE_CYCLE_FAMILIES


def evaluate_vendor_admission(statuses: tuple[FoundationalFamilyStatus, ...]) -> tuple[str, ...]:
    """Return blocker messages that keep the vendor-admission gate closed."""

    by_key = {status.key: status for status in statuses}
    blockers: list[str] = []

    for vendor, family in FOUNDATIONAL_FAMILIES:
        status = by_key.get((vendor, family))
        if status is None:
            blockers.append(f"missing foundational family status for {vendor}/{family}")
            continue
        if not status.contract_complete:
            blockers.append(f"{vendor}/{family} is not contract-complete")

    for vendor, family in STABLE_CYCLE_FAMILIES:
        status = by_key.get((vendor, family))
        if status is None:
            continue
        if status.stable_publication_cycles < 2:
            blockers.append(f"{vendor}/{family} has fewer than two stable publication cycles")

    return tuple(blockers)
