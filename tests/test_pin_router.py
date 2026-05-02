"""Unit tests for the pin-router foundational pass.

Covers:

* :class:`PinmuxBackend` registry + STM32 AF dispatch.
* STM32 pad-label normalisation (alternate-pin, OSC32 markers,
  function-suffix stripping).
* :class:`SynthesisedDevice` carries a non-empty ``pin_routes``
  table for an STM32 chip; rows are deterministically sorted.
* ``emit_pin_router`` produces a header with the documented
  banner, ``pin::id`` enum, and ``kRoutes`` array of the right
  size.
* The package-level ``generate(config, out_dir)`` writes
  ``pins.h`` next to the other artifacts.
"""

from __future__ import annotations

from pathlib import Path

from alloy_codegen.emit_v2_1 import emit_pin_router
from alloy_codegen.emit_v2_1.pinmux_backends import backend_for, registry
from alloy_codegen.emit_v2_1.pinmux_backends.stm32_af import (
    SCHEMA_ID,
    _strip_pin_label,
)
from alloy_codegen.ir.synthesised import PinRoute
from alloy_codegen.sources.alloy_devices_yml import load_with_synthesis


def test_registry_exposes_stm32_af_backend() -> None:
    backends = registry()
    assert ("st", "stm32") in backends
    backend = backend_for("st", "stm32g0")
    assert backend is not None
    assert backend.schema_id == "alloy.pinmux.stm32-af-v1"


def test_unknown_family_returns_none() -> None:
    assert backend_for("acme", "any-family") is None


def test_strip_pin_label_handles_canonical_forms() -> None:
    assert _strip_pin_label("PA2") == ("PA2", None)
    # Alternate-pin annotation kept separately.
    assert _strip_pin_label("PA12 [PA10]") == ("PA12", "PA10")
    assert _strip_pin_label("PA9 [PA11]") == ("PA9", "PA11")
    # Trailing function annotation dropped.
    assert _strip_pin_label("PA14-BOOT0") == ("PA14", None)
    assert _strip_pin_label("PC15-OSC32_OUT (PC15)") == ("PC15", None)
    assert _strip_pin_label("PC14-OSC32_IN (PC14)") == ("PC14", None)


def test_synthesised_device_carries_pin_routes_for_stm32() -> None:
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    assert syn.pin_routes, "STM32 G0 must produce pin_routes"
    assert all(isinstance(r, PinRoute) for r in syn.pin_routes)
    assert all(r.backend_schema_id == SCHEMA_ID for r in syn.pin_routes)
    # Sorted by (peripheral_id, signal_id, pin_id).
    keys = [(r.peripheral_id, r.signal_id, r.pin_id) for r in syn.pin_routes]
    assert keys == sorted(keys)


def test_synthesised_pin_routes_capture_alternate_pins() -> None:
    """STM32 G0's PA12 [PA10] annotation should round-trip via
    ``PinRoute.alternate_pin``."""
    _, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    alt_routes = [r for r in syn.pin_routes if r.alternate_pin is not None]
    assert alt_routes, "G0 has at least one alternate-pin annotation"
    # Spot-check one expected entry: USART1.cts admits PA11 [PA9].
    assert any(
        r.peripheral_id == "usart1" and r.signal_id == "cts"
        and r.pin_id == "pa11" and r.alternate_pin == "PA9"
        for r in alt_routes
    )


def test_emit_pin_router_emits_well_formed_header() -> None:
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    text = emit_pin_router(canonical, syn)
    # Header guard + namespace.
    assert "#ifndef ALLOY_ST_STM32G0_STM32G071RB_PINS_H" in text
    assert "namespace alloy::st::stm32g0::stm32g071rb" in text
    # PinId enum present.
    assert "enum class id : uint16_t" in text
    # kRoutes carries exactly len(syn.pin_routes) rows.
    assert f"kRouteCount = {len(syn.pin_routes)}u" in text
    assert f"std::array<route, {len(syn.pin_routes)}>" in text
    # Banner declares the schema id.
    assert "alloy.pinmux.stm32-af-v1" in text
    assert "alloy-pins layout v1" in text


def test_emit_pin_router_is_deterministic() -> None:
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    a = emit_pin_router(canonical, syn)
    b = emit_pin_router(canonical, syn)
    assert a == b


def test_generate_writes_pins_h(tmp_path: Path) -> None:
    """The package-level ``generate(config, out_dir)`` entry point
    must include ``pins.h`` in the artifact set."""
    import alloy_codegen
    from dataclasses import dataclass

    @dataclass(frozen=True)
    class Chip:
        vendor: str = "st"
        family: str = "stm32g0"
        device: str = "stm32g071rb"

    @dataclass(frozen=True)
    class Cfg:
        chip: Chip = Chip()
        board: None = None

    written = alloy_codegen.generate(Cfg(), tmp_path)
    names = {p.name for p in written}
    assert "pins.h" in names
    pins_h = next(p for p in written if p.name == "pins.h")
    body = pins_h.read_text(encoding="utf-8")
    assert "alloy.pinmux.stm32-af-v1" in body


def test_unsupported_vendor_emits_empty_routes(tmp_path: Path) -> None:
    """Devices whose vendor has no PinmuxBackend yet still receive
    a well-formed (empty-table) ``pins.h`` — the emitter does not
    crash and the kRoutes array is sized 0."""
    canonical, syn = load_with_synthesis(
        vendor="microchip", family="same70", device="atsame70q21b",
    )
    text = emit_pin_router(canonical, syn)
    # Empty routes table — no SAM PIO backend yet.
    assert "kRouteCount = 0u" in text
    # Banner falls back to the unknown sentinel.
    assert "alloy.pinmux.unknown-v0" in text
