## ADDED Requirements

### Requirement: Pack-Based Vendor Source Ingestion
The source stage SHALL support vendors whose canonical upstream input is a structured pack
artifact rather than a loose repository tree.

#### Scenario: Fetch and select sources from a Microchip DFP
- **WHEN** the user or CI runs the source stage for `microchip/same70`
- **THEN** the system SHALL accept a reviewed DFP input as the upstream source product
- **AND** it SHALL materialize a deterministic extracted source tree or reuse a deterministic
  extracted tree input
- **AND** it SHALL select the ATDF and SVD files required for the targeted device from that
  source product

#### Scenario: Pack provenance is recorded explicitly
- **WHEN** the fetch stage resolves a DFP-backed family
- **THEN** the source manifest SHALL record pack identity, origin, archive revision or content
  hash, extracted-tree identity, and the selected device-specific source files
- **AND** downstream stages SHALL be able to trace normalized facts back to those source IDs

### Requirement: Named Source Bundles
The source stage SHALL model upstream inputs as named source bundles per `(vendor, family)`
scope instead of hardcoding vendor-specific auxiliary source flags.

#### Scenario: New vendor sources do not require new ad hoc CLI flags
- **WHEN** a supported family requires more than one upstream source or extraction product
- **THEN** the CLI and context model SHALL address those inputs by stable source IDs
- **AND** adding a new vendor source SHALL NOT require introducing a new top-level CLI flag for
  that source type

#### Scenario: Existing family source resolution remains stable
- **WHEN** named source bundles are introduced for a new vendor
- **THEN** previously supported ST family fetch behavior SHALL remain reproducible
- **AND** the same source bundle model SHALL be able to represent both ST and Microchip family
  inputs
