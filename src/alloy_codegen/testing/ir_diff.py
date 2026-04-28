"""Structured diff between two `CanonicalDeviceIR` instances.

Used by `add-codegen-yaml-parity-gate` (Phase 0.3) to surface
which fields drifted when the YAML-loaded IR differs from the
legacy-built IR.

Approach: convert both IRs to `to_primitive(...)` dicts and
walk them path-by-path.  Anything that fails to compare equal
becomes one :class:`IRDiffEntry` row.
"""

from __future__ import annotations

from dataclasses import dataclass
from typing import Any

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.serialization import to_primitive


@dataclass(frozen=True, slots=True)
class IRDiffEntry:
    """One drifted field."""

    path: str
    legacy: Any
    yaml: Any

    def render(self, *, max_repr: int = 200) -> str:
        legacy_repr = repr(self.legacy)
        yaml_repr = repr(self.yaml)
        if len(legacy_repr) > max_repr:
            legacy_repr = legacy_repr[:max_repr] + "…"
        if len(yaml_repr) > max_repr:
            yaml_repr = yaml_repr[:max_repr] + "…"
        return f"  • {self.path}\n      legacy: {legacy_repr}\n      yaml:   {yaml_repr}"


def _walk(left: Any, right: Any, path: str, out: list[IRDiffEntry]) -> None:
    if isinstance(left, dict) and isinstance(right, dict):
        for key in sorted(set(left) | set(right)):
            sub_path = f"{path}.{key}" if path else key
            if key not in left:
                out.append(IRDiffEntry(path=sub_path, legacy=_MISSING, yaml=right[key]))
                continue
            if key not in right:
                out.append(IRDiffEntry(path=sub_path, legacy=left[key], yaml=_MISSING))
                continue
            _walk(left[key], right[key], sub_path, out)
        return
    if isinstance(left, list | tuple) and isinstance(right, list | tuple):
        if len(left) != len(right):
            out.append(IRDiffEntry(path=f"{path}[len]", legacy=len(left), yaml=len(right)))
            # Diff the prefix anyway so the failure message is useful.
        for index, (lhs, rhs) in enumerate(zip(left, right, strict=False)):
            _walk(lhs, rhs, f"{path}[{index}]", out)
        return
    if left != right:
        out.append(IRDiffEntry(path=path or "<root>", legacy=left, yaml=right))


_MISSING = object()


def ir_diff(legacy: CanonicalDeviceIR, yaml_loaded: CanonicalDeviceIR) -> tuple[IRDiffEntry, ...]:
    """Return a tuple of structural differences between two IRs.

    Equality at every path → empty tuple.  Compares via
    primitive projection to avoid IR-internal `object`-typed
    fields tripping over identity comparison.
    """
    legacy_p = to_primitive(legacy)
    yaml_p = to_primitive(yaml_loaded)
    diffs: list[IRDiffEntry] = []
    _walk(legacy_p, yaml_p, path="", out=diffs)
    return tuple(diffs)


def render_diffs(diffs: tuple[IRDiffEntry, ...], *, limit: int = 20) -> str:
    """Pretty-print diff entries for failure messages."""
    if not diffs:
        return "<no diffs>"
    rendered = "\n".join(d.render() for d in diffs[:limit])
    if len(diffs) > limit:
        rendered += f"\n  … {len(diffs) - limit} more diff(s) suppressed"
    return rendered


__all__ = ["IRDiffEntry", "ir_diff", "render_diffs"]
