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
from alloy_codegen.reporting import (
    SystemDescriptorDomainStatus,
    ValidationGateStatus,
    ValidationReport,
    ValidationRuleResult,
)
from alloy_codegen.scope import PipelineScope


def _required_system_vector_slots(core: str) -> frozenset[int]:
    """Return the set of vector slot numbers that must be present for a given core.

    Cortex-M requires a fixed set of system exception slots (initial stack
    pointer, reset, NMI, HardFault, SVCall, PendSV, SysTick).  RISC-V and
    Xtensa only require the reset entry at slot 0.
    """
    normalized = core.lower()
    if normalized.startswith("cortex-m"):
        return frozenset({0, 1, 2, 3, 11, 14, 15})
    # RISC-V CLIC / Xtensa: flat interrupt model, only Reset_Handler (slot 0)
    # is part of the mandatory system baseline.
    return frozenset({0})


SYSTEM_DESCRIPTOR_RULE_SUFFIXES: dict[str, tuple[str, ...]] = {
    "interrupt": (
        "interrupts-reference-known-peripherals",
        "interrupt-aliases-present",
        "interrupt-aliases-unique",
        "interrupt-shared-groups-consistent",
        "interrupt-bindings-reference-known-peripherals",
        "interrupt-bindings-reference-known-interrupts",
        "interrupt-bindings-reference-known-vector-slots",
        "runtime-interrupt-bindings-present",
        "vector-slots-reference-known-interrupts",
        "vector-slots-unique",
        "interrupts-have-vector-slot",
    ),
    "memory": (
        "memory-sizes-positive",
        "memory-regions-carry-startup-roles",
    ),
    "startup": (
        "vector-slots-include-system-baseline",
        "startup-descriptors-present",
        "startup-descriptors-reference-known-memories",
        "startup-descriptors-cover-memory-roles",
        "startup-descriptors-include-runtime-baseline",
        "startup-descriptors-emit-without-handwritten-tables",
    ),
    "clock-reset": (
        "referenced-peripherals-have-rcc-enable",
        "clock-bindings-reference-known-descriptors",
        "clock-node-parents-known",
        "clock-graph-reaches-root",
        "clock-selectors-structured",
        "clock-gates-reference-known-nodes",
        "clock-bound-peripherals-covered",
    ),
    "dma": (
        "dma-controllers-known",
        "dma-request-peripherals-known",
        "dma-routes-unique",
        "dma-controller-descriptors-complete",
        "dma-controller-request-counts-match-routes",
        "dma-routes-cover-requests",
        "dma-routes-reference-known-controllers",
        "dma-routes-reference-known-peripherals",
        "dma-routes-reference-known-conflicts",
        "dma-bindings-reference-known-peripherals",
        "dma-bindings-reference-known-controllers",
        "dma-bindings-reference-known-routes",
        "dma-bindings-reference-known-conflicts",
        "dma-bindings-cover-routes",
        "dma-conflict-groups-reference-known-routes",
        "dma-conflict-groups-nontrivial",
        "dma-route-conflict-annotations-consistent",
    ),
    "package": (
        "package-pads-present",
        "package-pad-ids-unique",
        "package-pads-reference-known-packages",
        "package-variants-have-pad-coverage",
        "package-pad-positions-unique",
        "package-pad-bonding-consistent",
        "package-pads-reference-known-pins",
        "bonded-pins-have-package-pad",
    ),
}
RUNTIME_OWNED_PERIPHERAL_CLASSES = {"gpio", "uart"}


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


def _evaluate_system_descriptor_domains(
    results: tuple[ValidationRuleResult, ...],
) -> tuple[SystemDescriptorDomainStatus, ...]:
    statuses: list[SystemDescriptorDomainStatus] = []
    for domain_id, suffixes in SYSTEM_DESCRIPTOR_RULE_SUFFIXES.items():
        domain_results = tuple(result for result in results if result.rule_id.endswith(suffixes))
        passed = bool(domain_results) and all(
            result.passed for result in domain_results if result.severity == "error"
        )
        draft = not passed
        if not domain_results:
            message = f"{domain_id} domain is draft because no validation rules are registered."
        elif passed:
            message = f"{domain_id} domain is publishable with {len(domain_results)} rule(s)."
        else:
            failing_rule_ids = tuple(
                result.rule_id
                for result in domain_results
                if not result.passed and result.severity == "error"
            )
            message = (
                f"{domain_id} domain is draft because {len(failing_rule_ids)} "
                "blocking rule(s) failed."
            )
        statuses.append(
            SystemDescriptorDomainStatus(
                domain_id=domain_id,
                passed=passed,
                draft=draft,
                message=message,
                rule_ids=tuple(result.rule_id for result in domain_results),
            )
        )
    return tuple(statuses)


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
    # Pin→GPIO controller naming convention varies per vendor:
    # - ARM families use `GPIO<PORT>` (GPIOA, GPIOB, …)
    # - AVR uses `PORT<PORT>` (PORTA, PORTC, …)
    # Accept either to avoid forcing AVR to fake ARM-style names.
    pin_gpio_matches = all(
        pin.port is None
        or f"GPIO{pin.port}" in peripheral_names
        or f"PORT{pin.port}" in peripheral_names
        for pin in device.pins
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
        or canonical_peripheral_class(signal.peripheral) in {"adc", "dac", "comp", "opamp"}
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
    # DMA controllers are infrastructure (always-on bus masters) and do not
    # require a software-controlled clock-enable in all architectures.
    # Exclude them from the rcc_enable check so platforms like ESP32 — where
    # the GDMA/DMA peripheral is permanently clocked — do not fail validation.
    dma_controller_names = {request.controller for request in device.dma_requests}
    # Analog peripheral classes (ADC/DAC/comparators/opamps) often have a
    # dedicated analog-clock domain rather than a software-toggled RCC gate;
    # exempt them from the RCC-enable requirement when the canonical class
    # resolves to an analog class.
    analog_exempt_peripherals = {
        name
        for name in referenced_peripherals
        if name is not None
        and peripheral_map.get(name) is not None
        and canonical_peripheral_class(peripheral_map[name].ip_name)
        in {"adc", "dac", "comp", "opamp"}
    }
    rcc_check_peripherals = (
        referenced_peripherals - dma_controller_names - analog_exempt_peripherals
    )
    # AVR 8-bit parts do not expose a per-peripheral RCC enable signal in the
    # same style as ARM families — their CLKCTRL / PRR register flags are not
    # modelled until Phase 2.4 of add-microchip-avr-da-target.  Exempt AVR
    # cores from this rule so bootstrap ingestion does not require a fake
    # rcc_enable_signal on every peripheral.
    _rcc_exempt_core = device.identity.core.lower().startswith("avr")
    referenced_peripherals_have_rcc = _rcc_exempt_core or all(
        peripheral_map.get(name) is not None and peripheral_map[name].rcc_enable_signal is not None
        for name in rcc_check_peripherals
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
    capability_lookup = {capability.capability_id: capability for capability in device.capabilities}
    candidate_ids = {candidate.candidate_id for candidate in device.connection_candidates}
    candidate_lookup = {
        candidate.candidate_id: candidate for candidate in device.connection_candidates
    }
    group_ids = {group.group_id for group in device.connection_groups}
    interrupt_names = {interrupt.name for interrupt in device.interrupts}
    interrupt_counts_by_peripheral = Counter(
        interrupt.peripheral for interrupt in device.interrupts if interrupt.peripheral is not None
    )
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
        (pad.bonding_state == "bonded" and pad.bonded_pin is not None)
        or (pad.bonding_state in {"dedicated", "unbonded"} and pad.bonded_pin is None)
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
            and requirement_map[requirement_id].target_ref_kind == "package"
            and requirement_map[requirement_id].target_ref_id == device.identity.package
            for requirement_id in candidate.requirement_ids
        )
        for candidate in device.connection_candidates
    )
    candidate_source_requirements_known = all(
        candidate.route_selector is None
        or any(
            requirement.kind == "source-select"
            and requirement.value_ref_kind == "selector"
            and requirement.value_ref_id == candidate.route_selector
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
        group.package in {None, device.identity.package} for group in device.connection_groups
    )
    group_candidates_match_selected_package = all(
        all(
            any(
                requirement.kind == "package"
                and requirement.target_ref_kind == "package"
                and requirement.target_ref_id == (group.package or device.identity.package)
                for requirement in _candidate_requirements(candidate_id)
            )
            and (
                candidate_lookup[candidate_id].pin not in bonded_pin_names
                or any(
                    requirement.kind == "bonded-pin"
                    and requirement.target_ref_kind == "pin"
                    and requirement.target_ref_id == candidate_lookup[candidate_id].pin
                    and requirement.value_ref_kind == "package"
                    and requirement.value_ref_id == (group.package or device.identity.package)
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
    peripheral_backend_schema_covered = all(
        canonical_peripheral_class(peripheral.ip_name) not in RUNTIME_OWNED_PERIPHERAL_CLASSES
        or peripheral.backend_schema_id is not None
        for peripheral in device.peripherals
    )
    ip_block_backend_schema_covered = all(
        ip_block.peripheral_class not in RUNTIME_OWNED_PERIPHERAL_CLASSES
        or ip_block.backend_schema_id is not None
        for ip_block in device.ip_blocks
    )
    register_counts_by_peripheral = Counter(register.peripheral for register in device.registers)
    register_field_counts_by_peripheral = Counter(
        register_field.peripheral for register_field in device.register_fields
    )
    # Runtime-owned peripherals normally carry typed register descriptors derived
    # from an SVD.  AVR 8-bit parts do not publish CMSIS-SVD and their ATDF
    # register-group parsing is a Phase 2.4 follow-on — exempt AVR cores until
    # that lands, at which point the rule will again apply uniformly.
    _registers_exempt_core = device.identity.core.lower().startswith("avr")
    runtime_peripheral_registers_present = _registers_exempt_core or all(
        canonical_peripheral_class(peripheral.ip_name) not in RUNTIME_OWNED_PERIPHERAL_CLASSES
        or register_counts_by_peripheral.get(peripheral.name, 0) > 0
        for peripheral in device.peripherals
    )
    runtime_peripheral_register_fields_present = _registers_exempt_core or all(
        canonical_peripheral_class(peripheral.ip_name) not in RUNTIME_OWNED_PERIPHERAL_CLASSES
        or register_field_counts_by_peripheral.get(peripheral.name, 0) > 0
        for peripheral in device.peripherals
    )
    route_operations_typed = all(
        operation.schema_id is not None
        and operation.subject_kind is not None
        and operation.subject_id is not None
        and operation.target_ref_kind is not None
        and operation.target_ref_id is not None
        and (operation.kind != "write-selector" or operation.value_int is not None)
        for operation in device.route_operations
    )
    route_requirements_typed = all(
        requirement.target_ref_kind is not None
        and requirement.target_ref_id is not None
        and (
            requirement.kind != "source-select"
            or (requirement.value_ref_kind == "selector" and requirement.value_ref_id is not None)
        )
        for requirement in device.route_requirements
    )
    register_target_operations_resolved = all(
        operation.target_ref_kind not in {"clock-gate", "reset"}
        or (
            operation.register_offset is not None
            or operation.register_id is not None
            or operation.register_name is not None
        )
        for operation in device.route_operations
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
    vector_slot_lookup = {vector_slot.slot: vector_slot for vector_slot in device.vector_slots}
    interrupt_bindings_reference_known_peripherals = all(
        binding.peripheral in peripheral_names for binding in device.interrupt_bindings
    )
    interrupt_bindings_reference_known_interrupts = all(
        binding.interrupt in interrupt_names for binding in device.interrupt_bindings
    )
    interrupt_bindings_reference_known_vector_slots = all(
        binding.vector_slot is None
        or (
            binding.vector_slot in vector_slot_lookup
            and vector_slot_lookup[binding.vector_slot].interrupt == binding.interrupt
        )
        for binding in device.interrupt_bindings
    )
    runtime_interrupt_bindings_present = all(
        canonical_peripheral_class(peripheral.ip_name) not in RUNTIME_OWNED_PERIPHERAL_CLASSES
        or interrupt_counts_by_peripheral.get(peripheral.name, 0) == 0
        or any(binding.peripheral == peripheral.name for binding in device.interrupt_bindings)
        for peripheral in device.peripherals
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
    system_vector_baseline_present = (
        _required_system_vector_slots(device.identity.core) <= vector_slot_numbers
    )
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
                descriptor.kind == "copy-source-region" and descriptor.source_region == memory.name
                for descriptor in device.startup_descriptors
            )
        )
        and (
            "copy-target" not in memory.startup_roles
            or any(
                descriptor.kind == "copy-target-region" and descriptor.target_region == memory.name
                for descriptor in device.startup_descriptors
            )
        )
        and (
            "zero-target" not in memory.startup_roles
            or any(
                descriptor.kind == "zero-target-region" and descriptor.target_region == memory.name
                for descriptor in device.startup_descriptors
            )
        )
        and (
            "retained-target" not in memory.startup_roles
            or any(
                descriptor.kind == "retained-region" and descriptor.target_region == memory.name
                for descriptor in device.startup_descriptors
            )
        )
        for memory in device.memories
    )
    startup_descriptors_include_runtime_baseline = all(
        any(descriptor.kind == required_kind for descriptor in device.startup_descriptors)
        for required_kind in ("vector-table", "initial-stack-pointer")
    )
    startup_descriptors_emit_without_handwritten_tables = (
        vector_slots_reference_known_interrupts
        and vector_slots_unique
        and interrupts_have_vector_slot
        and system_vector_baseline_present
        and memory_regions_carry_startup_roles
        and startup_descriptors_are_present
        and startup_descriptors_reference_known_memories
        and startup_descriptors_cover_memory_roles
        and startup_descriptors_include_runtime_baseline
    )
    clock_parent_map = {node.node_id: node.parent for node in device.clock_nodes}
    clock_node_parents_known = all(
        node.parent is None or node.parent in clock_node_ids for node in device.clock_nodes
    )
    clock_graph_root_reachable = all(
        _node_reaches_root(node.node_id, clock_parent_map) for node in device.clock_nodes
    )
    clock_selectors_structured = all(
        bool(selector.parent_options)
        and all(parent_option in clock_node_ids for parent_option in selector.parent_options)
        and (
            selector.register_target is None
            or (
                selector.register_peripheral is not None
                and (
                    selector.register_id is not None
                    or selector.register_offset is not None
                    or selector.register_name is not None
                )
            )
        )
        for selector in device.clock_selectors
    )
    clock_gates_reference_known_nodes = all(
        gate.parent_node is None or gate.parent_node in clock_node_ids
        for gate in device.clock_gates
    )
    clock_gates_structured = all(
        gate.peripheral is None
        or gate.peripheral not in peripheral_map
        or canonical_peripheral_class(peripheral_map[gate.peripheral].ip_name)
        not in RUNTIME_OWNED_PERIPHERAL_CLASSES
        or (
            gate.register_peripheral is not None
            and gate.register_name is not None
            and gate.register_id is not None
            and gate.register_field_id is not None
        )
        for gate in device.clock_gates
    )
    resets_structured = all(
        reset.peripheral is None
        or reset.peripheral not in peripheral_map
        or canonical_peripheral_class(peripheral_map[reset.peripheral].ip_name)
        not in RUNTIME_OWNED_PERIPHERAL_CLASSES
        or (
            reset.register_peripheral is not None
            and reset.register_name is not None
            and reset.register_id is not None
            and reset.register_field_id is not None
        )
        for reset in device.resets
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
    # When a peripheral declares a diagnostic rcc_enable_signal / rcc_reset_signal
    # string, the PeripheralClockBinding MUST also carry the matching typed
    # clock_gate_id / reset_id.  This guarantees the runtime contract is
    # executable from typed refs alone — diagnostic strings are never the
    # only path for clock/reset routing.
    binding_by_peripheral = {
        binding.peripheral: binding for binding in device.peripheral_clock_bindings
    }
    clock_reset_bindings_not_diagnostic_only = all(
        (
            peripheral.rcc_enable_signal is None
            or (
                binding_by_peripheral.get(peripheral.name) is not None
                and binding_by_peripheral[peripheral.name].clock_gate_id is not None
            )
        )
        and (
            peripheral.rcc_reset_signal is None
            or (
                binding_by_peripheral.get(peripheral.name) is not None
                and binding_by_peripheral[peripheral.name].reset_id is not None
            )
        )
        for peripheral in device.peripherals
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
    dma_bindings_reference_known_peripherals = all(
        binding.peripheral in peripheral_names for binding in device.dma_bindings
    )
    dma_bindings_reference_known_controllers = all(
        binding.controller in dma_controller_ids for binding in device.dma_bindings
    )
    dma_bindings_reference_known_routes = all(
        binding.route_id in dma_route_ids for binding in device.dma_bindings
    )
    dma_bindings_reference_known_conflicts = all(
        binding.conflict_group is None or binding.conflict_group in dma_conflict_ids
        for binding in device.dma_bindings
    )
    dma_bindings_cover_routes = {binding.route_id for binding in device.dma_bindings} == {
        route.route_id for route in device.dma_routes if route.peripheral is not None
    }
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
                f"{device.identity.device} every declared GPIO pin is covered by a package pad."
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
                f"{device.identity.device} route candidates only reference declared requirements."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-candidates-carry-package-requirement",
            category="semantic",
            severity="error",
            passed=candidate_package_requirements_known,
            message=(
                f"{device.identity.device} route candidates carry an explicit package requirement."
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
                f"{device.identity.device} route candidates only reference declared operations."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-connection-candidates-reference-known-capabilities",
            category="semantic",
            severity="error",
            passed=candidate_capabilities_known,
            message=(
                f"{device.identity.device} route candidates only reference declared capabilities."
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
                group_packages_match_selected_package and group_candidates_match_selected_package
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
            rule_id=f"{device.identity.device}-peripherals-carry-backend-schema",
            category="semantic",
            severity="error",
            passed=peripheral_backend_schema_covered,
            message=(
                f"{device.identity.device} runtime-owned peripheral instances carry "
                "a backend schema identifier."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-ip-blocks-carry-backend-schema",
            category="semantic",
            severity="error",
            passed=ip_block_backend_schema_covered,
            message=(
                f"{device.identity.device} runtime-owned IP blocks carry "
                "a backend schema identifier."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-runtime-peripherals-have-register-descriptors",
            category="semantic",
            severity="error",
            passed=runtime_peripheral_registers_present,
            message=(
                f"{device.identity.device} runtime-owned peripheral instances expose "
                "normalized register descriptors."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-runtime-peripherals-have-register-field-descriptors",
            category="semantic",
            severity="error",
            passed=runtime_peripheral_register_fields_present,
            message=(
                f"{device.identity.device} runtime-owned peripheral instances expose "
                "normalized register field descriptors."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-route-requirements-typed",
            category="semantic",
            severity="error",
            passed=route_requirements_typed,
            message=(f"{device.identity.device} route requirements expose typed runtime fields."),
        ),
        _rule(
            rule_id=f"{device.identity.device}-route-operations-typed",
            category="semantic",
            severity="error",
            passed=route_operations_typed,
            message=(f"{device.identity.device} route operations expose typed runtime fields."),
        ),
        _rule(
            rule_id=f"{device.identity.device}-register-target-operations-resolved",
            category="semantic",
            severity="error",
            passed=register_target_operations_resolved,
            message=(
                f"{device.identity.device} route operations with register-like targets "
                "resolve a normalized register offset."
            ),
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
            rule_id=f"{device.identity.device}-interrupt-bindings-reference-known-peripherals",
            category="semantic",
            severity="error",
            passed=interrupt_bindings_reference_known_peripherals,
            message=(
                f"{device.identity.device} interrupt bindings reference known peripheral instances."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-interrupt-bindings-reference-known-interrupts",
            category="semantic",
            severity="error",
            passed=interrupt_bindings_reference_known_interrupts,
            message=(f"{device.identity.device} interrupt bindings reference declared interrupts."),
        ),
        _rule(
            rule_id=f"{device.identity.device}-interrupt-bindings-reference-known-vector-slots",
            category="semantic",
            severity="error",
            passed=interrupt_bindings_reference_known_vector_slots,
            message=(
                f"{device.identity.device} interrupt bindings reference matching vector slots."
            ),
        ),
        _rule(
            rule_id=f"{device.identity.device}-runtime-interrupt-bindings-present",
            category="semantic",
            severity="error",
            passed=runtime_interrupt_bindings_present,
            message=(
                f"{device.identity.device} runtime-owned peripherals with interrupts "
                "expose typed interrupt bindings."
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
                f"{device.identity.device} startup descriptors only reference declared memories."
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
            rule_id=(
                f"{device.identity.device}-startup-descriptors-emit-without-handwritten-tables"
            ),
            category="semantic",
            severity="error",
            passed=startup_descriptors_emit_without_handwritten_tables,
            message=(
                f"{device.identity.device} startup vectors and startup descriptors are "
                "sufficient to emit startup artifacts without handwritten device tables."
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
            rule_id=f"{device.identity.device}-clock-reset-bindings-not-diagnostic-only",
            category="semantic",
            severity="error",
            passed=clock_reset_bindings_not_diagnostic_only,
            message=(
                f"{device.identity.device} clock/reset bindings expose typed gate/reset ids "
                "whenever diagnostic rcc_enable_signal / rcc_reset_signal strings are set."
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
            rule_id=f"{device.identity.device}-clock-gates-structured",
            category="semantic",
            severity="error",
            passed=clock_gates_structured,
            message=f"{device.identity.device} clock gates expose typed register references.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-resets-structured",
            category="semantic",
            severity="error",
            passed=resets_structured,
            message=f"{device.identity.device} resets expose typed register references.",
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
            rule_id=f"{device.identity.device}-dma-bindings-reference-known-peripherals",
            category="semantic",
            severity="error",
            passed=dma_bindings_reference_known_peripherals,
            message=f"{device.identity.device} DMA bindings reference known peripherals.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-bindings-reference-known-controllers",
            category="semantic",
            severity="error",
            passed=dma_bindings_reference_known_controllers,
            message=f"{device.identity.device} DMA bindings reference known controllers.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-bindings-reference-known-routes",
            category="semantic",
            severity="error",
            passed=dma_bindings_reference_known_routes,
            message=f"{device.identity.device} DMA bindings reference known DMA routes.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-bindings-reference-known-conflicts",
            category="semantic",
            severity="error",
            passed=dma_bindings_reference_known_conflicts,
            message=f"{device.identity.device} DMA bindings reference declared conflict groups.",
        ),
        _rule(
            rule_id=f"{device.identity.device}-dma-bindings-cover-routes",
            category="semantic",
            severity="error",
            passed=dma_bindings_cover_routes,
            message=f"{device.identity.device} DMA bindings cover the typed DMA route set.",
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
        any(len(group.signals) >= 2 for group in device.connection_groups) for device in devices
    )
    ip_block_usage: dict[tuple[str, str], set[str]] = {}
    for device in devices:
        for ip_block in device.ip_blocks:
            ip_block_usage.setdefault((ip_block.ip_name, ip_block.ip_version), set()).add(
                device.identity.device
            )
    families_with_versioned_ip = bool(ip_block_usage)
    # Reuse is only meaningful when multiple devices exist in the family; a
    # single-device family trivially cannot "share" an IP block across devices.
    is_multi_device_family = len(devices) >= 2
    family_reuses_ip_blocks = (
        not families_with_versioned_ip
        or not is_multi_device_family
        or any(len(device_names) >= 2 for device_names in ip_block_usage.values())
    )
    scope_label = (
        f"{scope.vendor}-{scope.family}" if scope.vendor is not None else str(scope.family)
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
    system_descriptor_domains = _evaluate_system_descriptor_domains(gate_c_results)
    draft_domain_ids = tuple(
        domain.domain_id for domain in system_descriptor_domains if domain.draft
    )

    gate_c = _evaluate_gate(gate_id="gate-c", blocking=True, results=gate_c_results)
    if draft_domain_ids:
        gate_c = ValidationGateStatus(
            gate_id=gate_c.gate_id,
            passed=gate_c.passed,
            blocking=gate_c.blocking,
            message=(
                f"{gate_c.gate_id} {'passed' if gate_c.passed else 'failed'} with "
                f"{len(gate_c_results)} rule(s); draft system descriptor domains: "
                f"{', '.join(draft_domain_ids)}."
            ),
            rule_ids=gate_c.rule_ids,
        )

    gates = (
        _evaluate_gate(gate_id="gate-a", blocking=False, results=gate_a_results),
        _evaluate_gate(gate_id="gate-b", blocking=False, results=gate_b_results),
        gate_c,
    )

    return ValidationReport(
        report_id="bootstrap-validation-v1",
        scope=scope.to_dict(),
        results=all_results,
        gates=gates,
        system_descriptor_domains=system_descriptor_domains,
    )
