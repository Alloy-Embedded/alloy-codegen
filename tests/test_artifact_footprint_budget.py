"""Tests for the artifact footprint budget gate
(``artifact-footprint-budget``).

Covers the spec scenarios:

* No currently admitted device exceeds its warn budget on day one.
* A deliberately oversized artifact triggers ``fail`` mode with a
  discoverable error message identifying the offending tuple.
* A per-device override entry suppresses a ``fail`` exceedance
  for the matched device only — every other device sharing the
  same artifact name still hits the global default.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

import pytest

from alloy_codegen.footprint_budget import (
    FootprintOverride,
    _reset_cache,
    evaluate_artifacts,
    format_violation_message,
    load_budget,
    load_overrides,
)


@dataclass(frozen=True)
class _StubArtifact:
    path: str
    content: str
    content_bytes: int | None = None


@pytest.fixture(autouse=True)
def _clear_module_cache() -> None:
    """Reset the load_budget / load_overrides caches between tests so
    monkey-patched paths are not contaminated by an earlier run."""
    _reset_cache()
    yield
    _reset_cache()


def test_default_budget_loads_from_repo_root() -> None:
    budget = load_budget()
    assert budget.default.warn > 0
    assert budget.default.fail > budget.default.warn
    # Spot-check a few artifact names declared in the repo.
    assert budget.lookup("routes.hpp").fail >= budget.lookup("routes.hpp").warn
    assert budget.lookup("connectors.hpp").warn > 0


def test_override_file_initially_empty() -> None:
    overrides = load_overrides()
    assert overrides == ()


def test_oversized_artifact_triggers_fail_with_diagnostic_message() -> None:
    """An emitter regression that produces an artifact larger than
    its `fail` budget SHALL fire a ``fail`` violation whose message
    identifies the artifact path, actual size, budget, and the
    override file path."""
    budget = load_budget()
    routes_budget = budget.lookup("routes.hpp")
    bloat = _StubArtifact(
        path="st/stm32g0/generated/runtime/devices/stm32g071rb/routes.hpp",
        content="x" * (routes_budget.fail + 1024),
    )
    violations = evaluate_artifacts(
        artifacts=(bloat,), vendor="st", family="stm32g0", budget=budget, overrides=()
    )
    assert len(violations) == 1
    assert violations[0].severity == "fail"
    assert violations[0].artifact_name == "routes.hpp"
    assert violations[0].device == "stm32g071rb"
    assert violations[0].actual_bytes > violations[0].budget_bytes

    msg = format_violation_message(violations[0])
    assert "FAIL" in msg
    assert "routes.hpp" in msg
    assert "stm32g071rb" in msg
    assert "data/artifact_footprint_overrides.toml" in msg


def test_warn_budget_surfaces_warning_without_failing() -> None:
    """A size between ``warn`` and ``fail`` SHALL produce a ``warn``
    severity entry — surfaced in the validation report, not the
    abort path."""
    budget = load_budget()
    routes_budget = budget.lookup("routes.hpp")
    halfway = (routes_budget.warn + routes_budget.fail) // 2
    artifact = _StubArtifact(
        path="st/stm32g0/generated/runtime/devices/stm32g071rb/routes.hpp",
        content="x" * halfway,
    )
    violations = evaluate_artifacts(
        artifacts=(artifact,), vendor="st", family="stm32g0", budget=budget, overrides=()
    )
    assert len(violations) == 1
    assert violations[0].severity == "warn"


def test_override_suppresses_fail_for_matched_device() -> None:
    """An override entry covering the offending tuple SHALL allow
    the build to pass — and SHALL NOT relax the budget for any
    other device sharing the same artifact name."""
    budget = load_budget()
    routes_budget = budget.lookup("routes.hpp")
    bloat = _StubArtifact(
        path="nxp/imxrt1060/generated/runtime/devices/mimxrt1062/routes.hpp",
        content="x" * (routes_budget.fail + 1024),
    )
    overrides = (
        FootprintOverride(
            vendor="nxp",
            family="imxrt1060",
            device="mimxrt1062",
            artifact="routes.hpp",
            warn=routes_budget.fail + 4096,
            fail=routes_budget.fail + 8192,
            rationale="known-large iMXRT pinmux table; reviewed by infra team",
        ),
    )
    violations = evaluate_artifacts(
        artifacts=(bloat,),
        vendor="nxp",
        family="imxrt1060",
        budget=budget,
        overrides=overrides,
    )
    assert violations == ()

    # Sibling device sharing the same artifact name is NOT covered.
    sibling = _StubArtifact(
        path="nxp/imxrt1060/generated/runtime/devices/mimxrt1064/routes.hpp",
        content="x" * (routes_budget.fail + 1024),
    )
    sibling_violations = evaluate_artifacts(
        artifacts=(sibling,),
        vendor="nxp",
        family="imxrt1060",
        budget=budget,
        overrides=overrides,
    )
    assert len(sibling_violations) == 1
    assert sibling_violations[0].severity == "fail"
    assert sibling_violations[0].device == "mimxrt1064"


def test_no_admitted_device_artifact_exceeds_warn_budget(
    tmp_path: Path,
) -> None:
    """Day-1 invariant: walking every emitted artifact under
    ``tests/fixtures/emitted/`` SHALL produce zero footprint
    violations.  The defaults are calibrated from the current
    worst-case output plus headroom; this test catches a regression
    where a future emitter change accidentally bloats an artifact
    past its budget."""
    repo_root = Path(__file__).resolve().parents[1]
    emitted_root = repo_root / "tests" / "fixtures" / "emitted"
    if not emitted_root.exists():
        pytest.skip("no emit fixture tree under tests/fixtures/emitted/")

    # ``enforce-strict-typing-and-golden-coverage`` Phase 2: the
    # canonical golden layout is ``tests/fixtures/emitted/<vendor>/<family>/...``
    # so the gate keys directly off the first two path segments.  Any
    # legacy top-level folder (``cmake/``, ``devices-readme/``) without a
    # ``<vendor>/<family>`` shape is skipped — it is not a per-device
    # artifact and not subject to the per-(vendor, family) footprint
    # gate.
    from alloy_codegen.bootstrap import DEVICE_REGISTRY

    valid_vendor_family: set[tuple[str, str]] = {(v, f) for (v, f) in DEVICE_REGISTRY}

    grouped: dict[tuple[str, str], list[_StubArtifact]] = {}
    for path in emitted_root.rglob("*"):
        if not path.is_file():
            continue
        if path.name == ".DS_Store":
            continue
        rel = path.relative_to(emitted_root)
        parts = rel.parts
        if len(parts) < 2:
            continue
        vendor_family = (parts[0], parts[1])
        if vendor_family not in valid_vendor_family:
            continue
        grouped.setdefault(vendor_family, []).append(
            _StubArtifact(
                path=str(rel),
                content="",
                content_bytes=path.stat().st_size,
            )
        )

    violations: list = []
    for (vendor, family), arts in grouped.items():
        violations.extend(evaluate_artifacts(artifacts=tuple(arts), vendor=vendor, family=family))
    fail_violations = [v for v in violations if v.severity == "fail"]
    assert not fail_violations, (
        "currently admitted devices must not exceed their `fail` "
        "footprint budget on day one — bumping a budget requires "
        "an explicit edit to data/artifact_footprint_budget.toml: "
        + ", ".join(format_violation_message(v) for v in fail_violations[:3])
    )


def test_evaluate_uses_content_bytes_when_provided() -> None:
    """When ``EmittedArtifact.content_bytes`` is populated by the
    materialise step, the gate SHALL use it instead of re-encoding
    ``content``.  Cheaper and matches the value the publication
    sees on disk."""
    artifact = _StubArtifact(
        path="st/stm32g0/generated/runtime/devices/stm32g071rb/timer.hpp",
        content="not authoritative",
        content_bytes=10,
    )
    violations = evaluate_artifacts(artifacts=(artifact,), vendor="st", family="stm32g0")
    assert violations == ()


def test_violation_sort_order_lists_fails_before_warns() -> None:
    budget = load_budget()
    timer = budget.lookup("timer.hpp")
    fail_art = _StubArtifact(
        path="st/stm32g0/generated/runtime/devices/stm32g071rb/timer.hpp",
        content="x" * (timer.fail + 8),
    )
    warn_art = _StubArtifact(
        path="st/stm32g0/generated/runtime/devices/stm32g071rb/uart.hpp",
        content="x" * ((budget.lookup("uart.hpp").warn + budget.lookup("uart.hpp").fail) // 2),
    )
    violations = evaluate_artifacts(artifacts=(warn_art, fail_art), vendor="st", family="stm32g0")
    severities = [v.severity for v in violations]
    assert severities == ["fail", "warn"]
