"""Regression tests for the Espressif ESP32-C3 bootstrap target.

Covers Phase 3 of OpenSpec change `add-espressif-esp32-target`:
- Task 3.4: emitted runtime goldens for interrupts.hpp, clock_graph.hpp,
  peripheral_instances.hpp, and startup.cpp.
- Task 3.5: publish/contract regression proving runtime-only completeness
  for `esp32c3` — typed primary contract, RISC-V startup conventions,
  no ARM-specific artifacts leaked into the RISC-V output.
"""

from __future__ import annotations

from pathlib import Path

from alloy_codegen.artifact_contract import find_runtime_cpp_string_violations
from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit

ESP32C3_EMITTED_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "emitted" / "esp32c3"


def _esp32c3_artifacts(espressif_execution_context: ExecutionContext):
    scope = PipelineScope(vendor="espressif", family="esp32c3", device="esp32c3")
    result = run_emit(scope, espressif_execution_context)
    return {artifact.path: artifact for artifact in result.payload.artifacts}, result


def test_esp32c3_runtime_contract_contains_required_headers(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 3.5: runtime headers required by the artifact contract are emitted."""
    artifacts, _ = _esp32c3_artifacts(espressif_execution_context)
    required = (
        "espressif/esp32c3/generated/runtime/devices/esp32c3/interrupts.hpp",
        "espressif/esp32c3/generated/runtime/devices/esp32c3/clock_graph.hpp",
        "espressif/esp32c3/generated/runtime/devices/esp32c3/peripheral_instances.hpp",
    )
    for path in required:
        assert path in artifacts, f"missing ESP32-C3 runtime header: {path}"


def test_esp32c3_interrupts_header_typed_contract(
    espressif_execution_context: ExecutionContext,
) -> None:
    """interrupts.hpp exposes typed InterruptId / descriptor tables, no CSV."""
    artifacts, _ = _esp32c3_artifacts(espressif_execution_context)
    content = artifacts[
        "espressif/esp32c3/generated/runtime/devices/esp32c3/interrupts.hpp"
    ].content
    assert "enum class InterruptId" in content
    assert "kInterruptDescriptors" in content


def test_esp32c3_clock_graph_header_typed_contract(
    espressif_execution_context: ExecutionContext,
) -> None:
    """clock_graph.hpp exposes typed ClockNodeId / dependency tables."""
    artifacts, _ = _esp32c3_artifacts(espressif_execution_context)
    content = artifacts[
        "espressif/esp32c3/generated/runtime/devices/esp32c3/clock_graph.hpp"
    ].content
    assert "enum class ClockNodeId" in content
    assert "kClockDependencies" in content


def test_esp32c3_peripheral_instances_header_typed_contract(
    espressif_execution_context: ExecutionContext,
) -> None:
    """peripheral_instances.hpp exposes typed PeripheralId / instance traits."""
    artifacts, _ = _esp32c3_artifacts(espressif_execution_context)
    content = artifacts[
        "espressif/esp32c3/generated/runtime/devices/esp32c3/peripheral_instances.hpp"
    ].content
    assert "enum class PeripheralId" in content
    assert "PeripheralInstanceTraits" in content


def test_esp32c3_startup_uses_riscv_conventions(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 3.5 / canonical-device-ir spec:

    Startup file uses RISC-V reset vector conventions (mtvec, BSS clear, main()),
    NOT the ARM CMSIS __stack_top-at-slot-0 vector table.
    """
    artifacts, _ = _esp32c3_artifacts(espressif_execution_context)
    startup = artifacts["espressif/esp32c3/generated/devices/esp32c3/startup.cpp"].content

    # Reset_Handler exists and sets up the stack pointer explicitly.
    assert "Reset_Handler" in startup
    assert "la sp, __stack_top" in startup

    # The vector table places Reset_Handler at slot 0 (RISC-V), NOT a raw
    # stack pointer cast like the ARM Cortex-M emitter would produce.
    assert "reinterpret_cast<void (*)()>(&__stack_top)" not in startup

    # Standard startup sequence is still present.
    assert "_sidata" in startup
    assert "_sbss" in startup


def test_esp32c3_systick_is_not_required_for_riscv(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Artifact-contract spec: systick.hpp is Cortex-M scoped; its omission on
    ESP32-C3 is valid.  The emitter may still produce a systick.hpp stub with
    kPresent=false, but the contract validator does NOT require the path for
    non-Cortex-M cores."""
    from alloy_codegen.runtime_systick import runtime_systick_required_paths
    from alloy_codegen.stages.normalize import run as run_normalize

    normalize_result = run_normalize(
        PipelineScope(vendor="espressif", family="esp32c3", device="esp32c3"),
        espressif_execution_context,
    )
    required = runtime_systick_required_paths(
        family_dir="espressif/esp32c3",
        devices=tuple(normalize_result.payload.devices),
    )
    assert required == (), "systick.hpp must not be required for RISC-V devices"


def test_esp32c3_runtime_has_no_string_glue_in_primary_contract(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 3.5: the ESP32-C3 runtime output passes the typed-contract gate
    (no string literals in primary runtime fields)."""
    _, result = _esp32c3_artifacts(espressif_execution_context)
    assert find_runtime_cpp_string_violations(result.payload.artifacts) == ()


def test_esp32c3_emitted_runtime_goldens_match(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 3.4: emitted runtime headers match their golden fixtures."""
    artifacts, _ = _esp32c3_artifacts(espressif_execution_context)
    pairs = (
        (
            "espressif/esp32c3/generated/runtime/devices/esp32c3/interrupts.hpp",
            ESP32C3_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "esp32c3"
            / "interrupts.hpp",
        ),
        (
            "espressif/esp32c3/generated/runtime/devices/esp32c3/clock_graph.hpp",
            ESP32C3_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "esp32c3"
            / "clock_graph.hpp",
        ),
        (
            "espressif/esp32c3/generated/runtime/devices/esp32c3/peripheral_instances.hpp",
            ESP32C3_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "esp32c3"
            / "peripheral_instances.hpp",
        ),
        (
            "espressif/esp32c3/generated/devices/esp32c3/startup.cpp",
            ESP32C3_EMITTED_FIXTURE_DIR / "generated" / "devices" / "esp32c3" / "startup.cpp",
        ),
    )
    for emitted_path, fixture_path in pairs:
        assert emitted_path in artifacts, f"missing emitted artifact: {emitted_path}"
        expected = fixture_path.read_text(encoding="utf-8")
        assert artifacts[emitted_path].content == expected, (
            f"emitted {emitted_path} does not match golden fixture {fixture_path}"
        )
