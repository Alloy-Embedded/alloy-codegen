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
            "--source",
            f"cmsis-svd-data={fixture_source_root}",
            "--source",
            f"stm32-open-pin-data={fixture_pin_source_root}",
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
            "--source",
            f"cmsis-svd-data={fixture_source_root}",
            "--source",
            f"stm32-open-pin-data={fixture_pin_source_root}",
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


def test_cli_targets_json_output_lists_supported_families(capsys) -> None:
    exit_code = cli_module.main(["targets", "--json"])
    captured = capsys.readouterr()
    payload = json.loads(captured.out)

    assert exit_code == 0
    assert payload["default_scope"] == {"vendor": "st", "family": "stm32g0"}
    assert any(
        entry["vendor"] == "microchip"
        and entry["family"] == "same70"
        and "atsame70n21b" in entry["devices"]
        and "microchip-dfp-extract" in entry["source_bundles"]
        for entry in payload["targets"]
    )


def test_cli_targets_returns_non_zero_for_unknown_filter(capsys) -> None:
    exit_code = cli_module.main(["targets", "--vendor", "foo", "--json"])
    captured = capsys.readouterr()
    payload = json.loads(captured.out)

    assert exit_code == 1
    assert "Unsupported vendor/family filter" in payload["error"]


def test_cli_explain_json_output_traces_runtime_fact(
    capsys,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
) -> None:
    exit_code = cli_module.main(
        [
            "explain",
            "--device",
            "stm32g071rb",
            "--fact",
            "system-clock-profile:default_pll_64mhz",
            "--source",
            f"cmsis-svd-data={fixture_source_root}",
            "--source",
            f"stm32-open-pin-data={fixture_pin_source_root}",
            "--json",
        ]
    )
    captured = capsys.readouterr()
    payload = json.loads(captured.out)

    assert exit_code == 0
    assert payload["command"] == "explain"
    assert payload["scope"]["device"] == "stm32g071rb"
    assert payload["fact"] == "system-clock-profile:default_pll_64mhz"
    assert payload["exact_match"] is True
    assert any(
        match["id"] == "system-clock-profile:default-pll-64mhz"
        and match["kind"] == "system_clock_profile"
        for match in payload["matches"]
    )


def test_cli_diff_json_output_reports_capability_delta(
    capsys,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
) -> None:
    exit_code = cli_module.main(
        [
            "diff",
            "--from",
            "stm32g071rb",
            "--to",
            "stm32f401re",
            "--source",
            f"cmsis-svd-data={fixture_source_root}",
            "--source",
            f"stm32-open-pin-data={fixture_pin_source_root}",
            "--json",
        ]
    )
    captured = capsys.readouterr()
    payload = json.loads(captured.out)

    assert exit_code == 0
    assert payload["command"] == "diff"
    assert payload["from"]["device"] == "stm32g071rb"
    assert payload["to"]["device"] == "stm32f401re"
    assert payload["added"] or payload["removed"] or payload["modified"]
    for entry in payload["added"] + payload["removed"]:
        assert "provenance" in entry
        assert "source_ids" in entry["provenance"]
