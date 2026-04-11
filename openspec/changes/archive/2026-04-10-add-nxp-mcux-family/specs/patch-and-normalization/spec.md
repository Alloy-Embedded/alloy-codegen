## ADDED Requirements

### Requirement: Header-Derived Connectivity Normalization
The normalize stage SHALL support families whose pin-function connectivity is delivered in
structured SDK headers.

#### Scenario: Parse NXP IOMUX header data into canonical facts
- **WHEN** a `nxp/imxrt1060` device is normalized
- **THEN** the normalizer SHALL parse structured SDK pin-function macros from the selected source
  headers
- **AND** it SHALL convert them into canonical pin, signal, peripheral, mux, and daisy facts

#### Scenario: Raw SDK strings do not leak past normalization
- **WHEN** header-derived pin-function data is normalized
- **THEN** required connectivity semantics SHALL be represented in canonical fields rather than
  only as raw header macro names or opaque vendor strings

### Requirement: Composite Repository Normalization
The system SHALL merge repository-delivered SDK connectivity data with repository-delivered SVD
register data into one canonical device model.

#### Scenario: SVD and SDK merge into one device IR
- **WHEN** the normalize stage runs for an `nxp/imxrt1060` device
- **THEN** SVD data SHALL provide register and interrupt structure
- **AND** SDK header data SHALL provide pin-function connectivity semantics
- **AND** the result SHALL be one canonical IR document with provenance to both sources
