# Tasks — decode-zephyr-pinctrl-into-connection-candidates

## Phase 1: Decoder scaffolding

- [x] 1.1 New module `src/alloy_codegen/sources/zephyr_pinctrl.py`
      exposes `PinctrlAssignment` + `decode_pinctrl_for_node(...)`.
- [x] 1.2 `PinctrlAssignment(pin, peripheral, signal,
      af_number, route_kind)` — uniform shape across vendors.
- [x] 1.3 `PINCTRL_DECODERS: dict[str, Callable]` — `nordic`
      and `stm32` shipped; `nxp` placeholder raises
      `NotImplementedError` with a pointer to the follow-up
      change `nxp-zephyr-pinctrl-decoder`.

## Phase 2: Nordic decoder

- [x] 2.1 NRF_PSEL macro decoder: cell layout
      `(NRF_FUN_<fun> << 16) | (port << 5) | pin`.  Function
      map covers UART, SPIM, SPIS, TWIM, TWIS, PWM, SAADC.
- [x] 2.2 Pin name canonicalised as `P<port>_<pin:02d>` —
      Zephyr convention.
- [x] 2.3 Peripheral instance taken from the parent peripheral
      node's label (the `pinctrl-0` reference resolves through
      the phandle).
- [x] 2.4 `route_kind = "alternate-function"` so the existing
      `pin_validation.hpp` emitter picks up the records.

## Phase 3: STM32 decoder

- [x] 3.1 Accepts the structured-string form
      ``"PA9:USART1:TX:7"`` for fixtures + tests.  Real
      preprocessor-expanded numeric cells will land as a
      drop-in extension when the first STM32 admission goes
      through Zephyr DTS (today STM32 is admitted via
      stm32-open-pin-data, not Zephyr).

## Phase 4: Pipeline integration

- [x] 4.1 `_build_zephyr_dts_device_ir` walks every peripheral
      node's `pinctrl-0` phandle, calls
      `decode_pinctrl_for_node(...)`, and projects the
      assignments into `connection_candidates`.
- [x] 4.2 Pin definitions populated from the union of the
      assignments so `device.pins` is no longer empty for
      Zephyr-admitted devices.
- [x] 4.3 Reuses the existing `ConnectionCandidate` shape —
      the existing `emit-pinmux-validator-concepts` machinery
      picks up the records without any emitter changes.

## Phase 5: Fixture + tests

- [x] 5.1 Extended `tests/fixtures/zephyr-dts/nordic/nrf52840.dts`
      with UART0 + SPI0 + I2C0 pinctrl groups (NRF_PSEL
      macro-expanded to literal cells) wired via `pinctrl-0`
      phandles.
- [x] 5.2 Test asserting nRF52840 pipeline emits
      `pin_validation.hpp` with at least one
      `PinAssignmentValid<PinId::P0_06,
      PeripheralSignal::UART0_TX> : std::true_type`
      specialisation.
- [x] 5.3 Negative test: an unsupported pinctrl function index
      logs and skips rather than crashing the adapter.
- [x] 5.4 Cross-vendor test: STM32 decoder returns the same
      shape on a synthetic `"PA9:USART1:TX:7"` cell.

## Phase 6: Data repo update

- [x] 6.1 Re-emitted the canonical YAML for nrf52840 with the
      new connection_candidates and pushed to
      `alloy-devices-yml` (SHA `ab8f7bd`).  alloy-codegen
      submodule pin bumped.
- [x] 6.2 Loading the YAML through the consumer round-trips
      back to 7 connection_candidates + 7 pins.

## Phase 7: Spec + final checks

- [x] 7.1 Spec delta in `specs/vendor-admission/spec.md`.
- [x] 7.2 `openspec validate
      decode-zephyr-pinctrl-into-connection-candidates --strict`
      passes.
- [x] 7.3 13 new pinctrl tests pass.  `--runtime-cpp-smoke` is
      green for nRF52840 with the new `pin_validation.hpp`
      artifact (the smoke harness now compiles
      `nordic/nrf52/.../pin_validation.hpp` cleanly).
