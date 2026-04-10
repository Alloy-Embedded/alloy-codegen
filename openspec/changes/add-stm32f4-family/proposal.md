## Why

The pipeline is hardcoded to a single bootstrap family (`stm32g0`). Gate E.6 of
`add-codegen-platform-foundation` requires a second major family to enter active
implementation only after E.1–E.5 pass. All five gates are now closed. This proposal
generalises the architecture to support multiple vendor/family pairs and adds `stm32f4`
as the second supported family using two representative devices.

## What Changes

- **`bootstrap.py`**: Replace single-family constants with a multi-family device registry
  mapping `(vendor, family)` → device names; keep `BOOTSTRAP_VENDOR/FAMILY` as the primary
  family reference for backwards-compatible defaults
- **`scope.py`**: `validate_supported()` and `resolved_device_names()` look up the registry
  instead of comparing against hardcoded bootstrap constants
- **`patches.py`**: `family_patch_file_path()` and `patch_file_path()` accept explicit
  `vendor`/`family` arguments derived from the resolved scope instead of using module-level
  constants
- **`normalize.py`** / **`emit.py`**: forward resolved `vendor`/`family` from scope to patch
  and emit helpers
- **New patch data**: `patches/st/stm32f4/family.json` + device overlays for `stm32f401re`
  and `stm32f405rg`
- **New fixtures**: minimal SVD + MCU XML + canonical JSON + emitted artifacts for both F4
  devices
- **New tests**: parametric normalize/emit/validate tests covering F4 devices; cross-family
  regression guard

## Impact

- Affected specs: `source-ingestion`, `patch-and-normalization`
- Affected code: `bootstrap.py`, `scope.py`, `patches.py`, `normalize.py`, `emit.py`
- **BREAKING** (internal only): `family_patch_file_path()` and `patch_file_path()` gain
  required `vendor` / `family` keyword parameters — callers inside the repo are updated as
  part of this change; no public API is exposed
- Artifact layout and publication contract are unchanged
- Canonical IR schema version is unchanged (no new IR fields)
