/**
 * Smoke consumer for published alloy-devices artifacts.
 *
 * This translation unit is owned by alloy-codegen and compiled against Alloy's
 * public headers plus the staged/published generated artifacts.
 */

#ifndef ALLOY_CODEGEN_SMOKE_REGISTER_MAP_HEADER
    #error "ALLOY_CODEGEN_SMOKE_REGISTER_MAP_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_GPIO_HEADER
    #error "ALLOY_CODEGEN_SMOKE_GPIO_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_CONNECTOR_TABLES_HEADER
    #error "ALLOY_CODEGEN_SMOKE_CONNECTOR_TABLES_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_INTERRUPT_MAP_HEADER
    #error "ALLOY_CODEGEN_SMOKE_INTERRUPT_MAP_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_MEMORY_MAP_HEADER
    #error "ALLOY_CODEGEN_SMOKE_MEMORY_MAP_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_PACKAGE_MAP_HEADER
    #error "ALLOY_CODEGEN_SMOKE_PACKAGE_MAP_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_CLOCK_TREE_HEADER
    #error "ALLOY_CODEGEN_SMOKE_CLOCK_TREE_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_DEVICE_DESCRIPTOR_HEADER
    #error "ALLOY_CODEGEN_SMOKE_DEVICE_DESCRIPTOR_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_PINS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_PINS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_PERIPHERAL_INSTANCES_HEADER
    #error "ALLOY_CODEGEN_SMOKE_PERIPHERAL_INSTANCES_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_CAPABILITY_OVERLAYS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_CAPABILITY_OVERLAYS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_STARTUP_DESCRIPTORS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_STARTUP_DESCRIPTORS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_DEVICE_NAMESPACE
    #error "ALLOY_CODEGEN_SMOKE_DEVICE_NAMESPACE must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_GENERATED_NAMESPACE
    #error "ALLOY_CODEGEN_SMOKE_GENERATED_NAMESPACE must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_GPIO_NAMESPACE
    #error "ALLOY_CODEGEN_SMOKE_GPIO_NAMESPACE must be defined"
#endif

#include "core/result.hpp"

#include ALLOY_CODEGEN_SMOKE_REGISTER_MAP_HEADER
#include ALLOY_CODEGEN_SMOKE_GPIO_HEADER
#include ALLOY_CODEGEN_SMOKE_CONNECTOR_TABLES_HEADER
#include ALLOY_CODEGEN_SMOKE_INTERRUPT_MAP_HEADER
#include ALLOY_CODEGEN_SMOKE_MEMORY_MAP_HEADER
#include ALLOY_CODEGEN_SMOKE_PACKAGE_MAP_HEADER
#include ALLOY_CODEGEN_SMOKE_CLOCK_TREE_HEADER
#include ALLOY_CODEGEN_SMOKE_DEVICE_DESCRIPTOR_HEADER
#include ALLOY_CODEGEN_SMOKE_PINS_HEADER
#include ALLOY_CODEGEN_SMOKE_PERIPHERAL_INSTANCES_HEADER
#include ALLOY_CODEGEN_SMOKE_CAPABILITY_OVERLAYS_HEADER
#include ALLOY_CODEGEN_SMOKE_STARTUP_DESCRIPTORS_HEADER
#ifdef ALLOY_CODEGEN_SMOKE_IP_HEADER
    #include ALLOY_CODEGEN_SMOKE_IP_HEADER
#endif

namespace published_device = ALLOY_CODEGEN_SMOKE_DEVICE_NAMESPACE;
namespace published_generated = ALLOY_CODEGEN_SMOKE_GENERATED_NAMESPACE;
namespace published_gpio = ALLOY_CODEGEN_SMOKE_GPIO_NAMESPACE;
#ifdef ALLOY_CODEGEN_SMOKE_IP_HEADER
namespace published_ip = ALLOY_CODEGEN_SMOKE_GENERATED_NAMESPACE::ip;
#endif

static_assert(published_device::kPeripheralBases[0].address != 0u);
static_assert(published_gpio::kPeripheral.base_address != 0u);
static_assert(published_generated::kConnectionCandidates[0].candidate_id != nullptr);
static_assert(published_generated::kConnectionGroups[0].group_id != nullptr);
static_assert(published_generated::kInterruptMap[0].interrupt_name != nullptr);
static_assert(published_generated::kMemoryMap[0].name != nullptr);
static_assert(published_generated::kPackageMap[0].package_name != nullptr);
static_assert(published_generated::kClockNodes.size() > 0u);
static_assert(published_generated::kClockGates.size() > 0u);
static_assert(published_generated::kPeripheralClockBindings.size() > 0u);
static_assert(published_device::kDeviceDescriptor.device != nullptr);
static_assert(published_device::kPins.size() > 0u);
static_assert(published_device::kPinSignals.size() > 0u);
static_assert(published_device::kPeripheralInstances.size() > 0u);
static_assert(published_device::kCapabilityOverlays.size() >= 0u);
static_assert(published_device::kVectorSlots[0].symbol_name != nullptr);
static_assert(published_device::kStartupDescriptors[0].descriptor_id != nullptr);
#ifdef ALLOY_CODEGEN_SMOKE_IP_HEADER
static_assert(published_ip::kIpBlock.ip_name != nullptr);
static_assert(published_ip::kCapabilities.size() > 0u);
#endif

constexpr auto build_ok_result() -> alloy::core::Result<int, int> {
    return alloy::core::Ok(0);
}

int main() {
    const auto result = build_ok_result();
    return result.is_ok() ? 0 : 1;
}
