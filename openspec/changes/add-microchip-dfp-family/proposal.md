## Why

The current pipeline proves the architecture with ST families, but it still carries one weak
assumption: auxiliary upstream sources are wired in ad hoc per vendor. That was acceptable for
bootstrapping `stm32g0` and `stm32f4`, but it is the wrong pattern to scale into a new vendor.

Microchip/Atmel families are distributed through Device Family Packs (DFPs) that bundle
multiple source types in one upstream product: pack metadata, ATDF device descriptions, SVD
register descriptions, startup files, and family metadata. If we bolt this onto the current
pipeline as "just another special source root", we will reproduce the same design debt we are
trying to remove from the old generator.

This change adds first-class support for DFP-backed vendor ingestion and uses `same70` as the
first Microchip family. The goal is not only to parse a pack, but to admit a second vendor
without forking the architecture, the IR, or the publication contract.

## What Changes

- **NEW** generic named-source input model for families that need more than one upstream source
  artifact, extraction stage, or SDK-delivered metadata bundle
- **NEW** `microchip_dfp` source adapter capable of ingesting Microchip DFP inputs, unpacking
  deterministic source trees, and selecting device-specific ATDF and SVD files
- **NEW** Microchip vendor namespace in the device registry using `microchip` as the canonical
  vendor key and `same70` as the first family
- **NEW** ATDF + SVD composite normalization path for Microchip families that maps pack data into
  the existing canonical IR
- **NEW** family patch catalog and device overlays for `microchip/same70`
- **NEW** validation rules and maturity gates for admitting a new vendor whose upstream data is a
  pack rather than a loose source repository
- **NEW** publication target for `microchip/same70` artifacts in `alloy-devices`
- **NON-GOAL** using Harmony, modm-data, modm-devices, or any third-party generated output as the
  system of record
- **NON-GOAL** supporting all SAM families in one step; this proposal is limited to the first
  Microchip vendor path and the `same70` family
- **BREAKING** (internal tooling only): vendor-specific auxiliary CLI flags such as
  `--pin-source-root` are replaced or deprecated in favor of a generic named-source override
  mechanism

## Impact

- Affected specs:
  - `source-ingestion`
  - `patch-and-normalization`
  - `canonical-device-ir`
  - `validation-and-gates`
  - `codegen-pipeline-cli`
- Affected code:
  - source adapter layer and source manifest model
  - CLI/context source override plumbing
  - device registry and scope resolution
  - Microchip family patch catalogs and fixtures
  - ATDF/SVD normalization and semantic validation
  - publication tests and `alloy-devices` family output
- Artifact layout remains family-scoped and stable; this change extends the matrix, not the
  contract shape
