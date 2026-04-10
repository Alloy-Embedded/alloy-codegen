"""Validation rules and gate evaluation for the bootstrap pipeline."""

from __future__ import annotations

from collections import Counter

from alloy_codegen.bootstrap import source_bundle_for
from alloy_codegen.connector_model import (
    canonical_peripheral_class,
    canonical_signal_role,
    ensure_connector_descriptors,
)
from alloy_codegen.ir.model import CanonicalDeviceIR, RouteRequirement
from alloy_codegen.manifests import PatchManifest, SourceManifest
from alloy_codegen.reporting import ValidationGateStatus, ValidationReport, ValidationRuleResult
from alloy_codegen.scope import PipelineScope


def _rule(
    *,
    rule_id: str,
    category: str,
    severity: str,
    passed: bool,
    message: str,
) -> ValidationRuleResult:
    return ValidationRuleResult(
        rule_id=rule_id,
        category=category,
        severity=severity,
        passed=passed,
        message=message,
    )


def _evaluate_gate(
    *,
    gate_id: str,
    blocking: bool,
    results: tuple[ValidationRuleResult, ...],
) -> ValidationGateStatus:
    passed = all(result.passed for result in results if result.severity == "error")
    return ValidationGateStatus(
        gate_id=gate_id,
        passed=passed,
        blocking=blocking,
        message=f"{gate_id} {'passed' if passed else 'failed'} with {len(results)} rule(s).",
        rule_ids=tuple(result.rule_id for result in results),
    )


def _node_reaches_root(
    node_id: str,
    parent_map: dict[str, str | None],
) -> bool:
    seen: set[str] = set()
    current = node_id
    while True:
        if current in seen:
            return False
        seen.add(current)
        parent = parent_map.get(current)
        if parent is None:
            return current == "clock-root"
        current = parent


def _validate_source_manifest(source_manifest: SourceManifest) -> tuple[ValidationRuleResult, ...]:
    revisions = {source.revision for source in source_manifest.sources}
    local_paths = [source.local_path for source in source_manifest.sources]
    target_devices = {source.target_device for source in source_manifest.sources}
    target_coverage = {
        target: {
            source.source_id for source in source_manifest.sources if source.target_device == target
        }
        for target in source_manifest.targets
    }
    scope = next((source.scope for source in source_manifest.sources), None)
    expected_source_ids = (
        set(
            source_bundle_for(
                str(scope["vendor"]),
                str(scope["family"]),
            )
        )
        if scope is not None
        else set()
    )
    return (
        _rule(
            rule_id="source-records-cover-targets",
            category="schema",
            severity="error",
            passed=target_devices == set(source_manifest.targets),
            message="Source records cover every requested bootstrap target.",
        ),
        _rule(
            rule_id="source-records-provide-required-upstreams",
            category="schema",
            severity="error",
            passed=all(
                bool(target_coverage[target]) and target_coverage[target] <= expected_source_ids
                for target in source_manifest.targets
            ),
            message="Every target carries records drawn from the declared family source bundle.",
        ),
        _rule(
            rule_id="source-records-have-revisions",
            category="schema",
            severity="error",
            passed=all(bool(revision) and revision != "unknown" for revision in revisions),
            message="All source records carry a concrete upstream revision.",
        ),
        _rule(
            rule_id="source-records-have-local-paths",
            category="schema",
            severity="error",
            passed=all(bool(path) for path in local_paths),
            message="All source records expose a resolved local path.",
        ),
    )


def _validate_patch_manifest(
    patch_manifest: PatchManifest,
    source_manifest: SourceManifest,
) -> tuple[ValidationRuleResult, ...]:
    target_count = len(source_manifest.targets)
    patch_count = len(patch_manifest.applied_patches)
    patch_ids = [patch.patch_id for patch in patch_manifest.applied_patches]
    return (
        _rule(
            rule_id="patch-target-count-match",
            category="schema",
            severity="error",
            passed=target_count == patch_count,
            message=f"Found {patch_count} patch record(s) for {target_count} target(s).",
        ),
        _rule(
            rule_id="patch-ids-unique",
            category="schema",
            severity="error",
            passed=len(patch_ids) == len(set(patch_ids)),
            message="Patch identifiers are unique within the requested scope.",
        ),
    )


def _validate_device_structure(device: CanonicalDeviceIR) -> tuple[ValidationRuleResult, ...]:
    return (
        _rule(
            rule_id=f"{device.identity.device}-schema-version-present",
            category="schema",
            severity="error",
            passed=bool(device.schema_version),
            message=f"{device.identity.device} declares an IR schema version.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-identity-fields-present",
            category="schema",
            severity="error",
            passed=all(
                bool(value)
                for value in (
                    device.identity.vendor,
                    device.identity.family,
                    device.identity.device,
                    device.identity.package,
                    device.identity.core,
                )
            ),
            message=f"{device.identity.device} exposes the required canonical identity fields.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-required-sections-present",
            category="schema",
            severity="error",
            passed=all(
                (
                    bool(device.memories),
                    bool(device.packages),
                    bool(device.pins),
                    bool(device.peripherals),
                )
            ),
            message=f"{device.identity.device} contains non-empty required canonical sections.",
        ),
    )


def _validate_device_semantics(device: CanonicalDeviceIR) -> tuple[ValidationRuleResult, ...]:
    package_pin_count = max((package.pin_count for package in device.packages), default=0)
    peripheral_names = {peripheral.name for peripheral in device.peripherals}
    peripheral_map = {peripheral.name: peripheral for peripheral in device.peripherals}
    pin_gpio_matches = all(
        pin.port is None or f"GPIO{pin.port}" in peripheral_names for pin in device.pins
    )
    memory_sizes_positive = all(memory.size_bytes > 0 for memory in device.memories)
    peripheral_bases = [peripheral.base_address for peripheral in device.peripherals]
    duplicate_peripheral_bases = [
        base for base, count in Counter(peripheral_bases).items() if count > 1
    ]
    pin_signals_present = all(bool(pin.signals) for pin in device.pins)
    signal_peripheral_matches = all(
        signal.peripheral is None or signal.peripheral in peripheral_names
        for pin in device.pins
        for signal in pin.signals
    )
    alternate_functions_explicit = all(
        signal.peripheral is None
        or signal.peripheral.startswith("GPIO")
        or signal.af_number is not None
        for pin in device.pins
        for signal in pin.signals
    )
    referenced_peripherals = {
        signal.peripheral
        for pin in device.pins
        for signal in pin.signals
        if signal.peripheral is not None
    }
    referenced_peripherals.update(
        request.peripheral for request in device.dma_requests if request.peripheral is not None
    )
    referenced_peripherals.update(request.controller for request in device.dma_requests)
    referenced_peripherals_have_rcc = all(
        peripheral_map.get(name) is not None and peripheral_map[name].rcc_enable_signal is not None
        for name in referenced_peripherals
    )
    interrupt_peripherals_known = all(
        interrupt.peripheral is None or interrupt.peripheral in peripheral_names
        for interrupt in device.interrupts
    )
    dma_controllers_known = all(
        request.controller in peripheral_names for request in device.dma_requests
    )
    dma_request_peripherals_known = all(
        request.peripheral is None or request.peripheral in peripheral_names
        for request in device.dma_requests
    )
    dma_route_keys = [(request.controller, request.request_line) for request in device.dma_requests]
    duplicate_dma_routes = [route for route, count in Counter(dma_route_keys).items() if count > 1]

    return (
        _rule(
            rule_id=f"{device.identity.device}-package-pin-count-covers-known-pins",
            category="semantic",
            severity="error",
            passed=package_pin_count >= len(device.pins),
            message=(
                f"{device.identity.device} package pin count {package_pin_count} covers "
                f"{len(device.pins)} known pin definition(s)."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-pin-port-has-gpio-peripheral",
            category="semantic",
            severity="error",
            passed=pin_gpio_matches,
            message=f"{device.identity.device} pin ports map to discovered GPIO peripherals.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-pin-signals-present",
            category="semantic",
            severity="error",
            passed=pin_signals_present,
            message=f"{device.identity.device} curated pins expose explicit signal metadata.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-pin-signals-reference-known-peripherals",
            category="semantic",
            severity="error",
            passed=signal_peripheral_matches,
            message=f"{device.identity.device} pin signals only reference discovered peripherals.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-alternate-functions-explicit",
            category="semantic",
            severity="error",
            passed=alternate_functions_explicit,
            message=(
                f"{device.identity.device} non-GPIO alternate functions carry explicit AF numbers."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-memory-sizes-positive",
            category="semantic",
            severity="error",
            passed=memory_sizes_positive,
            message=f"{device.identity.device} memory regions use positive non-placeholder sizes.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-peripheral-bases-unique",
            category="semantic",
            severity="error",
            passed=not duplicate_peripheral_bases,
            message=f"{device.identity.device} peripheral base addresses are unique.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-interrupts-present",
            category="semantic",
            severity="error",
            passed=bool(device.interrupts),
            message=f"{device.identity.device} exposes interrupt metadata from the raw source.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-interrupts-reference-known-peripherals",
            category="semantic",
            severity="error",
            passed=interrupt_peripherals_known,
            message=(
                f"{device.identity.device} interrupt entries only reference discovered peripherals."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-referenced-peripherals-have-rcc-enable",
            category="semantic",
            severity="error",
            passed=referenced_peripherals_have_rcc,
            message=f"{device.identity.device} referenced peripherals expose RCC enable ownership.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-controllers-known",
            category="semantic",
            severity="error",
            passed=dma_controllers_known,
            message=(
                f"{device.identity.device} DMA requests reference known controller peripherals."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-request-peripherals-known",
            category="semantic",
            severity="error",
            passed=dma_request_peripherals_known,
            message=f"{device.identity.device} DMA requests reference known target peripherals.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-routes-unique",
            category="semantic",
            severity="error",
            passed=not duplicate_dma_routes,
            message=f"{device.identity.device} DMA controller/request-line pairs are unique.",
        ),
    )


def _validate_descriptor_semantics(device: CanonicalDeviceIR) -> tuple[ValidationRuleResult, ...]:
    pin_names = {pin.name for pin in device.pins}
    peripheral_names = {peripheral.name for peripheral in device.peripherals}
    peripheral_map = {peripheral.name: peripheral for peripheral in device.peripherals}
    package_names = {package.name for package in device.packages}
    package_pad_ids = {pad.pad_id for pad in device.package_pads}
    package_position_keys = [(pad.package, pad.position_label) for pad in device.package_pads]
    bonded_pin_names = {
        pad.bonded_pin
        for pad in device.package_pads
        if pad.bonding_state == "bonded" and pad.bonded_pin is not None
    }
    requirement_ids = {requirement.requirement_id for requirement in device.route_requirements}
    requirement_map = {
        requirement.requirement_id: requirement for requirement in device.route_requirements
    }
    operation_ids = {operation.operation_id for operation in device.route_operations}
    capability_ids = {capability.capability_id for capability in device.capabilities}
    capability_lookup = {
        capability.capability_id: capability for capability in device.capabilities
    }
    candidate_ids = {candidate.candidate_id for candidate in device.connection_candidates}
    candidate_lookup = {
        candidate.candidate_id: candidate for candidate in device.connection_candidates
    }
    group_ids = {group.group_id for group in device.connection_groups}
    interrupt_names = {interrupt.name for interrupt in device.interrupts}
    shared_interrupt_groups: dict[str, list[object]] = {}
    for interrupt in device.interrupts:
        if interrupt.shared_group is not None:
            shared_interrupt_groups.setdefault(interrupt.shared_group, []).append(interrupt)
    memory_names = {memory.name for memory in device.memories}
    clock_node_ids = {node.node_id for node in device.clock_nodes}
    clock_gate_ids = {gate.gate_id for gate in device.clock_gates}
    reset_ids = {reset.reset_id for reset in device.resets}
    selector_ids = {selector.selector_id for selector in device.clock_selectors}
    dma_controller_ids = {controller.controller for controller in device.dma_controllers}
    dma_route_ids = {route.route_id for route in device.dma_routes}
    dma_conflict_ids = {group.conflict_group_id for group in device.dma_conflict_groups}
    ip_block_ids = {(block.ip_name, block.ip_version) for block in device.ip_blocks}

    def _candidate_requirements(candidate_id: str) -> tuple[RouteRequirement, ...]:
        candidate = candidate_lookup.get(candidate_id)
        if candidate is None:
            return ()
        return tuple(
            requirement_map[requirement_id]
            for requirement_id in candidate.requirement_ids
            if requirement_id in requirement_map
        )

    package_pads_present = bool(device.package_pads)
    package_pad_ids_unique = len(package_pad_ids) == len(device.package_pads)
    package_pads_reference_known_packages = all(
        pad.package in package_names for pad in device.package_pads
    )
    package_variants_have_pad_coverage = all(
        any(pad.package == package_name for pad in device.package_pads)
        for package_name in package_names
    )
    package_pad_positions_unique = len(package_position_keys) == len(set(package_position_keys))
    package_pad_bonding_consistent = all(
        (
            pad.bonding_state == "bonded"
            and pad.bonded_pin is not None
        )
        or (
            pad.bonding_state in {"dedicated", "unbonded"}
            and pad.bonded_pin is None
        )
        for pad in device.package_pads
    )
    package_pads_reference_known_pins = all(
        pad.bonded_pin is None or pad.bonded_pin in pin_names for pad in device.package_pads
    )
    bonded_pins_have_package_pad = pin_names <= bonded_pin_names
    signal_endpoints_present = bool(device.signal_endpoints)
    connection_candidates_present = bool(device.connection_candidates)
    candidate_pin_refs_known = all(
        candidate.pin in pin_names for candidate in device.connection_candidates
    )
    candidate_peripherals_known = all(
        candidate.peripheral in peripheral_names for candidate in device.connection_candidates
    )
    candidate_group_refs_known = all(
        candidate.route_group_id is None or candidate.route_group_id in group_ids
        for candidate in device.connection_candidates
    )
    candidate_requirements_known = all(
        requirement_id in requirement_ids
        for candidate in device.connection_candidates
        for requirement_id in candidate.requirement_ids
    )
    candidate_package_requirements_known = all(
        any(
            requirement_id in requirement_map
            and requirement_map[requirement_id].kind == "package"
            and requirement_map[requirement_id].target == device.identity.package
            for requirement_id in candidate.requirement_ids
        )
        for candidate in device.connection_candidates
    )
    candidate_source_requirements_known = all(
        candidate.route_selector is None
        or any(
            requirement.kind == "source-select"
            and requirement.value == candidate.route_selector
            for requirement in _candidate_requirements(candidate.candidate_id)
        )
        for candidate in device.connection_candidates
    )
    candidate_operations_known = all(
        operation_id in operation_ids
        for candidate in device.connection_candidates
        for operation_id in candidate.operation_ids
    )
    candidate_capabilities_known = all(
        capability_id in capability_ids
        for candidate in device.connection_candidates
        for capability_id in candidate.capability_ids
    )
    capability_descriptors_structured = all(
        (
            capability.scope == "ip-block"
            and capability.ip_name is not None
            and capability.ip_version is not None
            and capability.peripheral is None
            and capability.package is None
        )
        or (
            capability.scope == "instance-overlay"
            and capability.peripheral is not None
            and capability.package is not None
        )
        for capability in device.capabilities
    )
    candidate_capabilities_descriptor_resolved = all(
        (
            not candidate.capability_ids
            or any(
                capability_lookup[capability_id].scope == "instance-overlay"
                and capability_lookup[capability_id].peripheral == candidate.peripheral
                and capability_lookup[capability_id].package == device.identity.package
                for capability_id in candidate.capability_ids
                if capability_id in capability_lookup
            )
        )
        and (
            peripheral_map[candidate.peripheral].ip_version is None
            or any(
                capability_lookup[capability_id].scope == "ip-block"
                and capability_lookup[capability_id].ip_name
                == peripheral_map[candidate.peripheral].ip_name
                and capability_lookup[capability_id].ip_version
                == peripheral_map[candidate.peripheral].ip_version
                for capability_id in candidate.capability_ids
                if capability_id in capability_lookup
            )
        )
        for candidate in device.connection_candidates
        if candidate.peripheral in peripheral_map
    )
    group_candidates_known = all(
        candidate_id in candidate_ids
        for group in device.connection_groups
        for candidate_id in group.candidate_ids
    )
    group_signals_satisfiable = all(
        set(group.signals)
        <= {
            signal
            for candidate_id in group.candidate_ids
            if (candidate := candidate_lookup.get(candidate_id)) is not None
            for signal in (
                candidate.signal,
                canonical_signal_role(
                    canonical_peripheral_class(peripheral_map[group.peripheral].ip_name),
                    candidate.signal,
                ),
            )
            if signal is not None
        }
        for group in device.connection_groups
        if group.peripheral in peripheral_map
    )
    group_packages_known = all(
        group.package is None or group.package in package_names
        for group in device.connection_groups
    )
    group_packages_match_selected_package = all(
        group.package in {None, device.identity.package}
        for group in device.connection_groups
    )
    group_candidates_match_selected_package = all(
        all(
            any(
                requirement.kind == "package"
                and requirement.target == (group.package or device.identity.package)
                for requirement in _candidate_requirements(candidate_id)
            )
            and (
                candidate_lookup[candidate_id].pin not in bonded_pin_names
                or any(
                    requirement.kind == "bonded-pin"
                    and requirement.target == candidate_lookup[candidate_id].pin
                    and requirement.value == (group.package or device.identity.package)
                    for requirement in _candidate_requirements(candidate_id)
                )
            )
            for candidate_id in group.candidate_ids
            if candidate_id in candidate_lookup
        )
        for group in device.connection_groups
    )
    multi_signal_groups_present = any(len(group.signals) >= 2 for group in device.connection_groups)
    ip_blocks_resolve_instance_versions = all(
        peripheral.ip_version is None or (peripheral.ip_name, peripheral.ip_version) in ip_block_ids
        for peripheral in device.peripherals
    )
    interrupt_aliases_present = all(interrupt.alias_names for interrupt in device.interrupts)
    interrupt_aliases_unique = all(
        len(interrupt.alias_names) == len(set(interrupt.alias_names))
        for interrupt in device.interrupts
    )
    interrupt_shared_groups_consistent = all(
        len(interrupts) >= 2
        and all(interrupt.peripheral == interrupts[0].peripheral for interrupt in interrupts)
        and interrupts[0].peripheral is not None
        for interrupts in shared_interrupt_groups.values()
    )
    vector_slots_reference_known_interrupts = all(
        vector_slot.interrupt is None or vector_slot.interrupt in interrupt_names
        for vector_slot in device.vector_slots
    )
    vector_slot_sequence = [vector_slot.slot for vector_slot in device.vector_slots]
    vector_slots_unique = len(vector_slot_sequence) == len(set(vector_slot_sequence))
    interrupts_have_vector_slot = {
        vector_slot.interrupt
        for vector_slot in device.vector_slots
        if vector_slot.interrupt is not None
    } >= interrupt_names
    vector_slot_numbers = {vector_slot.slot for vector_slot in device.vector_slots}
    system_vector_baseline_present = {0, 1, 2, 3, 11, 14, 15} <= vector_slot_numbers
    memory_regions_carry_startup_roles = any(memory.startup_roles for memory in device.memories)
    startup_descriptors_are_present = bool(device.startup_descriptors)
    startup_descriptors_reference_known_memories = all(
        descriptor.source_region is None or descriptor.source_region in memory_names
        for descriptor in device.startup_descriptors
    ) and all(
        descriptor.target_region is None or descriptor.target_region in memory_names
        for descriptor in device.startup_descriptors
    )
    startup_descriptors_cover_memory_roles = all(
        (
            "vector-source" not in memory.startup_roles
            or any(
                descriptor.kind == "vector-source-region"
                and descriptor.source_region == memory.name
                for descriptor in device.startup_descriptors
            )
        )
        and (
            "copy-source" not in memory.startup_roles
            or any(
                descriptor.kind == "copy-source-region"
                and descriptor.source_region == memory.name
                for descriptor in device.startup_descriptors
            )
        )
        and (
            "copy-target" not in memory.startup_roles
            or any(
                descriptor.kind == "copy-target-region"
                and descriptor.target_region == memory.name
                for descriptor in device.startup_descriptors
            )
        )
        and (
            "zero-target" not in memory.startup_roles
            or any(
                descriptor.kind == "zero-target-region"
                and descriptor.target_region == memory.name
                for descriptor in device.startup_descriptors
            )
        )
        and (
            "retained-target" not in memory.startup_roles
            or any(
                descriptor.kind == "retained-region"
                and descriptor.target_region == memory.name
                for descriptor in device.startup_descriptors
            )
        )
        for memory in device.memories
    )
    startup_descriptors_include_runtime_baseline = all(
        any(descriptor.kind == required_kind for descriptor in device.startup_descriptors)
        for required_kind in ("vector-table", "initial-stack-pointer")
    )
    clock_parent_map = {node.node_id: node.parent for node in device.clock_nodes}
    clock_node_parents_known = all(
        node.parent is None or node.parent in clock_node_ids
        for node in device.clock_nodes
    )
    clock_graph_root_reachable = all(
        _node_reaches_root(node.node_id, clock_parent_map)
        for node in device.clock_nodes
    )
    clock_selectors_structured = all(
        bool(selector.parent_options)
        for selector in device.clock_selectors
    )
    clock_gates_reference_known_nodes = all(
        gate.parent_node is None or gate.parent_node in clock_node_ids
        for gate in device.clock_gates
    )
    clock_bound_peripherals_covered = all(
        peripheral.name in {binding.peripheral for binding in device.peripheral_clock_bindings}
        for peripheral in device.peripherals
        if peripheral.rcc_enable_signal is not None or peripheral.rcc_reset_signal is not None
    )
    clock_bindings_reference_known_descriptors = all(
        (binding.clock_gate_id is None or binding.clock_gate_id in clock_gate_ids)
        and (binding.reset_id is None or binding.reset_id in reset_ids)
        and (binding.selector_id is None or binding.selector_id in selector_ids)
        for binding in device.peripheral_clock_bindings
    )
    dma_route_keys = {
        (route.controller, route.request_line, route.peripheral, route.signal)
        for route in device.dma_routes
    }
    dma_request_keys = {
        (request.controller, request.request_line, request.peripheral, request.signal)
        for request in device.dma_requests
    }
    dma_controller_descriptors_complete = all(
        controller.channel_count is not None
        and controller.channel_count > 0
        and controller.request_count is not None
        and controller.request_count > 0
        for controller in device.dma_controllers
    )
    dma_controller_request_counts_match = all(
        controller.request_count
        == sum(1 for route in device.dma_routes if route.controller == controller.controller)
        for controller in device.dma_controllers
    )
    dma_routes_cover_requests = dma_route_keys == dma_request_keys
    dma_routes_reference_known_controllers = all(
        route.controller in dma_controller_ids for route in device.dma_routes
    )
    dma_routes_reference_known_peripherals = all(
        route.peripheral is None or route.peripheral in peripheral_names
        for route in device.dma_routes
    )
    dma_routes_reference_known_conflicts = all(
        route.conflict_group is None or route.conflict_group in dma_conflict_ids
        for route in device.dma_routes
    )
    dma_conflict_groups_reference_known_routes = all(
        route_id in dma_route_ids
        for conflict_group in device.dma_conflict_groups
        for route_id in conflict_group.route_ids
    )
    dma_conflict_groups_nontrivial = all(
        len(conflict_group.route_ids) >= 2 for conflict_group in device.dma_conflict_groups
    )
    dma_route_conflict_annotations_consistent = all(
        (
            route.conflict_group is None
            and not any(route.route_id in group.route_ids for group in device.dma_conflict_groups)
        )
        or (
            route.conflict_group is not None
            and any(
                group.conflict_group_id == route.conflict_group
                and route.route_id in group.route_ids
                for group in device.dma_conflict_groups
            )
        )
        for route in device.dma_routes
    )

    return (
        _rule(
            rule_id=f"{device.identity.device}-package-pads-present",
            category="semantic",
            severity="error",
            passed=package_pads_present,
            message=f"{device.identity.device} exposes package pad descriptors.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-package-pad-ids-unique",
            category="semantic",
            severity="error",
            passed=package_pad_ids_unique,
            message=f"{device.identity.device} package pad identifiers are unique.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-package-pads-reference-known-packages",
            category="semantic",
            severity="error",
            passed=package_pads_reference_known_packages,
            message=f"{device.identity.device} package pads reference declared packages.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-package-variants-have-pad-coverage",
            category="semantic",
            severity="error",
            passed=package_variants_have_pad_coverage,
            message=f"{device.identity.device} every declared package exposes package pads.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-package-pad-positions-unique",
            category="semantic",
            severity="error",
            passed=package_pad_positions_unique,
            message=f"{device.identity.device} package pad positions are unique per package.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-package-pad-bonding-state-consistent",
            category="semantic",
            severity="error",
            passed=package_pad_bonding_consistent,
            message=(
                f"{device.identity.device} package pad bonding state matches bonded-pin coverage."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-package-pads-reference-known-pins",
            category="semantic",
            severity="error",
            passed=package_pads_reference_known_pins,
            message=f"{device.identity.device} package pads reference declared bonded pins.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-bonded-pins-have-package-pad",
            category="semantic",
            severity="error",
            passed=bonded_pins_have_package_pad,
            message=(
                f"{device.identity.device} every declared GPIO pin is covered "
                "by a package pad."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-signal-endpoints-present",
            category="semantic",
            severity="error",
            passed=signal_endpoints_present,
            message=f"{device.identity.device} exposes canonical signal endpoints.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-candidates-present",
            category="semantic",
            severity="error",
            passed=connection_candidates_present,
            message=f"{device.identity.device} exposes route-driven connection candidates.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-candidates-reference-known-pins",
            category="semantic",
            severity="error",
            passed=candidate_pin_refs_known,
            message=f"{device.identity.device} connection candidates reference known pins.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-candidates-reference-known-peripherals",
            category="semantic",
            severity="error",
            passed=candidate_peripherals_known,
            message=f"{device.identity.device} connection candidates reference known peripherals.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-candidates-reference-known-groups",
            category="semantic",
            severity="error",
            passed=candidate_group_refs_known,
            message=f"{device.identity.device} connection candidates reference known route groups.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-candidates-reference-known-requirements",
            category="semantic",
            severity="error",
            passed=candidate_requirements_known,
            message=(
                f"{device.identity.device} route candidates only reference "
                "declared requirements."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-candidates-carry-package-requirement",
            category="semantic",
            severity="error",
            passed=candidate_package_requirements_known,
            message=(
                f"{device.identity.device} route candidates carry an explicit "
                "package requirement."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-candidates-carry-source-requirement",
            category="semantic",
            severity="error",
            passed=candidate_source_requirements_known,
            message=(
                f"{device.identity.device} route candidates with selectors carry "
                "an explicit source-selection requirement."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-candidates-reference-known-operations",
            category="semantic",
            severity="error",
            passed=candidate_operations_known,
            message=(
                f"{device.identity.device} route candidates only reference "
                "declared operations."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-candidates-reference-known-capabilities",
            category="semantic",
            severity="error",
            passed=candidate_capabilities_known,
            message=(
                f"{device.identity.device} route candidates only reference "
                "declared capabilities."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-capability-descriptors-carry-context",
            category="semantic",
            severity="error",
            passed=capability_descriptors_structured,
            message=(
                f"{device.identity.device} capability descriptors carry explicit "
                "ip-block or instance-overlay context."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-candidate-capabilities-resolve-from-descriptors",
            category="semantic",
            severity="error",
            passed=candidate_capabilities_descriptor_resolved,
            message=(
                f"{device.identity.device} candidate capabilities resolve through "
                "ip-block and instance-overlay descriptors."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-groups-reference-known-candidates",
            category="semantic",
            severity="error",
            passed=group_candidates_known,
            message=f"{device.identity.device} route groups only reference declared candidates.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-groups-match-selected-package",
            category="semantic",
            severity="error",
            passed=(
                group_packages_match_selected_package
                and group_candidates_match_selected_package
            ),
            message=(
                f"{device.identity.device} route groups only admit candidates "
                "valid for the selected package and bonded pinout."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-groups-have-satisfiable-signals",
            category="semantic",
            severity="error",
            passed=group_signals_satisfiable,
            message=f"{device.identity.device} route groups declare satisfiable signal bundles.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-groups-reference-known-packages",
            category="semantic",
            severity="error",
            passed=group_packages_known,
            message=f"{device.identity.device} route groups only reference declared packages.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-multi-signal-connection-groups-present",
            category="semantic",
            severity="error",
            passed=multi_signal_groups_present,
            message=f"{device.identity.device} exposes at least one multi-signal connection group.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-ip-blocks-cover-versioned-instances",
            category="semantic",
            severity="error",
            passed=ip_blocks_resolve_instance_versions,
            message=f"{device.identity.device} IP block descriptors cover versioned instances.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-interrupts-carry-aliases",
            category="semantic",
            severity="error",
            passed=interrupt_aliases_present,
            message=f"{device.identity.device} interrupts carry explicit alias descriptors.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-interrupt-aliases-unique",
            category="semantic",
            severity="error",
            passed=interrupt_aliases_unique,
            message=f"{device.identity.device} interrupt aliases are unique per interrupt.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-interrupt-shared-groups-consistent",
            category="semantic",
            severity="error",
            passed=interrupt_shared_groups_consistent,
            message=(
                f"{device.identity.device} interrupt shared groups describe a real "
                "multi-interrupt owner."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-vector-slots-reference-known-interrupts",
            category="semantic",
            severity="error",
            passed=vector_slots_reference_known_interrupts,
            message=f"{device.identity.device} vector slots only reference declared interrupts.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-vector-slots-unique",
            category="semantic",
            severity="error",
            passed=vector_slots_unique,
            message=f"{device.identity.device} vector slot numbers are unique.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-interrupts-have-vector-slot",
            category="semantic",
            severity="error",
            passed=interrupts_have_vector_slot,
            message=f"{device.identity.device} every interrupt owns an external vector slot.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-vector-slots-include-system-baseline",
            category="semantic",
            severity="error",
            passed=system_vector_baseline_present,
            message=f"{device.identity.device} vector slots include the system baseline slots.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-memory-regions-carry-startup-roles",
            category="semantic",
            severity="error",
            passed=memory_regions_carry_startup_roles,
            message=(
                f"{device.identity.device} exposes startup-relevant memory classifications "
                "for at least one memory region."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-startup-descriptors-present",
            category="semantic",
            severity="error",
            passed=startup_descriptors_are_present,
            message=f"{device.identity.device} exposes startup descriptors separately from logic.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-startup-descriptors-reference-known-memories",
            category="semantic",
            severity="error",
            passed=startup_descriptors_reference_known_memories,
            message=(
                f"{device.identity.device} startup descriptors only reference "
                "declared memories."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-startup-descriptors-cover-memory-roles",
            category="semantic",
            severity="error",
            passed=startup_descriptors_cover_memory_roles,
            message=(
                f"{device.identity.device} startup descriptors cover every "
                "startup-classified memory region."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-startup-descriptors-include-runtime-baseline",
            category="semantic",
            severity="error",
            passed=startup_descriptors_include_runtime_baseline,
            message=(
                f"{device.identity.device} startup descriptors include vector-table "
                "and initial-stack-pointer facts."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-clock-bindings-reference-known-descriptors",
            category="semantic",
            severity="error",
            passed=clock_bindings_reference_known_descriptors,
            message=(
                f"{device.identity.device} clock bindings reference known "
                "gate/reset/selector descriptors."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-clock-node-parents-known",
            category="semantic",
            severity="error",
            passed=clock_node_parents_known,
            message=f"{device.identity.device} clock nodes only reference known parents.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-clock-graph-reaches-root",
            category="semantic",
            severity="error",
            passed=clock_graph_root_reachable,
            message=f"{device.identity.device} clock graph remains root-reachable and acyclic.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-clock-selectors-structured",
            category="semantic",
            severity="error",
            passed=clock_selectors_structured,
            message=(
                f"{device.identity.device} clock selectors expose at least one parent option "
                "when present."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-clock-gates-reference-known-nodes",
            category="semantic",
            severity="error",
            passed=clock_gates_reference_known_nodes,
            message=f"{device.identity.device} clock gates reference known clock nodes.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-clock-bound-peripherals-covered",
            category="semantic",
            severity="error",
            passed=clock_bound_peripherals_covered,
            message=(
                f"{device.identity.device} peripherals with enable/reset ownership "
                "have clock bindings."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-controller-descriptors-complete",
            category="semantic",
            severity="error",
            passed=dma_controller_descriptors_complete,
            message=(
                f"{device.identity.device} DMA controllers expose non-empty channel and "
                "request counts."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-controller-request-counts-match",
            category="semantic",
            severity="error",
            passed=dma_controller_request_counts_match,
            message=(
                f"{device.identity.device} DMA controller request counts match the normalized "
                "DMA route set."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-routes-cover-requests",
            category="semantic",
            severity="error",
            passed=dma_routes_cover_requests,
            message=f"{device.identity.device} DMA routes cover the normalized DMA request set.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-routes-reference-known-controllers",
            category="semantic",
            severity="error",
            passed=dma_routes_reference_known_controllers,
            message=f"{device.identity.device} DMA routes reference known controller descriptors.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-routes-reference-known-peripherals",
            category="semantic",
            severity="error",
            passed=dma_routes_reference_known_peripherals,
            message=f"{device.identity.device} DMA routes reference known target peripherals.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-routes-reference-known-conflicts",
            category="semantic",
            severity="error",
            passed=dma_routes_reference_known_conflicts,
            message=f"{device.identity.device} DMA routes reference declared conflict groups.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-conflict-groups-reference-known-routes",
            category="semantic",
            severity="error",
            passed=dma_conflict_groups_reference_known_routes,
            message=f"{device.identity.device} DMA conflict groups reference known DMA routes.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-conflict-groups-nontrivial",
            category="semantic",
            severity="error",
            passed=dma_conflict_groups_nontrivial,
            message=(
                f"{device.identity.device} DMA conflict groups only exist for true "
                "multi-route conflicts."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-route-conflict-annotations-consistent",
            category="semantic",
            severity="error",
            passed=dma_route_conflict_annotations_consistent,
            message=(
                f"{device.identity.device} DMA route conflict annotations match the declared "
                "conflict groups."
            ),
        ),
    )


def _validate_scope_semantics(
    scope: PipelineScope,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[ValidationRuleResult, ...]:
    if scope.device is not None or scope.family is None or not devices:
        return ()

    family_has_multi_signal_groups = all(
        any(len(group.signals) >= 2 for group in device.connection_groups)
        for device in devices
    )
    ip_block_usage: dict[tuple[str, str], set[str]] = {}
    for device in devices:
        for ip_block in device.ip_blocks:
            ip_block_usage.setdefault((ip_block.ip_name, ip_block.ip_version), set()).add(
                device.identity.device
            )
    families_with_versioned_ip = bool(ip_block_usage)
    family_reuses_ip_blocks = (
        not families_with_versioned_ip
        or any(len(device_names) >= 2 for device_names in ip_block_usage.values())
    )
    scope_label = (
        f"{scope.vendor}-{scope.family}"
        if scope.vendor is not None
        else str(scope.family)
    )
    return (
        _rule(
            rule_id=f"{scope_label}-family-devices-expose-multi-signal-groups",
            category="semantic",
            severity="error",
            passed=family_has_multi_signal_groups,
            message=(
                f"{scope_label} family scope exposes at least one multi-signal "
                "connection group for every normalized device."
            ),
        ),
        _rule(
            rule_id=f"{scope_label}-family-reuses-ip-version-descriptors",
            category="semantic",
            severity="error",
            passed=family_reuses_ip_blocks,
            message=(
                f"{scope_label} family scope reuses at least one ip-version "
                "descriptor across multiple devices when versioned IP data exist."
            ),
        ),
    )


def build_validation_report(
    *,
    scope: PipelineScope,
    source_manifest: SourceManifest,
    patch_manifest: PatchManifest,
    devices: tuple[CanonicalDeviceIR, ...],
) -> ValidationReport:
    """Build a structured validation report and gate statuses."""
    descriptor_devices = tuple(ensure_connector_descriptors(device) for device in devices)
    source_results = _validate_source_manifest(source_manifest)
    patch_results = _validate_patch_manifest(patch_manifest, source_manifest)
    schema_results = tuple(
        result for device in descriptor_devices for result in _validate_device_structure(device)
    )
    semantic_results = tuple(
        result
        for device in descriptor_devices
        for result in (_validate_device_semantics(device) + _validate_descriptor_semantics(device))
    ) + _validate_scope_semantics(scope, descriptor_devices)

    gate_a_results = source_results + patch_results
    gate_b_results = schema_results
    gate_c_results = semantic_results
    all_results = gate_a_results + gate_b_results + gate_c_results

    gates = (
        _evaluate_gate(gate_id="gate-a", blocking=False, results=gate_a_results),
        _evaluate_gate(gate_id="gate-b", blocking=False, results=gate_b_results),
        _evaluate_gate(gate_id="gate-c", blocking=True, results=gate_c_results),
    )

    return ValidationReport(
        report_id="bootstrap-validation-v1",
        scope=scope.to_dict(),
        results=all_results,
        gates=gates,
    )
