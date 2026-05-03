"""Shared dotted-path → (absolute_address, mask, lsb, width) resolver.

Both ``rcc_enable.py`` and ``peripheral_traits.py`` need to convert
the canonical dotted RCC paths (``"rcc.apbenr1.lpuart1en"``,
``"CCM_CCGR5.CG12"``, etc.) into concrete numeric tuples at codegen
time.  This module centralises the logic so the two emitters cannot
drift.

The dotted path comes from
:mod:`alloy_codegen.ir.synthesised.builder._build_rcc_lookup` and
follows two formats:

* **3-part lowercase** (canonical) — ``"<template>.<register>.<field>"``,
  e.g. ``"rcc.apbenr1.lpuart1en"``, ``"mclk.apbamask.sercom0_"``,
  ``"ccm.ccgr5.cg12"``.
* **2-part UPPER** (legacy inline YAML on iMXRT / RP2040) —
  ``"<TEMPLATE_REGISTER>.<FIELD>"``, e.g. ``"CCM_CCGR5.CG12"``,
  ``"RESETS_RESET.UART0"``.  Recovered by trying ``_``-split
  positions against the known template names.
"""

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.v2_1 import CanonicalDevice, Template, TemplateField


@dataclass(frozen=True, slots=True)
class ResolvedRccField:
    """A dotted RCC path resolved to its numeric components.

    ``addr`` is the absolute MMIO address (clock-controller base +
    register offset).  ``mask`` is the bit-mask (single-bit for
    enable/reset; multi-bit for kernel-clock muxes).  ``lsb`` and
    ``width`` are the field's bit position and bit count — useful for
    kernel-clock-mux selectors that need to write a typed value into
    a sub-field, not just toggle a bit.
    """

    template: str          # e.g. "rcc"
    register: str          # e.g. "apbenr1"
    field: str             # e.g. "lpuart1en"
    addr: int              # absolute address (controller base + reg offset)
    mask: int              # ``(1 << lsb)`` for single-bit, range mask for multi-bit
    lsb: int               # bit position of the field's least-significant bit
    width: int             # field width in bits (1 for single-bit gates)


def _bit_lsb_and_width(field: TemplateField) -> tuple[int, int] | None:
    """Pull (lsb, width) out of a TemplateField in either single-bit
    or multi-bit form.
    """
    if field.bit is not None:
        return field.bit, 1
    if field.bits is not None:
        lo, hi = field.bits
        return lo, hi - lo + 1
    return None


def _find_ctrl_base(device: CanonicalDevice, tname: str) -> int | None:
    """Return the base address of the clock-control peripheral for
    ``tname``.

    Walks ``device.peripherals`` and returns the first peripheral
    whose ``.template`` attribute equals ``tname``.  Falls back to
    matching by peripheral ``.id`` (handles the degenerate case where
    a singleton peripheral is its own template controller).
    """
    for per in device.peripherals:
        if per.template == tname and per.base is not None:
            return per.base
    for per in device.peripherals:
        if per.id == tname and per.base is not None:
            return per.base
    return None


def _split_array_register(
    reg_name: str, template: Template
) -> tuple[str, int] | tuple[None, None]:
    """Detect a synthesised array-register reference (``pchctrl7``,
    ``ccgr5``, ``perip_clk_en0``) and return ``(base_register_name,
    index)``.

    The IR's :class:`Template` only models the *generic* register
    (``pchctrl``) with one offset; vendor synthesisers emit the
    indexed name (``pchctrl7``) as the gate-path slug.  We resolve
    the index here so callers don't have to special-case each vendor.

    The match rule: ``reg_name`` must end in ``\\d+``, and stripping
    the trailing digits MUST yield a register name actually present
    in the template.  Otherwise we return ``(None, None)`` and the
    caller proceeds with the original name (which handles registers
    whose name legitimately ends in a digit, e.g. ``perip_clk_en0``
    on ESP32-C3 — both ``perip_clk_en0`` and ``perip_clk_en1`` exist
    as real distinct registers, so the strip-digits heuristic
    would not find ``perip_clk_en`` in the template's register map
    and we keep the original).
    """
    import re as _re

    m = _re.match(r"^(.+?)(\d+)$", reg_name)
    if m is None:
        return None, None
    base, idx_str = m.group(1), m.group(2)
    if base not in template.registers:
        return None, None
    if reg_name in template.registers:
        # Both ``foo`` and ``foo7`` exist — the original is the
        # canonical match, no array indexing needed.
        return None, None
    return base, int(idx_str)


def _parse_three_part(path: str) -> tuple[str, str, str] | None:
    """``"rcc.apbenr1.lpuart1en"`` → ``("rcc", "apbenr1", "lpuart1en")``."""
    parts = path.split(".", 2)
    if len(parts) != 3:
        return None
    return parts[0], parts[1], parts[2]


def _parse_two_part_upper(
    path: str, templates: dict[str, Template]
) -> tuple[str, str, str] | None:
    """Recover ``(tname, reg, field)`` from legacy UPPER form
    ``"TEMPLATE_REGISTER.FIELD"``.

    Tries longer template names first (greedy) so that
    ``IO_BANK0_CTRL`` correctly binds to template ``io_bank0`` rather
    than ``io``.
    """
    dot_parts = path.split(".", 1)
    if len(dot_parts) != 2:
        return None
    prefix_lower = dot_parts[0].lower()
    field = dot_parts[1].lower()
    sub_parts = prefix_lower.split("_")
    for split in range(len(sub_parts) - 1, 0, -1):
        tname = "_".join(sub_parts[:split])
        reg = "_".join(sub_parts[split:])
        if tname in templates:
            return tname, reg, field
    return None


def resolve_rcc_path(
    path: str,
    device: CanonicalDevice,
) -> ResolvedRccField | None:
    """Resolve any dotted RCC path to its absolute (addr, mask, lsb,
    width) tuple.  Returns ``None`` when the lookup fails (e.g. the
    template wasn't loaded, or the field name doesn't appear in the
    template's field map).

    Design choice: the function takes the *whole device* rather than
    pre-built ``base_const_map`` / ``templates`` dicts so callers can
    use it with a single import.  Internal lookups stay O(1) thanks
    to the dict membership tests.
    """
    if not path:
        return None
    templates = device.templates or {}

    parsed = _parse_three_part(path)
    if parsed is None:
        parsed = _parse_two_part_upper(path, templates)
    if parsed is None:
        return None

    tname, reg, field = parsed
    tpl = templates.get(tname)
    if tpl is None:
        return None

    # Array-register fallback: the synthesiser emits ``pchctrl7.gen``
    # for SAMD51 GCLK channel 7, but the template carries the
    # generic ``pchctrl.gen`` (one entry, register array stride is
    # 4 bytes per channel).  Detect ``<reg_base><digits>``, compute
    # ``base_offset + index * 4`` and look up the field on the base
    # register name.
    array_reg_base, array_index = _split_array_register(reg, tpl)
    if array_reg_base is not None and array_index is not None:
        field_key = f"{array_reg_base}.{field}"
        reg_lookup = array_reg_base
        array_byte_offset = array_index * 4
    else:
        field_key = f"{reg}.{field}"
        reg_lookup = reg
        array_byte_offset = 0

    field_obj = tpl.fields.get(field_key)
    if field_obj is None:
        return None

    bit_info = _bit_lsb_and_width(field_obj)
    if bit_info is None:
        return None
    lsb, width = bit_info

    reg_obj = tpl.registers.get(reg_lookup)
    # When the register has no explicit entry in the template
    # (e.g. RP2040's RESETS.RESET at offset 0 is implied — only
    # WDSEL and RESET_DONE are enumerated), fall back to offset 0.
    # This is safe because offset-0 is always the primary read-write
    # control register of the peripheral.
    reg_offset = (reg_obj.offset if reg_obj is not None else 0) + array_byte_offset

    base = _find_ctrl_base(device, tname)
    if base is None:
        return None

    abs_addr = base + reg_offset
    # Multi-bit field mask spans the whole field; single-bit collapses
    # to ``(1 << lsb)``.
    mask = ((1 << width) - 1) << lsb

    return ResolvedRccField(
        template=tname,
        register=reg,
        field=field,
        addr=abs_addr,
        mask=mask,
        lsb=lsb,
        width=width,
    )


__all__ = [
    "ResolvedRccField",
    "resolve_rcc_path",
]
