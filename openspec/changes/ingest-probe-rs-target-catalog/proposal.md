# Ingest probe-rs Target Catalog as Known-Devices Index

## Why

The repo has no canonical answer to "what MCUs exist?".  When we
admit a new family, we hand-pick a couple of devices and write
patches for them — there's no inventory we can pull from.

`probe-rs/probe-rs/targets/*.yaml` is a community-maintained
catalog of ~5,000 chip variants with normalized identity strings
(vendor, family, part number, core), memory map, and flash-algo
references.  Apache-2.0/MIT licensed, machine-readable YAML.
Importing it gives us an authoritative "known-devices" index that
the autogen-device-patches generator and admission flows can
consult.

## What Changes

- New importer `tools/import_probe_rs_targets.py` that clones (or
  syncs an existing checkout of) `probe-rs/probe-rs`, parses
  `targets/*.yaml`, and emits a single
  `data/known_devices.toml` table indexed by canonical
  `(vendor, family, device)`.
- Each entry records: probe-rs target name, core, memory regions,
  flash algorithm reference, source pack reference.
- A guard test asserts that every device the alloy pipeline
  currently admits resolves to a known-devices entry — catches
  identity drift between our patches and the canonical catalog.
- The importer is idempotent and pinned to a specific probe-rs
  commit SHA, recorded in `data/known_devices.meta.toml`.
- This is a **read-only catalog**, not a source of truth that
  overrides patches.  Patches still win on conflict; the catalog
  is for discoverability and admission scaffolding.

## Impact

Admission flow knows which MCUs exist before someone writes a
patch.  Pairs with `autogen-device-patches-from-svd` to enable
batch admission ("here are the 47 STM32G0 variants we don't
admit yet — generate drafts for all of them").  Foundation for a
future "admit-by-default-from-catalog" UX where most MCUs come
in for free.
