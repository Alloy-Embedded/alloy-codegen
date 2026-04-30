#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g030f6 {
enum class StartupMemoryRegionId : std::uint16_t {
  none,
  flash,
  sram,
};

enum class StartupSymbolId : std::uint16_t {
  none,
  DMA1_Channel1_IRQHandler,
  HardFault_Handler,
  NMI_Handler,
  PendSV_Handler,
  RCC_CRS_IRQHandler,
  Reserved_Handler_10,
  Reserved_Handler_12,
  Reserved_Handler_13,
  Reserved_Handler_4,
  Reserved_Handler_5,
  Reserved_Handler_6,
  Reserved_Handler_7,
  Reserved_Handler_8,
  Reserved_Handler_9,
  Reset_Handler,
  SVCall_Handler,
  SysTick_Handler,
  USART2_IRQHandler,
  __stack_top,
  _vectors,
};

enum class StartupDescriptorId : std::uint16_t {
  none,
  startup_copy_source_flash,
  startup_copy_target_sram,
  startup_stack_top,
  startup_vector_source_flash,
  startup_vectors,
  startup_zero_target_sram,
};

enum class InterruptBindingId : std::uint16_t {
  none,
  interrupt_binding_dma1_dma1_channel1,
  interrupt_binding_rcc_rcc_crs,
  interrupt_binding_usart2_usart2,
};

struct VectorSlotDescriptor {
  int slot;
  StartupSymbolId symbol_id;
  InterruptBindingId interrupt_binding_id;
  VectorKindId kind_id;
};
inline constexpr std::array<VectorSlotDescriptor, 19> kVectorSlots = {{
  {0, StartupSymbolId::__stack_top, InterruptBindingId::none, VectorKindId::vector_kind_initial_stack_pointer},
  {1, StartupSymbolId::Reset_Handler, InterruptBindingId::none, VectorKindId::vector_kind_reset_handler},
  {2, StartupSymbolId::NMI_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {3, StartupSymbolId::HardFault_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {4, StartupSymbolId::Reserved_Handler_4, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {5, StartupSymbolId::Reserved_Handler_5, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {6, StartupSymbolId::Reserved_Handler_6, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {7, StartupSymbolId::Reserved_Handler_7, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {8, StartupSymbolId::Reserved_Handler_8, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {9, StartupSymbolId::Reserved_Handler_9, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {10, StartupSymbolId::Reserved_Handler_10, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {11, StartupSymbolId::SVCall_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {12, StartupSymbolId::Reserved_Handler_12, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {13, StartupSymbolId::Reserved_Handler_13, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {14, StartupSymbolId::PendSV_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {15, StartupSymbolId::SysTick_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {20, StartupSymbolId::RCC_CRS_IRQHandler, InterruptBindingId::interrupt_binding_rcc_rcc_crs, VectorKindId::vector_kind_external_interrupt},
  {25, StartupSymbolId::DMA1_Channel1_IRQHandler, InterruptBindingId::interrupt_binding_dma1_dma1_channel1, VectorKindId::vector_kind_external_interrupt},
  {44, StartupSymbolId::USART2_IRQHandler, InterruptBindingId::interrupt_binding_usart2_usart2, VectorKindId::vector_kind_external_interrupt},
}};

struct StartupDescriptor {
  StartupDescriptorId descriptor_id;
  StartupKindId kind_id;
  StartupMemoryRegionId source_region_id;
  StartupMemoryRegionId target_region_id;
  StartupSymbolId symbol_id;
};
inline constexpr std::array<StartupDescriptor, 6> kStartupDescriptors = {{
  {StartupDescriptorId::startup_copy_source_flash, StartupKindId::startup_kind_copy_source_region, StartupMemoryRegionId::flash, StartupMemoryRegionId::none, StartupSymbolId::none},
  {StartupDescriptorId::startup_copy_target_sram, StartupKindId::startup_kind_copy_target_region, StartupMemoryRegionId::none, StartupMemoryRegionId::sram, StartupSymbolId::none},
  {StartupDescriptorId::startup_stack_top, StartupKindId::startup_kind_initial_stack_pointer, StartupMemoryRegionId::none, StartupMemoryRegionId::none, StartupSymbolId::__stack_top},
  {StartupDescriptorId::startup_vector_source_flash, StartupKindId::startup_kind_vector_source_region, StartupMemoryRegionId::flash, StartupMemoryRegionId::none, StartupSymbolId::none},
  {StartupDescriptorId::startup_vectors, StartupKindId::startup_kind_vector_table, StartupMemoryRegionId::none, StartupMemoryRegionId::none, StartupSymbolId::_vectors},
  {StartupDescriptorId::startup_zero_target_sram, StartupKindId::startup_kind_zero_target_region, StartupMemoryRegionId::none, StartupMemoryRegionId::sram, StartupSymbolId::none},
}};
}
}
}
}
}
}
