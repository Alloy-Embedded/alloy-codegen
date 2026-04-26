#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"
#include "registers.hpp"
#include "startup.hpp"
#include "system_clock.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
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
inline constexpr std::array<SystemSequenceStepDescriptor, 5> kSystemSequenceSteps = {{
  {SystemSequenceId::default_bringup, 0u, SystemSequenceStepKindId::startup_descriptor, StartupDescriptorId::startup_copy_target_ocram, PeripheralId::none, SystemClockProfileId::none, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
  {SystemSequenceId::default_bringup, 1u, SystemSequenceStepKindId::startup_descriptor, StartupDescriptorId::startup_stack_top, PeripheralId::none, SystemClockProfileId::none, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
  {SystemSequenceId::default_bringup, 2u, SystemSequenceStepKindId::startup_descriptor, StartupDescriptorId::startup_vectors, PeripheralId::none, SystemClockProfileId::none, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
  {SystemSequenceId::default_bringup, 3u, SystemSequenceStepKindId::startup_descriptor, StartupDescriptorId::startup_zero_target_ocram, PeripheralId::none, SystemClockProfileId::none, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
  {SystemSequenceId::default_bringup, 4u, SystemSequenceStepKindId::system_clock_profile, StartupDescriptorId::none, PeripheralId::none, SystemClockProfileId::default_arm_pll_600mhz, RegisterId::none, RegisterId::none, SecondaryCoreReleaseOperationId::none},
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
  static constexpr std::uint16_t kStepCount = 5u;
  static constexpr std::uint16_t kStartupDescriptorCount = 4u;
  static constexpr std::uint16_t kStartupControlCount = 0u;
  static constexpr SystemClockProfileId kDefaultSystemClockProfileId = SystemClockProfileId::default_arm_pll_600mhz;
  static constexpr SystemClockProfileId kSafeSystemClockProfileId = SystemClockProfileId::safe_osc24m;
};
}
}
}
}
}
}
