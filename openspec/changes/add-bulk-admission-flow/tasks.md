# Tasks — add-bulk-admission-flow

## Phase 1: CLI scaffolding

- [ ] 1.1 New script `scripts/bulk_admit.py` with argparse
      (`--vendor`, `--family`, `--device`, `--limit`,
      `--dry-run`, `--out-root`).
- [ ] 1.2 Catalog resolver: load
      `data/known_devices.toml`, filter by the requested
      `(vendor, family[, device])`.
- [ ] 1.3 Source-path resolver: dispatch on the catalog entry's
      `source_pack` / `probe_rs_target` to either an SVD path
      (under a configured CMSIS-Pack root) or a Zephyr DTS path.
- [ ] 1.4 Autogen dispatcher: call
      `scripts.autogen_device_patches.build_patch(...)` for SVD
      or `scripts.autogen_device_patches_from_dts.build_patch(...)`
      for Zephyr.

## Phase 2: DTS-flavoured autogen

- [ ] 2.1 New script `scripts/autogen_device_patches_from_dts.py`
      mirroring the SVD generator: same output shape
      (`$autogen` / `$todo_review` envelope) but seeded from the
      Zephyr DTS adapter's intermediate objects rather than SVD.
- [ ] 2.2 Reuses the existing `autogen_device_patches`
      determinism contract (sorted lists, fixed key order,
      byte-stable output).

## Phase 3: Registry scaffold output

- [ ] 3.1 For each admitted device, print a stub for
      `vendors/_register_<vendor>_<family>.py` if the family is
      net-new (matching the existing
      `_register_nordic_nrf52.py` shape).
- [ ] 3.2 Print a one-line `bootstrap.py:DEVICE_REGISTRY` patch
      (e.g. `("renesas", "ra4"): ("r7fa4m1ab", "r7fa6m4af"),`)
      so the reviewer can drop it in.
- [ ] 3.3 Print a one-line
      `bootstrap.py:SOURCE_BUNDLES` companion entry.

## Phase 4: Review tooling

- [ ] 4.1 `scripts/bulk_admit_review.py` walks
      `patches/**/*.json`, counts `$todo_review` array length
      per file, and emits a Markdown table sorted by review
      density.
- [ ] 4.2 Output identifies the top-5 fields most often left
      as TODO_REVIEW so reviewers know where to focus
      template-library extensions.

## Phase 5: Tests

- [ ] 5.1 End-to-end test: synthesise a small fake catalog +
      SVD tree under `tmp_path`, run `bulk_admit --dry-run`,
      assert the printed JSON drafts are byte-deterministic.
- [ ] 5.2 Negative test: requesting a `(vendor, family)` not in
      the catalog fails with a helpful message listing the
      closest matches.
- [ ] 5.3 `bulk_admit_review` test asserts the Markdown output
      is stable and counts match.

## Phase 6: Docs + spec

- [ ] 6.1 `docs/bulk-admission.md` walks through admitting a
      sample family end-to-end (with screenshots / sample
      output).
- [ ] 6.2 Spec delta in `specs/vendor-admission/spec.md`.
- [ ] 6.3 `openspec validate add-bulk-admission-flow --strict`
      passes.
- [ ] 6.4 `pytest -q` + `ruff check` clean.
