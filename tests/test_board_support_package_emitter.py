"""Tests for the per-board BSP header + boards manifest emitter
added by ``add-board-support-package-emitter``.

The emitter SHALL render
``<vendor>/<family>/generated/runtime/boards/<board_id>/board.hpp``
exposing named pins as typed `PinId` constexpr constants grouped by
category, plus the default clock profile.  A top-level
``metadata/boards.json`` lists every admitted board across the family
scope so tooling (CLI, docs, IDE) can enumerate boards without
parsing every per-device sidecar.
"""

from __future__ import annotations

import json
from pathlib import Path

import pytest

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.normalize import run as run_normalize


def _emit(context: ExecutionContext, device: str):
    return run_emit(PipelineScope(device=device), context).payload.artifacts


def test_nucleo_g071rb_bsp_header_exposes_named_pins(
    execution_context: ExecutionContext,
) -> None:
    artifacts = _emit(execution_context, "stm32g071rb")
    board_artifact = next(
        a for a in artifacts if a.path.endswith("/boards/nucleo_g071rb/board.hpp")
    )
    content = board_artifact.content
    # Leds::kGreen → PA5 (admitted active-high).
    assert "struct Leds {" in content
    assert "static constexpr PinId kGreen = PinId::PA5;" in content
    assert "static constexpr bool kGreenActiveHigh = true;" in content
    # Buttons::kUser → PB7 (fixture-coverage gap; real silicon uses PC13).
    assert "struct Buttons {" in content
    assert "static constexpr PinId kUser = PinId::PB7;" in content
    assert "static constexpr bool kUserActiveHigh = false;" in content
    # DebugUart names the USART2 peripheral + TX/RX pins.
    assert "struct DebugUart {" in content
    assert "static constexpr PeripheralId kPeripheral = PeripheralId::USART2;" in content
    assert "static constexpr PinId kTx = PinId::PA2;" in content
    assert "static constexpr PinId kRx = PinId::PA3;" in content
    # static_assert per named pin (consumer-time typo guard).
    assert "static_assert(::st::stm32g0::generated::runtime::devices::stm32g071rb" in content
    assert "GpioSemanticTraits<PinId::PA5>::kPresent" in content


def test_boards_manifest_lists_nucleo_g071rb(
    execution_context: ExecutionContext,
) -> None:
    artifacts = _emit(execution_context, "stm32g071rb")
    manifest_artifact = next(
        a for a in artifacts if a.path.endswith("/metadata/boards.json")
    )
    payload = json.loads(manifest_artifact.content)
    assert payload["manifest_kind"] == "boards-manifest-v1"
    assert any(
        entry["board_id"] == "nucleo-g071rb"
        and entry["device"] == "stm32g071rb"
        and entry["vendor"] == "st"
        and entry["family"] == "stm32g0"
        for entry in payload["boards"]
    )


def test_board_with_unknown_pin_fails_normalize(
    execution_context: ExecutionContext,
    tmp_path: Path,
) -> None:
    """Negative test: a board file referencing a non-existent pin
    raises ``StageExecutionError`` during the normalize stage so a
    BSP header that would `static_assert` at the consumer's
    ``#include`` is rejected at codegen time."""
    # Build a temporary patch tree mirroring the fixture, with one
    # extra board.json that names a non-existent pin.
    fixture_patches = Path(__file__).resolve().parents[1] / "patches"
    fake_root = tmp_path / "patches"
    fake_root.mkdir()
    # Copy the st subtree so we can mutate boards/ without touching shared fixtures.
    import shutil
    shutil.copytree(fixture_patches / "st", fake_root / "st", symlinks=False)
    bad_board = fake_root / "st" / "stm32g0" / "boards" / "broken-board.json"
    bad_board.write_text(
        json.dumps(
            {
                "board_id": "broken-board",
                "device": "stm32g071rb",
                "package": "lqfp64",
                "summary": "Negative-test board referencing a non-existent pin.",
                "named_pins": [
                    {"name": "LED_BAD", "pin": "PZ99", "polarity": "active_high"},
                ],
            }
        )
    )
    # Symlink the rest of the patches root to keep the dispatch happy.
    for entry in fixture_patches.iterdir():
        if entry.name == "st":
            continue
        (fake_root / entry.name).symlink_to(entry, target_is_directory=entry.is_dir())
    ctx = execution_context.with_overrides(
        patch_root=str(fake_root),
        artifact_root=str(tmp_path / "artifacts"),
        publication_root=str(tmp_path / "publication"),
    )
    with pytest.raises(StageExecutionError) as excinfo:
        run_normalize(PipelineScope(device="stm32g071rb"), ctx)
    msg = str(excinfo.value)
    assert "broken-board" in msg
    assert "LED_BAD" in msg
    assert "PZ99" in msg
