"""Per-vendor compatible-map coverage tests added by
``extend-zephyr-dts-vendor-coverage``.

These tests assert the *vocabulary* surface of the Zephyr DTS
adapter — they do not parse real DTS files.  Goldens for each
new vendor land separately when an admission proposal pulls a
device into ``DEVICE_REGISTRY``.
"""

from __future__ import annotations

import sys
import textwrap
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.errors import StageExecutionError  # noqa: E402
from alloy_codegen.sources.zephyr_dts import (  # noqa: E402
    AMBIQ_COMPATIBLE_MAP,
    ATMEL_COMPATIBLE_MAP,
    COMPATIBLE_MAPS,
    ESPRESSIF_COMPATIBLE_MAP,
    INFINEON_COMPATIBLE_MAP,
    NORDIC_COMPATIBLE_MAP,
    RENESAS_RA_COMPATIBLE_MAP,
    SILABS_COMPATIBLE_MAP,
    TI_COMPATIBLE_MAP,
    compatible_map_for_vendor,
    parse_zephyr_device_document,
)

_NEW_VENDORS = (
    "renesas",
    "ti",
    "atmel",
    "ambiq",
    "infineon",
    "silabs",
    "espressif",
)


def test_all_new_vendors_registered() -> None:
    for vendor in _NEW_VENDORS:
        assert vendor in COMPATIBLE_MAPS, f"missing {vendor!r} from COMPATIBLE_MAPS"
    # Nordic is preserved.
    assert "nordic" in COMPATIBLE_MAPS


@pytest.mark.parametrize("vendor", _NEW_VENDORS)
def test_vendor_map_covers_minimum_peripherals(vendor: str) -> None:
    mapping = compatible_map_for_vendor(vendor)
    ip_names = set(mapping.values())
    # Every map must cover the bedrock peripheral classes.
    for required in ("uart", "spi", "i2c", "gpio"):
        assert required in ip_names, f"{vendor} map missing {required}"
    # Must carry at least one of timer/pwm.
    assert ip_names & {"timer", "pwm"}, f"{vendor} map carries neither timer nor pwm"


@pytest.mark.parametrize("vendor", _NEW_VENDORS + ("nordic",))
def test_vendor_map_values_are_clean_lowercase(vendor: str) -> None:
    mapping = compatible_map_for_vendor(vendor)
    for compatible, ip_name in mapping.items():
        assert compatible, f"{vendor}: empty compatible string"
        assert ip_name, f"{vendor} {compatible}: empty ip-name"
        assert ip_name == ip_name.lower(), (
            f"{vendor} {compatible}: ip-name {ip_name!r} is not lowercase"
        )
        assert " " not in ip_name, f"{vendor} {compatible}: ip-name has whitespace"


def test_renesas_ra_minimum_compatibles() -> None:
    mapping = compatible_map_for_vendor("renesas")
    assert mapping["renesas,ra-sci-uart"] == "uart"
    assert mapping["renesas,ra-spi"] == "spi"
    assert mapping["renesas,ra-sci-i2c"] == "i2c"
    assert mapping["renesas,ra-ioport"] == "gpio"


def test_espressif_minimum_compatibles_and_pwm() -> None:
    mapping = compatible_map_for_vendor("espressif")
    assert mapping["espressif,esp32-uart"] == "uart"
    assert mapping["espressif,esp32-spi"] == "spi"
    assert mapping["espressif,esp32-i2c"] == "i2c"
    assert mapping["espressif,esp32-gpio"] == "gpio"
    pwm_keys = {k for k, v in mapping.items() if v == "pwm"}
    assert {"espressif,esp32-mcpwm", "espressif,esp32-ledc"} & pwm_keys


def test_silabs_minimum_compatibles() -> None:
    mapping = compatible_map_for_vendor("silabs")
    assert mapping["silabs,gecko-usart"] == "uart"
    assert mapping["silabs,gecko-spi-usart"] == "spi"
    assert mapping["silabs,gecko-i2c"] == "i2c"
    assert mapping["silabs,gecko-gpio"] == "gpio"


def test_generic_arm_nvic_present_under_every_vendor() -> None:
    """The shared `_GENERIC_COMPATIBLE_MAP` must merge into every
    vendor lookup so ARM-core bindings don't have to be repeated."""
    for vendor in COMPATIBLE_MAPS:
        mapping = compatible_map_for_vendor(vendor)
        assert "arm,armv7m-nvic" in mapping
        assert mapping["arm,armv7m-nvic"] == "nvic"
        assert "arm,armv8m-nvic" in mapping


def test_generic_map_is_not_in_per_vendor_dicts() -> None:
    """Sanity-check the merge isn't accidental — the per-vendor
    dicts should NOT redeclare the generic compatibles."""
    for vendor_map in (
        NORDIC_COMPATIBLE_MAP,
        RENESAS_RA_COMPATIBLE_MAP,
        TI_COMPATIBLE_MAP,
        ATMEL_COMPATIBLE_MAP,
        AMBIQ_COMPATIBLE_MAP,
        INFINEON_COMPATIBLE_MAP,
        SILABS_COMPATIBLE_MAP,
        ESPRESSIF_COMPATIBLE_MAP,
    ):
        assert "arm,armv7m-nvic" not in vendor_map


def test_unknown_vendor_raises_with_known_keys_listed() -> None:
    with pytest.raises(StageExecutionError) as excinfo:
        compatible_map_for_vendor("not-a-vendor")
    msg = str(excinfo.value)
    for vendor in _NEW_VENDORS + ("nordic",):
        assert vendor in msg


def test_unmapped_compatible_is_recorded_not_raised(tmp_path: Path) -> None:
    """Synthetic DTS with an unknown vendor compatible — the
    adapter must record it in `skipped_compatibles` and continue."""
    dts_text = textwrap.dedent("""\
        /dts-v1/;
        / {
            #address-cells = <1>;
            #size-cells = <1>;
            soc {
                #address-cells = <1>;
                #size-cells = <1>;
                compatible = "simple-bus";
                ranges;

                frob0: frobnicator@40000000 {
                    compatible = "acme,frobnicator-2000";
                    reg = <0x40000000 0x1000>;
                };
            };
        };
    """)
    dts_path = tmp_path / "synthetic.dts"
    dts_path.write_text(dts_text, encoding="utf-8")

    doc = parse_zephyr_device_document(
        dts_path,
        compatible_map=compatible_map_for_vendor("nordic"),
    )
    assert "acme,frobnicator-2000" in doc.skipped_compatibles
    assert all(p.name != "FROB0" for p in doc.raw.peripherals)


def test_nordic_map_unchanged_keys() -> None:
    """Regression guard: the Nordic map shape (a few representative
    keys) must not silently shift while we extend other vendors."""
    mapping = NORDIC_COMPATIBLE_MAP
    assert mapping["nordic,nrf-uarte"] == "uart"
    assert mapping["nordic,nrf-twim"] == "i2c"
    assert mapping["nordic,nrf-saadc"] == "adc"
    assert mapping["nordic,nrf-gpio"] == "gpio"
    assert mapping["nordic,nrf-pwm"] == "pwm"
