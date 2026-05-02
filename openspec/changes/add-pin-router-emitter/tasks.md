# Tasks — Add Pin-Router Emitter

## 1. Synthesised IR

- [ ] 1.1 Add `PinRoute` dataclass to `src/alloy_codegen/ir/synthesised/`
      with fields: `peripheral_id: str`, `peripheral_signal: str`,
      `pin_id: str`, `backend_schema_id: str`,
      `code: int | None`, `payload: Mapping[str, int | str]`
      (typed cell holding `af_number` / `psel_id` / `funcsel` /
      `matrix_function`, the variant decided by `backend_schema_id`).
- [ ] 1.2 Add `pin_routes: tuple[PinRoute, ...]` field to
      `SynthesisedDevice`; ensure deterministic ordering
      (`peripheral_id, peripheral_signal, pin_id`).
- [ ] 1.3 Extend `synthesise/builder.py` to walk
      `device.peripherals[*].pin_options` and lower each
      `PinOptionFixed | PinOptionMatrix | PinOptionPsel` payload to
      the corresponding `PinRoute`.  Use a `PinmuxBackend` Protocol
      to pick the encoder per family.
- [ ] 1.4 Materialise `tuple[PinId, ...]` (canonical pad enumeration)
      from `device.pinout` filtered by constraint set.

## 2. Pinmux backend adapters

- [ ] 2.1 `src/alloy_codegen/synthesise/pinmux/stm32_af_v1.py` — encodes
      `PinOptionFixed` to a single 4-bit AF number per
      (instance, signal, pin).
- [ ] 2.2 `src/alloy_codegen/synthesise/pinmux/sam_pio_v1.py` —
      encodes `PinOptionMatrix.matrix` (A/B/C/D) for SAM E70/V71
      PIO controllers; SAMD21/D51/L21 use a different sub-schema
      (peripheral function PMUXEN), encoded as a separate variant.
- [ ] 2.3 `src/alloy_codegen/synthesise/pinmux/rp2040_funcsel_v1.py`
      — encodes RP2040's `FUNCSEL` 0-31 indices.
- [ ] 2.4 `src/alloy_codegen/synthesise/pinmux/iomatrix_espressif_v1.py`
      — encodes ESP32 IO Matrix signal index (`af_number` is the
      matrix slot).
- [ ] 2.5 `src/alloy_codegen/synthesise/pinmux/iomuxc_imxrt_v1.py`
      — encodes NXP iMX RT IOMUXC mux mode + daisy-chain.
- [ ] 2.6 `src/alloy_codegen/synthesise/pinmux/avr_portmux_v1.py`
      — encodes Microchip AVR-DA PORTMUX selection index.
- [ ] 2.7 Each adapter rejects payloads it can't encode and raises a
      `StageExecutionError` with a clear "<family>/<device>:
      pin_options shape <X> not encodable under
      <backend_schema_id>" message.

## 3. Emitter

- [ ] 3.1 New module `src/alloy_codegen/emit_v2_1/pin_router.py`
      with `emit_pin_router(device, synthesised) -> str` returning
      the full `pins.h` text.
- [ ] 3.2 Header preamble: include guard, schema lock-string check,
      schema-specific banner ("alloy-pins-v1" — bump on every
      breaking shape change).
- [ ] 3.3 Emit `enum class PinId : uint16_t { ... };` from
      `synthesised.pin_ids`, with one entry per non-power pad,
      named after `Pin.signal` (sanitised).
- [ ] 3.4 Emit `struct PinRoute { PeripheralId; SignalId; PinId;
      uint8_t code; }` and the route table as a flat
      `constexpr std::array<PinRoute, N> kRoutes`.
- [ ] 3.5 Emit `template <PeripheralId I, SignalId S, PinId P>
      constexpr auto route_for() noexcept` resolving from
      `kRoutes` at compile time via a `consteval` lookup.
- [ ] 3.6 Emit `template <PinId P> constexpr PinConstraints
      constraints_of() noexcept` from `device.pinout[*].constraints`.
- [ ] 3.7 STM32 alternate-pin annotation (`PA12 [PA10]`) emits a
      `kAlternateRoutes` runtime table and exposes
      `pin_route_lookup(PeripheralId, SignalId, PinId)` for chips
      where the IR marks routes as runtime-resolvable.

## 4. Wire-up

- [ ] 4.1 Register `_EmitterEntry(name="pin_router",
      filename="pins.h", fn=emit_pin_router)` in
      `cli.py::_EMITTERS` and `entrypoint.py::_EMITTERS`.
- [ ] 4.2 Update `cli.py` `--list` and `--emit` documentation to
      mention the new artifact.
- [ ] 4.3 Update `pyproject.toml` if any new optional deps are
      pulled in (none expected).

## 5. Tests

- [ ] 5.1 Unit tests for each `PinmuxBackend` adapter under
      `tests/test_synthesise_pin_routes.py` — synthetic
      `PinOptionFixed`/`Matrix`/`Psel` payloads; assert encoded
      `PinRoute`.
- [ ] 5.2 Unit tests for `emit_pin_router` shape (header guard,
      `PinId` enum size matches non-power pad count, route count
      matches synthesised count) under
      `tests/test_emit_pin_router.py`.
- [ ] 5.3 Add `pins.h` to the existing per-device golden suite under
      `tests/fixtures/emitted/<vendor>/<family>/<chip>/pins.h` for
      every admitted device (covered by the
      `enforce-strict-typing-and-golden-coverage` 100% gate).
- [ ] 5.4 Add a smoke test that compiles `pins.h` against a
      stub `alloy::device::types` namespace using the project's
      existing arm-none-eabi smoke harness.
- [ ] 5.5 Update `test_entrypoint.py` to assert `pins.h` is in the
      written-files set.

## 6. Documentation

- [ ] 6.1 Add a "Pin routing" section to `CONTRIBUTING_DEVICES.md`
      explaining how to verify a new chip's `pin_options`
      round-trips through the chosen `PinmuxBackend`.
- [ ] 6.2 Add a `docs/pin_router_contract.md` (or update
      `runtime-lite-contract` design notes) documenting the
      `pins.h` shape so alloy HAL contributors can rely on it.
