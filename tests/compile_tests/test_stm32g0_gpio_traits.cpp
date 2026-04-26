// Compile-time invariants for the populated GPIO AF topology emitted by
// ``fill-gpio-semantic-gaps`` Phase A.  Compiled headers-only by
// ``test_compile_invariants.py``; the harness defines
// ALLOY_CODEGEN_STM32G0_GPIO_HEADER and ALLOY_CODEGEN_STM32G0_PINS_HEADER
// pointing at the regenerated stm32g071rb fixtures.

#ifndef ALLOY_CODEGEN_STM32G0_GPIO_HEADER
#error "ALLOY_CODEGEN_STM32G0_GPIO_HEADER must be defined by the harness"
#endif

#ifndef ALLOY_CODEGEN_STM32G0_PINS_HEADER
#error "ALLOY_CODEGEN_STM32G0_PINS_HEADER must be defined by the harness"
#endif

#include <array>
#include <cstdint>

// pins.hpp declares ``PinId`` in the parent (stm32g071rb) namespace; gpio.hpp
// then opens ``driver_semantics`` and uses unqualified ``PinId``.  This
// compile test mirrors that lookup by aliasing the parent namespace.
#include ALLOY_CODEGEN_STM32G0_GPIO_HEADER

namespace dev = st::stm32g0::generated::runtime::devices::stm32g071rb;
namespace ds = st::stm32g0::generated::runtime::devices::stm32g071rb::driver_semantics;

// Primary template: zero defaults so non-AF-present pins remain zero-cost.
static_assert(ds::GpioSemanticTraits<dev::PinId::none>::kPortOffset == 0u);
static_assert(ds::GpioSemanticTraits<dev::PinId::none>::kPinIndex == 0u);
static_assert(ds::GpioSemanticTraits<dev::PinId::none>::kMaxAltFunction == 0u);
static_assert(ds::GpioSemanticTraits<dev::PinId::none>::kValidAltFunctions.empty());
static_assert(!ds::GpioSemanticTraits<dev::PinId::none>::kIsInputOnly);

// PA0 — present in the test OPD slice with the kPortOffset/kPinIndex
// fields populated; AF list may be empty depending on the slice.
static_assert(ds::GpioSemanticTraits<dev::PinId::PA0>::kPresent);
static_assert(ds::GpioSemanticTraits<dev::PinId::PA0>::kPortOffset == 0u);
static_assert(ds::GpioSemanticTraits<dev::PinId::PA0>::kPinIndex == 0u);
static_assert(!ds::GpioSemanticTraits<dev::PinId::PA0>::kIsInputOnly);

// PB6 — different port; verifies the 0x400 GPIOA→GPIOB stride and that
// the populated AF array is non-empty in this slice.
static_assert(ds::GpioSemanticTraits<dev::PinId::PB6>::kPresent);
static_assert(ds::GpioSemanticTraits<dev::PinId::PB6>::kPortOffset == 0x400u);
static_assert(ds::GpioSemanticTraits<dev::PinId::PB6>::kPinIndex == 6u);
static_assert(ds::GpioSemanticTraits<dev::PinId::PB6>::kValidAltFunctions.size() >= 1u);

int main() {}
