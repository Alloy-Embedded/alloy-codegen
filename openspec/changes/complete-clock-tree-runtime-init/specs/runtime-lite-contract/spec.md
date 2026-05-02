## ADDED Requirements

### Requirement: Runtime-Lite Contract SHALL Emit A Self-Contained Body Per `clock.profile`

The runtime-lite contract SHALL emit a complete, self-contained C
function `alloy_clock_enter_<profile_id>(void)` for every entry in
`device.clock.profiles`, with a body that programs the device's
clock fabric to match the profile's declared `sysclk_source`,
`hclk_hz`, and `pclk_hz` (and, where applicable, PLL coefficients
and FLASH wait states), and SHALL NOT require any external symbol
the consumer must define.

#### Scenario: STM32 G0 enter PLL HSI16 64 MHz body programs RCC + FLASH

- **WHEN** alloy-codegen emits `runtime_init.c` for
  `st/stm32g0/stm32g071rb`
- **THEN** `runtime_init.c` defines
  `void alloy_clock_enter_pll_hsi16_64mhz(void)` whose body
  - sets `FLASH.ACR.LATENCY` to `2` before the SYSCLK switch
  - configures `RCC.PLLCFGR` with `PLLM=1, PLLN=8, PLLR=2`
  - sets `RCC.CR.PLLON=1` and spins on `RCC.CR.PLLRDY`
  - sets `RCC.CFGR.SW=0b011` and spins on `RCC.CFGR.SWS == 0b011`
- **AND** the body compiles without any consumer-supplied helper

#### Scenario: SAM E70 enter recommended-300mhz body programs PMC + EFC

- **WHEN** alloy-codegen emits `runtime_init.c` for
  `microchip/same70/atsame70q21b`
- **THEN** `runtime_init.c` defines
  `void alloy_clock_enter_recommended_300mhz(void)` whose body
  - sets `EFC.FMR.FWS` to the WS count for 300 MHz before the
    PLLA switch
  - programs `CKGR.CKGR_PLLAR` from the IR's PLLA coefficients
  - spins on `PMC.PMC_SR.LOCKA`
  - sets `PMC.PMC_MCKR.CSS=PLLA_CLK` and spins on
    `PMC.PMC_SR.MCKRDY`

### Requirement: `enter_<profile>` Bodies SHALL Use A Bounded Spin-Loop Helper

Profile bodies SHALL NOT contain bare `while ((reg & mask) !=
expected) {}` loops.  Every readback-spin SHALL go through a
typed helper `alloy_clock_spin_until(volatile uint32_t *,
uint32_t mask, uint32_t expected, uint32_t timeout_us)` declared
in the runtime-lite contract.

#### Scenario: PLL lock spin uses bounded helper

- **WHEN** alloy-codegen emits the PLL lock spin in any
  `alloy_clock_enter_*` body
- **THEN** the body calls
  `alloy_clock_spin_until(&RCC->CR, RCC_CR_PLLRDY_Msk,
  RCC_CR_PLLRDY_Msk, ALLOY_CLOCK_PLL_LOCK_TIMEOUT_US)`
- **AND** on timeout the helper triggers `__BKPT(0)` so the
  stuck transition is debuggable from the first instruction

### Requirement: `enter_<profile>` Bodies SHALL Be Byte-Deterministic

The runtime-lite contract SHALL emit each
`alloy_clock_enter_<profile_id>` body byte-identically for a
fixed canonical IR across runs on different machines, Python
versions ≥ 3.13, and OSes.

#### Scenario: Diff against the golden file is empty

- **WHEN** the test suite regenerates `runtime_init.c` for any
  admitted device and diffs against
  `tests/fixtures/emitted/<vendor>/<family>/<chip>/runtime_init.c`
- **THEN** the diff is empty

### Requirement: Runtime-Lite Contract SHALL Reject Unreachable Profiles At Synthesis Time

The runtime-lite synthesiser SHALL raise `StageExecutionError`
naming the offending profile id and the violated constraint when
`device.clock.profiles[i]` declares a `sysclk_source` / `hclk_hz`
combination unreachable from the IR's `clock.domains` graph (e.g.
PLL coefficients out of `clock.pll.*_range`, no path from listed
oscillators to the requested SYSCLK source), and SHALL NOT emit a
body that boots the part into a hung state.

#### Scenario: Out-of-range PLL coefficients refuse at synthesis

- **WHEN** a YAML carries a profile with `pll_n: 200` for an
  STM32 G0 whose `clock.pll.n_range` is `[8, 86]`
- **THEN** synthesis raises `StageExecutionError`
- **AND** the message names the profile id, the violated
  range, and the YAML file path
