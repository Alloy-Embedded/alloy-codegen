"""Bootstrap family configuration and device registry."""

from __future__ import annotations

from alloy_codegen.errors import UnsupportedScopeError

BOOTSTRAP_VENDOR = "st"
BOOTSTRAP_FAMILY = "stm32g0"
IR_SCHEMA_VERSION = "1.1.0"
PIPELINE_NAME = "alloy-codegen"
PUBLICATION_TARGET_REPOSITORY = "alloy-devices"
ARTIFACT_LAYOUT_VERSION = "alloy-devices-v1"
CPP_CONTRACT_VERSION = "alloy-cpp-bootstrap-v1"

# Registry of all supported (vendor, family) → device names.
DEVICE_REGISTRY: dict[tuple[str, str], tuple[str, ...]] = {
    ("st", "stm32g0"): ("stm32g030f6", "stm32g071rb", "stm32g0b1re"),
    ("st", "stm32f4"): ("stm32f401re", "stm32f405rg"),
    ("microchip", "same70"): ("atsame70n21b", "atsame70q21b"),
}

SOURCE_BUNDLES: dict[tuple[str, str], tuple[str, ...]] = {
    ("st", "stm32g0"): ("cmsis-svd-data", "stm32-open-pin-data"),
    ("st", "stm32f4"): ("cmsis-svd-data", "stm32-open-pin-data"),
    ("microchip", "same70"): ("microchip-dfp-pack", "microchip-dfp-extract"),
}

# Flat reverse map for auto-resolving family from device name.
_DEVICE_TO_FAMILY: dict[str, tuple[str, str]] = {
    device: (vendor, family)
    for (vendor, family), devices in DEVICE_REGISTRY.items()
    for device in devices
}


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
