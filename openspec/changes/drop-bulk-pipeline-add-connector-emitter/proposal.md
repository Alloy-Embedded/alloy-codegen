# Drop Bulk Pipeline + Add Connector/Route Emitters

## Context

The `alloy-devices` repository (pre-generated C++ headers for ~5000 MCUs,
committed to git) has been deleted.  It was a CI-managed artifact store that
alloy-codegen fed via a bulk-regen pipeline.  That architecture is gone.

The new model is **on-demand generation**: `alloy-codegen st/stm32g0/stm32g071rb --out ./`
generates only for the chip the user is building for.  alloy-cli already drives this
via `core/codegen.py` with stamp-based caching.

This openspec has two parts:

1. **Remove** pipeline scripts/tools that existed to maintain the deleted repo.
2. **Add** the missing emitters for the runtime connector/route/signal system that the
   alloy HAL needs (`connectors.hpp`, `routes.hpp`, `signal_id.hpp`, etc.).

---

## Part 1 — Remove Bulk Pipeline Artifacts

### What is being removed and why

| File | Reason |
|---|---|
| `tests/codegen/published_runtime_lite_contract_smoke.cpp` | Smoke-tests against *published* (pre-generated) alloy-devices artifacts. Those artifacts no longer exist. The smoke should be replaced by testing against *freshly-generated* output. |
| `tools/runtime_cpp_smoke.py` | Runs clang++ over ALL admitted devices in bulk. Pipeline-only; a single-device CI job replaces it. |
| `tools/bump_devices_yml.py` | Bumps the submodule pin, runs the full pipeline, detects C++ artifact drift vs the deleted alloy-devices repo. No longer needed. |

### What stays

| File | Reason kept |
|---|---|
| `scripts/regen_canonical_yamls.py` | Maintains YAML in `alloy-devices-yml` submodule (NOT the deleted C++ repo). Data maintenance tool; still valid. |
| `scripts/clean_orphan_yaml_references.py` | YAML data hygiene. Still valid. |
| `scripts/bake_tier_data_into_yaml.py` | Bakes tier metadata into YAML. Still valid. |

### What replaces the pipeline smoke

A narrow per-device compile smoke (`tests/compile_tests/smoke_one_device.cpp`) that
runs as part of the regular `pytest -q` CI job against one representative device
(e.g. `st/stm32g0/stm32g071rb`).  Covers the same template-metaprogramming regressions
without requiring all admitted devices.

---

## Part 2 — Add Missing Runtime Emitters

`alloy-codegen` currently emits 10 artifacts.  The alloy HAL also needs several
headers that were previously only in the deleted alloy-devices repo.  These must
now come from alloy-codegen.

### Required new emitters

| Emitter | Output file | Content |
|---|---|---|
| `emit_connector_traits` | `connectors.hpp` | `ConnectorTraits<Pin,Peripheral,Signal>` full + partial specs; Guard A (wrong pin for known peripheral) + Guard B (wrong peripheral for known pin, modm-style); `kConnectors` array; `ConnectorSignalTraits`. |
| `emit_routes` | `routes.hpp` | `RouteId` enum, `RouteKindId` enum, `RouteDescriptor`, `kRoutes` table. |
| `emit_signal_id` | `signal_id.hpp` | `SignalId` enum from all signal roles in the device IR. |
| `emit_connection_groups` | `connection_groups.hpp` | `ConnectionGroupId` enum from group metadata. |

### Guard B (modm-style from-GPIO errors)

Guard B fires when the user writes `connector<USART2, tx<PB6>>` but PB6 only serves
`signal_tx` on USART1.  Pattern:

```cpp
// Guard B partial spec — keyed on (Pin, *, Signal)
template<PeripheralId Peripheral>
struct ConnectorTraits<PinId::PB6, Peripheral, SignalId::signal_tx> {
  static_assert(detail::kInvalidConnector<Peripheral>,
    "PB6 can only serve signal_tx on: USART1. "
    "Check the connector<> peripheral ID or choose a different pin.");
};
// Guard A partial spec — keyed on (*, Peripheral, Signal)
template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_tx> {
  static_assert(detail::kInvalidConnector<Pin>,
    "Invalid connector for USART1 tx. Valid pins: PB6.");
};
// Full spec (correct case — suppresses both partial specs)
template<>
struct ConnectorTraits<PinId::PB6, PeripheralId::USART1, SignalId::signal_tx> { ... };
```

### Integration with existing emitters

The new emitters share the same `(CanonicalDevice, SynthesisedDevice)` inputs as
existing emitters.  They slot into `_EMITTERS` in `cli.py` and `entrypoint.py`
unchanged.

The `SynthesisedDevice` IR must expose:
- `routes: list[RouteRow]` — already present in synthesised IR
- Per-route: `pin_id`, `peripheral_id`, `signal_id`, `route_kind`, `group_id`, `af_number`

Verify these fields exist in `alloy_codegen/ir/synthesised.py` before implementing.
