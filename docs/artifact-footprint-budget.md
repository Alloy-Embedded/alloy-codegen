# Artifact Footprint Budget Gate

The publish stage measures every emitted artifact's UTF-8 byte
size and compares it against a budget declared in
`data/artifact_footprint_budget.toml`.  An exceedance of the
`warn` budget surfaces in the publication's warnings; an
exceedance of the `fail` budget aborts the build.

This caps consumer-side compile-time + firmware-image blast
radius as the device catalog scales: if a future MCU with
thousands of pinmux candidates would produce a multi-megabyte
`pin_validation.hpp`, the gate fires before the artifact reaches
the publication root.

## Files

| File | Purpose |
|------|---------|
| `data/artifact_footprint_budget.toml` | Per-artifact `warn` + `fail` byte budgets, plus a catch-all `[default]` block.  Defaults derived from the largest currently admitted device's actual output + headroom — no admitted device fails on day one. |
| `data/artifact_footprint_overrides.toml` | Per-device exemptions (`vendor`, `family`, `device`, `artifact` tuple).  Initially empty; an override carries a one-line rationale comment so future maintainers see why the entry exists. |
| `src/alloy_codegen/footprint_budget.py` | Loader + comparator.  `evaluate_artifacts(...)` returns the list of violations, sorted `fail` first. |

## Adding a new artifact

When you ship a new emitter, add a `[artifact."<name>.hpp"]`
entry to the budget file with a `warn`/`fail` sized for what the
emitter currently produces plus headroom.  If you skip this
step, the artifact lands under the `[default]` catch-all, which
is intentionally generous (~512 KiB warn / 1 MiB fail) — you
will pass on day one but the budget is loose.  Tighten it.

## Bumping a budget

Two paths:

1. **Global tighten / loosen** — edit
   `data/artifact_footprint_budget.toml` directly.  Reviewable
   diff; tests run against the new budget.
2. **Per-device exemption** — when one specific MCU has a
   genuinely large output (e.g., an iMXRT with 800 IOMUX
   candidates), add an entry to
   `data/artifact_footprint_overrides.toml`:

   ```toml
   [[override]]
   vendor = "nxp"
   family = "imxrt1060"
   device = "mimxrt1062"
   artifact = "pin_validation.hpp"
   warn = 262144
   fail = 524288
   rationale = "iMXRT1060 ships 800 IOMUX pin candidates; ..."
   ```

   The override applies only to the matched
   `(vendor, family, device, artifact)` tuple — every other
   device sharing the same artifact name still hits the global
   default.

## Failure mode

When `fail` is exceeded and no override applies, the publish
stage aborts with a one-line message identifying:

- the offending artifact path,
- the actual byte size,
- the budget that was breached,
- the override file path so the reviewer knows where to act.

The corresponding `StageResult` carries `status="failed"` and
`publication_mode="blocked"`.  No artifact is promoted to the
publication root.

## What this gate does NOT do

- It does **not** measure consumer-side firmware image size.
  That is the runtime-lite consumer-verification harness's
  domain.  This gate measures emitted source bytes only.
- It does **not** auto-split artifacts.  A breach is a build
  failure; resolution is a human decision (raise the budget,
  refactor the emitter, exempt the device).
