# validation-and-gates Specification

## Purpose
TBD - created by archiving change build-best-in-class-generator-core. Update Purpose after archive.
## Requirements
### Requirement: Publish proves deterministic runtime publication

Foundational publication MUST prove that identical inputs produce the same materialized runtime
tree.

#### Scenario: Repeated publish yields the same tree revision
- **WHEN** the same foundational family is published twice with the same sources and patches
- **THEN** the materialized publication tree revision is identical

### Requirement: Publish fails on missing semantic completeness

Foundational publication MUST fail when the runtime contract is semantically incomplete.

#### Scenario: Missing system-control coverage blocks publish
- **WHEN** a foundational family lacks required runtime interrupt, reset, clock, or power facts
- **THEN** publish fails

#### Scenario: Missing capability coverage blocks publish
- **WHEN** a runtime-supported foundational peripheral lacks formal capability coverage
- **THEN** publish fails

### Requirement: Consumer verification compiles the semantic moat

Consumer verification MUST compile the new runtime semantic layers directly.

#### Scenario: Consumer smoke covers system-control and capability contracts
- **WHEN** consumer verification runs for a foundational device
- **THEN** it compiles the typed runtime contracts for system-control and capability surfaces
- **AND** it does not substitute handwritten assumptions for those contracts

### Requirement: Validation SHALL Ban Semantic Strings In Runtime C++ Headers

Validation SHALL fail when a runtime-consumed generated C++ header exposes a semantic string
field.

#### Scenario: Runtime header still exposes textual schema or signal information
- **WHEN** validation detects fields such as `const char* schema_id`, `const char* signal`,
  `const char* kind`, `const char* package_name`, or similar semantic labels in a runtime
  header
- **THEN** validation fails
- **AND** publication is blocked

### Requirement: Foundational Publication SHALL Require Zero-String Runtime Headers

Foundational families SHALL not publish unless every runtime-consumed generated C++ artifact
obeys the zero-string rule.

#### Scenario: Foundational family still leaks semantic labels into C++
- **WHEN** a foundational family emits a runtime-facing C++ artifact with semantic strings
- **THEN** publish fails for that family
- **AND** no artifact publication record is materialized

### Requirement: Foundational Publish SHALL Fail Without Runtime-Lite Coverage

Foundational family publication SHALL fail when runtime-lite artifacts do not provide the data
needed for foundational runtime-owned drivers.

#### Scenario: Missing runtime-lite route lowering blocks publication

- **WHEN** a foundational family lacks runtime-lite route data for a published UART or GPIO path
- **THEN** the publish stage fails before publication

### Requirement: Foundational Publish SHALL Fail When Runtime-Lite Depends On Reflection Lookup

Foundational family publication SHALL fail when the emitted runtime-lite contract still requires
reflection-style family table lookup as the normal runtime usage model.

#### Scenario: Family emits only reflective connector graph

- **WHEN** the generated output exposes only reflection connector tables for a foundational
  runtime-owned use case
- **THEN** validation marks the runtime-lite contract incomplete
- **AND** publication is blocked

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

### Requirement: Expanded peripheral coverage follows the same validation standard

New peripheral families MUST not bypass the generator's semantic and validation moat.

#### Scenario: New runtime peripheral families require capability and verification coverage
- **WHEN** a new runtime peripheral family is added
- **THEN** publication requires formal capability coverage and consumer verification coverage
- **AND** the family is not considered complete with schema-only or parser-only support

