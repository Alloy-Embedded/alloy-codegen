# Add NVIC + System-Exception Init Surface

## Why

Three pieces of bring-up infrastructure live on every Cortex-M
chip and **none of it is generated today**:

1. **NVIC priority encoding** — `core.nvic_priority_bits` is
   populated on 332 STM32 F4/G0/G4/H7 chips (56% of corpus).
   The number says "this part has 4 priority bits, valid
   priorities are 0..15" but the emitter never writes a typed
   priority table; the consumer gets `vector_table.c` listing
   every IRQ in slot order with no priority configured (which
   means the runtime starts with all IRQs at priority 0 — i.e.
   the highest, which is wrong for almost any real program).

2. **FPU initialization** — `core.fpu` is populated on every
   chip with a Cortex-M4F/M7/M33F core (SAM E70/V71, STM32 F4/H7,
   etc.).  The compiler emits `vldr`/`vstr` instructions in
   `-mfpu=fpv4-sp-d16` builds but the FPU is **disabled at
   reset**; without enabling it (`SCB->CPACR |= 0xF << 20`)
   the first floating-point instruction faults.  Today this is
   open-coded by every consumer.

3. **MPU base setup** — `core.mpu` is populated on every chip
   with an MPU (a strict superset of FPU chips plus the SAM D
   line).  An optional but commonly-needed bring-up step.

`vector_table.c` already lists every IRQ; this proposal extends
it (or splits off a sibling artifact) to cover priorities and
the system-exception bring-up.  The IR has all the data; the
consumer should not be re-deriving "Cortex-M4 has 4 priority
bits" by hand.

## What Changes

`vector_table.c` and a new sibling `system_init.c` artifact
publish three new typed surfaces:

### A. NVIC priority table

`vector_table.c` gains a `kNvicPrioritySetup` table:

```c
struct alloy_nvic_priority_setup {
    uint8_t  irqn;
    uint8_t  priority;     // already shifted into the upper bits per nvic_priority_bits
};

static const struct alloy_nvic_priority_setup
alloy_nvic_priority_setup[ALLOY_NVIC_PRIORITY_COUNT] = {
    { /*irqn*/ 0, /*priority*/ 0 },
    ...
};

void alloy_nvic_apply_priorities(void);  // walks the table
```

The table is built from `device.interrupts.vectors[*].priority` —
a new optional IR field consumers can populate per device.
Defaults that the YAML doesn't override stay at the chip's
documented reset value (priority = 0 for unset entries; the
table only emits non-zero rows).

`alloy_nvic_apply_priorities()` is intended to be called from
the consumer's reset handler before peripheral initialization.

### B. FPU enable helper

`system_init.c` (new artifact) emits a typed
`alloy_system_init_fpu(void)` whose body programs `SCB->CPACR`
when `core.fpu` is populated, or is a no-op otherwise.  The
emitter chooses the right `CPACR` field per FPU variant
(single-precision-only `fpv4-sp-d16` vs double-precision
`fpv5-d16` etc.).

### C. MPU base helper

`system_init.c` also emits `alloy_system_init_mpu(void)` which
programs the MPU's base configuration when `core.mpu` is
populated.  This is intentionally minimal — region-specific
attributes belong to a per-application MPU configuration; the
generated body just verifies the MPU exists, sets a sane
control word (`PRIVDEFENA=1, ENABLE=1`), and returns.

## Impact

- **Affected specs**:
  - **MODIFIED** `canonical-device-ir` — promotes `core.fpu`,
    `core.mpu`, and `core.nvic_priority_bits` from "round-trip
    metadata" to "executable contract" (requires an
    `interrupts.vectors[*].priority: int | None` optional
    field).
  - **MODIFIED** `artifact-contract` — `vector_table.c` grows
    a typed priority table; new `system_init.c` artifact
    becomes part of the published tree.
  - **MODIFIED** `runtime-lite-contract` — adds typed
    `alloy_nvic_apply_priorities()`, `alloy_system_init_fpu()`,
    `alloy_system_init_mpu()` accessors.
- **Affected code**:
  - `src/alloy_codegen/emit_v2_1/vector_table.py` — gains the
    priority-table emit path
  - new `src/alloy_codegen/emit_v2_1/system_init.py`
  - `cli.py::_EMITTERS` and `entrypoint.py::_EMITTERS` register
    the new emitter
- **Risks / trade-offs**:
  - **Per-vendor priority bit count is canonical, not opt-in**
    — `core.nvic_priority_bits` is published in the YAML.
    Emitter MUST refuse to emit a priority table when the
    field is absent; it MUST NOT default to "4 bits" (which
    is wrong for Cortex-M0+ and most M0 chips).
  - **MPU bring-up is intentionally minimal** — per-application
    region tables are out of scope; this proposal only emits
    the "you have an MPU, here's how to turn it on" helper.
    Region-specific configuration is left to the consumer.
  - **System-init ordering** — `alloy_system_init_fpu()` MUST
    run before any C++ static initializer with FP arithmetic;
    `alloy_nvic_apply_priorities()` MUST run before any
    interrupt is enabled.  The runtime-lite contract documents
    the ordering; consumers responsible for calling them in the
    right place.
- **Out of scope**:
  - Cache enable (Cortex-M7 ICache/DCache) — separate proposal
    once cache region attribution lands in the IR.
  - Per-region MPU configuration — application-specific, not a
    codegen concern.
  - Vendor-specific exception handlers (HardFault telemetry,
    BusFault recovery) — runtime-lite scope ends at "vector
    table is correct"; telemetry is alloy HAL's responsibility.
