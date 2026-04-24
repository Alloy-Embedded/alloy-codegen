# Project Context

## Purpose
`alloy-codegen` is the source-of-truth toolchain for transforming messy vendor hardware
descriptions into a clean, validated, reproducible device model and then emitting versioned
artifacts for the Alloy ecosystem.

Its job is not only to generate C++ headers. It must own the full pipeline:
- acquiring raw source data
- applying reproducible corrections
- normalizing vendors into a canonical intermediate representation
- validating semantic consistency
- emitting machine-consumable metadata and generated code
- publishing artifacts to `alloy-devices`

The long-term goal is to make Alloy device support deterministic, auditable, and scalable
without embedding vendor quirks directly into handwritten HAL code or final codegen
templates.

## Tech Stack
- Python 3.12+ for CLI, pipeline orchestration, validation, and emitters
- Structured schemas for canonical data and manifests (JSON and/or YAML)
- Template-based code emission for generated C++ output
- GitHub Actions for CI validation and artifact publication

## Project Conventions

### Code Style
- Prefer explicit, typed Python over dynamic convenience code
- Keep vendor-specific logic isolated in adapters and normalizers
- Treat reproducibility as a product feature: same inputs plus same patches must produce
  byte-for-byte stable normalized data and artifacts unless versioned schema changes
- Avoid “magic fixups” inside emitters; corrections must live in patch or normalization
  layers with provenance

### Architecture Patterns
- Stage-separated pipeline: `fetch -> patch -> normalize -> validate -> emit -> publish`
- Canonical intermediate representation (IR) is the heart of the system
- Emitters are downstream consumers of IR; they do not own business rules
- Validation is multi-layered: schema validation, semantic validation, and artifact
  validation
- Vendor support grows by implementing adapters into the same IR, not by branching the
  whole architecture per vendor

### Testing Strategy
- Each pipeline stage must be testable in isolation
- Synthetic fixtures are preferred for deterministic unit tests
- Golden tests are required for normalized IR and emitted artifacts
- CI must block progression when a maturity gate fails
- New vendor/family support must ship with regression fixtures before expanding coverage

### Git Workflow
- Architectural or contract changes require OpenSpec proposals first
- Breaking changes to schemas, manifests, artifact layout, or publication flow require a
  change proposal
- Implementation follows approved phase gates; do not skip gates to add breadth prematurely

## Domain Context
The raw hardware ecosystem is inconsistent. SVDs are incomplete or wrong, vendor tool
exports encode valuable data in incompatible formats, and device support usually depends on
more than register blocks alone. The codegen system therefore must model:
- IP blocks and their versions
- devices and packages
- pins and alternate-function connectivity
- interrupts
- DMA request routing
- clock/reset enable data
- provenance for every normalized field

The system is inspired by ideas seen in projects like `modm-data`, `modm-devices`,
`stm32-data`, `chiptool`, and `svdtools`, but it must remain Alloy-owned in architecture,
schemas, and tooling.

## Important Constraints
- Do not depend on third-party generated outputs as the foundation of the product
- Keep licensing and provenance explicit for upstream data sources and derived artifacts
- Avoid baking vendor quirks into final emitted C++ templates
- A phase may only advance after its quality gate passes
- Multi-vendor expansion is forbidden until the single-family path is reproducible and
  semantically validated

## External Dependencies
- Upstream vendor/device descriptions such as SVD and other vendor-provided metadata
- Git for fetching sources and publishing artifacts
- GitHub Actions for CI execution and publication orchestration

## Admitted Foundational Families
The foundational vendor/family set is deliberately explicit.  A family is
"admitted" only after the full fetch → normalize → validate → emit → publish
pipeline passes end-to-end with regression fixtures in place.

| Vendor / Family      | Bootstrap device(s)                     | ISA           | Memory model | Upstream source(s)                          | License     |
|----------------------|-----------------------------------------|---------------|--------------|---------------------------------------------|-------------|
| `st/stm32g0`         | `stm32g030f6, stm32g071rb, stm32g0b1re` | Cortex-M0+    | Unified      | `cmsis-svd/cmsis-svd-data` + STM32 Open Pin Data | varies      |
| `st/stm32f4`         | `stm32f401re, stm32f405rg`              | Cortex-M4F    | Unified      | `cmsis-svd/cmsis-svd-data` + STM32 Open Pin Data | varies      |
| `microchip/same70`   | `atsame70n21b, atsame70q21b`            | Cortex-M7     | Unified      | Microchip SAME70 DFP (ATDF + SVD)           | Apache-2.0  |
| `microchip/avr-da`   | `avr128da32`                            | AVR8 (Harvard) | prog / data / eeprom (Harvard) | Microchip AVR-Dx DFP (ATDF only; no SVD) | Apache-2.0  |
| `nxp/imxrt1060`      | `mimxrt1062, mimxrt1064`                | Cortex-M7     | Unified      | `nxp/mcux-soc-svd` + `nxp/mcux-sdk`         | varies      |
| `raspberrypi/rp2040` | `pico, rp2040`                          | Cortex-M0+ ×2 | Unified      | `raspberrypi/pico-sdk`                      | BSD-3       |
| `espressif/esp32c3`  | `esp32c3`                               | RISC-V RV32IMC | Unified      | `espressif/svd` + esp-idf `gpio_sig_map.h`  | Apache-2.0  |

Notes on non-SVD ingestion:

- **AVR-DA (Microchip)**: 8-bit AVR devices do not publish a CMSIS-SVD file.
  Register / interrupt / memory data is parsed directly from the ATDF inside
  the Microchip AVR-Dx DFP pack.  `sources/microchip_dfp.py` treats SVD as
  optional via the `SVD_OPTIONAL_FAMILIES` frozenset so the selector does
  not fail when the PDSC omits `<debug svd="…"/>`.
- **ESP32-C3 (Espressif)**: SVD comes from `github.com/espressif/svd` (sparse
  git clone).  The IO Matrix signal indices that populate `af_number` on
  PinSignals are tracked as a supplementary source
  (`sources/esp_idf.py::parse_gpio_sig_map`) that reads
  `components/soc/esp32c3/include/soc/gpio_sig_map.h` from esp-idf.
  A committed minimal fixture of that header lives at
  `tests/fixtures/esp-idf-gpio-sig-map/esp32c3/gpio_sig_map.h` and its
  Apache-2.0 header is preserved verbatim for provenance.

Pinmux backend schema ids per family:

- `st/stm32*`         — `alloy.pinmux.stm32-af-v1`
- `microchip/same70`  — `alloy.pinmux.sam-pio-v1`
- `microchip/avr-da`  — `alloy.pinmux.avr-portmux-v1`
- `nxp/imxrt1060`     — `alloy.pinmux.imxrt-iomuxc-v1`
- `raspberrypi/rp2040` — `alloy.pinmux.rp2040-funcsel-v1`
- `espressif/esp32c3` — `alloy.pinmux.espressif-iomatrix-v1`

Each schema id tells consumers how to interpret the numeric `af_number` on a
PinSignal: as an ARM alternate-function slot, an ESP32 IO Matrix index, an
AVR PORTMUX selection index, or an RP2040 FUNCSEL code.  No downstream
consumer should parse a string signal name to make routing decisions —
typed ref domains carry every executable path.
