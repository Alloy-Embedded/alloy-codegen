#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "clock_graph.hpp"
#include "peripheral_instances.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
using EnableDomainId = ClockGateId;

struct EnableDomainDescriptor {
  EnableDomainId enable_domain_id;
  PeripheralId peripheral_id;
  ClockGateId clock_gate_id;
  ClockNodeId parent_clock_node_id;
  RegisterId register_id;
  FieldId field_id;
};
inline constexpr std::array<EnableDomainDescriptor, 5> kEnableDomains = {{
  {EnableDomainId::gate_gpio1, PeripheralId::GPIO1, ClockGateId::gate_gpio1, ClockNodeId::clock_node_ccm_ccgr1, RegisterId::register_ccm_ccgr1, FieldId::field_ccm_ccgr1_cg13},
  {EnableDomainId::gate_gpio4, PeripheralId::GPIO4, ClockGateId::gate_gpio4, ClockNodeId::clock_node_ccm_ccgr3, RegisterId::register_ccm_ccgr3, FieldId::field_ccm_ccgr3_cg13},
  {EnableDomainId::gate_lpspi1, PeripheralId::LPSPI1, ClockGateId::gate_lpspi1, ClockNodeId::clock_node_lpspi_root, RegisterId::register_ccm_ccgr1, FieldId::field_ccm_ccgr1_cg0},
  {EnableDomainId::gate_lpuart1, PeripheralId::LPUART1, ClockGateId::gate_lpuart1, ClockNodeId::clock_node_lpuart_root, RegisterId::register_ccm_ccgr5, FieldId::field_ccm_ccgr5_cg12},
  {EnableDomainId::gate_lpuart3, PeripheralId::LPUART3, ClockGateId::gate_lpuart3, ClockNodeId::clock_node_ccm_ccgr0, RegisterId::register_ccm_ccgr0, FieldId::field_ccm_ccgr0_cg6},
}};

template<EnableDomainId Id>
struct EnableDomainTraits {
  static constexpr bool kPresent = false;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::none;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<PeripheralId Id>
struct PeripheralEnableDomainTraits {
  static constexpr bool kPresent = false;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::none;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_gpio1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIO1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpio1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_ccm_ccgr1;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr1;
  static constexpr FieldId kFieldId = FieldId::field_ccm_ccgr1_cg13;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::GPIO1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_gpio1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_gpio4> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIO4;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpio4;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_ccm_ccgr3;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr3;
  static constexpr FieldId kFieldId = FieldId::field_ccm_ccgr3_cg13;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::GPIO4> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_gpio4;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_lpspi1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::LPSPI1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_lpspi1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_lpspi_root;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr1;
  static constexpr FieldId kFieldId = FieldId::field_ccm_ccgr1_cg0;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::LPSPI1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_lpspi1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_lpuart1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::LPUART1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_lpuart1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_lpuart_root;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr5;
  static constexpr FieldId kFieldId = FieldId::field_ccm_ccgr5_cg12;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::LPUART1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_lpuart1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_lpuart3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::LPUART3;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_lpuart3;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_ccm_ccgr0;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr0;
  static constexpr FieldId kFieldId = FieldId::field_ccm_ccgr0_cg6;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::LPUART3> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_lpuart3;
};

}
}
}
}
}
}
