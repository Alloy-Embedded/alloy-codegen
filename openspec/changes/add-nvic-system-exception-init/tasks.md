# Tasks — Add NVIC + System-Exception Init Surface

## 1. IR additions

- [ ] 1.1 Add `priority: int | None` field to
      `InterruptVector`.  Validates against `core.nvic_priority_bits`
      bound: when set, must be `0 <= priority < (1 <<
      nvic_priority_bits)`.
- [ ] 1.2 Promote `core.fpu` to a typed enum
      `FpuVariant ∈ {NONE, FPV4_SP_D16, FPV5_SP_D16,
      FPV5_D16, FPV5_DP_D16}`.  Existing `fpu: bool` carriage
      maps to `FPV4_SP_D16` for ARMv7E-M and `NONE` otherwise;
      explicit YAML overrides win.
- [ ] 1.3 Promote `core.mpu` to a typed enum `MpuVariant ∈
      {NONE, ARMV7M_PMSA, ARMV8M_PMSA}`.

## 2. Vector-table priority emission

- [ ] 2.1 Extend `vector_table.py` with `_emit_nvic_priority_table(
      device) -> str` that walks
      `device.interrupts.vectors[*].priority` and emits the
      `kNvicPrioritySetup` C array.  Empty when no vector
      carries an explicit priority.
- [ ] 2.2 Emit `void alloy_nvic_apply_priorities(void)` whose
      body iterates `kNvicPrioritySetup` and calls the
      Cortex-M intrinsic `NVIC_SetPriority(irqn, priority)`
      (or its open-coded register write).
- [ ] 2.3 The priority value is **already encoded** for the
      device's `nvic_priority_bits` (left-shifted into the
      upper bits of `NVIC->IPR[n]`) so consumers don't need
      to know the bit count at runtime.

## 3. New `system_init.c` emitter

- [ ] 3.1 New module `src/alloy_codegen/emit_v2_1/system_init.py`
      with `emit_system_init(device, synthesised) -> str`.
- [ ] 3.2 Emit `void alloy_system_init_fpu(void)` body based
      on `core.fpu`:
      - `FpuVariant.NONE`: empty body (return immediately)
      - `FPV4_SP_D16` / `FPV5_*`: `SCB->CPACR |= (0xF << 20);
        __DSB(); __ISB();`
      - The `0xF << 20` mask covers CP10 (full access) +
        CP11 (full access)
- [ ] 3.3 Emit `void alloy_system_init_mpu(void)` body based
      on `core.mpu`:
      - `MpuVariant.NONE`: empty body
      - `ARMV7M_PMSA`: verify `MPU->TYPE & MPU_TYPE_DREGION_Msk
        != 0`, set `MPU->CTRL = MPU_CTRL_PRIVDEFENA_Msk |
        MPU_CTRL_ENABLE_Msk`, `__DSB(); __ISB();`
      - `ARMV8M_PMSA`: equivalent for v8M
- [ ] 3.4 Emit `void alloy_system_init(void)` umbrella that
      calls `alloy_system_init_fpu()` followed by
      `alloy_system_init_mpu()` followed by
      `alloy_nvic_apply_priorities()`.

## 4. Wire-up

- [ ] 4.1 Register `_EmitterEntry(name="system_init",
      filename="system_init.c", fn=emit_system_init)` in
      `cli.py::_EMITTERS` and `entrypoint.py::_EMITTERS`.
- [ ] 4.2 Update CLI `--list` and `--emit` documentation.

## 5. Tests

- [ ] 5.1 Unit tests for `_emit_nvic_priority_table` —
      synthetic vectors with mixed priority/no-priority;
      assert table has only non-default rows.
- [ ] 5.2 Unit tests for FPU variant dispatch — assert
      `FpuVariant.NONE` produces an empty body, all FPV4/5
      variants produce the same `CPACR` write.
- [ ] 5.3 Compile-test the regenerated `vector_table.c` and
      new `system_init.c` against a stub `core_cm0plus.h`,
      `core_cm4.h`, and `core_cm7.h`.
- [ ] 5.4 Add `system_init.c` to the per-device golden suite.
- [ ] 5.5 Update `test_entrypoint.py` to assert
      `system_init.c` is in the written-files set.

## 6. Documentation

- [ ] 6.1 Document the bring-up call ordering in
      `runtime-lite-contract` design notes:
      `alloy_system_init_fpu()` → C++ static init →
      `alloy_system_init_mpu()` → `alloy_nvic_apply_priorities()`.
