"""Publication helpers for alloy-devices outputs."""

from __future__ import annotations

import shutil
from pathlib import Path

from alloy_codegen.errors import StageExecutionError
from alloy_codegen.manifests import ArtifactManifest
from alloy_codegen.reporting import ConsumerVerification, EmittedArtifact, ValidationReport
from alloy_codegen.scope import PipelineScope
from alloy_codegen.serialization import canonical_json_sha256, canonical_json_text, to_primitive


def _text_artifact(*, path: str, artifact_kind: str, payload: object) -> EmittedArtifact:
    content = canonical_json_text(payload)
    return EmittedArtifact(
        path=path,
        artifact_kind=artifact_kind,
        content=content,
        content_sha256=canonical_json_sha256(payload),
        content_bytes=len(content.encode("utf-8")),
    )


def compute_target_artifact_revision(artifacts: tuple[EmittedArtifact, ...]) -> str:
    """Compute a deterministic revision for a set of emitted artifacts."""
    payload = [
        {
            "path": artifact.path,
            "artifact_kind": artifact.artifact_kind,
            "content_sha256": artifact.content_sha256,
            "content_bytes": artifact.content_bytes,
        }
        for artifact in sorted(artifacts, key=lambda item: item.path)
    ]
    return canonical_json_sha256(payload)


def emit_publication_record(
    *,
    family_dir: str,
    scope: PipelineScope,
    target_repository: str,
    publication_mode: str,
    target_artifact_revision: str,
    artifact_manifest: ArtifactManifest,
    validation_report: ValidationReport,
    published_artifacts: tuple[EmittedArtifact, ...],
    consumer_verification: ConsumerVerification,
) -> EmittedArtifact:
    """Emit a deterministic publication record for the target artifact set."""
    payload = {
        "target_repository": target_repository,
        "publication_mode": publication_mode,
        "scope": scope.to_dict(),
        "target_artifact_revision": target_artifact_revision,
        "artifact_manifest": artifact_manifest.to_dict(),
        "validation": {
            "report_id": validation_report.report_id,
            "is_passing": validation_report.is_passing,
            "gates": to_primitive(validation_report.gates),
        },
        "consumer_verification": to_primitive(consumer_verification),
        "published_artifact_count": len(published_artifacts),
        "published_artifacts": [
            {
                "path": artifact.path,
                "artifact_kind": artifact.artifact_kind,
                "content_sha256": artifact.content_sha256,
                "content_bytes": artifact.content_bytes,
            }
            for artifact in sorted(published_artifacts, key=lambda item: item.path)
        ],
    }
    return _text_artifact(
        path=f"{family_dir}/publication-record.json",
        artifact_kind="publication-record",
        payload=payload,
    )


def prepare_staging_root(publication_root: Path) -> Path:
    """Create a clean staging directory for publication."""
    staging_root = publication_root.parent / f".{publication_root.name}.staging"
    if staging_root.exists():
        shutil.rmtree(staging_root)
    staging_root.mkdir(parents=True, exist_ok=True)
    return staging_root


def promote_staging_root(*, staging_root: Path, publication_root: Path) -> None:
    """Replace publication_root with the verified staging tree."""
    if not staging_root.exists():
        raise StageExecutionError(f"Publication staging root does not exist: {staging_root}")
    publication_root.parent.mkdir(parents=True, exist_ok=True)
    if publication_root.exists():
        shutil.rmtree(publication_root)
    shutil.move(str(staging_root), str(publication_root))
