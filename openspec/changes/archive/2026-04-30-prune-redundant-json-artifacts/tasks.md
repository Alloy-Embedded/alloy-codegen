# Tasks — prune-redundant-json-artifacts

## Audit note (2026-04-30)

The implementation work for this OpenSpec was already
completed by the ``consume-alloy-devices-yml-as-canonical-input``
archive (Phase 3+4+5).  The unused emitters had already been
removed from ``emission.py`` and ``stages/emit.py`` before
this OpenSpec was filed.  The remaining work for this change
is verification + spec delta capture.

## Phase 1: Drop unused metadata emitters

- [x] 1.1 Delete the seven family-rollup emitters from
      `src/alloy_codegen/emission.py`:
      `emit_family_connectivity`,
      `emit_system_descriptors_metadata`,
      `emit_ip_blocks_metadata`,
      `emit_packages_metadata`,
      `emit_connectors_metadata`,
      `emit_capabilities_metadata`,
      `emit_device_metadata`.  *(Done by
      ``consume-alloy-devices-yml-as-canonical-input``;
      verified absent — only ``emit_family_index`` remains in
      ``emission.py``.)*
- [x] 1.2 Remove their imports from `stages/emit.py` and the
      corresponding entries in the `artifacts: list[EmittedArtifact]`
      assembly.  *(Done; verified absent in current
      ``stages/emit.py``.)*
- [x] 1.3 Drop the `_device_metadata_path` /
      `_family_metadata_path` helpers if no surviving emitter
      uses them.  *(``_family_metadata_path`` retained — used
      by the surviving ``emit_family_index`` to emit
      ``family-index.json``; ``_device_metadata_path`` removed
      with the per-device JSON dump.)*

## Phase 2: Drop unused reports

- [x] 2.1 Delete `emit_runtime_capability_summary_report` and
      `emit_runtime_compatibility_matrix_report` from
      `src/alloy_codegen/runtime_reports.py`.  *(Done; verified
      absent.)*
- [x] 2.2 Remove their imports + emit-stage call sites.
      *(Done; ``stages/emit.py`` no longer references them.)*
- [x] 2.3 Confirm no test references them.  *(Verified.)*

## Phase 3: Update family-index.json

- [x] 3.1 In `emit_family_index`, change each device entry's
      `metadata_path` field to a `yaml_path` pointing at the
      canonical YAML location:
      `data/devices/vendors/<vendor>/<family>/devices/<device>.yml`.
      *(Done — ``_canonical_yaml_path`` helper at
      ``emission.py:158`` produces exactly this path; field
      ``yaml_path`` is set per device entry.)*
- [x] 3.2 Update the field name in tests + any consumer.
      *(Field is ``yaml_path``; CI workflow checks existence
      only.)*

## Phase 4: Regenerate goldens + verify

- [x] 4.1 Goldens regenerated.  Verified: live pipeline emits
      only the kept artefacts —
      ``metadata/family-index.json``,
      ``metadata/boards.json``,
      ``reports/runtime-{provenance,explainability}.json``,
      ``reports/coverage.json``,
      ``reports/validation-{report,summary}.json``,
      ``artifact-manifest.json``,
      and the per-device runtime tree.
- [x] 4.2 ``tests/fixtures/emitted/<family>/metadata/`` no
      longer contains the deleted rollups (verified: no
      ``family-connectivity.json`` /
      ``system-descriptors.json`` / ``connectors.json`` /
      ``ip-blocks.json`` / ``packages.json`` /
      ``capabilities.json`` under any ``metadata/`` directory).
- [x] 4.3 ``tests/fixtures/emitted/<family>/metadata/devices/``
      directory is gone (verified: zero matches for the
      ``metadata/devices/`` path under fixtures).
- [ ] 4.4 ``pytest --runtime-cpp-smoke`` stays green for every
      admitted device.  *(Deferred — smoke harness predates
      the merge; runs on CI rather than locally as part of
      this archive.)*

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/artifact-contract/spec.md`
      capturing the slimmed JSON layout.  *(Authored in
      ``specs/artifact-contract/spec.md``: 3 ADDED Requirements
      covering YAML pointer, family-rollup removal, and
      pruned-reports.)*
- [x] 5.2 `openspec validate prune-redundant-json-artifacts
      --strict` passes.
- [x] 5.3 `pytest -q` (relevant suites) + `ruff check` clean.
- [x] 5.4 CI workflow assertions in
      `.github/workflows/bootstrap-family.yml` already only
      check ``family-index.json`` existence — no edits needed.
