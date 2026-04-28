"""Emit stage bootstrap implementation."""

from __future__ import annotations

from alloy_codegen.bootstrap import (
    ARTIFACT_LAYOUT_VERSION,
    CPP_CONTRACT_VERSION,
    IR_SCHEMA_VERSION,
    PIPELINE_NAME,
    PUBLICATION_TARGET_REPOSITORY,
)
from alloy_codegen.canonical_device_yaml_emitter import emit_canonical_device_yaml
from alloy_codegen.cmake_emission import (
    emit_cmake_device_module,
    emit_cmake_meta_package,
    emit_cmake_toolchain_fragment,
)
from alloy_codegen.context import ExecutionContext
from alloy_codegen.emission import (
    emit_artifact_manifest,
    emit_capabilities_metadata,
    emit_connectors_metadata,
    emit_coverage_report,
    emit_device_metadata,
    emit_family_connectivity,
    emit_family_index,
    emit_ip_blocks_metadata,
    emit_packages_metadata,
    emit_startup_source,
    emit_startup_vectors_source,
    emit_system_descriptors_metadata,
    emit_validation_report,
    emit_validation_summary,
    materialize_artifacts,
)
from alloy_codegen.manifests import ArtifactManifest
from alloy_codegen.reporting import EmissionPlan, EmittedArtifact
from alloy_codegen.runtime_avr_startup import (
    _is_avr_device,
    emit_avr_startup_source,
    emit_avr_startup_vectors_source,
)
from alloy_codegen.runtime_board_emission import emit_boards_manifest, emit_runtime_board_header
from alloy_codegen.runtime_capabilities import (
    emit_runtime_capabilities_header,
    emit_runtime_capabilities_json,
)
from alloy_codegen.runtime_clock_config import (
    emit_runtime_clock_config_header,
    emit_runtime_clock_profiles_header,
)
from alloy_codegen.runtime_clock_graph import emit_runtime_clock_graph_header
from alloy_codegen.runtime_connectors import emit_runtime_connectors_header
from alloy_codegen.runtime_driver_semantics import (
    emit_runtime_driver_adc_semantics_header,
    emit_runtime_driver_can_semantics_header,
    emit_runtime_driver_dac_semantics_header,
    emit_runtime_driver_dma_semantics_header,
    emit_runtime_driver_eth_semantics_header,
    emit_runtime_driver_gpio_semantics_header,
    emit_runtime_driver_i2c_semantics_header,
    emit_runtime_driver_pio_semantics_header,
    emit_runtime_driver_pwm_semantics_header,
    emit_runtime_driver_qspi_semantics_header,
    emit_runtime_driver_rtc_semantics_header,
    emit_runtime_driver_sdmmc_semantics_header,
    emit_runtime_driver_semantics_common_header,
    emit_runtime_driver_spi_semantics_header,
    emit_runtime_driver_timer_semantics_header,
    emit_runtime_driver_uart_semantics_header,
    emit_runtime_driver_usb_semantics_header,
    emit_runtime_driver_watchdog_semantics_header,
)
from alloy_codegen.runtime_enable_domains import emit_runtime_enable_domains_header
from alloy_codegen.runtime_interrupt_stubs import emit_runtime_interrupt_stubs_header
from alloy_codegen.runtime_interrupts import emit_runtime_interrupts_header
from alloy_codegen.runtime_linker_script import emit_runtime_linker_script
from alloy_codegen.runtime_lite_emission import (
    emit_runtime_lite_clock_bindings_header,
    emit_runtime_lite_dma_bindings_header,
    emit_runtime_lite_peripheral_instances_header,
    emit_runtime_lite_pins_header,
    emit_runtime_lite_register_fields_header,
    emit_runtime_lite_registers_header,
    emit_runtime_lite_routes_header,
    emit_runtime_lite_types_header,
)
from alloy_codegen.runtime_low_power import emit_runtime_low_power_header
from alloy_codegen.runtime_pin_validation import emit_runtime_pin_validation_header
from alloy_codegen.runtime_reports import (
    emit_runtime_capability_summary_report,
    emit_runtime_compatibility_matrix_report,
    emit_runtime_explainability_report,
    emit_runtime_provenance_report,
)
from alloy_codegen.runtime_resets import emit_runtime_resets_header
from alloy_codegen.runtime_riscv_startup import (
    _is_riscv_device,
    emit_riscv_startup_source,
    emit_riscv_startup_vectors_source,
)
from alloy_codegen.runtime_startup import emit_runtime_startup_header
from alloy_codegen.runtime_system_clock import emit_runtime_system_clock_header
from alloy_codegen.runtime_system_sequences import emit_runtime_system_sequences_header
from alloy_codegen.runtime_systick import emit_runtime_systick_header
from alloy_codegen.runtime_xtensa_startup import (
    _is_xtensa_device,
    emit_xtensa_startup_source,
    emit_xtensa_startup_vectors_source,
)
from alloy_codegen.scope import PipelineScope
from alloy_codegen.serialization import canonical_json_sha256
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.validate import run as run_validate
from alloy_codegen.version import __version__


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the bootstrap emit stage."""
    execution_context = context or ExecutionContext.default()
    validate_result = run_validate(scope, execution_context)
    source_manifest = validate_result.payload.source_manifest
    patch_manifest = validate_result.payload.patch_manifest
    devices = validate_result.payload.devices
    validation_report = validate_result.payload.report
    artifact_manifest = ArtifactManifest.for_scope(
        generator_version=__version__,
        ir_schema_version=IR_SCHEMA_VERSION,
        scope=validate_result.scope,
        source_manifest=source_manifest,
        patch_manifest=patch_manifest,
        canonical_ir_sha256=canonical_json_sha256(devices),
        validation_report_id=validation_report.report_id,
        validation_report_sha256=canonical_json_sha256(validation_report.to_dict()),
        pipeline_name=PIPELINE_NAME,
        artifact_layout_version=ARTIFACT_LAYOUT_VERSION,
        cpp_contract_version=CPP_CONTRACT_VERSION,
        target_repository=PUBLICATION_TARGET_REPOSITORY,
    )

    resolved_scope = validate_result.scope
    family_dir = f"{resolved_scope.resolved_vendor()}/{resolved_scope.resolved_family()}"
    artifacts: list[EmittedArtifact] = [
        emit_artifact_manifest(family_dir=family_dir, artifact_manifest=artifact_manifest),
        emit_validation_report(family_dir=family_dir, report=validation_report),
        emit_validation_summary(
            family_dir=family_dir,
            devices=devices,
            report=validation_report,
        ),
        emit_coverage_report(
            family_dir=family_dir,
            devices=devices,
            report=validation_report,
        ),
        emit_runtime_provenance_report(family_dir=family_dir, devices=devices),
        emit_runtime_explainability_report(family_dir=family_dir, devices=devices),
        emit_runtime_capability_summary_report(family_dir=family_dir, devices=devices),
        emit_runtime_compatibility_matrix_report(family_dir=family_dir, devices=devices),
        emit_family_index(family_dir=family_dir, devices=devices),
        emit_family_connectivity(family_dir=family_dir, devices=devices),
        emit_ip_blocks_metadata(family_dir=family_dir, devices=devices),
        emit_capabilities_metadata(family_dir=family_dir, devices=devices),
        emit_packages_metadata(family_dir=family_dir, devices=devices),
        emit_connectors_metadata(family_dir=family_dir, devices=devices),
        emit_system_descriptors_metadata(family_dir=family_dir, devices=devices),
    ]
    for device in devices:
        artifacts.extend(
            (
                emit_device_metadata(family_dir=family_dir, device=device),
                emit_runtime_linker_script(family_dir=family_dir, device=device),
                emit_cmake_device_module(family_dir=family_dir, device=device),
                (
                    emit_avr_startup_source(family_dir=family_dir, device=device)
                    if _is_avr_device(device)
                    else emit_riscv_startup_source(family_dir=family_dir, device=device)
                    if _is_riscv_device(device)
                    else emit_xtensa_startup_source(family_dir=family_dir, device=device)
                    if _is_xtensa_device(device)
                    else emit_startup_source(family_dir=family_dir, device=device)
                ),
                (
                    emit_avr_startup_vectors_source(family_dir=family_dir, device=device)
                    if _is_avr_device(device)
                    else emit_riscv_startup_vectors_source(family_dir=family_dir, device=device)
                    if _is_riscv_device(device)
                    else emit_xtensa_startup_vectors_source(family_dir=family_dir, device=device)
                    if _is_xtensa_device(device)
                    else emit_startup_vectors_source(family_dir=family_dir, device=device)
                ),
                emit_runtime_lite_peripheral_instances_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_lite_pins_header(family_dir=family_dir, device=device),
                emit_runtime_lite_registers_header(family_dir=family_dir, device=device),
                emit_runtime_lite_register_fields_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_lite_clock_bindings_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_lite_dma_bindings_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_lite_routes_header(family_dir=family_dir, device=device),
                emit_runtime_connectors_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_semantics_common_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_gpio_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_uart_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_i2c_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_spi_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_dma_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_adc_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_dac_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_can_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_eth_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_usb_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_qspi_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_sdmmc_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_rtc_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_watchdog_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_timer_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_pwm_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_driver_pio_semantics_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_interrupts_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_interrupt_stubs_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_resets_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_enable_domains_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_clock_graph_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_capabilities_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_capabilities_json(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_systick_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_startup_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_system_clock_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_clock_profiles_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_clock_config_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_low_power_header(
                    family_dir=family_dir,
                    device=device,
                ),
                emit_runtime_system_sequences_header(
                    family_dir=family_dir,
                    device=device,
                ),
            )
        )
        # emit-pinmux-validator-concepts: per-device C++20-concepts
        # projection of ``device.connection_candidates`` so HAL drivers
        # can constrain templates with ``ValidPinAssignment<...>``.  Only
        # devices that actually carry connection candidates emit a
        # header.
        pin_validation = emit_runtime_pin_validation_header(family_dir=family_dir, device=device)
        if pin_validation is not None:
            artifacts.append(pin_validation)
        # define-canonical-device-yaml-schema: per-device canonical YAML
        # artifact — foundation of the alloy-devices-yml data-repo split.
        artifacts.append(emit_canonical_device_yaml(family_dir=family_dir, device=device))
        # add-board-support-package-emitter: per-board BSP headers.
        for board in device.boards:
            artifacts.append(
                emit_runtime_board_header(family_dir=family_dir, device=device, board=board)
            )
    # Top-level boards manifest aggregating every admitted board.
    artifacts.append(emit_boards_manifest(family_dir=family_dir, devices=devices))
    artifacts.append(emit_runtime_lite_types_header(family_dir=family_dir, devices=devices))
    # CMake package-config (added by ``add-cmake-package-config``).  One
    # opt-in toolchain fragment per unique core, plus a top-level
    # ``cmake/AlloyDeviceConfig.cmake`` + version file resolving
    # ``find_package(AlloyDevice REQUIRED COMPONENTS <device>...)``.
    seen_cores: set[str] = set()
    for device in devices:
        core = device.identity.core
        if core in seen_cores:
            continue
        seen_cores.add(core)
        toolchain = emit_cmake_toolchain_fragment(family_dir=family_dir, device=device)
        if toolchain is not None:
            artifacts.append(toolchain)
    cmake_config, cmake_version = emit_cmake_meta_package(devices=tuple(devices))
    artifacts.append(cmake_config)
    artifacts.append(cmake_version)
    materialized_artifacts = materialize_artifacts(
        artifact_root=execution_context.artifact_root,
        artifacts=tuple(artifacts),
    )

    return StageResult(
        stage="emit",
        scope=validate_result.scope,
        status="completed",
        payload=EmissionPlan(
            artifact_manifest=artifact_manifest,
            artifacts=materialized_artifacts,
        ),
    )
