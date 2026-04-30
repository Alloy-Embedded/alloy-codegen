#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
struct RouteOperation {
  BackendSchemaId schema_id;
  OperationKindId kind_id;
  OperationSubjectKindId subject_kind_id;
  RegisterId register_id;
  FieldId field_id;
  PinId pin_id;
  ClockGateId clock_gate_id;
  ResetId reset_id;
  int value_int;
};

enum class RouteId : std::uint16_t {
  none,
  candidate_gpio_ad_b0_00_gpio1_io00,
  candidate_gpio_ad_b0_00_lpuart1_tx,
  candidate_gpio_ad_b0_01_gpio1_io01,
  candidate_gpio_ad_b0_01_lpuart1_rx,
  candidate_gpio_emc_00_gpio4_io00,
  candidate_gpio_emc_00_lpspi1_sck,
  candidate_gpio_emc_01_gpio4_io01,
  candidate_gpio_emc_01_lpspi1_pcs0,
};

struct RouteDescriptor {
  RouteId route_id;
  PinId pin_id;
  PeripheralId peripheral_id;
  SignalId signal_id;
  RouteKindId route_kind_id;
};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
struct RouteTraits {
  static constexpr bool kPresent = false;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr std::array<RouteOperation, 0> kOperations = {};
};

template<>
struct RouteTraits<PinId::GPIO_AD_B0_00, PeripheralId::GPIO1, SignalId::signal_io00> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_ad_b0_00_gpio1_io00;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_nxp_ccm, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_ccm_ccgr1, FieldId::field_ccm_ccgr1_cg13, PinId::none, ClockGateId::gate_gpio1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO_AD_B0_00, ClockGateId::none, ResetId::none, 5},
  }};
};

template<>
struct RouteTraits<PinId::GPIO_AD_B0_00, PeripheralId::LPUART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_ad_b0_00_lpuart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_nxp_ccm, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_ccm_ccgr5, FieldId::field_ccm_ccgr5_cg12, PinId::none, ClockGateId::gate_lpuart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO_AD_B0_00, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GPIO_AD_B0_01, PeripheralId::GPIO1, SignalId::signal_io01> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_ad_b0_01_gpio1_io01;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_nxp_ccm, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_ccm_ccgr1, FieldId::field_ccm_ccgr1_cg13, PinId::none, ClockGateId::gate_gpio1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO_AD_B0_01, ClockGateId::none, ResetId::none, 5},
  }};
};

template<>
struct RouteTraits<PinId::GPIO_AD_B0_01, PeripheralId::LPUART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_ad_b0_01_lpuart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_nxp_ccm, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_ccm_ccgr5, FieldId::field_ccm_ccgr5_cg12, PinId::none, ClockGateId::gate_lpuart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO_AD_B0_01, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GPIO_EMC_00, PeripheralId::GPIO4, SignalId::signal_io00> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_emc_00_gpio4_io00;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_nxp_ccm, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_ccm_ccgr3, FieldId::field_ccm_ccgr3_cg13, PinId::none, ClockGateId::gate_gpio4, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO_EMC_00, ClockGateId::none, ResetId::none, 5},
  }};
};

template<>
struct RouteTraits<PinId::GPIO_EMC_00, PeripheralId::LPSPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_emc_00_lpspi1_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_nxp_ccm, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_ccm_ccgr1, FieldId::field_ccm_ccgr1_cg0, PinId::none, ClockGateId::gate_lpspi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO_EMC_00, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GPIO_EMC_01, PeripheralId::GPIO4, SignalId::signal_io01> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_emc_01_gpio4_io01;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_nxp_ccm, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_ccm_ccgr3, FieldId::field_ccm_ccgr3_cg13, PinId::none, ClockGateId::gate_gpio4, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO_EMC_01, ClockGateId::none, ResetId::none, 5},
  }};
};

template<>
struct RouteTraits<PinId::GPIO_EMC_01, PeripheralId::LPSPI1, SignalId::signal_pcs0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_emc_01_lpspi1_pcs0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_nxp_ccm, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_ccm_ccgr1, FieldId::field_ccm_ccgr1_cg0, PinId::none, ClockGateId::gate_lpspi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO_EMC_01, ClockGateId::none, ResetId::none, 2},
  }};
};

inline constexpr std::array<RouteDescriptor, 8> kRuntimeRoutes = {{
  {RouteId::candidate_gpio_ad_b0_00_gpio1_io00, PinId::GPIO_AD_B0_00, PeripheralId::GPIO1, SignalId::signal_io00, RouteKindId::route_kind_iomuxc_mux},
  {RouteId::candidate_gpio_ad_b0_00_lpuart1_tx, PinId::GPIO_AD_B0_00, PeripheralId::LPUART1, SignalId::signal_tx, RouteKindId::route_kind_iomuxc_mux},
  {RouteId::candidate_gpio_ad_b0_01_gpio1_io01, PinId::GPIO_AD_B0_01, PeripheralId::GPIO1, SignalId::signal_io01, RouteKindId::route_kind_iomuxc_mux},
  {RouteId::candidate_gpio_ad_b0_01_lpuart1_rx, PinId::GPIO_AD_B0_01, PeripheralId::LPUART1, SignalId::signal_rx, RouteKindId::route_kind_iomuxc_mux},
  {RouteId::candidate_gpio_emc_00_gpio4_io00, PinId::GPIO_EMC_00, PeripheralId::GPIO4, SignalId::signal_io00, RouteKindId::route_kind_iomuxc_mux},
  {RouteId::candidate_gpio_emc_00_lpspi1_sck, PinId::GPIO_EMC_00, PeripheralId::LPSPI1, SignalId::signal_sck, RouteKindId::route_kind_iomuxc_mux},
  {RouteId::candidate_gpio_emc_01_gpio4_io01, PinId::GPIO_EMC_01, PeripheralId::GPIO4, SignalId::signal_io01, RouteKindId::route_kind_iomuxc_mux},
  {RouteId::candidate_gpio_emc_01_lpspi1_pcs0, PinId::GPIO_EMC_01, PeripheralId::LPSPI1, SignalId::signal_pcs0, RouteKindId::route_kind_iomuxc_mux},
}};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
inline auto apply_route() noexcept -> void {
  static_assert(RouteTraits<Pin, Peripheral, Signal>::kPresent, "");
}

template<>
inline auto apply_route<PinId::GPIO_AD_B0_00, PeripheralId::GPIO1, SignalId::signal_io00>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400FC06Cu) |=(std::uint32_t{1} << 26);
}

template<>
inline auto apply_route<PinId::GPIO_AD_B0_00, PeripheralId::LPUART1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400FC07Cu) |=(std::uint32_t{1} << 24);
}

template<>
inline auto apply_route<PinId::GPIO_AD_B0_01, PeripheralId::GPIO1, SignalId::signal_io01>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400FC06Cu) |=(std::uint32_t{1} << 26);
}

template<>
inline auto apply_route<PinId::GPIO_AD_B0_01, PeripheralId::LPUART1, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400FC07Cu) |=(std::uint32_t{1} << 24);
}

template<>
inline auto apply_route<PinId::GPIO_EMC_00, PeripheralId::GPIO4, SignalId::signal_io00>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400FC074u) |=(std::uint32_t{1} << 26);
}

template<>
inline auto apply_route<PinId::GPIO_EMC_00, PeripheralId::LPSPI1, SignalId::signal_sck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400FC06Cu) |=(std::uint32_t{1} << 0);
}

template<>
inline auto apply_route<PinId::GPIO_EMC_01, PeripheralId::GPIO4, SignalId::signal_io01>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400FC074u) |=(std::uint32_t{1} << 26);
}

template<>
inline auto apply_route<PinId::GPIO_EMC_01, PeripheralId::LPSPI1, SignalId::signal_pcs0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400FC06Cu) |=(std::uint32_t{1} << 0);
}

enum class ConnectionGroupId : std::uint16_t {
  none,
  group_gpio1_bga196_all_signals,
  group_gpio4_bga196_all_signals,
  group_lpspi1_bga196_sck_cs,
  group_lpuart1_bga196_tx_rx,
};

template<PeripheralId Peripheral, SignalId... Signals>
struct ConnectionGroupTraits {
  static constexpr bool kPresent = false;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::none;
  static constexpr std::array<RouteId, 0> kRoutes = {};
};

template<>
struct ConnectionGroupTraits<PeripheralId::GPIO1, SignalId::signal_io00, SignalId::signal_io01> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_gpio1_bga196_all_signals;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_gpio_ad_b0_00_gpio1_io00,
    RouteId::candidate_gpio_ad_b0_01_gpio1_io01,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::GPIO4, SignalId::signal_io00, SignalId::signal_io01> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_gpio4_bga196_all_signals;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_gpio_emc_00_gpio4_io00,
    RouteId::candidate_gpio_emc_01_gpio4_io01,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::LPSPI1, SignalId::signal_sck, SignalId::signal_cs> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_lpspi1_bga196_sck_cs;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_gpio_emc_00_lpspi1_sck,
    RouteId::candidate_gpio_emc_01_lpspi1_pcs0,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::LPUART1, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_lpuart1_bga196_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_gpio_ad_b0_00_lpuart1_tx,
    RouteId::candidate_gpio_ad_b0_01_lpuart1_rx,
  }};
};

struct ConnectionGroupDescriptor {
  ConnectionGroupId group_id;
  PeripheralId peripheral_id;
  std::uint16_t route_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 4> kRuntimeConnectionGroups = {{
  {ConnectionGroupId::group_gpio1_bga196_all_signals, PeripheralId::GPIO1, 2u},
  {ConnectionGroupId::group_gpio4_bga196_all_signals, PeripheralId::GPIO4, 2u},
  {ConnectionGroupId::group_lpspi1_bga196_sck_cs, PeripheralId::LPSPI1, 2u},
  {ConnectionGroupId::group_lpuart1_bga196_tx_rx, PeripheralId::LPUART1, 2u},
}};

}
}
}
}
}
}
