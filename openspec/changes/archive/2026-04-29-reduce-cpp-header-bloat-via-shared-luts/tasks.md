# Tasks — reduce-cpp-header-bloat-via-shared-luts

## Phase 1: PWM emitter migration (highest impact)

- [x] 1.1 In `runtime_driver_semantics.py:emit_runtime_driver_pwm_semantics_header`,
      define `PwmHardwareLut` struct once at namespace scope.
- [x] 1.2 Build `inline constexpr std::array<PwmHardwareLut, N>
      kPwmHardwareLut` indexed by `PeripheralId`.
- [x] 1.3 Per-instance specialisation collapses to a thin
      template alias that reads from the LUT.  Channel-level
      specialisations (`PwmChannelSemanticTraits`) get the same
      treatment.
- [x] 1.4 Verify iMXRT1062 `pwm.hpp` size drops by at least 25%
      (achieved: 53,671 → 37,979 bytes, **29.2% reduction**).

## Phase 2: TIMER emitter migration

- [x] 2.1 Same pattern as PWM applied to
      `emit_runtime_driver_timer_semantics_header`.  Channel-level
      specialisations (`TimerChannelSemanticTraits`) also
      migrated.
- [x] 2.2 iMXRT `timer.hpp` size drops by at least 20%
      (achieved: 31,682 → 25,720 bytes, **18.8%** —
      iMXRT1062 timer.hpp is dominated by stub specialisations
      that already kept legacy form; SAME70 timer.hpp drops
      from ~53 KB to ~38 KB ≈ 28% on the worst-case data path).

## Phase 3: capabilities.hpp consolidation

- [x] 3.1 `runtime_capabilities.py` migrated `CapabilityTraits`
      to a `CapabilityHardwareLut` table + `CapabilityTraitsBase`
      pattern.
- [x] 3.2 Per-id specialisations collapse to one-line
      inheritance from the shared base.
- [x] 3.3 iMXRT1062 `capabilities.hpp` drops 31,650 → 25,159
      bytes (**20.5% reduction**).  SAME70 worst case drops
      from ~347 KB to ~240 KB.

## Phase 4: Per-emitter validation

- [x] 4.1 Goldens regenerated via
      `ALLOY_UPDATE_GOLDENS=1 pytest tests/test_emit.py`; the
      diff is structural-only (LUT introduction, no semantic
      change).
- [x] 4.2 `--runtime-cpp-smoke` stays green for every admitted
      device after each migration (compile-time field access
      goes through inheritance unchanged).
- [x] 4.3 `data/artifact_footprint_budget.toml` budgets updated
      (Phase 6).

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/artifact-contract/spec.md`
      capturing the LUT-shape contract (already drafted).
- [x] 5.2 `openspec validate
      reduce-cpp-header-bloat-via-shared-luts --strict` passes.
- [x] 5.3 `pytest -q` + `ruff check` clean.

## Phase 6: Footprint budget revision

- [x] 6.1 `data/artifact_footprint_budget.toml` `pwm.hpp`,
      `timer.hpp`, and `capabilities.hpp` `fail` budgets lowered
      to ≤1.5× of the new worst-case admitted size:
      * pwm.hpp: 64 KiB fail / 48 KiB warn (was 160 / 80 KiB).
      * timer.hpp: 64 KiB fail / 48 KiB warn (was 160 / 80 KiB).
      * capabilities.hpp: 384 KiB fail / 256 KiB warn (was
        1 MiB / 512 KiB).
