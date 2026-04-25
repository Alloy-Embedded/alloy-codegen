## MODIFIED Requirements

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

## ADDED Requirements

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
