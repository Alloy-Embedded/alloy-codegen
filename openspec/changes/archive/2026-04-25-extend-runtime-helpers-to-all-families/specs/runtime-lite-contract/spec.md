# Runtime Lite Contract — Per-Family Helpers Delta

## ADDED Requirements

### Requirement: STM32 G0 and F4 emit pinmux apply specializations

The runtime-lite emission SHALL produce, for every `(Pin, Peripheral, Signal)`
route candidate admitted on `st/stm32g0` and `st/stm32f4` devices, an
`apply_route<>()` specialization whose body writes `GPIOx_MODER`
(alternate-function mode) and `GPIOx_AFRL`/`AFRH` (4-bit AF selector)
for that pin.

#### Scenario: stm32g071rb USART2 PA2/PA3 routes

- **WHEN** the runtime-lite emission runs for `stm32g071rb`
- **THEN** `apply_route<PinId::PA2, PeripheralId::USART2, SignalId::tx>()`
  contains a write to `GPIOA_MODER` setting bits [5:4] to `0b10`
- **AND** a write to `GPIOA_AFRL` setting bits [11:8] to the AF
  number recorded in the IR for that route

### Requirement: NXP IMXRT 1060 emits pinmux apply specializations

Every IMXRT 1060 route candidate SHALL emit an `apply_route<>()`
specialization that writes the pad's `IOMUXC_SW_MUX_CTL_PAD_*`
register with the IR-recorded `MUX_MODE` value.

#### Scenario: mimxrt1062 LPUART1 routes

- **WHEN** emission runs for `mimxrt1062`
- **THEN** `apply_route<>` for any LPUART1 pin contains a write to
  the corresponding `IOMUXC_SW_MUX_CTL_PAD_*` register with the
  selector value from the route operation table

### Requirement: Espressif ESP32 emits clock and pinmux helpers

The runtime-lite emission SHALL produce, for both `espressif/esp32c3`
and `espressif/esp32s3`, per-peripheral `clock_enable/disable<>`
specializations writing `SYSTEM_PERIP_CLK_EN*_REG` (set-bit/clear-bit),
and `apply_route<>` specializations writing the GPIO-matrix
`GPIO_FUNCx_OUT_SEL_CFG` and `IO_MUX_GPIOx_REG.MCU_SEL`.

#### Scenario: esp32c3 UART0 routes are bound to apply_route specializations

- **WHEN** emission runs for `esp32c3`
- **THEN** `apply_route<>` for an admitted UART0 pin writes the
  IO_MUX MCU_SEL field for that GPIO and the matching GPIO matrix
  output-select register

### Requirement: Raspberry Pi RP2040 emits clock and pinmux helpers

For `raspberrypi/rp2040`, the runtime-lite output SHALL emit
`clock_enable<>` specializations that release the peripheral from
reset via `RESETS_RESET_CLR` (and poll `RESETS_RESET_DONE`), and
`apply_route<>` specializations that write `IO_BANK0_GPIOx_CTRL.FUNCSEL`
with the IR-recorded 5-bit function selector.

#### Scenario: rp2040 UART0 TX route configures FUNCSEL

- **WHEN** emission runs for `rp2040`
- **THEN** `apply_route<>` for the admitted UART0 TX pin contains a
  write to the corresponding `IO_BANK0_GPIO*_CTRL` register that sets
  the `FUNCSEL` field to `2` (UART)

### Requirement: Microchip AVR-DA emits pinmux apply specializations

For `microchip/avr-da` devices, every admitted route candidate SHALL
emit an `apply_route<>()` specialization that writes the matching
`PORTMUX.*ROUTE*` selector. `clock_enable/disable<>` for peripherals
without per-instance clock gating SHALL be valid empty inline
specializations.

#### Scenario: avr128da32 USART0 default route

- **WHEN** emission runs for `avr128da32`
- **THEN** `apply_route<>` for the default USART0 TX pin writes the
  `PORTMUX.USARTROUTEA` field for USART0 to the IR-recorded value
