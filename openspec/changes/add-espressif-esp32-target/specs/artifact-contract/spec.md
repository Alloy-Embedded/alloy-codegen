## ADDED Requirements

### Requirement: ESP32 families emit runtime headers matching the standard contract shape

Espressif ESP32 devices MUST emit the same runtime header set as ARM foundational devices,
with the exception of artifacts that are explicitly scoped to a different architecture family.

#### Scenario: ESP32-C3 runtime device headers are present and valid

- **WHEN** the pipeline emits artifacts for an ESP32-C3 device
- **THEN** `generated/runtime/devices/esp32c3/interrupts.hpp` is present and contains
  `enum class InterruptId` and `kInterruptDescriptors`
- **AND** `generated/runtime/devices/esp32c3/clock_graph.hpp` is present and contains
  `enum class ClockNodeId` and `kClockDependencies`
- **AND** `generated/runtime/devices/esp32c3/peripheral_instances.hpp` is present and
  contains `enum class PeripheralId` and `kPeripheralInstances`
- **AND** `generated/runtime/devices/esp32c3/systick.hpp` is NOT emitted (RISC-V has no SysTick)
- **AND** the artifact contract treats that omission as valid because `systick.hpp`
  is Cortex-M-scoped

#### Scenario: ESP32-C3 startup artifact uses RISC-V conventions

- **WHEN** the pipeline emits startup artifacts for an ESP32-C3 device
- **THEN** the startup file uses RISC-V reset vector conventions (`mtvec`, BSS clear, `main()`)
- **AND** no ARM CMSIS vector table (`__Vectors[]` at address 0) is emitted

#### Scenario: ESP32-S3 runtime device headers are present and valid

- **WHEN** the pipeline emits artifacts for an ESP32-S3 device
- **THEN** `generated/runtime/devices/esp32s3/interrupts.hpp` is present with Xtensa interrupt IDs
- **AND** `generated/runtime/devices/esp32s3/clock_graph.hpp` is present with ESP32-S3 clock nodes
- **AND** the startup file uses Xtensa reset vector conventions (`VECBASE`, level handlers)
- **AND** `generated/runtime/devices/esp32s3/systick.hpp` is NOT emitted
- **AND** the artifact contract treats that omission as valid because `systick.hpp`
  is Cortex-M-scoped

#### Scenario: Consumer smoke test compiles ESP32 runtime headers without error

- **WHEN** the consumer smoke test runs for an ESP32-C3 device
- **THEN** it compiles `interrupts.hpp`, `clock_graph.hpp`, and `peripheral_instances.hpp`
  without errors
- **AND** it does not require any ARM-specific include paths or definitions

### Requirement: Published Espressif artifacts are covered by the artifact contract validator

The artifact contract checker MUST validate ESP32 device artifacts using the same required-paths
and content checks applied to ARM devices.

#### Scenario: Artifact contract catches missing ESP32 interrupt header

- **WHEN** the artifact contract validator runs for an ESP32-C3 device
- **THEN** it verifies that `generated/runtime/devices/esp32c3/interrupts.hpp` is present
- **AND** it verifies the file contains `enum class InterruptId` and `kInterruptDescriptors`
- **AND** it reports a violation if either check fails

### Requirement: Supplementary non-SVD sources are part of the validated contract

When a published family depends on supplementary non-SVD sources, the contract MUST record
their provenance and treat them as part of the supported input set.

#### Scenario: IO Matrix publication records supplementary-source provenance

- **WHEN** the pipeline publishes artifacts for an Espressif family that uses `gpio_sig_map.h`
- **THEN** the publication metadata records that supplementary source alongside the SVD source
- **AND** emitted IO Matrix facts can be traced back to that supplementary source
- **AND** the absence of that source metadata is a contract violation

#### Scenario: Artifact contract catches missing ESP32 clock graph header

- **WHEN** the artifact contract validator runs for an ESP32-C3 device
- **THEN** it verifies that `generated/runtime/devices/esp32c3/clock_graph.hpp` is present
- **AND** it verifies the file contains `enum class ClockNodeId` and `kClockDependencies`
- **AND** it reports a violation if either check fails
