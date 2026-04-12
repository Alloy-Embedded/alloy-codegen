## 1. OpenSpec

- [x] 1.1 Add artifact-contract deltas defining runtime-lite driver semantic traits
- [x] 1.2 Add validation deltas requiring foundational driver semantic completeness
- [x] 1.3 Add boundary deltas clarifying that foundational driver hot paths must not depend on reflection tables

## 2. IR And Enrichment

- [x] 2.1 Add an explicit runtime-semantic enrichment layer for foundational driver classes
- [x] 2.2 Model schema-aware semantic roles for `gpio`, `uart`, `i2c`, and `spi`
- [x] 2.3 Allow curated overrides where upstream metadata is insufficient

## 3. Emission

- [x] 3.1 Emit `generated/runtime/devices/<device>/driver_semantics/gpio.hpp`
- [x] 3.2 Emit `generated/runtime/devices/<device>/driver_semantics/uart.hpp`
- [x] 3.3 Emit `generated/runtime/devices/<device>/driver_semantics/i2c.hpp`
- [x] 3.4 Emit `generated/runtime/devices/<device>/driver_semantics/spi.hpp`
- [x] 3.5 Include the new driver semantic headers in runtime-lite consumer verification

## 4. Validation And Gates

- [x] 4.1 Fail validation when a foundational runtime-owned instance lacks required semantic traits
- [x] 4.2 Fail publish when foundational driver semantic coverage is incomplete
- [x] 4.3 Extend foundational-family regression coverage for semantic trait emission

## 5. Docs And Verification

- [x] 5.1 Update artifact layout and boundary docs for the new runtime-lite layer
- [x] 5.2 Add smoke coverage proving foundational semantic traits compile for ST, Microchip, and NXP
- [x] 5.3 Run `openspec validate publish-runtime-lite-driver-semantics --strict`
