#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
consteval bool is_valid_i2c_speed(PeripheralId peripheral, std::uint32_t speed_hz) noexcept {
  if (peripheral == PeripheralId::TWI0) {
    constexpr std::uint32_t kSpeeds[] = { 100000u, 400000u };
    for (auto candidate : kSpeeds) {
      if (candidate == speed_hz) {
        return true;
      }
    }
    return false;
  }
  return false;
}

template<PeripheralId Peripheral, std::uint32_t SpeedHz>
concept ValidI2cSpeed = is_valid_i2c_speed(Peripheral, SpeedHz);

namespace detail {
template<PeripheralId Peripheral, std::uint32_t SpeedHz>
inline constexpr bool kInvalidI2cSpeed = false;
}  // namespace detail

struct I2cSpeedEntry {
  PeripheralId peripheral;
  std::uint32_t speed_hz;
};

inline constexpr std::array<I2cSpeedEntry, 2> kI2cSpeeds = {{
  {PeripheralId::TWI0, 100000u},
  {PeripheralId::TWI0, 400000u},
}};
}
}
}
}
}
}
