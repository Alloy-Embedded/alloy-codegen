"""Emit ``peripheral_id.hpp`` from a v2.1 :class:`CanonicalDevice`.

Produces a single ``enum class PeripheralId`` with one enumerator per
peripheral instance declared in the device YAML, plus the ``kCount``
sentinel.

Design rationale
----------------
The old ``alloy-devices`` format shipped a hand-written or template-
generated ``PeripheralId`` enum that every HAL driver could use for
compile-time dispatch (e.g. ``IrqSemanticTraits<PeripheralId::kUsart1>``).
The new ``alloy-codegen`` ``peripheral_traits.h`` uses flat namespaces
(``alloy::…::usart1::kBaseAddress``) which are great for direct access
but lose the type-level enumeration needed for generic code.

This emitter bridges the gap: it generates a typed ``PeripheralId``
enum whose enumerators match the namespace names in ``peripheral_traits.h``
(same ``to_lower(id)`` → ``kCamelCase`` convention), plus a convenience
``constexpr std::size_t kPeripheralCount``.

Usage in downstream HAL
-----------------------
.. code-block:: cpp

    #include "peripheral_id.hpp"
    using namespace alloy::st::stm32g0::stm32g071rb;

    // type-safe peripheral selector
    template <PeripheralId Id>
    struct MyDriver { … };

    // iterate all peripherals at compile time via the sentinel
    static_assert(static_cast<unsigned>(PeripheralId::kCount) > 0);
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised import SynthesisedDevice
from alloy_codegen.ir.v2_1 import CanonicalDevice


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


def _header_guard(device: CanonicalDevice) -> str:
    parts = (
        device.identity.vendor,
        device.identity.family,
        device.identity.device,
        "peripheral_id_hpp",
    )
    return "_".join(p.upper().replace("-", "_") for p in parts) + "_"


def _to_enum_name(per_id: str) -> str:
    """Convert a peripheral id to a CamelCase enum enumerator.

    Examples::

        "usart1"  → "kUsart1"
        "gpio_b"  → "kGpioB"
        "spi1"    → "kSpi1"
        "adc12"   → "kAdc12"
    """
    # Split on underscores, capitalise each part, re-join
    parts = per_id.replace("-", "_").split("_")
    camel = "".join(p.capitalize() for p in parts if p)
    return f"k{camel}"


def _namespace_path(device: CanonicalDevice) -> str:
    v = device.identity.vendor.replace("-", "_").lower()
    f = device.identity.family.replace("-", "_").lower()
    d = device.identity.device.replace("-", "_").lower()
    return f"alloy::{v}::{f}::{d}"


# ---------------------------------------------------------------------------
# Public emitter
# ---------------------------------------------------------------------------


def emit_peripheral_id(
    device: CanonicalDevice,
    synthesised: SynthesisedDevice,  # noqa: ARG001 — API symmetry
) -> str:
    """Render the ``peripheral_id.hpp`` enum header for ``device``."""
    guard = _header_guard(device)
    ns = _namespace_path(device)

    lines: list[str] = [
        f"/* peripheral_id.hpp",
        f" *",
        f" * {device.identity.vendor}/{device.identity.family}/{device.identity.device}"
        f" — generated from {device.schema}",
        f" *",
        f" * Schema: {device.schema}",
        f" * Provenance: {device.provenance.primary}",
        f" */",
        f"#pragma once",
        f"#ifndef {guard}",
        f"#define {guard}",
        f"",
        f"#include <cstddef>",
        f"",
        f"namespace {ns} {{",
        f"",
        f"/// Typed enumeration of every peripheral instance on this device.",
        f"/// Enumerator names mirror the flat namespaces in peripheral_traits.h",
        f"/// (e.g. PeripheralId::kUsart1 ↔ alloy::…::usart1::kBaseAddress).",
        f"enum class PeripheralId : unsigned {{",
    ]

    for per in device.peripherals:
        enum_name = _to_enum_name(per.id)
        lines.append(f"  {enum_name},")

    lines += [
        f"  kCount,  ///< Sentinel — total number of peripheral instances.",
        f"}};",
        f"",
        f"/// Total number of peripheral instances declared for this device.",
        f"inline constexpr std::size_t kPeripheralCount =",
        f"    static_cast<std::size_t>(PeripheralId::kCount);",
        f"",
        f"}}  // namespace {ns}",
        f"",
        f"#endif  // {guard}",
        f"",
    ]

    return "\n".join(lines)
