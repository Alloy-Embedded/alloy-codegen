#pragma once

#include <cstdint>
#include "../peripheral_instances.hpp"
#include "../registers.hpp"
#include "../register_fields.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
namespace driver_semantics {
struct RuntimeRegisterRef {
  RegisterId register_id = RegisterId::none;
  std::uintptr_t base_address = 0u;
  std::uint32_t offset_bytes = 0u;
  bool valid = false;
};

struct RuntimeFieldRef {
  FieldId field_id = FieldId::none;
  RuntimeRegisterRef reg{};
  std::uint16_t bit_offset = 0u;
  std::uint16_t bit_width = 0u;
  bool valid = false;
};

struct RuntimeIndexedFieldRef {
  std::uintptr_t base_address = 0u;
  std::uint32_t base_offset_bytes = 0u;
  std::uint32_t stride_bytes = 0u;
  std::uint16_t bit_offset = 0u;
  std::uint16_t bit_width = 0u;
  std::uint16_t bit_stride_bits = 0u;
  bool valid = false;
};

inline constexpr RuntimeRegisterRef kInvalidRegisterRef{};
inline constexpr RuntimeFieldRef kInvalidFieldRef{};
inline constexpr RuntimeIndexedFieldRef kInvalidIndexedFieldRef{};
}
}
}
}
}
}
}
