# Tasks — autogen-device-patches-from-svd

## Phase 1: Generator core

- [ ] 1.1 Create `scripts/autogen_device_patches.py` CLI:
      `python -m scripts.autogen_device_patches --vendor st
      --family stm32g0 --device stm32g071rb --svd <path>`.
- [ ] 1.2 Extract device identity (name, package candidate list,
      core) from SVD + CMSIS-Pack PDSC when available.
- [ ] 1.3 Extract memory regions from SVD `<addressBlock>` and
      pack PDSC `<memory>` entries.
- [ ] 1.4 Extract peripheral instance list (name, base address,
      register file ref) from SVD `<peripheral>`.
- [ ] 1.5 Extract IRQ vector table from SVD `<interrupt>` nodes.
- [ ] 1.6 Mark clock-tree overrides + RCC bindings as
      `"// TODO review"` placeholders — the generator does not
      synthesise data it cannot prove.
- [ ] 1.7 Generator output is byte-deterministic given the same
      inputs.

## Phase 2: Diff tooling

- [ ] 2.1 `scripts/diff_device_patch.py` shows a structured diff
      between the generator output and an existing hand-curated
      patch.  Used to validate the generator on already-admitted
      devices.

## Phase 3: Validation against admitted devices

- [ ] 3.1 For each currently admitted device, run the generator
      and assert it reproduces ≥80% of the existing patch JSON
      (the rest being legitimate hand-curated overrides marked
      with `// TODO review` placeholders).
- [ ] 3.2 Document the residual 20% in
      `docs/autogen-device-patches.md` — what fields require
      manual review and why.

## Phase 4: Spec + final checks

- [ ] 4.1 Spec delta in `specs/vendor-admission/spec.md`.
- [ ] 4.2 `openspec validate autogen-device-patches-from-svd
      --strict` passes.
- [ ] 4.3 `pytest -q` + `ruff check` clean.
