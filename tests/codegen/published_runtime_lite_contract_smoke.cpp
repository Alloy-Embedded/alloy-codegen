/**
 * Smoke consumer for runtime-lite published alloy-devices artifacts.
 */

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_TYPES_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_TYPES_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PERIPHERALS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PERIPHERALS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PINS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PINS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_REGISTERS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_REGISTERS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_REGISTER_FIELDS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_REGISTER_FIELDS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_CLOCK_BINDINGS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_CLOCK_BINDINGS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ROUTES_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ROUTES_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_NAMESPACE
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_NAMESPACE must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_NAMESPACE
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_NAMESPACE must be defined"
#endif

#include ALLOY_CODEGEN_SMOKE_RUNTIME_TYPES_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PERIPHERALS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PINS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_REGISTERS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_REGISTER_FIELDS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_CLOCK_BINDINGS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ROUTES_HEADER

namespace published_runtime = ALLOY_CODEGEN_SMOKE_RUNTIME_NAMESPACE;
namespace published_device_runtime = ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_NAMESPACE;

static_assert(published_device_runtime::kRuntimePeripherals.size() > 0u);
static_assert(published_device_runtime::kPins.size() > 0u);
static_assert(published_device_runtime::kRegisters.size() > 0u);
static_assert(published_device_runtime::kRegisterFields.size() > 0u);
static_assert(published_device_runtime::kClockBoundPeripherals.size() > 0u);
static_assert(published_device_runtime::kRuntimeRoutes.size() > 0u);

constexpr auto kFirstPeripheral = published_device_runtime::kRuntimePeripherals[0];
constexpr auto kFirstPin = published_device_runtime::kPins[0];
constexpr auto kFirstRoute = published_device_runtime::kRuntimeRoutes[0];

static_assert(
    published_device_runtime::PeripheralInstanceTraits<kFirstPeripheral>::kPresent
);
static_assert(published_device_runtime::PinTraits<kFirstPin>::kPresent);
static_assert(
    published_device_runtime::RegisterTraits<published_device_runtime::kRegisters[0]>::kPresent
);
static_assert(
    published_device_runtime::RegisterFieldTraits<published_device_runtime::kRegisterFields[0]>::kPresent
);
static_assert(
    published_device_runtime::PeripheralClockBindingTraits<
        published_device_runtime::kClockBoundPeripherals[0]>::kPresent
);
static_assert(
    published_device_runtime::RouteTraits<
        kFirstRoute.pin_id,
        kFirstRoute.peripheral_id,
        kFirstRoute.signal_id>::kPresent
);
static_assert(published_runtime::BackendSchemaId::none == published_runtime::BackendSchemaId::none);

int main() {
    return 0;
}
