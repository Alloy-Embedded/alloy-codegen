## ADDED Requirements

### Requirement: Runtime-Lite Contract SHALL Expose `alloy_multicore_release_core`

The runtime-lite contract SHALL expose
`void alloy_multicore_release_core(uint8_t core_id)` defined
in `multicore_release.c`.  The function body SHALL look up the
matching descriptor in `alloy_multicore_release_table[]`,
program the descriptor's `vector_base` (where applicable),
and execute the descriptor's `release_op` against
`release_register_addr` with `release_value` masked by
`release_mask`.  The body SHALL emit a `__DSB(); __ISB();`
barrier pair after the release write.

#### Scenario: Future RP2040 release of core 1 follows the SIO FIFO protocol

- **WHEN** alloy HAL on a (future-admitted) RP2040 device calls
  `alloy_multicore_release_core(1)`
- **THEN** the function body looks up `core_id == 1` in
  `alloy_multicore_release_table[]`, programs the secondary
  core's vector base via `start_vector_symbol`, and executes
  the SIO FIFO handshake encoded in `release_op == Mailbox`
- **AND** the function returns once the secondary core
  reports it has booted

#### Scenario: Single-core invocation is a typed no-op

- **WHEN** consumer code on a single-core device calls
  `alloy_multicore_release_core(0)` defensively
- **THEN** the function returns immediately
- **AND** `ALLOY_MULTICORE_RELEASE_COUNT` is `0` so the body
  has no descriptor lookup to perform

### Requirement: Runtime-Lite Contract SHALL Document Multicore Release Ordering

The runtime-lite contract SHALL document that
`alloy_multicore_release_core(N)` for any `N > 0` MUST be
called only after the boot core has finished
`alloy_system_init()` and after the second-core stack
top has been written by the linker.  Calling the release
helper before the boot core's `Reset_Handler` returns is
undefined behavior; the documentation SHALL state this
explicitly.

#### Scenario: Release after system init succeeds

- **WHEN** consumer code calls
  `alloy_system_init()` followed by
  `alloy_multicore_release_core(1)` from `Reset_Handler`
- **THEN** the secondary core boots from
  `start_vector_symbol`
- **AND** clock setup, FPU, MPU, and NVIC priorities are
  already applied on the boot core before the release write
