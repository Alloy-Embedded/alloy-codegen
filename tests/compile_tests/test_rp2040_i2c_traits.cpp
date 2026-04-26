// Compile-time invariants for the populated I2C traits emitted by
// ``fill-i2c-semantic-gaps`` Phase C (RP2040).

#ifndef ALLOY_CODEGEN_RP2040_I2C_HEADER
#error "ALLOY_CODEGEN_RP2040_I2C_HEADER must be defined by the harness"
#endif

#ifndef ALLOY_CODEGEN_RP2040_PINS_HEADER
#error "ALLOY_CODEGEN_RP2040_PINS_HEADER must be defined by the harness"
#endif

#include <array>
#include <cstdint>

#include ALLOY_CODEGEN_RP2040_I2C_HEADER

namespace dev = raspberrypi::rp2040::generated::runtime::devices::rp2040;
namespace ds = raspberrypi::rp2040::generated::runtime::devices::rp2040::driver_semantics;

// I2C0 — datasheet Tables 2-5 (pin allowlist) + 2-7 (DREQs).
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::I2C0>::kPresent);
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::I2C0>::kBaseAddress == 0x40044000u);
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::I2C0>::kDmaReqTx == 32u);
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::I2C0>::kDmaReqRx == 33u);
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::I2C0>::kValidSdaPins.size() == 8u);
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::I2C0>::kValidSdaPins[0] == dev::PinId::GP0);
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::I2C0>::kValidSclPins[7] == dev::PinId::GP29);

// I2C1 — distinct DREQs and pad set.
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::I2C1>::kBaseAddress == 0x40048000u);
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::I2C1>::kDmaReqTx == 34u);
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::I2C1>::kDmaReqRx == 35u);
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::I2C1>::kValidSdaPins[0] == dev::PinId::GP2);

// Primary template defaults.
static_assert(!ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::None>::kPresent);
static_assert(ds::I2cPeripheralTraits<ds::RuntimeI2cCtrlId::None>::kClockSource ==
              ds::RuntimeI2cClockSource::None);

int main() {}
