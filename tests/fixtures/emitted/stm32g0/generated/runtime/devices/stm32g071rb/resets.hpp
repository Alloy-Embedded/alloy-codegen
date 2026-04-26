#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "peripheral_instances.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g071rb {
struct ResetDescriptor {
  ResetId reset_id;
  PeripheralId peripheral_id;
  RegisterId register_id;
  FieldId field_id;
  ActiveLevelId active_level_id;
};
inline constexpr std::array<ResetDescriptor, 10> kResetDescriptors = {{
  {ResetId::reset_adc1, PeripheralId::ADC1, RegisterId::register_rcc_apbrstr2, FieldId::none, ActiveLevelId::active_level_high},
  {ResetId::reset_dma1, PeripheralId::DMA1, RegisterId::register_rcc_ahbrstr, FieldId::field_rcc_ahbrstr_dma1rst, ActiveLevelId::active_level_high},
  {ResetId::reset_dmamux1, PeripheralId::DMAMUX1, RegisterId::register_rcc_ahbrstr, FieldId::field_rcc_ahbrstr_dma1rst, ActiveLevelId::active_level_high},
  {ResetId::reset_gpioa, PeripheralId::GPIOA, RegisterId::register_rcc_ioprstr, FieldId::field_rcc_ioprstr_gpioarst, ActiveLevelId::active_level_high},
  {ResetId::reset_gpiob, PeripheralId::GPIOB, RegisterId::register_rcc_ioprstr, FieldId::field_rcc_ioprstr_gpiobrst, ActiveLevelId::active_level_high},
  {ResetId::reset_i2c1, PeripheralId::I2C1, RegisterId::register_rcc_apbrstr1, FieldId::none, ActiveLevelId::active_level_high},
  {ResetId::reset_i2c2, PeripheralId::I2C2, RegisterId::register_rcc_apbrstr1, FieldId::none, ActiveLevelId::active_level_high},
  {ResetId::reset_spi1, PeripheralId::SPI1, RegisterId::register_rcc_apbrstr2, FieldId::none, ActiveLevelId::active_level_high},
  {ResetId::reset_tim1, PeripheralId::TIM1, RegisterId::register_rcc_apbrstr2, FieldId::none, ActiveLevelId::active_level_high},
  {ResetId::reset_usart1, PeripheralId::USART1, RegisterId::register_rcc_apbrstr2, FieldId::field_rcc_apbrstr2_usart1rst, ActiveLevelId::active_level_high},
}};
}
}
}
}
}
}
