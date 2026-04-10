# alloy-codegen

`alloy-codegen` is the source-of-truth pipeline for turning upstream device descriptions
into validated canonical hardware metadata and generated artifacts for the Alloy ecosystem.

The repository starts from a clean architecture:

1. `fetch`
2. `patch`
3. `normalize`
4. `validate`
5. `emit`
6. `publish`

The canonical IR sits at the center of the system. Emitters consume validated IR; they do
not recover missing semantics from raw vendor data.

## Bootstrap Scope

The first implementation wave is intentionally narrow:

- Vendor: `st`
- Family: `stm32g0`

This repository should reach deterministic single-family quality before adding more
families.

## Current Bootstrap

The repository now has:

- stage-oriented CLI
- explicit patch descriptors under `patches/`
- a real `cmsis-svd-data` source adapter for the STM32G0 bootstrap family
- canonical IR bootstrap flow backed by SVD discovery plus patch metadata

You can point the fetch stage at an existing local `cmsis-svd-data` checkout:

```bash
alloy-codegen fetch --family stm32g0 --source cmsis-svd-data=/path/to/cmsis-svd-data --json
```
