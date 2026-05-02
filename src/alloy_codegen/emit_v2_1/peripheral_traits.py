"""Emit ``peripheral_traits.h`` from a v2.1 :class:`CanonicalDevice`.

Produces one ``constexpr`` block per peripheral instance carrying the
facts that downstream alloy C++ traits / drivers consume at compile
time:

* ``kBaseAddress`` — silicon base address (always emitted).
* ``kIrqLines`` — array of IRQ vector numbers (compile-time list).
* ``kRccEnable`` / ``kRccReset`` — register references when set.
* ``kDmaTx`` / ``kDmaRx`` — typed DMA channel record when set.
* ``kIpVersion`` — string literal when ``ip_version`` is declared.

For each unique template referenced by the peripherals, also emit:

* ``namespace template::<ip_name>`` containing ``constexpr`` field
  names mapped to bit positions / bit ranges.  Codegen drivers
  flip bits by name (e.g. ``template::usart::cr1::ue.bit``).

The emitter is **device-agnostic**: it doesn't bake STM32 / ESP32 /
nRF specifics into the output.  Vendor-specific behaviour rides on
the ``ip_version`` string, which downstream traits dispatch on.

The output is a single C++ header file, header-guarded with the
device id and intended to be included by every device-specific
driver.
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised import SynthesisedDevice
from alloy_codegen.ir.v2_1 import (
    CanonicalDevice,
    PeripheralInstance,
    Template,
    TemplateField,
)


def _header_guard(device: CanonicalDevice) -> str:
    parts = (
        device.identity.vendor,
        device.identity.family,
        device.identity.device,
        "peripheral_traits_h",
    )
    return "_".join(p.upper().replace("-", "_") for p in parts) + "_"


def _hex_addr(value: int) -> str:
    return f"0x{value:08X}u"


def _emit_field_constexpr(name: str, field: TemplateField) -> list[str]:
    """One ``constexpr`` block per template field.  Single-bit fields
    expose ``.bit`` and ``.mask``; multi-bit fields add ``.lsb``,
    ``.msb``, ``.width``, ``.mask`` plus the ``.encoding`` enum when
    present."""
    safe = name.replace(".", "_")
    out: list[str] = [f"  namespace {safe} {{"]
    if field.bit is not None:
        out.append(f"    inline constexpr unsigned bit  = {field.bit};")
        out.append(f"    inline constexpr uint32_t mask = (1u << {field.bit});")
    elif field.bits is not None:
        lsb, msb = field.bits
        width = msb - lsb + 1
        mask_value = ((1 << width) - 1) << lsb
        out.append(f"    inline constexpr unsigned lsb   = {lsb};")
        out.append(f"    inline constexpr unsigned msb   = {msb};")
        out.append(f"    inline constexpr unsigned width = {width};")
        out.append(f"    inline constexpr uint32_t mask  = 0x{mask_value:08X}u;")
    if field.enum:
        out.append("    enum class value : unsigned {")
        for k, v in field.enum.items():
            # YAML parses `1: 0` and `"1": 0` differently — the first
            # gives us an int, the second a str.  Normalise to str
            # so the C++ enumerator name is well-formed in both cases.
            key_str = str(k)
            sanitised = (
                key_str.replace("-", "_")
                       .replace(".", "_")
                       .replace("/", "_")
                       .replace(" ", "_")
            )
            # Numeric / unit-suffix names get prefixed with `e` so the
            # enumerator is a valid C++ identifier.
            if not sanitised[:1].isalpha() and sanitised[:1] != "_":
                sanitised = f"e{sanitised}"
            out.append(f"      {sanitised} = {v},")
        out.append("    };")
    out.append("  }")
    return out


def _emit_template_namespace(ip_name: str, template: Template) -> list[str]:
    safe_ns = ip_name.replace("-", "_")
    out: list[str] = [
        f"namespace template_{safe_ns} {{",
    ]
    if template.capabilities or template.capabilities_extra:
        caps = list(template.capabilities) + list(template.capabilities_extra)
        out.append(
            f"  // capabilities: {', '.join(caps)}"
        )
    if template.max_clock:
        out.append(f"  // max_clock: {template.max_clock}")

    # Per-register offset constants.
    if template.registers:
        out.append("")
        out.append("  // Register offsets (bytes from peripheral base).")
        for reg_name, reg in sorted(template.registers.items()):
            out.append(
                f"  inline constexpr uint32_t reg_{reg_name}_offset = "
                f"0x{reg.offset:04X}u;"
            )

    # Per-field bit / range / enum.
    if template.fields:
        out.append("")
        out.append("  // Bit positions of fields the driver flips.")
        for field_name, field in sorted(template.fields.items()):
            out.extend(_emit_field_constexpr(field_name, field))

    out.append("}  // namespace template_" + safe_ns)
    return out


def _emit_peripheral_instance(per: PeripheralInstance, syn: SynthesisedDevice) -> list[str]:
    safe_id = per.id.replace("-", "_")
    out = [
        f"namespace {safe_id} {{",
        f"  inline constexpr const char * kName       = \"{per.id}\";",
        f"  inline constexpr const char * kTemplate   = \"{per.template}\";",
    ]
    if per.ip_version:
        out.append(f"  inline constexpr const char * kIpVersion  = \"{per.ip_version}\";")
    if per.base is not None:
        out.append(f"  inline constexpr uintptr_t   kBaseAddress = {_hex_addr(per.base)};")
    if per.bus:
        out.append(f"  inline constexpr const char * kBus        = \"{per.bus}\";")
    if per.clock_source:
        out.append(f"  inline constexpr const char * kClockSrc   = \"{per.clock_source}\";")
    if per.max_clock_override:
        out.append(f"  inline constexpr const char * kMaxClock   = \"{per.max_clock_override}\";")

    # IRQs
    if per.irq:
        irq_lines = [str(i.num) for i in per.irq]
        irq_names = [f"\"{i.name}\"" for i in per.irq]
        out.append(
            f"  inline constexpr unsigned    kIrqLines[]  = "
            f"{{ {', '.join(irq_lines)} }};"
        )
        out.append(
            f"  inline constexpr const char *kIrqNames[]  = "
            f"{{ {', '.join(irq_names)} }};"
        )
        out.append(f"  inline constexpr unsigned    kIrqCount    = {len(per.irq)};")

    # RCC
    if per.rcc and per.rcc.en:
        out.append(f"  inline constexpr const char * kRccEnable  = \"{per.rcc.en}\";")
    if per.rcc and per.rcc.rst:
        out.append(f"  inline constexpr const char * kRccReset   = \"{per.rcc.rst}\";")

    # DMA
    if per.dma and per.dma.tx:
        out.append("  // DMA TX:")
        if per.dma.tx.ctrl is not None:
            out.append(f"  inline constexpr const char * kDmaTxCtrl = \"{per.dma.tx.ctrl}\";")
        if per.dma.tx.channel is not None:
            out.append(f"  inline constexpr unsigned    kDmaTxCh   = {per.dma.tx.channel};")
        if per.dma.tx.dreq is not None:
            out.append(f"  inline constexpr unsigned    kDmaTxDreq = {per.dma.tx.dreq};")
    if per.dma and per.dma.rx:
        out.append("  // DMA RX:")
        if per.dma.rx.ctrl is not None:
            out.append(f"  inline constexpr const char * kDmaRxCtrl = \"{per.dma.rx.ctrl}\";")
        if per.dma.rx.channel is not None:
            out.append(f"  inline constexpr unsigned    kDmaRxCh   = {per.dma.rx.channel};")
        if per.dma.rx.dreq is not None:
            out.append(f"  inline constexpr unsigned    kDmaRxDreq = {per.dma.rx.dreq};")

    # Mutex group (Nordic shared-IRQ peripherals)
    if per.mutex_group:
        out.append(f"  inline constexpr const char * kMutexGroup = \"{per.mutex_group}\";")

    # Synthesised endpoints (signal names this peripheral exposes)
    endpoints = [e for e in syn.signal_endpoints if e.peripheral == per.id]
    if endpoints:
        signal_names = [f"\"{e.signal}\"" for e in endpoints]
        out.append(
            f"  inline constexpr const char *kSignals[]   = "
            f"{{ {', '.join(signal_names)} }};"
        )
        out.append(f"  inline constexpr unsigned    kSignalCount = {len(endpoints)};")

    out.append(f"}}  // namespace {safe_id}")
    return out


def emit_peripheral_traits(
    device: CanonicalDevice,
    synthesised: SynthesisedDevice,
) -> str:
    """Render the peripheral-traits header for ``device``."""
    guard = _header_guard(device)
    lines: list[str] = [
        f"// peripheral_traits.h",
        f"//",
        f"// {device.identity.vendor}/{device.identity.family}/{device.identity.device}"
        f" — generated from {device.schema}",
        f"//",
        f"// Provenance: {device.provenance.primary}",
        f"// Authored:   {device.provenance.authored}",
        f"//",
        f"// Each peripheral instance lives in its own ``namespace`` carrying",
        f"// ``constexpr`` traits.  Each unique IP template lives in",
        f"// ``namespace template_<ip>`` carrying register offsets + bit",
        f"// positions of every named field.",
        f"",
        f"#ifndef {guard}",
        f"#define {guard}",
        f"",
        f"#include <cstddef>",
        f"#include <cstdint>",
        f"",
        f"namespace alloy::{device.identity.vendor}::{device.identity.family}"
        f"::{device.identity.device.replace('-', '_')} {{",
        f"",
    ]

    # Sorted templates first — they're referenced by per-instance namespaces.
    if device.templates:
        for ip_name, template in sorted(device.templates.items()):
            lines.extend(_emit_template_namespace(ip_name, template))
            lines.append("")

    # Per-instance namespaces.
    for per in device.peripherals:
        lines.extend(_emit_peripheral_instance(per, synthesised))
        lines.append("")

    lines.append(f"}}  // namespace alloy::{device.identity.vendor}::"
                 f"{device.identity.family}::"
                 f"{device.identity.device.replace('-', '_')}")
    lines.append("")
    lines.append(f"#endif  // {guard}")
    lines.append("")
    return "\n".join(lines)
