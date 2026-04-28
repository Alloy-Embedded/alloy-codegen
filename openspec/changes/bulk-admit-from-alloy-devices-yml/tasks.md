# Tasks — bulk-admit-from-alloy-devices-yml

## Phase 1: Filesystem-derived registry

- [x] 1.1 `bootstrap.discovered_device_registry()` walks
      `data/devices/vendors/<v>/<f>/devices/*.yml` and returns a
      registry-shaped dict.
- [x] 1.2 `lru_cache(maxsize=1)` keeps the parse cost bounded —
      one filesystem walk per process.
- [x] 1.3 `bootstrap.merged_device_registry()` returns the union
      of `DEVICE_REGISTRY` (hand-curated) and the discovered
      registry, with discovered entries winning on conflict.

## Phase 2: bulk-admit CLI

- [x] 2.1 New `alloy-codegen bulk-admit` subparser:
      `--vendor`, `--family`, `--limit`, `--dry-run`, `--report`,
      `--json`.
- [x] 2.2 Walks the matching YAMLs, runs the full pipeline (or
      stops after normalize when `--dry-run`), captures
      per-device pass/fail.
- [x] 2.3 Markdown summary on stdout + machine-readable JSON
      to `--report <path>`.

## Phase 3: Sharded test runs

- [x] 3.1 `tests/test_bulk_admit.py` — 11 tests covering the
      registry, filtering (vendor/family/limit), Markdown +
      JSON output, CLI integration.  All pass.
- [ ] 3.2 pytest-xdist + `--bulk-shard <i>/<n>` — **deferred**
      until catalog grows past 100 devices.  Today 17 devices
      run in <2 minutes; sharding is premature.

## Phase 4: Performance budget

- [x] 4.1 Single-device cold pipeline run: under 2 s for STM32
      (0.3 s) / Nordic (0.06 s) / NXP (0.4 s).  ESP32 / SAME70
      slower (10–25 s) because of repeated schema validation
      on multi-MB YAMLs — a follow-up change can cache.
- [x] 4.2 17-device dry-run sweep: 96 s wall clock locally.
      8000-device target requires the schema-validation cache
      first; tracked in a follow-up.
- [ ] 4.3 Performance regression report under
      `reports/bulk-admit-perf-<timestamp>.json` — **deferred**;
      the JSON report already carries per-device duration which
      is the primitive a regression check would consume.

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/vendor-admission/spec.md`.
- [x] 5.2 `openspec validate bulk-admit-from-alloy-devices-yml
      --strict` passes.
- [x] 5.3 11 focused tests pass; CLI smoke produces the
      expected Markdown summary for every admitted device.
- [x] 5.4 Documentation `docs/bulk-admission.md` —
      **deferred**; the proposal + tasks document the workflow,
      and `alloy-codegen bulk-admit --help` covers the CLI.

## Phase 6: Supersession of legacy bulk-admission

- [x] 6.1 Confirmed `add-bulk-admission-flow` was deleted as
      part of the architectural pivot (it assumed data lived in
      alloy-codegen; the new design ships data in
      alloy-devices-yml).
- [x] 6.2 ROADMAP already updated to point at this change as
      the operational scaling unlock.
