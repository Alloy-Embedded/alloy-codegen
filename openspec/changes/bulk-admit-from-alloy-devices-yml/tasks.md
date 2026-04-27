# Tasks — bulk-admit-from-alloy-devices-yml

## Phase 1: Filesystem-derived registry

- [ ] 1.1 New `alloy_codegen.bootstrap.discovered_device_registry()`
      walks `data/devices/vendors/**/*.yml` and returns a
      registry-shaped dict.
- [ ] 1.2 The function caches the result for the process
      lifetime to keep parse cost bounded.
- [ ] 1.3 `DEVICE_REGISTRY` becomes a property that returns
      the union of `_HAND_CURATED_DEVICE_REGISTRY` (legacy)
      and `discovered_device_registry()` — discovered devices
      win on conflict.

## Phase 2: bulk-admit CLI

- [ ] 2.1 New `python -m alloy_codegen.cli bulk-admit`
      subcommand with `--vendor`, `--family`, `--limit`,
      `--dry-run`.
- [ ] 2.2 Walks the matching YAMLs, runs the full pipeline
      per device, captures per-device pass/fail.
- [ ] 2.3 Summary table written to stdout (Markdown) +
      machine-readable JSON to
      `reports/bulk-admit-<timestamp>.json`.

## Phase 3: Sharded test runs

- [ ] 3.1 `tests/test_bulk_admission.py` parametrises over
      every YAML discovered in `data/devices/`.  Test asserts:
      schema-valid + IR build succeeds + smoke-compile
      passes (when `--runtime-cpp-smoke` is set).
- [ ] 3.2 pytest-xdist support: `pytest -n auto` shards across
      cores.  CI matrix sharding documented.
- [ ] 3.3 `--bulk-shard <i>/<n>` flag selects a stable subset
      of devices (hash-based) so a CI matrix of 8 jobs
      covers 8,000 devices in 1,000-device shards.

## Phase 4: Performance budget

- [ ] 4.1 Single-device cold pipeline run target: under 2 s
      (parse YAML + emit + smoke compile).
- [ ] 4.2 8,000 devices on 8-shard CI: under 30 minutes wall
      clock.
- [ ] 4.3 Performance regression test: cold-pipeline cost per
      device tracked in
      `reports/bulk-admit-perf-<timestamp>.json`.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/vendor-admission/spec.md`.
- [ ] 5.2 `openspec validate bulk-admit-from-alloy-devices-yml
      --strict` passes.
- [ ] 5.3 `pytest -q` clean.
- [ ] 5.4 Documentation `docs/bulk-admission.md` covers the
      contributor + maintainer workflows.

## Phase 6: Supersession of legacy bulk-admission

- [ ] 6.1 Confirm `add-bulk-admission-flow` (the predecessor
      proposal that assumed the data lived inside
      alloy-codegen) is archived without implementation —
      this change is the new design.
- [ ] 6.2 ROADMAP updated to point at this change as the
      operational scaling unlock.
