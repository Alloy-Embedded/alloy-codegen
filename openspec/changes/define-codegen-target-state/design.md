## Context

The project now has three layers of understanding:

1. a product direction for Alloy
   - bring-up quality over breadth
   - compile-time-safe peripheral connection
   - clear simple/expert API split

2. a codegen architecture
   - `fetch -> patch -> normalize -> validate -> emit -> publish`
   - canonical IR as the center
   - `alloy-devices` as a published artifact repository

3. active family proposals
   - ST bootstrap families already proven
   - Microchip via DFP
   - NXP via SDK-backed structured sources

What is missing is the end-state contract that says which parts of the system the codegen owns
forever and which parts belong to Alloy forever.

This proposal is that contract.

It does not replace the vendor-family proposals. Instead, it becomes the umbrella target they
must converge on.

## Goals / Non-Goals

Goals:
- Define the full target-state responsibilities of `alloy-codegen`
- Define the complete canonical IR domains needed by the future Alloy architecture
- Define the final artifact families and directory contract expected in `alloy-devices`
- Keep generated outputs descriptor-first and auditable
- Require three vendor shapes to pass before vendor 4 enters implementation
- Make the division between generated hardware facts and handwritten behavior explicit

Non-Goals:
- Rewriting the `alloy` runtime/HAL in this proposal
- Locking the exact syntax of every generated C++ header in advance
- Supporting every vendor source pattern immediately
- Turning `alloy-codegen` into a board framework or driver library
- Making vendor breadth a goal before the foundational vendor set proves the architecture

## System Boundary

### `alloy-codegen` owns

`alloy-codegen` owns facts, descriptors, provenance, and publication:

- upstream source acquisition
- patch application
- canonical normalization
- validation and gates
- machine-readable metadata
- generated C++ hardware descriptors
- artifact manifests and publication records

That means it owns:
- *what hardware exists*
- *how it is connected*
- *how it is identified*
- *which source and patch produced each fact*

### `alloy` owns

`alloy` owns behavior, policy, and user experience:

- public HAL APIs
- `simple` and `expert` layers
- drivers and policies
- `connect()` API surface
- ownership/tokens/singletons
- runtime state machines
- startup/runtime algorithms
- boards, BSP helpers, and examples

That means it owns:
- *how the user asks for hardware*
- *how resource ownership is enforced*
- *how peripherals are initialized and used*

### Boundary rule

`alloy-codegen` may generate translation units or headers when needed for low-level startup or
descriptor exposure, but those generated artifacts must remain *descriptor-oriented*. They may
declare tables, vectors, addresses, names, constants, and compile-time compatibility data. They
must not own public runtime APIs, driver logic, or behavioral policy.

## Target-State Source Model

The source model must be generic across at least three upstream shapes:

1. repository + structured metadata companion
   - example: ST `cmsis-svd-data + stm32-open-pin-data`

2. pack archive + deterministic extracted tree
   - example: Microchip DFP `(.atpack -> ATDF + SVD)`

3. repository + SDK-delivered structured headers
   - example: NXP `mcux-soc-svd + mcux-sdk`

The pipeline therefore standardizes on **named source bundles**:

- every `(vendor, family)` declares one or more logical source IDs
- every source ID has provenance and version identity
- CLI overrides address sources by source ID, not by vendor-specific flags

This model must remain stable when vendor 4 arrives.

## Canonical IR Target

The complete IR target is larger than the bootstrap implementation. It must cover:

### Identity and provenance
- vendor
- family
- device
- package
- source identities and revisions
- patch identities
- field-level provenance

### Device topology
- device variants
- package variants
- pins and package positions
- pin constraints and reserved pins

### Connectivity
- pin signals
- alternate functions / mux selectors
- peripheral instance ownership
- input daisy / route selectors where relevant
- compatibility tables needed for generated connector logic

### Peripheral modeling
- peripheral instances
- `ip_name`
- `ip_version`
- IP block definitions deduplicated by version
- base addresses and address spaces

### System integration domains
- interrupts and vector-table data
- memory regions and startup-related sections
- clock/reset/enable relationships
- DMA request routing
- documentation links and upstream references

The design goal is simple: the future Alloy runtime should be able to answer all hardware
questions from canonical descriptors, not from raw vendor sources and not from ad hoc handwritten
tables.

## Target-State Published Artifacts

The final `alloy-devices` contract is descriptor-first and split into three families of output.

### 1. `metadata/`

Machine-readable, stable artifacts for tooling and validation:

- `manifest.json`
- `metadata/family-index.json`
- `metadata/family-connectivity.json`
- `metadata/ip-blocks.json`
- `metadata/packages.json`
- `metadata/interrupt-map.json`
- `metadata/memory-map.json`
- `metadata/clock-reset-map.json`
- `metadata/dma-map.json`
- `metadata/docs.json`
- `metadata/devices/<device>.json`

### 2. `generated/`

C++ descriptor artifacts for Alloy consumption:

- `generated/peripherals/<peripheral>.hpp`
- `generated/ip/<ip-version>.hpp`
- `generated/signal_map.hpp`
- `generated/rcc_map.hpp`
- `generated/dma_map.hpp`
- `generated/interrupt_map.hpp`
- `generated/memory_map.hpp`
- `generated/package_map.hpp`
- `generated/devices/<device>/register_map.hpp`
- `generated/devices/<device>/pin_functions.hpp`
- `generated/devices/<device>/startup_descriptors.hpp`
- `generated/devices/<device>/startup_vectors.cpp` or equivalent descriptor-only translation unit

### 3. `reports/`

Validation and coverage outputs:

- `reports/validation-summary.json`
- `reports/coverage.json`
- `reports/publication-record.json`

The exact filenames may still evolve during implementation, but the contract shape must stay:
`metadata/`, `generated/`, `reports/`, plus a family root manifest.

## Descriptor-First Emission

The codegen must emit descriptors, not drivers.

Examples of acceptable generated C++:
- peripheral base-address tables
- pin-function tables
- typed signal descriptors
- compile-time compatibility tables
- startup vector descriptors
- IP-version descriptor headers

Examples of unacceptable generated C++:
- `Uart` runtime classes
- `Spi` transaction logic
- ownership/token systems
- board initialization policy
- public `connect()` behavior implementation

Those belong in Alloy.

## Validation and Gates

### Family publishable gate

A family is publishable only when:
- source inputs are reproducible
- normalization is complete for connectivity-critical domains
- validation is green for pins, clocks, DMA, interrupts, memory, and packages
- generated artifacts are byte-stable
- one Alloy consumer path builds from published artifacts only

### Foundational vendor set

Before vendor 4 enters active implementation, the following must each have at least one
publishable family on the same contract:

- ST
  - `stm32g0`
  - `stm32f4`

- Microchip
  - `same70`

- NXP
  - `imxrt1060`

This is not about market breadth. It is a genericity test:
- repository+metadata source pattern
- pack/extract source pattern
- SDK-header source pattern

If the same IR, validators, emitters, and publication contract survive those three, the base is
strong enough to admit vendor 4 responsibly.

### Vendor 4 admission gate

Vendor 4 is blocked until:
- all foundational families are publishable
- each has completed at least two stable publication cycles without artifact-contract change
- no family-specific exceptions are required in the final emit or publish stages

## Relationship to Existing Family Proposals

The active `add-microchip-dfp-family` and `add-nxp-mcux-family` changes remain valid, but they
are now subordinate to this target-state contract.

They must converge on:
- the named source-bundle model
- the complete IR target
- the descriptor-first artifact contract
- the publishable-family gates

If a family proposal cannot converge without a family-specific exception at the contract level,
the correct action is to harden the generic architecture first, not to special-case the family.

## Implementation Phases

### Phase A: Boundary and contract lock
- freeze the codegen/alloy boundary
- freeze the descriptor-first publication target
- freeze the foundational vendor set gate

### Phase B: Source and IR completion
- finish generic source bundles
- finish the complete IR domains
- finish field-level provenance and source manifests

### Phase C: Validator completion
- finish semantic validation for packages, pins, clocks, DMA, interrupts, memory, startup data
- make publishability machine-readable

### Phase D: Artifact completion
- emit the full metadata set
- emit the full descriptor C++ set
- migrate bootstrap artifact layout to the target contract

### Phase E: Foundational family closure
- close ST target families
- close Microchip target family
- close NXP target family

### Phase F: Expansion readiness
- prove stability across reruns and releases
- only then admit vendor 4

## Risks / Trade-offs

- **Risk: output contract becomes too broad**
  Mitigation: keep outputs descriptor-first and ban runtime behavior from codegen

- **Risk: family-specific pressure distorts the IR**
  Mitigation: require three-vendor convergence before broader expansion

- **Risk: package/clock/DMA completeness is harder than register generation**
  Mitigation: treat those domains as first-class publishability gates, not optional extras

- **Risk: publication layout churn breaks Alloy migration**
  Mitigation: codify the final directory contract now and use explicit migration phases

- **Risk: codegen starts to absorb runtime concerns**
  Mitigation: formalize the codegen/alloy boundary as a requirement, not an opinion

## Open Questions

- Should `reports/coverage.json` be family-scoped only, or also device-scoped when coverage
  differs by package variant?
- Should `generated/ip/<ip-version>.hpp` contain only static descriptors, or also alias helpers
  for the Alloy trait layer?
