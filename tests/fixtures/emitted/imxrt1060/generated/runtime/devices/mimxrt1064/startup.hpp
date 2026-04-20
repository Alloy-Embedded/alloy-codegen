#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
enum class StartupMemoryRegionId : std::uint16_t {
  none,
  OCRAM,
  FLASH,
};

enum class StartupSymbolId : std::uint16_t {
  none,
  BusFault_Handler,
  DebugMon_Handler,
  HardFault_Handler,
  LPI2C1_IRQHandler,
  LPSPI1_IRQHandler,
  LPUART1_IRQHandler,
  LPUART3_IRQHandler,
  MemManage_Handler,
  NMI_Handler,
  PendSV_Handler,
  Reserved_Handler_10,
  Reserved_Handler_13,
  Reserved_Handler_7,
  Reserved_Handler_8,
  Reserved_Handler_9,
  Reset_Handler,
  SVCall_Handler,
  SysTick_Handler,
  UsageFault_Handler,
  __stack_top,
  _vectors,
};

enum class StartupDescriptorId : std::uint16_t {
  none,
  startup_copy_source_flash,
  startup_copy_target_ocram,
  startup_stack_top,
  startup_vectors,
  startup_zero_target_ocram,
};

enum class InterruptBindingId : std::uint16_t {
  none,
  interrupt_binding_lpi2c1_lpi2c1,
  interrupt_binding_lpspi1_lpspi1,
  interrupt_binding_lpuart1_lpuart1,
  interrupt_binding_lpuart3_lpuart3,
};

struct VectorSlotDescriptor {
  int slot;
  StartupSymbolId symbol_id;
  InterruptBindingId interrupt_binding_id;
  VectorKindId kind_id;
};
inline constexpr std::array<VectorSlotDescriptor, 20> kVectorSlots = {{
  {0, StartupSymbolId::__stack_top, InterruptBindingId::none, VectorKindId::vector_kind_initial_stack_pointer},
  {1, StartupSymbolId::Reset_Handler, InterruptBindingId::none, VectorKindId::vector_kind_reset_handler},
  {2, StartupSymbolId::NMI_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {3, StartupSymbolId::HardFault_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {4, StartupSymbolId::MemManage_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {5, StartupSymbolId::BusFault_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {6, StartupSymbolId::UsageFault_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {7, StartupSymbolId::Reserved_Handler_7, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {8, StartupSymbolId::Reserved_Handler_8, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {9, StartupSymbolId::Reserved_Handler_9, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {10, StartupSymbolId::Reserved_Handler_10, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {11, StartupSymbolId::SVCall_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {12, StartupSymbolId::DebugMon_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {13, StartupSymbolId::Reserved_Handler_13, InterruptBindingId::none, VectorKindId::vector_kind_reserved},
  {14, StartupSymbolId::PendSV_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {15, StartupSymbolId::SysTick_Handler, InterruptBindingId::none, VectorKindId::vector_kind_system_exception},
  {36, StartupSymbolId::LPUART1_IRQHandler, InterruptBindingId::interrupt_binding_lpuart1_lpuart1, VectorKindId::vector_kind_external_interrupt},
  {38, StartupSymbolId::LPUART3_IRQHandler, InterruptBindingId::interrupt_binding_lpuart3_lpuart3, VectorKindId::vector_kind_external_interrupt},
  {44, StartupSymbolId::LPI2C1_IRQHandler, InterruptBindingId::interrupt_binding_lpi2c1_lpi2c1, VectorKindId::vector_kind_external_interrupt},
  {48, StartupSymbolId::LPSPI1_IRQHandler, InterruptBindingId::interrupt_binding_lpspi1_lpspi1, VectorKindId::vector_kind_external_interrupt},
}};

struct StartupDescriptor {
  StartupDescriptorId descriptor_id;
  StartupKindId kind_id;
  StartupMemoryRegionId source_region_id;
  StartupMemoryRegionId target_region_id;
  StartupSymbolId symbol_id;
};
inline constexpr std::array<StartupDescriptor, 5> kStartupDescriptors = {{
  {StartupDescriptorId::startup_copy_source_flash, StartupKindId::startup_kind_copy_source_region, StartupMemoryRegionId::FLASH, StartupMemoryRegionId::none, StartupSymbolId::none},
  {StartupDescriptorId::startup_copy_target_ocram, StartupKindId::startup_kind_copy_target_region, StartupMemoryRegionId::none, StartupMemoryRegionId::OCRAM, StartupSymbolId::none},
  {StartupDescriptorId::startup_stack_top, StartupKindId::startup_kind_initial_stack_pointer, StartupMemoryRegionId::none, StartupMemoryRegionId::none, StartupSymbolId::__stack_top},
  {StartupDescriptorId::startup_vectors, StartupKindId::startup_kind_vector_table, StartupMemoryRegionId::none, StartupMemoryRegionId::none, StartupSymbolId::_vectors},
  {StartupDescriptorId::startup_zero_target_ocram, StartupKindId::startup_kind_zero_target_region, StartupMemoryRegionId::none, StartupMemoryRegionId::OCRAM, StartupSymbolId::none},
}};
}
}
}
}
}
}
