# Design — Add Pin-Router Emitter

## Context

Six admitted vendor families and six pinmux backends:

| Family            | Backend schema id                  | Encoding shape                                 |
|-------------------|------------------------------------|------------------------------------------------|
| `st/stm32*`       | `alloy.pinmux.stm32-af-v1`         | 4-bit AF number per (pad, peripheral, signal) |
| `microchip/same70`, `samv71` | `alloy.pinmux.sam-pio-v1` | PIO matrix function letter A/B/C/D |
| `microchip/samd21`, `samd51`, `saml21` | `alloy.pinmux.sam-pmux-v1` (new) | Peripheral function index 0-7 + PMUXEN |
| `microchip/avr-da` | `alloy.pinmux.avr-portmux-v1`     | PORTMUX register selection index               |
| `nxp/imxrt1060`   | `alloy.pinmux.imxrt-iomuxc-v1`     | IOMUXC mux mode + daisy-chain register         |
| `raspberrypi/rp2040` | `alloy.pinmux.rp2040-funcsel-v1` | FUNCSEL 0-31 index                             |
| `espressif/esp32*` | `alloy.pinmux.espressif-iomatrix-v1` | IO Matrix signal index (per-direction tables) |

Today the IR carries the raw payload (e.g. `PinOptionFixed.func: 7`)
without committing to what `func` *means* under the family's backend
schema — the backend schema id is only carried in `project.md`.
This proposal binds the schema id into the emitter dispatch so the
generated `pins.h` is unambiguous.

## Goals

- Single typed surface `route_for<I, S, P>()` that returns a
  `constexpr PinRoute` for any compile-time-known (instance, signal,
  pin) triple.
- Per-family backend logic is **isolated to one adapter** — the
  emitter has zero per-vendor branches.
- Output is byte-deterministic given the same IR.
- No `const char*` semantic strings in `pins.h` (per artifact-contract
  zero-string rule); all routing facts are integers, enums, or refs.

## Non-Goals

- **Pin conflict resolution** — when two peripherals can both drive
  PA2, this emitter publishes both routes; the alloy HAL `pin_router`
  picks one at config time.  Static conflict detection is a follow-up
  proposal once the published surface stabilises.
- **Runtime-only pin remap fuses** — chips that flip pin functions
  via a OTP fuse (some Renesas, some Nordic) are out of scope.  The
  IR can carry a `runtime_resolvable: true` marker; the emitter
  emits an entry in `kAlternateRoutes` so the bring-up code can
  resolve it post-fuse-read.

## Decisions

### Decision 1 — Adapter Protocol vs class hierarchy

**Choice**: `PinmuxBackend` `Protocol` (Python), one adapter module
per backend schema id, each exporting a single
`encode(option: PinOption*, signal: str, pin: str) -> PinRouteCell`
function.

**Alternatives considered**:
- *Class hierarchy* — less Pythonic, harder to add a new backend
  without subclassing.
- *Inline `match` in the synthesiser* — keeps every vendor's
  encoding in one giant function; same problem the emitters already
  have (template-blind by accident).

The Protocol form mirrors how alloy-codegen already handles
vendor-specific normalizers (`sources/microchip_dfp.py`,
`sources/esp_idf.py`).

### Decision 2 — Synthesise-once vs emit-time iteration

**Choice**: Synthesise once into `tuple[PinRoute, ...]` on the
`SynthesisedDevice`; the emitter is a pure formatter.

**Alternatives considered**:
- *Emit-time iteration* — couples the emitter to every backend and
  re-walks `peripherals[].pin_options` per emitter (peripheral_traits
  also wants the route data for `kCanonicalRxPin` etc.).

Synthesising once is consistent with how `route_operations`,
`vector_slots`, and `signal_endpoints` are already materialised.

### Decision 3 — `PinId` scope

**Choice**: Per-package, named after the `Pin.signal` label.  Power
pads (`constraints: [power]`), ground, and strapping pads are
filtered out of `PinId` and only surface through `constraints_of()`.

**Alternatives considered**:
- *Global flat enumeration* — duplicates entries across packages,
  consumer can't iterate "all pads on this device".
- *Per-port* (PA0..PA15, PB0..PB15) — STM32-flavoured, doesn't map
  onto SAM/RP2040/ESP32 numbering.

`Pin.signal` is the canonical pad label across vendors and is what
the YAML carries; `PinId` reflects that 1:1.

### Decision 4 — Alternate-pin annotation

**Choice**: Two-tier — compile-time `kRoutes` for the canonical
pad, runtime-resolvable `kAlternateRoutes` for STM32-style
`PA12 [PA10]` annotations.  The IR carries
`PinOptionFixed.alternate_pin: str | None` to flag this; the
synthesiser emits both rows.

**Rationale**: alternate-pin annotations are package-and-fuse
conditional; resolving them at compile time would require the
caller to know the fuse state.  Runtime resolution costs one
indirection on the cold path of `pin_router::open()` and is
strictly safer.

## Risks

| Risk                                            | Mitigation                                                     |
|-------------------------------------------------|----------------------------------------------------------------|
| Per-vendor adapter bug silently miswires pins   | Per-backend unit tests with golden encoded payloads + alloy HAL contract test on a real eval board |
| `pins.h` blows up to 100 KB on STM32H743       | Tables are `constexpr std::array`, dead-code-eliminated at link time; only routes for instantiated `PeripheralId` survive |
| New vendor lands without backend schema id     | `_validate_registry` rejects with a clear error referencing `project.md`'s admitted-backends table |
| ESP32 IO Matrix has bidirectional routing      | Backend emits two route entries (in + out); `route_for<>()` resolves by signal direction |

## Migration Plan

This is net-new code; nothing existing emits `pins.h`.  Roll-out:

1. Land synthesiser + STM32 backend; validate against existing 514
   STM32 chips' golden suite.
2. Land SAM-PIO + AVR-PORTMUX + RP2040-FUNCSEL backends; validate
   against the 53 SAM + 11 AVR + 2 RP2040 chips.
3. Land ESP32 IO Matrix + iMX RT IOMUXC backends.
4. Ship `pins.h` to consumers behind a `--emit pin_router` opt-in
   for one release cycle, then promote to default.

## Open Questions

- Does alloy HAL prefer `PinRoute` to carry the backend's raw cell
  value (e.g. `code: 7` for AF7) or a typed `Stm32AfNumber` /
  `RpFuncSel` wrapper?  The latter is safer; the former is smaller.
  Default to typed wrappers per backend, expose the raw value as
  `code()`.
- Should `pins.h` re-export `device.pinout[*].constraints` as a
  separate `pin_constraints.h`?  Probably not — keeping
  `constraints_of()` next to `route_for<>()` is more discoverable
  and the constraint set is small.
