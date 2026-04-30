# Prune Redundant JSON Artifacts

## Why

The emit stage currently produces ~20 JSON artifacts per
admitted device-family.  Audit (against actual consumers in
`alloy/`, the CI workflows under `.github/workflows/`, and
alloy-data-extractor) shows roughly **75% of the emitted JSON
is unused**:

| Artifact | Size / family | Consumer |
|---|---|---|
| `metadata/devices/<device>.json` | 150-180 KB × N devices | **none** — identical key set to `data/devices/.../<device>.yml`; pure duplication after the canonical-YAML pivot |
| `metadata/family-connectivity.json` | 16 KB | none |
| `metadata/system-descriptors.json` | 43 KB | none |
| `metadata/connectors.json` | 45 KB | none |
| `metadata/ip-blocks.json` | 5 KB | none |
| `metadata/packages.json` | 4.7 KB | none |
| `metadata/capabilities.json` | 2.8 KB | none |
| `reports/runtime-capability-summary.json` | 8 KB | none |
| `reports/runtime-compatibility-matrix.json` | 5 KB | none |
| `metadata/family-index.json` | 348 B | CI checks existence only — no content read |

Per-family extra weight: ~117 KB metadata rollups + 13 KB
unused reports + ~150 KB per device for the duplicated
metadata/devices JSONs.  Across the 9 admitted families this
is **~4 MB** of redundant publication output.

The remaining JSONs *are* consumed and stay:

* `artifact-manifest.json` — `publish-alloy-devices.yml`
  pins build SHA/version
* `reports/runtime-provenance.json` — bootstrap CI workflow
  asserts on `report_id`
* `reports/runtime-explainability.json` — same workflow
* `reports/coverage.json` — `publish-alloy-devices.yml`
  reads coverage rollup
* `reports/validation-report.json` /
  `reports/validation-summary.json` — gate diagnostics
* `generated/runtime/devices/<device>/capabilities.json` —
  `alloy/cmake/alloy_devices.cmake` does `EXISTS` check to
  detect capability availability

## What Changes

- Remove the following emitters from the emit stage:
  - `emit_device_metadata` (per-device JSON dump — duplicated
    by canonical YAML)
  - `emit_family_connectivity`
  - `emit_system_descriptors_metadata`
  - `emit_ip_blocks_metadata`
  - `emit_packages_metadata`
  - `emit_connectors_metadata`
  - `emit_capabilities_metadata`
  - `emit_runtime_capability_summary_report`
  - `emit_runtime_compatibility_matrix_report`
- Slim `family-index.json` so each device entry points at the
  canonical YAML path
  (`data/devices/vendors/<vendor>/<family>/devices/<device>.yml`)
  instead of the deleted `metadata/devices/<device>.json`.
- Drop the matching emit-stage glue in `stages/emit.py` and the
  `metadata_path` field that pointed at the removed JSONs.
- Regenerate golden fixtures under `tests/fixtures/emitted/` —
  the 9 redundant artifacts disappear; `family-index.json` body
  changes shape.

## Impact

- ~9 emitter functions deleted from `emission.py` (~250 LOC).
- ~4 MB removed from every published `alloy-devices` payload.
- Faster `publish` stage (fewer artifacts to materialise).
- No consumer breaks — every removed artifact had zero
  external readers per the audit.
- `metadata/devices/` directory disappears from the layout —
  consumers that want the canonical IR read the YAML directly
  via the data repo (the documented pattern post-pivot).

## What this DOES NOT do

- Does not change the canonical IR shape.  The data is still
  emitted; only the redundant JSON projections of it go away.
- Does not change the `runtime/devices/<device>/capabilities.json`
  artifact (alloy/ HAL CMake depends on it).
- Does not consolidate `validation-report.json` +
  `validation-summary.json` (they're both small and have
  distinct roles — gate vs. summary — so neither is redundant).
- Does not touch the runtime-provenance / explainability
  reports — both are explicit CI consumers.
