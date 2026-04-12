## Why

The current `alloy-devices` publish includes the new device-scoped headers, but the runtime
contract is still partially string-driven. `peripheral_instances.hpp` still exposes
`rcc_enable_signal`, `rcc_reset_signal`, `interrupt_names`, and `capability_overlay_ids`,
while `connector_tables.hpp` still uses `RuntimeRefKind + target/value` textual IDs as the
primary runtime payload.

That leaves `alloy` in the wrong position: it still has to interpret vendor-specific strings
instead of consuming a purely typed descriptor contract. This blocks the final runtime
refactor and does not scale to many families or vendors.

## What Changes

- remove string fields as primary runtime contract from emitted foundational headers
- emit typed runtime-ref domains and index-based references for package, pin, constraint,
  selector, clock-gate, reset, register, and register-field references
- replace CSV/string payloads in `peripheral_instances.hpp` with typed offsets/counts and
  typed binding references only
- replace `rcc_map.hpp` string signals with typed clock/reset bindings
- hard-block publication when foundational families still require runtime string parsing for
  clock/reset, route operations, or per-instance bindings

## Impact

- Affected specs: `canonical-device-ir`, `artifact-contract`, `validation-and-gates`,
  `vendor-admission`
- Affected code:
  - `src/alloy_codegen/ir/model.py`
  - `src/alloy_codegen/stages/normalize.py`
  - `src/alloy_codegen/validation.py`
  - `src/alloy_codegen/emission.py`
  - foundational fixtures and publish smoke tests
