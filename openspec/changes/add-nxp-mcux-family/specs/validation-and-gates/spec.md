## ADDED Requirements

### Requirement: SDK-Backed Family Admission Gates
The validation system SHALL enforce explicit gates before an SDK-backed NXP family is considered
publishable support.

#### Scenario: Draft artifacts are allowed before publishable closure
- **WHEN** `nxp/imxrt1060` can be fetched and normalized but still lacks closed clock, DMA, or
  other connectivity-critical semantics
- **THEN** the system MAY emit draft validation and draft artifacts for development
- **AND** publication SHALL remain blocked until the family closes its publishable gate

#### Scenario: Both bootstrap devices must pass for family admission
- **WHEN** `nxp/imxrt1060` is evaluated for publication readiness
- **THEN** both bootstrap devices SHALL pass the semantic validation suite
- **AND** one passing device SHALL NOT be sufficient to mark the family supported

### Requirement: SDK and SVD Semantic Agreement
The validation stage SHALL verify semantic agreement between SDK-derived connectivity data and
SVD-derived peripheral data for the publication scope.

#### Scenario: Peripheral naming agrees across sources
- **WHEN** validation runs for `nxp/imxrt1060`
- **THEN** SDK-derived signal tuples and SVD-derived peripheral instances SHALL align without
  critical conflicts on the publication scope

#### Scenario: Missing clock or DMA closure blocks publication
- **WHEN** required clock/enable or DMA semantics cannot be closed from the chosen NXP sources
  and reviewed patches with sufficient confidence
- **THEN** the validation report SHALL mark the family as non-publishable
- **AND** the publish stage SHALL refuse to release `alloy-devices` artifacts for that family
