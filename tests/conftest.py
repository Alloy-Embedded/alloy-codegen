"""Shared pytest config for the alloy-codegen v2.1 test suite."""

from __future__ import annotations

import sys
from pathlib import Path

import pytest

_SRC = Path(__file__).resolve().parents[1] / "src"
if str(_SRC) not in sys.path:
    sys.path.insert(0, str(_SRC))


def pytest_addoption(parser: pytest.Parser) -> None:
    parser.addoption(
        "--compile-smoke",
        action="store_true",
        default=False,
        help=(
            "Enable C++ compile smoke tests (require clang++ on PATH "
            "or ALLOY_CLANGPP env-var).  Not run by default."
        ),
    )


@pytest.fixture
def compile_smoke(request: pytest.FixtureRequest) -> bool:
    """True when the user passed ``--compile-smoke``."""
    return bool(request.config.getoption("--compile-smoke"))
