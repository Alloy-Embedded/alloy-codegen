from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import CanonicalDeviceIR, PackagePad, PeripheralInstance, PinDefinition
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.normalize import run as run_normalize
from alloy_codegen.stages.validate import run as run_validate
from alloy_codegen.validation import build_validation_report


def test_validate_reports_gate_statuses(execution_context: ExecutionContext) -> None:
    result = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    report = result.payload.report
    device = result.payload.devices[0]

    assert result.status == "completed"
    assert report.report_id == "bootstrap-validation-v1"
    assert report.gate_status("gate-a").passed is True
    assert report.gate_status("gate-b").passed is True
    assert report.gate_status("gate-c").passed is True
    assert report.draft_system_descriptor_domains == ()
    assert report.system_descriptor_status("startup").passed is True
    assert report.system_descriptor_status("clock-reset").passed is True
    assert device.connection_candidates
    assert device.connection_groups
    assert device.vector_slots
    assert device.startup_descriptors


def test_validation_fails_gate_c_when_route_candidate_references_unknown_requirement(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    candidate = original_device.connection_candidates[0]
    broken_candidate = type(candidate)(
        candidate_id=candidate.candidate_id,
        pin=candidate.pin,
        peripheral=candidate.peripheral,
        signal=candidate.signal,
        route_kind=candidate.route_kind,
        route_selector=candidate.route_selector,
        route_group_id=candidate.route_group_id,
        requirement_ids=("requirement:missing",),
        operation_ids=candidate.operation_ids,
        capability_ids=candidate.capability_ids,
        provenance=candidate.provenance,
    )
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=(broken_candidate,) + original_device.connection_candidates[1:],
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-connection-candidates-reference-known-requirements" in failing_rules


def test_validation_fails_gate_c_when_pin_gpio_mapping_is_invalid(
    execution_context: ExecutionContext,
) -> None:
    normalize_result = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = normalize_result.payload.devices[0]
    broken_pin = PinDefinition(
        name="PZ0",
        port="Z",
        number=0,
        signals=(),
        provenance=original_device.provenance,
    )
    broken_device = CanonicalDeviceIR(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=(broken_pin,),
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
    )

    report = build_validation_report(
        scope=normalize_result.scope,
        source_manifest=normalize_result.payload.source_manifest,
        patch_manifest=normalize_result.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-pin-port-has-gpio-peripheral" in failing_rules


def test_validation_fails_gate_c_when_referenced_peripheral_lacks_rcc_enable(
    execution_context: ExecutionContext,
) -> None:
    normalize_result = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = normalize_result.payload.devices[0]
    broken_peripherals = tuple(
        PeripheralInstance(
            name=peripheral.name,
            ip_name=peripheral.ip_name,
            ip_version=peripheral.ip_version,
            instance=peripheral.instance,
            base_address=peripheral.base_address,
            rcc_enable_signal=None if peripheral.name == "USART1" else peripheral.rcc_enable_signal,
            rcc_reset_signal=peripheral.rcc_reset_signal,
            provenance=peripheral.provenance,
        )
        for peripheral in original_device.peripherals
    )
    broken_device = CanonicalDeviceIR(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=broken_peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
    )

    report = build_validation_report(
        scope=normalize_result.scope,
        source_manifest=normalize_result.payload.source_manifest,
        patch_manifest=normalize_result.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-referenced-peripherals-have-rcc-enable" in failing_rules


def test_validation_fails_gate_c_when_package_pad_references_unknown_pin(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    bad_pad = PackagePad(
        pad_id="BADPAD",
        package=original_device.identity.package,
        position_label="999",
        physical_index=999,
        pad_kind="io",
        bonded_pin="PZ99",
        provenance=original_device.provenance,
    )
    broken_device = CanonicalDeviceIR(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads + (bad_pad,),
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=original_device.connection_candidates,
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-package-pads-reference-known-pins" in failing_rules


def test_validation_fails_gate_c_when_bonded_pin_has_no_package_pad(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    filtered_pads = tuple(pad for pad in original_device.package_pads if pad.bonded_pin != "PA0")
    broken_device = CanonicalDeviceIR(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=filtered_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=original_device.connection_candidates,
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-bonded-pins-have-package-pad" in failing_rules


def test_validation_fails_gate_c_when_candidate_has_no_package_requirement(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    candidate = original_device.connection_candidates[0]
    broken_candidate = type(candidate)(
        candidate_id=candidate.candidate_id,
        pin=candidate.pin,
        peripheral=candidate.peripheral,
        signal=candidate.signal,
        route_kind=candidate.route_kind,
        route_selector=candidate.route_selector,
        route_group_id=candidate.route_group_id,
        requirement_ids=tuple(
            requirement_id
            for requirement_id in candidate.requirement_ids
            if not requirement_id.startswith("requirement:package:")
        ),
        operation_ids=candidate.operation_ids,
        capability_ids=candidate.capability_ids,
        provenance=candidate.provenance,
    )
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=(broken_candidate,) + original_device.connection_candidates[1:],
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-connection-candidates-carry-package-requirement" in failing_rules


def test_validation_fails_gate_c_when_candidate_has_no_source_requirement(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    candidate = next(
        candidate for candidate in original_device.connection_candidates if candidate.route_selector
    )
    broken_candidate = type(candidate)(
        candidate_id=candidate.candidate_id,
        pin=candidate.pin,
        peripheral=candidate.peripheral,
        signal=candidate.signal,
        route_kind=candidate.route_kind,
        route_selector=candidate.route_selector,
        route_group_id=candidate.route_group_id,
        requirement_ids=tuple(
            requirement_id
            for requirement_id in candidate.requirement_ids
            if not requirement_id.startswith("requirement:source-select:")
        ),
        operation_ids=candidate.operation_ids,
        capability_ids=candidate.capability_ids,
        provenance=candidate.provenance,
    )
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=(broken_candidate,)
        + tuple(
            item
            for item in original_device.connection_candidates
            if item.candidate_id != candidate.candidate_id
        ),
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-connection-candidates-carry-source-requirement" in failing_rules


def test_validation_fails_gate_c_when_candidate_capabilities_lack_instance_overlay(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    candidate = next(
        candidate
        for candidate in original_device.connection_candidates
        if any(
            capability_id.startswith("capability-instance:")
            for capability_id in candidate.capability_ids
        )
    )
    broken_candidate = type(candidate)(
        candidate_id=candidate.candidate_id,
        pin=candidate.pin,
        peripheral=candidate.peripheral,
        signal=candidate.signal,
        route_kind=candidate.route_kind,
        route_selector=candidate.route_selector,
        route_group_id=candidate.route_group_id,
        requirement_ids=candidate.requirement_ids,
        operation_ids=candidate.operation_ids,
        capability_ids=tuple(
            capability_id
            for capability_id in candidate.capability_ids
            if not capability_id.startswith("capability-instance:")
        ),
        provenance=candidate.provenance,
    )
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=(broken_candidate,)
        + tuple(
            item
            for item in original_device.connection_candidates
            if item.candidate_id != candidate.candidate_id
        ),
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-candidate-capabilities-resolve-from-descriptors" in failing_rules


def test_validation_fails_gate_c_when_group_signals_are_not_satisfiable(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    group = original_device.connection_groups[0]
    broken_group = type(group)(
        group_id=group.group_id,
        peripheral=group.peripheral,
        signals=group.signals + ("cts",),
        candidate_ids=group.candidate_ids,
        package=group.package,
        conflict_group=group.conflict_group,
        provenance=group.provenance,
    )
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=original_device.connection_candidates,
        connection_groups=(broken_group,) + original_device.connection_groups[1:],
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-connection-groups-have-satisfiable-signals" in failing_rules


def test_validation_fails_gate_c_when_group_candidate_lacks_bonded_package_requirement(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    group = next(group for group in original_device.connection_groups if group.candidate_ids)
    candidate_id = group.candidate_ids[0]
    candidate = next(
        candidate
        for candidate in original_device.connection_candidates
        if candidate.candidate_id == candidate_id
    )
    broken_candidate = type(candidate)(
        candidate_id=candidate.candidate_id,
        pin=candidate.pin,
        peripheral=candidate.peripheral,
        signal=candidate.signal,
        route_kind=candidate.route_kind,
        route_selector=candidate.route_selector,
        route_group_id=candidate.route_group_id,
        requirement_ids=tuple(
            requirement_id
            for requirement_id in candidate.requirement_ids
            if not requirement_id.startswith("requirement:bonded-pin:")
        ),
        operation_ids=candidate.operation_ids,
        capability_ids=candidate.capability_ids,
        provenance=candidate.provenance,
    )
    broken_candidates = tuple(
        broken_candidate if item.candidate_id == candidate_id else item
        for item in original_device.connection_candidates
    )
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=broken_candidates,
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-connection-groups-match-selected-package" in failing_rules


def test_family_scope_reports_multi_signal_groups_for_all_devices(
    execution_context: ExecutionContext,
) -> None:
    result = run_validate(PipelineScope(vendor="st", family="stm32g0"), execution_context)
    report = result.payload.report

    assert result.status == "completed"
    family_rule = next(
        rule
        for rule in report.results
        if rule.rule_id == "st-stm32g0-family-devices-expose-multi-signal-groups"
    )
    assert family_rule.passed is True


def test_family_scope_reports_ip_version_reuse_when_available(
    execution_context: ExecutionContext,
) -> None:
    result = run_validate(PipelineScope(vendor="st", family="stm32g0"), execution_context)
    report = result.payload.report

    assert result.status == "completed"
    family_rule = next(
        rule
        for rule in report.results
        if rule.rule_id == "st-stm32g0-family-reuses-ip-version-descriptors"
    )
    assert family_rule.passed is True


def test_validation_fails_gate_c_when_package_pad_bonding_is_inconsistent(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    original_pad = original_device.package_pads[0]
    broken_pad = PackagePad(
        pad_id=original_pad.pad_id,
        package=original_pad.package,
        position_label=original_pad.position_label,
        physical_index=original_pad.physical_index,
        pad_kind=original_pad.pad_kind,
        bonded_pin=None,
        provenance=original_pad.provenance,
        bonding_state="bonded",
    )
    broken_device = CanonicalDeviceIR(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=(broken_pad,) + original_device.package_pads[1:],
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=original_device.connection_candidates,
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-package-pad-bonding-state-consistent" in failing_rules


def test_validation_fails_gate_c_when_memory_lacks_startup_roles(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    broken_memories = tuple(
        type(memory)(
            name=memory.name,
            kind=memory.kind,
            base_address=memory.base_address,
            size_bytes=memory.size_bytes,
            access=memory.access,
            provenance=memory.provenance,
            startup_roles=(),
        )
        for memory in original_device.memories
    )
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=broken_memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=original_device.connection_candidates,
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-memory-regions-carry-startup-roles" in failing_rules


def test_validation_fails_gate_c_when_system_vector_baseline_is_missing(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=original_device.connection_candidates,
        connection_groups=original_device.connection_groups,
        vector_slots=tuple(
            vector_slot for vector_slot in original_device.vector_slots if vector_slot.slot != 1
        ),
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    assert "startup" in report.draft_system_descriptor_domains
    assert report.system_descriptor_status("startup").draft is True
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-vector-slots-include-system-baseline" in failing_rules
    assert "stm32g071rb-startup-descriptors-emit-without-handwritten-tables" in failing_rules


def test_validation_fails_gate_c_when_interrupt_shared_group_is_not_shared(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    interrupt = original_device.interrupts[0]
    broken_interrupt = type(interrupt)(
        name=interrupt.name,
        line=interrupt.line,
        peripheral=interrupt.peripheral,
        provenance=interrupt.provenance,
        shared_group="interrupt-group:fake",
        alias_names=interrupt.alias_names,
    )
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=(broken_interrupt,) + original_device.interrupts[1:],
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=original_device.connection_candidates,
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-interrupt-shared-groups-consistent" in failing_rules


def test_validation_fails_gate_c_when_dma_controller_channel_count_is_missing(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    controller = original_device.dma_controllers[0]
    broken_controller = type(controller)(
        controller=controller.controller,
        version=controller.version,
        channel_count=None,
        request_count=controller.request_count,
        provenance=controller.provenance,
    )
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=original_device.connection_candidates,
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=(broken_controller,) + original_device.dma_controllers[1:],
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-dma-controller-descriptors-complete" in failing_rules


def test_validation_fails_gate_c_when_dma_controller_request_count_is_missing(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    controller = original_device.dma_controllers[0]
    broken_controller = type(controller)(
        controller=controller.controller,
        version=controller.version,
        channel_count=controller.channel_count,
        request_count=None,
        provenance=controller.provenance,
    )
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=original_device.connection_candidates,
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=original_device.clock_selectors,
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=(broken_controller,) + original_device.dma_controllers[1:],
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-dma-controller-descriptors-complete" in failing_rules


def test_validation_fails_gate_c_when_clock_selector_references_unknown_parent(
    execution_context: ExecutionContext,
) -> None:
    validated = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = validated.payload.devices[0]
    selector = next(
        selector
        for selector in original_device.clock_selectors
        if selector.selector_id == "selector:usart1-kernel"
    )
    broken_selector = type(selector)(
        selector_id=selector.selector_id,
        parent_options=("clock-node:missing-parent",),
        register_target=selector.register_target,
        provenance=selector.provenance,
    )
    broken_device = type(original_device)(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
        ip_blocks=original_device.ip_blocks,
        capabilities=original_device.capabilities,
        package_pads=original_device.package_pads,
        pin_constraints=original_device.pin_constraints,
        signal_endpoints=original_device.signal_endpoints,
        route_requirements=original_device.route_requirements,
        route_operations=original_device.route_operations,
        connection_candidates=original_device.connection_candidates,
        connection_groups=original_device.connection_groups,
        vector_slots=original_device.vector_slots,
        startup_descriptors=original_device.startup_descriptors,
        clock_nodes=original_device.clock_nodes,
        clock_selectors=(broken_selector,)
        + tuple(
            candidate
            for candidate in original_device.clock_selectors
            if candidate.selector_id != selector.selector_id
        ),
        clock_gates=original_device.clock_gates,
        resets=original_device.resets,
        peripheral_clock_bindings=original_device.peripheral_clock_bindings,
        dma_controllers=original_device.dma_controllers,
        dma_routes=original_device.dma_routes,
        dma_conflict_groups=original_device.dma_conflict_groups,
    )

    report = build_validation_report(
        scope=validated.scope,
        source_manifest=validated.payload.source_manifest,
        patch_manifest=validated.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-clock-selectors-structured" in failing_rules
