# Changelog

All notable changes to alloy-codegen are recorded in this file.

The format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/);
versions follow [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.5.0] — 2026-05-03

### Connector + route emitters — cross-peripheral, cross-vendor

Two new on-demand emitters replace the deleted bulk-pipeline tools:

#### `connectors.hpp` — compile-time routing validation

`emit_v2_1.emit_connector_traits(device, synthesised)` generates a full
`ConnectorTraits<PinId, PeripheralId, SignalId>` specialisation tree for
every valid `(pin, peripheral, signal)` triple in the device's pin-routes
table.  The artifact is consumed by `alloy/src/hal/connect/runtime_connector.hpp`.

Emitted types per device:
- `PinId`, `PeripheralId`, `SignalId`, `RouteKindId`, `ConnectionGroupId`,
  `RouteId`, `ConnectorId` typed enums.
- Full specialisations (`kPresent = true`) for every valid triple.
- Guard A partial specs — `static_assert` for a wrong pin on a known
  peripheral+signal pair.
- Guard B partial specs — `static_assert` for a wrong peripheral on a
  known pin+signal pair.
- `ConnectorSignalTraits<Peri, Signal>` with the valid-pins array.
- `kConnectors` descriptor table.

#### `routes.hpp` — runtime routing code table

`emit_v2_1.emit_routes(device, synthesised)` generates the `RouteDescriptor`
struct and `kRoutes` lookup table (`route_kind + hw_code` per route).
`code = 0xFFFFu` is the sentinel for routes whose YAML has not yet been
enriched with AF / FUNCSEL / ABCDSR values.

#### SAME70 / SAMV71 PIO backend

`emit_v2_1.pinmux_backends.sam_pio` implements the Microchip SAM PIO
matrix-function backend (`alloy.pinmux.sam-matrix-function-v1`).  Registered
for `("microchip", "same70")` and `("microchip", "samv71")`.

ATSAME70Q21B synthesises **497 routes** spanning UART, USART, SPI, I2C (TWIHS),
AFEC (ADC), DACC, CAN, Ethernet, SDRAMC, PIOA–PIOE — all peripherals in
one shot, without any per-peripheral per-family special-casing.
`code = None` until the YAML enrichment pass adds A/B/C/D function-letter
integers to each `PinOptionFixed` row.

### Removed

- `tools/bump_devices_yml.py` — submodule-pin bumper, superseded by the
  per-device emit path.
- `tools/runtime_cpp_smoke.py` — bulk clang++ runner, superseded by
  `tests/test_compile_smoke.py` (per-device smoke via pytest fixture).
- `tests/codegen/published_runtime_lite_contract_smoke.cpp` — pre-generated
  artifact smoke template; the new `smoke_connector_routes.cpp` covers the
  same ground.

### Tests

- 35 new tests for the connector-traits and routes emitters.
- `test_pin_router::test_unsupported_vendor_emits_empty_routes` updated to
  use RP2040 (SAME70 now has a backend; RP2040 FUNCSEL is still pending).

## [0.4.0] — 2026-05-03

### Type-safe RCC trait surface (BREAKING CHANGE)

The four dotted-path strings on every peripheral struct
(`kRccEnable`, `kRccReset`, `kKernelClockMux`, `kBus`) are replaced
with typed C++ values resolved at codegen time.  HAL drivers no
longer need to parse strings at runtime; every typed value folds
to an immediate at `-O2`.

#### Before (v0.3.x)
```cpp
struct lpuart1 {
    static constexpr const char * kBus            = "APB1";
    static constexpr const char * kRccEnable      = "rcc.apbenr1.lpuart1en";
    static constexpr const char * kRccReset       = "rcc.apbrstr1.lpuart1rst";
    static constexpr const char * kKernelClockMux = "rcc.ccipr.lpuart1sel";
};
```

#### After (v0.4.0)
```cpp
struct lpuart1 {
    static constexpr Bus         kBus            = Bus::apb1;
    static constexpr RccGate     kRccEnable      = { 0x4002103Cu, 0x00100000u };
    static constexpr RccGate     kRccReset       = { 0x4002102Cu, 0x00100000u };
    static constexpr RccMuxField kKernelClockMux = { 0x40021054u, 0x00000C00u, 10u, 2u };
};
```

#### New types in `rcc_traits.hpp`
- **`enum class Bus`** — closed enumeration replacing the vendor
  bus-tag strings.  Members: `apb`, `apb1..apb4`, `ahb`,
  `ahb1..ahb4`, `dport`, `system`, `pcr`, `ccgr`, `mclk`, `pm`,
  `pmc`, `resets`, plus the `unknown` sentinel.
- **`struct RccGate`** — `{ uintptr_t addr; uint32_t mask; }`.
  Used by `kRccEnable` and `kRccReset`.  HAL writes
  `*reinterpret_cast<volatile uint32_t*>(g.addr) |= g.mask;`
  which folds to a single 5-instruction RMW at `-O2`.
- **`struct RccMuxField`** — `{ uintptr_t addr; uint32_t mask;
  uint8_t lsb; uint8_t width; }`.  Used by `kKernelClockMux` for
  multi-bit kernel-clock selectors.  HAL writes the standard
  read-modify-write with shift-and-mask; ARM Cortex-M compiles
  this to `bfi` (bit field insert) — one instruction.

#### Codegen-time resolution
A new shared module `_rcc_path_resolver.py` converts every
synthesiser-emitted dotted path
(`"rcc.apbenr1.lpuart1en"`, `"CCM_CCGR5.CG12"`,
`"gclk.pchctrl7.gen"`) into a `(absolute_addr, mask, lsb, width)`
tuple at codegen time.  Both `peripheral_traits.py` and
`rcc_enable.py` consume it, so the two emitters cannot drift.

The resolver also handles array-style registers
(`pchctrl7.gen` → `pchctrl_base + 7*4 + field`) so SAMD51 / SAML21
GCLK kernel-clock muxes resolve to absolute addresses without
requiring per-vendor IR support.

#### Verified machine code

A HAL probe TU using `clk_enable<P>()`, the typed `kRccEnable`
struct, and a hand-written MMIO write produces **byte-identical
machine code** for all three paths at `-O2`:

```
typed struct:    6 instructions, 24 bytes
hand-written:    6 instructions, 24 bytes
specialisation:  6 instructions, 24 bytes
```

Multi-bit `RccMuxField` writes compile to ARM's `bfi` (bit
field insert) — a single instruction.

#### Migration

HAL drivers using the old string fields:

```cpp
// OLD — string parsing required
if (strcmp(P::kBus, "APB1") == 0) { ... }
parse_dotted_path(P::kRccEnable);
```

must migrate to:

```cpp
// NEW — typed dispatch
if constexpr (P::kBus == Bus::apb1) { ... }
*reinterpret_cast<volatile uint32_t*>(P::kRccEnable.addr)
    |= P::kRccEnable.mask;
```

The unchanged surface is the `clk_enable<P>()` template
specialisations in `rcc_enable.hpp` — they continue to work
across all 5 GateModel branches without modification.

#### Edge cases

- Paths that don't resolve (template missing, malformed inline
  YAML) fall back to a `kRccEnableRaw` / `kRccResetRaw` /
  `kKernelClockMuxRaw` field carrying the original string,
  marked with a TODO comment.  This keeps the surface
  observable while signalling that an upstream YAML fix is
  needed.

## [0.3.1] — 2026-05-03

### Fixed

- **`rcc_enable.hpp` always_on portability gap** — peripherals on
  silicon without per-peripheral gates (every peripheral on AVR-Dx
  / NRF52, plus system-control peripherals on every other vendor)
  now emit no-op specialisations for `clk_enable<P>()`,
  `clk_disable<P>()`, `rst_assert<P>()`, `rst_release<P>()`,
  `peripheral_on<P>()`.  HAL drivers can now call these
  uniformly across vendors; on always-on silicon the call site
  evaporates to zero instructions after inlining.  Previously,
  the same call would hit the primary template's `= delete` and
  fail to compile.

### Added

- **`rcc_gate_table.hpp` (10th emitted artifact)** — per-device
  RCC enable-gate lookup table with `(dotted_path, absolute_addr,
  bit_mask)` rows.  Consumed by `device/rcc_gate_table.hpp`
  (alloy-hal) when string-keyed gate lookup is needed (e.g.,
  power-management code that walks `kRccEnable` paths
  generically).  Direct-MMIO callers continue to use the
  zero-overhead `clk_enable<P>()` template specialisations from
  `rcc_enable.hpp`.

### Analysis (no behaviour change)

Trait-surface measurement on the five reference fixtures
(stm32g0b1cbtx, rp2040, mimxrt1062, avr64da32, esp32c3) confirms:

* **Zero runtime overhead** — a HAL probe exercising
  `kBaseAddress`, `kGateModel` `constexpr if`, `kIrqLines[0]`,
  and `kBaseAddress + register_offset` compiles to **56 bytes
  of `__TEXT`** at `-O2`.  Every `static constexpr` collapses
  to immediate-value loads.
* **Zero binary bloat** — including all ten emitted headers
  (1.9 MB of `peripheral_traits.h` on iMXRT) without referencing
  any symbol produces an **8-byte object file** at `-O2`.
  `inline constexpr` is ODR-emitted only when used.
* **Trait-surface uniformity** — universal core fields
  (`kName`, `kTemplate`, `kBaseAddress`) are at 100% coverage.
  `kGateModel` covers 80.5% of all peripherals across vendors;
  the remaining ~20% are system-control peripherals without
  gates, which is silicon-correct.

## [0.3.0] — 2026-05-02

### Cross-vendor RCC synthesis + GateModel enum + compile gate

`alloy-codegen` now produces nine artifacts per device (was six) and
synthesises clock-gate / reset / kernel-clock-mux paths for **every
admitted vendor**:

```
out/<vendor>/<family>/<chip>/
├── linker.ld
├── peripheral_id.hpp        (new — typed PeripheralId enum)
├── peripheral_traits.h      (extended — kBus, kRccEnable, kRccReset,
│                                        kKernelClockMux, kGateModel)
├── pin_router.h
├── rcc_enable.hpp           (new — direct-MMIO clock-gate helpers)
├── rcc_traits.hpp           (new — typed `enum class GateModel`)
├── runtime_init.c
├── system_init.c
└── vector_table.c
```

#### Added

- **Cross-vendor RCC synthesis** (`complete-rcc-synthesis-cross-vendor`):
  - **Espressif ESP32 / C3 / S3** — DPORT (esp32), SYSTEM
    `perip_clk_en0/1` + `cpu_peri_clk_en` (c3/s3), and PCR
    `<peri>_conf_reg` self-contained gates.  Hand-curated alias
    map in `vendor_tables/espressif_clock_gates.py` resolves
    legacy naming (`uart_clk_en` → `uart0`, `crypto_aes` → `aes`,
    `timergroup` → `timg0`, `spi01` shared between spi0+spi1).
  - **NXP iMXRT 1060** — full CCGR PID table from RM 14-5
    (`vendor_tables/nxp_imxrt_ccgr.py`); mimxrt1062 jumps from
    30 → 92 mapped peripherals.
  - **Microchip SAM family** — GCLK kernel-clock-mux indices for
    SAMD21 (`CLKCTRL.id<N>`), SAMD51/SAML21/SAML22
    (`PCHCTRL[N].gen`).
  - **AVR-Dx + Nordic NRF52** — explicit `always_on` marker pass
    for silicon without per-peripheral gates.
- **GateModel enum on the alloy boundary** (`rcc_traits.hpp`):
  `always_on`, `per_peri_en`, `per_peri_en_rst`, `index_based`,
  `per_peri_pcr`.  Every peripheral's `kGateModel` constexpr line
  drives `constexpr if` dispatch in alloy HAL drivers.
- **Per-device compile gate** (`add-alloy-hal-compile-gate-per-device`):
  `scripts/run_compile_gate.py` drives `clang++ -Wall -Werror
  -Wundef` over a generated probe TU per admitted device.  CI job
  hard-fails on five reference fixtures (one per `GateModel`)
  and report-only on the full 587-device matrix.

#### Fixed

Five emitter bugs surfaced by the compile gate (latent — golden
text equality is weaker than C++ well-formedness):

- `rcc_enable.py` — primary template `= delete` declarations
  needed `noexcept` to match specialisation signatures.
- `peripheral_traits.py` — namespace path didn't sanitise hyphens
  (`alloy::microchip::avr-da::…` invalid C++).  Now sanitises
  vendor + family + device.
- `peripheral_traits.py` — C++ reserved keywords in enum entry
  names (e.g. `default` from AVR-Dx ATDF) now suffixed with `_`.
- `peripheral_traits.py` — unresolved template placeholders
  (`%s`, `<n>`) in vendor YAML register / field names now
  skipped at emit-time.
- `pin_router.py` — same hyphen-sanitisation bug as
  `peripheral_traits.py`; fixed via `_safe_c_id` wrapper.

#### Coverage

| Family | Mapped peripherals | GateModel branch |
|--------|-------------------|------------------|
| STM32 (F0/F1/F3/F4/G0/G4/H7) | 39+ per chip | `per_peri_en_rst` + `per_peri_en` |
| RP2040 | 24 | `per_peri_en` |
| Microchip SAMD51 | 46 + 26 GCLK muxes | `per_peri_en` |
| Microchip SAMD21 | 26 + GCLK CLKCTRL | `per_peri_en` |
| NXP iMXRT 1062 | 92 (was 30) | `index_based` |
| Espressif ESP32-C3 | 25 (was 4) | `per_peri_en_rst` + `per_peri_pcr` |
| Espressif ESP32-S3 | 33 (was 7) | `per_peri_en_rst` |
| Espressif ESP32 | 20 (was 6) | `per_peri_en_rst` |
| Microchip AVR-Dx | 47 (all) | `always_on` |
| Nordic NRF52 | 7 (all) | `always_on` |

## [0.2.0] — 2026-05-02

### Generator parity with canonical-device v2.1

`alloy-codegen` produces six artifacts per device now (was four),
covering the full bring-up surface alloy HAL needs to compile and
boot a chip end-to-end without per-vendor escape hatches:

```
out/<vendor>/<family>/<chip>/
├── linker.ld
├── peripheral_traits.h
├── pin_router.h          (new in 0.2.0 — `pins.h`)
├── runtime_init.c
├── system_init.c         (new in 0.2.0)
└── vector_table.c
```

#### Added

- **`pins.h` (new artifact)** — typed `enum class pin::id` per
  device + `kRoutes` table mapping every
  `(peripheral_instance, signal, pad)` triple admitted by the IR's
  `peripherals[*].pin_options`.  Backend dispatch via a
  `PinmuxBackend` Protocol; first vendor backend covers STM32 AF
  (`alloy.pinmux.stm32-af-v1`, 514 admitted chips).  STM32
  alternate-pin annotations (`PA12 [PA10]` / `PC15-OSC32_OUT`)
  are normalised at synthesis time.
- **`system_init.c` (new artifact)** — `alloy_system_init_fpu()`
  programs `SCB->CPACR` for Cortex-M with FPU; `alloy_system_init_mpu()`
  enables the MPU with `PRIVDEFENA=1` for Cortex-M with MPU; both
  are explicit no-ops on cores without the feature.  Umbrella
  `alloy_system_init()` calls fpu → mpu → `alloy_nvic_apply_priorities()`
  in the documented order.
- **NVIC priority surface in `vector_table.c`** —
  `alloy_nvic_priority_setup[]` table built from
  `InterruptVector.priority`; `alloy_nvic_apply_priorities()` is
  always defined so consumers can call it unconditionally even when
  no vector carries an explicit priority.
- **Clock-tree dispatch in `runtime_init.c`** —
  `alloy_clock_enter_<profile_id>()` carries an executable body
  per `clock.profiles[]` entry: FLASH WS programming, PLL coefficient
  writes, PLL lock spin, SYSCLK switch + SWS readback, DSB/ISB
  barriers.  Lowering goes through a per-vendor `ClockBackend`
  Protocol; STM32 backend covers F0/F1/F3/F4/G0/G4/H7.  Profiles
  whose YAML lacks `hclk_hz` degrade to a documented stub instead
  of crashing synthesis.
- **Rich `peripheral_traits.h`** — new `calibration::{vrefint,
  ts_cal_low, ts_cal_high}` and `external_triggers::{regular,
  injected}` sub-namespaces for ADC instances; `timing_presets`
  for I²C; `trigger_sources` / `master_outputs` /
  `deadtime_options` / `break_inputs` for advanced timer
  templates.  Coverage on the admitted corpus: 514 ADCs with
  calibration, 269 with external triggers, 181 with timer matrix.
- **IR additions** — first-class `ClockProfile.hclk_hz`,
  `pclk_hz`, `pll_m/n/r/p/q/frac`, `flash_latency_hz`;
  `Identity.flash_wait_states: tuple[FlashLatencyEntry, ...]`;
  `InterruptVector.priority: int | None`; new
  `SynthesisedDevice.clock_program_steps` and `pin_routes` fields.

### Changed

- **CI (`bootstrap-family.yml`, `publish-alloy-devices.yml`)** —
  removed.  alloy-codegen no longer publishes generated artifacts
  to a separate `alloy-devices` repository.  Consumers obtain the
  CLI from PyPI and run it directly against their project's
  device data.  Pre-merge tests run via the new lean
  `.github/workflows/tests.yml`.
- **Submodule pin** — `data/devices` advanced from `bd4015e` to
  `2f10ac0`, expanding the admitted corpus to 587 chips across
  STM32 (G0/F4 plus G4/H7/F0/F1/F3 bulk-emit), SAM E70/V71/D21/
  D51/L21, RP2040, ESP32 family, Nordic nRF52, NXP iMX RT 1060,
  AVR-DA.  Pytest stays 100% green across the bumped corpus.
- **`runtime_init.c` profile fn name** —
  `alloy_clock_apply_<id>()` → `alloy_clock_enter_<id>()` to match
  the runtime-lite-contract bring-up vocabulary.

### Improved

- Test count grew from 102 → 138 (+36) across four foundational
  implementation passes; suite runs in under 9 seconds on a stock
  Apple Silicon laptop.
- 5 new OpenSpec proposals documenting the v2.1 parity surface,
  all `openspec validate --strict` clean.

## [0.1.0] — 2026-04-30

### Added

- Initial public release on PyPI.
- Canonical-device v2.1 IR + four-emitter pipeline (`linker.ld`,
  `peripheral_traits.h`, `runtime_init.c`, `vector_table.c`).
- `alloy-codegen` CLI + `alloy_codegen.generate(config, out_dir)`
  Python entrypoint.
- 102 regression tests covering the IR loader, synthesiser, and
  every emitter.
