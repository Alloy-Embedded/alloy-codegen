# Consume modm Clock-Tree Edges

## Why

The IR-completeness audit found that `ingest-modm-devices-as-source`
already parses STM32 clock-tree edges from
`modm-devices/devices/stm32/g0/<part>.xml` into
`ModmClockEdge(source, target, multiplier, divisor)` records —
but the normalize stage **never consumes them**.  STM32 clock
trees in the IR today come entirely from hand-curated patches
(`patches/st/stm32g0/family.json` carries 463 LOC of `clock_nodes`
+ `clock_selectors`).

Wiring modm's data into the merge chain
(`baseline ← modm ← family-patch ← device-patch`) replaces
hundreds of lines of hand work with parsed data, while leaving
patches as the override layer for the genuinely device-specific
quirks.

## What Changes

- `_build_st_device_ir` calls
  `modm_devices.parse_clock_edges(modm_xml_path)` and merges the
  edges into the IR's `clock_nodes` + `clock_selectors`
  tuples, before applying any patch override.
- The `MODM_CLOCK_EDGES_INDEX` is built once per family and
  cached so the per-device builder doesn't re-parse XML
  repeatedly.
- A merge-precedence test asserts that when modm and a hand
  patch disagree, the patch wins (today's contract).
- A coverage report logs which clock nodes came from modm vs.
  patches per device, so reviewers can see how much hand work
  the import eliminated.
- Patches that become redundant are flagged for removal in a
  follow-up `minify-stm32-clock-patches` change (gated by
  `invert-patch-as-diff`).

## Impact

STM32 clock-tree hand-work in `family.json` becomes optional —
modm provides ~80% of the surface from already-extracted PDF
data.  Pairs with the future `migrate-stm32g0-patches` change
to collapse `family.json` from 463 LOC toward 100 LOC.

## What this DOES NOT do

- Does not change the emitted artifacts unless a hand patch
  is wrong — modm + patches together produce the same merged
  graph as today's patch-only path.
- Does not extend modm consumption to non-STM32 vendors.  modm
  covers some SAM and Nordic but Zephyr DTS already covers
  those better; modm is best-positioned for STM32.
- Does not eliminate the modm pin/AF or DMA-matrix consumers.
  Those are separate slots in the modm adapter and stay as-is.
