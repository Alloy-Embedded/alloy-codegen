"""Tests for the bulk-admit machinery + filesystem-derived
device registry.  Added by ``bulk-admit-from-alloy-devices-yml``.
"""

from __future__ import annotations

import json
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.bootstrap import (  # noqa: E402
    DEVICE_REGISTRY,
    discovered_device_registry,
    merged_device_registry,
)
from alloy_codegen.bulk_admit import (  # noqa: E402
    BulkAdmitOutcome,
    BulkAdmitReport,
    admit_devices,
    render_markdown,
    write_report_json,
)

# ---------------------------------------------------------------------------
# Filesystem-derived registry
# ---------------------------------------------------------------------------


def test_discovered_registry_has_at_least_the_admitted_set() -> None:
    """Spec scenario: every chip with a YAML in alloy-devices-yml
    appears in the discovered registry.  Skips when the submodule
    is not initialised."""
    discovered = discovered_device_registry()
    if not discovered:
        pytest.skip("alloy-devices-yml submodule not initialised")
    # The 17 devices that landed in the bootstrap commit MUST be
    # discoverable from the filesystem.
    for (vendor, family), expected in DEVICE_REGISTRY.items():
        if (vendor, family) not in discovered:
            continue
        for device in expected:
            assert device in discovered[(vendor, family)], (
                f"{vendor}/{family}/{device} missing from discovered registry"
            )


def test_merged_registry_unions_hand_curated_with_discovered() -> None:
    """Spec scenario: merged registry contains the union of both
    sources."""
    merged = merged_device_registry()
    # Hand-curated entries persist.
    assert ("st", "stm32g0") in merged
    assert "stm32g071rb" in merged[("st", "stm32g0")]


def test_discovered_registry_caches_within_process() -> None:
    """``functools.lru_cache(maxsize=1)`` — second call returns
    the same dict."""
    a = discovered_device_registry()
    b = discovered_device_registry()
    assert a is b


# ---------------------------------------------------------------------------
# admit_devices() filtering + outcomes
# ---------------------------------------------------------------------------


def test_admit_devices_with_limit_stops_after_n() -> None:
    report = admit_devices(limit=2, dry_run=True)
    assert report.total == 2
    assert report.failures == 0


def test_admit_devices_filters_by_vendor() -> None:
    report = admit_devices(vendor="nordic", dry_run=True)
    assert report.total >= 1
    for outcome in report.devices:
        assert outcome.vendor == "nordic"


def test_admit_devices_filters_by_family() -> None:
    report = admit_devices(vendor="st", family="stm32g0", dry_run=True)
    assert report.total >= 1
    for outcome in report.devices:
        assert outcome.vendor == "st"
        assert outcome.family == "stm32g0"


def test_admit_devices_dry_run_passes_for_yaml_admitted_nordic() -> None:
    """Spec scenario: bulk admission produces PASS / known-status
    rows for every device."""
    report = admit_devices(vendor="nordic", family="nrf52", dry_run=True)
    assert report.total >= 1
    nrf = next(o for o in report.devices if o.device == "nrf52840")
    assert nrf.status == "PASS"


# ---------------------------------------------------------------------------
# Markdown + JSON reporting
# ---------------------------------------------------------------------------


def test_render_markdown_emits_summary_and_table() -> None:
    report = BulkAdmitReport(started_utc="2026-04-28T00:00:00+00:00")
    report.finished_utc = "2026-04-28T00:00:01+00:00"
    report.add(
        BulkAdmitOutcome(
            vendor="acme",
            family="fam",
            device="dev",
            status="PASS",
            duration_seconds=0.5,
            artifact_count=10,
        )
    )
    text = render_markdown(report)
    assert "# Bulk-admit summary" in text
    assert "acme | fam | dev" in text
    assert "✅ PASS" in text


def test_render_markdown_emits_failure_row() -> None:
    report = BulkAdmitReport(started_utc="2026-04-28T00:00:00+00:00")
    report.add(
        BulkAdmitOutcome(
            vendor="acme",
            family="fam",
            device="bad",
            status="EMIT_FAILED",
            duration_seconds=0.1,
            error="boom",
        )
    )
    text = render_markdown(report)
    assert "❌ EMIT_FAILED" in text
    assert "boom" in text


def test_write_report_json_round_trips(tmp_path: Path) -> None:
    report = BulkAdmitReport(started_utc="2026-04-28T00:00:00+00:00")
    report.finished_utc = "2026-04-28T00:00:01+00:00"
    report.add(
        BulkAdmitOutcome(
            vendor="v",
            family="f",
            device="d",
            status="PASS",
            duration_seconds=0.25,
            artifact_count=3,
        )
    )
    out = tmp_path / "report.json"
    write_report_json(report, out)
    payload = json.loads(out.read_text(encoding="utf-8"))
    assert payload["total"] == 1
    assert payload["passes"] == 1
    assert payload["devices"][0]["device"] == "d"


# ---------------------------------------------------------------------------
# CLI integration
# ---------------------------------------------------------------------------


def test_cli_bulk_admit_dry_run_matches_admit_devices(tmp_path: Path) -> None:
    """``alloy-codegen bulk-admit --dry-run --json`` returns the
    same shape as the programmatic API."""
    from alloy_codegen.cli import main

    rc = main(
        [
            "bulk-admit",
            "--vendor",
            "nordic",
            "--family",
            "nrf52",
            "--dry-run",
            "--report",
            str(tmp_path / "r.json"),
            "--json",
        ]
    )
    assert rc == 0
    payload = json.loads((tmp_path / "r.json").read_text(encoding="utf-8"))
    assert payload["passes"] >= 1
    assert any(d["device"] == "nrf52840" for d in payload["devices"])
