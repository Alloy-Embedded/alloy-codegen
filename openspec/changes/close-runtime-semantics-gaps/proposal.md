## Why

Bring-up of the seed drivers on SAME70 Xplained Ultra (AT24MAC402, IS42S16100F,
KSZ8081) exposed that the runtime-lite contract does not carry enough semantic
information for HAL backends or probes to drive peripherals without reaching
for raw MMIO. Concrete evidence from the alloy repo:

- **Driver semantics emit `kInvalidFieldRef` for fields the HAL references.**
  TWIHS `CR.START`, `CR.STOP`, `CR.MSEN`, `CR.MSDIS`, `CR.SVDIS` were all
  unpopulated, forcing raw bit-masks in `src/hal/i2c/detail/backend.hpp`. The
  same gap affects SPI, USART, PMC, GMAC rows.
- **No typed pin-route helper.** `routes.hpp` carries the correct
  `(PinId, PeripheralId, SignalId) → selector` table but no
  `alloy::pinmux::route<Pin, Peripheral, Signal>()` free function is emitted,
  so every probe re-implements `ABCDSR1 / ABCDSR2 / PDR` by hand and gets it
  wrong.
- **No typed clock enable/disable.** `clock_bindings.hpp` carries the
  `ClockGateId → PCER register + bit` mapping but no
  `alloy::clock::enable(PeripheralId)` free function is emitted. Probes write
  `PMC_PCER0/PCER1` with magic PID numbers.
- **No typed peripheral base accessor.** `PeripheralInstanceTraits<Id>::kBaseAddress`
  is emitted but no `alloy::device::base<PeripheralId>()` accessor exists, so
  probes type base-address literals (and got GMAC wrong — wrote XDMAC's base).

## What Changes

1. **Extend `RuntimeFieldRef` emission** in `runtime_driver_semantics.py` so
   that every CR/SR/MR bit referenced by a public HAL backend resolves to a
   valid `RuntimeFieldRef` (bit offset + width). Minimum scope: TWIHS, SPI,
   USART, PMC, GMAC rows for Microchip SAM E70, and the equivalent rows for
   the other admitted families.
2. **Emit `alloy::pinmux::route<PinId, PeripheralId, SignalId>()`** in
   `runtime_lite_emission.py` (routes header). Writes the vendor-correct
   selector register(s) for the route already captured in `routes.hpp`.
   SAM E70: `ABCDSR1` / `ABCDSR2` / `PDR` at the correct pin offset.
   Compile-time diagnostic when the `(Pin, Peripheral, Signal)` triple has
   no route entry.
3. **Emit `alloy::clock::enable(PeripheralId)` / `disable(PeripheralId)`**
   in `runtime_lite_emission.py` (clock bindings header). Resolves to the
   correct PCERx register and bit.
4. **Emit `alloy::device::base<PeripheralId>()`** in `runtime_lite_emission.py`
   (peripheral instances header). Returns
   `PeripheralInstanceTraits<Id>::kBaseAddress`.

Out of scope for this change:

- New peripheral families beyond the currently admitted set.
- Changing the canonical IR schema — this change is emitter-side.
- HAL-side refactors (happen in the alloy repo under
  `close-codegen-semantics-gaps`).

## Outcome

After this change:

- Adopter probes and HAL backends can drive TWIHS / SPI / USART / PMC / GMAC
  without typing raw bit masks or base-address literals.
- Pinmux, clock enable, and base-address MMIO never leak into user code.
- A regression that re-introduces `kInvalidFieldRef` for a HAL-referenced
  field is caught by the compile-time smoke check on the alloy side.

## Impact

- Affected specs:
  - modified: `runtime-lite-contract`
- Affected code:
  - `src/alloy_codegen/runtime_driver_semantics.py` (FieldRef completeness)
  - `src/alloy_codegen/runtime_lite_emission.py` (new emitters for
    `alloy::pinmux::route`, `alloy::clock::enable/disable`,
    `alloy::device::base`)
- Republished artifacts:
  - `alloy-devices/microchip/same70/generated/**`
  - `alloy-devices/st/stm32g0/generated/**`
  - `alloy-devices/st/stm32f4/generated/**`
  - `alloy-devices/nxp/imxrt1060/generated/**`
