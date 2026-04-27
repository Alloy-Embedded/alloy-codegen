# Autogenerate Device Patches from SVD/CMSIS-Pack

## Why

Per-device patches (`patches/<vendor>/<family>/devices/<mcu>.json`)
are 100% hand-curated today, ~180 LOC each.  For 1000 MCUs that
is 180,000 LOC of manual JSON.  ~80% of every patch is mechanical
data already present in the vendor's CMSIS-SVD + CMSIS-Pack
descriptor (memory map, peripheral instances, IRQ vectors, package,
core).  Only ~20% (clock-tree overrides, RCC enable signals,
package-specific tweaks) genuinely needs human review.

A generator script that scaffolds the mechanical 80% from authoritative
vendor sources cuts per-device manual work from ~180 LOC to ~30 LOC
of human review and overrides.

## What Changes

- New script `scripts/autogen_device_patches.py` that, given a
  `(vendor, family, device, svd_path, pack_path?)` tuple, emits
  a draft `patches/<vendor>/<family>/devices/<device>.json`
  populated from authoritative sources.
- The generator extracts: device identity, package, core, memory
  map, peripheral instance list, register file references,
  interrupt vector table, basic RCC bindings (when discoverable
  from the SVD).
- Fields the generator cannot determine (e.g. clock-tree
  overrides, package-specific pinmux) are emitted as
  `"// TODO review"` markers so a reviewer sees exactly what is
  unfinished.
- A complementary `scripts/diff_device_patch.py` shows the diff
  between the generated draft and the existing hand-curated
  patch, so the team can validate the generator on already-admitted
  devices before trusting it for net-new ones.
- Generator is **idempotent and deterministic** — running it twice
  on the same input produces byte-identical output.

## Impact

Admitting a new MCU within an admitted family drops from ~180 LOC of
manual patch JSON to ~30 LOC of review-and-override.  Unblocks
batch admission of long-tail devices (every STM32G0 variant,
every iMXRT, every nRF52*) without exploding patch-LOC inventory.
