"""Tests for ``alloy_codegen.generate(config, out_dir)`` (#add-generate-entrypoint)."""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

import pytest

import alloy_codegen
from alloy_codegen.bootstrap import DEVICE_REGISTRY
from alloy_codegen.errors import ConfigError


# ---------------------------------------------------------------------------
# Lightweight stand-ins for alloy_cli.core.project.{ChipRef, BoardRef}.
# Deliberately *not* importing from alloy-cli — that would invert the
# dependency direction.
# ---------------------------------------------------------------------------


@dataclass(frozen=True)
class _ChipRef:
    vendor: str
    family: str
    device: str


@dataclass(frozen=True)
class _BoardRef:
    id: str


@dataclass(frozen=True)
class _Config:
    chip: _ChipRef | None = None
    board: _BoardRef | None = None


def _first_admitted_chip() -> tuple[str, str, str]:
    """Pick a stable target out of the live registry for the happy path."""
    for (vendor, family), devices in sorted(DEVICE_REGISTRY.items()):
        if devices:
            return vendor, family, devices[0]
    raise RuntimeError("DEVICE_REGISTRY is empty — bootstrap regressed.")


# ---------------------------------------------------------------------------
# Public surface
# ---------------------------------------------------------------------------


def test_package_exports_generate_and_errors() -> None:
    """The public surface is exactly the four canonical names."""
    assert hasattr(alloy_codegen, "generate")
    assert hasattr(alloy_codegen, "ConfigError")
    assert hasattr(alloy_codegen, "StageExecutionError")
    assert hasattr(alloy_codegen, "__version__")


# ---------------------------------------------------------------------------
# Resolver
# ---------------------------------------------------------------------------


def test_generate_with_chip_writes_four_artifacts(tmp_path: Path) -> None:
    vendor, family, device = _first_admitted_chip()
    config = _Config(chip=_ChipRef(vendor=vendor, family=family, device=device))
    written = alloy_codegen.generate(config, tmp_path)

    expected_names = {
        "linker.ld",
        "vector_table.c",
        "peripheral_traits.h",
        "runtime_init.c",
    }
    assert {p.name for p in written} == expected_names
    for path in written:
        assert path.parent == tmp_path
        assert path.exists()


def test_generate_returns_sorted_tuple(tmp_path: Path) -> None:
    vendor, family, device = _first_admitted_chip()
    config = _Config(chip=_ChipRef(vendor=vendor, family=family, device=device))
    written = alloy_codegen.generate(config, tmp_path)
    assert tuple(written) == tuple(sorted(written))


def test_generate_creates_missing_out_dir(tmp_path: Path) -> None:
    vendor, family, device = _first_admitted_chip()
    config = _Config(chip=_ChipRef(vendor=vendor, family=family, device=device))
    target = tmp_path / "deeper" / "nested" / "out"
    written = alloy_codegen.generate(config, target)
    assert target.exists()
    assert all(p.parent == target for p in written)


# ---------------------------------------------------------------------------
# Error paths
# ---------------------------------------------------------------------------


def test_generate_without_chip_or_board_raises(tmp_path: Path) -> None:
    config = _Config(chip=None, board=None)
    with pytest.raises(ConfigError) as exc:
        alloy_codegen.generate(config, tmp_path)
    assert "config.chip" in str(exc.value)


def test_generate_with_board_only_raises_with_hint(tmp_path: Path) -> None:
    config = _Config(chip=None, board=_BoardRef(id="nucleo_g071rb"))
    with pytest.raises(ConfigError) as exc:
        alloy_codegen.generate(config, tmp_path)
    msg = str(exc.value)
    assert "board.id" in msg
    assert "nucleo_g071rb" in msg
    assert "alloy_cli.core.boards.lookup" in msg


def test_generate_unknown_vendor_raises(tmp_path: Path) -> None:
    config = _Config(chip=_ChipRef(vendor="atari", family="2600", device="cpu"))
    with pytest.raises(ConfigError) as exc:
        alloy_codegen.generate(config, tmp_path)
    assert "vendor 'atari'" in str(exc.value)


def test_generate_unknown_family_raises(tmp_path: Path) -> None:
    # Pick a real vendor with a fake family so the second branch fires.
    vendor = next(v for v, _ in DEVICE_REGISTRY)
    config = _Config(chip=_ChipRef(vendor=vendor, family="ghost", device="zzz"))
    with pytest.raises(ConfigError) as exc:
        alloy_codegen.generate(config, tmp_path)
    assert "family" in str(exc.value)


def test_generate_unknown_device_lists_neighbours(tmp_path: Path) -> None:
    (vendor, family), devices = next(iter(sorted(DEVICE_REGISTRY.items())))
    config = _Config(
        chip=_ChipRef(vendor=vendor, family=family, device="not-a-real-chip")
    )
    with pytest.raises(ConfigError) as exc:
        alloy_codegen.generate(config, tmp_path)
    msg = str(exc.value)
    assert "not admitted" in msg
    for device in devices:
        assert device in msg


def test_generate_partial_chip_fields_raise(tmp_path: Path) -> None:
    config = _Config(chip=_ChipRef(vendor="st", family="", device=""))
    with pytest.raises(ConfigError):
        alloy_codegen.generate(config, tmp_path)
