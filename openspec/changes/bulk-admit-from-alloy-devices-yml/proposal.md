# Bulk Admit from alloy-devices-yml

## Why

Once the three repos exist
(alloy-data-extractor → alloy-devices-yml → alloy-codegen) and
the extractor has run against every pinned source, the data
repo will hold ~8,000 canonical device YAMLs.  The codegen
pipeline today still operates on a hand-curated
`bootstrap.DEVICE_REGISTRY` of 17 devices.

This change is the operational unlock: a CLI that walks the
data repo, generates a per-family parametrised admission entry,
and produces C++ artifacts for every device with a valid YAML —
no per-device hand-wiring, no `bootstrap.DEVICE_REGISTRY`
edits.

This supersedes the earlier `add-bulk-admission-flow` change
(which assumed the data lived in alloy-codegen).  The new flow
is simpler because the data is already canonical YAML — no
autogen step needed.

## What Changes

- `bootstrap.DEVICE_REGISTRY` becomes a **derived registry**
  rather than a hand-curated dict:
  - At import time, scan
    `data/devices/vendors/<vendor>/<family>/devices/*.yml`
    and build the registry from the filesystem.
  - The hand-curated dict stays as a fallback for the legacy
    SVD+patch path until that retires.
- New CLI `alloy-codegen bulk-admit
  [--vendor <v>] [--family <f>] [--limit <N>] [--dry-run]`:
  - Iterates every YAML in the requested scope.
  - Runs the full pipeline (parse YAML → CanonicalDeviceIR →
    emit artifacts → publish).
  - Reports per-device pass/fail/skip with a summary table.
  - `--dry-run` mode: parses + validates every YAML without
    emitting, reports schema or IR-construction failures.
- Per-family parametrised pytest scope: `pytest -q -m
  family/<vendor>/<family>` runs the admission tests for
  every device in that family by walking the data repo.
- `tests/test_bulk_admission.py` parametrises over every
  YAML found in `data/devices/`.  When the data repo grows
  to 8,000 chips, the test grows with it automatically — no
  manual parametrisation list to keep in sync.
- A `runtime-cpp-smoke` shard mode: when running over 1,000+
  devices, `pytest --runtime-cpp-smoke --shard 3/8` parallelises
  via pytest-xdist or CI matrix.
- Reports: per-bulk-run summary at
  `reports/bulk-admit-<timestamp>.json` with schema-counted
  failure modes (schema invalid, IR build failed, smoke
  compile failed, footprint budget exceeded).

## Impact

After all four data-side changes ship and the extractor runs
against pinned sources, **alloy-codegen emits C++ artifacts
for every chip in alloy-devices-yml automatically**.  No
per-device admission, no per-family bootstrap.

For 8,000 MCUs this means:
- One PR in alloy-data-extractor adds GigaDevice GD32 →
  extractor produces ~30 GD32 YAMLs → alloy-codegen
  bumps submodule → C++ artifacts ship for all 30.
- Time from "PR opened" to "C++ artifacts published" is
  measured in hours, not weeks.

## What this DOES NOT do

- Does not auto-publish artifacts.  The C++ output of bulk
  admission is reviewable in CI like any other PR.  Bulk
  admission produces artifacts; humans (or the existing
  `publish-alloy-devices` workflow) decide what to publish.
- Does not bypass the smoke-compile or footprint-budget
  gates.  Every bulk-admitted device runs every gate; bulk
  admission just stops being O(humans-curating-list).
- Does not replace `alloy-codegen-rust` / future language
  generators.  Each language consumer runs its own bulk
  admission against the same data repo.
