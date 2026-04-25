"""Compute which admitted (vendor, family) pairs a git diff affects.

Used by the publish workflow to scope its matrix dynamically — a commit that
only touches one family's patches publishes only that family, while a change
in shared codegen logic conservatively triggers the full matrix.

The mapping is path-based, not AST-based: simple, deterministic, and easy to
maintain.  When a path doesn't match any rule, we fall back to "all families"
so we never silently publish stale artefacts (false positives are preferred
over false negatives).

Public surface:

- :class:`AffectedSet` — frozen dataclass carrying ``all_families`` + the
  resolved ``families`` tuple.
- :func:`compute_affected` — pure function from diff paths + registry.
- :func:`compute_diff_paths` — shells out to ``git diff --name-only`` with
  graceful fallback (returns ``None`` when the diff command fails, signalling
  "go full matrix").

See ``add-publication-scale-features`` for the spec deltas.
"""

from __future__ import annotations

import re
import subprocess
from collections.abc import Iterable, Mapping
from dataclasses import dataclass
from pathlib import Path
from typing import cast

from alloy_codegen.bootstrap import DEVICE_REGISTRY, SOURCE_BUNDLES

# ---------------------------------------------------------------------------
# Result type
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class AffectedSet:
    """Resolved (vendor, family) set the workflow should publish.

    ``all_families`` is True when the change either explicitly targets every
    admitted family or when the heuristic falls back conservatively (unknown
    path, missing diff, malformed input).  ``families`` always carries the
    fully-expanded list — it equals ``DEVICE_REGISTRY.keys()`` when
    ``all_families`` is True so workflow consumers can ignore the flag and
    iterate the tuple directly.
    """

    all_families: bool
    families: tuple[tuple[str, str], ...]

    def to_workflow_matrix(self) -> list[dict[str, str]]:
        """Render the matrix entries the publish workflow expects.

        Each entry is a `{"vendor": str, "family": str}` mapping suitable for
        ``strategy.matrix.include`` via ``fromJson()``.
        """
        return [{"vendor": vendor, "family": family} for vendor, family in self.families]


# ---------------------------------------------------------------------------
# Path patterns
# ---------------------------------------------------------------------------


# Order matters — first match wins.  Tuples are (regex, handler-name).
_PATCH_PATTERN = re.compile(r"^patches/(?P<vendor>[^/]+)/(?P<family>[^/]+)/.+")
_SOURCE_ADAPTER_PATTERN = re.compile(r"^src/alloy_codegen/sources/(?P<source>[^/]+)\.py$")
_RUNTIME_STARTUP_PATTERN = re.compile(
    r"^src/alloy_codegen/runtime_(?P<arch>xtensa|riscv|avr)_startup\.py$"
)
_CORTEX_M_STARTUP_PATTERN = re.compile(r"^src/alloy_codegen/runtime_startup\.py$")
_OTHER_SRC_PATTERN = re.compile(r"^src/alloy_codegen/.+\.py$")


# Source-adapter basename → families that consume it (via SOURCE_BUNDLES).
# Maintained dynamically so adding a new adapter or family keeps this in sync.
def _families_for_source_adapter(source_basename: str) -> tuple[tuple[str, str], ...]:
    """Resolve `(vendor, family)` set whose SOURCE_BUNDLES references this adapter.

    The mapping recognises a few well-known adapter→source-id aliases:

    - ``esp_idf`` / ``espressif_svd`` → ``espressif-svd``
    - ``cmsis_svd`` → ``cmsis-svd-data``
    - ``stm32_open_pin_data`` → ``stm32-open-pin-data``
    - ``microchip_dfp`` → ``microchip-dfp-pack``, ``microchip-dfp-extract``
    - ``nxp_mcux`` / ``nxp_mcux_sdk`` → ``nxp-mcux-soc-svd``, ``nxp-mcux-sdk``
    - ``pico_sdk`` → ``pico-sdk``
    - ``raw`` → all families (raw is shared infrastructure)
    """
    if source_basename == "raw":
        return tuple(sorted(DEVICE_REGISTRY.keys()))
    aliases: dict[str, frozenset[str]] = {
        "esp_idf": frozenset({"espressif-svd"}),
        "espressif_svd": frozenset({"espressif-svd"}),
        "cmsis_svd": frozenset({"cmsis-svd-data"}),
        "stm32_open_pin_data": frozenset({"stm32-open-pin-data"}),
        "microchip_dfp": frozenset({"microchip-dfp-pack", "microchip-dfp-extract"}),
        "nxp_mcux": frozenset({"nxp-mcux-soc-svd", "nxp-mcux-sdk"}),
        "nxp_mcux_sdk": frozenset({"nxp-mcux-soc-svd", "nxp-mcux-sdk"}),
        "pico_sdk": frozenset({"pico-sdk"}),
    }
    source_ids = aliases.get(source_basename)
    if source_ids is None:
        # Unknown adapter — fall back to all families (conservative).
        return tuple(sorted(DEVICE_REGISTRY.keys()))
    affected: set[tuple[str, str]] = set()
    for key, bundles in SOURCE_BUNDLES.items():
        if any(bundle in source_ids for bundle in bundles):
            affected.add(key)
    return tuple(sorted(affected))


# Architecture → core prefixes.  Used by `runtime_<arch>_startup.py` matching.
_ARCH_TO_CORE_PREFIXES: dict[str, tuple[str, ...]] = {
    "xtensa": ("xtensa",),
    "riscv": ("rv32imc", "rv32imac", "riscv"),
    "avr": ("avr",),
}


def _families_with_core_prefix(prefixes: tuple[str, ...]) -> tuple[tuple[str, str], ...]:
    """Return admitted families whose first device's core matches one of the prefixes.

    The lookup uses the device patches lazily — but for the path-detection
    heuristic we don't actually load patches; we hardcode known mappings here.
    Hardcoded because: this set is small (9 entries today) and walking every
    device patch from CI for every diff is slow.  When a new family is admitted
    its mapping is added below.

    If a (vendor, family) is in DEVICE_REGISTRY but not in this static map,
    falls back to including it (so unmapped admissions don't silently miss
    refresh on architecture-specific changes).
    """
    static_core_map: dict[tuple[str, str], str] = {
        ("espressif", "esp32"): "xtensa-lx6",
        ("espressif", "esp32c3"): "rv32imc",
        ("espressif", "esp32s3"): "xtensa-lx7",
        ("microchip", "avr-da"): "avr8",
        ("microchip", "same70"): "cortex-m7f",
        ("nxp", "imxrt1060"): "cortex-m7f",
        ("raspberrypi", "rp2040"): "cortex-m0plus-dual",
        ("st", "stm32f4"): "cortex-m4f",
        ("st", "stm32g0"): "cortex-m0plus",
    }
    affected: set[tuple[str, str]] = set()
    for key in DEVICE_REGISTRY:
        core = static_core_map.get(key)
        if core is None:
            # Unknown family — conservative: include it.
            affected.add(key)
            continue
        if any(core.startswith(prefix) for prefix in prefixes):
            affected.add(key)
    return tuple(sorted(affected))


def _families_with_cortex_m_core() -> tuple[tuple[str, str], ...]:
    return _families_with_core_prefix(("cortex-m",))


# ---------------------------------------------------------------------------
# Per-path classifier
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class _PathVerdict:
    """Outcome of classifying one path."""

    all_families: bool = False
    families: frozenset[tuple[str, str]] = frozenset()
    skip: bool = False  # True = path doesn't affect publication at all


def _classify_path(path: str, *, registry_keys: frozenset[tuple[str, str]]) -> _PathVerdict:
    """Map one git-diff path to its publication impact."""
    # Skip paths that NEVER affect published artefacts.
    if (
        path.startswith("tests/")
        or path.startswith("openspec/")
        or path == ".github/workflows/bootstrap-family.yml"
        or path.endswith(".md")
    ):
        return _PathVerdict(skip=True)

    # Whole-matrix triggers (workflow self-modify, dependency lock, top-level config).
    if (
        path == ".github/workflows/publish-alloy-devices.yml"
        or path == "pyproject.toml"
        or path == "uv.lock"
        or path.startswith(".github/workflows/")
    ):
        return _PathVerdict(all_families=True)

    # Per-family patch.
    match = _PATCH_PATTERN.match(path)
    if match is not None:
        candidate = (match.group("vendor"), match.group("family"))
        if candidate in registry_keys:
            return _PathVerdict(families=frozenset({candidate}))
        # Patches under an unknown family — fall back conservatively.
        return _PathVerdict(all_families=True)

    # Per-source adapter.
    match = _SOURCE_ADAPTER_PATTERN.match(path)
    if match is not None:
        return _PathVerdict(families=frozenset(_families_for_source_adapter(match.group("source"))))

    # Per-arch runtime startup emitter.
    match = _RUNTIME_STARTUP_PATTERN.match(path)
    if match is not None:
        prefixes = _ARCH_TO_CORE_PREFIXES[match.group("arch")]
        return _PathVerdict(families=frozenset(_families_with_core_prefix(prefixes)))

    # Cortex-M shared startup emitter.
    if _CORTEX_M_STARTUP_PATTERN.match(path) is not None:
        return _PathVerdict(families=frozenset(_families_with_cortex_m_core()))

    # Any other src/alloy_codegen/**.py change → conservative full matrix.
    if _OTHER_SRC_PATTERN.match(path) is not None:
        return _PathVerdict(all_families=True)

    # Unknown path — conservative full matrix.
    return _PathVerdict(all_families=True)


# ---------------------------------------------------------------------------
# Public entry points
# ---------------------------------------------------------------------------


def compute_affected(
    diff_paths: Iterable[str],
    *,
    registry: Mapping[tuple[str, str], tuple[str, ...]] | None = None,
) -> AffectedSet:
    """Compute the affected (vendor, family) set from a sequence of git-diff paths.

    Returns an :class:`AffectedSet` with ``all_families`` flagged when the
    change has a global blast radius (or when no rule matched a path).
    """
    registry_map = dict(registry) if registry is not None else dict(DEVICE_REGISTRY)
    registry_keys = frozenset(registry_map.keys())
    paths = tuple(diff_paths)
    if not paths:
        # Empty diff → no families to publish.  This is distinct from "no
        # paths matched" — empty input is honest "nothing changed".
        return AffectedSet(all_families=False, families=())

    accumulated: set[tuple[str, str]] = set()
    saw_global = False
    saw_any_change = False
    for path in paths:
        verdict = _classify_path(path, registry_keys=registry_keys)
        if verdict.skip:
            continue
        saw_any_change = True
        if verdict.all_families:
            saw_global = True
            break
        accumulated.update(verdict.families)

    if saw_global:
        return AffectedSet(
            all_families=True,
            families=tuple(sorted(registry_keys)),
        )
    if not saw_any_change:
        # All paths were docs/openspec/test-only.
        return AffectedSet(all_families=False, families=())
    return AffectedSet(all_families=False, families=tuple(sorted(accumulated)))


def all_admitted_families(
    *, registry: Mapping[tuple[str, str], tuple[str, ...]] | None = None
) -> AffectedSet:
    """Return the full admitted set (used by ``--force-all`` and diff failure)."""
    registry_keys = (
        tuple(sorted(registry.keys()))
        if registry is not None
        else tuple(sorted(DEVICE_REGISTRY.keys()))
    )
    return AffectedSet(all_families=True, families=registry_keys)


def compute_diff_paths(
    *,
    since: str,
    head: str = "HEAD",
    repo_root: Path | None = None,
) -> tuple[str, ...] | None:
    """Resolve the file paths git considers changed between ``since`` and ``head``.

    Returns ``None`` when the diff command fails — callers treat this as
    "fall back to all families" (safe default).  Returns an empty tuple when
    the diff succeeds with no changes.
    """
    cwd = str(repo_root) if repo_root is not None else None
    try:
        completed = subprocess.run(
            ["git", "diff", "--name-only", f"{since}...{head}"],
            check=False,
            capture_output=True,
            text=True,
            cwd=cwd,
        )
    except FileNotFoundError:
        return None
    if completed.returncode != 0:
        return None
    return tuple(line.strip() for line in completed.stdout.splitlines() if line.strip())


def compute_affected_from_git(
    *,
    since: str,
    head: str = "HEAD",
    repo_root: Path | None = None,
    force_all: bool = False,
) -> AffectedSet:
    """High-level helper combining diff resolution and classification.

    When ``force_all`` is set, returns :func:`all_admitted_families` directly.
    When the underlying ``git diff`` fails (returns ``None``), also falls back
    to all admitted families — this matches the design's "safe default" rule.
    """
    if force_all:
        return all_admitted_families()
    diff_paths = compute_diff_paths(since=since, head=head, repo_root=repo_root)
    if diff_paths is None:
        return all_admitted_families()
    return compute_affected(diff_paths)


def serialize_affected_set(affected: AffectedSet, *, since: str, head: str) -> dict[str, object]:
    """Render an :class:`AffectedSet` as the JSON payload the CLI prints."""
    return {
        "since": since,
        "head": head,
        "all_families": affected.all_families,
        "families": [{"vendor": vendor, "family": family} for vendor, family in affected.families],
        # Convenience field for workflow consumers — `should_publish=false`
        # means the matrix is empty AND no family was affected (docs-only push).
        "should_publish": bool(affected.families) or affected.all_families,
        # Pre-rendered matrix list so workflow can do `fromJson(... ).matrix`.
        "matrix": cast(object, affected.to_workflow_matrix()),
    }
