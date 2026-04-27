# Tasks — auto-update-goldens

## Phase 1: Pytest plumbing

- [x] 1.1 Added `ALLOY_UPDATE_GOLDENS` env var support to
      `tests/conftest.py` (parsed alongside the CLI flag).
- [x] 1.2 Added `--update-goldens` pytest CLI flag via
      `pytest_addoption` in `tests/conftest.py`.
- [x] 1.3 Helpers `assert_matches_text_golden` and
      `assert_matches_json_golden` live in
      `tests/golden_helpers.py` and write the fixture instead of
      asserting when `update_mode=True`.

## Phase 2: Migrate existing assertions

- [x] 2.1 Replaced every `assert X.content == Y.read_text(...)`
      pattern in `tests/test_emit.py::test_emit_matches_golden_artifacts`
      with the new helpers (~26 assertions collapsed into
      tabular `_text(...)` / `_json(...)` calls).
- [x] 2.2 Migrated the 2 NXP golden assertions in
      `tests/test_nxp_mcux.py::test_emit_nxp_imxrt1060_matches_golden_fixtures`.

## Phase 3: Guardrails

- [x] 3.1 The session-scoped `goldens_update_mode` fixture
      raises `pytest.UsageError` listing offending paths when
      `git status --porcelain` reports dirty files outside
      `tests/fixtures/`.
- [x] 3.2 `scripts/update_goldens_pytest.sh` wraps the flag and
      runs `git diff --stat tests/fixtures/` after.

## Phase 4: Spec + final checks

- [x] 4.1 Spec delta in `specs/validation-and-gates/spec.md`.
- [x] 4.2 Documented the workflow in `docs/updating-goldens.md`.
- [x] 4.3 `openspec validate auto-update-goldens --strict` passes.
- [x] 4.4 `pytest -q` + `ruff check` clean (with and without
      the new flag).
