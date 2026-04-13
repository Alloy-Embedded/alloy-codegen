## Overview

DMA needs one more layer than the existing foundational drivers because the hot path depends on
both controller-local facts and route-local numeric selectors. The runtime contract therefore
gains:

- typed DMA binding facts in the runtime namespace
- typed DMA semantic traits keyed by the published binding surface
- canonical numeric route metadata that does not force Alloy to infer mux values from names

## Contract Shape

### Canonical IR

The canonical DMA request/binding/route descriptors gain optional numeric fields:

- `channel_index`
- `request_value`
- `channel_selector`

These fields are omitted when genuinely not applicable.

The intent is:

- `channel_index`: fixed controller slot/stream/channel index when the route binds one
- `request_value`: numeric request source/peripheral id value programmed into a mux/controller
- `channel_selector`: extra controller-local selector such as STM32F4 `CHSEL`

### Runtime-Lite DMA Bindings

Each device publishes:

- `generated/runtime/devices/<device>/dma_bindings.hpp`

This header uses the runtime namespace and runtime `PeripheralId` / `SignalId`, and publishes:

- `DmaBindingId`
- `DmaControllerId`
- `DmaRequestLineId`
- `DmaRouteId`
- `DmaConflictGroupId`
- `DmaBindingDescriptor`
- `BindingTraits<PeripheralId, SignalId>`
- `ControllerTraits<DmaControllerId>`

### Runtime DMA Driver Semantics

Each device with DMA bindings publishes:

- `generated/runtime/devices/<device>/driver_semantics/dma.hpp`

This header exposes:

- `DmaSemanticTraits<PeripheralId, SignalId>`

The trait surface is schema-aware and typed. It includes:

- identity: binding/controller/route/conflict ids
- controller/router peripheral ids
- controller/router schema ids
- numeric route facts (`channel_index`, `request_value`, `channel_selector`)
- controller/router register and field refs needed for the foundational DMA hot path

The emitted refs may use fallback base+offset/bit metadata when the source fixture omits a
register block, but the semantic meaning must still be published in the contract.

## Foundational Family Requirements

The foundational DMA contract must cover:

- `st/stm32g0`: controller channel slot + DMAMUX request selector
- `st/stm32f4`: stream slot + `CHSEL`
- `microchip/same70`: XDMAC request/peripheral id value

If a foundational family has DMA bindings but cannot publish these semantics, publish must fail.

## Patch and Source Responsibilities

Structured sources remain authoritative when they provide the data. Patches are allowed to
supplement:

- missing controller/request numeric selectors
- missing register blocks and bitfields required by DMA semantics

The emitter must not reconstruct these values from string parsing in Alloy.
