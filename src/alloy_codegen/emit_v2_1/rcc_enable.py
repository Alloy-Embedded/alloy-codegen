"""Emit ``rcc_enable.hpp`` — per-peripheral typed clock-gate / reset helpers.

Generates direct-MMIO C++ template specialisations for every peripheral that
has a synthesised clock-enable path (``PeripheralRcc.en``) and/or a reset
path (``PeripheralRcc.rst``).

Supported families
------------------
* **STM32** (``rcc`` template) — set bit = enable; set bit = rst_assert.
* **RP2040** (``resets`` template) — INVERTED: clear bit = unreset/enable.
  The same register field doubles as both clock-gate and reset; releasing
  the reset also enables the peripheral.
* **Microchip SAMx** (``mclk``, ``pm``) — set bit = enable;
  no per-peripheral reset (use peripheral CTRLA.SWRST).
* **Microchip SAME70 / SAMV71** (``pmc``) — write-1-to-PCER = enable,
  write-1-to-PCDR = disable; no per-peripheral reset.
* **NXP iMXRT** (``ccm``) — set bit = enable (inline ``rcc:`` block,
  same read-modify-write semantics as STM32).
* **Generic fallback** — set bit = enable; clear bit = disable.

Lookup chain (per peripheral)
------------------------------
``en_path``  e.g. ``"rcc.apbenr2.usart1en"``
  1. Split on ``'.'`` → ``(tname, reg, field)``.
  2. ``device.templates[tname].registers[reg].offset`` → byte offset from
     the clock-control peripheral's base address.
  3. ``device.templates[tname].fields[f"{reg}.{field}"].bit`` → LSB of the
     control bit (single-bit fields use ``.bit``; multi-bit use ``.bits[0]``).
  4. Find clock-control base: first ``PeripheralInstance`` whose ``.template``
     equals ``tname``.

Generated API (per namespace ``alloy::<vendor>::<family>::<device>``)
----------------------------------------------------------------------
.. code-block:: cpp

    template <typename P> void clk_enable()    = delete;
    template <typename P> void clk_disable()   = delete;
    template <typename P> void rst_assert()    = delete;
    template <typename P> void rst_release()   = delete;
    template <typename P> void peripheral_on() = delete;

    // Specialisation for each peripheral that has an RCC path:
    template <> inline void clk_enable<usart1>()  noexcept { … }
    template <> inline void clk_disable<usart1>() noexcept { … }
    template <> inline void rst_assert<usart1>()  noexcept { … }
    template <> inline void rst_release<usart1>() noexcept { … }
    template <> inline void peripheral_on<usart1>() noexcept { … }
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised import SynthesisedDevice
from alloy_codegen.ir.v2_1 import CanonicalDevice
from alloy_codegen.ir.v2_1.peripherals import PeripheralRcc
from alloy_codegen.ir.v2_1.templates import Template, TemplateField


# ──────────────────────────────────────────────────────────────────────────────
# Template-family classification
# ──────────────────────────────────────────────────────────────────────────────

# Templates where clearing the bit = enable  (RP2040 RESETS register).
_INVERTED_ENABLE_TEMPLATES: frozenset[str] = frozenset({"resets"})

# Templates with no dedicated per-peripheral reset path.
# Peripherals on these buses reset via their own CTRLA.SWRST.
_NO_RESET_TEMPLATES: frozenset[str] = frozenset({"mclk", "pm", "pmc", "ccm"})

# Templates that use write-1-to-ENABLE / write-1-to-DISABLE semantics
# (separate registers, not read-modify-write).
_WRITE1_ENABLE_TEMPLATES: frozenset[str] = frozenset({"pmc"})


# ──────────────────────────────────────────────────────────────────────────────
# File-level helpers (shared with peripheral_id.py pattern)
# ──────────────────────────────────────────────────────────────────────────────


def _header_guard(device: CanonicalDevice) -> str:
    parts = (
        device.identity.vendor,
        device.identity.family,
        device.identity.device,
        "rcc_enable_hpp",
    )
    return "_".join(p.upper().replace("-", "_") for p in parts) + "_"


def _namespace_path(device: CanonicalDevice) -> str:
    v = device.identity.vendor.replace("-", "_").lower()
    f = device.identity.family.replace("-", "_").lower()
    d = device.identity.device.replace("-", "_").lower()
    return f"alloy::{v}::{f}::{d}"


# ──────────────────────────────────────────────────────────────────────────────
# RCC-path parsing
# ──────────────────────────────────────────────────────────────────────────────


def _parse_rcc_path(path: str) -> tuple[str, str, str] | None:
    """Split ``'template.register.field'`` → ``(tname, reg, field)``.

    Returns ``None`` for paths that don't have exactly three dot-separated
    components (e.g. two-part legacy paths or empty strings).
    """
    parts = path.split(".", 2)
    if len(parts) != 3:
        return None
    return parts[0], parts[1], parts[2]


def _parse_rcc_path_2part(
    path: str,
    templates: dict[str, "Template"],
    base_const_map: dict[str, str],
) -> tuple[str, str, str] | None:
    """Decode a 2-part uppercase path ``'TEMPLATE_REGISTER.FIELD'``.

    Some synthesisers (e.g. RP2040) emit paths like ``'RESETS_RESET.UART0'``
    instead of the canonical 3-part lowercase form.  This function recovers
    the (tname, reg, field) triple by trying all ``_``-split positions in the
    prefix and checking against the known template names.

    Tries longer template names first (greedy) so that ``IO_BANK0_CTRL``
    would correctly bind to template ``io_bank0`` rather than ``io``.
    """
    dot_parts = path.split(".", 1)
    if len(dot_parts) != 2:
        return None
    prefix_lower = dot_parts[0].lower()
    field = dot_parts[1].lower()
    sub_parts = prefix_lower.split("_")
    # Try longest template match first (greedy left-to-right).
    for split in range(len(sub_parts) - 1, 0, -1):
        tname = "_".join(sub_parts[:split])
        reg = "_".join(sub_parts[split:])
        if tname in templates and tname in base_const_map:
            return tname, reg, field
    return None


def _bit_lsb(field: TemplateField) -> int | None:
    """LSB of a template field (works for single-bit and multi-bit fields)."""
    if field.bit is not None:
        return field.bit
    if field.bits is not None:
        return field.bits[0]
    return None


def _find_ctrl_base(device: CanonicalDevice, tname: str) -> int | None:
    """Return the base address of the clock-control peripheral for ``tname``.

    Walks ``device.peripherals`` and returns the first peripheral whose
    ``.template`` attribute equals ``tname``.  Falls back to matching by
    peripheral ``.id`` (handles the degenerate case where a singleton
    peripheral is its own template controller).
    """
    for per in device.peripherals:
        if per.template == tname and per.base is not None:
            return per.base
    for per in device.peripherals:
        if per.id == tname and per.base is not None:
            return per.base
    return None


# ──────────────────────────────────────────────────────────────────────────────
# MMIO expression builders
# ──────────────────────────────────────────────────────────────────────────────


def _ptr_expr(base_const: str, offset: int) -> str:
    return f"reinterpret_cast<volatile std::uint32_t*>({base_const} + 0x{offset:04X}u)"


def _set_bit(base_const: str, offset: int, bit: int) -> str:
    return f"    *{_ptr_expr(base_const, offset)} |= (1u << {bit}u);"


def _clear_bit(base_const: str, offset: int, bit: int) -> str:
    return f"    *{_ptr_expr(base_const, offset)} &= ~(1u << {bit}u);"


def _write1(base_const: str, offset: int, bit: int) -> str:
    """Write-1 style (PMC PCER/PCDR): write the single bit, no read."""
    return f"    *{_ptr_expr(base_const, offset)} = (1u << {bit}u);"


# ──────────────────────────────────────────────────────────────────────────────
# PMC disable-register lookup (SAME70/SAMV71)
# ──────────────────────────────────────────────────────────────────────────────


def _pcer_to_pcdr(reg: str) -> str:
    """``'pmc_pcer0'`` → ``'pmc_pcdr0'``, ``'pmc_pcer1'`` → ``'pmc_pcdr1'``."""
    return reg.replace("pcer", "pcdr").replace("PCER", "PCDR")


# ──────────────────────────────────────────────────────────────────────────────
# Per-peripheral code generation
# ──────────────────────────────────────────────────────────────────────────────


def _resolve_path(
    path: str,
    templates: dict[str, Template],
    base_const_map: dict[str, str],
) -> tuple[str, str, str, int, int] | None:
    """Resolve a dotted RCC path to ``(tname, reg, base_const, offset, bit)``.

    Returns ``None`` when any lookup fails so the caller can skip gracefully.
    """
    parsed = _parse_rcc_path(path)
    if parsed is None:
        # Fallback: 2-part uppercase format e.g. 'RESETS_RESET.UART0'.
        parsed = _parse_rcc_path_2part(path, templates, base_const_map)
    if parsed is None:
        return None
    tname, reg, field = parsed
    if tname not in base_const_map:
        return None
    tpl = templates.get(tname)
    if tpl is None:
        return None
    field_key = f"{reg}.{field}"
    field_obj = tpl.fields.get(field_key)
    if field_obj is None:
        return None
    bit = _bit_lsb(field_obj)
    if bit is None:
        return None
    reg_obj = tpl.registers.get(reg)
    # When the register has no explicit entry in the template (e.g. RP2040's
    # RESETS.RESET at offset 0 is implied — only WDSEL and RESET_DONE are
    # enumerated), fall back to offset 0. This is safe because offset-0
    # is always the primary read-write control register of the peripheral.
    reg_offset = reg_obj.offset if reg_obj is not None else 0
    return (tname, reg, base_const_map[tname], reg_offset, bit)


def _emit_peripheral_block(
    per_id: str,
    eff_rcc: PeripheralRcc,
    templates: dict[str, Template],
    base_const_map: dict[str, str],
) -> list[str]:
    """Emit all five template specialisations for one peripheral.

    Returns an empty list when neither the enable nor reset path can be
    resolved to a concrete address+bit (missing template data, unknown
    template base, etc.).
    """
    safe_id = per_id.replace("-", "_")

    # ── Resolve enable path ─────────────────────────────────────────────────
    en_tname: str | None = None
    en_reg: str | None = None
    en_base: str | None = None
    en_offset: int | None = None
    en_bit: int | None = None

    if eff_rcc.en:
        resolved = _resolve_path(eff_rcc.en, templates, base_const_map)
        if resolved:
            en_tname, en_reg, en_base, en_offset, en_bit = resolved

    # ── Resolve reset path ──────────────────────────────────────────────────
    rst_tname: str | None = None
    rst_base: str | None = None
    rst_offset: int | None = None
    rst_bit: int | None = None

    if eff_rcc.rst:
        resolved = _resolve_path(eff_rcc.rst, templates, base_const_map)
        if resolved:
            rst_tname, _rst_reg, rst_base, rst_offset, rst_bit = resolved

    has_en  = en_base  is not None and en_offset  is not None and en_bit  is not None
    has_rst = rst_base is not None and rst_offset is not None and rst_bit is not None

    # Always-on peripherals (avr-da / nrf52 silicon-wide, plus
    # system-control peripherals on every other vendor — gpc, ccm,
    # mpu, nvic, system, pcr, …) have neither an enable bit nor a
    # reset bit.  Emit no-op specialisations so HAL drivers can call
    # ``clk_enable<P>()`` uniformly across vendors without
    # special-casing the always-on case at the call site.  Empty
    # ``inline`` bodies cost zero bytes once the compiler inlines.
    if not has_en and not has_rst:
        gate_model = (eff_rcc.extra or {}).get("gate_model")
        if gate_model != "always_on":
            return []
        out: list[str] = [
            "",
            f"// {safe_id} — always_on (no gate, no reset)",
            f"template <> inline void clk_enable<{safe_id}>()    noexcept {{}}",
            f"template <> inline void clk_disable<{safe_id}>()   noexcept {{}}",
            f"template <> inline void rst_assert<{safe_id}>()    noexcept {{}}",
            f"template <> inline void rst_release<{safe_id}>()   noexcept {{}}",
            f"template <> inline void peripheral_on<{safe_id}>() noexcept {{}}",
        ]
        return out

    # ── Per-family flags ─────────────────────────────────────────────────────
    tname_for_flags = en_tname or rst_tname or ""
    is_inverted = tname_for_flags in _INVERTED_ENABLE_TEMPLATES
    is_write1   = tname_for_flags in _WRITE1_ENABLE_TEMPLATES
    no_rst      = tname_for_flags in _NO_RESET_TEMPLATES

    out: list[str] = []

    # Comment block
    out.append("")
    out.append(f"// {safe_id}")
    if eff_rcc.en:
        out.append(f"//   clk : {eff_rcc.en}")
    if eff_rcc.rst:
        out.append(f"//   rst : {eff_rcc.rst}")

    # ── clk_enable ──────────────────────────────────────────────────────────
    if has_en:
        assert en_base is not None and en_offset is not None and en_bit is not None
        out.append(f"template <> inline void clk_enable<{safe_id}>() noexcept {{")
        if is_write1:
            out.append(_write1(en_base, en_offset, en_bit))
        elif is_inverted:
            out.append(_clear_bit(en_base, en_offset, en_bit))
        else:
            out.append(_set_bit(en_base, en_offset, en_bit))
        out.append("}")

    # ── clk_disable ─────────────────────────────────────────────────────────
    if has_en:
        assert en_base is not None and en_offset is not None and en_bit is not None
        out.append(f"template <> inline void clk_disable<{safe_id}>() noexcept {{")
        if is_write1:
            # PMC: write 1 to the matching PCDRn register (same bit position).
            pcdr_reg = _pcer_to_pcdr(en_reg or "")
            pcdr_tpl = templates.get(en_tname or "")
            pcdr_offset: int | None = None
            if pcdr_tpl and pcdr_reg:
                pcdr_reg_obj = pcdr_tpl.registers.get(pcdr_reg)
                if pcdr_reg_obj:
                    pcdr_offset = pcdr_reg_obj.offset
            if pcdr_offset is not None:
                out.append(_write1(en_base, pcdr_offset, en_bit))
            else:
                # PCDR register not in template — fall back to clear-bit.
                out.append(f"    // NOTE: PCDR register '{pcdr_reg}' not in template; using clear-bit fallback")
                out.append(_clear_bit(en_base, en_offset, en_bit))
        elif is_inverted:
            out.append(_set_bit(en_base, en_offset, en_bit))
        else:
            out.append(_clear_bit(en_base, en_offset, en_bit))
        out.append("}")

    # ── rst_assert ──────────────────────────────────────────────────────────
    if has_rst and not no_rst:
        assert rst_base is not None and rst_offset is not None and rst_bit is not None
        out.append(f"template <> inline void rst_assert<{safe_id}>() noexcept {{")
        # Asserting reset = putting the peripheral in reset state:
        #   STM32  — set bit in RSTRn.
        #   RP2040 — set bit in RESETS.RESET (same semantics).
        out.append(_set_bit(rst_base, rst_offset, rst_bit))
        out.append("}")

    # ── rst_release ─────────────────────────────────────────────────────────
    if has_rst and not no_rst:
        assert rst_base is not None and rst_offset is not None and rst_bit is not None
        out.append(f"template <> inline void rst_release<{safe_id}>() noexcept {{")
        out.append(_clear_bit(rst_base, rst_offset, rst_bit))
        out.append("}")

    # ── peripheral_on ───────────────────────────────────────────────────────
    out.append(f"template <> inline void peripheral_on<{safe_id}>() noexcept {{")
    if is_inverted and has_rst and not no_rst:
        # RP2040: rst_release == unreset == enable — one call does both.
        out.append(f"    rst_release<{safe_id}>();")
    elif has_en and has_rst and not no_rst:
        # STM32-style: enable the clock, then deassert reset.
        out.append(f"    clk_enable<{safe_id}>();")
        out.append(f"    rst_release<{safe_id}>();")
    elif has_en:
        # SAMx / PMC / CCM / peripherals without a reset bit.
        out.append(f"    clk_enable<{safe_id}>();")
    elif has_rst and not no_rst:
        # Reset-only peripheral (unusual but handle gracefully).
        out.append(f"    rst_release<{safe_id}>();")
    out.append("}")

    return out


# ──────────────────────────────────────────────────────────────────────────────
# Public emitter
# ──────────────────────────────────────────────────────────────────────────────


def emit_rcc_enable(
    device: CanonicalDevice,
    synthesised: SynthesisedDevice,
) -> str:
    """Render the ``rcc_enable.hpp`` header for ``device``."""

    guard = _header_guard(device)
    ns    = _namespace_path(device)
    templates: dict[str, Template] = device.templates or {}

    # ── Collect all template names that appear in any RCC path ──────────────
    tnames_needed: set[str] = set()
    for _per_id, rcc in synthesised.per_rcc_map.items():
        for path in (rcc.en, rcc.rst):
            if path:
                parsed = _parse_rcc_path(path)
                if parsed:
                    tnames_needed.add(parsed[0])
    # Also scan inline per.rcc entries not in per_rcc_map
    for per in device.peripherals:
        if per.rcc:
            for path in (per.rcc.en, per.rcc.rst):
                if path:
                    parsed = _parse_rcc_path(path)
                    if parsed:
                        tnames_needed.add(parsed[0])

    # ── Resolve base addresses for each needed template ──────────────────────
    # base_const_map: tname → C++ constant name emitted in the file header.
    base_const_map: dict[str, str] = {}
    base_values: dict[str, int] = {}  # tname → address value

    for tname in sorted(tnames_needed):
        base = _find_ctrl_base(device, tname)
        if base is not None:
            # Generate a readable constant name, e.g. "rcc" → "kRccBase"
            const_name = "k" + tname.replace("-", "_").capitalize() + "Base"
            base_const_map[tname] = const_name
            base_values[tname] = base

    # ── Collect peripherals to emit (prefer per_rcc_map, fall back inline) ──
    # Also include always_on entries — they have neither en nor rst path
    # but DO carry gate_model="always_on", so we still emit the no-op
    # specialisations (handled inside _emit_peripheral_block).  Without
    # this, HAL drivers can't call ``clk_enable<P>()`` portably on
    # AVR-Dx / NRF52 silicon.
    per_rcc_effective: dict[str, PeripheralRcc] = {}
    for per in device.peripherals:
        eff = synthesised.per_rcc_map.get(per.id) or per.rcc
        if not eff:
            continue
        if eff.en or eff.rst:
            per_rcc_effective[per.id] = eff
        elif (eff.extra or {}).get("gate_model") == "always_on":
            per_rcc_effective[per.id] = eff

    # ── Build the file ────────────────────────────────────────────────────────
    lines: list[str] = [
        f"/* rcc_enable.hpp",
        f" *",
        f" * {device.identity.vendor}/{device.identity.family}/{device.identity.device}"
        f" — generated from {device.schema}",
        f" *",
        f" * Per-peripheral clock-gate and reset helpers.",
        f" * All functions operate directly on MMIO — no runtime tables.",
        f" *",
        f" * IMPORTANT: include this header AFTER peripheral_traits.h so that",
        f" * the peripheral struct tags (usart1, gpioa, …) are already declared.",
        f" *",
        f" * Schema:     {device.schema}",
        f" * Provenance: {device.provenance.primary}",
        f" */",
        f"#pragma once",
        f"#ifndef {guard}",
        f"#define {guard}",
        f"",
        f"#include <cstdint>",
        f"",
        f"// peripheral struct tags must be visible before the specialisations.",
        f'#include "peripheral_traits.h"',
        f"",
        f"namespace {ns} {{",
    ]

    # ── Base-address constants ───────────────────────────────────────────────
    if base_values:
        lines.append("")
        lines.append("// ============================================================================")
        lines.append("// Clock-control peripheral base addresses")
        lines.append("// ============================================================================")
        for tname in sorted(base_values):
            const = base_const_map[tname]
            addr  = base_values[tname]
            lines.append(
                f"inline constexpr std::uintptr_t {const} = 0x{addr:08X}u;"
                f"  // {tname}"
            )

    # ── Primary (deleted) templates ──────────────────────────────────────────
    lines += [
        "",
        "// ============================================================================",
        "// Primary templates — only the explicit specialisations below are valid.",
        "// Calling any of these on an unsupported peripheral type is a compile error.",
        "// ``noexcept`` here matches the specialisation signature; clang flags",
        "// a mismatch otherwise (the per-specialisation body is also noexcept).",
        "// ============================================================================",
        "// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)",
        "template <typename P> void clk_enable()    noexcept = delete;  // NOLINT",
        "template <typename P> void clk_disable()   noexcept = delete;  // NOLINT",
        "template <typename P> void rst_assert()    noexcept = delete;  // NOLINT",
        "template <typename P> void rst_release()   noexcept = delete;  // NOLINT",
        "template <typename P> void peripheral_on() noexcept = delete;  // NOLINT",
        "",
        "// ============================================================================",
        "// Per-peripheral specialisations",
        "// ============================================================================",
    ]

    # ── Per-peripheral blocks ────────────────────────────────────────────────
    emitted = 0
    for per in device.peripherals:
        eff_rcc = per_rcc_effective.get(per.id)
        if eff_rcc is None:
            continue
        block = _emit_peripheral_block(
            per.id, eff_rcc, templates, base_const_map
        )
        if block:
            lines.extend(block)
            emitted += 1

    lines += [
        "",
        f"}}  // namespace {ns}",
        "",
        f"#endif  // {guard}",
        "",
    ]

    return "\n".join(lines)
