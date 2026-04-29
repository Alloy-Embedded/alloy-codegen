# Tasks — prune-redundant-json-artifacts

## Phase 1: Drop unused metadata emitters

- [ ] 1.1 Delete the seven family-rollup emitters from
      `src/alloy_codegen/emission.py`:
      `emit_family_connectivity`,
      `emit_system_descriptors_metadata`,
      `emit_ip_blocks_metadata`,
      `emit_packages_metadata`,
      `emit_connectors_metadata`,
      `emit_capabilities_metadata`,
      `emit_device_metadata`.
- [ ] 1.2 Remove their imports from `stages/emit.py` and the
      corresponding entries in the `artifacts: list[EmittedArtifact]`
      assembly.
- [ ] 1.3 Drop the `_device_metadata_path` /
      `_family_metadata_path` helpers if no surviving emitter
      uses them.

## Phase 2: Drop unused reports

- [ ] 2.1 Delete `emit_runtime_capability_summary_report` and
      `emit_runtime_compatibility_matrix_report` from
      `src/alloy_codegen/runtime_reports.py`.
- [ ] 2.2 Remove their imports + emit-stage call sites.
- [ ] 2.3 Confirm no test references them (grep
      `runtime-capability-summary\|runtime-compatibility-matrix`).

## Phase 3: Update family-index.json

- [ ] 3.1 In `emit_family_index`, change each device entry's
      `metadata_path` field to a `yaml_path` pointing at the
      canonical YAML location:
      `data/devices/vendors/<vendor>/<family>/devices/<device>.yml`.
- [ ] 3.2 Update the field name in tests + any consumer (CI
      workflow only checks for *existence* today, so the body
      change is safe).

## Phase 4: Regenerate goldens + verify

- [ ] 4.1 `ALLOY_UPDATE_GOLDENS=1 pytest tests/test_emit.py` —
      regenerate the emitted-artifact tree.  9 JSON files per
      family disappear; `family-index.json` body changes.
- [ ] 4.2 Confirm `tests/fixtures/emitted/<family>/metadata/`
      no longer contains the deleted rollups.
- [ ] 4.3 Confirm `tests/fixtures/emitted/<family>/metadata/devices/`
      directory is gone.
- [ ] 4.4 `pytest --runtime-cpp-smoke` stays green for every
      admitted device (no header references the deleted JSONs).

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/artifact-contract/spec.md`
      capturing the slimmed JSON layout.
- [ ] 5.2 `openspec validate prune-redundant-json-artifacts
      --strict` passes.
- [ ] 5.3 `pytest -q` + `ruff check` clean.
- [ ] 5.4 Update CI workflow assertions in
      `.github/workflows/bootstrap-family.yml` to drop any
      reference to the removed artifacts (only the existence
      check on `family-index.json` is currently used; nothing
      else needs editing).
