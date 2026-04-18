"""Tests for NXP MCUXpresso source adapter and imxrt1060 pipeline."""

from __future__ import annotations

import json
from dataclasses import replace
from pathlib import Path

import pytest

from alloy_codegen.bootstrap import registered_device_names
from alloy_codegen.context import ExecutionContext
from alloy_codegen.runtime_driver_semantics import _context
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.fetch import run as run_fetch
from alloy_codegen.stages.normalize import run as run_normalize
from alloy_codegen.stages.publish import run as run_publish
from alloy_codegen.stages.validate import run as run_validate

IMXRT1060_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "imxrt1060"
IMXRT1060_EMITTED_DIR = Path(__file__).parent / "fixtures" / "emitted" / "imxrt1060"


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
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/routes.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/startup.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/interrupts.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/resets.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/enable_domains.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/clock_graph.hpp" in artifacts
    assert f"{family_dir}/generated/runtime/devices/mimxrt1062/capabilities.hpp" in artifacts
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
    runtime_routes = artifacts[f"{family_dir}/generated/runtime/devices/mimxrt1062/routes.hpp"]
    runtime_startup = artifacts[f"{family_dir}/generated/runtime/devices/mimxrt1062/startup.hpp"]
    runtime_interrupts = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/interrupts.hpp"
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
    runtime_system_sequences = artifacts[
        f"{family_dir}/generated/runtime/devices/mimxrt1062/system_sequences.hpp"
    ]
    assert "enum class BackendSchemaId" in runtime_types.content
    assert "enum class StartupKindId" in runtime_types.content
    assert "enum class VectorKindId" in runtime_types.content
    assert "PeripheralInstanceTraits<PeripheralId::" in runtime_peripherals.content
    assert "PinTraits<PinId::" in runtime_pins.content
    assert "RegisterTraits<RegisterId::" in runtime_registers.content
    assert "RegisterFieldTraits<FieldId::" in runtime_register_fields.content
    assert "PeripheralClockBindingTraits<PeripheralId::" in runtime_clock_bindings.content
    assert "RouteTraits<" in runtime_routes.content
    assert "kVectorSlots" in runtime_startup.content
    assert "kStartupDescriptors" in runtime_startup.content
    assert "kInterruptDescriptors" in runtime_interrupts.content
    assert "kResetDescriptors" in runtime_resets.content
    assert "kEnableDomains" in runtime_enable_domains.content
    assert "EnableDomainTraits<EnableDomainId::" in runtime_enable_domains.content
    assert "kClockDependencies" in runtime_clock_graph.content
    assert "kCapabilities" in runtime_capabilities.content
    assert "kSystemSequenceSteps" in runtime_system_sequences.content


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
