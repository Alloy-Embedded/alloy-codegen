# Tasks — autogen-device-patches-from-svd

## Phase 1: Generator core

- [x] 1.1 Create `scripts/autogen_device_patches.py` CLI:
      `python -m scripts.autogen_device_patches --vendor st
      --family stm32g0 --device stm32g071rb --svd <path>`.
- [x] 1.2 Extract device identity (name, optional package via
      PDSC, core via SVD `<cpu>` block).
- [x] 1.3 Extract memory regions from CMSIS-Pack PDSC `<memory>`
      entries when `--pack` is supplied; SVD alone has no
      flash/sram declarations.
- [x] 1.4 Extract peripheral instance list (sorted by name) via
      the existing `parse_raw_device_document`.
- [x] 1.5 Extract IRQ vector table (sorted by `(line, name)`) via
      the existing parser.
- [x] 1.6 Mark every field the generator cannot derive as
      `"TODO_REVIEW"` and record its key in the top-level
      `$todo_review` array.  Tier 2/3/4 list fields ship as
      empty lists; their names are added to `$todo_review`.
- [x] 1.7 Generator output is byte-deterministic given the same
      inputs (sorted lists, fixed key order, `indent=2`,
      `ensure_ascii=False`, trailing newline).

## Phase 2: Diff tooling

- [x] 2.1 `scripts/diff_device_patch.py` shows a structured diff
      with three buckets (only_autogen / only_curated / changed).
      Emptiness-aware so `TODO_REVIEW` placeholders and `[]`
      lists do not pollute the diff.

## Phase 3: Validation against admitted devices

- [x] 3.1 Tests in `tests/test_autogen_device_patches.py`:
      determinism, peripheral coverage vs. SVD, IRQ sort
      stability, `$todo_review` enumerates the undriverable
      fields, `<cpu>` block resolves to a canonical core string.
- [x] 3.2 Documented residual review surface in
      `docs/autogen-device-patches.md`.

## Phase 4: Spec + final checks

- [x] 4.1 Spec delta in `specs/vendor-admission/spec.md`.
- [x] 4.2 `openspec validate autogen-device-patches-from-svd
      --strict` passes.
- [x] 4.3 `pytest -q` + `ruff check` clean.
