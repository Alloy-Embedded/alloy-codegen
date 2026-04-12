#pragma once

#include <array>
#include <cstdint>
#include "../../runtime_refs.hpp"
#include "../../runtime_semantics.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
struct PinDescriptor {
  PinRefId pin_id;
  PortId port_id;
  int number;
  std::uint16_t package_pad_offset;
  std::uint16_t package_pad_count;
  std::uint16_t constraint_offset;
  std::uint16_t constraint_count;
};
inline constexpr std::array<PinDescriptor, 6> kPins = {{
  {PinRefId::stm32g071rb_PA0, PortId::port_A, 0, 0u, 1u, 0u, 0u},
  {PinRefId::stm32g071rb_PA1, PortId::port_A, 1, 1u, 1u, 0u, 0u},
  {PinRefId::stm32g071rb_PA2, PortId::port_A, 2, 2u, 1u, 0u, 0u},
  {PinRefId::stm32g071rb_PA3, PortId::port_A, 3, 3u, 1u, 0u, 0u},
  {PinRefId::stm32g071rb_PB6, PortId::port_B, 6, 4u, 1u, 0u, 0u},
  {PinRefId::stm32g071rb_PB7, PortId::port_B, 7, 5u, 1u, 0u, 0u},
}};

struct PinPackagePadRef {
  PinRefId pin_id;
  PackagePadRefId package_pad_id;
};
inline constexpr std::array<PinPackagePadRef, 6> kPinPackagePadRefs = {{
  {PinRefId::stm32g071rb_PA0, PackagePadRefId::stm32g071rb_17},
  {PinRefId::stm32g071rb_PA1, PackagePadRefId::stm32g071rb_18},
  {PinRefId::stm32g071rb_PA2, PackagePadRefId::stm32g071rb_19},
  {PinRefId::stm32g071rb_PA3, PackagePadRefId::stm32g071rb_20},
  {PinRefId::stm32g071rb_PB6, PackagePadRefId::stm32g071rb_29},
  {PinRefId::stm32g071rb_PB7, PackagePadRefId::stm32g071rb_30},
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
inline constexpr std::array<PinSignalDescriptor, 8> kPinSignals = {{
  {PinRefId::stm32g071rb_PA0, PinFunctionId::pin_function_gpio, PeripheralRefId::stm32g071rb_GPIOA, SignalId::signal_IN0, -1},
  {PinRefId::stm32g071rb_PA1, PinFunctionId::pin_function_gpio, PeripheralRefId::stm32g071rb_GPIOA, SignalId::signal_IN1, -1},
  {PinRefId::stm32g071rb_PA2, PinFunctionId::pin_function_gpio, PeripheralRefId::stm32g071rb_GPIOA, SignalId::signal_IN2, -1},
  {PinRefId::stm32g071rb_PA3, PinFunctionId::pin_function_gpio, PeripheralRefId::stm32g071rb_GPIOA, SignalId::signal_IN3, -1},
  {PinRefId::stm32g071rb_PB6, PinFunctionId::pin_function_gpio, PeripheralRefId::stm32g071rb_GPIOB, SignalId::signal_IN6, -1},
  {PinRefId::stm32g071rb_PB6, PinFunctionId::pin_function_usart1_tx, PeripheralRefId::stm32g071rb_USART1, SignalId::signal_TX, 0},
  {PinRefId::stm32g071rb_PB7, PinFunctionId::pin_function_gpio, PeripheralRefId::stm32g071rb_GPIOB, SignalId::signal_IN7, -1},
  {PinRefId::stm32g071rb_PB7, PinFunctionId::pin_function_usart1_rx, PeripheralRefId::stm32g071rb_USART1, SignalId::signal_RX, 0},
}};
}
}
}
}
}
