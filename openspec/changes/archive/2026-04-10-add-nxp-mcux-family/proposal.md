## Why

The latest public market snapshot I found, published on April 7, 2026 and based on Omdia's
2025 estimates, puts the leading MCU vendors in this order: Infineon, NXP, Renesas, ST, and
Microchip. If Alloy wants broad public reach while keeping ST and Microchip in scope, NXP is
the largest missing vendor to add next.

NXP is also a better architectural fit than it might look at first. It does not appear to
publish a standalone open pin-data repository equivalent to `STM32_open_pin_data`, but it does
publish two strong official structured sources:

- `mcux-soc-svd` for SVD delivery
- `mcux-sdk` for device SDK content, including device-level pinmux headers such as
  `fsl_iomuxc.h` on i.MX RT families

That means the right Alloy move is not to wait for a perfect "pin repo". It is to support a
second structured source pattern: families whose pin-function metadata is delivered in SDK
headers rather than a dedicated XML repository.

This proposal adds NXP as a first-class vendor through the `imxrt1060` family using
`mcux-soc-svd + mcux-sdk`.

## What Changes

- **NEW** NXP vendor namespace in the device registry using `nxp` as the canonical vendor key
- **NEW** `imxrt1060` as the first NXP family, with two representative devices from the same
  family
- **NEW** source-bundle support for NXP official repositories:
  `nxp-mcux-soc-svd` and `nxp-mcux-sdk`
- **NEW** header-derived pin-function normalization path for SDK-delivered sources such as
  `fsl_iomuxc.h`
- **NEW** family patch catalog and device overlays for `nxp/imxrt1060`
- **NEW** validation gates for SDK-backed pinmux sources where connectivity comes from structured
  headers rather than dedicated XML pin databases
- **NEW** publication target for `nxp/imxrt1060` artifacts in `alloy-devices`
- **NON-GOAL** choosing a generic NXP vendor path for every product line in one proposal; this
  change is limited to the `imxrt1060` family
- **NON-GOAL** depending on MCUXpresso Config Tools internal databases as the primary source of
  truth

## Impact

- Affected specs:
  - `source-ingestion`
  - `patch-and-normalization`
  - `canonical-device-ir`
  - `validation-and-gates`
- Affected code:
  - device registry and family source-bundle registration
  - source adapters and manifests for NXP repositories
  - header parsers for SDK-delivered pinmux metadata
  - family/device patch catalogs and fixtures for NXP
  - validation and publication coverage for `nxp/imxrt1060`
- No artifact layout change is required; this extends the supported vendor/family matrix
