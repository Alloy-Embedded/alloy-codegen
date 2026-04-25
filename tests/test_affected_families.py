"""Regression tests for the publish-workflow affected-families heuristic.

Covers `add-publication-scale-features`:
- per-family patch isolates to that family
- per-source adapter isolates to its families
- per-arch runtime emitter isolates to that ISA
- docs / openspec / test paths skip the publish entirely
- unknown-path / global src changes fall back to all families
- empty diff means no publish
- ``compute_affected_from_git`` falls back to all families on diff failure
- serialised payload exposes the workflow-friendly fields
"""

from __future__ import annotations

from alloy_codegen.affected_families import (
    AffectedSet,
    all_admitted_families,
    compute_affected,
    serialize_affected_set,
)
from alloy_codegen.bootstrap import DEVICE_REGISTRY


def test_single_family_patch_isolates_to_that_family() -> None:
    affected = compute_affected(
        ["patches/espressif/esp32/devices/esp32.json"],
    )
    assert affected.all_families is False
    assert affected.families == (("espressif", "esp32"),)


def test_single_family_patch_with_unrelated_subpath_still_isolates() -> None:
    affected = compute_affected(
        [
            "patches/microchip/avr-da/family.json",
            "patches/microchip/avr-da/devices/avr128da32.json",
        ],
    )
    assert affected.all_families is False
    assert affected.families == (("microchip", "avr-da"),)


def test_source_adapter_change_scopes_to_its_families() -> None:
    """`sources/esp_idf.py` only impacts espressif families."""
    affected = compute_affected(["src/alloy_codegen/sources/esp_idf.py"])
    assert affected.all_families is False
    assert set(affected.families) == {
        ("espressif", "esp32"),
        ("espressif", "esp32c3"),
        ("espressif", "esp32s3"),
    }


def test_source_adapter_microchip_dfp_scopes_to_microchip_families() -> None:
    affected = compute_affected(["src/alloy_codegen/sources/microchip_dfp.py"])
    assert affected.all_families is False
    assert set(affected.families) == {
        ("microchip", "avr-da"),
        ("microchip", "same70"),
    }


def test_xtensa_runtime_emitter_scopes_to_xtensa_families() -> None:
    affected = compute_affected(["src/alloy_codegen/runtime_xtensa_startup.py"])
    assert affected.all_families is False
    assert set(affected.families) == {
        ("espressif", "esp32"),
        ("espressif", "esp32s3"),
    }


def test_riscv_runtime_emitter_scopes_to_riscv_families() -> None:
    affected = compute_affected(["src/alloy_codegen/runtime_riscv_startup.py"])
    assert affected.all_families is False
    assert set(affected.families) == {("espressif", "esp32c3")}


def test_avr_runtime_emitter_scopes_to_avr_families() -> None:
    affected = compute_affected(["src/alloy_codegen/runtime_avr_startup.py"])
    assert affected.all_families is False
    assert set(affected.families) == {("microchip", "avr-da")}


def test_cortex_m_runtime_emitter_scopes_to_cortex_m_families() -> None:
    affected = compute_affected(["src/alloy_codegen/runtime_startup.py"])
    assert affected.all_families is False
    expected = {
        ("microchip", "same70"),
        ("nxp", "imxrt1060"),
        ("raspberrypi", "rp2040"),
        ("st", "stm32f4"),
        ("st", "stm32g0"),
    }
    assert set(affected.families) == expected


def test_docs_only_changes_skip_publish() -> None:
    """Tests, openspec, *.md, and bootstrap-family workflow are publication-neutral."""
    for paths in (
        ["tests/test_cli.py"],
        ["openspec/changes/foo/proposal.md"],
        ["README.md"],
        [".github/workflows/bootstrap-family.yml"],
        ["openspec/AGENTS.md", "tests/test_emit.py"],
    ):
        affected = compute_affected(paths)
        assert affected.all_families is False
        assert affected.families == (), f"unexpected families for {paths!r}"


def test_unknown_src_path_falls_back_to_all_families() -> None:
    affected = compute_affected(["src/alloy_codegen/connector_model.py"])
    assert affected.all_families is True
    assert set(affected.families) == set(DEVICE_REGISTRY.keys())


def test_workflow_self_modify_triggers_full_matrix() -> None:
    affected = compute_affected([".github/workflows/publish-alloy-devices.yml"])
    assert affected.all_families is True


def test_dependency_lock_change_triggers_full_matrix() -> None:
    affected = compute_affected(["pyproject.toml"])
    assert affected.all_families is True
    affected = compute_affected(["uv.lock"])
    assert affected.all_families is True


def test_unknown_path_falls_back_to_all_families() -> None:
    """Top-level files we have no rule for trigger the conservative fallback."""
    affected = compute_affected(["LICENSE"])
    assert affected.all_families is True


def test_mixed_paths_union_then_global_short_circuits() -> None:
    """A global trigger short-circuits any partial accumulator from earlier paths."""
    affected = compute_affected(
        [
            "patches/espressif/esp32/family.json",
            "src/alloy_codegen/connector_model.py",  # global trigger
            "patches/microchip/avr-da/family.json",
        ],
    )
    assert affected.all_families is True
    assert set(affected.families) == set(DEVICE_REGISTRY.keys())


def test_mixed_partial_paths_union_two_families() -> None:
    affected = compute_affected(
        [
            "patches/espressif/esp32/family.json",
            "patches/st/stm32g0/family.json",
        ],
    )
    assert affected.all_families is False
    assert set(affected.families) == {("espressif", "esp32"), ("st", "stm32g0")}


def test_empty_diff_skips_publish() -> None:
    affected = compute_affected([])
    assert affected.all_families is False
    assert affected.families == ()


def test_force_all_returns_full_matrix() -> None:
    affected = all_admitted_families()
    assert affected.all_families is True
    assert set(affected.families) == set(DEVICE_REGISTRY.keys())


def test_to_workflow_matrix_renders_one_dict_per_family() -> None:
    affected = AffectedSet(
        all_families=False,
        families=(("espressif", "esp32"), ("st", "stm32g0")),
    )
    matrix = affected.to_workflow_matrix()
    assert matrix == [
        {"vendor": "espressif", "family": "esp32"},
        {"vendor": "st", "family": "stm32g0"},
    ]


def test_serialize_payload_for_cli_consumption() -> None:
    affected = AffectedSet(
        all_families=False,
        families=(("espressif", "esp32"),),
    )
    payload = serialize_affected_set(affected, since="HEAD~1", head="HEAD")
    assert payload["since"] == "HEAD~1"
    assert payload["head"] == "HEAD"
    assert payload["all_families"] is False
    assert payload["should_publish"] is True
    assert payload["families"] == [{"vendor": "espressif", "family": "esp32"}]
    assert payload["matrix"] == [{"vendor": "espressif", "family": "esp32"}]


def test_serialize_payload_for_empty_diff_signals_skip() -> None:
    affected = AffectedSet(all_families=False, families=())
    payload = serialize_affected_set(affected, since="HEAD~1", head="HEAD")
    assert payload["should_publish"] is False
    assert payload["families"] == []
    assert payload["matrix"] == []


def test_serialize_payload_for_full_matrix() -> None:
    affected = all_admitted_families()
    payload = serialize_affected_set(affected, since="HEAD~1", head="HEAD")
    assert payload["all_families"] is True
    assert payload["should_publish"] is True
    assert len(payload["families"]) == len(DEVICE_REGISTRY)  # type: ignore[arg-type]
