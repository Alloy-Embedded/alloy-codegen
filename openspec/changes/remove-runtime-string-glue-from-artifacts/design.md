## Context

The previous typed-runtime work got the project close to the right boundary, but the emitted
artifact contract still treats some human-readable strings as normal runtime fields. The
remaining string glue is concentrated in:

- `generated/devices/<device>/peripheral_instances.hpp`
- `generated/connector_tables.hpp`
- `generated/rcc_map.hpp`

The Alloy runtime can tolerate diagnostic strings, but it must not depend on them for
execution. The emitted contract therefore needs a clear split:

- primary runtime fields: typed enums, ids, offsets, counts, and structured references
- secondary diagnostics: optional strings kept only for debugging or inspection

## Goals

- make foundational runtime headers executable from typed refs alone
- remove CSV and raw signal strings from instance descriptors
- publish typed binding domains for clock/reset/selector/package/pin/constraint
- keep current family coverage for `st/stm32g0`, `st/stm32f4`, `microchip/same70`, and
  `nxp/imxrt1060`

## Non-Goals

- redesign the entire canonical IR from scratch
- remove all human-readable text from every emitted artifact
- add breadth to more vendors or families

## Decisions

### 1. Introduce typed runtime-ref domains

The emitted family contract SHALL expose stable typed domains for runtime-owned references.
At minimum:

- `PackageRefId`
- `PinRefId`
- `ConstraintRefId`
- `SelectorRefId`
- `ClockGateRefId`
- `ResetRefId`
- `RegisterRefId`
- `RegisterFieldRefId`

These ids SHALL be emitted as enums and referenced by index/enum in runtime headers.

### 2. Keep diagnostics separate

Where a human-readable string is still useful, it SHALL be emitted in a dedicated diagnostic
field or diagnostic table. The runtime-facing structs SHALL not require those strings to be
present or parsed.

### 3. Remove string payloads from peripheral instance descriptors

`PeripheralInstanceDescriptor` SHALL keep only:

- typed peripheral id
- typed backend schema id
- base address / instance number
- typed clock/reset/selector refs
- typed offsets/counts for interrupt bindings, DMA bindings, and capability overlays
- typed register counts / ids where needed

It SHALL no longer publish CSV strings or RCC signal strings as primary fields.

### 4. Replace textual route refs with typed ref ids

`RouteRequirementDescriptor` and `RouteOperationDescriptor` SHALL continue to carry diagnostic
strings optionally, but their primary contract SHALL be typed ref domains plus typed ids and
typed integers.

### 5. Tighten publish gates

Foundational families SHALL fail validation/publish if:

- any runtime-owned instance depends on `rcc_enable_signal` / `rcc_reset_signal` as the only
  executable contract
- any route requirement or operation still requires string parsing to identify the target or
  value
- any primary runtime struct still uses CSV payloads for bindings/capabilities

## Implementation Order

1. Add canonical typed runtime-ref ids and remove string primaries from IR structs
2. Emit typed instance/binding/ref tables
3. Update validation gates and publish coverage
4. Refresh golden fixtures and smoke tests
