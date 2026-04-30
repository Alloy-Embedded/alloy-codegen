"""Tests for the Phase 3 forbidden-pattern gate added by
``enforce-strict-typing-and-golden-coverage``.

Two checks are wired into the publish stage and verified here:

1. **Emitted runtime C++** SHALL NOT contain ``dynamic_cast`` or
   ``typeid`` — RTTI features are forbidden across the alloy
   contract because they pull in per-type metadata, defeat dead-code
   elimination, and contradict the compile-time type-discrimination
   model (concepts + typed enums).

2. **Emitter Python** under ``src/alloy_codegen/runtime_driver/``
   SHALL NOT raise — driver-semantics emitters return
   ``EmittedArtifact | None`` so a malformed device IR is signalled
   via an explicit None / empty-row-set, never an exception.  An
   escape hatch exists for the narrow case of contradictory-IR
   sanity checks: lines tagged
   ``# alloy-codegen-allow-raise: <reason>`` are exempt.
"""

from __future__ import annotations

from pathlib import Path

import pytest

from alloy_codegen.artifact_contract import (
    find_emitter_python_throw_violations,
    find_runtime_cpp_forbidden_pattern_violations,
)
from alloy_codegen.bootstrap import DEVICE_REGISTRY
from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _admitted_families() -> list[tuple[str, str]]:
    return sorted(DEVICE_REGISTRY.keys())


@pytest.mark.parametrize(
    ("vendor", "family"),
    _admitted_families(),
    ids=lambda pair: f"{pair[0]}/{pair[1]}" if isinstance(pair, tuple) else str(pair),
)
def test_emitted_cpp_carries_no_dynamic_cast_or_typeid(
    vendor: str, family: str, tmp_path: Path
) -> None:
    """For every admitted family, the emit pipeline SHALL produce
    runtime C++ artifacts free of ``dynamic_cast`` and ``typeid``."""
    ctx = ExecutionContext.default().with_overrides(
        artifact_root=str(tmp_path / "artifacts"),
    )
    result = run_emit(PipelineScope(vendor=vendor, family=family), ctx)
    violations = find_runtime_cpp_forbidden_pattern_violations(result.payload.artifacts)
    assert violations == (), (
        f"{vendor}/{family} emit produced forbidden RTTI patterns: " + "; ".join(violations[:5])
    )


def test_runtime_driver_emitter_python_does_not_raise() -> None:
    """Source-level invariant: every ``.py`` file under
    ``src/alloy_codegen/runtime_driver/`` is free of bare ``raise``
    statements (any legitimate raises must carry the
    ``# alloy-codegen-allow-raise: <reason>`` marker)."""
    repo_root = Path(__file__).resolve().parents[1]
    emitter_root = repo_root / "src" / "alloy_codegen" / "runtime_driver"
    violations = find_emitter_python_throw_violations(emitter_root)
    assert violations == (), (
        "emitter Python contains unannotated ``raise`` statements: " + "\n  ".join(violations[:5])
    )
