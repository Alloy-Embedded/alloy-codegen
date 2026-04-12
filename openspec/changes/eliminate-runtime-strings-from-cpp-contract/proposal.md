## Why

The current runtime-facing C++ artifacts are better than before, but they still leak semantic
strings into the Alloy boundary. Headers such as `connector_tables.hpp`,
`clock_tree_lite.hpp`, `runtime_profiles.hpp`, `pins.hpp`, `rcc_map.hpp`, `interrupt_map.hpp`,
`dma_map.hpp`, `package_map.hpp`, `memory_map.hpp`, `startup_descriptors.hpp`, and
`generated/ip/*.hpp` still expose `const char*` fields for concepts that the runtime must
interpret.

That is still the wrong contract. A typed runtime must not parse names, kinds, classes,
signals, roles, package names, selector names, or schema IDs from strings. If the runtime
needs a value to execute behavior, the codegen must publish it as a typed enum, typed id,
typed ref, or integer.

## What Changes

- define a zero-string rule for all runtime-consumed generated C++ artifacts
- replace remaining textual runtime fields with typed ids, enums, refs, offsets, counts, or
  integral values
- move human-readable labels entirely to JSON metadata and reports, not the emitted C++
  runtime contract
- add validation gates that fail foundational publication whenever any runtime C++ header
  still exposes semantic strings
- tighten vendor admission so new families can only publish when they reuse the fully typed
  contract

## Impact

- Affected specs: `canonical-device-ir`, `artifact-contract`, `validation-and-gates`,
  `codegen-alloy-boundary`, `vendor-admission`
- Affected code:
  - `src/alloy_codegen/ir/model.py`
  - `src/alloy_codegen/stages/normalize.py`
  - `src/alloy_codegen/validation.py`
  - `src/alloy_codegen/emission.py`
  - publish smoke tests and foundational emitted fixtures
- Breaking impact:
  - runtime-facing generated headers in `alloy-devices` will change shape again
  - Alloy runtime code must consume typed enums/ids only, with no string fallback
