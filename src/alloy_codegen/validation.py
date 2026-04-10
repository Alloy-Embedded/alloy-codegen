"""Validation rules and gate evaluation for the bootstrap pipeline."""

from __future__ import annotations

from collections import Counter

from alloy_codegen.ir.model import CanonicalDeviceIR
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


def _validate_source_manifest(source_manifest: SourceManifest) -> tuple[ValidationRuleResult, ...]:
    revisions = {source.revision for source in source_manifest.sources}
    local_paths = [source.local_path for source in source_manifest.sources]
    target_devices = {source.target_device for source in source_manifest.sources}
    target_coverage = {
        target: {
            source.source_id
            for source in source_manifest.sources
            if source.target_device == target
        }
        for target in source_manifest.targets
    }
    expected_source_ids = {"cmsis-svd-data", "stm32-open-pin-data"}
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
                target_coverage[target] >= expected_source_ids for target in source_manifest.targets
            ),
            message="Every target carries cmsis-svd-data and stm32-open-pin-data records.",
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
        peripheral_map.get(name) is not None
        and peripheral_map[name].rcc_enable_signal is not None
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
    duplicate_dma_routes = [
        route for route, count in Counter(dma_route_keys).items() if count > 1
    ]

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
                f"{device.identity.device} non-GPIO alternate functions carry "
                "explicit AF numbers."
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
                f"{device.identity.device} interrupt entries only reference "
                "discovered peripherals."
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
                f"{device.identity.device} DMA requests reference known "
                "controller peripherals."
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


def build_validation_report(
    *,
    scope: PipelineScope,
    source_manifest: SourceManifest,
    patch_manifest: PatchManifest,
    devices: tuple[CanonicalDeviceIR, ...],
) -> ValidationReport:
    """Build a structured validation report and gate statuses."""
    source_results = _validate_source_manifest(source_manifest)
    patch_results = _validate_patch_manifest(patch_manifest, source_manifest)
    schema_results = tuple(
        result
        for device in devices
        for result in _validate_device_structure(device)
    )
    semantic_results = tuple(
        result
        for device in devices
        for result in _validate_device_semantics(device)
    )

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
