# Expose a Top-Level `generate(config, out_dir)` Entrypoint

## Why

`alloy-cli` consumes alloy-codegen via Python import:

```python
# alloy-cli/src/alloy_cli/core/codegen.py
module = importlib.import_module("alloy_codegen")
callable_obj = getattr(module, "generate", None)
```

That import path silently fails today — `alloy_codegen.__init__`
re-exports only `__version__`.  The CLI falls back to a
"skipped: alloy-codegen-not-installed" stub for every project,
and `alloy build` ends up shipping stale (or empty) generated/
trees.

The CLI's contract (encoded in
`openspec/specs/build-pipeline/spec.md`) treats codegen as the
critical pre-cmake step.  We need to publish a stable Python
entrypoint that fulfils that contract.

## What Changes

### Public callable

- `alloy_codegen.generate(config, out_dir)` becomes the
  canonical Python entrypoint.
- `config` is duck-typed — any object exposing
  `.chip.vendor / .chip.family / .chip.device` (or
  `.board.id`) parses through.  Concretely it accepts the
  `alloy_cli.core.project.ProjectConfig` shape but doesn't
  import alloy-cli (no upstream dependency).
- `out_dir: pathlib.Path` is the destination directory.
  Files land flat (`peripheral_traits.h`, `runtime_init.c`,
  `linker.ld`, `vector_table.c`); the per-vendor subtree is
  the CLI's responsibility, not ours.
- Returns `tuple[Path, ...]` of files written so the caller
  can log / cache them.

### Boards stay out of scope

- alloy-codegen owns devices (vendor / family / chip), not
  boards.  When `config.board` is set but `config.chip`
  isn't, `generate` raises `ConfigError` and tells the
  caller to resolve the board id upstream (alloy-cli's
  `core.boards.lookup` already does this).

### Errors

- A new `alloy_codegen.errors.ConfigError` surfaces the two
  failure modes:
  - `config has neither chip nor board` → ConfigError.
  - `device <vendor/family/device> not in registry` →
    ConfigError.
- StageExecutionError continues to wrap downstream parse +
  synthesis failures.

### Re-exports

- `__init__.py` re-exports `generate`, `ConfigError`, and the
  existing `__version__`.

## Impact

- `alloy build` runs the codegen step end-to-end against any
  alloy-cli project that pins `alloy-codegen` as a dep.
- alloy-cli's existing stamp-cache keys on `IR SHA +
  alloy-codegen __version__` — which now actually advances
  when alloy-codegen ships a release.
- Future MCP tools (`alloy.regenerate`) automatically benefit
  with no further wiring.

## What this DOES NOT do

- Does not change the existing `alloy-codegen <target>` CLI.
- Does not introduce a new artefact format — the four
  emitters (linker_script / vector_table /
  peripheral_traits / runtime_init) ship verbatim.
- Does not wire the CLI's stamp-cache or progress callbacks
  here; those stay alloy-cli's concern.
