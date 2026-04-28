## ADDED Requirements

### Requirement: The pipeline SHALL emit per-device validity-concept headers for DMA, clock-source, IRQ-slot, and I2C-speed

The pipeline SHALL emit four additional per-device runtime
headers projecting IR-carried wiring data into C++20 concepts:

* `dma_validation.hpp` — `ValidDmaBinding<PeripheralId,
  DmaChannelId>` from `dma_bindings`.
* `clock_validation.hpp` — `ValidClockSource<PeripheralId,
  ClockSourceId>` from `peripheral_clock_bindings`.
* `interrupt_validation.hpp` — `ValidInterruptSlot<PeripheralId,
  VectorSlotId>` from `interrupt_bindings` +
  `vector_slots`.
* `i2c_speed_validation.hpp` — a `consteval`-driven
  `ValidI2cSpeed<PeripheralId, SpeedHz>` concept whose
  predicate consults `i2c_peripherals.speed_modes`.

Each header SHALL follow the existing `pin_validation.hpp`
shape: a primary template `: std::false_type {}` plus
per-candidate `: std::true_type` specialisations, plus a
convenience `concept Valid<...> = ...::value;` declaration.
The headers SHALL be omitted entirely when the underlying IR
tuples are empty (no DMA bindings → no `dma_validation.hpp`
emitted), preserving today's behaviour for partially-populated
IRs.

#### Scenario: stm32g071rb emits all four concept headers with real specialisations

- **WHEN** the pipeline emits artifacts for stm32g071rb
- **THEN** the four `<concept>_validation.hpp` files SHALL
  exist
- **AND** each SHALL contain at least one `: std::true_type`
  specialisation drawn from the device's IR (DMA bindings,
  peripheral clock bindings, interrupt bindings, I2C speed
  modes)

#### Scenario: ValidI2cSpeed evaluates to true for an admitted speed

- **WHEN** a consumer writes
  `static_assert(ValidI2cSpeed<PeripheralId::I2C1, 400'000>)`
  against an stm32g071rb whose I2C1 admits `fast` mode
- **THEN** the assertion SHALL pass at compile time
- **AND** an asserted speed *outside* the device's admitted
  range (e.g. `2'000'000` on a chip that admits up to
  `1'000'000` fast-plus) SHALL fail compilation

#### Scenario: Devices with empty source tuples emit no concept header

- **WHEN** a device's `dma_bindings` tuple is empty
- **THEN** `dma_validation.hpp` SHALL NOT appear in the
  emitted artifact set
- **AND** no other artifact SHALL be affected
