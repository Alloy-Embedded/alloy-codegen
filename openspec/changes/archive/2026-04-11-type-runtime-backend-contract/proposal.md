## Why

The current `alloy-devices` contract still leaks too much interpretation work into the
runtime. The generated artifacts expose route targets, pinmux operations, clock enables, and
register access patterns with stringly-typed fields. The Alloy runtime is then forced to:

- detect families manually
- parse strings such as `RCC_APBENR1.USART2EN` or `pinmux.PA2`
- hardcode register offsets that should come from upstream source data

That scales poorly across vendors and families, and it undermines the goal that
`alloy-codegen` should own hardware facts while `alloy` owns behavior.

## What Changes

- Add explicit backend schema identifiers to canonical IP blocks and peripheral instances.
- Add normalized register descriptors to the canonical IR, sourced from SVD/ATDF upstream data.
- Replace string-only route operations with typed runtime operations that carry schema and
  register references.
- Emit runtime-facing generated headers for:
  - backend/runtime profiles
  - peripheral instances
  - typed register maps with register offsets
- Harden validation and publication so foundational families cannot publish with
  legacy-only runtime contract gaps.

## Impact

- Affected specs:
  - `canonical-device-ir`
  - `artifact-contract`
  - `validation-and-gates`
  - `codegen-alloy-boundary`
- Affected code:
  - `src/alloy_codegen/sources/*`
  - `src/alloy_codegen/ir/model.py`
  - `src/alloy_codegen/stages/normalize.py`
  - `src/alloy_codegen/connector_model.py`
  - `src/alloy_codegen/emission.py`
  - `src/alloy_codegen/validation.py`
  - `tests/*`
