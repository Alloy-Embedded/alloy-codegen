"""Tests for NXP MCUXpresso source adapter and imxrt1060 pipeline."""

from __future__ import annotations

import json
from pathlib import Path

import pytest

from alloy_codegen.bootstrap import registered_device_names
from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.fetch import run as run_fetch
from alloy_codegen.stages.normalize import run as run_normalize

IMXRT1060_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "imxrt1060"


@pytest.mark.parametrize("device_name", registered_device_names("nxp", "imxrt1060"))
def test_fetch_nxp_resolves_both_source_ids(
    device_name: str,
    nxp_execution_context: ExecutionContext,
) -> None:
    result = run_fetch(PipelineScope(device=device_name), nxp_execution_context)
    source_ids = {s.source_id for s in result.payload.source_manifest.sources}

    assert "nxp-mcux-soc-svd" in source_ids
    assert "nxp-mcux-sdk" in source_ids


@pytest.mark.parametrize("device_name", registered_device_names("nxp", "imxrt1060"))
def test_fetch_nxp_records_device_svd_and_header_paths(
    device_name: str,
    nxp_execution_context: ExecutionContext,
) -> None:
    result = run_fetch(PipelineScope(device=device_name), nxp_execution_context)
    sources = result.payload.source_manifest.sources
    upstream = device_name.upper()  # e.g. "MIMXRT1062"

    assert any(
        s.source_id == "nxp-mcux-soc-svd"
        and s.upstream_path == f"{upstream}/{upstream}.xml"
        for s in sources
    )
    assert any(
        s.source_id == "nxp-mcux-sdk"
        and s.upstream_path == f"devices/{upstream}/drivers/fsl_iomuxc.h"
        for s in sources
    )


@pytest.mark.parametrize("device_name", registered_device_names("nxp", "imxrt1060"))
def test_fetch_nxp_revisions_are_content_hashes(
    device_name: str,
    nxp_execution_context: ExecutionContext,
) -> None:
    result = run_fetch(PipelineScope(device=device_name), nxp_execution_context)
    for source in result.payload.source_manifest.sources:
        assert source.revision.startswith("content-sha256:")


@pytest.mark.parametrize("device_name", registered_device_names("nxp", "imxrt1060"))
def test_fetch_nxp_is_deterministic(
    device_name: str,
    nxp_execution_context: ExecutionContext,
) -> None:
    result_a = run_fetch(PipelineScope(device=device_name), nxp_execution_context)
    result_b = run_fetch(PipelineScope(device=device_name), nxp_execution_context)

    revisions_a = {(s.source_id, s.revision) for s in result_a.payload.source_manifest.sources}
    revisions_b = {(s.source_id, s.revision) for s in result_b.payload.source_manifest.sources}
    assert revisions_a == revisions_b


@pytest.mark.parametrize("device_name", registered_device_names("nxp", "imxrt1060"))
def test_normalize_matches_imxrt1060_golden_fixture(
    device_name: str,
    nxp_execution_context: ExecutionContext,
) -> None:
    fixture_path = IMXRT1060_FIXTURE_DIR / f"{device_name}.canonical.json"
    expected = json.loads(fixture_path.read_text())

    result = run_normalize(PipelineScope(device=device_name), nxp_execution_context)

    assert result.payload.devices[0].to_dict() == expected


@pytest.mark.parametrize("device_name", registered_device_names("nxp", "imxrt1060"))
def test_normalize_imxrt1060_vendor_family_identity(
    device_name: str,
    nxp_execution_context: ExecutionContext,
) -> None:
    result = run_normalize(PipelineScope(device=device_name), nxp_execution_context)
    device = result.payload.devices[0]

    assert device.identity.vendor == "nxp"
    assert device.identity.family == "imxrt1060"
    assert device.identity.device == device_name


@pytest.mark.parametrize("device_name", registered_device_names("nxp", "imxrt1060"))
def test_normalize_imxrt1060_schema_version_matches_st(
    device_name: str,
    nxp_execution_context: ExecutionContext,
    execution_context: ExecutionContext,
) -> None:
    nxp_result = run_normalize(PipelineScope(device=device_name), nxp_execution_context)
    st_result = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)

    assert nxp_result.payload.devices[0].schema_version == st_result.payload.devices[0].schema_version


def test_normalize_nxp_pins_have_no_port(nxp_execution_context: ExecutionContext) -> None:
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    device = result.payload.devices[0]

    for pin in device.pins:
        assert pin.port is None, f"NXP pin {pin.name!r} unexpectedly has port={pin.port!r}"


def test_normalize_nxp_signals_only_reference_svd_peripherals(
    nxp_execution_context: ExecutionContext,
) -> None:
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    device = result.payload.devices[0]
    peripheral_names = {p.name for p in device.peripherals}

    for pin in device.pins:
        for signal in pin.signals:
            assert signal.peripheral in peripheral_names, (
                f"Pin {pin.name!r} signal {signal.function!r} references "
                f"peripheral {signal.peripheral!r} not found in SVD peripherals."
            )


def test_normalize_nxp_iomuxc_semc_signals_filtered_out(
    nxp_execution_context: ExecutionContext,
) -> None:
    """SEMC is absent from the fixture SVD, so SEMC signals must be filtered."""
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    device = result.payload.devices[0]

    for pin in device.pins:
        for signal in pin.signals:
            assert signal.peripheral != "SEMC", (
                f"Pin {pin.name!r}: SEMC signal leaked into canonical IR: {signal.function!r}"
            )


def test_normalize_nxp_provenance_source_ids(nxp_execution_context: ExecutionContext) -> None:
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    device = result.payload.devices[0]

    # Top-level provenance is SDK-sourced
    assert device.provenance.source_id == "nxp-mcux-sdk"

    # Peripheral provenance is SVD-sourced
    for peripheral in device.peripherals:
        assert peripheral.provenance.source_id == "nxp-mcux-soc-svd"

    # Pin provenance is SDK-sourced
    for pin in device.pins:
        assert pin.provenance.source_id == "nxp-mcux-sdk"


def test_scope_resolves_nxp_vendor_from_device_name() -> None:
    scope = PipelineScope(device="mimxrt1062").validate_supported()
    assert scope.resolved_vendor() == "nxp"
    assert scope.resolved_family() == "imxrt1060"


def test_scope_resolves_all_imxrt1060_devices() -> None:
    devices = registered_device_names("nxp", "imxrt1060")
    assert "mimxrt1062" in devices
    assert "mimxrt1064" in devices


def test_normalize_mimxrt1062_has_ocram_memory(nxp_execution_context: ExecutionContext) -> None:
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    device = result.payload.devices[0]
    memory_names = {m.name for m in device.memories}

    assert "OCRAM" in memory_names


def test_normalize_mimxrt1064_has_flash_and_ocram(nxp_execution_context: ExecutionContext) -> None:
    result = run_normalize(PipelineScope(device="mimxrt1064"), nxp_execution_context)
    device = result.payload.devices[0]
    memory_names = {m.name for m in device.memories}

    assert "OCRAM" in memory_names
    assert "FLASH" in memory_names
