## 1. OpenSpec

- [x] 1.1 Add canonical IR deltas for typed runtime-ref domains and no-string primary instance bindings
- [x] 1.2 Add artifact-contract deltas for typed instance, connector, and clock/reset headers
- [x] 1.3 Add validation deltas blocking foundational publication when string glue remains

## 2. Canonical IR

- [x] 2.1 Replace primary `PeripheralInstance` clock/reset signal strings with typed binding ids
- [x] 2.2 Add canonical typed runtime-ref ids for package, pin, constraint, selector, gate, reset, register, and field domains
- [x] 2.3 Mark any remaining human-readable route/instance payloads as diagnostics only

## 3. Emission

- [x] 3.1 Remove `interrupt_names` and `capability_overlay_ids` CSV payloads from `peripheral_instances.hpp`
- [x] 3.2 Remove `rcc_enable_signal` and `rcc_reset_signal` from `peripheral_instances.hpp`
- [x] 3.3 Emit typed clock/reset reference tables for runtime consumption
- [x] 3.4 Replace `RuntimeRefKind + const char*` primary refs in `connector_tables.hpp` with typed ids/domains
- [x] 3.5 Keep optional diagnostic strings only as secondary fields
- [x] 3.6 Replace `rcc_map.hpp` string signals with typed binding refs

## 4. Validation and Publication

- [x] 4.1 Add gates detecting CSV/string primary payloads in foundational runtime headers
- [x] 4.2 Add gates detecting route operations that still require textual target/value parsing
- [x] 4.3 Block publish when foundational families expose only diagnostic strings for clock/reset routing
- [x] 4.4 Close vendor-admission gap so new families must reuse typed runtime domains

## 5. Regression Coverage

- [x] 5.1 Update foundational emitted fixtures for `stm32g0`, `stm32f4`, `same70`, and `imxrt1060`
- [x] 5.2 Update smoke tests to compile against the typed runtime-ref contract
- [x] 5.3 Validate with `python3 -m ruff check src tests`
- [x] 5.4 Validate with `python3 -m pytest tests -q`
- [x] 5.5 Validate with `openspec validate remove-runtime-string-glue-from-artifacts --strict`
