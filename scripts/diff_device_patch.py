"""Structured diff between an autogen draft patch and a curated
patch.

Added by ``autogen-device-patches-from-svd``.  Used to validate
the generator on already-admitted devices ("does the autogen
output cover what the curated patch encodes?") and to gauge how
much human review is left after running the generator.

The output is grouped into three sections:

* ``ONLY IN AUTOGEN``: keys/values present in the generator output
  but missing or empty in the curated patch.
* ``ONLY IN CURATED``: keys/values present in the curated patch
  but missing or empty in the generator output.
* ``CHANGED``: keys present in both with diverging values.

CLI:

    python -m scripts.diff_device_patch \\
        --autogen path/to/autogen.json \\
        --curated path/to/curated.json

Exit code is 0 even when diffs are present — the tool is a
reporter, not a gate.
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path
from typing import Any

# Keys that are scaffolding artefacts of the autogen output and
# should not contribute diff noise against curated patches.
_AUTOGEN_META_KEYS = frozenset({"$autogen", "$todo_review"})


def _load_json(path: Path) -> dict[str, Any]:
    return json.loads(path.read_text(encoding="utf-8"))


def _is_empty(value: Any) -> bool:
    if value is None:
        return True
    if isinstance(value, str) and value in ("", "TODO_REVIEW"):
        return True
    if isinstance(value, (list, tuple, dict)) and len(value) == 0:
        return True
    return False


def diff(autogen: dict[str, Any], curated: dict[str, Any]) -> dict[str, list[str]]:
    """Return three buckets of differences."""
    only_autogen: list[str] = []
    only_curated: list[str] = []
    changed: list[str] = []

    auto_keys = set(autogen.keys()) - _AUTOGEN_META_KEYS
    cur_keys = set(curated.keys())

    for key in sorted(auto_keys | cur_keys):
        a = autogen.get(key, ...)
        c = curated.get(key, ...)
        if a is ...:
            if not _is_empty(c):
                only_curated.append(key)
            continue
        if c is ...:
            if not _is_empty(a):
                only_autogen.append(key)
            continue
        if _is_empty(a) and _is_empty(c):
            continue
        if _is_empty(a) and not _is_empty(c):
            only_curated.append(key)
            continue
        if _is_empty(c) and not _is_empty(a):
            only_autogen.append(key)
            continue
        if a != c:
            changed.append(key)
    return {
        "only_autogen": only_autogen,
        "only_curated": only_curated,
        "changed": changed,
    }


def render(diff_result: dict[str, list[str]]) -> str:
    sections = (
        ("ONLY IN AUTOGEN", "+", diff_result["only_autogen"]),
        ("ONLY IN CURATED", "-", diff_result["only_curated"]),
        ("CHANGED", "~", diff_result["changed"]),
    )
    lines: list[str] = []
    for header, marker, keys in sections:
        lines.append(f"=== {header} ===")
        if keys:
            lines.extend(f"  {marker} {key}" for key in keys)
        else:
            lines.append("  (none)")
        lines.append("")
    return "\n".join(lines)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        prog="diff_device_patch",
        description=(
            "Diff an autogen device-patch draft against a curated "
            "device patch."
        ),
    )
    parser.add_argument("--autogen", required=True, type=Path)
    parser.add_argument("--curated", required=True, type=Path)
    args = parser.parse_args(argv)

    auto = _load_json(args.autogen)
    cur = _load_json(args.curated)
    sys.stdout.write(render(diff(auto, cur)))
    return 0


if __name__ == "__main__":  # pragma: no cover
    raise SystemExit(main())
