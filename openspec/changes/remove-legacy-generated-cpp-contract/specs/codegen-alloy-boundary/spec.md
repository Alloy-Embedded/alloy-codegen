## MODIFIED Requirements

### Requirement: The Alloy-facing C++ boundary is runtime-only

Codegen MUST publish only one Alloy-facing C++ boundary for device behavior: the typed runtime
contract.

#### Scenario: Alloy-facing headers stay inside the runtime boundary
- **WHEN** codegen emits published C++ artifacts intended for `alloy`
- **THEN** those artifacts live under `generated/runtime/**`
- **AND** they do not require Alloy to include table-oriented C++ reflection headers from
  `generated/**`

## ADDED Requirements

### Requirement: Startup follows the same runtime-only boundary

Startup MUST not remain a legacy exception to the runtime-only device boundary.

#### Scenario: Alloy includes startup through runtime startup contract
- **WHEN** `alloy` consumes startup descriptors from a published device tree
- **THEN** it can do so through `generated/runtime/devices/<device>/startup.hpp`
- **AND** it does not need `generated/devices/<device>/startup_descriptors.hpp`

### Requirement: Migration terminology does not create a second public contract

The public contract MUST not distinguish between "runtime" and "runtime-lite" as separate
published C++ products.

#### Scenario: Public publication uses one runtime name
- **WHEN** the published C++ device contract is inspected
- **THEN** the supported public path is `generated/runtime/**`
- **AND** any remaining `runtime-lite` naming is internal migration terminology only
