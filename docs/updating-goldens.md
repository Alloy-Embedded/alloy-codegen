# Updating Test Goldens

Tests under `tests/test_emit.py` and `tests/test_nxp_mcux.py`
byte-compare the pipeline's emitted artifacts against committed
fixtures under `tests/fixtures/emitted/<family>/`.  When you make
an intentional change to an emitter (new typed enum, new spec
field, etc.), every affected golden has to be rewritten.

Two paths are supported:

## 1. Pytest-driven (recommended for diffs you wrote)

Added by the OpenSpec change `auto-update-goldens`.

```bash
# Either set the env var:
ALLOY_UPDATE_GOLDENS=1 pytest -q

# Or use the CLI flag:
pytest --update-goldens -q

# Convenience wrapper that also prints the diff stat after:
scripts/update_goldens_pytest.sh
```

When the flag is set, every golden helper
(`assert_matches_text_golden`, `assert_matches_json_golden`)
**rewrites the fixture instead of asserting**.  The resulting
`git diff tests/fixtures/` is the reviewable artefact.

### Guardrails

- The flag is **off by default**.  CI never sets it, so golden
  mismatches still fail the build under normal conditions.
- The flag **refuses to run** if `git status --porcelain` reports
  modified files outside `tests/fixtures/`.  This prevents
  accidental source changes from being baked into goldens.
- The flag is opt-in per run.  Setting it in your shell rc is
  unsafe — you'll bake unintentional changes the next time you
  forget to unset it.

## 2. Pipeline-driven (refresh families wholesale)

`scripts/update_goldens.py` was the original tool, predating the
pytest flag.  It runs the emit pipeline directly, walks the
emitted artifacts, and writes any changed text artifact to its
fixture path.  Use this when you want to refresh a whole family
without running pytest:

```bash
python scripts/update_goldens.py
```

Both tools are idempotent; running them on a clean tree is a
no-op.

## Workflow

1. Make the source change.  Run `pytest -q` — see which goldens
   fail.
2. Run `scripts/update_goldens_pytest.sh` (or set the env var).
3. Review `git diff tests/fixtures/` carefully.  Are these the
   changes you expect?
4. Commit `src/` + `tests/fixtures/` together.  CI will catch any
   golden that doesn't match the new emitter output.

## Why two tools?

The pytest flag (#1) covers any test that uses
`assert_matches_text_golden` / `assert_matches_json_golden`.  The
older `update_goldens.py` (#2) walks the emit pipeline directly
and is faster for whole-family refreshes.  They will converge as
more tests migrate to the helpers.
