"""Vendor adapter registry — emptied by
``consume-alloy-devices-yml-as-canonical-input``.

Originally this package side-effect-registered one
``VendorAdapter`` per family so the pipeline stages could resolve
``(vendor, family)`` pairs without hard-coded ``if vendor == ...``
cascades.  After the canonical-YAML pivot, every admitted
device's IR comes from ``alloy-devices-yml`` directly — there is
no per-family adapter code left in this repo.

The :func:`resolve_vendor_adapter` shim is kept only so the
diagnostics surface (CLI, tests) gets an actionable error
pointing contributors at the data repo if anything still tries
to dispatch through the registry.
"""

from __future__ import annotations

from .registry import (
    VendorAdapter,
    list_registered_adapters,
    register_vendor_adapter,
    resolve_vendor_adapter,
)

__all__ = [
    "VendorAdapter",
    "list_registered_adapters",
    "register_vendor_adapter",
    "resolve_vendor_adapter",
]
