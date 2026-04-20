## Context

The current `alloy-devices` remote tree already proves that the descriptor-first direction is
working:

- foundational families are emitted under `metadata/`, `generated/`, and `reports/`
- connectors, IP-version descriptors, package data, system descriptors, and startup data are all
  present
- the publish stage compiles a smoke consumer against the published tree

That is a strong milestone, but it is not the same thing as full contract completion.

The remaining gaps fall into three categories:

1. **C++ consumption parity**
   - JSON metadata is richer and easier to consume than the current generated C++ entrypoints
   - some generated C++ is still too shallow for the future Alloy runtime to stay
     descriptor-driven without reaching back into JSON or handwritten glue

2. **publication truth**
   - validation, coverage, and publish do not yet form one strict binary notion of
     "publishable family"
   - a family can still be materialized into `alloy-devices` while its own coverage report says
     one or more devices are not publishable

3. **contract drift**
   - the documentation still references bootstrap-era artifacts
   - the vendor-admission gate is not yet tied tightly enough to contract completeness

This proposal is the "last mile" for the foundational contract. It is intentionally not about
adding breadth.

## Goals / Non-Goals

### Goals

- Make the generated C++ contract strong enough that future Alloy consumption can stay
  descriptor-first without parsing JSON for publishability-critical hardware questions
- Make publication impossible when coverage or per-device readiness still says the family is
  incomplete
- Align the documented artifact contract with the emitted artifact contract
- Tighten foundational vendor admission so vendor 4 remains blocked until the foundational set is
  complete on the hardened contract
- Close the last foundational-family holes that still leave a published family semantically
  incomplete

### Non-Goals

- Generating runtime driver classes or behavioral `connect()` logic
- Reintroducing a legacy register/bitfield-heavy codegen model
- Expanding to vendor 4
- Redesigning the canonical IR again
- Replacing the metadata JSON artifacts with C++ only

## Decisions

### Decision 1: C++ parity means direct device-scoped descriptor entrypoints

The missing piece is not "more JSON". It is a stronger C++ surface for the Alloy runtime.

The generator SHALL emit four device-scoped entrypoints in addition to the family-level maps:

- `generated/devices/<device>/device_descriptor.hpp`
- `generated/devices/<device>/pins.hpp`
- `generated/devices/<device>/peripheral_instances.hpp`
- `generated/devices/<device>/capability_overlays.hpp`

These files remain descriptor-only. They do not implement runtime behavior. Their job is to give
Alloy a stable, direct C++ entrypoint for:

- selected package identity
- device-level pin and bonding facts
- device-level peripheral instance facts
- package- and instance-scoped capability overlays
- references into family-level connector/system descriptor tables

This keeps the boundary clean:
- `alloy-devices` owns facts in metadata and generated descriptors
- `alloy` owns runtime behavior over those facts

### Decision 2: `register_map.hpp` remains descriptor-only

The current `register_map.hpp` only emits peripheral base tables. That is acceptable if the rest
of the descriptor contract is complete.

This proposal does **not** require a return to a full register/bitfield generation model.
If the Alloy runtime later needs more low-level descriptor depth, that depth must still be added
as descriptors, not as handwritten driver logic or behavioral code generation.

### Decision 3: publication truth must be single-source and strict

The repo cannot claim "publishable" and "not publishable" for the same family at the same time.

Publication SHALL be blocked unless all of the following are true for the requested scope:

- validation is passing
- no required system-descriptor domain is draft
- `coverage.all_devices_publishable` is true
- every targeted device reports `publishable=true`

The publish stage, coverage report, validation summary, and publication record must agree on this
state.

### Decision 4: foundational-family completeness is part of the contract

The foundational set is:

- `st/stm32g0`
- `st/stm32f4`
- `microchip/same70`
- `nxp/imxrt1060`

This proposal treats any remaining domain gap in those families as a contract gap, not as a
"future enhancement". If a foundational family still reports an incomplete domain, the pipeline is
not 100% complete.

That means this change includes closing those remaining family-level holes, not just tightening
generic infra.

### Decision 5: documentation is a tested part of the contract

The published artifact contract is a product interface. The docs that describe it must stay in
lockstep with the emitted tree.

Bootstrap-era names such as:

- `generated/signal_map.hpp`
- `generated/devices/<device>/pin_functions.hpp`
- `generated/devices/<device>/startup.cpp`

must be removed from the active contract docs once they are no longer emitted.

The repo should have regression coverage that fails if:

- active docs reference retired artifact names
- active docs omit required artifact families

## Resulting Artifact Contract

### Required family root

- `artifact-manifest.json`

### Required metadata artifacts

- `metadata/family-index.json`
- `metadata/family-connectivity.json`
- `metadata/ip-blocks.json`
- `metadata/capabilities.json`
- `metadata/packages.json`
- `metadata/connectors.json`
- `metadata/system-descriptors.json`
- `metadata/devices/<device>.json`

### Required generated family-level descriptors

- `generated/ip/<ip-version>.hpp`
- `generated/peripherals/*.hpp`
- `generated/connector_tables.hpp`
- `generated/rcc_map.hpp`
- `generated/dma_map.hpp`
- `generated/interrupt_map.hpp`
- `generated/memory_map.hpp`
- `generated/package_map.hpp`
- `generated/clock_tree_lite.hpp`

### Required generated device-level descriptors

- `generated/devices/<device>/register_map.hpp`
- `generated/devices/<device>/device_descriptor.hpp`
- `generated/devices/<device>/pins.hpp`
- `generated/devices/<device>/peripheral_instances.hpp`
- `generated/devices/<device>/capability_overlays.hpp`
- `generated/devices/<device>/startup_descriptors.hpp`
- `generated/devices/<device>/startup_vectors.cpp`

### Required reports

- `reports/validation-report.json`
- `reports/validation-summary.json`
- `reports/coverage.json`
- `reports/publication-record.json`

## Gates

### Gate K1: Device-scoped C++ consumption parity

Closed when:

- every foundational family emits the required device-scoped descriptor entrypoints
- Alloy smoke-consumer coverage can build from the generated C++ contract without reading metadata
  JSON for publishability-critical facts

### Gate K2: Publication consistency

Closed when:

- publish is blocked whenever family coverage is not publishable
- publish is blocked whenever any targeted device is not publishable
- no remote `alloy-devices` tree can be produced with coverage that still says
  `all_devices_publishable=false`

### Gate K3: Foundational contract completeness

Closed when:

- `st/stm32g0` is contract-complete
- `st/stm32f4` is contract-complete
- `microchip/same70` is contract-complete
- `nxp/imxrt1060` is contract-complete

For this gate, "contract-complete" means:

- all required descriptor domains are publishable
- all required artifacts are emitted
- publication is permitted by the hardened rules

### Gate K4: Contract-document synchronization

Closed when:

- active docs describe only emitted artifact families
- active docs include every required emitted artifact family
- regression checks prevent stale artifact names from re-entering the docs

## Risks / Trade-offs

- Adding device-scoped C++ entrypoints increases artifact count and golden-fixture churn
  - Mitigation: keep these headers aggregate and descriptor-only, not per-candidate micro-files
- Tightening publish may temporarily stop publication for a foundational family that currently
  "works well enough"
  - Mitigation: treat that as intended pressure to close the real completeness gap
- Some family-specific cleanup may be needed to satisfy the hardened contract
  - Mitigation: keep those fixes inside normalization/patch/validation, not inside emitters

## Migration Plan

1. Add the missing device-scoped descriptor headers and smoke-consumer coverage
2. Harden publication against coverage and per-device readiness
3. Close foundational-family domain gaps still preventing true publishability
4. Update contract docs and add regression coverage for doc drift
5. Tighten vendor-admission rules to depend on the hardened contract

## Open Questions

- Whether `generated/peripherals/*.hpp` should remain family-level only or also gain
  device-scoped siblings for non-GPIO classes
- Whether a dedicated machine-readable `contract-status.json` report would add value beyond the
  current `coverage.json` and `validation-summary.json`
