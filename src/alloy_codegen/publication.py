"""Publication helpers for alloy-devices outputs."""

from __future__ import annotations

import hashlib
import json
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
            "draft_system_descriptor_domains": list(
                validation_report.draft_system_descriptor_domains
            ),
            "gates": to_primitive(validation_report.gates),
            "system_descriptor_domains": to_primitive(validation_report.system_descriptor_domains),
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
        path=f"{family_dir}/reports/publication-record.json",
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


def _load_device_capability_ids(path: Path) -> tuple[str, ...]:
    """Load one published runtime capability sidecar and return stable capability ids."""
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except json.JSONDecodeError as exc:
        raise StageExecutionError(
            f"Invalid published capability sidecar {path}: {exc.msg}"
        ) from exc
    capabilities = payload.get("capabilities")
    if not isinstance(capabilities, list):
        raise StageExecutionError(f"Published capability sidecar {path} has no capability list.")
    capability_ids: list[str] = []
    for entry in capabilities:
        capability_id = entry.get("capability_id") if isinstance(entry, dict) else None
        if not isinstance(capability_id, str) or not capability_id:
            raise StageExecutionError(
                f"Published capability sidecar {path} has an invalid capability_id entry."
            )
        capability_ids.append(capability_id)
    return tuple(sorted(capability_ids))


def _tracks_capability_regression(capability_id: str) -> bool:
    """Return whether a capability id is part of the stable runtime regression surface.

    Legacy ``capability:*`` and ``capability-instance:*`` ids are generated from the older
    connector-facing metadata model and are intentionally excluded from publish-time regression
    blocking while the runtime-only contract becomes authoritative. Stable runtime capability ids
    are emitted under the ``runtime-`` prefix.
    """

    return capability_id.startswith("runtime-")


def find_capability_regressions(
    *,
    publication_root: Path,
    staging_root: Path,
    family_dir: str,
) -> tuple[str, ...]:
    """Compare staged and previously published capability sidecars for removed capability ids."""
    published_family_root = publication_root / family_dir
    staged_family_root = staging_root / family_dir
    if not published_family_root.exists() or not staged_family_root.exists():
        return ()

    staged_sidecars = sorted(
        staged_family_root.glob("generated/runtime/devices/*/capabilities.json"),
        key=lambda item: item.as_posix(),
    )
    regressions: list[str] = []
    for staged_sidecar in staged_sidecars:
        device = staged_sidecar.parent.name
        published_sidecar = (
            published_family_root
            / "generated"
            / "runtime"
            / "devices"
            / device
            / "capabilities.json"
        )
        if not published_sidecar.exists():
            continue
        published_ids = {
            capability_id
            for capability_id in _load_device_capability_ids(published_sidecar)
            if _tracks_capability_regression(capability_id)
        }
        staged_ids = {
            capability_id
            for capability_id in _load_device_capability_ids(staged_sidecar)
            if _tracks_capability_regression(capability_id)
        }
        removed_ids = sorted(published_ids - staged_ids)
        if removed_ids:
            sample = ", ".join(removed_ids[:6])
            if len(removed_ids) > 6:
                sample = f"{sample}, ..."
            regressions.append(f"{device} removed capability ids: {sample}")
    return tuple(regressions)


_FAMILY_MARKER_NAMES: frozenset[str] = frozenset(
    {"generated", "metadata", "reports", "artifact-manifest.json"}
)


def _looks_like_vendor_dir(path: Path) -> bool:
    """Return True when ``path`` looks like a vendor directory in a publication tree.

    A vendor directory holds per-family subdirectories (e.g. ``st/stm32g0/``,
    ``microchip/avr-da/``), each of which carries family-artifact markers
    like ``generated/``, ``metadata/``, ``reports/`` or ``artifact-manifest.json``.
    This heuristic lets :func:`promote_staging_root` preserve sibling families
    under the same vendor without special-casing vendor names.
    """
    if not path.is_dir():
        return False
    for child in path.iterdir():
        if not child.is_dir():
            continue
        if any((child / marker).exists() for marker in _FAMILY_MARKER_NAMES):
            return True
    return False


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
        # Promote staging into a live git checkout, preserving sibling families
        # under the same vendor that aren't part of this publication scope.
        #
        # Each publish invocation is scoped to one (vendor, family) pair and
        # only materialises ``staging_root/<vendor>/<family>/...``.  Replacing
        # the whole vendor directory would wipe any OTHER family published
        # earlier (e.g. microchip/same70 when publishing microchip/avr-da, or
        # espressif/esp32c3 when publishing espressif/esp32s3) — the
        # alloy-devices publish workflow then commits that deletion, dropping
        # previously-published families from the repo.
        #
        # Top-level non-vendor children (e.g. release reports, READMEs) are
        # still replaced wholesale so publication metadata stays in sync.
        vendor_dirs = tuple(
            child
            for child in sorted(staging_root.iterdir(), key=lambda item: item.name)
            if child.is_dir() and _looks_like_vendor_dir(child)
        )
        for vendor_dir in vendor_dirs:
            destination_vendor_dir = publication_root / vendor_dir.name
            destination_vendor_dir.mkdir(parents=True, exist_ok=True)
            for family_dir in sorted(vendor_dir.iterdir(), key=lambda item: item.name):
                _replace_path(
                    source_path=family_dir,
                    destination_path=destination_vendor_dir / family_dir.name,
                )
        vendor_names = {vendor_dir.name for vendor_dir in vendor_dirs}
        for child in sorted(
            (item for item in staging_root.iterdir() if item.name not in vendor_names),
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
