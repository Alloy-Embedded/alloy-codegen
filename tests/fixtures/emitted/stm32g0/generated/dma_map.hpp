#pragma once

namespace st {
namespace stm32g0 {
namespace generated {
struct DmaDescriptor {
  const char* peripheral;
  const char* signal;
  const char* controller;
  const char* request_line;
};
inline constexpr DmaDescriptor kDmaMap[] = {
  {"USART1", "RX", "DMA1", "DMA1_CH1"},
  {"USART1", "TX", "DMA1", "DMA1_CH2"},
};
}
}
}
