"""Per-device canonical YAML emitter.

Added by ``define-canonical-device-yaml-schema``.

For every admitted device, emit a schema-validated YAML file at
``<vendor>/<family>/generated/devices/<device>.yml`` that captures
the full :class:`CanonicalDeviceIR`.  Foundation of the
``alloy-devices-yml`` data-repo split — once consumers point at
the YAML instead of raw vendor sources, this emitter's output
becomes the canonical source of truth.

Tagged ``artifact_kind="generated-yaml"`` so the runtime-C++
string-literal gate skips the file (YAML payloads are not
firmware-image bytes).
"""

from __future__ import annotations

from alloy_codegen.canonical_device_yaml import serialize_device, validate_device
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact
from alloy_codegen.serialization import canonical_json_sha256


def _yaml_artifact(*, path: str, content: str) -> EmittedArtifact:
    """Wrap a YAML payload as an :class:`EmittedArtifact`.

    Distinct kind from ``generated-cpp`` / ``generated-cmake`` so
    publication gates that scan for C++ patterns don't misread
    the YAML as code.
    """
    content_bytes = len(content.encode("utf-8"))
    content_sha256 = canonical_json_sha256({"content": content})
    return EmittedArtifact(
        path=path,
        artifact_kind="generated-yaml",
        content=content,
        content_sha256=content_sha256,
        content_bytes=content_bytes,
    )


def emit_canonical_device_yaml(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit the canonical per-device YAML artifact.

    The emitter validates against the JSON Schema before returning
    so a schema regression fails the emit stage immediately rather
    than landing as a broken artifact downstream.
    """
    text = serialize_device(device)
    try:
        validate_device(text)
    except StageExecutionError:
        # Re-raise with the device path attached for diagnostics.
        raise StageExecutionError(
            f"canonical YAML for {device.identity.vendor}/"
            f"{device.identity.family}/{device.identity.device} "
            "failed schema validation; see prior message for details"
        ) from None
    return _yaml_artifact(
        path=f"{family_dir}/generated/devices/{device.identity.device}.yml",
        content=text,
    )


__all__ = ["emit_canonical_device_yaml"]
