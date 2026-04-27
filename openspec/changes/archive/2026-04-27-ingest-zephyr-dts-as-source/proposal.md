# Ingest Zephyr DTS as a Cross-Vendor Source

## Why

Zephyr's `dts/<arch>/<vendor>/*.dtsi` carries already-normalized
peripheral instances, IRQ numbers, clock-controller parents, DMA
channels, and pinctrl groups for **600+ SoCs** across STM32, NXP,
Nordic, TI, Espressif, Renesas, Infineon, Microchip, Ambiq, SiLabs,
Telink, and more — Apache-2.0 licensed, parseable via Zephyr's own
`edtlib` Python module.  No other single source covers this many
vendors with comparable depth.

A single Zephyr-DTS adapter is the highest-leverage cross-vendor
ingestion in the roadmap: one integration unlocks ~10 vendors that
each would otherwise require a bespoke 200-1000 LOC adapter.

## What Changes

- New adapter `src/alloy_codegen/sources/zephyr_dts.py` that
  consumes a Zephyr checkout and produces the same intermediate
  objects (peripherals, interrupts, clocks, dma_requests, pins,
  signals) that existing adapters emit.
- The adapter relies on `edtlib` (vendored from `zephyr/scripts/dts/`
  or installed via `python-devicetree`) to fully resolve `.dts` +
  `.dtsi` overlays — no hand-rolled DTS parser.
- Pinctrl groups (`<vendor>-pinctrl.h` / `*-pinctrl.dtsi`) feed
  the IR's `connection_candidates`.  AF/funcsel encoding is
  vendor-specific and lives in a small per-vendor pin-encoding
  table inside the adapter.
- Initial admission target: **Nordic nRF52** (`dts/arm/nordic/`)
  — covers the "validate the plumbing on a vendor we don't have
  yet" goal without committing to all 600 SoCs upfront.
- Adapter registers itself through the `add-vendor-adapter-registry`
  decorator (Sprint 1 dependency).
- A `--zephyr-root` source override extends `ExecutionContext` so
  tests can pin a specific Zephyr checkout in fixtures.

## Impact

After this lands, admitting Renesas, TI, Infineon, Ambiq, etc.
becomes ~500 LOC of pin-encoding + a registry decorator instead
of 2,000-5,000 LOC of bespoke adapter.  The flagship cross-vendor
move that takes alloy-codegen from "9 families" to "any vendor
Zephyr supports".

## What this DOES NOT do

- Does not replace existing STM32/Microchip/NXP adapters where
  they have richer data than DTS (e.g. modm's already-extracted
  STM32 clock tree, ATDF's signal mux).  Zephyr DTS is additive,
  not a replacement.
- Does not commit to bulk-admitting all 600 Zephyr SoCs in this
  change — that comes later, gated by the `autogen-device-patches`
  flow.
