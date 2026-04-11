from __future__ import annotations

import json
import shutil
import subprocess
from dataclasses import replace
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.publication import compute_materialized_tree_revision
from alloy_codegen.reporting import (
    SystemDescriptorDomainStatus,
    ValidationBundle,
    ValidationGateStatus,
    ValidationReport,
)
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.normalize import run as run_normalize
from alloy_codegen.stages.publish import run


def test_publish_includes_materialized_summary(
    execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    summary = result.payload.publication_summary
    record = result.payload.publication_record

    assert result.stage == "publish"
    assert result.status == "completed"
    assert result.payload.publication_mode == "published"
    assert result.payload.artifact_root == str(execution_context.artifact_root)
    assert result.payload.publication_root == str(execution_context.publication_root)
    assert result.payload.target_artifact_revision is not None
    assert result.payload.consumer_verification is not None
    assert result.payload.consumer_verification.succeeded is True
    assert any(
        argument.startswith("-DALLOY_CODEGEN_SMOKE_CONNECTOR_TABLES_HEADER=")
        for argument in result.payload.consumer_verification.command
    )
    assert any(
        argument.startswith("-DALLOY_CODEGEN_SMOKE_CLOCK_TREE_HEADER=")
        for argument in result.payload.consumer_verification.command
    )
    assert summary is not None
    assert record is not None
    assert summary.materialized_path is not None
    assert record.materialized_path is not None

    summary_path = Path(summary.materialized_path)
    record_path = Path(record.materialized_path)
    assert summary_path.exists()
    assert record_path.exists()
    assert any(
        artifact.materialized_path
        == str(
            execution_context.publication_root
            / "st/stm32g0/generated/devices/stm32g071rb/register_map.hpp"
        )
        for artifact in result.payload.published_artifacts
    )

    payload = json.loads(summary.content)
    assert payload["target_repository"] == "alloy-devices"
    assert payload["publication_mode"] == "published"
    assert payload["artifact_root"] == "st/stm32g0/"
    assert payload["publication_root"] == str(execution_context.publication_root)
    assert payload["target_artifact_revision"] == result.payload.target_artifact_revision
    assert payload["consumer_verification"]["consumer_id"] == "alloy-published-artifact-smoke"
    assert payload["consumer_verification"]["succeeded"] is True
    assert payload["materialized_artifact_count"] >= 10
    assert any(
        artifact["path"] == "st/stm32g0/reports/publication-record.json"
        for artifact in payload["materialized_artifacts"]
    )
    assert any(
        artifact["path"] == "st/stm32g0/reports/validation-report.json"
        for artifact in payload["materialized_artifacts"]
    )
    assert any(
        artifact["path"] == "st/stm32g0/generated/devices/stm32g071rb/register_map.hpp"
        for artifact in payload["materialized_artifacts"]
    )

    record_payload = json.loads(record.content)
    assert record_payload["publication_mode"] == "published"
    assert record_payload["target_artifact_revision"] == result.payload.target_artifact_revision
    assert record_payload["published_artifact_count"] >= 9
    assert record_payload["consumer_verification"]["succeeded"] is True


def test_publish_is_deterministic_for_same_inputs(execution_context: ExecutionContext) -> None:
    scope = PipelineScope(device="stm32g071rb")
    result_a = run(scope, execution_context)
    publication_revision_a = compute_materialized_tree_revision(execution_context.publication_root)
    summary_sha_a = result_a.payload.publication_summary.content_sha256
    record_sha_a = result_a.payload.publication_record.content_sha256
    published_sha_a = [artifact.content_sha256 for artifact in result_a.payload.published_artifacts]

    shutil.rmtree(execution_context.artifact_root)
    shutil.rmtree(execution_context.publication_root)

    result_b = run(scope, execution_context)
    publication_revision_b = compute_materialized_tree_revision(execution_context.publication_root)

    assert result_a.payload.target_artifact_revision == result_b.payload.target_artifact_revision
    assert record_sha_a == result_b.payload.publication_record.content_sha256
    assert summary_sha_a == result_b.payload.publication_summary.content_sha256
    assert published_sha_a == [
        artifact.content_sha256 for artifact in result_b.payload.published_artifacts
    ]
    assert publication_revision_a == publication_revision_b


def test_publish_microchip_family_scope(
    microchip_execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(vendor="microchip", family="same70"), microchip_execution_context)

    assert result.stage == "publish"
    assert result.status == "completed"
    assert result.payload.publication_mode == "published"
    assert result.payload.consumer_verification is not None
    assert result.payload.consumer_verification.succeeded is True
    assert (
        microchip_execution_context.publication_root
        / "microchip"
        / "same70"
        / "generated"
        / "devices"
        / "atsame70n21b"
        / "register_map.hpp"
    ).exists()
    assert (
        microchip_execution_context.publication_root
        / "microchip"
        / "same70"
        / "generated"
        / "devices"
        / "atsame70q21b"
        / "register_map.hpp"
    ).exists()


def test_publish_does_not_modify_publication_root_when_validation_fails(
    execution_context: ExecutionContext,
    monkeypatch,
) -> None:
    normalize_result = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)
    failing_report = ValidationReport(
        report_id="bootstrap-validation-v1",
        scope=normalize_result.scope.to_dict(),
        results=(),
        gates=(
            ValidationGateStatus(
                gate_id="gate-c",
                passed=False,
                blocking=True,
                message="gate-c failed with 1 rule(s).",
                rule_ids=("forced-failure",),
            ),
        ),
    )

    def fake_validate(scope: PipelineScope, context: ExecutionContext) -> StageResult:
        return StageResult(
            stage="validate",
            scope=scope,
            status="failed",
            payload=ValidationBundle(
                source_manifest=normalize_result.payload.source_manifest,
                patch_manifest=normalize_result.payload.patch_manifest,
                devices=normalize_result.payload.devices,
                report=failing_report,
            ),
        )

    def fail_emit(_: PipelineScope, __: ExecutionContext) -> StageResult:
        raise AssertionError("publish should not emit artifacts when validation is failing")

    monkeypatch.setattr("alloy_codegen.stages.publish.run_validate", fake_validate)
    monkeypatch.setattr("alloy_codegen.stages.publish.run_emit", fail_emit)

    result = run(PipelineScope(device="stm32g071rb"), execution_context)

    assert result.status == "failed"
    assert result.payload.publication_mode == "blocked"
    assert result.payload.artifact_manifest is None
    assert result.payload.published_artifacts == ()
    assert result.payload.publication_record is None
    assert result.payload.publication_summary is None
    assert not execution_context.publication_root.exists()


def test_publish_blocks_when_system_descriptor_domain_is_draft(
    execution_context: ExecutionContext,
    monkeypatch,
) -> None:
    normalize_result = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)
    draft_report = ValidationReport(
        report_id="bootstrap-validation-v1",
        scope=normalize_result.scope.to_dict(),
        results=(),
        gates=(
            ValidationGateStatus(
                gate_id="gate-c",
                passed=True,
                blocking=True,
                message="gate-c passed with 0 rule(s).",
                rule_ids=(),
            ),
        ),
        system_descriptor_domains=(
            SystemDescriptorDomainStatus(
                domain_id="startup",
                passed=False,
                draft=True,
                message="startup domain is draft because no validation rules are registered.",
                rule_ids=(),
            ),
        ),
    )

    def fake_validate(scope: PipelineScope, context: ExecutionContext) -> StageResult:
        return StageResult(
            stage="validate",
            scope=scope,
            status="failed",
            payload=ValidationBundle(
                source_manifest=normalize_result.payload.source_manifest,
                patch_manifest=normalize_result.payload.patch_manifest,
                devices=normalize_result.payload.devices,
                report=draft_report,
            ),
        )

    def fail_emit(_: PipelineScope, __: ExecutionContext) -> StageResult:
        raise AssertionError("publish should not emit artifacts when a system domain is draft")

    monkeypatch.setattr("alloy_codegen.stages.publish.run_validate", fake_validate)
    monkeypatch.setattr("alloy_codegen.stages.publish.run_emit", fail_emit)

    result = run(PipelineScope(device="stm32g071rb"), execution_context)

    assert result.status == "failed"
    assert result.payload.publication_mode == "blocked"
    assert result.payload.draft_system_descriptor_domains == ("startup",)
    assert result.warnings == (
        "Publication is blocked by draft system descriptor domains: startup.",
    )
    assert not execution_context.publication_root.exists()


def test_publish_blocks_when_requested_scope_is_not_fully_publishable(
    execution_context: ExecutionContext,
    monkeypatch,
) -> None:
    normalize_result = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)
    incomplete_device = replace(normalize_result.payload.devices[0], startup_descriptors=())
    passing_report = ValidationReport(
        report_id="bootstrap-validation-v1",
        scope=normalize_result.scope.to_dict(),
        results=(),
        gates=(
            ValidationGateStatus(
                gate_id="gate-c",
                passed=True,
                blocking=True,
                message="gate-c passed with 0 rule(s).",
                rule_ids=(),
            ),
        ),
    )

    def fake_validate(scope: PipelineScope, context: ExecutionContext) -> StageResult:
        return StageResult(
            stage="validate",
            scope=scope,
            status="completed",
            payload=ValidationBundle(
                source_manifest=normalize_result.payload.source_manifest,
                patch_manifest=normalize_result.payload.patch_manifest,
                devices=(incomplete_device,),
                report=passing_report,
            ),
        )

    def fail_emit(_: PipelineScope, __: ExecutionContext) -> StageResult:
        raise AssertionError("publish should not emit artifacts when coverage is incomplete")

    monkeypatch.setattr("alloy_codegen.stages.publish.run_validate", fake_validate)
    monkeypatch.setattr("alloy_codegen.stages.publish.run_emit", fail_emit)

    result = run(PipelineScope(device="stm32g071rb"), execution_context)

    assert result.status == "failed"
    assert result.payload.publication_mode == "blocked"
    assert result.warnings == (
        "Publication is blocked because the requested scope is not fully publishable: stm32g071rb.",
    )
    assert not execution_context.publication_root.exists()


def test_publish_does_not_modify_publication_root_when_consumer_verification_fails(
    execution_context: ExecutionContext,
    monkeypatch,
) -> None:
    from alloy_codegen.reporting import ConsumerVerification

    def fake_verify(**_: object) -> ConsumerVerification:
        return ConsumerVerification(
            consumer_id="alloy-published-artifact-smoke",
            compiler="c++",
            source_file="/tmp/source.cpp",
            startup_source="/tmp/startup_vectors.cpp",
            build_dir="/tmp/build",
            executable_path="/tmp/build/smoke-consumer",
            command=("c++",),
            succeeded=False,
            stdout="",
            stderr="forced failure",
        )

    monkeypatch.setattr("alloy_codegen.stages.publish.verify_alloy_smoke_consumer", fake_verify)

    result = run(PipelineScope(device="stm32g071rb"), execution_context)

    assert result.status == "failed"
    assert result.payload.publication_mode == "blocked"
    assert result.payload.consumer_verification is not None
    assert result.payload.consumer_verification.succeeded is False
    assert result.payload.publication_record is None
    assert result.payload.publication_summary is None
    assert not execution_context.publication_root.exists()


def test_publish_preserves_git_checkout_metadata_and_unrelated_files(
    execution_context: ExecutionContext,
    tmp_path: Path,
) -> None:
    publication_checkout = tmp_path / "alloy-devices"
    publication_checkout.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        ["git", "init", "--initial-branch=main", str(publication_checkout)],
        check=True,
        capture_output=True,
        text=True,
    )
    readme_path = publication_checkout / "README.md"
    readme_path.write_text("# alloy-devices\n", encoding="utf-8")
    subprocess.run(
        ["git", "-C", str(publication_checkout), "config", "user.name", "Alloy CI"],
        check=True,
        capture_output=True,
        text=True,
    )
    subprocess.run(
        ["git", "-C", str(publication_checkout), "config", "user.email", "ci@example.com"],
        check=True,
        capture_output=True,
        text=True,
    )
    subprocess.run(
        ["git", "-C", str(publication_checkout), "add", "README.md"],
        check=True,
        capture_output=True,
        text=True,
    )
    subprocess.run(
        ["git", "-C", str(publication_checkout), "commit", "-m", "docs: bootstrap repo"],
        check=True,
        capture_output=True,
        text=True,
    )

    context = execution_context.with_overrides(publication_root=str(publication_checkout))
    result = run(PipelineScope(family="stm32g0"), context)

    status = subprocess.run(
        ["git", "-C", str(publication_checkout), "status", "--short"],
        check=True,
        capture_output=True,
        text=True,
    )

    assert result.status == "completed"
    assert (publication_checkout / ".git").exists()
    assert readme_path.read_text(encoding="utf-8") == "# alloy-devices\n"
    assert (publication_checkout / "st" / "stm32g0" / "artifact-manifest.json").exists()
    assert (
        publication_checkout
        / "st"
        / "stm32g0"
        / "generated"
        / "devices"
        / "stm32g030f6"
        / "register_map.hpp"
    ).exists()
    assert "README.md" not in status.stdout
    assert "?? st/" in status.stdout or "A  st/" in status.stdout


def test_compute_materialized_tree_revision_ignores_git_metadata(tmp_path: Path) -> None:
    tree_root = tmp_path / "alloy-devices"
    tracked_dir = tree_root / "st" / "stm32g0" / "metadata"
    git_dir = tree_root / ".git"

    tracked_dir.mkdir(parents=True, exist_ok=True)
    git_dir.mkdir(parents=True, exist_ok=True)

    tracked_dir.mkdir(parents=True, exist_ok=True)
    (tracked_dir / "family-index.json").write_text('{"family":"stm32g0"}\n', encoding="utf-8")
    (git_dir / "HEAD").write_text("ref: refs/heads/main\n", encoding="utf-8")

    revision_a = compute_materialized_tree_revision(tree_root)

    (git_dir / "index").write_text("changed between runs\n", encoding="utf-8")
    revision_b = compute_materialized_tree_revision(tree_root)

    assert revision_a == revision_b
