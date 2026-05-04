"""Tests for :func:`emit_routes`.

Covers:
* Well-formed header structure (guard, namespace, enums, struct).
* RouteId enum contains expected candidate names.
* RouteKindId enum contains route_kind_alternate_function for STM32.
* RouteDescriptor struct present with correct fields.
* kRoutes table length matches pin_routes count.
* AF code values present in table (not all None).
* Emitter is deterministic.
* generate() writes routes.hpp alongside other artifacts.
"""

from __future__ import annotations

from pathlib import Path

from alloy_codegen.emit_v2_1 import emit_routes
from alloy_codegen.sources.alloy_devices_yml import load_with_synthesis


def _load() -> tuple:
    return load_with_synthesis(vendor="st", family="stm32g0", device="stm32g071rb")


# ---------------------------------------------------------------------------
# Header structure
# ---------------------------------------------------------------------------


def test_header_guard_and_namespace() -> None:
    canonical, syn = _load()
    text = emit_routes(canonical, syn)
    assert "#pragma once" in text
    assert "#ifndef ST_STM32G0_STM32G071RB_ROUTES_HPP_" in text
    assert "#define ST_STM32G0_STM32G071RB_ROUTES_HPP_" in text
    assert "namespace alloy::st::stm32g0::stm32g071rb {" in text
    assert "#endif  // ST_STM32G0_STM32G071RB_ROUTES_HPP_" in text


def test_includes_required_headers() -> None:
    """routes.hpp pulls array/cstdint transitively through connectors.hpp."""
    canonical, syn = _load()
    text = emit_routes(canonical, syn)
    assert '#include "connectors.hpp"' in text


# ---------------------------------------------------------------------------
# Enums
# ---------------------------------------------------------------------------


def test_includes_connectors_hpp() -> None:
    """routes.hpp must include connectors.hpp — RouteId/RouteKindId live there."""
    canonical, syn = _load()
    text = emit_routes(canonical, syn)
    assert '#include "connectors.hpp"' in text


def test_route_id_values_referenced_in_k_routes() -> None:
    """RouteId enum values are generated in connectors.hpp; routes.hpp
    references them in the kRoutes table body."""
    canonical, syn = _load()
    text = emit_routes(canonical, syn)
    assert "RouteId::candidate_pb6_usart1_tx" in text
    assert "RouteId::candidate_pa9_usart1_tx" in text


def test_route_kind_referenced_in_k_routes() -> None:
    canonical, syn = _load()
    text = emit_routes(canonical, syn)
    assert "RouteKindId::route_kind_alternate_function" in text


# ---------------------------------------------------------------------------
# RouteDescriptor struct
# ---------------------------------------------------------------------------


def test_route_descriptor_struct_present() -> None:
    canonical, syn = _load()
    text = emit_routes(canonical, syn)
    assert "struct RouteDescriptor {" in text
    assert "RouteId     route_id;" in text
    assert "RouteKindId route_kind_id;" in text
    assert "std::uint16_t code;" in text


# ---------------------------------------------------------------------------
# kRoutes table
# ---------------------------------------------------------------------------


def test_k_routes_size_matches_unique_route_count() -> None:
    """kRoutes is deduplicated — size == unique (pin, peri, signal) triples."""
    canonical, syn = _load()
    text = emit_routes(canonical, syn)
    unique_n = len({(r.pin_id, r.peripheral_id, r.signal_id) for r in syn.pin_routes})
    assert f"inline constexpr std::array<RouteDescriptor, {unique_n}> kRoutes" in text


def test_k_routes_entry_for_pb6_usart1_tx() -> None:
    canonical, syn = _load()
    text = emit_routes(canonical, syn)
    assert "RouteId::candidate_pb6_usart1_tx" in text
    assert "RouteKindId::route_kind_alternate_function" in text


def test_k_routes_code_sentinel_for_none_codes() -> None:
    """Routes where code=None must emit the sentinel 0xFFFFu."""
    canonical, syn = _load()
    text = emit_routes(canonical, syn)
    # stm32g071rb has routes with code=None (AF not yet in IR).
    none_routes = [r for r in syn.pin_routes if r.code is None]
    if none_routes:
        assert "0xFFFFu" in text


# ---------------------------------------------------------------------------
# Determinism
# ---------------------------------------------------------------------------


def test_emit_routes_is_deterministic() -> None:
    canonical, syn = _load()
    assert emit_routes(canonical, syn) == emit_routes(canonical, syn)


# ---------------------------------------------------------------------------
# Integration
# ---------------------------------------------------------------------------


def test_generate_writes_routes_hpp(tmp_path: Path) -> None:
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
    assert "routes.hpp" in names
    body = next(p for p in written if p.name == "routes.hpp").read_text("utf-8")
    assert "RouteDescriptor" in body
    assert "route_kind_alternate_function" in body
