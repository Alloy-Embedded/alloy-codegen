## Why

The current generated C++ contract is now typed, but it still follows the wrong runtime shape.
`alloy-devices` publishes large family-level tables such as connector graphs, clock maps, and
register field inventories, and the `alloy` runtime currently consumes those tables through
lookup-style helper code.

That is acceptable for reflection, validation, tooling, and smoke checks, but it is the wrong
shape for the final runtime path. The production runtime must not pay for:

- linear scans over generated tables
- large `std::span`-backed descriptor sets in the hot path
- string or id lookups that exist only to rediscover a compile-time fact
- unnecessary flash or compile-time bloat compared with direct register use

We need to split the generated outputs into two explicit contracts:

- a **reflection contract** for tooling, validation, and inspection
- a **runtime-lite contract** for zero-overhead runtime consumption

## What Changes

- **NEW** define a `runtime-lite` generated contract optimized for compile-time consumption
- **NEW** keep the current table-rich generated outputs as a separate `reflection` contract
- **BREAKING** require that runtime-owned use cases be expressible from generated type aliases,
  traits, `constexpr` packs, and template specializations instead of family-wide lookup tables
- **NEW** emit per-instance and per-route generated constructs that let `alloy` compile down to
  direct register operations with no runtime descriptor walks
- **NEW** add publication gates proving that foundational families provide the runtime-lite
  contract without forcing the runtime to include reflection tables

## Impact

- Affected specs:
  - `artifact-contract`
  - `codegen-alloy-boundary`
  - `validation-and-gates`
  - `vendor-admission`
  - `runtime-lite-contract`
- Affected code:
  - `src/alloy_codegen/emission.py`
  - canonical IR lowering and any supporting helper modules
  - publish and validation stages
  - foundational emitted fixtures
- Breaking impact:
  - runtime-facing headers in `alloy-devices` gain a new contract split
  - `alloy` should stop consuming family-wide reflection tables in its hot path
