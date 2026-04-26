# Tasks: Define PIO Semantic Struct Fields

## 1. Update PioSemanticTraits struct definition in alloy-codegen templates

- [ ] 1.1 Locate the C++ template emitter for `pio.hpp` in
      `src/alloy_codegen/emitters/` (or `runtime_lite_emission.py`). Extend the
      base template to include all new fields with zero defaults:
      `kStateMachineCount`, `kInstructionMemoryDepth`, `kTxFifoDepth`,
      `kRxFifoDepth`, `kGpioBase`, `kGpioCount`, `kBaseAddress`, `kDreqTx`, `kDreqRx`.
- [ ] 1.2 Add the nested `StateMachineSemanticTraits<PioId, Sm>` template stub to
      the same emitter. Base template: all zero, `kPresent=false`.
- [ ] 1.3 Verify all existing goldens still compile: the new fields default to zero
      and do not break existing `kPresent=false` specializations.

## 2. IR model

- [ ] 2.1 Add `PioDescriptor` dataclass to `src/alloy_codegen/ir/model.py`:
      `pio_id: str`, `base_address: int`, `state_machine_count: int`,
      `instruction_memory_depth: int`, `tx_fifo_depth: int`, `rx_fifo_depth: int`,
      `gpio_base: int`, `gpio_count: int`, `dreq_tx_base: int`, `dreq_rx_base: int`.
- [ ] 2.2 Add `Device.pio_blocks: list[PioDescriptor] = []`. Existing fixtures pass.
- [ ] 2.3 Update JSON schema and round-trip tests.

## 3. RP2040 PIO data overlay

- [ ] 3.1 Create `patches/raspberrypi/rp2040/pio.json`:
      ```json
      {
        "pio_blocks": [
          { "pio_id": "Pio0", "base_address": "0x50200000",
            "state_machine_count": 4, "instruction_memory_depth": 32,
            "tx_fifo_depth": 4, "rx_fifo_depth": 4,
            "gpio_base": 0, "gpio_count": 30,
            "dreq_tx_base": 0, "dreq_rx_base": 4 },
          { "pio_id": "Pio1", "base_address": "0x50300000",
            "state_machine_count": 4, "instruction_memory_depth": 32,
            "tx_fifo_depth": 4, "rx_fifo_depth": 4,
            "gpio_base": 0, "gpio_count": 30,
            "dreq_tx_base": 8, "dreq_rx_base": 12 }
        ]
      }
      ```
- [ ] 3.2 Extend RP2040 normalizer in `src/alloy_codegen/sources/rp2040_sdk.py`
      (or equivalent) to load `pio.json` and populate `Device.pio_blocks`.

## 4. PIO semantic emitter for RP2040

- [ ] 4.1 Implement `PioSemanticEmitter.emit_rp2040(device)`:
      For each `PioDescriptor`, emit a `PioSemanticTraits<PioId::Pio0>` specialization
      with all fields populated.
- [ ] 4.2 For each state machine (0 to `state_machine_count - 1`), emit
      `StateMachineSemanticTraits<PioId::Pio0, 0>` through
      `StateMachineSemanticTraits<PioId::Pio1, 3>` with per-SM DREQ values
      (`dreq_tx_base + sm`, `dreq_rx_base + sm`).

## 5. Goldens and compile tests

- [ ] 5.1 Regenerate `tests/fixtures/emitted/rp2040/driver_semantics/pio.hpp`.
      Assert: `PioSemanticTraits<PioId::Pio0>::kStateMachineCount == 4`,
      `PioSemanticTraits<PioId::Pio0>::kInstructionMemoryDepth == 32`,
      `StateMachineSemanticTraits<PioId::Pio0, 3>::kDreqTx == 3`.
- [ ] 5.2 Compile test: `tests/compile_tests/test_rp2040_pio_traits.cpp`:
      ```cpp
      static_assert(PioSemanticTraits<PioId::Pio0>::kStateMachineCount == 4);
      static_assert(PioSemanticTraits<PioId::Pio1>::kBaseAddress == 0x50300000u);
      static_assert(StateMachineSemanticTraits<PioId::Pio1, 2>::kDreqTx == 10u);
      ```
- [ ] 5.3 Assert all non-RP2040 family goldens have `kStateMachineCount=0` on the
      base template (no regressions).

## 6. Documentation

- [ ] 6.1 Update `docs/COVERAGE_MATRIX.md`: add `pio_traits` column.
      RP2040=✓, all others=N/A.
- [ ] 6.2 Add comment in emitter: document why `kDreqTx` is the SM0 base
      (consumers add the SM index at compile time via `kDreqTx + sm_index`).
