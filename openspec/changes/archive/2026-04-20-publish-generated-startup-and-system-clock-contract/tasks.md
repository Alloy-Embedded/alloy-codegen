## 1. Spec and IR

- [x] 1.1 Add this startup/system-clock bring-up change
- [x] 1.2 Extend patches and canonical IR with typed `system_clock_profiles`
- [x] 1.3 Update docs/spec deltas for the new bring-up boundary

## 2. Generated Startup

- [x] 2.1 Emit `generated/devices/<device>/startup.cpp`
- [x] 2.2 Retire `startup_vectors.cpp` from the active executable contract
- [x] 2.3 Update smoke verification to compile the generated startup TU

## 3. Runtime-Lite System Clock

- [x] 3.1 Emit `generated/runtime/devices/<device>/system_clock.hpp`
- [x] 3.2 Publish typed system clock profiles for `stm32g071rb`
- [x] 3.3 Publish typed system clock profiles for `stm32f401re`
- [x] 3.4 Publish typed system clock profiles for `atsame70q21b`
- [x] 3.5 Expose generated helpers for default and safe bring-up profiles

## 4. Gates and Docs

- [x] 4.1 Update artifact contract verification and runtime-lite smoke coverage
- [x] 4.2 Update artifact-layout / boundary docs
- [x] 4.3 Regenerate affected emitted fixtures
- [x] 4.4 Validate with `python3 -m ruff check src tests`
- [x] 4.5 Validate with `python3 -m pytest tests -q`
- [x] 4.6 Validate with `openspec validate publish-generated-startup-and-system-clock-contract --strict`
