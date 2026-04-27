## ADDED Requirements

### Requirement: Existing admitted device patches SHALL migrate to the template + diff format

Every device patch SHALL migrate to the
`peripheral-trait-template-library` inheritance chain plus the
`invert-patch-as-diff` baseline-diff shape (covering every
patch under `patches/<vendor>/<family>/devices/`).
Tier 2/3/4 fields (`uart_*`, `spi_*`, `i2c_*`,
`timer_*`, `pwm_*`, `adc_*`, `peripheral_max_clock_hz`) SHALL
move to `data/peripheral_traits/<class>/<ip_version>.toml`
where the template-library schemas accept them.  Source-derived
fields (peripherals, interrupts, base addresses, registers)
SHALL be removed from the patches when the SVD / ATDF / Zephyr
DTS baseline already supplies them.  Per-device patch LOC after
migration SHALL be at most 100 LOC per device for SVD-clean
families, at most 200 LOC for ATDF-only families (SAME70,
AVR-DA).

#### Scenario: stm32g071rb patch collapses by 80% after migration

- **WHEN** the migration wave for STM32G0 completes
- **THEN** `patches/st/stm32g0/devices/stm32g071rb.json` SHALL
  be at most 200 LOC (vs. ~1043 LOC pre-migration)
- **AND** the resolved IR after merging baseline + template +
  family-patch + device-patch SHALL be byte-identical to the
  pre-migration IR
- **AND** every emitted artifact for stm32g071rb SHALL match
  its post-migration golden fixture

#### Scenario: Total patch LOC drops by at least 60% after Wave 4

- **WHEN** Waves 1-4 are complete (pilots + STM32 + Espressif +
  iMXRT)
- **THEN** the union of `patches/**/*.json` LOC SHALL be at
  most 5,500 (down from ~14,129 pre-migration)

#### Scenario: ATDF-only families wait for the autogen prerequisite

- **WHEN** Wave 5 (SAME70 + AVR-DA) is attempted before
  `extend-autogen-to-atdf-and-mcuxpresso` ships
- **THEN** the wave SHALL be deferred — the diff invertor
  has no baseline to subtract against without an ATDF reader
- **AND** the documented dependency SHALL appear in the
  wave's tasks.md
