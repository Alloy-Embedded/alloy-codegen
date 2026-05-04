"""Per-device C++ compile smoke for connectors.hpp + routes.hpp.

Generates artifacts for ``st/stm32g0/stm32g071rb``, then compiles
``tests/compile_tests/smoke_connector_routes.cpp`` against them with
``clang++``.

Not run by default — requires both:
  * ``--compile-smoke`` pytest flag
  * ``clang++`` on PATH (or ALLOY_CLANGPP env-var override)

Run manually::

    pytest tests/test_compile_smoke.py --compile-smoke -v

CI::

    pytest tests/test_compile_smoke.py --compile-smoke
"""

from __future__ import annotations

import os
import shutil
import subprocess
from pathlib import Path

import pytest

# ---------------------------------------------------------------------------
# Smoke TU path
# ---------------------------------------------------------------------------

_REPO_ROOT = Path(__file__).resolve().parents[1]
_SMOKE_CPP = _REPO_ROOT / "tests" / "compile_tests" / "smoke_connector_routes.cpp"

# ---------------------------------------------------------------------------
# clang++ resolution
# ---------------------------------------------------------------------------

_CLANGPP_OVERRIDE = os.environ.get("ALLOY_CLANGPP", "")


def _clangpp() -> str | None:
    if _CLANGPP_OVERRIDE:
        return _CLANGPP_OVERRIDE
    return shutil.which("clang++")


# ---------------------------------------------------------------------------
# Compile flags
# ---------------------------------------------------------------------------

_CFLAGS: tuple[str, ...] = (
    "-std=c++20",
    "-ffreestanding",
    "-nostdlib",
    "-Wall",
    "-Werror",
    "-Wno-unused-const-variable",
    "-Wno-c++23-extensions",
    "-c",
    "-o",
    os.devnull,
)


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------


@pytest.mark.compile_smoke
def test_connectors_routes_smoke_stm32g071rb(
    tmp_path: Path,
    compile_smoke: bool,
) -> None:
    """Generate connectors.hpp + routes.hpp for stm32g071rb and compile
    the smoke TU against them."""
    if not compile_smoke:
        pytest.skip("pass --compile-smoke to enable")

    clang = _clangpp()
    if clang is None:
        pytest.skip("clang++ not on PATH; set ALLOY_CLANGPP to override")

    # --- generate artifacts ---
    import alloy_codegen
    from dataclasses import dataclass

    @dataclass(frozen=True)
    class Chip:
        vendor: str = "st"
        family: str = "stm32g0"
        device: str = "stm32g071rb"

    @dataclass(frozen=True)
    class Cfg:
        chip: Chip = Chip()
        board: None = None

    written = alloy_codegen.generate(Cfg(), tmp_path)
    out_dir = next(iter(written)).parent  # all in same dir

    # --- compile ---
    cmd = [clang, *_CFLAGS, f"-I{out_dir}", str(_SMOKE_CPP)]
    result = subprocess.run(cmd, capture_output=True, text=True)

    if result.returncode != 0:
        pytest.fail(
            f"clang++ failed (exit {result.returncode}):\n"
            f"stdout: {result.stdout}\n"
            f"stderr: {result.stderr}"
        )


@pytest.mark.compile_smoke
def test_clangpp_version(compile_smoke: bool) -> None:
    """Sanity-check: clang++ is callable and reports C++20 support."""
    if not compile_smoke:
        pytest.skip("pass --compile-smoke to enable")

    clang = _clangpp()
    if clang is None:
        pytest.skip("clang++ not on PATH")

    result = subprocess.run([clang, "--version"], capture_output=True, text=True)
    assert result.returncode == 0, f"clang++ --version failed: {result.stderr}"
    assert "clang" in result.stdout.lower() or "clang" in result.stderr.lower()
