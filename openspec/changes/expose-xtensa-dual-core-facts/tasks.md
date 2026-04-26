# Tasks: Expose Xtensa Dual-Core Bring-Up Facts

Tasks are ordered. Each phase MUST land green before the next begins.

## 1. IR vocabulary
- [ ] 1.1 Add `MulticoreTopology` enum to `src/alloy_codegen/ir/model.py`
      with values `single_core`, `symmetric_dual_core`,
      `xtensa_asymmetric_dual_core`. Default factory returns `single_core`.
- [ ] 1.2 Add `AppCpuControlPlane` dataclass with fields:
      `release_register: RegisterId`, `release_register_secondary:
      RegisterId | None` (LX7 needs two), `operation: Literal["set-bit-0",
      "clear-runstall-after-clkgate"]`, `start_vector_symbol: str`.
- [ ] 1.3 Add `Device.multicore_topology: MulticoreTopology = single_core`
      and `Device.app_cpu_control_plane: AppCpuControlPlane | None = None`.
      Keep the legacy `core: str` field; populate it derivatively for one
      cycle.
- [ ] 1.4 Add `RegisterDescriptor.role: RegisterRole = general` with
      `RegisterRole = Literal["general", "secondary-core-release"]`.
- [ ] 1.5 Update IR JSON serializers and JSON Schema to round-trip the new
      fields. Existing fixtures must still validate (defaults preserve
      back-compat).
- [ ] 1.6 Unit tests in `tests/test_ir_model.py` covering construction,
      defaults, JSON round-trip.

## 2. Source-data overlays
- [ ] 2.1 `patches/espressif/esp32/family.json` gains a `multicore_topology`
      block: `topology = "xtensa-asymmetric-dual-core"`, `core_count = 2`,
      `app_cpu_control_plane = { register = "DPORT.APPCPU_CTRL_B",
      operation = "set-bit-0", start_vector_symbol = "_vectors_cpu1" }`.
- [ ] 2.2 `patches/espressif/esp32s3/family.json` gains the analogous LX7
      block with both `SYSTEM.CORE_1_CONTROL_0` and
      `SYSTEM.CORE_1_CONTROL_1` and `operation =
      "clear-runstall-after-clkgate"`.
- [ ] 2.3 Patch validator asserts: asymmetric Xtensa devices MUST have a
      populated `multicore_topology` block; symmetric or single-core devices
      MUST NOT.
- [ ] 2.4 `esp32c3` patch is unchanged (single-core RISC-V).

## 3. Normalizer wiring
- [ ] 3.1 `src/alloy_codegen/sources/esp_idf.py` (or the relevant SVD adapter)
      reads the patch's `multicore_topology` and populates
      `Device.multicore_topology` + `Device.app_cpu_control_plane`.
- [ ] 3.2 The normalizer resolves the patch's `register = "DPORT.APPCPU_CTRL_B"`
      string to a typed `RegisterId` after register filtering. Validation
      fails fast if the named register is not present in the typed enum.
- [ ] 3.3 APPCPU_CTRL_A/B/C/D registers are added to the ESP32 emission
      allow-list. The S3 SYSTEM.CORE_1_CONTROL_0/1 registers are flagged
      with `role = "secondary-core-release"`.

## 4. Artifact emission
- [ ] 4.1 `runtime_lite_emission.py` (registers.hpp builder) honors
      `RegisterDescriptor.role`; emits a typed `RegisterRole` enum
      alongside `RegisterId`.
- [ ] 4.2 `runtime_system_sequences.py` adds
      `SystemSequenceStepKindId::secondary_core_release`. For asymmetric
      Xtensa devices the `default_bringup` sequence ends with this step,
      referencing `Device.app_cpu_control_plane.release_register` (and
      `_secondary` if present) by typed id.
- [ ] 4.3 `runtime_capabilities.py` writes:
      `device:multicore-topology`, `device:core-count`, and (when
      asymmetric) `device:secondary-core-release-register` (and the
      secondary entry on LX7).
- [ ] 4.4 `runtime_xtensa_startup.py` is refactored to read addresses
      and bit operations from `Device.app_cpu_control_plane` instead of
      its current hardcoded constants. Behavior must be byte-identical
      against the existing goldens before the goldens are regenerated.

## 5. Goldens & tests
- [ ] 5.1 Regenerate `tests/fixtures/emitted/esp32/`,
      `tests/fixtures/emitted/esp32s3/`. Diff against the previous
      goldens MUST be limited to: (a) new register entries +
      `RegisterRole` enum, (b) the new `secondary_core_release` step,
      (c) the new capability keys. The generated startup.cpp must be
      bit-identical to the prior version (refactor is invisible).
- [ ] 5.2 `tests/fixtures/emitted/esp32c3/` MUST gain only the two
      single-core-safe capability keys (`device:multicore-topology =
      "single-core"`, `device:core-count = 1`) and NO sequence step.
- [ ] 5.3 New positive test in `tests/test_espressif.py`:
      `test_esp32_secondary_core_release_step_emitted` — asserts the
      step exists in the dual-core sequence and the typed register id
      resolves to `register_dport_appcpu_ctrl_b`.
- [ ] 5.4 New positive test for esp32s3 covering both registers.
- [ ] 5.5 New negative test:
      `test_esp32c3_has_no_secondary_core_release_step`.
- [ ] 5.6 New IR test asserting `Device.multicore_topology` matches the
      patch overlay for all three Espressif devices.

## 6. Spec validation
- [ ] 6.1 `openspec validate expose-xtensa-dual-core-facts --strict` passes.
- [ ] 6.2 Full pytest suite passes (`pytest -q`).
- [ ] 6.3 Diff review: confirm no goldens for non-Espressif devices changed
      beyond defaulting `multicore-topology = "single-core"` /
      `core-count = 1`.

## 7. Downstream unblock
- [ ] 7.1 Ping the alloy `add-esp32-classic-family` change owner: phase 4
      blocker is resolved; the runtime can now read multicore facts from
      `capabilities.json` + the typed register id from the secondary-core
      release step.
- [ ] 7.2 Note in the archive entry that this change unblocks alloy's
      `alloy::runtime::Core` / `current_core()` / `launch_on()` surface.
