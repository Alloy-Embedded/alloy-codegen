# Tasks — peripheral-trait-template-library

## Phase 1: Schema + library layout

- [ ] 1.1 Define `schemas/peripheral_traits/<class>.json` for
      each admitted peripheral class (uart, spi, i2c, timer, pwm,
      adc, dac, can, usb, etc.).
- [ ] 1.2 Create `data/peripheral_traits/<class>/` directory tree.
- [ ] 1.3 Each template file is TOML with a `template_revision`
      field at the top.

## Phase 2: Seed templates from existing data

- [ ] 2.1 Build `scripts/extract_peripheral_template.py` that
      walks every admitted device's resolved IR, groups by
      `(class, ip_version)`, and emits the most-common value for
      each Tier 2/3/4 field.
- [ ] 2.2 Run the extractor across all 9 admitted families to
      seed the initial library.
- [ ] 2.3 Hand-review the seeded templates — extractor outputs
      *most common*, not *correct*; reviewer fixes outliers.

## Phase 3: Pipeline integration

- [ ] 3.1 In normalize, join each peripheral instance to its
      template via `(peripheral.ip_name, peripheral.ip_version)`.
- [ ] 3.2 Apply template defaults to the IR *before* device-patch
      overrides — the merge order is
      `baseline ← template ← family-patch ← device-patch`.
- [ ] 3.3 Patches that match template values fail validation
      (re-uses the redundancy gate from `invert-patch-as-diff`).

## Phase 4: Migration

- [ ] 4.1 Per-class migration: for each peripheral class, run the
      extractor → populate template → minify device patches →
      verify goldens unchanged → commit.
- [ ] 4.2 Document the migration order in
      `docs/peripheral-trait-templates.md`.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/canonical-device-ir/spec.md`.
- [ ] 5.2 `openspec validate peripheral-trait-template-library
      --strict` passes.
- [ ] 5.3 `pytest -q` + `ruff check` clean.
