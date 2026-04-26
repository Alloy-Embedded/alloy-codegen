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

### Requirement: Publication SHALL Require Fully Typed Foundational Runtime Schemas

Publication SHALL fail for a foundational family when any runtime-owned backend schema still
depends on string parsing or handwritten register-field knowledge in Alloy.

#### Scenario: Foundational family remains partially textual
- **WHEN** validation detects that a foundational runtime-owned schema lacks typed field
  descriptors or executable typed operation targets
- **THEN** the family fails validation
- **AND** publication is blocked

### Requirement: Validation SHALL Verify Typed Binding Completeness

Validation SHALL verify that interrupt, DMA, clock, reset, selector, register, and field
bindings are complete and internally consistent for foundational families.

#### Scenario: Peripheral binding is incomplete
- **WHEN** a foundational peripheral instance is missing a required typed binding or field
  descriptor for its runtime schema
- **THEN** validation reports the missing domain as an error
- **AND** the family is not publishable

### Requirement: No String Glue in Foundational Runtime Headers
Validation SHALL fail for a foundational family when its runtime-facing headers still depend on
CSV payloads or textual signal fields as primary executable contract.

#### Scenario: Foundational family still emits CSV payload
- **WHEN** a foundational family emits CSV capability or interrupt payloads in a primary
  runtime struct
- **THEN** validation fails
- **AND** publish is blocked

### Requirement: No Text Parsing Required for Runtime Route Execution
Validation SHALL fail when a foundational route requirement or route operation still requires
text parsing to determine target or value semantics.

#### Scenario: Route operation only identifies its target textually
- **WHEN** a route operation lacks sufficient typed ids or typed refs
- **THEN** validation fails
- **AND** the family is not publishable

### Requirement: Admitted families SHALL pass a GPIO-semantic coverage gate

Every admitted MCU family SHALL emit a `driver_semantics/gpio.hpp` that
contains at least one `GpioSemanticTraits<PinId::...>` specialization with
`kPresent = true` once this change is applied to the family in question.
A repository-level CI gate SHALL fail PRs that admit a new family without
populated GPIO semantics, or that regress an existing family back to a
zero-specialization state.

The gate is rolled out per-family alongside the implementation phase that
populates that family. The gate becomes mandatory for every admitted family
once the final implementation phase lands. **As of `complete-rp2040-semantics`
Phase A, the gate is mandatory for RP2040 — the previous `xfail` marker
on the RP2040 case is removed and the family is expected to emit at
least one populated `GpioSemanticTraits` specialization.**

#### Scenario: GPIO coverage gate accepts a populated family

- **WHEN** a family that has been wired through the GPIO-semantic emitter
  emits its `gpio.hpp`
- **THEN** the file contains at least one specialization where
  `kPresent = true`
- **AND** the coverage gate passes for that family

#### Scenario: GPIO coverage gate blocks a regression

- **WHEN** a family that previously emitted populated `GpioSemanticTraits`
  specializations is changed in a way that drops all specializations
- **THEN** the coverage gate flags the family as regressed and the CI job
  fails

#### Scenario: RP2040 is included in the mandatory gate

- **WHEN** `tests/test_gpio_semantic_coverage.py` runs
- **THEN** the rp2040 device emits at least one `GpioSemanticTraits`
  specialization with `kPresent = true`
- **AND** the test does NOT carry an `xfail` marker for RP2040

### Requirement: I2C-bearing families MUST pass the I2C semantic coverage gate

I2C-bearing admitted families MUST emit at least one populated `I2cPeripheralTraits` specialization. Every admitted MCU family that ships at least one I2C / TWI controller in its admitted device set is covered by this gate; the gate fails the build when a family has zero `kPresent = true` specializations on its emitted `driver_semantics/i2c.hpp`.

The gate is rolled out per-family alongside the implementation phase
that populates that family.

#### Scenario: I2C coverage gate accepts a populated family

- **WHEN** a family that has been wired through the I2C-semantic
  emitter emits its `i2c.hpp`
- **THEN** the file contains at least one specialization where
  `kPresent = true`
- **AND** the coverage gate passes for that family

#### Scenario: I2C coverage gate ignores devices without I2C hardware

- **WHEN** an admitted family has no I2C / TWI controller on any
  device in its registered device list
- **THEN** the I2C coverage gate is treated as N/A for that family
  (it neither passes nor fails — the assertion does not run)

