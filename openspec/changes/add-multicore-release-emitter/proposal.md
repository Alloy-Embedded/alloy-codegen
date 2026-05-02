# Add Multicore Release Emitter (`multicore_release.{c,h}`)

## Why

The canonical IR carries a `Multicore` block with five fields
purpose-built for second-core release: `MulticoreCore.id`,
`role`, `vector_base`, `release_register`, `release_op`,
`start_vector_symbol`, and `app_cpu`.  None of those fields are
populated on any of the 587 admitted chips today, but the dataclass
is in `ir/v2_1/identity.py` waiting for data.

Meanwhile, in `linker_script.py`, the multicore handling **already
exists** — but as a hardcoded heuristic that pattern-matches
`sram_bank4` / `sram_bank5` memory region names and assumes those
are the second-core stacks.  That heuristic is silently wrong for
RP2040 (uses scratch memory) and pre-emptively wrong for any future
chip where the data team uses different region names.

The Alloy product needs at least one supported dual-core target
(rp2040 → rp2350 next year, esp32-p4, imxrt117x), and every one
needs the **release protocol** committed to a stable artifact:
"to start core 1, write value V to register R, then make sure
core 1's vector base points at symbol S".  Today the consumer
either reads the chip's reference manual or copies vendor SDK code.

## What Changes

A new emitter `emit_multicore_release` produces two artifacts:

### `multicore_release.h`

A typed runtime-lite header carrying the per-core release
descriptors:

```cpp
struct alloy_multicore_release {
    uint8_t  core_id;           // 0..N-1
    uint8_t  role_kind;         // typed enum (Boot, App)
    uint32_t vector_base_addr;  // VTOR for the secondary core
    uint32_t release_register_addr;
    uint32_t release_value;
    uint32_t release_mask;
    void   (*start_vector_symbol)(void);
};

extern const struct alloy_multicore_release
    alloy_multicore_release_table[ALLOY_MULTICORE_RELEASE_COUNT];

void alloy_multicore_release_core(uint8_t core_id);
```

### `multicore_release.c`

The companion source file populating
`alloy_multicore_release_table[]` from
`device.identity.multicore.cores[*]` and defining
`alloy_multicore_release_core(uint8_t)` whose body looks up the
core by id, writes its `release_value` into `release_register_addr`,
and barriers.

`linker_script.py` is **simplified** — the existing
`sram_bank4/sram_bank5` heuristic is removed.  Instead, the linker
script declares the second-core stack symbol from
`MulticoreCore.start_vector_symbol` and sources its memory region
from the `MulticoreCore.role` mapping (the IR already carries the
correct memory region; the heuristic was workaround code).

For chips without a populated `identity.multicore` block, the
new emitter writes a stub `multicore_release.h` declaring
`ALLOY_MULTICORE_RELEASE_COUNT == 0` and a no-op
`alloy_multicore_release_core()`.  Single-core consumers compile
without modification; the cost is one symbol that gets
dead-code-eliminated.

## Impact

- **Affected specs**:
  - **MODIFIED** `canonical-device-ir` — promotes `Multicore`
    and `MulticoreCore` from "round-trip metadata" to
    "executable contract"; admission of a multicore chip
    REQUIRES the block to be populated.
  - **ADDED** `artifact-contract` — `multicore_release.{c,h}`
    is a new published artifact pair under the runtime-lite
    contract.
  - **MODIFIED** `runtime-lite-contract` — adds typed
    `alloy_multicore_release_table[]` and
    `alloy_multicore_release_core()` accessors;
    documents the call ordering contract.
- **Affected code**:
  - new `src/alloy_codegen/emit_v2_1/multicore_release.py`
  - `src/alloy_codegen/emit_v2_1/linker_script.py` —
    remove `sram_bank4/5` heuristic; read multicore stack
    symbols from IR
  - `cli.py::_EMITTERS` and `entrypoint.py::_EMITTERS`
    register the new emitter
  - `ir/v2_1/identity.py` — tighten `MulticoreCore`
    validation
- **Risks / trade-offs**:
  - **Backwards compat with current linker scripts** — STM32
    H745/H755 dual-core chips are not yet admitted; removing
    the `sram_bank4/5` heuristic does not regress any active
    output.  The change is verifiable by running the existing
    golden suite (no goldens carry the heuristic).
  - **Per-vendor release protocol diversity** —
    - **ARM Cortex-M dual-core** (STM32 H745, H755): release
      via `RCC.GCR.BOOT_C2 = 1` and the second core picks up
      from VTOR.
    - **RP2040**: write to FIFO mailbox `SIO_FIFO_WR` with a
      handshake sequence; `start_vector_symbol` is the
      address pushed to FIFO.
    - **iMX RT 117x**: write CCM `SRC.SCR.M7_SW_RESET` and
      VTOR through `IOMUXC_LPSR_GPR.M7_INIT_VTOR_LOW/HIGH`.
    - **ESP32 (LX7+RV32 dual)**: write
      `RTC_CNTL.SW_CPU_STALL` and `OPTIONS0.APPCPU_RESETTING`.

    All four shapes lower to the same `release_value`/
    `release_register_addr`/`release_mask` triple in the IR;
    the per-vendor knowledge lives in the YAML, not the
    emitter.  No `if vendor == "rp"` in this proposal.
  - **Vector-base programming on Cortex-M** — secondary
    cores need their VTOR set before the release write.
    The emitter handles this via a typed
    `alloy_multicore_setup_vtor(core_id, vector_base_addr)`
    helper called inside
    `alloy_multicore_release_core()`; on architectures where
    VTOR is in shared memory (RP2040 SIO), the helper is a
    no-op.
- **Out of scope**:
  - **Inter-core synchronisation primitives** (mailboxes,
    spin locks, shared-memory coherency).  Those belong to
    alloy HAL's `multicore::channel` series.  This proposal
    only covers the **release** moment.
  - **Hot CPU re-entry** — re-launching a core after halt
    is more involved than the cold-start release this
    proposal covers.
  - **Heterogeneous core families** (ESP32 LX7 + RV32-IMC,
    iMX RT 117x M7 + M4) — the IR carries `MulticoreCore.app_cpu:
    bool` to flag the asymmetric core, but the emitter does
    not change ISA-specific reset code.  The asymmetric ISA
    is the consumer's problem on the second-core firmware
    side.
