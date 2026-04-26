# Tasks — fill-gpio-tier-1-fields

## Phase 1: Wire field resolution

- [ ] 1.1 Add `_st_gpio_field_for_pin(context, port, pin_index, field_kind)`
      helper resolving `MODE{n}`, `OSPEED{n}`, `OT{n}`, `PUPD{n}` from
      `device.register_fields`.
- [ ] 1.2 `_st_gpio_row` populates `kModeField`, `kSpeedField`,
      `kOutputTypeField`, `kPullField` via the helper instead of
      `_invalid_field_ref`.
- [ ] 1.3 Verify the SAM and RP2040 paths still emit their existing
      (valid) field refs — no regression.

## Phase 2: Tests + goldens

- [ ] 2.1 Regression test: `GpioSemanticTraits<PinId::PA0>::kModeField`
      on STM32G0 stm32g071rb resolves to a non-invalid `FieldRef`
      whose register is `GPIOA.MODER` and bit offset is `0`.
- [ ] 2.2 Same for `kSpeedField` (`OSPEEDR.OSPEED0`),
      `kOutputTypeField` (`OTYPER.OT0`), `kPullField`
      (`PUPDR.PUPD0`).
- [ ] 2.3 Regenerate `gpio.hpp` goldens for stm32g0 + stm32f4.

## Phase 3: Spec + final checks

- [ ] 3.1 Spec delta in `specs/artifact-contract/spec.md`.
- [ ] 3.2 `openspec validate fill-gpio-tier-1-fields --strict` passes.
- [ ] 3.3 Full `pytest -q` + `ruff check` clean.
- [ ] 3.4 Archive entry notes that this unblocks compile-time
      GPIO configuration for STM32 in the alloy HAL.
