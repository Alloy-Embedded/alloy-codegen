#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"
#include "registers.hpp"
#include "startup.hpp"
#include "system_clock.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g030f6 {
enum class SystemSequenceId : std::uint16_t {
  none,
  default_bringup,
};

enum class SystemSequenceStepKindId : std::uint16_t {
  none,
  startup_descriptor,
  startup_control,
  system_clock_profile,
  secondary_core_release,
};

enum class SecondaryCoreReleaseOperationId : std::uint16_t {
  none,
  set_bit_0,
  clear_runstall_after_clkgate,
};

struct SystemSequenceStepDescriptor {
  SystemSequenceId sequence_id;
  std::uint16_t ordinal;
  SystemSequenceStepKindId kind_id;
  StartupDescriptorId startup_descriptor_id;
  PeripheralId peripheral_id;
  SystemClockProfileId system_clock_profile_id;
  RegisterId secondary_core_release_register_id;
  RegisterId secondary_core_release_register_secondary_id;
  SecondaryCoreReleaseOperationId secondary_core_release_operation_id;
};
inline constexpr std::array<SystemSequenceStepDescriptor, 7> kSystemSequenceSteps = {{
  {SystemSequenceId::default_bringup, 0u, SystemSequenceStepKindId::startup_descriptor, StartupDescriptorId::startup_copy_source_flash, PeripheralId::none, SystemClockProfileId::none, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
  {SystemSequenceId::default_bringup, 1u, SystemSequenceStepKindId::startup_descriptor, StartupDescriptorId::startup_copy_target_sram, PeripheralId::none, SystemClockProfileId::none, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
  {SystemSequenceId::default_bringup, 2u, SystemSequenceStepKindId::startup_descriptor, StartupDescriptorId::startup_stack_top, PeripheralId::none, SystemClockProfileId::none, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
  {SystemSequenceId::default_bringup, 3u, SystemSequenceStepKindId::startup_descriptor, StartupDescriptorId::startup_vector_source_flash, PeripheralId::none, SystemClockProfileId::none, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
  {SystemSequenceId::default_bringup, 4u, SystemSequenceStepKindId::startup_descriptor, StartupDescriptorId::startup_vectors, PeripheralId::none, SystemClockProfileId::none, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
  {SystemSequenceId::default_bringup, 5u, SystemSequenceStepKindId::startup_descriptor, StartupDescriptorId::startup_zero_target_sram, PeripheralId::none, SystemClockProfileId::none, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
  {SystemSequenceId::default_bringup, 6u, SystemSequenceStepKindId::system_clock_profile, StartupDescriptorId::none, PeripheralId::none, SystemClockProfileId::default_pll_64mhz, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
}};

template<SystemSequenceId Id>
struct SystemSequenceTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint16_t kStepCount = 0u;
  static constexpr std::uint16_t kStartupDescriptorCount = 0u;
  static constexpr std::uint16_t kStartupControlCount = 0u;
  static constexpr SystemClockProfileId kDefaultSystemClockProfileId = SystemClockProfileId::none;
  static constexpr SystemClockProfileId kSafeSystemClockProfileId = SystemClockProfileId::none;
};

template<>
struct SystemSequenceTraits<SystemSequenceId::default_bringup> {
  static constexpr bool kPresent = true;
  static constexpr std::uint16_t kStepCount = 7u;
  static constexpr std::uint16_t kStartupDescriptorCount = 6u;
  static constexpr std::uint16_t kStartupControlCount = 0u;
  static constexpr SystemClockProfileId kDefaultSystemClockProfileId = SystemClockProfileId::default_pll_64mhz;
  static constexpr SystemClockProfileId kSafeSystemClockProfileId = SystemClockProfileId::safe_hsi16;
};
}
}
}
}
}
}
