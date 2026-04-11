## ADDED Requirements

### Requirement: New Vendor Admission Gates
The validation system SHALL enforce explicit admission gates before a DFP-backed vendor family
is considered publishable support.

#### Scenario: Draft normalization is allowed before publication closure
- **WHEN** a new Microchip family can be fetched and normalized but still lacks closed
  connectivity-critical semantics
- **THEN** the system MAY emit draft validation and draft artifacts for development
- **AND** publication SHALL remain blocked until the family closes its publishable gate

#### Scenario: SAME70 publication requires two representative devices
- **WHEN** `microchip/same70` is evaluated for publication readiness
- **THEN** the board-target device and one second package variant SHALL both pass the semantic
  validation suite
- **AND** a single passing device SHALL NOT be sufficient to mark the family publishable

### Requirement: DFP Semantic Closure
Connectivity-critical validation for Microchip families SHALL cover the semantic domains needed
for trustworthy published support.

#### Scenario: Clock, interrupt, and package semantics must close
- **WHEN** validation runs for `microchip/same70`
- **THEN** it SHALL report zero critical conflicts for package pin connectivity, peripheral
  clock/enable ownership, and interrupt topology on the publication scope

#### Scenario: DMA gaps block publication
- **WHEN** DMA semantics required for the publication scope cannot be derived from DFP data and
  reviewed patches with sufficient confidence
- **THEN** the validation report SHALL mark the family as non-publishable
- **AND** the publish stage SHALL refuse to materialize released `alloy-devices` outputs for that
  family
