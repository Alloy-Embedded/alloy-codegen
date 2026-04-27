# Tasks — extract-alloy-devices-data-repo

## Phase 1: Repo bootstrap (out-of-tree)

- [ ] 1.1 Create new GitHub repo `alloy-devices-yml` under the
      same organization.
- [ ] 1.2 Bootstrap with: `README.md`, `CHANGELOG.md`,
      `LICENSE` (MIT, matching alloy-codegen),
      `.github/workflows/ci.yml` (schema-validates every
      committed YAML).
- [ ] 1.3 Copy `schema/canonical_device/*.json` from
      alloy-codegen as the source of truth for validation.

## Phase 2: Initial population

- [ ] 2.1 Run alloy-codegen against every admitted device,
      capture the per-device canonical YAML output (from
      `define-canonical-device-yaml-schema`).
- [ ] 2.2 Commit the 17 YAMLs to `alloy-devices-yml/vendors/...`
      respecting the layout in the proposal.
- [ ] 2.3 Build `alloy-devices-yml/index.yml` listing every
      triple + provenance + content hash.

## Phase 3: alloy-codegen submodule wiring

- [ ] 3.1 Add `alloy-devices-yml` as a git submodule at
      `data/devices/` in alloy-codegen.
- [ ] 3.2 Pin to the bootstrap SHA from Phase 2.
- [ ] 3.3 CI clones submodules (`actions/checkout` with
      `submodules: recursive`).

## Phase 4: Consumer module

- [ ] 4.1 New `src/alloy_codegen/sources/alloy_devices_yml.py`:
      - `resolve_device_yaml(vendor, family, device) -> Path`
        looks up the YAML in the submodule.
      - `load_canonical_device(yaml_path) -> CanonicalDeviceIR`
        parses and validates it.
- [ ] 4.2 Wire into `stages/normalize.py` as a short-circuit:
      when the device YAML exists in the submodule and is
      schema-valid, skip the legacy SVD + patch path and
      return the parsed IR directly.
- [ ] 4.3 Fall-through to legacy path when the YAML is absent
      (back-compat for any device added before its YAML
      lands).

## Phase 5: Bump tooling

- [ ] 5.1 `tools/bump_devices_yml.py`:
      - Updates the submodule to a target SHA.
      - Reruns `pytest -q` + `pytest --runtime-cpp-smoke`.
      - Diffs the resolved IRs (before vs. after).
      - Reports per-device any drift.
- [ ] 5.2 The tool refuses to update if drift exceeds
      thresholds (configurable; default: any C++ artifact
      changes require explicit review).

## Phase 6: Tests + docs

- [ ] 6.1 Pipeline parity test: for every admitted device,
      assert that the YAML-sourced IR produces emitted
      artifacts byte-identical to the legacy-sourced IR.
- [ ] 6.2 `docs/alloy-devices-yml.md` covers consumer +
      contributor workflows.
- [ ] 6.3 `docs/contributing.md` updated to point new-MCU
      contributors at alloy-devices-yml first.

## Phase 7: Spec + final checks

- [ ] 7.1 Spec delta in `specs/vendor-admission/spec.md`.
- [ ] 7.2 `openspec validate extract-alloy-devices-data-repo
      --strict` passes.
- [ ] 7.3 `pytest -q` + `ruff check` clean.
- [ ] 7.4 `--runtime-cpp-smoke` green for every admitted
      device on both code paths (legacy + YAML).
