## Why

The current generated `system_clock.hpp` contract is only half-finished outside ST.

- `stm32g0` and `stm32f4` already emit real bring-up algorithms.
- `same70` and `imxrt1060` still publish profile metadata without executable device-scoped
  clock programming.

That leaves a hole in the startup story: Alloy can import typed startup and clock contracts, but
non-ST foundational families still force handwritten or implicit bring-up knowledge.

## What Changes

- extend typed `system_clock_profiles` with the numeric knobs needed by non-ST foundational clock
  algorithms
- publish executable SAME70 system-clock profiles, including internal RC, external crystal, and
  PLLA-based profiles
- publish executable IMXRT1060 system-clock profiles, including safe direct crystal and default
  ARM PLL performance bring-up
- require runtime-lite publication to include the PMC/EFC register closure needed by the emitted
  SAME70 clock helpers and the `CCM/CCM_ANALOG/DCDC` closure needed by IMXRT1060
- tighten publication gates so foundational families cannot ship metadata-only system-clock
  profiles when an executable algorithm is expected

## Impact

- foundational startup moves closer to fully generated bring-up instead of handwritten board code
- Alloy gets an executable SAME70 clock contract instead of a placeholder metadata header
- Alloy gets an executable IMXRT1060 clock contract instead of a placeholder 24 MHz metadata-only
  header
- the system-clock profile model becomes capable of expressing richer profile families without
  pushing board policy back into Alloy
