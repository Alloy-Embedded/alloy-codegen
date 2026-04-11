## Why

The current canonical IR and emitted artifacts are strong enough for bootstrap publication, but
they are still centered on a simplified `pin -> signal -> optional af_number` model. That is too
weak for the Alloy direction we already chose:

- generic compile-time-safe `connect()` behavior implemented in Alloy
- descriptor-first generated artifacts in `alloy-devices`
- the same architectural contract across ST, Microchip, and NXP before vendor 4

That simplified model is already under pressure:

- STM32 mostly fits an AF-centric representation, but the final contract needs more than AF
  numbers once package variants, capabilities, and startup descriptors become first-class
- Microchip SAME70 needs route facts that look more like matrix/PIO configuration than simple
  alternate functions
- NXP i.MX RT needs mux selectors, input daisy selectors, and pad-level routing facts that do not
  fit cleanly in `af_number`

If we continue growing vendor support on the bootstrap model, we will lock in STM32-shaped
assumptions and then have to re-open the whole pipeline later. This change moves the codegen to
the real target-state model now.

## What Changes

- **BREAKING** Refactor the canonical IR from an AF-centric pin model to a route-driven connector
  model built around `ConnectionCandidate`, `ConnectionGroup`, `RouteOperation`, and
  `RouteRequirement`
- Add explicit `ip_blocks` and capability descriptors keyed by `ip_name + ip_version`, separate
  from peripheral instances
- Add full package/pin topology modeling, including package pads, physical pin positions, and pin
  constraints
- Add complete system descriptor domains:
  - interrupt and vector descriptors
  - memory and startup descriptors
  - clock/reset/enable descriptors
  - DMA routing descriptors
- Define the final artifact families needed for the future Alloy runtime:
  - connector tables
  - IP-version descriptors
  - interrupt/memory/package/clock maps
  - startup descriptors separated from startup logic
- Lock the `alloy-codegen -> alloy-devices -> alloy` boundary for `connect()`:
  - codegen emits facts and descriptors
  - Alloy implements runtime `connect()` behavior, ownership, and policies
- Require ST, Microchip, and NXP to converge on the same descriptor contract before vendor 4

## Impact

- Affected specs:
  - `canonical-device-ir`
  - `patch-and-normalization`
  - `validation-and-gates`
  - `artifact-emission`
  - `publication-workflow`
  - `codegen-alloy-boundary`
- Affected code:
  - `src/alloy_codegen/ir/`
  - `src/alloy_codegen/stages/normalize.py`
  - `src/alloy_codegen/validation.py`
  - `src/alloy_codegen/emission.py`
  - `src/alloy_codegen/stages/emit.py`
  - `src/alloy_codegen/stages/publish.py`
  - `schemas/`
  - vendor fixtures and golden artifacts
- Related active changes:
  - `define-codegen-target-state`
  - `add-microchip-dfp-family`
  - `add-nxp-mcux-family`
