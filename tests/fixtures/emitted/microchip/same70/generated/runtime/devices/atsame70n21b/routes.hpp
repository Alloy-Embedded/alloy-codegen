#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
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
  candidate_pa0_pwm0_pwmh0,
  candidate_pa0_tc0_tioa0,
  candidate_pa10_gpioa_piodc4,
  candidate_pa10_pwm0_pwmextrg0,
  candidate_pa10_uart0_utxd0,
  candidate_pa11_gpioa_piodc5,
  candidate_pa11_pwm0_pwmh0,
  candidate_pa11_pwm1_pwml0,
  candidate_pa11_qspi_qcs,
  candidate_pa12_gpioa_piodc6,
  candidate_pa12_pwm0_pwmh1,
  candidate_pa12_pwm1_pwmh0,
  candidate_pa12_qspi_qio1,
  candidate_pa13_gpioa_piodc7,
  candidate_pa13_pwm0_pwmh2,
  candidate_pa13_pwm1_pwml1,
  candidate_pa13_qspi_qio0,
  candidate_pa14_gpioa_piodcen1,
  candidate_pa14_pwm0_pwmh3,
  candidate_pa14_pwm1_pwmh1,
  candidate_pa14_qspi_qsck,
  candidate_pa15_pwm0_pwml3,
  candidate_pa15_tc0_tioa1,
  candidate_pa16_pwm0_pwml2,
  candidate_pa16_tc0_tiob1,
  candidate_pa17_afec0_ad6,
  candidate_pa17_pwm0_pwmh3,
  candidate_pa17_qspi_qio2,
  candidate_pa18_afec0_ad7,
  candidate_pa18_pwm1_pwmextrg1,
  candidate_pa19_afec0_ad8,
  candidate_pa19_pwm0_pwml0,
  candidate_pa1_pwm0_pwml0,
  candidate_pa1_tc0_tiob0,
  candidate_pa20_afec0_ad9,
  candidate_pa20_pwm0_pwml1,
  candidate_pa21_afec0_ad1,
  candidate_pa21_gpioa_piodcen2,
  candidate_pa21_pwm1_pwmfi0,
  candidate_pa21_usart1_rxd1,
  candidate_pa22_gpioa_piodcclk,
  candidate_pa22_pwm0_pwmextrg1,
  candidate_pa23_pwm0_pwmh0,
  candidate_pa23_pwm1_pwml2,
  candidate_pa23_usart1_sck1,
  candidate_pa24_pwm0_pwmh1,
  candidate_pa24_usart1_rts1,
  candidate_pa25_hsmci_mcck,
  candidate_pa25_pwm0_pwmh2,
  candidate_pa25_usart1_cts1,
  candidate_pa26_hsmci_mcda2,
  candidate_pa26_pwm1_pwmfi1,
  candidate_pa26_tc0_tioa2,
  candidate_pa26_usart1_dcd1,
  candidate_pa27_hsmci_mcda3,
  candidate_pa27_tc0_tiob2,
  candidate_pa27_usart1_dtr1,
  candidate_pa28_hsmci_mccda,
  candidate_pa28_pwm1_pwmfi2,
  candidate_pa28_tc0_tclk1,
  candidate_pa28_usart1_dsr1,
  candidate_pa2_dacc_datrg,
  candidate_pa2_pwm0_pwmh1,
  candidate_pa30_hsmci_mcda0,
  candidate_pa30_pwm0_pwml2,
  candidate_pa30_pwm1_pwmextrg0,
  candidate_pa31_hsmci_mcda1,
  candidate_pa31_pwm1_pwmh2,
  candidate_pa31_spi0_npcs1,
  candidate_pa3_gpioa_piodc0,
  candidate_pa3_twihs0_twd0,
  candidate_pa3_usart1_loncol1,
  candidate_pa4_gpioa_piodc1,
  candidate_pa4_tc0_tclk0,
  candidate_pa4_twihs0_twck0,
  candidate_pa4_uart1_utxd1,
  candidate_pa5_gpioa_piodc2,
  candidate_pa5_pwm1_pwml3,
  candidate_pa5_uart1_urxd1,
  candidate_pa7_pwm0_pwmh3,
  candidate_pa8_afec0_adtrg,
  candidate_pa8_pwm1_pwmh3,
  candidate_pa9_gpioa_piodc3,
  candidate_pa9_pwm0_pwmfi0,
  candidate_pa9_uart0_urxd0,
  candidate_pb0_afec0_ad10,
  candidate_pb0_pwm0_pwmh0,
  candidate_pb0_rtc_rtcout0,
  candidate_pb0_usart0_rxd0,
  candidate_pb12_gmac_gtsucomp,
  candidate_pb12_pwm0_pwml1,
  candidate_pb13_dacc_dac0,
  candidate_pb13_pwm0_pwml2,
  candidate_pb13_usart0_sck0,
  candidate_pb1_afec1_ad0,
  candidate_pb1_gmac_gtsucomp,
  candidate_pb1_pwm0_pwmh1,
  candidate_pb1_rtc_rtcout1,
  candidate_pb1_usart0_txd0,
  candidate_pb2_afec0_ad5,
  candidate_pb2_mcan0_cantx0,
  candidate_pb2_spi0_npcs0,
  candidate_pb2_usart0_cts0,
  candidate_pb3_afec0_ad2,
  candidate_pb3_mcan0_canrx0,
  candidate_pb3_usart0_rts0,
  candidate_pb4_pwm0_pwmh2,
  candidate_pb4_twihs1_twd1,
  candidate_pb4_usart1_txd1,
  candidate_pb5_pwm0_pwml0,
  candidate_pb5_twihs1_twck1,
  candidate_pd0_dacc_dac1,
  candidate_pd0_gmac_gtxck,
  candidate_pd0_pwm1_pwml0,
  candidate_pd0_usart0_dcd0,
  candidate_pd10_gmac_gcrs,
  candidate_pd10_pwm0_pwml0,
  candidate_pd11_gmac_grx2,
  candidate_pd11_gmac_gtsucomp,
  candidate_pd11_pwm0_pwmh0,
  candidate_pd12_gmac_grx3,
  candidate_pd12_mcan1_cantx1,
  candidate_pd12_spi0_npcs2,
  candidate_pd13_gmac_gcol,
  candidate_pd14_gmac_grxck,
  candidate_pd15_gmac_gtx2,
  candidate_pd15_usart2_rxd2,
  candidate_pd16_gmac_gtx3,
  candidate_pd16_usart2_txd2,
  candidate_pd17_gmac_gtxer,
  candidate_pd17_usart2_sck2,
  candidate_pd18_uart4_urxd4,
  candidate_pd18_usart2_rts2,
  candidate_pd19_uart4_utxd4,
  candidate_pd19_usart2_cts2,
  candidate_pd1_gmac_gtxen,
  candidate_pd1_pwm1_pwmh0,
  candidate_pd1_usart0_dtr0,
  candidate_pd20_gmac_gtsucomp,
  candidate_pd20_pwm0_pwmh0,
  candidate_pd20_spi0_miso,
  candidate_pd21_pwm0_pwmh1,
  candidate_pd21_spi0_mosi,
  candidate_pd21_tc3_tioa11,
  candidate_pd22_pwm0_pwmh2,
  candidate_pd22_spi0_spck,
  candidate_pd22_tc3_tiob11,
  candidate_pd24_pwm0_pwml0,
  candidate_pd24_tc3_tclk11,
  candidate_pd25_pwm0_pwml1,
  candidate_pd25_spi0_npcs1,
  candidate_pd25_uart2_urxd2,
  candidate_pd26_pwm0_pwml2,
  candidate_pd26_uart1_utxd1,
  candidate_pd26_uart2_utxd2,
  candidate_pd27_pwm0_pwml3,
  candidate_pd27_spi0_npcs3,
  candidate_pd27_twihs2_twd2,
  candidate_pd28_mcan1_canrx1,
  candidate_pd28_twihs2_twck2,
  candidate_pd28_uart3_urxd3,
  candidate_pd2_gmac_gtx0,
  candidate_pd2_pwm1_pwml1,
  candidate_pd2_usart0_dsr0,
  candidate_pd30_afec0_ad0,
  candidate_pd30_uart3_utxd3,
  candidate_pd31_qspi_qio3,
  candidate_pd31_uart3_utxd3,
  candidate_pd3_gmac_gtx1,
  candidate_pd3_pwm1_pwmh1,
  candidate_pd3_uart4_utxd4,
  candidate_pd3_usart0_ri0,
  candidate_pd4_gmac_grxdv,
  candidate_pd4_pwm1_pwml2,
  candidate_pd4_usart2_dcd2,
  candidate_pd5_gmac_grx0,
  candidate_pd5_pwm1_pwmh2,
  candidate_pd5_usart2_dtr2,
  candidate_pd6_gmac_grx1,
  candidate_pd6_pwm1_pwml3,
  candidate_pd6_usart2_dsr2,
  candidate_pd7_gmac_grxer,
  candidate_pd7_pwm1_pwmh3,
  candidate_pd7_usart2_ri2,
  candidate_pd8_gmac_gmdc,
  candidate_pd8_pwm0_pwmfi1,
  candidate_pd9_afec1_adtrg,
  candidate_pd9_gmac_gmdio,
  candidate_pd9_pwm0_pwmfi2,
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
struct RouteTraits<PinId::PA0, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa0_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA0, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA0, PeripheralId::TC0, SignalId::signal_tioa0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa0_tc0_tioa0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid23, PinId::none, ClockGateId::gate_tc0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA0, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA10, PeripheralId::GPIOA, SignalId::signal_piodc4> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa10_gpioa_piodc4;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10, PinId::none, ClockGateId::gate_gpioa, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA10, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA10, PeripheralId::PWM0, SignalId::signal_pwmextrg0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa10_pwm0_pwmextrg0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA10, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA10, PeripheralId::UART0, SignalId::signal_utxd0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa10_uart0_utxd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid7, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA10, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA11, PeripheralId::GPIOA, SignalId::signal_piodc5> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa11_gpioa_piodc5;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10, PinId::none, ClockGateId::gate_gpioa, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA11, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA11, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa11_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA11, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA11, PeripheralId::PWM1, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa11_pwm1_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA11, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA11, PeripheralId::QSPI, SignalId::signal_qcs> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa11_qspi_qcs;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid43, PinId::none, ClockGateId::gate_qspi, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA11, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA12, PeripheralId::GPIOA, SignalId::signal_piodc6> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa12_gpioa_piodc6;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10, PinId::none, ClockGateId::gate_gpioa, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA12, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA12, PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa12_pwm0_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA12, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA12, PeripheralId::PWM1, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa12_pwm1_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA12, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA12, PeripheralId::QSPI, SignalId::signal_qio1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa12_qspi_qio1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid43, PinId::none, ClockGateId::gate_qspi, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA12, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA13, PeripheralId::GPIOA, SignalId::signal_piodc7> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa13_gpioa_piodc7;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10, PinId::none, ClockGateId::gate_gpioa, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA13, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA13, PeripheralId::PWM0, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa13_pwm0_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA13, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA13, PeripheralId::PWM1, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa13_pwm1_pwml1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA13, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA13, PeripheralId::QSPI, SignalId::signal_qio0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa13_qspi_qio0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid43, PinId::none, ClockGateId::gate_qspi, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA13, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA14, PeripheralId::GPIOA, SignalId::signal_piodcen1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa14_gpioa_piodcen1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10, PinId::none, ClockGateId::gate_gpioa, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA14, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA14, PeripheralId::PWM0, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa14_pwm0_pwmh3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA14, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA14, PeripheralId::PWM1, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa14_pwm1_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA14, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA14, PeripheralId::QSPI, SignalId::signal_qsck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa14_qspi_qsck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid43, PinId::none, ClockGateId::gate_qspi, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA14, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA15, PeripheralId::PWM0, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa15_pwm0_pwml3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA15, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA15, PeripheralId::TC0, SignalId::signal_tioa1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa15_tc0_tioa1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid23, PinId::none, ClockGateId::gate_tc0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA15, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA16, PeripheralId::PWM0, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa16_pwm0_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA16, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA16, PeripheralId::TC0, SignalId::signal_tiob1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa16_tc0_tiob1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid23, PinId::none, ClockGateId::gate_tc0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA16, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA17, PeripheralId::AFEC0, SignalId::signal_ad6> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa17_afec0_ad6;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid29, PinId::none, ClockGateId::gate_afec0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA17, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA17, PeripheralId::PWM0, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa17_pwm0_pwmh3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA17, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA17, PeripheralId::QSPI, SignalId::signal_qio2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa17_qspi_qio2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid43, PinId::none, ClockGateId::gate_qspi, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA17, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA18, PeripheralId::AFEC0, SignalId::signal_ad7> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa18_afec0_ad7;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid29, PinId::none, ClockGateId::gate_afec0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA18, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA18, PeripheralId::PWM1, SignalId::signal_pwmextrg1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa18_pwm1_pwmextrg1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA18, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA19, PeripheralId::AFEC0, SignalId::signal_ad8> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa19_afec0_ad8;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid29, PinId::none, ClockGateId::gate_afec0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA19, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA19, PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa19_pwm0_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA19, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA1, PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa1_pwm0_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA1, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA1, PeripheralId::TC0, SignalId::signal_tiob0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa1_tc0_tiob0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid23, PinId::none, ClockGateId::gate_tc0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA1, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA20, PeripheralId::AFEC0, SignalId::signal_ad9> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa20_afec0_ad9;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid29, PinId::none, ClockGateId::gate_afec0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA20, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA20, PeripheralId::PWM0, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa20_pwm0_pwml1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA20, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA21, PeripheralId::AFEC0, SignalId::signal_ad1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa21_afec0_ad1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid29, PinId::none, ClockGateId::gate_afec0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA21, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA21, PeripheralId::GPIOA, SignalId::signal_piodcen2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa21_gpioa_piodcen2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10, PinId::none, ClockGateId::gate_gpioa, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA21, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA21, PeripheralId::PWM1, SignalId::signal_pwmfi0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa21_pwm1_pwmfi0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA21, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA21, PeripheralId::USART1, SignalId::signal_rxd1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa21_usart1_rxd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid14, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA21, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA22, PeripheralId::GPIOA, SignalId::signal_piodcclk> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa22_gpioa_piodcclk;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10, PinId::none, ClockGateId::gate_gpioa, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA22, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA22, PeripheralId::PWM0, SignalId::signal_pwmextrg1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa22_pwm0_pwmextrg1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA22, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA23, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa23_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA23, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA23, PeripheralId::PWM1, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa23_pwm1_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA23, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PA23, PeripheralId::USART1, SignalId::signal_sck1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa23_usart1_sck1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid14, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA23, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA24, PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa24_pwm0_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA24, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA24, PeripheralId::USART1, SignalId::signal_rts1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa24_usart1_rts1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid14, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA24, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA25, PeripheralId::HSMCI, SignalId::signal_mcck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa25_hsmci_mcck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid18, PinId::none, ClockGateId::gate_hsmci, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA25, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PA25, PeripheralId::PWM0, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa25_pwm0_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA25, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA25, PeripheralId::USART1, SignalId::signal_cts1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa25_usart1_cts1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid14, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA25, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA26, PeripheralId::HSMCI, SignalId::signal_mcda2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa26_hsmci_mcda2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid18, PinId::none, ClockGateId::gate_hsmci, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA26, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA26, PeripheralId::PWM1, SignalId::signal_pwmfi1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa26_pwm1_pwmfi1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA26, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PA26, PeripheralId::TC0, SignalId::signal_tioa2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa26_tc0_tioa2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid23, PinId::none, ClockGateId::gate_tc0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA26, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA26, PeripheralId::USART1, SignalId::signal_dcd1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa26_usart1_dcd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid14, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA26, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA27, PeripheralId::HSMCI, SignalId::signal_mcda3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa27_hsmci_mcda3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid18, PinId::none, ClockGateId::gate_hsmci, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA27, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA27, PeripheralId::TC0, SignalId::signal_tiob2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa27_tc0_tiob2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid23, PinId::none, ClockGateId::gate_tc0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA27, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA27, PeripheralId::USART1, SignalId::signal_dtr1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa27_usart1_dtr1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid14, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA27, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA28, PeripheralId::HSMCI, SignalId::signal_mccda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa28_hsmci_mccda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid18, PinId::none, ClockGateId::gate_hsmci, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA28, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA28, PeripheralId::PWM1, SignalId::signal_pwmfi2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa28_pwm1_pwmfi2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA28, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PA28, PeripheralId::TC0, SignalId::signal_tclk1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa28_tc0_tclk1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid23, PinId::none, ClockGateId::gate_tc0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA28, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA28, PeripheralId::USART1, SignalId::signal_dsr1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa28_usart1_dsr1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid14, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA28, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA2, PeripheralId::DACC, SignalId::signal_datrg> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa2_dacc_datrg;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid30, PinId::none, ClockGateId::gate_dacc, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA2, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA2, PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa2_pwm0_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA2, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA30, PeripheralId::HSMCI, SignalId::signal_mcda0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa30_hsmci_mcda0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid18, PinId::none, ClockGateId::gate_hsmci, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA30, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA30, PeripheralId::PWM0, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa30_pwm0_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA30, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA30, PeripheralId::PWM1, SignalId::signal_pwmextrg0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa30_pwm1_pwmextrg0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA30, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA31, PeripheralId::HSMCI, SignalId::signal_mcda1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa31_hsmci_mcda1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid18, PinId::none, ClockGateId::gate_hsmci, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA31, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA31, PeripheralId::PWM1, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa31_pwm1_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA31, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PA31, PeripheralId::SPI0, SignalId::signal_npcs1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa31_spi0_npcs1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid21, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA31, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA3, PeripheralId::GPIOA, SignalId::signal_piodc0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa3_gpioa_piodc0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10, PinId::none, ClockGateId::gate_gpioa, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA3, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA3, PeripheralId::TWIHS0, SignalId::signal_twd0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa3_twihs0_twd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid19, PinId::none, ClockGateId::gate_twihs0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA3, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA3, PeripheralId::USART1, SignalId::signal_loncol1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa3_usart1_loncol1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid14, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA3, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA4, PeripheralId::GPIOA, SignalId::signal_piodc1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa4_gpioa_piodc1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10, PinId::none, ClockGateId::gate_gpioa, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA4, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA4, PeripheralId::TC0, SignalId::signal_tclk0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa4_tc0_tclk0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid23, PinId::none, ClockGateId::gate_tc0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA4, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA4, PeripheralId::TWIHS0, SignalId::signal_twck0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa4_twihs0_twck0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid19, PinId::none, ClockGateId::gate_twihs0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA4, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA4, PeripheralId::UART1, SignalId::signal_utxd1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa4_uart1_utxd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid8, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA4, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA5, PeripheralId::GPIOA, SignalId::signal_piodc2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa5_gpioa_piodc2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10, PinId::none, ClockGateId::gate_gpioa, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA5, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA5, PeripheralId::PWM1, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa5_pwm1_pwml3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA5, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA5, PeripheralId::UART1, SignalId::signal_urxd1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa5_uart1_urxd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid8, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA5, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA7, PeripheralId::PWM0, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa7_pwm0_pwmh3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA7, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA8, PeripheralId::AFEC0, SignalId::signal_adtrg> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa8_afec0_adtrg;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid29, PinId::none, ClockGateId::gate_afec0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA8, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA8, PeripheralId::PWM1, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa8_pwm1_pwmh3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA8, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA9, PeripheralId::GPIOA, SignalId::signal_piodc3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa9_gpioa_piodc3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10, PinId::none, ClockGateId::gate_gpioa, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA9, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PA9, PeripheralId::PWM0, SignalId::signal_pwmfi0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa9_pwm0_pwmfi0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA9, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PA9, PeripheralId::UART0, SignalId::signal_urxd0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa9_uart0_urxd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid7, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA9, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PB0, PeripheralId::AFEC0, SignalId::signal_ad10> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb0_afec0_ad10;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid29, PinId::none, ClockGateId::gate_afec0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB0, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PB0, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb0_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB0, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PB0, PeripheralId::RTC, SignalId::signal_rtcout0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb0_rtc_rtcout0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::none, PinId::none, ClockGateId::gate_rtc, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB0, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PB0, PeripheralId::USART0, SignalId::signal_rxd0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb0_usart0_rxd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid13, PinId::none, ClockGateId::gate_usart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB0, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PB12, PeripheralId::GMAC, SignalId::signal_gtsucomp> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb12_gmac_gtsucomp;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB12, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PB12, PeripheralId::PWM0, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb12_pwm0_pwml1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB12, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PB13, PeripheralId::DACC, SignalId::signal_dac0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb13_dacc_dac0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid30, PinId::none, ClockGateId::gate_dacc, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB13, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PB13, PeripheralId::PWM0, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb13_pwm0_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB13, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PB13, PeripheralId::USART0, SignalId::signal_sck0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb13_usart0_sck0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid13, PinId::none, ClockGateId::gate_usart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB13, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PB1, PeripheralId::AFEC1, SignalId::signal_ad0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb1_afec1_ad0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid40, PinId::none, ClockGateId::gate_afec1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB1, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PB1, PeripheralId::GMAC, SignalId::signal_gtsucomp> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb1_gmac_gtsucomp;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB1, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PB1, PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb1_pwm0_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB1, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PB1, PeripheralId::RTC, SignalId::signal_rtcout1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb1_rtc_rtcout1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::none, PinId::none, ClockGateId::gate_rtc, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB1, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PB1, PeripheralId::USART0, SignalId::signal_txd0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb1_usart0_txd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid13, PinId::none, ClockGateId::gate_usart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB1, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PB2, PeripheralId::AFEC0, SignalId::signal_ad5> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb2_afec0_ad5;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid29, PinId::none, ClockGateId::gate_afec0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB2, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PB2, PeripheralId::MCAN0, SignalId::signal_cantx0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb2_mcan0_cantx0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid35, PinId::none, ClockGateId::gate_mcan0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB2, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PB2, PeripheralId::SPI0, SignalId::signal_npcs0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb2_spi0_npcs0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid21, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB2, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PB2, PeripheralId::USART0, SignalId::signal_cts0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb2_usart0_cts0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid13, PinId::none, ClockGateId::gate_usart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB2, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PB3, PeripheralId::AFEC0, SignalId::signal_ad2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb3_afec0_ad2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid29, PinId::none, ClockGateId::gate_afec0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB3, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PB3, PeripheralId::MCAN0, SignalId::signal_canrx0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb3_mcan0_canrx0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid35, PinId::none, ClockGateId::gate_mcan0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB3, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PB3, PeripheralId::USART0, SignalId::signal_rts0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb3_usart0_rts0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid13, PinId::none, ClockGateId::gate_usart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB3, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PB4, PeripheralId::PWM0, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb4_pwm0_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB4, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PB4, PeripheralId::TWIHS1, SignalId::signal_twd1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb4_twihs1_twd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid20, PinId::none, ClockGateId::gate_twihs1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB4, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PB4, PeripheralId::USART1, SignalId::signal_txd1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb4_usart1_txd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid14, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB4, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PB5, PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb5_pwm0_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB5, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PB5, PeripheralId::TWIHS1, SignalId::signal_twck1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb5_twihs1_twck1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid20, PinId::none, ClockGateId::gate_twihs1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB5, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD0, PeripheralId::DACC, SignalId::signal_dac1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd0_dacc_dac1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid30, PinId::none, ClockGateId::gate_dacc, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD0, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PD0, PeripheralId::GMAC, SignalId::signal_gtxck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd0_gmac_gtxck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD0, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD0, PeripheralId::PWM1, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd0_pwm1_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD0, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD0, PeripheralId::USART0, SignalId::signal_dcd0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd0_usart0_dcd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid13, PinId::none, ClockGateId::gate_usart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD0, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PD10, PeripheralId::GMAC, SignalId::signal_gcrs> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd10_gmac_gcrs;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD10, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD10, PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd10_pwm0_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD10, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD11, PeripheralId::GMAC, SignalId::signal_grx2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd11_gmac_grx2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD11, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD11, PeripheralId::GMAC, SignalId::signal_gtsucomp> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd11_gmac_gtsucomp;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD11, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD11, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd11_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD11, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD12, PeripheralId::GMAC, SignalId::signal_grx3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd12_gmac_grx3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD12, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD12, PeripheralId::MCAN1, SignalId::signal_cantx1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd12_mcan1_cantx1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid37, PinId::none, ClockGateId::gate_mcan1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD12, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD12, PeripheralId::SPI0, SignalId::signal_npcs2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd12_spi0_npcs2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid21, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD12, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD13, PeripheralId::GMAC, SignalId::signal_gcol> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd13_gmac_gcol;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD13, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD14, PeripheralId::GMAC, SignalId::signal_grxck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd14_gmac_grxck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD14, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD15, PeripheralId::GMAC, SignalId::signal_gtx2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd15_gmac_gtx2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD15, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD15, PeripheralId::USART2, SignalId::signal_rxd2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd15_usart2_rxd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid15, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD15, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD16, PeripheralId::GMAC, SignalId::signal_gtx3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd16_gmac_gtx3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD16, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD16, PeripheralId::USART2, SignalId::signal_txd2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd16_usart2_txd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid15, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD16, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD17, PeripheralId::GMAC, SignalId::signal_gtxer> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd17_gmac_gtxer;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD17, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD17, PeripheralId::USART2, SignalId::signal_sck2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd17_usart2_sck2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid15, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD17, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD18, PeripheralId::UART4, SignalId::signal_urxd4> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd18_uart4_urxd4;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid46, PinId::none, ClockGateId::gate_uart4, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD18, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD18, PeripheralId::USART2, SignalId::signal_rts2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd18_usart2_rts2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid15, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD18, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD19, PeripheralId::UART4, SignalId::signal_utxd4> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd19_uart4_utxd4;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid46, PinId::none, ClockGateId::gate_uart4, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD19, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD19, PeripheralId::USART2, SignalId::signal_cts2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd19_usart2_cts2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid15, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD19, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD1, PeripheralId::GMAC, SignalId::signal_gtxen> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd1_gmac_gtxen;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD1, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD1, PeripheralId::PWM1, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd1_pwm1_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD1, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD1, PeripheralId::USART0, SignalId::signal_dtr0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd1_usart0_dtr0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid13, PinId::none, ClockGateId::gate_usart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD1, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PD20, PeripheralId::GMAC, SignalId::signal_gtsucomp> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd20_gmac_gtsucomp;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD20, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD20, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd20_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD20, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD20, PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd20_spi0_miso;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid21, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD20, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD21, PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd21_pwm0_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD21, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD21, PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd21_spi0_mosi;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid21, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD21, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD21, PeripheralId::TC3, SignalId::signal_tioa11> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd21_tc3_tioa11;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid50, PinId::none, ClockGateId::gate_tc3, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD21, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD22, PeripheralId::PWM0, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd22_pwm0_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD22, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD22, PeripheralId::SPI0, SignalId::signal_spck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd22_spi0_spck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid21, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD22, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD22, PeripheralId::TC3, SignalId::signal_tiob11> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd22_tc3_tiob11;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid50, PinId::none, ClockGateId::gate_tc3, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD22, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD24, PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd24_pwm0_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD24, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD24, PeripheralId::TC3, SignalId::signal_tclk11> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd24_tc3_tclk11;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid50, PinId::none, ClockGateId::gate_tc3, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD24, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD25, PeripheralId::PWM0, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd25_pwm0_pwml1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD25, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD25, PeripheralId::SPI0, SignalId::signal_npcs1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd25_spi0_npcs1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid21, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD25, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD25, PeripheralId::UART2, SignalId::signal_urxd2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd25_uart2_urxd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid44, PinId::none, ClockGateId::gate_uart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD25, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD26, PeripheralId::PWM0, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd26_pwm0_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD26, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD26, PeripheralId::UART1, SignalId::signal_utxd1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd26_uart1_utxd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid8, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD26, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PD26, PeripheralId::UART2, SignalId::signal_utxd2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd26_uart2_utxd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid44, PinId::none, ClockGateId::gate_uart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD26, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD27, PeripheralId::PWM0, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd27_pwm0_pwml3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD27, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD27, PeripheralId::SPI0, SignalId::signal_npcs3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd27_spi0_npcs3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid21, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD27, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD27, PeripheralId::TWIHS2, SignalId::signal_twd2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd27_twihs2_twd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid41, PinId::none, ClockGateId::gate_twihs2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD27, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD28, PeripheralId::MCAN1, SignalId::signal_canrx1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd28_mcan1_canrx1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid37, PinId::none, ClockGateId::gate_mcan1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD28, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD28, PeripheralId::TWIHS2, SignalId::signal_twck2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd28_twihs2_twck2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid41, PinId::none, ClockGateId::gate_twihs2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD28, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD28, PeripheralId::UART3, SignalId::signal_urxd3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd28_uart3_urxd3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid45, PinId::none, ClockGateId::gate_uart3, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD28, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD2, PeripheralId::GMAC, SignalId::signal_gtx0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd2_gmac_gtx0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD2, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD2, PeripheralId::PWM1, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd2_pwm1_pwml1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD2, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD2, PeripheralId::USART0, SignalId::signal_dsr0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd2_usart0_dsr0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid13, PinId::none, ClockGateId::gate_usart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD2, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PD30, PeripheralId::AFEC0, SignalId::signal_ad0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd30_afec0_ad0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid29, PinId::none, ClockGateId::gate_afec0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD30, ClockGateId::none, ResetId::none, 101},
  }};
};

template<>
struct RouteTraits<PinId::PD30, PeripheralId::UART3, SignalId::signal_utxd3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd30_uart3_utxd3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid45, PinId::none, ClockGateId::gate_uart3, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD30, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD31, PeripheralId::QSPI, SignalId::signal_qio3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd31_qspi_qio3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid43, PinId::none, ClockGateId::gate_qspi, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD31, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD31, PeripheralId::UART3, SignalId::signal_utxd3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd31_uart3_utxd3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid45, PinId::none, ClockGateId::gate_uart3, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD31, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD3, PeripheralId::GMAC, SignalId::signal_gtx1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd3_gmac_gtx1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD3, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD3, PeripheralId::PWM1, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd3_pwm1_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD3, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD3, PeripheralId::UART4, SignalId::signal_utxd4> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd3_uart4_utxd4;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid46, PinId::none, ClockGateId::gate_uart4, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD3, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD3, PeripheralId::USART0, SignalId::signal_ri0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd3_usart0_ri0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid13, PinId::none, ClockGateId::gate_usart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD3, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PD4, PeripheralId::GMAC, SignalId::signal_grxdv> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd4_gmac_grxdv;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD4, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD4, PeripheralId::PWM1, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd4_pwm1_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD4, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD4, PeripheralId::USART2, SignalId::signal_dcd2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd4_usart2_dcd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid15, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD4, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PD5, PeripheralId::GMAC, SignalId::signal_grx0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd5_gmac_grx0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD5, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD5, PeripheralId::PWM1, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd5_pwm1_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD5, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD5, PeripheralId::USART2, SignalId::signal_dtr2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd5_usart2_dtr2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid15, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD5, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PD6, PeripheralId::GMAC, SignalId::signal_grx1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd6_gmac_grx1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD6, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD6, PeripheralId::PWM1, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd6_pwm1_pwml3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD6, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD6, PeripheralId::USART2, SignalId::signal_dsr2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd6_usart2_dsr2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid15, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD6, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PD7, PeripheralId::GMAC, SignalId::signal_grxer> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd7_gmac_grxer;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD7, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD7, PeripheralId::PWM1, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd7_pwm1_pwmh3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60, PinId::none, ClockGateId::gate_pwm1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD7, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD7, PeripheralId::USART2, SignalId::signal_ri2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd7_usart2_ri2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid15, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD7, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PD8, PeripheralId::GMAC, SignalId::signal_gmdc> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd8_gmac_gmdc;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD8, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD8, PeripheralId::PWM0, SignalId::signal_pwmfi1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd8_pwm0_pwmfi1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD8, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PD9, PeripheralId::AFEC1, SignalId::signal_adtrg> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd9_afec1_adtrg;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid40, PinId::none, ClockGateId::gate_afec1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD9, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::PD9, PeripheralId::GMAC, SignalId::signal_gmdio> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd9_gmac_gmdio;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39, PinId::none, ClockGateId::gate_gmac, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD9, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PD9, PeripheralId::PWM0, SignalId::signal_pwmfi2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pd9_pwm0_pwmfi2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_microchip_pmc_p, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31, PinId::none, ClockGateId::gate_pwm0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_sam_pio_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PD9, ClockGateId::none, ResetId::none, 1},
  }};
};

inline constexpr std::array<RouteDescriptor, 189> kRuntimeRoutes = {{
  {RouteId::candidate_pa0_pwm0_pwmh0, PinId::PA0, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa0_tc0_tioa0, PinId::PA0, PeripheralId::TC0, SignalId::signal_tioa0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa10_gpioa_piodc4, PinId::PA10, PeripheralId::GPIOA, SignalId::signal_piodc4, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa10_pwm0_pwmextrg0, PinId::PA10, PeripheralId::PWM0, SignalId::signal_pwmextrg0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa10_uart0_utxd0, PinId::PA10, PeripheralId::UART0, SignalId::signal_utxd0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa11_gpioa_piodc5, PinId::PA11, PeripheralId::GPIOA, SignalId::signal_piodc5, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa11_pwm0_pwmh0, PinId::PA11, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa11_pwm1_pwml0, PinId::PA11, PeripheralId::PWM1, SignalId::signal_pwml0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa11_qspi_qcs, PinId::PA11, PeripheralId::QSPI, SignalId::signal_qcs, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa12_gpioa_piodc6, PinId::PA12, PeripheralId::GPIOA, SignalId::signal_piodc6, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa12_pwm0_pwmh1, PinId::PA12, PeripheralId::PWM0, SignalId::signal_pwmh1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa12_pwm1_pwmh0, PinId::PA12, PeripheralId::PWM1, SignalId::signal_pwmh0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa12_qspi_qio1, PinId::PA12, PeripheralId::QSPI, SignalId::signal_qio1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa13_gpioa_piodc7, PinId::PA13, PeripheralId::GPIOA, SignalId::signal_piodc7, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa13_pwm0_pwmh2, PinId::PA13, PeripheralId::PWM0, SignalId::signal_pwmh2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa13_pwm1_pwml1, PinId::PA13, PeripheralId::PWM1, SignalId::signal_pwml1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa13_qspi_qio0, PinId::PA13, PeripheralId::QSPI, SignalId::signal_qio0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa14_gpioa_piodcen1, PinId::PA14, PeripheralId::GPIOA, SignalId::signal_piodcen1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa14_pwm0_pwmh3, PinId::PA14, PeripheralId::PWM0, SignalId::signal_pwmh3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa14_pwm1_pwmh1, PinId::PA14, PeripheralId::PWM1, SignalId::signal_pwmh1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa14_qspi_qsck, PinId::PA14, PeripheralId::QSPI, SignalId::signal_qsck, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa15_pwm0_pwml3, PinId::PA15, PeripheralId::PWM0, SignalId::signal_pwml3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa15_tc0_tioa1, PinId::PA15, PeripheralId::TC0, SignalId::signal_tioa1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa16_pwm0_pwml2, PinId::PA16, PeripheralId::PWM0, SignalId::signal_pwml2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa16_tc0_tiob1, PinId::PA16, PeripheralId::TC0, SignalId::signal_tiob1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa17_afec0_ad6, PinId::PA17, PeripheralId::AFEC0, SignalId::signal_ad6, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa17_pwm0_pwmh3, PinId::PA17, PeripheralId::PWM0, SignalId::signal_pwmh3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa17_qspi_qio2, PinId::PA17, PeripheralId::QSPI, SignalId::signal_qio2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa18_afec0_ad7, PinId::PA18, PeripheralId::AFEC0, SignalId::signal_ad7, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa18_pwm1_pwmextrg1, PinId::PA18, PeripheralId::PWM1, SignalId::signal_pwmextrg1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa19_afec0_ad8, PinId::PA19, PeripheralId::AFEC0, SignalId::signal_ad8, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa19_pwm0_pwml0, PinId::PA19, PeripheralId::PWM0, SignalId::signal_pwml0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa1_pwm0_pwml0, PinId::PA1, PeripheralId::PWM0, SignalId::signal_pwml0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa1_tc0_tiob0, PinId::PA1, PeripheralId::TC0, SignalId::signal_tiob0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa20_afec0_ad9, PinId::PA20, PeripheralId::AFEC0, SignalId::signal_ad9, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa20_pwm0_pwml1, PinId::PA20, PeripheralId::PWM0, SignalId::signal_pwml1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa21_afec0_ad1, PinId::PA21, PeripheralId::AFEC0, SignalId::signal_ad1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa21_gpioa_piodcen2, PinId::PA21, PeripheralId::GPIOA, SignalId::signal_piodcen2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa21_pwm1_pwmfi0, PinId::PA21, PeripheralId::PWM1, SignalId::signal_pwmfi0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa21_usart1_rxd1, PinId::PA21, PeripheralId::USART1, SignalId::signal_rxd1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa22_gpioa_piodcclk, PinId::PA22, PeripheralId::GPIOA, SignalId::signal_piodcclk, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa22_pwm0_pwmextrg1, PinId::PA22, PeripheralId::PWM0, SignalId::signal_pwmextrg1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa23_pwm0_pwmh0, PinId::PA23, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa23_pwm1_pwml2, PinId::PA23, PeripheralId::PWM1, SignalId::signal_pwml2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa23_usart1_sck1, PinId::PA23, PeripheralId::USART1, SignalId::signal_sck1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa24_pwm0_pwmh1, PinId::PA24, PeripheralId::PWM0, SignalId::signal_pwmh1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa24_usart1_rts1, PinId::PA24, PeripheralId::USART1, SignalId::signal_rts1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa25_hsmci_mcck, PinId::PA25, PeripheralId::HSMCI, SignalId::signal_mcck, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa25_pwm0_pwmh2, PinId::PA25, PeripheralId::PWM0, SignalId::signal_pwmh2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa25_usart1_cts1, PinId::PA25, PeripheralId::USART1, SignalId::signal_cts1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa26_hsmci_mcda2, PinId::PA26, PeripheralId::HSMCI, SignalId::signal_mcda2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa26_pwm1_pwmfi1, PinId::PA26, PeripheralId::PWM1, SignalId::signal_pwmfi1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa26_tc0_tioa2, PinId::PA26, PeripheralId::TC0, SignalId::signal_tioa2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa26_usart1_dcd1, PinId::PA26, PeripheralId::USART1, SignalId::signal_dcd1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa27_hsmci_mcda3, PinId::PA27, PeripheralId::HSMCI, SignalId::signal_mcda3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa27_tc0_tiob2, PinId::PA27, PeripheralId::TC0, SignalId::signal_tiob2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa27_usart1_dtr1, PinId::PA27, PeripheralId::USART1, SignalId::signal_dtr1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa28_hsmci_mccda, PinId::PA28, PeripheralId::HSMCI, SignalId::signal_mccda, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa28_pwm1_pwmfi2, PinId::PA28, PeripheralId::PWM1, SignalId::signal_pwmfi2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa28_tc0_tclk1, PinId::PA28, PeripheralId::TC0, SignalId::signal_tclk1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa28_usart1_dsr1, PinId::PA28, PeripheralId::USART1, SignalId::signal_dsr1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa2_dacc_datrg, PinId::PA2, PeripheralId::DACC, SignalId::signal_datrg, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa2_pwm0_pwmh1, PinId::PA2, PeripheralId::PWM0, SignalId::signal_pwmh1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa30_hsmci_mcda0, PinId::PA30, PeripheralId::HSMCI, SignalId::signal_mcda0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa30_pwm0_pwml2, PinId::PA30, PeripheralId::PWM0, SignalId::signal_pwml2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa30_pwm1_pwmextrg0, PinId::PA30, PeripheralId::PWM1, SignalId::signal_pwmextrg0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa31_hsmci_mcda1, PinId::PA31, PeripheralId::HSMCI, SignalId::signal_mcda1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa31_pwm1_pwmh2, PinId::PA31, PeripheralId::PWM1, SignalId::signal_pwmh2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa31_spi0_npcs1, PinId::PA31, PeripheralId::SPI0, SignalId::signal_npcs1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa3_gpioa_piodc0, PinId::PA3, PeripheralId::GPIOA, SignalId::signal_piodc0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa3_twihs0_twd0, PinId::PA3, PeripheralId::TWIHS0, SignalId::signal_twd0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa3_usart1_loncol1, PinId::PA3, PeripheralId::USART1, SignalId::signal_loncol1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa4_gpioa_piodc1, PinId::PA4, PeripheralId::GPIOA, SignalId::signal_piodc1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa4_tc0_tclk0, PinId::PA4, PeripheralId::TC0, SignalId::signal_tclk0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa4_twihs0_twck0, PinId::PA4, PeripheralId::TWIHS0, SignalId::signal_twck0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa4_uart1_utxd1, PinId::PA4, PeripheralId::UART1, SignalId::signal_utxd1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa5_gpioa_piodc2, PinId::PA5, PeripheralId::GPIOA, SignalId::signal_piodc2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa5_pwm1_pwml3, PinId::PA5, PeripheralId::PWM1, SignalId::signal_pwml3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa5_uart1_urxd1, PinId::PA5, PeripheralId::UART1, SignalId::signal_urxd1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa7_pwm0_pwmh3, PinId::PA7, PeripheralId::PWM0, SignalId::signal_pwmh3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa8_afec0_adtrg, PinId::PA8, PeripheralId::AFEC0, SignalId::signal_adtrg, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa8_pwm1_pwmh3, PinId::PA8, PeripheralId::PWM1, SignalId::signal_pwmh3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa9_gpioa_piodc3, PinId::PA9, PeripheralId::GPIOA, SignalId::signal_piodc3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa9_pwm0_pwmfi0, PinId::PA9, PeripheralId::PWM0, SignalId::signal_pwmfi0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa9_uart0_urxd0, PinId::PA9, PeripheralId::UART0, SignalId::signal_urxd0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb0_afec0_ad10, PinId::PB0, PeripheralId::AFEC0, SignalId::signal_ad10, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb0_pwm0_pwmh0, PinId::PB0, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb0_rtc_rtcout0, PinId::PB0, PeripheralId::RTC, SignalId::signal_rtcout0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb0_usart0_rxd0, PinId::PB0, PeripheralId::USART0, SignalId::signal_rxd0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb12_gmac_gtsucomp, PinId::PB12, PeripheralId::GMAC, SignalId::signal_gtsucomp, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb12_pwm0_pwml1, PinId::PB12, PeripheralId::PWM0, SignalId::signal_pwml1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb13_dacc_dac0, PinId::PB13, PeripheralId::DACC, SignalId::signal_dac0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb13_pwm0_pwml2, PinId::PB13, PeripheralId::PWM0, SignalId::signal_pwml2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb13_usart0_sck0, PinId::PB13, PeripheralId::USART0, SignalId::signal_sck0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb1_afec1_ad0, PinId::PB1, PeripheralId::AFEC1, SignalId::signal_ad0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb1_gmac_gtsucomp, PinId::PB1, PeripheralId::GMAC, SignalId::signal_gtsucomp, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb1_pwm0_pwmh1, PinId::PB1, PeripheralId::PWM0, SignalId::signal_pwmh1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb1_rtc_rtcout1, PinId::PB1, PeripheralId::RTC, SignalId::signal_rtcout1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb1_usart0_txd0, PinId::PB1, PeripheralId::USART0, SignalId::signal_txd0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb2_afec0_ad5, PinId::PB2, PeripheralId::AFEC0, SignalId::signal_ad5, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb2_mcan0_cantx0, PinId::PB2, PeripheralId::MCAN0, SignalId::signal_cantx0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb2_spi0_npcs0, PinId::PB2, PeripheralId::SPI0, SignalId::signal_npcs0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb2_usart0_cts0, PinId::PB2, PeripheralId::USART0, SignalId::signal_cts0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb3_afec0_ad2, PinId::PB3, PeripheralId::AFEC0, SignalId::signal_ad2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb3_mcan0_canrx0, PinId::PB3, PeripheralId::MCAN0, SignalId::signal_canrx0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb3_usart0_rts0, PinId::PB3, PeripheralId::USART0, SignalId::signal_rts0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb4_pwm0_pwmh2, PinId::PB4, PeripheralId::PWM0, SignalId::signal_pwmh2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb4_twihs1_twd1, PinId::PB4, PeripheralId::TWIHS1, SignalId::signal_twd1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb4_usart1_txd1, PinId::PB4, PeripheralId::USART1, SignalId::signal_txd1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb5_pwm0_pwml0, PinId::PB5, PeripheralId::PWM0, SignalId::signal_pwml0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pb5_twihs1_twck1, PinId::PB5, PeripheralId::TWIHS1, SignalId::signal_twck1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd0_dacc_dac1, PinId::PD0, PeripheralId::DACC, SignalId::signal_dac1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd0_gmac_gtxck, PinId::PD0, PeripheralId::GMAC, SignalId::signal_gtxck, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd0_pwm1_pwml0, PinId::PD0, PeripheralId::PWM1, SignalId::signal_pwml0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd0_usart0_dcd0, PinId::PD0, PeripheralId::USART0, SignalId::signal_dcd0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd10_gmac_gcrs, PinId::PD10, PeripheralId::GMAC, SignalId::signal_gcrs, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd10_pwm0_pwml0, PinId::PD10, PeripheralId::PWM0, SignalId::signal_pwml0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd11_gmac_grx2, PinId::PD11, PeripheralId::GMAC, SignalId::signal_grx2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd11_gmac_gtsucomp, PinId::PD11, PeripheralId::GMAC, SignalId::signal_gtsucomp, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd11_pwm0_pwmh0, PinId::PD11, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd12_gmac_grx3, PinId::PD12, PeripheralId::GMAC, SignalId::signal_grx3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd12_mcan1_cantx1, PinId::PD12, PeripheralId::MCAN1, SignalId::signal_cantx1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd12_spi0_npcs2, PinId::PD12, PeripheralId::SPI0, SignalId::signal_npcs2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd13_gmac_gcol, PinId::PD13, PeripheralId::GMAC, SignalId::signal_gcol, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd14_gmac_grxck, PinId::PD14, PeripheralId::GMAC, SignalId::signal_grxck, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd15_gmac_gtx2, PinId::PD15, PeripheralId::GMAC, SignalId::signal_gtx2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd15_usart2_rxd2, PinId::PD15, PeripheralId::USART2, SignalId::signal_rxd2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd16_gmac_gtx3, PinId::PD16, PeripheralId::GMAC, SignalId::signal_gtx3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd16_usart2_txd2, PinId::PD16, PeripheralId::USART2, SignalId::signal_txd2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd17_gmac_gtxer, PinId::PD17, PeripheralId::GMAC, SignalId::signal_gtxer, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd17_usart2_sck2, PinId::PD17, PeripheralId::USART2, SignalId::signal_sck2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd18_uart4_urxd4, PinId::PD18, PeripheralId::UART4, SignalId::signal_urxd4, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd18_usart2_rts2, PinId::PD18, PeripheralId::USART2, SignalId::signal_rts2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd19_uart4_utxd4, PinId::PD19, PeripheralId::UART4, SignalId::signal_utxd4, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd19_usart2_cts2, PinId::PD19, PeripheralId::USART2, SignalId::signal_cts2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd1_gmac_gtxen, PinId::PD1, PeripheralId::GMAC, SignalId::signal_gtxen, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd1_pwm1_pwmh0, PinId::PD1, PeripheralId::PWM1, SignalId::signal_pwmh0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd1_usart0_dtr0, PinId::PD1, PeripheralId::USART0, SignalId::signal_dtr0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd20_gmac_gtsucomp, PinId::PD20, PeripheralId::GMAC, SignalId::signal_gtsucomp, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd20_pwm0_pwmh0, PinId::PD20, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd20_spi0_miso, PinId::PD20, PeripheralId::SPI0, SignalId::signal_miso, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd21_pwm0_pwmh1, PinId::PD21, PeripheralId::PWM0, SignalId::signal_pwmh1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd21_spi0_mosi, PinId::PD21, PeripheralId::SPI0, SignalId::signal_mosi, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd21_tc3_tioa11, PinId::PD21, PeripheralId::TC3, SignalId::signal_tioa11, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd22_pwm0_pwmh2, PinId::PD22, PeripheralId::PWM0, SignalId::signal_pwmh2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd22_spi0_spck, PinId::PD22, PeripheralId::SPI0, SignalId::signal_spck, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd22_tc3_tiob11, PinId::PD22, PeripheralId::TC3, SignalId::signal_tiob11, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd24_pwm0_pwml0, PinId::PD24, PeripheralId::PWM0, SignalId::signal_pwml0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd24_tc3_tclk11, PinId::PD24, PeripheralId::TC3, SignalId::signal_tclk11, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd25_pwm0_pwml1, PinId::PD25, PeripheralId::PWM0, SignalId::signal_pwml1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd25_spi0_npcs1, PinId::PD25, PeripheralId::SPI0, SignalId::signal_npcs1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd25_uart2_urxd2, PinId::PD25, PeripheralId::UART2, SignalId::signal_urxd2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd26_pwm0_pwml2, PinId::PD26, PeripheralId::PWM0, SignalId::signal_pwml2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd26_uart1_utxd1, PinId::PD26, PeripheralId::UART1, SignalId::signal_utxd1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd26_uart2_utxd2, PinId::PD26, PeripheralId::UART2, SignalId::signal_utxd2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd27_pwm0_pwml3, PinId::PD27, PeripheralId::PWM0, SignalId::signal_pwml3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd27_spi0_npcs3, PinId::PD27, PeripheralId::SPI0, SignalId::signal_npcs3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd27_twihs2_twd2, PinId::PD27, PeripheralId::TWIHS2, SignalId::signal_twd2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd28_mcan1_canrx1, PinId::PD28, PeripheralId::MCAN1, SignalId::signal_canrx1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd28_twihs2_twck2, PinId::PD28, PeripheralId::TWIHS2, SignalId::signal_twck2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd28_uart3_urxd3, PinId::PD28, PeripheralId::UART3, SignalId::signal_urxd3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd2_gmac_gtx0, PinId::PD2, PeripheralId::GMAC, SignalId::signal_gtx0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd2_pwm1_pwml1, PinId::PD2, PeripheralId::PWM1, SignalId::signal_pwml1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd2_usart0_dsr0, PinId::PD2, PeripheralId::USART0, SignalId::signal_dsr0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd30_afec0_ad0, PinId::PD30, PeripheralId::AFEC0, SignalId::signal_ad0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd30_uart3_utxd3, PinId::PD30, PeripheralId::UART3, SignalId::signal_utxd3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd31_qspi_qio3, PinId::PD31, PeripheralId::QSPI, SignalId::signal_qio3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd31_uart3_utxd3, PinId::PD31, PeripheralId::UART3, SignalId::signal_utxd3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd3_gmac_gtx1, PinId::PD3, PeripheralId::GMAC, SignalId::signal_gtx1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd3_pwm1_pwmh1, PinId::PD3, PeripheralId::PWM1, SignalId::signal_pwmh1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd3_uart4_utxd4, PinId::PD3, PeripheralId::UART4, SignalId::signal_utxd4, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd3_usart0_ri0, PinId::PD3, PeripheralId::USART0, SignalId::signal_ri0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd4_gmac_grxdv, PinId::PD4, PeripheralId::GMAC, SignalId::signal_grxdv, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd4_pwm1_pwml2, PinId::PD4, PeripheralId::PWM1, SignalId::signal_pwml2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd4_usart2_dcd2, PinId::PD4, PeripheralId::USART2, SignalId::signal_dcd2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd5_gmac_grx0, PinId::PD5, PeripheralId::GMAC, SignalId::signal_grx0, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd5_pwm1_pwmh2, PinId::PD5, PeripheralId::PWM1, SignalId::signal_pwmh2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd5_usart2_dtr2, PinId::PD5, PeripheralId::USART2, SignalId::signal_dtr2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd6_gmac_grx1, PinId::PD6, PeripheralId::GMAC, SignalId::signal_grx1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd6_pwm1_pwml3, PinId::PD6, PeripheralId::PWM1, SignalId::signal_pwml3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd6_usart2_dsr2, PinId::PD6, PeripheralId::USART2, SignalId::signal_dsr2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd7_gmac_grxer, PinId::PD7, PeripheralId::GMAC, SignalId::signal_grxer, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd7_pwm1_pwmh3, PinId::PD7, PeripheralId::PWM1, SignalId::signal_pwmh3, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd7_usart2_ri2, PinId::PD7, PeripheralId::USART2, SignalId::signal_ri2, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd8_gmac_gmdc, PinId::PD8, PeripheralId::GMAC, SignalId::signal_gmdc, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd8_pwm0_pwmfi1, PinId::PD8, PeripheralId::PWM0, SignalId::signal_pwmfi1, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd9_afec1_adtrg, PinId::PD9, PeripheralId::AFEC1, SignalId::signal_adtrg, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd9_gmac_gmdio, PinId::PD9, PeripheralId::GMAC, SignalId::signal_gmdio, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pd9_pwm0_pwmfi2, PinId::PD9, PeripheralId::PWM0, SignalId::signal_pwmfi2, RouteKindId::route_kind_peripheral_mux},
}};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
inline auto apply_route() noexcept -> void {
  static_assert(RouteTraits<Pin, Peripheral, Signal>::kPresent, "");
}

template<>
inline auto apply_route<PinId::PA0, PeripheralId::PWM0, SignalId::signal_pwmh0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 0);
}

template<>
inline auto apply_route<PinId::PA0, PeripheralId::TC0, SignalId::signal_tioa0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 0);
}

template<>
inline auto apply_route<PinId::PA10, PeripheralId::GPIOA, SignalId::signal_piodc4>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA10, PeripheralId::PWM0, SignalId::signal_pwmextrg0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 10);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 10);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA10, PeripheralId::UART0, SignalId::signal_utxd0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 10);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 10);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA11, PeripheralId::GPIOA, SignalId::signal_piodc5>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA11, PeripheralId::PWM0, SignalId::signal_pwmh0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 11);
}

template<>
inline auto apply_route<PinId::PA11, PeripheralId::PWM1, SignalId::signal_pwml0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 11);
}

template<>
inline auto apply_route<PinId::PA11, PeripheralId::QSPI, SignalId::signal_qcs>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 11);
}

template<>
inline auto apply_route<PinId::PA12, PeripheralId::GPIOA, SignalId::signal_piodc6>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA12, PeripheralId::PWM0, SignalId::signal_pwmh1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 12);
}

template<>
inline auto apply_route<PinId::PA12, PeripheralId::PWM1, SignalId::signal_pwmh0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 12);
}

template<>
inline auto apply_route<PinId::PA12, PeripheralId::QSPI, SignalId::signal_qio1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 12);
}

template<>
inline auto apply_route<PinId::PA13, PeripheralId::GPIOA, SignalId::signal_piodc7>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA13, PeripheralId::PWM0, SignalId::signal_pwmh2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 13);
}

template<>
inline auto apply_route<PinId::PA13, PeripheralId::PWM1, SignalId::signal_pwml1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 13);
}

template<>
inline auto apply_route<PinId::PA13, PeripheralId::QSPI, SignalId::signal_qio0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 13);
}

template<>
inline auto apply_route<PinId::PA14, PeripheralId::GPIOA, SignalId::signal_piodcen1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA14, PeripheralId::PWM0, SignalId::signal_pwmh3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 14);
}

template<>
inline auto apply_route<PinId::PA14, PeripheralId::PWM1, SignalId::signal_pwmh1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 14);
}

template<>
inline auto apply_route<PinId::PA14, PeripheralId::QSPI, SignalId::signal_qsck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 14);
}

template<>
inline auto apply_route<PinId::PA15, PeripheralId::PWM0, SignalId::signal_pwml3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 15);
}

template<>
inline auto apply_route<PinId::PA15, PeripheralId::TC0, SignalId::signal_tioa1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 15);
}

template<>
inline auto apply_route<PinId::PA16, PeripheralId::PWM0, SignalId::signal_pwml2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::PA16, PeripheralId::TC0, SignalId::signal_tiob1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::PA17, PeripheralId::AFEC0, SignalId::signal_ad6>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 29);
}

template<>
inline auto apply_route<PinId::PA17, PeripheralId::PWM0, SignalId::signal_pwmh3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::PA17, PeripheralId::QSPI, SignalId::signal_qio2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::PA18, PeripheralId::AFEC0, SignalId::signal_ad7>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 29);
}

template<>
inline auto apply_route<PinId::PA18, PeripheralId::PWM1, SignalId::signal_pwmextrg1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 18);
}

template<>
inline auto apply_route<PinId::PA19, PeripheralId::AFEC0, SignalId::signal_ad8>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 29);
}

template<>
inline auto apply_route<PinId::PA19, PeripheralId::PWM0, SignalId::signal_pwml0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 19);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 19);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 19);
}

template<>
inline auto apply_route<PinId::PA1, PeripheralId::PWM0, SignalId::signal_pwml0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 1);
}

template<>
inline auto apply_route<PinId::PA1, PeripheralId::TC0, SignalId::signal_tiob0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 1);
}

template<>
inline auto apply_route<PinId::PA20, PeripheralId::AFEC0, SignalId::signal_ad9>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 29);
}

template<>
inline auto apply_route<PinId::PA20, PeripheralId::PWM0, SignalId::signal_pwml1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 20);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 20);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 20);
}

template<>
inline auto apply_route<PinId::PA21, PeripheralId::AFEC0, SignalId::signal_ad1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 29);
}

template<>
inline auto apply_route<PinId::PA21, PeripheralId::GPIOA, SignalId::signal_piodcen2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA21, PeripheralId::PWM1, SignalId::signal_pwmfi0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 21);
}

template<>
inline auto apply_route<PinId::PA21, PeripheralId::USART1, SignalId::signal_rxd1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 21);
}

template<>
inline auto apply_route<PinId::PA22, PeripheralId::GPIOA, SignalId::signal_piodcclk>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA22, PeripheralId::PWM0, SignalId::signal_pwmextrg1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::PA23, PeripheralId::PWM0, SignalId::signal_pwmh0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::PA23, PeripheralId::PWM1, SignalId::signal_pwml2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::PA23, PeripheralId::USART1, SignalId::signal_sck1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::PA24, PeripheralId::PWM0, SignalId::signal_pwmh1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 24);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 24);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 24);
}

template<>
inline auto apply_route<PinId::PA24, PeripheralId::USART1, SignalId::signal_rts1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 24);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 24);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 24);
}

template<>
inline auto apply_route<PinId::PA25, PeripheralId::HSMCI, SignalId::signal_mcck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 25);
}

template<>
inline auto apply_route<PinId::PA25, PeripheralId::PWM0, SignalId::signal_pwmh2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 25);
}

template<>
inline auto apply_route<PinId::PA25, PeripheralId::USART1, SignalId::signal_cts1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 25);
}

template<>
inline auto apply_route<PinId::PA26, PeripheralId::HSMCI, SignalId::signal_mcda2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 26);
}

template<>
inline auto apply_route<PinId::PA26, PeripheralId::PWM1, SignalId::signal_pwmfi1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 26);
}

template<>
inline auto apply_route<PinId::PA26, PeripheralId::TC0, SignalId::signal_tioa2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 26);
}

template<>
inline auto apply_route<PinId::PA26, PeripheralId::USART1, SignalId::signal_dcd1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 26);
}

template<>
inline auto apply_route<PinId::PA27, PeripheralId::HSMCI, SignalId::signal_mcda3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 27);
}

template<>
inline auto apply_route<PinId::PA27, PeripheralId::TC0, SignalId::signal_tiob2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 27);
}

template<>
inline auto apply_route<PinId::PA27, PeripheralId::USART1, SignalId::signal_dtr1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 27);
}

template<>
inline auto apply_route<PinId::PA28, PeripheralId::HSMCI, SignalId::signal_mccda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 28);
}

template<>
inline auto apply_route<PinId::PA28, PeripheralId::PWM1, SignalId::signal_pwmfi2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 28);
}

template<>
inline auto apply_route<PinId::PA28, PeripheralId::TC0, SignalId::signal_tclk1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 28);
}

template<>
inline auto apply_route<PinId::PA28, PeripheralId::USART1, SignalId::signal_dsr1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 28);
}

template<>
inline auto apply_route<PinId::PA2, PeripheralId::DACC, SignalId::signal_datrg>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 30);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 2);
}

template<>
inline auto apply_route<PinId::PA2, PeripheralId::PWM0, SignalId::signal_pwmh1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 2);
}

template<>
inline auto apply_route<PinId::PA30, PeripheralId::HSMCI, SignalId::signal_mcda0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 30);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 30);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 30);
}

template<>
inline auto apply_route<PinId::PA30, PeripheralId::PWM0, SignalId::signal_pwml2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 30);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 30);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 30);
}

template<>
inline auto apply_route<PinId::PA30, PeripheralId::PWM1, SignalId::signal_pwmextrg0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 30);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 30);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 30);
}

template<>
inline auto apply_route<PinId::PA31, PeripheralId::HSMCI, SignalId::signal_mcda1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 31);
}

template<>
inline auto apply_route<PinId::PA31, PeripheralId::PWM1, SignalId::signal_pwmh2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 31);
}

template<>
inline auto apply_route<PinId::PA31, PeripheralId::SPI0, SignalId::signal_npcs1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 31);
}

template<>
inline auto apply_route<PinId::PA3, PeripheralId::GPIOA, SignalId::signal_piodc0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA3, PeripheralId::TWIHS0, SignalId::signal_twd0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 19);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::PA3, PeripheralId::USART1, SignalId::signal_loncol1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::PA4, PeripheralId::GPIOA, SignalId::signal_piodc1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA4, PeripheralId::TC0, SignalId::signal_tclk0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::PA4, PeripheralId::TWIHS0, SignalId::signal_twck0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 19);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::PA4, PeripheralId::UART1, SignalId::signal_utxd1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::PA5, PeripheralId::GPIOA, SignalId::signal_piodc2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA5, PeripheralId::PWM1, SignalId::signal_pwml3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 5);
}

template<>
inline auto apply_route<PinId::PA5, PeripheralId::UART1, SignalId::signal_urxd1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 5);
}

template<>
inline auto apply_route<PinId::PA7, PeripheralId::PWM0, SignalId::signal_pwmh3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 7);
}

template<>
inline auto apply_route<PinId::PA8, PeripheralId::AFEC0, SignalId::signal_adtrg>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 29);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) |=(std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 8);
}

template<>
inline auto apply_route<PinId::PA8, PeripheralId::PWM1, SignalId::signal_pwmh3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 8);
}

template<>
inline auto apply_route<PinId::PA9, PeripheralId::GPIOA, SignalId::signal_piodc3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PA9, PeripheralId::PWM0, SignalId::signal_pwmfi0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) |=(std::uint32_t{1} << 9);
}

template<>
inline auto apply_route<PinId::PA9, PeripheralId::UART0, SignalId::signal_urxd0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E04u) = (std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E70u) &= ~(std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0E74u) &= ~(std::uint32_t{1} << 9);
}

template<>
inline auto apply_route<PinId::PB0, PeripheralId::AFEC0, SignalId::signal_ad10>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 29);
}

template<>
inline auto apply_route<PinId::PB0, PeripheralId::PWM0, SignalId::signal_pwmh0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 0);
}

template<>
inline auto apply_route<PinId::PB0, PeripheralId::RTC, SignalId::signal_rtcout0>() noexcept -> void {
  // no MMIO ops captured for this route
}

template<>
inline auto apply_route<PinId::PB0, PeripheralId::USART0, SignalId::signal_rxd0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) |=(std::uint32_t{1} << 0);
}

template<>
inline auto apply_route<PinId::PB12, PeripheralId::GMAC, SignalId::signal_gtsucomp>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) |=(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 12);
}

template<>
inline auto apply_route<PinId::PB12, PeripheralId::PWM0, SignalId::signal_pwml1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 12);
}

template<>
inline auto apply_route<PinId::PB13, PeripheralId::DACC, SignalId::signal_dac0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 30);
}

template<>
inline auto apply_route<PinId::PB13, PeripheralId::PWM0, SignalId::signal_pwml2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 13);
}

template<>
inline auto apply_route<PinId::PB13, PeripheralId::USART0, SignalId::signal_sck0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) |=(std::uint32_t{1} << 13);
}

template<>
inline auto apply_route<PinId::PB1, PeripheralId::AFEC1, SignalId::signal_ad0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 8);
}

template<>
inline auto apply_route<PinId::PB1, PeripheralId::GMAC, SignalId::signal_gtsucomp>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 1);
}

template<>
inline auto apply_route<PinId::PB1, PeripheralId::PWM0, SignalId::signal_pwmh1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 1);
}

template<>
inline auto apply_route<PinId::PB1, PeripheralId::RTC, SignalId::signal_rtcout1>() noexcept -> void {
  // no MMIO ops captured for this route
}

template<>
inline auto apply_route<PinId::PB1, PeripheralId::USART0, SignalId::signal_txd0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) |=(std::uint32_t{1} << 1);
}

template<>
inline auto apply_route<PinId::PB2, PeripheralId::AFEC0, SignalId::signal_ad5>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 29);
}

template<>
inline auto apply_route<PinId::PB2, PeripheralId::MCAN0, SignalId::signal_cantx0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 2);
}

template<>
inline auto apply_route<PinId::PB2, PeripheralId::SPI0, SignalId::signal_npcs0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) |=(std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) |=(std::uint32_t{1} << 2);
}

template<>
inline auto apply_route<PinId::PB2, PeripheralId::USART0, SignalId::signal_cts0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) |=(std::uint32_t{1} << 2);
}

template<>
inline auto apply_route<PinId::PB3, PeripheralId::AFEC0, SignalId::signal_ad2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 29);
}

template<>
inline auto apply_route<PinId::PB3, PeripheralId::MCAN0, SignalId::signal_canrx0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::PB3, PeripheralId::USART0, SignalId::signal_rts0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) |=(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::PB4, PeripheralId::PWM0, SignalId::signal_pwmh2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::PB4, PeripheralId::TWIHS1, SignalId::signal_twd1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 20);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::PB4, PeripheralId::USART1, SignalId::signal_txd1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) |=(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::PB5, PeripheralId::PWM0, SignalId::signal_pwml0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) |=(std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 5);
}

template<>
inline auto apply_route<PinId::PB5, PeripheralId::TWIHS1, SignalId::signal_twck1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 20);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1004u) = (std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1070u) &= ~(std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1074u) &= ~(std::uint32_t{1} << 5);
}

template<>
inline auto apply_route<PinId::PD0, PeripheralId::DACC, SignalId::signal_dac1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 30);
}

template<>
inline auto apply_route<PinId::PD0, PeripheralId::GMAC, SignalId::signal_gtxck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 0);
}

template<>
inline auto apply_route<PinId::PD0, PeripheralId::PWM1, SignalId::signal_pwml0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 0);
}

template<>
inline auto apply_route<PinId::PD0, PeripheralId::USART0, SignalId::signal_dcd0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 0);
}

template<>
inline auto apply_route<PinId::PD10, PeripheralId::GMAC, SignalId::signal_gcrs>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 10);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 10);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PD10, PeripheralId::PWM0, SignalId::signal_pwml0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 10);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 10);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 10);
}

template<>
inline auto apply_route<PinId::PD11, PeripheralId::GMAC, SignalId::signal_grx2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 11);
}

template<>
inline auto apply_route<PinId::PD11, PeripheralId::GMAC, SignalId::signal_gtsucomp>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 11);
}

template<>
inline auto apply_route<PinId::PD11, PeripheralId::PWM0, SignalId::signal_pwmh0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 11);
}

template<>
inline auto apply_route<PinId::PD12, PeripheralId::GMAC, SignalId::signal_grx3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 12);
}

template<>
inline auto apply_route<PinId::PD12, PeripheralId::MCAN1, SignalId::signal_cantx1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 12);
}

template<>
inline auto apply_route<PinId::PD12, PeripheralId::SPI0, SignalId::signal_npcs2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 12);
}

template<>
inline auto apply_route<PinId::PD13, PeripheralId::GMAC, SignalId::signal_gcol>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 13);
}

template<>
inline auto apply_route<PinId::PD14, PeripheralId::GMAC, SignalId::signal_grxck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 14);
}

template<>
inline auto apply_route<PinId::PD15, PeripheralId::GMAC, SignalId::signal_gtx2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 15);
}

template<>
inline auto apply_route<PinId::PD15, PeripheralId::USART2, SignalId::signal_rxd2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 15);
}

template<>
inline auto apply_route<PinId::PD16, PeripheralId::GMAC, SignalId::signal_gtx3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::PD16, PeripheralId::USART2, SignalId::signal_txd2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::PD17, PeripheralId::GMAC, SignalId::signal_gtxer>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::PD17, PeripheralId::USART2, SignalId::signal_sck2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::PD18, PeripheralId::UART4, SignalId::signal_urxd4>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 18);
}

template<>
inline auto apply_route<PinId::PD18, PeripheralId::USART2, SignalId::signal_rts2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 18);
}

template<>
inline auto apply_route<PinId::PD19, PeripheralId::UART4, SignalId::signal_utxd4>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 19);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 19);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 19);
}

template<>
inline auto apply_route<PinId::PD19, PeripheralId::USART2, SignalId::signal_cts2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 19);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 19);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 19);
}

template<>
inline auto apply_route<PinId::PD1, PeripheralId::GMAC, SignalId::signal_gtxen>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 1);
}

template<>
inline auto apply_route<PinId::PD1, PeripheralId::PWM1, SignalId::signal_pwmh0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 1);
}

template<>
inline auto apply_route<PinId::PD1, PeripheralId::USART0, SignalId::signal_dtr0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 1);
}

template<>
inline auto apply_route<PinId::PD20, PeripheralId::GMAC, SignalId::signal_gtsucomp>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 20);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 20);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 20);
}

template<>
inline auto apply_route<PinId::PD20, PeripheralId::PWM0, SignalId::signal_pwmh0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 20);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 20);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 20);
}

template<>
inline auto apply_route<PinId::PD20, PeripheralId::SPI0, SignalId::signal_miso>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 20);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 20);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 20);
}

template<>
inline auto apply_route<PinId::PD21, PeripheralId::PWM0, SignalId::signal_pwmh1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 21);
}

template<>
inline auto apply_route<PinId::PD21, PeripheralId::SPI0, SignalId::signal_mosi>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 21);
}

template<>
inline auto apply_route<PinId::PD21, PeripheralId::TC3, SignalId::signal_tioa11>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 21);
}

template<>
inline auto apply_route<PinId::PD22, PeripheralId::PWM0, SignalId::signal_pwmh2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::PD22, PeripheralId::SPI0, SignalId::signal_spck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::PD22, PeripheralId::TC3, SignalId::signal_tiob11>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::PD24, PeripheralId::PWM0, SignalId::signal_pwml0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 24);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 24);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 24);
}

template<>
inline auto apply_route<PinId::PD24, PeripheralId::TC3, SignalId::signal_tclk11>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 24);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 24);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 24);
}

template<>
inline auto apply_route<PinId::PD25, PeripheralId::PWM0, SignalId::signal_pwml1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 25);
}

template<>
inline auto apply_route<PinId::PD25, PeripheralId::SPI0, SignalId::signal_npcs1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 25);
}

template<>
inline auto apply_route<PinId::PD25, PeripheralId::UART2, SignalId::signal_urxd2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 25);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 25);
}

template<>
inline auto apply_route<PinId::PD26, PeripheralId::PWM0, SignalId::signal_pwml2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 26);
}

template<>
inline auto apply_route<PinId::PD26, PeripheralId::UART1, SignalId::signal_utxd1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 26);
}

template<>
inline auto apply_route<PinId::PD26, PeripheralId::UART2, SignalId::signal_utxd2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 26);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 26);
}

template<>
inline auto apply_route<PinId::PD27, PeripheralId::PWM0, SignalId::signal_pwml3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 27);
}

template<>
inline auto apply_route<PinId::PD27, PeripheralId::SPI0, SignalId::signal_npcs3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 21);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 27);
}

template<>
inline auto apply_route<PinId::PD27, PeripheralId::TWIHS2, SignalId::signal_twd2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 27);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 27);
}

template<>
inline auto apply_route<PinId::PD28, PeripheralId::MCAN1, SignalId::signal_canrx1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 28);
}

template<>
inline auto apply_route<PinId::PD28, PeripheralId::TWIHS2, SignalId::signal_twck2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 28);
}

template<>
inline auto apply_route<PinId::PD28, PeripheralId::UART3, SignalId::signal_urxd3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 28);
}

template<>
inline auto apply_route<PinId::PD2, PeripheralId::GMAC, SignalId::signal_gtx0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 2);
}

template<>
inline auto apply_route<PinId::PD2, PeripheralId::PWM1, SignalId::signal_pwml1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 2);
}

template<>
inline auto apply_route<PinId::PD2, PeripheralId::USART0, SignalId::signal_dsr0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 2);
}

template<>
inline auto apply_route<PinId::PD30, PeripheralId::AFEC0, SignalId::signal_ad0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 29);
}

template<>
inline auto apply_route<PinId::PD30, PeripheralId::UART3, SignalId::signal_utxd3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 30);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 30);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 30);
}

template<>
inline auto apply_route<PinId::PD31, PeripheralId::QSPI, SignalId::signal_qio3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 11);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 31);
}

template<>
inline auto apply_route<PinId::PD31, PeripheralId::UART3, SignalId::signal_utxd3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 31);
}

template<>
inline auto apply_route<PinId::PD3, PeripheralId::GMAC, SignalId::signal_gtx1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::PD3, PeripheralId::PWM1, SignalId::signal_pwmh1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::PD3, PeripheralId::UART4, SignalId::signal_utxd4>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::PD3, PeripheralId::USART0, SignalId::signal_ri0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 13);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::PD4, PeripheralId::GMAC, SignalId::signal_grxdv>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::PD4, PeripheralId::PWM1, SignalId::signal_pwml2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::PD4, PeripheralId::USART2, SignalId::signal_dcd2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::PD5, PeripheralId::GMAC, SignalId::signal_grx0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 5);
}

template<>
inline auto apply_route<PinId::PD5, PeripheralId::PWM1, SignalId::signal_pwmh2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 5);
}

template<>
inline auto apply_route<PinId::PD5, PeripheralId::USART2, SignalId::signal_dtr2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 5);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 5);
}

template<>
inline auto apply_route<PinId::PD6, PeripheralId::GMAC, SignalId::signal_grx1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 6);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 6);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 6);
}

template<>
inline auto apply_route<PinId::PD6, PeripheralId::PWM1, SignalId::signal_pwml3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 6);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 6);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 6);
}

template<>
inline auto apply_route<PinId::PD6, PeripheralId::USART2, SignalId::signal_dsr2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 6);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 6);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 6);
}

template<>
inline auto apply_route<PinId::PD7, PeripheralId::GMAC, SignalId::signal_grxer>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 7);
}

template<>
inline auto apply_route<PinId::PD7, PeripheralId::PWM1, SignalId::signal_pwmh3>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 28);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 7);
}

template<>
inline auto apply_route<PinId::PD7, PeripheralId::USART2, SignalId::signal_ri2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 15);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 7);
}

template<>
inline auto apply_route<PinId::PD8, PeripheralId::GMAC, SignalId::signal_gmdc>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 8);
}

template<>
inline auto apply_route<PinId::PD8, PeripheralId::PWM0, SignalId::signal_pwmfi1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 8);
}

template<>
inline auto apply_route<PinId::PD9, PeripheralId::AFEC1, SignalId::signal_adtrg>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) |=(std::uint32_t{1} << 9);
}

template<>
inline auto apply_route<PinId::PD9, PeripheralId::GMAC, SignalId::signal_gmdio>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0700u) = (std::uint32_t{1} << 7);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) &= ~(std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 9);
}

template<>
inline auto apply_route<PinId::PD9, PeripheralId::PWM0, SignalId::signal_pwmfi2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x400E0610u) = (std::uint32_t{1} << 31);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1404u) = (std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1470u) |=(std::uint32_t{1} << 9);
  *reinterpret_cast<volatile std::uint32_t*>(0x400E1474u) &= ~(std::uint32_t{1} << 9);
}

enum class ConnectionGroupId : std::uint16_t {
  none,
  group_afec0_lqfp100_all_signals,
  group_afec1_lqfp100_all_signals,
  group_dacc_lqfp100_all_signals,
  group_gmac_lqfp100_all_signals,
  group_gpioa_lqfp100_all_signals,
  group_hsmci_lqfp100_all_signals,
  group_mcan0_lqfp100_tx_rx,
  group_mcan1_lqfp100_tx_rx,
  group_pwm0_lqfp100_all_signals,
  group_pwm1_lqfp100_all_signals,
  group_qspi_lqfp100_all_signals,
  group_rtc_lqfp100_all_signals,
  group_spi0_lqfp100_sck_cs,
  group_spi0_lqfp100_sck_mosi_miso,
  group_tc0_lqfp100_all_signals,
  group_tc3_lqfp100_all_signals,
  group_twihs0_lqfp100_scl_sda,
  group_twihs1_lqfp100_scl_sda,
  group_twihs2_lqfp100_scl_sda,
  group_uart0_lqfp100_all_signals,
  group_uart1_lqfp100_all_signals,
  group_uart2_lqfp100_all_signals,
  group_uart3_lqfp100_all_signals,
  group_uart4_lqfp100_all_signals,
  group_usart0_lqfp100_tx_rx,
  group_usart0_lqfp100_tx_rx_cts_rts,
  group_usart1_lqfp100_tx_rx,
  group_usart1_lqfp100_tx_rx_cts_rts,
  group_usart2_lqfp100_tx_rx,
  group_usart2_lqfp100_tx_rx_cts_rts,
};

template<PeripheralId Peripheral, SignalId... Signals>
struct ConnectionGroupTraits {
  static constexpr bool kPresent = false;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::none;
  static constexpr std::array<RouteId, 0> kRoutes = {};
};

template<>
struct ConnectionGroupTraits<PeripheralId::AFEC0, SignalId::signal_ad0, SignalId::signal_ad1, SignalId::signal_ad10, SignalId::signal_ad2, SignalId::signal_ad5, SignalId::signal_ad6, SignalId::signal_ad7, SignalId::signal_ad8, SignalId::signal_ad9, SignalId::signal_adtrg> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_afec0_lqfp100_all_signals;
  static constexpr std::array<RouteId, 10> kRoutes = {{
    RouteId::candidate_pa17_afec0_ad6,
    RouteId::candidate_pa18_afec0_ad7,
    RouteId::candidate_pa19_afec0_ad8,
    RouteId::candidate_pa20_afec0_ad9,
    RouteId::candidate_pa21_afec0_ad1,
    RouteId::candidate_pa8_afec0_adtrg,
    RouteId::candidate_pb0_afec0_ad10,
    RouteId::candidate_pb2_afec0_ad5,
    RouteId::candidate_pb3_afec0_ad2,
    RouteId::candidate_pd30_afec0_ad0,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::AFEC1, SignalId::signal_ad0, SignalId::signal_adtrg> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_afec1_lqfp100_all_signals;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pb1_afec1_ad0,
    RouteId::candidate_pd9_afec1_adtrg,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::DACC, SignalId::signal_dac0, SignalId::signal_dac1, SignalId::signal_datrg> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_dacc_lqfp100_all_signals;
  static constexpr std::array<RouteId, 3> kRoutes = {{
    RouteId::candidate_pa2_dacc_datrg,
    RouteId::candidate_pb13_dacc_dac0,
    RouteId::candidate_pd0_dacc_dac1,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::GMAC, SignalId::signal_gcol, SignalId::signal_gcrs, SignalId::signal_gmdc, SignalId::signal_gmdio, SignalId::signal_grx0, SignalId::signal_grx1, SignalId::signal_grx2, SignalId::signal_grx3, SignalId::signal_grxck, SignalId::signal_grxdv, SignalId::signal_grxer, SignalId::signal_gtsucomp, SignalId::signal_gtx0, SignalId::signal_gtx1, SignalId::signal_gtx2, SignalId::signal_gtx3, SignalId::signal_gtxck, SignalId::signal_gtxen, SignalId::signal_gtxer> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
  static constexpr std::array<RouteId, 22> kRoutes = {{
    RouteId::candidate_pb12_gmac_gtsucomp,
    RouteId::candidate_pb1_gmac_gtsucomp,
    RouteId::candidate_pd0_gmac_gtxck,
    RouteId::candidate_pd10_gmac_gcrs,
    RouteId::candidate_pd11_gmac_grx2,
    RouteId::candidate_pd11_gmac_gtsucomp,
    RouteId::candidate_pd12_gmac_grx3,
    RouteId::candidate_pd13_gmac_gcol,
    RouteId::candidate_pd14_gmac_grxck,
    RouteId::candidate_pd15_gmac_gtx2,
    RouteId::candidate_pd16_gmac_gtx3,
    RouteId::candidate_pd17_gmac_gtxer,
    RouteId::candidate_pd1_gmac_gtxen,
    RouteId::candidate_pd20_gmac_gtsucomp,
    RouteId::candidate_pd2_gmac_gtx0,
    RouteId::candidate_pd3_gmac_gtx1,
    RouteId::candidate_pd4_gmac_grxdv,
    RouteId::candidate_pd5_gmac_grx0,
    RouteId::candidate_pd6_gmac_grx1,
    RouteId::candidate_pd7_gmac_grxer,
    RouteId::candidate_pd8_gmac_gmdc,
    RouteId::candidate_pd9_gmac_gmdio,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::GPIOA, SignalId::signal_piodc0, SignalId::signal_piodc1, SignalId::signal_piodc2, SignalId::signal_piodc3, SignalId::signal_piodc4, SignalId::signal_piodc5, SignalId::signal_piodc6, SignalId::signal_piodc7, SignalId::signal_piodcclk, SignalId::signal_piodcen1, SignalId::signal_piodcen2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
  static constexpr std::array<RouteId, 11> kRoutes = {{
    RouteId::candidate_pa10_gpioa_piodc4,
    RouteId::candidate_pa11_gpioa_piodc5,
    RouteId::candidate_pa12_gpioa_piodc6,
    RouteId::candidate_pa13_gpioa_piodc7,
    RouteId::candidate_pa14_gpioa_piodcen1,
    RouteId::candidate_pa21_gpioa_piodcen2,
    RouteId::candidate_pa22_gpioa_piodcclk,
    RouteId::candidate_pa3_gpioa_piodc0,
    RouteId::candidate_pa4_gpioa_piodc1,
    RouteId::candidate_pa5_gpioa_piodc2,
    RouteId::candidate_pa9_gpioa_piodc3,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::HSMCI, SignalId::signal_mccda, SignalId::signal_mcck, SignalId::signal_mcda0, SignalId::signal_mcda1, SignalId::signal_mcda2, SignalId::signal_mcda3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_hsmci_lqfp100_all_signals;
  static constexpr std::array<RouteId, 6> kRoutes = {{
    RouteId::candidate_pa25_hsmci_mcck,
    RouteId::candidate_pa26_hsmci_mcda2,
    RouteId::candidate_pa27_hsmci_mcda3,
    RouteId::candidate_pa28_hsmci_mccda,
    RouteId::candidate_pa30_hsmci_mcda0,
    RouteId::candidate_pa31_hsmci_mcda1,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::MCAN0, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_mcan0_lqfp100_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pb2_mcan0_cantx0,
    RouteId::candidate_pb3_mcan0_canrx0,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::MCAN1, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_mcan1_lqfp100_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pd12_mcan1_cantx1,
    RouteId::candidate_pd28_mcan1_canrx1,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::PWM0, SignalId::signal_pwmextrg0, SignalId::signal_pwmextrg1, SignalId::signal_pwmfi0, SignalId::signal_pwmfi1, SignalId::signal_pwmfi2, SignalId::signal_pwmh0, SignalId::signal_pwmh1, SignalId::signal_pwmh2, SignalId::signal_pwmh3, SignalId::signal_pwml0, SignalId::signal_pwml1, SignalId::signal_pwml2, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
  static constexpr std::array<RouteId, 37> kRoutes = {{
    RouteId::candidate_pa0_pwm0_pwmh0,
    RouteId::candidate_pa10_pwm0_pwmextrg0,
    RouteId::candidate_pa11_pwm0_pwmh0,
    RouteId::candidate_pa12_pwm0_pwmh1,
    RouteId::candidate_pa13_pwm0_pwmh2,
    RouteId::candidate_pa14_pwm0_pwmh3,
    RouteId::candidate_pa15_pwm0_pwml3,
    RouteId::candidate_pa16_pwm0_pwml2,
    RouteId::candidate_pa17_pwm0_pwmh3,
    RouteId::candidate_pa19_pwm0_pwml0,
    RouteId::candidate_pa1_pwm0_pwml0,
    RouteId::candidate_pa20_pwm0_pwml1,
    RouteId::candidate_pa22_pwm0_pwmextrg1,
    RouteId::candidate_pa23_pwm0_pwmh0,
    RouteId::candidate_pa24_pwm0_pwmh1,
    RouteId::candidate_pa25_pwm0_pwmh2,
    RouteId::candidate_pa2_pwm0_pwmh1,
    RouteId::candidate_pa30_pwm0_pwml2,
    RouteId::candidate_pa7_pwm0_pwmh3,
    RouteId::candidate_pa9_pwm0_pwmfi0,
    RouteId::candidate_pb0_pwm0_pwmh0,
    RouteId::candidate_pb12_pwm0_pwml1,
    RouteId::candidate_pb13_pwm0_pwml2,
    RouteId::candidate_pb1_pwm0_pwmh1,
    RouteId::candidate_pb4_pwm0_pwmh2,
    RouteId::candidate_pb5_pwm0_pwml0,
    RouteId::candidate_pd10_pwm0_pwml0,
    RouteId::candidate_pd11_pwm0_pwmh0,
    RouteId::candidate_pd20_pwm0_pwmh0,
    RouteId::candidate_pd21_pwm0_pwmh1,
    RouteId::candidate_pd22_pwm0_pwmh2,
    RouteId::candidate_pd24_pwm0_pwml0,
    RouteId::candidate_pd25_pwm0_pwml1,
    RouteId::candidate_pd26_pwm0_pwml2,
    RouteId::candidate_pd27_pwm0_pwml3,
    RouteId::candidate_pd8_pwm0_pwmfi1,
    RouteId::candidate_pd9_pwm0_pwmfi2,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::PWM1, SignalId::signal_pwmextrg0, SignalId::signal_pwmextrg1, SignalId::signal_pwmfi0, SignalId::signal_pwmfi1, SignalId::signal_pwmfi2, SignalId::signal_pwmh0, SignalId::signal_pwmh1, SignalId::signal_pwmh2, SignalId::signal_pwmh3, SignalId::signal_pwml0, SignalId::signal_pwml1, SignalId::signal_pwml2, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
  static constexpr std::array<RouteId, 21> kRoutes = {{
    RouteId::candidate_pa11_pwm1_pwml0,
    RouteId::candidate_pa12_pwm1_pwmh0,
    RouteId::candidate_pa13_pwm1_pwml1,
    RouteId::candidate_pa14_pwm1_pwmh1,
    RouteId::candidate_pa18_pwm1_pwmextrg1,
    RouteId::candidate_pa21_pwm1_pwmfi0,
    RouteId::candidate_pa23_pwm1_pwml2,
    RouteId::candidate_pa26_pwm1_pwmfi1,
    RouteId::candidate_pa28_pwm1_pwmfi2,
    RouteId::candidate_pa30_pwm1_pwmextrg0,
    RouteId::candidate_pa31_pwm1_pwmh2,
    RouteId::candidate_pa5_pwm1_pwml3,
    RouteId::candidate_pa8_pwm1_pwmh3,
    RouteId::candidate_pd0_pwm1_pwml0,
    RouteId::candidate_pd1_pwm1_pwmh0,
    RouteId::candidate_pd2_pwm1_pwml1,
    RouteId::candidate_pd3_pwm1_pwmh1,
    RouteId::candidate_pd4_pwm1_pwml2,
    RouteId::candidate_pd5_pwm1_pwmh2,
    RouteId::candidate_pd6_pwm1_pwml3,
    RouteId::candidate_pd7_pwm1_pwmh3,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::QSPI, SignalId::signal_qcs, SignalId::signal_qio0, SignalId::signal_qio1, SignalId::signal_qio2, SignalId::signal_qio3, SignalId::signal_qsck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_qspi_lqfp100_all_signals;
  static constexpr std::array<RouteId, 6> kRoutes = {{
    RouteId::candidate_pa11_qspi_qcs,
    RouteId::candidate_pa12_qspi_qio1,
    RouteId::candidate_pa13_qspi_qio0,
    RouteId::candidate_pa14_qspi_qsck,
    RouteId::candidate_pa17_qspi_qio2,
    RouteId::candidate_pd31_qspi_qio3,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::RTC, SignalId::signal_rtcout0, SignalId::signal_rtcout1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_rtc_lqfp100_all_signals;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pb0_rtc_rtcout0,
    RouteId::candidate_pb1_rtc_rtcout1,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::SPI0, SignalId::signal_sck, SignalId::signal_cs> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_spi0_lqfp100_sck_cs;
  static constexpr std::array<RouteId, 6> kRoutes = {{
    RouteId::candidate_pa31_spi0_npcs1,
    RouteId::candidate_pb2_spi0_npcs0,
    RouteId::candidate_pd12_spi0_npcs2,
    RouteId::candidate_pd22_spi0_spck,
    RouteId::candidate_pd25_spi0_npcs1,
    RouteId::candidate_pd27_spi0_npcs3,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::SPI0, SignalId::signal_sck, SignalId::signal_mosi, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_spi0_lqfp100_sck_mosi_miso;
  static constexpr std::array<RouteId, 3> kRoutes = {{
    RouteId::candidate_pd20_spi0_miso,
    RouteId::candidate_pd21_spi0_mosi,
    RouteId::candidate_pd22_spi0_spck,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::TC0, SignalId::signal_tclk0, SignalId::signal_tclk1, SignalId::signal_tioa0, SignalId::signal_tioa1, SignalId::signal_tioa2, SignalId::signal_tiob0, SignalId::signal_tiob1, SignalId::signal_tiob2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_tc0_lqfp100_all_signals;
  static constexpr std::array<RouteId, 8> kRoutes = {{
    RouteId::candidate_pa0_tc0_tioa0,
    RouteId::candidate_pa15_tc0_tioa1,
    RouteId::candidate_pa16_tc0_tiob1,
    RouteId::candidate_pa1_tc0_tiob0,
    RouteId::candidate_pa26_tc0_tioa2,
    RouteId::candidate_pa27_tc0_tiob2,
    RouteId::candidate_pa28_tc0_tclk1,
    RouteId::candidate_pa4_tc0_tclk0,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::TC3, SignalId::signal_tclk11, SignalId::signal_tioa11, SignalId::signal_tiob11> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_tc3_lqfp100_all_signals;
  static constexpr std::array<RouteId, 3> kRoutes = {{
    RouteId::candidate_pd21_tc3_tioa11,
    RouteId::candidate_pd22_tc3_tiob11,
    RouteId::candidate_pd24_tc3_tclk11,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::TWIHS0, SignalId::signal_scl, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_twihs0_lqfp100_scl_sda;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pa3_twihs0_twd0,
    RouteId::candidate_pa4_twihs0_twck0,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::TWIHS1, SignalId::signal_scl, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_twihs1_lqfp100_scl_sda;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pb4_twihs1_twd1,
    RouteId::candidate_pb5_twihs1_twck1,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::TWIHS2, SignalId::signal_scl, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_twihs2_lqfp100_scl_sda;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pd27_twihs2_twd2,
    RouteId::candidate_pd28_twihs2_twck2,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART0, SignalId::signal_urxd0, SignalId::signal_utxd0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart0_lqfp100_all_signals;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pa10_uart0_utxd0,
    RouteId::candidate_pa9_uart0_urxd0,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART1, SignalId::signal_urxd1, SignalId::signal_utxd1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart1_lqfp100_all_signals;
  static constexpr std::array<RouteId, 3> kRoutes = {{
    RouteId::candidate_pa4_uart1_utxd1,
    RouteId::candidate_pa5_uart1_urxd1,
    RouteId::candidate_pd26_uart1_utxd1,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART2, SignalId::signal_urxd2, SignalId::signal_utxd2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart2_lqfp100_all_signals;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pd25_uart2_urxd2,
    RouteId::candidate_pd26_uart2_utxd2,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART3, SignalId::signal_urxd3, SignalId::signal_utxd3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart3_lqfp100_all_signals;
  static constexpr std::array<RouteId, 3> kRoutes = {{
    RouteId::candidate_pd28_uart3_urxd3,
    RouteId::candidate_pd30_uart3_utxd3,
    RouteId::candidate_pd31_uart3_utxd3,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART4, SignalId::signal_urxd4, SignalId::signal_utxd4> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart4_lqfp100_all_signals;
  static constexpr std::array<RouteId, 3> kRoutes = {{
    RouteId::candidate_pd18_uart4_urxd4,
    RouteId::candidate_pd19_uart4_utxd4,
    RouteId::candidate_pd3_uart4_utxd4,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART0, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart0_lqfp100_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pb0_usart0_rxd0,
    RouteId::candidate_pb1_usart0_txd0,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART0, SignalId::signal_tx, SignalId::signal_rx, SignalId::signal_cts, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart0_lqfp100_tx_rx_cts_rts;
  static constexpr std::array<RouteId, 4> kRoutes = {{
    RouteId::candidate_pb0_usart0_rxd0,
    RouteId::candidate_pb1_usart0_txd0,
    RouteId::candidate_pb2_usart0_cts0,
    RouteId::candidate_pb3_usart0_rts0,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART1, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart1_lqfp100_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pa21_usart1_rxd1,
    RouteId::candidate_pb4_usart1_txd1,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART1, SignalId::signal_tx, SignalId::signal_rx, SignalId::signal_cts, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart1_lqfp100_tx_rx_cts_rts;
  static constexpr std::array<RouteId, 4> kRoutes = {{
    RouteId::candidate_pa21_usart1_rxd1,
    RouteId::candidate_pa24_usart1_rts1,
    RouteId::candidate_pa25_usart1_cts1,
    RouteId::candidate_pb4_usart1_txd1,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART2, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart2_lqfp100_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pd15_usart2_rxd2,
    RouteId::candidate_pd16_usart2_txd2,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART2, SignalId::signal_tx, SignalId::signal_rx, SignalId::signal_cts, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart2_lqfp100_tx_rx_cts_rts;
  static constexpr std::array<RouteId, 4> kRoutes = {{
    RouteId::candidate_pd15_usart2_rxd2,
    RouteId::candidate_pd16_usart2_txd2,
    RouteId::candidate_pd18_usart2_rts2,
    RouteId::candidate_pd19_usart2_cts2,
  }};
};

struct ConnectionGroupDescriptor {
  ConnectionGroupId group_id;
  PeripheralId peripheral_id;
  std::uint16_t route_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 30> kRuntimeConnectionGroups = {{
  {ConnectionGroupId::group_afec0_lqfp100_all_signals, PeripheralId::AFEC0, 10u},
  {ConnectionGroupId::group_afec1_lqfp100_all_signals, PeripheralId::AFEC1, 2u},
  {ConnectionGroupId::group_dacc_lqfp100_all_signals, PeripheralId::DACC, 3u},
  {ConnectionGroupId::group_gmac_lqfp100_all_signals, PeripheralId::GMAC, 22u},
  {ConnectionGroupId::group_gpioa_lqfp100_all_signals, PeripheralId::GPIOA, 11u},
  {ConnectionGroupId::group_hsmci_lqfp100_all_signals, PeripheralId::HSMCI, 6u},
  {ConnectionGroupId::group_mcan0_lqfp100_tx_rx, PeripheralId::MCAN0, 2u},
  {ConnectionGroupId::group_mcan1_lqfp100_tx_rx, PeripheralId::MCAN1, 2u},
  {ConnectionGroupId::group_pwm0_lqfp100_all_signals, PeripheralId::PWM0, 37u},
  {ConnectionGroupId::group_pwm1_lqfp100_all_signals, PeripheralId::PWM1, 21u},
  {ConnectionGroupId::group_qspi_lqfp100_all_signals, PeripheralId::QSPI, 6u},
  {ConnectionGroupId::group_rtc_lqfp100_all_signals, PeripheralId::RTC, 2u},
  {ConnectionGroupId::group_spi0_lqfp100_sck_cs, PeripheralId::SPI0, 6u},
  {ConnectionGroupId::group_spi0_lqfp100_sck_mosi_miso, PeripheralId::SPI0, 3u},
  {ConnectionGroupId::group_tc0_lqfp100_all_signals, PeripheralId::TC0, 8u},
  {ConnectionGroupId::group_tc3_lqfp100_all_signals, PeripheralId::TC3, 3u},
  {ConnectionGroupId::group_twihs0_lqfp100_scl_sda, PeripheralId::TWIHS0, 2u},
  {ConnectionGroupId::group_twihs1_lqfp100_scl_sda, PeripheralId::TWIHS1, 2u},
  {ConnectionGroupId::group_twihs2_lqfp100_scl_sda, PeripheralId::TWIHS2, 2u},
  {ConnectionGroupId::group_uart0_lqfp100_all_signals, PeripheralId::UART0, 2u},
  {ConnectionGroupId::group_uart1_lqfp100_all_signals, PeripheralId::UART1, 3u},
  {ConnectionGroupId::group_uart2_lqfp100_all_signals, PeripheralId::UART2, 2u},
  {ConnectionGroupId::group_uart3_lqfp100_all_signals, PeripheralId::UART3, 3u},
  {ConnectionGroupId::group_uart4_lqfp100_all_signals, PeripheralId::UART4, 3u},
  {ConnectionGroupId::group_usart0_lqfp100_tx_rx, PeripheralId::USART0, 2u},
  {ConnectionGroupId::group_usart0_lqfp100_tx_rx_cts_rts, PeripheralId::USART0, 4u},
  {ConnectionGroupId::group_usart1_lqfp100_tx_rx, PeripheralId::USART1, 2u},
  {ConnectionGroupId::group_usart1_lqfp100_tx_rx_cts_rts, PeripheralId::USART1, 4u},
  {ConnectionGroupId::group_usart2_lqfp100_tx_rx, PeripheralId::USART2, 2u},
  {ConnectionGroupId::group_usart2_lqfp100_tx_rx_cts_rts, PeripheralId::USART2, 4u},
}};

}
}
}
}
}
}
