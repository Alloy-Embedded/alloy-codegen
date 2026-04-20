## Why

`alloy-devices` now publishes two very different C++ surfaces:

- the typed runtime contract under `generated/runtime/**`
- a legacy reflection-oriented C++ surface under `generated/**`

That split was useful during migration, but it is now actively harmful:

- the public device tree is harder to understand because users see two competing contracts
- publish and smoke verification still spend time validating large table-oriented C++ headers that
  `alloy` no longer needs in its hot path
- the remaining legacy surface keeps pressure on the runtime to preserve old include shapes
- the last public startup dependency still comes from `generated/devices/<device>/startup_descriptors.hpp`

At this point the typed runtime contract is the real product. The reflection-heavy C++ surface is
legacy scaffolding and should stop being part of the supported published C++ API.

## What Changes

- **BREAKING** make `generated/runtime/**` the only supported published C++ device contract
- **BREAKING** stop publishing reflection-oriented C++ headers such as connector tables, clock
  trees, device descriptors, legacy register inventories, and other table-driven generated C++
  artifacts
- **NEW** publish a typed startup contract under `generated/runtime/devices/<device>/startup.hpp`
- **MODIFIED** keep startup implementation sources (`startup.cpp`, `startup_vectors.cpp`) published
  where needed for board builds, but make their public descriptor contract runtime-typed
- **MODIFIED** keep JSON metadata, validation reports, and coverage outputs; remove only the
  reflection-oriented **C++** surface
- **BREAKING** remove the legacy artifact smoke consumer and make runtime-contract smoke the only
  published C++ consumer verification path
- **MODIFIED** treat "runtime-lite" as migration language only; the published contract remains
  under the standard `generated/runtime/**` layout and becomes the default contract

## Impact

- Affected specs:
  - `artifact-contract`
  - `codegen-alloy-boundary`
  - `validation-and-gates`
- Affected code:
  - `src/alloy_codegen/emission.py`
  - `src/alloy_codegen/stages/emit.py`
  - `src/alloy_codegen/consumer_verification.py`
  - `src/alloy_codegen/artifact_contract.py`
  - startup/runtime emitters and foundational fixtures
- Breaking impact:
  - consumers can no longer rely on legacy C++ artifacts under `generated/**`
  - `alloy` must stop including `generated/devices/<device>/startup_descriptors.hpp` and consume
    the typed runtime startup contract instead
