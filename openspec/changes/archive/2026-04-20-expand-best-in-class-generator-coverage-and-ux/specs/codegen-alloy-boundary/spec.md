## ADDED Requirements

### Requirement: User-facing configuration layers build on the runtime contract

Any higher-level generator UX or configuration surface MUST build on the same typed runtime device
model used by Alloy.

#### Scenario: Recipes and configurator outputs do not create a second device model
- **WHEN** the generator emits configuration recipes, examples, or configurator outputs
- **THEN** those outputs are derived from the typed runtime contract
- **AND** they do not introduce a parallel handwritten or reflection-only device model

