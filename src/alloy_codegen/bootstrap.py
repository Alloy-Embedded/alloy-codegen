"""Supported target configuration and device registry."""

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.errors import UnsupportedScopeError

BOOTSTRAP_VENDOR = "st"
BOOTSTRAP_FAMILY = "stm32g0"
IR_SCHEMA_VERSION = "1.2.0"
PIPELINE_NAME = "alloy-codegen"
PUBLICATION_TARGET_REPOSITORY = "alloy-devices"
ARTIFACT_LAYOUT_VERSION = "alloy-devices-v1"
CPP_CONTRACT_VERSION = "alloy-cpp-bootstrap-v1"

# Registry of all supported (vendor, family) → device names.
DEVICE_REGISTRY: dict[tuple[str, str], tuple[str, ...]] = {
    ("espressif", "esp32"): ("esp32", "esp32-wroom32"),
    ("espressif", "esp32c3"): ("esp32c3",),
    ("espressif", "esp32s3"): ("esp32s3",),
    ("st", "stm32g0"): ("stm32g030f6", "stm32g071rb", "stm32g0b1re"),
    ("st", "stm32f4"): ("stm32f401re", "stm32f405rg"),
    ("microchip", "same70"): ("atsame70n21b", "atsame70q21b"),
    ("microchip", "avr-da"): ("avr128da32",),
    ("nxp", "imxrt1060"): ("mimxrt1062", "mimxrt1064"),
    ("raspberrypi", "rp2040"): ("pico", "rp2040"),
}

SOURCE_BUNDLES: dict[tuple[str, str], tuple[str, ...]] = {
    ("espressif", "esp32"): ("espressif-svd",),
    ("espressif", "esp32c3"): ("espressif-svd",),
    ("espressif", "esp32s3"): ("espressif-svd",),
    ("st", "stm32g0"): ("cmsis-svd-data", "stm32-open-pin-data"),
    ("st", "stm32f4"): ("cmsis-svd-data", "stm32-open-pin-data"),
    ("microchip", "same70"): ("microchip-dfp-pack", "microchip-dfp-extract"),
    ("microchip", "avr-da"): ("microchip-dfp-pack", "microchip-dfp-extract"),
    ("nxp", "imxrt1060"): ("nxp-mcux-soc-svd", "nxp-mcux-sdk"),
    ("raspberrypi", "rp2040"): ("pico-sdk",),
}

# Flat reverse map for auto-resolving family from device name.
_DEVICE_TO_FAMILY: dict[str, tuple[str, str]] = {
    device: (vendor, family)
    for (vendor, family), devices in DEVICE_REGISTRY.items()
    for device in devices
}


@dataclass(frozen=True, slots=True)
class SupportedFamily:
    """Stable description of one supported vendor/family target."""

    vendor: str
    family: str
    devices: tuple[str, ...]
    source_bundles: tuple[str, ...]
    is_default: bool = False

    def to_dict(self) -> dict[str, object]:
        """Return a JSON-friendly representation."""
        return {
            "vendor": self.vendor,
            "family": self.family,
            "devices": list(self.devices),
            "source_bundles": list(self.source_bundles),
            "is_default": self.is_default,
        }


def registered_family_keys() -> tuple[tuple[str, str], ...]:
    """Return supported vendor/family keys in stable order."""
    return tuple(sorted(DEVICE_REGISTRY))


def supported_families(
    *,
    vendor: str | None = None,
    family: str | None = None,
) -> tuple[SupportedFamily, ...]:
    """Return supported families, optionally filtered by vendor and/or family."""
    normalized_vendor = vendor.lower() if vendor is not None else None
    normalized_family = family.lower() if family is not None else None
    matches: list[SupportedFamily] = []

    for key_vendor, key_family in registered_family_keys():
        if normalized_vendor is not None and key_vendor != normalized_vendor:
            continue
        if normalized_family is not None and key_family != normalized_family:
            continue
        matches.append(
            SupportedFamily(
                vendor=key_vendor,
                family=key_family,
                devices=registered_device_names(key_vendor, key_family),
                source_bundles=source_bundle_for(key_vendor, key_family),
                is_default=(key_vendor, key_family) == (BOOTSTRAP_VENDOR, BOOTSTRAP_FAMILY),
            )
        )

    if matches:
        return tuple(matches)

    supported = ", ".join(
        f"{entry_vendor}/{entry_family}" for entry_vendor, entry_family in registered_family_keys()
    )
    raise UnsupportedScopeError(
        f"Unsupported vendor/family filter '{vendor or '*'}'/'{family or '*'}'. "
        f"Supported: {supported}."
    )


def registered_device_names(vendor: str, family: str) -> tuple[str, ...]:
    """Return supported device names for the given vendor/family in stable order."""
    key = (vendor.lower(), family.lower())
    if key not in DEVICE_REGISTRY:
        raise UnsupportedScopeError(
            f"Unsupported vendor/family '{vendor}/{family}'. "
            f"Supported: {', '.join(f'{v}/{f}' for v, f in sorted(DEVICE_REGISTRY))}."
        )
    return tuple(sorted(DEVICE_REGISTRY[key]))


def resolve_device_family(device_name: str) -> tuple[str, str]:
    """Return (vendor, family) for a registered device name."""
    entry = _DEVICE_TO_FAMILY.get(device_name.lower())
    if entry is None:
        supported = ", ".join(sorted(_DEVICE_TO_FAMILY))
        raise UnsupportedScopeError(f"Unsupported device '{device_name}'. Supported: {supported}.")
    return entry


def bootstrap_device_names() -> tuple[str, ...]:
    """Return bootstrap family device names (compatibility shim)."""
    return registered_device_names(BOOTSTRAP_VENDOR, BOOTSTRAP_FAMILY)


def source_bundle_for(vendor: str, family: str) -> tuple[str, ...]:
    """Return the logical source bundle declared for a supported family."""
    key = (vendor.lower(), family.lower())
    if key not in SOURCE_BUNDLES:
        raise UnsupportedScopeError(
            f"Unsupported vendor/family '{vendor}/{family}'. "
            f"Supported: {', '.join(f'{v}/{f}' for v, f in sorted(SOURCE_BUNDLES))}."
        )
    return SOURCE_BUNDLES[key]
