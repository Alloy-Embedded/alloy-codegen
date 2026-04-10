from __future__ import annotations

from pathlib import Path

import pytest

from alloy_codegen.errors import ReleaseMetadataError
from alloy_codegen.release import build_release_metadata, write_github_output


def test_build_release_metadata_from_publish_report() -> None:
    publish_report = {
        "stage": "publish",
        "status": "completed",
        "payload": {
            "scope": {
                "vendor": "st",
                "family": "stm32g0",
                "device": None,
            },
            "target_repository": "alloy-devices",
            "target_artifact_revision": "abc123",
        },
    }

    metadata = build_release_metadata(
        publish_report=publish_report,
        source_revision="25d0e3ce30e69bcfa6b5ce367f2ead4793cd3cb8",
    )

    assert metadata.scope_path == "st/stm32g0"
    assert metadata.target_repository == "alloy-devices"
    assert metadata.target_artifact_revision == "abc123"
    assert metadata.commit_subject == (
        "chore(devices): publish st/stm32g0 from alloy-codegen 25d0e3ce30e6"
    )
    assert "Source revision: 25d0e3ce30e69bcfa6b5ce367f2ead4793cd3cb8" in metadata.commit_body


def test_write_github_output_writes_multiline_body(tmp_path: Path) -> None:
    publish_report = {
        "stage": "publish",
        "status": "completed",
        "payload": {
            "scope": {
                "vendor": "st",
                "family": "stm32g0",
                "device": "stm32g071rb",
            },
            "target_repository": "alloy-devices",
            "target_artifact_revision": "def456",
        },
    }
    metadata = build_release_metadata(
        publish_report=publish_report,
        source_revision="cee6830f4f979a9ab4d01f602f3d1a8ee02011ab",
    )

    output_path = tmp_path / "github-output.txt"
    write_github_output(metadata, output_path)

    output = output_path.read_text(encoding="utf-8")
    assert "scope_path=st/stm32g0/stm32g071rb" in output
    assert (
        "commit_subject=chore(devices): publish st/stm32g0/stm32g071rb "
        "from alloy-codegen cee6830f4f97"
    ) in output
    assert "commit_body<<ALLOY_CODEGEN_COMMIT_BODY" in output
    assert "Target artifact revision: def456" in output


def test_build_release_metadata_accepts_top_level_scope() -> None:
    publish_report = {
        "stage": "publish",
        "status": "completed",
        "scope": {
            "vendor": "st",
            "family": "stm32g0",
            "device": None,
        },
        "payload": {
            "target_repository": "alloy-devices",
            "target_artifact_revision": "feedbeef",
        },
    }

    metadata = build_release_metadata(
        publish_report=publish_report,
        source_revision="8f7159991fdb9cf285c65356614efad4f5859270",
    )

    assert metadata.scope_path == "st/stm32g0"
    assert metadata.target_artifact_revision == "feedbeef"


def test_build_release_metadata_rejects_invalid_report() -> None:
    with pytest.raises(ReleaseMetadataError):
        build_release_metadata(
            publish_report={"stage": "validate", "status": "completed", "payload": {}},
            source_revision="deadbeef",
        )
