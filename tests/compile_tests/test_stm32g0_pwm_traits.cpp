// Compile-time invariants for the populated STM32 TIMx PWM traits
// emitted by ``extend-pwm-coverage-all-mcus`` Phase A.

#ifndef ALLOY_CODEGEN_STM32G0_PWM_HEADER
#error "ALLOY_CODEGEN_STM32G0_PWM_HEADER must be defined by the harness"
#endif

#ifndef ALLOY_CODEGEN_STM32G0_PINS_HEADER
#error "ALLOY_CODEGEN_STM32G0_PINS_HEADER must be defined by the harness"
#endif

#include <array>
#include <cstdint>

#include ALLOY_CODEGEN_STM32G0_PINS_HEADER
#include ALLOY_CODEGEN_STM32G0_PWM_HEADER

namespace ds = st::stm32g0::generated::runtime::devices::stm32g071rb::driver_semantics;

// TIM1 is the only advanced-control timer admitted by the stm32g071rb
// fixture SVD slice — assert its silicon-fixed shape.
static_assert(ds::StmTimerPwmTraits<ds::RuntimeStmTimerPwmId::TIM1>::kPresent);
static_assert(ds::StmTimerPwmTraits<ds::RuntimeStmTimerPwmId::TIM1>::kBaseAddress == 0x40012c00u);
static_assert(
    ds::StmTimerPwmTraits<ds::RuntimeStmTimerPwmId::TIM1>::kKind ==
    ds::RuntimeStmTimerKind::Advanced
);

// Primary template defaults — kPresent must be false for any
// non-specialized id.
static_assert(!ds::StmTimerPwmTraits<ds::RuntimeStmTimerPwmId::None>::kPresent);
static_assert(
    ds::StmTimerPwmTraits<ds::RuntimeStmTimerPwmId::None>::kKind ==
    ds::RuntimeStmTimerKind::None
);

int main() { return 0; }
