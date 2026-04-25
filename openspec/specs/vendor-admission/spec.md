# vendor-admission Specification

## Purpose

Define the policy that governs when a vendor or family is admitted into the supported
multi-vendor publication set.
## Requirements
### Requirement: Foundational vendor set is explicit

The admitted foundational vendor/family set MUST be explicitly documented.

#### Scenario: Foundational vendors are listed

- **WHEN** maintainers review current admission status
- **THEN** the admitted vendor/family set is explicit and includes: ST/stm32g0, ST/stm32f4,
  Microchip/same70, Microchip/avr-da, NXP/imxrt1060, Espressif/esp32c3, Espressif/esp32s3,
  and Espressif/esp32
- **AND** the source pattern used by each foundational family is documented
- **AND** the ISA family (Cortex-M, RISC-V, Xtensa LX6, Xtensa LX7, AVR8) and memory
  model (unified vs Harvard) are documented alongside each entry
- **AND** the multi-core posture (single-core vs dual-core control plane) is
  documented for every multi-core family

### Requirement: New vendor admission is gated

A new vendor beyond the admitted foundational set MUST NOT enter active implementation until
readiness gates are closed and an admission proposal exists.

#### Scenario: Admission checks bootstrap readiness

- **WHEN** a new vendor or family is considered publishable
- **THEN** Gates T7, T8, and T9 are closed
- **AND** no foundational family requires final-stage emitter or publish exceptions
- **AND** a completed vendor-admission proposal exists in `openspec/changes/`

### Requirement: CI enforces the admitted vendor set

The CI workflow MUST fail if unadmitted vendor directories appear in `patches/`.

#### Scenario: Unadmitted vendor directories are blocked

- **WHEN** the quality workflow scans `patches/`
- **THEN** any vendor directory outside the admitted set fails the build

### Requirement: Vendor admission proposals are complete

A proposal to admit a new vendor MUST answer the bootstrap and source questions needed to make
the vendor publishable and maintainable.

#### Scenario: Admission proposal covers the full checklist

- **WHEN** a new vendor-admission proposal is reviewed
- **THEN** it identifies vendor key, bootstrap family, source pattern, bootstrap devices,
  fixture plan, licensing notes, and gate plan

### Requirement: Additional families from admitted vendors are still gated

Admitted vendors MUST satisfy bootstrap stability and proposal requirements before adding new
families.

#### Scenario: Existing vendor expands to a new family

- **WHEN** an already admitted vendor adds another family
- **THEN** the bootstrap family has completed at least two stable publication cycles
- **AND** no outstanding CI exceptions exist for that vendor
- **AND** a proposal exists naming the new family, its devices, and its fixture plan

### Requirement: New vendor admission requires semantic and provenance readiness

Vendor/family admission MUST not be judged only by parser success or low-level artifact emission.

#### Scenario: Admission checks semantic readiness

- **WHEN** a new vendor or family is considered publishable
- **THEN** admission evaluates system-control coverage, capability coverage, and provenance quality
- **AND** the family is not considered foundational-ready if those remain heuristic or opaque

### Requirement: Vendor Admission SHALL Require Zero-String Runtime Reuse

A new family or vendor SHALL only be admitted when it reuses or extends the fully typed
zero-string runtime contract.

#### Scenario: New family reuses existing typed schemas
- **WHEN** a new family maps onto existing fully typed runtime schemas
- **THEN** vendor admission succeeds without requiring semantic string fields in runtime C++

#### Scenario: New family needs semantic labels in runtime C++
- **WHEN** a candidate family can only be represented by adding schema names, signal names,
  route kinds, or similar semantic strings to runtime-facing headers
- **THEN** vendor admission fails until those semantics are modeled as typed ids or refs

### Requirement: Vendor Admission SHALL Depend On Runtime-Lite Reuse

A new vendor or family SHALL NOT be considered admission-ready unless it reuses the runtime-lite
contract expected by foundational drivers, without requiring a new reflection-table hot path in
`alloy`.

#### Scenario: New family needs custom table-walk runtime glue

- **WHEN** a new family can only be consumed through handwritten reflection-table lookup in the
  runtime
- **THEN** vendor admission fails until codegen emits a compatible runtime-lite contract

### Requirement: Vendor breadth is staged by quality, not just count

Coverage expansion MUST prioritize quality-complete vendor support over raw vendor-count growth.

#### Scenario: New coverage waves respect admission quality
- **WHEN** a peripheral class is expanded to additional vendors
- **THEN** each admitted vendor/family meets the same runtime-contract and validation expectations
- **AND** "partial but opaque" coverage is not treated as equivalent to complete support

### Requirement: Vendor Admission SHALL Depend on Typed Schema Reuse

Admission of a new family or vendor SHALL require either reuse of an already published typed
runtime backend schema or the introduction of a new localized schema contract that avoids
family-name parsing in Alloy.

#### Scenario: New family reuses an existing runtime schema
- **WHEN** a candidate family maps to already published runtime backend schemas
- **THEN** vendor admission succeeds without requiring Alloy runtime changes outside schema
  dispatch tables

#### Scenario: New family requires family-specific runtime parsing
- **WHEN** a candidate family can only be consumed by adding family-name checks or string
  parsing in Alloy
- **THEN** vendor admission fails until the contract is expressed as typed schema descriptors

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

### Requirement: Vendor Admission Requires Typed Runtime Contract Reuse
New foundational-family admission SHALL require reuse of the typed runtime-ref domains and
typed runtime header contract, unless a localized new schema is explicitly added and validated.

#### Scenario: New family attempts to publish with string glue
- **WHEN** a new family or vendor publishes foundational runtime artifacts
- **THEN** vendor admission fails if it depends on raw signal strings or CSV payloads as
  primary runtime contract

### Requirement: Espressif ESP32 families are admitted as non-ARM targets

The pipeline MUST support Espressif ESP32 families as first-class non-ARM vendor targets, starting
with ESP32-C3 (RISC-V RV32IMC) as the bootstrap family.

#### Scenario: ESP32-C3 is a supported bootstrap family

- **WHEN** the pipeline runs for vendor `espressif`, family `esp32c3`
- **THEN** it fetches device data from the Espressif SVD repository
- **AND** it produces a valid `CanonicalDeviceIR` without ARM-specific fallbacks
- **AND** it emits runtime C++ headers that pass the artifact contract checks

#### Scenario: ESP32-S3 is admitted after ESP32-C3 stabilizes

- **WHEN** the ESP32-C3 bootstrap family has completed at least one stable publication cycle
- **THEN** `esp32s3` (Xtensa LX7) may be added to the registry
- **AND** a proposal exists naming the new family, its Xtensa-specific requirements, and its
  fixture plan
- **AND** the proposal documents whether the first admitted model is single-core-perspective
  only or full multi-core aware

#### Scenario: Espressif vendor is admitted in CI gate

- **WHEN** the CI admission check scans `patches/`
- **THEN** `patches/espressif/` is recognized as admitted and does not fail the build

### Requirement: IO Matrix routing is modeled as a documented vendor-specific backend schema

ESP32's fully-programmable GPIO IO Matrix MUST be modeled as a named backend schema rather than
as an extension of the ARM alternate-function model.

#### Scenario: IO Matrix signals carry a distinguishing schema ID

- **WHEN** an Espressif peripheral instance is present in canonical IR
- **THEN** its `backend_schema_id` is `alloy.pinmux.espressif-iomatrix-v1`
- **AND** pin signal `af_number` values represent IO Matrix signal indices from
  Espressif's `gpio_sig_map.h`
- **AND** consumers that check `backend_schema_id` before interpreting `af_number` see a
  distinct identifier and apply IO Matrix routing logic instead of ARM AF logic

#### Scenario: IO Matrix supplementary data is explicitly admitted

- **WHEN** Espressif IO Matrix routing is used in normalization
- **THEN** the admitted source set includes the supplementary routing data source
- **AND** maintainers can identify its upstream repository, revision, and license

#### Scenario: Existing ARM backends are unaffected

- **WHEN** an ST or NXP peripheral instance is present in canonical IR
- **THEN** its `backend_schema_id` remains `alloy.pinmux.stm32-af-v1` or
  `alloy.pinmux.imxrt-iomuxc-v1` respectively
- **AND** no IO Matrix logic is applied to ARM pin signal entries

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

### Requirement: Espressif ESP32 classic family is admitted as a dual-core LX6 target

The pipeline MUST support the Espressif ESP32 classic family (dual-core Xtensa LX6) as a
first-class target, sharing the existing `espressif-svd` source adapter and the
dual-core Xtensa runtime contract.

#### Scenario: ESP32 classic is a supported family

- **WHEN** the pipeline runs for vendor `espressif`, family `esp32`
- **THEN** it fetches `esp32.svd` via the existing `espressif-svd` adapter without
  requiring a new source adapter
- **AND** it produces a valid `CanonicalDeviceIR` for both `esp32` (QFN48) and
  `esp32-wroom32` (module) device variants
- **AND** the canonical IR has `core: "xtensa-lx6"` and is recognized by
  `runtime_xtensa_startup.py::_is_xtensa_device`
- **AND** it emits runtime C++ headers that pass the architecture-scoped artifact contract

#### Scenario: ESP32 classic admits two packages sharing one family catalog

- **WHEN** the bootstrap registers `espressif/esp32`
- **THEN** the family catalog `patches/espressif/esp32/family.json` is shared by every
  device variant
- **AND** at least two device patches exist: `esp32.json` for QFN48 and
  `esp32-wroom32.json` for the WROOM-32 module
- **AND** the WROOM-32 patch flags GPIO6–GPIO11 as reserved for the on-module SPI flash
  via the standard `package_pads` mechanism
- **AND** ESP32-PICO-D4 and ESP32-WROVER are explicitly NOT admitted in this change

#### Scenario: ESP32 classic Wi-Fi/BT/Ethernet/SDMMC are out of scope

- **WHEN** the family patch declares its admitted peripherals
- **THEN** the allowlist covers UART0/1/2, SPI2/3, I2C0/1, TIMG0/1, GPIO, LEDC, RMT,
  ADC1, and DPORT (system control)
- **AND** Wi-Fi, Bluetooth, Ethernet MAC, SDMMC host, DAC, AES/SHA accelerators, ADC2
  (which shares hardware with Wi-Fi), and the ULP coprocessor are intentionally excluded
- **AND** the design document lists each excluded subsystem with its reason

#### Scenario: ESP32 classic publishes alongside the existing Espressif families

- **WHEN** the Bootstrap Family CI run on `main` is green
- **THEN** the chained Publish workflow runs a `vendor=espressif, family=esp32` matrix entry
- **AND** the publication lands under `alloy-devices/espressif/esp32/` without erasing
  `esp32c3/` or `esp32s3/` siblings
- **AND** the consumer smoke compiles the emitted runtime headers for both `esp32` and
  `esp32-wroom32` device variants

