"""Build :class:`SynthesisedDevice` from a v2.1 :class:`CanonicalDevice`.

Synthesis rules:

* For every peripheral with ``rcc.en`` set, emit one ``set-bit``
  :class:`RouteOperation` targeting a synthetic clock-gate id.
* For every peripheral with ``rcc.rst`` set, emit one ``clear-bit``
  ``RouteOperation`` targeting a synthetic reset id.
* For every peripheral with one or more IRQ slots, emit one
  :class:`InterruptBinding` per ``(peripheral, irq)`` pair.
* For every IRQ in the top-level ``interrupts:`` vector list, emit one
  :class:`VectorSlot` ``kind="peripheral-irq"``.  System exceptions
  (``__vector_default``, ``Reset_Handler``, etc.) get
  ``kind="reset"`` / ``"system-exception"`` instead.
* For every peripheral signal in ``pin_options``, emit one
  :class:`SignalEndpoint`.

Determinism: builds run in source order (peripheral declaration order
in the YAML, signal order inside ``pin_options``).  No sorting; the
order is the same on every machine.
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised.clock_program import ClockProgramStep
from alloy_codegen.ir.synthesised.device import SynthesisedDevice
from alloy_codegen.ir.synthesised.endpoints import SignalEndpoint
from alloy_codegen.ir.synthesised.interrupts import (
    InterruptBinding,
    VectorSlot,
)
from alloy_codegen.ir.synthesised.pin_routes import PinRoute
from alloy_codegen.ir.synthesised.route_operations import RouteOperation
from alloy_codegen.ir.v2_1 import (
    CanonicalDevice,
    InterruptMatrix,
    InterruptVector,
    PeripheralInstance,
    PeripheralRcc,
)

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


def _bus_from_reg(reg: str) -> str | None:
    """Infer APB/AHB bus domain from an RCC register name.

    Handles two STM32 naming conventions:
      * G0 / G4 / H7 style: ``apbenr1``, ``apbrstr2``   (suffix digit)
      * F4 / F1 style:      ``apb1enr``, ``apb2rstr``   (infix digit)
    """
    import re as _re
    r = reg.lower()
    if "ahb" in r:
        return "AHB"
    # F4/F1: digit immediately after "apb" — e.g. apb2enr, apb1rstr
    m = _re.search(r"apb([12])", r)
    if m:
        return f"APB{m.group(1)}"
    # G0/G4/H7: digit at the end — e.g. apbenr1, apbrstr2, apbsmenr1
    m = _re.search(r"apb.*?([12])$", r)
    if m:
        return f"APB{m.group(1)}"
    if "apb" in r:
        return "APB"
    if "iop" in r:          # STM32 F1 IOPx → APB2
        return "APB2"
    return None


def _expand_grouped_peri_ids(token: str) -> list[str]:
    """Expand a kernel-clock-mux token into the list of peripheral ids
    it covers.

    Examples:
      * ``"lpuart1"``    → ``["lpuart1"]``
      * ``"i2c4"``       → ``["i2c4"]``
      * ``"adc"``        → ``["adc"]``                 (singleton)
      * ``"i2c123"``     → ``["i2c1", "i2c2", "i2c3"]``  (compound)
      * ``"spi45"``      → ``["spi4", "spi5"]``
      * ``"usart234578"``→ ``["usart2","usart3","usart4","usart5","usart7","usart8"]``
      * ``"sai23"``      → ``["sai2", "sai3"]``

    Used by the H7-style ``d2ccip1r.spi123src`` / ``d3ccipr.spi6src``
    kernel-clock-mux convention where a single field controls multiple
    peripheral instances of the same template.
    """
    import re as _re

    m = _re.match(r"^([a-z]+)(\d+)$", token)
    if m is None:
        return [token]
    prefix, digits = m.group(1), m.group(2)
    if len(digits) <= 1:
        return [token]
    return [f"{prefix}{d}" for d in digits]


def _build_rcc_lookup(device: CanonicalDevice) -> dict[str, PeripheralRcc]:
    """Cross-link clock-gate / reset / kernel-clock-mux template fields
    to peripheral IDs.

    Returns a map from peripheral_id → :class:`PeripheralRcc`.

    Two vendor conventions are handled:

    **STM32 ('rcc' template)** — fields shaped like
      * **enable:**     ``{reg}.{peripheral_id}en``   (excl. ``smen``/``rdy``)
      * **reset:**      ``{reg}.{peripheral_id}rst``
      * **clock-mux:**  one of
          - ``ccipr*.{peripheral_id}sel``         (G0 / G4 style)
          - ``*ccip*.{peripheral_id}src``         (H7 style, may be grouped:
              ``i2c123src`` → ``i2c1``, ``i2c2``, ``i2c3``)
          - ``dckcfgr*.{peripheral_id}sel|src``   (F4 style)

    **RP2040 ('resets' + 'clocks' templates)** — fields shaped like
      * **reset:**      ``reset.{peripheral_id}``  (also doubles as enable —
        RP2040 has no separate clock-gate; releasing reset implicitly
        enables the peripheral, so we mirror the same path into ``en``)
      * **clock-mux:**  ``clk_{peripheral_id}_ctrl.auxsrc``  (only present
        for the small set of peripherals with a dedicated kernel clock:
        adc, peri, usb, rtc, ref, sys)

    The ``extra`` dict on each PeripheralRcc carries:
      * ``"bus"``       — inferred bus domain string (APB1, APB2, AHB…),
                          empty for vendors without explicit bus tagging.
      * ``"clock_sel"`` — dotted path for kernel-clock mux field.
    """
    templates = device.templates or {}
    valid_per_ids: set[str] = {per.id for per in device.peripherals}

    per_en:  dict[str, str] = {}   # per_id → "rcc.reg.field"
    per_rst: dict[str, str] = {}
    per_sel: dict[str, str] = {}

    # ----- STM32 'rcc' template -----------------------------------------
    rcc_template = templates.get("rcc")
    if rcc_template is not None:
        for field_key in rcc_template.fields:
            parts = field_key.split(".", 1)
            if len(parts) != 2:
                continue
            reg, fld = parts
            reg_lower = reg.lower()

            # Enable: ends with "en" — exclude sleep-mode ("smen") and
            # ready-flag ("rdy") fields which have the same suffix.
            if (fld.endswith("en")
                    and not fld.endswith("smen")
                    and not fld.endswith("rdy")
                    and not fld.endswith("cen")):   # "lscoen" etc. are not peri enables
                per_id = fld[:-2]
                per_en[per_id] = f"rcc.{field_key}"
                continue

            # Reset: ends with "rst"
            if fld.endswith("rst"):
                per_id = fld[:-3]
                per_rst[per_id] = f"rcc.{field_key}"
                continue

            # Kernel-clock mux on a CCIPR-style register.  Two suffix
            # conventions exist: G0/G4 use "sel", H7 uses "src".
            # F4's DCKCFGR* uses "src" too on a non-CCIPR register.
            is_ccipr_like = "ccip" in reg_lower or reg_lower.startswith("dckcfgr")
            if is_ccipr_like:
                for suffix in ("sel", "src"):
                    if fld.endswith(suffix):
                        token = fld[: -len(suffix)]
                        for per_id in _expand_grouped_peri_ids(token):
                            if per_id in valid_per_ids:
                                per_sel[per_id] = f"rcc.{field_key}"
                        break

    # ----- RP2040 'resets' template ------------------------------------
    # On RP2040 the only per-peripheral gate is the reset bit in
    # RESETS.RESET; releasing the bit implicitly enables the
    # peripheral.  We mirror the same dotted path into ``en`` so the
    # alloy HAL can treat ``kRccEnable`` and ``kRccReset`` uniformly
    # across vendors (the same write toggles both).
    resets_template = templates.get("resets")
    if resets_template is not None:
        for field_key in resets_template.fields:
            parts = field_key.split(".", 1)
            if len(parts) != 2:
                continue
            reg, fld = parts
            if reg.lower() != "reset":
                continue   # ignore reset_done / wdsel mirror registers
            per_id = fld
            if per_id not in valid_per_ids:
                continue
            path = f"resets.{field_key}"
            # Don't clobber an inline ``en`` already declared on the
            # peripheral or a more-specific entry from another template
            # (per.rcc is consulted later as the primary source of truth).
            per_en.setdefault(per_id, path)
            per_rst.setdefault(per_id, path)

    # ----- RP2040 'clocks' template (kernel-clock muxes) ---------------
    # Fields like ``clk_adc_ctrl.auxsrc`` carry the kernel-clock
    # source-mux for the small set of RP2040 peripherals with a
    # dedicated clock domain (adc, peri, usb, rtc, ref, sys).  Map
    # them onto kKernelClockMux just like a CCIPR ``sel`` on STM32.
    clocks_template = templates.get("clocks")
    if clocks_template is not None:
        import re as _re

        for field_key in clocks_template.fields:
            parts = field_key.split(".", 1)
            if len(parts) != 2:
                continue
            reg, fld = parts
            if fld != "auxsrc":
                continue
            m = _re.match(r"^clk_(\w+)_ctrl$", reg)
            if m is None:
                continue
            per_id = m.group(1)
            if per_id in valid_per_ids:
                per_sel[per_id] = f"clocks.{field_key}"

    # ----- assemble the final PeripheralRcc map ------------------------
    all_ids = set(per_en) | set(per_rst)
    result: dict[str, PeripheralRcc] = {}
    for per_id in all_ids:
        extra: dict[str, object] = {}
        en_path = per_en.get(per_id, "")
        # Bus inference applies only to STM32 ``rcc.`` paths — RP2040's
        # ``resets.`` paths don't carry an APB/AHB domain.
        if en_path.startswith("rcc."):
            bus_reg = en_path.split(".")[1] if en_path else ""
            bus = _bus_from_reg(bus_reg) if bus_reg else None
            if bus:
                extra["bus"] = bus
        if per_id in per_sel:
            extra["clock_sel"] = per_sel[per_id]
        result[per_id] = PeripheralRcc(
            en=per_en.get(per_id),
            rst=per_rst.get(per_id),
            extra=extra,
        )

    return result


def _normalize_register_path(reg_path: str | None) -> str | None:
    """Turn a vendor-specific RCC register reference into a canonical
    ``register:<peripheral>:<reg>`` id.

    The input shape varies wildly:

    * STM32 hand-crafted: ``APB2ENR.IOPAEN`` (RCC implicit).
    * STM32 absolute:     ``RCC.APB2ENR.IOPAEN``.
    * ESP32:              ``DPORT.PERIP_CLK_EN.GPIO``.
    * nRF52:              ``ENABLE.UARTE0`` (peripheral-relative).
    * RP2040:             ``RESETS.RESET.uart0``.

    We canonicalise to lower-case + colon-separated; the **last** path
    component is the bit/field name and the rest is the register.
    """
    if not reg_path:
        return None
    parts = reg_path.split(".")
    if len(parts) < 2:
        return None
    if len(parts) == 2:
        # ``REG.BIT`` — peripheral implicit, use REG twice for clarity.
        peripheral, _bit = parts
        return f"register:{peripheral.lower()}:{peripheral.lower()}"
    # Three or more components: ``PERIPH.REG.BIT`` — drop the trailing bit.
    peripheral = parts[0].lower()
    register = parts[1].lower()
    return f"register:{peripheral}:{register}"


def _normalize_field_id(reg_path: str | None) -> str | None:
    """``register:<periph>:<reg>:<field>`` from the dotted form."""
    if not reg_path:
        return None
    parts = reg_path.split(".")
    if len(parts) < 2:
        return None
    if len(parts) == 2:
        peripheral, field = parts
        return f"field:{peripheral.lower()}:{peripheral.lower()}:{field.lower()}"
    return (
        f"field:{parts[0].lower()}:{parts[1].lower()}:"
        f"{'.'.join(parts[2:]).lower()}"
    )


# ---------------------------------------------------------------------------
# Per-row synthesis
# ---------------------------------------------------------------------------


def _synth_clock_routes(
    per: PeripheralInstance,
    rcc_override: PeripheralRcc | None = None,
) -> list[RouteOperation]:
    """Synthesise clock-enable and reset RouteOperations.

    ``rcc_override`` is the RCC entry from the template cross-link table
    used when the peripheral YAML entry has no inline ``rcc:`` block.
    """
    effective_rcc = per.rcc or rcc_override
    rows: list[RouteOperation] = []
    if effective_rcc and effective_rcc.en:
        rows.append(
            RouteOperation(
                operation_id=f"operation:clock-enable:{per.id}",
                kind="set-bit",
                target_ref_kind="clock-gate",
                target_ref_id=f"gate:{per.id}",
                register_id=_normalize_register_path(effective_rcc.en),
                register_field_id=_normalize_field_id(effective_rcc.en),
                value_ref_kind="int",
                value_int=1,
                subject_kind="peripheral",
                subject_id=per.id,
                schema_id=(
                    f"alloy.{per.template}.{per.ip_version}"
                    if per.ip_version
                    else f"alloy.{per.template}"
                ),
            )
        )
    if effective_rcc and effective_rcc.rst:
        # Reset is a "pulse": set + clear.  Codegen emits one
        # set-bit followed by clear-bit; we emit both rows here so
        # the pipeline can drive each independently.
        rows.append(
            RouteOperation(
                operation_id=f"operation:reset-assert:{per.id}",
                kind="set-bit",
                target_ref_kind="reset",
                target_ref_id=f"reset:{per.id}",
                register_id=_normalize_register_path(effective_rcc.rst),
                register_field_id=_normalize_field_id(effective_rcc.rst),
                value_ref_kind="int",
                value_int=1,
                subject_kind="peripheral",
                subject_id=per.id,
            )
        )
        rows.append(
            RouteOperation(
                operation_id=f"operation:reset-release:{per.id}",
                kind="clear-bit",
                target_ref_kind="reset",
                target_ref_id=f"reset:{per.id}",
                register_id=_normalize_register_path(effective_rcc.rst),
                register_field_id=_normalize_field_id(effective_rcc.rst),
                value_ref_kind="int",
                value_int=0,
                subject_kind="peripheral",
                subject_id=per.id,
            )
        )
    return rows


def _synth_interrupt_bindings(per: PeripheralInstance) -> list[InterruptBinding]:
    out: list[InterruptBinding] = []
    for irq in per.irq:
        out.append(
            InterruptBinding(
                binding_id=f"binding:{per.id}:{irq.name}",
                peripheral=per.id,
                interrupt=irq.name,
                line=irq.num,
                vector_slot=irq.num,
                symbol_name=irq.name,
                shared_group=per.mutex_group,
            )
        )
    return out


def _synth_signal_endpoints(per: PeripheralInstance) -> list[SignalEndpoint]:
    out: list[SignalEndpoint] = []
    for signal in per.pin_options:
        out.append(
            SignalEndpoint(
                endpoint_id=f"endpoint:{per.id}:{signal}",
                peripheral=per.id,
                peripheral_class=per.template,
                signal=signal,
            )
        )
    # Also emit endpoints for ADC / SAADC channels.
    for channel in per.channels:
        out.append(
            SignalEndpoint(
                endpoint_id=f"endpoint:{per.id}:{channel}",
                peripheral=per.id,
                peripheral_class=per.template,
                signal=channel,
                direction="analog",
            )
        )
    return out


def _classify_vector_kind(name: str) -> str:
    """Classify a vector symbol by name pattern.

    AVR's reset slot is ``__vector_default`` (slot 0).  ARM Cortex-M
    uses ``Reset_Handler`` + ``__stack_top`` + system-exception names
    (``NMI_Handler``, ``HardFault_Handler``, …).
    """
    n = name.lower()
    if n in {"__stack_top", "_estack"}:
        return "initial-stack-pointer"
    if n in {"__vector_default", "reset_handler", "_start"}:
        return "reset"
    if n.endswith("_handler") and not n.endswith("_irqhandler"):
        return "system-exception"
    return "peripheral-irq"


def _synth_vector_slots(
    interrupts: tuple[InterruptVector, ...] | InterruptMatrix | None,
) -> list[VectorSlot]:
    if interrupts is None:
        return []
    if isinstance(interrupts, InterruptMatrix):
        # Matrix-style chips don't have fixed vector slots; the runtime
        # router populates them.  Emit one per declared peripheral source.
        return [
            VectorSlot(
                slot=src.id,
                symbol_name=src.name,
                kind="matrix-source",
                interrupt=src.name,
            )
            for src in interrupts.peripheral_sources
        ]
    return [
        VectorSlot(
            slot=v.num,
            symbol_name=v.name,
            kind=_classify_vector_kind(v.name),  # type: ignore[arg-type]
            interrupt=v.name if _classify_vector_kind(v.name) == "peripheral-irq" else None,
        )
        for v in interrupts
    ]


# ---------------------------------------------------------------------------
# Public entry point
# ---------------------------------------------------------------------------


def _synth_pin_routes(device: CanonicalDevice) -> tuple[PinRoute, ...]:
    """Lower every (peripheral, signal, pin_option) triple to a
    canonical :class:`PinRoute` via the family's
    :class:`PinmuxBackend`.

    Returns an empty tuple when no backend ships for the family
    yet — the pin-router emitter then emits a stub
    ``ALLOY_PIN_ROUTE_COUNT == 0`` artifact and consumers compile
    cleanly.

    Sorted by ``(peripheral_id, signal_id, pin_id)`` so the
    regenerated table is byte-stable across runs.

    Local import (deferred) to keep the IR layer free of an
    eager dependency on ``emit_v2_1`` — same pattern as
    :func:`_synth_clock_program_steps`.
    """
    from alloy_codegen.emit_v2_1.pinmux_backends import backend_for

    backend = backend_for(device.identity.vendor, device.identity.family)
    if backend is None:
        return ()
    rows: list[PinRoute] = []
    for per in device.peripherals:
        for signal, options in per.pin_options.items():
            for option in options:
                try:
                    rows.append(backend.encode(per, signal, option))
                except ValueError:
                    # Backend rejected an option type it can't handle
                    # (e.g. STM32 backend seeing a Matrix option from
                    # a future heterogeneous family).  Drop quietly;
                    # the option survives in the IR for diagnostics.
                    continue
    rows.sort(key=lambda r: (r.peripheral_id, r.signal_id, r.pin_id))
    return tuple(rows)


def _synth_clock_program_steps(
    device: CanonicalDevice,
) -> dict[str, tuple[ClockProgramStep, ...]]:
    """Lower every :class:`ClockProfile` to its vendor-agnostic
    program via the per-vendor :class:`ClockBackend`.

    Returns an empty dict for any vendor without a registered
    backend yet — the runtime-init emitter then falls back to
    declaration-only output for those profiles.

    Local import is deliberate: the clock-backend registry lives
    under ``alloy_codegen.emit_v2_1.clock_backends`` because the
    backends carry artifact-adjacent knowledge (FLASH WS tables,
    barrier discipline) that conceptually belongs next to the
    runtime_init emitter rather than the IR layer.  We pay a
    one-time import cost to keep the synthesiser's hot path free
    of circular imports.
    """
    from alloy_codegen.emit_v2_1.clock_backends import backend_for

    backend = backend_for(device.identity.vendor)
    if backend is None:
        return {}
    return {
        profile.id: backend.emit_profile(profile, device)
        for profile in device.clock.profiles
    }


def build_synthesised(device: CanonicalDevice) -> SynthesisedDevice:
    """Walk ``device`` and produce its :class:`SynthesisedDevice`.

    Deterministic — re-running on the same input yields a structurally-
    equal result (every aggregate is built in source order).
    """
    # Build the RCC lookup from the 'rcc' template (STM32-style YAMLs
    # declare clock-enable/reset fields centrally, not per peripheral).
    rcc_lookup = _build_rcc_lookup(device)

    route_ops: list[RouteOperation] = []
    bindings: list[InterruptBinding] = []
    endpoints: list[SignalEndpoint] = []
    per_rcc_map: dict[str, PeripheralRcc] = {}

    for per in device.peripherals:
        # Prefer the peripheral's own rcc: block; fall back to the lookup.
        rcc_override = None if per.rcc else rcc_lookup.get(per.id)
        route_ops.extend(_synth_clock_routes(per, rcc_override))
        bindings.extend(_synth_interrupt_bindings(per))
        endpoints.extend(_synth_signal_endpoints(per))
        effective_rcc = per.rcc or rcc_override
        if effective_rcc:
            per_rcc_map[per.id] = effective_rcc

    return SynthesisedDevice(
        route_operations=tuple(route_ops),
        interrupt_bindings=tuple(bindings),
        vector_slots=tuple(_synth_vector_slots(device.interrupts)),
        signal_endpoints=tuple(endpoints),
        clock_program_steps=_synth_clock_program_steps(device),
        pin_routes=_synth_pin_routes(device),
        per_rcc_map=per_rcc_map,
    )
