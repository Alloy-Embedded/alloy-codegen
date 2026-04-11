## ADDED Requirements

### Requirement: Multi-Pattern Source Bundles
The source stage SHALL support a generic source-bundle model that can represent repository-backed,
pack-backed, and SDK-backed vendor inputs without changing the pipeline shape.

#### Scenario: Repository-backed family uses named source IDs
- **WHEN** a family such as `st/stm32g0` is fetched
- **THEN** the source stage SHALL resolve its upstream inputs through stable logical source IDs
- **AND** those source IDs SHALL appear in source manifests and structured CLI output

#### Scenario: Pack-backed family uses the same source-bundle model
- **WHEN** a family such as `microchip/same70` is fetched from a DFP archive and extracted tree
- **THEN** the source stage SHALL represent the pack and extracted tree as named source IDs in the
  same source-bundle model used by repository-backed families

#### Scenario: SDK-backed family uses the same source-bundle model
- **WHEN** a family such as `nxp/imxrt1060` is fetched from official repository sources including
  SDK headers
- **THEN** the source stage SHALL represent those repository inputs as named source IDs in the
  same source-bundle model used by other vendor shapes

### Requirement: Source Provenance and Licensing
The source stage SHALL record sufficient provenance and licensing metadata for every logical
source input used to build publishable artifacts.

#### Scenario: Source manifests capture origin and licensing identity
- **WHEN** a family fetch completes successfully
- **THEN** the source manifest SHALL record origin, revision or content hash, logical source ID,
  and source licensing identity for each resolved input

#### Scenario: Publishable artifacts remain traceable to source inputs
- **WHEN** published artifacts are inspected later without access to the original fetch workspace
- **THEN** the manifest chain SHALL still identify which source bundle and source revisions
  produced the published family artifacts
