## ADDED Requirements

### Requirement: Alloy Runtime SHALL Target Runtime-Lite Artifacts

The documented boundary between `alloy-codegen` and `alloy` SHALL state that normal runtime
consumption targets the runtime-lite contract, while reflection artifacts remain available for
tooling, validation, smoke compilation, and debugging.

#### Scenario: Boundary doc describes runtime-lite as the hot-path contract

- **WHEN** the boundary documentation is updated for this change
- **THEN** it explicitly identifies runtime-lite artifacts as the intended hot-path contract for
  `alloy`
- **AND** it identifies reflection artifacts as non-hot-path support products
