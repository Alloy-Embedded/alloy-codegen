# Bulk Admission Flow

## Why

Three pieces of infrastructure are now in place but disconnected:
- `data/known_devices.toml` — ~5,000 chip catalog imported from
  probe-rs.
- `scripts/autogen_device_patches.py` — generates 80% of a
  device patch from SVD/PDSC.
- `ingest-zephyr-dts-as-source` — vendor-agnostic DTS adapter.

Today admitting one MCU still takes ~5 manual steps (look up the
chip, find its SVD, run autogen, write a fixture, register it).
At 1000 MCUs that's untenable.

A single CLI that pulls the chip from `known_devices.toml`,
locates the source artefact via the catalog's `source_pack` /
`probe_rs_target` references, runs autogen, and emits a draft
patch + bootstrap registration scaffold turns admission into a
mechanical operation — reviewable in seconds, runnable in a
batch loop.

## What Changes

- New CLI `python -m scripts.bulk_admit --vendor <v>
  --family <f> [--device <d>] [--limit <N>] [--dry-run]`.
- Step 1: query `data/known_devices.toml` for matching
  `(vendor, family[, device])` entries.
- Step 2: for each, resolve the input source (SVD path from a
  configured CMSIS-Pack root, OR Zephyr DTS path when the
  vendor is registered with the Zephyr adapter).
- Step 3: run the appropriate autogen tool
  (`scripts.autogen_device_patches` for SVD, or a new
  `scripts.autogen_device_patches_from_dts` mirror for Zephyr).
- Step 4: emit two files:
  - `patches/<vendor>/<family>/devices/<device>.json` (draft).
  - A diff-friendly stub for `bootstrap.py:DEVICE_REGISTRY` /
    `vendors/_register_<vendor>_<family>.py` printed to stdout
    (so a reviewer can paste the new entry into the registry
    with one click).
- Step 5: a summary report (rendered as Markdown to stdout)
  listing per-device: success / skipped / TODO_REVIEW count.
- `--dry-run` mode emits everything to stdout without touching
  disk so a reviewer can preview a 50-MCU batch before
  committing.
- A complementary `scripts.bulk_admit_review` CLI walks freshly
  admitted patches and reports `$todo_review` content density,
  so reviewers can prioritise which drafts need the most
  attention.

## Impact

Admitting 50 MCUs from a single Zephyr-covered family becomes
one command + a review pass over the 50 generated patches.
Mechanical work (file scaffolding, identity wiring, peripheral
list) is automated; only the genuinely device-specific
overrides (clock profiles, calibration, package selection)
need a human touch.

This is the operational unlock for the 1000-MCU target.

## What this DOES NOT do

- Does not auto-commit.  Every admission is reviewer-gated —
  the drafts land as a single `git status` diff for inspection.
- Does not bypass quality gates.  Smoke compile +
  artifact-footprint-budget + golden tests still run, so a
  bulk-admitted device that breaks emission fails CI like any
  other.
- Does not write integration tests automatically.  Per-family
  pipeline tests are still hand-authored — the admission
  surface is small enough that one parametrised test covers
  every device in a family.
