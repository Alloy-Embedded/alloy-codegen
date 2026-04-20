## 1. OpenSpec

- [x] 1.1 Add canonical IR deltas for fully typed runtime domains
- [x] 1.2 Add artifact-contract deltas banning semantic strings in runtime C++ headers
- [x] 1.3 Add validation and vendor-admission deltas enforcing the zero-string rule

## 2. Canonical IR

- [x] 2.1 Add typed ids for backend schema, peripheral class, signal, signal role, route kind,
      requirement kind, operation kind, operation subject kind, memory kind, startup kind,
      package pad kind, and active level
- [x] 2.2 Ensure every runtime-facing semantic field in foundational families resolves to a
      typed enum/id/ref in the canonical IR
- [x] 2.3 Move any remaining human-readable runtime labels to metadata-only payloads

## 3. Runtime Header Emission

- [x] 3.1 Replace remaining `const char* schema_id` fields with typed schema enums
- [x] 3.2 Replace remaining textual class, kind, signal, role, package, selector, reset, and
      register-name fields with typed ids
- [x] 3.3 Emit typed `rcc_map`, `interrupt_map`, `dma_map`, `memory_map`, and `package_map`
- [x] 3.4 Emit typed `pins.hpp`, `capability_overlays.hpp`, `startup_descriptors.hpp`, and
      `generated/ip/*.hpp`
- [x] 3.5 Remove semantic diagnostic strings from runtime-facing C++ artifacts entirely

## 4. Validation and Publication

- [x] 4.1 Add a zero-string validator for runtime-consumed generated C++ headers
- [x] 4.2 Fail foundational publish when any runtime C++ artifact still exposes semantic
      `const char*` fields
- [x] 4.3 Fail vendor admission when a new family requires semantic strings in runtime C++
      artifacts

## 5. Regression Coverage

- [x] 5.1 Refresh emitted fixtures for `stm32g0`, `stm32f4`, `same70`, and `imxrt1060`
- [x] 5.2 Update smoke tests to compile only against the zero-string typed runtime contract
- [x] 5.3 Validate with `python3 -m ruff check src tests`
- [x] 5.4 Validate with `python3 -m pytest tests -q`
- [x] 5.5 Validate with `openspec validate eliminate-runtime-strings-from-cpp-contract --strict`
