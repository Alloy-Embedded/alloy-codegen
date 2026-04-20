## 1. Spec and Typed Profile Model

- [x] 1.1 Add this executable non-ST system-clock change
- [x] 1.2 Extend the typed `system_clock_profiles` model/schema with non-ST numeric knobs
- [x] 1.3 Thread the new fields through patch parsing and normalization

## 2. SAME70 Data Publication

- [x] 2.1 Publish SAME70 PMC/EFC clock registers through the patch/device contract
- [x] 2.2 Publish SAME70 clock-related fields needed by executable bring-up
- [x] 2.3 Publish executable SAME70 profiles for internal RC, crystal direct, and PLLA

## 3. Runtime-Lite Emission

- [x] 3.1 Extend the runtime-lite register/field closure for SAME70 system-clock helpers
- [x] 3.2 Emit executable SAME70 `apply_system_clock_profile<...>()` branches
- [x] 3.3 Block foundational publication when SAME70 falls back to metadata-only system-clock bodies

## 4. Tests and Validation

- [x] 4.1 Update emit/artifact tests for executable SAME70 system-clock helpers
- [x] 4.2 Regenerate affected canonical/emitted fixtures
- [x] 4.3 Validate with `python3 -m ruff check src tests`
- [x] 4.4 Validate with `python3 -m pytest tests -q`
- [x] 4.5 Validate with `openspec validate materialize-executable-nonst-system-clock-profiles --strict`

## 5. IMXRT1060 Completion

- [x] 5.1 Publish IMXRT1060 `CCM/CCM_ANALOG/DCDC` register closure for executable system-clock bring-up
- [x] 5.2 Publish a performance ARM PLL system-clock profile for foundational IMXRT1060 devices
- [x] 5.3 Emit executable IMXRT1060 `apply_system_clock_profile<...>()` branches
- [x] 5.4 Block foundational publication when IMXRT1060 still falls back to metadata-only system-clock bodies
- [x] 5.5 Regenerate affected IMXRT1060 fixtures and refresh tests
