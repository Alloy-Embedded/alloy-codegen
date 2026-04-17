## Context

The runtime migration is effectively complete from the hot-path perspective:

- `alloy` consumes `generated/runtime/**` for GPIO/UART/I2C/SPI/DMA/timer/PWM/ADC/DAC, SysTick,
  system clock, and most board bring-up flows
- the remaining legacy public dependency is the startup descriptor include path
- the reflection-heavy C++ artifacts are no longer the intended runtime boundary

The device publication tree should reflect that reality. Right now it does not.

Users opening `alloy-devices/<vendor>/<family>/generated` still see:

- `connector_tables.hpp`
- `clock_tree_lite.hpp`
- `runtime_profiles.hpp`
- `runtime_semantics.hpp`
- `runtime_refs.hpp`
- `generated/devices/<device>/register_map.hpp`
- `generated/devices/<device>/device_descriptor.hpp`
- and many other legacy headers

Those headers describe a table-oriented model that the runtime intentionally moved away from.

## Goals

- make the typed runtime contract the only supported published C++ contract
- remove reflection-oriented C++ artifacts from the public published surface
- preserve JSON metadata and reports for tooling, validation, and inspection
- replace the last legacy startup descriptor include with a typed runtime startup contract
- simplify consumer verification so publish validates only the supported C++ boundary

## Non-Goals

- removing JSON metadata or report outputs
- removing generated startup source files needed for linking board firmware
- deleting information from the IR or validation pipeline when it is still useful for codegen
- renaming every internal helper in one change before consumers are migrated

## Decision 1: `generated/runtime/**` Is The Only Supported Published C++ Contract

The published C++ contract SHALL be:

- `generated/runtime/types.hpp`
- `generated/runtime/devices/<device>/*`
- `generated/runtime/devices/<device>/driver_semantics/*`
- `generated/runtime/devices/<device>/systick.hpp`
- `generated/runtime/devices/<device>/system_clock.hpp`
- `generated/runtime/devices/<device>/startup.hpp`

The generated startup source files MAY remain outside that tree if they are implementation units
used by board builds:

- `generated/devices/<device>/startup.cpp`
- `generated/devices/<device>/startup_vectors.cpp`

Everything else under `generated/**` SHALL be treated as legacy or internal and SHALL NOT remain
part of the supported public C++ contract.

## Decision 2: Reflection-Oriented C++ Artifacts Are Removed From Public Publication

The following published C++ artifacts SHALL be removed from the public tree:

- `generated/connector_tables.hpp`
- `generated/clock_tree_lite.hpp`
- `generated/runtime_profiles.hpp`
- `generated/runtime_semantics.hpp`
- `generated/runtime_refs.hpp`
- `generated/interrupt_map.hpp`
- `generated/memory_map.hpp`
- `generated/package_map.hpp`
- `generated/rcc_map.hpp`
- `generated/dma_map.hpp`
- `generated/ip/*`
- `generated/peripherals/*`
- `generated/devices/<device>/register_map.hpp`
- `generated/devices/<device>/register_fields.hpp`
- `generated/devices/<device>/device_descriptor.hpp`
- `generated/devices/<device>/pins.hpp`
- `generated/devices/<device>/peripheral_instances.hpp`
- `generated/devices/<device>/interrupt_bindings.hpp`
- `generated/devices/<device>/dma_bindings.hpp`
- `generated/devices/<device>/capability_overlays.hpp`
- `generated/devices/<device>/startup_descriptors.hpp`

If some of these remain useful for internal debugging or transitional local workflows, they MAY be
kept as non-published internal artifacts, but they SHALL NOT be part of the public supported
contract in `alloy-devices`.

## Decision 3: Startup Moves To A Typed Runtime Contract

Startup is the last functional boundary still using the legacy device contract.

Codegen SHALL publish a typed runtime startup header at:

- `generated/runtime/devices/<device>/startup.hpp`

That header SHALL expose the data currently needed by `alloy::device::startup` without forcing
consumers to include `generated/devices/<device>/startup_descriptors.hpp`.

At minimum the typed startup contract SHALL cover:

- vector slot descriptors
- startup descriptors / startup actions
- startup-related symbol and memory region ids
- any typed startup traits needed by `alloy`

This change does **not** require moving `startup.cpp` and `startup_vectors.cpp` under
`generated/runtime/**`; it only requires that the *public descriptor contract* become typed and
runtime-scoped.

## Decision 4: JSON Metadata Remains

The following outputs remain valuable and SHALL stay published:

- `artifact-manifest.json`
- validation reports and summaries
- coverage reports
- metadata JSON for devices, packages, connectivity, capabilities, and system descriptors

These are tooling/reporting assets, not runtime C++ contracts.

## Decision 5: Consumer Verification Becomes Runtime-Only

The current legacy smoke consumer in
`tests/codegen/published_artifact_contract_smoke.cpp` validates the old table-heavy C++ contract.

That consumer SHALL be removed.

`consumer_verification.py` SHALL use only the runtime smoke consumer in
`tests/codegen/published_runtime_lite_contract_smoke.cpp` or its renamed equivalent.

The runtime smoke consumer SHALL become the canonical verification of the published C++ boundary.

## Decision 6: The Public Name Becomes Simply "Runtime"

The published path already uses `generated/runtime/**`, which is the correct stable name.

This cleanup formalizes that:

- "runtime-lite" remains migration terminology only
- the supported public contract is simply the runtime contract
- internal names/macros/helpers using `runtime_lite` SHOULD be migrated to `runtime` after the
  legacy surface is removed, but that rename can be staged separately if needed

## Migration Order

1. Define the runtime-only public contract in OpenSpec
2. Emit typed runtime startup contract
3. Update `artifact_contract.py` to reject legacy public C++ publication
4. Remove the legacy artifact smoke consumer and point consumer verification at runtime-only smoke
5. Stop emitting/publishing reflection-oriented C++ headers
6. Refresh foundational fixtures and publish `alloy-devices`
7. Migrate `alloy` to the typed startup contract and remove the last legacy include path
