"""``PinmuxBackend`` Protocol — one adapter per family pinmux
backend schema id.

Family → backend schema id mapping (from ``openspec/project.md``):

==============================  ==========================================
Family                          ``pinmux_backend_schema_id``
==============================  ==========================================
``st/stm32*``                   ``alloy.pinmux.stm32-af-v1``
``microchip/same70``,``samv71``  ``alloy.pinmux.sam-pio-v1``
``microchip/samd21``,``samd51``,``saml21``  ``alloy.pinmux.sam-pmux-v1`` (new)
``microchip/avr-da``            ``alloy.pinmux.avr-portmux-v1``
``nxp/imxrt1060``               ``alloy.pinmux.imxrt-iomuxc-v1``
``raspberrypi/rp2040``          ``alloy.pinmux.rp2040-funcsel-v1``
``espressif/esp32*``            ``alloy.pinmux.espressif-iomatrix-v1``
==============================  ==========================================

Each backend exports a single ``encode(...)`` callable.  The
synthesiser (``ir.synthesised.builder``) walks
``device.peripherals[*].pin_options`` and calls the chosen
backend's ``encode(...)`` once per
``(peripheral_instance, peripheral_signal, pin_option)`` triple.
"""

from __future__ import annotations

from typing import Protocol, runtime_checkable

from alloy_codegen.ir.synthesised.pin_routes import PinRoute
from alloy_codegen.ir.v2_1 import (
    PeripheralInstance,
    PinOptionFixed,
    PinOptionMatrix,
    PinOptionPsel,
)

PinOption = PinOptionFixed | PinOptionMatrix | PinOptionPsel


@runtime_checkable
class PinmuxBackend(Protocol):
    """One vendor-specific pin-route encoding adapter.

    ``schema_id`` SHALL match ``device.identity.family``'s
    ``pinmux_backend_schema_id`` exactly.

    ``encode`` returns one :class:`PinRoute` per call.  When the
    on-disk YAML doesn't yet carry the routing code the backend
    expects (e.g. STM32 admits pad candidates without AF numbers
    today), the backend SHALL still return a ``PinRoute`` with
    ``code=None``; the emitter publishes the route entry so
    consumers can refuse invalid pad↔signal combinations at
    compile time.
    """

    schema_id: str

    def encode(
        self,
        peripheral: PeripheralInstance,
        signal: str,
        option: PinOption,
    ) -> PinRoute:
        ...
