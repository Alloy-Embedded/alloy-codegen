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
    assert not mismatches, "ESP32-C3 family patch drifted from gpio_sig_map.h:\n  " + "\n  ".join(
        mismatches
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


def test_esp32c3_apply_route_emits_iomux_and_gpio_matrix_writes(
    espressif_execution_context: ExecutionContext,
) -> None:
    """§3.3 — apply_route<> specializations write IO_MUX MCU_SEL and GPIO matrix."""
    result = run_emit(
        PipelineScope(vendor="espressif", family="esp32c3", device="esp32c3"),
        espressif_execution_context,
    )
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}
    routes = artifacts["espressif/esp32c3/generated/runtime/devices/esp32c3/routes.hpp"].content
    assert "apply_route<PinId::GPIO20, PeripheralId::UART0" in routes
    assert "& ~(std::uint32_t{0x7} << 12)" in routes  # MCU_SEL mask
    assert "std::uint32_t{0x1} << 12)" in routes  # MCU_SEL = 1 (GPIO matrix)
    assert "std::uint32_t{0x6u}" in routes  # UART0 RX signal selector


# ---------------------------------------------------------------------------
# Phase 4 — ESP32-S3 (Xtensa LX7) follow-on
# ---------------------------------------------------------------------------


ESP32S3_EMITTED_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "emitted" / "esp32s3"
ESP32S3_CANONICAL_FIXTURE = (
    Path(__file__).parent / "fixtures" / "esp32s3" / "esp32s3.canonical.json"
)


def _esp32s3_artifacts(espressif_execution_context: ExecutionContext):
    scope = PipelineScope(vendor="espressif", family="esp32s3", device="esp32s3")
    result = run_emit(scope, espressif_execution_context)
    return {artifact.path: artifact for artifact in result.payload.artifacts}, result


def test_esp32s3_canonical_fixture_matches(
    espressif_execution_context: ExecutionContext,
) -> None:
    """ESP32-S3 canonical IR matches the locked-in golden fixture."""
    import json as _json

    scope = PipelineScope(vendor="espressif", family="esp32s3", device="esp32s3")
    device = run_normalize(scope, espressif_execution_context).payload.devices[0]
    expected = _json.loads(ESP32S3_CANONICAL_FIXTURE.read_text())
    assert device.to_dict() == expected


def test_esp32s3_identity_is_single_core_xtensa_lx7(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 4.4: the first admitted ESP32-S3 model is single-core-perspective
    (core 0 control plane).  Identity metadata must reflect that — core is
    ``xtensa-lx7`` and no ARM/RISC-V markers leak into the IR."""
    scope = PipelineScope(vendor="espressif", family="esp32s3", device="esp32s3")
    device = run_normalize(scope, espressif_execution_context).payload.devices[0]
    assert device.identity.vendor == "espressif"
    assert device.identity.family == "esp32s3"
    assert device.identity.core == "xtensa-lx7"
    assert device.schema_version == "1.2.0"


def test_esp32s3_admits_both_interrupt_cores(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 1.3 of add-espressif-esp32-classic-target: the ESP32-S3 bootstrap
    admits BOTH interrupt-matrix peripherals (CORE0 + CORE1) so the dual-core
    runtime startup can partition vectors by ``core_affinity``.  The earlier
    single-core-perspective posture (which filtered ``INTERRUPT_CORE1``) is
    superseded by the dual-core control-plane contract."""
    scope = PipelineScope(vendor="espressif", family="esp32s3", device="esp32s3")
    device = run_normalize(scope, espressif_execution_context).payload.devices[0]
    admitted = {peripheral.name for peripheral in device.peripherals}
    # Both cores' interrupt matrices are admitted now.
    assert "INTERRUPT_CORE0" in admitted
    assert "INTERRUPT_CORE1" in admitted
    # At least one CPU1-affine vector must be present.
    cpu1_slots = [slot for slot in device.vector_slots if slot.core_affinity == "cpu1"]
    assert cpu1_slots, "Expected CPU1-affine vectors after dual-core admission"
    # And every cpu1 vector must reference a CORE1 peripheral.
    for slot in cpu1_slots:
        assert slot.interrupt is not None
        matching = [
            interrupt for interrupt in device.interrupts if interrupt.name == slot.interrupt
        ]
        assert matching, f"vector {slot.symbol_name} has no matching interrupt entry"
        peripheral = matching[0].peripheral
        assert peripheral is not None and (
            peripheral.upper() == "INTERRUPT_CORE1" or peripheral.upper().startswith("DPORT_APP_")
        ), f"cpu1 slot {slot.symbol_name} has unexpected peripheral {peripheral!r}"


def test_esp32s3_emits_dual_core_startup(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 1.9 of add-espressif-esp32-classic-target: the regenerated ESP32-S3
    startup carries the dual-core control plane — both vector tables, both
    Reset_Handlers, the bring-up primitive, and the LX7-specific CORE_1
    control register pokes."""
    artifacts, _ = _esp32s3_artifacts(espressif_execution_context)
    startup = artifacts["espressif/esp32s3/generated/devices/esp32s3/startup.cpp"].content
    # Per-core vector tables are present.
    assert "_vectors_cpu0[]" in startup
    assert "_vectors_cpu1[]" in startup
    assert ".xtensa_vectors_cpu0" in startup
    assert ".xtensa_vectors_cpu1" in startup
    # Both reset entry points are exposed.
    assert "void Reset_Handler()" in startup
    assert "void Reset_Handler_CPU1()" in startup
    # Application-callable APP_CPU release primitive.
    assert "void bring_up_app_cpu()" in startup
    # ESP32-S3 specific control registers (LX7 variant).
    assert "SYSTEM.CORE_1_CONTROL_0" in startup
    assert "SYSTEM.CORE_1_CONTROL_1" in startup
    assert "RUNSTALL" in startup
    # Affinity / IPC primitives are NOT exposed as callable symbols by the
    # bootstrap output (they appear only in the documentation comment).
    assert "void ipi_send" not in startup
    assert "void spinlock_" not in startup
    assert "void mutex_" not in startup
    assert "void queue_" not in startup


def test_esp32s3_runtime_contract_contains_required_headers(
    espressif_execution_context: ExecutionContext,
) -> None:
    artifacts, _ = _esp32s3_artifacts(espressif_execution_context)
    required = (
        "espressif/esp32s3/generated/runtime/devices/esp32s3/interrupts.hpp",
        "espressif/esp32s3/generated/runtime/devices/esp32s3/clock_graph.hpp",
        "espressif/esp32s3/generated/runtime/devices/esp32s3/peripheral_instances.hpp",
    )
    for path in required:
        assert path in artifacts, f"missing ESP32-S3 runtime header: {path}"


def test_esp32s3_startup_uses_xtensa_conventions(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 4.5: emitted startup.cpp uses Xtensa conventions — no ARM
    `_vectors[]` array at address 0, no RISC-V `mtvec`, no AVR
    `.vectors` / `__vector_<N>`.  The ROM bootloader owns VECBASE; our
    file only runs after control transfer."""
    artifacts, _ = _esp32s3_artifacts(espressif_execution_context)
    startup = artifacts["espressif/esp32s3/generated/devices/esp32s3/startup.cpp"].content

    # Reset_Handler still exists and does the usual init sequence.
    assert "Reset_Handler" in startup
    assert "_sidata" in startup
    assert "_sbss" in startup
    # No RISC-V or AVR-specific markers.
    assert "mtvec" not in startup
    assert "__vector_0" not in startup
    assert "la sp," not in startup
    # No ARM-style stack-pointer cast at slot 0.
    assert "reinterpret_cast<void (*)()>(&__stack_top)" not in startup
    # Dual-core Xtensa control plane is announced and the per-core vector
    # tables are emitted (introduced by add-espressif-esp32-classic-target;
    # the older ".xtensa_vectors_info" debug section was retired alongside
    # the single-core-perspective posture).
    assert "Dual-core Xtensa control plane" in startup
    assert ".xtensa_vectors_cpu0" in startup
    assert ".xtensa_vectors_cpu1" in startup


def test_esp32s3_systick_is_not_required_for_xtensa(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Artifact-contract spec: systick.hpp is Cortex-M scoped."""
    from alloy_codegen.runtime_systick import runtime_systick_required_paths

    normalize_result = run_normalize(
        PipelineScope(vendor="espressif", family="esp32s3", device="esp32s3"),
        espressif_execution_context,
    )
    required = runtime_systick_required_paths(
        family_dir="espressif/esp32s3",
        devices=tuple(normalize_result.payload.devices),
    )
    assert required == (), "systick.hpp must not be required for Xtensa devices"


def test_esp32s3_runtime_has_no_string_glue_in_primary_contract(
    espressif_execution_context: ExecutionContext,
) -> None:
    _, result = _esp32s3_artifacts(espressif_execution_context)
    assert find_runtime_cpp_string_violations(result.payload.artifacts) == ()


def test_esp32s3_pinmux_route_operations_carry_iomatrix_schema(
    espressif_execution_context: ExecutionContext,
) -> None:
    """ESP32-S3 reuses the same IO Matrix schema as ESP32-C3."""
    device = run_normalize(
        PipelineScope(vendor="espressif", family="esp32s3", device="esp32s3"),
        espressif_execution_context,
    ).payload.devices[0]

    expected_schema = _pinmux_backend_schema_id("espressif", "esp32s3")
    assert expected_schema == "alloy.pinmux.espressif-iomatrix-v1"

    pinmux_operations = [
        operation
        for operation in device.route_operations
        if operation.kind == "write-selector" and operation.target_ref_kind == "pin"
    ]
    assert pinmux_operations, "Expected at least one pinmux route operation for ESP32-S3"
    for operation in pinmux_operations:
        assert operation.schema_id == expected_schema


def test_esp32s3_emitted_runtime_goldens_match(
    espressif_execution_context: ExecutionContext,
) -> None:
    artifacts, _ = _esp32s3_artifacts(espressif_execution_context)
    pairs = (
        (
            "espressif/esp32s3/generated/runtime/devices/esp32s3/interrupts.hpp",
            ESP32S3_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "esp32s3"
            / "interrupts.hpp",
        ),
        (
            "espressif/esp32s3/generated/runtime/devices/esp32s3/clock_graph.hpp",
            ESP32S3_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "esp32s3"
            / "clock_graph.hpp",
        ),
        (
            "espressif/esp32s3/generated/runtime/devices/esp32s3/peripheral_instances.hpp",
            ESP32S3_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "esp32s3"
            / "peripheral_instances.hpp",
        ),
        (
            "espressif/esp32s3/generated/devices/esp32s3/startup.cpp",
            ESP32S3_EMITTED_FIXTURE_DIR / "generated" / "devices" / "esp32s3" / "startup.cpp",
        ),
    )
    for emitted_path, fixture_path in pairs:
        assert emitted_path in artifacts, f"missing emitted artifact: {emitted_path}"
        expected = fixture_path.read_text(encoding="utf-8")
        assert artifacts[emitted_path].content == expected, (
            f"emitted {emitted_path} does not match golden fixture {fixture_path}"
        )


def test_publish_esp32s3_consumer_smoke_passes(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 4.7: end-to-end publish + host `c++` smoke compile for ESP32-S3.

    Proves the Xtensa runtime output consumes cleanly without AVR / RISC-V /
    ARM specific glue, mirrors the ESP32-C3 smoke gate."""
    result = run_publish(
        PipelineScope(vendor="espressif", family="esp32s3", device="esp32s3"),
        espressif_execution_context,
    )

    assert result.payload.consumer_verification is not None, (
        "Publish should have invoked the consumer smoke verification for ESP32-S3"
    )
    assert result.payload.consumer_verification.succeeded is True, (
        "Alloy consumer smoke build failed for espressif/esp32s3/esp32s3:\n"
        + result.payload.consumer_verification.stderr
    )


# ---------------------------------------------------------------------------
# ESP32 classic (dual-core Xtensa LX6) — add-espressif-esp32-classic-target
# ---------------------------------------------------------------------------

ESP32_EMITTED_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "emitted" / "esp32"
ESP32_CANONICAL_FIXTURE = Path(__file__).parent / "fixtures" / "esp32" / "esp32.canonical.json"


def _esp32_artifacts(espressif_execution_context: ExecutionContext, device: str = "esp32"):
    scope = PipelineScope(vendor="espressif", family="esp32", device=device)
    result = run_emit(scope, espressif_execution_context)
    return {artifact.path: artifact for artifact in result.payload.artifacts}, result


def test_esp32_classic_emitted_runtime_goldens_match(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 6.1: pinned canonical artefacts for the QFN48 device."""
    artifacts, _ = _esp32_artifacts(espressif_execution_context)
    pairs = (
        (
            "espressif/esp32/generated/runtime/devices/esp32/interrupts.hpp",
            ESP32_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "esp32"
            / "interrupts.hpp",
        ),
        (
            "espressif/esp32/generated/runtime/devices/esp32/clock_graph.hpp",
            ESP32_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "esp32"
            / "clock_graph.hpp",
        ),
        (
            "espressif/esp32/generated/runtime/devices/esp32/peripheral_instances.hpp",
            ESP32_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "esp32"
            / "peripheral_instances.hpp",
        ),
        (
            "espressif/esp32/generated/devices/esp32/startup.cpp",
            ESP32_EMITTED_FIXTURE_DIR / "generated" / "devices" / "esp32" / "startup.cpp",
        ),
    )
    for emitted_path, fixture_path in pairs:
        assert emitted_path in artifacts, f"missing emitted artifact: {emitted_path}"
        expected = fixture_path.read_text(encoding="utf-8")
        assert artifacts[emitted_path].content == expected, (
            f"emitted {emitted_path} does not match golden fixture {fixture_path}"
        )


def test_esp32_classic_startup_uses_dual_core_xtensa_conventions(
    espressif_execution_context: ExecutionContext,
) -> None:
    """The emitted startup carries the dual-core Xtensa control plane shaped
    for the LX6 silicon — DPORT.APPCPU_CTRL_B bring-up, both vector tables,
    no ARM/RISC-V/AVR-specific markers."""
    artifacts, _ = _esp32_artifacts(espressif_execution_context)
    startup = artifacts["espressif/esp32/generated/devices/esp32/startup.cpp"].content
    assert "Reset_Handler" in startup
    assert "Reset_Handler_CPU1" in startup
    assert "bring_up_app_cpu" in startup
    assert "_vectors_cpu0[]" in startup
    assert "_vectors_cpu1[]" in startup
    # LX6-specific bring-up via DPORT.APPCPU_CTRL_B (not the LX7 SYSTEM regs).
    assert "DPORT.APPCPU_CTRL_B" in startup
    assert "SYSTEM.CORE_1_CONTROL_0" not in startup
    # No cross-architecture leakage.
    assert "mtvec" not in startup
    assert "__vector_0" not in startup
    assert ".isr_vector" not in startup


def test_esp32_classic_normalize_admits_dual_core_perspective(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 4.3 of add-espressif-esp32-classic-target: the ESP32 classic
    canonical IR carries the dual-core posture — both cores' bring-up
    primitives are reachable through the canonical IR (DPORT block carries
    the inter-core IPI registers and APPCPU_CTRL_B for app-CPU release)."""
    scope = PipelineScope(vendor="espressif", family="esp32", device="esp32")
    device = run_normalize(scope, espressif_execution_context).payload.devices[0]
    assert device.identity.core == "xtensa-lx6"
    assert device.identity.package == "qfn48"
    admitted = {peripheral.name for peripheral in device.peripherals}
    # DPORT carries APPCPU_CTRL_B; the dual-core control plane requires it.
    assert "DPORT" in admitted
    # Vector slots default to cpu0 (classic ESP32 SVD does not declare
    # separate INTERRUPT_CORE0/CORE1 peripherals — affinity is dynamic at
    # runtime via DPORT.PRO_/APP_INTR_MAP).  All vectors land on cpu0 in
    # the static IR; APP_CPU vectors come online when bring_up_app_cpu()
    # configures them at runtime.
    affinities = {slot.core_affinity for slot in device.vector_slots}
    assert affinities == {"cpu0"} or affinities == {"cpu0", "shared"}


def test_esp32_classic_validate_no_draft_domains(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 4.4: validation passes for both ESP32 classic device variants
    with no drafted system descriptor domains."""
    from alloy_codegen.stages.validate import run as run_validate

    for device_name in ("esp32", "esp32-wroom32"):
        scope = PipelineScope(vendor="espressif", family="esp32", device=device_name)
        result = run_validate(scope, espressif_execution_context)
        assert result.status == "completed", (
            f"validation failed for esp32/{device_name}: warnings={result.warnings!r}"
        )
        report = result.payload.report
        drafts = tuple(
            domain.domain_id for domain in report.system_descriptor_domains if domain.draft
        )
        assert drafts == (), f"unexpected draft domains for esp32/{device_name}: {drafts}"


def test_esp32_classic_qfn48_and_wroom32_share_signals(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 4.5: QFN48 and WROOM-32 share the family catalog and only
    diverge in package_pads — the WROOM-32 variant has a smaller pad set
    (GPIO6-11 reserved for on-module flash, 37/38/etc not exposed on the
    module pin headers)."""
    qfn = run_normalize(
        PipelineScope(vendor="espressif", family="esp32", device="esp32"),
        espressif_execution_context,
    ).payload.devices[0]
    wroom = run_normalize(
        PipelineScope(vendor="espressif", family="esp32", device="esp32-wroom32"),
        espressif_execution_context,
    ).payload.devices[0]
    # Same canonical core / family.
    assert qfn.identity.core == wroom.identity.core == "xtensa-lx6"
    # WROOM-32 pad set is a subset of QFN48.  In this bootstrap only pins
    # carrying a peripheral-attributed signal (currently UART0 TX/RX on
    # GPIO1/GPIO3) make it through the pin-builder filter — so the visible
    # difference is small until the IO Matrix follow-on populates more
    # peripheral signals.
    qfn_pads = {pad.pad_id for pad in qfn.package_pads}
    wroom_pads = {pad.pad_id for pad in wroom.package_pads}
    assert wroom_pads <= qfn_pads, "WROOM-32 pads must be a subset of QFN48 pads"
    # Peripheral admission is identical (same family.json).
    assert {p.name for p in qfn.peripherals} == {p.name for p in wroom.peripherals}


# ---------------------------------------------------------------------------
# expose-xtensa-dual-core-facts: data-driven dual-core surface tests
# ---------------------------------------------------------------------------


def test_esp32_secondary_core_release_step_emitted(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 5.3: ESP32 classic emits a typed secondary-core release step."""
    from alloy_codegen.runtime_system_sequences import runtime_system_sequence_steps

    scope = PipelineScope(vendor="espressif", family="esp32", device="esp32")
    device = run_normalize(scope, espressif_execution_context).payload.devices[0]
    assert device.multicore_topology == "xtensa_asymmetric_dual_core"
    assert device.app_cpu_control_plane is not None
    assert (
        device.app_cpu_control_plane.release_register == "register:dport:appcpu-ctrl-b"
    )
    assert device.app_cpu_control_plane.operation == "set-bit-0"
    steps = runtime_system_sequence_steps(device)
    release_steps = [s for s in steps if s.kind == "secondary-core-release"]
    assert len(release_steps) == 1
    assert (
        release_steps[0].secondary_core_release_register_id
        == "register:dport:appcpu-ctrl-b"
    )
    assert release_steps[0].secondary_core_release_register_secondary_id is None
    assert release_steps[0].secondary_core_release_operation == "set-bit-0"


def test_esp32s3_secondary_core_release_step_emitted(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 5.4: ESP32-S3 emits the typed step with both CORE_1_CONTROL regs."""
    from alloy_codegen.runtime_system_sequences import runtime_system_sequence_steps

    scope = PipelineScope(vendor="espressif", family="esp32s3", device="esp32s3")
    device = run_normalize(scope, espressif_execution_context).payload.devices[0]
    assert device.multicore_topology == "xtensa_asymmetric_dual_core"
    assert device.app_cpu_control_plane is not None
    assert (
        device.app_cpu_control_plane.release_register
        == "register:system:core-1-control-0"
    )
    assert (
        device.app_cpu_control_plane.release_register_secondary
        == "register:system:core-1-control-1"
    )
    assert device.app_cpu_control_plane.operation == "clear-runstall-after-clkgate"
    steps = runtime_system_sequence_steps(device)
    release_steps = [s for s in steps if s.kind == "secondary-core-release"]
    assert len(release_steps) == 1
    assert (
        release_steps[0].secondary_core_release_register_id
        == "register:system:core-1-control-0"
    )
    assert (
        release_steps[0].secondary_core_release_register_secondary_id
        == "register:system:core-1-control-1"
    )
    assert (
        release_steps[0].secondary_core_release_operation
        == "clear-runstall-after-clkgate"
    )


def test_esp32c3_has_no_secondary_core_release_step(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 5.5: ESP32-C3 (single-core RISC-V) does NOT emit the step."""
    from alloy_codegen.runtime_system_sequences import runtime_system_sequence_steps

    scope = PipelineScope(vendor="espressif", family="esp32c3", device="esp32c3")
    device = run_normalize(scope, espressif_execution_context).payload.devices[0]
    assert device.multicore_topology == "single_core"
    assert device.app_cpu_control_plane is None
    steps = runtime_system_sequence_steps(device)
    assert not any(s.kind == "secondary-core-release" for s in steps)


def test_espressif_devices_carry_typed_multicore_topology(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Phase 5.6: Each Espressif device's ``Device.multicore_topology`` matches its
    family overlay."""
    expected = {
        "esp32": "xtensa_asymmetric_dual_core",
        "esp32s3": "xtensa_asymmetric_dual_core",
        "esp32c3": "single_core",
    }
    for device_name, expected_topology in expected.items():
        family = device_name
        scope = PipelineScope(vendor="espressif", family=family, device=device_name)
        device = run_normalize(scope, espressif_execution_context).payload.devices[0]
        assert device.multicore_topology == expected_topology, (
            f"{device_name} expected {expected_topology}, got {device.multicore_topology}"
        )
