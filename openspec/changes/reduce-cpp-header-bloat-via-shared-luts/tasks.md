# Tasks — reduce-cpp-header-bloat-via-shared-luts

## Phase 1: PWM emitter migration (highest impact)

- [ ] 1.1 In `runtime_driver_semantics.py:emit_runtime_driver_pwm_semantics_header`,
      define `PwmHardwareLut` struct once at namespace scope.
- [ ] 1.2 Build `inline constexpr std::array<PwmHardwareLut, N>
      kPwmHardwareLut` indexed by `PeripheralId`.
- [ ] 1.3 Per-instance specialisation collapses to a thin
      template alias that reads from the LUT.
- [ ] 1.4 Verify iMXRT1062 `pwm.hpp` size drops by at least 25%
      (target: 52 KB → 35 KB).

## Phase 2: TIMER emitter migration

- [ ] 2.1 Same pattern as PWM applied to
      `emit_runtime_driver_timer_semantics_header`.
- [ ] 2.2 iMXRT `timer.hpp` size drops by at least 20%
      (target: 31 KB → 24 KB).

## Phase 3: capabilities.hpp consolidation

- [ ] 3.1 Audit `runtime_capabilities.py` for the duplicated
      enum surface.
- [ ] 3.2 Pull the duplicated identifiers into a single
      `CapabilityClassEnum` once per family (vs. once per
      device).
- [ ] 3.3 Per-device `capabilities.hpp` becomes a thin index
      table over the shared enum.

## Phase 4: Per-emitter validation

- [ ] 4.1 Goldens regen via `--update-goldens` per migrated
      emitter; reviewer manually confirms the diff is
      structural-only (LUT introduction, no semantic change).
- [ ] 4.2 `--runtime-cpp-smoke` stays green for every admitted
      device after each migration.
- [ ] 4.3 `artifact-footprint-budget` gate: every migrated
      artifact's new size still fits within its budget — and
      the existing budgets get revised down to capture the
      win.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/artifact-contract/spec.md`
      capturing the LUT-shape contract.
- [ ] 5.2 `openspec validate
      reduce-cpp-header-bloat-via-shared-luts --strict` passes.
- [ ] 5.3 `pytest -q` + `ruff check` clean.

## Phase 6: Footprint budget revision

- [ ] 6.1 After all three emitters migrate, lower the per-artifact
      `fail` budgets in
      `data/artifact_footprint_budget.toml` to lock in the win
      (currently sized at 1.5× the worst-case admitted device;
      shrink to 1.5× the new worst case).
