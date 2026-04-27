# Invert Patch Semantics: Patches Are Diffs, IR Is The Truth

## Why

Today the patch JSONs under `patches/<vendor>/<family>/devices/`
are the **source of truth**: ~180 LOC per device, ~14k LOC total
across 9 families, growing linearly with admitted MCUs.  The
problem: 90% of every patch is fields that could be derived from
the canonical sources (SVD, ATDF, DTS) — the patches duplicate
authoritative data so the pipeline can read it back.

Inverting the relationship — IR derived from sources is the truth,
patches are *only the diff* (overrides where sources are wrong or
incomplete) — collapses per-device patches from ~180 LOC to ~10-20
LOC and makes 1000-MCU scale tractable.

## What Changes

- New patch resolution model: at load time, the pipeline first
  builds a "source-derived IR baseline" from authoritative
  vendor data (SVD/ATDF/DTS).  The patch JSON is then applied
  as a **deep merge override** on top of that baseline.
- `patches/<vendor>/<family>/family.json` continues to carry
  family-level overrides.  `devices/<device>.json` becomes
  *diff-only*: any field that matches the baseline SHALL be
  omitted; only legitimate overrides survive.
- New tool `scripts/minify_device_patches.py` walks every
  existing patch, computes the diff vs. the source-derived
  baseline, and rewrites the file in place with only the
  overrides retained.  Reversible: an `--explode` mode rebuilds
  the full patch by re-merging.
- The patch schema gains a top-level `"$baseline-revision"` field
  recording the source SHA the diff was computed against — so we
  can detect when a vendor source updates and a patch needs
  re-review.
- A new validation gate refuses to admit a patch that contains
  fields matching the baseline (no redundant data) — keeps
  patches from drifting back into copy-of-source.
- Migration is **opt-in per family**: families flip to diff-mode
  one at a time after `minify_device_patches.py` runs on them
  and tests stay green.

## Impact

Per-device patch JSON drops 80-90%.  Reviewing a new device's
patch becomes "what is genuinely overridden" instead of "is this
180-line dump correct".  Unblocks bulk admission via
`autogen-device-patches-from-svd` because the autogen output is
also diff-shaped: it produces the baseline + the overrides the
generator can prove, and a human reviews only the overrides.

## What this DOES NOT do

- Does not change the validate or emit stages — the resolved
  in-memory IR is identical before and after this change.
- Does not eliminate patches.  Vendor data has bugs, ambiguities,
  and gaps; we still need an override layer.  The change is in
  what patches *contain*, not whether they exist.
