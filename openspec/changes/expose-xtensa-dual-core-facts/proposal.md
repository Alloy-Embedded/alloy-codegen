# Expose Xtensa Dual-Core Bring-Up Facts In Published Descriptors

## Why
The codegen already implements the Xtensa dual-core control plane: the
ESP32 classic and ESP32-S3 emitters produce dual vector tables, two reset entry
points, and a `bring_up_app_cpu()` primitive that pokes the per-device APP_CPU
control register. The implementation is correct but **invisible from the
published descriptor's data-only surface**. The hard-coded register write
inside `runtime_xtensa_startup.py` is the single place that knows the address
`0x3FF0'0030` (LX6 DPORT.APPCPU_CTRL_B) or the LX7 SYSTEM.CORE_1_CONTROL_*
sequence; nothing in `registers.hpp`, `system_sequences.hpp`, or
`capabilities.json` records that the device is dual-core or what the
secondary-core release sequence looks like.

That gap blocks downstream consumers that have to reason about cores from
data, not C++:

- The alloy runtime's `add-esp32-classic-family` change cannot implement an
  `alloy::runtime::Core` / `current_core()` / `launch_on()` surface against
  a descriptor that does not declare `core_count = 2` or expose APP_CPU
  control register typed identifiers. It is gated explicitly on this work.
- A future tool that audits "which alloy targets are multi-core?" has to
  parse C++ headers because no JSON capability says so.
- A future on-silicon hardware bring-up runbook for ESP32-WROVER-KIT has
  no machine-readable lever to assert "the secondary-core release step
  was emitted at sequence position N".

The implementation already exists. This change is about lifting the facts
that drove the implementation into the artifact contract so they are
discoverable, typed, and inspectable from the published artefact alone.

## What Changes

### CanonicalDeviceIR: explicit multicore topology

Today the IR carries a stringly-typed `core` field on device metadata
(`"cortex-m0plus-dual"` for RP2040) and `VectorSlotDescriptor.core_affinity`.
The IR will gain:

- A typed `MulticoreTopology` value on device metadata that distinguishes
  single-core, RP2040-style symmetric dual-core, and Xtensa asymmetric
  dual-core (PRO_CPU + APP_CPU). Includes a `core_count` integer for
  trivial consumption.
- An `AppCpuControlPlane` record on devices whose topology is asymmetric
  Xtensa dual-core, naming the typed `RegisterId` of the control register
  (LX6: `register_dport_appcpu_ctrl_b`; LX7: `register_system_core_1_control_0`
  + `register_system_core_1_control_1`), the bit-level operation
  (`set bit 0` / `clear runstall`), and the start vector address symbol.
- The IR field MUST be `None` for single-core devices; consumers that do
  not care about cores ignore it, preserving backwards compatibility.

### registers.hpp: include APP_CPU control registers in the typed enum

The DPORT.APPCPU_CTRL_A/B/C/D registers exist in the upstream SVD but are
filtered out of `RegisterId` today because no driver schema references them.
The change adds them to the emission allow-list for ESP32 classic; the
analogous SYSTEM.CORE_1_CONTROL_0/1 registers are already emitted on
ESP32-S3 but are not currently flagged as control-plane-relevant.

A new `RegisterDescriptor.role` enum (or capability tag) marks the
control-plane registers so consumers can find them without name pattern
matching.

### system_sequences.hpp: emit a secondary-core-release step

A new `SystemSequenceStepKindId::secondary_core_release` is added. For
dual-core Xtensa devices the `default_bringup` sequence ends with this
step, which references the `AppCpuControlPlane` from the IR by typed id
rather than by raw address.

The step is emitted **only** on dual-core targets. Single-core devices are
unchanged. Consumers MAY choose to honor the step (alloy runtime calling
`bring_up_app_cpu()`) or skip it (a single-core firmware on a dual-core
chip).

### capabilities.json: multicore topology + core count

Three new device-level capability entries:

- `device:multicore-topology = "single-core" | "symmetric-dual-core" | "xtensa-dual-core"`
- `device:core-count = 1 | 2`
- For asymmetric Xtensa: `device:secondary-core-release-register =
  "register_dport_appcpu_ctrl_b"` (LX6) or the equivalent S3 identifier
  pair.

### Source data: ESP32 family.json patch

The patch overlay `patches/espressif/esp32/family.json` gains an explicit
`multicore_topology` block carrying the same facts so the normalizer has
an authoritative source. ESP32-S3 patch is updated with the LX7 variant.
ESP32-C3 (single-core RISC-V) is unaffected.

### Test goldens

Goldens for `esp32`, `esp32s3` are updated. A new positive test asserts
the secondary-core-release step exists and references a typed register
id. A negative test asserts the step is absent on `esp32c3` (single-core).

## Impact

- Affected specs:
  - `canonical-device-ir` (extended: explicit multicore topology + APP_CPU
    control plane; the existing "Xtensa dual-core families SHALL emit dual-
    core control plane" requirement gains data-driven discoverability
    scenarios)
  - `artifact-contract` (extended: registers.hpp emits control-plane
    registers; system_sequences emits the new step kind; capabilities.json
    surfaces multicore facts)
  - `vendor-admission` (modified scenario: ESP32 classic admission now
    asserts that emitted artefacts carry the multicore topology fact, not
    just that the family is admitted)

- Affected code:
  - `src/alloy_codegen/ir/model.py` — new `MulticoreTopology` enum +
    `AppCpuControlPlane` dataclass; nullable field on `Device`.
  - `src/alloy_codegen/sources/esp_idf.py` and the SVD normalizer — recognise
    APPCPU_CTRL_* registers and populate the new IR field.
  - `src/alloy_codegen/runtime_lite_emission.py` (or wherever registers.hpp
    is built) — include the control-plane registers in emission.
  - `src/alloy_codegen/runtime_system_sequences.py` — new step kind +
    emission.
  - `src/alloy_codegen/runtime_capabilities.py` — new device-level
    capabilities.
  - `patches/espressif/esp32/family.json` and
    `patches/espressif/esp32s3/family.json` — multicore_topology block.
  - `tests/fixtures/emitted/esp32/`, `tests/fixtures/emitted/esp32s3/`,
    `tests/fixtures/emitted/esp32c3/` — regenerated goldens; new
    assertions in `tests/test_espressif.py`.

- Out of scope:
  - **Affinity routing of individual interrupts.** Vector partitioning by
    `core_affinity` is already specified and out of scope for this change.
  - **Inter-core IPC, IPI, spinlocks, shared-memory cache invalidation.**
    The codegen continues to delegate those to esp-idf. The existing
    "Affinity routing and inter-core IPC are out of scope" scenario is
    preserved verbatim.
  - **Auto-calling `bring_up_app_cpu()` from `Reset_Handler`.** The
    primitive remains opt-in. Applications still invoke it explicitly
    (and in alloy's case, the runtime's startup will invoke it once the
    consumer-side change lands).
  - **Symmetric-multiprocessing scheduling primitives.** A scheduler that
    spans both cores belongs in alloy's runtime-tasks roadmap; this change
    only publishes the data needed for somebody to build one.
  - **ESP32-H2 (Xtensa LX7 single-core) and ESP32-C6.** Same vocabulary
    will work when those families are admitted, but neither is in this
    change.
