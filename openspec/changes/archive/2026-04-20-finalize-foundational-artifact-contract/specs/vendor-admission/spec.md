## MODIFIED Requirements

### Requirement: Foundational vendor set

The system SHALL treat the following vendors and families as the foundational admitted set, and
those families may be published without further approval only while they remain contract-complete
under the active artifact and publication rules:

| Vendor      | Admitted families | Source pattern                              |
|-------------|-------------------|---------------------------------------------|
| `st`        | `stm32g0`, `stm32f4` | repository + structured metadata companion |
| `microchip` | `same70`          | pack archive + deterministic extracted tree |
| `nxp`       | `imxrt1060`       | repository + SDK-delivered structured headers |

#### Scenario: Foundational family regresses below contract-complete
- **WHEN** an admitted foundational family no longer satisfies the active artifact-contract or
  publication-consistency requirements
- **THEN** that family SHALL be treated as an open blocker for vendor admission
- **AND** no vendor 4 admission proposal may proceed until the regression is closed

### Requirement: Admission gate

The system SHALL keep the vendor-admission gate closed for any new vendor (vendor 4 or beyond)
until all of the following are true:

- Gates T7, T8, and T9 are closed:
  - T7: `st/stm32f4` is publishable, contract-complete, and has completed two stable publication
    cycles on the hardened contract
  - T8: `microchip/same70` is publishable, contract-complete, and has completed two stable
    publication cycles on the hardened contract
  - T9: `nxp/imxrt1060` is publishable, contract-complete, and has completed two stable
    publication cycles on the hardened contract
- No foundational family requires final-stage emitter or publish exceptions
- No foundational family remains published while its own coverage/readiness reports still mark it
  incomplete
- A completed vendor-admission proposal exists in `openspec/changes/` declaring all of the items
  in the checklist below

#### Scenario: Foundational family is emitted but not contract-complete
- **WHEN** a foundational family is materialized into `alloy-devices` but its own readiness data
  still says it is incomplete
- **THEN** the admission gate SHALL remain open
- **AND** that family SHALL NOT count toward T7, T8, or T9 closure
