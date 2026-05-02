# Complete Clock-Tree Runtime Init (Body of `enter_<profile>()`)

## Why

Every admitted device (587/587 chips, 100%) ships at least one
populated `clock.profiles[]` entry — typically `default-hsi16-16mhz`
(post-reset) plus one or more `*-recommended` profiles like
`pll-hsi16-64mhz` for STM32 G0.  Profiles carry the target
`sysclk_source`, `hclk_hz`, `pclk_hz`, and (where relevant) PLL
divider triples (`pll_m/n/r`).

Today `runtime_init.c` only emits a **forward-declaration per
profile**:

```c
extern void alloy_clock_enter_default_hsi16_16mhz(void);
extern void alloy_clock_enter_pll_hsi16_64mhz(void);
```

There is no body.  The IR carries everything needed to write that
body — `clock.domains[*]` describes every mux and prescaler with a
typed `select_register` / `prescaler_register` triple
(`{reg, field, encoding}`); `clock.oscillators` carries the typed
oscillator catalogue (HSI/HSE/LSI/LSE/HSI48 etc.); `clock.pll`
carries the PLL coefficient ranges — but no emitter consumes any
of it.

The downstream consequence is concrete: `alloy_add_runtime_executable`
links the firmware against `runtime_init.o` and the resulting ELF
**boots at the post-reset clock** (8–16 MHz HSI on STM32, 4 MHz
MSI on rp2040, etc.) for every chip.  No project that wants
"60 MHz on a G0" or "480 MHz on an H7" can use the codegen
output directly — the user has to hand-write CMSIS clock setup,
which defeats the codegen's purpose.

This proposal lands the body.

## What Changes

`emit_runtime_init` is extended to walk
`device.clock.profiles[*]` and emit a complete
`alloy_clock_enter_<profile>(void)` C function for each.  Each
function:

1. Selects the target `sysclk_source` by walking
   `clock.domains[id == "sysclk_source"]`.  The domain's
   `select_register` triple (`{reg: "RCC.CFGR", field: "SW",
   encoding: {hsi: 0, ...}}`) translates into a single
   read-modify-write of that field with the encoded value.
2. If the profile names a PLL source (`sysclk_source: pll_*`),
   programs the PLL: powers down PLL → writes coefficient
   registers from `pll_m/n/r/p/q` triples carried on the profile
   → powers up PLL → spins on the lock bit (the IR carries
   `clock.pll.lock_field` so the emitter doesn't hard-code
   register names).
3. Programs HCLK / PCLK prescalers from the
   `clock.domains[id == "ahb_pre"|"apb_pre"|...]`.
   `prescaler_register` carries the encoding map
   (`{1: 0, 2: 8, 4: 9, ...}` for STM32 RCC.CFGR.HPRE/PPRE).
4. For STM32 chips with FLASH wait-state requirements,
   programs `FLASH.ACR.LATENCY` from the family-level
   `flash_wait_states` table indexed by target HCLK.

**Per-vendor backend dispatch** is structured as `ClockBackend`
adapters keyed by vendor (`st`, `microchip`, `nxp`, `raspberrypi`,
`espressif`).  Each backend exports a single
`emit_profile_body(device, profile, domains, oscillators) -> str`.
The emitter has zero per-vendor branches; adding a vendor adds an
adapter module.

Backends shipped in this change:

- **`st` ClockBackend** — covers STM32 F0/F1/F3/F4/G0/G4/H7
  (514 chips).  Reads `RCC.*` register/field refs from
  `clock.domains`; understands HSI/HSE/HSI48/MSI oscillator
  selection and FLASH latency tables.
- **`microchip-sam` ClockBackend** — covers SAM E70/V71 (PMC
  + EFC) and SAM D21/D51/L21 (GCLK + OSCCTRL).  These are two
  distinct sub-backends because the PIO-flavour SAM chips
  (E70/V71) and the GCLK-flavour SAM chips (D21/D51/L21) have
  different clock-tree topologies.
- **`nxp-imxrt` ClockBackend** — minimal: iMX RT 1060 boots
  from external SEMC / FlexSPI quirks, but the runtime_init
  responsibility ends at "enter the recommended profile";
  external memory bring-up stays in the dedicated
  `flexspi_init.c` (out of scope here).
- **`raspberrypi-rp` ClockBackend** — RP2040 PLL_SYS / PLL_USB
  + CLK divider chain.
- **`espressif-soc` ClockBackend** — ESP32 / S3 / C3 SOC PLL +
  CPU/APB divider; emits the minimal "enter recommended"
  body and defers ESP-IDF clock-source switches to the
  app-layer.

## Impact

- **Affected specs**:
  - **MODIFIED** `runtime-lite-contract` — `enter_<profile>()`
    moves from "declared but unimplemented" to
    "executable, deterministic, byte-stable".
  - **MODIFIED** `artifact-contract` — `runtime_init.c` gains
    a guaranteed body for every published profile.
  - **MODIFIED** `canonical-device-ir` — clock-domain
    `select_register` and `prescaler_register` triples are
    promoted from "carry-through metadata" to "executable
    contract": every populated triple SHALL be sufficient to
    program its mux without supplemental data.
- **Affected code**:
  - `src/alloy_codegen/emit_v2_1/runtime_init.py` — gains the
    profile-body dispatcher
  - new `src/alloy_codegen/emit_v2_1/clock_backends/st.py`,
    `microchip_sam.py`, `microchip_samd_gclk.py`,
    `raspberrypi_rp.py`, `espressif_soc.py`
  - `tests/fixtures/emitted/<vendor>/<family>/<chip>/runtime_init.c`
    goldens regenerated for every admitted device
  - new `tests/test_clock_backends.py` per-backend unit tests
- **Risks / trade-offs**:
  - **Per-vendor PLL math correctness** — getting STM32 G0's
    `(M=1, N=8, R=2)` for 64 MHz right is straightforward;
    H7's three-domain RCC (D1/D2/D3 separate prescalers) is
    fiddly.  Mitigation: per-family golden fixtures + a
    smoke test that boots a STM32 G0 nucleo at 64 MHz on
    the existing CI HW-in-the-loop path (if available) or
    a QEMU-based instruction-trace gate.
  - **FLASH latency calculation** — getting the WS table
    from the IR is non-trivial because some STM32 families
    publish it as a peripheral metadata block while others
    bake it into the family.yml.  This proposal adds a
    `flash_wait_states: tuple[FlashLatencyEntry, ...]`
    field on `Identity` derived from family.yml during
    YAML loading.
  - **Profile mismatch** — if the YAML claims a profile is
    recommended but the IR's domain graph cannot reach the
    target HCLK, the emitter SHALL raise
    `StageExecutionError` at synthesis time instead of
    emitting a body that hangs at boot.
- **Out of scope**:
  - Dynamic profile switching at runtime (today's profiles
    are one-shot at startup).  A future proposal can add
    `runtime_clock_switch(profile_id)` once peripheral-class
    drivers learn to suspend before the switch.
  - Non-bring-up clocks (per-peripheral kernel-clock
    selection, e.g. STM32's `RCC.CCIPR.USART1SEL`).  Those
    are programmed by the peripheral-class HAL when it
    opens the instance; the codegen exposes the encoding
    via `pin_router`-style typed accessors as a follow-up.
