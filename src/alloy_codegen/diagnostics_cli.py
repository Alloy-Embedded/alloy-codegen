"""Diagnostic helpers for the alloy-codegen CLI."""

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import AlloyCodegenError
from alloy_codegen.runtime_capabilities import runtime_capability_rows
from alloy_codegen.runtime_lite_emission import (
    _runtime_lite_dma_bindings,
    _runtime_lite_peripherals,
    runtime_lite_peripheral_class_name,
)
from alloy_codegen.runtime_reports import (
    build_runtime_explainability_payload,
    build_runtime_provenance_payload,
)
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.validate import run as run_validate


@dataclass(frozen=True, slots=True)
class RuntimeExplainResult:
    """Explain one emitted fact for one device."""

    scope: PipelineScope
    fact: str
    exact_match: bool
    matches: tuple[dict[str, object], ...]

    def to_dict(self) -> dict[str, object]:
        return {
            "command": "explain",
            "scope": self.scope.to_dict(),
            "fact": self.fact,
            "exact_match": self.exact_match,
            "matches": list(self.matches),
        }


@dataclass(frozen=True, slots=True)
class RuntimeDiffResult:
    """Capability delta between two devices."""

    from_scope: PipelineScope
    to_scope: PipelineScope
    added: tuple[dict[str, object], ...]
    removed: tuple[dict[str, object], ...]
    modified: tuple[dict[str, object], ...]

    def to_dict(self) -> dict[str, object]:
        return {
            "command": "diff",
            "from": self.from_scope.to_dict(),
            "to": self.to_scope.to_dict(),
            "added": list(self.added),
            "removed": list(self.removed),
            "modified": list(self.modified),
        }


def _validated_device(
    *,
    device_name: str,
    context: ExecutionContext,
):
    scope = PipelineScope(device=device_name)
    result = run_validate(scope, context)
    if result.status != "completed":
        raise AlloyCodegenError(f"Validation failed for device {device_name}.")
    device = result.payload.devices[0]
    family_dir = f"{result.scope.resolved_vendor()}/{result.scope.resolved_family()}"
    return result.scope, family_dir, device


def _format_provenance(payload: dict[str, object] | None) -> dict[str, object]:
    if payload is None:
        return {"source_ids": [], "source_paths": [], "patch_ids": []}
    return {
        "source_ids": payload.get("source_ids", []),
        "source_paths": payload.get("source_paths", []),
        "patch_ids": payload.get("patch_ids", []),
    }


def _normalized_fact_token(value: str) -> str:
    return value.strip().lower().replace("_", "-")


def explain_runtime_fact(
    *,
    device_name: str,
    fact: str,
    context: ExecutionContext,
) -> RuntimeExplainResult:
    scope, family_dir, device = _validated_device(device_name=device_name, context=context)
    provenance_payload = build_runtime_provenance_payload(family_dir=family_dir, devices=(device,))
    explainability_payload = build_runtime_explainability_payload(
        family_dir=family_dir,
        devices=(device,),
    )

    provenance_device = provenance_payload["devices"][0]
    explainability_device = explainability_payload["devices"][0]
    candidates: list[dict[str, object]] = []

    for entry in provenance_device["facts"]:
        if _normalized_fact_token(entry["fact_id"]) == _normalized_fact_token(fact):
            candidates.append(
                {
                    "match_kind": "provenance_fact",
                    "id": entry["fact_id"],
                    "kind": entry["fact_kind"],
                    "artifact_path": entry["artifact_path"],
                    "detail": entry["detail"],
                    "provenance": _format_provenance(entry.get("provenance")),
                    "explanation": entry.get("inference_rule"),
                    "supporting_fact_ids": entry.get("supporting_fact_ids", []),
                }
            )

    decision_collections = (
        ("route_decisions", explainability_device["route_decisions"]),
        ("route_group_decisions", explainability_device["route_group_decisions"]),
        ("dma_binding_decisions", explainability_device["dma_binding_decisions"]),
        ("capability_decisions", explainability_device["capability_decisions"]),
        ("system_sequence_decisions", explainability_device["system_sequence_decisions"]),
        ("heuristic_facts", explainability_device["heuristic_facts"]),
    )
    for collection_name, items in decision_collections:
        for entry in items:
            entry_id = entry.get("decision_id") or entry.get("fact_id")
            if entry_id and _normalized_fact_token(str(entry_id)) == _normalized_fact_token(fact):
                candidates.append(
                    {
                        "match_kind": collection_name,
                        "id": entry_id,
                        "kind": entry.get("decision_kind") or entry.get("fact_kind"),
                        "artifact_path": entry["artifact_path"],
                        "detail": {
                            key: value
                            for key, value in entry.items()
                            if key
                            not in {
                                "decision_id",
                                "decision_kind",
                                "fact_id",
                                "fact_kind",
                                "artifact_path",
                                "explanation",
                            }
                        },
                        "provenance": {"source_ids": [], "source_paths": [], "patch_ids": []},
                        "explanation": entry.get("explanation"),
                        "supporting_fact_ids": [],
                    }
                )

    exact_match = bool(candidates)
    if not exact_match:
        fact_lower = _normalized_fact_token(fact)
        for entry in provenance_device["facts"]:
            if fact_lower in _normalized_fact_token(entry["fact_id"]):
                candidates.append(
                    {
                        "match_kind": "provenance_fact",
                        "id": entry["fact_id"],
                        "kind": entry["fact_kind"],
                        "artifact_path": entry["artifact_path"],
                        "detail": entry["detail"],
                        "provenance": _format_provenance(entry.get("provenance")),
                        "explanation": entry.get("inference_rule"),
                        "supporting_fact_ids": entry.get("supporting_fact_ids", []),
                    }
                )
        for collection_name, items in decision_collections:
            for entry in items:
                entry_id = entry.get("decision_id") or entry.get("fact_id")
                if entry_id and fact_lower in _normalized_fact_token(str(entry_id)):
                    candidates.append(
                        {
                            "match_kind": collection_name,
                            "id": entry_id,
                            "kind": entry.get("decision_kind") or entry.get("fact_kind"),
                            "artifact_path": entry["artifact_path"],
                            "detail": {
                                key: value
                                for key, value in entry.items()
                                if key
                                not in {
                                    "decision_id",
                                    "decision_kind",
                                    "fact_id",
                                    "fact_kind",
                                    "artifact_path",
                                    "explanation",
                                }
                            },
                            "provenance": {"source_ids": [], "source_paths": [], "patch_ids": []},
                            "explanation": entry.get("explanation"),
                            "supporting_fact_ids": [],
                        }
                    )

    if not candidates:
        raise AlloyCodegenError(f"No emitted fact matches {fact!r} for device {device_name}.")

    unique_candidates = {
        (candidate["match_kind"], candidate["id"]): candidate for candidate in candidates
    }
    return RuntimeExplainResult(
        scope=scope,
        fact=fact,
        exact_match=exact_match,
        matches=tuple(unique_candidates.values()),
    )


def _capability_row_key(row) -> tuple[str, str | None, str]:
    return (row.peripheral_class, row.peripheral, row.name)


def _capability_diff_sort_key(item: tuple[str, str | None, str]) -> tuple[str, str, str]:
    return (item[0], item[1] or "", item[2])


def _capability_provenance_map(device) -> dict[str, dict[str, object]]:
    capability_sources = {
        capability.capability_id: capability for capability in device.capabilities
    }
    dma_binding_sources = {}
    for binding in _runtime_lite_dma_bindings(device):
        capability_id = (
            f"runtime-dma:{binding.peripheral}:{binding.controller}:{binding.request_line}:"
            f"{binding.signal or 'peripheral'}"
        )
        dma_binding_sources[capability_id] = binding

    provenance_by_id: dict[str, dict[str, object]] = {}
    for row in runtime_capability_rows(device):
        if row.capability_id in capability_sources:
            provenance = capability_sources[row.capability_id].provenance
            explanation = "direct"
        elif row.capability_id in dma_binding_sources:
            provenance = dma_binding_sources[row.capability_id].provenance
            explanation = "runtime-capability-from-dma-binding"
        else:
            runtime_peripherals = [
                peripheral
                for peripheral in _runtime_lite_peripherals(device)
                if runtime_lite_peripheral_class_name(peripheral.ip_name) == row.peripheral_class
            ]
            provenance = (
                runtime_peripherals[0].provenance if runtime_peripherals else device.provenance
            )
            explanation = "runtime-class-support-baseline"
        provenance_by_id[row.capability_id] = {
            "source_ids": [provenance.source_id] if provenance.source_id else [],
            "source_paths": [provenance.source_path] if provenance.source_path else [],
            "patch_ids": list(provenance.patch_ids),
            "derivation": explanation,
        }
    return provenance_by_id


def diff_runtime_capabilities(
    *,
    from_device: str,
    to_device: str,
    context: ExecutionContext,
) -> RuntimeDiffResult:
    from_scope, _from_family_dir, from_ir = _validated_device(
        device_name=from_device, context=context
    )
    to_scope, _to_family_dir, to_ir = _validated_device(device_name=to_device, context=context)

    from_rows = runtime_capability_rows(from_ir)
    to_rows = runtime_capability_rows(to_ir)
    from_by_key = {_capability_row_key(row): row for row in from_rows}
    to_by_key = {_capability_row_key(row): row for row in to_rows}
    from_provenance = _capability_provenance_map(from_ir)
    to_provenance = _capability_provenance_map(to_ir)

    added: list[dict[str, object]] = []
    removed: list[dict[str, object]] = []
    modified: list[dict[str, object]] = []

    for key in sorted(to_by_key.keys() - from_by_key.keys(), key=_capability_diff_sort_key):
        row = to_by_key[key]
        added.append(
            {
                "peripheral_class": row.peripheral_class,
                "peripheral": row.peripheral,
                "name": row.name,
                "value": row.value,
                "scope": row.scope,
                "provenance": to_provenance[row.capability_id],
            }
        )
    for key in sorted(from_by_key.keys() - to_by_key.keys(), key=_capability_diff_sort_key):
        row = from_by_key[key]
        removed.append(
            {
                "peripheral_class": row.peripheral_class,
                "peripheral": row.peripheral,
                "name": row.name,
                "value": row.value,
                "scope": row.scope,
                "provenance": from_provenance[row.capability_id],
            }
        )
    for key in sorted(from_by_key.keys() & to_by_key.keys(), key=_capability_diff_sort_key):
        from_row = from_by_key[key]
        to_row = to_by_key[key]
        if from_row.value == to_row.value and from_row.scope == to_row.scope:
            continue
        modified.append(
            {
                "peripheral_class": to_row.peripheral_class,
                "peripheral": to_row.peripheral,
                "name": to_row.name,
                "from": {
                    "value": from_row.value,
                    "scope": from_row.scope,
                    "provenance": from_provenance[from_row.capability_id],
                },
                "to": {
                    "value": to_row.value,
                    "scope": to_row.scope,
                    "provenance": to_provenance[to_row.capability_id],
                },
            }
        )

    return RuntimeDiffResult(
        from_scope=from_scope,
        to_scope=to_scope,
        added=tuple(added),
        removed=tuple(removed),
        modified=tuple(modified),
    )


def format_explain_result(result: RuntimeExplainResult) -> str:
    lines = [
        f"explain: {result.scope.display_name()}",
        f"fact: {result.fact}",
        f"exact_match: {'true' if result.exact_match else 'false'}",
    ]
    for match in result.matches:
        lines.extend(
            [
                f"- {match['id']} [{match['match_kind']}]",
                f"  kind: {match['kind']}",
                f"  artifact: {match['artifact_path']}",
            ]
        )
        if match["explanation"]:
            lines.append(f"  explanation: {match['explanation']}")
        provenance = match["provenance"]
        if provenance["source_ids"] or provenance["patch_ids"]:
            lines.append(
                "  provenance: "
                f"sources={','.join(provenance['source_ids']) or '-'} "
                f"patches={','.join(provenance['patch_ids']) or '-'}"
            )
        if match["supporting_fact_ids"]:
            lines.append(f"  supporting: {', '.join(match['supporting_fact_ids'])}")
        if match["detail"]:
            lines.append(f"  detail: {match['detail']}")
    return "\n".join(lines)


def format_diff_result(result: RuntimeDiffResult) -> str:
    lines = [
        f"diff: {result.from_scope.display_name()} -> {result.to_scope.display_name()}",
        f"added={len(result.added)} removed={len(result.removed)} modified={len(result.modified)}",
    ]
    for label, items in (("added", result.added), ("removed", result.removed)):
        if not items:
            continue
        lines.append(f"{label}:")
        for item in items:
            provenance = item["provenance"]
            lines.append(
                f"- {item['peripheral_class']} {item['peripheral'] or '*'} {item['name']}="
                f"{item['value']} [{item['scope']}] "
                f"sources={','.join(provenance['source_ids']) or '-'} "
                f"patches={','.join(provenance['patch_ids']) or '-'}"
            )
    if result.modified:
        lines.append("modified:")
        for item in result.modified:
            from_provenance = item["from"]["provenance"]
            to_provenance = item["to"]["provenance"]
            lines.append(
                f"- {item['peripheral_class']} {item['peripheral'] or '*'} {item['name']}: "
                f"{item['from']['value']} [{item['from']['scope']}] -> "
                f"{item['to']['value']} [{item['to']['scope']}] "
                f"(from_sources={','.join(from_provenance['source_ids']) or '-'} "
                f"to_sources={','.join(to_provenance['source_ids']) or '-'})"
            )
    return "\n".join(lines)


__all__ = [
    "RuntimeDiffResult",
    "RuntimeExplainResult",
    "diff_runtime_capabilities",
    "explain_runtime_fact",
    "format_diff_result",
    "format_explain_result",
]
