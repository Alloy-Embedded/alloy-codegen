"""Tests for the ``auto-update-goldens`` flag and helpers.

Added by the OpenSpec change ``auto-update-goldens``.
"""

from __future__ import annotations

import json
import sys
from pathlib import Path

import pytest

# Allow ``import golden_helpers`` whether the test is invoked via
# ``pytest`` (which usually adds the test dir to sys.path) or via a
# direct module run.
_HERE = Path(__file__).resolve().parent
if str(_HERE) not in sys.path:
    sys.path.insert(0, str(_HERE))

from golden_helpers import (  # noqa: E402
    assert_matches_json_golden,
    assert_matches_text_golden,
)


def test_text_golden_default_mode_asserts_equality(tmp_path: Path) -> None:
    fixture = tmp_path / "golden.txt"
    fixture.write_text("expected", encoding="utf-8")
    assert_matches_text_golden("expected", fixture, update_mode=False)
    with pytest.raises(AssertionError):
        assert_matches_text_golden("different", fixture, update_mode=False)


def test_text_golden_update_mode_writes_fixture(tmp_path: Path) -> None:
    fixture = tmp_path / "golden.txt"
    fixture.write_text("old", encoding="utf-8")
    # Update mode rewrites and does not assert.
    assert_matches_text_golden("new", fixture, update_mode=True)
    assert fixture.read_text(encoding="utf-8") == "new"


def test_text_golden_update_mode_creates_missing_fixture(tmp_path: Path) -> None:
    fixture = tmp_path / "subdir" / "golden.txt"
    assert not fixture.exists()
    assert_matches_text_golden("hello", fixture, update_mode=True)
    assert fixture.read_text(encoding="utf-8") == "hello"


def test_text_golden_update_mode_skips_when_already_matching(
    tmp_path: Path,
) -> None:
    """Idempotence: re-running update mode on a matching fixture
    leaves the mtime untouched (we skip the write)."""
    fixture = tmp_path / "golden.txt"
    fixture.write_text("same", encoding="utf-8")
    mtime_before = fixture.stat().st_mtime_ns
    assert_matches_text_golden("same", fixture, update_mode=True)
    mtime_after = fixture.stat().st_mtime_ns
    assert mtime_after == mtime_before


def test_json_golden_default_mode_asserts_equality(tmp_path: Path) -> None:
    fixture = tmp_path / "golden.json"
    fixture.write_text(json.dumps({"a": 1}, indent=2) + "\n", encoding="utf-8")
    assert_matches_json_golden({"a": 1}, fixture, update_mode=False)
    with pytest.raises(AssertionError):
        assert_matches_json_golden({"a": 2}, fixture, update_mode=False)


def test_json_golden_update_mode_writes_with_canonical_format(
    tmp_path: Path,
) -> None:
    fixture = tmp_path / "golden.json"
    fixture.write_text("{}", encoding="utf-8")
    assert_matches_json_golden({"a": 1, "b": [2, 3]}, fixture, update_mode=True)
    text = fixture.read_text(encoding="utf-8")
    assert text.endswith("\n")
    # Pretty-printed with indent=2.
    assert "\n  " in text
    # Round-trips back to the same value.
    assert json.loads(text) == {"a": 1, "b": [2, 3]}


def test_pytest_addoption_registers_update_goldens_flag(
    pytestconfig: pytest.Config,
) -> None:
    """The CLI option must be registered by conftest's
    ``pytest_addoption`` hook so ``--update-goldens`` is recognised."""
    # ``getoption`` raises ValueError for unknown names; reaching this
    # line without an exception proves the option is registered.
    value = pytestconfig.getoption("--update-goldens")
    assert isinstance(value, bool)


def test_goldens_update_mode_fixture_returns_bool(
    goldens_update_mode: bool,
) -> None:
    """The session-scoped fixture exposes a plain bool, not a string."""
    assert isinstance(goldens_update_mode, bool)
