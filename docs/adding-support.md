# Adding Support

This document describes the real onboarding path for `alloy-codegen` today.

Use it when you need to:

- add a new device to an existing family
- add a new family under an existing vendor
- add a new vendor

The short rule is:

- upstream adapters ingest raw facts
- patches curate missing structure and naming
- normalization builds canonical IR
- validation proves publishability
- emission and publication must succeed without Alloy-side handwritten exceptions

## Start Here

Inspect the current support matrix first:

```bash
alloy-codegen targets
```

The active registry lives in [bootstrap.py](../src/alloy_codegen/bootstrap.py).

The most important entries are:

- `DEVICE_REGISTRY`: supported devices for each `vendor/family`
- `SOURCE_BUNDLES`: logical upstream source ids required for that family
- `BOOTSTRAP_VENDOR` and `BOOTSTRAP_FAMILY`: default scope when no target is specified

## Mental Model

Adding support is not just "make fetch work".

A family is only really integrated when all of this is true:

1. `fetch` can resolve reproducible upstream records for every device in scope.
2. `patch` can load a family catalog plus device overlays.
3. `normalize` can build canonical IR without family-specific handwritten tables in Alloy.
4. `validate` passes with no draft descriptor domains.
5. `emit` produces both reflection artifacts and runtime-lite artifacts.
6. `publish` passes the runtime-lite smoke consumer and the full Alloy smoke consumer.

If any of those fail, the family is not done yet.

## Adding a Device to an Existing Family

This is the cheapest path. You should prefer it when the vendor/family source adapter
already exists.

1. Add the device name to `DEVICE_REGISTRY` in [bootstrap.py](../src/alloy_codegen/bootstrap.py).
2. Add the device patch file under `patches/<vendor>/<family>/devices/<device>.json`.
3. Reuse or extend the family patch catalog in `patches/<vendor>/<family>/family.json`.
4. Confirm the family source adapter can resolve the raw device files.
5. Add or refresh canonical fixtures under `tests/fixtures/<family>/`.
6. Run `validate` for the single device first, then the full family.
7. Run `publish` for the full family before merging.

What usually changes:

- package and bonded-pin data
- memory regions
- peripheral list and IP versions
- pin signals and mux selectors
- clock/reset bindings
- DMA bindings

What should not change:

- Alloy runtime code to special-case the new device

If the new device needs new handwritten logic inside Alloy, the contract is probably still
missing something in the generator or patch model.

## Adding a New Family Under an Existing Vendor

This is more expensive because you usually need both a new patch catalog and new source
resolution rules.

1. Register the family and devices in [bootstrap.py](../src/alloy_codegen/bootstrap.py).
2. Declare the family source bundle in `SOURCE_BUNDLES`.
3. Extend or add the upstream adapter in `src/alloy_codegen/sources/`.
4. Wire the fetch dispatch in [fetch.py](../src/alloy_codegen/stages/fetch.py).
5. Create `patches/<vendor>/<family>/family.json`.
6. Create `patches/<vendor>/<family>/devices/<device>.json` for every supported device.
7. Add reproducible source fixtures in `tests/fixtures/`.
8. Add or refresh canonical IR fixtures.
9. Run `validate`, `emit`, and `publish` for the family.
10. Add the family to the publication workflow matrix if it is ready to publish.

Use an existing family as the template:

- `patches/st/stm32g0/`
- `patches/microchip/same70/`
- `patches/nxp/imxrt1060/`

Choose the closest existing vendor adapter before inventing a new ingestion path.

## Adding a New Vendor

Do this only when the raw upstream format is materially different from what already exists.

Minimum changes:

1. Add a new adapter under `src/alloy_codegen/sources/`.
2. Teach [fetch.py](../src/alloy_codegen/stages/fetch.py) how to dispatch that vendor/family.
3. Register devices and source bundles in [bootstrap.py](../src/alloy_codegen/bootstrap.py).
4. Add patches under `patches/<vendor>/<family>/`.
5. Add fixtures and tests for the new source adapter.
6. Prove the runtime-lite contract emits correctly for at least one family.
7. Add the family to `.github/workflows/publish-alloy-devices.yml` only after publish is stable.

If the family is meant to count toward vendor admission, also update
[vendor_admission.py](../src/alloy_codegen/vendor_admission.py).

## Required Files by Responsibility

Support registry:

- [bootstrap.py](../src/alloy_codegen/bootstrap.py)

Scope resolution:

- [scope.py](../src/alloy_codegen/scope.py)

Source ingestion:

- `src/alloy_codegen/sources/*.py`
- [fetch.py](../src/alloy_codegen/stages/fetch.py)

Curated overlays:

- `patches/<vendor>/<family>/family.json`
- `patches/<vendor>/<family>/devices/<device>.json`
- [patches.py](../src/alloy_codegen/patches.py)

Runtime-lite emission and publication gates:

- [runtime_lite_emission.py](../src/alloy_codegen/runtime_lite_emission.py)
- [artifact_contract.py](../src/alloy_codegen/artifact_contract.py)
- [publish.py](../src/alloy_codegen/stages/publish.py)

Release automation:

- [publish-alloy-devices.yml](../.github/workflows/publish-alloy-devices.yml)

## Source Override Rules

Logical source ids come from `SOURCE_BUNDLES`.

You can provide them with either:

- `--source SOURCE_ID=PATH`
- `ALLOY_CODEGEN_SOURCE_<SOURCE_ID>_ROOT`

The environment variable name is uppercase and replaces non-alphanumeric characters with
underscores.

Examples:

- `cmsis-svd-data` -> `ALLOY_CODEGEN_SOURCE_CMSIS_SVD_DATA_ROOT`
- `microchip-dfp-extract` -> `ALLOY_CODEGEN_SOURCE_MICROCHIP_DFP_EXTRACT_ROOT`
- `nxp-mcux-sdk` -> `ALLOY_CODEGEN_SOURCE_NXP_MCUX_SDK_ROOT`

## Validation Checklist

Before calling a target "supported", check these outputs:

1. `reports/validation-summary.json` says `is_passing: true`.
2. `reports/coverage.json` says `all_devices_publishable: true`.
3. `generated/runtime/types.hpp` exists.
4. `generated/runtime/devices/<device>/routes.hpp` exists.
5. `generated/runtime/devices/<device>/driver_semantics/{gpio,uart,i2c,spi}.hpp` exist when relevant.
6. `reports/publication-record.json` exists after `publish`.
7. The runtime-lite smoke consumer and the full Alloy smoke consumer both succeed.

If a family passes validation but does not emit `generated/runtime/.../driver_semantics/*`,
it is not ready for zero-overhead foundational drivers yet.

## SAME70-Specific Note

`microchip/same70` is already in the publication workflow matrix and already emits runtime-lite
artifacts, including:

- `generated/runtime/types.hpp`
- `generated/runtime/devices/<device>/clock_bindings.hpp`
- `generated/runtime/devices/<device>/routes.hpp`
- `generated/runtime/devices/<device>/driver_semantics/common.hpp`
- `generated/runtime/devices/<device>/driver_semantics/gpio.hpp`
- `generated/runtime/devices/<device>/driver_semantics/uart.hpp`
- `generated/runtime/devices/<device>/driver_semantics/i2c.hpp`
- `generated/runtime/devices/<device>/driver_semantics/spi.hpp`

For local work, prefer this validation command:

```bash
alloy-codegen publish \
  --vendor microchip \
  --family same70 \
  --source microchip-dfp-extract=/path/to/Microchip.SAME70_DFP.extract \
  --publication-root /tmp/alloy-devices-publish \
  --alloy-root /path/to/alloy \
  --json
```

That avoids depending on a local TLS/certificate setup just to download the DFP archive.
