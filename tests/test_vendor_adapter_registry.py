"""Tests for the central vendor adapter registry added by
``add-vendor-adapter-registry``.

The pipeline resolves ``(vendor, family)`` adapters through
``alloy_codegen.vendors.registry`` rather than hard-coded
``if vendor == ...`` cascades.  Each adapter module registers itself
at import time.  Pipeline stages call
``resolve_vendor_adapter(vendor, family)`` to look up the adapter.
"""

from __future__ import annotations

import pytest

from alloy_codegen.errors import StageExecutionError
from alloy_codegen.vendors import (
    VendorAdapter,
    list_registered_adapters,
    resolve_vendor_adapter,
)

_ADMITTED_PAIRS = (
    ("st", "stm32g0"),
    ("st", "stm32f4"),
    ("microchip", "same70"),
    ("microchip", "avr-da"),
    ("nxp", "imxrt1060"),
    ("raspberrypi", "rp2040"),
    ("espressif", "esp32"),
    ("espressif", "esp32c3"),
    ("espressif", "esp32s3"),
)


@pytest.mark.parametrize("vendor,family", _ADMITTED_PAIRS)
def test_admitted_family_resolves_to_registered_adapter(vendor: str, family: str) -> None:
    adapter = resolve_vendor_adapter(vendor, family)
    assert isinstance(adapter, VendorAdapter)
    assert adapter.vendor == vendor
    assert adapter.family == family
    # Both entry points are callables; stages can dispatch through them.
    assert callable(adapter.fetch)
    assert callable(adapter.normalize)


def test_list_registered_adapters_covers_every_admitted_pair() -> None:
    registered = set(list_registered_adapters())
    for pair in _ADMITTED_PAIRS:
        assert pair in registered, f"missing adapter registration for {pair}"


def test_unknown_vendor_family_raises_stage_execution_error() -> None:
    with pytest.raises(StageExecutionError) as excinfo:
        resolve_vendor_adapter("foo", "bar")
    msg = str(excinfo.value)
    assert "foo" in msg
    assert "bar" in msg
    # Error message lists the registered set so a developer adding a
    # family-without-adapter sees what is admitted.
    assert "registered adapters:" in msg
    assert "'st'" in msg or '"st"' in msg
