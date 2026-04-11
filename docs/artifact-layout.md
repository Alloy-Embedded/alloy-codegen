# Artifact Layout

`alloy-codegen` emits local build artifacts and published `alloy-devices` artifacts with
separate roots.

## Local Artifact Root

The local artifact root is controlled by `ExecutionContext.artifact_root` or
`--artifact-root`. It contains:

- `<vendor>/<family>/artifact-manifest.json`
- `<vendor>/<family>/metadata/family-index.json`
- `<vendor>/<family>/metadata/family-connectivity.json`
- `<vendor>/<family>/metadata/ip-blocks.json`
- `<vendor>/<family>/metadata/capabilities.json`
- `<vendor>/<family>/metadata/packages.json`
- `<vendor>/<family>/metadata/connectors.json`
- `<vendor>/<family>/metadata/system-descriptors.json`
- `<vendor>/<family>/metadata/devices/<device>.json`
- `<vendor>/<family>/generated/peripherals/<peripheral>.hpp`
- `<vendor>/<family>/generated/ip/<ip-version>.hpp`
- `<vendor>/<family>/generated/connector_tables.hpp`
- `<vendor>/<family>/generated/runtime_profiles.hpp`
- `<vendor>/<family>/generated/rcc_map.hpp`
- `<vendor>/<family>/generated/dma_map.hpp`
- `<vendor>/<family>/generated/interrupt_map.hpp`
- `<vendor>/<family>/generated/memory_map.hpp`
- `<vendor>/<family>/generated/package_map.hpp`
- `<vendor>/<family>/generated/clock_tree_lite.hpp`
- `<vendor>/<family>/generated/devices/<device>/device_descriptor.hpp`
- `<vendor>/<family>/generated/devices/<device>/pins.hpp`
- `<vendor>/<family>/generated/devices/<device>/peripheral_instances.hpp`
- `<vendor>/<family>/generated/devices/<device>/interrupt_bindings.hpp`
- `<vendor>/<family>/generated/devices/<device>/dma_bindings.hpp`
- `<vendor>/<family>/generated/devices/<device>/capability_overlays.hpp`
- `<vendor>/<family>/generated/devices/<device>/register_map.hpp`
- `<vendor>/<family>/generated/devices/<device>/register_fields.hpp`
- `<vendor>/<family>/generated/devices/<device>/startup_descriptors.hpp`
- `<vendor>/<family>/generated/devices/<device>/startup_vectors.cpp`
- `<vendor>/<family>/reports/validation-report.json`
- `<vendor>/<family>/reports/validation-summary.json`
- `<vendor>/<family>/reports/coverage.json`
- `<vendor>/<family>/reports/publication-summary.json`

`publication-summary.json` is a local run artifact. It may contain absolute filesystem paths
for the local machine that executed the pipeline.

## Publication Root

The publication root is controlled by `ExecutionContext.publication_root` or
`--publication-root`. When a sibling `../alloy-devices` git checkout exists,
`ExecutionContext.default()` prefers it automatically. The publication root models the
checked-out `alloy-devices` repository.

Successful publication writes:

- `<vendor>/<family>/artifact-manifest.json`
- `<vendor>/<family>/metadata/family-index.json`
- `<vendor>/<family>/metadata/family-connectivity.json`
- `<vendor>/<family>/metadata/ip-blocks.json`
- `<vendor>/<family>/metadata/capabilities.json`
- `<vendor>/<family>/metadata/packages.json`
- `<vendor>/<family>/metadata/connectors.json`
- `<vendor>/<family>/metadata/system-descriptors.json`
- `<vendor>/<family>/metadata/devices/<device>.json`
- `<vendor>/<family>/generated/peripherals/<peripheral>.hpp`
- `<vendor>/<family>/generated/ip/<ip-version>.hpp`
- `<vendor>/<family>/generated/connector_tables.hpp`
- `<vendor>/<family>/generated/runtime_profiles.hpp`
- `<vendor>/<family>/generated/rcc_map.hpp`
- `<vendor>/<family>/generated/dma_map.hpp`
- `<vendor>/<family>/generated/interrupt_map.hpp`
- `<vendor>/<family>/generated/memory_map.hpp`
- `<vendor>/<family>/generated/package_map.hpp`
- `<vendor>/<family>/generated/clock_tree_lite.hpp`
- `<vendor>/<family>/generated/devices/<device>/device_descriptor.hpp`
- `<vendor>/<family>/generated/devices/<device>/pins.hpp`
- `<vendor>/<family>/generated/devices/<device>/peripheral_instances.hpp`
- `<vendor>/<family>/generated/devices/<device>/interrupt_bindings.hpp`
- `<vendor>/<family>/generated/devices/<device>/dma_bindings.hpp`
- `<vendor>/<family>/generated/devices/<device>/capability_overlays.hpp`
- `<vendor>/<family>/generated/devices/<device>/register_map.hpp`
- `<vendor>/<family>/generated/devices/<device>/register_fields.hpp`
- `<vendor>/<family>/generated/devices/<device>/startup_descriptors.hpp`
- `<vendor>/<family>/generated/devices/<device>/startup_vectors.cpp`
- `<vendor>/<family>/reports/validation-report.json`
- `<vendor>/<family>/reports/validation-summary.json`
- `<vendor>/<family>/reports/coverage.json`
- `<vendor>/<family>/reports/publication-record.json`

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
- `reports/publication-record.json` contains the deterministic `target_artifact_revision` for the
  published artifact set.
- `artifact-manifest.json` is the traceability entrypoint for generator version, schema
  version, source manifest, patch manifest, and validation hashes.

## Remote Release Workflow

The GitHub Actions workflow
`/Users/lgili/Documents/01 - Codes/01 - Github/alloy-codegen/.github/workflows/publish-alloy-devices.yml`
turns a validated `publish` result into an optional git commit against the real
`alloy-devices` repository.

Remote release rules:

- The workflow always starts from a clean `alloy-devices` checkout before materializing
  artifacts.
- It reuses the same `alloy-codegen publish` command already validated in CI.
- It creates a commit only when the `alloy-devices` working tree actually changes.
- It skips commit and push when the published tree already matches the target branch.
- Automatic push requires the repository secret `ALLOY_DEVICES_PUSH_TOKEN` with write access
  to `Alloy-Embedded/alloy-devices`.
- Without that secret, the workflow still performs a validation-only publication and records
  that push was skipped.
