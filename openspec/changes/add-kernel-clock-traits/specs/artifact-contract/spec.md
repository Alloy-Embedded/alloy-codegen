## ADDED Requirements

### Requirement: UART / SPI / I2C / QSPI / SDMMC traits SHALL surface kernel-clock selector + max-clock

Each emitted `<peripheral>.hpp` for UART, SPI, I2C, QSPI, and SDMMC SHALL extend its specialization template with `kKernelClockSelectorField` (RCC mux `FieldRef`, or `kInvalidFieldRef` when hard-wired), `kKernelClockSourceOptions` (array mapping each `field_value` to a `ClockTreeNodeId`), `kMaxClockHz` (peripheral input clock ceiling, `0u` on the unspecialized template), and `kClockGateField` (RCC enable bit, co-located with the semantic surface).

#### Scenario: STM32G0 USART2 surfaces 4 clock sources + 64 MHz max

- **WHEN** the pipeline emits `uart.hpp` for STM32G0 stm32g071rb
- **THEN** `UartSemanticTraits<PeripheralId::USART2>::kMaxClockHz`
  equals `64'000'000u`
- **AND** `kKernelClockSourceOptions.size()` equals `4`
- **AND** the option set contains identifiers for PCLK, SYSCLK,
  HSI16, and LSE
- **AND** `kKernelClockSelectorField` resolves to the
  `RCC_CCIPR.USART2SEL` field reference

#### Scenario: AVR-DA USART0 has hard-wired clock and ships kInvalidFieldRef

- **WHEN** the pipeline emits `uart.hpp` for an AVR-DA device
- **THEN** `UartSemanticTraits<PeripheralId::USART0>::kKernelClockSelectorField`
  equals `kInvalidFieldRef` (CLK_PER is the only source)
- **AND** `kKernelClockSourceOptions.size()` equals `1`
- **AND** `kMaxClockHz` equals `24'000'000u`
