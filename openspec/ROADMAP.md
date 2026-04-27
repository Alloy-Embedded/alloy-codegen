# Driver-Semantics Roadmap

Implementation order for the OpenSpec changes that bring every emitted
`<peripheral>.hpp` up to ADC-gold-standard depth.  The ADC reference
header in `tests/fixtures/emitted/stm32g0/.../driver_semantics/adc.hpp`
is the target — option arrays + capability flags + calibration data +
external triggers + DMA bindings + max-clock + per-channel pin maps.

The order is dictated by what the **alloy async HAL drivers** consume
first, not by which peripheral has the largest gap.

## Stage 0 — done

| Change | Status |
|---|---|
| `add-adc-tier-2-3-4-data` | ✅ archived |
| `add-uart-spi-tier-2-3-4-data` | ✅ archived (2026-04-26) |
| `fill-i2c-semantic-gaps` | ✅ archived (Tier 1 + clock-mux + pinmux) |
| `fill-gpio-semantic-gaps` | ✅ archived (alt-fn lists) |

## Stage 1 — cross-cutting unblockers (P0)

These three are prerequisites for *every* async HAL driver in alloy.
Land them in this order so the consumer can stand up a full
async-UART driver immediately after the third merges.

| # | Change | What it adds | Why first |
|---|---|---|---|
| 1 | `add-irq-vector-traits` | `kIrqNumbers[]` on UART/SPI/I2C/TIMER/DMA traits + emitter wiring | Async drivers need NVIC vector ID at compile time to install handlers |
| 2 | `add-peripheral-dma-cross-references` | `kDmaBindings[]` on UART/SPI/I2C/TIMER traits — back-references into the existing `dma.hpp` binding ID space | DMA info already exists in the IR; today only `dma.hpp` knows `USART1_TX`. Drivers need `UartSemanticTraits<USART1>::kDmaBindings` |
| 3 | `add-kernel-clock-traits` | `kKernelClockSourceField` (RCC mux ref) + `kMaxClockHz` on UART/SPI/I2C/QSPI/SDMMC | modm-style baud resolver `Baudrate<f_pclk, 115200>` needs both the clock-source ref and the max input |

## Stage 2 — peripheral-tier completions (P1)

Mirrors of `add-uart-spi-tier-2-3-4-data` for the next set of
peripherals the alloy HAL roadmap targets.

| # | Change | Mirrors | Notes |
|---|---|---|---|
| 4 | `add-i2c-tier-2-3-4-data` | UART/SPI Tier 2/3/4 | Also fixes the broken STM32G0 emission (`kI2cSemanticPeripherals = {}`) |
| 5 | `fill-gpio-tier-1-fields` | n/a (Tier-1 activation) | STM32 GPIO mode/pull/speed/output-type fields are `kInvalidFieldRef` today; populate them |
| 6 | `add-timer-tier-2-3-4-data` | UART/SPI Tier 2/3/4 | Prescaler ranges, trigger sources (ITRx/ETR), DMA bindings, IRQ split (UP/CC/BRK) |

## Stage 2.5 — typed-channel projection on the ADC trait

Pure emission-layer change. Lifts the IR's existing
`AdcSemanticRow.internal_channels` data into a typed
`enum class AdcChannelOf<P>::type` per peripheral so consumers
(notably alloy's `extend-adc-coverage`) drop the `std::uint8_t`
transitional shim. No new IR sources, no patch overlay changes.

| # | Change | What it adds |
|---|---|---|
| 6.5 | `add-adc-channel-typed-enum` | `AdcChannelOf<P>` typed enum + `AdcChannel<P>` alias in every emitted ADC `driver_semantics/adc.hpp`; closed kind→name table; duplicate-name detection; tests + `docs/adc-channel-enum.md` |

Unblocks alloy `extend-adc-coverage` phase 1.

## Stage 3 — secondary peripherals (P2)

Build on Stage 2 outputs.  Lower priority because no async driver
in alloy is gated on them yet, but cheap to land once Stage 2 is in.

| # | Change | Notes |
|---|---|---|
| 7 | `add-pwm-tier-2-3-4-data` | After TIMER — adds prescaler range, deadtime options, break inputs |
| 8 | `fill-dma-controller-hw-traits` | Channel count, burst sizes, max-transfer, priority levels.  `dma.hpp` controller side is mostly stubbed today |

## Stage 3.5 — adoption + ergonomics (P1, "kill modm")

These three close the modm ergonomics gap and prove the multi-language
IR thesis.  Higher leverage than continuing to fill Tier 2/3/4 on
peripherals only used by 9 devices.

| # | Change | What it adds | Why now |
|---|---|---|---|
| 9 | `add-board-support-package-emitter` | Per-board BSP header (`Leds::kGreen`, `DebugUart`, `kDefaultClockProfile`) sourced from new board.json overlays | matches modm's `<modm/board.hpp>` "5-line blinky" — biggest onboarding-friction gap |
| 10 | `add-cmake-package-config` | `find_package(AlloyDevice REQUIRED COMPONENTS stm32g071rb)` ships per-device INTERFACE library + per-core toolchain fragment | drops consumer onboarding from ~30 lines of CMake plumbing to 2 |
| 11 | `add-typed-peripheral-enums-everywhere` | Per-peripheral typed `enum class`es (`UartParityOf<USART1>::type::even`) replace `std::uint8_t` field-value shims across UART/SPI/I2C/TIMER/PWM | catches "wrong field value" bugs at compile time; matches modm's typed-enum ergonomics |

## Stage 4 — niche peripherals (P3, on demand)

Defer until the corresponding alloy HAL driver is on the roadmap.
Each one would mirror the Stage 2 pattern.

- `add-dac-tier-2-3-4-data` — resolution, triggers, waveform generators
- `add-can-tier-2-3-4-data` — filter banks, FIFO depths, FD vs classic, max bitrate
- `add-rtc-tier-2-3-4-data` — clock sources, alarm count, sub-second bits, tamper
- `add-watchdog-tier-2-3-4-data` — clock source, prescaler, reload bits, timeout range
- `add-usb-tier-2-3-4-data` — speeds, endpoint-buffer kind, max packet sizes (also needs to fix G0 emission)
- `add-eth-tier-2-3-4-data` — descriptor counts, PHY clock, PTP flag, checksum offload
- `add-sdmmc-tier-2-3-4-data` — clock dividers, UHS modes, ADMA flags, voltages
- `add-qspi-tier-2-3-4-data` — line counts, address sizes, dummy cycles, mem-mapped base

## Cross-references that don't need a separate OpenSpec

These will be addressed inside the Stage 1–2 changes above:

- ADC currently emits `kHasDma = false` / `kDmaBindings = {}` even
  though ADC has DMA — fixed inside `add-peripheral-dma-cross-references`
  (Stage 1, item 2).
- STM32G0 has empty specialization arrays for I2C, USB, QSPI, SDMMC.
  I2C is fixed in Stage 2 (`add-i2c-tier-2-3-4-data`).  USB / QSPI /
  SDMMC are Stage 4.

## Ordering rule of thumb

If two changes are independent (e.g. `add-irq-vector-traits` and
`add-peripheral-dma-cross-references`), prefer the one that
unblocks the most consumer drivers per line of patch JSON.  Stage 1
items 1–3 are deliberately ordered for that reason: IRQ vectors
unblock 5 driver kinds; DMA cross-refs unblock 4; kernel-clock
unblocks 5 *but* requires the runtime-lite clock tree to consume
the new field-ref shape, so it ships last in Stage 1.

---

## Scaling Track — toward 1000–2000 MCUs

Separate from the driver-semantics depth track above, these 10
changes attack scaling: collapsing per-MCU manual work, layering
in cross-vendor data sources, and gating runtime C++ quality.
Order optimised for "biggest unblock first".

### Sprint 1 — quick wins (2–3 weeks, 1 dev)

| # | Change | Effect |
|---|---|---|
| 1 | `add-vendor-adapter-registry` | Replace hard-coded `if vendor == ...` cascades with a decorator/registry — every later sprint depends on this |
| 2 | `autogen-device-patches-from-svd` | Generate ~80% of per-device patch JSON from SVD + CMSIS-Pack; cuts per-MCU work from 180 → ~30 LOC |
| 3 | `auto-update-goldens` | `ALLOY_UPDATE_GOLDENS=1` flag — stops the per-family copy-paste chore on emitter changes |

### Sprint 2 — external sources (3–4 weeks)

| # | Change | Effect |
|---|---|---|
| 4 | `ingest-probe-rs-target-catalog` | ~5,000-chip catalog imported as `data/known_devices.toml` — discoverability + admission scaffolding |
| 5 | `ingest-zephyr-dts-as-source` | The cross-vendor spine — Zephyr DTS unlocks Nordic, Renesas, TI, Infineon, Ambiq, etc. through one adapter |

### Sprint 3 — structural rewrite (4–5 weeks)

| # | Change | Effect |
|---|---|---|
| 6 | `invert-patch-as-diff` | Patches become diffs over a source-derived baseline; per-MCU patches collapse 80–90% |

### Sprint 4 — depth + STM32 deep dive (3 weeks)

| # | Change | Effect |
|---|---|---|
| 7 | `peripheral-trait-template-library` | Tier 2/3/4 defaults inherited per `(class, ip_version)`; eliminates per-device duplication |
| 8 | `ingest-modm-devices-as-source` | modm's clock-tree + DMA-matrix data layered behind patches; STM32 coverage matches modm |

### Sprint 5 — runtime C++ quality gates (2 weeks)

| # | Change | Effect |
|---|---|---|
| 9 | `add-runtime-cpp-smoke-compile-ci` | Every device's emitted headers compile cleanly in a freestanding clang job in CI |
| 10 | `artifact-footprint-budget` | Per-artifact byte budgets + per-device overrides; caps blast radius as catalog grows |

### What lands at the end

- Per-MCU manual work drops from ~180 LOC to ~10–20 LOC.
- New family admission via Zephyr DTS + adapter registry: ~500 LOC.
- 1000–2000 MCUs becomes mechanically tractable; the bulk admission
  is then a series of "import + autogen + minify + review" commits.
- Runtime C++ output is gated by three layers: type-safety (smoke
  compile), zero overhead (no string literals — existing gate),
  bounded footprint (byte budget per artifact).

---

## Phase 2 Scaling Track — post-audit

After landing the 10-change scaling track, an IR-completeness +
C++-quality + patch-migration audit identified the next layer of
work.  These are queued in priority order.

### Wave 6 — Cross-vendor expansion (user-asked)

| # | Change | Effect |
|---|---|---|
| 1 | `extend-zephyr-dts-vendor-coverage` | Renesas / TI / Infineon / Ambiq / SiLabs admissible (5 pilots, ~500 LOC each) |
| 2 | `decode-zephyr-pinctrl-into-connection-candidates` | Nordic + STM32 pinctrl decoder; nRF52 emits real `pin_validation.hpp` |
| 3 | `add-bulk-admission-flow` | Single CLI: catalog query → autogen → registry scaffold; admits 50 MCUs in one batch |
| 4 | `migrate-uart-emitter-to-template-library` | First emitter consumer — proves the template chain end-to-end |

### Wave 7 — IR-completeness wins (audit findings)

| # | Change | Effect |
|---|---|---|
| 5 | `populate-imxrt-iomux-gpio-pins` | iMXRT goes from zero `gpio_pins` to hundreds; `pin_validation.hpp` emitted for NXP for the first time |
| 6 | `consume-modm-clock-tree-edges` | modm STM32 clock graph already parsed but ignored — wire it into `clock_nodes` |
| 7 | (deferred) `extract-svd-enumerated-values` | Bitfield enums + register-array `<dim>` from SVD |
| 8 | (deferred) `query-probe-rs-catalog-from-pipeline` | Make `data/known_devices.toml` actually consulted |

### Wave 8 — C++ quality wins

| # | Change | Effect |
|---|---|---|
| 9 | `add-additional-validity-concepts` | `ValidDmaBinding` + `ValidClockSource` + `ValidInterruptSlot` + `ValidI2cSpeed` — 4 more compile-time moats over modm |
| 10 | `reduce-cpp-header-bloat-via-shared-luts` | iMXRT pwm.hpp 52 KB → 35 KB via shared LUTs; pairs with footprint-budget gate |

### Wave 9 — Existing MCUs migration

| # | Change | Effect |
|---|---|---|
| 11 | `migrate-existing-mcus-to-template-and-diff-format` | 14k → ~3.5k LOC across all admitted patches.  5 sub-waves: pilots, STM32, Espressif, iMXRT, ATDF (gated on a prereq) |
| 12 | (prereq for ATDF wave) `extend-autogen-to-atdf-and-mcuxpresso` | Autogen reads ATDF + MCUXpresso headers, not just SVD |

### What lands at the end

- 11+ admitted vendors (vs. 6 today), 50+ pilot MCUs from each
  Zephyr-supported vendor admitted via one CLI command.
- iMXRT emits real compile-time pinmux validation (parity with
  STM32 — first non-ST vendor to get the structural moat).
- 5 compile-time validity concepts (vs. 1 today): ValidPin,
  ValidDma, ValidClock, ValidIrq, ValidI2cSpeed.
- 75% reduction in patch LOC (~14k → ~3.5k), enabling 1000+ MCU
  admission as mechanical work.
- Header bloat down ~30% on the worst offenders (iMXRT PWM,
  TIMER, capabilities) — locked in by the footprint-budget gate.

---

## Architectural Pivot — Three-Repo Split

After Phase-2 was drafted, an architectural rethink concluded
that the alloy-codegen monolith should split into three repos
(matching what modm-data/modm-devices and Embassy's
stm32-data-gen/stm32-data did, plus extending coverage to PIC
and other categories no OSS framework reaches).

### The four foundational changes

| Order | Change | Effect |
|---|---|---|
| 1 | `define-canonical-device-yaml-schema` | Stable text form for `CanonicalDeviceIR` — JSON Schema + round-trip contract.  Foundation of everything below. |
| 2 | `extract-alloy-devices-data-repo` | Spin out `alloy-devices-yml` (data only).  alloy-codegen consumes via git submodule.  Existing 17 admitted devices migrate first. |
| 3 | `add-alloy-data-extractor-repo` | Spin out `alloy-data-extractor` — Python ETL for every vendor source (CMSIS-SVD, ATDF/PIC/AVR, MCUXpresso, ESP-IDF, Zephyr DTS, STM32 CubeMX, modm-data PDF, Pico SDK, datasheet scraping).  Generates YAML into the data repo. |
| 4 | `bulk-admit-from-alloy-devices-yml` | alloy-codegen's `DEVICE_REGISTRY` becomes filesystem-derived from `data/devices/`.  Adding a chip = committing a YAML.  Sharded CI matrix runs over thousands of devices. |

### What this supersedes

- ❌ **`add-bulk-admission-flow`** (deleted) — the original flow
  assumed data lived in alloy-codegen.  Replaced by
  `bulk-admit-from-alloy-devices-yml` which is simpler because
  data already canonical.
- ❌ **`migrate-existing-mcus-to-template-and-diff-format`**
  (deleted) — the migration of existing patches IS the YAML
  emission step in `extract-alloy-devices-data-repo`.

### What stays from Phase-2

These remain valid as codegen-side changes (or as extractor-side
changes after the split — the `WHAT` doesn't move, only the
`WHERE`):

- `extend-zephyr-dts-vendor-coverage` (extractor side)
- `decode-zephyr-pinctrl-into-connection-candidates` (extractor side)
- `migrate-uart-emitter-to-template-library` (codegen side)
- `populate-imxrt-iomux-gpio-pins` (extractor side)
- `consume-modm-clock-tree-edges` (extractor side)
- `add-additional-validity-concepts` (codegen side)
- `reduce-cpp-header-bloat-via-shared-luts` (codegen side)

### What lands at the end of the architectural pivot

```
alloy-data-extractor    (Python ETL, multi-source, multi-vendor)
       │ generates YAML
       ▼
alloy-devices-yml       (~8000 device YAMLs; data only, no code)
       │ consumed by
       ▼
alloy-codegen           (C++ emitter, this repo, slimmed down)
alloy-codegen-rust      (future)
alloy-codegen-zig       (future)
alloy-codegen-docs      (future)
```

- 8,000 admitted MCUs across ARM Cortex-M (~5,000), AVR/SAM
  (~2,000 incl. **PIC8/16/18/24/32 + dsPIC33** — ~2,150 chips
  no OSS HAL covers), iMXRT/Kinetis/LPC/MCX (~400), Espressif
  (~15), RP2040 (~2), Zephyr-covered cross-vendor
  (Renesas/TI/Infineon/Ambiq/SiLabs/…).
- Adding a vendor = one PR in alloy-data-extractor.
  Adding a chip = one YAML in alloy-devices-yml.
- Adding a target language = a new sibling generator
  alongside alloy-codegen.

This is the move that takes alloy from "promising codegen with 9
admitted families" to **the broadest multi-vendor, multi-arch HAL
data foundation in OSS**, period.
