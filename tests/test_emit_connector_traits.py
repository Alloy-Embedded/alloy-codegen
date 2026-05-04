"""Tests for :func:`emit_connector_traits`.

Covers:
* Well-formed header structure (guard, namespace, enums).
* Full specialisation present for a known valid triple.
* Guard A fires the right diagnostic for (*, USART1, signal_tx).
* Guard B fires the right diagnostic for (PB6, *, signal_tx).
* ``kConnectors`` table has the right length.
* Emitter is deterministic across calls.
* ``generate()`` writes ``connectors.hpp`` alongside other artifacts.
* ``PinRoute.route_kind`` property returns the correct enumerator name.
"""

from __future__ import annotations

from pathlib import Path

from alloy_codegen.emit_v2_1 import emit_connector_traits
from alloy_codegen.ir.synthesised import PinRoute
from alloy_codegen.sources.alloy_devices_yml import load_with_synthesis


# ---------------------------------------------------------------------------
# Shared fixtures
# ---------------------------------------------------------------------------


def _load_stm32g071rb() -> tuple:
    return load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )


# ---------------------------------------------------------------------------
# PinRoute.route_kind property (task 2.1)
# ---------------------------------------------------------------------------


def test_pin_route_route_kind_stm32_af() -> None:
    _, syn = _load_stm32g071rb()
    stm32_routes = [r for r in syn.pin_routes if r.backend_schema_id == "alloy.pinmux.stm32-af-v1"]
    assert stm32_routes, "must have STM32 AF routes"
    assert all(r.route_kind == "route_kind_alternate_function" for r in stm32_routes)


def test_pin_route_route_kind_unknown_backend() -> None:
    r = PinRoute(
        peripheral_id="FOO1",
        signal_id="tx",
        pin_id="pa0",
        backend_schema_id="alloy.pinmux.hypothetical-v99",
    )
    assert r.route_kind == "route_kind_unknown"


# ---------------------------------------------------------------------------
# Header structure
# ---------------------------------------------------------------------------


def test_header_guard_and_namespace() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    assert "#pragma once" in text
    assert "#ifndef ST_STM32G0_STM32G071RB_CONNECTORS_HPP_" in text
    assert "#define ST_STM32G0_STM32G071RB_CONNECTORS_HPP_" in text
    assert "namespace alloy::st::stm32g0::stm32g071rb {" in text
    assert "#endif  // ST_STM32G0_STM32G071RB_CONNECTORS_HPP_" in text


def test_includes_required_headers() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    assert "#include <array>" in text
    assert "#include <cstdint>" in text


def test_all_required_enums_present() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    for enum in ("PinId", "PeripheralId", "SignalId", "RouteKindId",
                 "ConnectionGroupId", "RouteId", "ConnectorId"):
        assert f"enum class {enum}" in text, f"missing enum {enum}"


def test_route_kind_alternate_function_in_enum() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    assert "route_kind_alternate_function" in text


def test_connector_descriptor_struct_present() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    assert "struct ConnectorDescriptor {" in text
    assert "ConnectorId      connector_id;" in text
    assert "RouteKindId      route_kind_id;" in text


def test_detail_kinvalid_connector_helper() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    assert "namespace detail {" in text
    assert "kInvalidConnector" in text


# ---------------------------------------------------------------------------
# ConnectorTraits base template
# ---------------------------------------------------------------------------


def test_base_connector_traits_always_false() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    assert "template<PinId kPin, PeripheralId kPeripheral, SignalId kSignal>" in text
    assert "struct ConnectorTraits {" in text
    assert "kPresent     = false;" in text


# ---------------------------------------------------------------------------
# Full specialisations
# ---------------------------------------------------------------------------


def test_full_spec_pb6_usart1_tx_present() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    # Full spec for PB6 / USART1 / signal_tx.
    assert (
        "struct ConnectorTraits<PinId::PB6, PeripheralId::USART1, SignalId::signal_tx> {"
        in text
    )
    # Must declare kPresent = true.
    assert "kPresent      = true;" in text


def test_full_spec_sets_route_kind_alternate_function() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    assert "RouteKindId::route_kind_alternate_function" in text


def test_full_spec_connector_id_naming() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    # ConnectorId follows candidate_<pin>_<peri_lower>_<signal> convention.
    assert "ConnectorId::candidate_pb6_usart1_tx" in text


# ---------------------------------------------------------------------------
# Guard A — wrong pin for known (peripheral, signal)
# ---------------------------------------------------------------------------


def test_guard_a_template_partial_spec_present() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    # Guard A uses <kPin> free parameter.
    assert "template<PinId kPin>" in text
    # Must reference PeripheralId::USART1 with signal_tx.
    assert (
        "struct ConnectorTraits<kPin, PeripheralId::USART1, SignalId::signal_tx> {"
        in text
    )


def test_guard_a_usart1_tx_lists_valid_pins() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    # stm32g071rb exposes USART1 tx on PA9 (alternate PA11), PB6, PC4.
    # Guard A diagnostic must mention at least PB6.
    guard_a_idx = text.find(
        "struct ConnectorTraits<kPin, PeripheralId::USART1, SignalId::signal_tx>"
    )
    assert guard_a_idx != -1
    snippet = text[guard_a_idx: guard_a_idx + 400]
    assert "static_assert" in snippet
    assert "PB6" in snippet


def test_guard_a_static_assert_uses_kinvalid_connector() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    # Guard A must use the dependent-false helper so the assert is lazy.
    assert "detail::kInvalidConnector<kPin>" in text


# ---------------------------------------------------------------------------
# Guard B — wrong peripheral for known (pin, signal)
# ---------------------------------------------------------------------------


def test_guard_b_template_partial_spec_present() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    # Guard B uses <kPeripheral> free parameter.
    assert "template<PeripheralId kPeripheral>" in text
    assert (
        "struct ConnectorTraits<PinId::PB6, kPeripheral, SignalId::signal_tx> {"
        in text
    )


def test_guard_b_pb6_tx_lists_valid_peripherals() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    guard_b_idx = text.find(
        "struct ConnectorTraits<PinId::PB6, kPeripheral, SignalId::signal_tx>"
    )
    assert guard_b_idx != -1
    snippet = text[guard_b_idx: guard_b_idx + 300]
    assert "static_assert" in snippet
    assert "USART1" in snippet


def test_guard_b_static_assert_uses_kinvalid_connector() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    assert "detail::kInvalidConnector<kPeripheral>" in text


# ---------------------------------------------------------------------------
# ConnectorSignalTraits
# ---------------------------------------------------------------------------


def test_connector_signal_traits_base_present() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    assert "template<PeripheralId kPeripheral, SignalId kSignal>" in text
    assert "struct ConnectorSignalTraits {" in text


def test_connector_signal_traits_full_spec_usart1_tx() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    assert (
        "struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_tx> {"
        in text
    )


# ---------------------------------------------------------------------------
# kConnectors table
# ---------------------------------------------------------------------------


def test_k_connectors_size_matches_unique_route_count() -> None:
    """kConnectors is deduplicated — size == unique (pin, peri, signal) triples."""
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    unique_n = len({(r.pin_id, r.peripheral_id, r.signal_id) for r in syn.pin_routes})
    assert f"inline constexpr std::array<ConnectorDescriptor, {unique_n}> kConnectors" in text


def test_k_connectors_pb6_usart1_tx_entry() -> None:
    canonical, syn = _load_stm32g071rb()
    text = emit_connector_traits(canonical, syn)
    # At least one entry for candidate_pb6_usart1_tx in the descriptor table.
    assert "candidate_pb6_usart1_tx" in text
    assert "PinId::PB6" in text


# ---------------------------------------------------------------------------
# Determinism
# ---------------------------------------------------------------------------


def test_emit_connector_traits_is_deterministic() -> None:
    canonical, syn = _load_stm32g071rb()
    assert emit_connector_traits(canonical, syn) == emit_connector_traits(canonical, syn)


# ---------------------------------------------------------------------------
# Integration — generate() writes connectors.hpp
# ---------------------------------------------------------------------------


def test_generate_writes_connectors_hpp(tmp_path: Path) -> None:
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
    assert "connectors.hpp" in names
    body = next(p for p in written if p.name == "connectors.hpp").read_text("utf-8")
    assert "ConnectorTraits" in body
    assert "route_kind_alternate_function" in body
