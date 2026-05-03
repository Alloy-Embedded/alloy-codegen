"""Tests for the alloy-codegen v2.1 CLI."""

from __future__ import annotations

from pathlib import Path

import pytest

from alloy_codegen.cli import _EMITTERS, _parse_target, main


def test_emitter_registry_carries_every_known_emitter() -> None:
    names = {e.name for e in _EMITTERS}
    assert names == {"linker_script", "vector_table",
                     "peripheral_traits", "peripheral_id",
                     "rcc_enable", "rcc_gate_table", "rcc_traits",
                     "runtime_init",
                     "pin_router", "system_init"}


def test_parse_target_three_part() -> None:
    assert _parse_target("st/stm32g0/stm32g0b1re") == ("st", "stm32g0", "stm32g0b1re")


def test_parse_target_two_part_resolves_family() -> None:
    """`st/stm32g0b1re` resolves to family stm32g0 via DEVICE_REGISTRY."""
    vendor, family, device = _parse_target("st/stm32g0b1re")
    assert vendor == "st"
    assert family == "stm32g0"
    assert device == "stm32g0b1re"


def test_parse_target_unknown_chip_errors() -> None:
    with pytest.raises(SystemExit):
        _parse_target("st/this-chip-does-not-exist")


def test_parse_target_invalid_form_errors() -> None:
    with pytest.raises(SystemExit):
        _parse_target("just-one-word")


def test_main_list_succeeds(capsys: pytest.CaptureFixture) -> None:
    rc = main(["--list"])
    assert rc == 0
    out = capsys.readouterr().out
    assert "alloy-codegen" in out
    assert "alloy.device.v2.1" in out


def test_main_emits_every_artifact(tmp_path: Path) -> None:
    rc = main(["st/stm32g0/stm32g0b1re", "--out", str(tmp_path)])
    assert rc == 0
    chip_out = tmp_path / "st" / "stm32g0" / "stm32g0b1re"
    expected = {"linker.ld", "vector_table.c",
                "peripheral_traits.h", "peripheral_id.hpp",
                "rcc_enable.hpp", "rcc_gate_table.hpp",
                "rcc_traits.hpp",
                "runtime_init.c", "pins.h",
                "system_init.c"}
    actual = {p.name for p in chip_out.iterdir()}
    assert actual == expected


def test_main_emit_filter_writes_only_selected(tmp_path: Path) -> None:
    rc = main(
        ["st/stm32g0/stm32g0b1re",
         "--out", str(tmp_path),
         "--emit", "linker_script",
         "--emit", "vector_table"],
    )
    assert rc == 0
    chip_out = tmp_path / "st" / "stm32g0" / "stm32g0b1re"
    actual = {p.name for p in chip_out.iterdir()}
    assert actual == {"linker.ld", "vector_table.c"}


def test_main_unknown_emitter_errors(tmp_path: Path) -> None:
    with pytest.raises(SystemExit):
        main(["st/stm32g0/stm32g0b1re",
              "--out", str(tmp_path),
              "--emit", "nonexistent_emitter"])
