# Tasks — decode-zephyr-pinctrl-into-connection-candidates

## Phase 1: Decoder scaffolding

- [ ] 1.1 New module `src/alloy_codegen/sources/zephyr_pinctrl.py`
      exposing `decode_pinctrl(node, vendor) -> tuple[PinctrlAssignment, ...]`.
- [ ] 1.2 `PinctrlAssignment` dataclass: `(pin_name, peripheral,
      signal, af_number, route_kind)`.
- [ ] 1.3 `PINCTRL_DECODERS: dict[str, Callable]` registry —
      `nordic` + `stm32` shipped, `nxp` placeholder raises
      `NotImplementedError` with a clear pointer to the follow-up
      change.

## Phase 2: Nordic decoder

- [ ] 2.1 Parse `NRF_PSEL(<func>, <port>, <pin>)` macro
      invocations from the `psels` property.  Decode `<func>`
      via a curated map (`UART_TX → ("UART0", "TX")`,
      `SPI_SCK → ("SPI0", "SCK")`, …).
- [ ] 2.2 Compose pin name as `P<port>_<pin>` (Zephyr convention).
- [ ] 2.3 Map peripheral instance from the *enclosing* DTS
      label (the `pinctrl-0` reference points at a pin-state
      group whose parent is the peripheral node).
- [ ] 2.4 Emit `route_kind = "alternate-function"` so existing
      pin_validation.hpp emitter picks up the records.

## Phase 3: STM32 decoder

- [ ] 3.1 Parse `<STM32_PINMUX 'PA9', AF7_USART1>` style cells.
      The structure is two-element: `(pin_label, af_constant)`.
- [ ] 3.2 Extract the AF number from the constant suffix
      (e.g. `AF7_USART1` → `7`, peripheral=`USART1`).
- [ ] 3.3 Same `(pin, peripheral, signal, af_number,
      route_kind="alternate-function")` shape as Nordic.

## Phase 4: Pipeline integration

- [ ] 4.1 In `_build_zephyr_dts_device_ir`, after extracting
      peripherals + interrupts, walk every pinctrl group and
      call `decode_pinctrl(...)`.
- [ ] 4.2 Project the decoded assignments into IR
      `connection_candidates` tuple via the existing
      `ConnectionCandidate` dataclass (re-using
      `connector_model.assemble_connection_candidates(...)` if
      possible).
- [ ] 4.3 Pin definitions populated from the union of pinctrl
      pins so `device.pins` is no longer empty for Zephyr-admitted
      devices.

## Phase 5: Fixture + tests

- [ ] 5.1 Extend `tests/fixtures/zephyr-dts/nordic/nrf52840.dts`
      with a UART0 pinctrl group:
      `&uart0 { pinctrl-0 = <&uart0_default>; ... };`
      `&pinctrl { uart0_default { psels = <NRF_PSEL(UART_TX, 0, 6)>; ... }; };`.
- [ ] 5.2 Test asserting nRF52840 pipeline now emits
      `pin_validation.hpp` with at least one
      `PinAssignmentValid<PinId::P0_06, PeripheralSignal::UART0_TX>
      : std::true_type` specialisation.
- [ ] 5.3 Negative test: an unsupported pinctrl encoding logs
      and skips rather than crashing the adapter.
- [ ] 5.4 Cross-vendor test: STM32-pinctrl decoder returns the
      same shape on a synthetic STM32 DTS fragment.

## Phase 6: Spec + final checks

- [ ] 6.1 Spec delta in `specs/vendor-admission/spec.md`.
- [ ] 6.2 `openspec validate
      decode-zephyr-pinctrl-into-connection-candidates --strict`
      passes.
- [ ] 6.3 `pytest -q` + `ruff check` clean.
- [ ] 6.4 `--runtime-cpp-smoke` green for nRF52840 with the new
      `pin_validation.hpp` artifact.
