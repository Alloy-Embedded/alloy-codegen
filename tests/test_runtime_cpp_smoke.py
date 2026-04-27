"""Runtime C++ smoke-compile gate.

Added by the OpenSpec change ``add-runtime-cpp-smoke-compile-ci``.

For every admitted ``(vendor, family, device)`` triple, this module
materialises the pipeline's emitted runtime headers to a tmp tree
and drives ``clang++ -std=c++20 -ffreestanding -nostdlib -c`` over
a synthesised ``smoke.cpp`` that includes every header.  Catches
template-metaprogramming regressions (typed enums,
``ValidPinAssignment`` concept, specialisation arities) at PR time
— invisible to the existing golden + string-presence assertions.

Activation:
    pytest --runtime-cpp-smoke
    ALLOY_RUNTIME_CPP_SMOKE=1 pytest

When ``clang++`` is not on PATH the test is skipped (not failed)
so contributors without a clang toolchain are not blocked.
"""

from __future__ import annotations

import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
TOOLS = ROOT / "tools"
for path in (SRC, TOOLS):
    if str(path) not in sys.path:
        sys.path.insert(0, str(path))

from runtime_cpp_smoke import (  # noqa: E402
    SmokeResult,
    admitted_triples,
    clang_executable,
    smoke_compile_device,
)


@pytest.fixture(scope="session")
def fixtures_root() -> Path:
    return ROOT / "tests" / "fixtures"


@pytest.fixture(scope="session")
def clang_path() -> str:
    """Resolved clang++.  Skips the calling test when clang is absent."""
    clang = clang_executable()
    if clang is None:
        pytest.skip("clang++ not on PATH; runtime-cpp-smoke skipped")
    return clang


@pytest.mark.runtime_cpp_smoke
@pytest.mark.parametrize("triple", admitted_triples())
def test_runtime_cpp_smoke_compile(
    triple: tuple[str, str, str],
    fixtures_root: Path,
    clang_path: str,
    tmp_path: Path,
) -> None:
    """Spec scenario: every admitted device produces a per-device
    ``smoke.cpp`` that compiles cleanly with the freestanding clang
    invocation.  On failure the message identifies the device, the
    runtime headers included, and the compiler stderr."""
    vendor, family, device = triple
    result: SmokeResult = smoke_compile_device(
        vendor=vendor,
        family=family,
        device=device,
        work_dir=tmp_path,
        clang=clang_path,
        fixtures_root=fixtures_root,
    )
    assert result.passed, _format_failure(result)


def _format_failure(result: SmokeResult) -> str:
    """Render a human-friendly failure summary for a smoke compile."""
    headers = "\n  ".join(result.headers_included) or "(none)"
    stderr_excerpt = "\n".join(result.stderr.splitlines()[:60])
    return (
        f"\nrunes-cpp-smoke FAIL for {result.label}\n"
        f"\nHeaders included ({len(result.headers_included)}):\n  {headers}\n"
        f"\n--- compiler stderr (first 60 lines) ---\n{stderr_excerpt}\n"
    )
