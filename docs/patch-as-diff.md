# Patch-as-Diff Model

The `patches/<vendor>/<family>/devices/<device>.json` files have
historically been the **source of truth** — ~180 LOC per device,
~14k LOC across the 9 admitted families.  The
`invert-patch-as-diff` change inverts that relationship: the
**source-derived IR** (CMSIS-SVD, ATDF, Zephyr DTS, modm-devices)
becomes the truth, and patches carry only the **diff** between
that baseline and the desired final IR.

This document describes the schema + tooling that make the diff
model possible.  Migration is **opt-in per family** — the existing
patches keep working unchanged; per-family roll-out runs the
minifier on a family's patches and verifies tests stay green.

## Schema additions

Every device patch may declare a top-level `"$baseline-revision"`
string recording the source identifier the diff was minified
against:

```jsonc
{
  "patch_id": "st-stm32g0-stm32g071rb-bootstrap",
  "device": "stm32g071rb",
  "$baseline-revision": "a1b2c3d4e5f60718",
  "package": "lqfp64",
  "core": "cortex-m0plus",
  "summary": "...",
  // ... only the fields that override the baseline ...
}
```

The dollar prefix is intentional — JSON keys starting with `$` are
reserved for schema metadata so they cannot collide with future
patch fields.

The pipeline parser surfaces this on `DevicePatch.baseline_revision`
(empty string for legacy patches that omit the field).

## Stale-baseline detection

`alloy_codegen.patches.validate_baseline_revision(patch_path,
accept_stale_baselines=False)` compares the patch's recorded
`$baseline-revision` against the SHA-16 of the patch's current
contents.  When the values disagree, the loader raises
`StageExecutionError` identifying which source moved:

```
baseline-revision drift for stm32g071rb.json: patch declares
'0000staleshahash' but current source revision is 'a1b2c3d4e5f60718';
re-run scripts/minify_device_patches.py against the new source
or pass --accept-stale-baselines to override.
```

The override flag exists so reviewers can opt in to using a stale
diff while they re-derive it (e.g., during a vendor-source bump
where the diff is correct but the SHA needs refreshing).

Legacy patches that omit `$baseline-revision` skip the check
entirely — migration is per-family opt-in, so families that haven't
been minified yet still load.

## Minifier tool

```bash
# Minify one device:
python -m scripts.minify_device_patches --vendor st --family stm32g0 --device stm32g071rb

# Minify every admitted device (opt-in per family in practice):
python -m scripts.minify_device_patches --all

# Restore the original patch from the .full.json backup:
python -m scripts.minify_device_patches --vendor st --family stm32g0 --device stm32g071rb --explode
```

The minifier uses **greedy per-key minimization**:

1. Snapshot the IR produced by `stages.normalize.run` against the
   patch as-is — the **reference IR**.
2. For each top-level optional key in the patch, drop it, re-run
   normalize, and compare the resulting IR against the reference.
3. If the IR is byte-identical, the key is redundant (the value
   matches what the pipeline derives from sources alone) and stays
   dropped.  If the IR differs, the key is restored.
4. Stamp `$baseline-revision` on the result.

The first-run on each device creates a `<patch>.full.json` backup
so `--explode` can reverse the operation for human inspection.

### Required fields

The schema-required fields are **never** dropped, even if their
values happen to coincide with raw-source data:

- `patch_id`, `device`, `svd_file`, `pin_data_file`, `package`,
  `pin_count`, `core`, `summary`
- `peripherals` (admit-list semantics — the pipeline filters
  unknown peripherals against this set)

### Per-family migration plan

Bulk reduction depends on **enriching family.json** so the device
patch's family-wide constants (e.g., shared register layouts, ADC
calibration recipes) flow from the family overlay rather than
being repeated per-device.  The minifier captures fields that are
already redundant given the current family.json — running it on a
family today typically yields zero reductions because the
device-level patches carry data the family.json does not.

Roll-out per family is therefore a two-step process:

1. **Lift** redundant device-level fields into family.json (a
   manual edit; the goal is "things that are the same for every
   device in the family live in family.json").
2. **Run** `scripts/minify_device_patches.py --all` to drop the
   now-redundant per-device fields and stamp `$baseline-revision`.

The end state: ~10-20 LOC per device, sub-2k LOC across all
admitted families.  This is the path to 1000-MCU scale.

## Conflict policy

Patches still win on conflict.  The catalog of source-derived data
informs what *can* be expressed in the baseline; if a hand-curated
patch corrects vendor data, that correction survives in the diff.
The invariant is: `baseline + diff = pre-migration IR` byte-for-byte.
