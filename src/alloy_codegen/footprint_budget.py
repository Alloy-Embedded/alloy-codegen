"""Per-artifact byte-size footprint gate (artifact-footprint-budget).

The publish stage measures every emitted artifact's UTF-8 byte
size and compares it against a budget declared in
``data/artifact_footprint_budget.toml``.  An exceedance of the
``warn`` budget surfaces in the validation report as a footprint
warning; an exceedance of the ``fail`` budget aborts the build
unless an override entry in
``data/artifact_footprint_overrides.toml`` covers the offending
``(vendor, family, device, artifact_name)`` tuple.

The gate is non-disruptive on day one — defaults are derived from
the largest currently admitted device's actual output plus
headroom, so no admitted device fails today.
"""

from __future__ import annotations

import tomllib
from dataclasses import dataclass
from pathlib import Path

# Module-level cache so repeated calls within one publish run don't
# re-parse the TOML files.  Cleared by tests via ``_reset_cache``.
_BUDGET_CACHE: dict[Path, FootprintBudget] = {}
_OVERRIDE_CACHE: dict[Path, tuple[FootprintOverride, ...]] = {}


@dataclass(frozen=True, slots=True)
class _BudgetEntry:
    warn: int
    fail: int


@dataclass(frozen=True, slots=True)
class FootprintBudget:
    """Parsed ``data/artifact_footprint_budget.toml`` payload."""

    default: _BudgetEntry
    by_artifact: dict[str, _BudgetEntry]

    def lookup(self, artifact_name: str) -> _BudgetEntry:
        return self.by_artifact.get(artifact_name, self.default)


@dataclass(frozen=True, slots=True)
class FootprintOverride:
    vendor: str
    family: str
    device: str
    artifact: str
    warn: int
    fail: int
    rationale: str = ""


@dataclass(frozen=True, slots=True)
class FootprintViolation:
    """One artifact that exceeded its budget."""

    artifact_path: str
    artifact_name: str
    actual_bytes: int
    budget_bytes: int
    severity: str  # "warn" | "fail"
    vendor: str
    family: str
    device: str | None  # None for family-scoped artifacts


def _data_dir() -> Path:
    return Path(__file__).resolve().parents[2] / "data"


def _budget_path() -> Path:
    return _data_dir() / "artifact_footprint_budget.toml"


def _overrides_path() -> Path:
    return _data_dir() / "artifact_footprint_overrides.toml"


def _reset_cache() -> None:
    """Clear the module-level caches.  Test-only helper."""
    _BUDGET_CACHE.clear()
    _OVERRIDE_CACHE.clear()


def _parse_budget_entry(payload: dict[str, object]) -> _BudgetEntry:
    return _BudgetEntry(
        warn=int(payload.get("warn", 0) or 0),  # type: ignore[arg-type]
        fail=int(payload.get("fail", 0) or 0),  # type: ignore[arg-type]
    )


def load_budget(path: Path | None = None) -> FootprintBudget:
    target = path or _budget_path()
    if target in _BUDGET_CACHE:
        return _BUDGET_CACHE[target]
    if not target.exists():
        budget = FootprintBudget(
            default=_BudgetEntry(warn=2_000_000, fail=4_000_000),
            by_artifact={},
        )
    else:
        payload = tomllib.loads(target.read_text())
        default = _parse_budget_entry(payload.get("default") or {})  # type: ignore[arg-type]
        by_artifact: dict[str, _BudgetEntry] = {}
        artifact_block = payload.get("artifact") or {}
        if isinstance(artifact_block, dict):
            for name, entry in artifact_block.items():
                if isinstance(entry, dict):
                    by_artifact[str(name)] = _parse_budget_entry(entry)  # type: ignore[arg-type]
        budget = FootprintBudget(default=default, by_artifact=by_artifact)
    _BUDGET_CACHE[target] = budget
    return budget


def load_overrides(path: Path | None = None) -> tuple[FootprintOverride, ...]:
    target = path or _overrides_path()
    if target in _OVERRIDE_CACHE:
        return _OVERRIDE_CACHE[target]
    if not target.exists():
        _OVERRIDE_CACHE[target] = ()
        return ()
    payload = tomllib.loads(target.read_text())
    rows = payload.get("override") or []
    overrides: list[FootprintOverride] = []
    if isinstance(rows, list):
        for row in rows:
            if not isinstance(row, dict):
                continue
            overrides.append(
                FootprintOverride(
                    vendor=str(row.get("vendor", "")),
                    family=str(row.get("family", "")),
                    device=str(row.get("device", "")),
                    artifact=str(row.get("artifact", "")),
                    warn=int(row.get("warn", 0) or 0),  # type: ignore[arg-type]
                    fail=int(row.get("fail", 0) or 0),  # type: ignore[arg-type]
                    rationale=str(row.get("rationale", "")),
                )
            )
    result = tuple(overrides)
    _OVERRIDE_CACHE[target] = result
    return result


def _resolve_device_for_path(artifact_path: str) -> str | None:
    """Best-effort: extract a device id from an artifact path.

    Conventions:
      ``<vendor>/<family>/generated/runtime/devices/<device>/...``
      ``<vendor>/<family>/metadata/devices/<device>.json``

    Returns ``None`` for family-scoped artifacts (manifest, reports,
    etc.) — the override match for those falls through to artifact
    name only.
    """
    parts = artifact_path.split("/")
    if "devices" in parts:
        idx = parts.index("devices")
        if idx + 1 < len(parts):
            tail = parts[idx + 1]
            if tail.endswith(".json"):
                return tail[: -len(".json")]
            return tail
    return None


def evaluate_artifacts(
    *,
    artifacts: tuple[object, ...],
    vendor: str,
    family: str,
    budget: FootprintBudget | None = None,
    overrides: tuple[FootprintOverride, ...] | None = None,
) -> tuple[FootprintViolation, ...]:
    """Measure each emitted artifact's UTF-8 byte size and return
    every budget exceedance, ordered ``fail`` before ``warn``.

    ``artifacts`` is the tuple of ``EmittedArtifact``-shaped objects
    the emit stage produces (carries ``path`` + ``content`` +
    ``content_bytes``).  We use ``content_bytes`` when present and
    fall back to ``len(content.encode("utf-8"))`` so the gate works
    for both pre-materialized and freshly-built artifacts.
    """
    budget = budget or load_budget()
    overrides = overrides or load_overrides()

    violations: list[FootprintViolation] = []
    for artifact in artifacts:
        path = str(getattr(artifact, "path", ""))
        if not path:
            continue
        artifact_name = path.rsplit("/", 1)[-1]
        content_bytes = getattr(artifact, "content_bytes", None)
        if content_bytes is None:
            content = getattr(artifact, "content", "")
            content_bytes = len(str(content).encode("utf-8"))
        device = _resolve_device_for_path(path)
        entry = budget.lookup(artifact_name)
        warn_limit = entry.warn
        fail_limit = entry.fail
        # Override match: vendor + family + device + artifact_name.
        for override in overrides:
            if (
                override.vendor == vendor
                and override.family == family
                and override.artifact == artifact_name
                and (override.device == "" or override.device == (device or ""))
            ):
                warn_limit = override.warn or warn_limit
                fail_limit = override.fail or fail_limit
                break
        if fail_limit and content_bytes > fail_limit:
            violations.append(
                FootprintViolation(
                    artifact_path=path,
                    artifact_name=artifact_name,
                    actual_bytes=content_bytes,
                    budget_bytes=fail_limit,
                    severity="fail",
                    vendor=vendor,
                    family=family,
                    device=device,
                )
            )
        elif warn_limit and content_bytes > warn_limit:
            violations.append(
                FootprintViolation(
                    artifact_path=path,
                    artifact_name=artifact_name,
                    actual_bytes=content_bytes,
                    budget_bytes=warn_limit,
                    severity="warn",
                    vendor=vendor,
                    family=family,
                    device=device,
                )
            )
    # Stable order: fails first, then warns; both alphabetised by path
    # so the surfaced report is reproducible across runs.
    violations.sort(
        key=lambda v: (0 if v.severity == "fail" else 1, v.artifact_path)
    )
    return tuple(violations)


def format_violation_message(violation: FootprintViolation) -> str:
    """Render a one-line diagnostic suitable for warnings + abort
    messages.  Includes the full path, actual size, budget, and the
    override file path so a reviewer can act without grepping."""
    return (
        f"{violation.severity.upper()}: {violation.artifact_path} is "
        f"{violation.actual_bytes} bytes (>{violation.budget_bytes} "
        f"{violation.severity} budget); update the emitter or add an "
        f"override entry to data/artifact_footprint_overrides.toml "
        f"keyed on (vendor={violation.vendor!r}, "
        f"family={violation.family!r}, "
        f"device={violation.device!r}, "
        f"artifact={violation.artifact_name!r})."
    )
