"""Supported target configuration and device registry.

After ``consume-alloy-devices-yml-as-canonical-input`` Phase 5 the
registry is filesystem-derived from the ``alloy-devices-yml``
submodule mounted at ``data/devices/vendors/``.  Adding a chip is
"commit a YAML to alloy-devices-yml" — no edit to this file.

The registry is resolved **lazily** so ``import alloy_codegen``
never raises just because the data submodule isn't mounted (which
would happen on every PyPI install).  Callers who actually need
the data still get :class:`UnsupportedScopeError` on first
access — the contract is preserved, the eager-import bug is not.
"""

from __future__ import annotations

from dataclasses import dataclass
from functools import lru_cache
from pathlib import Path
from typing import Any

from alloy_codegen.errors import UnsupportedScopeError

BOOTSTRAP_VENDOR = "st"
BOOTSTRAP_FAMILY = "stm32g0"
# v2.1 lock-string — every YAML produced or consumed by the v2.1
# pipeline declares this exact value as its top-level ``schema:`` key.
CANONICAL_SCHEMA = "alloy.device.v2.1"
PIPELINE_NAME = "alloy-codegen"
PUBLICATION_TARGET_REPOSITORY = "alloy-devices"
ARTIFACT_LAYOUT_VERSION = "alloy-devices-v1"
CPP_CONTRACT_VERSION = "alloy-cpp-bootstrap-v1"

_DATA_DEVICES_ROOT = Path(__file__).resolve().parents[2] / "data" / "devices"


@lru_cache(maxsize=1)
def _discover_device_registry() -> dict[tuple[str, str], tuple[str, ...]]:
    """Walk ``data/devices/vendors/<v>/<f>/devices/*.yml`` and
    union the discovered devices into ``(vendor, family) ->
    tuple[device_names]``.

    Raises if the submodule is uninitialised — admission requires
    the data repo to be present.  Cached for the process lifetime
    (bumping the submodule mid-process is not supported; restart
    the process if the data repo changed).
    """
    registry: dict[tuple[str, str], list[str]] = {}
    vendors_root = _DATA_DEVICES_ROOT / "vendors"
    if not vendors_root.exists():
        raise UnsupportedScopeError(
            "data/devices/ submodule is not initialised — run "
            "`git submodule update --init` to mount alloy-devices-yml."
        )
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
    if not registry:
        raise UnsupportedScopeError(
            "alloy-devices-yml submodule contains no admitted devices "
            "(walked data/devices/vendors/<vendor>/<family>/devices/)."
        )
    return {key: tuple(devices) for key, devices in registry.items()}


def device_registry() -> dict[tuple[str, str], tuple[str, ...]]:
    """Return ``(vendor, family) -> tuple[device_names]`` mapping
    derived from the canonical YAMLs in
    ``data/devices/vendors/``.  Drop-in replacement for the legacy
    hand-curated ``DEVICE_REGISTRY`` mapping."""
    return dict(_discover_device_registry())


def discovered_device_registry() -> dict[tuple[str, str], tuple[str, ...]]:
    """Backwards-compat alias for ``device_registry()`` — kept for
    callers that imported the pre-Phase-5 name.  Returns the cached
    filesystem-derived mapping; identity-stable across repeated
    calls in the same process."""
    return _discover_device_registry()


# Lazy ``DEVICE_REGISTRY`` proxy — resolved on first attribute
# access via PEP 562 ``__getattr__``.  Importing the module no
# longer reads from disk, so a wheel install without the
# ``alloy-devices-yml`` submodule mounted continues to import
# cleanly; ``UnsupportedScopeError`` only fires when something
# actually asks for the registry.


def __getattr__(name: str) -> Any:  # noqa: ANN401 -- module-level proxy
    if name == "DEVICE_REGISTRY":
        return device_registry()
    raise AttributeError(f"module {__name__!r} has no attribute {name!r}")


def _device_to_family() -> dict[str, tuple[str, str]]:
    return {
        device: (vendor, family)
        for (vendor, family), devices in _discover_device_registry().items()
        for device in devices
    }


@dataclass(frozen=True, slots=True)
class SupportedFamily:
    """Stable description of one supported vendor/family target."""

    vendor: str
    family: str
    devices: tuple[str, ...]
    is_default: bool = False

    def to_dict(self) -> dict[str, object]:
        """Return a JSON-friendly representation."""
        return {
            "vendor": self.vendor,
            "family": self.family,
            "devices": list(self.devices),
            "is_default": self.is_default,
        }


def registered_family_keys() -> tuple[tuple[str, str], ...]:
    """Return supported vendor/family keys in stable order."""
    return tuple(sorted(_discover_device_registry()))


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
    registry = _discover_device_registry()
    if key not in registry:
        raise UnsupportedScopeError(
            f"Unsupported vendor/family '{vendor}/{family}'. "
            f"Supported: {', '.join(f'{v}/{f}' for v, f in sorted(registry))}."
        )
    return tuple(sorted(registry[key]))


def resolve_device_family(device_name: str) -> tuple[str, str]:
    """Return (vendor, family) for a registered device name."""
    entry = _device_to_family().get(device_name.lower())
    if entry is None:
        supported = ", ".join(sorted(_device_to_family()))
        raise UnsupportedScopeError(f"Unsupported device '{device_name}'. Supported: {supported}.")
    return entry


def bootstrap_device_names() -> tuple[str, ...]:
    """Return bootstrap family device names (compatibility shim)."""
    return registered_device_names(BOOTSTRAP_VENDOR, BOOTSTRAP_FAMILY)
