/**
 * Smoke consumer for published alloy-devices artifacts.
 *
 * This translation unit is owned by alloy-codegen and compiled against Alloy's
 * public headers plus the staged/published generated artifacts.
 */

#ifndef ALLOY_CODEGEN_SMOKE_REGISTER_MAP_HEADER
    #error "ALLOY_CODEGEN_SMOKE_REGISTER_MAP_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_PIN_FUNCTIONS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_PIN_FUNCTIONS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_GPIO_HEADER
    #error "ALLOY_CODEGEN_SMOKE_GPIO_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_DEVICE_NAMESPACE
    #error "ALLOY_CODEGEN_SMOKE_DEVICE_NAMESPACE must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_GPIO_NAMESPACE
    #error "ALLOY_CODEGEN_SMOKE_GPIO_NAMESPACE must be defined"
#endif

#include "core/result.hpp"

#include ALLOY_CODEGEN_SMOKE_REGISTER_MAP_HEADER
#include ALLOY_CODEGEN_SMOKE_PIN_FUNCTIONS_HEADER
#include ALLOY_CODEGEN_SMOKE_GPIO_HEADER

namespace published_device = ALLOY_CODEGEN_SMOKE_DEVICE_NAMESPACE;
namespace published_gpio = ALLOY_CODEGEN_SMOKE_GPIO_NAMESPACE;

static_assert(published_device::kPeripheralBases[0].address != 0u);
static_assert(published_device::kPinFunctions[0].pin_name != nullptr);
static_assert(published_gpio::kPeripheral.base_address != 0u);

constexpr auto build_ok_result() -> alloy::core::Result<int, int> {
    return alloy::core::Ok(0);
}

int main() {
    const auto result = build_ok_result();
    return result.is_ok() ? 0 : 1;
}
