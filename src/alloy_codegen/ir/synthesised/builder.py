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

from alloy_codegen.ir.synthesised.device import SynthesisedDevice
from alloy_codegen.ir.synthesised.endpoints import SignalEndpoint
from alloy_codegen.ir.synthesised.interrupts import (
    InterruptBinding,
    VectorSlot,
)
from alloy_codegen.ir.synthesised.route_operations import RouteOperation
from alloy_codegen.ir.v2_1 import (
    CanonicalDevice,
    InterruptMatrix,
    InterruptVector,
    PeripheralInstance,
)

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


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


def _synth_clock_routes(per: PeripheralInstance) -> list[RouteOperation]:
    rows: list[RouteOperation] = []
    if per.rcc and per.rcc.en:
        rows.append(
            RouteOperation(
                operation_id=f"operation:clock-enable:{per.id}",
                kind="set-bit",
                target_ref_kind="clock-gate",
                target_ref_id=f"gate:{per.id}",
                register_id=_normalize_register_path(per.rcc.en),
                register_field_id=_normalize_field_id(per.rcc.en),
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
    if per.rcc and per.rcc.rst:
        # Reset is a "pulse": set + clear.  Codegen emits one
        # set-bit followed by clear-bit; we emit both rows here so
        # the pipeline can drive each independently.
        rows.append(
            RouteOperation(
                operation_id=f"operation:reset-assert:{per.id}",
                kind="set-bit",
                target_ref_kind="reset",
                target_ref_id=f"reset:{per.id}",
                register_id=_normalize_register_path(per.rcc.rst),
                register_field_id=_normalize_field_id(per.rcc.rst),
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
                register_id=_normalize_register_path(per.rcc.rst),
                register_field_id=_normalize_field_id(per.rcc.rst),
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


def build_synthesised(device: CanonicalDevice) -> SynthesisedDevice:
    """Walk ``device`` and produce its :class:`SynthesisedDevice`.

    Deterministic — re-running on the same input yields a structurally-
    equal result (every aggregate is built in source order).
    """
    route_ops: list[RouteOperation] = []
    bindings: list[InterruptBinding] = []
    endpoints: list[SignalEndpoint] = []
    for per in device.peripherals:
        route_ops.extend(_synth_clock_routes(per))
        bindings.extend(_synth_interrupt_bindings(per))
        endpoints.extend(_synth_signal_endpoints(per))
    return SynthesisedDevice(
        route_operations=tuple(route_ops),
        interrupt_bindings=tuple(bindings),
        vector_slots=tuple(_synth_vector_slots(device.interrupts)),
        signal_endpoints=tuple(endpoints),
    )
