## Phase 0: Vendor admission and source registration

- [x] 0.1 Add `nxp` as a canonical vendor key in the device registry
- [x] 0.2 Register the `imxrt1060` family with bootstrap devices `mimxrt1062` and `mimxrt1064`
- [x] 0.3 Register the family source bundle as `nxp-mcux-soc-svd + nxp-mcux-sdk`
- [x] 0.4 Add regression coverage proving existing ST and Microchip source-bundle resolution is
      unchanged

### Gate N1: Source admission
- [x] N1.1 Resolve the two bootstrap devices reproducibly from both official NXP repositories
- [x] N1.2 Record repository revision, selected device-local file paths, and logical source IDs in
      source manifests
- [x] N1.3 Add fixtures and repeated-run tests for byte-stable source selection

## Phase 1: Source adapters and fixtures

- [x] 1.1 Implement source selection for `nxp-mcux-soc-svd`
- [x] 1.2 Implement source selection for `nxp-mcux-sdk`
- [x] 1.3 Add fixtures for representative SVD and SDK-header subsets for `mimxrt1062` and
      `mimxrt1064`
- [x] 1.4 Add tests proving deterministic selection of the device SVD and SDK pin-function header

### Gate N2: Header-to-IR closure
- [x] N2.1 Parse SDK pin-function tuples for both bootstrap devices into canonical signal facts
- [x] N2.2 Commit golden canonical fixtures for both devices
- [x] N2.3 Confirm no required pin connectivity fact remains only as a raw header string

## Phase 2: Composite normalization and patches

- [x] 2.1 Implement header parser support for `fsl_iomuxc.h`
- [x] 2.2 Normalize SDK macro tuples into canonical pin, signal, mux, and daisy data
- [x] 2.3 Merge SVD register and interrupt data with the SDK-derived connectivity model
- [x] 2.4 Add `patches/nxp/imxrt1060/family.json` with peripheral CCM clock-gate metadata
- [x] 2.5 Add device overlays for `mimxrt1062` and `mimxrt1064`
- [x] 2.6 Add normalization tests covering naming alignment between SVD peripherals and SDK signal
      names

### Gate N3: Semantic closure
- [x] N3.1 Validate pin-function connectivity with zero critical conflicts
- [x] N3.2 Validate SVD/SDK peripheral instance alignment with zero critical conflicts
- [x] N3.3 Validate interrupt topology with zero critical conflicts
- [x] N3.4 Model and validate clock/enable semantics required for publication, or block
      publication explicitly until closed
- [x] N3.5 Model and validate DMA semantics required for publication, or block publication
      explicitly until closed

## Phase 3: Emission, publication, and Alloy consumption

- [x] 3.1 Emit `nxp/imxrt1060` metadata and generated C++ artifacts using the existing contract
- [x] 3.2 Publish `nxp/imxrt1060` artifacts into `alloy-devices`
- [x] 3.3 Add emitted artifact golden tests for `mimxrt1062`
- [x] 3.4 Add one Alloy consumer smoke path that builds from published `nxp/imxrt1060` artifacts
      only
- [x] 3.5 Add CI coverage for validate and publish on the NXP family

### Gate N4: Publication readiness
- [x] N4.1 Confirm repeated publication runs are byte-stable and no-op when inputs are unchanged
- [x] N4.2 Confirm one Alloy consumer path builds from published `nxp/imxrt1060` artifacts only
- [x] N4.3 Confirm both bootstrap devices pass the full publishable family gate

## Phase 4: Family admission cleanup

- [x] 4.1 Document NXP source provenance and source selection strategy
- [x] 4.2 Mark `nxp/imxrt1060` as supported only after Gates N1-N4 are closed
- [x] 4.3 Keep additional NXP families blocked until `imxrt1060` completes at least two stable
      publication cycles without contract changes
