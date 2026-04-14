## MODIFIED Requirements

### Requirement: Codegen/Runtime Boundary
`alloy-codegen` SHALL publish the complete hardware contract required by Alloy startup and system
bring-up. Alloy SHALL NOT need handwritten SAME70 `PMC`/`EEFC` sequencing to realize foundational
system-clock profiles.

#### Scenario: Alloy consumes SAME70 system-clock profiles
- **WHEN** Alloy selects a published SAME70 system-clock profile
- **THEN** the required oscillator, PLLA, flash-wait-state, and MCK sequencing facts SHALL
  already be published by `alloy-codegen`
- **AND** Alloy SHALL NOT need to reconstruct or hardcode that sequence outside the published
  device contract
