"""Pipeline scope handling."""

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.bootstrap import BOOTSTRAP_FAMILY, BOOTSTRAP_VENDOR, bootstrap_device_names
from alloy_codegen.errors import UnsupportedScopeError


@dataclass(frozen=True, slots=True)
class PipelineScope:
    """Represents the user-selected pipeline scope."""

    vendor: str | None = None
    family: str | None = None
    device: str | None = None

    def resolved_vendor(self) -> str:
        return (self.vendor or BOOTSTRAP_VENDOR).lower()

    def resolved_family(self) -> str:
        return (self.family or BOOTSTRAP_FAMILY).lower()

    def resolved_device_names(self) -> tuple[str, ...]:
        if self.device is None:
            return bootstrap_device_names()
        return (self.device.lower(),)

    def validate_supported(self) -> PipelineScope:
        vendor = self.resolved_vendor()
        family = self.resolved_family()
        if vendor != BOOTSTRAP_VENDOR:
            raise UnsupportedScopeError(
                "Unsupported vendor "
                f"'{vendor}'. Bootstrap scope only supports '{BOOTSTRAP_VENDOR}'."
            )
        if family != BOOTSTRAP_FAMILY:
            raise UnsupportedScopeError(
                "Unsupported family "
                f"'{family}'. Bootstrap scope only supports '{BOOTSTRAP_FAMILY}'."
            )
        supported_devices = set(bootstrap_device_names())
        unsupported_devices = set(self.resolved_device_names()) - supported_devices
        if unsupported_devices:
            unsupported_device = sorted(unsupported_devices)[0]
            raise UnsupportedScopeError(
                f"Unsupported device '{unsupported_device}'. "
                f"Bootstrap scope supports: {', '.join(bootstrap_device_names())}."
            )
        return PipelineScope(
            vendor=vendor,
            family=family,
            device=self.device.lower() if self.device else None,
        )

    def to_dict(self) -> dict[str, str | None]:
        return {
            "vendor": self.resolved_vendor(),
            "family": self.resolved_family(),
            "device": self.device.lower() if self.device else None,
        }

    def display_name(self) -> str:
        if self.device:
            return f"{self.resolved_vendor()}:{self.resolved_family()}:{self.device.lower()}"
        return f"{self.resolved_vendor()}:{self.resolved_family()}"
