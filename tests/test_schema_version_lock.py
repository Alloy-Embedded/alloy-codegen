"""Tests for `lock-canonical-yaml-schema-v1` codegen-side
enforcement: parse_device must refuse YAMLs whose
`schema_version` major component differs from the codegen's
pinned `IR_SCHEMA_VERSION`.
"""

from __future__ import annotations

import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.bootstrap import IR_SCHEMA_VERSION  # noqa: E402
from alloy_codegen.canonical_device_yaml import (  # noqa: E402
    IRSchemaVersionMismatchError,
    parse_device,
)

_MIN_VALID_DEVICE = """\
schema_version: {version}
identity:
  vendor: synth
  family: synthfam
  device: synthdev
  core: cortex-m0
"""


def test_pinned_major_loads_cleanly() -> None:
    """Sanity: a YAML at the pinned version parses without
    raising.  This guards against regressions in the
    enforcement helper itself.
    """
    text = _MIN_VALID_DEVICE.format(version=IR_SCHEMA_VERSION)
    # parse_device may still complain about unrelated fields the
    # IR demands; we only care that the version check passes.
    try:
        parse_device(text)
    except IRSchemaVersionMismatchError:
        pytest.fail("pinned schema_version should not raise IRSchemaVersionMismatchError")
    except Exception:
        # Other errors (missing required IR fields) are not
        # what this test guards.
        pass


def test_future_major_is_rejected() -> None:
    text = _MIN_VALID_DEVICE.format(version="2.0.0")
    with pytest.raises(IRSchemaVersionMismatchError) as excinfo:
        parse_device(text)
    msg = str(excinfo.value)
    assert "2.0.0" in msg
    assert IR_SCHEMA_VERSION in msg


def test_missing_schema_version_is_rejected() -> None:
    text = "identity:\n  vendor: synth\n  family: synthfam\n  device: synthdev\n  core: cortex-m0\n"
    with pytest.raises(IRSchemaVersionMismatchError) as excinfo:
        parse_device(text)
    assert "schema_version" in str(excinfo.value)


def test_non_string_schema_version_is_rejected() -> None:
    text = "schema_version: 1\nidentity:\n  vendor: a\n  family: b\n  device: c\n  core: d\n"
    with pytest.raises(IRSchemaVersionMismatchError):
        parse_device(text)


def test_invalid_semver_is_rejected() -> None:
    from alloy_codegen.errors import StageExecutionError

    text = _MIN_VALID_DEVICE.format(version="not-semver")
    with pytest.raises(StageExecutionError):
        parse_device(text)


def test_minor_or_patch_bump_within_pinned_major_is_accepted() -> None:
    """A 1.99.99 YAML must NOT be rejected when codegen is
    pinned at 1.x — only major mismatches abort."""
    bumped = "1.99.99"
    text = _MIN_VALID_DEVICE.format(version=bumped)
    # Same caveat as test_pinned_major_loads_cleanly: this only
    # guards the version check; downstream IR errors are fine.
    try:
        parse_device(text)
    except IRSchemaVersionMismatchError:
        pytest.fail("minor/patch bump within pinned major must not raise IRSchemaVersionMismatchError")
    except Exception:
        pass
