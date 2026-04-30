#pragma once

#include <cstdint>
#include "driver_semantics/common.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
enum class SysTickClockSourceId : std::uint16_t {
  none,
  processor_clock,
  alternate_reference_clock,
};

struct SysTickDescriptor {
  bool present;
  std::uint32_t counter_bits;
  std::uint32_t exception_number;
};

using RuntimeRegisterRef = driver_semantics::RuntimeRegisterRef;
using RuntimeFieldRef = driver_semantics::RuntimeFieldRef;

struct SysTickTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kCounterBits = 24u;
  static constexpr std::uint32_t kMaxReloadValue = 0x00FF'FFFFu;
  static constexpr std::uint32_t kExceptionNumber = 15u;
  static constexpr SysTickClockSourceId kDefaultClockSource = SysTickClockSourceId::processor_clock;
  static constexpr RuntimeRegisterRef kCtrlRegister = RuntimeRegisterRef{RegisterId::none, 0xE000E010u, 0u, kPresent};
  static constexpr RuntimeRegisterRef kLoadRegister = RuntimeRegisterRef{RegisterId::none, 0xE000E010u, 4u, kPresent};
  static constexpr RuntimeRegisterRef kValRegister = RuntimeRegisterRef{RegisterId::none, 0xE000E010u, 8u, kPresent};
  static constexpr RuntimeRegisterRef kCalibRegister = RuntimeRegisterRef{RegisterId::none, 0xE000E010u, 12u, kPresent};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, kCtrlRegister, 0u, 1u, kPresent};
  static constexpr RuntimeFieldRef kTickIntField = RuntimeFieldRef{FieldId::none, kCtrlRegister, 1u, 1u, kPresent};
  static constexpr RuntimeFieldRef kClkSourceField = RuntimeFieldRef{FieldId::none, kCtrlRegister, 2u, 1u, kPresent};
  static constexpr RuntimeFieldRef kCountFlagField = RuntimeFieldRef{FieldId::none, kCtrlRegister, 16u, 1u, kPresent};
  static constexpr RuntimeFieldRef kReloadField = RuntimeFieldRef{FieldId::none, kLoadRegister, 0u, 24u, kPresent};
  static constexpr RuntimeFieldRef kCurrentField = RuntimeFieldRef{FieldId::none, kValRegister, 0u, 24u, kPresent};
  static constexpr RuntimeFieldRef kTenMsField = RuntimeFieldRef{FieldId::none, kCalibRegister, 0u, 24u, kPresent};
  static constexpr RuntimeFieldRef kSkewField = RuntimeFieldRef{FieldId::none, kCalibRegister, 30u, 1u, kPresent};
  static constexpr RuntimeFieldRef kNoRefField = RuntimeFieldRef{FieldId::none, kCalibRegister, 31u, 1u, kPresent};
};

inline constexpr SysTickDescriptor kSysTick = {
  SysTickTraits::kPresent,
  SysTickTraits::kCounterBits,
  SysTickTraits::kExceptionNumber,
};

inline std::uint32_t systick_read_register(RuntimeRegisterRef reg) {
  auto* const ptr = reinterpret_cast<volatile std::uint32_t*>(
      reg.base_address + reg.offset_bytes);
  return *ptr;
}

inline void systick_write_register(RuntimeRegisterRef reg, std::uint32_t value) {
  auto* const ptr = reinterpret_cast<volatile std::uint32_t*>(
      reg.base_address + reg.offset_bytes);
  *ptr = value;
}

inline std::uint32_t systick_field_mask(RuntimeFieldRef field) {
  return ((field.bit_width >= 32u ? 0xFFFF'FFFFu : ((1u << field.bit_width) - 1u)) << field.bit_offset);
}

inline std::uint32_t systick_read_field(RuntimeFieldRef field) {
  const auto value = systick_read_register(field.reg) & systick_field_mask(field);
  return value >> field.bit_offset;
}

inline void systick_write_field(RuntimeFieldRef field, std::uint32_t value) {
  const auto current = systick_read_register(field.reg);
  const auto mask = systick_field_mask(field);
  const auto shifted = (value << field.bit_offset) & mask;
  systick_write_register(field.reg, (current & ~mask) | shifted);
}

inline bool configure_reload(std::uint32_t reload_value) {
  if (!SysTickTraits::kPresent || reload_value > SysTickTraits::kMaxReloadValue) {
    return false;
  }
  systick_write_field(SysTickTraits::kReloadField, reload_value);
  systick_write_register(SysTickTraits::kValRegister, 0u);
  return true;
}

inline void disable() {
  if (!SysTickTraits::kPresent) {
    return;
  }
  systick_write_register(SysTickTraits::kCtrlRegister, 0u);
}

inline bool enable(
    std::uint32_t reload_value,
    SysTickClockSourceId source = SysTickTraits::kDefaultClockSource,
    bool interrupt_enable = true) {
  if (source == SysTickClockSourceId::none) {
    return false;
  }
  if (!configure_reload(reload_value)) {
    return false;
  }
  std::uint32_t control = 0x1u;
  if (interrupt_enable) {
    control |= 0x2u;
  }
  if (source == SysTickClockSourceId::processor_clock) {
    control |= 0x4u;
  }
  systick_write_register(SysTickTraits::kCtrlRegister, control);
  return true;
}

inline bool configure_for_tick_hz(
    std::uint32_t source_clock_hz,
    std::uint32_t tick_hz,
    SysTickClockSourceId source = SysTickTraits::kDefaultClockSource,
    bool interrupt_enable = true) {
  if (!SysTickTraits::kPresent || source == SysTickClockSourceId::none || source_clock_hz == 0u || tick_hz == 0u) {
    return false;
  }
  const auto ticks_per_period = source_clock_hz / tick_hz;
  if (ticks_per_period == 0u) {
    return false;
  }
  return enable(ticks_per_period - 1u, source, interrupt_enable);
}

inline std::uint32_t calibration_ten_ms() {
  if (!SysTickTraits::kPresent) {
    return 0u;
  }
  return systick_read_field(SysTickTraits::kTenMsField);
}

inline bool calibration_has_reference_clock() {
  if (!SysTickTraits::kPresent) {
    return false;
  }
  return systick_read_field(SysTickTraits::kNoRefField) == 0u;
}

inline bool calibration_has_skew() {
  if (!SysTickTraits::kPresent) {
    return false;
  }
  return systick_read_field(SysTickTraits::kSkewField) != 0u;
}

inline bool counted_to_zero() {
  if (!SysTickTraits::kPresent) {
    return false;
  }
  return systick_read_field(SysTickTraits::kCountFlagField) != 0u;
}
}
}
}
}
}
}
