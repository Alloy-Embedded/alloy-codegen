## ADDED Requirements

### Requirement: dma.hpp SHALL surface DMA controller hardware traits

The emitted `dma.hpp` SHALL extend every populated
`DmaControllerHwTraits<DmaControllerId>` specialization with:
channel count, max transfer count (NDTR width), supported burst
sizes, supported data widths, priority level count, and capability
flags `kSupportsCircular`, `kSupportsDoubleBuffer`,
`kSupportsMemToMem`, `kSupportsDescriptorChaining`,
`kSupportsByteSwap`, `kSupportsScatterGather`.  `0u` / empty
arrays / `false` on the unspecialized template.

#### Scenario: RP2040 DMA controller advertises 12 channels + byte-swap

- **WHEN** the pipeline emits `dma.hpp` for RP2040 rp2040
- **THEN** `DmaControllerHwTraits<DmaControllerId::DMA>::kChannelCount`
  equals `12u`
- **AND** `kSupportsByteSwap == true`
- **AND** `kSupportsScatterGather == true`
- **AND** `kSupportedBurstSizes.size() >= 1`

#### Scenario: STM32G0 DMA1 advertises 7 channels + 4 priority levels

- **WHEN** the pipeline emits `dma.hpp` for STM32G0 stm32g071rb
- **THEN** `DmaControllerHwTraits<DmaControllerId::DMA1>::kChannelCount`
  equals `7u`
- **AND** `kPriorityLevelCount == 4u`
- **AND** `kMaxTransferCount == 0xFFFFu`
- **AND** `kSupportsCircular == true`
- **AND** `kSupportsByteSwap == false`
