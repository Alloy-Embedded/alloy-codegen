## ADDED Requirements

### Requirement: Emitted artifacts MUST stay within declared per-class footprint budgets

The publish stage SHALL measure every emitted artifact's UTF-8
byte size and compare it against a budget declared in
`data/artifact_footprint_budget.toml`.  Each artifact name SHALL
have a `warn` budget (surfaced in the validation report on
exceedance) and a `fail` budget (aborts the build on exceedance).
A per-device override file
`data/artifact_footprint_overrides.toml` SHALL allow opting a
specific `(vendor, family, device, artifact_name)` tuple into a
larger budget without relaxing the global default.  Default
budgets SHALL be set from the largest currently admitted output
plus 50% headroom so the gate is non-disruptive on day one.

#### Scenario: No currently admitted device exceeds its warn budget on day one

- **WHEN** the gate is evaluated against every device the
  pipeline currently admits
- **THEN** zero artifacts SHALL exceed their `warn` budget
- **AND** the validation report SHALL contain no
  footprint warnings

#### Scenario: An oversized artifact aborts the build

- **WHEN** an emitter regression produces an artifact larger than
  its declared `fail` budget
- **AND** no override entry covers the offending device
- **THEN** the publish stage SHALL fail the build with a message
  identifying the artifact path, the actual size, the budget, and
  the override file path so a reviewer knows exactly how to
  proceed

#### Scenario: A per-device override permits a known-large artifact

- **WHEN** an entry in `data/artifact_footprint_overrides.toml`
  covers `(vendor=nxp, family=imxrt1060, device=mimxrt1062,
  artifact=pin_validation.hpp)` with a budget higher than the
  default
- **AND** the artifact's actual size sits within the override
  budget
- **THEN** the gate SHALL pass for that device
- **AND** the override SHALL NOT relax the budget for any other
  device sharing the same artifact name
