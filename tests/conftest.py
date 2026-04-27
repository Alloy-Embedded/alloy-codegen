"""Test configuration for alloy-codegen."""

from __future__ import annotations

import os
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"

if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.context import ExecutionContext  # noqa: E402

# ---------------------------------------------------------------------------
# auto-update-goldens: opt-in flag that rewrites golden fixtures from
# the current pipeline output instead of asserting equality.
#
# Activated by either ``ALLOY_UPDATE_GOLDENS=1`` env var or pytest's
# ``--update-goldens`` CLI flag.  When the flag is *not* set, golden
# helpers behave exactly like a plain ``assert`` — the default contract
# is unchanged in CI.  When the flag IS set, the harness refuses to
# run if ``git status`` reports dirty files outside ``tests/fixtures/``
# so source changes can't get baked into goldens silently.
# ---------------------------------------------------------------------------

_FIXTURE_DIR_RELATIVE = Path("tests/fixtures")


def pytest_addoption(parser: pytest.Parser) -> None:
    """Register the ``--update-goldens`` CLI flag."""
    parser.addoption(
        "--update-goldens",
        action="store_true",
        default=False,
        help=(
            "Rewrite golden fixtures from the current pipeline output "
            "instead of asserting equality.  Equivalent to setting "
            "ALLOY_UPDATE_GOLDENS=1 in the environment.  Refuses to "
            "run if non-fixture files are dirty in git."
        ),
    )


def _is_dirty_outside_fixtures() -> tuple[bool, list[str]]:
    """Return (dirty?, offending_paths).  Treat git failures as
    non-dirty — devs without git on PATH still need the test suite."""
    try:
        proc = subprocess.run(
            ["git", "status", "--porcelain"],
            cwd=ROOT,
            capture_output=True,
            text=True,
            timeout=10,
        )
    except (FileNotFoundError, subprocess.TimeoutExpired):
        return False, []
    if proc.returncode != 0:
        return False, []
    offenders: list[str] = []
    fixture_prefix = _FIXTURE_DIR_RELATIVE.as_posix()
    for line in proc.stdout.splitlines():
        # Porcelain v1 lines: "XY <path>" (or "XY <orig> -> <new>" on
        # rename).  Strip the 2-char status + leading space.
        if len(line) < 4:
            continue
        path = line[3:].strip()
        if " -> " in path:
            path = path.split(" -> ", 1)[1]
        path = path.strip('"')  # porcelain quotes paths with special chars
        if not path.startswith(fixture_prefix + "/") and path != fixture_prefix:
            offenders.append(path)
    return bool(offenders), offenders


def _resolve_update_mode(config: pytest.Config) -> bool:
    flag_set = bool(config.getoption("--update-goldens"))
    env_set = os.environ.get("ALLOY_UPDATE_GOLDENS", "").strip() in {"1", "true", "yes"}
    return flag_set or env_set


@pytest.fixture(scope="session")
def goldens_update_mode(pytestconfig: pytest.Config) -> bool:
    """Session-scoped boolean: are we rewriting goldens this run?"""
    update = _resolve_update_mode(pytestconfig)
    if update:
        dirty, offenders = _is_dirty_outside_fixtures()
        if dirty:
            preview = "\n  ".join(offenders[:10])
            extra = "" if len(offenders) <= 10 else f"\n  … and {len(offenders) - 10} more"
            raise pytest.UsageError(
                "Refusing to run with --update-goldens / "
                "ALLOY_UPDATE_GOLDENS=1: there are dirty files outside "
                f"tests/fixtures/.  Commit or stash them first so source "
                f"changes are not baked into goldens silently.\n"
                f"Offending paths:\n  {preview}{extra}"
            )
    return update


__all__ = ("goldens_update_mode",)


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
def fixture_microchip_avr_da_root() -> Path:
    return ROOT / "tests" / "fixtures" / "microchip-dfp-avr-da"


@pytest.fixture
def microchip_avr_da_execution_context(
    fixture_microchip_avr_da_root: Path,
    tmp_path: Path,
) -> ExecutionContext:
    default_context = ExecutionContext.default()
    alloy_root = default_context.alloy_root or (ROOT.parent / "alloy")
    return default_context.with_overrides(
        source_overrides={
            "microchip-dfp-extract": str(fixture_microchip_avr_da_root),
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
