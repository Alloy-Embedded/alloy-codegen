## ADDED Requirements

### Requirement: Publication Includes Full Descriptor Families
Publication SHALL publish connector, capability, package, interrupt, memory, startup, clock/reset,
and DMA descriptor families together as one validated family release.

#### Scenario: A family publish is requested after validation passes
- **WHEN** a family reaches publishable state
- **THEN** the publication output SHALL include every required descriptor family for that contract
- **AND** a partial publish that omits a required descriptor family SHALL be blocked

### Requirement: Publication Scope Supports Vendor and Family Generically
The publication workflow SHALL support generic `vendor + family` scope selection rather than
hard-coding a bootstrap vendor or family.

#### Scenario: A non-ST family is published through the remote workflow
- **WHEN** publication is requested for a family such as `microchip/same70` or `nxp/imxrt1060`
- **THEN** the workflow SHALL pass the requested vendor and family through the same publish path
- **AND** the resulting release metadata SHALL identify the correct vendor/family scope
