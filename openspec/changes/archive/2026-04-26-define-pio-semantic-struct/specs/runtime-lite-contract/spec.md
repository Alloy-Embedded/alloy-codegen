## ADDED Requirements

### Requirement: pio.hpp SHALL define a populated PioSemanticTraits surface

Every emitted `driver_semantics/pio.hpp` SHALL declare a primary
`PioSemanticTraits<PioId>` template whose body provides zero-valued defaults
for the full set of compile-time PIO facts so that downstream alloy concept
checks can rely on the fields existing regardless of family:

- `kPresent: bool` (default `false`)
- `kStateMachineCount: std::uint8_t`
- `kInstructionMemoryDepth: std::uint8_t`
- `kTxFifoDepth: std::uint8_t`
- `kRxFifoDepth: std::uint8_t`
- `kGpioBase: std::uint8_t`
- `kGpioCount: std::uint8_t`
- `kBaseAddress: std::uint32_t`
- `kDreqTx: std::uint8_t`
- `kDreqRx: std::uint8_t`

Devices without PIO hardware SHALL emit only the primary template (all defaults).

#### Scenario: Non-PIO families keep zero-cost defaults

- **WHEN** a device with `pio_blocks == []` is emitted
- **THEN** the emitted `pio.hpp` declares the primary template with all fields
  defaulted to zero (and `kPresent = false`)
- **AND** no `PioSemanticTraits<PioId::*>` specializations are emitted

#### Scenario: RP2040 emits fully populated specializations

- **WHEN** the RP2040 device is emitted
- **THEN** `pio.hpp` contains a `PioSemanticTraits<PioId::Pio0>` specialization
  with `kPresent = true`, `kStateMachineCount = 4`, `kInstructionMemoryDepth = 32`,
  `kTxFifoDepth = 4`, `kRxFifoDepth = 4`, `kGpioBase = 0`, `kGpioCount = 30`,
  `kBaseAddress = 0x50200000u`, `kDreqTx = 0`, `kDreqRx = 4`
- **AND** an analogous `PioSemanticTraits<PioId::Pio1>` specialization is emitted
  with `kBaseAddress = 0x50300000u`, `kDreqTx = 8`, `kDreqRx = 12`

### Requirement: pio.hpp SHALL define StateMachineSemanticTraits per PIO state machine

Every emitted `driver_semantics/pio.hpp` SHALL declare a primary
`StateMachineSemanticTraits<PioId, std::uint8_t Sm>` template providing
`kPresent`, `kDreqTx`, and `kDreqRx` defaults so consumer code can index
state-machine DREQs at compile time without runtime arithmetic.

For each `PioDescriptor` in `device.pio_blocks`, the emitter SHALL produce
`state_machine_count` specializations whose `kDreqTx = dreq_tx_base + sm` and
`kDreqRx = dreq_rx_base + sm` for `sm` in `[0, state_machine_count)`.

#### Scenario: RP2040 emits 8 state-machine specializations

- **WHEN** the RP2040 device is emitted
- **THEN** `pio.hpp` declares `StateMachineSemanticTraits<PioId::Pio0, 0>`
  through `StateMachineSemanticTraits<PioId::Pio1, 3>` (8 specializations total)
- **AND** `StateMachineSemanticTraits<PioId::Pio0, 3>::kDreqTx == 3`
- **AND** `StateMachineSemanticTraits<PioId::Pio1, 2>::kDreqTx == 10`
- **AND** every specialization sets `kPresent = true`

#### Scenario: Non-PIO families emit only the primary StateMachineSemanticTraits template

- **WHEN** a device with `pio_blocks == []` is emitted
- **THEN** `pio.hpp` declares the primary `StateMachineSemanticTraits` template
  with `kPresent = false` and zero-valued DREQ defaults
- **AND** emits no `StateMachineSemanticTraits<...>` specializations
