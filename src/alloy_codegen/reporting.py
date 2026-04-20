"""Stage payload models and validation reporting."""

from __future__ import annotations

from dataclasses import dataclass, field

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.manifests import ArtifactManifest, PatchManifest, SourceManifest
from alloy_codegen.serialization import to_primitive


@dataclass(frozen=True, slots=True)
class FetchBundle:
    """Payload for the fetch stage."""

    source_manifest: SourceManifest


@dataclass(frozen=True, slots=True)
class PatchBundle:
    """Payload for the patch stage."""

    source_manifest: SourceManifest
    patch_manifest: PatchManifest
    device_patches: tuple[dict[str, object], ...]


@dataclass(frozen=True, slots=True)
class NormalizationBundle:
    """Payload for the normalize stage."""

    source_manifest: SourceManifest
    patch_manifest: PatchManifest
    devices: tuple[CanonicalDeviceIR, ...]


@dataclass(frozen=True, slots=True)
class ValidationRuleResult:
    """One validation rule result."""

    rule_id: str
    category: str
    severity: str
    passed: bool
    message: str


@dataclass(frozen=True, slots=True)
class ValidationGateStatus:
    """One maturity gate status."""

    gate_id: str
    passed: bool
    blocking: bool
    message: str
    rule_ids: tuple[str, ...]


@dataclass(frozen=True, slots=True)
class SystemDescriptorDomainStatus:
    """Publishability status for one required system-descriptor domain."""

    domain_id: str
    passed: bool
    draft: bool
    message: str
    rule_ids: tuple[str, ...]


@dataclass(frozen=True, slots=True)
class ValidationReport:
    """Validation report emitted by the validate stage."""

    report_id: str
    scope: dict[str, str | None]
    results: tuple[ValidationRuleResult, ...]
    gates: tuple[ValidationGateStatus, ...]
    system_descriptor_domains: tuple[SystemDescriptorDomainStatus, ...] = field(
        default=(),
        metadata={"omit_if_empty": True},
    )

    @property
    def is_passing(self) -> bool:
        blocking_gates = [gate for gate in self.gates if gate.blocking]
        return all(gate.passed for gate in blocking_gates) and not (
            self.draft_system_descriptor_domains
        )

    @property
    def draft_system_descriptor_domains(self) -> tuple[str, ...]:
        return tuple(domain.domain_id for domain in self.system_descriptor_domains if domain.draft)

    def gate_status(self, gate_id: str) -> ValidationGateStatus:
        for gate in self.gates:
            if gate.gate_id == gate_id:
                return gate
        raise KeyError(f"Unknown validation gate '{gate_id}'.")

    def system_descriptor_status(self, domain_id: str) -> SystemDescriptorDomainStatus:
        for domain in self.system_descriptor_domains:
            if domain.domain_id == domain_id:
                return domain
        raise KeyError(f"Unknown system descriptor domain '{domain_id}'.")

    def to_dict(self) -> dict[str, object]:
        payload = to_primitive(self)
        payload["is_passing"] = self.is_passing
        payload["draft_system_descriptor_domains"] = list(self.draft_system_descriptor_domains)
        return payload


@dataclass(frozen=True, slots=True)
class ValidationBundle:
    """Payload for the validate stage."""

    source_manifest: SourceManifest
    patch_manifest: PatchManifest
    devices: tuple[CanonicalDeviceIR, ...]
    report: ValidationReport

    def to_dict(self) -> dict[str, object]:
        return {
            "source_manifest": self.source_manifest.to_dict(),
            "patch_manifest": self.patch_manifest.to_dict(),
            "devices": [device.to_dict() for device in self.devices],
            "report": self.report.to_dict(),
        }


@dataclass(frozen=True, slots=True)
class EmittedArtifact:
    """One planned emitted artifact."""

    path: str
    artifact_kind: str
    content: str | None = None
    content_sha256: str | None = None
    content_bytes: int | None = None
    materialized_path: str | None = None


@dataclass(frozen=True, slots=True)
class EmissionPlan:
    """Payload for the emit stage."""

    artifact_manifest: ArtifactManifest
    artifacts: tuple[EmittedArtifact, ...]


@dataclass(frozen=True, slots=True)
class LinkerScriptVerification:
    """Result of validating a generated linker script with a smoke link step."""

    attempted: bool
    succeeded: bool
    linker_script: str
    source_file: str
    object_file: str
    output_file: str
    map_file: str
    command: tuple[str, ...] = ()
    stdout: str = ""
    stderr: str = ""
    skipped_reason: str | None = None


@dataclass(frozen=True, slots=True)
class ConsumerVerification:
    """Result of compiling a published-artifact smoke consumer."""

    consumer_id: str
    compiler: str
    source_file: str
    startup_source: str
    build_dir: str
    executable_path: str
    command: tuple[str, ...]
    succeeded: bool
    stdout: str
    stderr: str
    linker_script_verification: LinkerScriptVerification | None = None


@dataclass(frozen=True, slots=True)
class PublicationPlan:
    """Payload for the publish stage."""

    target_repository: str
    publication_mode: str
    artifact_root: str
    publication_root: str
    artifact_manifest: ArtifactManifest | None
    artifacts: tuple[EmittedArtifact, ...]
    published_artifacts: tuple[EmittedArtifact, ...] = ()
    target_artifact_revision: str | None = None
    consumer_verification: ConsumerVerification | None = None
    publication_record: EmittedArtifact | None = None
    publication_summary: EmittedArtifact | None = None
    draft_system_descriptor_domains: tuple[str, ...] = ()
