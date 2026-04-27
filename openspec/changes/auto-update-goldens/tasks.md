# Tasks — auto-update-goldens

## Phase 1: Pytest plumbing

- [ ] 1.1 Add `ALLOY_UPDATE_GOLDENS` env var support to
      `tests/conftest.py`.
- [ ] 1.2 Add `--update-goldens` pytest CLI flag (alias for the
      env var).
- [ ] 1.3 Helper `assert_matches_golden(artifact_content,
      fixture_path)` that, when the flag is set, writes the
      content to disk instead of asserting.

## Phase 2: Migrate existing assertions

- [ ] 2.1 Replace `assert X.content == Y.read_text(...)` patterns
      in `tests/test_emit.py` with the new helper.
- [ ] 2.2 Same migration in any other test that byte-compares
      goldens.

## Phase 3: Guardrails

- [ ] 3.1 The flag refuses to run if `git status --porcelain`
      reports dirty non-fixture files — prevents accidentally
      baking source changes into goldens.
- [ ] 3.2 `make update-goldens` (or top-level script) wraps the
      flag and runs `git diff --stat tests/fixtures/` after.

## Phase 4: Spec + final checks

- [ ] 4.1 Spec delta in `specs/validation-and-gates/spec.md`.
- [ ] 4.2 Document the workflow in `docs/contributing.md` or a
      new `docs/updating-goldens.md`.
- [ ] 4.3 `openspec validate auto-update-goldens --strict` passes.
- [ ] 4.4 `pytest -q` + `ruff check` clean.
