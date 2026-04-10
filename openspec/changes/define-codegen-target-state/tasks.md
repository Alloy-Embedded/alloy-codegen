## Phase A: Boundary and contract lock

- [ ] A.1 Freeze the codegen/alloy boundary in docs, schemas, and artifact naming
- [ ] A.2 Define the final `alloy-devices` family-root contract:
      `manifest.json`, `metadata/`, `generated/`, `reports/`
- [ ] A.3 Define migration rules from the bootstrap artifact layout to the target contract
- [ ] A.4 Add regression checks preventing generated runtime behavior from entering the published
      artifact set

### Gate T1: Contract clarity
- [ ] T1.1 Every emitted artifact category is classified as `metadata`, `generated`, or `report`
- [ ] T1.2 Every foundational family proposal references the same contract shape
- [ ] T1.3 No codegen task that belongs to Alloy runtime behavior remains unclassified

## Phase B: Generic source-bundle architecture

- [ ] B.1 Implement named source-bundle resolution for repository, pack, and SDK-header source
      patterns
- [ ] B.2 Replace vendor-specific source override flags with generic source-ID overrides
- [ ] B.3 Extend source manifests with licensing/provenance data for every logical source ID
- [ ] B.4 Add regression fixtures for all three foundational source patterns
- [ ] B.5 Make source selection and manifest generation byte-stable across repeated runs

### Gate T2: Generic source model
- [ ] T2.1 ST repository-backed sources pass on the generic source-bundle model
- [ ] T2.2 Microchip pack-backed sources pass on the same model
- [ ] T2.3 NXP SDK-backed sources pass on the same model
- [ ] T2.4 No new top-level vendor-specific source flag is required for foundational vendors

## Phase C: Canonical IR completion

- [ ] C.1 Add explicit `ip_blocks` modeling keyed by `ip_name + ip_version`
- [ ] C.2 Complete package and package-pin modeling, including physical pin positions and variant
      identity
- [ ] C.3 Complete pin constraint modeling, including reserved/NC/debug constraints where known
- [ ] C.4 Complete interrupt modeling for vector, line, peripheral ownership, and aliases
- [ ] C.5 Complete memory-region and startup-descriptor modeling
- [ ] C.6 Complete clock/reset/enable modeling
- [ ] C.7 Complete DMA request and route modeling
- [ ] C.8 Add documentation-link and upstream reference modeling
- [ ] C.9 Extend provenance so every canonical field can be traced to source and patch identity
- [ ] C.10 Add schema versioning and golden fixtures for the complete IR

### Gate T3: Complete IR domains
- [ ] T3.1 No publishability-critical domain remains represented only as opaque vendor blobs
- [ ] T3.2 All foundational families normalize into the same IR schema family without vendor forks
- [ ] T3.3 Golden fixtures exist for at least one publishable candidate family from each vendor

## Phase D: Validation completion

- [ ] D.1 Add validators for package-pin consistency and variant coverage
- [ ] D.2 Add validators for pin-function compatibility and connector-critical signal data
- [ ] D.3 Add validators for clock/reset ownership and enable semantics
- [ ] D.4 Add validators for DMA request routing and conflicts
- [ ] D.5 Add validators for interrupt/vector completeness
- [ ] D.6 Add validators for memory and startup-descriptor completeness
- [ ] D.7 Add validators for manifest/provenance completeness
- [ ] D.8 Expose machine-readable publishability reports at family and device scope

### Gate T4: Publishable family validator
- [ ] T4.1 The validator can answer whether a family is draft or publishable without manual review
- [ ] T4.2 Publish is blocked automatically for draft families
- [ ] T4.3 Validation coverage is reported per foundational family

## Phase E: Artifact and emitter completion

- [ ] E.1 Emit `manifest.json` at the family root
- [ ] E.2 Emit all target `metadata/` artifacts
- [ ] E.3 Emit all target `generated/` descriptor headers
- [ ] E.4 Emit startup descriptor artifacts in descriptor-only form
- [ ] E.5 Emit IP-version descriptor headers
- [ ] E.6 Emit package, interrupt, memory, RCC, and DMA descriptor headers
- [ ] E.7 Add artifact golden tests for all descriptor categories
- [ ] E.8 Add checks that generated C++ contains no public runtime behavior

### Gate T5: Descriptor-first artifact contract
- [ ] T5.1 All foundational artifact categories are emitted from the same validated IR revision
- [ ] T5.2 The final artifact set is byte-stable across repeated runs
- [ ] T5.3 No required Alloy hardware descriptor must be reconstructed from raw vendor inputs at
      runtime

## Phase F: Publication and `alloy-devices` contract

- [ ] F.1 Migrate publication to the final family-root layout
- [ ] F.2 Publish metadata, generated descriptors, and reports together
- [ ] F.3 Preserve deterministic publication records and no-op reruns
- [ ] F.4 Add CI checks for contract shape and content hashing
- [ ] F.5 Add release checks that published artifacts remain self-describing without access to the
      source checkout

### Gate T6: Stable publication contract
- [ ] T6.1 `alloy-devices` publication is deterministic and no-op when inputs are unchanged
- [ ] T6.2 The published tree is sufficient for Alloy consumption without local regeneration
- [ ] T6.3 Contract changes require a new approved proposal

## Phase G: Foundational ST closure

- [ ] G.1 Close `stm32g0` on the final contract
- [ ] G.2 Close `stm32f4` on the final contract
- [ ] G.3 Ensure both families publish from the generic source-bundle model
- [ ] G.4 Ensure both families emit the full descriptor target set
- [ ] G.5 Ensure both families pass the publishable-family validator

### Gate T7: ST publishable foundation
- [ ] T7.1 `stm32g0` is publishable on the final contract
- [ ] T7.2 `stm32f4` is publishable on the final contract
- [ ] T7.3 Both complete at least two stable publication cycles without contract change

## Phase H: Foundational Microchip closure

- [ ] H.1 Close `same70` on the final contract using the generic source-bundle model
- [ ] H.2 Complete DFP-backed package/pin/interrupt/clock/DMA normalization
- [ ] H.3 Emit the full descriptor target set for `same70`
- [ ] H.4 Ensure one Alloy consumer path builds from published `same70` artifacts only

### Gate T8: Microchip publishable foundation
- [ ] T8.1 `same70` is publishable on the final contract
- [ ] T8.2 `same70` completes at least two stable publication cycles without contract change

## Phase I: Foundational NXP closure

- [ ] I.1 Close `imxrt1060` on the final contract using the generic source-bundle model
- [ ] I.2 Complete SDK-header-backed connectivity normalization
- [ ] I.3 Emit the full descriptor target set for `imxrt1060`
- [ ] I.4 Ensure one Alloy consumer path builds from published `imxrt1060` artifacts only

### Gate T9: NXP publishable foundation
- [ ] T9.1 `imxrt1060` is publishable on the final contract
- [ ] T9.2 `imxrt1060` completes at least two stable publication cycles without contract change

## Phase J: Vendor-4 admission

- [ ] J.1 Add CI rule preventing vendor-4 implementation branches from merging before gates
      `T7`, `T8`, and `T9` are all closed
- [ ] J.2 Document the vendor-admission checklist for future vendors
- [ ] J.3 Require any vendor-4 proposal to declare which source pattern it uses and why the
      existing generic source-bundle model is sufficient

### Gate T10: Expansion readiness
- [ ] T10.1 ST, Microchip, and NXP each have at least one publishable family on the same contract
- [ ] T10.2 No foundational family requires final-stage emitter or publish exceptions
- [ ] T10.3 Only after `T10.1` and `T10.2` pass may vendor 4 enter active implementation
