## ADDED Requirements

### Requirement: Codegen Emits Facts, Alloy Implements Behavior
`alloy-codegen` SHALL emit hardware facts and descriptor artifacts, while `alloy` SHALL own
runtime behavior, policies, boards, and public API layers.

#### Scenario: Codegen does not generate public runtime HAL APIs
- **WHEN** a new generated artifact category is proposed for `alloy-codegen`
- **THEN** that artifact SHALL be limited to hardware description, compatibility data, manifests,
  or descriptor-oriented translation units
- **AND** it SHALL NOT introduce public driver APIs, ownership logic, board policy, or runtime
  behavior that belongs in `alloy`

#### Scenario: Alloy consumes generated descriptors to implement behavior
- **WHEN** Alloy adds bring-up or peripheral integration features
- **THEN** it SHALL consume the published descriptor artifacts from `alloy-devices`
- **AND** the behavior layer SHALL remain handwritten and testable inside `alloy`
