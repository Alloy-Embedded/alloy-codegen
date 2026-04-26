# Design: Expose Xtensa Dual-Core Bring-Up Facts

## Context

The codegen already emits a working dual-core control plane for ESP32 classic
and ESP32-S3:

- `runtime_xtensa_startup.py` produces `_vectors_cpu0[]` / `_vectors_cpu1[]`,
  `Reset_Handler` / `Reset_Handler_CPU1`, and `bring_up_app_cpu()`.
- `bring_up_app_cpu()` writes the per-device CPU-1 control register sequence
  (LX6: `DPORT.APPCPU_CTRL_B` bit 0; LX7: `SYSTEM.CORE_1_CONTROL_0.CLKGATE_EN`
  + clear `SYSTEM.CORE_1_CONTROL_1.RUNSTALL`).

The implementation is correct but the **facts** that drive it (which register
is the CPU-1 release lever, what bit, what the start vector address is, that
the device is dual-core at all) live only inside the Python emitter. They
are not represented anywhere in the published descriptor's data-only surface
(`registers.hpp`, `system_sequences.hpp`, `capabilities.json`, IR JSON).

This change does not add new dual-core capability. It promotes the facts that
already drove the working implementation into the IR and the published
artifacts so downstream consumers can reason about cores from data.

The immediate driver is alloy's `add-esp32-classic-family` change (phase 4 of
its tasks list), which is gated explicitly on this work: alloy cannot expose
`alloy::runtime::Core` / `current_core()` / `launch_on()` against a descriptor
that does not declare `core_count = 2` or surface the APP_CPU control register
as a typed `RegisterId`.

## Goals / Non-Goals

### Goals

1. Surface `MulticoreTopology` (single / symmetric / xtensa-asymmetric) and
   `core_count` on the IR `Device` so any consumer can branch on topology
   without parsing strings.
2. Surface the APP_CPU control plane (typed register id, bit operation,
   start-vector symbol) on the IR for asymmetric Xtensa devices.
3. Emit those facts in the artifacts:
   - `registers.hpp` includes the control-plane registers and tags them via
     a new `RegisterDescriptor.role` enum.
   - `system_sequences.hpp` ends the `default_bringup` sequence on dual-core
     devices with a `secondary_core_release` step that references the typed
     register id.
   - `capabilities.json` carries `device:multicore-topology`,
     `device:core-count`, and (for asymmetric Xtensa)
     `device:secondary-core-release-register`.
4. Stay backwards compatible: single-core devices ignore the new fields;
   `MulticoreTopology` defaults to `single-core`; the new sequence step is
   absent on single-core targets.

### Non-Goals

- **No new dual-core implementation work.** `bring_up_app_cpu()` already
  exists and works; this change is plumbing, not new capability.
- **No interrupt affinity changes.** `VectorSlotDescriptor.core_affinity` is
  already specified and out of scope here.
- **No inter-core IPC, IPI, spinlocks, cache coherency.** Still delegated.
- **No new families.** ESP32-H2, ESP32-C6, etc. will reuse the vocabulary
  when they're admitted; not in this change.
- **No automatic invocation of `bring_up_app_cpu()` from `Reset_Handler`.**
  The primitive remains opt-in.

## Key Decisions

### Decision 1: `MulticoreTopology` is a typed enum, not a free-form string

The IR currently carries a stringly-typed `core` field (e.g. RP2040 has
`"cortex-m0plus-dual"`). That string was fine for human inspection but
unsuitable for downstream branching: a consumer has to know that
`*-dual` means dual-core, that ESP32 is asymmetric, etc.

Replacing it with a typed enum (`single_core`, `symmetric_dual_core`,
`xtensa_asymmetric_dual_core`) plus an explicit `core_count: int` makes the
contract type-checkable in Python and self-documenting in JSON. Consumers
that do not care about cores ignore both fields.

**Backwards compat:** the existing `core` string field stays for one cycle
as a derived diagnostic alias, then is removed in a follow-up. The IR JSON
emitter writes both during the transition.

### Decision 2: `AppCpuControlPlane` is a separate optional record, not enum-tagged data

I considered putting the LX6/LX7 register details inside the topology enum
itself (e.g. variant-style with payload). Two reasons not to:

1. The Python IR uses dataclasses, not tagged unions. A nullable sibling
   field is more natural and serializes more cleanly to JSON.
2. The control-plane shape might expand later (cache invalidation step,
   secondary stack pointer, etc.) without forcing every consumer that only
   wanted to branch on topology to change.

So: `Device.multicore_topology: MulticoreTopology` (always present, defaults
to `single_core`) and `Device.app_cpu_control_plane: AppCpuControlPlane | None`
(populated only for asymmetric Xtensa).

### Decision 3: New `secondary_core_release` step kind, not a reused `startup-control`

Existing `SystemSequenceStepKindId` values (`startup-descriptor`,
`startup-control`, `system-clock-profile`) are coarse — they describe phases
of bring-up. Adding a fine-grained `secondary_core_release` step:

- Lets the consumer tell at a glance whether a target is dual-core (the step
  is present) without parsing topology fields separately.
- Lets the runtime emit `bring_up_app_cpu()` invocations at exactly the right
  point (after clocks, before app code).
- Keeps the step opt-in: a single-core firmware on a dual-core chip can skip
  this step without weakening any other phase.

Reusing `startup-control` would force consumers to inspect the step's payload
to find out whether it actually contains a CPU release.

### Decision 4: `RegisterDescriptor.role` enum, not a free-form tag list

Today the only way to find APP_CPU control registers in `registers.hpp` is to
match on the name `register_dport_appcpu_ctrl_b`. That breaks the contract's
"discoverable from data, not strings" rule.

A typed `role` field with a small enum (`general`, `secondary_core_release`,
…) lets consumers find the relevant register by enum equality. Future roles
(e.g. `cache_control`, `bootrom_lock`) can be added without breaking
existing consumers — unknown roles fall back to `general`.

### Decision 5: Source-data is authoritative; the normalizer is a derivation

The dual-core facts are not in upstream Espressif SVD — they live in the IDF
docs and the bootrom code. Putting them in `patches/espressif/esp32/family.json`
(and the analogous `esp32s3/family.json`) keeps the normalizer free of
hardcoded vendor knowledge. The normalizer reads `multicore_topology` from
the patch overlay and resolves the typed register id at IR-build time.

This matches the precedent set by clock graphs and reset-domain overrides.

### Decision 6: Goldens are regenerated, not partially patched

Spot-patching goldens for the new fields without regenerating them risks
divergence. The change regenerates `tests/fixtures/emitted/{esp32,esp32s3}/`
in full and adds explicit positive (step present + register typed id) and
negative (step absent on `esp32c3`) assertions in `tests/test_espressif.py`.

## Risks & Trade-offs

- **Schema churn for downstream consumers.** Any tool that parsed
  `capabilities.json` will see three new keys; we mitigate by defaulting
  every key to a single-core-safe value. The new IR fields are nullable.
- **`role` enum growth pressure.** If we add a role per use case, the enum
  becomes a dumping ground. Mitigation: only add a role when at least one
  consumer needs to find a register by it without name matching.
- **Patch overlay divergence.** Two patch files (esp32, esp32s3) now carry
  the same shape; future Xtensa parts must add their own. Mitigated by a
  validator step that asserts asymmetric Xtensa devices have a populated
  `multicore_topology` patch block.
- **One-cycle dual representation of `core`.** During the transition the IR
  carries both the legacy string `core` and the new `multicore_topology`.
  Mitigated by a documented removal in the next archive cycle.

## Open Questions

1. **Should `core_count` ever exceed 2?** The current ESP32 lineup is 1 or 2.
   ESP32-P4 has more cores; out of scope for this change but the int field
   is forward-safe.
2. **Cache flush as a separate step?** ESP32-S3 needs a cache invalidation
   between APP_CPU release and the secondary core executing app code. For
   now this is folded into `bring_up_app_cpu()`'s body; if it ever needs to
   be called independently, it gets its own step kind. Not addressed here.
3. **Does `secondary_core_release` need a payload describing what to invoke?**
   Today the step references the `AppCpuControlPlane` by typed register id;
   the runtime maps that to `bring_up_app_cpu()`. If a consumer wants to
   inline the writes, the typed register id is enough. No payload needed.

## Migration Plan

1. Land IR changes (new enum, new dataclass, new `role` field) behind the
   default values so existing fixtures still validate.
2. Land emission changes; regenerate goldens; add tests.
3. Land patch overlays for esp32 + esp32s3.
4. After this change archives, the alloy `add-esp32-classic-family` change
   can unblock its phase 4 by reading `core_count` from `capabilities.json`
   and `device:secondary-core-release-register` to pick the typed register.
