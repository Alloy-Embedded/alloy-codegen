#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
enum class DmaBindingId : std::uint16_t {
  none,
};

enum class DmaControllerId : std::uint16_t {
  none,
};

enum class DmaRequestLineId : std::uint16_t {
  none,
};

enum class DmaRouteId : std::uint16_t {
  none,
};

enum class DmaConflictGroupId : std::uint16_t {
  none,
};

struct DmaBindingDescriptor {
  DmaBindingId binding_id;
  PeripheralId peripheral_id;
  SignalId signal_id;
  DmaControllerId controller_id;
  DmaRequestLineId request_line_id;
  DmaRouteId route_id;
  DmaConflictGroupId conflict_group_id;
  std::int32_t channel_index;
  std::int32_t request_value;
  std::int32_t channel_selector;
};

template<PeripheralId Peripheral, SignalId Signal>
struct BindingTraits {
  static constexpr bool kPresent = false;
  static constexpr DmaBindingId kBindingId = DmaBindingId::none;
  static constexpr DmaControllerId kControllerId = DmaControllerId::none;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::none;
  static constexpr DmaRouteId kRouteId = DmaRouteId::none;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = -1;
  static constexpr int kChannelSelector = -1;
};

template<DmaControllerId Id>
struct ControllerTraits {
  static constexpr bool kPresent = false;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr int kChannelCount = -1;
  static constexpr int kRequestCount = -1;
};

inline constexpr std::array<DmaBindingDescriptor, 0> kDmaBindings = {};

inline constexpr std::array<DmaControllerId, 0> kDmaControllers = {};
}
}
}
}
}
}
