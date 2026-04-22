## ADDED Requirements

### Requirement: IR SHALL model XIP-mapped flash as a distinct memory kind

The canonical device IR SHALL represent externally-mapped XIP (Execute in Place) flash
regions with `kind = "xip-flash"` rather than `kind = "flash"`, preserving the distinction
between internal programmable flash and read-execute memory accessed via an XIP controller.

#### Scenario: RP2040 XIP window is captured as xip-flash kind

- **WHEN** the RP2040 device is normalized
- **THEN** the memory region at `0x10000000` carries `kind = "xip-flash"` and `access = "rx"`
- **AND** no `kind = "flash"` region exists for RP2040 (it has no internal flash)
- **AND** the SRAM regions at `0x20000000` continue to carry `kind = "sram"`

#### Scenario: Internal-flash devices are unaffected by the new kind

- **WHEN** an STM32 or SAME70 device is normalized
- **THEN** its flash region retains `kind = "flash"`
- **AND** no `xip-flash` region is emitted for those devices

#### Scenario: Consumers can distinguish programmable flash from XIP

- **WHEN** the linker script emitter processes a device IR
- **THEN** `kind = "xip-flash"` regions produce `BOOT2` and `XIP_MAIN` MEMORY entries
- **AND** `kind = "flash"` regions produce standard `FLASH` MEMORY entries

### Requirement: IR SHALL capture PIO as a present peripheral with an explicit stub schema

The canonical IR SHALL capture Programmable I/O (PIO) peripherals as present entries
with a named stub schema that explicitly signals the semantics are not yet fully modeled,
rather than omitting them entirely or mapping them to an unrelated existing schema.

#### Scenario: PIO0 and PIO1 are present in RP2040 canonical IR

- **WHEN** the RP2040 device is normalized
- **THEN** `PIO0` and `PIO1` appear in the peripheral instance list
- **AND** their `backend_schema_id` is `alloy.pio.rp2040-v1-stub`
- **AND** the capability manifest records `runtime-support:pio` as present

#### Scenario: PIO stub schema does not block admission

- **WHEN** the RP2040 vendor-admission gates are evaluated
- **THEN** the presence of PIO with a stub schema does not cause any CI gate to fail
- **AND** the stub schema is explicitly recognized as admission-valid until a full
  PIO semantic driver spec is approved

### Requirement: IR SHALL model dual-core topology with single-core-perspective annotation

The canonical device IR SHALL record the actual core topology of multi-core devices in
device metadata and SHALL carry an explicit provenance note documenting which core
perspective the emitted artifacts represent.

#### Scenario: RP2040 dual-core topology is recorded in IR

- **WHEN** the RP2040 device is normalized
- **THEN** device metadata records `core = "cortex-m0plus-dual"`
- **AND** a provenance note documents that emitted artifacts target core 0 only
- **AND** no facts about core 1 state, inter-core FIFOs, or spinlocks are emitted
  in this first cut

#### Scenario: Single-core annotation is visible in emitted startup

- **WHEN** `startup.cpp` is emitted for an RP2040 device
- **THEN** a generated comment explicitly states the single-core-perspective assumption
- **AND** no code to launch or synchronize core 1 is present in the emitted file
