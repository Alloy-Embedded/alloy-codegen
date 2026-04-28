"""Supported target configuration and device registry."""

from __future__ import annotations

from dataclasses import dataclass
from functools import lru_cache
from pathlib import Path

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
    # ingest-zephyr-dts-as-source: Nordic nRF52 admitted via the
    # cross-vendor Zephyr-DTS adapter.  Same plumbing will unlock
    # Renesas / TI / Infineon / Ambiq in follow-up changes.
    ("nordic", "nrf52"): ("nrf52840",),
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
    ("nordic", "nrf52"): ("zephyr-dts",),
}

# bulk-admit-from-alloy-devices-yml: filesystem-derived registry.
# Walks ``data/devices/vendors/<v>/<f>/devices/*.yml`` and unions
# the results into the in-memory registry.  Adding a chip becomes
# "commit a YAML to alloy-devices-yml" — no edit to this file.

_DATA_DEVICES_ROOT = Path(__file__).resolve().parents[2] / "data" / "devices"


@lru_cache(maxsize=1)
def discovered_device_registry() -> dict[tuple[str, str], tuple[str, ...]]:
    """Return ``(vendor, family) -> tuple[device_names]`` discovered
    from the ``alloy-devices-yml`` submodule.

    Empty when the submodule is not initialised.  Cached for the
    process lifetime — bumping the submodule mid-process is not
    supported (just restart the process).
    """
    registry: dict[tuple[str, str], list[str]] = {}
    vendors_root = _DATA_DEVICES_ROOT / "vendors"
    if not vendors_root.exists():
        return {}
    for vendor_dir in sorted(vendors_root.iterdir()):
        if not vendor_dir.is_dir():
            continue
        for family_dir in sorted(vendor_dir.iterdir()):
            if not family_dir.is_dir():
                continue
            devices_dir = family_dir / "devices"
            if not devices_dir.exists():
                continue
            yamls = sorted(p.stem for p in devices_dir.glob("*.yml"))
            if yamls:
                registry[(vendor_dir.name, family_dir.name)] = yamls
    return {key: tuple(devices) for key, devices in registry.items()}


def merged_device_registry() -> dict[tuple[str, str], tuple[str, ...]]:
    """Hand-curated ``DEVICE_REGISTRY`` ∪ filesystem-discovered.
    Discovered entries win on conflict — alloy-devices-yml is the
    source of truth once the YAML lands."""
    merged: dict[tuple[str, str], tuple[str, ...]] = dict(DEVICE_REGISTRY)
    for key, devices in discovered_device_registry().items():
        existing = merged.get(key, ())
        # Union, discovered first (source of truth).
        seen: set[str] = set()
        unioned: list[str] = []
        for d in (*devices, *existing):
            if d not in seen:
                unioned.append(d)
                seen.add(d)
        merged[key] = tuple(unioned)
    return merged


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
