from __future__ import annotations

from alloy_codegen.connector_model import enrich_connector_descriptors
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.normalize import run as run_normalize


def test_enrich_connector_descriptors_builds_st_route_model(execution_context) -> None:
    normalized = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)
    device = enrich_connector_descriptors(normalized.payload.devices[0])

    assert device.ip_blocks
    assert device.capabilities
    assert device.signal_endpoints
    assert device.route_requirements
    assert device.route_operations
    assert device.connection_candidates
    assert device.connection_groups
    assert device.vector_slots
    assert device.startup_descriptors
    assert device.clock_gates
    assert device.peripheral_clock_bindings
    assert device.dma_controllers
    assert device.dma_routes

    tx_candidates = [
        candidate
        for candidate in device.connection_candidates
        if candidate.peripheral == "USART1" and candidate.signal == "tx"
    ]
    uart_groups = [
        group
        for group in device.connection_groups
        if group.peripheral == "USART1" and group.signals == ("tx", "rx")
    ]
    assert tx_candidates
    assert uart_groups
    assert all(candidate.route_kind == "alternate-function" for candidate in tx_candidates)
    assert all(
        any(
            requirement_id.startswith("requirement:package:")
            for requirement_id in candidate.requirement_ids
        )
        for candidate in tx_candidates
    )
    assert all(
        any(
            requirement_id.startswith("requirement:bonded-pin:")
            for requirement_id in candidate.requirement_ids
        )
        for candidate in tx_candidates
    )
    assert all(
        any(
            capability_id.startswith("capability-instance:usart1:")
            for capability_id in candidate.capability_ids
        )
        for candidate in tx_candidates
    )
    assert any(op.kind == "write-selector" for op in device.route_operations)
    assert any(interrupt.alias_names for interrupt in device.interrupts)
    assert any(vector_slot.slot == 1 for vector_slot in device.vector_slots)
    assert any(memory.startup_roles for memory in device.memories)
    dma1 = next(
        controller
        for controller in device.dma_controllers
        if controller.controller == "DMA1"
    )
    assert dma1.channel_count is not None and dma1.channel_count > 0
    assert dma1.version == "bdma_v1_0"


def test_enrich_connector_descriptors_builds_microchip_route_model(
    microchip_execution_context,
) -> None:
    normalized = run_normalize(
        PipelineScope(device="atsame70q21b"),
        microchip_execution_context,
    )
    device = enrich_connector_descriptors(normalized.payload.devices[0])

    assert device.connection_candidates
    assert device.connection_groups
    assert device.signal_endpoints
    assert device.vector_slots
    assert device.startup_descriptors
    assert device.clock_gates
    assert device.peripheral_clock_bindings
    assert device.dma_controllers
    assert device.dma_routes

    microchip_candidates = [
        candidate
        for candidate in device.connection_candidates
        if candidate.pin == "PA0"
    ]
    can_groups = [
        group
        for group in device.connection_groups
        if group.peripheral == "MCAN0" and group.signals == ("tx", "rx")
    ]
    assert microchip_candidates
    assert can_groups
    assert any(candidate.route_kind == "peripheral-mux" for candidate in microchip_candidates)
    assert all(
        "requirement:package:lqfp144" in candidate.requirement_ids
        for candidate in microchip_candidates
    )
    assert any(
        "requirement:bonded-pin:lqfp144:pa0" in candidate.requirement_ids
        for candidate in microchip_candidates
    )
    assert any(
        "requirement:constraint:PA0:wakeup-capable" in candidate.requirement_ids
        for candidate in microchip_candidates
    )
    assert any(
        any(
            capability_id.startswith("capability-instance:")
            for capability_id in candidate.capability_ids
        )
        for candidate in microchip_candidates
    )
    assert any(interrupt.shared_group for interrupt in device.interrupts)


def test_enrich_connector_descriptors_builds_nxp_route_model(
    nxp_execution_context,
) -> None:
    normalized = run_normalize(
        PipelineScope(device="mimxrt1062"),
        nxp_execution_context,
    )
    device = enrich_connector_descriptors(normalized.payload.devices[0])

    assert device.connection_candidates
    assert device.connection_groups
    assert device.signal_endpoints
    assert device.vector_slots
    assert device.startup_descriptors
    assert device.clock_gates
    assert device.peripheral_clock_bindings

    nxp_candidates = [
        candidate
        for candidate in device.connection_candidates
        if candidate.peripheral in {"LPUART1", "LPUART3", "SPI1", "I2C1"}
    ]
    bundle_groups = [
        group
        for group in device.connection_groups
        if group.peripheral in {"LPUART1", "LPI2C1"}
    ]
    assert nxp_candidates
    assert any(group.signals == ("tx", "rx") for group in bundle_groups) or any(
        group.signals == ("scl", "sda") for group in bundle_groups
    )
    assert any(candidate.route_kind == "iomuxc-mux" for candidate in nxp_candidates)
    assert all(
        any(
            capability_id.startswith("capability-instance:")
            for capability_id in candidate.capability_ids
        )
        for candidate in nxp_candidates
    )
    if device.dma_requests:
        assert device.dma_controllers
        assert device.dma_routes
    assert any(vector_slot.slot == 1 for vector_slot in device.vector_slots)
