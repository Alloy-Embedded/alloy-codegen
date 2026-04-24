from __future__ import annotations

from pathlib import Path
from zipfile import ZIP_DEFLATED, ZipFile

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.microchip_dfp import (
    SVD_OPTIONAL_FAMILIES,
    parse_memory_patches,
    parse_peripheral_patches,
    select_device_files,
)
from alloy_codegen.stages.fetch import run as run_fetch


def _build_fixture_pack(source_root: Path, archive_path: Path) -> None:
    with ZipFile(archive_path, "w", compression=ZIP_DEFLATED) as archive:
        for path in sorted(source_root.rglob("*")):
            if not path.is_file():
                continue
            archive.write(path, arcname=str(path.relative_to(source_root)))


def test_fetch_microchip_accepts_local_atpack_input(
    fixture_microchip_extract_root: Path,
    tmp_path: Path,
) -> None:
    archive_path = tmp_path / "Microchip.SAME70_DFP.fixture.atpack"
    _build_fixture_pack(fixture_microchip_extract_root, archive_path)
    default_context = ExecutionContext.default()
    alloy_root = default_context.alloy_root or (
        Path("/Users/lgili/Documents/01 - Codes/01 - Github/alloy")
    )
    execution_context = default_context.with_overrides(
        source_overrides={"microchip-dfp-pack": str(archive_path)},
        artifact_root=str(tmp_path / "artifacts"),
        publication_root=str(tmp_path / "publication"),
        alloy_root=str(alloy_root),
    )

    result = run_fetch(PipelineScope(device="atsame70n21b"), execution_context)
    sources = result.payload.source_manifest.sources

    assert {source.source_id for source in sources} == {
        "microchip-dfp-pack",
        "microchip-dfp-extract",
    }
    assert any(
        source.source_id == "microchip-dfp-pack"
        and source.local_path.endswith(".atpack")
        and source.revision.startswith("content-sha256:")
        for source in sources
    )
    assert any(
        source.source_id == "microchip-dfp-extract"
        and source.local_path.endswith("ATSAME70N21B.atdf")
        and source.upstream_path == "same70b/atdf/ATSAME70N21B.atdf"
        for source in sources
    )


# ---------------------------------------------------------------------------
# AVR-DA Phase 0.5 / 0.6 — ATDF-only DFP source adapter tests
# ---------------------------------------------------------------------------

AVR_DA_FIXTURE = Path(__file__).parent / "fixtures" / "microchip-dfp-avr-da"


def _avr_da_context() -> ExecutionContext:
    return ExecutionContext.default().with_overrides(
        source_overrides={"microchip-dfp-extract": str(AVR_DA_FIXTURE)},
    )


def test_avr_da_is_registered_as_an_svd_optional_family() -> None:
    """Phase 0.2: SVD_OPTIONAL_FAMILIES must include microchip/avr-da so the
    selector does not fail when the PDSC omits the <debug svd=...> node."""
    assert ("microchip", "avr-da") in SVD_OPTIONAL_FAMILIES


def test_select_avr_da_files_resolves_atdf_without_svd() -> None:
    """Phase 0.6: select_device_files returns a populated ATDF path and a
    None SVD path for AVR128DA32, exercising the SVD-optional code path."""
    selected = select_device_files(
        _avr_da_context(), "avr128da32", vendor="microchip", family="avr-da"
    )
    assert selected.device_name == "avr128da32"
    assert selected.atdf_path.exists()
    assert selected.atdf_path.name == "AVR128DA32.atdf"
    # AVR devices publish no CMSIS-SVD; the adapter must accept None.
    assert selected.svd_path is None


def test_avr128da32_atdf_declares_harvard_address_spaces() -> None:
    """Phase 1.1/1.3 × AVR-DA: parsing the AVR128DA32 ATDF yields memory
    patches annotated with the three Harvard address spaces (prog/data/eeprom)
    and classifies the EEPROM region with ``kind="eeprom"``.

    This is the regression gate that proves the existing Microchip DFP
    adapter correctly ingests an 8-bit AVR device — the refactors landed in
    earlier phases (SVD-optional, address_space threading, eeprom kind) hold
    together on a real AVR fixture.
    """
    selected = select_device_files(
        _avr_da_context(), "avr128da32", vendor="microchip", family="avr-da"
    )
    memories = parse_memory_patches(selected.atdf_path)
    by_space: dict[str | None, list[str]] = {}
    for memory in memories:
        by_space.setdefault(memory.address_space, []).append(memory.name.lower())
    assert "prog" in by_space, f"prog space missing: {by_space}"
    assert "data" in by_space, f"data space missing: {by_space}"
    assert "eeprom" in by_space, f"eeprom space missing: {by_space}"
    eeprom = [m for m in memories if m.address_space == "eeprom"]
    assert len(eeprom) == 1
    assert eeprom[0].kind == "eeprom"
    # Harvard ambiguity: flash app section and internal SRAM both start at low
    # addresses within their own spaces, which only works because address_space
    # disambiguates them.
    app_starts = [m.base_address for m in memories if m.name == "app_section"]
    sram_starts = [m.base_address for m in memories if m.name == "internal_sram"]
    assert app_starts and sram_starts
    assert app_starts[0] == 0, app_starts
    assert sram_starts[0] == 0x4000, sram_starts


def test_avr128da32_atdf_resolves_expected_peripheral_aliases() -> None:
    """Phase 2.3: parsing the AVR128DA32 ATDF yields peripheral names that
    the canonical_peripheral_class alias table (USART/TWI/SPI/TCA/PORT)
    resolves correctly — proves the AVR aliases landed in prep work are
    wired into real ATDF ingestion."""
    from alloy_codegen.connector_model import canonical_peripheral_class

    selected = select_device_files(
        _avr_da_context(), "avr128da32", vendor="microchip", family="avr-da"
    )
    peripherals = parse_peripheral_patches(selected.atdf_path)
    names = {p.name for p in peripherals}
    assert {"USART0", "USART1", "TWI0", "SPI0", "TCA0"} <= names, names

    # Module IDs come through as lowercase ip_names via parse_ip_version_table.
    # The canonical_peripheral_class table must reduce AVR module names to
    # the runtime-meaningful class.
    assert canonical_peripheral_class("usart") == "uart"
    assert canonical_peripheral_class("twi") == "i2c"
    assert canonical_peripheral_class("spi") == "spi"
    assert canonical_peripheral_class("tca") == "timer"
    assert canonical_peripheral_class("tcb") == "timer"
    assert canonical_peripheral_class("tcd") == "timer"
