## Why

`alloy-codegen` already has a working foundation and active vendor-expansion proposals, but it
still lacks one thing that matters more than any individual adapter: an explicit definition of
what "finished" means.

Without a target-state proposal, the repository can drift into local optimizations:
- emiters that satisfy today's smoke tests but not tomorrow's Alloy integration
- family-specific additions that do not close the real IR or artifact contract
- generated C++ that leaks behavior instead of describing hardware
- vendor expansion before the first three vendor paths prove that the architecture is truly
  generic

This change defines the complete target state for `alloy-codegen`: the full hardware domains it
must model, the complete artifact contract it must publish, the boundary between codegen and
Alloy, and the maturity gates required before vendor 4 enters active implementation.

## What Changes

- **NEW** end-state contract for `alloy-codegen` as a descriptor-first hardware data platform
- **NEW** explicit boundary between `alloy-codegen`/`alloy-devices` and the `alloy` runtime/HAL
- **NEW** complete canonical IR target covering IP versions, packages, pins, signals, clocks,
  DMA, interrupts, memory, startup descriptors, documentation, and provenance
- **NEW** complete emitted artifact set for future Alloy consumption, including metadata,
  validation reports, and generated C++ descriptor headers
- **NEW** publication contract for `alloy-devices` based on stable `metadata/`, `generated/`,
  `reports/`, and `manifest.json` structure
- **NEW** admission gates that require ST, Microchip, and NXP foundational vendor paths to be
  publishable before vendor 4 enters active implementation
- **NEW** implementation roadmap covering source ingestion, normalization, validation, emission,
  publication, and three-vendor hardening
- **NON-GOAL** generating public HAL APIs, drivers, ownership/runtime semantics, or board BSPs in
  `alloy-codegen`; those belong in `alloy`

## Impact

- Affected specs:
  - `source-ingestion`
  - `patch-and-normalization`
  - `canonical-device-ir`
  - `validation-and-gates`
  - `artifact-emission`
  - `publication-workflow`
  - `codegen-pipeline-cli`
  - `codegen-alloy-boundary`
- Affected code:
  - source bundle resolution and vendor adapters
  - canonical IR schemas and manifests
  - validators, gates, and CI policy
  - emitters and `alloy-devices` artifact layout
  - future Alloy integration path based on published descriptors
- **BREAKING** (target-state contract): the final published `alloy-devices` layout is codified as
  a descriptor-first contract and may require migration from the current bootstrap artifact
  layout
