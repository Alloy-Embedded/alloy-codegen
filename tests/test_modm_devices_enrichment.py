"""Tests for the modm-devices STM32 enrichment adapter
(``ingest-modm-devices-as-source``).

Covers the spec scenarios:

* modm-devices fills DMA-request gaps left by CMSIS-SVD + STM32
  open-pin-data.
* The hand-curated device patch wins on conflict (modm cannot
  overwrite a patch-supplied DMA request).
* The on-disk modm checkout SHA must match
  ``data/source_pins.toml::modm_devices.sha`` unless the loader
  is invoked with ``accept_stale_sources=True``.
"""

from __future__ import annotations

from pathlib import Path

import pytest

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.modm_devices import (
    ModmEnrichment,
    apply_modm_enrichment,
    validate_modm_source_pin,
)
from alloy_codegen.sources.modm_devices import (
    fetch_records as fetch_modm_records,
)
from alloy_codegen.sources.modm_devices import (
    load_enrichment as load_modm_enrichment,
)
from alloy_codegen.stages.normalize import run as run_normalize

_REPO = Path(__file__).resolve().parents[1]
_MODM_FIXTURE_ROOT = _REPO / "tests" / "fixtures" / "modm-devices"


def _stm32g0_context_with_modm() -> ExecutionContext:
    base = ExecutionContext.default()
    return base.with_overrides(
        source_overrides={
            "cmsis-svd-data": str(_REPO / "tests/fixtures/cmsis-svd-data"),
            "stm32-open-pin-data": str(_REPO / "tests/fixtures/stm32-open-pin-data"),
            "modm-devices": str(_MODM_FIXTURE_ROOT),
        },
        artifact_root="/tmp/_alloy_modm_test_artifacts",
        publication_root="/tmp/_alloy_modm_test_publication",
    )


def test_load_enrichment_parses_clock_edges_dma_requests_and_signals() -> None:
    ctx = _stm32g0_context_with_modm()
    enrichment = load_modm_enrichment(
        ctx, vendor="st", family="stm32g0", device="stm32g071rb"
    )
    assert enrichment is not None
    assert enrichment.device == "stm32g071rb"
    assert enrichment.family == "stm32g0"
    # Fixture declares 8 RCC edges, 7 DMA requests, 5 signal AFs.
    assert len(enrichment.clock_edges) == 8
    assert len(enrichment.dma_requests) == 7
    assert len(enrichment.signal_afs) == 5
    # ADC1 + USART2 RX/TX + SPI1 RX/TX + USART1 RX/TX peripheral keys.
    peripherals = {req.peripheral for req in enrichment.dma_requests}
    assert {"ADC1", "USART1", "USART2", "SPI1"} <= peripherals


def test_load_enrichment_returns_none_without_override() -> None:
    """Modm enrichment is opt-in per workstation: when the
    ``modm-devices`` source override is missing the loader returns
    None and the pipeline behaves exactly like today's flow."""
    base = ExecutionContext.default()
    enrichment = load_modm_enrichment(
        base, vendor="st", family="stm32g0", device="stm32g071rb"
    )
    assert enrichment is None


def test_load_enrichment_returns_none_for_non_st_vendor() -> None:
    """The adapter is STM32-only (per the proposal); other vendors
    short-circuit even when an override is configured."""
    ctx = _stm32g0_context_with_modm()
    assert load_modm_enrichment(
        ctx, vendor="microchip", family="same70", device="atsame70q21b"
    ) is None


def test_apply_enrichment_gap_fills_missing_dma_requests() -> None:
    """End-to-end: running normalize against an STM32G0 device with
    the modm fixture available SHALL extend ``device.dma_requests``
    with entries that do not collide with patch-supplied rows.
    Patch-supplied USART1 RX/TX rows survive untouched."""
    ctx = _stm32g0_context_with_modm()
    result = run_normalize(PipelineScope(device="stm32g071rb"), ctx)
    device = result.payload.devices[0]
    by_source = {req.provenance.source_id for req in device.dma_requests}
    assert "modm-devices" in by_source, "expected modm-devices to gap-fill DMA requests"
    assert "bootstrap-patch" in by_source, (
        "patch-supplied USART1 entries must survive the enrichment merge"
    )
    # ADC1 entry comes from modm only — the patch did not declare it.
    adc1_entries = [req for req in device.dma_requests if req.peripheral == "ADC1"]
    assert adc1_entries, "modm should have contributed an ADC1 DMA request"
    assert adc1_entries[0].provenance.source_id == "modm-devices"


def test_apply_enrichment_does_not_overwrite_patch_rows() -> None:
    """Per the merge precedence spec, a patch-supplied DMA request
    SHALL NOT be replaced by a modm-supplied row with the same key.
    The patch's USART1 RX entry stays under bootstrap-patch
    provenance even though modm also lists USART1 RX."""
    ctx = _stm32g0_context_with_modm()
    result = run_normalize(PipelineScope(device="stm32g071rb"), ctx)
    device = result.payload.devices[0]
    usart1_rx_rows = [
        req for req in device.dma_requests
        if req.peripheral == "USART1" and req.signal == "RX"
        and req.request_line == "DMA1_CH1"  # patch-supplied request_line
    ]
    assert len(usart1_rx_rows) == 1
    assert usart1_rx_rows[0].provenance.source_id == "bootstrap-patch"


def test_apply_enrichment_returns_unchanged_device_when_enrichment_is_none() -> None:
    """``apply_modm_enrichment(device, None)`` is the identity — used
    to keep the ST builder shape uniform whether or not the override
    is configured."""
    ctx = _stm32g0_context_with_modm()
    result = run_normalize(PipelineScope(device="stm32g071rb"), ctx)
    device = result.payload.devices[0]
    assert apply_modm_enrichment(device, None) is device


def test_fetch_records_emits_modm_source_record() -> None:
    """The fetch stage SHALL surface modm-devices as a tracked
    upstream source so the publication source-manifest records the
    SHA used for each device."""
    ctx = _stm32g0_context_with_modm()
    records = fetch_modm_records(ctx, PipelineScope(device="stm32g071rb"))
    assert records, "modm fetch_records should emit ≥1 record when override is set"
    assert records[0]["source_id"] == "modm-devices"
    assert records[0]["target_device"] == "stm32g071rb"
    assert records[0]["origin_url"] == "https://github.com/modm-io/modm-devices"


def test_fetch_records_empty_without_override() -> None:
    base = ExecutionContext.default()
    records = fetch_modm_records(base, PipelineScope(device="stm32g071rb"))
    assert records == ()


def test_validate_modm_source_pin_is_silent_when_no_pin_recorded(
    tmp_path: Path,
) -> None:
    """First-time ingest: ``data/source_pins.toml`` carries an empty
    sha → the loader accepts whatever the caller has on disk."""
    # The default repo state has empty `sha`; this shouldn't raise.
    validate_modm_source_pin(modm_root=_MODM_FIXTURE_ROOT)


def test_validate_modm_source_pin_rejects_drift_when_sha_pinned(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    """When a SHA is pinned, the loader compares it to the checkout
    git HEAD and raises ``StageExecutionError`` on drift unless
    ``accept_stale_sources=True``."""
    from alloy_codegen.sources import modm_devices as modm_module

    monkeypatch.setattr(modm_module, "_read_modm_pin_sha", lambda: "deadbeefcafef00d")

    # The fixture is not a git repo → validate falls through silently
    # by design (best-effort).  Provide a fake git invocation that
    # returns a divergent SHA.
    import subprocess

    real_run = subprocess.run

    def fake_run(*args, **kwargs):
        class _R:
            returncode = 0
            stdout = "ffffffffffffffff\n"
            stderr = ""
        return _R()

    monkeypatch.setattr(subprocess, "run", fake_run)

    with pytest.raises(StageExecutionError) as excinfo:
        modm_module.validate_modm_source_pin(modm_root=_MODM_FIXTURE_ROOT)
    msg = str(excinfo.value)
    assert "deadbeefcafef00d" in msg
    assert "ffffffffffffffff" in msg
    assert "--accept-stale-sources" in msg
    # Override flag bypasses the check.
    modm_module.validate_modm_source_pin(
        modm_root=_MODM_FIXTURE_ROOT, accept_stale_sources=True
    )

    # Restore (monkeypatch handles automatic teardown).
    _ = real_run


def test_modm_enrichment_dataclass_round_trips_to_dict() -> None:
    """Sanity check on the enrichment serialization shape used by
    diagnostics + future provenance reports."""
    enrichment = ModmEnrichment(
        device="stm32g071rb",
        family="stm32g0",
        provenance_sha="abc123",
    )
    payload = enrichment.to_dict()
    assert payload["device"] == "stm32g071rb"
    assert payload["clock_edges"] == []
    assert payload["dma_requests"] == []
    assert payload["signal_afs"] == []
    assert payload["provenance_sha"] == "abc123"
