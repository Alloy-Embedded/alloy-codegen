# alloy-codegen

`alloy-codegen` is the source-of-truth pipeline for turning upstream device descriptions
into validated canonical hardware metadata and published `alloy-devices` artifacts for the
Alloy ecosystem.

The architecture is stage-oriented:

1. `fetch`
2. `patch`
3. `normalize`
4. `validate`
5. `emit`
6. `publish`

The canonical IR sits at the center of the system. Emitters consume validated IR; they do
not recover missing semantics from raw vendor data.

## Supported Targets

The repository currently supports these published families:

- `st/stm32g0`, `st/stm32f4`
- `microchip/same70`, `microchip/avr-da`
- `nxp/imxrt1060`
- `raspberrypi/rp2040`
- `espressif/esp32`, `espressif/esp32c3`, `espressif/esp32s3`

You can inspect the active support matrix directly from the CLI:

```bash
alloy-codegen targets
alloy-codegen targets --json
```

The default scope remains `st/stm32g0` when no `--vendor`, `--family`, or `--device` is
provided.

## Published Device Matrix

The `alloy-devices` repository carries a top-level `README.md` that lists every admitted
`(vendor, family)` pair plus its devices, packages, and peripherals.  This file is **auto-
generated** by `alloy-codegen` on every publish — do not edit it manually.  It reads
`DEVICE_REGISTRY` and the family/device patches and stays in sync without operator effort.

Each family can surface a one-line caveat in the auto-generated table by setting
`__source_notes.__readme_caveat` in its `family.json` (the field is optional; families
without it are simply omitted from the "Coverage caveats" section).

### Selective publish — affected-families detection

Once 9 families turns into 100+, re-publishing every family on every push is wasteful.
The publish workflow runs a `detect-affected` job that maps the git diff to the subset of
admitted families whose inputs the commit actually changed:

| Path pattern (first match wins) | Families published |
|---------------------------------|--------------------|
| `patches/<vendor>/<family>/**` | only that family |
| `src/alloy_codegen/sources/<adapter>.py` | families that consume that adapter |
| `src/alloy_codegen/runtime_xtensa_startup.py` | xtensa families |
| `src/alloy_codegen/runtime_riscv_startup.py` | RISC-V families |
| `src/alloy_codegen/runtime_avr_startup.py` | AVR families |
| `src/alloy_codegen/runtime_startup.py` | Cortex-M families |
| Other `src/alloy_codegen/**.py` | **all admitted families** (conservative) |
| `tests/**`, `openspec/**`, `*.md`, `bootstrap-family.yml` | **none** (publish is skipped entirely) |
| `publish-alloy-devices.yml`, `pyproject.toml`, `uv.lock` | **all admitted families** |
| Unknown / `git diff` failure | **all admitted families** (safe default) |

Inspect what the heuristic would publish for the current diff:

```bash
alloy-codegen affected-families --since HEAD~1 --plain
```

To force a full-matrix run (e.g. cache invalidation, security re-publish), trigger the
publish workflow via `gh workflow run` (or the Actions UI) with `force_all=true`.

## Quick Start

Install the project in editable mode:

```bash
python3 -m pip install -e .
```

Inspect supported targets:

```bash
alloy-codegen targets
```

Validate one existing family using local source overrides:

```bash
alloy-codegen validate \
  --vendor microchip \
  --family same70 \
  --source microchip-dfp-extract=/path/to/Microchip.SAME70_DFP.extract \
  --json
```

Publish one family into a local `alloy-devices` checkout:

```bash
alloy-codegen publish \
  --vendor st \
  --family stm32g0 \
  --source cmsis-svd-data=/path/to/cmsis-svd-data \
  --source stm32-open-pin-data=/path/to/stm32-open-pin-data \
  --publication-root /path/to/alloy-devices \
  --alloy-root /path/to/alloy \
  --json
```

## Source Overrides

Each family declares a logical source bundle in `src/alloy_codegen/bootstrap.py`. Source
paths can be provided either with repeated `--source SOURCE_ID=PATH` flags or with
environment variables of the form `ALLOY_CODEGEN_SOURCE_<SOURCE_ID>_ROOT`.

Examples:

- `cmsis-svd-data` -> `ALLOY_CODEGEN_SOURCE_CMSIS_SVD_DATA_ROOT`
- `stm32-open-pin-data` -> `ALLOY_CODEGEN_SOURCE_STM32_OPEN_PIN_DATA_ROOT`
- `microchip-dfp-pack` -> `ALLOY_CODEGEN_SOURCE_MICROCHIP_DFP_PACK_ROOT`
- `microchip-dfp-extract` -> `ALLOY_CODEGEN_SOURCE_MICROCHIP_DFP_EXTRACT_ROOT`
- `nxp-mcux-soc-svd` -> `ALLOY_CODEGEN_SOURCE_NXP_MCUX_SOC_SVD_ROOT`
- `nxp-mcux-sdk` -> `ALLOY_CODEGEN_SOURCE_NXP_MCUX_SDK_ROOT`

## Documentation

- [Artifact Layout](docs/artifact-layout.md)
- [Codegen and Alloy Boundary](docs/codegen-alloy-boundary.md)
- [Adding Support](docs/adding-support.md)

## Repository Responsibilities

- `src/alloy_codegen/bootstrap.py`: supported target registry and source bundles
- `src/alloy_codegen/sources/`: upstream source adapters
- `patches/<vendor>/<family>/`: curated family and device overlays
- `tests/fixtures/`: reproducible upstream snapshots and canonical fixtures
- `.github/workflows/publish-alloy-devices.yml`: remote publication matrix

## SAME70 Note

`microchip/same70` already participates in the same publish flow as the other families and
publishes runtime-lite artifacts under `generated/runtime/` plus
`generated/runtime/devices/<device>/driver_semantics/`. If local publication fails while
trying to download the Microchip pack, prefer a `microchip-dfp-extract` override first; the
CI workflow publishes from a clean environment with working TLS roots.
