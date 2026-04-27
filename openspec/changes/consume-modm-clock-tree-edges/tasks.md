# Tasks — consume-modm-clock-tree-edges

## Phase 1: Adapter exposure

- [ ] 1.1 Confirm `sources/modm_devices.py` already exposes
      `parse_clock_edges(...)` returning
      `tuple[ModmClockEdge, ...]`.  If only internal, expose
      via the public adapter API.
- [ ] 1.2 Add `clock_edges` to the modm document type so the
      normalize stage can consume it without re-parsing.

## Phase 2: Normalize integration

- [ ] 2.1 In `_build_st_device_ir`, build a
      family-scoped index of modm clock edges keyed by
      `(source_node, target_node)` once per family.
- [ ] 2.2 For each modm edge, project a `ClockNodeLite`
      (target side) + `ClockSelectorLite` entry into the IR
      tuples *before* applying the family/device patch
      overlays.
- [ ] 2.3 Patch values for the same `(node, selector)` keys
      take precedence (today's merge contract); modm fills
      gaps only.

## Phase 3: Coverage reporting

- [ ] 3.1 Per-device IR enrichment records each
      `ClockNodeLite.provenance.source_id = "modm-devices"`
      when modm contributed it (vs. `"bootstrap-patch"` when
      a hand patch did).
- [ ] 3.2 New report
      `tests/fixtures/emitted/<vendor>/<family>/reports/
      modm-clock-coverage.json` per device summarising how many
      nodes came from each source.

## Phase 4: Tests

- [ ] 4.1 Pipeline test asserting STM32G0 stm32g071rb has at
      least 5 `ClockNodeLite` entries with provenance
      `modm-devices` after the merge.
- [ ] 4.2 Conflict test: a synthetic family patch overriding
      a modm-known node value wins in the merged IR.
- [ ] 4.3 Goldens stay byte-identical when patches already
      covered the modm-supplied edges (the common case
      today).

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/canonical-device-ir/spec.md`.
- [ ] 5.2 `openspec validate consume-modm-clock-tree-edges
      --strict` passes.
- [ ] 5.3 `pytest -q` + `ruff check` clean.
