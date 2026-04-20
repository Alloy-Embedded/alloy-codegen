## Context

`type-runtime-backend-contract` established the first typed bridge between
`alloy-devices` and the Alloy runtime:
- backend schema IDs now exist
- per-device register offsets now come from upstream source data
- runtime profile and peripheral-instance headers now exist

That change deliberately left a compatibility tail:
- `target` and `value` strings still exist beside typed fields
- connector tables still flatten lists through comma-separated strings
- clock/reset/interrupt/DMA bindings still use textual identifiers more than typed
  references
- fields and bit ranges are still missing from the emitted contract

This follow-up removes that tail and finishes the contract so Alloy can dispatch by schema
and operate only on generated descriptors.

## Goals / Non-Goals

- Goals:
  - eliminate runtime dependence on family-name checks and string parsing
  - expose typed register and field descriptors for runtime-owned subsystems
  - expose typed bindings for interrupt, DMA, clock, reset, selector, and pinmux domains
  - keep vendor growth tied to reusable backend schemas rather than family-specific code
- Non-Goals:
  - emitting a complete SPIR-like register DSL for every vendor feature
  - replacing all JSON metadata with C++ headers
  - redesigning Alloy runtime code in this change

## Decisions

### Decision: Add typed descriptor IDs for every runtime-owned reference domain

The contract SHALL expose stable generated IDs for:
- peripheral instances
- registers
- register fields
- clock gates
- resets
- selectors
- interrupt bindings
- DMA bindings
- route requirements
- route operations

This lets Alloy keep human-readable names for diagnostics while using typed identifiers for
backend execution and IDE-friendly compile-time APIs.

### Decision: Model route operations as typed hardware references

Route operations SHALL stop depending on textual target parsing. A typed operation will
identify:
- operation kind
- schema ID
- subject kind and subject ID
- target reference kind
- target reference ID
- optional integer payload

Examples of target references:
- register ref
- field ref
- pinmux ref
- selector ref
- clock gate ref

The legacy string fields may remain temporarily for metadata/debug output, but publication
of foundational families SHALL require the typed references to be sufficient on their own.

### Decision: Emit field descriptors, not only register offsets

Register offsets alone are not enough. The runtime must not hand-code field positions for
`CR1`, `MODER`, `AFRL`, `ABCDSR`, `IOMUXC`, or equivalent blocks. The codegen SHALL emit
normalized field descriptors for runtime-owned schemas so Alloy can implement MMIO writes
through generated data only.

### Decision: Replace CSV payloads with structured arrays

CSV lists are compact but not acceptable as a long-term boundary. The emitted C++ contract
SHALL use arrays of typed descriptors for:
- interrupt bindings
- DMA bindings
- capability overlays per peripheral
- candidate/group membership
- selector parent options

Human-readable joined strings may still exist in JSON metadata for diagnostics, but not as
the primary runtime interface.

### Decision: Vendor admission depends on schema reuse, not family count

A new family/vendor is admissible only if:
- it reuses existing runtime schema IDs with no Alloy runtime changes, or
- it introduces a new schema with a localized, explicit runtime backend implementation

Families that only work by adding string parsing or family branches in Alloy SHALL fail
admission.

## Target Artifact Additions

The runtime contract SHALL add or strengthen these artifacts:
- `generated/runtime_profiles.hpp`
  - schema rows remain, but point to typed reference domains
- `generated/devices/<device>/device_descriptor.hpp`
  - include typed counts and typed binding coverage
- `generated/devices/<device>/peripheral_instances.hpp`
  - include typed IDs for interrupt, DMA, clock, reset, and selector bindings
- `generated/devices/<device>/register_map.hpp`
  - include typed register IDs and per-register offsets
- `generated/devices/<device>/register_fields.hpp`
  - new header with field IDs, bit offsets, widths, and access shape
- `generated/devices/<device>/interrupt_bindings.hpp`
  - new header with typed interrupt-binding descriptors
- `generated/devices/<device>/dma_bindings.hpp`
  - new header with typed DMA-binding descriptors
- `generated/connector_tables.hpp`
  - replace CSV payloads with structured arrays and typed operation targets
- `generated/clock_tree_lite.hpp`
  - replace textual gate/reset/selector cross-links with typed IDs

## Risks / Trade-offs

- Parsing register fields from upstream sources will be uneven across vendors.
  - Mitigation: require full field coverage only for runtime-owned backend schemas in the
    foundational families.
- The emitted C++ surface will grow.
  - Mitigation: prefer shared IDs and compact descriptor arrays over template-heavy output.
- Some current tests and fixtures will churn heavily.
  - Mitigation: keep fixture updates localized to foundational families until Alloy consumes
    the new contract.

## Migration Plan

1. Extend raw-source and canonical IR models with register-field and binding descriptors.
2. Emit typed IDs and structured arrays beside current transitional payloads.
3. Update validation to require typed sufficiency for foundational runtime schemas.
4. Remove foundational dependence on CSV/textual interpretations from emitted headers.
5. Hand the new contract to Alloy and start the schema-dispatch runtime migration there.

## Open Questions

- Whether to emit one shared `runtime_refs.hpp` per family or keep IDs local to each device
  header set.
- Whether interrupt binding IDs should point to vector slots directly or through a separate
  interrupt-binding descriptor layer.
