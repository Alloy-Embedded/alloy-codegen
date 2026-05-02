# Design — Complete Clock-Tree Runtime Init

## Context

The IR's clock model is uniform across vendors:

```
Clock {
    oscillators: dict[str, Oscillator]   # 'hsi', 'lse', 'pll_main', ...
    domains:     tuple[ClockDomain, ...] # mux + prescaler graph
    pll:         PLLConfig | None        # coefficient ranges
    profiles:    tuple[ClockProfile, ...] # named target operating points
}

ClockDomain {
    id:                  str
    sources:             tuple[str, ...] | None   # mux candidates
    source:              str | None               # fixed source
    select_register:     SelectRegister | None    # {reg, field, encoding}
    prescaler_register:  Register | None
    prescalers:          tuple[int, ...] | None
}
```

What's vendor-specific is the **shape of the program**:
STM32 needs `RCC.CR.PLLON=1 → spin(PLLRDY) → RCC.CFGR.SW=PLL → spin(SWS)`,
SAM PMC needs `CKGR_PLLAR=... → spin(PMC_SR.LOCKA) → PMC_MCKR.CSS=PLLA → spin(MCKRDY)`,
RP2040 needs `pll_sys_init() → clocks_set_source(...)`.

The IR carries **enough data for any of these programs** in
`select_register` / `prescaler_register` triples — but the order
of writes, the readback spin loops, and the FLASH-latency
ordering are all per-vendor protocol.  That protocol lives in the
**ClockBackend adapter**, not in the emitter.

## Goals

- Single point of consumption: emitter calls
  `synthesised.clock_program_steps[profile_id]` and writes them.
- Per-vendor backend isolated to one module + one Protocol.
- Profile bodies are byte-deterministic.
- A "wrong" profile (target HCLK unreachable from the available
  oscillators) is rejected at synthesis time, not boot time.
- Output compiles with no consumer-side helpers required —
  `runtime_init.c` is self-contained.

## Non-Goals

- **Dynamic profile switching at runtime.**  The emitted bodies
  are one-shot.  Switching profiles after peripherals are open
  needs a suspend/resume protocol that's a separate proposal.
- **Per-peripheral kernel clock selection** (e.g.
  `RCC.CCIPR.USART1SEL = SYSCLK`).  Those switches happen when
  the HAL opens the instance, not in `enter_<profile>()`.
- **Non-MCU clock-source bring-up** (external crystal warm-up
  guidance, OTP fuse reads).  Out of scope; the `enter_<profile>`
  body assumes the IR-listed oscillators are available.

## Decisions

### Decision 1 — Backend Protocol shape

```python
class ClockBackend(Protocol):
    @staticmethod
    def emit_profile(
        profile: ClockProfile,
        device: CanonicalDevice,
    ) -> tuple[ClockProgramStep, ...]:
        ...
```

Each `ClockProgramStep` is a `(register_id, field_id, value, kind)`
tuple where `kind ∈ {WriteField, ReadbackSpin, BarrierIsb, BarrierDsb,
PllProgram, FlashLatency}`.  The emitter walks the steps and lowers
each to one or two C statements.

**Alternatives considered**:
- *Per-vendor C templates* — ties C string literals to vendor
  knowledge, makes audit hard.
- *In-emitter `if vendor == "st"`* — same anti-pattern as the
  existing template-blind emitters; rejected.

### Decision 2 — Where FLASH latency math lives

**Choice**: A small `flash_wait_states: tuple[FlashLatencyEntry, ...]`
field on `Identity`, populated from `family.yml` during YAML load.
Each entry is `(min_hz, max_hz, ws_count, encoding)`.  The ST
backend looks up the entry whose `min_hz <= profile.hclk_hz <
max_hz` and emits a single FLASH.ACR write.

**Rationale**: STM32 flash latency varies by family (G0: 0/1/2 WS,
H7: 0..7 WS) and by VOS voltage scaling.  Encoding it in the IR
keeps the backend small and gives reviewers a single-number
audit point per family.

### Decision 3 — PLL programming guard rails

**Choice**: The synthesiser computes the PLL coefficient triple
from `profile.pll_m/n/r/p/q` (already on the YAML) and verifies
against `clock.pll.{m_range, n_range, r_range, vco_range}`.
Mismatch raises `StageExecutionError` with a clear message naming
the violated bound.

**Rationale**: Today's YAML carries the triple but no validation;
a typo in a profile (M=1, N=80 → VCO out of range) would silently
emit a body that bricks the part on first boot.  Synthesis-time
validation catches it before any byte ships.

### Decision 4 — Readback spin-loop ergonomics

**Choice**: Emit a typed helper `alloy_clock_spin_until(uint32_t
volatile *addr, uint32_t mask, uint32_t expected, uint32_t timeout_us)`
in the runtime-lite contract; profile bodies call it instead of
`while (...) {}` directly.  The helper has a typed timeout and
raises `__BKPT(0)` on timeout (so a stuck PLL is debuggable from
the first instruction).

**Rationale**: Bare `while ((RCC->CR & PLLRDY) == 0) {}` has bricked
more dev boards than any other piece of bring-up code.  Putting
the timeout in one place makes it auditable.

## Risks

| Risk                                              | Mitigation                                                    |
|---------------------------------------------------|---------------------------------------------------------------|
| ST H7 three-domain RCC math has off-by-one bugs   | Per-family golden fixture + `pytest -m hardware` on a Nucleo |
| FLASH latency programmed in wrong order           | Backend test asserts WS write happens before SYSCLK switch when going higher and after when going lower |
| `enter_<profile>` runs before stack is up         | Profile body is `noinline`; consumer's reset handler MUST set MSP before calling.  Documented + asserted in the body's first line via `__set_MSP` check on Cortex-M |
| Backend disagrees with vendor reference manual    | Each backend module includes a `# Reference: RM0444 §6.2.x` comment per non-trivial step |
| New family lands without a backend                | `_validate_registry` rejects with a clear "no ClockBackend for vendor=<v>" error |

## Migration Plan

1. Land the IR additions (`flash_wait_states`, validators) +
   ClockBackend Protocol.  No emitter change yet; tests confirm
   IR loads and synthesises.
2. Land ST backend.  Regenerate goldens for the 514 STM32 chips.
   Verify byte-stable; alloy HAL's existing build should still
   pass against the new bodies (the headers are unchanged).
3. Land SAM-PMC + SAM-GCLK backends.
4. Land RP2040 + ESP32 backends.
5. Drop the "stub forward-decl only" wording from the existing
   `runtime-lite-contract` spec; the contract is now
   "executable body for every admitted profile".

## Open Questions

- Should `enter_default_<oscillator>()` (the post-reset profile)
  be emitted at all, given the chip is already there at reset?
  Default to yes — it gives consumers a no-op landing pad they
  can call as a sanity check, and on chips like RP2040 the
  "post-reset" profile already requires writing the watchdog
  before the first PLL bring-up.
- Where do per-peripheral kernel clocks get programmed if not
  here?  Strawman: `peripheral_traits.h` exposes
  `kKernelClockSelectField` and the HAL writes it on open.  Out
  of scope for this proposal.
- Does ESP32 need its own `enter_*` family at all, or does
  ESP-IDF's `bootloader.c` always run first?  Default to
  emitting only the "enter_recommended" stub for ESP32 in this
  proposal; full bring-up parity is a follow-up.
