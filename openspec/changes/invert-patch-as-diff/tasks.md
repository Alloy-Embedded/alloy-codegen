# Tasks — invert-patch-as-diff

## Phase 1: Baseline derivation

- [ ] 1.1 Extract a "source-derived baseline IR" builder from the
      existing normalize stage.  Given `(vendor, family, device,
      raw sources)`, produce the same fields the patch currently
      carries — without any patch applied.
- [ ] 1.2 Document the contract: a baseline has every field the
      patch can override, populated from authoritative sources.

## Phase 2: Patch-as-diff loader

- [ ] 2.1 New loader `patches.load_patch_as_diff(...)` that
      deep-merges a patch JSON on top of a baseline IR.
- [ ] 2.2 Add `"$baseline-revision"` schema field at the top of
      every patch — records the source SHA the diff was computed
      against.
- [ ] 2.3 Validation: refuse to load a patch whose
      `$baseline-revision` does not match the current source SHA
      without an explicit `--accept-stale-baselines` flag.

## Phase 3: Minifier tool

- [ ] 3.1 `scripts/minify_device_patches.py` walks every existing
      patch, computes diff vs. baseline, rewrites in place.
- [ ] 3.2 Reversible `--explode` mode re-merges baseline + diff
      to produce the full patch (for human inspection).
- [ ] 3.3 Validation gate: a patch SHALL NOT contain any field
      that matches the baseline value — checked by a unit test.

## Phase 4: Per-family migration

- [ ] 4.1 Migrate STM32G0 first (smallest fixture).  Run
      minifier, verify pipeline output unchanged, commit reduced
      patches.
- [ ] 4.2 Repeat for the remaining 8 admitted families.
- [ ] 4.3 Goldens unchanged after migration — patches shrink, but
      emitted artifacts are byte-identical.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/canonical-device-ir/spec.md`.
- [ ] 5.2 Document the diff model in `docs/patch-as-diff.md`.
- [ ] 5.3 `openspec validate invert-patch-as-diff --strict` passes.
- [ ] 5.4 `pytest -q` + `ruff check` clean.
