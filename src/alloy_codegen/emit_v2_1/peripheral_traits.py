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

    # Optional timer-matrix block (deadtime / triggers / break inputs).
    if classify_template(template) == TemplateTraitKind.TIMER:
        out.extend(_emit_timer_template_traits(template))

    out.append("}  // namespace template_" + safe_ns)
    return out


def _emit_calibration_data_point(name: str, point: object) -> list[str]:
    """Emit one ``CalibrationDataPoint`` as a typed sub-namespace."""
    # Imported inline to keep the top-of-file imports tidy; the
    # type comes from ir.v2_1.peripherals.
    from alloy_codegen.ir.v2_1 import CalibrationDataPoint
    if not isinstance(point, CalibrationDataPoint):
        return []
    out = [f"    namespace {name} {{"]
    out.append(f"      inline constexpr uintptr_t kRomAddr   = 0x{point.rom_addr:08X}u;")
    out.append(f"      inline constexpr unsigned  kSizeBits  = {point.size_bits};")
    if point.nominal_mv is not None:
        out.append(f"      inline constexpr unsigned  kNominalMv = {int(point.nominal_mv)};")
    if point.temp_celsius is not None:
        out.append(f"      inline constexpr int       kTempC     = {int(point.temp_celsius)};")
    if point.vdda_calibration is not None:
        out.append(f"      inline constexpr unsigned  kVddaCalMv = {int(point.vdda_calibration)};")
    out.append("    }")
    return out


def _emit_adc_instance_traits(per: PeripheralInstance) -> list[str]:
    """Emit ADC-only sub-namespaces inside a peripheral instance.

    Two blocks:
    * ``calibration::{vrefint, ts_cal_low, ts_cal_high}`` — typed
      addresses + nominal / temperature constants from the IR's
      :class:`AdcCalibration`.  HAL reads these to compute Vdda
      and chip temperature without re-deriving the data sheet.
    * ``external_triggers::{regular, injected}`` — typed
      ``{source, extsel, polarity}`` rows for every populated
      kind.  Source and polarity are still ``const char *`` until
      typed enums ship from a follow-up; the integer encoding
      (``extsel`` / ``jextsel``) is the executable bit.
    """
    out: list[str] = []
    cal = per.calibration
    if cal is not None:
        out.append("")
        out.append("  // ADC factory calibration (read at boot to compute Vdda + chip temp).")
        out.append("  namespace calibration {")
        if cal.vrefint is not None:
            out.extend(_emit_calibration_data_point("vrefint", cal.vrefint))
        if cal.ts_cal_low is not None:
            out.extend(_emit_calibration_data_point("ts_cal_low", cal.ts_cal_low))
        if cal.ts_cal_high is not None:
            out.extend(_emit_calibration_data_point("ts_cal_high", cal.ts_cal_high))
        if cal.ts_slope_uv_per_c is not None:
            out.append(
                f"    inline constexpr unsigned kTsSlopeUvPerC = "
                f"{int(cal.ts_slope_uv_per_c)};"
            )
        out.append("  }")

    if per.external_triggers:
        out.append("")
        out.append("  // ADC external-trigger map per kind (regular / injected).")
        out.append("  namespace external_triggers {")
        for kind, triggers in sorted(per.external_triggers.items()):
            sanitised_kind = kind.replace("-", "_").replace(".", "_")
            out.append(f"    namespace {sanitised_kind} {{")
            out.append("      struct row {")
            out.append("        const char *source;     // typed enum lift queued")
            out.append("        int         extsel;     // -1 = not encoded for this kind")
            out.append("        int         jextsel;    // -1 = not encoded for this kind")
            out.append("        const char *polarity;   // \"rising\" | \"falling\" | \"both\"")
            out.append("      };")
            out.append(f"      inline constexpr row kRows[] = {{")
            for trig in triggers:
                ext = trig.extsel if trig.extsel is not None else -1
                jext = trig.jextsel if trig.jextsel is not None else -1
                pol = trig.polarity or ""
                out.append(
                    f"        {{ \"{trig.source}\", {ext}, {jext}, \"{pol}\" }},"
                )
            out.append("      };")
            out.append(f"      inline constexpr unsigned kCount = {len(triggers)};")
            out.append("    }")
        out.append("  }")
    return out


def _emit_i2c_instance_traits(per: PeripheralInstance) -> list[str]:
    """Emit I²C-only sub-namespace inside a peripheral instance.

    One block: ``timing_presets::kRows`` carrying every populated
    ``I2cTimingPreset`` (TIMINGR for v2/v3 — F0/F3/G0/G4/H7;
    CCR + TRISE for v1 — F1/F2/F4).  Each row carries the speed
    label, source-clock label, and the encoded register payload
    so HAL picks the matching preset at open time without runtime
    PCLK division.
    """
    if not per.timing_presets:
        return []
    out = ["", "  // I²C pre-computed timing presets (one per supported speed)."]
    out.append("  namespace timing_presets {")
    out.append("    struct row {")
    out.append("      const char *speed;          // e.g. \"100kHz\" / \"400kHz\" / \"1MHz\"")
    out.append("      const char *source_clock;   // e.g. \"pclk1\"")
    out.append("      unsigned    timingr;        // 0 when not encoded for this row")
    out.append("      unsigned    ccr;            // 0 when not encoded for this row")
    out.append("      unsigned    trise;          // 0 when not encoded for this row")
    out.append("    };")
    out.append(f"    inline constexpr row kRows[] = {{")
    for tp in per.timing_presets:
        timingr = tp.timingr if tp.timingr is not None else 0
        ccr = tp.ccr if tp.ccr is not None else 0
        trise = tp.trise if tp.trise is not None else 0
        out.append(
            f"      {{ \"{tp.speed}\", \"{tp.source_clock}\", "
            f"0x{timingr:08X}u, 0x{ccr:08X}u, 0x{trise:08X}u }},"
        )
    out.append("    };")
    out.append(f"    inline constexpr unsigned kCount = {len(per.timing_presets)};")
    out.append("  }")
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

    # Optional rich-metadata sub-namespaces gated on the trait
    # classifier.  Empty result for instances whose template
    # doesn't carry calibration / timing-preset payloads.
    trait_kind = classify_instance(per)
    if trait_kind == InstanceTraitKind.ADC:
        out.extend(_emit_adc_instance_traits(per))
    elif trait_kind == InstanceTraitKind.I2C:
        out.extend(_emit_i2c_instance_traits(per))

    out.append(f"}}  // namespace {safe_id}")
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
        f"namespace alloy::{device.identity.vendor}::{device.identity.family}"
        f"::{device.identity.device.replace('-', '_')} {{",
        "",
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
