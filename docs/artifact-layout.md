# Artifact Layout

`alloy-codegen` emits local build artifacts and published `alloy-devices` artifacts with
separate roots.

## Local Artifact Root

The local artifact root is controlled by `ExecutionContext.artifact_root` or
`--artifact-root`. It contains:

- `st/<family>/artifact-manifest.json`
- `st/<family>/validation-report.json`
- `st/<family>/family-index.json`
- `st/<family>/family-connectivity.json`
- `st/<family>/<device>/device.json`
- `st/<family>/<device>/register_map.hpp`
- `st/<family>/<device>/pin_functions.hpp`
- `st/<family>/<device>/startup.cpp`
- `st/<family>/generated/peripherals/<peripheral>.hpp`
- `st/<family>/publication-summary.json`

`publication-summary.json` is a local run artifact. It may contain absolute filesystem paths
for the local machine that executed the pipeline.

## Publication Root

The publication root is controlled by `ExecutionContext.publication_root` or
`--publication-root`. When a sibling `../alloy-devices` git checkout exists,
`ExecutionContext.default()` prefers it automatically. The publication root models the
checked-out `alloy-devices` repository.

For the bootstrap family, successful publication writes:

- `st/<family>/artifact-manifest.json`
- `st/<family>/validation-report.json`
- `st/<family>/family-index.json`
- `st/<family>/family-connectivity.json`
- `st/<family>/<device>/device.json`
- `st/<family>/<device>/register_map.hpp`
- `st/<family>/<device>/pin_functions.hpp`
- `st/<family>/<device>/startup.cpp`
- `st/<family>/generated/peripherals/<peripheral>.hpp`
- `st/<family>/publication-record.json`

## Contract Notes

- Published artifacts are written only when validation passes for the requested scope.
- Published artifacts are staged and verified against an Alloy smoke consumer before
  promotion to the final publication root.
- When the publication root is a git checkout, promotion preserves `.git` and unrelated
  repository files while replacing only the managed published artifact subtrees.
- The smoke consumer source lives in
  `tests/codegen/published_artifact_contract_smoke.cpp` inside `alloy-codegen`, but it is
  compiled against the checked-out Alloy headers and the staged/published generated
  artifacts.
- `publication-record.json` contains the deterministic `target_artifact_revision` for the
  published artifact set.
- `artifact-manifest.json` is the traceability entrypoint for generator version, schema
  version, source manifest, patch manifest, and validation hashes.
