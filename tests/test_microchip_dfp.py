from __future__ import annotations

from pathlib import Path
from zipfile import ZIP_DEFLATED, ZipFile

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
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
