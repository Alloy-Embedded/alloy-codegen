# Enforce Strict Typing and 100% Golden Coverage

## Why

Two quality cliffs cap how confidently we can scale alloy-codegen to 1.000+ chips:

1. **Type-checker noise**: 18 `type: ignore` suppressions scattered across the codebase, no `pyright` / `mypy` strict gate in CI.  ruff catches lints but not type errors.  As more vendors land, copy-paste typing bugs (wrong dataclass field type, `None`-comparison on a `str | None`) will silently survive review.
2. **Golden coverage gap**: only **8 of the admitted devices** have full golden snapshots under `tests/fixtures/emitted/` (out of 17 admitted today, growing toward 1.000+).  Devices without goldens are validated only by smoke compile + emission count — a regression in *content* (wrong base address, missing field) goes unnoticed.

Both gates are cheap to add today, expensive to retrofit at 100+ chips.  This change adds the gates before scale exposes the gaps.

## What Changes

- **Strict pyright gate in CI**:
  - Add `pyright` (or equivalent) to the repo's dependencies.
  - Configure `pyrightconfig.json` with `"strict": true` for `src/alloy_codegen/**` and `"basic"` for `tests/**`.
  - First pass: silence/fix all reported errors (the existing 18 `type: ignore` suppressions stay; the new strict pass surfaces the underlying issues that ruff missed).
  - CI fails any PR that introduces a new type error.
- **Auto-golden-coverage**:
  - Today's `tests/conftest.py` has a `--update-goldens` mode that's manual.  Extend it: for *every* admitted device, fail the test if a golden file is missing (rather than just for the 8 today).
  - Add a CI helper (`scripts/regen_all_goldens.py`) that regenerates every golden in one pass; PR template asks contributors to attach the regen output diff.
  - Coverage dashboard reports `golden_coverage = covered_devices / admitted_devices` and CI fails if it ever drops below 100% on `main`.
- **Forbidden-pattern gate**:
  - Extend `artifact-contract.find_runtime_cpp_string_violations` style gates with new patterns:
    - No `dynamic_cast`, no `typeid`, no exception-throwing constructors in driver-semantics emitters.
    - No raw-pointer arithmetic in emission helpers (encourage `std::span`-shaped iteration).
  - These are forward-looking constraints to prevent code-smell from creeping in as more contributors land changes.

## Impact

- **Affected specs**: MODIFIED `validation-and-gates` (gains strict-typing + 100%-golden-coverage requirements).
- **Affected code**: new `pyrightconfig.json`; CI workflow update (`.github/workflows/ci.yml`); `tests/conftest.py` golden-coverage extension; new `scripts/regen_all_goldens.py`; possibly small typing fixes in `src/alloy_codegen/`.
- **Dependencies**: independent of P0/P1/P2/P3; ideally lands **before** the P3 admission OpenSpecs so each new family arrives with full goldens by default.  Should land alongside or just after P4 (the per-class refactor benefits from strict typing surfacing latent issues).
- **Risk**: First strict-pyright pass may surface 50-100 errors that take a day to fix.  Mitigation: phase the rollout — strict mode on `runtime_driver/` first (post-P4 refactor), expand to other modules over follow-up PRs.
- **Out of scope**: type-stub generation (no public-facing typing surface to ship); IDE configuration (settings.json, etc.).
