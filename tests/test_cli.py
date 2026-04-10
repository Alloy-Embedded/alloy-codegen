from __future__ import annotations

import json
from pathlib import Path

from alloy_codegen import cli as cli_module
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.common import StageResult


def test_cli_fetch_json_output(
    capsys,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
) -> None:
    exit_code = cli_module.main(
        [
            "fetch",
            "--device",
            "stm32g071rb",
            "--source-root",
            str(fixture_source_root),
            "--pin-source-root",
            str(fixture_pin_source_root),
            "--json",
        ]
    )
    captured = capsys.readouterr()
    payload = json.loads(captured.out)

    assert exit_code == 0
    assert payload["stage"] == "fetch"
    assert payload["scope"]["family"] == "stm32g0"
    assert payload["scope"]["device"] == "stm32g071rb"
    assert payload["payload"]["source_manifest"]["sources"][0]["upstream_path"].endswith(
        "STM32G071.svd"
    )


def test_cli_validate_json_output_includes_report_summary(
    capsys,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
) -> None:
    exit_code = cli_module.main(
        [
            "validate",
            "--device",
            "stm32g071rb",
            "--source-root",
            str(fixture_source_root),
            "--pin-source-root",
            str(fixture_pin_source_root),
            "--json",
        ]
    )
    captured = capsys.readouterr()
    payload = json.loads(captured.out)

    assert exit_code == 0
    assert payload["stage"] == "validate"
    assert payload["status"] == "completed"
    assert payload["payload"]["report"]["report_id"] == "bootstrap-validation-v1"
    assert payload["payload"]["report"]["is_passing"] is True


def test_cli_returns_non_zero_for_failed_stage(monkeypatch, capsys) -> None:
    def fake_validate(_scope: PipelineScope, _context: object) -> StageResult:
        return StageResult(
            stage="validate",
            scope=PipelineScope(vendor="st", family="stm32g0", device="stm32g071rb"),
            status="failed",
            payload={"reason": "synthetic failure"},
            warnings=("synthetic warning",),
        )

    monkeypatch.setitem(cli_module.STAGE_RUNNERS, "validate", fake_validate)

    exit_code = cli_module.main(["validate", "--device", "stm32g071rb", "--json"])
    captured = capsys.readouterr()
    payload = json.loads(captured.out)

    assert exit_code == 1
    assert payload["stage"] == "validate"
    assert payload["status"] == "failed"
    assert payload["warnings"] == ["synthetic warning"]
