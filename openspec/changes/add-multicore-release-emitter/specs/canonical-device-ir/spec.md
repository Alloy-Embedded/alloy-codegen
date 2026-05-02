## ADDED Requirements

### Requirement: Canonical IR `Multicore` Block SHALL Be Fully Populated For Multicore Chips

The canonical IR loader SHALL refuse to admit a multicore device whose
`device.identity.multicore` block is partially populated; every
entry in `Multicore.cores[*]` SHALL carry `id`, `role`,
`vector_base`, `release_register`, `release_op`,
`start_vector_symbol`, and `app_cpu` when the parent block is
non-`None`.

#### Scenario: Partial Multicore block refuses to load

- **WHEN** a YAML carries
  `identity.multicore.cores[1]: {id: 1, role: app}` without
  `release_register` or `start_vector_symbol`
- **THEN** the loader raises `ConfigError` naming the offending
  core entry and the missing fields

#### Scenario: Single-core devices keep `multicore: None`

- **WHEN** alloy-codegen loads a single-core device
- **THEN** `device.identity.multicore` is `None`
- **AND** the loader does not require any `MulticoreCore` fields

### Requirement: Canonical IR `MulticoreCore.role` SHALL Be A Typed Enum

The canonical IR `MulticoreCore.role` field SHALL be a typed
enum `MulticoreRole ∈ {Boot, App, Coprocessor}` rather than a
free-form string.  Legacy YAML carriage of `role: "boot"` |
`"app"` | `"coprocessor"` SHALL be lifted to the enum at load
time.

#### Scenario: Boot core role lifts to MulticoreRole.Boot

- **WHEN** a YAML carries
  `identity.multicore.cores[0].role: "boot"`
- **THEN** `device.identity.multicore.cores[0].role` is
  `MulticoreRole.Boot` (typed enum value)
- **AND** the loader rejects unknown role strings with
  `ConfigError`

### Requirement: Canonical IR `MulticoreCore.release_op` SHALL Be A Typed Enum

The canonical IR `MulticoreCore.release_op` field SHALL be a
typed enum `ReleaseOpKind ∈ {WriteValue, WriteMask, Mailbox}`
distinguishing the three release-protocol shapes Alloy supports
across vendors.  Each `release_op` value SHALL imply a
well-defined runtime sequence the emitter can lower without
per-vendor branches.

#### Scenario: STM32 H745 release_op is WriteValue

- **WHEN** a (future-admitted) STM32 H745 YAML carries
  `release_op: write_value` for core 1
- **THEN** `device.identity.multicore.cores[1].release_op` is
  `ReleaseOpKind.WriteValue`
- **AND** the emitter lowers it to a single
  `*release_register_addr = release_value` write

#### Scenario: RP2040 release_op is Mailbox

- **WHEN** a (future-admitted) RP2040 YAML carries
  `release_op: mailbox` for core 1 with the FIFO handshake
  sequence in `release_value`
- **THEN** `device.identity.multicore.cores[1].release_op` is
  `ReleaseOpKind.Mailbox`
- **AND** the emitter lowers it to the SIO_FIFO_WR handshake
  loop

### Requirement: Canonical IR `MulticoreCore` SHALL Carry A Typed Stack Region Reference

The canonical IR `MulticoreCore` SHALL carry a
`stack_region_id: MemoryRegionId` reference naming the canonical
`MemoryRegion.id` hosting that core's stack, so the linker-script
emitter can locate the stack without pattern-matching on the
region's label.

#### Scenario: Future STM32 H745 carries stack_region_id per core

- **WHEN** a (future-admitted) STM32 H745 YAML carries
  `cores[0].stack_region_id: dtcm`,
  `cores[1].stack_region_id: sram_bank4`
- **THEN** the emitter resolves both regions through
  `device.memory[*]` lookup
- **AND** the linker script emits
  `core_0_stack_top = ORIGIN(dtcm) + LENGTH(dtcm);` and
  `core_1_stack_top = ORIGIN(sram_bank4) + LENGTH(sram_bank4);`
- **AND** no string pattern-match on `sram_bank4`/`sram_bank5`
  appears in `linker_script.py`
