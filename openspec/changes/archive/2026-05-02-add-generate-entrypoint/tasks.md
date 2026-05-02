# Tasks — add-generate-entrypoint

## Phase 1: Core entrypoint

- [x] 1.1 `alloy_codegen.entrypoint.generate(config, out_dir)`
      lives in its own module so the package `__init__` stays
      thin.
- [x] 1.2 Resolves `(vendor, family, device)` from
      `config.chip`; falls through to a `ConfigError` when the
      caller passed only `config.board` (alloy-codegen doesn't
      host a board catalogue).
- [x] 1.3 Calls `load_with_synthesis(...)` then iterates the
      four emitters, writing each artifact under `out_dir`.
- [x] 1.4 Returns `tuple[Path, ...]` of files written, sorted
      and stable.

## Phase 2: Errors + types

- [x] 2.1 `alloy_codegen.errors.ConfigError` covers the
      "no chip / unknown device / unknown vendor / unknown
      family" cases with helpful messages (closest matches /
      pointer to alloy_cli.core.boards.lookup).
- [x] 2.2 Existing `StageExecutionError` continues to wrap
      synthesis failures.

## Phase 3: Re-exports

- [x] 3.1 `alloy_codegen/__init__.py` re-exports `generate`,
      `ConfigError`, `StageExecutionError`, and `__version__`.

## Phase 4: Tests

- [x] 4.1 `tests/test_entrypoint.py` — 10 cases: package
      surface, happy path emits 4 artifacts, sorted return,
      auto-create out_dir, missing chip+board raises,
      board-only raises with hint, unknown vendor / family /
      device, partial chip fields.

## Phase 5: Spec + final checks

- [x] 5.1 Spec deltas in
      `specs/codegen-alloy-boundary/spec.md`.
- [x] 5.2 `openspec validate add-generate-entrypoint
      --strict` passes.
