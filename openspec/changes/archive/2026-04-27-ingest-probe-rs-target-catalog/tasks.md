# Tasks — ingest-probe-rs-target-catalog

## Phase 1: Importer

- [x] 1.1 Create `tools/import_probe_rs_targets.py` CLI:
      `python -m tools.import_probe_rs_targets --probe-rs-root <path>`.
- [x] 1.2 Parse every `targets/*.yaml`.  Extract: target name,
      vendor, family, part number, core, memory map, flash algo
      reference.
- [x] 1.3 Canonicalise vendor/family identity to alloy-codegen
      conventions (e.g. probe-rs `STMicroelectronics` → alloy `st`).
- [x] 1.4 Emit `data/known_devices.toml` sorted by
      `(vendor, family, device)` for byte-deterministic output.
- [x] 1.5 Emit `data/known_devices.meta.toml` recording the
      probe-rs commit SHA the catalog was imported from.

## Phase 2: Validation guard

- [x] 2.1 Test that every device the alloy pipeline admits today
      resolves to a known-devices entry (or is explicitly
      allow-listed as "alloy-admitted-but-not-in-probe-rs").
- [x] 2.2 Test that `data/known_devices.toml` is byte-stable when
      re-importing from the pinned SHA.

## Phase 3: Spec + final checks

- [x] 3.1 Spec delta in `specs/vendor-admission/spec.md`.
- [x] 3.2 Document the workflow in `docs/known-devices.md`.
- [x] 3.3 `openspec validate ingest-probe-rs-target-catalog
      --strict` passes.
- [x] 3.4 `pytest -q` + `ruff check` clean.
