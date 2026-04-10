"""Pipeline scope handling."""

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.bootstrap import (
    BOOTSTRAP_FAMILY,
    BOOTSTRAP_VENDOR,
    registered_device_names,
    resolve_device_family,
)
from alloy_codegen.errors import UnsupportedScopeError


@dataclass(frozen=True, slots=True)
class PipelineScope:
    """Represents the user-selected pipeline scope."""

    vendor: str | None = None
    family: str | None = None
    device: str | None = None

    def resolved_vendor(self) -> str:
        if self.vendor is not None:
            return self.vendor.lower()
        if self.device is not None:
            vendor, _ = resolve_device_family(self.device.lower())
            return vendor
        return BOOTSTRAP_VENDOR

    def resolved_family(self) -> str:
        if self.family is not None:
            return self.family.lower()
        if self.device is not None:
            _, family = resolve_device_family(self.device.lower())
            return family
        return BOOTSTRAP_FAMILY

    def resolved_device_names(self) -> tuple[str, ...]:
        if self.device is None:
            return registered_device_names(self.resolved_vendor(), self.resolved_family())
        return (self.device.lower(),)

    def validate_supported(self) -> PipelineScope:
        vendor = self.resolved_vendor()
        family = self.resolved_family()
        # This will raise UnsupportedScopeError if vendor/family is unknown.
        supported_devices = set(registered_device_names(vendor, family))
        unsupported_devices = set(self.resolved_device_names()) - supported_devices
        if unsupported_devices:
            unsupported_device = sorted(unsupported_devices)[0]
            raise UnsupportedScopeError(
                f"Unsupported device '{unsupported_device}'. "
                f"Supported for {vendor}/{family}: "
                f"{', '.join(sorted(supported_devices))}."
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
