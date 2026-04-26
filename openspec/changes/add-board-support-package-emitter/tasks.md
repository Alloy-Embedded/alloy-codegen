# Tasks — add-board-support-package-emitter

## Phase 1: Patch + IR plumbing

- [ ] 1.1 Add `BoardPatch` + `NamedPinPatch` + `ExternalOscillatorPatch`
      dataclasses to `patches.py`.  Add `_parse_board_patch` etc.
- [ ] 1.2 Add `BoardDescriptor` + `NamedPinDescriptor` +
      `ExternalOscillatorDescriptor` IR records in `ir/model.py`.
      Provenance per record.
- [ ] 1.3 Extend `CanonicalDeviceIR` with `boards: tuple[BoardDescriptor, ...] = ()`
      (or stand-alone, depending on how multi-board-per-device shakes
      out — single-device, multi-board is the common case).
- [ ] 1.4 New `load_board_patch(context, vendor, family, board_id)`
      loader walking `patches/<vendor>/<family>/boards/<board>.json`.
- [ ] 1.5 Validate `named_pins[*].pin` against the device's admitted
      `pin_definitions` at normalize time; emit `StageExecutionError`
      on mismatch.

## Phase 2: Emitter

- [ ] 2.1 New `emit_runtime_board_header(family_dir, board)` in
      `runtime_board_emission.py`.  Renders
      `<vendor>/<family>/generated/runtime/boards/<board_id>/board.hpp`.
- [ ] 2.2 Header structure:
      - `Leds` / `Buttons` structs grouping named pins by prefix
      - `DebugUart` / `DebugSpi` / `DebugI2c` when the board names
        a debug peripheral
      - Per-named-pin `static constexpr PinId kFoo = PinId::PA5;`
        + `kFooActiveHigh` polarity bool
      - `kDefaultClockProfile` constexpr
      - Re-include of `peripheral_instances.hpp` + `pins.hpp` so
        consumers get one-shot import
- [ ] 2.3 `static_assert(GpioSemanticTraits<PinId::PA5>::kPresent)`
      embedded for every named pin so typos fail at consumer
      `#include`-time, not later.

## Phase 3: Board catalog metadata

- [ ] 3.1 New `metadata/boards.json` artifact listing every admitted
      board globally:
      `[{board_id, device, vendor, family, package, summary}, ...]`
- [ ] 3.2 Sidecar entry on `metadata/devices/<device>.json` linking
      back to the boards that target this device.

## Phase 4: Bootstrap board files

Five seed boards proving the pipeline:

- [ ] 4.1 `patches/st/stm32g0/boards/nucleo-g071rb.json`
      (LED PA5 active-high, BUTTON PC13 active-low, ST-Link UART2)
- [ ] 4.2 `patches/st/stm32f4/boards/nucleo-f401re.json`
- [ ] 4.3 `patches/raspberrypi/rp2040/boards/pico.json`
      (LED GP25, no button, USB UART)
- [ ] 4.4 `patches/microchip/avr-da/boards/curiosity-nano-128da48.json`
- [ ] 4.5 `patches/microchip/same70/boards/atsame70-xpld.json`

## Phase 5: Tests + goldens

- [ ] 5.1 Per-board emit-fixture goldens under
      `tests/fixtures/emitted/<family>/.../boards/<board>/board.hpp`.
- [ ] 5.2 Regression test `test_board_header_resolves_named_pins`
      asserting NUCLEO-G071RB's `Leds::kGreen == PinId::PA5` and
      the embedded `static_assert` compiles via the smoke consumer.
- [ ] 5.3 Negative test: a board file referencing a non-existent
      pin raises `StageExecutionError` during normalize.

## Phase 6: Spec + final checks

- [ ] 6.1 Spec delta in `specs/artifact-contract/spec.md`.
- [ ] 6.2 `openspec validate add-board-support-package-emitter --strict`
      passes.
- [ ] 6.3 Full `pytest -q` + `ruff check` clean.
- [ ] 6.4 Archive entry notes that this matches modm's `<modm/board.hpp>`
      adoption pattern and unblocks `add-cli-project-bootstrap`
      (`alloy new --board nucleo-g071rb`).
