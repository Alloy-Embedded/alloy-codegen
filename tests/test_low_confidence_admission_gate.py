"""Tests for the low-confidence-admission gate
(`add-modm-data-pdf-extractor` Phase 2 codegen-side opt-in).

Mirrors the contract from
alloy_data_extractor.extractors.datasheet_pdf: every YAML
carrying ``provenance.confidence: low`` is refused by default
and only loaded when the consumer explicitly opts in.
"""

from __future__ import annotations

import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.errors import StageExecutionError  # noqa: E402
from alloy_codegen.sources.alloy_devices_yml import (  # noqa: E402
    DATA_REPO_ROOT,
    load_canonical_device,
)


def _write_synthetic_yaml(tmp_path: Path, *, confidence: str | None) -> Path:
    """Write a minimal-but-valid canonical YAML at a synthetic
    submodule root, returning the root path."""
    repo = tmp_path / "data-repo"
    target = repo / "vendors" / "synth" / "synthfam" / "devices" / "synthdev.yml"
    target.parent.mkdir(parents=True, exist_ok=True)
    lines = [
        "schema_version: 1.2.0",
        "identity:",
        "  vendor: synth",
        "  family: synthfam",
        "  device: synthdev",
        "  core: cortex-m0",
        "provenance:",
        "  source_id: datasheet-pdf-scrape",
    ]
    if confidence is not None:
        lines.append(f"  confidence: {confidence}")
    lines.extend(["peripherals: []", "interrupts: []"])
    target.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return repo


def test_low_confidence_yaml_is_rejected_by_default(monkeypatch, tmp_path: Path) -> None:
    repo = _write_synthetic_yaml(tmp_path, confidence="low")
    monkeypatch.setattr(
        "alloy_codegen.sources.alloy_devices_yml.DATA_REPO_ROOT",
        repo,
    )
    with pytest.raises(StageExecutionError, match="confidence=low"):
        load_canonical_device(vendor="synth", family="synthfam", device="synthdev")


def test_low_confidence_loads_with_explicit_opt_in(monkeypatch, tmp_path: Path) -> None:
    repo = _write_synthetic_yaml(tmp_path, confidence="low")
    monkeypatch.setattr(
        "alloy_codegen.sources.alloy_devices_yml.DATA_REPO_ROOT",
        repo,
    )
    # Explicit opt-in.  May still fail downstream due to incomplete
    # IR for normalize, but the confidence gate must NOT be the
    # blocker.
    try:
        load_canonical_device(
            vendor="synth",
            family="synthfam",
            device="synthdev",
            accept_low_confidence=True,
            validate=False,
        )
    except Exception as exc:  # noqa: BLE001
        assert "confidence=low" not in str(exc), (
            "accept_low_confidence=True must bypass the confidence gate"
        )


def test_high_confidence_yaml_loads_without_opt_in(monkeypatch, tmp_path: Path) -> None:
    repo = _write_synthetic_yaml(tmp_path, confidence="high")
    monkeypatch.setattr(
        "alloy_codegen.sources.alloy_devices_yml.DATA_REPO_ROOT",
        repo,
    )
    try:
        load_canonical_device(
            vendor="synth", family="synthfam", device="synthdev", validate=False
        )
    except Exception as exc:  # noqa: BLE001
        assert "confidence=low" not in str(exc), (
            "high-confidence YAMLs must not trip the gate"
        )


def test_yaml_without_confidence_field_loads(monkeypatch, tmp_path: Path) -> None:
    """Existing YAMLs predate the confidence field — they must
    continue to load (gate only refuses when confidence is
    explicitly ``low``)."""
    repo = _write_synthetic_yaml(tmp_path, confidence=None)
    monkeypatch.setattr(
        "alloy_codegen.sources.alloy_devices_yml.DATA_REPO_ROOT",
        repo,
    )
    try:
        load_canonical_device(
            vendor="synth", family="synthfam", device="synthdev", validate=False
        )
    except Exception as exc:  # noqa: BLE001
        assert "confidence=low" not in str(exc)


def test_admitted_devices_carry_no_confidence_marker() -> None:
    """Sanity: scan every committed YAML in the submodule for
    ``confidence: low`` markers.  None of the codegen-admitted
    YAMLs should carry it (they're CMSIS-SVD / ATDF / DTS sourced,
    not PDF-scraped).  Pure file scan — doesn't actually load the
    IRs (which would hit network for un-cached vendor packs)."""
    if not DATA_REPO_ROOT.exists():
        pytest.skip("alloy-devices-yml submodule not initialised")
    offenders = []
    for path in DATA_REPO_ROOT.glob("vendors/**/devices/*.yml"):
        text = path.read_text(encoding="utf-8")
        if "confidence: low" in text:
            offenders.append(path)
    assert not offenders, (
        "codegen-admitted YAMLs must not carry confidence=low: "
        f"{[str(p) for p in offenders[:5]]}"
    )
