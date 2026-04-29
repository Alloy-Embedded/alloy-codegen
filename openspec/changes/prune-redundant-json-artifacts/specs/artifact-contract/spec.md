## ADDED Requirements

### Requirement: The publication tree SHALL not duplicate canonical YAML data as JSON

The emit stage SHALL NOT emit a per-device JSON dump of the
canonical IR (formerly at
`<family_dir>/metadata/devices/<device>.json`).  The canonical
IR is published exactly once — as YAML in the
`alloy-devices-yml` data repo at
`data/devices/vendors/<vendor>/<family>/devices/<device>.yml`.
The `family-index.json` artifact SHALL link each device entry
to its YAML path via a `yaml_path` field instead of the
removed `metadata_path` field.

#### Scenario: family-index.json points at canonical YAML

- **WHEN** the pipeline emits `family-index.json` for any
  admitted family
- **THEN** every device entry SHALL contain a `yaml_path`
  field of the form
  `data/devices/vendors/<vendor>/<family>/devices/<device>.yml`
- **AND** no entry SHALL contain a `metadata_path` field
- **AND** no `metadata/devices/<device>.json` artifact SHALL
  appear in the published artifact tree

#### Scenario: Family-rollup metadata JSONs are removed

- **WHEN** the pipeline emits artifacts for any admitted family
- **THEN** the published tree SHALL NOT contain
  `metadata/family-connectivity.json`,
  `metadata/system-descriptors.json`,
  `metadata/connectors.json`, `metadata/ip-blocks.json`,
  `metadata/packages.json`, or `metadata/capabilities.json`
- **AND** the `family-index.json` and `artifact-manifest.json`
  artifacts SHALL still be present (their consumers are
  documented and load-bearing)

#### Scenario: Runtime-rollup reports are pruned to consumed set

- **WHEN** the pipeline emits the `reports/` artifacts for any
  admitted family
- **THEN** `reports/runtime-capability-summary.json` and
  `reports/runtime-compatibility-matrix.json` SHALL NOT be
  emitted
- **AND** `reports/runtime-provenance.json`,
  `reports/runtime-explainability.json`, `reports/coverage.json`,
  `reports/validation-report.json`, and
  `reports/validation-summary.json` SHALL still be emitted
  (each has a documented CI or diagnostic consumer)
