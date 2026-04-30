#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g071rb {
consteval bool is_valid_i2c_speed(PeripheralId peripheral, std::uint32_t speed_hz) noexcept {
  if (peripheral == PeripheralId::I2C1) {
    constexpr std::uint32_t kSpeeds[] = { 100000u, 400000u, 1000000u };
    for (auto candidate : kSpeeds) {
      if (candidate == speed_hz) {
        return true;
      }
    }
    return false;
  }
  if (peripheral == PeripheralId::I2C2) {
    constexpr std::uint32_t kSpeeds[] = { 100000u, 400000u, 1000000u };
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

inline constexpr std::array<I2cSpeedEntry, 6> kI2cSpeeds = {{
  {PeripheralId::I2C1, 100000u},
  {PeripheralId::I2C1, 400000u},
  {PeripheralId::I2C1, 1000000u},
  {PeripheralId::I2C2, 100000u},
  {PeripheralId::I2C2, 400000u},
  {PeripheralId::I2C2, 1000000u},
}};
}
}
}
}
}
}
