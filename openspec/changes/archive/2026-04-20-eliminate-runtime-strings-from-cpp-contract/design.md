## Context

The previous change removed the worst runtime string glue, but the generated C++ contract is
still only partially typed. Several headers still expose semantic strings as normal fields,
for example:

- backend schema identifiers
- peripheral class labels
- route kinds, requirement kinds, operation kinds, subject kinds
- signal names and signal role strings
- package names, startup kinds, memory kinds, pad kinds
- selector names, reset names, active-level names
- peripheral/register/register-field names in runtime-facing structs

Those values are still interpreted by code or are likely to be interpreted by code as Alloy
continues the runtime migration. The correct boundary is stricter:

- C++ artifacts consumed by the runtime are fully typed
- human-readable names exist only in JSON metadata and reports

## Goals

- make runtime-consumed generated C++ headers fully typed, with no semantic `const char*`
  fields
- make schema dispatch, route execution, pin/signal binding, and system descriptor usage
  possible without any string comparison or parsing
- keep foundational publication green for `st/stm32g0`, `st/stm32f4`, `microchip/same70`,
  and `nxp/imxrt1060`

## Non-Goals

- remove strings from JSON metadata, manifests, reports, or docs
- redesign the whole vendor normalization flow from scratch
- add more vendor breadth before the contract is finished

## Decision: Separate Human Labels From Runtime C++

The contract splits into two products:

- runtime C++ contract:
  - only enums, ids, refs, offsets, counts, addresses, masks, widths, and integral values
- metadata/report contract:
  - human-readable names, labels, diagnostics, provenance, and inspection data

If a runtime field is useful only for inspection, it belongs in JSON metadata, not in the
generated C++ headers that Alloy includes.

## Decision: Define Runtime Header Scope Explicitly

The zero-string rule applies to all runtime-consumed generated C++ artifacts, including:

- `generated/runtime_profiles.hpp`
- `generated/runtime_refs.hpp`
- `generated/connector_tables.hpp`
- `generated/clock_tree_lite.hpp`
- `generated/rcc_map.hpp`
- `generated/interrupt_map.hpp`
- `generated/dma_map.hpp`
- `generated/memory_map.hpp`
- `generated/package_map.hpp`
- `generated/peripherals/*.hpp`
- `generated/ip/*.hpp`
- `generated/devices/<device>/*.hpp`

The rule does not apply to:

- `metadata/*.json`
- `reports/*.json`
- `artifact-manifest.json`
- textual docs

## Decision: Introduce Typed Domain Enums Everywhere

The runtime contract SHALL define typed enums or typed refs for every semantic domain still
represented as strings. At minimum this includes:

- `BackendSchemaId`
- `PeripheralClassId`
- `SignalId`
- `SignalRoleId`
- `RouteKindId`
- `RequirementKindId`
- `OperationKindId`
- `OperationSubjectKindId`
- `MemoryKindId`
- `StartupKindId`
- `PackagePadKindId`
- `ActiveLevelId`

These ids SHALL be emitted as enums in generated C++ and referenced from descriptors instead
of textual names.

## Decision: Runtime Maps and Bindings Use Ids Only

Family-level maps and device-scoped bindings SHALL use ids only:

- `rcc_map.hpp` uses `PeripheralId`, `ClockGateId`, `ResetId`
- `interrupt_map.hpp` uses `PeripheralId`, `InterruptId`, `VectorSlotId`
- `dma_map.hpp` and `dma_bindings.hpp` use `PeripheralId`, `SignalId`, `DmaControllerId`,
  `DmaRouteId`, `DmaConflictGroupId`
- `pins.hpp` uses `PeripheralId`, `SignalId`, `PinRefId`, `SelectorRefId`
- `package_map.hpp` uses `PackageRefId`, `PackagePadKindId`, `PinRefId`
- `memory_map.hpp` and `startup_descriptors.hpp` use `MemoryKindId`, `StartupKindId`

## Decision: IP Headers Become Fully Typed Profiles

`generated/ip/*.hpp` SHALL stop exposing semantic text fields such as `peripheral_class`,
`signal_roles`, and instance overlay names. They SHALL instead publish:

- typed class id
- typed signal role ids
- typed capability ids or refs
- typed instance/profile ids where needed

## Decision: Validation Gates Ban Semantic Strings

Publication SHALL fail when a runtime C++ header exposes a semantic string field. Examples:

- `const char* schema_id`
- `const char* peripheral_class`
- `const char* signal`
- `const char* kind`
- `const char* selector_name`
- `const char* package_name`
- `const char* register_name`

Allowed strings are limited to non-runtime JSON outputs only.

## Implementation Order

1. Define the zero-string runtime contract in OpenSpec
2. Extend the canonical IR with typed domains that cover every remaining semantic string
3. Re-emit runtime-facing headers with typed ids only
4. Tighten validation to fail any remaining semantic string field
5. Refresh foundational fixtures and republish `alloy-devices`
