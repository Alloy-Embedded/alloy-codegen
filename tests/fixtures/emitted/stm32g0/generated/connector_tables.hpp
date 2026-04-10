#pragma once

namespace st {
namespace stm32g0 {
namespace generated {
struct SignalEndpointDescriptor {
  const char* device;
  const char* endpoint_id;
  const char* peripheral_class;
  const char* signal;
  const char* direction;
};
inline constexpr SignalEndpointDescriptor kSignalEndpoints[] = {
  {"stm32g071rb", "endpoint:gpio:in0", "gpio", "IN0", nullptr},
  {"stm32g071rb", "endpoint:gpio:in1", "gpio", "IN1", nullptr},
  {"stm32g071rb", "endpoint:gpio:in2", "gpio", "IN2", nullptr},
  {"stm32g071rb", "endpoint:gpio:in3", "gpio", "IN3", nullptr},
  {"stm32g071rb", "endpoint:gpio:in6", "gpio", "IN6", nullptr},
  {"stm32g071rb", "endpoint:gpio:in7", "gpio", "IN7", nullptr},
  {"stm32g071rb", "endpoint:uart:rx", "uart", "RX", "input"},
  {"stm32g071rb", "endpoint:uart:tx", "uart", "TX", "output"},
};

struct RouteRequirementDescriptor {
  const char* device;
  const char* requirement_id;
  const char* kind;
  const char* target;
  const char* value;
};
inline constexpr RouteRequirementDescriptor kRouteRequirements[] = {
  {"stm32g071rb", "requirement:bonded-pin:lqfp64:pb6", "bonded-pin", "PB6", "lqfp64"},
  {"stm32g071rb", "requirement:bonded-pin:lqfp64:pb7", "bonded-pin", "PB7", "lqfp64"},
  {"stm32g071rb", "requirement:clock-enable:dma1", "clock-enable", "RCC_AHBENR.DMA1EN", "1"},
  {"stm32g071rb", "requirement:clock-enable:dmamux1", "clock-enable", "RCC_AHBENR.DMAMUX1EN", "1"},
  {"stm32g071rb", "requirement:clock-enable:gpioa", "clock-enable", "RCC_IOPENR.GPIOAEN", "1"},
  {"stm32g071rb", "requirement:clock-enable:gpiob", "clock-enable", "RCC_IOPENR.GPIOBEN", "1"},
  {"stm32g071rb", "requirement:clock-enable:usart1", "clock-enable", "RCC_APBENR2.USART1EN", "1"},
  {"stm32g071rb", "requirement:package:lqfp64", "package", "lqfp64", "selected"},
  {"stm32g071rb", "requirement:reset-release:dma1", "reset-release", "RCC_AHBRSTR.DMA1RST", "0"},
  {"stm32g071rb", "requirement:reset-release:dmamux1", "reset-release", "RCC_AHBRSTR.DMAMUX1RST", "0"},
  {"stm32g071rb", "requirement:reset-release:gpioa", "reset-release", "RCC_IOPRSTR.GPIOARST", "0"},
  {"stm32g071rb", "requirement:reset-release:gpiob", "reset-release", "RCC_IOPRSTR.GPIOBRST", "0"},
  {"stm32g071rb", "requirement:reset-release:usart1", "reset-release", "RCC_APBRSTR2.USART1RST", "0"},
  {"stm32g071rb", "requirement:source-select:pb6:usart1:tx", "source-select", "pinmux.PB6", "selector:0"},
  {"stm32g071rb", "requirement:source-select:pb7:usart1:rx", "source-select", "pinmux.PB7", "selector:0"},
};

struct RouteOperationDescriptor {
  const char* device;
  const char* operation_id;
  const char* kind;
  const char* target;
  const char* value;
};
inline constexpr RouteOperationDescriptor kRouteOperations[] = {
  {"stm32g071rb", "operation:clock-enable:dma1", "set-bit", "RCC_AHBENR.DMA1EN", "1"},
  {"stm32g071rb", "operation:clock-enable:dmamux1", "set-bit", "RCC_AHBENR.DMAMUX1EN", "1"},
  {"stm32g071rb", "operation:clock-enable:gpioa", "set-bit", "RCC_IOPENR.GPIOAEN", "1"},
  {"stm32g071rb", "operation:clock-enable:gpiob", "set-bit", "RCC_IOPENR.GPIOBEN", "1"},
  {"stm32g071rb", "operation:clock-enable:usart1", "set-bit", "RCC_APBENR2.USART1EN", "1"},
  {"stm32g071rb", "operation:reset-release:dma1", "clear-bit", "RCC_AHBRSTR.DMA1RST", "0"},
  {"stm32g071rb", "operation:reset-release:dmamux1", "clear-bit", "RCC_AHBRSTR.DMAMUX1RST", "0"},
  {"stm32g071rb", "operation:reset-release:gpioa", "clear-bit", "RCC_IOPRSTR.GPIOARST", "0"},
  {"stm32g071rb", "operation:reset-release:gpiob", "clear-bit", "RCC_IOPRSTR.GPIOBRST", "0"},
  {"stm32g071rb", "operation:reset-release:usart1", "clear-bit", "RCC_APBRSTR2.USART1RST", "0"},
  {"stm32g071rb", "operation:route:pb6:usart1:tx", "write-selector", "pinmux.PB6", "0"},
  {"stm32g071rb", "operation:route:pb7:usart1:rx", "write-selector", "pinmux.PB7", "0"},
};

struct ConnectionCandidateDescriptor {
  const char* device;
  const char* candidate_id;
  const char* pin;
  const char* peripheral;
  const char* signal;
  const char* route_kind;
  const char* route_selector;
  const char* route_group_id;
  const char* requirement_ids;
  const char* operation_ids;
  const char* capability_ids;
};
inline constexpr ConnectionCandidateDescriptor kConnectionCandidates[] = {
  {"stm32g071rb", "candidate:pb6:usart1:tx", "PB6", "USART1", "tx", "alternate-function", "selector:0", "group:usart1:lqfp64:tx-rx", "requirement:package:lqfp64,requirement:bonded-pin:lqfp64:pb6,requirement:clock-enable:usart1,requirement:reset-release:usart1,requirement:source-select:pb6:usart1:tx", "operation:clock-enable:usart1,operation:reset-release:usart1,operation:route:pb6:usart1:tx", "capability:usart:usart-v3-1:tx,capability-instance:usart1:lqfp64:tx"},
  {"stm32g071rb", "candidate:pb7:usart1:rx", "PB7", "USART1", "rx", "alternate-function", "selector:0", "group:usart1:lqfp64:tx-rx", "requirement:package:lqfp64,requirement:bonded-pin:lqfp64:pb7,requirement:clock-enable:usart1,requirement:reset-release:usart1,requirement:source-select:pb7:usart1:rx", "operation:clock-enable:usart1,operation:reset-release:usart1,operation:route:pb7:usart1:rx", "capability:usart:usart-v3-1:rx,capability-instance:usart1:lqfp64:rx"},
};

struct ConnectionGroupDescriptor {
  const char* device;
  const char* group_id;
  const char* peripheral;
  const char* signals;
  const char* candidate_ids;
  const char* package_name;
  const char* conflict_group;
};
inline constexpr ConnectionGroupDescriptor kConnectionGroups[] = {
  {"stm32g071rb", "group:usart1:lqfp64:tx-rx", "USART1", "tx,rx", "candidate:pb6:usart1:tx,candidate:pb7:usart1:rx", "lqfp64", "conflict:usart1:lqfp64:tx-rx"},
};
}
}
}
