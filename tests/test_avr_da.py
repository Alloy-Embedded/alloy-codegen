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
    routes = artifacts[
        "microchip/avr-da/generated/runtime/devices/avr128da32/routes.hpp"
    ].content
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
