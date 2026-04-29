# Tasks — enforce-strict-typing-and-golden-coverage

## Phase 1: Pyright integration

- [ ] 1.1 Add `pyright` to `pyproject.toml` dev dependencies.
- [ ] 1.2 Create `pyrightconfig.json` with module-scoped
      strictness:
      - `"strict"`: `src/alloy_codegen/runtime_driver/**`,
        `src/alloy_codegen/ir/**`, `src/alloy_codegen/stages/**`.
      - `"basic"`: rest of `src/alloy_codegen/**` and
        `tests/**`.
- [ ] 1.3 Run pyright locally; triage reported errors.
- [ ] 1.4 Fix or `# pyright: ignore[<reason>]` each error
      with a one-line justification (no blank suppressions).
- [ ] 1.5 Add `pyright` step to `.github/workflows/ci.yml`.

## Phase 2: Golden-coverage 100%

- [ ] 2.1 Extend `tests/conftest.py` to enumerate admitted
      devices and assert each has a golden snapshot directory.
- [ ] 2.2 Generate goldens for every admitted device that
      currently lacks them (esp32-classic, esp32-wroom32,
      stm32g030f6, atsame70n21b, mimxrt1064, nrf52840 if
      missing).
- [ ] 2.3 Add `scripts/regen_all_goldens.py` (one-button
      regen across every admitted device).
- [ ] 2.4 Coverage dashboard regenerated to show
      `golden_coverage: 17/17 = 100%`.
- [ ] 2.5 CI gate: `golden_coverage < 100%` fails the build.

## Phase 3: Forbidden-pattern gate

- [ ] 3.1 Extend the existing `artifact-contract` gate
      family with checks for:
      - `dynamic_cast` in any emitted C++ file (forbidden).
      - `typeid` in any emitted C++ file (forbidden).
      - `throw` in any emitter Python file (no exceptions in
        driver-semantics codegen — emitters return
        `EmittedArtifact | None`).
- [ ] 3.2 First-pass run; fix any violations that surface.
- [ ] 3.3 CI gate: any new violation fails the build.

## Phase 4: Spec + final checks

- [ ] 4.1 MODIFIED `validation-and-gates` requirement adding
      strict-typing rule + 100%-golden-coverage rule +
      forbidden-pattern rule.
- [ ] 4.2 `openspec validate
      enforce-strict-typing-and-golden-coverage --strict`
      passes.
- [ ] 4.3 `pytest -q` + `ruff check` + `pyright` clean on
      `main`.
- [ ] 4.4 Document the gates in `CONTRIBUTING.md` so new
      contributors see them up front.
