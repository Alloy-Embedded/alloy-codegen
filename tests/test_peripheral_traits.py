"""Tests for the peripheral-trait template library.

Added by ``peripheral-trait-template-library``.
"""

from __future__ import annotations

import importlib.util
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.peripheral_traits import (  # noqa: E402
    SUPPORTED_CLASSES,
    discover_template_files,
    load_all_templates,
    load_template,
    load_templates,
    merge_chain,
    resolve_template,
    template_provenance_tag,
)


def _load_extractor():
    """Import ``scripts/extract_peripheral_template.py`` for direct testing."""
    path = ROOT / "scripts" / "extract_peripheral_template.py"
    spec = importlib.util.spec_from_file_location("scripts_extract_template", path)
    assert spec is not None and spec.loader is not None
    module = importlib.util.module_from_spec(spec)
    sys.modules["scripts_extract_template"] = module
    spec.loader.exec_module(module)
    return module


# ---------------------------------------------------------------------------
# Library shape
# ---------------------------------------------------------------------------


def test_supported_classes_have_schemas() -> None:
    """Every entry in SUPPORTED_CLASSES must have a JSON schema and
    a templates directory shipped at the canonical path."""
    schemas_dir = ROOT / "schemas" / "peripheral_traits"
    templates_dir = ROOT / "data" / "peripheral_traits"
    for cls in SUPPORTED_CLASSES:
        assert (schemas_dir / f"{cls}.json").exists(), f"missing schema for {cls!r}"
        assert (templates_dir / cls).exists(), f"missing templates dir for {cls!r}"


def test_every_shipped_template_loads_without_error() -> None:
    files = list(discover_template_files())
    assert files, "no shipped templates discovered"
    for path in files:
        peripheral_class = path.parent.name
        template = load_template(path, peripheral_class=peripheral_class)
        assert template.template_revision >= 1
        assert template.ip_name
        assert template.ip_version


def test_load_all_templates_indexes_by_ip_pair() -> None:
    catalog = load_all_templates()
    # uart catalog has at least usart_v2 + lpuart_v1 + nrf-uart-v1
    uart_keys = set(catalog["uart"].keys())
    assert ("usart", "v2") in uart_keys
    assert ("lpuart", "v1") in uart_keys


# ---------------------------------------------------------------------------
# Resolution + spec scenarios
# ---------------------------------------------------------------------------


def test_two_instances_on_same_ip_version_resolve_to_same_template() -> None:
    """Spec scenario: STM32G0 USART1 and STM32F4 USART2 both
    `(ip_name=usart, ip_version=v2)` MUST receive identical defaults."""
    catalog = load_all_templates()
    g0 = resolve_template(
        catalog, peripheral_class="uart", ip_name="usart", ip_version="v2"
    )
    f4 = resolve_template(
        catalog, peripheral_class="uart", ip_name="usart", ip_version="v2"
    )
    assert g0 is not None and f4 is not None
    assert g0 is f4  # cached lookup returns the exact same object
    assert g0.values == f4.values


def test_resolve_template_returns_none_for_unknown_ip_version() -> None:
    catalog = load_all_templates()
    assert (
        resolve_template(
            catalog, peripheral_class="uart", ip_name="usart", ip_version="v999"
        )
        is None
    )


def test_resolve_template_returns_none_when_ip_version_is_none() -> None:
    catalog = load_all_templates()
    assert (
        resolve_template(
            catalog, peripheral_class="uart", ip_name="usart", ip_version=None
        )
        is None
    )


def test_template_provenance_tag_carries_revision() -> None:
    """Spec scenario: template revision MUST be visible in
    per-peripheral provenance."""
    catalog = load_all_templates()
    template = resolve_template(
        catalog, peripheral_class="uart", ip_name="usart", ip_version="v2"
    )
    assert template is not None
    tag = template_provenance_tag(template)
    assert tag.startswith("peripheral_traits/uart/usart__v2@rev")
    assert f"@rev{template.template_revision}" in tag


# ---------------------------------------------------------------------------
# Merge order
# ---------------------------------------------------------------------------


def test_merge_chain_applies_baseline_template_patch_in_order() -> None:
    """Spec: merge order MUST be
    `baseline ← template ← family-patch ← device-patch`."""
    baseline = {"max_baud_hz": 0, "parity_options": ["none"]}
    template = {
        "max_baud_hz": 12_500_000,
        "parity_options": ["none", "even", "odd"],
        "data_bits_options": [7, 8, 9],
    }
    family_patch = {"max_baud_hz": 10_000_000}
    device_patch = {"parity_options": ["none", "even"]}

    merged = merge_chain(baseline, template, family_patch, device_patch)
    # device_patch overrides template's parity_options
    assert merged["parity_options"] == ["none", "even"]
    # family_patch overrides template's max_baud_hz
    assert merged["max_baud_hz"] == 10_000_000
    # template's data_bits_options shines through (no override)
    assert merged["data_bits_options"] == [7, 8, 9]


def test_merge_chain_treats_empty_layers_as_no_op() -> None:
    """Empty/None layers MUST NOT null earlier values."""
    baseline = {"foo": [1, 2, 3]}
    no_override: dict[str, object] = {}
    merged = merge_chain(baseline, None, no_override, {})
    assert merged == {"foo": [1, 2, 3]}


def test_merge_chain_skips_empty_leaves_in_override_layers() -> None:
    """Empty list / None values in an override layer act as
    'no override' so callers can omit a key without nulling."""
    template = {"parity_options": ["none", "even", "odd"]}
    device_patch_with_empty: dict[str, object] = {"parity_options": []}
    merged = merge_chain(template, device_patch_with_empty)
    # Empty list = "no override", template wins
    assert merged["parity_options"] == ["none", "even", "odd"]


def test_merged_into_helper_matches_merge_chain() -> None:
    catalog = load_all_templates()
    template = resolve_template(
        catalog, peripheral_class="uart", ip_name="usart", ip_version="v2"
    )
    assert template is not None
    overrides = {"max_baud_hz": 5_000_000}
    merged = template.merged_into(overrides)
    assert merged["max_baud_hz"] == 5_000_000
    assert merged["parity_options"] == template.values["parity_options"]


# ---------------------------------------------------------------------------
# Schema validation
# ---------------------------------------------------------------------------


def test_template_missing_required_field_raises(tmp_path: Path) -> None:
    bad = tmp_path / "bad.toml"
    bad.write_text('ip_name = "x"\nip_version = "v1"\n', encoding="utf-8")
    with pytest.raises(Exception, match="template_revision"):
        load_template(bad, peripheral_class="uart")


def test_load_templates_for_unknown_class_raises() -> None:
    with pytest.raises(Exception, match="unsupported peripheral_class"):
        load_templates(peripheral_class="usb_zigzag")


# ---------------------------------------------------------------------------
# Extractor
# ---------------------------------------------------------------------------


def test_extractor_is_deterministic_on_synthetic_input(tmp_path: Path) -> None:
    """The extractor's output MUST be deterministic across runs so
    reviewers can re-run it and only see real data drift.

    Uses a synthetic minimal patches tree so the test is hermetic
    (the real STM32 families don't tag ``ip_version`` on family
    peripherals — that's a known gap the migration plan documents).
    """
    fake_root = tmp_path / "patches"
    fam_dir = fake_root / "acme" / "fam"
    (fam_dir / "devices").mkdir(parents=True)
    (fam_dir / "family.json").write_text(
        '{"patch_id": "acme-fam", "peripherals": ['
        '{"name": "UART0", "ip_version": "lpuart-v1"},'
        '{"name": "UART1", "ip_version": "lpuart-v1"}'
        "]}",
        encoding="utf-8",
    )
    (fam_dir / "devices" / "dev1.json").write_text(
        '{"patch_id": "dev1", "device": "dev1", "peripherals": ["UART0", "UART1"], '
        '"uart_max_baud_hz": 8000000, '
        '"uart_parity_options": ['
        '{"peripheral": "UART0", "kind": "none"},'
        '{"peripheral": "UART0", "kind": "even"},'
        '{"peripheral": "UART1", "kind": "none"}]}',
        encoding="utf-8",
    )

    extractor = _load_extractor()
    out = tmp_path / "uart.toml"
    extractor.main(
        ["--class", "uart", "--patches-root", str(fake_root), "--out", str(out)]
    )
    text_a = out.read_text(encoding="utf-8")
    extractor.main(
        ["--class", "uart", "--patches-root", str(fake_root), "--out", str(out)]
    )
    text_b = out.read_text(encoding="utf-8")
    assert text_a == text_b
    assert "lpuart-v1" in text_a
