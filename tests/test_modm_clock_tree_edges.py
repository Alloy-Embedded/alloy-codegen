"""Tests for modm-devices clock-tree edge consumption.

Added by ``consume-modm-clock-tree-edges``.
"""

from __future__ import annotations

import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.ir.model import (  # noqa: E402
    ClockNodeLite,
    Provenance,
)
from alloy_codegen.sources.modm_devices import (  # noqa: E402
    ModmClockEdge,
    ModmEnrichment,
    apply_modm_enrichment,
    load_enrichment,
)
from alloy_codegen.stages.normalize import _build_st_device_ir  # noqa: E402


def _ctx() -> ExecutionContext:
    return ExecutionContext.default().with_overrides(
        source_overrides={
            "cmsis-svd-data": str(ROOT / "tests/fixtures/cmsis-svd-data"),
            "stm32-open-pin-data": str(ROOT / "tests/fixtures/stm32-open-pin-data"),
            "modm-devices": str(ROOT / "tests/fixtures/modm-devices"),
        },
        artifact_root="/tmp/_modm_a",
        publication_root="/tmp/_modm_p",
    )


def _build_pre_modm_ir():
    return _build_st_device_ir(
        execution_context=_ctx(),
        device_name="stm32g071rb",
        vendor="st",
        family="stm32g0",
    )


# ---------------------------------------------------------------------------
# End-to-end: modm clock edges flow into the IR
# ---------------------------------------------------------------------------


def test_apply_modm_enrichment_adds_clock_nodes_with_modm_provenance() -> None:
    """Spec scenario: STM32G0 stm32g071rb merges ≥5 modm clock
    nodes whose ``provenance.source_id`` is ``"modm-devices"``."""
    ir = _build_pre_modm_ir()
    enrichment = load_enrichment(_ctx(), vendor="st", family="stm32g0", device="stm32g071rb")
    assert enrichment is not None
    enriched = apply_modm_enrichment(ir, enrichment)
    modm_nodes = [n for n in enriched.clock_nodes if n.provenance.source_id == "modm-devices"]
    assert len(modm_nodes) >= 5, f"expected ≥5 modm-provenance clock_nodes; got {len(modm_nodes)}"


def test_apply_modm_enrichment_preserves_existing_patch_nodes() -> None:
    """Patch-supplied nodes (existing source_id != modm-devices)
    SHALL NOT be overwritten when modm contributes a different
    value for the same node id."""
    ir = _build_pre_modm_ir()
    pre_count = len(ir.clock_nodes)
    enriched = apply_modm_enrichment(
        ir,
        load_enrichment(_ctx(), vendor="st", family="stm32g0", device="stm32g071rb"),
    )
    # Every node that existed before MUST still be present (and
    # carry its original provenance).
    existing_ids = {n.node_id for n in ir.clock_nodes}
    for node_id in existing_ids:
        kept = next(n for n in enriched.clock_nodes if n.node_id == node_id)
        # Provenance comes from the original IR — modm did not
        # overwrite it.
        original = next(n for n in ir.clock_nodes if n.node_id == node_id)
        assert kept.provenance == original.provenance
    assert len(enriched.clock_nodes) >= pre_count


# ---------------------------------------------------------------------------
# Targeted apply_modm_enrichment unit tests
# ---------------------------------------------------------------------------


def test_apply_modm_enrichment_with_no_enrichment_is_noop() -> None:
    ir = _build_pre_modm_ir()
    result = apply_modm_enrichment(ir, None)
    assert result is ir


def test_apply_modm_enrichment_emits_selector_for_multi_parent_targets() -> None:
    """When modm has multiple edges into the same target, the
    helper SHALL emit a `mux` ClockNodeLite + a ClockSelectorLite
    with the parent options."""
    enrichment = ModmEnrichment(
        device="acme",
        family="acme1",
        clock_edges=(
            ModmClockEdge(source="hsi16", target="sysclk"),
            ModmClockEdge(source="hse", target="sysclk"),
            ModmClockEdge(source="pll_r", target="sysclk"),
        ),
    )
    # Synthetic minimal device: only the fields we use.
    from dataclasses import dataclass

    @dataclass
    class _Stub:
        clock_nodes: tuple = ()
        clock_selectors: tuple = ()
        dma_requests: tuple = ()

    result = apply_modm_enrichment(_Stub(), enrichment)
    sysclk_nodes = [n for n in result.clock_nodes if n.node_id == "sysclk"]
    assert len(sysclk_nodes) == 1
    assert sysclk_nodes[0].kind == "mux"
    assert sysclk_nodes[0].selector == "selector:sysclk"
    sel = next(s for s in result.clock_selectors if s.selector_id == "selector:sysclk")
    assert sorted(sel.parent_options) == ["hse", "hsi16", "pll_r"]


def test_apply_modm_enrichment_emits_divider_for_single_parent_with_divisor() -> None:
    enrichment = ModmEnrichment(
        device="acme",
        family="acme1",
        clock_edges=(ModmClockEdge(source="sysclk", target="hclk", divisor=1),),
    )
    from dataclasses import dataclass

    @dataclass
    class _Stub:
        clock_nodes: tuple = ()
        clock_selectors: tuple = ()
        dma_requests: tuple = ()

    result = apply_modm_enrichment(_Stub(), enrichment)
    hclk = next(n for n in result.clock_nodes if n.node_id == "hclk")
    assert hclk.kind == "divider"
    assert hclk.parent == "sysclk"
    assert hclk.selector is None


def test_apply_modm_enrichment_skips_targets_already_in_ir() -> None:
    """When the IR already carries a node for a target id, modm's
    contribution for the same target is skipped (patches win)."""
    existing_provenance = Provenance(source_id="bootstrap-patch", source_path=None, patch_ids=())
    enrichment = ModmEnrichment(
        device="acme",
        family="acme1",
        clock_edges=(ModmClockEdge(source="hsi16", target="sysclk"),),
    )
    from dataclasses import dataclass

    @dataclass
    class _Stub:
        clock_nodes: tuple = ()
        clock_selectors: tuple = ()
        dma_requests: tuple = ()

    pre_existing = ClockNodeLite(
        node_id="sysclk",
        kind="fixed",
        parent="patch_clk",
        selector=None,
        provenance=existing_provenance,
    )
    stub = _Stub(clock_nodes=(pre_existing,))
    result = apply_modm_enrichment(stub, enrichment)
    # Result still has exactly one sysclk, the patch one.
    sysclks = [n for n in result.clock_nodes if n.node_id == "sysclk"]
    assert len(sysclks) == 1
    assert sysclks[0] is pre_existing
