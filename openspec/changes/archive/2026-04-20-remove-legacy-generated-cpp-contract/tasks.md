## 1. OpenSpec

- [x] 1.1 Add `artifact-contract` deltas declaring `generated/runtime/**` as the only supported
      published C++ contract
- [x] 1.2 Add `codegen-alloy-boundary` deltas forbidding Alloy-facing dependence on legacy
      `generated/**` C++ headers
- [x] 1.3 Add `validation-and-gates` deltas replacing legacy artifact smoke with runtime-only
      smoke

## 2. Typed Startup Contract

- [x] 2.1 Emit `generated/runtime/devices/<device>/startup.hpp`
- [x] 2.2 Move startup descriptor ids, vector slot descriptors, and typed startup facts into that
      runtime-scoped header
- [x] 2.3 Keep `startup.cpp` and `startup_vectors.cpp` publishable for board builds
- [x] 2.4 Remove `generated/devices/<device>/startup_descriptors.hpp` from the supported public
      contract

## 3. Public Artifact Pruning

- [x] 3.1 Stop publishing family-level reflection C++ headers such as `connector_tables.hpp`,
      `clock_tree_lite.hpp`, `interrupt_map.hpp`, `memory_map.hpp`, and `package_map.hpp`
- [x] 3.2 Stop publishing legacy runtime helper headers such as `runtime_profiles.hpp`,
      `runtime_semantics.hpp`, and `runtime_refs.hpp`
- [x] 3.3 Stop publishing device-level reflection C++ headers under `generated/devices/<device>/`
      other than startup implementation sources
- [x] 3.4 Remove `generated/ip/*` and `generated/peripherals/*` from the supported public C++
      publication surface

## 4. Gates And Smoke

- [x] 4.1 Replace `published_artifact_contract_smoke.cpp` with runtime-only published smoke
- [x] 4.2 Update `consumer_verification.py` to compile only the supported runtime contract
- [x] 4.3 Update `artifact_contract.py` to fail when legacy public C++ headers are still emitted
- [x] 4.4 Keep JSON metadata/report publication intact

## 5. Regression Coverage

- [x] 5.1 Refresh foundational emitted fixtures
- [x] 5.2 Update publish tests to assert the runtime-only public surface
- [x] 5.3 Validate with `python3 -m ruff check src tests`
- [x] 5.4 Validate with `python3 -m pytest tests -q`
- [x] 5.5 Validate with `openspec validate remove-legacy-generated-cpp-contract --strict`
