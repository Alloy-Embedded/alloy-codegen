"""Publication helpers for alloy-devices outputs."""

from __future__ import annotations

import hashlib
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


def compute_materialized_tree_revision(root: Path) -> str:
    """Compute a deterministic revision for a materialized artifact tree."""
    if not root.exists():
        raise StageExecutionError(f"Materialized artifact root does not exist: {root}")

    digest = hashlib.sha256()
    for path in sorted(
        item
        for item in root.rglob("*")
        if item.is_file() and ".git" not in item.relative_to(root).parts
    ):
        relative_path = path.relative_to(root).as_posix()
        payload = path.read_bytes()
        digest.update(relative_path.encode("utf-8"))
        digest.update(len(payload).to_bytes(8, byteorder="big"))
        digest.update(hashlib.sha256(payload).digest())
    return digest.hexdigest()


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


def _replace_path(*, source_path: Path, destination_path: Path) -> None:
    """Replace one destination path with a staged source path."""
    if destination_path.exists():
        if destination_path.is_dir():
            shutil.rmtree(destination_path)
        else:
            destination_path.unlink()
    destination_path.parent.mkdir(parents=True, exist_ok=True)
    if source_path.is_dir():
        shutil.copytree(source_path, destination_path)
    else:
        shutil.copy2(source_path, destination_path)


def promote_staging_root(*, staging_root: Path, publication_root: Path) -> None:
    """Promote the verified staging tree while preserving git repository metadata."""
    if not staging_root.exists():
        raise StageExecutionError(f"Publication staging root does not exist: {staging_root}")
    publication_root.parent.mkdir(parents=True, exist_ok=True)
    if not publication_root.exists():
        shutil.move(str(staging_root), str(publication_root))
        return

    if (publication_root / ".git").exists():
        staged_st_root = staging_root / "st"
        if staged_st_root.exists():
            for child in sorted(staged_st_root.iterdir(), key=lambda item: item.name):
                _replace_path(
                    source_path=child,
                    destination_path=publication_root / "st" / child.name,
                )
        for child in sorted(
            (item for item in staging_root.iterdir() if item.name != "st"),
            key=lambda item: item.name,
        ):
            _replace_path(
                source_path=child,
                destination_path=publication_root / child.name,
            )
        shutil.rmtree(staging_root)
        return

    shutil.rmtree(publication_root)
    shutil.move(str(staging_root), str(publication_root))
