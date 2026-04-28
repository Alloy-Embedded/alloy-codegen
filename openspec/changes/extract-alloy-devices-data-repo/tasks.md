# Tasks — extract-alloy-devices-data-repo

## Phase 1: Repo bootstrap (out-of-tree)

- [x] 1.1 Created GitHub repo `Alloy-Embedded/alloy-devices-yml`.
- [x] 1.2 Bootstrap content: `README.md`, `CHANGELOG.md`,
      `LICENSE` (MIT), `.github/workflows/ci.yml` schema-validates
      every committed YAML.
- [x] 1.3 Schemas at `schema/canonical_device/{device,family,vendor}.schema.json`
      copied from alloy-codegen.

## Phase 2: Initial population

- [x] 2.1 Generated canonical YAML for every admitted device via
      `serialize_device(...)` and committed under
      `vendors/<vendor>/<family>/devices/<device>.yml`.  17
      devices, sizes 17 KB → 7 MB.
- [x] 2.2 First push pinned at `40f7437` after seeding all
      device YAMLs.

## Phase 3: alloy-codegen submodule wiring

- [x] 3.1 Added as git submodule at `data/devices/`.
      `.gitmodules` records the URL.
- [x] 3.2 Pinned at `40f7437`.
- [ ] 3.3 CI clones submodules — add `submodules: recursive`
      to `actions/checkout@v6` step in
      `.github/workflows/bootstrap-family.yml` (one-line edit
      to land alongside this commit).

## Phase 4: Consumer module

- [x] 4.1 `src/alloy_codegen/sources/alloy_devices_yml.py`:
      `device_yaml_path`, `resolve_device_yaml`, `is_available`,
      `load_canonical_device` (schema-validates by default),
      `submodule_revision` (parses `.git` file pointer to read
      pinned SHA).
- [x] 4.2 Short-circuit wired into `stages/normalize.py`: when
      `is_available()` returns True, parse YAML directly and
      append to `devices`; otherwise fall through to the
      registry-resolved adapter.
- [x] 4.3 Fetch stage also short-circuits — synthesises an
      `alloy-devices-yml` source record per YAML-admitted
      device so the source manifest carries provenance even
      when no upstream vendor adapter is invoked.

## Phase 5: Bump tooling

- [x] 5.1 `tools/bump_devices_yml.py` accepts `--sha` /
      `--allow-drift`, captures pre-bump YAML snapshot, fetches
      + checks out the new pin, captures post-bump snapshot,
      reports per-device line drift, exits non-zero unless
      drift is allowed.

## Phase 6: Tests + docs

- [x] 6.1 `tests/test_alloy_devices_yml_consumer.py` (23 tests):
      data-repo root resolves, every admitted triple has a
      YAML, submodule revision parses, load_canonical_device
      returns a valid IR, normalize short-circuits through
      YAML without source overrides, fetch synthesises
      alloy-devices-yml records.  All pass.
- [ ] 6.2 `docs/alloy-devices-yml.md` consumer + contributor
      workflow — deferred to a follow-up tightening change
      because the README in alloy-devices-yml itself already
      covers contributor flow; codegen-side doc is a one-page
      pointer.

## Phase 7: Spec + final checks

- [x] 7.1 Spec delta in `specs/vendor-admission/spec.md`.
- [x] 7.2 `openspec validate extract-alloy-devices-data-repo
      --strict` passes.
- [x] 7.3 Smoke verification: all 17 admitted devices normalize
      successfully via the YAML short-circuit (no source
      overrides supplied).  ESP32 / SAME70 are slow (10-25s)
      because of repeated schema validation on multi-MB YAMLs;
      a follow-up change can cache.
- [ ] 7.4 Full pytest + runtime-cpp-smoke gate — focused tests
      pass; full-suite goldens regen is a separate cleanup
      change because the new YAML emitter adds artifacts to
      every emit run that goldens were not authored to expect.
