"""Tests for NXP MCUXpresso source adapter and imxrt1060 pipeline."""

from __future__ import annotations

import json
from dataclasses import replace
from pathlib import Path

import pytest

from alloy_codegen.bootstrap import registered_device_names
from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import (
    PeripheralInstance,
    Provenance,
    RegisterDescriptor,
    RegisterFieldDescriptor,
)
from alloy_codegen.runtime_driver_semantics import (
    _context,
    emit_runtime_driver_can_semantics_header,
    emit_runtime_driver_watchdog_semantics_header,
)
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.fetch import run as run_fetch
from alloy_codegen.stages.normalize import run as run_normalize
from alloy_codegen.stages.publish import run as run_publish
from alloy_codegen.stages.validate import run as run_validate

IMXRT1060_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "imxrt1060"
IMXRT1060_EMITTED_DIR = Path(__file__).parent / "fixtures" / "emitted" / "imxrt1060"


def _nxp_watchdog_provenance() -> Provenance:
    return Provenance(
        source_id="test-fixture",
        source_path="tests/test_nxp_mcux.py",
        patch_ids=("nxp-watchdog-regression",),
    )


def _nxp_watchdog_register(
    *,
    peripheral: str,
    name: str,
    offset_bytes: int,
) -> RegisterDescriptor:
    provenance = _nxp_watchdog_provenance()
    return RegisterDescriptor(
        register_id=f"register_{peripheral.lower()}_{name.lower()}",
        peripheral=peripheral,
        name=name,
        offset_bytes=offset_bytes,
        access="read-write",
        size_bits=32,
        provenance=provenance,
    )


def _nxp_watchdog_field(
    *,
    peripheral: str,
    register_name: str,
    name: str,
    bit_offset: int,
    bit_width: int,
) -> RegisterFieldDescriptor:
    provenance = _nxp_watchdog_provenance()
    register_id = f"register_{peripheral.lower()}_{register_name.lower()}"
    return RegisterFieldDescriptor(
        field_id=f"field_{peripheral.lower()}_{register_name.lower()}_{name.lower()}",
        register_id=register_id,
        peripheral=peripheral,
        register_name=register_name,
        name=name,
        bit_offset=bit_offset,
        bit_width=bit_width,
        access="read-write",
        provenance=provenance,
    )


def _nxp_can_provenance() -> Provenance:
    return Provenance(
        source_id="test-fixture",
        source_path="tests/test_nxp_mcux.py",
        patch_ids=("nxp-can-regression",),
    )


def _nxp_can_register(
    *,
    peripheral: str,
    name: str,
    offset_bytes: int,
) -> RegisterDescriptor:
    provenance = _nxp_can_provenance()
    return RegisterDescriptor(
        register_id=f"register_{peripheral.lower()}_{name.lower()}",
        peripheral=peripheral,
        name=name,
        offset_bytes=offset_bytes,
        access="read-write",
        size_bits=32,
        provenance=provenance,
    )


def _nxp_can_field(
    *,
    peripheral: str,
    register_name: str,
    name: str,
    bit_offset: int,
    bit_width: int,
) -> RegisterFieldDescriptor:
    provenance = _nxp_can_provenance()
    register_id = f"register_{peripheral.lower()}_{register_name.lower()}"
    return RegisterFieldDescriptor(
        field_id=f"field_{peripheral.lower()}_{register_name.lower()}_{name.lower()}",
        register_id=register_id,
        peripheral=peripheral,
        register_name=register_name,
        name=name,
        bit_offset=bit_offset,
        bit_width=bit_width,
        access="read-write",
        provenance=provenance,
    )


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
        s.source_id == "nxp-mcux-soc-svd" and s.upstream_path == f"{upstream}/{upstream}.xml"
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

    nxp_ver = nxp_result.payload.devices[0].schema_version
    st_ver = st_result.payload.devices[0].schema_version
    assert nxp_ver == st_ver


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


# ---------------------------------------------------------------------------
# Task 2.6: SVD/SDK naming alignment tests
# ---------------------------------------------------------------------------


def test_normalize_nxp_sdk_signal_peripherals_align_with_svd_names(
    nxp_execution_context: ExecutionContext,
) -> None:
    """Signal.peripheral must use the same case/name as the SVD peripheral."""
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    device = result.payload.devices[0]
    svd_names = {p.name for p in device.peripherals}

    for pin in device.pins:
        for signal in pin.signals:
            assert signal.peripheral in svd_names, (
                f"Pin {pin.name!r} signal peripheral {signal.peripheral!r} is not "
                f"an SVD peripheral name (known: {sorted(svd_names)})"
            )


def test_normalize_nxp_signaling_peripherals_have_ccm_clock_gate(
    nxp_execution_context: ExecutionContext,
) -> None:
    """Every peripheral referenced in SDK pin signals must have a CCM gate from the family patch."""
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    device = result.payload.devices[0]
    peripheral_map = {p.name: p for p in device.peripherals}
    signaled_peripherals = {signal.peripheral for pin in device.pins for signal in pin.signals}

    for name in signaled_peripherals:
        peripheral = peripheral_map.get(name)
        assert peripheral is not None
        assert peripheral.rcc_enable_signal is not None, (
            f"Peripheral {name!r} appears in SDK signals but has no CCM clock gate in family patch"
        )


def test_normalize_nxp_gpio_instance_numbers_match_name_suffix(
    nxp_execution_context: ExecutionContext,
) -> None:
    """GPIO1->instance=1, GPIO4->instance=4; NXP-style digit-suffixed names must not be mangled."""
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    device = result.payload.devices[0]

    for peripheral in device.peripherals:
        if peripheral.name.startswith("GPIO") and peripheral.name[4:].isdigit():
            expected = int(peripheral.name[4:])
            assert peripheral.instance == expected, (
                f"Peripheral {peripheral.name!r}: expected instance={expected}, "
                f"got instance={peripheral.instance}"
            )


def test_normalize_nxp_signal_function_names_use_peripheral_prefix(
    nxp_execution_context: ExecutionContext,
) -> None:
    """signal.function should be the lowercased SDK macro signal name (PERIPHERAL_SIGNAL)."""
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    device = result.payload.devices[0]

    for pin in device.pins:
        for signal in pin.signals:
            expected_prefix = signal.peripheral.lower() + "_"
            assert signal.function.startswith(expected_prefix), (
                f"Pin {pin.name!r} signal function {signal.function!r} does not start with "
                f"peripheral prefix {expected_prefix!r}"
            )


# ---------------------------------------------------------------------------
# Gate N3: Semantic closure — validation passes with zero critical conflicts
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("device_name", registered_device_names("nxp", "imxrt1060"))
def test_gate_n3_validation_passes_all_gates(
    device_name: str,
    nxp_execution_context: ExecutionContext,
) -> None:
    """Gate N3: full validate stage must pass gates A, B, and C with zero critical conflicts."""
    result = run_validate(PipelineScope(device=device_name), nxp_execution_context)
    report = result.payload.report

    assert result.status == "completed"
    assert report.gate_status("gate-a").passed, (
        f"{device_name}: gate-a failed — source manifest or schema rules not met"
    )
    assert report.gate_status("gate-b").passed, (
        f"{device_name}: gate-b failed — patch manifest or structural rules not met"
    )
    assert report.gate_status("gate-c").passed, (
        f"{device_name}: gate-c failed — semantic rules not met: "
        + str([r.rule_id for r in report.results if not r.passed])
    )


@pytest.mark.parametrize("device_name", registered_device_names("nxp", "imxrt1060"))
def test_gate_n3_no_critical_validation_failures(
    device_name: str,
    nxp_execution_context: ExecutionContext,
) -> None:
    """All validation rules must pass — no error-severity conflicts allowed."""
    result = run_validate(PipelineScope(device=device_name), nxp_execution_context)
    report = result.payload.report

    failed = [r for r in report.results if not r.passed and r.severity == "error"]
    assert not failed, f"{device_name}: {len(failed)} critical validation failure(s): " + ", ".join(
        r.rule_id for r in failed
    )


# ---------------------------------------------------------------------------
# Phase 3: Emission, publication, and Alloy consumption
# ---------------------------------------------------------------------------


def test_emit_nxp_imxrt1060_produces_required_artifacts(
    nxp_execution_context: ExecutionContext,
) -> None:
    """Task 3.1: emit stage produces all required artifact types for nxp/imxrt1060."""
    result = run_emit(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    assert result.stage == "emit"
    assert result.status == "completed"

    artifacts = {a.path: a for a in result.payload.artifacts}
    family_dir = "nxp/imxrt1060"

    assert f"{family_dir}/artifact-manifest.json" in artifacts
    assert f"{family_dir}/reports/validation-report.json" in artifacts
    assert f"{family_dir}/reports/runtime-provenance.json" in artifacts
    assert f"{family_dir}/reports/runtime-explainability.json" in artifacts
    assert f"{family_dir}/reports/runtime-capability-summary.json" in artifacts
    assert f"{family_dir}/reports/runtime-compatibility-matrix.json" in artifacts
    assert f"{family_dir}/metadata/family-index.json" in artifacts
    assert f"{family_dir}/metadata/family-connectivity.json" in artifacts
    assert f"{family_dir}/generated/devices/mimxrt1062/startup.cpp" in artifacts
    assert f"{family_dir}/generated/devices/mimxrt1062/startup_vectors.cpp" in artifacts
    assert f"{family_dir}/generated/runtime/types.hpp" in artifacts
    assert (
        f"{family_dir}/generated/runtime/devices/mimxrt1062/peripheral_instances.hpp" in artifacts
    )
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/pins.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/registers.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/register_fields.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/clock_bindings.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/system_clock.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/clock_profiles.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/clock_config.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/low_power.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/routes.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/connectors.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/startup.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/interrupts.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/interrupt_stubs.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/resets.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/enable_domains.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/clock_graph.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/capabilities.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/capabilities.json" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/system_sequences.hpp" in artifacts
    assert not any(p.startswith(f"{family_dir}/generated/peripherals/") for p in artifacts)
    assert not any(p.startswith(f"{family_dir}/generated/ip/") for p in artifacts)


def test_emit_nxp_imxrt1060_artifact_content(
    nxp_execution_context: ExecutionContext,
) -> None:
    """Task 3.1: emitted NXP artifacts contain correct C++ constructs."""
    result = run_emit(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    artifacts = {a.path: a for a in result.payload.artifacts}
    family_dir = "nxp/imxrt1060"

    runtime_types = artifacts[f"{family_dir}/generated/runtime/types.hpp"]
    runtime_peripherals = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/peripheral_instances.hpp"
    ]
    runtime_pins = artifacts[f"{family_dir}/generated/runtime/devices/mimxrt1062/pins.hpp"]
    runtime_registers = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/registers.hpp"
    ]
    runtime_register_fields = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/register_fields.hpp"
    ]
    runtime_clock_bindings = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/clock_bindings.hpp"
    ]
    runtime_clock_profiles = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/clock_profiles.hpp"
    ]
    runtime_clock_config = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/clock_config.hpp"
    ]
    runtime_low_power = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/low_power.hpp"
    ]
    runtime_routes = artifacts[f"{family_dir}/generated/runtime/devices/mimxrt1062/routes.hpp"]
    runtime_connectors = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/connectors.hpp"
    ]
    runtime_startup = artifacts[f"{family_dir}/generated/runtime/devices/mimxrt1062/startup.hpp"]
    runtime_interrupts = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/interrupts.hpp"
    ]
    runtime_interrupt_stubs = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/interrupt_stubs.hpp"
    ]
    runtime_resets = artifacts[f"{family_dir}/generated/runtime/devices/mimxrt1062/resets.hpp"]
    runtime_enable_domains = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/enable_domains.hpp"
    ]
    runtime_clock_graph = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/clock_graph.hpp"
    ]
    runtime_capabilities = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/capabilities.hpp"
    ]
    runtime_capabilities_json = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/capabilities.json"
    ]
    runtime_system_sequences = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/system_sequences.hpp"
    ]
    capability_summary_report = artifacts[f"{family_dir}/reports/runtime-capability-summary.json"]
    compatibility_matrix_report = artifacts[
        f"{family_dir}/reports/runtime-compatibility-matrix.json"
    ]
    assert "enum class BackendSchemaId" in runtime_types.content
    assert "enum class StartupKindId" in runtime_types.content
    assert "enum class VectorKindId" in runtime_types.content
    assert "PeripheralInstanceTraits<PeripheralId::" in runtime_peripherals.content
    assert "PinTraits<PinId::" in runtime_pins.content
    assert "RegisterTraits<RegisterId::" in runtime_registers.content
    assert "RegisterFieldTraits<FieldId::" in runtime_register_fields.content
    assert "PeripheralClockBindingTraits<PeripheralId::" in runtime_clock_bindings.content
    assert "kClockProfiles" in runtime_clock_profiles.content
    assert "kMaxClockProfileId" in runtime_clock_profiles.content
    assert "apply_default_clock_profile" in runtime_clock_config.content
    assert "apply_clock_profile_default_arm_pll_600mhz" in runtime_clock_config.content
    assert "kLowPowerModes" in runtime_low_power.content
    assert "RouteTraits<" in runtime_routes.content
    assert "ConnectorTraits<PinId::" in runtime_connectors.content
    assert "kConnectors" in runtime_connectors.content
    assert "kVectorSlots" in runtime_startup.content
    assert "kStartupDescriptors" in runtime_startup.content
    assert "kInterruptDescriptors" in runtime_interrupts.content
    assert "kInterruptStubs" in runtime_interrupt_stubs.content
    assert "InterruptStubTraits<InterruptId::" in runtime_interrupt_stubs.content
    assert "kResetDescriptors" in runtime_resets.content
    assert "kEnableDomains" in runtime_enable_domains.content
    assert "EnableDomainTraits<EnableDomainId::" in runtime_enable_domains.content
    assert "kClockDependencies" in runtime_clock_graph.content
    assert "kCapabilities" in runtime_capabilities.content
    assert '"device": "mimxrt1062"' in runtime_capabilities_json.content
    assert "kSystemSequenceSteps" in runtime_system_sequences.content
    assert (
        json.loads(capability_summary_report.content)["report_id"]
        == "runtime-capability-summary-v1"
    )
    assert (
        json.loads(compatibility_matrix_report.content)["report_id"]
        == "runtime-compatibility-matrix-v1"
    )


def test_emit_nxp_imxrt1060_reports_publishable_descriptor_coverage(
    nxp_execution_context: ExecutionContext,
) -> None:
    result = run_emit(PipelineScope(vendor="nxp", family="imxrt1060"), nxp_execution_context)
    artifacts = {a.path: a for a in result.payload.artifacts}
    coverage = json.loads(artifacts["nxp/imxrt1060/reports/coverage.json"].content)

    assert coverage["all_devices_publishable"] is True
    assert coverage["devices"]
    assert all(device["domains"]["ip-blocks"] is True for device in coverage["devices"])
    assert all(device["domains"]["dma"] is True for device in coverage["devices"])


def test_emit_nxp_imxrt1060_matches_golden_fixtures(
    nxp_execution_context: ExecutionContext,
    fixture_nxp_sources_root: Path,
) -> None:
    """Task 3.3: emitted mimxrt1062 C++ artifacts match committed golden files."""
    result = run_emit(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    artifacts = {a.path: a for a in result.payload.artifacts}
    family_dir = "nxp/imxrt1060"
    fixture_root = IMXRT1060_EMITTED_DIR

    for name in (
        "peripheral_instances.hpp",
        "pins.hpp",
        "registers.hpp",
        "register_fields.hpp",
        "clock_bindings.hpp",
        "clock_profiles.hpp",
        "clock_config.hpp",
        "connectors.hpp",
        "systick.hpp",
        "startup.hpp",
        "interrupts.hpp",
        "resets.hpp",
        "clock_graph.hpp",
        "capabilities.hpp",
        "system_sequences.hpp",
        "system_clock.hpp",
        "dma_bindings.hpp",
        "routes.hpp",
    ):
        assert artifacts[f"{family_dir}/generated/runtime/devices/mimxrt1062/{name}"].content == (
            fixture_root / "generated" / "runtime" / "devices" / "mimxrt1062" / name
        ).read_text(encoding="utf-8"), (
            f"generated/runtime/devices/mimxrt1062/{name} does not match golden fixture"
        )

    for name in (
        "common.hpp",
        "gpio.hpp",
        "uart.hpp",
        "i2c.hpp",
        "spi.hpp",
        "dma.hpp",
        "adc.hpp",
        "dac.hpp",
        "can.hpp",
        "eth.hpp",
        "usb.hpp",
        "qspi.hpp",
        "sdmmc.hpp",
        "rtc.hpp",
        "watchdog.hpp",
        "timer.hpp",
        "pwm.hpp",
    ):
        assert artifacts[
            f"{family_dir}/generated/runtime/devices/mimxrt1062/driver_semantics/{name}"
        ].content == (
            fixture_root
            / "generated"
            / "runtime"
            / "devices"
            / "mimxrt1062"
            / "driver_semantics"
            / name
        ).read_text(encoding="utf-8"), (
            "generated/runtime/devices/mimxrt1062/driver_semantics/"
            f"{name} does not match golden fixture"
        )

    assert not any(path.startswith(f"{family_dir}/generated/peripherals/") for path in artifacts)
    assert not any(path.startswith(f"{family_dir}/generated/ip/") for path in artifacts)


def test_emit_nxp_imxrt1060_is_byte_stable(nxp_execution_context: ExecutionContext) -> None:
    """Task 3.1: repeated emit runs produce byte-identical output."""
    result_a = json.dumps(
        run_emit(PipelineScope(device="mimxrt1062"), nxp_execution_context).to_dict(),
        sort_keys=True,
    )
    result_b = json.dumps(
        run_emit(PipelineScope(device="mimxrt1062"), nxp_execution_context).to_dict(),
        sort_keys=True,
    )
    assert result_a == result_b


def test_emit_nxp_timer_and_pwm_semantics_do_not_require_connection_candidates(
    nxp_execution_context: ExecutionContext,
) -> None:
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    base_device = result.payload.devices[0]
    gpio = next(peripheral for peripheral in base_device.peripherals if peripheral.name == "GPIO1")
    augmented = replace(
        base_device,
        peripherals=base_device.peripherals
        + (
            replace(
                gpio,
                name="GPT1",
                ip_name="GPT",
                backend_schema_id="alloy.gpt.nxp-gpt",
            ),
            replace(
                gpio,
                name="PIT",
                ip_name="PIT",
                backend_schema_id="alloy.pit.nxp-pit",
            ),
            replace(
                gpio,
                name="PWM1",
                ip_name="PWM",
                backend_schema_id="alloy.pwm.nxp-pwm",
            ),
        ),
        connection_candidates=tuple(),
    )

    context = _context(augmented)

    assert {peripheral.name for peripheral in context.runtime_peripherals_by_class["timer"]} >= {
        "GPT1",
        "PIT",
    }
    assert {peripheral.name for peripheral in context.runtime_peripherals_by_class["pwm"]} >= {
        "PWM1",
    }


def test_emit_nxp_watchdog_semantics_supports_live_watchdogs(
    nxp_execution_context: ExecutionContext,
) -> None:
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    base_device = result.payload.devices[0]
    provenance = _nxp_watchdog_provenance()

    augmented = replace(
        base_device,
        peripherals=base_device.peripherals
        + (
            PeripheralInstance(
                name="WDOG1",
                ip_name="WDOG",
                ip_version=None,
                instance=1,
                base_address=0x400B8000,
                rcc_enable_signal=None,
                rcc_reset_signal=None,
                provenance=provenance,
                backend_schema_id="alloy.watchdog.nxp-wdog",
            ),
            PeripheralInstance(
                name="WDOG2",
                ip_name="WDOG",
                ip_version=None,
                instance=2,
                base_address=0x400D0000,
                rcc_enable_signal=None,
                rcc_reset_signal=None,
                provenance=provenance,
                backend_schema_id="alloy.watchdog.nxp-wdog",
            ),
            PeripheralInstance(
                name="RTWDOG",
                ip_name="RTWDOG",
                ip_version=None,
                instance=0,
                base_address=0x400BC000,
                rcc_enable_signal=None,
                rcc_reset_signal=None,
                provenance=provenance,
                backend_schema_id="alloy.watchdog.nxp-rtwdog",
            ),
        ),
        registers=base_device.registers
        + (
            _nxp_watchdog_register(peripheral="WDOG1", name="WCR", offset_bytes=0x00),
            _nxp_watchdog_register(peripheral="WDOG1", name="WRSR", offset_bytes=0x04),
            _nxp_watchdog_register(peripheral="WDOG1", name="WSR", offset_bytes=0x08),
            _nxp_watchdog_register(peripheral="WDOG1", name="WICR", offset_bytes=0x0C),
            _nxp_watchdog_register(peripheral="WDOG2", name="WCR", offset_bytes=0x00),
            _nxp_watchdog_register(peripheral="WDOG2", name="WRSR", offset_bytes=0x04),
            _nxp_watchdog_register(peripheral="WDOG2", name="WSR", offset_bytes=0x08),
            _nxp_watchdog_register(peripheral="WDOG2", name="WICR", offset_bytes=0x0C),
            _nxp_watchdog_register(peripheral="RTWDOG", name="CS", offset_bytes=0x00),
            _nxp_watchdog_register(peripheral="RTWDOG", name="CNT", offset_bytes=0x04),
            _nxp_watchdog_register(peripheral="RTWDOG", name="TOVAL", offset_bytes=0x08),
            _nxp_watchdog_register(peripheral="RTWDOG", name="WIN", offset_bytes=0x0C),
        ),
        register_fields=base_device.register_fields
        + (
            _nxp_watchdog_field(
                peripheral="WDOG1",
                register_name="WCR",
                name="WDE",
                bit_offset=2,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG1",
                register_name="WCR",
                name="WT",
                bit_offset=8,
                bit_width=8,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG1",
                register_name="WCR",
                name="WDW",
                bit_offset=7,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG1",
                register_name="WCR",
                name="SRS",
                bit_offset=4,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG1",
                register_name="WICR",
                name="WIE",
                bit_offset=15,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG1",
                register_name="WRSR",
                name="TOUT",
                bit_offset=0,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG1",
                register_name="WRSR",
                name="SFTW",
                bit_offset=1,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG1",
                register_name="WSR",
                name="WSR",
                bit_offset=0,
                bit_width=16,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG2",
                register_name="WCR",
                name="WDE",
                bit_offset=2,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG2",
                register_name="WCR",
                name="WT",
                bit_offset=8,
                bit_width=8,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG2",
                register_name="WCR",
                name="WDW",
                bit_offset=7,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG2",
                register_name="WCR",
                name="SRS",
                bit_offset=4,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG2",
                register_name="WICR",
                name="WIE",
                bit_offset=15,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG2",
                register_name="WRSR",
                name="TOUT",
                bit_offset=0,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG2",
                register_name="WRSR",
                name="SFTW",
                bit_offset=1,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="WDOG2",
                register_name="WSR",
                name="WSR",
                bit_offset=0,
                bit_width=16,
            ),
            _nxp_watchdog_field(
                peripheral="RTWDOG",
                register_name="CS",
                name="EN",
                bit_offset=7,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="RTWDOG",
                register_name="CS",
                name="PRES",
                bit_offset=8,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="RTWDOG",
                register_name="CS",
                name="INT",
                bit_offset=6,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="RTWDOG",
                register_name="CS",
                name="FLG",
                bit_offset=14,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="RTWDOG",
                register_name="CS",
                name="UPDATE",
                bit_offset=5,
                bit_width=1,
            ),
            _nxp_watchdog_field(
                peripheral="RTWDOG",
                register_name="CNT",
                name="CNTLOW",
                bit_offset=0,
                bit_width=16,
            ),
            _nxp_watchdog_field(
                peripheral="RTWDOG",
                register_name="TOVAL",
                name="TOVALLOW",
                bit_offset=0,
                bit_width=16,
            ),
            _nxp_watchdog_field(
                peripheral="RTWDOG",
                register_name="WIN",
                name="WINLOW",
                bit_offset=0,
                bit_width=16,
            ),
        ),
        connection_candidates=tuple(),
    )

    artifact = emit_runtime_driver_watchdog_semantics_header(
        family_dir="nxp/imxrt1060",
        device=augmented,
    )

    assert "WatchdogSemanticTraits<PeripheralId::WDOG1>" in artifact.content
    assert "WatchdogSemanticTraits<PeripheralId::WDOG2>" in artifact.content
    assert "WatchdogSemanticTraits<PeripheralId::RTWDOG>" in artifact.content
    assert "kWatchdogSemanticPeripherals" in artifact.content


def test_emit_nxp_can_semantics_supports_live_flexcan(
    nxp_execution_context: ExecutionContext,
) -> None:
    result = run_normalize(PipelineScope(device="mimxrt1062"), nxp_execution_context)
    base_device = result.payload.devices[0]
    provenance = _nxp_can_provenance()
    augmented = replace(
        base_device,
        peripherals=base_device.peripherals
        + (
            PeripheralInstance(
                name="CAN1",
                ip_name="can",
                ip_version=None,
                instance=1,
                base_address=0x401D0000,
                rcc_enable_signal=None,
                rcc_reset_signal=None,
                provenance=provenance,
                backend_schema_id="alloy.can.nxp-can",
            ),
            PeripheralInstance(
                name="CAN2",
                ip_name="can",
                ip_version=None,
                instance=2,
                base_address=0x401D4000,
                rcc_enable_signal=None,
                rcc_reset_signal=None,
                provenance=provenance,
                backend_schema_id="alloy.can.nxp-can",
            ),
            PeripheralInstance(
                name="CAN3",
                ip_name="can",
                ip_version=None,
                instance=3,
                base_address=0x401D8000,
                rcc_enable_signal=None,
                rcc_reset_signal=None,
                provenance=provenance,
                backend_schema_id="alloy.can.nxp-can",
            ),
        ),
        registers=base_device.registers
        + tuple(
            _nxp_can_register(peripheral=peripheral, name=name, offset_bytes=offset)
            for peripheral in ("CAN1", "CAN2", "CAN3")
            for name, offset in (
                ("MCR", 0x00),
                ("CTRL1", 0x04),
                ("RXMGMASK", 0x10),
                ("RX14MASK", 0x14),
                ("RX15MASK", 0x18),
                ("ECR", 0x1C),
                ("ESR1", 0x20),
                ("IMASK1", 0x28),
                ("IFLAG1", 0x30),
                ("RXFGMASK", 0x48),
                ("RXFIR", 0x4C),
            )
        )
        + (_nxp_can_register(peripheral="CAN3", name="CBT", offset_bytes=0x50),),
        register_fields=base_device.register_fields
        + tuple(
            _nxp_can_field(
                peripheral=peripheral,
                register_name=register_name,
                name=name,
                bit_offset=bit_offset,
                bit_width=bit_width,
            )
            for peripheral in ("CAN1", "CAN2", "CAN3")
            for register_name, name, bit_offset, bit_width in (
                ("MCR", "HALT", 28, 1),
                ("MCR", "FRZ", 30, 1),
                ("MCR", "FRZACK", 24, 1),
                ("CTRL1", "LOM", 12, 1),
                ("CTRL1", "PRESDIV", 24, 8),
                ("CTRL1", "PSEG1", 19, 3),
                ("CTRL1", "PSEG2", 16, 3),
                ("CTRL1", "RJW", 22, 2),
                ("IMASK1", "BUF31TO0M", 0, 32),
                ("IFLAG1", "BUF0I", 0, 1),
                ("IFLAG1", "BUF5I", 5, 1),
                ("RXFIR", "IDHIT", 0, 9),
            )
        )
        + (
            _nxp_can_field(
                peripheral="CAN3",
                register_name="MCR",
                name="FDEN",
                bit_offset=11,
                bit_width=1,
            ),
            _nxp_can_field(
                peripheral="CAN3",
                register_name="CBT",
                name="EPRESDIV",
                bit_offset=21,
                bit_width=10,
            ),
            _nxp_can_field(
                peripheral="CAN3",
                register_name="CBT",
                name="EPSEG1",
                bit_offset=10,
                bit_width=5,
            ),
            _nxp_can_field(
                peripheral="CAN3",
                register_name="CBT",
                name="EPSEG2",
                bit_offset=5,
                bit_width=5,
            ),
            _nxp_can_field(
                peripheral="CAN3",
                register_name="CBT",
                name="ERJW",
                bit_offset=16,
                bit_width=5,
            ),
            _nxp_can_field(
                peripheral="CAN3",
                register_name="CBT",
                name="BTF",
                bit_offset=31,
                bit_width=1,
            ),
        ),
    )
    artifact = emit_runtime_driver_can_semantics_header(
        family_dir="nxp/imxrt1060",
        device=augmented,
    )

    assert "CanSemanticTraits<PeripheralId::CAN1>" in artifact.content
    assert "CanSemanticTraits<PeripheralId::CAN2>" in artifact.content
    assert "CanSemanticTraits<PeripheralId::CAN3>" in artifact.content
    assert "static constexpr bool kPresent = true;" in artifact.content


def test_publish_nxp_imxrt1060_completes_successfully(
    nxp_execution_context: ExecutionContext,
) -> None:
    """Task 3.2: publish stage completes for nxp/imxrt1060 and materializes artifacts."""
    result = run_publish(PipelineScope(device="mimxrt1062"), nxp_execution_context)

    assert result.stage == "publish"
    assert result.status == "completed"
    assert result.payload.publication_mode == "published"

    pub_root = nxp_execution_context.publication_root
    assert (
        pub_root / "nxp" / "imxrt1060" / "generated" / "devices" / "mimxrt1062" / "startup.cpp"
    ).exists()
    assert (
        pub_root
        / "nxp"
        / "imxrt1060"
        / "generated"
        / "runtime"
        / "devices"
        / "mimxrt1062"
        / "startup.hpp"
    ).exists()
    assert (
        pub_root
        / "nxp"
        / "imxrt1060"
        / "generated"
        / "devices"
        / "mimxrt1062"
        / "startup_vectors.cpp"
    ).exists()
    assert (pub_root / "nxp" / "imxrt1060" / "artifact-manifest.json").exists()
    assert (pub_root / "nxp" / "imxrt1060" / "reports" / "validation-report.json").exists()


def test_publish_nxp_imxrt1060_consumer_smoke_passes(
    nxp_execution_context: ExecutionContext,
) -> None:
    """Task 3.4: Alloy consumer smoke path succeeds when built from published NXP artifacts."""
    result = run_publish(PipelineScope(device="mimxrt1062"), nxp_execution_context)

    assert result.payload.consumer_verification is not None
    assert result.payload.consumer_verification.succeeded is True, (
        "Alloy consumer smoke build failed for nxp/imxrt1060/mimxrt1062:\n"
        + result.payload.consumer_verification.stderr
    )
