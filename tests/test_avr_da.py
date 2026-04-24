"""Regression tests for the Microchip AVR-DA bootstrap target.

Covers Phase 3 of OpenSpec change `add-microchip-avr-da-target`:
- 3.1 Backend schema id `alloy.pinmux.avr-portmux-v1` is registered.
- 3.2/3.3 PORTMUX pin-signal coverage for USART/SPI/TWI peripherals.
- 3.4 Emitted runtime artifacts (routes.hpp, types.hpp) encode the
  PORTMUX schema id, so Alloy consumers can distinguish AVR-Dx routing
  from ARM AF and ESP32 IO Matrix at the type level.
"""

from __future__ import annotations

from alloy_codegen.connector_model import _pinmux_backend_schema_id
from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.normalize import run as run_normalize


def test_pinmux_schema_for_avr_da_is_avr_portmux_v1() -> None:
    """Phase 3.1: `_pinmux_backend_schema_id("microchip", "avr-da")`
    returns the AVR PORTMUX schema id, distinct from the SAME70 PIO schema
    used by the other Microchip family."""
    assert _pinmux_backend_schema_id("microchip", "avr-da") == "alloy.pinmux.avr-portmux-v1"
    # SAME70 stays on its own schema — the new family-scoped arm of the
    # match expression must not accidentally rewrite Microchip/same70.
    assert _pinmux_backend_schema_id("microchip", "same70") == "alloy.pinmux.sam-pio-v1"
    # Vendor without a family hint falls back to the historical per-vendor
    # default (SAME70 PIO for Microchip).
    assert _pinmux_backend_schema_id("microchip") == "alloy.pinmux.sam-pio-v1"


def test_avr128da32_pinmux_route_operations_carry_portmux_schema(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """Phase 3.4: every `write-selector` route operation emitted for an
    AVR128DA32 pin signal carries `alloy.pinmux.avr-portmux-v1` as its
    `schema_id`."""
    device = run_normalize(
        PipelineScope(device="avr128da32"), microchip_avr_da_execution_context
    ).payload.devices[0]

    pinmux_operations = [
        operation
        for operation in device.route_operations
        if operation.kind == "write-selector" and operation.target_ref_kind == "pin"
    ]
    assert pinmux_operations, "Expected at least one pinmux route operation for AVR128DA32"
    for operation in pinmux_operations:
        assert operation.schema_id == "alloy.pinmux.avr-portmux-v1", (
            f"{operation.operation_id}: schema_id={operation.schema_id!r}"
        )


def test_avr128da32_pinmux_covers_usart_spi_twi_bootstrap_peripherals(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """Phase 3.2/3.3: PORTMUX pin-signal coverage spans the bootstrap
    peripheral set (USART/SPI/TWI).  Without this, runtime drivers for
    those classes would have nowhere to route their signals."""
    device = run_normalize(
        PipelineScope(device="avr128da32"), microchip_avr_da_execution_context
    ).payload.devices[0]
    candidate_peripherals_by_class: dict[str, set[str]] = {}
    for candidate in device.connection_candidates:
        candidate_peripherals_by_class.setdefault(candidate.peripheral, set()).add(candidate.signal)

    # Signal roles are stored lowercase on ConnectionCandidate.  The AVR-DA
    # bootstrap must route USART TX+RX, the full SPI MOSI/MISO/SCK + CS
    # quartet, and TWI SDA/SCL.
    assert "tx" in candidate_peripherals_by_class.get("USART0", set())
    assert "rx" in candidate_peripherals_by_class.get("USART0", set())
    spi0_signals = candidate_peripherals_by_class.get("SPI0", set())
    assert {"mosi", "miso", "sck", "cs"} <= spi0_signals, spi0_signals
    assert {"sda", "scl"} <= candidate_peripherals_by_class.get("TWI0", set())


def test_avr128da32_runtime_routes_header_encodes_portmux_schema(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """Phase 3.4: the emitted `runtime/devices/avr128da32/routes.hpp` and
    `runtime/types.hpp` encode the PORTMUX schema id in the BackendSchemaId
    enum — the executable runtime output carries the same provenance as the
    canonical IR."""
    result = run_emit(PipelineScope(device="avr128da32"), microchip_avr_da_execution_context)
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}
    routes = artifacts["microchip/avr-da/generated/runtime/devices/avr128da32/routes.hpp"].content
    types = artifacts["microchip/avr-da/generated/runtime/types.hpp"].content

    # The emitter sanitizes the schema id into a C++ enum identifier.
    # `alloy.pinmux.avr-portmux-v1` becomes `schema_alloy_pinmux_avr_portmux_v1`.
    assert "schema_alloy_pinmux_avr_portmux_v1" in types, (
        "Expected PORTMUX backend schema id to be declared in the BackendSchemaId "
        "enum in the emitted runtime types.hpp"
    )
    assert "schema_alloy_pinmux_avr_portmux_v1" in routes, (
        "Expected PORTMUX backend schema id to appear on every pinmux route "
        "operation in the emitted routes.hpp"
    )


# ---------------------------------------------------------------------------
# Phase 4 — AVR runtime emission (startup + header contract)
# ---------------------------------------------------------------------------


AVR_DA_EMITTED_FIXTURE_DIR = (
    __import__("pathlib").Path(__file__).parent / "fixtures" / "emitted" / "avr-da"
)


def _avr_da_emit_artifacts(microchip_avr_da_execution_context):
    result = run_emit(
        PipelineScope(vendor="microchip", family="avr-da", device="avr128da32"),
        microchip_avr_da_execution_context,
    )
    return {artifact.path: artifact for artifact in result.payload.artifacts}


def test_avr128da32_runtime_contract_emits_required_headers(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """Phase 4.1/4.2: emitted runtime contract includes the typed headers the
    artifact contract spec requires for AVR-DA."""
    artifacts = _avr_da_emit_artifacts(microchip_avr_da_execution_context)
    required = (
        "microchip/avr-da/generated/runtime/devices/avr128da32/interrupts.hpp",
        "microchip/avr-da/generated/runtime/devices/avr128da32/clock_graph.hpp",
        "microchip/avr-da/generated/runtime/devices/avr128da32/peripheral_instances.hpp",
    )
    for path in required:
        assert path in artifacts, f"missing AVR-DA runtime header: {path}"


def test_avr128da32_interrupts_hpp_carries_avr8_slots_without_arm_offset(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """Phase 4.1: interrupts.hpp contains the ATDF-derived AVR interrupt names
    and NONE of the ARM Cortex-M system exception names."""
    artifacts = _avr_da_emit_artifacts(microchip_avr_da_execution_context)
    content = artifacts[
        "microchip/avr-da/generated/runtime/devices/avr128da32/interrupts.hpp"
    ].content
    # ATDF-sourced interrupts appear as InterruptId enum entries.
    for expected in ("USART0_RXC", "USART0_DRE", "USART0_TXC", "TWI0_TWIM", "SPI0_INT"):
        assert expected in content, f"{expected} missing from emitted interrupts.hpp"
    # ARM fault handlers must not leak into the AVR enum.
    for forbidden in ("HardFault", "MemManage", "PendSV", "SysTick_Handler", "SVCall"):
        assert forbidden not in content, (
            f"ARM fault symbol {forbidden!r} leaked into AVR interrupts.hpp"
        )


def test_avr128da32_startup_uses_crt0_vector_n_convention(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """Phase 4.4: the emitted startup.cpp follows avr-libc conventions —
    ``__vector_<line>`` weak handlers, guarded behind ``__AVR__`` so host
    smoke builds stay portable."""
    artifacts = _avr_da_emit_artifacts(microchip_avr_da_execution_context)
    startup = artifacts["microchip/avr-da/generated/devices/avr128da32/startup.cpp"].content

    # AVR convention: __vector_N for each peripheral interrupt where N is the
    # ATDF interrupt index (18 = USART0_RXC, 28 = SPI0_INT, etc. — per the
    # bootstrap fixture ATDF).
    assert "__vector_18" in startup  # USART0_RXC
    assert "__vector_28" in startup  # SPI0_INT

    # The IR's canonical X_IRQHandler symbol is emitted as a weak alias of
    # __vector_<line>.
    assert 'USART0_RXC_IRQHandler() __attribute__((weak, alias("__vector_18")))' in startup
    assert 'SPI0_INT_IRQHandler() __attribute__((weak, alias("__vector_28")))' in startup

    # Host smoke guard plus __AVR__ guard — nothing AVR-specific runs in a
    # generic host compile.
    assert "#if defined(ALLOY_CODEGEN_HOST_SMOKE)" in startup
    assert "#elif defined(__AVR__)" in startup

    # avr-libc owns __vector_0 (reset).  Redefining it here would collide at
    # link time.  The emitter must NOT declare __vector_0.
    assert "void __vector_0()" not in startup

    # No ARM-style artefacts.
    assert "_vectors[]" not in startup  # ARM array of function pointers
    assert "__stack_top" not in startup  # ARM CMSIS convention
    assert "Reset_Handler" not in startup  # ARM startup symbol
    assert "mtvec" not in startup  # RISC-V register


def test_avr128da32_systick_hpp_is_not_required(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """Phase 4.3: ``systick.hpp`` is Cortex-M scoped; AVR publish must not
    require the path, mirroring the RISC-V exemption for ESP32-C3."""
    from alloy_codegen.runtime_systick import runtime_systick_required_paths
    from alloy_codegen.stages.normalize import run as run_normalize

    devices = run_normalize(
        PipelineScope(vendor="microchip", family="avr-da", device="avr128da32"),
        microchip_avr_da_execution_context,
    ).payload.devices
    assert (
        runtime_systick_required_paths(family_dir="microchip/avr-da", devices=tuple(devices)) == ()
    )


def test_avr128da32_runtime_has_no_string_glue_in_primary_contract(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """Phase 4 × remove-runtime-string-glue: the AVR-DA runtime output passes
    the typed-contract gate — no string literals in primary runtime fields."""
    from alloy_codegen.artifact_contract import find_runtime_cpp_string_violations

    result = run_emit(
        PipelineScope(vendor="microchip", family="avr-da", device="avr128da32"),
        microchip_avr_da_execution_context,
    )
    assert find_runtime_cpp_string_violations(result.payload.artifacts) == ()


def test_avr128da32_emitted_runtime_goldens_match(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """Phase 4.9: emitted runtime artifacts match the goldens committed in
    ``tests/fixtures/emitted/avr-da/``.  Any drift in the AVR emit path
    (startup layout, interrupts.hpp typed enums, peripheral instance traits)
    shows up here."""
    artifacts = _avr_da_emit_artifacts(microchip_avr_da_execution_context)
    pairs = (
        (
            "microchip/avr-da/generated/runtime/devices/avr128da32/interrupts.hpp",
            AVR_DA_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "avr128da32"
            / "interrupts.hpp",
        ),
        (
            "microchip/avr-da/generated/runtime/devices/avr128da32/clock_graph.hpp",
            AVR_DA_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "avr128da32"
            / "clock_graph.hpp",
        ),
        (
            "microchip/avr-da/generated/runtime/devices/avr128da32/peripheral_instances.hpp",
            AVR_DA_EMITTED_FIXTURE_DIR
            / "generated"
            / "runtime"
            / "devices"
            / "avr128da32"
            / "peripheral_instances.hpp",
        ),
        (
            "microchip/avr-da/generated/devices/avr128da32/startup.cpp",
            AVR_DA_EMITTED_FIXTURE_DIR / "generated" / "devices" / "avr128da32" / "startup.cpp",
        ),
    )
    for emitted_path, fixture_path in pairs:
        assert emitted_path in artifacts, f"missing emitted artifact: {emitted_path}"
        expected = fixture_path.read_text(encoding="utf-8")
        assert artifacts[emitted_path].content == expected, (
            f"emitted {emitted_path} does not match golden fixture {fixture_path}"
        )


# ---------------------------------------------------------------------------
# Phase 4.6–4.8 — avr-gcc compile + avr-objdump disassembly validation
# ---------------------------------------------------------------------------


def test_verify_avr_startup_with_avr_gcc_skips_cleanly_when_toolchain_absent(
    microchip_avr_da_execution_context: ExecutionContext,
    tmp_path,
) -> None:
    """Phase 4.6: when the avr-gcc toolchain is not installed, the helper
    returns ``None`` so callers can skip instead of exploding."""
    import shutil

    from alloy_codegen.consumer_verification import (
        avr_gcc_is_available,
        verify_avr_startup_with_avr_gcc,
    )

    artifacts = _avr_da_emit_artifacts(microchip_avr_da_execution_context)
    staged = tmp_path / "startup.cpp"
    staged.write_text(
        artifacts["microchip/avr-da/generated/devices/avr128da32/startup.cpp"].content,
        encoding="utf-8",
    )

    expected_available = (
        shutil.which("avr-gcc") is not None and shutil.which("avr-objdump") is not None
    )
    assert avr_gcc_is_available() is expected_available

    result = verify_avr_startup_with_avr_gcc(
        startup_source=staged,
        build_root=tmp_path / "build",
        mcu="avr128da32",
    )
    if avr_gcc_is_available():
        assert result is not None
        assert result.succeeded is True, (
            "avr-gcc compile + avr-objdump disassembly failed for the "
            "emitted AVR startup:\n" + result.stderr
        )
    else:
        assert result is None, "avr-gcc is not on PATH; helper must return None so pytest can skip"


def test_verify_avr_startup_with_avr_gcc_catches_missing_vector_alias(
    tmp_path,
) -> None:
    """Phase 4.8: if avr-gcc is available, feeding a startup.cpp that
    does NOT emit the expected weak-alias structure must make the
    disassembly check fail.  This protects against silent regressions
    in `runtime_avr_startup.py`.

    Skipped cleanly when avr-gcc is not installed."""
    import pytest as _pytest

    from alloy_codegen.consumer_verification import (
        avr_gcc_is_available,
        verify_avr_startup_with_avr_gcc,
    )

    if not avr_gcc_is_available():
        _pytest.skip("avr-gcc / avr-objdump not installed on PATH")

    broken = tmp_path / "broken-startup.cpp"
    broken.write_text(
        # Compiles with avr-gcc but carries none of the expected aliases.
        'extern "C" {\nvoid harmless_stub() {}\n}\n',
        encoding="utf-8",
    )
    result = verify_avr_startup_with_avr_gcc(
        startup_source=broken,
        build_root=tmp_path / "build",
        mcu="avr128da32",
    )
    assert result is not None
    assert result.succeeded is False
    assert "Missing expected symbols" in result.stderr
