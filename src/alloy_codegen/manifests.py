"""Manifest models for source, patch, and artifact traceability."""

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.scope import PipelineScope
from alloy_codegen.serialization import to_primitive


@dataclass(frozen=True, slots=True)
class SourceRecord:
    """One upstream source entry."""

    source_id: str
    target_device: str
    origin_url: str
    revision: str
    local_path: str
    upstream_path: str
    scope: dict[str, str | None]


@dataclass(frozen=True, slots=True)
class SourceManifest:
    """Manifest emitted by the fetch stage."""

    manifest_kind: str
    bootstrap_family: str
    targets: tuple[str, ...]
    sources: tuple[SourceRecord, ...]

    def to_dict(self) -> dict[str, object]:
        return to_primitive(self)


@dataclass(frozen=True, slots=True)
class PatchRecord:
    """One patch declaration."""

    patch_id: str
    description: str


@dataclass(frozen=True, slots=True)
class PatchManifest:
    """Manifest emitted by the patch stage."""

    manifest_kind: str
    bootstrap_family: str
    targets: tuple[str, ...]
    applied_patches: tuple[PatchRecord, ...]

    def to_dict(self) -> dict[str, object]:
        return to_primitive(self)


@dataclass(frozen=True, slots=True)
class ArtifactBuildMetadata:
    """Deterministic metadata describing the emission contract."""

    pipeline_name: str
    artifact_layout_version: str
    cpp_contract_version: str
    target_repository: str


@dataclass(frozen=True, slots=True)
class ArtifactManifest:
    """Manifest tying emitted artifacts back to upstream and IR inputs."""

    manifest_kind: str
    generator_version: str
    ir_schema_version: str
    scope: dict[str, str | None]
    canonical_ir_sha256: str
    validation_report_id: str
    validation_report_sha256: str
    source_manifest: dict[str, object]
    patch_manifest: dict[str, object]
    build_metadata: ArtifactBuildMetadata

    @classmethod
    def for_scope(
        cls,
        *,
        generator_version: str,
        ir_schema_version: str,
        scope: PipelineScope,
        source_manifest: SourceManifest,
        patch_manifest: PatchManifest,
        canonical_ir_sha256: str,
        validation_report_id: str,
        validation_report_sha256: str,
        pipeline_name: str,
        artifact_layout_version: str,
        cpp_contract_version: str,
        target_repository: str,
    ) -> ArtifactManifest:
        return cls(
            manifest_kind="artifact-manifest-v1",
            generator_version=generator_version,
            ir_schema_version=ir_schema_version,
            scope=scope.to_dict(),
            canonical_ir_sha256=canonical_ir_sha256,
            validation_report_id=validation_report_id,
            validation_report_sha256=validation_report_sha256,
            source_manifest=source_manifest.to_dict(),
            patch_manifest=patch_manifest.to_dict(),
            build_metadata=ArtifactBuildMetadata(
                pipeline_name=pipeline_name,
                artifact_layout_version=artifact_layout_version,
                cpp_contract_version=cpp_contract_version,
                target_repository=target_repository,
            ),
        )

    def to_dict(self) -> dict[str, object]:
        return to_primitive(self)
