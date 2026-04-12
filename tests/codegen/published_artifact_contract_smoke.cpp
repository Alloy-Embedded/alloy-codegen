/**
 * Smoke consumer for published alloy-devices artifacts.
 *
 * This translation unit is owned by alloy-codegen and compiled against Alloy's
 * public headers plus the staged/published generated artifacts.
 */

#ifndef ALLOY_CODEGEN_SMOKE_REGISTER_MAP_HEADER
    #error "ALLOY_CODEGEN_SMOKE_REGISTER_MAP_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_REGISTER_FIELDS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_REGISTER_FIELDS_HEADER must be defined"
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

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_PROFILES_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_PROFILES_HEADER must be defined"
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

#ifndef ALLOY_CODEGEN_SMOKE_INTERRUPT_BINDINGS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_INTERRUPT_BINDINGS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_DMA_BINDINGS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_DMA_BINDINGS_HEADER must be defined"
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
#include ALLOY_CODEGEN_SMOKE_REGISTER_FIELDS_HEADER
#include ALLOY_CODEGEN_SMOKE_GPIO_HEADER
#include ALLOY_CODEGEN_SMOKE_CONNECTOR_TABLES_HEADER
#include ALLOY_CODEGEN_SMOKE_INTERRUPT_MAP_HEADER
#include ALLOY_CODEGEN_SMOKE_MEMORY_MAP_HEADER
#include ALLOY_CODEGEN_SMOKE_PACKAGE_MAP_HEADER
#include ALLOY_CODEGEN_SMOKE_CLOCK_TREE_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_PROFILES_HEADER
#include ALLOY_CODEGEN_SMOKE_DEVICE_DESCRIPTOR_HEADER
#include ALLOY_CODEGEN_SMOKE_PINS_HEADER
#include ALLOY_CODEGEN_SMOKE_PERIPHERAL_INSTANCES_HEADER
#include ALLOY_CODEGEN_SMOKE_INTERRUPT_BINDINGS_HEADER
#include ALLOY_CODEGEN_SMOKE_DMA_BINDINGS_HEADER
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
static_assert(published_device::kRegisters.size() > 0u);
static_assert(published_device::kRegisterFields.size() > 0u);
static_assert(published_gpio::kPeripheral.base_address != 0u);
static_assert(
    published_generated::kConnectionCandidates[0].candidate_id
    != published_generated::ConnectionCandidateId::none
);
static_assert(
    published_generated::kConnectionGroups[0].group_id
    != published_generated::ConnectionGroupId::none
);
static_assert(
    published_generated::kInterruptMap[0].interrupt_id
    != published_generated::InterruptMapId::none
);
static_assert(
    published_generated::kMemoryMap[0].region_id
    != published_generated::MemoryRegionId::none
);
static_assert(
    published_generated::kPackageMap[0].package_id
    != published_generated::PackageRefId::none
);
static_assert(published_generated::kClockNodes.size() > 0u);
static_assert(published_generated::kClockGates.size() > 0u);
static_assert(published_generated::kPeripheralClockBindings.size() > 0u);
static_assert(published_generated::kRuntimeProfiles.size() > 0u);
static_assert(published_device::kDeviceDescriptor.package_id != published_generated::PackageRefId::none);
static_assert(published_device::kPins.size() > 0u);
static_assert(published_device::kPinSignals.size() > 0u);
static_assert(published_device::kPeripheralInstances.size() > 0u);
static_assert(published_device::kInterruptBindings.size() > 0u);
static_assert(
    published_device::kDmaBindings.empty()
    || published_device::kDmaBindings[0].request_line_id
        != published_device::DmaRequestLineId::none
);
static_assert(
    published_device::kCapabilityOverlays.empty()
    || published_device::kCapabilityOverlays[0].capability_id
        != published_generated::CapabilityId::none
);
static_assert(
    published_device::kVectorSlots[0].symbol_id
    != published_device::StartupSymbolId::none
);
static_assert(
    published_device::kStartupDescriptors[0].descriptor_id
    != published_device::StartupDescriptorId::none
);
#ifdef ALLOY_CODEGEN_SMOKE_IP_HEADER
static_assert(published_ip::kIpBlock.ip_block_id != published_generated::IpBlockId::none);
static_assert(
    published_ip::kCapabilities.empty()
    || published_ip::kCapabilities[0].capability_id != published_generated::CapabilityId::none
);
#endif

constexpr auto build_ok_result() -> alloy::core::Result<int, int> {
    return alloy::core::Ok(0);
}

int main() {
    const auto result = build_ok_result();
    return result.is_ok() ? 0 : 1;
}
