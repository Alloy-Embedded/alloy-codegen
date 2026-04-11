## ADDED Requirements

### Requirement: SDK-Delivered Structured Source Support
The source stage SHALL support vendors whose canonical connectivity source is delivered through
official SDK repositories and structured headers rather than a standalone pin-data repository.

#### Scenario: Resolve NXP source bundle from official repositories
- **WHEN** the user or CI runs the fetch stage for `nxp/imxrt1060`
- **THEN** the system SHALL resolve the family inputs from the official `nxp-mcux-soc-svd` and
  `nxp-mcux-sdk` source bundle
- **AND** it SHALL record repository revisions, logical source IDs, and selected device-local
  files in the source manifest

#### Scenario: SDK-backed families are reproducible
- **WHEN** the same NXP source-bundle revisions are fetched twice for the same scope
- **THEN** the selected file manifests SHALL be byte-stable
- **AND** downstream stages SHALL see the same logical source identities on both runs
