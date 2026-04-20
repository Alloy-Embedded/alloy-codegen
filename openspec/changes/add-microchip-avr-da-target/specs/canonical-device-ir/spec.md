## ADDED Requirements

### Requirement: Canonical IR models Harvard address space separation

For Harvard architecture devices, `CanonicalDeviceIR` MUST annotate each memory region with
its address space so that overlapping base addresses across separate spaces are not ambiguous.

#### Scenario: AVR flash and EEPROM regions carry distinct address spaces

- **WHEN** canonical IR is built for an AVR-DA device
- **THEN** the flash memory region carries `address_space: "prog"`
- **AND** the SRAM memory region carries `address_space: "data"`
- **AND** the EEPROM memory region carries `address_space: "eeprom"`
- **AND** no two memory regions with the same `base_address` value appear without distinct
  `address_space` values

#### Scenario: Unified-address-space devices omit the address space field

- **WHEN** canonical IR is built for an ARM Cortex-M, RISC-V, or Xtensa device
- **THEN** all memory regions have `address_space` absent or null
- **AND** no behavioral change occurs in normalization, emission, or validation for those devices

#### Scenario: Schema version reflects the Harvard extension

- **WHEN** any consumer reads a serialized `CanonicalDeviceIR`
- **THEN** the schema version is `1.2.0` or higher if `address_space` may be present
- **AND** consumers that only handle `address_space: null` can ignore the field without error

### Requirement: Canonical IR recognizes EEPROM as a distinct memory kind

The pipeline MUST represent EEPROM memory as a first-class memory kind with no startup copy
roles, distinct from flash (copy-source), SRAM (copy-target), and retained memory.

#### Scenario: EEPROM region has no startup roles

- **WHEN** canonical IR is built for a device with an EEPROM region
- **THEN** the EEPROM memory region has zero startup roles
- **AND** it is not designated `nonvolatile`, `copy-source`, `volatile-target`, or
  `copy-target` — none of those roles apply to EEPROM in startup context
- **AND** the startup emitter does not emit copy or zeroing code for the EEPROM region

#### Scenario: EEPROM kind is distinct from flash and SRAM kinds

- **WHEN** a memory region with kind `"eeprom"` is present in canonical IR
- **THEN** it is correctly classified as EEPROM in normalization output
- **AND** it does not inherit `vector-source`, `copy-source`, `stack-target`, or any
  other role that would cause incorrect startup behavior

### Requirement: Canonical IR supports the AVR8 system-vector topology

The pipeline MUST produce correct interrupt and vector-slot metadata for 8-bit AVR devices,
where the vector table starts directly with device-specific handlers (no ARM system exceptions
prefix) and the reset handler occupies slot 0.

#### Scenario: AVR8 devices receive a reset-only vector baseline

- **WHEN** canonical IR is built for an AVR-DA device with core `"avr8"`
- **THEN** vector slot 0 is reserved for the reset handler (`__vector_0`)
- **AND** no ARM system exception slots (NMI_Handler, HardFault_Handler, SysTick_Handler,
  etc.) appear in the interrupt binding list
- **AND** device interrupt bindings start at vector slot 1 and are numbered by their
  ATDF interrupt line value

#### Scenario: Unknown core fails explicitly rather than silently defaulting to ARM

- **WHEN** a device with an unrecognized `core` string is processed
- **THEN** the pipeline raises an explicit error identifying the unknown core
- **AND** it does not silently fall back to a Cortex-M4 baseline
