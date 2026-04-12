#pragma once

#include <array>
#include <cstdint>
#include "../../runtime_refs.hpp"
#include "../../runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
struct PinDescriptor {
  PinRefId pin_id;
  PortId port_id;
  int number;
  std::uint16_t package_pad_offset;
  std::uint16_t package_pad_count;
  std::uint16_t constraint_offset;
  std::uint16_t constraint_count;
};
inline constexpr std::array<PinDescriptor, 4> kPins = {{
  {PinRefId::mimxrt1062_GPIO_AD_B0_00, PortId::none, 0, 0u, 1u, 0u, 0u},
  {PinRefId::mimxrt1062_GPIO_AD_B0_01, PortId::none, 1, 1u, 1u, 0u, 0u},
  {PinRefId::mimxrt1062_GPIO_EMC_00, PortId::none, 0, 2u, 1u, 0u, 0u},
  {PinRefId::mimxrt1062_GPIO_EMC_01, PortId::none, 1, 3u, 1u, 0u, 0u},
}};

struct PinPackagePadRef {
  PinRefId pin_id;
  PackagePadRefId package_pad_id;
};
inline constexpr std::array<PinPackagePadRef, 4> kPinPackagePadRefs = {{
  {PinRefId::mimxrt1062_GPIO_AD_B0_00, PackagePadRefId::mimxrt1062_GPIO_AD_B0_00},
  {PinRefId::mimxrt1062_GPIO_AD_B0_01, PackagePadRefId::mimxrt1062_GPIO_AD_B0_01},
  {PinRefId::mimxrt1062_GPIO_EMC_00, PackagePadRefId::mimxrt1062_GPIO_EMC_00},
  {PinRefId::mimxrt1062_GPIO_EMC_01, PackagePadRefId::mimxrt1062_GPIO_EMC_01},
}};

struct PinConstraintRef {
  PinRefId pin_id;
  ConstraintRefId constraint_id;
};
inline constexpr std::array<PinConstraintRef, 0> kPinConstraintRefs = {};

struct PinSignalDescriptor {
  PinRefId pin_id;
  PinFunctionId function_id;
  PeripheralRefId peripheral_id;
  SignalId signal_id;
  int af_number;
};
inline constexpr std::array<PinSignalDescriptor, 10> kPinSignals = {{
  {PinRefId::mimxrt1062_GPIO_AD_B0_00, PinFunctionId::pin_function_gpio1_io00, PeripheralRefId::mimxrt1062_GPIO1, SignalId::signal_IO00, 5},
  {PinRefId::mimxrt1062_GPIO_AD_B0_00, PinFunctionId::pin_function_lpi2c1_scl, PeripheralRefId::mimxrt1062_LPI2C1, SignalId::signal_SCL, 0},
  {PinRefId::mimxrt1062_GPIO_AD_B0_00, PinFunctionId::pin_function_lpuart1_tx, PeripheralRefId::mimxrt1062_LPUART1, SignalId::signal_TX, 2},
  {PinRefId::mimxrt1062_GPIO_AD_B0_01, PinFunctionId::pin_function_gpio1_io01, PeripheralRefId::mimxrt1062_GPIO1, SignalId::signal_IO01, 5},
  {PinRefId::mimxrt1062_GPIO_AD_B0_01, PinFunctionId::pin_function_lpi2c1_sda, PeripheralRefId::mimxrt1062_LPI2C1, SignalId::signal_SDA, 0},
  {PinRefId::mimxrt1062_GPIO_AD_B0_01, PinFunctionId::pin_function_lpuart1_rx, PeripheralRefId::mimxrt1062_LPUART1, SignalId::signal_RX, 2},
  {PinRefId::mimxrt1062_GPIO_EMC_00, PinFunctionId::pin_function_gpio4_io00, PeripheralRefId::mimxrt1062_GPIO4, SignalId::signal_IO00, 5},
  {PinRefId::mimxrt1062_GPIO_EMC_00, PinFunctionId::pin_function_lpspi1_sck, PeripheralRefId::mimxrt1062_LPSPI1, SignalId::signal_SCK, 2},
  {PinRefId::mimxrt1062_GPIO_EMC_01, PinFunctionId::pin_function_gpio4_io01, PeripheralRefId::mimxrt1062_GPIO4, SignalId::signal_IO01, 5},
  {PinRefId::mimxrt1062_GPIO_EMC_01, PinFunctionId::pin_function_lpspi1_pcs0, PeripheralRefId::mimxrt1062_LPSPI1, SignalId::signal_PCS0, 2},
}};
}
}
}
}
}
