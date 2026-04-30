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
enum class RegisterId : std::uint16_t {
  none,
  register_spi0_ctrla,
  register_spi0_ctrlb,
  register_tca0_ctrla,
  register_twi0_ctrla,
  register_twi0_mctrla,
  register_usart0_status,
  register_usart0_ctrla,
  register_usart0_ctrlb,
  register_usart1_status,
  register_usart1_ctrla,
  register_usart1_ctrlb,
};

enum class RegisterRole : std::uint16_t {
  none,
  general,
  secondary_core_release,
};

template<RegisterId Id>
struct RegisterTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ctrla> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x000008C0u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
  static constexpr int kSizeBits = 8;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ctrlb> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x000008C0u;
  static constexpr std::uint32_t kOffsetBytes = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
  static constexpr int kSizeBits = 8;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_tca0_ctrla> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x00000A00u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
  static constexpr int kSizeBits = 8;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_twi0_ctrla> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x000008A0u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
  static constexpr int kSizeBits = 8;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_twi0_mctrla> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x000008A0u;
  static constexpr std::uint32_t kOffsetBytes = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
  static constexpr int kSizeBits = 8;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart0_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x00000800u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
  static constexpr int kSizeBits = 8;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart0_ctrla> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x00000800u;
  static constexpr std::uint32_t kOffsetBytes = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
  static constexpr int kSizeBits = 8;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart0_ctrlb> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x00000800u;
  static constexpr std::uint32_t kOffsetBytes = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
  static constexpr int kSizeBits = 8;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart1_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x00000820u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
  static constexpr int kSizeBits = 8;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart1_ctrla> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x00000820u;
  static constexpr std::uint32_t kOffsetBytes = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
  static constexpr int kSizeBits = 8;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart1_ctrlb> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x00000820u;
  static constexpr std::uint32_t kOffsetBytes = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
  static constexpr int kSizeBits = 8;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

inline constexpr std::array<RegisterId, 11> kRegisters = {{
  RegisterId::register_spi0_ctrla,
  RegisterId::register_spi0_ctrlb,
  RegisterId::register_tca0_ctrla,
  RegisterId::register_twi0_ctrla,
  RegisterId::register_twi0_mctrla,
  RegisterId::register_usart0_status,
  RegisterId::register_usart0_ctrla,
  RegisterId::register_usart0_ctrlb,
  RegisterId::register_usart1_status,
  RegisterId::register_usart1_ctrla,
  RegisterId::register_usart1_ctrlb,
}};
}
}
}
}
}
}
