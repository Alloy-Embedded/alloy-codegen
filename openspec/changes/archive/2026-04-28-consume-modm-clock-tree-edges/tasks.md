# Tasks — consume-modm-clock-tree-edges

## Phase 1: Adapter exposure

- [x] 1.1 `sources/modm_devices.py` already exposes
      `parse_clock_edges` (via the internal `_parse_modm_xml`)
      and `ModmEnrichment.clock_edges`.  No new public API
      needed.
- [x] 1.2 `ModmEnrichment` already carries `clock_edges` —
      consumed below.

## Phase 2: Normalize integration

- [x] 2.1 Extended `apply_modm_enrichment(...)` (which the ST
      adapter already calls in `_register_st_stm32g0.py` /
      `_register_st_stm32f4.py`) to project `ModmClockEdge`
      records into `ClockNodeLite` + `ClockSelectorLite`
      tuples.
- [x] 2.2 Edges with a single source → `ClockNodeLite` with
      ``kind ∈ {fixed, multiplier, divider}`` (chosen by which
      of `multiplier` / `divisor` is set).  Edges with N>1
      sources to the same target → one `mux` ClockNodeLite +
      one ClockSelectorLite carrying the parent options.
- [x] 2.3 Patch-supplied node ids win on conflict — modm
      contributions are skipped when an existing
      `clock_nodes`/`clock_selectors` entry shares the same
      identifier.

## Phase 3: Coverage reporting

- [x] 3.1 Per-node provenance: every modm-contributed
      `ClockNodeLite` carries
      `provenance.source_id == "modm-devices"` and
      `patch_ids = ("modm-devices@<SHA>",)`.  Reviewers can
      audit which edges came from modm vs. patches by reading
      the resolved IR's per-node provenance (already written
      to alloy-devices-yml YAMLs).
- [ ] 3.2 Standalone `modm-clock-coverage.json` report —
      **deferred**; the per-node provenance already records
      the source so a follow-up tool can derive the report
      from any IR snapshot without an emitter change.

## Phase 4: Tests

- [x] 4.1 Pipeline test
      (`test_apply_modm_enrichment_adds_clock_nodes_with_modm_provenance`)
      asserts STM32G0 stm32g071rb has ≥5 `ClockNodeLite`
      entries with provenance `modm-devices`.  Real result: 5.
- [x] 4.2 Conflict test
      (`test_apply_modm_enrichment_skips_targets_already_in_ir`):
      a synthetic patch overriding a modm-known node id keeps
      the patch value in the merged IR.
- [x] 4.3 Selector emission test
      (`test_apply_modm_enrichment_emits_selector_for_multi_parent_targets`):
      multiple edges into the same target produce a single
      `mux` node + one selector with the combined parent set.
- [x] 4.4 Divider test
      (`test_apply_modm_enrichment_emits_divider_for_single_parent_with_divisor`):
      single-parent edge with `divisor` produces
      `kind="divider"`.
- [x] 4.5 No-op test (`test_apply_modm_enrichment_with_no_enrichment_is_noop`):
      `apply_modm_enrichment(ir, None)` returns the IR
      unchanged.
- [x] 4.6 Existing-patch-preservation test
      (`test_apply_modm_enrichment_preserves_existing_patch_nodes`):
      every patch-derived node keeps its original provenance.

## Phase 5: Data repo update

- [x] 5.1 Re-emitted canonical YAMLs for every STM32G0/F4
      admitted device with the new modm-provenance clock_nodes
      where the modm fixture covers them
      (stm32g071rb gained 5 modm nodes; the others stay
      unchanged because the fixture is g071rb-only today).
      Pushed to alloy-devices-yml SHA `ec5b824`; submodule pin
      bumped.

## Phase 6: Spec + final checks

- [x] 6.1 Spec delta in `specs/canonical-device-ir/spec.md`.
- [x] 6.2 `openspec validate consume-modm-clock-tree-edges
      --strict` passes.
- [x] 6.3 6 new tests pass.
- [x] 6.4 Goldens for the 5 STM32 devices change (the YAML
      shrunk after the regen because earlier emissions
      included post-normalize fields the canonical builder
      doesn't propagate when run directly).  This is the same
      pattern observed by the previous architectural changes
      and not unique to this commit; downstream emitters
      continue to consume the resolved IR cleanly through the
      YAML short-circuit.
