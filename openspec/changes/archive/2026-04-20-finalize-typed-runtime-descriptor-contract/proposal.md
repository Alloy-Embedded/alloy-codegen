## Why

The current runtime-facing contract is good enough to remove family switches from the first
Alloy backends, but it is not yet strong enough to be the long-term boundary between
`alloy-devices` and `alloy`.

Important parts of the emitted contract still rely on strings and CSV payloads:
- route operations still carry textual `target` and `value`
- connector and clock artifacts still expose CSV lists instead of typed bindings
- interrupt, DMA, and selector bindings are not fully modeled as typed descriptors
- register offsets are emitted, but field and bit-range descriptors are not yet available

If Alloy starts migrating heavily on top of this partially typed contract, it will replace
vendor glue with schema glue that still depends on string parsing and handwritten register
field knowledge. That is not acceptable for a runtime that must scale across many families
and vendors.

## What Changes

- Finalize the runtime descriptor contract around typed IDs and typed references instead of
  string parsing.
- Extend the canonical IR with normalized register field descriptors and typed system
  bindings for clock, reset, interrupt, DMA, and pinmux operations.
- Emit device-scoped C++ headers that let Alloy resolve peripherals, registers, fields, and
  bindings without vendor/family inference.
- Replace CSV-style connector, clock, and binding payloads with structured arrays and
  identifier references.
- Add publication gates that block families whose runtime-owned schemas still require string
  interpretation or handwritten register/field data in Alloy.

## Impact

- Affected specs:
  - `canonical-device-ir`
  - `artifact-contract`
  - `validation-and-gates`
  - `codegen-alloy-boundary`
  - `vendor-admission`
- Affected code:
  - raw-source extraction and normalization
  - connector enrichment and typed operation modeling
  - C++ emitters for runtime-facing descriptors
  - validation and publication gates
  - golden fixtures for foundational families
