# Auto-Update Test Goldens

## Why

Test fixtures in `tests/fixtures/emitted/<family>/` are byte-compared
to the pipeline's emitted artifacts.  When an emitter changes
intentionally (e.g. new typed enum, new spec field), every golden
across 9 families must be hand-regenerated.  Today this is a
copy-paste-from-stdout chore that is error-prone and slows every
emitter change.

A pytest flag that opts into rewriting the golden tree from a
known-good run cuts the loop from "diff stdout, paste, commit"
to "set the flag, run, review the git diff".

## What Changes

- New env var `ALLOY_UPDATE_GOLDENS=1` (and matching
  `--update-goldens` pytest CLI flag via a conftest hook).
- When set, every assertion of the form
  `assert artifact.content == fixture_path.read_text(...)` is
  rewritten as a `Path.write_text(...)` instead of an `assert`.
- The flag is **off by default** in CI — golden mismatches still
  fail the build under normal conditions.
- A guardrail check refuses to run with the flag set when
  `git status` is dirty for non-fixture files (so accidental
  source changes don't get baked into goldens).
- `make update-goldens` / `just update-goldens` shortcut runs
  the flag plus `git diff --stat tests/fixtures/` so the diff is
  visible before commit.

## Impact

Adding a new emitter (e.g. the recent `pin_validation.hpp`) stops
requiring per-family copy-paste.  Reduces friction on any change
that touches output, which is most of them.  No runtime/footprint
impact — pure dev tooling.
