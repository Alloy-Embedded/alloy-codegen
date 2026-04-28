"""Tests for the iMXRT IOMUX → gpio_pins extraction.

Added by ``populate-imxrt-iomux-gpio-pins``.
"""

from __future__ import annotations

import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.ir.model import (  # noqa: E402
    GpioPinDescriptor,
    PinDefinition,
    PinSignal,
    Provenance,
)
from alloy_codegen.stages.normalize import (  # noqa: E402
    _build_imxrt_gpio_pins,
    _build_nxp_device_ir,
)


def _provenance() -> Provenance:
    return Provenance(source_id="test", source_path=None, patch_ids=())


def _signal(peripheral: str, signal: str, af: int) -> PinSignal:
    return PinSignal(
        function=f"{peripheral.lower()}_{signal.lower()}",
        peripheral=peripheral,
        signal=signal,
        af_number=af,
        provenance=_provenance(),
    )


def _pin(name: str, *signals: PinSignal) -> PinDefinition:
    return PinDefinition(
        name=name,
        port=None,
        number=int(name.rsplit("_", 1)[-1]),
        signals=signals,
        provenance=_provenance(),
    )


# ---------------------------------------------------------------------------
# Unit tests for the helper
# ---------------------------------------------------------------------------


def test_build_imxrt_gpio_pins_skips_pins_without_gpio_signal() -> None:
    """A pad whose IOMUX entries don't include a GPIO<n>_IO<xx>
    signal is skipped — those are dedicated pads (USB / JTAG)."""
    pin = _pin("GPIO_USB_DP_00", _signal("USB1", "DP", 0))
    descriptors = _build_imxrt_gpio_pins(pins=(pin,), provenance=_provenance())
    assert descriptors == ()


def test_build_imxrt_gpio_pins_extracts_port_and_index() -> None:
    """Spec scenario: IOMUX entry GPIO1.IO00 yields a
    GpioPinDescriptor with port="GPIO1" and pin_index=0."""
    pin = _pin(
        "GPIO_AD_B0_00",
        _signal("LPI2C1", "SCL", 0),
        _signal("LPUART1", "TX", 2),
        _signal("GPIO1", "IO00", 5),
    )
    descriptors = _build_imxrt_gpio_pins(pins=(pin,), provenance=_provenance())
    assert len(descriptors) == 1
    g = descriptors[0]
    assert g.pin_id == "GPIO_AD_B0_00"
    assert g.port == "GPIO1"
    assert g.pin_index == 0


def test_build_imxrt_gpio_pins_collects_alt_functions_excluding_gpio_self() -> None:
    """Alt-functions list every non-GPIO signal on the pad,
    sorted by (af_number, signal_name)."""
    pin = _pin(
        "GPIO_AD_B0_01",
        _signal("LPI2C1", "SDA", 0),
        _signal("LPUART1", "RX", 2),
        _signal("GPIO1", "IO01", 5),
    )
    descriptors = _build_imxrt_gpio_pins(pins=(pin,), provenance=_provenance())
    g = descriptors[0]
    af_pairs = [(af.af_number, af.peripheral, af.signal_name) for af in g.alt_functions]
    assert af_pairs == [
        (0, "LPI2C1", "SDA"),
        (2, "LPUART1", "RX"),
    ]
    # GPIO1.IO01 is the pin's identity, NOT in alt_functions.
    assert all(af.peripheral != "GPIO1" for af in g.alt_functions)


def test_build_imxrt_gpio_pins_computes_port_offset() -> None:
    """iMXRT GPIOn at 0x401B8000 + (n-1)*0x4000.  port_offset is
    the offset from the family's first GPIO bank."""
    pin1 = _pin("GPIO_EMC_00", _signal("GPIO4", "IO00", 5))
    pin2 = _pin("GPIO_AD_B0_00", _signal("GPIO1", "IO00", 5))
    descriptors = _build_imxrt_gpio_pins(pins=(pin1, pin2), provenance=_provenance())
    by_port = {g.pin_id: g for g in descriptors}
    assert by_port["GPIO_AD_B0_00"].port_offset == 0x0000  # GPIO1
    assert by_port["GPIO_EMC_00"].port_offset == 0xC000  # GPIO4 (3 * 0x4000)


def test_build_imxrt_gpio_pins_handles_empty_input() -> None:
    assert _build_imxrt_gpio_pins(pins=(), provenance=_provenance()) == ()


# ---------------------------------------------------------------------------
# End-to-end: iMXRT admission produces non-empty gpio_pins
# ---------------------------------------------------------------------------


def test_mimxrt1062_pipeline_populates_gpio_pins() -> None:
    """Spec scenario: the iMXRT IR has a non-empty ``gpio_pins``
    tuple after the pipeline runs against the IOMUX header."""
    fixtures = ROOT / "tests" / "fixtures" / "nxp-mcux-imxrt1060"
    ctx = ExecutionContext.default().with_overrides(
        source_overrides={
            "nxp-mcux-soc-svd": str(fixtures / "svd"),
            "nxp-mcux-sdk": str(fixtures / "sdk"),
        },
        artifact_root="/tmp/_imxrt_a",
        publication_root="/tmp/_imxrt_p",
    )
    ir = _build_nxp_device_ir(
        execution_context=ctx,
        device_name="mimxrt1062",
        vendor="nxp",
        family="imxrt1060",
    )
    assert len(ir.gpio_pins) >= 1, "iMXRT gpio_pins must be populated from IOMUX"
    # Every entry must have port=GPIO<N> and a sane pin_index.
    for g in ir.gpio_pins:
        assert isinstance(g, GpioPinDescriptor)
        assert g.port.startswith("GPIO")
        assert 0 <= g.pin_index < 32
