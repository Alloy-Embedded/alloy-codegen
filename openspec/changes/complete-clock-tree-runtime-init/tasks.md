# Tasks — Complete Clock-Tree Runtime Init

## 1. IR additions

- [ ] 1.1 Add `flash_wait_states: tuple[FlashLatencyEntry, ...]`
      field to `CanonicalDevice` (or `Identity`).  Each entry
      carries `(min_hz, max_hz, ws_count, encoding)` derived from
      `family.yml`.
- [ ] 1.2 Promote `clock.pll.lock_field`, `clock.pll.power_field`
      to mandatory typed refs (validate via JSON schema) where
      `clock.pll` is populated.
- [ ] 1.3 Add `Profile.flash_latency_hz: int | None` derived field
      so the emitter doesn't reach back into `Identity` per
      profile.
- [ ] 1.4 Update `canonical_device_v2_1.py` loader to populate
      the new fields and fail-fast on incomplete clock metadata.

## 2. Synthesised IR

- [ ] 2.1 Add `clock_program_steps: tuple[ClockProgramStep, ...]`
      per profile to `SynthesisedDevice`.  Each `ClockProgramStep`
      is a typed rmw operation
      (`{register_id, field_id, value, schema_id}`) emitted in
      execution order.
- [ ] 2.2 The synthesiser delegates per-vendor lowering to a
      `ClockBackend` Protocol; the resulting program is
      vendor-agnostic from the emitter's point of view.

## 3. Clock backends

- [ ] 3.1 `src/alloy_codegen/emit_v2_1/clock_backends/__init__.py`
      registry mapping `vendor` → backend module.
- [ ] 3.2 `clock_backends/st.py` — STM32 F0/F1/F3/F4/G0/G4/H7.
      Encodes:
      - PLL coefficient programming (`PLL.M/N/R/P/Q`)
      - PLL power-up + lock-spin
      - SYSCLK source switch via `RCC.CFGR.SW` + readback wait
      - HCLK / PCLK1 / PCLK2 prescalers
      - FLASH latency program before the SYSCLK switch when going
        higher, after when going lower
      - HSI48 enable for USB families
- [ ] 3.3 `clock_backends/microchip_sam_pmc.py` — SAM E70/V71
      (PMC + EFC).  Encodes oscillator selection, MAINCK source,
      PLLA programming, MCKR prescalers, EEFC wait states.
- [ ] 3.4 `clock_backends/microchip_samd_gclk.py` — SAM D21/D51/L21
      (GCLK + OSCCTRL).  Encodes XOSC/DFLL programming,
      `GCLK_GENCTRL[N]` for the requested generator, NVMCTRL
      wait states.
- [ ] 3.5 `clock_backends/raspberrypi_rp.py` — RP2040 (PLL_SYS,
      PLL_USB, CLK_SYS / CLK_PERI / CLK_USB dividers).
- [ ] 3.6 `clock_backends/espressif_soc.py` — ESP32 / S3 / C3
      RTC_CNTL clock source + CPU clock source.  Minimal "enter
      recommended" only.
- [ ] 3.7 `clock_backends/_protocol.py` — defines
      `ClockBackend(Protocol)` with `emit_profile(profile, device)
      -> tuple[ClockProgramStep, ...]`.
- [ ] 3.8 Each backend rejects profiles it cannot reach with
      `StageExecutionError` at synthesis time.

## 4. Emitter

- [ ] 4.1 `runtime_init.py::_emit_profile_body(profile,
      synthesised)` walks `synthesised.clock_program_steps[profile_id]`
      and lowers each step to a single C statement
      (`*(volatile uint32_t*)0x40021000 = (read & ~mask) | value;`)
      or to a typed `RouteOperation`-style helper call when the
      runtime-lite contract exposes one.
- [ ] 4.2 `_emit_profile_body` also emits the necessary readback
      spin-loops (`while ((RCC->CR & PLLRDY) == 0) {}` style)
      for PLL lock and SYSCLK source switch confirmation.
- [ ] 4.3 The function body is wrapped in
      `__attribute__((noinline))` and uses `__DSB()` / `__ISB()`
      barriers around clock-source transitions where the IR
      flags the domain as `requires_barrier: true`.
- [ ] 4.4 The forward-declarations stay; the bodies are now
      defined in the same `runtime_init.c` so consumers don't
      need to provide their own.

## 5. Wire-up

- [ ] 5.1 No new entry in `_EMITTERS` — `runtime_init` is already
      registered.
- [ ] 5.2 Update `cli.py` `--list` documentation to mention
      profiles are now self-contained.
- [ ] 5.3 Add a build-time assertion in `runtime_init.c` that
      `__SCB->CPACR` is reset-state at function entry (catches
      consumers that already enabled FPU before the clock
      profile runs).

## 6. Tests

- [ ] 6.1 Per-backend unit tests under
      `tests/test_clock_backend_<vendor>.py` — feed synthetic
      `Profile` + `ClockDomain` shapes; assert the lowered
      `tuple[ClockProgramStep, ...]` matches the expected
      register/field/value triples.
- [ ] 6.2 Regenerate `runtime_init.c` golden files for every
      admitted device.
- [ ] 6.3 Compile-test the regenerated bodies against
      `arm-none-eabi-gcc -mcpu=cortex-m0plus -nostdlib` (and the
      equivalent flag set per ISA) to catch syntax errors.
- [ ] 6.4 Add a "PLL settle math" test that verifies for every
      ST chip with a populated `pll-recommended` profile, the
      `(M, N, R)` triple in the YAML actually multiplies to
      the claimed `sysclk_hz` within 0.1% tolerance.
- [ ] 6.5 (Optional, behind `pytest -m hardware`) bring-up smoke
      on a Nucleo-G071RB confirming the emitted body runs and
      `SystemCoreClock` reads 64 MHz after `enter_pll_hsi16_64mhz()`.

## 7. Documentation

- [ ] 7.1 Update `runtime-lite-contract` design notes documenting
      the profile-body shape.
- [ ] 7.2 Add a "Clock backends" section to
      `CONTRIBUTING_DEVICES.md` for new-vendor onboarding.
