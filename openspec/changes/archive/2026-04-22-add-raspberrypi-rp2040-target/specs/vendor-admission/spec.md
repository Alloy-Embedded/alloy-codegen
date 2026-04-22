## MODIFIED Requirements

### Requirement: Foundational vendor set is explicit

The admitted foundational vendor/family set MUST be explicitly documented.

#### Scenario: Foundational vendors are listed

- **WHEN** maintainers review current admission status
- **THEN** the admitted vendor/family set is explicit and includes: ST/stm32g0, ST/stm32f4,
  Microchip/same70, NXP/imxrt1060, and Raspberry Pi/rp2040
- **AND** the source pattern used by each foundational family is documented
- **AND** the ISA family (Cortex-M0+, Cortex-M4F, Cortex-M7F) is documented alongside
  each entry
- **AND** multi-core devices document whether support is single-core-perspective or
  full multi-core aware

## ADDED Requirements

### Requirement: Raspberry Pi RP2040 is admitted as a Cortex-M0+ target

The pipeline MUST support the Raspberry Pi RP2040 as a first-class vendor target using
the pico-sdk SVD as canonical source and `alloy.pinmux.rp2040-funcsel-v1` as pinmux schema.

#### Scenario: RP2040 is a supported bootstrap family

- **WHEN** the pipeline runs for vendor `raspberrypi`, family `rp2040`
- **THEN** it fetches device data from `github.com/raspberrypi/pico-sdk`
- **AND** it produces a valid `CanonicalDeviceIR` using Cortex-M0+ normalization paths
- **AND** it emits the full standard runtime C++ artifact set passing all contract gates

#### Scenario: RP2040 dual-core is documented as single-core-perspective

- **WHEN** the RP2040 device IR is normalized
- **THEN** `core` is recorded as `"cortex-m0plus-dual"` in device metadata
- **AND** the emitted `startup.cpp` contains an explicit generated comment stating that
  core 1 is not started in this first cut
- **AND** no CI gate fails due to the dual-core topology being partially modeled

#### Scenario: Raspberry Pi vendor is admitted in CI gate

- **WHEN** the CI admission check scans `patches/`
- **THEN** `patches/raspberrypi/` is recognized as admitted and does not fail the build

### Requirement: FUNCSEL pinmux routing is modeled as a named backend schema

The RP2040's FUNCSEL pin routing MUST be modeled as a distinct backend schema rather than
as a transparent extension of the ARM alternate-function model.

#### Scenario: FUNCSEL signals carry a distinguishing schema ID

- **WHEN** an RP2040 peripheral instance is present in canonical IR
- **THEN** its `backend_schema_id` is `alloy.pinmux.rp2040-funcsel-v1`
- **AND** pin signal `af_number` values represent FUNCSEL indices (0–9) from the RP2040
  datasheet GPIO function table
- **AND** consumers that check `backend_schema_id` before interpreting `af_number` see a
  distinct identifier and apply FUNCSEL routing logic instead of ARM AF logic

#### Scenario: Existing ARM backends are unaffected

- **WHEN** an ST or NXP peripheral instance is present in canonical IR
- **THEN** its `backend_schema_id` remains `alloy.pinmux.stm32-af-v1` or
  `alloy.pinmux.imxrt-iomuxc-v1` respectively
- **AND** no FUNCSEL logic is applied to those pin signal entries
