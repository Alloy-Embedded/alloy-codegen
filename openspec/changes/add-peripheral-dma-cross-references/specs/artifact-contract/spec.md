## ADDED Requirements

### Requirement: Peripheral semantic traits SHALL surface DMA bindings as a typed array

Every emitted `<peripheral>.hpp` SHALL emit a populated `kDmaBindings` constexpr array of `DmaBindingRef` records carrying controller ID, channel index, request line, signal direction (`Tx` / `Rx` / `Cmd` / `Ack` / ...) and transfer-width-bits derived from the peripheral's frame size, for every peripheral instance with non-empty `device.dma_requests`. The unspecialized template SHALL ship `std::array<DmaBindingRef, 0>{}` so consumer code branching on `kDmaBindings.size() > 0` compiles even when no binding is admitted.

#### Scenario: STM32G0 USART1 surfaces TX + RX bindings

- **WHEN** the pipeline emits `uart.hpp` for STM32G0 stm32g071rb
- **THEN** `UartSemanticTraits<PeripheralId::USART1>::kDmaBindings`
  has size `2`
- **AND** one entry has `signal == DmaSignal::Tx` and the other
  `DmaSignal::Rx`
- **AND** both entries have `transfer_width_bits == 8`
- **AND** the `binding_id` field on each entry matches the ID
  used by the existing `dma.hpp` `DmaSemanticTraits<USART1, Tx>` /
  `<USART1, Rx>` specializations

### Requirement: ADC semantic traits SHALL no longer drop DMA bindings on the floor

The ADC specialization builder SHALL surface the same `kDmaBindings` array. The current behavior — calling `_dma_bindings_for_peripheral` and discarding the result — is a bug and SHALL be fixed.

#### Scenario: STM32G0 ADC1 surfaces its DMA binding

- **WHEN** the pipeline emits `adc.hpp` for STM32G0 stm32g071rb
- **THEN** `AdcSemanticTraits<PeripheralId::ADC1>::kHasDma == true`
- **AND** `kDmaBindings.size() >= 1`
- **AND** the first entry carries the request line ID emitted in
  `dma.hpp` for ADC1
