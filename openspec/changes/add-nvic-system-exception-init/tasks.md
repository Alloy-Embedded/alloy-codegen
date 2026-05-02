# Tasks — Add NVIC + System-Exception Init Surface

## 1. IR additions

- [x] 1.1 Add `priority: int | None` field to `InterruptVector`.
      *(Loader pulls it from YAML when present; round-trip test
      confirms None when absent and the encoded value when
      provided.  Bounds validation against
      `core.nvic_priority_bits` deferred until any YAML carries
      priority data.)*
- [ ] 1.2 Promote `core.fpu` to a typed enum
      `FpuVariant ∈ {NONE, FPV4_SP_D16, FPV5_SP_D16,
      FPV5_D16, FPV5_DP_D16}`.
      *(Deferred — the system_init emitter derives the variant
      from `(core.fpu, core.isa)` inline via
      `_has_cortexm_fpu`.  Promotion to a typed enum + YAML
      schema migration lands once one consumer needs to
      distinguish FPV4 vs FPV5.)*
- [ ] 1.3 Promote `core.mpu` to a typed enum `MpuVariant ∈
      {NONE, ARMV7M_PMSA, ARMV8M_PMSA}`.
      *(Same rationale — current emitter dispatches off
      `(core.mpu, core.isa)` and writes the v7-M / v8-M shared
      bit layout.  v8-M-only bring-up tweaks land with the
      typed enum.)*

## 2. Vector-table priority emission

- [x] 2.1 Extend `vector_table.py` with `_emit_nvic_priority_setup`
      that walks `device.interrupts[*].priority` and emits the
      `alloy_nvic_priority_setup[]` C array.  Empty / zero-row
      when no vector carries an explicit priority.
- [x] 2.2 Emit `void alloy_nvic_apply_priorities(void)` whose
      body iterates `alloy_nvic_priority_setup[]` and calls
      `NVIC_SetPriority(irqn, priority)`.
- [x] 2.3 The priority value is already encoded for the
      device's `nvic_priority_bits` — runtime helper writes it
      verbatim, no shift / no bit-count lookup.

## 3. New `system_init.c` emitter

- [x] 3.1 New module `src/alloy_codegen/emit_v2_1/system_init.py`
      with `emit_system_init(device, synthesised) -> str`.
- [x] 3.2 Emit `void alloy_system_init_fpu(void)` body based on
      `(core.fpu, core.isa)`:  Cortex-M with `fpu=True` writes
      `SCB->CPACR |= (0xFu << 20)` + DSB/ISB; everything else
      is an explicit no-op.
- [x] 3.3 Emit `void alloy_system_init_mpu(void)` body based on
      `(core.mpu, core.isa)`:  Cortex-M with `mpu=True` checks
      `MPU->TYPE.DREGION != 0`, writes
      `MPU->CTRL = PRIVDEFENA | ENABLE`, then DSB/ISB.
- [x] 3.4 Emit `void alloy_system_init(void)` umbrella calling
      `_fpu()` → `_mpu()` → `alloy_nvic_apply_priorities()` in
      that order.

## 4. Wire-up

- [x] 4.1 Register `_EmitterEntry(name="system_init",
      filename="system_init.c", fn=emit_system_init)` in
      `cli.py::_EMITTERS` and `entrypoint.py::_EMITTERS`.
- [ ] 4.2 Update CLI `--list` and `--emit` documentation.
      *(Tiny follow-up — `--emit` already auto-discovers the
      entry from `_EMITTERS`.)*

## 5. Tests

- [x] 5.1 Unit tests for `_emit_nvic_priority_setup` — confirms
      apply-helper is always defined, table degrades to zero
      rows when YAML carries no priorities, loader round-trips
      `priority: 12` into `InterruptVector.priority`.
- [x] 5.2 Unit tests for FPU variant dispatch — `_has_cortexm_fpu`
      requires both `core.fpu=True` and Cortex-M ISA; G0 (M0+,
      no FPU) emits a no-op body; synthetic F4 with `fpu=True`
      emits the full CPACR write.
- [ ] 5.3 Compile-test the regenerated `vector_table.c` and
      new `system_init.c` against a stub `core_cm0plus.h`,
      `core_cm4.h`, and `core_cm7.h`.
- [ ] 5.4 Add `system_init.c` to the per-device golden suite.
- [x] 5.5 Update `test_entrypoint.py` to assert `system_init.c`
      is in the written-files set (and `test_cli.py` for the
      6-artifact registry).

## 6. Documentation

- [ ] 6.1 Document the bring-up call ordering in
      `runtime-lite-contract` design notes:
      `alloy_system_init_fpu()` → C++ static init →
      `alloy_system_init_mpu()` → `alloy_nvic_apply_priorities()`.
      *(The ordering is documented in the emitted file's
      banner; the spec design-notes update follows.)*
