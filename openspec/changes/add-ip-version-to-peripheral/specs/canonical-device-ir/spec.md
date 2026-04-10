## MODIFIED Requirements

### Requirement: Canonical Device IR
The system SHALL define a versioned canonical intermediate representation (IR) that is the
single source of truth for validation, emission, and publication.

#### Scenario: Canonical IR models core hardware domains
- **WHEN** a device is normalized successfully
- **THEN** the canonical IR SHALL represent at least:
  device identity, family, packages, pins, alternate functions, IP blocks, register blocks,
  interrupts, DMA routing, RCC/clock/reset relationships, memory regions, and provenance

#### Scenario: IR is versioned explicitly
- **WHEN** normalized output is written or emitted
- **THEN** it SHALL declare the IR schema version explicitly
- **AND** any incompatible schema change SHALL require a breaking change proposal

#### Scenario: Peripheral instances carry IP version
- **WHEN** a device is normalized and IP version data is available from the source
- **THEN** each peripheral instance in the canonical IR SHALL carry an `ip_version` field
  containing the vendor-declared IP version string (e.g. `"usart_v3_1"`)
- **AND** if IP version data is not available for a given peripheral, `ip_version` SHALL be
  `null` rather than absent or filled with a placeholder

#### Scenario: IP version enables cross-device peripheral matching
- **WHEN** two peripheral instances across different devices carry the same `ip_version` value
- **THEN** downstream consumers MAY treat those instances as sharing the same register layout
  and hardware behavior
- **AND** the pipeline SHALL NOT assert uniqueness of `ip_version` values across families
