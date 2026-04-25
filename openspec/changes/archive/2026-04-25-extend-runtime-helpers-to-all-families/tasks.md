## 1. STM32 (g0 + f4)

- [x] 1.1 Extend `_emit_route_apply_helpers` so that for `st/stm32g0` and
      `st/stm32f4` each route specialization writes `GPIOx_MODER`
      (mode = 0b10 alternate-function) and `GPIOx_AFRL` / `AFRH`
      (4-bit AF selector). Resolve `GPIOx` base from the pin's port
      via `PeripheralInstanceTraits<PeripheralId::GPIO{port}>::kBaseAddress`.
- [x] 1.2 Add a unit test asserting non-empty body for at least one
      stm32g0 and one stm32f4 route candidate.

## 2. NXP IMXRT 1060

- [x] 2.1 Extend `_emit_route_apply_helpers` for `nxp/imxrt1060` to write
      the `IOMUXC_SW_MUX_CTL_PAD_*` register's `MUX_MODE` field. Pad
      register address comes from the route's `write-selector` op
      `register_id`; the value is `op.value_int`.
- [x] 2.2 Add a unit test for one mimxrt1062 route.

## 3. Espressif ESP32-C3 / S3

- [x] 3.1 Extend `_emit_clock_enable_disable_helpers` for `espressif/*`
      so per-peripheral PCER-equivalent (`SYSTEM_PERIP_CLK_EN0_REG`
      etc.) gets a set-bit / clear-bit specialization.
- [x] 3.2 Extend `_emit_route_apply_helpers` for `espressif/*`:
      write `IO_MUX_GPIOx_REG.MCU_SEL` and the matching
      `GPIO_FUNCx_OUT_SEL_CFG` register.
- [x] 3.3 Unit tests covering esp32c3 + esp32s3.

## 4. Raspberry Pi RP2040

- [x] 4.1 Add a `clock_enable<>` strategy for RP2040 that writes
      `RESETS_RESET_CLR` (release-from-reset) for the peripheral
      and busy-waits on `RESETS_RESET_DONE` until the bit clears.
- [x] 4.2 Extend `_emit_route_apply_helpers` for `raspberrypi/rp2040`:
      write `IO_BANK0_GPIOx_CTRL.FUNCSEL` (5-bit selector).
- [x] 4.3 Unit tests for rp2040 + pico devices.

## 5. Microchip AVR-DA

- [x] 5.1 Make `clock_enable/disable<>` a no-op (with valid empty body)
      for peripherals whose IR has no clock-gate binding; keeps the
      compile-time guard but doesn't error.
- [x] 5.2 Extend `_emit_route_apply_helpers` for `microchip/avr-da` to
      write the matching `PORTMUX.*ROUTE*` selector.
- [x] 5.3 Unit tests for avr128da32.

## 6. Validation

- [x] 6.1 `python -m ruff format src tests` + `python -m ruff check src tests`.
- [x] 6.2 `python -m pytest tests` green.
- [ ] 6.3 `openspec validate extend-runtime-helpers-to-all-families --strict`.
- [ ] 6.4 Republish all admitted families into `alloy-devices`.
- [ ] 6.5 alloy build matrix (review-same70, review-g071, review-f401)
      stays green against the new contract.
