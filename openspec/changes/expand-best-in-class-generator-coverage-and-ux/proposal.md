## Why

Once the core semantic and validation moat is in place, the remaining gap to "best in class" is
mostly breadth and user experience.

The generator still needs wider peripheral coverage and a clearer user-facing configuration layer
to beat vendor tooling in everyday adoption.

Those are important, but they should not block the core moat work.

## What Changes

- expand runtime driver coverage to the major remaining peripheral classes:
  - CAN/FDCAN
  - USB
  - ETH
  - RTC
  - QSPI/OSPI
  - SDMMC
  - watchdog as a public peripheral contract
  - advanced timer capture/compare/encoder features
  - low-power and wakeup controls
- add user-facing configuration and recipe surfaces on top of the typed runtime contract
- add generated examples, profile recipes, and richer onboarding artifacts

## Impact

- the generator covers a much larger share of real embedded products
- users can move from "runtime contract exists" to "I can configure and ship this MCU family"
- the project gains adoption leverage beyond architecture quality alone

