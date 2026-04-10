## Phase A: Connector-driven IR foundation

- [x] A.1 Define the new canonical route-driven connectivity model in the IR schema
- [x] A.2 Add `ip_block` and `capability` descriptor domains separate from peripheral instances
- [x] A.3 Add package, pad, and pin-constraint domains
- [x] A.4 Add interrupt, memory, startup, clock-lite, and DMA descriptor domains
- [x] A.5 Keep transitional compatibility with the bootstrap IR while new emitters are built
- [x] A.6 Add golden canonical fixtures exercising the new fields for ST, Microchip, and NXP

### Gate C1: IR completeness
- [ ] C1.1 No publishability-critical domain remains encoded only as `PinSignal.af_number`
- [x] C1.2 The same IR schema can represent ST, Microchip, and NXP connectivity without vendor
      forks
- [x] C1.3 Canonical fixtures exist for at least one family from each foundational vendor shape

## Phase B: Generic connector graph normalization

- [x] B.1 Define canonical `SignalEndpoint` identities per peripheral class
- [x] B.2 Normalize ST AF-based pinmux into `ConnectionCandidate` and `RouteOperation`
- [x] B.3 Normalize Microchip PIO/matrix-derived routing into the same route model
- [x] B.4 Normalize NXP mux/daisy/pad facts into the same route model
- [x] B.5 Add `ConnectionGroup` generation for valid multi-signal configurations
- [x] B.6 Add `RouteRequirement` generation for package, clock, reset, and source constraints
- [x] B.7 Record route-level provenance for every candidate, group, and operation

### Gate C2: Generic `connect()` data shape
- [x] C2.1 All foundational vendors normalize into the same route graph abstractions
- [x] C2.2 Connector candidates can be validated without inspecting raw vendor-specific blobs
- [x] C2.3 Every publishable family exposes at least one non-trivial multi-signal connection group

## Phase C: IP-version and capability completion

- [x] C.1 Define `ip_block` normalization keyed by `ip_name + ip_version`
- [x] C.2 Add capability descriptors shared by peripheral class and version
- [x] C.3 Add instance-level capability overlays for package- or instance-specific limits
- [x] C.4 Add validators ensuring capabilities can be resolved from descriptors alone
- [x] C.5 Add golden fixtures for versioned IP reuse across multiple devices

### Gate C3: Descriptor reuse by IP version
- [x] C3.1 At least one IP-version descriptor is reused across multiple devices in each supported
      vendor shape where the upstream data permit it
- [x] C3.2 Alloy-facing descriptors no longer infer capability from instance names alone

## Phase D: Package and pinout completion

- [x] D.1 Add package variants with physical pad positions and pad kinds
- [x] D.2 Add bonded/unbonded pad modeling per package variant
- [x] D.3 Add pin constraints such as analog-only, debug-only, wakeup-only, and NC
- [x] D.4 Add validators for package-to-pin consistency and variant coverage
- [x] D.5 Emit family package metadata and generated package descriptors

### Gate C4: Package-aware connectivity
- [x] C4.1 Connector validation can reject routes that are invalid in a selected package
- [x] C4.2 Published package metadata is sufficient to reconstruct the physical pinout

## Phase E: System descriptor completion

- [x] E.1 Add interrupt ownership, aliases, and vector-slot descriptors
- [x] E.2 Add memory-region descriptors with startup-relevant classification
- [x] E.3 Add startup copy/zero/vector descriptors separated from startup logic
- [ ] E.4 Add `ClockGraphLite` descriptors for enable, reset, parent selection, and source choice
- [ ] E.5 Add complete DMA controller/request/route/conflict descriptors
- [x] E.6 Add validators for all system descriptor families

### Gate C5: Publishable system descriptors
- [ ] C5.1 Startup data can be emitted without handwritten device-local tables
- [ ] C5.2 Clock, interrupt, memory, and DMA completeness are all machine-verifiable
- [ ] C5.3 Publish is blocked automatically when any required system descriptor domain is draft

## Phase F: Artifact contract upgrade

- [ ] F.1 Migrate emission to the final `metadata/`, `generated/`, and `reports/` family layout
- [x] F.2 Emit `metadata/ip-blocks.json`, `metadata/capabilities.json`, and `metadata/connectors.json`
- [x] F.3 Emit `generated/ip/<ip-version>.hpp`
- [x] F.4 Emit `generated/connector_tables.hpp`
- [x] F.5 Emit `generated/interrupt_map.hpp`, `generated/memory_map.hpp`, and `generated/package_map.hpp`
- [x] F.6 Emit `generated/clock_tree_lite.hpp` and the generalized clock/reset descriptors
- [x] F.7 Emit `generated/devices/<device>/startup_descriptors.hpp`
- [x] F.8 Emit descriptor-only startup vector translation units
- [x] F.9 Add artifact golden tests for every new descriptor family

### Gate C6: Descriptor-first artifact set
- [ ] C6.1 Every generated artifact category is descriptor-oriented and contains no runtime policy
- [ ] C6.2 The published family tree is self-describing without access to raw vendor sources
- [ ] C6.3 Repeated emission and publication are byte-stable

## Phase G: Alloy boundary and `connect()` contract

- [ ] G.1 Freeze the codegen-owned connector descriptor contract
- [ ] G.2 Explicitly document the Alloy-owned `connect()` responsibilities
- [ ] G.3 Add regression checks preventing runtime `connect()` behavior from entering generated code
- [ ] G.4 Add smoke-consumer coverage for the new generated descriptor families

### Gate C7: Clean codegen/runtime boundary
- [ ] C7.1 `alloy-codegen` emits facts and route data only
- [ ] C7.2 `alloy` is the only layer that owns runtime connection behavior and resource ownership

## Phase H: Foundational family migration

- [ ] H.1 Migrate `st/stm32g0` to the connector-driven contract
- [ ] H.2 Migrate `microchip/same70` to the same contract
- [ ] H.3 Migrate `st/stm32f4` to the same contract
- [ ] H.4 Complete `nxp/imxrt1060` on the same contract instead of the bootstrap model
- [ ] H.5 Add family publishability reports showing descriptor completeness across all four
      foundational families

### Gate C8: Foundational multi-vendor proof
- [ ] C8.1 ST, Microchip, and NXP all publish families using the same connector-driven descriptor
      contract
- [ ] C8.2 No foundational family requires vendor-specific emitter exceptions at publish time
- [ ] C8.3 Vendor 4 remains blocked until `C8.1` and `C8.2` are closed

## Phase I: Legacy cleanup

- [ ] I.1 Remove transitional emitter dependence on legacy AF-centric connectivity fields
- [ ] I.2 Remove obsolete bootstrap-only artifact names once Alloy migration is ready
- [ ] I.3 Update docs, fixtures, and workflows to reference the final descriptor contract only

### Gate C9: Legacy retirement
- [ ] C9.1 No publishable family depends on legacy bootstrap connectivity assumptions
- [ ] C9.2 The connector-driven descriptor model becomes the only supported contract
