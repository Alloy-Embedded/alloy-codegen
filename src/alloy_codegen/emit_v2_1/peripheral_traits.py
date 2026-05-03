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

import re

from alloy_codegen.emit_v2_1._rcc_path_resolver import resolve_rcc_path
from alloy_codegen.emit_v2_1.trait_classifier import (
    InstanceTraitKind,
    TemplateTraitKind,
    classify_instance,
    classify_template,
)
from alloy_codegen.ir.synthesised import SynthesisedDevice
from alloy_codegen.ir.v2_1 import (
    CanonicalDevice,
    PeripheralInstance,
    Template,
    TemplateField,
)


# Map the synthesiser's bus tag strings to the Bus enum enumerator names
# emitted into rcc_traits.hpp.  The synthesiser writes uppercase tags like
# "APB1", "DPORT", "CCGR" — these resolve to lowercase enumerators.  Keys
# are matched case-insensitively, so inline YAML values (`bus: "APB1"`)
# and synthesised tags (`extra["bus"] = "APB1"`) both land in the same
# enumerator regardless of case.
_BUS_TAG_TO_ENUM: dict[str, str] = {
    "apb":    "apb",
    "apb1":   "apb1",
    "apb2":   "apb2",
    "apb3":   "apb3",
    "apb4":   "apb4",
    "ahb":    "ahb",
    "ahb1":   "ahb1",
    "ahb2":   "ahb2",
    "ahb3":   "ahb3",
    "ahb4":   "ahb4",
    "dport":  "dport",
    "system": "system",
    "pcr":    "pcr",
    "ccgr":   "ccgr",
    "mclk":   "mclk",
    "pm":     "pm",
    "pmc":    "pmc",
    "resets": "resets",
}


def _bus_enum_for(tag: str | None) -> str | None:
    """Return the ``Bus::xxx`` enumerator name for a synthesiser tag,
    or ``None`` when the tag is empty / unknown (caller skips emission).
    """
    if not tag:
        return None
    return _BUS_TAG_TO_ENUM.get(tag.lower())


# C++20 reserved keywords that occasionally show up as enum entry
# names in vendor data (Microchip ATDF uses ``default`` on AVR-Dx
# CLKCTRL fields, ``class`` on a few Atmel SAM IPs, etc.).
# Centralised so both _emit_field_constexpr and any future emitter
# can sanitise consistently.
_CPP_KEYWORDS: frozenset[str] = frozenset({
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand",
    "bitor", "bool", "break", "case", "catch", "char", "char8_t",
    "char16_t", "char32_t", "class", "compl", "concept", "const",
    "consteval", "constexpr", "constinit", "const_cast", "continue",
    "co_await", "co_return", "co_yield", "decltype", "default",
    "delete", "do", "double", "dynamic_cast", "else", "enum",
    "explicit", "export", "extern", "false", "float", "for",
    "friend", "goto", "if", "inline", "int", "long", "mutable",
    "namespace", "new", "noexcept", "not", "not_eq", "nullptr",
    "operator", "or", "or_eq", "private", "protected", "public",
    "register", "reinterpret_cast", "requires", "return", "short",
    "signed", "sizeof", "static", "static_assert", "static_cast",
    "struct", "switch", "template", "this", "thread_local", "throw",
    "true", "try", "typedef", "typeid", "typename", "union",
    "unsigned", "using", "virtual", "void", "volatile", "wchar_t",
    "while", "xor", "xor_eq",
})


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
                key_str.replace("-", "_").replace(".", "_").replace("/", "_").replace(" ", "_")
            )
            # Numeric / unit-suffix names get prefixed with `e` so the
            # enumerator is a valid C++ identifier.
            if not sanitised[:1].isalpha() and sanitised[:1] != "_":
                sanitised = f"e{sanitised}"
            # C++ reserved keywords (default / class / new / delete /
            # …) are valid YAML strings but not valid identifiers.
            # Suffix with ``_`` to disambiguate.  Microchip ATDF
            # routinely uses ``default`` as an enum entry name on
            # AVR-Dx CLKCTRL fields.
            if sanitised in _CPP_KEYWORDS:
                sanitised = f"{sanitised}_"
            out.append(f"      {sanitised} = {v},")
        out.append("    };")
    out.append("  }")
    return out


def _emit_timer_template_traits(template: Template) -> list[str]:
    """Emit the timer matrix sub-namespace inside a template.

    Walks the populated subset of ``trigger_sources``,
    ``master_outputs``, ``waveform_modes``, ``deadtime_options``,
    ``break_inputs``, and ``counter_bits_options`` and emits one
    ``inline constexpr`` block per field.  Each entry is
    integral / typed — no ``const char *`` semantic strings.
    """
    out: list[str] = []
    if template.trigger_sources:
        out.append("")
        out.append("  // Timer matrix: trigger sources (TS encoding).")
        out.append("  namespace trigger_sources {")
        for name, enc in sorted(template.trigger_sources.items()):
            sanitised = name.replace("-", "_").replace(".", "_")
            out.append(f"    inline constexpr unsigned {sanitised} = {enc};")
        out.append(f"    inline constexpr unsigned kCount = {len(template.trigger_sources)};")
        out.append("  }")
    if template.master_outputs:
        out.append("")
        out.append("  // Timer matrix: master outputs (MMS encoding).")
        out.append("  namespace master_outputs {")
        for name, enc in sorted(template.master_outputs.items()):
            sanitised = name.replace("-", "_").replace(".", "_")
            out.append(f"    inline constexpr unsigned {sanitised} = {enc};")
        out.append(f"    inline constexpr unsigned kCount = {len(template.master_outputs)};")
        out.append("  }")
    if template.waveform_modes:
        out.append("")
        out.append("  // Timer matrix: waveform / output-compare modes.")
        out.append("  namespace waveform_modes {")
        for name, enc in sorted(template.waveform_modes.items()):
            sanitised = name.replace("-", "_").replace(".", "_")
            out.append(f"    inline constexpr unsigned {sanitised} = {enc};")
        out.append(f"    inline constexpr unsigned kCount = {len(template.waveform_modes)};")
        out.append("  }")
    if template.deadtime_options:
        out.append("")
        out.append("  // Timer matrix: dead-time generator options.")
        out.append("  namespace deadtime_options {")
        out.append("    struct option {")
        out.append("      unsigned dtg_prescaler;   // DTG[7:5] selector")
        out.append("      unsigned count_bits;      // bits used inside DTG")
        out.append("      unsigned max_ns;          // max insertable dead-time at ref clock")
        out.append("    };")
        out.append("    inline constexpr option kRows[] = {")
        for entry in template.deadtime_options:
            dtg = entry.get("dtg_prescaler", 0)
            cb = entry.get("count_bits", 0)
            mx = entry.get("max_ns", 0)
            out.append(f"      {{ {dtg}, {cb}, {mx} }},")
        out.append("    };")
        out.append(f"    inline constexpr unsigned kCount = {len(template.deadtime_options)};")
        out.append("  }")
    if template.break_inputs:
        out.append("")
        out.append("  // Timer matrix: break-input lines (BKIN, BKIN2, ...).")
        out.append("  namespace break_inputs {")
        for idx, name in enumerate(template.break_inputs):
            sanitised = name.replace("-", "_").replace(".", "_")
            out.append(f"    inline constexpr unsigned {sanitised} = {idx};")
        out.append(f"    inline constexpr unsigned kCount = {len(template.break_inputs)};")
        out.append("  }")
    if template.counter_bits_options:
        out.append("")
        out.append("  // Timer matrix: supported counter widths (in bits).")
        out.append("  namespace counter_bits_options {")
        opts = ", ".join(str(b) for b in template.counter_bits_options)
        out.append(f"    inline constexpr unsigned kRows[] = {{ {opts} }};")
        out.append(f"    inline constexpr unsigned kCount = {len(template.counter_bits_options)};")
        out.append("  }")
    return out


_PLACEHOLDER_RE = re.compile(r"%[sdN]|<n>|\{n\}|\$\{")


def _is_template_placeholder(name: str) -> bool:
    """Return True if the register/field name carries an unresolved
    template placeholder (``%s``, ``<n>``, ``${...}``).

    Some Espressif YAML rows ship with un-expanded channel-index
    placeholders (``in_conf0_ch%s``) that should be channel-numbered
    at IR-load time but currently aren't.  Emitting the literal
    ``%s`` produces broken C++ identifiers, so we skip those rows
    here and let the upstream YAML fix-up land separately.  This
    keeps the alloy-codegen compile gate green even with the data
    debt in place.
    """
    return bool(_PLACEHOLDER_RE.search(name))


def _emit_template_namespace(ip_name: str, template: Template) -> list[str]:
    safe_ns = ip_name.replace("-", "_")
    out: list[str] = [
        f"namespace template_{safe_ns} {{",
    ]
    if template.capabilities or template.capabilities_extra:
        caps = list(template.capabilities) + list(template.capabilities_extra)
        out.append(f"  // capabilities: {', '.join(caps)}")
    if template.max_clock:
        out.append(f"  // max_clock: {template.max_clock}")

    # Per-register offset constants.  Skip names with unresolved
    # template placeholders (``%s``, ``<n>``, etc.) — those are
    # upstream YAML data-debt that doesn't yield valid C++.
    if template.registers:
        out.append("")
        out.append("  // Register offsets (bytes from peripheral base).")
        for reg_name, reg in sorted(template.registers.items()):
            if _is_template_placeholder(reg_name):
                continue
            out.append(f"  inline constexpr uint32_t reg_{reg_name}_offset = 0x{reg.offset:04X}u;")

    # Per-field bit / range / enum.
    if template.fields:
        out.append("")
        out.append("  // Bit positions of fields the driver flips.")
        for field_name, field in sorted(template.fields.items()):
            if _is_template_placeholder(field_name):
                continue
            out.extend(_emit_field_constexpr(field_name, field))

    # Optional timer-matrix block (deadtime / triggers / break inputs).
    if classify_template(template) == TemplateTraitKind.TIMER:
        out.extend(_emit_timer_template_traits(template))

    out.append("}  // namespace template_" + safe_ns)
    return out


def _emit_calibration_data_point(name: str, point: object) -> list[str]:
    """Emit one ``CalibrationDataPoint`` as a typed nested struct."""
    from alloy_codegen.ir.v2_1 import CalibrationDataPoint

    if not isinstance(point, CalibrationDataPoint):
        return []
    out = [f"    struct {name} {{"]
    out.append(f"      static constexpr uintptr_t kRomAddr   = 0x{point.rom_addr:08X}u;")
    out.append(f"      static constexpr unsigned  kSizeBits  = {point.size_bits};")
    if point.nominal_mv is not None:
        out.append(f"      static constexpr unsigned  kNominalMv = {int(point.nominal_mv)};")
    if point.temp_celsius is not None:
        out.append(f"      static constexpr int       kTempC     = {int(point.temp_celsius)};")
    if point.vdda_calibration is not None:
        out.append(f"      static constexpr unsigned  kVddaCalMv = {int(point.vdda_calibration)};")
    out.append("    };")
    return out


def _emit_adc_instance_traits(per: PeripheralInstance) -> list[str]:
    """Emit ADC-only nested structs inside a peripheral struct.

    Two nested types:
    * ``calibration::{vrefint, ts_cal_low, ts_cal_high}`` — typed
      addresses + nominal / temperature constants from the IR's
      :class:`AdcCalibration`.
    * ``external_triggers::{regular, injected}`` — typed rows.
    """
    out: list[str] = []
    cal = per.calibration
    if cal is not None:
        out.append("")
        out.append("  // ADC factory calibration (read at boot to compute Vdda + chip temp).")
        out.append("  struct calibration {")
        if cal.vrefint is not None:
            out.extend(_emit_calibration_data_point("vrefint", cal.vrefint))
        if cal.ts_cal_low is not None:
            out.extend(_emit_calibration_data_point("ts_cal_low", cal.ts_cal_low))
        if cal.ts_cal_high is not None:
            out.extend(_emit_calibration_data_point("ts_cal_high", cal.ts_cal_high))
        if cal.ts_slope_uv_per_c is not None:
            out.append(
                f"    static constexpr unsigned kTsSlopeUvPerC = {int(cal.ts_slope_uv_per_c)};"
            )
        out.append("  };")

    if per.external_triggers:
        out.append("")
        out.append("  // ADC external-trigger map per kind (regular / injected).")
        out.append("  struct external_triggers {")
        for kind, triggers in sorted(per.external_triggers.items()):
            sanitised_kind = kind.replace("-", "_").replace(".", "_")
            out.append(f"    struct {sanitised_kind} {{")
            out.append("      struct row {")
            out.append("        const char *source;")
            out.append("        int         extsel;    // -1 = not encoded")
            out.append("        int         jextsel;   // -1 = not encoded")
            out.append('        const char *polarity;  // "rising" | "falling" | "both"')
            out.append("      };")
            out.append("      static constexpr row kRows[] = {")
            for trig in triggers:
                ext = trig.extsel if trig.extsel is not None else -1
                jext = trig.jextsel if trig.jextsel is not None else -1
                pol = trig.polarity or ""
                out.append(f'        {{ "{trig.source}", {ext}, {jext}, "{pol}" }},')
            out.append("      };")
            out.append(f"      static constexpr unsigned kCount = {len(triggers)};")
            out.append("    };")
        out.append("  };")
    return out


def _emit_i2c_instance_traits(per: PeripheralInstance) -> list[str]:
    """Emit I²C-only nested struct inside a peripheral struct.

    ``timing_presets::kRows`` — every populated ``I2cTimingPreset``
    (TIMINGR for F0/G0/G4/H7; CCR + TRISE for F1/F2/F4).
    """
    if not per.timing_presets:
        return []
    out = ["", "  // I²C pre-computed timing presets (one per supported speed)."]
    out.append("  struct timing_presets {")
    out.append("    struct row {")
    out.append('      const char *speed;         // e.g. "100kHz" / "400kHz" / "1MHz"')
    out.append('      const char *source_clock;  // e.g. "pclk1"')
    out.append("      unsigned    timingr;       // 0 when not encoded for this row")
    out.append("      unsigned    ccr;           // 0 when not encoded for this row")
    out.append("      unsigned    trise;         // 0 when not encoded for this row")
    out.append("    };")
    out.append("    static constexpr row kRows[] = {")
    for tp in per.timing_presets:
        timingr = tp.timingr if tp.timingr is not None else 0
        ccr = tp.ccr if tp.ccr is not None else 0
        trise = tp.trise if tp.trise is not None else 0
        out.append(
            f'      {{ "{tp.speed}", "{tp.source_clock}", '
            f"0x{timingr:08X}u, 0x{ccr:08X}u, 0x{trise:08X}u }},"
        )
    out.append("    };")
    out.append(f"    static constexpr unsigned kCount = {len(per.timing_presets)};")
    out.append("  };")
    return out


def _instance_number(per_id: str) -> int | None:
    """Extract trailing digit(s) from a peripheral id (e.g. 'usart1' → 1)."""
    m = re.search(r"(\d+)$", per_id)
    return int(m.group(1)) if m else None


def _emit_peripheral_instance(
    per: PeripheralInstance,
    syn: SynthesisedDevice,
    device: CanonicalDevice,
) -> list[str]:
    """Emit one peripheral instance as a plain struct.

    Design: each peripheral IS a type.  HAL drivers can use
    ``template <typename P>`` with concept constraints directly on
    the struct's static constexpr members — no ``PeripheralInstanceTraits``
    adapter needed.

    Example usage::

        #include "peripheral_traits.h"
        using ns = alloy::st::stm32g0::stm32g071rb;

        template <typename P>
        void enable_clock();  // specialised via concept

        enable_clock<ns::usart1>();
    """
    safe_id = per.id.replace("-", "_")
    out = [
        f"struct {safe_id} {{",
        f'  static constexpr const char * kName       = "{per.id}";',
        f'  static constexpr const char * kTemplate   = "{per.template}";',
    ]

    # Instance number (1 for usart1, 2 for usart2, None for singletons)
    inst_num = _instance_number(per.id)
    if inst_num is not None:
        out.append(f"  static constexpr unsigned    kInstance    = {inst_num}u;")

    if per.ip_version:
        out.append(f'  static constexpr const char * kIpVersion  = "{per.ip_version}";')
    if per.base is not None:
        out.append(f"  static constexpr uintptr_t   kBaseAddress = {_hex_addr(per.base)};")

    # Bus domain — typed enum (replaces the v0.3.x ``kBus`` string).
    # Source-of-truth precedence: inline YAML ``per.bus`` first, then
    # synthesised ``extra["bus"]``.  Unknown tags drop the line so the
    # struct doesn't carry a sentinel value HAL would have to filter.
    bus_tag = per.bus
    if not bus_tag:
        syn_rcc = syn.per_rcc_map.get(per.id)
        if syn_rcc:
            bus_tag = str(syn_rcc.extra.get("bus", "")) or None
    bus_enum = _bus_enum_for(bus_tag)
    if bus_enum is not None:
        out.append(f"  static constexpr Bus         kBus        = Bus::{bus_enum};")

    if per.clock_source:
        out.append(f'  static constexpr const char * kClockSrc   = "{per.clock_source}";')
    if per.max_clock_override:
        out.append(f'  static constexpr const char * kMaxClock   = "{per.max_clock_override}";')

    # IRQs
    if per.irq:
        irq_lines = [str(i.num) for i in per.irq]
        irq_names = [f'"{i.name}"' for i in per.irq]
        out.append(f"  static constexpr unsigned    kIrqLines[]  = {{ {', '.join(irq_lines)} }};")
        out.append(f"  static constexpr const char *kIrqNames[]  = {{ {', '.join(irq_names)} }};")
        out.append(f"  static constexpr unsigned    kIrqCount    = {len(per.irq)};")

    # RCC — ``syn.per_rcc_map`` is the merged source of truth (the
    # builder layers inline ``per.rcc`` over the template-synthesised
    # entry, so this dict carries both the YAML's en/rst paths AND the
    # cross-linked ``extra.clock_sel`` / ``extra.bus``).  Falling back
    # to ``per.rcc`` here covers any future code path that builds a
    # ``SynthesisedDevice`` without going through ``build_synthesised``.
    eff_rcc = syn.per_rcc_map.get(per.id) or per.rcc
    if eff_rcc and eff_rcc.en:
        resolved = resolve_rcc_path(eff_rcc.en, device)
        if resolved is not None:
            # Typed RccGate — pre-resolved (addr, mask).  HAL writes
            #   *reinterpret_cast<volatile uint32_t*>(g.addr) |= g.mask;
            # which folds to a single RMW at -O2.
            out.append(
                f"  static constexpr RccGate     kRccEnable  = "
                f"{{ 0x{resolved.addr:08X}u, 0x{resolved.mask:08X}u }};"
            )
        else:
            # Path didn't resolve (template missing, malformed inline,
            # etc.) — fall back to the dotted-path string so the field
            # is still observable, but flag it for the next regen.
            out.append(
                f'  static constexpr const char * kRccEnableRaw = "{eff_rcc.en}";'
                f"  // unresolved; type-safe form requires a template fix"
            )
    if eff_rcc and eff_rcc.rst:
        resolved = resolve_rcc_path(eff_rcc.rst, device)
        if resolved is not None:
            out.append(
                f"  static constexpr RccGate     kRccReset   = "
                f"{{ 0x{resolved.addr:08X}u, 0x{resolved.mask:08X}u }};"
            )
        else:
            out.append(
                f'  static constexpr const char * kRccResetRaw  = "{eff_rcc.rst}";'
                f"  // unresolved; type-safe form requires a template fix"
            )
    if eff_rcc:
        clock_sel = eff_rcc.extra.get("clock_sel")
        if isinstance(clock_sel, str) and clock_sel:
            resolved = resolve_rcc_path(clock_sel, device)
            if resolved is not None:
                # Typed RccMuxField — multi-bit kernel-clock selector.
                out.append(
                    f"  static constexpr RccMuxField kKernelClockMux = "
                    f"{{ 0x{resolved.addr:08X}u, 0x{resolved.mask:08X}u, "
                    f"{resolved.lsb}u, {resolved.width}u }};"
                )
            else:
                out.append(
                    f'  static constexpr const char * kKernelClockMuxRaw = "{clock_sel}";'
                    f"  // unresolved; type-safe form requires a template fix"
                )
        # Typed gate-model enumerator — drives the alloy HAL's
        # ``constexpr if`` dispatch on EnableClock paths
        # (always_on short-circuit, index_based parser, etc.).
        gate_model = eff_rcc.extra.get("gate_model")
        if isinstance(gate_model, str):
            out.append(
                f"  static constexpr GateModel  kGateModel = "
                f"GateModel::{gate_model};"
            )

    # DMA
    if per.dma and per.dma.tx:
        out.append("  // DMA TX:")
        if per.dma.tx.ctrl is not None:
            out.append(f'  static constexpr const char * kDmaTxCtrl    = "{per.dma.tx.ctrl}";')
        if per.dma.tx.channel is not None:
            out.append(f"  static constexpr unsigned    kDmaTxCh      = {per.dma.tx.channel};")
        if per.dma.tx.dreq is not None:
            out.append(f"  static constexpr unsigned    kDmaTxRequest = {per.dma.tx.dreq};")
    if per.dma and per.dma.rx:
        out.append("  // DMA RX:")
        if per.dma.rx.ctrl is not None:
            out.append(f'  static constexpr const char * kDmaRxCtrl    = "{per.dma.rx.ctrl}";')
        if per.dma.rx.channel is not None:
            out.append(f"  static constexpr unsigned    kDmaRxCh      = {per.dma.rx.channel};")
        if per.dma.rx.dreq is not None:
            out.append(f"  static constexpr unsigned    kDmaRxRequest = {per.dma.rx.dreq};")

    # Mutex group (Nordic shared-IRQ peripherals)
    if per.mutex_group:
        out.append(f'  static constexpr const char * kMutexGroup = "{per.mutex_group}";')

    # Synthesised endpoints (signal names this peripheral exposes)
    endpoints = [e for e in syn.signal_endpoints if e.peripheral == per.id]
    if endpoints:
        signal_names = [f'"{e.signal}"' for e in endpoints]
        out.append(
            f"  static constexpr const char *kSignals[]   = {{ {', '.join(signal_names)} }};"
        )
        out.append(f"  static constexpr unsigned    kSignalCount = {len(endpoints)};")

    # Optional rich-metadata nested structs gated on the trait classifier.
    trait_kind = classify_instance(per)
    if trait_kind == InstanceTraitKind.ADC:
        out.extend(_emit_adc_instance_traits(per))
    elif trait_kind == InstanceTraitKind.I2C:
        out.extend(_emit_i2c_instance_traits(per))

    out.append(f"}};  // struct {safe_id}")
    return out


def emit_peripheral_traits(
    device: CanonicalDevice,
    synthesised: SynthesisedDevice,
) -> str:
    """Render the peripheral-traits header for ``device``."""
    guard = _header_guard(device)
    lines: list[str] = [
        "// peripheral_traits.h",
        "//",
        f"// {device.identity.vendor}/{device.identity.family}/{device.identity.device}"
        f" — generated from {device.schema}",
        "//",
        f"// Provenance: {device.provenance.primary}",
        f"// Authored:   {device.provenance.authored}",
        "//",
        "// Each peripheral instance lives in its own ``namespace`` carrying",
        "// ``constexpr`` traits.  Each unique IP template lives in",
        "// ``namespace template_<ip>`` carrying register offsets + bit",
        "// positions of every named field.",
        "",
        f"#ifndef {guard}",
        f"#define {guard}",
        "",
        "#include <cstddef>",
        "#include <cstdint>",
        "",
        '#include "rcc_traits.hpp"',
        "",
        f"namespace alloy::"
        f"{device.identity.vendor.replace('-', '_')}::"
        f"{device.identity.family.replace('-', '_')}::"
        f"{device.identity.device.replace('-', '_')} {{",
        "",
    ]

    # IP-block template namespaces first — register offsets + bit positions.
    # These remain namespaces (not structs) because they're indexed by IP-version
    # string rather than used as type parameters.
    if device.templates:
        for ip_name, template in sorted(device.templates.items()):
            lines.extend(_emit_template_namespace(ip_name, template))
            lines.append("")

    # Per-instance structs.  Each struct IS the peripheral's trait type:
    #   template <typename P> void enable_clock();  // concept-constrained
    #   enable_clock<usart1>();
    for per in device.peripherals:
        lines.extend(_emit_peripheral_instance(per, synthesised, device))
        lines.append("")

    lines.append(
        f"}}  // namespace alloy::"
        f"{device.identity.vendor.replace('-', '_')}::"
        f"{device.identity.family.replace('-', '_')}::"
        f"{device.identity.device.replace('-', '_')}"
    )
    lines.append("")
    lines.append(f"#endif  // {guard}")
    lines.append("")
    return "\n".join(lines)
