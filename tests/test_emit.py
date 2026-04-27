from __future__ import annotations

import json
from dataclasses import replace
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import (
    CanonicalDeviceIR,
    DeviceIdentity,
    MemoryRegion,
    PeripheralInstance,
    Provenance,
    RegisterDescriptor,
    RegisterFieldDescriptor,
)
from alloy_codegen.runtime_driver_semantics import (
    emit_runtime_driver_can_semantics_header,
    emit_runtime_driver_timer_semantics_header,
    emit_runtime_driver_uart_semantics_header,
    emit_runtime_driver_usb_semantics_header,
)
from alloy_codegen.runtime_linker_script import emit_runtime_linker_script
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run
from alloy_codegen.stages.normalize import run as run_normalize


def _load_json_fixture(path: Path) -> dict[str, object]:
    return json.loads(path.read_text(encoding="utf-8"))


def _normalize_manifest_payload(
    payload: dict[str, object],
    *,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
) -> dict[str, object]:
    normalized = json.loads(json.dumps(payload))
    source_manifest = normalized["source_manifest"]
    for source in source_manifest["sources"]:
        local_path = Path(source["local_path"])
        if fixture_source_root in local_path.parents:
            source["local_path"] = str(local_path.relative_to(fixture_source_root))
        elif fixture_pin_source_root in local_path.parents:
            source["local_path"] = str(local_path.relative_to(fixture_pin_source_root))
    return normalized


def _synthetic_timer_provenance() -> Provenance:
    return Provenance(
        source_id="test-fixture",
        source_path="tests/test_emit.py",
        patch_ids=("timer-advanced-semantics-regression",),
    )


def _synthetic_timer_register(
    *,
    peripheral: str,
    name: str,
    offset_bytes: int,
) -> RegisterDescriptor:
    provenance = _synthetic_timer_provenance()
    return RegisterDescriptor(
        register_id=f"register_{peripheral.lower()}_{name.lower()}",
        peripheral=peripheral,
        name=name,
        offset_bytes=offset_bytes,
        access="read-write",
        size_bits=32,
        provenance=provenance,
    )


def _synthetic_bxcan_provenance() -> Provenance:
    return Provenance(
        source_id="test-fixture",
        source_path="tests/test_emit.py",
        patch_ids=("can-bxcan-semantic-regression",),
    )


def _synthetic_bxcan_register(
    *,
    peripheral: str,
    name: str,
    offset_bytes: int,
) -> RegisterDescriptor:
    provenance = _synthetic_bxcan_provenance()
    return RegisterDescriptor(
        register_id=f"register_{peripheral.lower()}_{name.lower()}",
        peripheral=peripheral,
        name=name,
        offset_bytes=offset_bytes,
        access="read-write",
        size_bits=32,
        provenance=provenance,
    )


def _synthetic_bxcan_field(
    *,
    peripheral: str,
    register_name: str,
    name: str,
    bit_offset: int,
    bit_width: int,
) -> RegisterFieldDescriptor:
    provenance = _synthetic_bxcan_provenance()
    return RegisterFieldDescriptor(
        field_id=f"field_{peripheral.lower()}_{register_name.lower()}_{name.lower()}",
        register_id=f"register_{peripheral.lower()}_{register_name.lower()}",
        peripheral=peripheral,
        register_name=register_name,
        name=name,
        bit_offset=bit_offset,
        bit_width=bit_width,
        access="read-write",
        provenance=provenance,
    )


def _synthetic_usb_provenance() -> Provenance:
    return Provenance(
        source_id="test-fixture",
        source_path="tests/test_emit.py",
        patch_ids=("usb-wave2-semantic-regression",),
    )


def _synthetic_usb_register(
    *,
    peripheral: str,
    name: str,
    offset_bytes: int,
) -> RegisterDescriptor:
    provenance = _synthetic_usb_provenance()
    return RegisterDescriptor(
        register_id=f"register_{peripheral.lower()}_{name.lower()}",
        peripheral=peripheral,
        name=name,
        offset_bytes=offset_bytes,
        access="read-write",
        size_bits=32,
        provenance=provenance,
    )


def _synthetic_usb_field(
    *,
    peripheral: str,
    register_name: str,
    name: str,
    bit_offset: int,
    bit_width: int,
) -> RegisterFieldDescriptor:
    provenance = _synthetic_usb_provenance()
    return RegisterFieldDescriptor(
        field_id=f"field_{peripheral.lower()}_{register_name.lower()}_{name.lower()}",
        register_id=f"register_{peripheral.lower()}_{register_name.lower()}",
        peripheral=peripheral,
        register_name=register_name,
        name=name,
        bit_offset=bit_offset,
        bit_width=bit_width,
        access="read-write",
        provenance=provenance,
    )


def _synthetic_linker_provenance() -> Provenance:
    return Provenance(
        source_id="test-fixture",
        source_path="tests/test_emit.py",
        patch_ids=("harvard-linker-script",),
    )


def test_emit_linker_script_disambiguates_harvard_address_spaces() -> None:
    provenance = _synthetic_linker_provenance()
    device = CanonicalDeviceIR(
        schema_version="1.1.0",
        identity=DeviceIdentity(
            vendor="microchip",
            family="avr-da",
            device="avr128da64",
            package="tqfp64",
            core="avr",
            summary="synthetic harvard device",
        ),
        memories=(
            MemoryRegion(
                name="flash",
                kind="flash",
                base_address=0x0000,
                size_bytes=0x20000,
                access="rx",
                provenance=provenance,
                address_space="prog",
                startup_roles=("nonvolatile", "copy-source", "vector-source"),
            ),
            MemoryRegion(
                name="sram",
                kind="ram",
                base_address=0x0000,
                size_bytes=0x4000,
                access="rw",
                provenance=provenance,
                address_space="data",
                startup_roles=("copy-target", "zero-target", "stack-target"),
            ),
        ),
        packages=(),
        pins=(),
        peripherals=(),
        interrupts=(),
        dma_requests=(),
        provenance=provenance,
    )

    artifact = emit_runtime_linker_script(family_dir="microchip/avr-da", device=device)

    assert "PROG_FLASH" in artifact.content
    assert "DATA_SRAM" in artifact.content
    assert "address_space=prog" in artifact.content
    assert "address_space=data" in artifact.content


def test_emit_includes_metadata_artifacts_with_content(
    execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}

    assert result.stage == "emit"
    assert result.payload.artifact_manifest.manifest_kind == "artifact-manifest-v1"

    manifest_artifact = artifacts["st/stm32g0/artifact-manifest.json"]
    validation_artifact = artifacts["st/stm32g0/reports/validation-report.json"]
    validation_summary_artifact = artifacts["st/stm32g0/reports/validation-summary.json"]
    coverage_artifact = artifacts["st/stm32g0/reports/coverage.json"]
    provenance_report_artifact = artifacts["st/stm32g0/reports/runtime-provenance.json"]
    explainability_report_artifact = artifacts["st/stm32g0/reports/runtime-explainability.json"]
    capability_summary_report_artifact = artifacts[
        "st/stm32g0/reports/runtime-capability-summary.json"
    ]
    compatibility_matrix_report_artifact = artifacts[
        "st/stm32g0/reports/runtime-compatibility-matrix.json"
    ]
    family_index_artifact = artifacts["st/stm32g0/metadata/family-index.json"]
    connectivity_artifact = artifacts["st/stm32g0/metadata/family-connectivity.json"]
    ip_blocks_artifact = artifacts["st/stm32g0/metadata/ip-blocks.json"]
    capabilities_artifact = artifacts["st/stm32g0/metadata/capabilities.json"]
    packages_artifact = artifacts["st/stm32g0/metadata/packages.json"]
    connectors_artifact = artifacts["st/stm32g0/metadata/connectors.json"]
    system_descriptors_artifact = artifacts["st/stm32g0/metadata/system-descriptors.json"]
    device_artifact = artifacts["st/stm32g0/metadata/devices/stm32g071rb.json"]
    linker_script_artifact = artifacts["st/stm32g0/generated/devices/stm32g071rb/device.ld"]
    startup_source_artifact = artifacts["st/stm32g0/generated/devices/stm32g071rb/startup.cpp"]
    startup_vectors_artifact = artifacts[
        "st/stm32g0/generated/devices/stm32g071rb/startup_vectors.cpp"
    ]
    runtime_types_artifact = artifacts["st/stm32g0/generated/runtime/types.hpp"]
    runtime_peripheral_instances_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/peripheral_instances.hpp"
    ]
    runtime_pins_artifact = artifacts["st/stm32g0/generated/runtime/devices/stm32g071rb/pins.hpp"]
    runtime_registers_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/registers.hpp"
    ]
    runtime_register_fields_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/register_fields.hpp"
    ]
    runtime_clock_bindings_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/clock_bindings.hpp"
    ]
    runtime_dma_bindings_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/dma_bindings.hpp"
    ]
    runtime_routes_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/routes.hpp"
    ]
    runtime_connectors_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/connectors.hpp"
    ]
    runtime_driver_common_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/common.hpp"
    ]
    runtime_gpio_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/gpio.hpp"
    ]
    runtime_uart_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/uart.hpp"
    ]
    runtime_i2c_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/i2c.hpp"
    ]
    runtime_spi_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/spi.hpp"
    ]
    runtime_dma_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/dma.hpp"
    ]
    runtime_adc_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/adc.hpp"
    ]
    runtime_dac_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/dac.hpp"
    ]
    runtime_can_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/can.hpp"
    ]
    runtime_eth_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/eth.hpp"
    ]
    runtime_usb_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/usb.hpp"
    ]
    runtime_qspi_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/qspi.hpp"
    ]
    runtime_sdmmc_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/sdmmc.hpp"
    ]
    runtime_rtc_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/rtc.hpp"
    ]
    runtime_watchdog_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/watchdog.hpp"
    ]
    runtime_timer_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/timer.hpp"
    ]
    runtime_pwm_semantics_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/pwm.hpp"
    ]
    runtime_startup_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/startup.hpp"
    ]
    runtime_interrupts_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/interrupts.hpp"
    ]
    runtime_interrupt_stubs_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/interrupt_stubs.hpp"
    ]
    runtime_resets_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/resets.hpp"
    ]
    runtime_enable_domains_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/enable_domains.hpp"
    ]
    runtime_clock_graph_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/clock_graph.hpp"
    ]
    runtime_capabilities_contract_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/capabilities.hpp"
    ]
    runtime_capabilities_json_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/capabilities.json"
    ]
    runtime_system_sequences_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/system_sequences.hpp"
    ]
    runtime_system_clock_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/system_clock.hpp"
    ]
    runtime_clock_profiles_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/clock_profiles.hpp"
    ]
    runtime_clock_config_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/clock_config.hpp"
    ]
    runtime_low_power_artifact = artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/low_power.hpp"
    ]
    assert not any(path.startswith("st/stm32g0/generated/ip/") for path in artifacts), (
        "Legacy IP headers should not be published"
    )
    assert not any(path.startswith("st/stm32g0/generated/peripherals/") for path in artifacts), (
        "Legacy peripheral headers should not be published"
    )

    for artifact in (
        manifest_artifact,
        validation_artifact,
        validation_summary_artifact,
        coverage_artifact,
        provenance_report_artifact,
        explainability_report_artifact,
        capability_summary_report_artifact,
        compatibility_matrix_report_artifact,
        family_index_artifact,
        connectivity_artifact,
        ip_blocks_artifact,
        capabilities_artifact,
        packages_artifact,
        connectors_artifact,
        system_descriptors_artifact,
        device_artifact,
    ):
        assert artifact.artifact_kind in {
            "canonical-metadata",
            "validation-report",
            "coverage-report",
            "runtime-report",
        }
        assert artifact.content is not None
        assert artifact.content_sha256 is not None
        assert artifact.content_bytes and artifact.content_bytes > 0
        assert artifact.materialized_path is not None
        assert Path(artifact.materialized_path).exists()

    manifest_payload = json.loads(manifest_artifact.content)
    validation_payload = json.loads(validation_artifact.content)
    validation_summary_payload = json.loads(validation_summary_artifact.content)
    coverage_payload = json.loads(coverage_artifact.content)
    provenance_report_payload = json.loads(provenance_report_artifact.content)
    explainability_report_payload = json.loads(explainability_report_artifact.content)
    capability_summary_payload = json.loads(capability_summary_report_artifact.content)
    compatibility_matrix_payload = json.loads(compatibility_matrix_report_artifact.content)
    family_index_payload = json.loads(family_index_artifact.content)
    connectivity_payload = json.loads(connectivity_artifact.content)
    ip_blocks_payload = json.loads(ip_blocks_artifact.content)
    capabilities_payload = json.loads(capabilities_artifact.content)
    packages_payload = json.loads(packages_artifact.content)
    connectors_payload = json.loads(connectors_artifact.content)
    system_descriptors_payload = json.loads(system_descriptors_artifact.content)
    device_payload = json.loads(device_artifact.content)

    assert manifest_payload["manifest_kind"] == "artifact-manifest-v1"
    assert manifest_payload["validation_report_id"] == "bootstrap-validation-v1"
    assert len(manifest_payload["canonical_ir_sha256"]) == 64
    assert len(manifest_payload["validation_report_sha256"]) == 64
    assert manifest_payload["source_manifest"]["manifest_kind"] == "source-manifest-v1"
    assert manifest_payload["patch_manifest"]["manifest_kind"] == "patch-manifest-v1"
    assert manifest_payload["build_metadata"]["target_repository"] == "alloy-devices"
    assert manifest_payload["build_metadata"]["artifact_layout_version"] == "alloy-devices-v1"
    assert validation_payload["report_id"] == "bootstrap-validation-v1"
    assert validation_payload["draft_system_descriptor_domains"] == []
    assert any(
        domain["domain_id"] == "startup" and domain["passed"] is True
        for domain in validation_payload["system_descriptor_domains"]
    )
    assert validation_summary_payload["report_id"] == "bootstrap-validation-v1"
    assert validation_summary_payload["device_count"] == 1
    assert validation_summary_payload["devices"][0]["device"] == "stm32g071rb"
    assert coverage_payload["all_devices_publishable"] is True
    assert coverage_payload["devices"][0]["domains"]["startup"] is True
    assert coverage_payload["devices"][0]["counts"]["connection_candidates"] > 0
    assert provenance_report_payload["report_id"] == "runtime-provenance-v1"
    assert provenance_report_payload["devices"][0]["device"] == "stm32g071rb"
    assert provenance_report_payload["devices"][0]["fact_count"] > 0
    assert explainability_report_payload["report_id"] == "runtime-explainability-v1"
    assert explainability_report_payload["devices"][0]["device"] == "stm32g071rb"
    assert explainability_report_payload["devices"][0]["route_decision_count"] > 0
    assert any(
        coverage["coverage_kind"] in {"instance", "class-only"}
        for coverage in explainability_report_payload["devices"][0]["capability_coverage"]
    )
    assert capability_summary_payload["report_id"] == "runtime-capability-summary-v1"
    assert capability_summary_payload["devices"][0]["device"] == "stm32g071rb"
    assert any(row["peripheral_class"] == "uart" for row in capability_summary_payload["classes"])
    assert compatibility_matrix_payload["report_id"] == "runtime-compatibility-matrix-v1"
    assert "gpio" in compatibility_matrix_payload["driver_classes"]
    assert compatibility_matrix_payload["devices"][0]["device"] == "stm32g071rb"
    assert family_index_payload["device_count"] == 1
    assert family_index_payload["devices"][0]["device"] == "stm32g071rb"
    assert (
        family_index_payload["devices"][0]["metadata_path"]
        == "st/stm32g0/metadata/devices/stm32g071rb.json"
    )
    assert ip_blocks_payload["family"] == "stm32g0"
    assert ip_blocks_payload["ip_blocks"]
    assert capabilities_payload["capabilities"]
    assert packages_payload["packages"]
    assert packages_payload["packages"][0]["pads"]
    assert packages_payload["packages"][0]["pinouts"]
    assert packages_payload["packages"][0]["pinouts"][0]["pinout"]
    assert packages_payload["packages"][0]["pinouts"][0]["pin_index"]
    assert connectors_payload["signal_endpoints"]
    assert connectors_payload["devices"][0]["device"] == "stm32g071rb"
    assert any(
        candidate["route_kind"] == "alternate-function"
        for candidate in connectors_payload["devices"][0]["connection_candidates"]
    )
    assert system_descriptors_payload["devices"][0]["device"] == "stm32g071rb"
    assert system_descriptors_payload["devices"][0]["vector_slots"]
    assert system_descriptors_payload["devices"][0]["startup_descriptors"]
    assert system_descriptors_payload["devices"][0]["clock_gates"]
    assert system_descriptors_payload["devices"][0]["dma_routes"]
    assert any(
        memory.get("startup_roles")
        for memory in system_descriptors_payload["devices"][0]["memories"]
    )
    assert any(pin["name"] == "PA0" for pin in connectivity_payload["pins"])
    assert device_payload["identity"]["device"] == "stm32g071rb"
    assert system_descriptors_payload["devices"][0]["vector_slots"][0]["slot"] == 0
    assert (
        system_descriptors_payload["devices"][0]["startup_descriptors"][0]["kind"]
        == "initial-stack-pointer"
        or system_descriptors_payload["devices"][0]["startup_descriptors"][0]["kind"]
        == "vector-table"
    )
    assert [
        pad["pad_id"] for pad in packages_payload["packages"][0]["pinouts"][0]["pinout"]
    ] == sorted(
        [pad["pad_id"] for pad in packages_payload["packages"][0]["pinouts"][0]["pinout"]],
        key=int,
    )
    assert any(
        pin_entry["pin"] == "PA0" and "17" in pin_entry["pad_ids"]
        for pin_entry in packages_payload["packages"][0]["pinouts"][0]["pin_index"]
    )

    assert linker_script_artifact.artifact_kind == "generated-linker-script"
    assert "MEMORY" in linker_script_artifact.content
    assert "SECTIONS" in linker_script_artifact.content
    assert "__stack_top" in linker_script_artifact.content
    assert startup_source_artifact.artifact_kind == "generated-cpp"
    assert "Reset_Handler" in startup_source_artifact.content
    assert "_vectors" in startup_source_artifact.content

    assert startup_vectors_artifact.artifact_kind == "generated-cpp"
    assert "../../runtime/devices/stm32g071rb/startup.hpp" in startup_vectors_artifact.content
    assert runtime_types_artifact.artifact_kind == "generated-cpp"
    assert "enum class BackendSchemaId" in runtime_types_artifact.content
    assert "enum class StartupKindId" in runtime_types_artifact.content
    assert "enum class VectorKindId" in runtime_types_artifact.content
    assert runtime_peripheral_instances_artifact.artifact_kind == "generated-cpp"
    assert (
        "PeripheralInstanceTraits<PeripheralId::" in runtime_peripheral_instances_artifact.content
    )
    assert runtime_pins_artifact.artifact_kind == "generated-cpp"
    assert "PinTraits<PinId::" in runtime_pins_artifact.content
    assert runtime_registers_artifact.artifact_kind == "generated-cpp"
    assert "RegisterTraits<RegisterId::" in runtime_registers_artifact.content
    assert runtime_register_fields_artifact.artifact_kind == "generated-cpp"
    assert "RegisterFieldTraits<FieldId::" in runtime_register_fields_artifact.content
    assert runtime_clock_bindings_artifact.artifact_kind == "generated-cpp"
    assert "PeripheralClockBindingTraits<PeripheralId::" in runtime_clock_bindings_artifact.content
    assert runtime_dma_bindings_artifact.artifact_kind == "generated-cpp"
    assert "BindingTraits<PeripheralId" in runtime_dma_bindings_artifact.content
    assert "ControllerTraits<DmaControllerId" in runtime_dma_bindings_artifact.content
    assert runtime_routes_artifact.artifact_kind == "generated-cpp"
    assert "RouteTraits<" in runtime_routes_artifact.content
    assert runtime_connectors_artifact.artifact_kind == "generated-cpp"
    assert "ConnectorTraits<PinId::" in runtime_connectors_artifact.content
    assert "ConnectorSignalTraits<PeripheralId::" in runtime_connectors_artifact.content
    assert "kConnectors" in runtime_connectors_artifact.content
    assert "ConnectionGroupTraits<" in runtime_routes_artifact.content
    assert runtime_driver_common_artifact.artifact_kind == "generated-cpp"
    assert "struct RuntimeRegisterRef" in runtime_driver_common_artifact.content
    assert runtime_gpio_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct GpioSemanticTraits" in runtime_gpio_semantics_artifact.content
    assert "kGpioSemanticPins" in runtime_gpio_semantics_artifact.content
    assert runtime_uart_semantics_artifact.artifact_kind == "generated-cpp"
    assert "UartSemanticTraits<PeripheralId::" in runtime_uart_semantics_artifact.content
    assert runtime_i2c_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct I2cSemanticTraits" in runtime_i2c_semantics_artifact.content
    assert "kI2cSemanticPeripherals" in runtime_i2c_semantics_artifact.content
    assert runtime_spi_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct SpiSemanticTraits" in runtime_spi_semantics_artifact.content
    assert "kSpiSemanticPeripherals" in runtime_spi_semantics_artifact.content
    assert runtime_dma_semantics_artifact.artifact_kind == "generated-cpp"
    assert "DmaSemanticTraits<PeripheralId" in runtime_dma_semantics_artifact.content
    assert "kDmaSemanticPeripherals" in runtime_dma_semantics_artifact.content
    assert runtime_adc_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct AdcSemanticTraits" in runtime_adc_semantics_artifact.content
    assert "kAdcSemanticPeripherals" in runtime_adc_semantics_artifact.content
    assert runtime_dac_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct DacSemanticTraits" in runtime_dac_semantics_artifact.content
    assert "struct DacChannelSemanticTraits" in runtime_dac_semantics_artifact.content
    assert "kDacSemanticPeripherals" in runtime_dac_semantics_artifact.content
    assert runtime_can_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct CanSemanticTraits" in runtime_can_semantics_artifact.content
    assert "kCanSemanticPeripherals" in runtime_can_semantics_artifact.content
    assert runtime_eth_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct EthSemanticTraits" in runtime_eth_semantics_artifact.content
    assert "kEthSemanticPeripherals" in runtime_eth_semantics_artifact.content
    assert runtime_usb_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct UsbSemanticTraits" in runtime_usb_semantics_artifact.content
    assert "kUsbSemanticPeripherals" in runtime_usb_semantics_artifact.content
    assert runtime_qspi_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct QspiSemanticTraits" in runtime_qspi_semantics_artifact.content
    assert "kQspiSemanticPeripherals" in runtime_qspi_semantics_artifact.content
    assert runtime_sdmmc_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct SdmmcSemanticTraits" in runtime_sdmmc_semantics_artifact.content
    assert "kSdmmcSemanticPeripherals" in runtime_sdmmc_semantics_artifact.content
    assert runtime_rtc_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct RtcSemanticTraits" in runtime_rtc_semantics_artifact.content
    assert "kRtcSemanticPeripherals" in runtime_rtc_semantics_artifact.content
    assert runtime_watchdog_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct WatchdogSemanticTraits" in runtime_watchdog_semantics_artifact.content
    assert "kWatchdogSemanticPeripherals" in runtime_watchdog_semantics_artifact.content
    assert runtime_timer_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct TimerSemanticTraits" in runtime_timer_semantics_artifact.content
    assert "struct TimerChannelSemanticTraits" in runtime_timer_semantics_artifact.content
    assert "kHasEncoder" in runtime_timer_semantics_artifact.content
    assert "kSupportsEncoderInput" in runtime_timer_semantics_artifact.content
    assert "kTimerSemanticPeripherals" in runtime_timer_semantics_artifact.content
    assert runtime_pwm_semantics_artifact.artifact_kind == "generated-cpp"
    assert "struct PwmSemanticTraits" in runtime_pwm_semantics_artifact.content
    assert "struct PwmChannelSemanticTraits" in runtime_pwm_semantics_artifact.content
    assert "kPwmSemanticPeripherals" in runtime_pwm_semantics_artifact.content
    assert runtime_startup_artifact.artifact_kind == "generated-cpp"
    assert "struct VectorSlotDescriptor" in runtime_startup_artifact.content
    assert "StartupSymbolId" in runtime_startup_artifact.content
    assert "kVectorSlots" in runtime_startup_artifact.content
    assert "kStartupDescriptors" in runtime_startup_artifact.content
    assert runtime_interrupts_artifact.artifact_kind == "generated-cpp"
    assert "enum class InterruptId" in runtime_interrupts_artifact.content
    assert "kInterruptDescriptors" in runtime_interrupts_artifact.content
    assert runtime_interrupt_stubs_artifact.artifact_kind == "generated-cpp"
    assert 'extern "C"' in runtime_interrupt_stubs_artifact.content
    assert "kInterruptStubs" in runtime_interrupt_stubs_artifact.content
    assert "InterruptStubTraits<InterruptId::" in runtime_interrupt_stubs_artifact.content
    assert runtime_resets_artifact.artifact_kind == "generated-cpp"
    assert "kResetDescriptors" in runtime_resets_artifact.content
    assert runtime_enable_domains_artifact.artifact_kind == "generated-cpp"
    assert "using EnableDomainId = ClockGateId;" in runtime_enable_domains_artifact.content
    assert "kEnableDomains" in runtime_enable_domains_artifact.content
    assert "PeripheralEnableDomainTraits<PeripheralId::" in runtime_enable_domains_artifact.content
    assert runtime_clock_graph_artifact.artifact_kind == "generated-cpp"
    assert "enum class ClockNodeId" in runtime_clock_graph_artifact.content
    assert "kClockDependencies" in runtime_clock_graph_artifact.content
    assert runtime_capabilities_contract_artifact.artifact_kind == "generated-cpp"
    assert "enum class CapabilityId" in runtime_capabilities_contract_artifact.content
    assert (
        "PeripheralCapabilityTraits<PeripheralId::"
        in runtime_capabilities_contract_artifact.content
    )
    assert "kCapabilities" in runtime_capabilities_contract_artifact.content
    assert "CapabilityNameId::runtime_supported" in runtime_capabilities_contract_artifact.content
    assert runtime_capabilities_json_artifact.artifact_kind == "generated-runtime-metadata"
    assert '"device": "stm32g071rb"' in runtime_capabilities_json_artifact.content
    assert '"capabilities": [' in runtime_capabilities_json_artifact.content
    assert runtime_system_sequences_artifact.artifact_kind == "generated-cpp"
    assert "enum class SystemSequenceId" in runtime_system_sequences_artifact.content
    assert "kSystemSequenceSteps" in runtime_system_sequences_artifact.content
    assert (
        "SystemSequenceTraits<SystemSequenceId::default_bringup>"
        in runtime_system_sequences_artifact.content
    )
    assert runtime_system_clock_artifact.artifact_kind == "generated-cpp"
    assert (
        "SystemClockProfileTraits<SystemClockProfileId::" in runtime_system_clock_artifact.content
    )
    assert "apply_default_system_clock" in runtime_system_clock_artifact.content
    assert 'static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for ' in (
        runtime_connectors_artifact.content
    )
    assert runtime_clock_profiles_artifact.artifact_kind == "generated-cpp"
    assert "using ClockProfileId = SystemClockProfileId;" in runtime_clock_profiles_artifact.content
    assert "kClockProfiles" in runtime_clock_profiles_artifact.content
    assert "kMaxClockProfileId" in runtime_clock_profiles_artifact.content
    assert runtime_clock_config_artifact.artifact_kind == "generated-cpp"
    assert runtime_low_power_artifact.artifact_kind == "generated-cpp"
    assert "apply_default_clock_profile" in runtime_clock_config_artifact.content
    assert "enum class LowPowerModeId" in runtime_low_power_artifact.content
    assert "kLowPowerModes" in runtime_low_power_artifact.content
    assert "kWakeupSources" in runtime_low_power_artifact.content
    assert "apply_max_clock_profile" in runtime_clock_config_artifact.content
    assert "apply_clock_profile_default_pll_64mhz" in runtime_clock_config_artifact.content


def test_emit_runtime_lite_clock_bindings_are_executable_for_foundational_edges(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    stm32g0_artifacts = {
        artifact.path: artifact
        for artifact in run(
            PipelineScope(device="stm32g071rb"),
            execution_context,
        ).payload.artifacts
    }
    stm32f4_artifacts = {
        artifact.path: artifact
        for artifact in run(
            PipelineScope(device="stm32f401re"),
            execution_context,
        ).payload.artifacts
    }
    same70_artifacts = {
        artifact.path: artifact
        for artifact in run(
            PipelineScope(device="atsame70q21b"),
            microchip_execution_context,
        ).payload.artifacts
    }
    nxp_artifacts = {
        artifact.path: artifact
        for artifact in run(
            PipelineScope(device="mimxrt1062"),
            nxp_execution_context,
        ).payload.artifacts
    }

    stm32g0_clock_bindings = stm32g0_artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/clock_bindings.hpp"
    ].content
    assert "ClockGateTraits<ClockGateId::gate_gpioa>" in stm32g0_clock_bindings
    assert "FieldId::field_rcc_iopenr_gpioaen" in stm32g0_clock_bindings
    assert "ResetTraits<ResetId::reset_gpioa>" in stm32g0_clock_bindings
    assert "FieldId::field_rcc_ioprstr_gpioarst" in stm32g0_clock_bindings

    stm32f4_clock_bindings = stm32f4_artifacts[
        "st/stm32f4/generated/runtime/devices/stm32f401re/clock_bindings.hpp"
    ].content
    assert "ResetTraits<ResetId::reset_usart2>" in stm32f4_clock_bindings
    assert "FieldId::field_rcc_apb1rstr_usart2rst" in stm32f4_clock_bindings

    # §2.2 — NXP apply_route<> emits IOMUXC SW_MUX_CTL_PAD writes
    nxp_routes = nxp_artifacts[
        "nxp/imxrt1060/generated/runtime/devices/mimxrt1062/routes.hpp"
    ].content
    assert "apply_route<PinId::GPIO_AD_B0_00, PeripheralId::LPUART1" in nxp_routes
    assert "& ~std::uint32_t{0x7})" in nxp_routes  # MUX_MODE mask
    assert "0x401F8024u" in nxp_routes  # SW_MUX_CTL_PAD_GPIO_AD_B0_00

    # §1.2 — STM32 apply_route<> specializations emit MODER + AFR writes
    stm32g0_routes = stm32g0_artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/routes.hpp"
    ].content
    assert "apply_route<PinId::PB6, PeripheralId::USART1" in stm32g0_routes
    assert "0x3} << 12)" in stm32g0_routes  # MODER bits[13:12] for PB6
    assert "0xF} << 24)" in stm32g0_routes  # AFRH bits[27:24] for PB6

    stm32f4_routes = stm32f4_artifacts[
        "st/stm32f4/generated/runtime/devices/stm32f401re/routes.hpp"
    ].content
    assert "apply_route<" in stm32f4_routes
    assert "0x3} <<" in stm32f4_routes  # MODER RMW present
    assert "0xF} <<" in stm32f4_routes  # AFR RMW present

    same70_clock_bindings = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/clock_bindings.hpp"
    ].content
    same70_peripheral_instances = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/peripheral_instances.hpp"
    ].content
    same70_dma_bindings = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/dma_bindings.hpp"
    ].content
    same70_dma_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/dma.hpp"
    ].content
    same70_adc_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/adc.hpp"
    ].content
    same70_dac_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/dac.hpp"
    ].content
    same70_can_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/can.hpp"
    ].content
    same70_eth_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/eth.hpp"
    ].content
    same70_usb_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/usb.hpp"
    ].content
    same70_qspi_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/qspi.hpp"
    ].content
    same70_sdmmc_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/sdmmc.hpp"
    ].content
    same70_rtc_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/rtc.hpp"
    ].content
    same70_watchdog_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/watchdog.hpp"
    ].content
    same70_timer_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/timer.hpp"
    ].content
    same70_pwm_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/pwm.hpp"
    ].content
    same70_registers = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/registers.hpp"
    ].content
    same70_register_fields = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/register_fields.hpp"
    ].content
    same70_routes = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/routes.hpp"
    ].content
    same70_system_clock = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/system_clock.hpp"
    ].content
    same70_clock_profiles = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/clock_profiles.hpp"
    ].content
    same70_clock_config = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/clock_config.hpp"
    ].content
    same70_capabilities = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/capabilities.hpp"
    ].content
    same70_resets = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/resets.hpp"
    ].content
    same70_enable_domains = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/enable_domains.hpp"
    ].content
    same70_system_sequences = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/system_sequences.hpp"
    ].content
    same70_low_power = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/low_power.hpp"
    ].content
    assert "ClockGateTraits<ClockGateId::gate_usart0>" in same70_clock_bindings
    assert "FieldId::field_pmc_pcer0_pid13" in same70_clock_bindings
    assert "PeripheralId::WDT" in same70_peripheral_instances
    assert "PeripheralId::RSWDT" in same70_peripheral_instances
    assert "PeripheralInstanceTraits<PeripheralId::AFEC0>" in same70_peripheral_instances
    assert "PeripheralInstanceTraits<PeripheralId::DACC>" in same70_peripheral_instances
    assert "PeripheralInstanceTraits<PeripheralId::TC0>" in same70_peripheral_instances
    assert "PeripheralInstanceTraits<PeripheralId::PWM0>" in same70_peripheral_instances
    assert "PeripheralInstanceTraits<PeripheralId::MCAN0>" in same70_peripheral_instances
    assert "PeripheralInstanceTraits<PeripheralId::MCAN1>" in same70_peripheral_instances
    assert "PeripheralInstanceTraits<PeripheralId::GMAC>" in same70_peripheral_instances
    assert "PeripheralInstanceTraits<PeripheralId::QSPI>" in same70_peripheral_instances
    assert "PeripheralInstanceTraits<PeripheralId::HSMCI>" in same70_peripheral_instances
    assert "PeripheralClassId::class_adc" in same70_peripheral_instances
    assert "PeripheralClassId::class_dac" in same70_peripheral_instances
    assert "PeripheralClassId::class_can" in same70_peripheral_instances
    assert "PeripheralClassId::class_eth" in same70_peripheral_instances
    assert "PeripheralClassId::class_qspi" in same70_peripheral_instances
    assert "PeripheralClassId::class_sdmmc" in same70_peripheral_instances
    assert "PeripheralClassId::class_timer" in same70_peripheral_instances
    assert "PeripheralClassId::class_pwm" in same70_peripheral_instances
    assert "BindingTraits<PeripheralId::AFEC0" in same70_dma_bindings
    assert "BindingTraits<PeripheralId::DACC" in same70_dma_bindings
    assert "BindingTraits<PeripheralId::PWM0" in same70_dma_bindings
    assert "BindingTraits<PeripheralId::SPI0" in same70_dma_bindings
    assert "BindingTraits<PeripheralId::QSPI" in same70_dma_bindings
    assert "BindingTraits<PeripheralId::HSMCI" in same70_dma_bindings
    assert "BindingTraits<PeripheralId::TWIHS0" in same70_dma_bindings
    assert "AdcSemanticTraits<PeripheralId::AFEC0>" in same70_adc_semantics
    assert "kAdcSemanticPeripherals" in same70_adc_semantics
    assert "DacSemanticTraits<PeripheralId::DACC>" in same70_dac_semantics
    assert "DacChannelSemanticTraits<PeripheralId::DACC, 0u>" in same70_dac_semantics
    assert "kDacSemanticPeripherals" in same70_dac_semantics
    assert "CanSemanticTraits<PeripheralId::MCAN0>" in same70_can_semantics
    assert "CanSemanticTraits<PeripheralId::MCAN1>" in same70_can_semantics
    assert "kCanSemanticPeripherals" in same70_can_semantics
    assert "EthSemanticTraits<PeripheralId::GMAC>" in same70_eth_semantics
    assert "kSupportsRmii = true;" in same70_eth_semantics
    assert "kHasDmaEngine = true;" in same70_eth_semantics
    assert "kRxDescriptorBaseRegister" in same70_eth_semantics
    assert "kTxDescriptorBaseRegister" in same70_eth_semantics
    assert "kManagementPortEnableField" in same70_eth_semantics
    assert "kEthSemanticPeripherals" in same70_eth_semantics
    assert "UsbSemanticTraits<PeripheralId::USBHS>" in same70_usb_semantics
    assert "kSupportsDeviceMode = true;" in same70_usb_semantics
    assert "kSupportsHostMode = true;" in same70_usb_semantics
    assert "kEnableField" in same70_usb_semantics
    assert "kClockUsableField" in same70_usb_semantics
    assert "kUsbSemanticPeripherals" in same70_usb_semantics
    assert "QspiSemanticTraits<PeripheralId::QSPI>" in same70_qspi_semantics
    assert "kSupportsMemoryMode = true;" in same70_qspi_semantics
    assert "kHasDma = true;" in same70_qspi_semantics
    assert "kInstructionFrameRegister" in same70_qspi_semantics
    assert "kInstructionEnableField" in same70_qspi_semantics
    assert "kScramblingEnableField" in same70_qspi_semantics
    assert "kQspiSemanticPeripherals" in same70_qspi_semantics
    assert "SdmmcSemanticTraits<PeripheralId::HSMCI>" in same70_sdmmc_semantics
    assert "kSupports4Bit = true;" in same70_sdmmc_semantics
    assert "kSupports8Bit = false;" in same70_sdmmc_semantics
    assert "kHasDma = true;" in same70_sdmmc_semantics
    assert "kCommandRegister" in same70_sdmmc_semantics
    assert "kBusWidthField" in same70_sdmmc_semantics
    assert "kSdmmcSemanticPeripherals" in same70_sdmmc_semantics
    assert "RtcSemanticTraits<PeripheralId::RTC>" in same70_rtc_semantics
    assert "kRtcSemanticPeripherals" in same70_rtc_semantics
    assert "WatchdogSemanticTraits<PeripheralId::WDT>" in same70_watchdog_semantics
    assert "WatchdogSemanticTraits<PeripheralId::RSWDT>" in same70_watchdog_semantics
    assert "kWatchdogSemanticPeripherals" in same70_watchdog_semantics
    assert "PeripheralId::AFEC0" in same70_dma_semantics
    assert "PeripheralId::DACC" in same70_dma_semantics
    assert "PeripheralId::PWM0" in same70_dma_semantics
    assert "PeripheralId::SPI0" in same70_dma_semantics
    assert "PeripheralId::QSPI" in same70_dma_semantics
    assert "PeripheralId::HSMCI" in same70_dma_semantics
    assert "PeripheralId::TWIHS0" in same70_dma_semantics
    assert "TimerSemanticTraits<PeripheralId::TC0>" in same70_timer_semantics
    assert "kHasEncoder = true;" in same70_timer_semantics
    assert "kEncoderEnableField" in same70_timer_semantics
    assert "kDirectionField" in same70_timer_semantics
    assert "TimerChannelSemanticTraits<PeripheralId::TC0, 0u>" in same70_timer_semantics
    assert "PwmSemanticTraits<PeripheralId::PWM0>" in same70_pwm_semantics
    assert "PwmChannelSemanticTraits<PeripheralId::PWM0, 0u>" in same70_pwm_semantics
    assert "RegisterId::register_wdt_mr" in same70_registers
    assert "RegisterId::register_rswdt_mr" in same70_registers
    assert "FieldId::field_wdt_mr_wddis" in same70_register_fields
    assert "FieldId::field_rswdt_mr_allones" in same70_register_fields
    assert "RegisterId::register_pmc_pcer0" in same70_routes
    assert "FieldId::field_pmc_pcer0_pid13" in same70_routes
    assert "same70_enable_external_crystal" in same70_system_clock
    assert "same70_switch_mck" in same70_system_clock
    assert "SystemClockProfileId::plla_150mhz" in same70_system_clock
    assert "FieldId::field_pmc_ckgr_mor_key" in same70_system_clock
    assert "FieldId::field_efc_eefc_fmr_fws" in same70_system_clock
    assert 'static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for ' in (
        same70_artifacts[
            "microchip/same70/generated/runtime/devices/atsame70q21b/connectors.hpp"
        ].content
    )
    assert (
        "kDefaultClockProfileId = ClockProfileId::default_safe_internal_12mhz"
        in same70_clock_profiles
    )
    assert "kMaxClockProfileId = ClockProfileId::plla_150mhz" in same70_clock_profiles
    assert "apply_clock_profile_plla_150mhz" in same70_clock_config
    assert "apply_max_clock_profile" in same70_clock_config
    assert "kCapabilities" in same70_capabilities
    assert "CapabilityNameId::dma_compatible_signal" in same70_capabilities
    assert "CapabilityNameId::runtime_supported" in same70_capabilities
    assert "kResetDescriptors" in same70_resets
    assert "kEnableDomains" in same70_enable_domains
    assert "PeripheralEnableDomainTraits<PeripheralId::USART0>" in same70_enable_domains
    assert "SystemSequenceId::default_bringup" in same70_system_sequences
    assert "PeripheralId::WDT" in same70_system_sequences
    assert "SystemClockProfileId::default_safe_internal_12mhz" in same70_system_sequences
    assert "WakeupPinTraits<PinId::PA0>" in same70_low_power
    assert "WakeupTagId::WKUP0" in same70_low_power
    assert "kWakeupSources" in same70_low_power
    assert "LowPowerModeTraits<LowPowerModeId::deep_sleep>" in same70_low_power

    nxp_clock_bindings = nxp_artifacts[
        "nxp/imxrt1060/generated/runtime/devices/mimxrt1062/clock_bindings.hpp"
    ].content
    nxp_system_clock = nxp_artifacts[
        "nxp/imxrt1060/generated/runtime/devices/mimxrt1062/system_clock.hpp"
    ].content
    nxp_clock_profiles = nxp_artifacts[
        "nxp/imxrt1060/generated/runtime/devices/mimxrt1062/clock_profiles.hpp"
    ].content
    nxp_clock_config = nxp_artifacts[
        "nxp/imxrt1060/generated/runtime/devices/mimxrt1062/clock_config.hpp"
    ].content
    nxp_capabilities = nxp_artifacts[
        "nxp/imxrt1060/generated/runtime/devices/mimxrt1062/capabilities.hpp"
    ].content
    nxp_linker_script = nxp_artifacts[
        "nxp/imxrt1060/generated/devices/mimxrt1062/device.ld"
    ].content
    nxp_resets = nxp_artifacts[
        "nxp/imxrt1060/generated/runtime/devices/mimxrt1062/resets.hpp"
    ].content
    nxp_enable_domains = nxp_artifacts[
        "nxp/imxrt1060/generated/runtime/devices/mimxrt1062/enable_domains.hpp"
    ].content
    nxp_system_sequences = nxp_artifacts[
        "nxp/imxrt1060/generated/runtime/devices/mimxrt1062/system_sequences.hpp"
    ].content
    nxp_low_power = nxp_artifacts[
        "nxp/imxrt1060/generated/runtime/devices/mimxrt1062/low_power.hpp"
    ].content
    assert "ClockGateTraits<ClockGateId::gate_lpuart1>" in nxp_clock_bindings
    assert "RegisterId::register_ccm_ccgr5" in nxp_clock_bindings
    assert "FieldId::field_ccm_ccgr5_cg12" in nxp_clock_bindings
    assert "ClockSelectorTraits<ClockSelectorId::selector_lpuart_root>" in nxp_clock_bindings
    assert "FieldId::field_ccm_cscdr1_uart_clk_sel" in nxp_clock_bindings
    assert "imxrt_switch_to_periph_clk2_osc24m" in nxp_system_clock
    assert "imxrt_program_arm_pll" in nxp_system_clock
    assert "SystemClockProfileId::default_arm_pll_600mhz" in nxp_system_clock
    assert "FieldId::field_ccm_analog_pll_arm_div_select" in nxp_system_clock
    assert "FieldId::field_dcdc_reg3_trg" in nxp_system_clock
    assert 'static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for ' in (
        nxp_artifacts["nxp/imxrt1060/generated/runtime/devices/mimxrt1062/connectors.hpp"].content
    )
    assert "kMaxClockProfileId = ClockProfileId::default_arm_pll_600mhz" in nxp_clock_profiles
    assert "apply_clock_profile_default_arm_pll_600mhz" in nxp_clock_config
    assert "apply_default_clock_profile" in nxp_clock_config
    assert "enum class LowPowerModeId" in nxp_low_power
    assert "kLowPowerModes" in nxp_low_power
    assert "PeripheralClassCapabilityTraits<PeripheralClassId::class_gpio>" in nxp_capabilities
    assert "kCapabilities" in nxp_capabilities
    assert "CapabilityNameId::runtime_supported" in nxp_capabilities
    assert "kResetDescriptors" in nxp_resets
    assert "kEnableDomains" in nxp_enable_domains
    assert "PeripheralEnableDomainTraits<PeripheralId::LPUART1>" in nxp_enable_domains
    assert "SystemSequenceId::default_bringup" in nxp_system_sequences
    assert "SystemClockProfileId::default_arm_pll_600mhz" in nxp_system_sequences
    assert nxp_linker_script == (
        Path(__file__).parent
        / "fixtures"
        / "emitted"
        / "imxrt1060"
        / "generated"
        / "devices"
        / "mimxrt1062"
        / "device.ld"
    ).read_text(encoding="utf-8")


def test_emit_matches_golden_artifacts(
    execution_context: ExecutionContext,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
) -> None:
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}
    fixture_root = Path(__file__).parent / "fixtures" / "emitted" / "stm32g0"

    manifest_payload = json.loads(artifacts["st/stm32g0/artifact-manifest.json"].content)
    validation_payload = json.loads(artifacts["st/stm32g0/reports/validation-report.json"].content)

    assert _normalize_manifest_payload(
        manifest_payload,
        fixture_source_root=fixture_source_root,
        fixture_pin_source_root=fixture_pin_source_root,
    ) == _load_json_fixture(fixture_root / "artifact-manifest.json")
    assert validation_payload == _load_json_fixture(
        fixture_root / "reports" / "validation-report.json"
    )
    assert json.loads(
        artifacts["st/stm32g0/metadata/family-index.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "family-index.json")
    assert json.loads(
        artifacts["st/stm32g0/metadata/family-connectivity.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "family-connectivity.json")
    assert json.loads(
        artifacts["st/stm32g0/metadata/ip-blocks.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "ip-blocks.json")
    assert json.loads(
        artifacts["st/stm32g0/metadata/capabilities.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "capabilities.json")
    assert json.loads(artifacts["st/stm32g0/metadata/packages.json"].content) == _load_json_fixture(
        fixture_root / "metadata" / "packages.json"
    )
    assert json.loads(
        artifacts["st/stm32g0/metadata/connectors.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "connectors.json")
    assert json.loads(
        artifacts["st/stm32g0/metadata/system-descriptors.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "system-descriptors.json")
    assert json.loads(
        artifacts["st/stm32g0/metadata/devices/stm32g071rb.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "devices" / "stm32g071rb.json")
    assert not any(path.startswith("st/stm32g0/generated/ip/") for path in artifacts), (
        "Legacy IP headers should not be emitted"
    )
    assert not any(path.startswith("st/stm32g0/generated/peripherals/") for path in artifacts), (
        "Legacy peripheral headers should not be emitted"
    )
    assert not any(
        path.startswith("st/stm32g0/generated/devices/stm32g071rb/") and path.endswith(".hpp")
        for path in artifacts
    ), "Legacy device-scoped generated headers should not be emitted"
    assert "st/stm32g0/generated/connector_tables.hpp" not in artifacts
    assert "st/stm32g0/generated/interrupt_map.hpp" not in artifacts
    assert "st/stm32g0/generated/memory_map.hpp" not in artifacts
    assert "st/stm32g0/generated/package_map.hpp" not in artifacts
    assert "st/stm32g0/generated/clock_tree_lite.hpp" not in artifacts
    assert "st/stm32g0/generated/dma_map.hpp" not in artifacts
    assert "st/stm32g0/generated/rcc_map.hpp" not in artifacts
    assert artifacts["st/stm32g0/generated/runtime/types.hpp"].content == (
        fixture_root / "generated" / "runtime" / "types.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/peripheral_instances.hpp"
    ].content == (
        fixture_root
        / "generated"
        / "runtime"
        / "devices"
        / "stm32g071rb"
        / "peripheral_instances.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/runtime/devices/stm32g071rb/pins.hpp"].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "pins.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/runtime/devices/stm32g071rb/registers.hpp"].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "registers.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/register_fields.hpp"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "register_fields.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/clock_bindings.hpp"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "clock_bindings.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/dma_bindings.hpp"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "dma_bindings.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/runtime/devices/stm32g071rb/routes.hpp"].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "routes.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/runtime/devices/stm32g071rb/connectors.hpp"].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "connectors.hpp"
    ).read_text(encoding="utf-8")
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
            f"st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/{name}"
        ].content == (
            fixture_root
            / "generated"
            / "runtime"
            / "devices"
            / "stm32g071rb"
            / "driver_semantics"
            / name
        ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/runtime/devices/stm32g071rb/startup.hpp"].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "startup.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/devices/stm32g071rb/device.ld"].content == (
        fixture_root / "generated" / "devices" / "stm32g071rb" / "device.ld"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/devices/stm32g071rb/startup.cpp"].content == (
        fixture_root / "generated" / "devices" / "stm32g071rb" / "startup.cpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/devices/stm32g071rb/startup_vectors.cpp"].content == (
        fixture_root / "generated" / "devices" / "stm32g071rb" / "startup_vectors.cpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/runtime/devices/stm32g071rb/systick.hpp"].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "systick.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/runtime/devices/stm32g071rb/interrupts.hpp"].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "interrupts.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/interrupt_stubs.hpp"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "interrupt_stubs.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/runtime/devices/stm32g071rb/resets.hpp"].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "resets.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/enable_domains.hpp"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "enable_domains.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/clock_graph.hpp"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "clock_graph.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/capabilities.hpp"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "capabilities.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/capabilities.json"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "capabilities.json"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/system_sequences.hpp"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "system_sequences.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/system_clock.hpp"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "system_clock.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/clock_profiles.hpp"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "clock_profiles.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/clock_config.hpp"
    ].content == (
        fixture_root / "generated" / "runtime" / "devices" / "stm32g071rb" / "clock_config.hpp"
    ).read_text(encoding="utf-8")


def test_emit_can_semantics_cover_wave1_vendors(
    execution_context: ExecutionContext,
) -> None:
    st_result = run(PipelineScope(device="stm32g0b1re"), execution_context)
    st_artifacts = {artifact.path: artifact for artifact in st_result.payload.artifacts}
    st_can_semantics = st_artifacts[
        "st/stm32g0/generated/runtime/devices/stm32g0b1re/driver_semantics/can.hpp"
    ].content

    assert "CanSemanticTraits<PeripheralId::FDCAN1>" in st_can_semantics
    assert "kCanSemanticPeripherals" in st_can_semantics


def test_emit_timer_advanced_semantics_cover_wave1_vendors(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    st_base_device = run_normalize(
        PipelineScope(device="stm32g071rb"), execution_context
    ).payload.devices[0]
    gpio = next(
        peripheral for peripheral in st_base_device.peripherals if peripheral.name == "GPIOA"
    )
    st_augmented = replace(
        st_base_device,
        peripherals=st_base_device.peripherals
        + (
            replace(
                gpio,
                name="TIM1",
                ip_name="timer",
                instance=1,
                base_address=0x40012C00,
                backend_schema_id="alloy.timer.st-gptimer2-v1-0",
                provenance=_synthetic_timer_provenance(),
            ),
        ),
        registers=st_base_device.registers
        + (
            _synthetic_timer_register(peripheral="TIM1", name="CR1", offset_bytes=0x00),
            _synthetic_timer_register(peripheral="TIM1", name="SMCR", offset_bytes=0x08),
            _synthetic_timer_register(peripheral="TIM1", name="DIER", offset_bytes=0x0C),
            _synthetic_timer_register(peripheral="TIM1", name="SR", offset_bytes=0x10),
            _synthetic_timer_register(peripheral="TIM1", name="EGR", offset_bytes=0x14),
            _synthetic_timer_register(peripheral="TIM1", name="CCMR1_INPUT", offset_bytes=0x18),
            _synthetic_timer_register(peripheral="TIM1", name="CCMR2_INPUT", offset_bytes=0x1C),
            _synthetic_timer_register(peripheral="TIM1", name="CCER", offset_bytes=0x20),
            _synthetic_timer_register(peripheral="TIM1", name="CNT", offset_bytes=0x24),
            _synthetic_timer_register(peripheral="TIM1", name="PSC", offset_bytes=0x28),
            _synthetic_timer_register(peripheral="TIM1", name="ARR", offset_bytes=0x2C),
            _synthetic_timer_register(peripheral="TIM1", name="CCR1", offset_bytes=0x34),
            _synthetic_timer_register(peripheral="TIM1", name="CCR2", offset_bytes=0x38),
            _synthetic_timer_register(peripheral="TIM1", name="CCR3", offset_bytes=0x3C),
            _synthetic_timer_register(peripheral="TIM1", name="CCR4", offset_bytes=0x40),
        ),
    )
    st_timer_semantics = emit_runtime_driver_timer_semantics_header(
        family_dir="st/stm32g0",
        device=st_augmented,
    ).content

    assert "TimerSemanticTraits<PeripheralId::TIM1>" in st_timer_semantics
    assert "kHasEncoder = true;" in st_timer_semantics
    assert "kEncoderModeField" in st_timer_semantics
    assert "kDirectionField" in st_timer_semantics
    assert "TimerChannelSemanticTraits<PeripheralId::TIM1, 0u>" in st_timer_semantics
    assert "TimerChannelSemanticTraits<PeripheralId::TIM1, 1u>" in st_timer_semantics
    assert "kSupportsEncoderInput = true;" in st_timer_semantics

    same70_result = run(PipelineScope(device="atsame70q21b"), microchip_execution_context)
    same70_artifacts = {artifact.path: artifact for artifact in same70_result.payload.artifacts}
    same70_timer_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/timer.hpp"
    ].content

    assert "TimerSemanticTraits<PeripheralId::TC0>" in same70_timer_semantics
    assert "kHasEncoder = true;" in same70_timer_semantics
    assert "kEncoderEnableField" in same70_timer_semantics
    assert "kEncoderPositionEnableField" in same70_timer_semantics
    assert "kEncoderSpeedEnableField" in same70_timer_semantics
    assert "kEncoderPhaseEdgeField" in same70_timer_semantics
    assert "kDirectionField" in same70_timer_semantics

    nxp_base_device = run_normalize(
        PipelineScope(device="mimxrt1062"), nxp_execution_context
    ).payload.devices[0]
    nxp_gpio = next(
        peripheral for peripheral in nxp_base_device.peripherals if peripheral.name == "GPIO1"
    )
    nxp_augmented = replace(
        nxp_base_device,
        peripherals=nxp_base_device.peripherals
        + (
            replace(
                nxp_gpio,
                name="GPT1",
                ip_name="GPT",
                instance=1,
                base_address=0x401EC000,
                backend_schema_id="alloy.gpt.nxp-gpt",
                provenance=_synthetic_timer_provenance(),
            ),
            replace(
                nxp_gpio,
                name="PIT",
                ip_name="PIT",
                instance=0,
                base_address=0x40084000,
                backend_schema_id="alloy.pit.nxp-pit",
                provenance=_synthetic_timer_provenance(),
            ),
        ),
    )
    nxp_timer_semantics = emit_runtime_driver_timer_semantics_header(
        family_dir="nxp/imxrt1060",
        device=nxp_augmented,
    ).content

    assert "TimerSemanticTraits<PeripheralId::GPT1>" in nxp_timer_semantics
    assert "TimerSemanticTraits<PeripheralId::PIT>" in nxp_timer_semantics
    assert "kHasEncoder = false;" in nxp_timer_semantics


def test_emit_usb_semantics_cover_wave2_vendors(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
) -> None:
    st_base_device = run_normalize(
        PipelineScope(device="stm32f405rg"), execution_context
    ).payload.devices[0]
    st_augmented = replace(
        st_base_device,
        registers=st_base_device.registers
        + (
            _synthetic_usb_register(peripheral="OTG_FS", name="GUSBCFG", offset_bytes=0x0C),
            _synthetic_usb_register(peripheral="OTG_FS", name="GINTSTS", offset_bytes=0x14),
            _synthetic_usb_register(peripheral="OTG_FS", name="GINTMSK", offset_bytes=0x18),
            _synthetic_usb_register(peripheral="OTG_FS", name="GCCFG", offset_bytes=0x38),
            _synthetic_usb_register(peripheral="OTG_FS", name="HCFG", offset_bytes=0x400),
            _synthetic_usb_register(peripheral="OTG_FS", name="HPRT", offset_bytes=0x440),
            _synthetic_usb_register(peripheral="OTG_FS", name="DCFG", offset_bytes=0x800),
            _synthetic_usb_register(peripheral="OTG_FS", name="DCTL", offset_bytes=0x804),
            _synthetic_usb_register(peripheral="OTG_FS", name="DSTS", offset_bytes=0x808),
        ),
        register_fields=st_base_device.register_fields
        + (
            _synthetic_usb_field(
                peripheral="OTG_FS",
                register_name="GUSBCFG",
                name="FDMOD",
                bit_offset=30,
                bit_width=1,
            ),
            _synthetic_usb_field(
                peripheral="OTG_FS",
                register_name="GUSBCFG",
                name="FHMOD",
                bit_offset=29,
                bit_width=1,
            ),
            _synthetic_usb_field(
                peripheral="OTG_FS",
                register_name="GINTSTS",
                name="CMOD",
                bit_offset=0,
                bit_width=1,
            ),
            _synthetic_usb_field(
                peripheral="OTG_FS",
                register_name="GCCFG",
                name="PWRDWN",
                bit_offset=16,
                bit_width=1,
            ),
            _synthetic_usb_field(
                peripheral="OTG_FS",
                register_name="DCTL",
                name="RWUSIG",
                bit_offset=0,
                bit_width=1,
            ),
            _synthetic_usb_field(
                peripheral="OTG_FS",
                register_name="DCTL",
                name="SDIS",
                bit_offset=1,
                bit_width=1,
            ),
            _synthetic_usb_field(
                peripheral="OTG_FS",
                register_name="DCFG",
                name="DAD",
                bit_offset=4,
                bit_width=7,
            ),
        ),
    )
    st_usb_semantics = emit_runtime_driver_usb_semantics_header(
        family_dir="st/stm32f4",
        device=st_augmented,
    ).content

    assert "UsbSemanticTraits<PeripheralId::OTG_FS>" in st_usb_semantics
    assert "kSupportsDeviceMode = true;" in st_usb_semantics
    assert "kSupportsHostMode = true;" in st_usb_semantics
    assert "kForceDeviceModeField" in st_usb_semantics
    assert "kForceHostModeField" in st_usb_semantics
    assert "kSoftDisconnectField" in st_usb_semantics
    assert "kAddressField" in st_usb_semantics
    assert "kUsbSemanticPeripherals" in st_usb_semantics

    same70_result = run(PipelineScope(device="atsame70q21b"), microchip_execution_context)
    same70_artifacts = {artifact.path: artifact for artifact in same70_result.payload.artifacts}
    same70_usb_semantics = same70_artifacts[
        "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/usb.hpp"
    ].content

    assert "UsbSemanticTraits<PeripheralId::USBHS>" in same70_usb_semantics
    assert "kHasClockFreeze = true;" in same70_usb_semantics
    assert "kAddressEnableField" in same70_usb_semantics
    assert "kAddressField" in same70_usb_semantics
    assert "kClockUsableField" in same70_usb_semantics


def test_emit_uart_semantics_accepts_live_st_schema_ids(
    execution_context: ExecutionContext,
) -> None:
    cases = (
        (
            "stm32g071rb",
            "st/stm32g0",
            {
                "usart": ("sci3_v2_1_Cube", "alloy.uart.st-sci3-v2-1-cube"),
                "lpuart": ("sci3_v1_2_Cube", "alloy.uart.st-sci3-v1-2-cube"),
            },
        ),
        (
            "stm32f401re",
            "st/stm32f4",
            {
                "usart": ("sci2_v1_2_Cube", "alloy.uart.st-sci2-v1-2-cube"),
            },
        ),
    )

    for device_name, family_dir, schema_overrides in cases:
        normalized = run_normalize(PipelineScope(device=device_name), execution_context)
        device = normalized.payload.devices[0]
        mutated_peripherals = []
        for peripheral in device.peripherals:
            override = schema_overrides.get(peripheral.ip_name.lower())
            if override is None:
                mutated_peripherals.append(peripheral)
                continue
            ip_version, schema_id = override
            mutated_peripherals.append(
                replace(peripheral, ip_version=ip_version, backend_schema_id=schema_id)
            )
        artifact = emit_runtime_driver_uart_semantics_header(
            family_dir=family_dir,
            device=replace(device, peripherals=tuple(mutated_peripherals)),
        )

        assert "UartSemanticTraits<PeripheralId::" in artifact.content
        assert "static constexpr bool kPresent = true;" in artifact.content


def test_emit_can_semantics_accepts_live_st_schema_ids(
    execution_context: ExecutionContext,
) -> None:
    normalized = run_normalize(PipelineScope(device="stm32g0b1re"), execution_context)
    device = normalized.payload.devices[0]
    mutated_peripherals = []
    for peripheral in device.peripherals:
        if peripheral.ip_name.lower() != "fdcan":
            mutated_peripherals.append(peripheral)
            continue
        mutated_peripherals.append(
            replace(
                peripheral,
                ip_version="fdcan1_v1_0_Cube",
                backend_schema_id="alloy.can.st-fdcan1-v1-0-cube",
            )
        )
    artifact = emit_runtime_driver_can_semantics_header(
        family_dir="st/stm32g0",
        device=replace(device, peripherals=tuple(mutated_peripherals)),
    )

    assert "CanSemanticTraits<PeripheralId::FDCAN1>" in artifact.content
    assert "static constexpr bool kPresent = true;" in artifact.content


def test_emit_can_semantics_supports_st_bxcan_devices(
    execution_context: ExecutionContext,
) -> None:
    normalized = run_normalize(PipelineScope(device="stm32f401re"), execution_context)
    base_device = normalized.payload.devices[0]
    provenance = _synthetic_bxcan_provenance()
    augmented = replace(
        base_device,
        peripherals=base_device.peripherals
        + (
            PeripheralInstance(
                name="CAN1",
                ip_name="can",
                ip_version="bxcan1_v1_1_Cube",
                instance=1,
                base_address=0x40006400,
                rcc_enable_signal=None,
                rcc_reset_signal=None,
                provenance=provenance,
                backend_schema_id="alloy.can.st-bxcan1-v1-1-cube",
            ),
            PeripheralInstance(
                name="CAN2",
                ip_name="can",
                ip_version="bxcan1_v1_1_Cube",
                instance=2,
                base_address=0x40006800,
                rcc_enable_signal=None,
                rcc_reset_signal=None,
                provenance=provenance,
                backend_schema_id="alloy.can.st-bxcan1-v1-1-cube",
            ),
        ),
        registers=base_device.registers
        + tuple(
            _synthetic_bxcan_register(peripheral=peripheral, name=name, offset_bytes=offset)
            for peripheral in ("CAN1", "CAN2")
            for name, offset in (
                ("MCR", 0x0),
                ("MSR", 0x4),
                ("TSR", 0x8),
                ("RF0R", 0xC),
                ("IER", 0x14),
                ("ESR", 0x18),
                ("BTR", 0x1C),
                ("TI0R", 0x180),
                ("TI1R", 0x190),
                ("TI2R", 0x1A0),
                ("FMR", 0x200),
                ("FM1R", 0x204),
                ("FS1R", 0x20C),
                ("FFA1R", 0x214),
                ("FA1R", 0x21C),
            )
        ),
        register_fields=base_device.register_fields
        + tuple(
            _synthetic_bxcan_field(
                peripheral=peripheral,
                register_name=register_name,
                name=name,
                bit_offset=bit_offset,
                bit_width=bit_width,
            )
            for peripheral in ("CAN1", "CAN2")
            for register_name, name, bit_offset, bit_width in (
                ("MCR", "INRQ", 0, 1),
                ("BTR", "BRP", 0, 10),
                ("BTR", "TS1", 16, 4),
                ("BTR", "TS2", 20, 3),
                ("BTR", "SJW", 24, 2),
                ("BTR", "SILM", 31, 1),
                ("RF0R", "FMP0", 0, 2),
                ("RF0R", "FOVR0", 4, 1),
                ("RF0R", "RFOM0", 5, 1),
                ("IER", "TMEIE", 0, 1),
                ("IER", "FMPIE0", 1, 1),
                ("TSR", "TXOK0", 1, 1),
                ("TSR", "CODE", 24, 2),
            )
        ),
    )
    artifact = emit_runtime_driver_can_semantics_header(
        family_dir="st/stm32f4",
        device=augmented,
    )

    assert "CanSemanticTraits<PeripheralId::CAN1>" in artifact.content
    assert "CanSemanticTraits<PeripheralId::CAN2>" in artifact.content
    assert "static constexpr bool kHasFlexibleDataRate = false;" in artifact.content
    assert "static constexpr bool kPresent = true;" in artifact.content


def test_emit_can_semantics_supports_st_can_alias_schema(
    execution_context: ExecutionContext,
) -> None:
    normalized = run_normalize(PipelineScope(device="stm32f401re"), execution_context)
    base_device = normalized.payload.devices[0]
    provenance = _synthetic_bxcan_provenance()
    augmented = replace(
        base_device,
        peripherals=base_device.peripherals
        + (
            PeripheralInstance(
                name="CAN1",
                ip_name="can",
                ip_version=None,
                instance=1,
                base_address=0x40006400,
                rcc_enable_signal=None,
                rcc_reset_signal=None,
                provenance=provenance,
                backend_schema_id="alloy.can.st-can",
            ),
        ),
        registers=base_device.registers
        + tuple(
            _synthetic_bxcan_register(peripheral="CAN1", name=name, offset_bytes=offset)
            for name, offset in (
                ("MCR", 0x0),
                ("MSR", 0x4),
                ("TSR", 0x8),
                ("RF0R", 0xC),
                ("IER", 0x14),
                ("ESR", 0x18),
                ("BTR", 0x1C),
                ("TI0R", 0x180),
                ("FMR", 0x200),
                ("FM1R", 0x204),
                ("FS1R", 0x20C),
                ("FFA1R", 0x214),
                ("FA1R", 0x21C),
            )
        ),
        register_fields=base_device.register_fields
        + tuple(
            _synthetic_bxcan_field(
                peripheral="CAN1",
                register_name=register_name,
                name=name,
                bit_offset=bit_offset,
                bit_width=bit_width,
            )
            for register_name, name, bit_offset, bit_width in (
                ("MCR", "INRQ", 0, 1),
                ("BTR", "BRP", 0, 10),
                ("BTR", "TS1", 16, 4),
                ("BTR", "TS2", 20, 3),
                ("BTR", "SJW", 24, 2),
                ("BTR", "SILM", 31, 1),
                ("RF0R", "FMP0", 0, 2),
                ("RF0R", "FOVR0", 4, 1),
                ("RF0R", "RFOM0", 5, 1),
                ("IER", "TMEIE", 0, 1),
                ("IER", "FMPIE0", 1, 1),
                ("TSR", "TXOK0", 1, 1),
                ("TSR", "CODE", 24, 2),
            )
        ),
    )
    artifact = emit_runtime_driver_can_semantics_header(
        family_dir="st/stm32f4",
        device=augmented,
    )

    assert "CanSemanticTraits<PeripheralId::CAN1>" in artifact.content
    assert "static constexpr bool kHasFlexibleDataRate = false;" in artifact.content


def test_emit_connector_metadata_supports_microchip_family(
    microchip_execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="atsame70q21b"), microchip_execution_context)
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}

    connectors_payload = json.loads(artifacts["microchip/same70/metadata/connectors.json"].content)
    ip_blocks_payload = json.loads(artifacts["microchip/same70/metadata/ip-blocks.json"].content)
    packages_payload = json.loads(artifacts["microchip/same70/metadata/packages.json"].content)
    system_payload = json.loads(
        artifacts["microchip/same70/metadata/system-descriptors.json"].content
    )

    assert connectors_payload["vendor"] == "microchip"
    assert connectors_payload["family"] == "same70"
    assert connectors_payload["signal_endpoints"]
    assert connectors_payload["devices"][0]["device"] == "atsame70q21b"
    assert packages_payload["packages"][0]["pads"]
    assert packages_payload["packages"][0]["pinouts"]
    assert packages_payload["packages"][0]["pinouts"][0]["pinout"]
    assert any(
        candidate["route_kind"] == "peripheral-mux"
        for candidate in connectors_payload["devices"][0]["connection_candidates"]
    )
    assert ip_blocks_payload["ip_blocks"]
    assert system_payload["devices"][0]["vector_slots"]
    assert system_payload["devices"][0]["startup_descriptors"]
    assert system_payload["devices"][0]["clock_gates"]
    assert system_payload["devices"][0]["dma_routes"]
    assert any(memory.get("startup_roles") for memory in system_payload["devices"][0]["memories"])
    assert (
        artifacts["microchip/same70/generated/runtime/devices/atsame70q21b/startup.hpp"].content
        is not None
    )
    assert (
        artifacts["microchip/same70/generated/devices/atsame70q21b/startup.cpp"].content is not None
    )
    assert (
        artifacts["microchip/same70/generated/devices/atsame70q21b/startup_vectors.cpp"].content
        is not None
    )
    assert (
        artifacts["microchip/same70/generated/runtime/devices/atsame70q21b/systick.hpp"].content
        is not None
    )
    assert (
        artifacts[
            "microchip/same70/generated/runtime/devices/atsame70q21b/system_clock.hpp"
        ].content
        is not None
    )
    assert (
        artifacts[
            "microchip/same70/generated/runtime/devices/atsame70q21b/clock_profiles.hpp"
        ].content
        is not None
    )
    assert (
        artifacts[
            "microchip/same70/generated/runtime/devices/atsame70q21b/clock_config.hpp"
        ].content
        is not None
    )
    assert not any(path.startswith("microchip/same70/generated/ip/") for path in artifacts)


def test_emit_runtime_systick_header_for_foundational_cortex_m_devices(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    cases = (
        ("stm32g071rb", execution_context, "st/stm32g0"),
        ("stm32f401re", execution_context, "st/stm32f4"),
        ("atsame70q21b", microchip_execution_context, "microchip/same70"),
        ("mimxrt1062", nxp_execution_context, "nxp/imxrt1060"),
    )

    for device_name, context, family_dir in cases:
        result = run(PipelineScope(device=device_name), context)
        artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}
        systick_artifact = artifacts[
            f"{family_dir}/generated/runtime/devices/{device_name}/systick.hpp"
        ]

        assert systick_artifact.content is not None
        assert "enum class SysTickClockSourceId" in systick_artifact.content
        assert "struct SysTickTraits" in systick_artifact.content
        assert "kCtrlRegister" in systick_artifact.content
        assert "configure_for_tick_hz" in systick_artifact.content
        assert "calibration_has_reference_clock" in systick_artifact.content


def test_emit_packages_metadata_can_reconstruct_physical_pinout(
    execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}

    packages_payload = json.loads(artifacts["st/stm32g0/metadata/packages.json"].content)
    package_entry = next(
        package for package in packages_payload["packages"] if package["name"] == "lqfp64"
    )
    device_pinout = next(
        pinout for pinout in package_entry["pinouts"] if pinout["device"] == "stm32g071rb"
    )

    topology_by_pad = {pad["pad_id"]: pad for pad in package_entry["pads"]}
    reconstructed_pinout = [
        {
            **topology_by_pad[pad["pad_id"]],
            "bonded_pin": pad["bonded_pin"],
            "bonding_state": pad["bonding_state"],
            "constraint_ids": pad["constraint_ids"],
        }
        for pad in device_pinout["pinout"]
    ]

    # Pad "21" (PA5) was admitted by add-board-support-package-emitter so the
    # Nucleo-G071RB seed board's LED_GREEN pin survives validation.
    assert [pad["pad_id"] for pad in reconstructed_pinout] == [
        "17", "18", "19", "20", "21", "29", "30",
    ]
    assert reconstructed_pinout[0]["position_label"] == "17"
    assert reconstructed_pinout[0]["bonded_pin"] == "PA0"
    assert reconstructed_pinout[0]["pad_kind"] == "io"
    assert any(pin_entry["pin"] == "PB6" for pin_entry in device_pinout["pin_index"])


def test_emit_stage_is_byte_stable(execution_context: ExecutionContext) -> None:
    scope = PipelineScope()
    result_a = json.dumps(run(scope, execution_context).to_dict(), sort_keys=True)
    result_b = json.dumps(run(scope, execution_context).to_dict(), sort_keys=True)

    assert result_a == result_b


# ---------------------------------------------------------------------------
# add-usb-semantic-traits: USB hardware-feature trait coverage
# ---------------------------------------------------------------------------


def test_stm32g0_usb_traits_emit_hardware_feature_constexprs(
    execution_context: ExecutionContext,
) -> None:
    """Phase 2.4 of add-usb-semantic-traits: STM32G0 USB FS trait
    specialization carries kHardwarePresent=true plus the silicon facts
    from ``Device.usb_controllers``."""
    result = run(PipelineScope(device="stm32g0b1re"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    usb_path = "st/stm32g0/generated/runtime/devices/stm32g0b1re/driver_semantics/usb.hpp"
    assert usb_path in arts
    content = arts[usb_path].content
    # Locate the per-peripheral specialization (USB) and assert hardware fields
    assert "struct UsbSemanticTraits<PeripheralId::USB>" in content
    assert "static constexpr bool kHardwarePresent = true;" in content
    assert "static constexpr std::uintptr_t kBaseAddress = 0x40005C00u;" in content
    assert "static constexpr std::uint16_t kEndpointCount = 8u;" in content
    assert "static constexpr bool kCrystalless = true;" in content
    assert "static constexpr std::uintptr_t kDpramBaseAddress = 0x40006000u;" in content
    assert "static constexpr std::uint32_t kDpramSizeBytes = 1024u;" in content


def test_stm32f4_usb_traits_emit_otg_fs_facts(
    execution_context: ExecutionContext,
) -> None:
    """Phase 3.4: STM32F4 USB OTG FS trait specialization carries the
    OTG FS silicon facts."""
    result = run(PipelineScope(device="stm32f401re"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    usb_path = "st/stm32f4/generated/runtime/devices/stm32f401re/driver_semantics/usb.hpp"
    assert usb_path in arts
    content = arts[usb_path].content
    assert "struct UsbSemanticTraits<PeripheralId::OTG_FS>" in content
    assert "static constexpr std::uintptr_t kBaseAddress = 0x50000000u;" in content
    assert "static constexpr std::uint16_t kEndpointCount = 4u;" in content
    assert "static constexpr bool kSupportsDma = true;" in content


def test_same70_usbhs_traits_emit_high_speed_dma_facts(
    microchip_execution_context: ExecutionContext,
) -> None:
    """Phase 5.4 of add-usb-semantic-traits: SAME70 USBHS trait
    specialization carries the high-speed + DMA-capable silicon facts."""
    result = run(
        PipelineScope(vendor="microchip", family="same70", device="atsame70q21b"),
        microchip_execution_context,
    )
    arts = {a.path: a for a in result.payload.artifacts}
    usb_path = "microchip/same70/generated/runtime/devices/atsame70q21b/driver_semantics/usb.hpp"
    assert usb_path in arts
    content = arts[usb_path].content
    assert "struct UsbSemanticTraits<PeripheralId::USBHS>" in content
    assert "static constexpr bool kHardwarePresent = true;" in content
    assert "static constexpr std::uintptr_t kBaseAddress = 0x40038000u;" in content
    assert "static constexpr std::uint16_t kEndpointCount = 7u;" in content
    assert "static constexpr bool kSupportsHighSpeed = true;" in content
    assert "static constexpr bool kSupportsDma = true;" in content
    assert "static constexpr std::uint8_t kDmaChannelCount = 7u;" in content


# ---------------------------------------------------------------------------
# fill-espressif-semantic-gaps: hardware-feature traits surface on Espressif
# ---------------------------------------------------------------------------


def test_esp32_uart_traits_emit_hardware_feature_constexprs(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 4 of fill-espressif-semantic-gaps: ESP32 UART trait
    specializations carry kHardwarePresent=true plus base address, FIFO
    depth and DMA support flag from the family overlay."""
    result = run(
        PipelineScope(vendor="espressif", family="esp32", device="esp32"),
        espressif_execution_context,
    )
    arts = {a.path: a for a in result.payload.artifacts}
    usb_path = "espressif/esp32/generated/runtime/devices/esp32/driver_semantics/uart.hpp"
    assert usb_path in arts
    content = arts[usb_path].content
    assert "struct UartSemanticTraits<PeripheralId::UART0>" in content
    assert "static constexpr bool kHardwarePresent = true;" in content
    # Base address is sourced from the SVD-driven peripheral IR (0x3FF40000
    # on ESP32 classic) so any patch overlay typo cannot drift from silicon.
    assert "static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;" in content
    assert "static constexpr std::uint16_t kFifoDepth = 128u;" in content
    assert "static constexpr bool kSupportsDma = true;" in content


def test_esp32c3_uart_traits_emit_256_byte_fifo(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 4 of fill-espressif-semantic-gaps: ESP32-C3 UART FIFO depth
    is 256 bytes (vs 128 on classic/S3)."""
    result = run(
        PipelineScope(vendor="espressif", family="esp32c3", device="esp32c3"),
        espressif_execution_context,
    )
    arts = {a.path: a for a in result.payload.artifacts}
    p = "espressif/esp32c3/generated/runtime/devices/esp32c3/driver_semantics/uart.hpp"
    content = arts[p].content
    assert "struct UartSemanticTraits<PeripheralId::UART0>" in content
    assert "static constexpr std::uint16_t kFifoDepth = 256u;" in content


def test_esp32_spi_traits_emit_iomux_fast_path_pins(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 4 of fill-espressif-semantic-gaps: ESP32 SPI2 advertises
    its IO_MUX fast-path pins (MOSI=13, MISO=12, CLK=14, CS=15)."""
    result = run(
        PipelineScope(vendor="espressif", family="esp32", device="esp32"),
        espressif_execution_context,
    )
    arts = {a.path: a for a in result.payload.artifacts}
    p = "espressif/esp32/generated/runtime/devices/esp32/driver_semantics/spi.hpp"
    content = arts[p].content
    assert "struct SpiSemanticTraits<PeripheralId::SPI2>" in content
    assert "static constexpr bool kHardwarePresent = true;" in content
    assert "static constexpr bool kHasIomuxFastPath = true;" in content
    assert "static constexpr std::int16_t kIomuxMosiPin = 13;" in content
    assert "static constexpr std::int16_t kIomuxMisoPin = 12;" in content
    assert "static constexpr std::int16_t kIomuxClkPin = 14;" in content
    assert "static constexpr std::int16_t kIomuxCsPin = 15;" in content
    assert "static constexpr std::uint32_t kMaxClockHz = 80000000u;" in content


def test_esp32c3_spi_has_no_iomux_fast_path(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 4 of fill-espressif-semantic-gaps: ESP32-C3 SPI2 has no
    dedicated IO_MUX fast-path pins."""
    result = run(
        PipelineScope(vendor="espressif", family="esp32c3", device="esp32c3"),
        espressif_execution_context,
    )
    arts = {a.path: a for a in result.payload.artifacts}
    p = "espressif/esp32c3/generated/runtime/devices/esp32c3/driver_semantics/spi.hpp"
    content = arts[p].content
    assert "struct SpiSemanticTraits<PeripheralId::SPI2>" in content
    assert "static constexpr bool kHasIomuxFastPath = false;" in content


def test_stm32g071rb_uart_traits_emit_tier234_facts(
    execution_context: ExecutionContext,
) -> None:
    """Phase 4 of add-uart-spi-tier-2-3-4-data: STM32G0 USART1 trait
    specialization carries the populated Tier 2/3/4 silicon facts
    (LIN/IrDA/smartcard support, 8x+16x oversampling, 7/8/9-bit data,
    4 MHz max baud, FIFO trigger levels)."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    p = "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/uart.hpp"
    content = arts[p].content
    assert "struct UartSemanticTraits<PeripheralId::USART1>" in content
    assert "static constexpr bool kSupportsLin = true;" in content
    assert "static constexpr bool kSupportsIrda = true;" in content
    assert "static constexpr bool kSupportsSmartcard = true;" in content
    assert "static constexpr std::uint32_t kMaxBaudHz = 4000000u;" in content
    assert "kSupportedDataBits = {{7u, 8u, 9u}};" in content
    assert "kBaudOversamplingOptions = {{16u, 8u}};" in content


def test_stm32g071rb_spi_traits_emit_tier234_facts(
    execution_context: ExecutionContext,
) -> None:
    """Phase 4 of add-uart-spi-tier-2-3-4-data: STM32G0 SPI1 trait
    specialization carries 4..16 bit frame sizes, CRC + TI + Motorola
    + LSB-first + NSS-HW-management + 3-wire bidirectional flags,
    and 8 baud prescaler divisors (/2 .. /256)."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    p = "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/spi.hpp"
    content = arts[p].content
    assert "struct SpiSemanticTraits<PeripheralId::SPI1>" in content
    assert "static constexpr bool kSupportsCrc = true;" in content
    assert "static constexpr bool kSupportsTiFrame = true;" in content
    assert "static constexpr bool kSupportsMotorolaFrame = true;" in content
    assert "static constexpr bool kSupportsLsbFirst = true;" in content
    assert "static constexpr bool kSupportsNssHwManagement = true;" in content
    assert "static constexpr bool kSupportsBidirectional3Wire = true;" in content
    assert "kBaudPrescalerDivisors = {{2u, 4u, 8u, 16u, 32u, 64u, 128u, 256u}};" in content
    # Frame sizes 4..16 inclusive (13 entries).
    assert (
        "kSupportedFrameSizes = {{4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u, 16u}};"
        in content
    )


def test_stm32g071rb_uart_traits_emit_irq_numbers(
    execution_context: ExecutionContext,
) -> None:
    """add-irq-vector-traits: STM32G0 USART1 trait specialization carries
    a populated ``kIrqNumbers`` array sourced from the canonical-device-IR
    interrupt_bindings table (USART1_IRQn = 27 on STM32G071)."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    p = "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/uart.hpp"
    content = arts[p].content
    # Unspecialized template ships an empty array.
    assert "static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};" in content
    # USART1 specialization carries the NVIC line number.
    assert "struct UartSemanticTraits<PeripheralId::USART1>" in content
    assert "static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{27u}};" in content


def test_stm32g071rb_uart_traits_emit_kernel_clock(
    execution_context: ExecutionContext,
) -> None:
    """add-kernel-clock-traits: STM32G0 USART1 carries the four
    kernel-clock constexprs — selector field, source-option array
    (PCLK / SYSCLK / HSI16 / LSE), 64 MHz max, and the RCC enable
    gate field reference."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    p = "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/uart.hpp"
    content = arts[p].content
    # Unspecialized defaults.
    assert (
        "static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};"
    ) in content
    # USART1 specialization carries 4 sources + 64 MHz max + valid gate.
    assert "struct UartSemanticTraits<PeripheralId::USART1>" in content
    assert "static constexpr std::uint32_t kKernelMaxClockHz = 64000000u;" in content
    assert (
        "static constexpr std::array<KernelClockSourceOption, 4> kKernelClockSourceOptions = {{"
    ) in content
    assert "KernelClockSource::sysclk" in content
    assert "KernelClockSource::hsi16" in content
    assert "KernelClockSource::lse" in content
    assert "FieldId::field_rcc_apbenr2_usart1en" in content


def test_stm32g071rb_i2c_traits_emit_specialization_and_tier234(
    execution_context: ExecutionContext,
) -> None:
    """add-i2c-tier-2-3-4-data: STM32G0 I2C1 surfaces a populated
    specialization (closing the broken-emission bug) carrying the
    three Tier 2/3/4 speeds (100k/400k/1M), TIMINGR presets, and
    the SMBus / 7-bit / 10-bit addressing flags."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    p = "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/i2c.hpp"
    content = arts[p].content
    # Phase 1: I2C1 + I2C2 specializations exist (used to be empty).
    assert "struct I2cSemanticTraits<PeripheralId::I2C1>" in content
    assert "struct I2cSemanticTraits<PeripheralId::I2C2>" in content
    assert "PeripheralId::I2C1" in content  # listed in kI2cSemanticPeripherals
    # Phase 3+4: Tier 2/3/4 facts.
    assert ("kSupportedSpeeds = {{100000u, 400000u, 1000000u}}") in content
    assert "kSupportsSmbus = true;" in content
    assert "kSupports7BitAddressing = true;" in content
    assert "kSupports10BitAddressing = true;" in content
    # TIMINGR preset for 400 kHz @ 64 MHz.
    assert "kTimingPresets = {{" in content
    assert "400000u, 64000000u" in content


def test_stm32g071rb_uart_traits_emit_typed_enums(
    execution_context: ExecutionContext,
) -> None:
    """add-typed-peripheral-enums-everywhere: STM32G0 USART1 surfaces
    typed `UartParityOf<USART1>::type` etc. with named entries.  No
    string-view name tables — the publication gate forbids string
    literals in runtime C++ output, so consumers stringify host-side."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    p = "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/uart.hpp"
    content = arts[p].content
    assert "struct UartParityOf {" in content
    assert "struct UartParityOf<PeripheralId::USART1> {" in content
    assert "using UartParity = typename UartParityOf<Id>::type;" in content
    assert "struct UartStopBitsOf<PeripheralId::USART1> {" in content
    assert "struct UartOversamplingOf<PeripheralId::USART1> {" in content
    assert "struct UartDataBitsOf<PeripheralId::USART1> {" in content
    assert "struct UartBaudClockSourceOf<PeripheralId::USART1> {" in content
    # Publication gate: no string literals + no string_view include.
    assert "#include <string_view>" not in content
    assert '"none"' not in content
    assert '"even"' not in content


def test_stm32g071rb_spi_traits_emit_typed_enums(
    execution_context: ExecutionContext,
) -> None:
    """SPI1 surfaces typed prescaler + frame-size enums with named
    entries (`div_2`..`div_256`, `bits_4`..`bits_16`)."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    p = "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/spi.hpp"
    content = arts[p].content
    assert "struct SpiPrescalerOf<PeripheralId::SPI1> {" in content
    assert "div_2 = 0u," in content
    assert "div_256 = 7u," in content
    assert "struct SpiFrameSizeOf<PeripheralId::SPI1> {" in content
    assert "bits_4 = 0u," in content
    assert "bits_16 = 12u," in content


def test_stm32g071rb_i2c_traits_emit_typed_speed_mode(
    execution_context: ExecutionContext,
) -> None:
    """I2C1 surfaces typed `I2cSpeedModeOf<I2C1>::type` with
    `standard`, `fast`, `fast_plus` entries."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    p = "st/stm32g0/generated/runtime/devices/stm32g071rb/driver_semantics/i2c.hpp"
    content = arts[p].content
    assert "struct I2cSpeedModeOf<PeripheralId::I2C1> {" in content
    assert "standard = 0u," in content
    assert "fast = 1u," in content
    assert "fast_plus = 2u," in content


def test_stm32g071rb_emits_cmake_device_module(
    execution_context: ExecutionContext,
) -> None:
    """add-cmake-package-config: STM32G0 emits per-device
    AlloyDevice-stm32g071rb.cmake declaring an INTERFACE IMPORTED
    target with Cortex-M0+ compile flags + linker-script reference."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    p = "st/stm32g0/generated/cmake/AlloyDevice-stm32g071rb.cmake"
    assert p in arts
    content = arts[p].content
    assert "add_library(AlloyDevice::stm32g071rb INTERFACE IMPORTED)" in content
    assert "target_compile_features(AlloyDevice::stm32g071rb INTERFACE cxx_std_20)" in content
    assert "-mcpu=cortex-m0plus" in content
    assert "-mthumb" in content
    assert "-mfloat-abi=soft" in content
    assert "device.ld" in content
    assert "startup.cpp" in content
    assert "${ALLOY_DEVICE_ROOT}" in content


def test_stm32g071rb_emits_cmake_toolchain_fragment(
    execution_context: ExecutionContext,
) -> None:
    """The opt-in toolchain fragment for cortex-m0plus selects
    arm-none-eabi-gcc as the cross-compiler."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    p = "st/stm32g0/generated/cmake/toolchain-cortex-m0plus.cmake"
    assert p in arts
    content = arts[p].content
    assert "set(CMAKE_SYSTEM_NAME Generic)" in content
    assert "set(CMAKE_SYSTEM_PROCESSOR arm)" in content
    assert "set(CMAKE_C_COMPILER arm-none-eabi-gcc)" in content
    assert "set(CMAKE_CXX_COMPILER arm-none-eabi-g++)" in content


def test_emits_cmake_meta_package(
    execution_context: ExecutionContext,
) -> None:
    """The top-level cmake/AlloyDeviceConfig.cmake resolves
    find_package(AlloyDevice REQUIRED COMPONENTS stm32g071rb) by
    including the per-device module."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    assert "cmake/AlloyDeviceConfig.cmake" in arts
    assert "cmake/AlloyDeviceConfigVersion.cmake" in arts
    config = arts["cmake/AlloyDeviceConfig.cmake"].content
    assert '"stm32g071rb=st/stm32g0/generated/cmake/AlloyDevice-stm32g071rb.cmake"' in config
    assert "AlloyDevice_FIND_COMPONENTS" in config
    version = arts["cmake/AlloyDeviceConfigVersion.cmake"].content
    assert "set(PACKAGE_VERSION" in version


def test_emit_pin_validation_header_for_stm32g071rb(
    execution_context: ExecutionContext,
) -> None:
    """emit-pinmux-validator-concepts: per-device pin_validation.hpp
    projects ``device.connection_candidates`` into C++20 concepts."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    key = "st/stm32g0/generated/runtime/devices/stm32g071rb/pin_validation.hpp"
    assert key in arts
    content = arts[key].content

    # Closed PeripheralSignal enum carries every admitted pair.
    assert "enum class PeripheralSignal : std::uint16_t {" in content
    assert "SPI1_SCK = 0u," in content
    assert "USART1_RX = " in content
    assert "USART1_TX = " in content

    # Closed RouteKind enum (no string literals).
    assert "enum class RouteKind : std::uint8_t {" in content
    assert "alternate_function = 0u," in content
    assert "std::string_view" not in content

    # Primary template defaults to std::false_type.
    assert (
        "template<PinId Pin, PeripheralSignal Signal>\n"
        "struct PinAssignmentValid : std::false_type {};" in content
    )

    # At least one populated specialisation flips it to true_type.
    assert (
        "struct PinAssignmentValid<PinId::PA1, PeripheralSignal::SPI1_SCK> "
        ": std::true_type {" in content
    )
    assert "static constexpr RouteKind kRouteKind = RouteKind::alternate_function;" in content
    assert "static constexpr std::uint8_t kRouteSelectorIndex = 0u;" in content

    # ValidPinAssignment concept declared.
    assert (
        "concept ValidPinAssignment = "
        "PinAssignmentValid<Pin, Signal>::value;" in content
    )

    # Constexpr lookup table + linear scan.
    assert "struct PinAssignmentEntry {" in content
    assert "inline constexpr std::array<PinAssignmentEntry, 3> kPinAssignments" in content
    assert "constexpr bool is_valid_pin_assignment(" in content


def test_emit_pin_validation_omits_unrouted_pin_signal_pairs(
    execution_context: ExecutionContext,
) -> None:
    """A (pin, signal) pair NOT in the IR's connection_candidates yields
    only the primary std::false_type template — no specialisation."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    content = arts[
        "st/stm32g0/generated/runtime/devices/stm32g071rb/pin_validation.hpp"
    ].content

    # PA1 is admitted as SPI1_SCK but NOT as USART1_TX — the
    # specialisation block for the latter must not exist, so the
    # primary false_type template applies.
    assert (
        "struct PinAssignmentValid<PinId::PA1, PeripheralSignal::USART1_TX>"
        not in content
    )
