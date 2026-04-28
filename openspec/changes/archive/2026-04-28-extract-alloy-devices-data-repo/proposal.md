# Extract `alloy-devices-yml` Data Repo

## Why

Once `define-canonical-device-yaml-schema` lands, every admitted
MCU has a stable text form.  The next architectural move is to
move the canonical data **out of the codegen repo** into a
dedicated `alloy-devices-yml` repository.

Why split:

- **Data scale.** Targeting 8000+ MCUs (ARM, AVR, PIC, RISC-V,
  Xtensa, MSP430, …) means ~1 GB of YAML.  That doesn't belong
  inside a Python codegen repo.
- **Multi-language consumers.** The same canonical data feeds
  the current C++ generator, a future Rust PAC generator, a
  future docs generator.  Each pulls a pinned tag of the data
  repo; they don't all need the extraction Python.
- **Contribution surface.** A community contributor adding one
  PIC18F variant edits one YAML file.  They don't need to
  understand the codegen pipeline, run pytest, or set up a
  Python venv.
- **CI cost.** Today every codegen change rebuilds the full
  device set from raw sources (SVD/ATDF/DTS).  After the split,
  codegen pulls a pinned data SHA — instantaneous.
- **Industry precedent.** modm-data → modm-devices → modm.
  Embassy stm32-data-gen → stm32-data → stm32-metapac.  Both
  proved this scales.

## What Changes

- Create new repository `alloy-devices-yml` (separate from
  alloy-codegen) containing:
  ```
  alloy-devices-yml/
    schema/                    (copied from this change's predecessor)
      canonical_device/*.json
    vendors/<vendor>/
      vendor.yml
      <family>/
        family.yml
        devices/<device>.yml   (one per admitted MCU)
    index.yml                  (catalog: every triple + provenance)
    README.md
    CHANGELOG.md
  ```
- Initial population: every device the alloy-codegen pipeline
  admits today (17 devices) emits its canonical YAML once
  (using the emitter from
  `define-canonical-device-yaml-schema`) and that output is
  committed to `alloy-devices-yml` as the bootstrap snapshot.
- alloy-codegen gains a git submodule pointing at
  `alloy-devices-yml` at a pinned SHA, exposed via
  `data/devices/` (consistent with the existing
  `data/known_devices.toml` / `data/peripheral_traits/` pattern).
- New consumer module
  `src/alloy_codegen/sources/alloy_devices_yml.py` reads the
  YAML files instead of consulting raw vendor sources directly.
  Pipeline stages (`fetch`, `normalize`) flip to this consumer
  for any device whose YAML exists in the data repo.
- Backwards-compat: families that still live as raw
  SVD+patches keep working through the existing adapters.  The
  YAML-source consumer is **additive**; it short-circuits
  normalize when the YAML is present.
- A bump tool `tools/bump_devices_yml.py` updates the submodule
  pin, runs the round-trip + smoke-compile gates, and reports
  any regressions.
- Documentation `docs/alloy-devices-yml.md` covers the consumer
  workflow + the contributor workflow (how to add a new MCU
  by committing a YAML to the data repo).

## Impact

After this lands, alloy-codegen is no longer the source of
truth for device data — `alloy-devices-yml` is.  Codegen
becomes a pure consumer.  Future Rust PAC / Zig / docs
generators slot in alongside as siblings.

The migration of *existing* per-vendor patches into the YAML
form is incremental: each family flips when its YAML emission
is verified against the existing pipeline output.

## What this DOES NOT do

- Does not delete the existing patches/ tree.  Patches stay
  during the transition; the YAML emission is parallel until
  every consumer flips.
- Does not bulk-import 8000 MCUs.  This change only extracts
  the 17 currently-admitted devices.  Bulk admission is
  `add-alloy-data-extractor-repo` + `bulk-admit-from-alloy-devices-yml`.
- Does not change the C++ output.  Every emitted artifact for
  the 17 admitted devices stays byte-identical; the YAML is
  just an intermediate form.
- Does not introduce a third Python package.  alloy-codegen
  still owns the C++ emitters; the data repo is data-only
  (no Python).
