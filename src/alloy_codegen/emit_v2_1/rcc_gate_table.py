"""Emit ``rcc_gate_table.hpp`` — compile-time RCC clock-gate lookup table.

The generated file is the device-specific half of the two-part lookup
mechanism described in ``src/device/rcc_gate_table.hpp`` (alloy-hal):

  1. ``device/rcc_gate_table.hpp`` (alloy-hal, shared) — declares the
     ``RccGate`` struct and the ``find_rcc_gate()`` function signature.
  2. This generated file — provides the per-device ``kRccGatesData[]``
     array and the ``consteval find_rcc_gate()`` definition.

Usage in a firmware build:

  -DALLOY_DEVICE_RCC_TABLE_AVAILABLE=1
  -DALLOY_DEVICE_RCC_TABLE_INCLUDE="<path/to/rcc_gate_table.hpp>"

When those defines are present, ``device/rcc_gate_table.hpp`` includes
this file inside the ``alloy::device::detail`` namespace, satisfying
the ``find_rcc_gate()`` declaration with a concrete ``consteval``
definition.

Lookup chain (per peripheral)
------------------------------
``en_path``  e.g. ``"rcc.apbenr2.usart1en"``
  1. Split on ``'.'`` → ``(tname, reg, field)``.
  2. ``device.templates[tname].registers[reg].offset`` → byte offset.
  3. ``device.templates[tname].fields[f"{reg}.{field}"].bit`` → bit index.
  4. Find clock-control peripheral base (same logic as ``rcc_enable.py``).
  5. Emit ``{ "en_path", base + offset, 1u << bit }`` in ``kRccGatesData``.

Reuses ``_resolve_path`` / ``_find_ctrl_base`` from :mod:`rcc_enable`
to avoid duplicating the path-parsing / base-address lookup logic.
"""

from __future__ import annotations

from alloy_codegen.emit_v2_1.rcc_enable import (
    _find_ctrl_base,
    _parse_rcc_path,
    _resolve_path,
)
from alloy_codegen.ir.synthesised import SynthesisedDevice
from alloy_codegen.ir.v2_1 import CanonicalDevice
from alloy_codegen.ir.v2_1.peripherals import PeripheralRcc
from alloy_codegen.ir.v2_1.templates import Template


def _header_guard(device: CanonicalDevice) -> str:
    parts = (
        device.identity.vendor,
        device.identity.family,
        device.identity.device,
        "rcc_gate_table_hpp",
    )
    return "_".join(p.upper().replace("-", "_") for p in parts) + "_"


def emit_rcc_gate_table(
    device: CanonicalDevice,
    synthesised: SynthesisedDevice,
) -> str:
    """Render the per-device ``rcc_gate_table.hpp`` for ``device``.

    The output is the *definition half* of the two-part lookup — it must be
    included from inside the ``alloy::device::detail`` namespace block that
    the base ``device/rcc_gate_table.hpp`` header opens before the
    ``#include ALLOY_DEVICE_RCC_TABLE_INCLUDE`` line.
    """
    guard = _header_guard(device)
    templates: dict[str, Template] = device.templates or {}

    # ── Collect all RCC template names referenced by enable paths ────────────
    tnames_needed: set[str] = set()
    for rcc in synthesised.per_rcc_map.values():
        if rcc.en:
            parsed = _parse_rcc_path(rcc.en)
            if parsed:
                tnames_needed.add(parsed[0])
    for per in device.peripherals:
        if per.rcc and per.rcc.en:
            parsed = _parse_rcc_path(per.rcc.en)
            if parsed:
                tnames_needed.add(parsed[0])

    # ── Resolve base address for each needed clock-control template ───────────
    # base_const_map: template-name → C++ constant name (e.g. "kRccBase")
    # base_values   : template-name → actual integer base address
    base_const_map: dict[str, str] = {}
    base_values: dict[str, int] = {}

    for tname in sorted(tnames_needed):
        base = _find_ctrl_base(device, tname)
        if base is not None:
            const_name = "k" + tname.replace("-", "_").capitalize() + "Base"
            base_const_map[tname] = const_name
            base_values[tname] = base

    # ── Collect per-peripheral enable gates ───────────────────────────────────
    gate_rows: list[tuple[str, int, int]] = []  # (en_path, absolute_addr, mask)
    seen_paths: set[str] = set()

    for per in device.peripherals:
        eff_rcc: PeripheralRcc | None = synthesised.per_rcc_map.get(per.id) or per.rcc
        if eff_rcc is None or not eff_rcc.en:
            continue
        en_path = eff_rcc.en
        if en_path in seen_paths:
            continue  # de-duplicate shared enable paths (e.g. shared DMA enable bit)

        resolved = _resolve_path(en_path, templates, base_const_map)
        if resolved is None:
            continue
        _, _, base_const, offset, bit = resolved

        # Reconstruct absolute address: look up the actual integer base
        # corresponding to the C++ constant name returned by _resolve_path.
        raw_base: int | None = None
        for t, v in base_values.items():
            if base_const_map.get(t) == base_const:
                raw_base = v
                break
        if raw_base is None:
            continue

        addr = raw_base + offset
        mask = 1 << bit
        gate_rows.append((en_path, addr, mask))
        seen_paths.add(en_path)

    # Sort by dotted path for stable, reproducible output
    gate_rows.sort(key=lambda r: r[0])

    # ── Render ────────────────────────────────────────────────────────────────
    vendor = device.identity.vendor
    family = device.identity.family
    dev    = device.identity.device

    lines: list[str] = [
        f"// rcc_gate_table.hpp",
        f"//",
        f"// {vendor}/{family}/{dev} — generated from {device.schema}",
        f"//",
        f"// Per-peripheral RCC enable-gate lookup table.",
        f"// This file is included by device/rcc_gate_table.hpp (alloy-hal) when",
        f"// ALLOY_DEVICE_RCC_TABLE_AVAILABLE is defined — do NOT include directly.",
        f"//",
        f"// Usage:",
        f"//   -DALLOY_DEVICE_RCC_TABLE_AVAILABLE=1",
        f'//   -DALLOY_DEVICE_RCC_TABLE_INCLUDE=\\"path/to/rcc_gate_table.hpp\\"',
        f"//",
        f"// Schema:     {device.schema}",
        f"// Provenance: {device.provenance.primary}",
        f"",
        f"#pragma once",
        f"#ifndef {guard}",
        f"#define {guard}",
        f"",
        f"#include <cstdint>",
        f"#include <string_view>",
        f"",
        f"// This file is included inside namespace alloy::device::detail by",
        f"// the base device/rcc_gate_table.hpp header. Do NOT re-open the namespace.",
        f"",
        f"// ============================================================================",
        f"// RCC enable-gate table — {len(gate_rows)} entries",
        f"// ============================================================================",
        f"// Each row: {{ dotted_path, absolute_register_address, single_bit_mask }}",
        f"// Addresses are absolute (clock-controller base + register offset).",
        f"",
    ]

    if gate_rows:
        lines += [
            "inline constexpr struct {",
            "    const char*   path;",
            "    std::uint32_t addr;",
            "    std::uint32_t mask;",
            "} kRccGatesData[] = {",
        ]
        for path, addr, mask in gate_rows:
            # Compute bit index for comment
            bit_idx = mask.bit_length() - 1
            lines.append(
                f'    {{ "{path}", 0x{addr:08X}u, (1u << {bit_idx:2d}u) }},'
            )
        lines.append("};")
    else:
        lines += [
            "// No RCC enable paths could be resolved for this device.",
            "inline constexpr struct {",
            "    const char*   path;",
            "    std::uint32_t addr;",
            "    std::uint32_t mask;",
            "} kRccGatesData[] = {};",
        ]

    lines += [
        "",
        "// ============================================================================",
        "// Compile-time lookup",
        "// ============================================================================",
        "",
        "/// Resolve a kRccEnable dotted path to its {{addr, mask}} gate at compile time.",
        "///",
        "/// Returns {{ 0u, 0u }} when the path is not in kRccGatesData.",
        "/// Drivers call this inside consteval clock_on() / clock_off().",
        "/// A result of {{ 0u, 0u }} causes a compile-time assert in the driver body.",
        "[[nodiscard]] consteval RccGate find_rcc_gate(const char* dotted_path) noexcept {",
        "    const std::string_view key{dotted_path};",
        "    for (const auto& g : kRccGatesData) {",
        "        if (std::string_view{g.path} == key) {",
        "            return { g.addr, g.mask };",
        "        }",
        "    }",
        "    // Path not found in the generated gate table for this device.",
        "    // The drivers assert gate.addr != 0 after this call.",
        "    return { 0u, 0u };",
        "}",
        "",
        f"#endif  // {guard}",
        "",
    ]

    return "\n".join(lines)
