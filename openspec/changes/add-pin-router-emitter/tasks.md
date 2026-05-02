# Tasks — Add Pin-Router Emitter

## 1. Synthesised IR

- [x] 1.1 Add `PinRoute` dataclass to `src/alloy_codegen/ir/synthesised/`
      with fields: `peripheral_id: str`, `peripheral_signal: str`,
      `pin_id: str`, `backend_schema_id: str`,
      `code: int | None`, `payload: Mapping[str, int | str]`
      (typed cell holding `af_number` / `psel_id` / `funcsel` /
      `matrix_function`, the variant decided by `backend_schema_id`).
      *(Landed minus the `payload: Mapping` field — current YAML
      doesn't carry per-backend payload variants yet; using
      ``code: int | None`` + ``alternate_pin: str | None`` as
      the foundational cell.)*
- [x] 1.2 Add `pin_routes: tuple[PinRoute, ...]` field to
      `SynthesisedDevice`; ensure deterministic ordering
      (`peripheral_id, peripheral_signal, pin_id`).
- [x] 1.3 Extend `synthesise/builder.py` to walk
      `device.peripherals[*].pin_options` and lower each
      `PinOptionFixed | PinOptionMatrix | PinOptionPsel` payload to
      the corresponding `PinRoute`.  Use a `PinmuxBackend` Protocol
      to pick the encoder per family.
- [ ] 1.4 Materialise `tuple[PinId, ...]` (canonical pad enumeration)
      from `device.pinout` filtered by constraint set.
      *(Pad enumeration lives directly in the emitter via
      `_gather_pin_ids`; promoting to a synthesised tuple lands
      with the constraints follow-up.)*

## 2. Pinmux backend adapters

- [x] 2.1 `src/alloy_codegen/emit_v2_1/pinmux_backends/stm32_af.py`
      — encodes `PinOptionFixed` to a single 4-bit AF number per
      (instance, signal, pin).  Landed under
      ``alloy.pinmux.stm32-af-v1``; ``code`` stays ``None`` until
      alloy-devices-yml carries an ``af:`` field on each row,
      then the backend passes it through unchanged.  Pad-label
      normalisation handles ``PA12 [PA10]`` /
      ``PC15-OSC32_OUT (PC15)`` / ``PA14-BOOT0`` cleanly.
- [ ] 2.2 `sam_pio_v1.py` — encodes `PinOptionMatrix.matrix`
      (A/B/C/D) for SAM E70/V71 PIO controllers; SAMD21/D51/L21
      use a different sub-schema (peripheral function PMUXEN),
      encoded as a separate variant.
- [ ] 2.3 `rp2040_funcsel_v1.py` — encodes RP2040's `FUNCSEL`
      0-31 indices.
- [ ] 2.4 `iomatrix_espressif_v1.py` — encodes ESP32 IO Matrix
      signal index.
- [ ] 2.5 `iomuxc_imxrt_v1.py` — NXP iMX RT IOMUXC mux mode +
      daisy-chain.
- [ ] 2.6 `avr_portmux_v1.py` — Microchip AVR-DA PORTMUX
      selection index.
- [ ] 2.7 Each adapter rejects payloads it can't encode and raises
      a `StageExecutionError` with a clear "<family>/<device>:
      pin_options shape <X> not encodable under
      <backend_schema_id>" message.
      *(STM32 backend rejects non-Fixed options today; full
      cross-vendor refusal lands when the SAM/RP/ESP backends
      arrive.)*

## 3. Emitter

- [x] 3.1 New module `src/alloy_codegen/emit_v2_1/pin_router.py`
      with `emit_pin_router(device, synthesised) -> str` returning
      the full `pins.h` text.
- [x] 3.2 Header preamble: include guard, schema lock-string check,
      schema-specific banner ("alloy-pins layout v1" — bump on
      every breaking shape change).
- [x] 3.3 Emit `enum class id : uint16_t { ... };` (in namespace
      `alloy::<v>::<f>::<chip>::pin`) from the gathered pad set —
      one entry per non-power pad in ``device.pinout`` plus any
      alternate-pin destinations referenced by routes.
- [x] 3.4 Emit `struct route { ... }` and the route table as a
      flat `constexpr std::array<route, N> kRoutes`.
      *(Peripheral / signal flow as `const char *` placeholders
      until typed PeripheralId / SignalId enums ship from a
      sibling proposal; pin id is already typed.)*
- [ ] 3.5 Emit `template <PeripheralId I, SignalId S, PinId P>
      constexpr auto route_for() noexcept` resolving from
      `kRoutes` at compile time via a `consteval` lookup.
      *(Awaits the typed PeripheralId / SignalId surface — once
      `peripheral_traits.h` ships those enums, the template
      lands here.)*
- [ ] 3.6 Emit `template <PinId P> constexpr PinConstraints
      constraints_of() noexcept` from `device.pinout[*].constraints`.
- [ ] 3.7 STM32 alternate-pin annotation (`PA12 [PA10]`) emits a
      `kAlternateRoutes` runtime table and exposes
      `pin_route_lookup(PeripheralId, SignalId, PinId)` for chips
      where the IR marks routes as runtime-resolvable.
      *(Synthesised `PinRoute.alternate_pin` already round-trips;
      the runtime fallback table lands when the typed accessor
      from §3.5 is in.)*

## 4. Wire-up

- [x] 4.1 Register `_EmitterEntry(name="pin_router",
      filename="pins.h", fn=emit_pin_router)` in
      `cli.py::_EMITTERS` and `entrypoint.py::_EMITTERS`.
- [ ] 4.2 Update `cli.py` `--list` and `--emit` documentation to
      mention the new artifact.
      *(``--emit`` already auto-discovers the entry; ``--list``
      docstring update is a tiny follow-up.)*
- [x] 4.3 Update `pyproject.toml` if any new optional deps are
      pulled in (none expected).

## 5. Tests

- [x] 5.1 Unit tests for the `PinmuxBackend` adapter — synthetic
      `PinOptionFixed` payloads via the live STM32G0 corpus; assert
      encoded `PinRoute`.  *(8 tests in `tests/test_pin_router.py`;
      SAM/RP/ESP follow when those backends land.)*
- [x] 5.2 Unit tests for `emit_pin_router` shape (header guard,
      `pin::id` enum, route count matches synthesised count,
      banner declares the schema id, deterministic).
- [ ] 5.3 Add `pins.h` to the existing per-device golden suite
      under `tests/fixtures/emitted/<vendor>/<family>/<chip>/pins.h`
      for every admitted device.
- [ ] 5.4 Add a smoke test that compiles `pins.h` against a
      stub `alloy::device::types` namespace using the project's
      existing arm-none-eabi smoke harness.
- [x] 5.5 Update `test_entrypoint.py` to assert `pins.h` is in the
      written-files set.

## 6. Documentation

- [ ] 6.1 Add a "Pin routing" section to `CONTRIBUTING_DEVICES.md`
      explaining how to verify a new chip's `pin_options`
      round-trips through the chosen `PinmuxBackend`.
- [ ] 6.2 Add a `docs/pin_router_contract.md` (or update
      `runtime-lite-contract` design notes) documenting the
      `pins.h` shape so alloy HAL contributors can rely on it.
