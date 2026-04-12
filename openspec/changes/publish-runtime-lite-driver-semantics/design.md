## Context

`runtime-lite` currently publishes neutral facts:
- instance ids and base addresses
- clock/reset bindings
- register ids and field ids
- route traits and typed route operations

That is enough for typed wiring and low-level execution, but not enough for driver backends. A
driver needs semantic groupings, not just inventories. For example, a UART backend needs "enable
field", "tx-enable field", "rx-enable field", "baud register", "tx-ready field", and "rx-ready
field". Those are semantic roles over raw register fields.

If Alloy derives those roles by handwritten conventions, it will embed per-schema knowledge in the
runtime and reintroduce scaling problems across many families and vendors.

## Goals

- publish a zero-overhead driver contract for foundational drivers on top of `runtime-lite`
- keep the contract fully typed and instance-safe
- let Alloy dispatch by `BackendSchemaId` and then consume generated semantic traits with no
  reflection-table scanning in the hot path
- ensure a new family that reuses an existing schema needs no runtime edits in Alloy

## Non-Goals

- publishing every possible peripheral-class semantic pack in one pass
- replacing reflection artifacts used by validation, debugging, or tooling
- generating high-level drivers in `alloy-devices`

## Design

### 1. Split Between Facts And Semantics

The published contract will have three layers:

1. Reflection contract
   - family-wide and device-wide tables for tooling, validation, and debugging
2. Runtime-lite fact contract
   - typed ids, routes, clocks, registers, fields
3. Runtime-lite driver semantic contract
   - schema-aware semantic traits used directly by foundational drivers

The new third layer is the missing piece.

### 2. Driver Semantic Traits

For each foundational driver class, the codegen SHALL emit schema-aware semantic traits under:

`generated/runtime/devices/<device>/driver_semantics/`

Required foundational packs:
- `gpio.hpp`
- `uart.hpp`
- `i2c.hpp`
- `spi.hpp`

These headers SHALL contain typed traits keyed by the runtime-lite ids already published.

Illustrative shape:

```cpp
template<PeripheralId Id>
struct UartSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr RegisterId kControlRegister = RegisterId::none;
  static constexpr FieldId kEnableField = FieldId::none;
  static constexpr FieldId kTxEnableField = FieldId::none;
  static constexpr FieldId kRxEnableField = FieldId::none;
  static constexpr RegisterId kBaudRegister = RegisterId::none;
  static constexpr FieldId kTxReadyField = FieldId::none;
  static constexpr FieldId kRxReadyField = FieldId::none;
};
```

Illustrative GPIO shape:

```cpp
template<PinId Id>
struct GpioSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr PeripheralId kPortPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr FieldId kModeField = FieldId::none;
  static constexpr FieldId kPullField = FieldId::none;
  static constexpr FieldId kOutputTypeField = FieldId::none;
  static constexpr FieldId kInputField = FieldId::none;
  static constexpr FieldId kOutputSetField = FieldId::none;
  static constexpr FieldId kOutputResetField = FieldId::none;
};
```

The exact field set can differ per driver, but every emitted semantic trait SHALL:
- use typed ids only
- be directly consumable by `if constexpr` schema dispatch
- avoid requiring the runtime to rediscover semantic roles from register names

### 3. Source Of Truth

Semantic roles SHALL be derived in codegen from:
- IP metadata already normalized in canonical IR
- curated schema knowledge owned by `alloy-codegen`
- patch-layer overrides where upstream naming is inconsistent

Emitters MUST NOT guess semantics by string slicing inside the final template stage. Semantic
assignment belongs in normalized model construction or a dedicated runtime-semantic enrichment
layer.

### 4. Validation And Publication

Publish SHALL fail when any foundational runtime-owned instance is missing the required semantic
trait pack for its driver class.

Examples:
- a `class_gpio` instance without `GpioSemanticTraits`
- a `class_uart` instance without `UartSemanticTraits`
- a routed `class_i2c*` instance without `I2cSemanticTraits`
- a routed `class_spi` instance without `SpiSemanticTraits`

### 5. Boundary

The boundary becomes explicit:
- reflection tables are not the normal driver dependency
- runtime-lite facts plus driver semantic traits are the hot-path contract
- Alloy MAY include reflection headers only for tooling, validation, or startup domains that do not
  participate in foundational driver hot paths

## Risks

- schema knowledge may initially require curated overrides for inconsistent vendors
- foundational families may temporarily fail publish until semantic coverage is complete
- emitter complexity increases, but that is preferable to pushing hardware conventions into Alloy

## Migration

1. emit driver semantic traits for foundational families already publishing runtime-lite
2. gate publish on foundational semantic completeness
3. migrate Alloy drivers to consume these traits
4. only then remove reflection-based driver bridges in Alloy
