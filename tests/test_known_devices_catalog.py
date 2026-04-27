"""Validation guard for the probe-rs known-devices catalog
(``ingest-probe-rs-target-catalog``).

The catalog under ``data/known_devices.toml`` is a read-only
inventory imported from ``probe-rs/probe-rs``.  This test enforces
the spec scenarios:

* Every device the alloy pipeline admits today resolves to a
  catalog entry, or is recorded in the explicit allow-list below
  with a comment explaining why.
* The catalog is sorted by ``(vendor, family, device)`` so the
  importer's byte-stable output guarantee holds.
"""

from __future__ import annotations

import tomllib
from pathlib import Path

import pytest

from alloy_codegen.bootstrap import DEVICE_REGISTRY

_CATALOG_PATH = Path(__file__).resolve().parents[1] / "data" / "known_devices.toml"
_META_PATH = Path(__file__).resolve().parents[1] / "data" / "known_devices.meta.toml"


# Allow-listed (vendor, family, device) triples that the alloy pipeline
# admits but probe-rs does NOT cover.  Each entry carries a short
# rationale so future maintainers see why it is excluded.
_NOT_IN_PROBE_RS: dict[tuple[str, str, str], str] = {
    ("espressif", "esp32", "esp32-wroom32"): (
        "marketing module name; probe-rs catalogs the silicon (esp32) only"
    ),
    ("microchip", "avr-da", "avr128da32"): (
        "probe-rs is ARM-only — AVR DFPs are not in the probe-rs target catalog"
    ),
    ("raspberrypi", "rp2040", "pico"): (
        "Pico is a board, not a chip; the chip entry rp2040 covers it"
    ),
}


def _load_catalog() -> list[dict]:
    payload = tomllib.loads(_CATALOG_PATH.read_text())
    devices = payload.get("device", [])
    assert isinstance(devices, list), "known_devices.toml must declare a [[device]] array"
    return devices


def _admitted_triples() -> list[tuple[str, str, str]]:
    triples: list[tuple[str, str, str]] = []
    for (vendor, family), devices in DEVICE_REGISTRY.items():
        for device in devices:
            triples.append((vendor, family, device))
    return sorted(triples)


@pytest.fixture(scope="module")
def catalog() -> dict[tuple[str, str, str], dict]:
    """Index the catalog by ``(vendor, family, device)`` for O(1) lookup."""
    devices = _load_catalog()
    indexed: dict[tuple[str, str, str], dict] = {}
    for entry in devices:
        key = (str(entry["vendor"]), str(entry["family"]), str(entry["device"]))
        indexed[key] = entry
    return indexed


def test_catalog_file_exists_and_is_non_empty() -> None:
    assert _CATALOG_PATH.exists(), f"missing catalog file: {_CATALOG_PATH}"
    assert _CATALOG_PATH.read_text().strip(), "catalog file is empty"


def test_meta_records_pinned_probe_rs_sha() -> None:
    payload = tomllib.loads(_META_PATH.read_text())
    assert "probe_rs_sha" in payload
    assert "imported_at_utc" in payload
    assert "tool_version" in payload
    assert payload["probe_rs_sha"], "probe_rs_sha must be a non-empty string"


@pytest.mark.parametrize("triple", _admitted_triples())
def test_admitted_device_resolves_to_catalog_or_allowlist(
    triple: tuple[str, str, str],
    catalog: dict[tuple[str, str, str], dict],
) -> None:
    if triple in _NOT_IN_PROBE_RS:
        pytest.skip(f"allow-listed: {_NOT_IN_PROBE_RS[triple]}")
    assert triple in catalog, (
        f"admitted device {triple} is missing from data/known_devices.toml; "
        f"either add the catalog entry or record an explicit allow-list "
        f"exception in tests/test_known_devices_catalog.py with a rationale"
    )
    entry = catalog[triple]
    assert entry["probe_rs_target"], (
        f"catalog entry {triple} must carry a probe_rs_target identifier"
    )


def test_catalog_entries_are_sorted_by_vendor_family_device() -> None:
    devices = _load_catalog()
    keys = [(str(d["vendor"]), str(d["family"]), str(d["device"])) for d in devices]
    assert keys == sorted(keys), (
        "catalog entries must be sorted by (vendor, family, device) so "
        "tools/import_probe_rs_targets.py output stays byte-stable"
    )


def test_catalog_entries_are_unique() -> None:
    devices = _load_catalog()
    keys = [(str(d["vendor"]), str(d["family"]), str(d["device"])) for d in devices]
    assert len(keys) == len(set(keys)), (
        "catalog must not contain duplicate (vendor, family, device) triples"
    )
