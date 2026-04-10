## Phase 0: Foundation and contracts

- [x] 0.1 Finalize the canonical architecture and stage boundaries in OpenSpec
- [x] 0.2 Define the initial project context and repository conventions
- [x] 0.3 Lock `stm32g0` as the bootstrap family for the first implementation wave
- [x] 0.4 Define the canonical IR schema versioning strategy
- [x] 0.5 Define artifact manifests and publication metadata shape

### Gate A: Source Bootstrap
- [x] A.1 At least two representative `stm32g0` devices can be fetched reproducibly
- [x] A.2 Source manifests capture origin, revision, and fetch metadata for both raw and
      patched inputs
- [x] A.3 Patches apply deterministically and are tracked as explicit inputs
- [x] A.4 Two consecutive `fetch + patch` runs with unchanged upstream revisions are
      byte-stable

## Phase 1: Source ingestion and patching

- [x] 1.1 Implement source adapters for the bootstrap family
- [x] 1.2 Implement a patch system for corrected upstream data
- [x] 1.3 Add fixtures for raw and patched source inputs
- [x] 1.4 Add tests for reproducible patch application
- [x] 1.5 Emit source manifests and patch manifests

### Gate B: Canonical IR Stability
- [x] B.1 At least three representative `stm32g0` devices normalize fully into the
      canonical IR
- [x] B.2 The IR schema is versioned and validated in CI
- [x] B.3 Golden fixtures exist for normalized device output
- [x] B.4 No critical normalized fields remain hidden inside vendor-specific opaque blobs
- [x] B.5 No required canonical fields in device, pin, AF, RCC, IRQ, DMA, or memory domains
      rely on placeholder sentinel values

## Phase 2: Canonical IR and normalization

- [x] 2.1 Implement canonical models for devices, packages, pins, IP blocks, interrupts,
      DMA, RCC, and memory regions
- [x] 2.2 Implement vendor-specific normalization into the canonical IR
- [x] 2.3 Record provenance for normalized facts
- [x] 2.4 Add golden tests for normalized device data
- [x] 2.5 Add schema evolution rules and compatibility tests

### Gate C: Semantic Correctness
- [x] C.1 Pin/package/connectivity validation reports zero critical errors for the bootstrap family
- [x] C.2 RCC/clock/reset ownership validates with zero critical conflicts
- [x] C.3 IRQ mapping validates with zero critical conflicts
- [x] C.4 DMA routing validates with zero critical conflicts
- [x] C.5 Validation reports are machine-readable and CI-gating
- [x] C.6 Published-scope devices contain zero unresolved TODO placeholders in
      connectivity-critical domains
- [x] C.7 At least one low-end and one higher-feature `stm32g0` device pass the full
      semantic suite

## Phase 3: Validation engine

- [x] 3.1 Implement schema validation for all intermediate and canonical artifacts
- [x] 3.2 Implement semantic validators for pins, signals, RCC, IRQ, DMA, and packages
- [x] 3.3 Implement validation report aggregation and severity handling
- [x] 3.4 Integrate validation outputs into CLI and CI

### Gate D: Artifact Contract
- [x] D.1 Metadata and generated C++ are emitted from the same validated IR revision
- [x] D.2 Published artifacts include generator version, schema version, source manifest,
      patch manifest, and build metadata
- [x] D.3 Artifact layout is stable and documented
- [x] D.4 At least one Alloy consumer path builds successfully from published artifacts
- [x] D.5 Repeated emission with unchanged validated inputs is byte-stable for both metadata
      and generated C++ artifacts

## Phase 4: Emission and publication

- [x] 4.1 Implement metadata emitters for canonical device exports
- [x] 4.2 Implement generated C++ emitters for Alloy consumption
- [x] 4.3 Implement artifact manifests and publication summaries
- [x] 4.4 Implement `alloy-devices` publication flow
- [x] 4.5 Add golden tests for emitted metadata and generated code
- [x] 4.6 Implement CI automation that can commit and push changed published artifacts into
      the real `alloy-devices` repository
- [x] 4.7 Document remote publication credentials, no-op behavior, and release workflow

### Gate E: Family Expansion
- [x] E.1 Gate D passes in CI for the bootstrap family
- [x] E.2 Regression fixtures protect already-supported families
- [x] E.3 Family-specific logic is isolated to adapters and normalizers
- [x] E.4 Repeated publication runs are deterministic
- [x] E.5 The bootstrap family completes at least two successful publication cycles without
      artifact contract changes
- [ ] E.6 Only after E.1-E.5 pass may a second major family enter active implementation

## Phase 5: Multi-family expansion

- [ ] 5.1 Add the second major family using the same pipeline architecture
- [ ] 5.2 Add cross-family regression tests
- [ ] 5.3 Verify schema reuse rather than family-specific schema forks
- [ ] 5.4 Keep publication and artifact contracts unchanged unless a new approved proposal exists
