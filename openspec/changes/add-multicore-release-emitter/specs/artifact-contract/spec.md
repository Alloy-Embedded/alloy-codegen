## ADDED Requirements

### Requirement: Published Artifact Tree SHALL Include `multicore_release.h` And `multicore_release.c`

The published artifact tree SHALL include the typed
runtime-lite pair `multicore_release.h` (declarations + table
extern) and `multicore_release.c` (table definition + release
function body) for every admitted device, single-core or
multicore.  Single-core devices SHALL receive a stub pair
declaring `ALLOY_MULTICORE_RELEASE_COUNT == 0`.

#### Scenario: Single-core STM32 G0 publishes a stub multicore_release pair

- **WHEN** alloy-codegen emits artifacts for
  `st/stm32g0/stm32g071rb`
- **THEN** the output tree contains
  `out/st/stm32g0/stm32g071rb/multicore_release.h` and
  `out/st/stm32g0/stm32g071rb/multicore_release.c`
- **AND** the header declares
  `#define ALLOY_MULTICORE_RELEASE_COUNT 0`
- **AND** the source defines a no-op
  `void alloy_multicore_release_core(uint8_t core_id) {(void)core_id;}`

#### Scenario: Future RP2040 publishes a populated multicore_release pair

- **WHEN** alloy-codegen emits artifacts for a (future-admitted)
  RP2040 device with `identity.multicore.cores[]` carrying
  core 0 and core 1
- **THEN** `multicore_release.h` declares
  `#define ALLOY_MULTICORE_RELEASE_COUNT 2`
- **AND** `multicore_release.c` populates
  `alloy_multicore_release_table[]` with two rows whose
  `release_register_addr`, `release_value`, `vector_base_addr`
  match the IR

### Requirement: `multicore_release.c` Body SHALL Be Vendor-Agnostic

The published `multicore_release.c` body SHALL contain no
per-vendor `#ifdef VENDOR_X` block.  Per-vendor release
protocol differences (Cortex-M `RCC.GCR.BOOT_C2`, RP2040 SIO
FIFO, iMX RT CCM_SRC, ESP32 RTC_CNTL) SHALL be expressed
through the typed `ReleaseOpKind` enum and the
`release_register_addr`/`release_value`/`release_mask` triple
on each `MulticoreCore` IR entry.

#### Scenario: Source has no #ifdef on vendor

- **WHEN** the pre-publication content gate scans
  `out/<vendor>/<family>/<chip>/multicore_release.c`
- **THEN** the gate finds no `#if defined(STM32` or
  `#ifdef RP2040` or `#if ESP32` patterns
- **AND** the function body switches on `core_id` only

### Requirement: `multicore_release.{c,h}` SHALL Stay Zero-String

`multicore_release.h` and `multicore_release.c` SHALL contain
no semantic `const char*` field; all references SHALL be
encoded as enums, ids, integers, masks, or function pointers
per the existing zero-string artifact-contract rule.

#### Scenario: Zero-string gate passes after multicore_release lands

- **WHEN** the pre-publication zero-string gate scans
  `out/<vendor>/<family>/<chip>/multicore_release.{c,h}` after
  this proposal's emitter changes
- **THEN** the gate finds no semantic string literal in any
  table row or function body

## MODIFIED Requirements

### Requirement: Runtime Maps and Bindings SHALL Use Typed IDs Only

Family maps and device-scoped bindings SHALL use typed ids only for runtime relationships.
This SHALL include the new `multicore_release.h` runtime-lite header.

#### Scenario: Alloy consumes peripheral, interrupt, DMA, pin, package, and multicore-release bindings

- **WHEN** the runtime reads `rcc_map.hpp`, `interrupt_map.hpp`, `dma_map.hpp`, `pins.h`,
  `package_map.hpp`, `multicore_release.h`, or device-scoped binding headers
- **THEN** those relationships are encoded with typed ids or refs
- **AND** no semantic string parsing is required

#### Scenario: Multicore release table resolves via typed enums only

- **WHEN** alloy HAL calls `alloy_multicore_release_core(1)`
  on a future-admitted RP2040 device
- **THEN** the table lookup uses `core_id`, `role_kind`,
  `release_op_kind` typed enums
- **AND** the call requires no string label and no `const char*`
  field
