## ADDED Requirements

### Requirement: Final `alloy-devices` Contract Shape
The publication workflow SHALL converge on a stable family-root contract consisting of
`manifest.json`, `metadata/`, `generated/`, and `reports/`.

#### Scenario: Published family subtree is self-describing
- **WHEN** a family has been published into `alloy-devices`
- **THEN** its family root SHALL contain enough manifest and report data to identify the generator
  revision, schema version, source inputs, patch inputs, and publication outcome

#### Scenario: Published family subtree separates metadata from generated descriptors
- **WHEN** tooling or Alloy consumes a published family
- **THEN** machine-readable metadata and generated C++ descriptors SHALL live in distinct
  publication subtrees under the family root

### Requirement: Publication Without Regeneration
Published artifacts SHALL be sufficient for Alloy consumption without local vendor-source access
or local code generation.

#### Scenario: Alloy consumes published artifacts directly
- **WHEN** Alloy checks out a pinned `alloy-devices` revision
- **THEN** it SHALL be able to consume the published hardware descriptors it needs directly
- **AND** it SHALL NOT require local regeneration from upstream vendor sources
