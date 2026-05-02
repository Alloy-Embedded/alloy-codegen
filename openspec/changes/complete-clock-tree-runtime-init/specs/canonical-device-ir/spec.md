## ADDED Requirements

### Requirement: Canonical IR Clock Domains SHALL Carry Executable `select_register` Triples

The canonical IR SHALL carry a populated `select_register:
SelectRegister(reg, field, encoding)` triple on every multiplexed
`ClockDomain` (any domain whose `sources` field has more than one
entry), mapping every named source to its encoded value, so an
emitter can program the mux from this triple alone without
vendor-specific lookup tables.

#### Scenario: STM32 G0 USART1 mux carries a complete encoding

- **WHEN** alloy-codegen loads
  `data/devices/vendors/st/stm32g0/devices/stm32g071rb.yml`
- **THEN** `device.clock.domains[id == "usart1mult"].select_register`
  is `(reg="RCC.CCIPR", field="USART1SEL", encoding={"pclk": 0,
  "sysclk": 1, "hsi": 2, "lse": 3})`
- **AND** every entry in `sources` has a key in `encoding`

#### Scenario: Multiplexed domain missing encoding refuses to load

- **WHEN** a YAML carries a domain with `sources: [hsi, hse]` but
  `select_register.encoding` only maps `hsi: 0`
- **THEN** the loader raises `ConfigError` naming the domain id
  and the missing source

### Requirement: Canonical IR SHALL Carry FLASH Wait-State Tables Per Family

The canonical IR SHALL carry a typed `flash_wait_states:
tuple[FlashLatencyEntry, ...]` field on `Identity`, populated from
`family.yml`, for every device whose family requires FLASH
wait-state programming during clock setup (every Cortex-M family
with embedded FLASH).  Each entry SHALL carry `(min_hz: int,
max_hz: int, ws: int, encoding: int)` where `encoding` is the
value to write into the FLASH latency field.

#### Scenario: STM32 G0 family carries 0/1/2 WS table

- **WHEN** alloy-codegen loads any STM32 G0 device
- **THEN** `identity.flash_wait_states` contains entries
  covering 0 ≤ HCLK < 24 MHz (0 WS), 24 ≤ HCLK < 48 MHz (1 WS),
  48 ≤ HCLK ≤ 64 MHz (2 WS)
- **AND** each entry's `encoding` matches the value to write
  into `FLASH.ACR.LATENCY`

### Requirement: Canonical IR SHALL Validate PLL Coefficients At Load Time

The canonical IR loader SHALL validate the `pll_m/n/r/p/q`
coefficients of every PLL-driven entry in `device.clock.profiles`
against the IR's `clock.pll.*_range` bounds and SHALL refuse to
load any device whose YAML carries an out-of-range coefficient.

#### Scenario: Out-of-range PLL N coefficient refuses to load

- **WHEN** a YAML carries
  `clock.profiles[].sysclk_source: pll_hsi16` with `pll_n: 200`
  for a chip whose `clock.pll.n_range` is `[8, 86]`
- **THEN** the loader raises `ConfigError` naming the profile,
  the offending coefficient, and the violated range
