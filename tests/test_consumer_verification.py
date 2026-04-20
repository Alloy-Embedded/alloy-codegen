from __future__ import annotations

from alloy_codegen.consumer_verification import (
    _linker_script_requires_distinct_data_load_address,
)


def test_linker_script_skips_lma_requirement_when_text_and_data_share_region(tmp_path) -> None:
    linker_script = tmp_path / "device.ld"
    linker_script.write_text(
        "\n".join(
            [
                'REGION_ALIAS("REGION_TEXT", OCRAM);',
                'REGION_ALIAS("REGION_DATA", OCRAM);',
            ]
        ),
        encoding="utf-8",
    )

    assert _linker_script_requires_distinct_data_load_address(linker_script) is False


def test_linker_script_requires_lma_when_text_and_data_regions_differ(tmp_path) -> None:
    linker_script = tmp_path / "device.ld"
    linker_script.write_text(
        "\n".join(
            [
                'REGION_ALIAS("REGION_TEXT", FLASH);',
                'REGION_ALIAS("REGION_DATA", SRAM);',
            ]
        ),
        encoding="utf-8",
    )

    assert _linker_script_requires_distinct_data_load_address(linker_script) is True
