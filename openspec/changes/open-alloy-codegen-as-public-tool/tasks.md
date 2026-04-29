# Tasks — open-alloy-codegen-as-public-tool

## Phase 1: PyPI publication

- [ ] 1.1 `pyproject.toml` `[project.scripts]` entry exposing
      `alloy-codegen = "alloy_codegen.cli:main"` so
      `pip install alloy-codegen && alloy-codegen --version`
      works out of the box.
- [ ] 1.2 Wire `--version` flag in `cli.py` returning a
      string matching `IR_SCHEMA_VERSION`.
- [ ] 1.3 GitHub Actions workflow `release.yml` that publishes
      to PyPI on tagged commits (`v<semver>`); test-PyPI
      mirror for dry-run.
- [ ] 1.4 First public release `v0.1.0` matching
      `IR_SCHEMA_VERSION = "1.2.0"` (or the latest pinned).

## Phase 2: CONTRIBUTING_DEVICES.md walkthrough

- [ ] 2.1 Top-level `CONTRIBUTING_DEVICES.md` covering the
      end-to-end flow from "I want to add a new chip" to
      "PR open in alloy-codegen + alloy-devices-yml".
- [ ] 2.2 Section: sourcing vendor data
      (CMSIS-SVD repos, Microchip DFP, ESP-IDF headers, Zephyr
      DTS, vendor MCU XML).
- [ ] 2.3 Section: running alloy-data-extractor to produce
      the canonical YAML; what the YAML must contain to pass
      schema validation.
- [ ] 2.4 Section: running `alloy-codegen generate` against
      the YAML to produce artifacts; running
      `alloy-codegen validate` to confirm contracts pass.
- [ ] 2.5 Section: opening the PR — file locations, golden
      regen, smoke compile expectation, review checklist.

## Phase 3: Overlay schema reference

- [ ] 3.1 `docs/overlay-schema.md` documenting every patchable
      IR field with type, default, example, and the source
      data it usually comes from (SVD / ATDF / DTS / MCU XML).
- [ ] 3.2 Cross-link to the canonical
      `data/devices/schema/canonical_device/device.schema.json`.
- [ ] 3.3 Worked example: walk through patching an STM32G0
      DMA request mapping not present in the upstream SVD.

## Phase 4: CLI consolidation

- [ ] 4.1 Refactor `src/alloy_codegen/cli.py` into a single
      `alloy-codegen <subcommand>` front door with three
      subcommands: `generate`, `validate`, `doctor`.
- [ ] 4.2 `generate` subcommand: accepts `--device <name>` or
      `--family <vendor/family>` or `--all`; runs the full
      pipeline; emits artifacts to a configurable output
      directory.
- [ ] 4.3 `validate` subcommand: runs the artifact contract
      + golden gates against existing artifacts; useful for
      "is my candidate-device YAML good enough to admit?".
- [ ] 4.4 `doctor` subcommand: prints schema version,
      installed CLI version, admitted-device count, missing
      goldens, anything else useful for debugging
      installation.
- [ ] 4.5 Each subcommand has `--help` text covering every
      flag with one-line descriptions; help text is the
      first thing a contributor sees.

## Phase 5: Spec + final checks

- [ ] 5.1 MODIFIED `codegen-alloy-boundary` requirement
      defining the public-tool admission criteria.
- [ ] 5.2 `openspec validate
      open-alloy-codegen-as-public-tool --strict` passes.
- [ ] 5.3 `pip install -e .` followed by
      `alloy-codegen --version` works from a fresh clone.
- [ ] 5.4 First contributor walkthrough timed: a new
      contributor reaches "first device YAML committed and
      passing alloy-codegen validate" in under 30 minutes
      following only `CONTRIBUTING_DEVICES.md`.
