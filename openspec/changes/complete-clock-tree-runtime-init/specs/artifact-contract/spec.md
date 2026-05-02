## ADDED Requirements

### Requirement: `runtime_init.c` SHALL Carry An Executable Body For Every Published Profile

The published `runtime_init.c` SHALL define one fully-implemented
`alloy_clock_enter_<profile_id>(void)` function per entry in
`device.clock.profiles` for every device admitted to
alloy-devices, and stub forward-declarations alone SHALL NOT
satisfy this requirement.

#### Scenario: Published runtime_init for STM32 G071RB carries every profile body

- **WHEN** alloy-codegen publishes
  `out/st/stm32g0/stm32g071rb/runtime_init.c`
- **THEN** the file contains a definition (not just declaration)
  of `alloy_clock_enter_default_hsi16_16mhz` and
  `alloy_clock_enter_pll_hsi16_64mhz`
- **AND** each definition's body contains at least one register
  write to RCC, FLASH, or PWR

### Requirement: `runtime_init.c` SHALL Stay Zero-String

The bodies emitted by this proposal SHALL NOT introduce any
semantic `const char*` field, label, or log message.  Diagnostic
breakpoints (`__BKPT(N)`) and integer codes are acceptable.

#### Scenario: Zero-string gate passes after profile bodies land

- **WHEN** the pre-publication zero-string gate scans
  `out/<vendor>/<family>/<chip>/runtime_init.c` after this
  proposal's emitter changes
- **THEN** the gate finds no semantic string literal in any
  `alloy_clock_enter_*` body
