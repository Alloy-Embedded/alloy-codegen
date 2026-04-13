## Why

`alloy-devices` already publishes typed DMA bindings, but the hot-path runtime contract still
stops short of a usable DMA driver boundary. The missing pieces are:

- no `generated/runtime/devices/<device>/dma_bindings.hpp`
- no `generated/runtime/devices/<device>/driver_semantics/dma.hpp`
- no numeric DMA route metadata for schemas that require mux request values or controller-side
  selectors

That keeps Alloy DMA on a partial contract while `gpio`, `uart`, `i2c`, and `spi` already moved
to runtime-lite semantics.

## What Changes

- extend canonical DMA route metadata with typed numeric facts needed by the driver hot path
- publish runtime-lite DMA bindings under `generated/runtime/devices/<device>/dma_bindings.hpp`
- publish typed DMA driver semantics under
  `generated/runtime/devices/<device>/driver_semantics/dma.hpp`
- require foundational families with DMA bindings to publish that contract before release

## Impact

- Alloy can rebuild DMA on the same runtime-lite boundary as the other foundational drivers
- ST `stm32g0` and `stm32f4` stop depending on implicit DMA mux/channel knowledge outside the
  contract
- SAME70 XDMAC gets a typed request-value path instead of ad hoc parsing in the runtime
