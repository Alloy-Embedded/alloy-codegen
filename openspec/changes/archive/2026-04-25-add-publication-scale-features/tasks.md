# Tasks — add-publication-scale-features

## Phase 1: README emitter

- [x] 1.1 Create `src/alloy_codegen/runtime_readme.py` with
      `emit_devices_readme(execution_context) -> EmittedArtifact` rendering the
      three-section markdown (header + admitted families table + coverage
      caveats) from `DEVICE_REGISTRY`, family.json, and device.json
- [x] 1.2 Extend `patches.py` to parse the optional
      `family.json::__source_notes::__readme_caveat` field into the
      `FamilyPatchCatalog` (or a sibling structure surfacing only to the
      emitter); fields without the key are dropped from the caveats section
- [x] 1.3 Wire `emit_devices_readme()` into `stages/publish.py` so the artifact
      list returned by `run_publish` includes `EmittedArtifact(path="README.md",
      artifact_kind="documentation", ...)` at the publication root
- [x] 1.4 Add `tests/test_runtime_readme.py` covering:
      (a) every `(vendor, family)` from `DEVICE_REGISTRY` appears in the table
      (b) `__readme_caveat` from a family.json appears in the caveats section
      (c) families without `__readme_caveat` do NOT appear in caveats
      (d) idempotency: regenerating with the same inputs produces byte-identical output
- [x] 1.5 Add a `__readme_caveat` to each existing family.json that has known
      coverage limitations:
        - `espressif/esp32`: SVD coverage gap (UART1/2, SPI2/3, I2C1, TIMG1 only as DPORT bits)
        - `espressif/esp32s3`: dual-core control plane + bring_up_app_cpu();
          affinity routing delegated to esp-idf
        - `espressif/esp32c3`: PCR clock/reset registers patched manually
        - `microchip/avr-da`: Harvard memory layout; host-ld validation skipped
        - `raspberrypi/rp2040`: single-core perspective (core 1 not initialised)
        - Other families left without `__readme_caveat` if no current quirk applies

## Phase 2: CLI `affected-families`

- [x] 2.1 Create `src/alloy_codegen/affected_families.py` exposing
      `compute_affected(diff_paths: Iterable[str], registry: Mapping[(vendor, family), tuple[str, ...]]) -> AffectedSet`
      where `AffectedSet` carries `all_families: bool` and `families:
      tuple[tuple[str, str], ...]`
- [x] 2.2 Implement the path-mapping rules from design.md Decision 3 in priority
      order: per-family patch → per-source adapter → per-arch startup emitter →
      shared src catch-all → docs/openspec exclusion → workflow self-modify →
      conservative fallback
- [x] 2.3 Add a helper `compute_diff_paths(since: str, head: str = "HEAD") ->
      tuple[str, ...]` shelling out to `git diff --name-only <since>...<head>`
      with a graceful fallback (returns empty + signals "all" when the diff
      command fails)
- [x] 2.4 Add CLI subcommand `affected-families` in `src/alloy_codegen/cli.py`:
      `--since <ref>` (required), `--json` (default), `--plain` (alternative).
      JSON shape per design.md Decision 4
- [x] 2.5 Add `tests/test_affected_families.py` with synthetic diffs covering:
      single family patch, single source adapter, single startup emitter, mixed
      paths, docs-only, workflow self-modify, unknown path fallback

## Phase 3: Workflow integration

- [x] 3.1 Add `force_all` boolean input to the `workflow_dispatch` block of
      `.github/workflows/publish-alloy-devices.yml`
- [x] 3.2 Add a new `detect-affected` job (runs first):
        - Checks out alloy-codegen at the workflow head SHA
        - Resolves the "since" ref: `github.event.workflow_run.head_sha~1` for
          `workflow_run` triggers, `inputs.ref~1` for manual dispatch (or 'HEAD~1'
          when neither is meaningful)
        - When `inputs.force_all == 'true'`, skips detection and outputs the full
          matrix
        - Otherwise runs `python -m alloy_codegen.cli affected-families --since
          <ref> --json` and parses the result
        - Outputs: `matrix` (JSON for fromJson) and `should_publish` (string boolean)
- [x] 3.3 Convert the `publish` job to:
        - `needs: detect-affected`
        - `if: needs.detect-affected.outputs.should_publish == 'true'`
        - `strategy.matrix.include: ${{ fromJson(needs.detect-affected.outputs.matrix) }}`

## Phase 4: Spec deltas + alloy-codegen README

- [x] 4.1 Author `specs/artifact-contract/spec.md` delta adding the requirement
      "publication root carries an auto-generated `README.md` listing the
      admitted device matrix" with scenarios for table presence, caveat
      auto-extraction, and idempotent regeneration
- [x] 4.2 Author `specs/vendor-admission/spec.md` delta adding the requirement
      "publication CI computes affected families per push" with scenarios for
      single-family change, source-adapter change, runtime emitter change,
      docs-only change (skip everything), unknown-path fallback (run all),
      manual `force_all` override
- [x] 4.3 Update the alloy-codegen top-level `README.md` adding a "Published
      device matrix" section that links to `alloy-devices/README.md` and
      describes:
        - Auto-generation (regenerated every publish; do not edit manually)
        - How affected-families detection scopes the publish workflow
        - How to use `force_all` for cache invalidation

## Phase 5: Goldens + final checks

- [x] 5.1 Pin a sample of the generated README under
      `tests/fixtures/emitted/devices-readme/README.md` and add a regression
      test asserting `emit_devices_readme()` produces byte-equal output
- [x] 5.2 Run end-to-end publish locally for at least two vendors (ex.
      `espressif/esp32` and `microchip/avr-da`); inspect the resulting
      `README.md` manually and confirm the table renders well in the GitHub
      preview (use `gh markdown` or the GitHub web preview)
- [x] 5.3 Push a commit that touches **only** one family's patch; observe the
      Bootstrap CI → Publish chain on GitHub and confirm `detect-affected`
      yields a single-job matrix and the unrelated families' jobs are skipped
- [x] 5.4 Push a commit that touches `tests/**` only; confirm the Publish
      workflow short-circuits (`should_publish=false`) and no matrix runs
- [x] 5.5 Trigger `workflow_dispatch` with `force_all=true`; confirm the full
      matrix runs even when no diff would otherwise affect anything
- [x] 5.6 Run `openspec validate add-publication-scale-features --strict` and
      resolve any findings
