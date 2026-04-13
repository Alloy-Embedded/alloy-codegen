## 1. Spec and IR

- [x] 1.1 Add this DMA runtime-lite driver-semantics change
- [x] 1.2 Extend canonical DMA descriptors with optional numeric route metadata
- [x] 1.3 Extend patch parsing/normalization to accept and publish that metadata

## 2. Runtime-Lite DMA Contract

- [x] 2.1 Emit `generated/runtime/devices/<device>/dma_bindings.hpp`
- [x] 2.2 Emit `generated/runtime/devices/<device>/driver_semantics/dma.hpp`
- [x] 2.3 Include DMA/DMA-router runtime-owned facts in the runtime-lite closure when needed

## 3. Foundational Coverage

- [x] 3.1 Publish STM32G0 DMA mux request values
- [x] 3.2 Publish STM32F4 DMA channel-selector values
- [x] 3.3 Publish SAME70 XDMAC request values
- [x] 3.4 Keep IMXRT1060 publishable with an empty-but-valid DMA semantic pack when no bindings exist

## 4. Gates and Docs

- [x] 4.1 Update runtime-lite contract verification and smoke coverage
- [x] 4.2 Update artifact-layout / boundary docs
- [x] 4.3 Regenerate affected emitted fixtures
- [x] 4.4 Validate with `python3 -m ruff check src tests`
- [x] 4.5 Validate with `python3 -m pytest tests -q`
- [x] 4.6 Validate with `openspec validate publish-runtime-lite-dma-driver-semantics --strict`
