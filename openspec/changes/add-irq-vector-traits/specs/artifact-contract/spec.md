## ADDED Requirements

### Requirement: Per-peripheral semantic traits SHALL surface NVIC IRQ numbers

Every emitted `<peripheral>.hpp` SHALL carry a `kIrqNumbers` constexpr array (or split scalar fields for TIMER / per-channel for DMA) listing the NVIC vector indices that fire for each admitted peripheral instance, sourced from the canonical-device-IR `interrupt_bindings` table filtered by `peripheral_aliases`. The unspecialized template SHALL ship an empty array (or sentinel `0xFFFF'FFFFu` for the split scalar form) so consumer code that branches on `kIrqNumbers.size() > 0` compiles even when no binding is admitted.

#### Scenario: STM32G0 USART2 advertises USART2_IRQn

- **WHEN** the pipeline emits `uart.hpp` for an STM32G0 device that
  admits USART2 and the IR carries an `InterruptDescriptor` named
  `USART2` with `peripheral_aliases = ("USART2",)`
- **THEN** `UartSemanticTraits<PeripheralId::USART2>::kIrqNumbers`
  has size `1` and `kIrqNumbers[0]` equals the SVD-reported
  USART2 NVIC vector number

#### Scenario: STM32G0 TIM1 splits update / capture / break / trigger

- **WHEN** the pipeline emits `timer.hpp` for an STM32G0 device that
  admits TIM1
- **THEN** `TimerSemanticTraits<PeripheralId::TIM1>::kUpdateIrqNumber`
  matches the TIM1_BRK_UP_TRG_COM line index reported by the SVD
- **AND** `kBreakIrqNumber`, `kTriggerIrqNumber` mirror the same
  line on G0 (shared vector); on F4/F7 they resolve to distinct
  indices

#### Scenario: AVR-DA SPI0 has no NVIC and ships an empty array

- **WHEN** the pipeline emits `spi.hpp` for an AVR-DA device
- **THEN** `SpiSemanticTraits<PeripheralId::SPI0>::kIrqNumbers.size()`
  equals `0` (AVR has its own vector table not surfaced as
  `interrupt_bindings`)
- **AND** the unspecialized fallback `SpiSemanticTraits<X>::kIrqNumbers`
  is `std::array<std::uint32_t, 0>{}`
