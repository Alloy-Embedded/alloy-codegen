"""Compute which admitted (vendor, family) pairs a git diff affects.

Used by the publish workflow to scope its matrix dynamically — a commit
that only touches one family's canonical YAML publishes only that
family; a change in shared codegen logic conservatively triggers the
full matrix.

After ``consume-alloy-devices-yml-as-canonical-input`` Phase 5 the
file-→ family resolution is simple:

* Paths matching ``data/devices/vendors/<vendor>/<family>/...`` map
  to that family.
* Anything else (codegen, schema, tests, infra) goes full matrix.
"""

from __future__ import annotations

import re
import subprocess
from collections.abc import Iterable
from dataclasses import dataclass
from pathlib import Path

from alloy_codegen.bootstrap import DEVICE_REGISTRY


@dataclass(frozen=True, slots=True)
class AffectedSet:
    """Resolved (vendor, family) set the workflow should publish.

    ``all_families`` is True when the change either explicitly targets
    every admitted family or when the heuristic falls back
    conservatively (unknown path, missing diff, malformed input).
    ``families`` always carries the fully-expanded list — it equals
    ``DEVICE_REGISTRY.keys()`` when ``all_families`` is True so
    workflow consumers can ignore the flag and iterate the tuple
    directly.
    """

    all_families: bool
    families: tuple[tuple[str, str], ...]

    def to_workflow_matrix(self) -> list[dict[str, str]]:
        """Render the matrix entries the publish workflow expects.

        Each entry is a `{"vendor": str, "family": str}` mapping
        suitable for ``strategy.matrix.include`` via ``fromJson()``.
        """
        return [{"vendor": vendor, "family": family} for vendor, family in self.families]


_DEVICE_YAML_PATTERN = re.compile(
    r"^data/devices/vendors/(?P<vendor>[^/]+)/(?P<family>[^/]+)/.+"
)


def _all_families_set() -> AffectedSet:
    return AffectedSet(
        all_families=True,
        families=tuple(sorted(DEVICE_REGISTRY)),
    )


def compute_affected(paths: Iterable[str]) -> AffectedSet:
    """Resolve the affected ``(vendor, family)`` set from a sequence
    of changed paths.

    Returns the full matrix when at least one path is unrecognised
    or matches shared infrastructure (``src/``, ``schema/``,
    ``tests/``, etc.).  Returns the matching subset only when every
    path falls under
    ``data/devices/vendors/<vendor>/<family>/``.
    """
    affected: set[tuple[str, str]] = set()
    for path in paths:
        match = _DEVICE_YAML_PATTERN.match(path)
        if match is None:
            return _all_families_set()
        key = (match.group("vendor"), match.group("family"))
        if key not in DEVICE_REGISTRY:
            return _all_families_set()
        affected.add(key)
    if not affected:
        return _all_families_set()
    return AffectedSet(all_families=False, families=tuple(sorted(affected)))


def compute_diff_paths(*, base_ref: str = "HEAD~1") -> tuple[str, ...] | None:
    """Run ``git diff --name-only <base_ref>...HEAD`` and return the
    changed paths.  Returns ``None`` when the git invocation fails —
    callers should treat that as "go full matrix".
    """
    try:
        result = subprocess.run(
            ["git", "diff", "--name-only", f"{base_ref}...HEAD"],
            cwd=Path(__file__).resolve().parents[2],
            capture_output=True,
            text=True,
            check=True,
        )
    except (subprocess.CalledProcessError, FileNotFoundError):
        return None
    return tuple(line.strip() for line in result.stdout.splitlines() if line.strip())


__all__ = [
    "AffectedSet",
    "compute_affected",
    "compute_diff_paths",
]
