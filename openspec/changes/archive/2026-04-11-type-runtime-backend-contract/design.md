## Context

`alloy-codegen` already emits canonical connectivity, clock, DMA, startup, and package data.
That was enough to bootstrap `connect()` and basic runtime bring-up, but the contract is still
too weak in two important places:

1. Backend dispatch still requires family-specific interpretation in `alloy`.
2. Runtime register access still depends on handwritten offsets because `alloy-devices` does
   not publish normalized register offsets in the new contract.

The change therefore has to strengthen the runtime boundary, not just add another helper file.

## Goals

- Publish backend schema identifiers that let Alloy dispatch by schema instead of family.
- Publish register blocks and register offsets from upstream source data.
- Publish typed route operations that no longer require parsing text targets in the runtime.
- Keep the contract multi-vendor and reusable across ST, Microchip, and NXP.

## Non-Goals

- Reintroduce the old handwritten `generated/registers` and `generated/bitfields` model.
- Encode complete field-level register semantics for every runtime feature in this change.
- Rewrite Alloy runtime consumption in this repo; this change only strengthens the
  `alloy-devices` side of the boundary.

## Decisions

### Decision 1: Dispatch by backend schema, not family

The generated contract will publish stable backend schema identifiers for the subsystems that
the runtime executes directly:

- peripheral backend schema
- pinmux backend schema
- clock/reset backend schema
- DMA backend schema when present

These schema IDs are generated facts owned by `alloy-codegen`. Alloy will eventually dispatch
small backends by schema family, so a new MCU family that reuses an existing schema can land
without handwritten family detection in the runtime.

### Decision 2: Register offsets belong in `alloy-devices`

Register offsets and block layouts must be derived from upstream source data and published in
the generated artifacts. Alloy may still choose to use a narrow subset of those registers, but
it must not carry handwritten offsets for STM32 GPIO/UART or any future backend.

This change adds canonical register descriptors to the IR and emits device-scoped register maps
that include per-register offsets.

### Decision 3: Route operations become typed runtime operations

The current route operation shape:

- `kind`
- `target`
- `value`

is too weak because `target` is free-form text. The new shape retains a human-readable ID, but
the runtime-facing content becomes typed:

- `schema_id`
- `subject_kind`
- `subject_id`
- `register_ref`
- `value_int`

This makes runtime consumption deterministic and removes string parsing from Alloy.

## Data Model

### New canonical entities

- `RegisterDescriptor`
  - canonical peripheral owner
  - register name
  - offset in bytes
  - access mode
  - register width in bits
- `BackendSchemaDescriptor`
  - schema ID
  - subsystem
  - vendor class / runtime family
- typed route operation fields
  - schema ID
  - subject kind
  - subject ID
  - optional register reference
  - optional integer payload

### Extended entities

- `PeripheralInstance`
  - add `backend_schema_id`
- `IpBlockDefinition`
  - add `backend_schema_id`

## Artifact Contract

The generated contract must expose at least:

- `generated/runtime_profiles.hpp`
- `generated/devices/<device>/peripheral_instances.hpp`
- `generated/devices/<device>/register_map.hpp`
- `generated/connector_tables.hpp`

`register_map.hpp` remains descriptor-first, but it must include typed per-register offsets for
the device.

## Validation

Publication must fail when:

- a foundational family has a runtime-consumable peripheral class without `backend_schema_id`
- route operations required by connector candidates are missing typed schema/runtime fields
- a foundational family publishes a device without normalized register descriptors for
  peripherals that participate in runtime-owned subsystems

## Migration

The implementation should be staged:

1. Extend raw source extraction with register descriptors.
2. Extend canonical IR and schema.
3. Emit typed runtime headers while keeping legacy descriptors temporarily for compatibility.
4. Tighten validation so foundational families require the stronger contract.
