"""Vendor adapter registry (add-vendor-adapter-registry).

Importing this package registers every built-in adapter so the
pipeline stages (`stages.fetch`, `stages.normalize`) can resolve
``(vendor, family)`` pairs without touching their own source code.
"""

from __future__ import annotations

# Registering imports — kept as side-effects.  Order doesn't matter:
# every `_register` module just calls
# ``register_vendor_adapter(...)`` at import time.
from . import (
    _register_espressif,  # noqa: F401
    _register_microchip_avr_da,  # noqa: F401
    _register_microchip_same70,  # noqa: F401
    _register_nordic_nrf52,  # noqa: F401  — ingest-zephyr-dts-as-source
    _register_nxp_imxrt1060,  # noqa: F401
    _register_raspberrypi_rp2040,  # noqa: F401
    _register_st_stm32f4,  # noqa: F401
    _register_st_stm32g0,  # noqa: F401
)
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
