"""Emit ``rcc_traits.hpp`` carrying the typed ``GateModel`` enum.

The alloy HAL needs a typed ``enum class GateModel`` so that
``RccTraits<P>::EnableClock()`` can ``constexpr if`` on the gate
strategy of every peripheral:

* ``always_on``       — silicon has no per-peripheral gate (Microchip
                        AVR-Dx, Nordic NRF52); EnableClock is a no-op.
* ``per_peri_en``     — single bit gates clock + reset (RP2040,
                        Microchip SAMD51 mclk / SAMD21 pm).
* ``per_peri_en_rst`` — separate enable + reset bits in centralised
                        registers (every STM32 family).
* ``index_based``     — gate identified by a numeric index, NOT a
                        peripheral name; HAL parses the
                        ``kRccEnable`` path verbatim
                        (NXP iMXRT CCGR).
* ``per_peri_pcr``    — gate lives inside the peripheral's own
                        register block, not a centralised enable
                        register (ESP32-C3 / S3 PCR fast-path
                        peripherals).

The enum is emitted into ``rcc_traits.hpp`` (a sibling header to
``peripheral_id.hpp``) so HAL drivers consume it via:

.. code-block:: cpp

    #include "rcc_traits.hpp"

    using namespace alloy::nxp::imxrt1060::mimxrt1062;

    template <PeripheralId Id> struct LpuartDriver {
      static constexpr void EnableClock() {
        if constexpr (lpuart1::kGateModel == GateModel::always_on) {
          // no-op
        } else if constexpr (lpuart1::kGateModel == GateModel::index_based) {
          // CCGR write — parse kRccEnable verbatim
          MmioWrite(parse_register_path(lpuart1::kRccEnable), 0b11);
        } else {
          // per_peri_en / per_peri_en_rst — uniform path
          MmioWrite(parse_register_path(lpuart1::kRccEnable), 0b1);
        }
      }
    };
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised import SynthesisedDevice
from alloy_codegen.ir.v2_1 import CanonicalDevice


def _header_guard(device: CanonicalDevice) -> str:
    parts = (
        device.identity.vendor,
        device.identity.family,
        device.identity.device,
        "rcc_traits_h",
    )
    return "_".join(p.upper().replace("-", "_") for p in parts) + "_"


def _namespace_path(device: CanonicalDevice) -> str:
    v = device.identity.vendor.replace("-", "_").lower()
    f = device.identity.family.replace("-", "_").lower()
    d = device.identity.device.replace("-", "_").lower()
    return f"alloy::{v}::{f}::{d}"


def emit_rcc_traits(
    device: CanonicalDevice,
    synthesised: SynthesisedDevice,  # noqa: ARG001 — API symmetry
) -> str:
    """Render the ``rcc_traits.hpp`` header carrying the typed
    ``GateModel`` enum.

    The enum body is identical for every device — the alloy-codegen
    boundary stamp lives here and the per-peripheral ``kGateModel``
    value lives in ``peripheral_traits.h``.  Co-locating the enum
    with the device's other generated headers keeps the include
    graph closed (no cross-device dependency).
    """
    guard = _header_guard(device)
    ns = _namespace_path(device)

    lines = [
        "/* rcc_traits.hpp",
        " *",
        f" * {device.identity.vendor}/{device.identity.family}/{device.identity.device}"
        f" — generated from {device.schema}",
        " *",
        " * Typed GateModel enum for compile-time dispatch by HAL drivers.",
        " * See alloy-codegen `complete-rcc-synthesis-cross-vendor`",
        " * proposal for the full semantics of each enumerator.",
        " */",
        "#pragma once",
        f"#ifndef {guard}",
        f"#define {guard}",
        "",
        f"namespace {ns} {{",
        "",
        "/// Closed five-value enumeration describing how the silicon",
        "/// gates a peripheral's clock / reset.  Every peripheral",
        "/// instance carries a `static constexpr GateModel kGateModel`",
        "/// drawn from this set; HAL drivers `constexpr if` on it to",
        "/// pick the right MMIO sequence.",
        "enum class GateModel : unsigned {",
        "  always_on,        ///< no per-peripheral gate (AVR-Dx, NRF52)",
        "  per_peri_en,      ///< single bit gates clock + reset",
        "  per_peri_en_rst,  ///< separate enable + reset bits",
        "  index_based,      ///< CCGR-style index, parse path verbatim",
        "  per_peri_pcr,     ///< gate inside peripheral's own register",
        "};",
        "",
        f"}}  // namespace {ns}",
        "",
        f"#endif  // {guard}",
        "",
    ]

    return "\n".join(lines)
