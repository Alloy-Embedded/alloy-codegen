"""Tests for the Zephyr DTS source adapter and Nordic nRF52
admission pipeline.  Added by ``ingest-zephyr-dts-as-source``."""

from __future__ import annotations

import sys
import textwrap
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.errors import StageExecutionError  # noqa: E402
from alloy_codegen.scope import PipelineScope  # noqa: E402
from alloy_codegen.sources.zephyr_dts import (  # noqa: E402
    NORDIC_COMPATIBLE_MAP,
    SOURCE_ID,
    compatible_map_for_vendor,
    ensure_source_root,
    parse_zephyr_device_document,
    peripheral_instance_index,
    resolve_dts_path,
)
from alloy_codegen.stages.normalize import run as run_normalize  # noqa: E402
from alloy_codegen.vendors import (  # noqa: E402
    list_registered_adapters,
    resolve_vendor_adapter,
)


@pytest.fixture
def zephyr_dts_root() -> Path:
    return ROOT / "tests" / "fixtures" / "zephyr-dts"


@pytest.fixture
def nordic_nrf52_dts(zephyr_dts_root: Path) -> Path:
    return zephyr_dts_root / "nordic" / "nrf52840.dts"


@pytest.fixture
def nordic_nrf52_context(zephyr_dts_root: Path, tmp_path: Path) -> ExecutionContext:
    return ExecutionContext.default().with_overrides(
        source_overrides={SOURCE_ID: str(zephyr_dts_root)},
        artifact_root=str(tmp_path / "artifacts"),
        publication_root=str(tmp_path / "publication"),
    )


# ---------------------------------------------------------------------------
# Adapter unit tests
# ---------------------------------------------------------------------------


def test_parse_extracts_nordic_peripherals(nordic_nrf52_dts: Path) -> None:
    """Adapter pulls out the canonical Nordic peripheral set."""
    doc = parse_zephyr_device_document(
        nordic_nrf52_dts, compatible_map=NORDIC_COMPATIBLE_MAP
    )
    names = {p.name for p in doc.raw.peripherals}
    expected = {"UART0", "SPI0", "I2C0", "TIMER0", "RTC0", "GPIO0", "WDT0"}
    assert expected.issubset(names), f"missing peripherals: {expected - names}"


def test_parse_extracts_interrupts_with_peripheral_attribution(
    nordic_nrf52_dts: Path,
) -> None:
    doc = parse_zephyr_device_document(
        nordic_nrf52_dts, compatible_map=NORDIC_COMPATIBLE_MAP
    )
    irqs_by_peripheral = {irq.peripheral: irq.line for irq in doc.raw.interrupts}
    assert irqs_by_peripheral["UART0"] == 2
    assert irqs_by_peripheral["TIMER0"] == 8
    assert irqs_by_peripheral["RTC0"] == 11
    assert irqs_by_peripheral["WDT0"] == 16


def test_parse_extracts_memory_regions(nordic_nrf52_dts: Path) -> None:
    doc = parse_zephyr_device_document(
        nordic_nrf52_dts, compatible_map=NORDIC_COMPATIBLE_MAP
    )
    bases = {m.base_address: m.size_bytes for m in doc.memories}
    assert bases.get(0x20000000) == 0x40000  # SRAM 256 KB
    assert bases.get(0x00000000) == 0x100000  # Flash 1 MB


def test_unsupported_compatible_strings_are_skipped_not_raised(tmp_path: Path) -> None:
    """Spec: unsupported compatibles must skip without raising."""
    dts = tmp_path / "exotic.dts"
    dts.write_text(
        textwrap.dedent(
            """
            /dts-v1/;
            / {
                soc {
                    compatible = "simple-bus";
                    exotic: exotic@40000000 {
                        compatible = "renesas,future-uart";
                        reg = <0x40000000 0x1000>;
                        interrupts = <99 1>;
                    };
                };
            };
            """
        ).strip(),
        encoding="utf-8",
    )
    doc = parse_zephyr_device_document(dts, compatible_map=NORDIC_COMPATIBLE_MAP)
    assert doc.raw.peripherals == ()
    assert "renesas,future-uart" in doc.skipped_compatibles


def test_peripheral_instance_index_strips_alpha_prefix() -> None:
    assert peripheral_instance_index("uart0", "uart@40002000") == 0
    assert peripheral_instance_index("spi2", "spi@40003000") == 2
    assert peripheral_instance_index(None, "weird@4000") == 0


def test_compatible_map_for_unknown_vendor_raises() -> None:
    with pytest.raises(StageExecutionError, match="No Zephyr compatible map"):
        compatible_map_for_vendor("acme")


# ---------------------------------------------------------------------------
# Source-root resolution
# ---------------------------------------------------------------------------


def test_ensure_source_root_aborts_when_unconfigured(tmp_path: Path) -> None:
    bare_ctx = ExecutionContext.default().with_overrides(
        source_overrides={},
        artifact_root=str(tmp_path / "a"),
        publication_root=str(tmp_path / "p"),
    )
    with pytest.raises(StageExecutionError, match="zephyr-dts source root"):
        ensure_source_root(bare_ctx)


def test_resolve_dts_path_finds_nordic_layout(
    nordic_nrf52_context: ExecutionContext, nordic_nrf52_dts: Path
) -> None:
    resolved = resolve_dts_path(
        nordic_nrf52_context, vendor="nordic", family="nrf52", device="nrf52840"
    )
    assert resolved == nordic_nrf52_dts


# ---------------------------------------------------------------------------
# Vendor-registry integration
# ---------------------------------------------------------------------------


def test_nordic_nrf52_resolves_through_registry() -> None:
    adapter = resolve_vendor_adapter("nordic", "nrf52")
    assert adapter.vendor == "nordic"
    assert adapter.family == "nrf52"
    assert callable(adapter.fetch)
    assert callable(adapter.normalize)


def test_nordic_nrf52_listed_in_registered_adapters() -> None:
    pairs = list_registered_adapters()
    assert ("nordic", "nrf52") in pairs


# ---------------------------------------------------------------------------
# End-to-end normalize pipeline
# ---------------------------------------------------------------------------


def test_normalize_nrf52840_produces_canonical_ir(
    nordic_nrf52_context: ExecutionContext,
) -> None:
    """Spec scenario: nRF52 device admitted via Zephyr DTS produces a
    valid canonical IR with peripheral instances + IRQ numbers."""
    result = run_normalize(PipelineScope(device="nrf52840"), nordic_nrf52_context)
    assert len(result.payload.devices) == 1
    device = result.payload.devices[0]

    # Identity
    assert device.identity.vendor == "nordic"
    assert device.identity.family == "nrf52"
    assert device.identity.device == "nrf52840"
    assert device.identity.core == "cortex-m4f"
    assert device.identity.package == "aqfn73"

    # Memories from device patch
    memory_kinds = {m.kind for m in device.memories}
    assert "flash" in memory_kinds
    assert "sram" in memory_kinds

    # Peripherals from DTS, restricted by patch allowlist
    peripheral_names = {p.name for p in device.peripherals}
    assert {"UART0", "SPI0", "I2C0", "TIMER0", "RTC0", "GPIO0"}.issubset(peripheral_names)
    # Family ip_version flowed through
    uart0 = next(p for p in device.peripherals if p.name == "UART0")
    assert uart0.ip_version == "nrf-uart-v1"

    # IRQs attributed to admitted peripherals only
    irq_peripherals = {irq.peripheral for irq in device.interrupts if irq.peripheral}
    assert irq_peripherals.issubset(peripheral_names | {None})


def test_normalize_nrf52840_filters_out_unmapped_dts_compatibles(
    nordic_nrf52_context: ExecutionContext,
) -> None:
    """DTS nodes whose ``compatible`` is not in
    :data:`NORDIC_COMPATIBLE_MAP` (or which carry no ``reg``) are
    silently skipped — the resulting IR carries only mapped
    peripherals."""
    result = run_normalize(PipelineScope(device="nrf52840"), nordic_nrf52_context)
    device = result.payload.devices[0]
    peripheral_names = {p.name for p in device.peripherals}
    # Sanity: nothing exotic crept in; every admitted peripheral is
    # part of the family catalog's known set.
    family_known = {
        "UART0", "UART1", "SPI0", "SPI1", "SPI2", "I2C0", "I2C1",
        "TIMER0", "TIMER1", "TIMER2", "RTC0", "RTC1", "PWM0",
        "ADC0", "WDT0", "GPIO0", "GPIO1",
    }
    assert peripheral_names.issubset(family_known)


def test_zephyr_dts_adapter_does_not_clone_silently(tmp_path: Path) -> None:
    """The Zephyr adapter MUST refuse to silently clone the
    multi-hundred-MB Zephyr repo — caller must point at a checkout
    explicitly via the source override."""
    bare_ctx = ExecutionContext.default().with_overrides(
        source_overrides={},
        artifact_root=str(tmp_path / "a"),
        publication_root=str(tmp_path / "p"),
    )
    adapter = resolve_vendor_adapter("nordic", "nrf52")
    with pytest.raises(StageExecutionError, match="zephyr-dts source root"):
        adapter.fetch(bare_ctx, PipelineScope(device="nrf52840"))
