## ADDED Requirements

### Requirement: AVR-DA devices emit runtime headers matching the standard contract shape

Microchip AVR-DA devices MUST emit the same runtime header set as ARM foundational devices,
with the exception of headers that are explicitly gated on Cortex-M architecture, and with
an AVR-specific startup artifact instead of an ARM CMSIS vector table.

#### Scenario: AVR128DA32 runtime device headers are present and valid

- **WHEN** the pipeline emits artifacts for an AVR128DA32 device
- **THEN** `generated/runtime/devices/avr128da32/interrupts.hpp` is present and contains
  `enum class InterruptId` and `kInterruptDescriptors`
- **AND** `generated/runtime/devices/avr128da32/clock_graph.hpp` is present and contains
  `enum class ClockNodeId` and `kClockDependencies`
- **AND** `generated/runtime/devices/avr128da32/peripheral_instances.hpp` is present and
  contains `enum class PeripheralId` and `kPeripheralInstances`
- **AND** `generated/runtime/devices/avr128da32/systick.hpp` is NOT emitted (AVR8 has no SysTick)

#### Scenario: AVR128DA32 startup artifact uses AVR8 vector table conventions

- **WHEN** the pipeline emits startup artifacts for an AVR128DA32 device
- **THEN** the startup file places a weak-symbol vector table in `.section .vectors`
  using C function pointer slots (`__vector_0` through `__vector_N`)
- **AND** it includes crt0 initialization: `.data` section copy from flash,
  `.bss` section zeroing, and a call to `main()`
- **AND** no ARM CMSIS vector table (`__Vectors[]` at address 0) is emitted
- **AND** no RISC-V `mtvec` initialization is emitted

#### Scenario: Consumer smoke test compiles AVR128DA32 runtime headers without error

- **WHEN** the consumer smoke test runs for an AVR128DA32 device
- **THEN** it compiles `interrupts.hpp`, `clock_graph.hpp`, and `peripheral_instances.hpp`
  using an AVR8 target triple (`avr-unknown-none`)
- **AND** it does not require any ARM-specific include paths or definitions

### Requirement: Published AVR-DA artifacts are covered by the artifact contract validator

The artifact contract checker MUST validate AVR-DA device artifacts using the same
required-paths and content checks applied to ARM and ESP32 devices.

#### Scenario: Artifact contract catches missing AVR interrupt header

- **WHEN** the artifact contract validator runs for an AVR128DA32 device
- **THEN** it verifies that `generated/runtime/devices/avr128da32/interrupts.hpp` is present
- **AND** it verifies the file contains `enum class InterruptId` and `kInterruptDescriptors`
- **AND** it reports a violation if either check fails

#### Scenario: Artifact contract catches missing AVR clock graph header

- **WHEN** the artifact contract validator runs for an AVR128DA32 device
- **THEN** it verifies that `generated/runtime/devices/avr128da32/clock_graph.hpp` is present
- **AND** it verifies the file contains `enum class ClockNodeId` and `kClockDependencies`
- **AND** it reports a violation if either check fails

#### Scenario: Artifact contract does not require systick header for AVR devices

- **WHEN** the artifact contract validator runs for an AVR128DA32 device
- **THEN** it does not flag the absence of `systick.hpp` as a violation
- **AND** it only enforces the systick requirement for Cortex-M family devices
