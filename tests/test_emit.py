from __future__ import annotations

import json
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run


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


def test_emit_includes_metadata_artifacts_with_content(
    execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}

    assert result.stage == "emit"
    assert result.payload.artifact_manifest.manifest_kind == "artifact-manifest-v1"

    manifest_artifact = artifacts["st/stm32g0/artifact-manifest.json"]
    validation_artifact = artifacts["st/stm32g0/validation-report.json"]
    family_index_artifact = artifacts["st/stm32g0/family-index.json"]
    connectivity_artifact = artifacts["st/stm32g0/family-connectivity.json"]
    ip_blocks_artifact = artifacts["st/stm32g0/metadata/ip-blocks.json"]
    capabilities_artifact = artifacts["st/stm32g0/metadata/capabilities.json"]
    packages_artifact = artifacts["st/stm32g0/metadata/packages.json"]
    connectors_artifact = artifacts["st/stm32g0/metadata/connectors.json"]
    system_descriptors_artifact = artifacts["st/stm32g0/metadata/system-descriptors.json"]
    device_artifact = artifacts["st/stm32g0/stm32g071rb/device.json"]
    register_map_artifact = artifacts["st/stm32g0/stm32g071rb/register_map.hpp"]
    pin_functions_artifact = artifacts["st/stm32g0/stm32g071rb/pin_functions.hpp"]
    startup_artifact = artifacts["st/stm32g0/stm32g071rb/startup.cpp"]
    rcc_map_artifact = artifacts["st/stm32g0/generated/rcc_map.hpp"]
    dma_map_artifact = artifacts["st/stm32g0/generated/dma_map.hpp"]
    connector_tables_artifact = artifacts["st/stm32g0/generated/connector_tables.hpp"]
    interrupt_map_artifact = artifacts["st/stm32g0/generated/interrupt_map.hpp"]
    memory_map_artifact = artifacts["st/stm32g0/generated/memory_map.hpp"]
    package_map_artifact = artifacts["st/stm32g0/generated/package_map.hpp"]
    clock_tree_artifact = artifacts["st/stm32g0/generated/clock_tree_lite.hpp"]
    startup_descriptors_artifact = artifacts[
        "st/stm32g0/generated/devices/stm32g071rb/startup_descriptors.hpp"
    ]
    startup_vectors_artifact = artifacts[
        "st/stm32g0/generated/devices/stm32g071rb/startup_vectors.cpp"
    ]
    ip_block_artifacts = [
        artifact
        for path, artifact in artifacts.items()
        if path.startswith("st/stm32g0/generated/ip/")
    ]
    gpio_artifacts = [
        artifact
        for path, artifact in artifacts.items()
        if path.startswith("st/stm32g0/generated/peripherals/")
    ]
    assert gpio_artifacts, "Expected at least one GPIO peripheral header"
    assert ip_block_artifacts, "Expected at least one IP block header"

    for artifact in (
        manifest_artifact,
        validation_artifact,
        family_index_artifact,
        connectivity_artifact,
        ip_blocks_artifact,
        capabilities_artifact,
        packages_artifact,
        connectors_artifact,
        system_descriptors_artifact,
        device_artifact,
    ):
        assert artifact.artifact_kind in {"canonical-metadata", "validation-report"}
        assert artifact.content is not None
        assert artifact.content_sha256 is not None
        assert artifact.content_bytes and artifact.content_bytes > 0
        assert artifact.materialized_path is not None
        assert Path(artifact.materialized_path).exists()

    manifest_payload = json.loads(manifest_artifact.content)
    validation_payload = json.loads(validation_artifact.content)
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
    assert family_index_payload["device_count"] == 1
    assert family_index_payload["devices"][0]["device"] == "stm32g071rb"
    assert (
        family_index_payload["devices"][0]["metadata_path"] == "st/stm32g0/stm32g071rb/device.json"
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

    for artifact in (register_map_artifact, pin_functions_artifact, startup_artifact):
        assert artifact.artifact_kind == "generated-cpp"
        assert artifact.content is not None
        assert artifact.content_sha256 is not None
        assert artifact.materialized_path is not None
        assert Path(artifact.materialized_path).exists()

    for gpio_artifact in gpio_artifacts:
        assert gpio_artifact.artifact_kind == "generated-cpp"
        assert gpio_artifact.content is not None
        assert Path(gpio_artifact.materialized_path).exists()
        assert "kPeripheral" in gpio_artifact.content

    for ip_block_artifact in ip_block_artifacts:
        assert ip_block_artifact.artifact_kind == "generated-cpp"
        assert "kIpBlock" in ip_block_artifact.content
        assert "kCapabilities" in ip_block_artifact.content

    assert "kPeripheralBases" in register_map_artifact.content
    assert "kPinFunctions" in pin_functions_artifact.content
    assert "kInterruptTable" in startup_artifact.content

    signal_map_artifact = artifacts["st/stm32g0/generated/signal_map.hpp"]
    assert signal_map_artifact.artifact_kind == "generated-cpp"
    assert "kSignalMap" in signal_map_artifact.content
    assert "SignalDescriptor" in signal_map_artifact.content

    assert connector_tables_artifact.artifact_kind == "generated-cpp"
    assert "kConnectionCandidates" in connector_tables_artifact.content
    assert "kConnectionGroups" in connector_tables_artifact.content

    assert rcc_map_artifact.artifact_kind == "generated-cpp"
    assert rcc_map_artifact.content is not None
    assert rcc_map_artifact.content_sha256 is not None
    assert Path(rcc_map_artifact.materialized_path).exists()
    assert "kRccMap" in rcc_map_artifact.content
    assert "RccDescriptor" in rcc_map_artifact.content

    assert dma_map_artifact.artifact_kind == "generated-cpp"
    assert dma_map_artifact.content is not None
    assert dma_map_artifact.content_sha256 is not None
    assert Path(dma_map_artifact.materialized_path).exists()
    assert "kDmaMap" in dma_map_artifact.content
    assert "DmaDescriptor" in dma_map_artifact.content

    assert interrupt_map_artifact.artifact_kind == "generated-cpp"
    assert "kInterruptMap" in interrupt_map_artifact.content
    assert "InterruptDescriptor" in interrupt_map_artifact.content
    assert "shared_group" in interrupt_map_artifact.content
    assert "alias_names" in interrupt_map_artifact.content

    assert memory_map_artifact.artifact_kind == "generated-cpp"
    assert "kMemoryMap" in memory_map_artifact.content
    assert "MemoryDescriptor" in memory_map_artifact.content
    assert "startup_roles" in memory_map_artifact.content

    assert package_map_artifact.artifact_kind == "generated-cpp"
    assert "kPackageMap" in package_map_artifact.content
    assert "PackageDescriptor" in package_map_artifact.content

    assert clock_tree_artifact.artifact_kind == "generated-cpp"
    assert "kClockNodes" in clock_tree_artifact.content
    assert "kClockGates" in clock_tree_artifact.content
    assert "kPeripheralClockBindings" in clock_tree_artifact.content

    assert startup_descriptors_artifact.artifact_kind == "generated-cpp"
    assert "kVectorSlots" in startup_descriptors_artifact.content
    assert "kStartupDescriptors" in startup_descriptors_artifact.content

    assert startup_vectors_artifact.artifact_kind == "generated-cpp"
    assert "kStartupVectorTable" in startup_vectors_artifact.content


def test_emit_matches_golden_artifacts(
    execution_context: ExecutionContext,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
) -> None:
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}
    fixture_root = Path(__file__).parent / "fixtures" / "emitted" / "stm32g0"

    manifest_payload = json.loads(artifacts["st/stm32g0/artifact-manifest.json"].content)
    validation_payload = json.loads(artifacts["st/stm32g0/validation-report.json"].content)

    assert _normalize_manifest_payload(
        manifest_payload,
        fixture_source_root=fixture_source_root,
        fixture_pin_source_root=fixture_pin_source_root,
    ) == _load_json_fixture(fixture_root / "stm32g071rb" / "artifact-manifest.json")
    assert validation_payload == _load_json_fixture(
        fixture_root / "stm32g071rb" / "validation-report.json"
    )
    assert json.loads(artifacts["st/stm32g0/family-index.json"].content) == _load_json_fixture(
        fixture_root / "family-index.json"
    )
    assert json.loads(
        artifacts["st/stm32g0/family-connectivity.json"].content
    ) == _load_json_fixture(fixture_root / "family-connectivity.json")
    assert json.loads(
        artifacts["st/stm32g0/metadata/ip-blocks.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "ip-blocks.json")
    assert json.loads(
        artifacts["st/stm32g0/metadata/capabilities.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "capabilities.json")
    assert json.loads(
        artifacts["st/stm32g0/metadata/packages.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "packages.json")
    assert json.loads(
        artifacts["st/stm32g0/metadata/connectors.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "connectors.json")
    assert json.loads(
        artifacts["st/stm32g0/metadata/system-descriptors.json"].content
    ) == _load_json_fixture(fixture_root / "metadata" / "system-descriptors.json")
    assert json.loads(
        artifacts["st/stm32g0/stm32g071rb/device.json"].content
    ) == _load_json_fixture(fixture_root / "stm32g071rb" / "device.json")
    assert artifacts["st/stm32g0/stm32g071rb/register_map.hpp"].content == (
        fixture_root / "stm32g071rb" / "register_map.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/stm32g071rb/pin_functions.hpp"].content == (
        fixture_root / "stm32g071rb" / "pin_functions.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/stm32g071rb/startup.cpp"].content == (
        fixture_root / "stm32g071rb" / "startup.cpp"
    ).read_text(encoding="utf-8")
    for gpio_fixture in (fixture_root / "generated" / "peripherals").iterdir():
        artifact_path = f"st/stm32g0/generated/peripherals/{gpio_fixture.name}"
        assert artifacts[artifact_path].content == gpio_fixture.read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/signal_map.hpp"].content == (
        fixture_root / "generated" / "signal_map.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/rcc_map.hpp"].content == (
        fixture_root / "generated" / "rcc_map.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/dma_map.hpp"].content == (
        fixture_root / "generated" / "dma_map.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/connector_tables.hpp"].content == (
        fixture_root / "generated" / "connector_tables.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/interrupt_map.hpp"].content == (
        fixture_root / "generated" / "interrupt_map.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/memory_map.hpp"].content == (
        fixture_root / "generated" / "memory_map.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/package_map.hpp"].content == (
        fixture_root / "generated" / "package_map.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/clock_tree_lite.hpp"].content == (
        fixture_root / "generated" / "clock_tree_lite.hpp"
    ).read_text(encoding="utf-8")
    assert (
        artifacts["st/stm32g0/generated/devices/stm32g071rb/startup_descriptors.hpp"].content
        == (
            fixture_root / "generated" / "devices" / "stm32g071rb" / "startup_descriptors.hpp"
        ).read_text(encoding="utf-8")
    )
    assert artifacts["st/stm32g0/generated/devices/stm32g071rb/startup_vectors.cpp"].content == (
        fixture_root / "generated" / "devices" / "stm32g071rb" / "startup_vectors.cpp"
    ).read_text(encoding="utf-8")
    for ip_fixture in sorted((fixture_root / "generated" / "ip").iterdir()):
        artifact_path = f"st/stm32g0/generated/ip/{ip_fixture.name}"
        assert artifacts[artifact_path].content == ip_fixture.read_text(encoding="utf-8")


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
    assert artifacts["microchip/same70/generated/connector_tables.hpp"].content is not None
    assert artifacts["microchip/same70/generated/interrupt_map.hpp"].content is not None
    assert artifacts["microchip/same70/generated/memory_map.hpp"].content is not None
    assert artifacts["microchip/same70/generated/package_map.hpp"].content is not None
    assert artifacts["microchip/same70/generated/clock_tree_lite.hpp"].content is not None
    assert (
        artifacts["microchip/same70/generated/devices/atsame70q21b/startup_descriptors.hpp"].content
        is not None
    )
    assert (
        artifacts["microchip/same70/generated/devices/atsame70q21b/startup_vectors.cpp"].content
        is not None
    )
    microchip_ip_headers = [
        path for path in artifacts if path.startswith("microchip/same70/generated/ip/")
    ]
    assert microchip_ip_headers


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

    assert [pad["pad_id"] for pad in reconstructed_pinout] == ["17", "18", "19", "20", "29", "30"]
    assert reconstructed_pinout[0]["position_label"] == "17"
    assert reconstructed_pinout[0]["bonded_pin"] == "PA0"
    assert reconstructed_pinout[0]["pad_kind"] == "io"
    assert any(pin_entry["pin"] == "PB6" for pin_entry in device_pinout["pin_index"])


def test_emit_stage_is_byte_stable(execution_context: ExecutionContext) -> None:
    scope = PipelineScope()
    result_a = json.dumps(run(scope, execution_context).to_dict(), sort_keys=True)
    result_b = json.dumps(run(scope, execution_context).to_dict(), sort_keys=True)

    assert result_a == result_b
