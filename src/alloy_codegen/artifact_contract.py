"""Validation helpers for the generated runtime artifact contract."""

from __future__ import annotations

from alloy_codegen.reporting import EmittedArtifact


def find_runtime_cpp_string_violations(
    artifacts: tuple[EmittedArtifact, ...],
) -> tuple[str, ...]:
    """Return violations for generated runtime artifacts that still carry string literals."""

    violations: list[str] = []
    for artifact in artifacts:
        if artifact.artifact_kind != "generated-cpp":
            continue
        if "/generated/" not in f"/{artifact.path}":
            continue
        if artifact.content is None:
            continue
        for lineno, line in enumerate(artifact.content.splitlines(), start=1):
            stripped = line.strip()
            if stripped.startswith("#include") or stripped.startswith("#pragma once"):
                continue
            if '"' in line:
                violations.append(
                    f"{artifact.path}:{lineno} contains a string literal in runtime C++ output"
                )
    return tuple(violations)
