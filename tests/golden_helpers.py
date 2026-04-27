"""Golden-fixture comparison helpers used by tests.

Added by the OpenSpec change ``auto-update-goldens``.

Tests import :func:`assert_matches_text_golden` /
:func:`assert_matches_json_golden` and pass the session-scoped
``goldens_update_mode`` fixture (defined in :mod:`tests.conftest`)
as the ``update_mode`` argument.

When ``update_mode`` is ``False`` (the CI default) the helpers
behave like a plain ``assert`` against the on-disk fixture.  When
``True`` they rewrite the fixture instead — used together with
``ALLOY_UPDATE_GOLDENS=1`` or ``pytest --update-goldens`` to bulk
refresh goldens after an intentional emitter change.
"""

from __future__ import annotations

import json
from pathlib import Path
from typing import Any


def assert_matches_text_golden(
    actual: str,
    fixture_path: Path,
    *,
    update_mode: bool,
) -> None:
    """Compare ``actual`` text against a golden fixture file.

    Default mode: ``assert actual == fixture_path.read_text(...)``.

    Update mode: rewrite the fixture if the content differs.  Never
    raises on mismatch — the resulting ``git diff`` is the
    reviewable artefact.
    """
    if update_mode:
        fixture_path.parent.mkdir(parents=True, exist_ok=True)
        if not fixture_path.exists() or fixture_path.read_text(encoding="utf-8") != actual:
            fixture_path.write_text(actual, encoding="utf-8")
        return
    expected = fixture_path.read_text(encoding="utf-8")
    assert actual == expected, f"golden mismatch: {fixture_path}"


def assert_matches_json_golden(
    actual: Any,
    fixture_path: Path,
    *,
    update_mode: bool,
) -> None:
    """Compare ``actual`` (a JSON-serialisable value) against a JSON
    golden fixture.

    Default mode: ``assert actual == json.loads(fixture_path.read_text(...))``.

    Update mode: rewrite the fixture with ``indent=2``,
    ``ensure_ascii=False``, and a trailing newline.
    """
    if update_mode:
        fixture_path.parent.mkdir(parents=True, exist_ok=True)
        serialised = json.dumps(actual, indent=2, ensure_ascii=False) + "\n"
        if not fixture_path.exists() or fixture_path.read_text(encoding="utf-8") != serialised:
            fixture_path.write_text(serialised, encoding="utf-8")
        return
    expected = json.loads(fixture_path.read_text(encoding="utf-8"))
    assert actual == expected, f"golden mismatch: {fixture_path}"


__all__ = ("assert_matches_text_golden", "assert_matches_json_golden")
