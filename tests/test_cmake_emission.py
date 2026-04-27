"""Unit tests for the per-core flag table.  Added by
``add-cmake-package-config``."""

from __future__ import annotations

import pytest

from alloy_codegen.cmake_emission import core_compile_flags, core_toolchain_triple

# Every device.identity.core that the IR currently reports across the
# 9 admitted families.  Keep this list in lockstep with the cores
# emitted by `_infer_ip_metadata` + the per-vendor normalizers.
_ADMITTED_CORES = (
    "cortex-m0plus",
    "cortex-m0plus-dual",  # RP2040
    "cortex-m4f",
    "cortex-m7f",
    "avr8",
    "rv32imc",
    "xtensa-lx6",
    "xtensa-lx7",
)


@pytest.mark.parametrize("core", _ADMITTED_CORES)
def test_core_compile_flags_non_empty(core: str) -> None:
    """Every admitted core must resolve to at least one compile flag."""
    flags = core_compile_flags(core)
    assert flags, f"core {core} resolved to empty compile-flag list"


@pytest.mark.parametrize("core", _ADMITTED_CORES)
def test_core_toolchain_triple_resolves(core: str) -> None:
    """Every admitted core must resolve to a toolchain triple."""
    triple = core_toolchain_triple(core)
    assert triple is not None, f"core {core} has no toolchain triple"
    processor, c_compiler, cxx_compiler, ar = triple
    assert processor
    assert c_compiler
    assert cxx_compiler
    assert ar


def test_unknown_core_returns_empty() -> None:
    """Unknown core returns empty flags + None toolchain — emitter
    skips toolchain artifact in that case."""
    assert core_compile_flags("nonexistent-core") == ()
    assert core_toolchain_triple("nonexistent-core") is None


def test_cortex_m4f_uses_hard_float() -> None:
    flags = core_compile_flags("cortex-m4f")
    assert "-mfloat-abi=hard" in flags
    assert "-mfpu=fpv4-sp-d16" in flags


def test_cortex_m7f_uses_hard_float_with_v5_fpu() -> None:
    flags = core_compile_flags("cortex-m7f")
    assert "-mfloat-abi=hard" in flags
    assert "-mfpu=fpv5-d16" in flags


def test_riscv32_emits_march_and_mabi() -> None:
    flags = core_compile_flags("rv32imc")
    assert "-march=rv32imc" in flags
    assert "-mabi=ilp32" in flags


def test_xtensa_emits_longcalls() -> None:
    assert "-mlongcalls" in core_compile_flags("xtensa-lx6")
    assert "-mlongcalls" in core_compile_flags("xtensa-lx7")
