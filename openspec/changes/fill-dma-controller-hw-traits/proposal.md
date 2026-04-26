# Fill DMA Controller HW Traits

## Why

`DmaSemanticTraits<Peripheral, Signal>` (the binding side) is
already deep — controller ID, channel index, request line, route ID,
conflict groups.  But the **controller-level** traits
(`DmaControllerHwTraits<DmaControllerId>`) are mostly stubbed:
`kChannelCount = 0`, `kMaxTransferCount = 0`,
`kSupportsChaining = false`, `kSupportsByteSwap = false`.

Async DMA-driven drivers in alloy need the controller surface to
size their pre-allocated descriptor pools and validate burst-size
choices.  modm exposes per-channel `Priority`, `BurstSize`, and
`TransferDirection` enums backed by controller-level capability
constants.

## What Changes

### IR plumbing

`DmaControllerDescriptor` already carries channel count via
`device.dma_controllers[*].channel_count` on RP2040 (12 channels).
For STM32, ESP32, iMXRT1060 the count is in the family overlay but
not surfaced into the trait.  Add patch fields if missing:

- `DmaBurstSizeOptionPatch` — `{controller, burst_bytes}`
- `DmaPriorityLevelsPatch` — `{controller, level_count}`
- `DmaModeFlagsPatch` extends with
  `supports_circular`, `supports_double_buffer`,
  `supports_mem_to_mem`, `supports_descriptor_chaining`,
  `supports_scatter_gather`

### Trait surface

`DmaControllerHwTraits<DmaControllerId>` gains:

- `kChannelCount` — populated from existing IR
- `kMaxTransferCount` — typically `0xFFFFu` on STM32 (16-bit NDTR)
- `kSupportedBurstSizes` — array of `{1, 4, 8, 16}` bytes
- `kSupportedDataWidths` — array of `{8, 16, 32}` bits
- `kPriorityLevelCount` — 4 on STM32, 16 on iMXRT eDMA
- Capability flags as listed above

### Per-family population

- STM32G0 — DMA1 (7 channels) + DMAMUX
- STM32F4 — DMA1 (8 streams) + DMA2 (8 streams)
- SAME70 — XDMAC (24 channels)
- iMXRT1060 — eDMA (32 channels) + DMAMUX
- RP2040 — DMA (12 channels, scatter-gather, byte-swap)
- ESP32 family — GDMA (per chip)

### Goldens

Regenerate every `dma.hpp` golden across all 9 families.

## Impact

Closes the controller-side of the DMA surface.  Combined with the
binding-side that already exists and the per-peripheral
back-references from `add-peripheral-dma-cross-references`, the
DMA story is complete.
