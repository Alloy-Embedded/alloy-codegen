## ADDED Requirements

### Requirement: Publication fails when capability manifest is incomplete for runtime peripherals

Foundational publication MUST fail when a runtime-supported peripheral is present in the
device IR but has no capability facts documented in the manifest.

#### Scenario: Missing capability entry blocks publish for known peripheral class

- **WHEN** a foundational device has a peripheral of class `uart`, `spi`, `i2c`, `adc`,
  `dma`, `timer`, or `pwm` in its canonical IR
- **THEN** publish fails if that peripheral has zero `CapabilityDescriptor` entries
- **AND** the failure message names the peripheral and the required minimum capability IDs

#### Scenario: Capability manifest completeness is a CI gate, not a warning

- **WHEN** the quality CI workflow runs for a foundational family
- **THEN** a missing or empty `capabilities.json` fails the workflow
- **AND** an incomplete capability entry (e.g., `kMaxBaudRate` absent for a UART)
  emits a warning but does not block publish at initial rollout

### Requirement: Consumer verification compiles and links the full generated artifact set

Consumer verification MUST demonstrate that the complete generated artifact set —
linker script, startup, runtime headers, connector tables, clock config, capability
manifest, and interrupt stubs — compiles and links into a valid object file.

#### Scenario: Smoke build links against the generated linker script

- **WHEN** consumer verification runs for a foundational device
- **THEN** it validates or links a smoke object against `generated/devices/<device>/device.ld`
- **AND** the link succeeds with correct section placement (`.text` in flash,
  `.data` load-from-flash, `.bss` zeroed, `__stack_top` defined)

#### Scenario: Smoke build compiles the full runtime header set

- **WHEN** consumer verification runs for a foundational device
- **THEN** it compiles a single translation unit that includes all runtime headers:
  `peripheral_instances.hpp`, `interrupts.hpp`, `clock_graph.hpp`, `connectors.hpp`,
  `clock_config.hpp`, `capabilities.hpp`, and `interrupt_stubs.hpp`
- **AND** it does not require any hand-written header or macro to bridge the gap
  between generated headers

#### Scenario: Smoke build includes at least one capability `static_assert`

- **WHEN** consumer verification runs for a foundational device
- **THEN** the smoke translation unit contains at least one
  `static_assert(alloy::<device>::<peripheral>::kHas<Feature>)` check
- **AND** that assertion passes for all currently published devices

### Requirement: Cross-vendor capability parity is machine-checkable

The pipeline MUST be able to compare capability manifests across two devices and report
structural differences, enabling portability analysis and cross-vendor regression detection.

#### Scenario: `alloy diff` reports capability delta between two devices

- **WHEN** the `alloy diff --from <device1> --to <device2>` command runs for two
  devices with the same peripheral class
- **THEN** it outputs a table of capability changes: added, removed, and modified
  capability entries
- **AND** the output cites the patch or SVD source for each changed entry

#### Scenario: CI detects capability regression across publications

- **WHEN** a new publication for a previously admitted device has fewer capability
  entries than the prior publication
- **THEN** the CI workflow reports a capability regression and fails
- **AND** it identifies which capability IDs were removed and which device is affected
