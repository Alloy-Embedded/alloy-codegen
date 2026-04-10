## Phase 0: Generic source-model refactor

- [ ] 0.1 Define the named-source bundle model used by `(vendor, family)` scopes
- [ ] 0.2 Add generic source override plumbing to context and CLI
- [ ] 0.3 Deprecate or remove vendor-specific auxiliary source flags in favor of named-source
      overrides
- [ ] 0.4 Add `microchip/same70` to the device registry using two DFP-confirmed representative
      devices, one of them matching the Alloy board target
- [ ] 0.5 Add regression coverage proving existing ST source resolution still works after the
      source-model refactor

### Gate M1: DFP source admission
- [ ] M1.1 Implement deterministic DFP pack selection for the two representative `same70`
      devices
- [ ] M1.2 Record source manifests for pack archive, extracted tree, and selected ATDF/SVD files
- [ ] M1.3 Add fixture coverage for repeated `fetch + extract` stability
- [ ] M1.4 Prove two consecutive runs with the same DFP input produce byte-identical source
      manifests and selected-file manifests

## Phase 1: Microchip DFP ingestion

- [ ] 1.1 Implement `sources/microchip_dfp.py` for pack resolution, extraction, and file
      selection
- [ ] 1.2 Add tests for local `.atpack` input, local extracted-tree input, and deterministic
      selection of device-specific ATDF/SVD files
- [ ] 1.3 Add fixtures for a reviewed extracted DFP subset covering the two bootstrap `same70`
      devices
- [ ] 1.4 Extend fetch-stage structured output and manifests to report named-source bundle inputs

### Gate M2: Composite IR closure
- [ ] M2.1 Normalize both bootstrap `same70` devices into the existing canonical IR schema
- [ ] M2.2 Confirm no new vendor-specific IR model or schema fork is introduced
- [ ] M2.3 Commit golden canonical fixtures for both devices
- [ ] M2.4 Confirm normalized provenance points to `microchip-dfp-pack` or
      `microchip-dfp-extract` for source-derived fields

## Phase 2: Composite ATDF + SVD normalization

- [ ] 2.1 Parse ATDF device/package/pin/signal/peripheral topology for `same70`
- [ ] 2.2 Merge SVD register and interrupt data into the same canonical peripheral model
- [ ] 2.3 Implement explicit alias/canonicalization rules for Microchip-specific names such as
      PIO/PMC/XDMAC
- [ ] 2.4 Add `patches/microchip/same70/family.json` and device overlays for the bootstrap
      devices
- [ ] 2.5 Add normalization tests for package variants and instance-name alignment between ATDF
      and SVD

### Gate M3: Semantic closure
- [ ] M3.1 Validate package/pin/signal connectivity with zero critical conflicts
- [ ] M3.2 Validate peripheral clock/enable ownership data for the publication scope with zero
      critical conflicts
- [ ] M3.3 Validate interrupt topology and numbering with zero critical conflicts
- [ ] M3.4 Model and validate DMA semantics required for publication, or explicitly block
      publication until the reviewed source/patch set closes the gap
- [ ] M3.5 Emit machine-readable validation reports showing Gate M3 pass/fail by device

## Phase 3: Emission, publication, and Alloy consumption

- [ ] 3.1 Emit `microchip/same70` metadata and generated C++ artifacts using the existing
      artifact contract
- [ ] 3.2 Publish `microchip/same70` outputs into `alloy-devices` without changing artifact
      layout semantics
- [ ] 3.3 Add emitted artifact golden tests for the board-target `same70` device
- [ ] 3.4 Add one Alloy consumer smoke path that builds from published `microchip/same70`
      artifacts only
- [ ] 3.5 Add CI coverage for `validate` and `publish` on the `same70` family

### Gate M4: Publication readiness
- [ ] M4.1 Confirm one Alloy consumer path builds from published `microchip/same70` artifacts
- [ ] M4.2 Confirm repeated publication runs are byte-stable and produce no-op commits when
      inputs are unchanged
- [ ] M4.3 Confirm the board-target `same70` device and one second package variant both pass the
      full publishable family gate

## Phase 4: Family admission cleanup

- [ ] 4.1 Document Microchip source provenance, licensing notes, and publication scope
- [ ] 4.2 Mark the `same70` family as supported only after Gates M1-M4 are closed
- [ ] 4.3 Keep additional Microchip families blocked until `same70` has at least two stable
      publication cycles without contract changes
