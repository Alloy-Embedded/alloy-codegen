## ADDED Requirements

### Requirement: The Zephyr DTS adapter SHALL ship compatible-string maps for every Zephyr-supported vendor in scope

The pipeline's Zephyr DTS adapter (`src/alloy_codegen/sources/zephyr_dts.py`) SHALL register a curated `compatible` → IP-name map for each of the additional vendors `renesas`, `ti`, `atmel`, `ambiq`, `infineon`, `silabs`, and `espressif`, in addition to the existing Nordic map.  Each map SHALL cover at minimum the peripheral classes `uart`, `spi`, `i2c`, `gpio`, and the family's primary timer or PWM binding.  All map values SHALL be non-empty alloy canonical IP names (lowercase, underscore-separated where multiword).

#### Scenario: Renesas RA compatibles resolve through the registry

- **WHEN** `compatible_map_for_vendor("renesas")` is called
- **THEN** the returned mapping SHALL contain at minimum `renesas,ra-sci-uart` → `uart`, `renesas,ra-spi` → `spi`, `renesas,ra-sci-i2c` → `i2c`, `renesas,ra-ioport` → `gpio`
- **AND** every value in the mapping SHALL be a non-empty lowercase string

#### Scenario: ESP32 compatibles resolve through the registry

- **WHEN** `compatible_map_for_vendor("espressif")` is called
- **THEN** the returned mapping SHALL contain at minimum `espressif,esp32-uart` → `uart`, `espressif,esp32-spi` → `spi`, `espressif,esp32-i2c` → `i2c`, `espressif,esp32-gpio` → `gpio`
- **AND** the mapping SHALL include at least one PWM-class binding (`espressif,esp32-mcpwm` or `espressif,esp32-ledc`)

#### Scenario: SiLabs gecko compatibles resolve through the registry

- **WHEN** `compatible_map_for_vendor("silabs")` is called
- **THEN** the returned mapping SHALL contain at minimum `silabs,gecko-usart` → `uart`, `silabs,gecko-spi` → `spi`, `silabs,gecko-i2c` → `i2c`, `silabs,gecko-gpio` → `gpio`

### Requirement: Cross-vendor generic compatibles SHALL be shared across every vendor map

The Zephyr DTS adapter SHALL maintain a `_GENERIC_COMPATIBLE_MAP` covering compatibles whose semantics are the same across every vendor (ARM core peripherals such as `arm,armv7m-nvic` and `arm,armv8m-nvic`).  `compatible_map_for_vendor(v)` SHALL return the union of `_GENERIC_COMPATIBLE_MAP` and the per-vendor map, so vendor-specific maps do not have to redeclare ARM-core bindings.

#### Scenario: Generic ARM NVIC compatible resolves under any vendor

- **WHEN** `compatible_map_for_vendor("nordic")` and `compatible_map_for_vendor("renesas")` are both called
- **THEN** both returned mappings SHALL include `arm,armv7m-nvic` (or `arm,armv8m-nvic` for v8 cores) under a shared generic IP-name key
- **AND** removing the entry from the per-vendor map SHALL NOT break this scenario — the entry comes from the shared generic map

### Requirement: Unmapped vendor compatibles SHALL be skipped, not raised

The adapter SHALL preserve the existing "silent-skip on unknown compatible" behaviour for any compatible string that is not in either the generic map or the resolved per-vendor map.  The skipped compatibles SHALL be surfaced through `ZephyrDeviceDocument.skipped_compatibles` for diagnostics.

#### Scenario: Unknown vendor compatible string is recorded, not raised

- **WHEN** the adapter parses a DTS file containing a node with compatible string `acme,frobnicator-2000` (no vendor map registered)
- **THEN** the adapter SHALL skip the node and continue
- **AND** the resulting `ZephyrDeviceDocument.skipped_compatibles` tuple SHALL contain `acme,frobnicator-2000`
- **AND** no exception SHALL be raised

### Requirement: Vendor map lookups SHALL fail loudly for unknown vendor keys

`compatible_map_for_vendor(vendor)` SHALL continue to raise `StageExecutionError` when called with a vendor key that has no registered map.  The error message SHALL list the known vendor keys so the caller sees the available options.

#### Scenario: Unknown vendor key raises with a discoverable error

- **WHEN** `compatible_map_for_vendor("not-a-vendor")` is called
- **THEN** a `StageExecutionError` SHALL be raised
- **AND** the message SHALL list every currently registered vendor key (nordic, renesas, ti, atmel, ambiq, infineon, silabs, espressif)
