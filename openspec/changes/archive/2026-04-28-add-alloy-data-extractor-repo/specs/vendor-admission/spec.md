## ADDED Requirements

### Requirement: Vendor extraction logic SHALL live in a separate alloy-data-extractor repository

The repository ecosystem SHALL split vendor source extraction
into a standalone `alloy-data-extractor` repository — every
vendor parser (CMSIS-SVD, ATDF, MCUXpresso, ESP-IDF, Zephyr
DTS, modm-data, Pico SDK, datasheet PDF scraping, …) lives
there rather than inside alloy-codegen.  alloy-codegen SHALL
consume the canonical YAML
output produced by the extractor (via `alloy-devices-yml`)
rather than parsing vendor sources directly.  Adding a new
vendor SHALL be a one-PR change in alloy-data-extractor — a
new extractor module under
`src/alloy_data_extractor/extractors/<vendor>.py` plus an
entry in the source-pins manifest — with no edits required to
alloy-codegen.  The two repos communicate exclusively through
the schema-validated YAML format defined by
`define-canonical-device-yaml-schema`.

#### Scenario: alloy-codegen no longer imports vendor-specific source parsers

- **WHEN** alloy-codegen is built and tested after this change
  lands
- **THEN** `src/alloy_codegen/sources/` SHALL no longer contain
  bespoke vendor parsers (cmsis-svd, atdf, mcuxpresso, …)
- **AND** the only `sources/` module SHALL be
  `alloy_devices_yml.py` (the YAML consumer)

#### Scenario: Adding a new vendor is a single-repo change

- **WHEN** a contributor adds support for a new vendor (e.g.
  GigaDevice GD32)
- **THEN** the contribution SHALL touch only
  alloy-data-extractor: one new
  `extractors/gd32.py` + a `data/source_pins.toml` entry
- **AND** the extractor's CI SHALL produce YAML files that
  alloy-codegen consumes without further changes
- **AND** alloy-codegen SHALL emit C++ artifacts for the new
  vendor as soon as it bumps its `alloy-devices-yml`
  submodule pin

#### Scenario: Cross-language consumers reuse the same data

- **WHEN** a future `alloy-codegen-rust` or similar
  language-specific generator is added
- **THEN** it SHALL consume the same alloy-devices-yml data
- **AND** SHALL NOT need to ship its own vendor extractors
- **AND** SHALL pin to the same alloy-devices-yml SHA model
  alloy-codegen uses
