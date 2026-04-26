# Define PIO Semantic Struct Fields

## Why

`pio.hpp` is generated for every device but the `PioSemanticTraits<PioId>` struct
currently contains only `kPresent`. No meaningful fields are defined beyond that
sentinel, making the trait useless:

```cpp
// Current state — generated pio.hpp for rp2040:
template<> struct PioSemanticTraits<PioId::Pio0> {
    static constexpr bool kPresent = true;
    // ... nothing else
};
```

This blocks the alloy `add-gpio-hal` and `expand-driver-ecosystem` openspecs,
which need compile-time PIO information to implement:

1. **RP2040 PIO state machines** — the `PioStateMachine<PioId, SmId>` concept
   needs to know at compile time: how many state machines a PIO block has,
   the instruction memory depth, the FIFO depth, and which GPIO range can be
   driven by that PIO block.

2. **Compile-time program placement validation** — a PIO program of N instructions
   must fit in the 32-instruction instruction memory. The alloy concept check for
   a PIO driver requires `kInstructionMemoryDepth` to enforce this at compile time.

3. **Cross-family future use** — Espressif's RMT peripheral on ESP32-S3 and the
   SAME70's PWM peripheral with fine-grained timing share similar "programmable
   state machine" semantics. Defining the PIO trait vocabulary now avoids
   redesigning the struct when those families are admitted.

Only RP2040 has true PIO hardware today. All other families emit `kPresent=false`.

## What Changes

### `PioSemanticTraits<PioId>` struct extension

The struct gains the following fields (only meaningful when `kPresent=true`):

```cpp
template<PioId Id>
struct PioSemanticTraits {
    static constexpr bool kPresent = false;

    // Number of state machines in this PIO block.
    static constexpr std::uint8_t kStateMachineCount = 0;

    // Instruction memory depth in 32-bit words.
    static constexpr std::uint8_t kInstructionMemoryDepth = 0;

    // TX FIFO depth per state machine (words).
    static constexpr std::uint8_t kTxFifoDepth = 0;

    // RX FIFO depth per state machine (words).
    static constexpr std::uint8_t kRxFifoDepth = 0;

    // First GPIO pin index that this PIO block can control.
    static constexpr std::uint8_t kGpioBase = 0;

    // Number of contiguous GPIO pins this PIO block can control.
    static constexpr std::uint8_t kGpioCount = 0;

    // Base address of the PIO block.
    static constexpr std::uint32_t kBaseAddress = 0;

    // DMA DREQ for TX FIFO (used by DMA-driven PIO programs).
    static constexpr std::uint8_t kDreqTx = 0;

    // DMA DREQ for RX FIFO.
    static constexpr std::uint8_t kDreqRx = 0;
};
```

### RP2040 PIO0 and PIO1 specializations

RP2040 has two PIO blocks (PIO0 and PIO1), each with:
- 4 state machines (`kStateMachineCount = 4`).
- 32 instruction words (`kInstructionMemoryDepth = 32`).
- 4-word TX FIFO and 4-word RX FIFO per state machine
  (`kTxFifoDepth = 4`, `kRxFifoDepth = 4`; can be joined to 8 via SHIFTCTRL).
- Both PIO blocks can address all 30 GPIO pins on RP2040 (`kGpioBase=0`, `kGpioCount=30`).
- PIO0 base: `0x50200000`, PIO1 base: `0x50300000`.
- DREQ values from RP2040 datasheet Table 2-7:
  - PIO0_TX0=0, PIO0_TX1=1, PIO0_TX2=2, PIO0_TX3=3
  - PIO0_RX0=4, PIO0_RX1=5, PIO0_RX2=6, PIO0_RX3=7
  - PIO1_TX0=8, …, PIO1_RX3=15
  (Per-state-machine DREQs are parameterized; `kDreqTx` = base DREQ for SM0;
   `kDreqTx + sm_index` gives the DREQ for SM `sm_index`.)

### `StateMachineSemanticTraits<PioId, SmId>` (new nested struct)

For per-state-machine compile-time lookup without runtime indexing:

```cpp
template<PioId Pio, std::uint8_t Sm>
struct StateMachineSemanticTraits {
    static constexpr bool kPresent = false;
    static constexpr std::uint8_t kDreqTx = 0;
    static constexpr std::uint8_t kDreqRx = 0;
};
```

RP2040 emits specializations for `<Pio0, 0>` through `<Pio1, 3>`.

### IR model extension

`PioDescriptor` added to `CanonicalDeviceIR`:
- `pio_id`, `base_address`, `state_machine_count`, `instruction_memory_depth`,
  `tx_fifo_depth`, `rx_fifo_depth`, `gpio_base`, `gpio_count`,
  `dreq_tx_base`, `dreq_rx_base`.

RP2040 normalizer populates two `PioDescriptor`s from `patches/raspberrypi/rp2040/pio.json`.

## What Does NOT Change

- Families with `kPresent=false` — struct defaults ensure zero-cost when unused.
- The `PioId` enum layout — already generated, this change only fills the struct body.
- RMT / ESP32-S3 programmable peripheral support — deferred to a future openspec
  when ESP32-S3 is admitted as a full family.

## Alternatives Considered

**Leave PIO as `kPresent`-only until RP2040 full admission:** RP2040 is already
admitted. Its PIO hardware is working in alloy examples today. Leaving the trait
empty means the `complete-rp2040-semantics` openspec cannot deliver PIO concept
validation — the entire value proposition of alloy's PIO support is blocked.
