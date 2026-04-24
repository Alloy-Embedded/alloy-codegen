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
from alloy_codegen.connector_model import _pinmux_backend_schema_id
from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.esp_idf import parse_gpio_sig_map
from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.normalize import run as run_normalize
from alloy_codegen.stages.publish import run as run_publish

ESP32C3_EMITTED_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "emitted" / "esp32c3"
ESP32C3_GPIO_SIG_MAP = (
    Path(__file__).parent / "fixtures" / "esp-idf-gpio-sig-map" / "esp32c3" / "gpio_sig_map.h"
)

# Canonical map from (peripheral, signal) pairs in the ESP32-C3 family patch
# to their upstream ``gpio_sig_map.h`` entry names.  A mismatch between the
# family-patch ``af_number`` and the parsed upstream value indicates the
# patch drifted from esp-idf — Phase 2.2 provenance gate.
_ESP32C3_SIGNAL_TO_IOMATRIX_NAME: dict[tuple[str, str], str] = {
    ("UART0", "RX"): "U0RXD_IN",
    ("UART0", "TX"): "U0TXD_OUT",
    ("UART1", "RX"): "U1RXD_IN",
    ("UART1", "TX"): "U1TXD_OUT",
    ("I2C0", "SDA"): "I2CEXT0_SDA_IN",
    ("I2C0", "SCL"): "I2CEXT0_SCL_IN",
    ("SPI2", "MISO"): "FSPIQ_IN",
    ("SPI2", "MOSI"): "FSPID_OUT",
    ("SPI2", "SCK"): "FSPICLK_OUT",
    ("SPI2", "CS"): "FSPICS0_OUT",
}


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


def test_publish_esp32c3_consumer_smoke_passes(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 3.3: the Alloy runtime-lite smoke consumer compiles the ESP32-C3
    runtime headers and RISC-V startup without ARM-specific glue.

    This test actually runs the host ``c++`` compiler against the staged
    publication root and asserts that the smoke executable links.  The RISC-V
    ``__attribute__((interrupt))`` annotations on peripheral IRQ handlers are
    guarded by ``ALLOY_CODEGEN_HOST_SMOKE`` so they do not trip the host
    compiler's ``-Werror=unknown-attributes`` gate.
    """
    result = run_publish(
        PipelineScope(vendor="espressif", family="esp32c3", device="esp32c3"),
        espressif_execution_context,
    )

    assert result.payload.consumer_verification is not None, (
        "Publish should have invoked the consumer smoke verification for ESP32-C3"
    )
    assert result.payload.consumer_verification.succeeded is True, (
        "Alloy consumer smoke build failed for espressif/esp32c3/esp32c3:\n"
        + result.payload.consumer_verification.stderr
    )


# ---------------------------------------------------------------------------
# Phase 2.2 \u2014 IO Matrix parser + provenance tests
# ---------------------------------------------------------------------------


def test_parse_gpio_sig_map_extracts_expected_indices() -> None:
    """Phase 2.2: parse_gpio_sig_map() extracts every ``#define <NAME>_IDX``
    macro and returns it keyed by the canonical IO Matrix signal name."""
    mapping = parse_gpio_sig_map(ESP32C3_GPIO_SIG_MAP)
    # Core UART0 console signals (Espressif dev-board default).
    assert mapping["U0RXD_IN"] == 6
    assert mapping["U0TXD_OUT"] == 6
    # Secondary UART1.
    assert mapping["U1RXD_IN"] == 9
    # I2C0 SDA / SCL carry direction-specific indices.
    assert mapping["I2CEXT0_SDA_IN"] == 15
    assert mapping["I2CEXT0_SCL_OUT"] == 14
    # SPI2 (FSPI) — note MISO/CLK share the same numeric index in different
    # directions, MOSI is 64, chip-select is 68.
    assert mapping["FSPIQ_IN"] == 63
    assert mapping["FSPICLK_OUT"] == 63
    assert mapping["FSPID_OUT"] == 64
    assert mapping["FSPICS0_OUT"] == 68


def test_parse_gpio_sig_map_skips_unrelated_lines() -> None:
    """Phase 2.2: lines that do not match ``#define <NAME>_IDX <num>`` are
    silently skipped — copyright headers, comments, and unrelated macros must
    not leak into the returned mapping."""
    mapping = parse_gpio_sig_map(ESP32C3_GPIO_SIG_MAP)
    assert all(key.isupper() and "_IDX" not in key for key in mapping)
    assert all(isinstance(value, int) and value >= 0 for value in mapping.values())


def test_esp32c3_family_af_numbers_match_gpio_sig_map_upstream(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 2.2: every ``af_number`` in the ESP32-C3 family patch matches
    the canonical index published by esp-idf ``gpio_sig_map.h``.  This is the
    supplementary-source provenance gate — drift between the hand-authored
    patch and upstream is a validation failure, not silent breakage."""
    mapping = parse_gpio_sig_map(ESP32C3_GPIO_SIG_MAP)
    device = run_normalize(
        PipelineScope(vendor="espressif", family="esp32c3", device="esp32c3"),
        espressif_execution_context,
    ).payload.devices[0]

    mismatches: list[str] = []
    for pin in device.pins:
        for signal in pin.signals:
            if signal.peripheral is None:
                continue
            key = (signal.peripheral, signal.signal)
            if key not in _ESP32C3_SIGNAL_TO_IOMATRIX_NAME:
                continue
            iomatrix_name = _ESP32C3_SIGNAL_TO_IOMATRIX_NAME[key]
            expected = mapping.get(iomatrix_name)
            if expected is None:
                mismatches.append(
                    f"{pin.name} {signal.peripheral}.{signal.signal}: "
                    f"family cites {iomatrix_name} but upstream does not define it"
                )
                continue
            if signal.af_number != expected:
                mismatches.append(
                    f"{pin.name} {signal.peripheral}.{signal.signal}: "
                    f"family af_number={signal.af_number} upstream {iomatrix_name}={expected}"
                )
    assert not mismatches, (
        "ESP32-C3 family patch drifted from gpio_sig_map.h:\n  " + "\n  ".join(mismatches)
    )


# ---------------------------------------------------------------------------
# Phase 2.4 / 2.5 \u2014 IO Matrix backend_schema_id emission tests
# ---------------------------------------------------------------------------


def test_esp32c3_pinmux_route_operations_carry_iomatrix_schema(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 2.4: every ``write-selector`` route operation generated for an
    ESP32-C3 pin signal carries ``alloy.pinmux.espressif-iomatrix-v1`` as its
    ``schema_id``, so Alloy consumers can tell IO Matrix routing apart from
    ARM alternate functions and RP2040 FUNCSEL at the type level."""
    device = run_normalize(
        PipelineScope(vendor="espressif", family="esp32c3", device="esp32c3"),
        espressif_execution_context,
    ).payload.devices[0]

    expected_schema = _pinmux_backend_schema_id("espressif")
    assert expected_schema == "alloy.pinmux.espressif-iomatrix-v1"

    pinmux_operations = [
        operation
        for operation in device.route_operations
        if operation.kind == "write-selector" and operation.target_ref_kind == "pin"
    ]
    assert pinmux_operations, "Expected at least one pinmux route operation for ESP32-C3"
    for operation in pinmux_operations:
        assert operation.schema_id == expected_schema, (
            f"{operation.operation_id}: schema_id={operation.schema_id!r} "
            f"expected {expected_schema!r}"
        )


def test_esp32c3_runtime_routes_header_encodes_iomatrix_schema(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 2.5: the emitted ``routes.hpp`` (which is where route operations
    ship in the typed runtime contract) encodes the IO Matrix schema id in the
    BackendSchemaId enum, so the executable runtime output reflects the same
    provenance the canonical IR carries."""
    result = run_emit(
        PipelineScope(vendor="espressif", family="esp32c3", device="esp32c3"),
        espressif_execution_context,
    )
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}
    routes_header = artifacts[
        "espressif/esp32c3/generated/runtime/devices/esp32c3/routes.hpp"
    ].content
    types_header = artifacts["espressif/esp32c3/generated/runtime/types.hpp"].content

    # The emitter sanitizes the schema id into a C++ enum identifier.
    # ``alloy.pinmux.espressif-iomatrix-v1`` becomes
    # ``schema_alloy_pinmux_espressif_iomatrix_v1`` in the BackendSchemaId enum.
    assert "schema_alloy_pinmux_espressif_iomatrix_v1" in types_header, (
        "Expected IO Matrix backend schema id to be declared in the BackendSchemaId "
        "enum in the emitted runtime types.hpp"
    )
    assert "schema_alloy_pinmux_espressif_iomatrix_v1" in routes_header, (
        "Expected IO Matrix backend schema id to appear on every pinmux route "
        "operation in the emitted routes.hpp"
    )
