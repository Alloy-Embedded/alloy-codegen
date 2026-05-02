# Add Pin-Router Emitter (`pins.h`)

## Why

The canonical v2.1 IR carries the **richest single block of dead data**
in the entire schema:

- `device.pinout` is populated on **587/587 admitted chips**, with one
  `Pin` entry per package pad (signal, constraints, and on STM32 the
  per-package alternate-pin annotations like `PA12 [PA10]`).
- `peripherals[].pin_options` is populated on **almost every routable
  instance**: 3,918 timer instances, 2,451 USARTs, 1,538 SPIs, 1,364
  I²Cs, 1,064 ADCs, plus the SAM/RP2040/ESP32 equivalents — across the
  full 587-chip corpus.

None of that data reaches a generated artifact today.  The four
emitters never read `device.pinout` and only use the **keys** of
`peripherals[].pin_options` (via the synthesiser, to populate
`SignalEndpoint`); the payloads (`PinOptionFixed.pin/remap/func/pinned`,
`PinOptionMatrix.matrix/default/fast_path`, `PinOptionPsel`) are
parsed and dropped on the floor.  The result: alloy's HAL has no
typed way to ask "give me the AF/PSEL/FUNCSEL number that routes
USART2_TX to PA2 on this device" — every backend is open-coded
against vendor headers, defeating the codegen's purpose.

`alloy_cli init` + `alloy_add_runtime_executable` cannot wire up a
single `alloy::gpio::route_uart_tx<PA2>()` call without this artifact.
This proposal closes the gap.

## What Changes

A new emitter `emit_pin_router` produces **`pins.h`**, a
runtime-lite C++ artifact that publishes the typed pin-route surface
the HAL needs:

- A typed `PinId` enum scoped per package (one entry per
  `device.pinout[i].signal` whose `constraints` mark it as a routable
  GPIO/AF pad — power/ground/strapping pads are excluded).
- For every `(peripheral_instance, peripheral_signal, pin)` triple in
  the device's `pin_options` payload, a `constexpr PinRoute` literal
  carrying the typed instance ref, the typed signal ref, the typed
  pin ref, and the **vendor-specific routing code** (`af_number`,
  `psel_id`, `funcsel`, `matrix_function`, etc.) under the family's
  pinmux backend schema id (e.g. `alloy.pinmux.stm32-af-v1`).
- A `template <PeripheralId I, SignalId S, PinId P>
  constexpr auto route_for() noexcept` accessor returning the matching
  `PinRoute` at compile time, plus a runtime fallback table for the
  small set of cases where alternate-pin annotations like STM32's
  `PA12 [PA10]` (PA10 mode for a USB DP/DM pad on UFQFPN28) need to
  be resolved by the bring-up code.
- `device.pinout[i].constraints` (`power`, `ground`, `strapping`,
  `analog_only`, `input_only`) is exposed via
  `template <PinId P> constexpr PinConstraints constraints_of()`
  so the HAL can refuse routes onto power pads at compile time.

The emitter is **template-name-blind in its core path** — it iterates
`peripherals[*].pin_options` regardless of peripheral class — but
delegates the per-vendor encoding of the routing code to a small set
of `PinmuxBackend` adapters keyed by the family's
`pinmux_backend_schema_id` (already published in `project.md`).
Adding a new vendor adds one adapter; the emitter does not branch
per peripheral class.

The IR gains a small companion synthesised dataclass `PinRoute` so
the emitter doesn't reach into raw `PinOption*` shapes at write time;
the synthesiser materialises the per-device, per-instance route
table once and the four emitters read it as a tuple.

`linker_script` and `vector_table` are untouched.  `peripheral_traits`
gains one cross-reference per instance so a `PeripheralInstanceTraits`
specialisation can name its first valid route at compile time
(`kCanonicalRxPin` etc.) — that surface is opt-in and only emitted
for instance kinds the HAL classifies as needing a default route.

## Impact

- **Affected specs**:
  - **MODIFIED** `canonical-device-ir` — pin assignment data is
    promoted from "parsed but unused" to "executable contract"; the
    `PinmuxBackend` schema-id contract is folded into the canonical
    IR requirements.
  - **ADDED** `artifact-contract` — `pins.h` is a new published
    runtime-lite artifact with a documented per-vendor encoding
    contract.
  - **ADDED** `runtime-lite-contract` — typed `PinId`, `PinRoute`,
    and `route_for<>()` accessor join the runtime-lite surface.
- **Affected code**:
  - new `src/alloy_codegen/emit_v2_1/pin_router.py`
  - new `src/alloy_codegen/synthesise/pin_routes.py` (or extension
    of the existing synthesiser to materialise `tuple[PinRoute, ...]`)
  - new `tests/fixtures/emitted/<family>/<chip>/pins.h` golden
    snapshots — gated behind the existing 100% admitted-device golden
    coverage requirement
  - `cli.py` and `entrypoint.py` register the new emitter in
    `_EMITTERS`
- **Risks / trade-offs**:
  - **Per-vendor backend complexity** — STM32 AF, SAM PIO matrix,
    RP2040 FUNCSEL, ESP32 IO Matrix, and AVR PORTMUX have different
    encoding shapes.  Mitigation: a single `PinmuxBackend` Protocol
    keeps the dispatch in one file; new backends are net-new modules,
    not branches in the emitter.
  - **STM32 alternate-pin annotation** (`PA12 [PA10]` style) is
    package-conditional; the emitter handles this by emitting both
    the canonical `PA12` route and a runtime-resolvable alternate
    when the IR carries it.  Pure compile-time selection is unsafe
    when a single pad has two functions tied to a fuse or strap.
  - **Golden-file blow-up** — `pins.h` is large for chips like
    STM32H743 (10+ ports × 16 pins × 16 AFs).  Mitigation: emit
    grouped tables, not flat literals; rely on the emitter being
    deterministic so diffs only appear when the IR changes.
- **Out of scope**:
  - Pin-conflict resolution (one pin → multiple peripheral routes
    chosen at config time).  This proposal makes the conflict
    *expressible*; choosing one is the alloy HAL's `pin_router::open`
    call.
  - GPIO mode/speed/pull-up encoding — already covered by alloy's
    `Gpio*Traits` headers via existing `peripheral_traits`.
  - Any `device.pinout` entries with constraint `power`/`ground`/
    `strapping` are excluded from `PinId` — they are exposed only
    through `constraints_of()`.
