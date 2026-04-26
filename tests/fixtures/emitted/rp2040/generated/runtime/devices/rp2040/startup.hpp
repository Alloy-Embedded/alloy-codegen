#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
enum class StartupMemoryRegionId : std::uint16_t {
  none,
  XIP_FLASH,
  SRAM,
};

enum class StartupSymbolId : std::uint16_t {
  none,
  ADC_IRQ_FIFO_IRQHandler,
  CLOCKS_IRQ_IRQHandler,
  DMA_IRQ_0_IRQHandler,
  DMA_IRQ_1_IRQHandler,
  HardFault_Handler,
  I2C0_IRQ_IRQHandler,
  I2C1_IRQ_IRQHandler,
  IO_IRQ_BANK0_IRQHandler,
  NMI_Handler,
  PIO0_IRQ_0_IRQHandler,
  PIO0_IRQ_1_IRQHandler,
  PIO1_IRQ_0_IRQHandler,
  PIO1_IRQ_1_IRQHandler,
  PWM_IRQ_WRAP_IRQHandler,
  PendSV_Handler,
  RTC_IRQ_IRQHandler,
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
  SPI0_IRQ_IRQHandler,
  SPI1_IRQ_IRQHandler,
  SVCall_Handler,
  SysTick_Handler,
  TIMER_IRQ_0_IRQHandler,
  TIMER_IRQ_1_IRQHandler,
  TIMER_IRQ_2_IRQHandler,
  TIMER_IRQ_3_IRQHandler,
  UART0_IRQ_IRQHandler,
  UART1_IRQ_IRQHandler,
  USBCTRL_IRQ_IRQHandler,
  __stack_top,
  _vectors,
};

enum class StartupDescriptorId : std::uint16_t {
  none,
  startup_copy_source_xip_flash,
  startup_copy_target_sram,
  startup_stack_top,
  startup_vector_source_xip_flash,
  startup_vectors,
  startup_zero_target_sram,
};

enum class InterruptBindingId : std::uint16_t {
  none,
  interrupt_binding_adc_adc_irq_fifo,
  interrupt_binding_clocks_clocks_irq,
  interrupt_binding_dma_dma_irq_0,
  interrupt_binding_dma_dma_irq_1,
  interrupt_binding_i2c0_i2c0_irq,
  interrupt_binding_i2c1_i2c1_irq,
  interrupt_binding_io_bank0_io_irq_bank0,
  interrupt_binding_pio0_pio0_irq_0,
  interrupt_binding_pio0_pio0_irq_1,
  interrupt_binding_pio1_pio1_irq_0,
  interrupt_binding_pio1_pio1_irq_1,
  interrupt_binding_pwm_pwm_irq_wrap,
  interrupt_binding_rtc_rtc_irq,
  interrupt_binding_spi0_spi0_irq,
  interrupt_binding_spi1_spi1_irq,
  interrupt_binding_timer_timer_irq_0,
  interrupt_binding_timer_timer_irq_1,
  interrupt_binding_timer_timer_irq_2,
  interrupt_binding_timer_timer_irq_3,
  interrupt_binding_uart0_uart0_irq,
  interrupt_binding_uart1_uart1_irq,
  interrupt_binding_usbctrl_regs_usbctrl_irq,
};

struct VectorSlotDescriptor {
  int slot;
  StartupSymbolId symbol_id;
  InterruptBindingId interrupt_binding_id;
  VectorKindId kind_id;
};
inline constexpr std::array<VectorSlotDescriptor, 38> kVectorSlots = {{
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
  {16, StartupSymbolId::TIMER_IRQ_0_IRQHandler, InterruptBindingId::interrupt_binding_timer_timer_irq_0, VectorKindId::vector_kind_external_interrupt},
  {17, StartupSymbolId::TIMER_IRQ_1_IRQHandler, InterruptBindingId::interrupt_binding_timer_timer_irq_1, VectorKindId::vector_kind_external_interrupt},
  {18, StartupSymbolId::TIMER_IRQ_2_IRQHandler, InterruptBindingId::interrupt_binding_timer_timer_irq_2, VectorKindId::vector_kind_external_interrupt},
  {19, StartupSymbolId::TIMER_IRQ_3_IRQHandler, InterruptBindingId::interrupt_binding_timer_timer_irq_3, VectorKindId::vector_kind_external_interrupt},
  {20, StartupSymbolId::PWM_IRQ_WRAP_IRQHandler, InterruptBindingId::interrupt_binding_pwm_pwm_irq_wrap, VectorKindId::vector_kind_external_interrupt},
  {21, StartupSymbolId::USBCTRL_IRQ_IRQHandler, InterruptBindingId::interrupt_binding_usbctrl_regs_usbctrl_irq, VectorKindId::vector_kind_external_interrupt},
  {23, StartupSymbolId::PIO0_IRQ_0_IRQHandler, InterruptBindingId::interrupt_binding_pio0_pio0_irq_0, VectorKindId::vector_kind_external_interrupt},
  {24, StartupSymbolId::PIO0_IRQ_1_IRQHandler, InterruptBindingId::interrupt_binding_pio0_pio0_irq_1, VectorKindId::vector_kind_external_interrupt},
  {25, StartupSymbolId::PIO1_IRQ_0_IRQHandler, InterruptBindingId::interrupt_binding_pio1_pio1_irq_0, VectorKindId::vector_kind_external_interrupt},
  {26, StartupSymbolId::PIO1_IRQ_1_IRQHandler, InterruptBindingId::interrupt_binding_pio1_pio1_irq_1, VectorKindId::vector_kind_external_interrupt},
  {27, StartupSymbolId::DMA_IRQ_0_IRQHandler, InterruptBindingId::interrupt_binding_dma_dma_irq_0, VectorKindId::vector_kind_external_interrupt},
  {28, StartupSymbolId::DMA_IRQ_1_IRQHandler, InterruptBindingId::interrupt_binding_dma_dma_irq_1, VectorKindId::vector_kind_external_interrupt},
  {29, StartupSymbolId::IO_IRQ_BANK0_IRQHandler, InterruptBindingId::interrupt_binding_io_bank0_io_irq_bank0, VectorKindId::vector_kind_external_interrupt},
  {33, StartupSymbolId::CLOCKS_IRQ_IRQHandler, InterruptBindingId::interrupt_binding_clocks_clocks_irq, VectorKindId::vector_kind_external_interrupt},
  {34, StartupSymbolId::SPI0_IRQ_IRQHandler, InterruptBindingId::interrupt_binding_spi0_spi0_irq, VectorKindId::vector_kind_external_interrupt},
  {35, StartupSymbolId::SPI1_IRQ_IRQHandler, InterruptBindingId::interrupt_binding_spi1_spi1_irq, VectorKindId::vector_kind_external_interrupt},
  {36, StartupSymbolId::UART0_IRQ_IRQHandler, InterruptBindingId::interrupt_binding_uart0_uart0_irq, VectorKindId::vector_kind_external_interrupt},
  {37, StartupSymbolId::UART1_IRQ_IRQHandler, InterruptBindingId::interrupt_binding_uart1_uart1_irq, VectorKindId::vector_kind_external_interrupt},
  {38, StartupSymbolId::ADC_IRQ_FIFO_IRQHandler, InterruptBindingId::interrupt_binding_adc_adc_irq_fifo, VectorKindId::vector_kind_external_interrupt},
  {39, StartupSymbolId::I2C0_IRQ_IRQHandler, InterruptBindingId::interrupt_binding_i2c0_i2c0_irq, VectorKindId::vector_kind_external_interrupt},
  {40, StartupSymbolId::I2C1_IRQ_IRQHandler, InterruptBindingId::interrupt_binding_i2c1_i2c1_irq, VectorKindId::vector_kind_external_interrupt},
  {41, StartupSymbolId::RTC_IRQ_IRQHandler, InterruptBindingId::interrupt_binding_rtc_rtc_irq, VectorKindId::vector_kind_external_interrupt},
}};

struct StartupDescriptor {
  StartupDescriptorId descriptor_id;
  StartupKindId kind_id;
  StartupMemoryRegionId source_region_id;
  StartupMemoryRegionId target_region_id;
  StartupSymbolId symbol_id;
};
inline constexpr std::array<StartupDescriptor, 6> kStartupDescriptors = {{
  {StartupDescriptorId::startup_copy_source_xip_flash, StartupKindId::startup_kind_copy_source_region, StartupMemoryRegionId::XIP_FLASH, StartupMemoryRegionId::none, StartupSymbolId::none},
  {StartupDescriptorId::startup_copy_target_sram, StartupKindId::startup_kind_copy_target_region, StartupMemoryRegionId::none, StartupMemoryRegionId::SRAM, StartupSymbolId::none},
  {StartupDescriptorId::startup_stack_top, StartupKindId::startup_kind_initial_stack_pointer, StartupMemoryRegionId::none, StartupMemoryRegionId::none, StartupSymbolId::__stack_top},
  {StartupDescriptorId::startup_vector_source_xip_flash, StartupKindId::startup_kind_vector_source_region, StartupMemoryRegionId::XIP_FLASH, StartupMemoryRegionId::none, StartupSymbolId::none},
  {StartupDescriptorId::startup_vectors, StartupKindId::startup_kind_vector_table, StartupMemoryRegionId::none, StartupMemoryRegionId::none, StartupSymbolId::_vectors},
  {StartupDescriptorId::startup_zero_target_sram, StartupKindId::startup_kind_zero_target_region, StartupMemoryRegionId::none, StartupMemoryRegionId::SRAM, StartupSymbolId::none},
}};
}
}
}
}
}
}
