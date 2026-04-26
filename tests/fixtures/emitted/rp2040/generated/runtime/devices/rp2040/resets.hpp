#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "peripheral_instances.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
struct ResetDescriptor {
  ResetId reset_id;
  PeripheralId peripheral_id;
  RegisterId register_id;
  FieldId field_id;
  ActiveLevelId active_level_id;
};
inline constexpr std::array<ResetDescriptor, 11> kResetDescriptors = {{
  {ResetId::reset_adc, PeripheralId::ADC, RegisterId::register_resets_reset, FieldId::field_resets_reset_adc, ActiveLevelId::active_level_high},
  {ResetId::reset_dma, PeripheralId::DMA, RegisterId::register_resets_reset, FieldId::field_resets_reset_dma, ActiveLevelId::active_level_high},
  {ResetId::reset_i2c0, PeripheralId::I2C0, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, ActiveLevelId::active_level_high},
  {ResetId::reset_i2c1, PeripheralId::I2C1, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, ActiveLevelId::active_level_high},
  {ResetId::reset_pwm, PeripheralId::PWM, RegisterId::register_resets_reset, FieldId::field_resets_reset_pwm, ActiveLevelId::active_level_high},
  {ResetId::reset_rtc, PeripheralId::RTC, RegisterId::register_resets_reset, FieldId::field_resets_reset_rtc, ActiveLevelId::active_level_high},
  {ResetId::reset_spi0, PeripheralId::SPI0, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, ActiveLevelId::active_level_high},
  {ResetId::reset_spi1, PeripheralId::SPI1, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, ActiveLevelId::active_level_high},
  {ResetId::reset_timer, PeripheralId::TIMER, RegisterId::register_resets_reset, FieldId::field_resets_reset_timer, ActiveLevelId::active_level_high},
  {ResetId::reset_uart0, PeripheralId::UART0, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, ActiveLevelId::active_level_high},
  {ResetId::reset_uart1, PeripheralId::UART1, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, ActiveLevelId::active_level_high},
}};
}
}
}
}
}
}
