## ADDED Requirements

### Requirement: Per-board BSP header SHALL surface named pins + default clock profile

The pipeline SHALL emit a `<vendor>/<family>/generated/runtime/boards/<board_id>/board.hpp` artifact for every admitted board, exposing the on-board pin functions (LEDs, buttons, debug UART, etc.) as typed `PinId` constexpr constants grouped by category, plus the default `ClockProfile` reference.  Each named pin SHALL embed a `static_assert(GpioSemanticTraits<PinId::*>::kPresent)` so consumer typos fail at `#include`-time.  The header SHALL re-export the device's `peripheral_instances.hpp` + `pins.hpp` so a single `#include "board.hpp"` is sufficient (matching the `<modm/board.hpp>` ergonomic).

#### Scenario: Nucleo-G071RB BSP exposes LED + button + debug UART

- **WHEN** the pipeline emits BSP artifacts for the Nucleo-G071RB board file
- **THEN** `st/stm32g0/generated/runtime/boards/nucleo-g071rb/board.hpp`
  SHALL contain `static constexpr PinId kGreen = PinId::PA5;` inside a
  `Leds` struct
- **AND** SHALL contain `static constexpr bool kGreenActiveHigh = true;`
- **AND** SHALL contain `static constexpr PinId kUser = PinId::PC13;`
  inside a `Buttons` struct with `kUserActiveHigh = false`
- **AND** SHALL contain a `DebugUart` struct exposing
  `kPeripheral == PeripheralId::USART2`, `kTxPin == PinId::PA2`,
  `kRxPin == PinId::PA3`
- **AND** SHALL embed `static_assert` calls for each named pin

### Requirement: Board catalog SHALL enumerate every admitted board

The pipeline SHALL emit a top-level `metadata/boards.json` artifact listing every admitted board globally with its `board_id`, `device`, `vendor`, `family`, `package`, and `summary`.  Each per-device sidecar `metadata/devices/<device>.json` SHALL list the boards that target the device under a `boards` field.

#### Scenario: Boards manifest enumerates Nucleo-G071RB

- **WHEN** the pipeline emits artifacts for any device that has at
  least one board file
- **THEN** `metadata/boards.json` SHALL contain an entry with
  `board_id == "nucleo-g071rb"`, `device == "stm32g071rb"`,
  `vendor == "st"`, `family == "stm32g0"`
- **AND** `metadata/devices/stm32g071rb.json` SHALL list
  `"nucleo-g071rb"` in its `boards` array

### Requirement: Board patches with invalid pin references SHALL fail at normalize time

Board files referencing pins that the device's admitted package does not expose SHALL raise a `StageExecutionError` during the normalize stage with a message identifying the offending `(board_id, named_pin, pin_name)` triple.  This is a hard-fail to prevent shipping a BSP header that would `static_assert` at the consumer's `#include`.

#### Scenario: Board file with non-existent pin fails normalize

- **WHEN** a board file declares a `named_pin` whose `pin` value is
  not in the device's admitted `pin_definitions`
- **THEN** the normalize stage SHALL raise `StageExecutionError`
- **AND** the error message SHALL include the board ID, the named
  pin label, and the unrecognised pin string
