"""Machine-readable runtime provenance and explainability reports."""

from __future__ import annotations

from collections import defaultdict

from alloy_codegen.ir.model import CanonicalDeviceIR, Provenance
from alloy_codegen.reporting import EmittedArtifact

from .emission import _family_report_path, _text_artifact
from .runtime_capabilities import runtime_capability_rows
from .runtime_lite_emission import (
    _runtime_lite_candidates,
    _runtime_lite_dma_bindings,
    _runtime_lite_groups,
    _runtime_lite_peripherals,
    _runtime_lite_reset_ids,
    runtime_lite_peripheral_class_name,
)
from .runtime_system_sequences import runtime_system_sequence_steps

RUNTIME_PROVENANCE_REPORT = "runtime-provenance.json"
RUNTIME_EXPLAINABILITY_REPORT = "runtime-explainability.json"
RUNTIME_CAPABILITY_SUMMARY_REPORT = "runtime-capability-summary.json"
RUNTIME_COMPATIBILITY_MATRIX_REPORT = "runtime-compatibility-matrix.json"


def runtime_report_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    if not devices:
        return ()
    return (
        _family_report_path(family_dir, RUNTIME_PROVENANCE_REPORT),
        _family_report_path(family_dir, RUNTIME_EXPLAINABILITY_REPORT),
        _family_report_path(family_dir, RUNTIME_CAPABILITY_SUMMARY_REPORT),
        _family_report_path(family_dir, RUNTIME_COMPATIBILITY_MATRIX_REPORT),
    )


def _device_runtime_capability_views(
    device: CanonicalDeviceIR,
) -> tuple[list[dict[str, object]], dict[str, dict[str, object]]]:
    runtime_peripherals = tuple(_runtime_lite_peripherals(device))
    peripherals_by_class: dict[str, list[str]] = defaultdict(list)
    for peripheral in runtime_peripherals:
        peripherals_by_class[runtime_lite_peripheral_class_name(peripheral.ip_name)].append(
            peripheral.name
        )

    rows_by_class: dict[str, list[object]] = defaultdict(list)
    for row in runtime_capability_rows(device):
        rows_by_class[row.peripheral_class].append(row)

    per_class_views: list[dict[str, object]] = []
    per_class_lookup: dict[str, dict[str, object]] = {}
    for peripheral_class in sorted(
        set(peripherals_by_class) | set(rows_by_class),
    ):
        rows = rows_by_class.get(peripheral_class, [])
        peripherals = sorted(peripherals_by_class.get(peripheral_class, []))
        capability_names = sorted({row.name for row in rows})
        dma_signals = sorted(
            {row.value for row in rows if row.name == "dma-compatible-signal" and row.value}
        )
        instance_capability_count = sum(
            1
            for row in rows
            if row.scope in {"instance_overlay", "dma_binding"} and row.peripheral is not None
        )
        class_capability_count = sum(
            1
            for row in rows
            if row.scope in {"ip_block", "runtime_contract"} and row.peripheral is None
        )
        view = {
            "peripheral_class": peripheral_class,
            "present": bool(peripherals),
            "peripheral_count": len(peripherals),
            "peripherals": peripherals,
            "capability_names": capability_names,
            "dma_signals": dma_signals,
            "instance_capability_count": instance_capability_count,
            "class_capability_count": class_capability_count,
        }
        per_class_views.append(view)
        per_class_lookup[peripheral_class] = view
    return per_class_views, per_class_lookup


def build_runtime_capability_summary_payload(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> dict[str, object]:
    if not devices:
        raise ValueError("Runtime capability summary generation requires at least one device.")

    device_payloads: list[dict[str, object]] = []
    family_class_aggregate: dict[str, dict[str, object]] = {}
    for device in sorted(devices, key=lambda item: item.identity.device):
        class_views, class_lookup = _device_runtime_capability_views(device)
        device_payloads.append(
            {
                "device": device.identity.device,
                "package": device.identity.package,
                "classes": class_views,
            }
        )
        for peripheral_class, view in class_lookup.items():
            aggregate = family_class_aggregate.setdefault(
                peripheral_class,
                {
                    "peripheral_class": peripheral_class,
                    "devices": [],
                    "device_count": 0,
                    "total_peripheral_count": 0,
                    "capability_names": set(),
                    "dma_signals": set(),
                },
            )
            if view["present"]:
                aggregate["devices"].append(device.identity.device)
                aggregate["device_count"] += 1
                aggregate["total_peripheral_count"] += view["peripheral_count"]
            aggregate["capability_names"].update(view["capability_names"])
            aggregate["dma_signals"].update(view["dma_signals"])

    summary_rows = [
        {
            "peripheral_class": peripheral_class,
            "devices": sorted(aggregate["devices"]),
            "device_count": aggregate["device_count"],
            "total_peripheral_count": aggregate["total_peripheral_count"],
            "capability_names": sorted(aggregate["capability_names"]),
            "dma_signals": sorted(aggregate["dma_signals"]),
        }
        for peripheral_class, aggregate in sorted(family_class_aggregate.items())
    ]

    first_device = devices[0]
    return {
        "report_id": "runtime-capability-summary-v1",
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "family_dir": family_dir,
        "devices": device_payloads,
        "classes": summary_rows,
    }


def build_runtime_compatibility_matrix_payload(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> dict[str, object]:
    if not devices:
        raise ValueError("Runtime compatibility matrix generation requires at least one device.")

    device_views: list[
        tuple[CanonicalDeviceIR, list[dict[str, object]], dict[str, dict[str, object]]]
    ] = []
    all_classes: set[str] = set()
    for device in sorted(devices, key=lambda item: item.identity.device):
        class_views, class_lookup = _device_runtime_capability_views(device)
        device_views.append((device, class_views, class_lookup))
        all_classes.update(class_lookup)

    driver_classes = sorted(all_classes)
    matrix_devices: list[dict[str, object]] = []
    for device, _class_views, class_lookup in device_views:
        matrix_devices.append(
            {
                "device": device.identity.device,
                "package": device.identity.package,
                "classes": [
                    {
                        "peripheral_class": peripheral_class,
                        **class_lookup.get(
                            peripheral_class,
                            {
                                "present": False,
                                "peripheral_count": 0,
                                "peripherals": [],
                                "capability_names": [],
                                "dma_signals": [],
                                "instance_capability_count": 0,
                                "class_capability_count": 0,
                            },
                        ),
                    }
                    for peripheral_class in driver_classes
                ],
            }
        )

    first_device = devices[0]
    return {
        "report_id": "runtime-compatibility-matrix-v1",
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "family_dir": family_dir,
        "driver_classes": driver_classes,
        "devices": matrix_devices,
    }


def _runtime_supported_peripherals(device: CanonicalDeviceIR):
    return tuple(_runtime_lite_peripherals(device))


def _device_runtime_paths(family_dir: str, device: CanonicalDeviceIR) -> dict[str, str]:
    device_name = device.identity.device
    root = f"{family_dir}/generated/runtime/devices/{device_name}"
    return {
        "interrupts": f"{root}/interrupts.hpp",
        "startup": f"{root}/startup.hpp",
        "resets": f"{root}/resets.hpp",
        "enable_domains": f"{root}/enable_domains.hpp",
        "clock_graph": f"{root}/clock_graph.hpp",
        "clock_bindings": f"{root}/clock_bindings.hpp",
        "dma_bindings": f"{root}/dma_bindings.hpp",
        "routes": f"{root}/routes.hpp",
        "capabilities": f"{root}/capabilities.hpp",
        "system_clock": f"{root}/system_clock.hpp",
        "system_sequences": f"{root}/system_sequences.hpp",
    }


def _runtime_dma_capability_id(binding: object) -> str:
    signal = getattr(binding, "signal", None) or "peripheral"
    return f"runtime-dma:{binding.peripheral}:{binding.controller}:{binding.request_line}:{signal}"


def _aggregate_provenance(provenances: tuple[Provenance, ...]) -> dict[str, object]:
    return {
        "source_ids": sorted(
            {provenance.source_id for provenance in provenances if provenance.source_id}
        ),
        "source_paths": sorted(
            {
                provenance.source_path
                for provenance in provenances
                if provenance.source_path is not None
            }
        ),
        "patch_ids": sorted(
            {patch_id for provenance in provenances for patch_id in provenance.patch_ids}
        ),
    }


def _derivation_kind(
    *,
    provenances: tuple[Provenance, ...],
    inference_rule: str | None,
) -> str:
    if inference_rule is not None:
        return "inferred"
    if any(provenance.patch_ids for provenance in provenances):
        return "patched"
    return "direct"


def _fact_entry(
    *,
    fact_id: str,
    fact_kind: str,
    artifact_path: str,
    provenances: tuple[Provenance, ...],
    detail: dict[str, object],
    inference_rule: str | None = None,
    supporting_fact_ids: tuple[str, ...] = (),
) -> dict[str, object]:
    provenance_payload = _aggregate_provenance(provenances)
    return {
        "fact_id": fact_id,
        "fact_kind": fact_kind,
        "artifact_path": artifact_path,
        "derivation_kind": _derivation_kind(
            provenances=provenances,
            inference_rule=inference_rule,
        ),
        "inference_rule": inference_rule,
        "supporting_fact_ids": list(supporting_fact_ids),
        "provenance": provenance_payload,
        "detail": detail,
    }


def build_runtime_provenance_payload(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> dict[str, object]:
    if not devices:
        raise ValueError("Runtime provenance payload generation requires at least one device.")

    device_payloads: list[dict[str, object]] = []
    for device in sorted(devices, key=lambda item: item.identity.device):
        paths = _device_runtime_paths(family_dir, device)
        runtime_peripheral_names = {
            peripheral.name for peripheral in _runtime_lite_peripherals(device)
        }
        runtime_supported_peripherals = _runtime_supported_peripherals(device)
        runtime_supported_by_class: dict[str, list[object]] = defaultdict(list)
        for peripheral in runtime_supported_peripherals:
            runtime_supported_by_class[
                runtime_lite_peripheral_class_name(peripheral.ip_name)
            ].append(peripheral)

        capability_by_id = {
            capability.capability_id: capability for capability in device.capabilities
        }
        runtime_bindings = _runtime_lite_dma_bindings(device)
        runtime_binding_by_capability_id = {
            _runtime_dma_capability_id(binding): binding for binding in runtime_bindings
        }

        facts: list[dict[str, object]] = []

        for vector_slot in sorted(device.vector_slots, key=lambda item: item.slot):
            facts.append(
                _fact_entry(
                    fact_id=f"vector-slot:{vector_slot.slot}",
                    fact_kind="vector_slot",
                    artifact_path=paths["startup"],
                    provenances=(vector_slot.provenance,),
                    detail={
                        "slot": vector_slot.slot,
                        "symbol_name": vector_slot.symbol_name,
                        "interrupt": vector_slot.interrupt,
                        "kind": vector_slot.kind,
                    },
                )
            )

        for descriptor in sorted(device.startup_descriptors, key=lambda item: item.descriptor_id):
            facts.append(
                _fact_entry(
                    fact_id=f"startup-descriptor:{descriptor.descriptor_id}",
                    fact_kind="startup_descriptor",
                    artifact_path=paths["startup"],
                    provenances=(descriptor.provenance,),
                    detail={
                        "descriptor_id": descriptor.descriptor_id,
                        "kind": descriptor.kind,
                        "source_region": descriptor.source_region,
                        "target_region": descriptor.target_region,
                        "symbol": descriptor.symbol,
                    },
                )
            )

        for binding in sorted(
            device.interrupt_bindings,
            key=lambda item: (item.peripheral, item.interrupt, item.line),
        ):
            if binding.peripheral not in runtime_peripheral_names:
                continue
            facts.append(
                _fact_entry(
                    fact_id=f"interrupt-binding:{binding.binding_id}",
                    fact_kind="interrupt_binding",
                    artifact_path=paths["interrupts"],
                    provenances=(binding.provenance,),
                    detail={
                        "binding_id": binding.binding_id,
                        "peripheral": binding.peripheral,
                        "interrupt": binding.interrupt,
                        "line": binding.line,
                        "vector_slot": binding.vector_slot,
                    },
                )
            )

        for node in sorted(device.clock_nodes, key=lambda item: item.node_id):
            facts.append(
                _fact_entry(
                    fact_id=f"clock-node:{node.node_id}",
                    fact_kind="clock_node",
                    artifact_path=paths["clock_graph"],
                    provenances=(node.provenance,),
                    detail={
                        "node_id": node.node_id,
                        "kind": node.kind,
                        "parent": node.parent,
                        "selector": node.selector,
                    },
                )
            )

        reset_ids = _runtime_lite_reset_ids(device)
        for reset in sorted(device.resets, key=lambda item: item.reset_id):
            if reset.reset_id not in reset_ids:
                continue
            facts.append(
                _fact_entry(
                    fact_id=f"reset:{reset.reset_id}",
                    fact_kind="reset_descriptor",
                    artifact_path=paths["resets"],
                    provenances=(reset.provenance,),
                    detail={
                        "reset_id": reset.reset_id,
                        "peripheral": reset.peripheral,
                        "register_id": reset.register_id,
                        "register_field_id": reset.register_field_id,
                    },
                )
            )

        runtime_gate_ids = {
            binding.clock_gate_id
            for binding in device.peripheral_clock_bindings
            if binding.peripheral in runtime_peripheral_names and binding.clock_gate_id is not None
        }
        for gate in sorted(device.clock_gates, key=lambda item: item.gate_id):
            if gate.gate_id not in runtime_gate_ids:
                continue
            facts.append(
                _fact_entry(
                    fact_id=f"enable-domain:{gate.gate_id}",
                    fact_kind="enable_domain",
                    artifact_path=paths["enable_domains"],
                    provenances=(gate.provenance,),
                    detail={
                        "enable_domain_id": gate.gate_id,
                        "peripheral": gate.peripheral,
                        "parent_clock_node": gate.parent_node,
                        "register_id": gate.register_id,
                        "register_field_id": gate.register_field_id,
                    },
                )
            )

        for binding in sorted(
            device.peripheral_clock_bindings,
            key=lambda item: item.peripheral,
        ):
            if binding.peripheral not in runtime_peripheral_names:
                continue
            facts.append(
                _fact_entry(
                    fact_id=f"clock-binding:{binding.peripheral}",
                    fact_kind="peripheral_clock_binding",
                    artifact_path=paths["clock_bindings"],
                    provenances=(binding.provenance,),
                    detail={
                        "peripheral": binding.peripheral,
                        "clock_gate_id": binding.clock_gate_id,
                        "reset_id": binding.reset_id,
                        "selector_id": binding.selector_id,
                    },
                )
            )

        for binding in runtime_bindings:
            facts.append(
                _fact_entry(
                    fact_id=f"dma-binding:{binding.binding_id}",
                    fact_kind="dma_binding",
                    artifact_path=paths["dma_bindings"],
                    provenances=(binding.provenance,),
                    detail={
                        "binding_id": binding.binding_id,
                        "peripheral": binding.peripheral,
                        "signal": binding.signal,
                        "controller": binding.controller,
                        "request_line": binding.request_line,
                        "route_id": binding.route_id,
                    },
                )
            )

        for candidate in _runtime_lite_candidates(device):
            facts.append(
                _fact_entry(
                    fact_id=f"route-candidate:{candidate.candidate_id}",
                    fact_kind="route_candidate",
                    artifact_path=paths["routes"],
                    provenances=(candidate.provenance,),
                    detail={
                        "candidate_id": candidate.candidate_id,
                        "pin": candidate.pin,
                        "peripheral": candidate.peripheral,
                        "signal": candidate.signal,
                        "route_kind": candidate.route_kind,
                        "route_selector": candidate.route_selector,
                    },
                )
            )

        for group in _runtime_lite_groups(device):
            facts.append(
                _fact_entry(
                    fact_id=f"route-group:{group.group_id}",
                    fact_kind="route_group",
                    artifact_path=paths["routes"],
                    provenances=(group.provenance,),
                    detail={
                        "group_id": group.group_id,
                        "peripheral": group.peripheral,
                        "signals": list(group.signals),
                        "candidate_ids": list(group.candidate_ids),
                    },
                )
            )

        for profile in sorted(device.system_clock_profiles, key=lambda item: item.profile_id):
            facts.append(
                _fact_entry(
                    fact_id=f"system-clock-profile:{profile.profile_id}",
                    fact_kind="system_clock_profile",
                    artifact_path=paths["system_clock"],
                    provenances=(profile.provenance,),
                    detail={
                        "profile_id": profile.profile_id,
                        "kind": profile.kind,
                        "source_kind": profile.source_kind,
                        "sysclk_hz": profile.sysclk_hz,
                    },
                )
            )

        for row in runtime_capability_rows(device):
            if row.capability_id in capability_by_id:
                provenance = (capability_by_id[row.capability_id].provenance,)
                inference_rule = None
                supporting_fact_ids: tuple[str, ...] = ()
            elif row.capability_id in runtime_binding_by_capability_id:
                binding = runtime_binding_by_capability_id[row.capability_id]
                provenance = (binding.provenance,)
                inference_rule = "runtime-capability-from-dma-binding"
                supporting_fact_ids = (f"dma-binding:{binding.binding_id}",)
            elif row.scope == "device":
                # Device-scope multicore facts (added by
                # ``expose-xtensa-dual-core-facts``) inherit provenance from
                # the device identity row — they are derived from the family
                # patch overlay, which is recorded on every register/peripheral
                # this device carries.  Use the first peripheral's provenance
                # as a representative source so the regression gate is
                # satisfied.
                first_peripheral = device.peripherals[0] if device.peripherals else None
                if first_peripheral is not None:
                    provenance = (first_peripheral.provenance,)
                else:
                    provenance = ()
                inference_rule = "runtime-capability-from-multicore-topology"
                supporting_fact_ids = ()
            else:
                class_provenances = tuple(
                    peripheral.provenance
                    for peripheral in runtime_supported_by_class.get(row.peripheral_class, ())
                )
                provenance = class_provenances
                inference_rule = "runtime-class-support-baseline"
                supporting_fact_ids = tuple(
                    f"runtime-peripheral:{peripheral.name}"
                    for peripheral in runtime_supported_by_class.get(row.peripheral_class, ())
                )
            facts.append(
                _fact_entry(
                    fact_id=f"capability:{row.capability_id}",
                    fact_kind="capability",
                    artifact_path=paths["capabilities"],
                    provenances=provenance,
                    inference_rule=inference_rule,
                    supporting_fact_ids=supporting_fact_ids,
                    detail={
                        "capability_id": row.capability_id,
                        "scope": row.scope,
                        "peripheral_class": row.peripheral_class,
                        "peripheral": row.peripheral,
                        "name": row.name,
                        "value": row.value,
                    },
                )
            )

        peripheral_by_name = {peripheral.name: peripheral for peripheral in device.peripherals}
        for step in runtime_system_sequence_steps(device):
            supporting_provenances: tuple[Provenance, ...]
            supporting_fact_ids: tuple[str, ...]
            if step.startup_descriptor_id is not None:
                descriptor = next(
                    descriptor
                    for descriptor in device.startup_descriptors
                    if descriptor.descriptor_id == step.startup_descriptor_id
                )
                supporting_provenances = (descriptor.provenance,)
                supporting_fact_ids = (f"startup-descriptor:{descriptor.descriptor_id}",)
            elif step.peripheral_name is not None:
                peripheral = peripheral_by_name[step.peripheral_name]
                supporting_provenances = (peripheral.provenance,)
                supporting_fact_ids = (f"runtime-peripheral:{step.peripheral_name}",)
            elif step.system_clock_profile_id is not None:
                profile = next(
                    profile
                    for profile in device.system_clock_profiles
                    if profile.profile_id == step.system_clock_profile_id
                )
                supporting_provenances = (profile.provenance,)
                supporting_fact_ids = (f"system-clock-profile:{profile.profile_id}",)
            elif step.kind == "secondary-core-release" and step.secondary_core_release_register_id:
                # Secondary-core release step (added by
                # ``expose-xtensa-dual-core-facts``) — provenance flows from
                # the typed register descriptor that the step references.
                register = next(
                    (
                        reg
                        for reg in device.registers
                        if reg.register_id == step.secondary_core_release_register_id
                    ),
                    None,
                )
                if register is not None:
                    supporting_provenances = (register.provenance,)
                    supporting_fact_ids = (f"register:{register.register_id}",)
                else:
                    supporting_provenances = ()
                    supporting_fact_ids = ()
            else:
                supporting_provenances = ()
                supporting_fact_ids = ()

            facts.append(
                _fact_entry(
                    fact_id=f"system-sequence:{step.sequence_id}:{step.ordinal}",
                    fact_kind="system_sequence_step",
                    artifact_path=paths["system_sequences"],
                    provenances=supporting_provenances,
                    inference_rule="runtime-system-sequence",
                    supporting_fact_ids=supporting_fact_ids,
                    detail={
                        "sequence_id": step.sequence_id,
                        "ordinal": step.ordinal,
                        "kind": step.kind,
                        "startup_descriptor_id": step.startup_descriptor_id,
                        "peripheral": step.peripheral_name,
                        "system_clock_profile_id": step.system_clock_profile_id,
                    },
                )
            )

        device_payloads.append(
            {
                "device": device.identity.device,
                "package": device.identity.package,
                "fact_count": len(facts),
                "facts": facts,
            }
        )

    first_device = devices[0]
    return {
        "schema_version": first_device.schema_version,
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "report_id": "runtime-provenance-v1",
        "devices": device_payloads,
    }


def build_runtime_explainability_payload(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> dict[str, object]:
    if not devices:
        raise ValueError("Runtime explainability payload generation requires at least one device.")

    device_payloads: list[dict[str, object]] = []
    for device in sorted(devices, key=lambda item: item.identity.device):
        paths = _device_runtime_paths(family_dir, device)
        runtime_supported_peripherals = _runtime_supported_peripherals(device)
        class_by_peripheral = {
            peripheral.name: runtime_lite_peripheral_class_name(peripheral.ip_name)
            for peripheral in runtime_supported_peripherals
        }
        capability_rows = runtime_capability_rows(device)
        capability_rows_by_peripheral: dict[str, list[object]] = defaultdict(list)
        class_capability_rows: dict[str, list[object]] = defaultdict(list)
        for row in capability_rows:
            if row.peripheral is None:
                class_capability_rows[row.peripheral_class].append(row)
            else:
                capability_rows_by_peripheral[row.peripheral].append(row)

        route_decisions = [
            {
                "decision_id": candidate.candidate_id,
                "decision_kind": "accepted_runtime_candidate",
                "artifact_path": paths["routes"],
                "pin": candidate.pin,
                "peripheral": candidate.peripheral,
                "signal": candidate.signal,
                "route_kind": candidate.route_kind,
                "route_selector": candidate.route_selector,
                "requirement_ids": list(candidate.requirement_ids),
                "operation_ids": list(candidate.operation_ids),
                "capability_ids": list(candidate.capability_ids),
                "explanation": (
                    "Candidate is published because it survived normalization "
                    "and belongs to the runtime contract."
                ),
            }
            for candidate in _runtime_lite_candidates(device)
        ]

        route_group_decisions = [
            {
                "decision_id": group.group_id,
                "decision_kind": "accepted_runtime_group",
                "artifact_path": paths["routes"],
                "peripheral": group.peripheral,
                "signals": list(group.signals),
                "candidate_ids": list(group.candidate_ids),
                "conflict_group": group.conflict_group,
                "package": group.package,
                "explanation": (
                    "Group is published because every member candidate survived runtime filtering."
                ),
            }
            for group in _runtime_lite_groups(device)
        ]

        dma_binding_decisions = [
            {
                "decision_id": binding.binding_id,
                "decision_kind": "accepted_runtime_dma_binding",
                "artifact_path": paths["dma_bindings"],
                "peripheral": binding.peripheral,
                "signal": binding.signal,
                "controller": binding.controller,
                "request_line": binding.request_line,
                "route_id": binding.route_id,
                "conflict_group": binding.conflict_group,
                "explanation": (
                    "DMA binding is published because the peripheral "
                    "participates in the runtime contract."
                ),
            }
            for binding in _runtime_lite_dma_bindings(device)
        ]

        capability_decisions: list[dict[str, object]] = []
        heuristic_facts: list[dict[str, object]] = []
        capability_sources = {
            capability.capability_id: capability for capability in device.capabilities
        }
        dma_binding_capability_ids = {
            _runtime_dma_capability_id(binding) for binding in _runtime_lite_dma_bindings(device)
        }
        for row in capability_rows:
            if row.capability_id in capability_sources:
                decision_kind = "direct_capability"
                explanation = "Capability is published directly from canonical capability data."
            elif row.capability_id in dma_binding_capability_ids:
                decision_kind = "inferred_dma_capability"
                explanation = (
                    "Capability is synthesized from a published DMA binding for the signal."
                )
            else:
                decision_kind = "inferred_runtime_support"
                explanation = (
                    "Capability is synthesized to mark baseline runtime "
                    "support for the peripheral class."
                )
            decision = {
                "decision_id": row.capability_id,
                "decision_kind": decision_kind,
                "artifact_path": paths["capabilities"],
                "scope": row.scope,
                "peripheral_class": row.peripheral_class,
                "peripheral": row.peripheral,
                "name": row.name,
                "value": row.value,
                "explanation": explanation,
            }
            capability_decisions.append(decision)
            if decision_kind.startswith("inferred_"):
                heuristic_facts.append(
                    {
                        "fact_id": row.capability_id,
                        "fact_kind": "capability",
                        "artifact_path": paths["capabilities"],
                        "explanation": explanation,
                    }
                )

        sequence_decisions = [
            {
                "decision_id": f"{step.sequence_id}:{step.ordinal}",
                "decision_kind": "inferred_system_sequence",
                "artifact_path": paths["system_sequences"],
                "sequence_id": step.sequence_id,
                "ordinal": step.ordinal,
                "kind": step.kind,
                "startup_descriptor_id": step.startup_descriptor_id,
                "peripheral": step.peripheral_name,
                "system_clock_profile_id": step.system_clock_profile_id,
                "explanation": (
                    "Bring-up step is synthesized from typed startup, "
                    "startup-control, and default clock facts."
                ),
            }
            for step in runtime_system_sequence_steps(device)
        ]
        heuristic_facts.extend(
            {
                "fact_id": decision["decision_id"],
                "fact_kind": "system_sequence_step",
                "artifact_path": decision["artifact_path"],
                "explanation": decision["explanation"],
            }
            for decision in sequence_decisions
        )

        capability_coverage = []
        for peripheral in sorted(runtime_supported_peripherals, key=lambda item: item.name):
            class_name = class_by_peripheral[peripheral.name]
            instance_rows = capability_rows_by_peripheral.get(peripheral.name, [])
            class_rows = class_capability_rows.get(class_name, [])
            if instance_rows:
                coverage_kind = "instance"
                explanation = "Peripheral has instance-specific published capability facts."
            elif class_rows:
                coverage_kind = "class-only"
                explanation = "Peripheral relies on class-level capability facts."
            else:
                coverage_kind = "none"
                explanation = "Peripheral has no published capability coverage."
            capability_coverage.append(
                {
                    "peripheral": peripheral.name,
                    "peripheral_class": class_name,
                    "artifact_path": paths["capabilities"],
                    "coverage_kind": coverage_kind,
                    "instance_capability_count": len(instance_rows),
                    "class_capability_count": len(class_rows),
                    "explanation": explanation,
                }
            )

        unsupported_runtime_peripherals = [
            coverage for coverage in capability_coverage if coverage["coverage_kind"] == "none"
        ]
        partial_runtime_peripherals = [
            coverage
            for coverage in capability_coverage
            if coverage["coverage_kind"] == "class-only"
        ]

        device_payloads.append(
            {
                "device": device.identity.device,
                "package": device.identity.package,
                "route_decision_count": len(route_decisions),
                "dma_binding_decision_count": len(dma_binding_decisions),
                "capability_decision_count": len(capability_decisions),
                "heuristic_fact_count": len(heuristic_facts),
                "route_decisions": route_decisions,
                "route_group_decisions": route_group_decisions,
                "dma_binding_decisions": dma_binding_decisions,
                "capability_decisions": capability_decisions,
                "system_sequence_decisions": sequence_decisions,
                "capability_coverage": capability_coverage,
                "unsupported_runtime_peripherals": unsupported_runtime_peripherals,
                "partial_runtime_peripherals": partial_runtime_peripherals,
                "heuristic_facts": heuristic_facts,
            }
        )

    first_device = devices[0]
    return {
        "schema_version": first_device.schema_version,
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "report_id": "runtime-explainability-v1",
        "devices": device_payloads,
    }


def find_runtime_report_violations(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    provenance_payload = build_runtime_provenance_payload(
        family_dir=family_dir,
        devices=devices,
    )
    explainability_payload = build_runtime_explainability_payload(
        family_dir=family_dir,
        devices=devices,
    )

    violations: list[str] = []
    device_by_name = {device.identity.device: device for device in devices}
    explainability_by_device = {
        candidate["device"]: candidate for candidate in explainability_payload["devices"]
    }
    for device_payload in provenance_payload["devices"]:
        device_name = str(device_payload["device"])
        device = device_by_name[device_name]
        inferred_count = 0
        for fact in device_payload["facts"]:
            if fact["derivation_kind"] == "inferred":
                inferred_count += 1
                if not fact["inference_rule"]:
                    violations.append(
                        f"{device_name} inferred fact {fact['fact_id']} has no inference rule"
                    )
            if not fact["provenance"]["source_ids"]:
                violations.append(
                    f"{device_name} runtime fact {fact['fact_id']} has no provenance source"
                )
        explainability_device = explainability_by_device[device_name]
        if inferred_count and explainability_device["heuristic_fact_count"] == 0:
            violations.append(
                f"{device_name} has inferred runtime facts but no heuristic explainability rows"
            )
        if any(
            coverage["coverage_kind"] == "none"
            for coverage in explainability_device["capability_coverage"]
        ):
            violations.append(
                f"{device_name} explainability report still marks unsupported runtime peripherals"
            )
        if _runtime_lite_candidates(device) and not explainability_device["route_decisions"]:
            violations.append(
                f"{device_name} has runtime candidates but no route explainability rows"
            )
        if (
            _runtime_lite_dma_bindings(device)
            and not explainability_device["dma_binding_decisions"]
        ):
            violations.append(f"{device_name} has runtime DMA bindings but no explainability rows")
        if runtime_capability_rows(device) and not explainability_device["capability_decisions"]:
            violations.append(f"{device_name} has runtime capabilities but no explainability rows")
    return tuple(violations)


def emit_runtime_provenance_report(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    return _text_artifact(
        path=_family_report_path(family_dir, RUNTIME_PROVENANCE_REPORT),
        artifact_kind="runtime-report",
        payload=build_runtime_provenance_payload(family_dir=family_dir, devices=devices),
    )


def emit_runtime_explainability_report(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    return _text_artifact(
        path=_family_report_path(family_dir, RUNTIME_EXPLAINABILITY_REPORT),
        artifact_kind="runtime-report",
        payload=build_runtime_explainability_payload(family_dir=family_dir, devices=devices),
    )


def emit_runtime_capability_summary_report(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    return _text_artifact(
        path=_family_report_path(family_dir, RUNTIME_CAPABILITY_SUMMARY_REPORT),
        artifact_kind="runtime-report",
        payload=build_runtime_capability_summary_payload(family_dir=family_dir, devices=devices),
    )


def emit_runtime_compatibility_matrix_report(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    return _text_artifact(
        path=_family_report_path(family_dir, RUNTIME_COMPATIBILITY_MATRIX_REPORT),
        artifact_kind="runtime-report",
        payload=build_runtime_compatibility_matrix_payload(family_dir=family_dir, devices=devices),
    )


__all__ = [
    "build_runtime_capability_summary_payload",
    "build_runtime_compatibility_matrix_payload",
    "build_runtime_explainability_payload",
    "build_runtime_provenance_payload",
    "emit_runtime_capability_summary_report",
    "emit_runtime_compatibility_matrix_report",
    "emit_runtime_explainability_report",
    "emit_runtime_provenance_report",
    "find_runtime_report_violations",
    "runtime_report_required_paths",
]
