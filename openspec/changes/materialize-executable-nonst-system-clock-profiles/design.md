## Overview

This change finishes the foundational non-ST executable system-clock path.

The first cut focused on SAME70 because:

- Alloy already has a foundational SAME70 board path
- the device family needs explicit `PMC` sequencing
- the current published profile set is metadata-only despite being foundational

The second cut closes the remaining foundational gap for `imxrt1060`, which still publishes only
metadata-level 24 MHz profiles despite depending on explicit `CCM/CCM_ANALOG/DCDC` sequencing for
performance bring-up.

The design also expands the typed profile model with a small set of extra numeric knobs so later
families do not need to overload unrelated fields.

## Typed Profile Extensions

`system_clock_profiles` gain optional typed fields:

- `oscillator_startup_cycles`
- `mck_prescaler`
- `cpu_prescaler`
- `ipg_prescaler`

These remain device-scoped numeric facts. They are not free-form payloads.

The intent is:

- `oscillator_startup_cycles`: vendor startup/stabilization count when the register contract uses
  one
- `mck_prescaler`: SAME70 master-clock prescaler divisor
- `cpu_prescaler`: CPU/core divider for families that separate core from bus clocks
- `ipg_prescaler`: low-speed peripheral divider for families that publish it directly

## SAME70 Bring-Up Contract

### Published profiles

Foundational SAME70 devices publish executable profiles for:

- safe internal RC at 12 MHz
- external crystal direct at 12 MHz
- PLLA performance profile from 12 MHz crystal to 150 MHz MCK

The default profile may remain conservative if board policy requires it, but the generated
contract must include the performance profile so Alloy no longer needs handwritten PLLA logic.

### Runtime-lite closure

The runtime-lite register/field closure must include the SAME70 clock facts used by the system
clock helper:

- `PMC.CKGR_MOR`
- `PMC.CKGR_PLLAR`
- `PMC.MCKR`
- `PMC.SR`
- `EFC.EEFC_FMR`

And the corresponding fields:

- `MOSCXTEN`, `MOSCRCEN`, `MOSCRCF`, `MOSCXTST`, `KEY`, `MOSCSEL`
- `DIVA`, `PLLACOUNT`, `MULA`, `ONE`
- `CSS`, `PRES`, `MDIV`
- `MOSCXTS`, `LOCKA`, `MCKRDY`, `MOSCSELS`, `MOSCRCS`
- `FWS`

### Emitted algorithm

The generated helper in `generated/runtime/devices/<device>/system_clock.hpp` must:

1. program `CKGR_MOR` with the required key on each write
2. wait for oscillator-ready status when switching RC/crystal source
3. program `EEFC_FMR.FWS` before entering high-frequency PLLA mode
4. program `CKGR_PLLAR` and wait for `LOCKA`
5. switch `MCKR` in the safe sequence required by the PMC:
   - CSS to `MAIN_CLK`
   - wait `MCKRDY`
   - PRES update
   - wait `MCKRDY`
   - final CSS
   - wait `MCKRDY`

## Validation and Gates

Publication must fail when foundational SAME70 devices:

- publish `system_clock_profiles` but emit only the generic metadata-only fallback body
- omit the PMC/EFC runtime-lite register closure needed by the generated helper
- publish a PLLA profile without the typed parameters required by the emitter

## IMXRT1060 Bring-Up Contract

### Published profiles

Foundational IMXRT1060 devices must publish:

- a safe 24 MHz direct crystal profile
- a default ARM PLL performance profile at 600 MHz core / 150 MHz IPG

The profile contract stays typed:

- `source_kind=external-oscillator` for the direct crystal path
- `source_kind=pll-external` for the ARM PLL path
- `cpu_prescaler`, `ahb_prescaler`, `ipg_prescaler`, and `pll_n` provide the numeric knobs needed
  by the emitted helper

### Runtime-lite closure

The runtime-lite register/field closure must include the IMXRT1060 facts used by the helper:

- `CCM.CACRR`
- `CCM.CBCDR`
- `CCM.CBCMR`
- `CCM.CDHIPR`
- `CCM_ANALOG.PLL_ARM`
- `DCDC.REG0`
- `DCDC.REG3`

And the corresponding fields:

- `ARM_PODF`
- `PERIPH_CLK2_PODF`, `PERIPH_CLK_SEL`, `IPG_PODF`, `AHB_PODF`
- `PERIPH_CLK2_SEL`, `PRE_PERIPH_CLK_SEL`
- `ARM_PODF_BUSY`, `PERIPH_CLK_SEL_BUSY`, `PERIPH2_CLK_SEL_BUSY`, `AHB_PODF_BUSY`
- `DIV_SELECT`, `POWERDOWN`, `ENABLE`, `BYPASS`, `LOCK`
- `STS_DC_OK`, `TRG`

### Emitted algorithm

The generated helper in `generated/runtime/devices/<device>/system_clock.hpp` must:

1. move the system temporarily to `PERIPH_CLK2` sourced from the 24 MHz crystal
2. raise `DCDC` target voltage before high-frequency ARM PLL operation
3. program `CCM_ANALOG.PLL_ARM` and wait for `LOCK`
4. program `CACRR/CBCDR` prescalers with the required handshake waits
5. select `PRE_PERIPH_CLK_SEL=PLL1` and switch `PERIPH_CLK_SEL` back to the performance path

Publication must fail when foundational IMXRT1060 devices emit only the generic metadata fallback.
