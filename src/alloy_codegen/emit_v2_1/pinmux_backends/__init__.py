"""Pinmux-backend registry.

Backends are keyed by ``(vendor, family)`` because STM32 G0 and
SAM E70 might both ship under ``microchip`` someday but use
different pinmux schemas.  ``backend_for(vendor, family)``
returns the backend or ``None`` when no backend has shipped yet
(the synthesiser then leaves ``pin_routes`` empty for that
device).
"""

from __future__ import annotations

from alloy_codegen.emit_v2_1.pinmux_backends._protocol import PinmuxBackend
from alloy_codegen.emit_v2_1.pinmux_backends.stm32_af import STM32_AF_BACKEND


def registry() -> dict[tuple[str, str], PinmuxBackend]:
    """Return the ``(vendor, family-prefix) → PinmuxBackend`` map.

    ``family-prefix`` matches via ``str.startswith`` so a single
    entry covers every STM32 family (``stm32f0``, ``stm32f4``,
    ``stm32g0``, ...).  Add new entries as backends land; the
    synthesiser never branches on vendor or family directly.
    """
    return {
        ("st", "stm32"): STM32_AF_BACKEND,
        # Future entries:
        # ("microchip", "same70"): SAM_PIO_BACKEND,
        # ("microchip", "samv71"): SAM_PIO_BACKEND,
        # ("microchip", "samd"):   SAM_PMUX_BACKEND,
        # ("microchip", "saml"):   SAM_PMUX_BACKEND,
        # ("microchip", "avr"):    AVR_PORTMUX_BACKEND,
        # ("nxp", "imxrt"):        IMXRT_IOMUXC_BACKEND,
        # ("raspberrypi", "rp"):   RP2040_FUNCSEL_BACKEND,
        # ("espressif", "esp32"):  ESPRESSIF_IOMATRIX_BACKEND,
    }


def backend_for(vendor: str, family: str) -> PinmuxBackend | None:
    """Pick the pinmux backend matching ``(vendor, family)`` via
    family-prefix lookup.  Returns ``None`` when no backend has
    shipped for the family yet."""
    v = vendor.lower()
    f = family.lower()
    for (vk, fk), backend in registry().items():
        if vk == v and f.startswith(fk):
            return backend
    return None


__all__ = ["PinmuxBackend", "backend_for", "registry"]
