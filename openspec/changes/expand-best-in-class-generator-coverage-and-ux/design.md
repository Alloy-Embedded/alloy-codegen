## Overview

This change is intentionally a follow-up to `build-best-in-class-generator-core`.

It assumes the generator already has:

- strong system-control semantics
- formal capabilities
- provenance and explainability
- strong validation gates

With that foundation in place, this change addresses the remaining "coverage and adoption moat".

It has two pillars:

1. broader peripheral coverage
2. user-facing configuration and onboarding UX

## 1. Broader Peripheral Coverage

### Coverage waves

Coverage should expand in staged waves, not in one unbounded implementation.

#### Wave 1

- CAN / FDCAN
- watchdog as a public driver contract
- RTC
- advanced timer modes:
  - capture
  - compare
  - encoder

#### Wave 2

- USB device/host facts
- ETH facts
- QSPI / OSPI
- SDMMC

#### Wave 3

- low-power / wakeup / backup-domain contracts
- deeper power-state and sleep-entry recipes

### Contract expectations

Each new peripheral family must follow the same rules as the current runtime contract:

- device-scoped
- typed
- no runtime reflection dependency
- formal capability coverage
- DMA compatibility where applicable

## 2. User-Facing Configuration and UX

### Declarative configuration

The generator should grow a declarative configuration layer for board/device recipes.

This layer is expected to express intents such as:

- desired system clock profile
- selected peripheral instances
- requested routes/pins
- requested DMA use
- requested example or board recipe outputs

### Explainable conflict resolution

The UX layer must be able to explain:

- why a configuration is valid
- why it is invalid
- what conflicts exist
- what the nearest valid alternatives are

### Onboarding outputs

The generator should publish user-facing artifacts such as:

- board/profile recipes
- example-ready peripheral setups
- capability summaries
- compatibility matrices

These outputs should be layered on top of the runtime contract instead of inventing a second
device model.

## Dependency

This change intentionally depends on the core moat work being in place first.

Without the core change, broader coverage and UX would scale poorly and would likely reintroduce
heuristics or handwritten glue.

