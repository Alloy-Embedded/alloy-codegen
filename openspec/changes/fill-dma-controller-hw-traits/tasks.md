# Tasks — fill-dma-controller-hw-traits

## Phase 1: Patch parser plumbing

- [ ] 1.1 Audit existing `DmaControllerDescriptor` — what's already
      in the IR vs what needs to be added.
- [ ] 1.2 Add patch dataclasses + parsers as needed:
      `DmaBurstSizeOptionPatch`, `DmaPriorityLevelsPatch`, extend
      `DmaModeFlagsPatch`.
- [ ] 1.3 Extend `DevicePatch` and `CanonicalDeviceIR`.

## Phase 2: Trait surface + safe defaults

- [ ] 2.1 Extend `DmaControllerHwRow` (or equivalent) with new
      fields.
- [ ] 2.2 `_dma_controller_hw_specialization_builder` emits new
      constexprs.
- [ ] 2.3 `default_lines` ships safe-falsy values.

## Phase 3: Per-family population

- [ ] 3.1 STM32G0 — DMA1 (7 channels, 4 priority levels, 16-bit
      NDTR, supports circular).
- [ ] 3.2 STM32F4 — DMA1/DMA2 (8 streams each, FIFO mode, burst,
      M2M, scatter-gather via SxFCR).
- [ ] 3.3 SAME70 — XDMAC (24 channels, full descriptor chaining,
      scatter-gather).
- [ ] 3.4 iMXRT1060 — eDMA (32 channels, 16 priorities, descriptor
      chaining via TCD).
- [ ] 3.5 RP2040 — DMA (12 channels, byte-swap, scatter-gather,
      sniff CRC).
- [ ] 3.6 ESP32 family — GDMA (per-chip channel counts).

## Phase 4: Tests + goldens

- [ ] 4.1 Per-family regression tests asserting `kChannelCount > 0`
      on every admitted controller.
- [ ] 4.2 RP2040 test: `kSupportsByteSwap == true`,
      `kChannelCount == 12`, `kSupportsScatterGather == true`.
- [ ] 4.3 Regenerate emit-fixture goldens.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/artifact-contract/spec.md`.
- [ ] 5.2 `openspec validate fill-dma-controller-hw-traits --strict`
      passes.
- [ ] 5.3 Full `pytest -q` + `ruff check` clean.
- [ ] 5.4 Archive entry notes that this completes the DMA
      semantic surface.
