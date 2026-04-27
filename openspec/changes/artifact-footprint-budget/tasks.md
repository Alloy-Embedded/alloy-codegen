# Tasks — artifact-footprint-budget

## Phase 1: Budget configuration

- [ ] 1.1 Create `data/artifact_footprint_budget.toml` with
      initial budgets for every emitted artifact name, derived
      from current worst-case output + 50% headroom.
- [ ] 1.2 Create `data/artifact_footprint_overrides.toml`
      (initially empty) for per-device exemptions.
- [ ] 1.3 Document the policy in
      `docs/artifact-footprint-budget.md`.

## Phase 2: Gate implementation

- [ ] 2.1 Extend the publish stage to measure every emitted
      artifact's UTF-8 byte size.
- [ ] 2.2 Compare against the budget; surface `warn` exceedances
      in the validation report.
- [ ] 2.3 Abort the build on `fail` exceedances unless an
      override entry covers the offending
      `(vendor, family, device, artifact_name)`.

## Phase 3: Tests

- [ ] 3.1 Unit test that no currently admitted device's emitted
      artifact exceeds its `warn` budget on day one.
- [ ] 3.2 Synthetic test that a deliberately oversized artifact
      triggers the `fail` mode with a discoverable error message.
- [ ] 3.3 Test that an override entry suppresses a `fail`
      exceedance for the matched device only.

## Phase 4: Spec + final checks

- [ ] 4.1 Spec delta in `specs/validation-and-gates/spec.md`.
- [ ] 4.2 `openspec validate artifact-footprint-budget --strict`
      passes.
- [ ] 4.3 `pytest -q` + `ruff check` clean.
