from __future__ import annotations

from dataclasses import replace

from alloy_codegen.ir.model import (
    CanonicalDeviceIR,
    CapabilityDescriptor,
    ClockGateDescriptor,
    ClockNodeLite,
    ConnectionCandidate,
    ConnectionGroup,
    DeviceIdentity,
    DmaBindingDescriptor,
    DmaConflictGroup,
    DmaControllerDescriptor,
    DmaRequestDefinition,
    DmaRouteDescriptor,
    InterruptBindingDescriptor,
    InterruptDefinition,
    IpBlockDefinition,
    MemoryRegion,
    PackageDefinition,
    PackagePad,
    PeripheralClockBinding,
    PeripheralInstance,
    PinConstraint,
    PinDefinition,
    PinSignal,
    Provenance,
    RegisterFieldDescriptor,
    ResetDescriptor,
    RouteOperation,
    RouteRequirement,
    SignalEndpoint,
    StartupDescriptor,
    SystemClockProfile,
    VectorSlotDescriptor,
)


def _provenance() -> Provenance:
    return Provenance(
        source_id="fixture-source",
        source_path="fixtures/example.json",
        patch_ids=("fixture-patch",),
    )


def _base_device() -> CanonicalDeviceIR:
    provenance = _provenance()
    return CanonicalDeviceIR(
        schema_version="1.2.0",
        identity=DeviceIdentity(
            vendor="st",
            family="stm32g0",
            device="stm32g071rb",
            package="lqfp64",
            core="cortex-m0plus",
            summary="fixture device",
        ),
        memories=(
            MemoryRegion(
                name="flash",
                kind="flash",
                base_address=0x08000000,
                size_bytes=131072,
                access="rx",
                provenance=provenance,
                startup_roles=("nonvolatile", "copy-source", "vector-source"),
            ),
        ),
        packages=(
            PackageDefinition(
                name="lqfp64",
                pin_count=64,
                provenance=provenance,
            ),
        ),
        pins=(
            PinDefinition(
                name="PA9",
                port="A",
                number=9,
                signals=(
                    PinSignal(
                        function="gpio",
                        peripheral="GPIOA",
                        signal="IN9",
                        af_number=None,
                        provenance=provenance,
                    ),
                ),
                provenance=provenance,
            ),
        ),
        peripherals=(
            PeripheralInstance(
                name="USART1",
                ip_name="usart",
                ip_version="usart_v3_1",
                instance=1,
                base_address=0x40013800,
                rcc_enable_signal="RCC.APBENR2.USART1EN",
                rcc_reset_signal="RCC.APBRSTR2.USART1RST",
                provenance=provenance,
            ),
        ),
        interrupts=(
            InterruptDefinition(
                name="USART1",
                line=27,
                peripheral="USART1",
                provenance=provenance,
                shared_group=None,
                alias_names=("USART1_IRQHandler",),
            ),
        ),
        dma_requests=(
            DmaRequestDefinition(
                controller="DMA1",
                request_line="DMA1_CH1",
                peripheral="USART1",
                signal="TX",
                provenance=provenance,
            ),
        ),
        provenance=provenance,
    )


def test_canonical_device_ir_omits_empty_transitional_domains() -> None:
    payload = _base_device().to_dict()

    assert "ip_blocks" not in payload
    assert "register_fields" not in payload
    assert "connection_candidates" not in payload
    assert "interrupt_bindings" not in payload
    assert "startup_descriptors" not in payload
    assert "system_clock_profiles" not in payload
    assert "clock_nodes" not in payload
    assert "dma_bindings" not in payload
    assert "dma_routes" not in payload


def test_canonical_device_ir_serializes_connector_driven_domains_when_present() -> None:
    provenance = _provenance()
    device = _base_device()
    enriched = CanonicalDeviceIR(
        schema_version=device.schema_version,
        identity=device.identity,
        memories=device.memories,
        packages=device.packages,
        pins=device.pins,
        peripherals=device.peripherals,
        interrupts=device.interrupts,
        dma_requests=device.dma_requests,
        provenance=device.provenance,
        ip_blocks=(
            IpBlockDefinition(
                ip_name="usart",
                ip_version="usart_v3_1",
                peripheral_class="uart",
                register_profile="stm32-usart-v3",
                signal_roles=("tx", "rx"),
                capability_ids=("uart-fifo",),
                provenance=provenance,
            ),
        ),
        capabilities=(
            CapabilityDescriptor(
                capability_id="uart-fifo",
                scope="ip-block",
                peripheral_class="uart",
                name="fifo_depth",
                value="8",
                ip_name="usart",
                ip_version="usart_v3_1",
                peripheral=None,
                package=None,
                provenance=provenance,
            ),
        ),
        package_pads=(
            PackagePad(
                pad_id="pad-pa9",
                package="lqfp64",
                position_label="42",
                physical_index=42,
                pad_kind="io",
                bonded_pin="PA9",
                provenance=provenance,
            ),
        ),
        pin_constraints=(
            PinConstraint(
                constraint_id="pa9-debug-conflict",
                pin="PA9",
                kind="reserved",
                value="boot-alt",
                provenance=provenance,
            ),
        ),
        signal_endpoints=(
            SignalEndpoint(
                endpoint_id="uart-tx",
                peripheral_class="uart",
                signal="tx",
                direction="output",
                provenance=provenance,
            ),
        ),
        register_fields=(
            RegisterFieldDescriptor(
                field_id="field:usart1:cr1:te",
                register_id="register:usart1:cr1",
                peripheral="USART1",
                register_name="CR1",
                name="TE",
                bit_offset=3,
                bit_width=1,
                access="read-write",
                provenance=provenance,
            ),
        ),
        route_requirements=(
            RouteRequirement(
                requirement_id="req-usart1-clock",
                kind="clock-enable",
                target="RCC.APBENR2.USART1EN",
                value="1",
                provenance=provenance,
            ),
        ),
        route_operations=(
            RouteOperation(
                operation_id="op-usart1-af",
                kind="write-field",
                target="GPIOA.AFRH.AFSEL9",
                value="1",
                provenance=provenance,
            ),
        ),
        connection_candidates=(
            ConnectionCandidate(
                candidate_id="cand-usart1-tx-pa9",
                pin="PA9",
                peripheral="USART1",
                signal="tx",
                route_kind="alternate-function",
                route_selector="AF1",
                route_group_id="grp-usart1-default",
                requirement_ids=("req-usart1-clock",),
                operation_ids=("op-usart1-af",),
                capability_ids=("uart-fifo",),
                provenance=provenance,
            ),
        ),
        connection_groups=(
            ConnectionGroup(
                group_id="grp-usart1-default",
                peripheral="USART1",
                signals=("tx", "rx"),
                candidate_ids=("cand-usart1-tx-pa9",),
                package="lqfp64",
                conflict_group=None,
                provenance=provenance,
            ),
        ),
        interrupt_bindings=(
            InterruptBindingDescriptor(
                binding_id="interrupt-binding:usart1:usart1",
                peripheral="USART1",
                interrupt="USART1",
                line=27,
                vector_slot=43,
                symbol_name="USART1_IRQHandler",
                shared_group=None,
                alias_names=("USART1_IRQHandler",),
                provenance=provenance,
            ),
        ),
        vector_slots=(
            VectorSlotDescriptor(
                slot=43,
                symbol_name="USART1_IRQHandler",
                interrupt="USART1",
                kind="external-interrupt",
                provenance=provenance,
            ),
        ),
        startup_descriptors=(
            StartupDescriptor(
                descriptor_id="startup-copy-data",
                kind="copy",
                source_region="flash",
                target_region="sram",
                symbol="_sidata",
                provenance=provenance,
            ),
        ),
        system_clock_profiles=(
            SystemClockProfile(
                profile_id="default-pll",
                kind="default",
                source_kind="pll-external",
                sysclk_hz=84_000_000,
                hclk_hz=84_000_000,
                apb1_hz=42_000_000,
                apb2_hz=84_000_000,
                source_hz=8_000_000,
                oscillator_startup_cycles=255,
                pll_m=4,
                pll_n=168,
                pll_p=4,
                pll_q=7,
                flash_latency=2,
                provenance=provenance,
            ),
        ),
        clock_nodes=(
            ClockNodeLite(
                node_id="pclk2",
                kind="derived",
                parent="sysclk",
                selector=None,
                provenance=provenance,
            ),
        ),
        clock_gates=(
            ClockGateDescriptor(
                gate_id="gate-usart1",
                peripheral="USART1",
                enable_signal="RCC.APBENR2.USART1EN",
                parent_node="pclk2",
                provenance=provenance,
            ),
        ),
        resets=(
            ResetDescriptor(
                reset_id="reset-usart1",
                peripheral="USART1",
                reset_signal="RCC.APBRSTR2.USART1RST",
                active_level="high",
                provenance=provenance,
            ),
        ),
        peripheral_clock_bindings=(
            PeripheralClockBinding(
                peripheral="USART1",
                clock_gate_id="gate-usart1",
                reset_id="reset-usart1",
                selector_id=None,
                provenance=provenance,
            ),
        ),
        dma_controllers=(
            DmaControllerDescriptor(
                controller="DMA1",
                version="dma_v1",
                channel_count=7,
                request_count=2,
                provenance=provenance,
            ),
        ),
        dma_bindings=(
            DmaBindingDescriptor(
                binding_id="dma-binding:usart1:tx:dma1:dma1_ch1",
                peripheral="USART1",
                signal="TX",
                controller="DMA1",
                request_line="DMA1_CH1",
                route_id="dma-usart1-tx",
                conflict_group="dma1-shared",
                provenance=provenance,
            ),
        ),
        dma_routes=(
            DmaRouteDescriptor(
                route_id="dma-usart1-tx",
                controller="DMA1",
                request_line="DMA1_CH1",
                peripheral="USART1",
                signal="TX",
                conflict_group="dma1-shared",
                provenance=provenance,
            ),
            DmaRouteDescriptor(
                route_id="dma-usart1-rx",
                controller="DMA1",
                request_line="DMA1_CH1",
                peripheral="USART1",
                signal="RX",
                conflict_group="dma1-shared",
                provenance=provenance,
            ),
        ),
        dma_conflict_groups=(
            DmaConflictGroup(
                conflict_group_id="dma1-shared",
                route_ids=("dma-usart1-rx", "dma-usart1-tx"),
                provenance=provenance,
            ),
        ),
    )

    payload = enriched.to_dict()

    assert payload["ip_blocks"][0]["ip_version"] == "usart_v3_1"
    assert payload["capabilities"][0]["capability_id"] == "uart-fifo"
    assert payload["capabilities"][0]["scope"] == "ip-block"
    assert payload["capabilities"][0]["ip_name"] == "usart"
    assert payload["package_pads"][0]["position_label"] == "42"
    assert payload["package_pads"][0]["bonding_state"] == "bonded"
    assert payload["pin_constraints"][0]["constraint_id"] == "pa9-debug-conflict"
    assert payload["signal_endpoints"][0]["endpoint_id"] == "uart-tx"
    assert payload["register_fields"][0]["field_id"] == "field:usart1:cr1:te"
    assert payload["route_requirements"][0]["requirement_id"] == "req-usart1-clock"
    assert payload["route_operations"][0]["operation_id"] == "op-usart1-af"
    assert payload["connection_candidates"][0]["candidate_id"] == "cand-usart1-tx-pa9"
    assert payload["connection_groups"][0]["group_id"] == "grp-usart1-default"
    assert payload["interrupt_bindings"][0]["binding_id"] == "interrupt-binding:usart1:usart1"
    assert payload["vector_slots"][0]["symbol_name"] == "USART1_IRQHandler"
    assert payload["interrupts"][0]["alias_names"] == ["USART1_IRQHandler"]
    assert payload["memories"][0]["startup_roles"] == [
        "nonvolatile",
        "copy-source",
        "vector-source",
    ]
    assert payload["startup_descriptors"][0]["descriptor_id"] == "startup-copy-data"
    assert payload["system_clock_profiles"][0]["profile_id"] == "default-pll"
    assert payload["system_clock_profiles"][0]["oscillator_startup_cycles"] == 255
    assert payload["clock_nodes"][0]["node_id"] == "pclk2"
    assert payload["clock_gates"][0]["gate_id"] == "gate-usart1"
    assert payload["resets"][0]["reset_id"] == "reset-usart1"
    assert payload["peripheral_clock_bindings"][0]["peripheral"] == "USART1"
    assert payload["dma_controllers"][0]["controller"] == "DMA1"
    assert payload["dma_controllers"][0]["request_count"] == 2
    assert payload["dma_bindings"][0]["binding_id"] == "dma-binding:usart1:tx:dma1:dma1_ch1"
    assert payload["dma_routes"][0]["route_id"] == "dma-usart1-tx"
    assert payload["dma_conflict_groups"][0]["conflict_group_id"] == "dma1-shared"


def test_canonical_device_ir_serializes_memory_address_space_when_present() -> None:
    device = _base_device()
    memory = replace(device.memories[0], address_space="prog")
    enriched = replace(device, memories=(memory,))

    payload = enriched.to_dict()

    assert payload["memories"][0]["address_space"] == "prog"
