# Tasks — peripheral-trait-template-library

## Phase 1: Schema + library layout

- [x] 1.1 Defined `schemas/peripheral_traits/<class>.json` for the
      first three classes covered by the bootstrap migration:
      uart, spi, i2c.  Adding more classes (timer, pwm, adc, dac,
      can, usb) is a one-line edit per class plus a schema file.
- [x] 1.2 Created `data/peripheral_traits/<class>/` directory tree
      with seeded TOML templates for ``uart/usart_v2.toml``,
      ``uart/lpuart_v1.toml``, ``uart/nrf-uart-v1.toml``,
      ``spi/spi_v2.toml``, ``i2c/i2c_v2.toml``.
- [x] 1.3 Each template carries a top-level
      ``template_revision`` integer that the spec requires bump
      when defaults change.

## Phase 2: Seed templates from existing data

- [x] 2.1 `scripts/extract_peripheral_template.py` walks every
      admitted device patch, groups by
      `(peripheral_class, ip_name, ip_version)`, and emits a
      most-common-value TOML draft.  Deterministic — re-running
      against the same patches tree produces byte-identical
      output.
- [x] 2.2 Initial library seeded by hand for the IP versions the
      admitted families consume; the extractor is for future
      additions.
- [x] 2.3 Documentation in `docs/peripheral-trait-templates.md`
      explains the most-common-vs-correct distinction and the
      review workflow.

## Phase 3: Pipeline integration

- [x] 3.1 `alloy_codegen.peripheral_traits` module exposes
      `load_all_templates(...)` + `resolve_template(...)` so the
      normalize stage can join each peripheral instance to its
      template via `(ip_name, ip_version)`.
- [x] 3.2 `merge_chain(*layers)` implements the
      `baseline ← template ← family-patch ← device-patch` merge
      order.  Empty / `None` leaves at any layer act as "no
      override" so existing patches don't accidentally null
      template values.
- [x] 3.3 Per-peripheral migrations (drop the redundant fields
      out of every device patch) are explicitly **deferred** to
      follow-up changes (one per peripheral class).  The
      redundancy gate that backs them up lands with
      `invert-patch-as-diff`.  Until those migrations land,
      device-patch values continue to win on every leaf, so
      every existing emitted artifact stays byte-identical.

## Phase 4: Migration

- [x] 4.1 Per-class migrations deferred to dedicated follow-up
      changes (see `docs/peripheral-trait-templates.md`).  This
      change ships the library + plumbing so those migrations
      become trivial one-class-at-a-time edits.
- [x] 4.2 `docs/peripheral-trait-templates.md` lays out the
      migration order and the merge-order contract.

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/canonical-device-ir/spec.md`.
- [x] 5.2 `openspec validate peripheral-trait-template-library
      --strict` passes.
- [x] 5.3 `pytest -q` (528 tests passing) + `ruff check src/
      tests/ scripts/` clean.
