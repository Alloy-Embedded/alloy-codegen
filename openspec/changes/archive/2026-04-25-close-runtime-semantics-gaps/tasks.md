## 1. Driver Semantics FieldRef Completeness

- [x] 1.1 Extend `_microchip_i2c_row` so TWIHS CR.START / CR.STOP / CR.MSEN /
      CR.MSDIS / CR.SVDIS resolve to valid `RuntimeFieldRef`.
- [x] 1.2 Do the same pass for SPI, USART, PMC, and GMAC row builders.
- [x] 1.3 Add a unit test that asserts zero `kInvalidFieldRef` entries for
      the HAL-referenced field set of each admitted family.

## 2. Peripheral Base Accessor

- [x] 2.1 Emit
      `template <PeripheralId Id> constexpr auto alloy::device::base() noexcept`
      returning `PeripheralInstanceTraits<Id>::kBaseAddress` in
      `runtime_lite_peripheral_instances.hpp`.
- [x] 2.2 Golden-test the emission for one SAM E70 and one STM32 device.

## 3. Clock Enable / Disable Helpers

- [x] 3.1 Emit `alloy::clock::enable(PeripheralId)` and
      `alloy::clock::disable(PeripheralId)` in
      `runtime_lite_clock_bindings.hpp`, resolving to the correct PCERx
      register write for SAM E70 (and the equivalent for STM32 / NXP).
- [x] 3.2 Guard against `PeripheralId` values that have no clock binding
      at compile time.

## 4. Pinmux Route Helper

- [x] 4.1 Emit
      `template <PinId, PeripheralId, SignalId> void alloy::pinmux::route() noexcept`
      in `runtime_lite_routes.hpp` that writes the vendor selector(s) for
      the route already captured in the table.
- [x] 4.2 Compile-time diagnostic when the `(Pin, Peripheral, Signal)`
      triple has no matching route entry.

## 5. Validation

- [x] 5.1 `python -m ruff format src tests` + `python -m ruff check src tests`.
- [x] 5.2 `python -m pytest tests` green.
- [x] 5.3 `openspec validate close-runtime-semantics-gaps --strict`.
- [x] 5.4 Republish all four admitted families into `alloy-devices`.
