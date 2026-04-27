"""Tests for ``scripts.autogen_device_patches`` and
``scripts.diff_device_patch``.  Added by
``autogen-device-patches-from-svd``."""

from __future__ import annotations

import importlib.util
import json
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))


def _load_script(name: str):
    """Import a top-level ``scripts/<name>.py`` module under a
    namespace that is safe to share across tests (the scripts dir
    is not a package)."""
    path = ROOT / "scripts" / f"{name}.py"
    module_name = f"scripts_{name}"
    spec = importlib.util.spec_from_file_location(module_name, path)
    assert spec is not None and spec.loader is not None
    module = importlib.util.module_from_spec(spec)
    # Register in sys.modules *before* exec so dataclass-internal
    # annotation resolution (which looks up cls.__module__ via
    # sys.modules) works for any dataclasses defined in the script.
    sys.modules[module_name] = module
    spec.loader.exec_module(module)
    return module


@pytest.fixture(scope="module")
def autogen_module():
    return _load_script("autogen_device_patches")


@pytest.fixture(scope="module")
def diff_module():
    return _load_script("diff_device_patch")


@pytest.fixture(scope="module")
def stm32g071_svd() -> Path:
    return ROOT / "tests/fixtures/cmsis-svd-data/data/STMicro/STM32G071.svd"


@pytest.fixture(scope="module")
def curated_g071_patch() -> dict:
    path = ROOT / "patches/st/stm32g0/devices/stm32g071rb.json"
    return json.loads(path.read_text(encoding="utf-8"))


def test_autogen_deterministic_output(autogen_module, stm32g071_svd: Path) -> None:
    """Running the generator twice on the same inputs MUST produce
    byte-identical JSON."""
    patch_a = autogen_module.build_patch(
        vendor="st",
        family="stm32g0",
        device="stm32g071rb",
        svd_path=stm32g071_svd,
        pack_path=None,
    )
    patch_b = autogen_module.build_patch(
        vendor="st",
        family="stm32g0",
        device="stm32g071rb",
        svd_path=stm32g071_svd,
        pack_path=None,
    )
    assert autogen_module.emit_json(patch_a) == autogen_module.emit_json(patch_b)


def test_autogen_peripherals_match_svd_contents(
    autogen_module,
    stm32g071_svd: Path,
    curated_g071_patch: dict,
) -> None:
    """The autogen peripherals list MUST equal the SVD's complete
    peripheral set, sorted.  When the curated patch lists a
    peripheral that *is* present in the SVD, autogen MUST cover it
    — peripherals the curated patch lists but the SVD does not
    carry are out of scope (the bootstrap fixture is intentionally
    trimmed)."""
    autogen_patch = autogen_module.build_patch(
        vendor="st",
        family="stm32g0",
        device="stm32g071rb",
        svd_path=stm32g071_svd,
        pack_path=None,
    )
    autogen_periphs = autogen_patch["peripherals"]
    # Sorted-and-unique invariant.
    assert autogen_periphs == sorted(set(autogen_periphs))
    # Bootstrap fixture has at least RCC + GPIOA + USART1.
    for required in ("RCC", "GPIOA", "USART1"):
        assert required in autogen_periphs
    # Every peripheral the curated patch lists that is also in the
    # SVD must show up in autogen.
    raw = autogen_module.parse_raw_device_document(stm32g071_svd)
    svd_periphs = {p.name for p in raw.peripherals}
    curated_in_svd = set(curated_g071_patch["peripherals"]) & svd_periphs
    assert curated_in_svd.issubset(set(autogen_periphs))


def test_autogen_emits_irq_table_with_stable_order(autogen_module, stm32g071_svd: Path) -> None:
    """The IRQ table MUST be sorted by (line, name) so reruns
    produce identical output."""
    patch = autogen_module.build_patch(
        vendor="st",
        family="stm32g0",
        device="stm32g071rb",
        svd_path=stm32g071_svd,
        pack_path=None,
    )
    irqs = patch["interrupts"]
    assert irqs, "G0 fixture should yield at least one interrupt"
    sort_key = [(irq["line"], irq["name"]) for irq in irqs]
    assert sort_key == sorted(sort_key)


def test_autogen_marks_undriverable_fields_as_todo_review(
    autogen_module, stm32g071_svd: Path
) -> None:
    """Fields the generator cannot derive from SVD alone (package,
    pin_data_file, summary, all Tier 2/3/4 lists) MUST appear in
    the top-level ``$todo_review`` array."""
    patch = autogen_module.build_patch(
        vendor="st",
        family="stm32g0",
        device="stm32g071rb",
        svd_path=stm32g071_svd,
        pack_path=None,
    )
    todo = set(patch["$todo_review"])
    expected = {
        "package",
        "pin_data_file",
        "summary",
        "memories",
        "uart_max_baud_hz",
        "uart_mode_flags",
        "spi_mode_flags",
        "i2c_speed_options",
    }
    missing = expected - todo
    assert not missing, f"missing from $todo_review: {missing}"


def test_autogen_resolves_core_from_cpu_block(autogen_module, tmp_path: Path) -> None:
    """When the SVD declares a ``<cpu>`` block, the generator MUST
    resolve a canonical core string (e.g. ``cortex-m4f`` for a
    ``CM4`` cpu with ``fpuPresent`` set)."""
    svd = tmp_path / "fake.svd"
    svd.write_text(
        """<?xml version="1.0"?>
<device>
  <name>FAKE</name>
  <cpu>
    <name>CM4</name>
    <revision>r0p1</revision>
    <fpuPresent>true</fpuPresent>
  </cpu>
  <peripherals>
    <peripheral>
      <name>FOO</name>
      <baseAddress>0x40000000</baseAddress>
    </peripheral>
  </peripherals>
</device>
""",
        encoding="utf-8",
    )
    patch = autogen_module.build_patch(
        vendor="acme",
        family="acme1",
        device="acme1xx",
        svd_path=svd,
        pack_path=None,
    )
    assert patch["core"] == "cortex-m4f"
    assert "core" not in patch["$todo_review"]


def test_diff_buckets_categorise_known_inputs(diff_module) -> None:
    """The diff tool MUST partition keys into the three buckets
    (only_autogen / only_curated / changed) using emptiness-aware
    semantics."""
    autogen = {
        "$autogen": {"generator_version": 1},
        "$todo_review": ["package"],
        "device": "x",
        "package": "TODO_REVIEW",
        "memories": [],
        "peripherals": ["A", "B"],
    }
    curated = {
        "device": "x",
        "package": "lqfp64",
        "memories": [{"name": "flash"}],
        "peripherals": ["A"],
        "summary": "hello",
    }
    result = diff_module.diff(autogen, curated)
    assert "package" in result["only_curated"]
    assert "memories" in result["only_curated"]
    assert "summary" in result["only_curated"]
    assert "peripherals" in result["changed"]
    assert result["only_autogen"] == []
