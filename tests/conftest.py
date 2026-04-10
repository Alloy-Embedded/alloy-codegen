"""Test configuration for alloy-codegen."""

from __future__ import annotations

import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"

if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.context import ExecutionContext  # noqa: E402


@pytest.fixture
def fixture_source_root() -> Path:
    return ROOT / "tests" / "fixtures" / "cmsis-svd-data"


@pytest.fixture
def fixture_pin_source_root() -> Path:
    return ROOT / "tests" / "fixtures" / "stm32-open-pin-data"


@pytest.fixture
def fixture_microchip_extract_root() -> Path:
    return ROOT / "tests" / "fixtures" / "microchip-dfp-same70"


@pytest.fixture
def execution_context(
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
    tmp_path: Path,
) -> ExecutionContext:
    default_context = ExecutionContext.default()
    alloy_root = default_context.alloy_root or (ROOT.parent / "alloy")
    return default_context.with_overrides(
        source_overrides={
            "cmsis-svd-data": str(fixture_source_root),
            "stm32-open-pin-data": str(fixture_pin_source_root),
        },
        artifact_root=str(tmp_path / "artifacts"),
        publication_root=str(tmp_path / "publication"),
        alloy_root=str(alloy_root),
    )


@pytest.fixture
def microchip_execution_context(
    fixture_microchip_extract_root: Path,
    tmp_path: Path,
) -> ExecutionContext:
    default_context = ExecutionContext.default()
    alloy_root = default_context.alloy_root or (ROOT.parent / "alloy")
    return default_context.with_overrides(
        source_overrides={
            "microchip-dfp-extract": str(fixture_microchip_extract_root),
        },
        artifact_root=str(tmp_path / "artifacts"),
        publication_root=str(tmp_path / "publication"),
        alloy_root=str(alloy_root),
    )
