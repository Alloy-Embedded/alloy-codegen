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

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DMA_BINDINGS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DMA_BINDINGS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ROUTES_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ROUTES_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_GPIO_SEMANTICS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_GPIO_SEMANTICS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_UART_SEMANTICS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_UART_SEMANTICS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_I2C_SEMANTICS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_I2C_SEMANTICS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SPI_SEMANTICS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SPI_SEMANTICS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DMA_SEMANTICS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DMA_SEMANTICS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ADC_SEMANTICS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ADC_SEMANTICS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DAC_SEMANTICS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DAC_SEMANTICS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_TIMER_SEMANTICS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_TIMER_SEMANTICS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PWM_SEMANTICS_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PWM_SEMANTICS_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SYSTICK_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SYSTICK_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SYSTEM_CLOCK_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SYSTEM_CLOCK_HEADER must be defined"
#endif

#ifndef ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_STARTUP_HEADER
    #error "ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_STARTUP_HEADER must be defined"
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
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DMA_BINDINGS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ROUTES_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_GPIO_SEMANTICS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_UART_SEMANTICS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_I2C_SEMANTICS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SPI_SEMANTICS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DMA_SEMANTICS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ADC_SEMANTICS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DAC_SEMANTICS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_TIMER_SEMANTICS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PWM_SEMANTICS_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SYSTICK_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SYSTEM_CLOCK_HEADER
#include ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_STARTUP_HEADER

#include <type_traits>

namespace published_runtime = ALLOY_CODEGEN_SMOKE_RUNTIME_NAMESPACE;
namespace published_device_runtime = ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_NAMESPACE;
namespace published_driver = ALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_NAMESPACE::driver_semantics;

static_assert(published_device_runtime::kRuntimePeripherals.size() > 0u);
static_assert(published_device_runtime::kPins.size() > 0u);
static_assert(published_device_runtime::kRegisters.size() > 0u);
static_assert(published_device_runtime::kRegisterFields.size() > 0u);
static_assert(published_device_runtime::kClockBoundPeripherals.size() > 0u);

constexpr auto kFirstPeripheral = published_device_runtime::kRuntimePeripherals[0];
constexpr auto kFirstPin = published_device_runtime::kPins[0];

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
static_assert(published_runtime::BackendSchemaId::none == published_runtime::BackendSchemaId::none);

template<const auto& Values, std::size_t Count = std::tuple_size_v<std::remove_cvref_t<decltype(Values)>>>
struct FirstGpioSemanticSmoke {
    static constexpr bool kPresent = published_driver::GpioSemanticTraits<Values[0]>::kPresent;
};

template<const auto& Values>
struct FirstGpioSemanticSmoke<Values, 0u> {
    static constexpr bool kPresent = true;
};

template<const auto& Values, std::size_t Count = std::tuple_size_v<std::remove_cvref_t<decltype(Values)>>>
struct FirstUartSemanticSmoke {
    static constexpr bool kPresent = published_driver::UartSemanticTraits<Values[0]>::kPresent;
};

template<const auto& Values>
struct FirstUartSemanticSmoke<Values, 0u> {
    static constexpr bool kPresent = true;
};

template<const auto& Values, std::size_t Count = std::tuple_size_v<std::remove_cvref_t<decltype(Values)>>>
struct FirstI2cSemanticSmoke {
    static constexpr bool kPresent = published_driver::I2cSemanticTraits<Values[0]>::kPresent;
};

template<const auto& Values>
struct FirstI2cSemanticSmoke<Values, 0u> {
    static constexpr bool kPresent = true;
};

template<const auto& Values, std::size_t Count = std::tuple_size_v<std::remove_cvref_t<decltype(Values)>>>
struct FirstSpiSemanticSmoke {
    static constexpr bool kPresent = published_driver::SpiSemanticTraits<Values[0]>::kPresent;
};

template<const auto& Values>
struct FirstSpiSemanticSmoke<Values, 0u> {
    static constexpr bool kPresent = true;
};

template<const auto& Values, std::size_t Count = std::tuple_size_v<std::remove_cvref_t<decltype(Values)>>>
struct FirstAdcSemanticSmoke {
    static constexpr bool kPresent = published_driver::AdcSemanticTraits<Values[0]>::kPresent;
};

template<const auto& Values>
struct FirstAdcSemanticSmoke<Values, 0u> {
    static constexpr bool kPresent = true;
};

template<const auto& Values, const auto& Bindings>
consteval bool first_dma_semantic_present() {
    constexpr auto kPeripheralCount = std::tuple_size_v<std::remove_cvref_t<decltype(Values)>>;
    constexpr auto kBindingCount = std::tuple_size_v<std::remove_cvref_t<decltype(Bindings)>>;
    if constexpr (kPeripheralCount == 0u || kBindingCount == 0u) {
        return true;
    } else {
        constexpr auto kSignalId = std::get<0>(Bindings).signal_id;
        return published_driver::DmaSemanticTraits<
            Values[0], kSignalId>::kPresent;
    }
}

template<const auto& Values, std::size_t Count = std::tuple_size_v<std::remove_cvref_t<decltype(Values)>>>
struct FirstDacSemanticSmoke {
    static constexpr bool kPresent = published_driver::DacSemanticTraits<Values[0]>::kPresent
                                      && published_driver::DacChannelSemanticTraits<
                                          Values[0], 0u>::kPresent;
};

template<const auto& Values>
struct FirstDacSemanticSmoke<Values, 0u> {
    static constexpr bool kPresent = true;
};

template<const auto& Values, std::size_t Count = std::tuple_size_v<std::remove_cvref_t<decltype(Values)>>>
struct FirstTimerSemanticSmoke {
    static constexpr bool kPresent = published_driver::TimerSemanticTraits<Values[0]>::kPresent
                                      && published_driver::TimerChannelSemanticTraits<
                                          Values[0], 0u>::kPresent;
};

template<const auto& Values>
struct FirstTimerSemanticSmoke<Values, 0u> {
    static constexpr bool kPresent = true;
};

template<const auto& Values, std::size_t Count = std::tuple_size_v<std::remove_cvref_t<decltype(Values)>>>
struct FirstPwmSemanticSmoke {
    static constexpr bool kPresent = published_driver::PwmSemanticTraits<Values[0]>::kPresent
                                      && published_driver::PwmChannelSemanticTraits<
                                          Values[0], 0u>::kPresent;
};

template<const auto& Values>
struct FirstPwmSemanticSmoke<Values, 0u> {
    static constexpr bool kPresent = true;
};

static_assert(FirstGpioSemanticSmoke<published_driver::kGpioSemanticPins>::kPresent);
static_assert(FirstUartSemanticSmoke<published_driver::kUartSemanticPeripherals>::kPresent);
static_assert(FirstI2cSemanticSmoke<published_driver::kI2cSemanticPeripherals>::kPresent);
static_assert(FirstSpiSemanticSmoke<published_driver::kSpiSemanticPeripherals>::kPresent);
static_assert(FirstAdcSemanticSmoke<published_driver::kAdcSemanticPeripherals>::kPresent);
static_assert(FirstDacSemanticSmoke<published_driver::kDacSemanticPeripherals>::kPresent);
static_assert(FirstTimerSemanticSmoke<published_driver::kTimerSemanticPeripherals>::kPresent);
static_assert(FirstPwmSemanticSmoke<published_driver::kPwmSemanticPeripherals>::kPresent);
static_assert(
    first_dma_semantic_present<
        published_driver::kDmaSemanticPeripherals,
        published_device_runtime::kDmaBindings>());
static_assert(!published_device_runtime::SysTickTraits::kPresent
              || published_device_runtime::SysTickTraits::kCounterBits == 24u);
static_assert(!published_device_runtime::SysTickTraits::kPresent
              || published_device_runtime::kSysTick.exception_number == 15u);
static_assert(published_device_runtime::kSystemClockProfiles.size() > 0u);
static_assert(published_device_runtime::kVectorSlots.size() > 0u);
static_assert(published_device_runtime::kStartupDescriptors.size() > 0u);
static_assert(
    published_device_runtime::SystemClockProfileTraits<
        published_device_runtime::kSystemClockProfiles[0].profile_id>::kPresent);

int main() {
    return 0;
}
