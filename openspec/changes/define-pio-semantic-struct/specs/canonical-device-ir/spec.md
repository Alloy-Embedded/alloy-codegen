## MODIFIED Requirements

### Requirement: IR SHALL capture PIO as a present peripheral with an explicit stub schema

The canonical IR SHALL capture Programmable I/O (PIO) peripherals as present entries
with a named stub schema that explicitly signals the program-execution semantics
(state-machine instruction format, assembled program payloads) are not yet fully
modeled, while the topology of each block is structured via `PioDescriptor`
(see "IR SHALL model PIO blocks with a structured PioDescriptor"). The stub
schema designation applies only to program-execution semantics; topology is
no longer stubbed.

#### Scenario: PIO0 and PIO1 are present in RP2040 canonical IR

- **WHEN** the RP2040 device is normalized
- **THEN** `PIO0` and `PIO1` appear in the peripheral instance list
- **AND** their `backend_schema_id` is `alloy.pio.rp2040-v1-stub`
- **AND** the capability manifest records `runtime-support:pio` as present

#### Scenario: PIO stub schema does not block admission

- **WHEN** the RP2040 vendor-admission gates are evaluated
- **THEN** the presence of PIO with a stub schema does not cause any CI gate to fail
- **AND** the stub schema is explicitly recognized as admission-valid until a full
  PIO program-execution spec is approved

## ADDED Requirements

### Requirement: IR SHALL model PIO blocks with a structured PioDescriptor

The canonical device IR SHALL represent each Programmable I/O block as a
`PioDescriptor` carrying the compile-time facts that downstream emitters need to
populate driver-semantic traits (state-machine count, instruction memory depth,
TX/RX FIFO depth, GPIO range, base address, and TX/RX DMA DREQ bases).

`PioDescriptor` SHALL be carried on `CanonicalDeviceIR` as `pio_blocks: list[PioDescriptor]`,
defaulting to an empty list for devices without PIO hardware.

#### Scenario: RP2040 IR exposes two structured PIO descriptors

- **WHEN** the RP2040 device is normalized
- **THEN** `device.pio_blocks` contains two entries with `pio_id` `Pio0` and `Pio1`
- **AND** each entry records `state_machine_count = 4`, `instruction_memory_depth = 32`,
  `tx_fifo_depth = 4`, `rx_fifo_depth = 4`, `gpio_base = 0`, `gpio_count = 30`
- **AND** `Pio0.base_address == 0x50200000` and `Pio1.base_address == 0x50300000`
- **AND** `Pio0.dreq_tx_base == 0`, `Pio0.dreq_rx_base == 4`,
  `Pio1.dreq_tx_base == 8`, `Pio1.dreq_rx_base == 12`

#### Scenario: Devices without PIO leave pio_blocks empty

- **WHEN** any non-RP2040 admitted device is normalized
- **THEN** `device.pio_blocks` is an empty list
- **AND** the canonical IR JSON serialization omits or emits an empty `pio_blocks` array

#### Scenario: PioDescriptor data is patch-sourced and provenance-tagged

- **WHEN** the RP2040 normalizer assembles `pio_blocks`
- **THEN** the values are loaded from `patches/raspberrypi/rp2040/pio.json`
- **AND** each `PioDescriptor` carries provenance referencing that patch file
