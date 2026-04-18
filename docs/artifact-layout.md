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
- `<vendor>/<family>/generated/runtime/types.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/peripheral_instances.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/pins.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/registers.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/register_fields.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/clock_bindings.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/dma_bindings.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/routes.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/systick.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/startup.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/system_clock.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/interrupts.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/resets.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/enable_domains.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/clock_graph.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/capabilities.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/system_sequences.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/common.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/gpio.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/uart.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/i2c.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/spi.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/dma.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/adc.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/dac.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/timer.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/pwm.hpp`
- `<vendor>/<family>/generated/devices/<device>/startup.cpp`
- `<vendor>/<family>/generated/devices/<device>/startup_vectors.cpp`
- `<vendor>/<family>/reports/validation-report.json`
- `<vendor>/<family>/reports/validation-summary.json`
- `<vendor>/<family>/reports/coverage.json`
- `<vendor>/<family>/reports/runtime-provenance.json`
- `<vendor>/<family>/reports/runtime-explainability.json`
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
- `<vendor>/<family>/generated/runtime/types.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/peripheral_instances.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/pins.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/registers.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/register_fields.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/clock_bindings.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/dma_bindings.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/routes.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/systick.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/startup.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/system_clock.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/interrupts.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/resets.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/enable_domains.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/clock_graph.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/capabilities.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/system_sequences.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/common.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/gpio.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/uart.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/i2c.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/spi.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/dma.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/adc.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/dac.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/timer.hpp`
- `<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/pwm.hpp`
- `<vendor>/<family>/generated/devices/<device>/startup.cpp`
- `<vendor>/<family>/generated/devices/<device>/startup_vectors.cpp`
- `<vendor>/<family>/reports/validation-report.json`
- `<vendor>/<family>/reports/validation-summary.json`
- `<vendor>/<family>/reports/coverage.json`
- `<vendor>/<family>/reports/runtime-provenance.json`
- `<vendor>/<family>/reports/runtime-explainability.json`
- `<vendor>/<family>/reports/publication-record.json`

## Contract Notes

- `generated/runtime/` is the only supported Alloy-facing C++ contract.
- `generated/runtime/devices/<device>/driver_semantics/*.hpp` is the semantic layer that maps
  runtime facts into zero-overhead driver roles for `gpio`, `uart`, `i2c`, `spi`, `dma`,
  `adc`, `dac`, `timer`, and `pwm`.
- `generated/runtime/devices/<device>/startup.hpp` is the typed startup metadata contract.
- `generated/runtime/devices/<device>/enable_domains.hpp` exposes typed enable-domain facts for
  peripherals whose activation is governed by published runtime clock-gate controls.
- `generated/runtime/devices/<device>/system_sequences.hpp` is the typed foundational
  bring-up sequence contract that ties startup, startup-control, and default clock metadata
  together without reintroducing reflection-heavy tables.
- `generated/devices/<device>/startup.cpp` and `startup_vectors.cpp` remain published build
  translation units.
- Published artifacts are written only when validation passes for the requested scope.
- Published artifacts are staged and verified against an Alloy smoke consumer before
  promotion to the final publication root.
- When the publication root is a git checkout, promotion preserves `.git` and unrelated
  repository files while replacing only the managed published artifact subtrees.
- The smoke consumer source lives in
  `tests/codegen/published_runtime_lite_contract_smoke.cpp` inside `alloy-codegen`, and it is
  compiled against the checked-out Alloy headers and the staged/published runtime contract.
- `reports/publication-record.json` contains the deterministic `target_artifact_revision` for the
  published artifact set.
- `reports/runtime-provenance.json` traces runtime-critical published facts back to upstream
  sources, patches, and inference rules.
- `reports/runtime-explainability.json` explains accepted runtime routes, bindings, capabilities,
  and any heuristic or partial coverage that remains visible in the published contract.
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
