## MODIFIED Requirements

### Requirement: Foundational vendor set is explicit

The admitted foundational vendor/family set MUST be explicitly documented.

#### Scenario: Foundational vendors are listed

- **WHEN** maintainers review current admission status
- **THEN** the admitted vendor/family set is explicit and includes: ST/stm32g0, ST/stm32f4,
  Microchip/same70, Microchip/avr-da, NXP/imxrt1060, and Espressif/esp32c3
- **AND** the source pattern used by each foundational family is documented
- **AND** the ISA family (Cortex-M, RISC-V, Xtensa, AVR8) and memory model
  (unified vs Harvard) are documented alongside each entry

## ADDED Requirements

### Requirement: Microchip AVR-DA family is admitted as an 8-bit Harvard target

The pipeline MUST support the Microchip AVR-DA family (`AVR128DA32` as bootstrap device)
as the first 8-bit Harvard architecture target.

#### Scenario: AVR128DA32 is a supported bootstrap device

- **WHEN** the pipeline runs for vendor `microchip`, family `avr-da`
- **THEN** it fetches device data from the Microchip AVR-Dx DFP pack via
  `packs.download.microchip.com`
- **AND** it produces a valid `CanonicalDeviceIR` with Harvard address space annotations
  on memory regions
- **AND** it emits runtime C++ headers that pass the artifact contract checks

#### Scenario: AVR-DA is recognized as an admitted Microchip family in CI

- **WHEN** the CI admission check scans `patches/`
- **THEN** `patches/microchip/avr-da/` is recognized as admitted and does not fail the build
- **AND** `patches/microchip/same70/` continues to pass unchanged

### Requirement: AVR PORTMUX routing is modeled as a documented vendor-specific backend schema

AVR-DA's `PORTMUX`-based alternate pin assignments MUST be modeled as a named backend schema
distinct from ARM alternate-function and ESP32 IO Matrix schemas.

#### Scenario: PORTMUX signals carry a distinguishing schema ID

- **WHEN** a Microchip AVR-DA peripheral instance is present in canonical IR
- **THEN** its `backend_schema_id` is `alloy.pinmux.avr-portmux-v1`
- **AND** pin signal `af_number` values encode the PORTMUX selection index:
  `0` for the default pin assignment, `1` for the first alternate, `2` for the second
- **AND** consumers that check `backend_schema_id` apply PORTMUX logic
  instead of ARM AF or ESP32 IO Matrix logic

#### Scenario: Existing ARM and ESP32 backends are unaffected

- **WHEN** an ST, NXP, or Espressif peripheral instance is processed
- **THEN** its `backend_schema_id` remains unchanged
- **AND** no PORTMUX logic is applied to non-AVR pin signal entries
