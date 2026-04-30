#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
enum class StartupMemoryRegionId : std::uint16_t {
  none,
  APP_SECTION,
  EEPROM,
  INTERNAL_SRAM,
};

enum class StartupSymbolId : std::uint16_t {
  none,
  NMI_IRQHandler,
  RESET_IRQHandler,
  SPI0_INT_IRQHandler,
  TWI0_TWIM_IRQHandler,
  TWI0_TWIS_IRQHandler,
  USART0_DRE_IRQHandler,
  USART0_RXC_IRQHandler,
  USART0_TXC_IRQHandler,
  __stack_top,
  __vector_0,
  _vectors,
};

enum class StartupDescriptorId : std::uint16_t {
  none,
  startup_copy_source_app_section,
  startup_copy_target_internal_sram,
  startup_stack_top,
  startup_vector_source_app_section,
  startup_vectors,
  startup_zero_target_internal_sram,
};

enum class InterruptBindingId : std::uint16_t {
  none,
  interrupt_binding_spi0_spi0_int,
  interrupt_binding_twi0_twi0_twis,
  interrupt_binding_twi0_twi0_twim,
  interrupt_binding_usart0_usart0_rxc,
  interrupt_binding_usart0_usart0_dre,
  interrupt_binding_usart0_usart0_txc,
};

struct VectorSlotDescriptor {
  int slot;
  StartupSymbolId symbol_id;
  InterruptBindingId interrupt_binding_id;
  VectorKindId kind_id;
};
inline constexpr std::array<VectorSlotDescriptor, 9> kVectorSlots = {{
  {0, StartupSymbolId::__vector_0, InterruptBindingId::none, VectorKindId::vector_kind_reset_handler},
  {16, StartupSymbolId::RESET_IRQHandler, InterruptBindingId::none, VectorKindId::vector_kind_external_interrupt},
  {17, StartupSymbolId::NMI_IRQHandler, InterruptBindingId::none, VectorKindId::vector_kind_external_interrupt},
  {34, StartupSymbolId::USART0_RXC_IRQHandler, InterruptBindingId::interrupt_binding_usart0_usart0_rxc, VectorKindId::vector_kind_external_interrupt},
  {35, StartupSymbolId::USART0_DRE_IRQHandler, InterruptBindingId::interrupt_binding_usart0_usart0_dre, VectorKindId::vector_kind_external_interrupt},
  {36, StartupSymbolId::USART0_TXC_IRQHandler, InterruptBindingId::interrupt_binding_usart0_usart0_txc, VectorKindId::vector_kind_external_interrupt},
  {42, StartupSymbolId::TWI0_TWIS_IRQHandler, InterruptBindingId::interrupt_binding_twi0_twi0_twis, VectorKindId::vector_kind_external_interrupt},
  {43, StartupSymbolId::TWI0_TWIM_IRQHandler, InterruptBindingId::interrupt_binding_twi0_twi0_twim, VectorKindId::vector_kind_external_interrupt},
  {44, StartupSymbolId::SPI0_INT_IRQHandler, InterruptBindingId::interrupt_binding_spi0_spi0_int, VectorKindId::vector_kind_external_interrupt},
}};

struct StartupDescriptor {
  StartupDescriptorId descriptor_id;
  StartupKindId kind_id;
  StartupMemoryRegionId source_region_id;
  StartupMemoryRegionId target_region_id;
  StartupSymbolId symbol_id;
};
inline constexpr std::array<StartupDescriptor, 6> kStartupDescriptors = {{
  {StartupDescriptorId::startup_copy_source_app_section, StartupKindId::startup_kind_copy_source_region, StartupMemoryRegionId::APP_SECTION, StartupMemoryRegionId::none, StartupSymbolId::none},
  {StartupDescriptorId::startup_copy_target_internal_sram, StartupKindId::startup_kind_copy_target_region, StartupMemoryRegionId::none, StartupMemoryRegionId::INTERNAL_SRAM, StartupSymbolId::none},
  {StartupDescriptorId::startup_stack_top, StartupKindId::startup_kind_initial_stack_pointer, StartupMemoryRegionId::none, StartupMemoryRegionId::none, StartupSymbolId::__stack_top},
  {StartupDescriptorId::startup_vector_source_app_section, StartupKindId::startup_kind_vector_source_region, StartupMemoryRegionId::APP_SECTION, StartupMemoryRegionId::none, StartupSymbolId::none},
  {StartupDescriptorId::startup_vectors, StartupKindId::startup_kind_vector_table, StartupMemoryRegionId::none, StartupMemoryRegionId::none, StartupSymbolId::_vectors},
  {StartupDescriptorId::startup_zero_target_internal_sram, StartupKindId::startup_kind_zero_target_region, StartupMemoryRegionId::none, StartupMemoryRegionId::INTERNAL_SRAM, StartupSymbolId::none},
}};
}
}
}
}
}
}
