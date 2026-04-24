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
def fixture_nxp_sources_root() -> Path:
    return ROOT / "tests" / "fixtures" / "nxp-mcux-imxrt1060"


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


@pytest.fixture
def nxp_execution_context(
    fixture_nxp_sources_root: Path,
    tmp_path: Path,
) -> ExecutionContext:
    default_context = ExecutionContext.default()
    alloy_root = default_context.alloy_root or (ROOT.parent / "alloy")
    return default_context.with_overrides(
        source_overrides={
            "nxp-mcux-soc-svd": str(fixture_nxp_sources_root / "svd"),
            "nxp-mcux-sdk": str(fixture_nxp_sources_root / "sdk"),
        },
        artifact_root=str(tmp_path / "artifacts"),
        publication_root=str(tmp_path / "publication"),
        alloy_root=str(alloy_root),
    )


@pytest.fixture
def fixture_espressif_svd_root() -> Path:
    return ROOT / "tests" / "fixtures" / "espressif-svd"


@pytest.fixture
def espressif_execution_context(
    fixture_espressif_svd_root: Path,
    tmp_path: Path,
) -> ExecutionContext:
    default_context = ExecutionContext.default()
    alloy_root = default_context.alloy_root or (ROOT.parent / "alloy")
    return default_context.with_overrides(
        source_overrides={
            "espressif-svd": str(fixture_espressif_svd_root),
        },
        artifact_root=str(tmp_path / "artifacts"),
        publication_root=str(tmp_path / "publication"),
        alloy_root=str(alloy_root),
    )


@pytest.fixture
def fixture_pico_sdk_root() -> Path:
    return ROOT / "tests" / "fixtures" / "pico-sdk"


@pytest.fixture
def rp2040_execution_context(
    fixture_pico_sdk_root: Path,
    tmp_path: Path,
) -> ExecutionContext:
    default_context = ExecutionContext.default()
    alloy_root = default_context.alloy_root or (ROOT.parent / "alloy")
    return default_context.with_overrides(
        source_overrides={
            "pico-sdk": str(fixture_pico_sdk_root),
        },
        artifact_root=str(tmp_path / "artifacts"),
        publication_root=str(tmp_path / "publication"),
        alloy_root=str(alloy_root),
    )
