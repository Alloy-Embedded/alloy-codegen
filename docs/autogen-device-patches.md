# Autogenerating Device Patches from SVD/PDSC

`scripts/autogen_device_patches.py` scaffolds the mechanical
~80% of a `patches/<vendor>/<family>/devices/<device>.json` from
authoritative vendor sources (CMSIS-SVD, optionally CMSIS-Pack
PDSC).  Goal: cut per-device manual work from ~180 LOC of patch
JSON to ~30 LOC of human review.

Added by the OpenSpec change `autogen-device-patches-from-svd`.

## CLI

```bash
python -m scripts.autogen_device_patches \
    --vendor st --family stm32g0 --device stm32g071rb \
    --svd path/to/STM32G071.svd \
    [--pack path/to/Keil.STM32G0xx_DFP.pdsc] \
    [--out patches/st/stm32g0/devices/stm32g071rb.json]
```

Without `--out`, the JSON goes to stdout.

## What the generator derives

| Field | Source | Notes |
|---|---|---|
| `device` | CLI `--device` | trivially recorded |
| `svd_file` | filename of `--svd` | basename only |
| `core` | SVD `<cpu><name>` (+ `<fpuPresent>`) | `CM4` + fpu → `cortex-m4f` |
| `peripherals` | SVD `<peripherals>` | sorted list of names |
| `interrupts` | SVD `<interrupt>` per peripheral | sorted by `(line, name)` |
| `memories` | PDSC `<memory>` (when `--pack` given) | sorted by base address |
| `$autogen` | self | metadata (svd_file, generator_version) |
| `$todo_review` | self | list of fields the reviewer must fill |

## What the generator marks as `TODO_REVIEW`

The CLI cannot synthesise these fields and emits sentinels for
them, recording each in the top-level `$todo_review` array:

- `package` — pick of the device's bonding/package variant; PDSC
  carries candidates but the choice is human.
- `pin_data_file` — vendor-specific pin/AF source filename
  (STM32 open-pin-data, Microchip ATDF, NXP MEX).
- `summary` — human-authored one-liner.
- `memories` — only when `--pack` is omitted (SVD has no
  flash/sram declarations).
- `core` — only when the SVD lacks a `<cpu>` block.
- All Tier 2/3/4 silicon facts — every UART/SPI/I2C/TIMER/PWM/ADC
  option array.  These belong in the family-level template
  library (planned by the `peripheral-trait-template-library`
  change) rather than per-device patches.

## Workflow

1. Run the generator into a fresh patch path.
2. Run `scripts/diff_device_patch.py` against the existing
   curated patch (when one exists) to see what differs:
   ```bash
   python -m scripts.diff_device_patch \
       --autogen new_draft.json \
       --curated patches/.../devices/<device>.json
   ```
3. Fill every entry in `$todo_review`.  Remove the `$todo_review`
   array once empty.
4. Drop `$autogen` once a human has reviewed the file (its only
   purpose is to flag drafts).
5. Run `pytest -q` — admitted devices have golden fixtures that
   will catch any pipeline-level regression.

## Determinism contract

Re-running the generator on the same inputs produces
byte-identical output:

- Lists are sorted (`peripherals` by name, `interrupts` by
  `(line, name)`, `memories` by base address).
- Top-level keys are emitted in a fixed order.
- JSON is dumped with `indent=2`, `ensure_ascii=False`, trailing
  newline.

This guarantees that "rerun the generator" is a safe operation
for catching upstream-source drift — diffs only show up when the
underlying SVD/PDSC actually changed.

## What this does NOT do

- Does not extract pin/AF tables.  Vendor pin sources
  (open-pin-data, ATDF, MEX) live behind separate adapters.
- Does not extract clock-tree topology.  RCC clock graph is
  vendor-specific and lives in `family.json` overlays.
- Does not bulk-admit devices.  Discovery of "what MCUs exist"
  is the `ingest-probe-rs-target-catalog` change's job; this
  generator is what you run *after* you've decided to admit one.
