## ADDED Requirements

### Requirement: Linker script contract SHALL support XIP memory layout

The linker script emitter MUST produce valid output for devices with `xip-flash` memory
regions, emitting the BOOT2 stage placeholder section and XIP text region alongside the
standard SRAM regions.

#### Scenario: RP2040 device.ld contains BOOT2 and XIP sections

- **WHEN** `device.ld` is emitted for a device with a `xip-flash` memory region
- **THEN** the linker script MEMORY block contains a `BOOT2 (rx)` region of 256 bytes
  at the start of the XIP window
- **AND** the linker script MEMORY block contains an `XIP_MAIN (rx)` region for the
  remaining XIP-mapped flash space
- **AND** the linker script defines `__boot2_start`, `__boot2_end`, `__boot2_size`,
  `__xip_text_start`, and `__xip_text_end` symbols
- **AND** the standard SRAM-based `.data`, `.bss`, and `.stack` sections are also present

#### Scenario: Standard flash devices produce unmodified linker scripts

- **WHEN** `device.ld` is emitted for a device with a `flash` (not `xip-flash`) memory region
- **THEN** no `BOOT2` section is present
- **AND** the linker script structure is identical to existing foundational devices

### Requirement: Startup artifact contract SHALL accommodate XIP flash initialization

The emitted `startup.cpp` for XIP-booting devices MUST include a flash initialization
step and a boot2 placeholder before the standard data-copy and BSS-zero loop.

#### Scenario: RP2040 startup.cpp contains XIP init and boot2 placeholder

- **WHEN** `startup.cpp` is emitted for a device with a `xip-flash` memory region
- **THEN** the emitted file includes a `.boot2` section placeholder (256-byte weak symbol)
- **AND** it calls `xip_init()` before the `.data` copy loop
- **AND** it contains a generated comment noting that the boot2 placeholder must be
  replaced with a flash-specific second-stage bootloader for hardware execution
- **AND** the standard `.data` copy, `.bss` zero, and `main()` call are present

#### Scenario: Non-XIP startup is unaffected

- **WHEN** `startup.cpp` is emitted for a device without a `xip-flash` memory region
- **THEN** no `xip_init()` call or `.boot2` placeholder is present
- **AND** the standard startup sequence is emitted unchanged

### Requirement: PIO driver semantics stub SHALL be emitted and tracked

Devices with PIO peripherals SHALL have a `driver_semantics/pio.hpp` stub emitted and the
`runtime-support:pio` capability SHALL be tracked in the capability regression gate.

#### Scenario: RP2040 emits pio.hpp as an explicit stub

- **WHEN** `driver_semantics/pio.hpp` is emitted for an RP2040 device
- **THEN** the file contains a `PioSemanticTraits<Id>` template with `kPresent = false`
- **AND** all register and field references are `kInvalidRegisterRef` / `kInvalidFieldRef`
- **AND** `kPioSemanticPeripherals` is an array of size 0

#### Scenario: runtime-support:pio is tracked across publication cycles

- **WHEN** the RP2040 device is published and a subsequent publication cycle runs
- **THEN** the presence of `runtime-support:pio` in the capability manifest is checked
  for regression
- **AND** a publication that drops `runtime-support:pio` from RP2040 is blocked
