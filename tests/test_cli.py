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


def test_cli_diff_json_output_reports_cross_vendor_capability_delta(
    capsys,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
    fixture_microchip_extract_root: Path,
) -> None:
    exit_code = cli_module.main(
        [
            "diff",
            "--from",
            "stm32g071rb",
            "--to",
            "atsame70q21b",
            "--source",
            f"cmsis-svd-data={fixture_source_root}",
            "--source",
            f"stm32-open-pin-data={fixture_pin_source_root}",
            "--source",
            f"microchip-dfp-extract={fixture_microchip_extract_root}",
            "--json",
        ]
    )
    captured = capsys.readouterr()
    payload = json.loads(captured.out)

    assert exit_code == 0
    assert payload["command"] == "diff"
    assert payload["from"]["device"] == "stm32g071rb"
    assert payload["to"]["device"] == "atsame70q21b"
    assert any(entry["peripheral_class"] == "can" for entry in payload["added"])
    assert any(
        entry["peripheral_class"] == "uart"
        for entry in payload["added"] + payload["removed"] + payload["modified"]
    )
    for entry in payload["added"] + payload["removed"]:
        assert entry["provenance"]["source_ids"] or entry["provenance"]["patch_ids"]


def test_cli_config_schema_json_output(capsys) -> None:
    exit_code = cli_module.main(["config-schema", "--json"])
    captured = capsys.readouterr()
    payload = json.loads(captured.out)

    assert exit_code == 0
    assert payload["title"] == "RuntimeConfigRequest"
    assert payload["properties"]["schema_version"]["const"] == "runtime-config-request-v1"
    assert payload["required"] == ["schema_version", "device", "requests", "outputs"]


def test_cli_config_template_json_output(
    capsys,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
) -> None:
    exit_code = cli_module.main(
        [
            "config-template",
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
    assert payload["command"] == "config-template"
    assert payload["scope"]["device"] == "stm32g071rb"
    assert payload["schema"] == "runtime-config-request-v1"
    assert payload["template"]["schema_version"] == "runtime-config-request-v1"
    assert payload["template"]["device"] == "stm32g071rb"
    assert payload["template"]["requests"] == []
    assert payload["available"]["clock_profiles"]
    assert "gpio" in payload["available"]["peripheral_classes"]


def test_cli_config_diagnose_json_output_for_valid_request(
    capsys,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
    tmp_path: Path,
) -> None:
    request_path = tmp_path / "uart-config.json"
    request_path.write_text(
        json.dumps(
            {
                "schema_version": "runtime-config-request-v1",
                "device": "stm32g071rb",
                "clock_profile": "default-pll-64mhz",
                "requests": [
                    {
                        "kind": "peripheral",
                        "peripheral_class": "uart",
                        "peripheral": "USART1",
                        "pins": {
                            "tx": "PB6",
                            "rx": "PB7",
                        },
                        "dma": {
                            "rx": True,
                            "tx": True,
                        },
                    }
                ],
                "outputs": {
                    "recipes": [],
                    "examples": [],
                },
            }
        ),
        encoding="utf-8",
    )

    exit_code = cli_module.main(
        [
            "config-diagnose",
            "--file",
            str(request_path),
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
    assert payload["command"] == "config-diagnose"
    assert payload["scope"]["device"] == "stm32g071rb"
    assert payload["is_valid"] is True
    assert payload["clock_profile"]["is_valid"] is True
    assert payload["requests"][0]["resolved_peripheral"] == "USART1"
    assert payload["requests"][0]["pins"]["tx"]["is_valid"] is True
    assert payload["requests"][0]["dma"]["rx"]["is_valid"] is True
    assert payload["requests"][0]["dma"]["tx"]["is_valid"] is True


def test_cli_config_diagnose_json_output_reports_invalid_request(
    capsys,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
    tmp_path: Path,
) -> None:
    request_path = tmp_path / "uart-config-invalid.json"
    request_path.write_text(
        json.dumps(
            {
                "schema_version": "runtime-config-request-v1",
                "device": "stm32g071rb",
                "clock_profile": "bad-profile",
                "requests": [
                    {
                        "kind": "peripheral",
                        "peripheral_class": "uart",
                        "peripheral": "USART1",
                        "pins": {
                            "tx": "PA2",
                            "rx": "PB7",
                        },
                        "dma": {
                            "rx": True,
                            "tx": True,
                        },
                    }
                ],
                "outputs": {
                    "recipes": [],
                    "examples": [],
                },
            }
        ),
        encoding="utf-8",
    )

    exit_code = cli_module.main(
        [
            "config-diagnose",
            "--file",
            str(request_path),
            "--source",
            f"cmsis-svd-data={fixture_source_root}",
            "--source",
            f"stm32-open-pin-data={fixture_pin_source_root}",
            "--json",
        ]
    )
    captured = capsys.readouterr()
    payload = json.loads(captured.out)

    assert exit_code == 1
    assert payload["command"] == "config-diagnose"
    assert payload["is_valid"] is False
    assert payload["clock_profile"]["is_valid"] is False
    assert "default-pll-64mhz" in payload["clock_profile"]["available"]
    assert payload["requests"][0]["pins"]["tx"]["is_valid"] is False
    assert any(
        diagnostic["code"] == "invalid-pin" and "PB6" in diagnostic["alternatives"]
        for diagnostic in payload["requests"][0]["diagnostics"]
    )


def test_cli_config_recipe_json_output_for_valid_request(
    capsys,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
    tmp_path: Path,
) -> None:
    request_path = tmp_path / "uart-config-recipe.json"
    request_path.write_text(
        json.dumps(
            {
                "schema_version": "runtime-config-request-v1",
                "device": "stm32g071rb",
                "clock_profile": "default-pll-64mhz",
                "requests": [
                    {
                        "kind": "peripheral",
                        "peripheral_class": "uart",
                        "peripheral": "USART1",
                        "pins": {
                            "tx": "PB6",
                            "rx": "PB7",
                        },
                        "dma": {
                            "rx": True,
                            "tx": True,
                        },
                    }
                ],
                "outputs": {
                    "recipes": ["board-uart"],
                    "examples": [],
                },
            }
        ),
        encoding="utf-8",
    )

    exit_code = cli_module.main(
        [
            "config-recipe",
            "--file",
            str(request_path),
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
    assert payload["command"] == "config-recipe"
    assert payload["scope"]["device"] == "stm32g071rb"
    assert payload["clock_profile"] == "default-pll-64mhz"
    assert payload["recipe"]["schema_version"] == "runtime-config-recipe-v1"
    assert payload["recipe"]["requests"][0]["peripheral_class"] == "uart"
    assert payload["recipe"]["requests"][0]["peripheral"] == "USART1"
    assert payload["recipe"]["requests"][0]["pins"] == {"rx": "PB7", "tx": "PB6"}
    assert payload["recipe"]["requests"][0]["dma"] == {"rx": True, "tx": True}


def test_cli_config_example_json_output_for_valid_request(
    capsys,
    fixture_source_root: Path,
    fixture_pin_source_root: Path,
    tmp_path: Path,
) -> None:
    request_path = tmp_path / "uart-config-example.json"
    request_path.write_text(
        json.dumps(
            {
                "schema_version": "runtime-config-request-v1",
                "device": "stm32g071rb",
                "clock_profile": "default-pll-64mhz",
                "requests": [
                    {
                        "kind": "peripheral",
                        "peripheral_class": "uart",
                        "peripheral": "USART1",
                        "pins": {
                            "tx": "PB6",
                            "rx": "PB7",
                        },
                        "dma": {
                            "rx": True,
                            "tx": True,
                        },
                    }
                ],
                "outputs": {
                    "recipes": [],
                    "examples": ["basic"],
                },
            }
        ),
        encoding="utf-8",
    )

    exit_code = cli_module.main(
        [
            "config-example",
            "--file",
            str(request_path),
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
    assert payload["command"] == "config-example"
    assert payload["scope"]["device"] == "stm32g071rb"
    assert payload["examples"][0]["example_id"] == "uart-usart1-basic"
    assert payload["examples"][0]["peripheral"] == "USART1"
    assert payload["examples"][0]["pins"] == {"rx": "PB7", "tx": "PB6"}
    assert payload["examples"][0]["dma"] == {"rx": True, "tx": True}
    assert any(
        header.endswith("/driver_semantics/uart.hpp")
        for header in payload["examples"][0]["runtime_headers"]
    )
    assert any(
        "Clock profile: default-pll-64mhz" in line for line in payload["examples"][0]["snippet"]
    )
