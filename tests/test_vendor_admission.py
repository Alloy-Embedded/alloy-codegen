from __future__ import annotations

import json
import shutil

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.publish import run as run_publish
from alloy_codegen.vendor_admission import (
    FOUNDATIONAL_FAMILIES,
    CandidateFamilySchemaStatus,
    FoundationalFamilyStatus,
    evaluate_candidate_family_schema_admission,
    evaluate_vendor_admission,
)


def _family_contexts(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> tuple[tuple[PipelineScope, ExecutionContext], ...]:
    return (
        (PipelineScope(vendor="st", family="stm32g0"), execution_context),
        (PipelineScope(vendor="st", family="stm32f4"), execution_context),
        (PipelineScope(vendor="microchip", family="same70"), microchip_execution_context),
        (PipelineScope(vendor="nxp", family="imxrt1060"), nxp_execution_context),
    )


def test_vendor_admission_gate_passes_for_foundational_families(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    statuses: list[FoundationalFamilyStatus] = []

    for scope, context in _family_contexts(
        execution_context,
        microchip_execution_context,
        nxp_execution_context,
    ):
        result_a = run_publish(scope, context)
        family_dir = f"{scope.resolved_vendor()}/{scope.resolved_family()}"
        coverage = json.loads(
            (context.publication_root / family_dir / "reports" / "coverage.json").read_text(
                encoding="utf-8"
            )
        )
        summary = json.loads(
            (
                context.publication_root / family_dir / "reports" / "validation-summary.json"
            ).read_text(encoding="utf-8")
        )

        shutil.rmtree(context.artifact_root)
        shutil.rmtree(context.publication_root)

        result_b = run_publish(scope, context)
        stable_cycles = 2
        if result_a.payload.target_artifact_revision != result_b.payload.target_artifact_revision:
            stable_cycles = 1
        if (
            result_a.payload.publication_record.content_sha256
            != result_b.payload.publication_record.content_sha256
        ):
            stable_cycles = 1

        statuses.append(
            FoundationalFamilyStatus(
                vendor=scope.resolved_vendor(),
                family=scope.resolved_family(),
                all_devices_publishable=bool(coverage["all_devices_publishable"]),
                draft_system_descriptor_domains=tuple(summary["draft_system_descriptor_domains"]),
                stable_publication_cycles=stable_cycles,
                published_without_exceptions=(
                    result_a.status == "completed"
                    and result_b.status == "completed"
                    and result_a.payload.publication_mode == "published"
                    and result_b.payload.publication_mode == "published"
                ),
            )
        )

    assert {status.key for status in statuses} == set(FOUNDATIONAL_FAMILIES)
    assert evaluate_vendor_admission(tuple(statuses)) == ()


def test_vendor_admission_gate_blocks_incomplete_foundational_family() -> None:
    statuses = (
        FoundationalFamilyStatus(
            vendor="st",
            family="stm32g0",
            all_devices_publishable=True,
            draft_system_descriptor_domains=(),
            stable_publication_cycles=2,
        ),
        FoundationalFamilyStatus(
            vendor="st",
            family="stm32f4",
            all_devices_publishable=False,
            draft_system_descriptor_domains=("clock-reset",),
            stable_publication_cycles=2,
        ),
        FoundationalFamilyStatus(
            vendor="microchip",
            family="same70",
            all_devices_publishable=True,
            draft_system_descriptor_domains=(),
            stable_publication_cycles=2,
        ),
        FoundationalFamilyStatus(
            vendor="nxp",
            family="imxrt1060",
            all_devices_publishable=True,
            draft_system_descriptor_domains=(),
            stable_publication_cycles=2,
        ),
    )

    blockers = evaluate_vendor_admission(statuses)

    assert blockers == ("st/stm32f4 is not contract-complete",)


def test_candidate_family_schema_admission_accepts_typed_schema_reuse() -> None:
    statuses = (
        CandidateFamilySchemaStatus(
            vendor="espressif",
            family="esp32c3",
            reuses_typed_runtime_schemas=True,
        ),
    )

    assert evaluate_candidate_family_schema_admission(statuses) == ()


def test_candidate_family_schema_admission_accepts_localized_schema_support() -> None:
    statuses = (
        CandidateFamilySchemaStatus(
            vendor="microchip",
            family="avr-da",
            reuses_typed_runtime_schemas=False,
            localized_runtime_schemas=("alloy.pinmux.avr-portmux-v1",),
        ),
    )

    assert evaluate_candidate_family_schema_admission(statuses) == ()


def test_candidate_family_schema_admission_blocks_runtime_string_glue_and_family_branches() -> None:
    statuses = (
        CandidateFamilySchemaStatus(
            vendor="vendorx",
            family="foo32",
            reuses_typed_runtime_schemas=False,
            requires_family_runtime_branches=True,
            requires_runtime_string_glue=True,
        ),
    )

    assert evaluate_candidate_family_schema_admission(statuses) == (
        "vendorx/foo32 still requires runtime string glue",
        "vendorx/foo32 still requires family-specific runtime branches",
        "vendorx/foo32 does not reuse typed schemas and does not declare localized schema support",
    )
