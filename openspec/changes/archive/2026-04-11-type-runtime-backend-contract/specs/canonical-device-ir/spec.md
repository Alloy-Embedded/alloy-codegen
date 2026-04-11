## ADDED Requirements

### Requirement: Canonical Runtime Backend Schemas

The canonical IR SHALL describe runtime backend schemas explicitly for IP blocks and peripheral
instances that participate in runtime-owned subsystems.

#### Scenario: Foundational UART instance exposes backend schema

- **WHEN** a foundational family normalizes a UART-capable peripheral instance
- **THEN** the canonical peripheral instance includes a backend schema identifier
- **AND** the canonical IP block for that instance includes the same backend schema identifier

### Requirement: Canonical Register Descriptors

The canonical IR SHALL include normalized register descriptors with byte offsets derived from
upstream device sources.

#### Scenario: Peripheral registers are normalized from SVD

- **WHEN** a device source declares a peripheral register block in SVD-derived input
- **THEN** the canonical IR includes register descriptors for that peripheral
- **AND** each descriptor includes register name and offset in bytes

### Requirement: Typed Route Operations

The canonical IR SHALL model route operations with typed runtime fields instead of relying only
on free-form text targets.

#### Scenario: Pinmux route operation carries typed runtime data

- **WHEN** a connection candidate requires a pinmux selection
- **THEN** its route operation includes a runtime schema identifier
- **AND** the operation exposes typed subject and integer selector fields
