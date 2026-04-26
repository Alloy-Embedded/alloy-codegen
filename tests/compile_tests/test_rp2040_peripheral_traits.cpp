// Aggregated compile-time invariants for `complete-rp2040-semantics`
// Phases A–D.  Compiled headers-only by `test_compile_invariants.py`;
// the harness defines ALLOY_CODEGEN_RP2040_DRIVER_ROOT pointing at the
// regenerated rp2040 driver_semantics directory.

#ifndef ALLOY_CODEGEN_RP2040_GPIO_HEADER
#error "ALLOY_CODEGEN_RP2040_GPIO_HEADER must be defined by the harness"
#endif

#ifndef ALLOY_CODEGEN_RP2040_UART_HEADER
#error "ALLOY_CODEGEN_RP2040_UART_HEADER must be defined by the harness"
#endif

#ifndef ALLOY_CODEGEN_RP2040_SPI_HEADER
#error "ALLOY_CODEGEN_RP2040_SPI_HEADER must be defined by the harness"
#endif

#ifndef ALLOY_CODEGEN_RP2040_ADC_HEADER
#error "ALLOY_CODEGEN_RP2040_ADC_HEADER must be defined by the harness"
#endif

#ifndef ALLOY_CODEGEN_RP2040_TIMER_HEADER
#error "ALLOY_CODEGEN_RP2040_TIMER_HEADER must be defined by the harness"
#endif

#ifndef ALLOY_CODEGEN_RP2040_PWM_HEADER
#error "ALLOY_CODEGEN_RP2040_PWM_HEADER must be defined by the harness"
#endif

#ifndef ALLOY_CODEGEN_RP2040_DMA_HEADER
#error "ALLOY_CODEGEN_RP2040_DMA_HEADER must be defined by the harness"
#endif

#include <array>
#include <cstdint>

#include ALLOY_CODEGEN_RP2040_GPIO_HEADER
#include ALLOY_CODEGEN_RP2040_UART_HEADER
#include ALLOY_CODEGEN_RP2040_SPI_HEADER
#include ALLOY_CODEGEN_RP2040_ADC_HEADER
#include ALLOY_CODEGEN_RP2040_TIMER_HEADER
#include ALLOY_CODEGEN_RP2040_PWM_HEADER
#include ALLOY_CODEGEN_RP2040_DMA_HEADER

namespace dev = raspberrypi::rp2040::generated::runtime::devices::rp2040;
namespace ds = raspberrypi::rp2040::generated::runtime::devices::rp2040::driver_semantics;

// Phase A: GPIO FUNCSEL.
static_assert(ds::GpioSemanticTraits<dev::PinId::GP0>::kPresent);
static_assert(ds::GpioSemanticTraits<dev::PinId::GP0>::kPinIndex == 0u);
static_assert(ds::GpioSemanticTraits<dev::PinId::GP0>::kValidAltFunctions.size() >= 1u);
static_assert(!ds::GpioSemanticTraits<dev::PinId::GP0>::kIsInputOnly);

// Phase B: UART/SPI.
static_assert(ds::UartPeripheralTraits<ds::RuntimeUartId::UART0>::kPresent);
static_assert(ds::UartPeripheralTraits<ds::RuntimeUartId::UART0>::kBaseAddress == 0x40034000u);
static_assert(ds::UartPeripheralTraits<ds::RuntimeUartId::UART0>::kFifoDepth == 32u);
static_assert(ds::UartPeripheralTraits<ds::RuntimeUartId::UART0>::kDreqTx == 20u);
static_assert(ds::UartPeripheralTraits<ds::RuntimeUartId::UART1>::kDreqRx == 23u);

static_assert(ds::SpiPeripheralTraits<ds::RuntimeSpiId::SPI0>::kPresent);
static_assert(ds::SpiPeripheralTraits<ds::RuntimeSpiId::SPI0>::kMaxClockHz == 62500000u);
static_assert(ds::SpiPeripheralTraits<ds::RuntimeSpiId::SPI0>::kValidMosiPins.size() == 4u);
static_assert(ds::SpiPeripheralTraits<ds::RuntimeSpiId::SPI1>::kBaseAddress == 0x40040000u);

// Phase C: ADC.
static_assert(ds::AdcPeripheralTraits<ds::RuntimeAdcId::ADC>::kPresent);
static_assert(ds::AdcPeripheralTraits<ds::RuntimeAdcId::ADC>::kChannelCount == 5u);
static_assert(ds::AdcPeripheralTraits<ds::RuntimeAdcId::ADC>::kResolutionBits == 12u);
static_assert(ds::AdcPeripheralTraits<ds::RuntimeAdcId::ADC>::kDreq == 36u);
static_assert(ds::AdcPeripheralTraits<ds::RuntimeAdcId::ADC>::kFifoDepth == 4u);
static_assert(ds::AdcPeripheralTraits<ds::RuntimeAdcId::ADC>::kSupportsFifo);
static_assert(ds::AdcPeripheralTraits<ds::RuntimeAdcId::ADC>::kChannelPins[0] == 26u);
static_assert(ds::AdcPeripheralTraits<ds::RuntimeAdcId::ADC>::kChannelPins[4] == 255u);

// Phase D: DMA / Timer / PWM HW.
static_assert(ds::DmaControllerHwTraits<ds::RuntimeDmaCtrlId::DMA>::kPresent);
static_assert(ds::DmaControllerHwTraits<ds::RuntimeDmaCtrlId::DMA>::kChannelCount == 12u);
static_assert(ds::DmaControllerHwTraits<ds::RuntimeDmaCtrlId::DMA>::kSupportsChaining);

static_assert(ds::TimerControllerHwTraits<ds::RuntimeTimerCtrlId::TIMER>::kCounterBits == 64u);
static_assert(ds::TimerControllerHwTraits<ds::RuntimeTimerCtrlId::TIMER>::kAlarmCount == 4u);
static_assert(ds::TimerControllerHwTraits<ds::RuntimeTimerCtrlId::TIMER>::kDreqAlarmBase == 39u);

static_assert(ds::PwmSliceHwTraits<0>::kChannelAPin == 0u);
static_assert(ds::PwmSliceHwTraits<0>::kChannelBPin == 1u);
static_assert(ds::PwmSliceHwTraits<7>::kChannelAPin == 14u);
static_assert(ds::PwmSliceHwTraits<7>::kChannelBPin == 15u);
static_assert(ds::PwmSliceHwTraits<7>::kCounterBits == 16u);

int main() {}
