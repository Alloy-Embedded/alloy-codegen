"""Shared substrate for the per-class driver-semantics emitters.

Carries the foundational dataclasses
(``RuntimeRegisterRef`` / ``RuntimeFieldRef`` /
``RuntimeIndexedFieldRef``), the ``_SemanticContext`` build /
construction helpers, the register / field resolution helpers,
the C++ expression generators, and a handful of pin /
peripheral / IRQ / schema reference helpers used across every
per-class emitter.

Carved out from ``runtime_driver_semantics.py`` under the
``refactor-runtime-driver-semantics-per-class`` OpenSpec
change.  The legacy monolith re-exports everything below for
backwards compatibility.

This module deliberately avoids importing from any per-class
emitter so the import graph stays acyclic.
"""

# ruff: noqa: E501

from __future__ import annotations

import re
from dataclasses import dataclass

from alloy_codegen.ir.model import (
    CanonicalDeviceIR,
    ConnectionCandidate,
    PeripheralInstance,
    PinDefinition,
    RegisterDescriptor,
    RegisterFieldDescriptor,
)

from ..emission import (
    _collect_runtime_semantics_catalog,
    _enum_identifier,
    _semantic_enum_ref,
)
from ..runtime_lite_emission import runtime_lite_peripheral_class_name

# ---------------------------------------------------------------------------
# Patterns
# ---------------------------------------------------------------------------

_IO_SIGNAL_PATTERN = re.compile(r"^io(?P<index>\d+)$", re.IGNORECASE)


# ---------------------------------------------------------------------------
# Foundational refs
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class RuntimeRegisterRef:
    """One runtime driver register reference."""

    register_id: str | None
    base_address: int
    offset_bytes: int
    valid: bool


@dataclass(frozen=True, slots=True)
class RuntimeFieldRef:
    """One runtime driver field reference."""

    field_id: str | None
    register: RuntimeRegisterRef
    bit_offset: int
    bit_width: int
    valid: bool


@dataclass(frozen=True, slots=True)
class RuntimeIndexedFieldRef:
    """One indexed runtime field reference pattern."""

    base_address: int
    base_offset_bytes: int
    stride_bytes: int
    bit_offset: int
    bit_width: int
    bit_stride_bits: int
    valid: bool


# ---------------------------------------------------------------------------
# Semantic context
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class _SemanticContext:
    device: CanonicalDeviceIR
    semantics_catalog: dict[str, dict[str, str]]
    peripheral_by_name: dict[str, PeripheralInstance]
    pin_by_name: dict[str, PinDefinition]
    register_by_key: dict[tuple[str, str], RegisterDescriptor]
    field_by_key: dict[tuple[str, str, str], RegisterFieldDescriptor]
    gpio_candidate_by_pin: dict[str, ConnectionCandidate]
    candidate_peripherals_by_class: dict[str, tuple[PeripheralInstance, ...]]
    runtime_peripherals_by_class: dict[str, tuple[PeripheralInstance, ...]]


def _context(device: CanonicalDeviceIR) -> _SemanticContext:
    peripheral_by_name = {peripheral.name: peripheral for peripheral in device.peripherals}
    pin_by_name = {pin.name: pin for pin in device.pins}
    register_by_key = {
        (register.peripheral, register.name.upper()): register for register in device.registers
    }
    field_by_key = {
        (
            register_field.peripheral,
            register_field.register_name.upper(),
            register_field.name.upper(),
        ): register_field
        for register_field in device.register_fields
    }
    gpio_candidates = sorted(
        (
            candidate
            for candidate in device.connection_candidates
            if candidate.peripheral in peripheral_by_name
            and runtime_lite_peripheral_class_name(peripheral_by_name[candidate.peripheral].ip_name)
            == "gpio"
        ),
        key=lambda item: item.candidate_id,
    )
    gpio_candidate_by_pin: dict[str, ConnectionCandidate] = {}
    for candidate in gpio_candidates:
        gpio_candidate_by_pin.setdefault(candidate.pin, candidate)

    candidate_peripherals: dict[str, list[PeripheralInstance]] = {}
    seen: set[tuple[str, str]] = set()
    for candidate in sorted(device.connection_candidates, key=lambda item: item.candidate_id):
        peripheral = peripheral_by_name.get(candidate.peripheral)
        if peripheral is None:
            continue
        peripheral_class = runtime_lite_peripheral_class_name(peripheral.ip_name)
        key = (peripheral_class, peripheral.name)
        if key in seen:
            continue
        seen.add(key)
        candidate_peripherals.setdefault(peripheral_class, []).append(peripheral)

    runtime_peripherals: dict[str, list[PeripheralInstance]] = {}
    for peripheral in sorted(device.peripherals, key=lambda item: item.name):
        peripheral_class = runtime_lite_peripheral_class_name(peripheral.ip_name)
        runtime_peripherals.setdefault(peripheral_class, []).append(peripheral)
    return _SemanticContext(
        device=device,
        semantics_catalog=_collect_runtime_semantics_catalog((device,)),
        peripheral_by_name=peripheral_by_name,
        pin_by_name=pin_by_name,
        register_by_key=register_by_key,
        field_by_key=field_by_key,
        gpio_candidate_by_pin=gpio_candidate_by_pin,
        candidate_peripherals_by_class={
            name: tuple(sorted(peripherals, key=lambda item: item.name))
            for name, peripherals in candidate_peripherals.items()
        },
        runtime_peripherals_by_class={
            name: tuple(sorted(peripherals, key=lambda item: item.name))
            for name, peripherals in runtime_peripherals.items()
        },
    )


# ---------------------------------------------------------------------------
# Invalid-ref factories
# ---------------------------------------------------------------------------


def _invalid_register_ref(base_address: int = 0) -> RuntimeRegisterRef:
    return RuntimeRegisterRef(
        register_id=None, base_address=base_address, offset_bytes=0, valid=False
    )


def _invalid_field_ref(base_address: int = 0) -> RuntimeFieldRef:
    return RuntimeFieldRef(
        field_id=None,
        register=_invalid_register_ref(base_address),
        bit_offset=0,
        bit_width=0,
        valid=False,
    )


def _invalid_indexed_field_ref(base_address: int = 0) -> RuntimeIndexedFieldRef:
    return RuntimeIndexedFieldRef(
        base_address=base_address,
        base_offset_bytes=0,
        stride_bytes=0,
        bit_offset=0,
        bit_width=0,
        bit_stride_bits=0,
        valid=False,
    )


def _indexed_field_ref(
    *,
    base_address: int,
    base_offset_bytes: int,
    stride_bytes: int,
    bit_offset: int,
    bit_width: int,
    bit_stride_bits: int = 0,
) -> RuntimeIndexedFieldRef:
    return RuntimeIndexedFieldRef(
        base_address=base_address,
        base_offset_bytes=base_offset_bytes,
        stride_bytes=stride_bytes,
        bit_offset=bit_offset,
        bit_width=bit_width,
        bit_stride_bits=bit_stride_bits,
        valid=True,
    )


# ---------------------------------------------------------------------------
# Resolution helpers
# ---------------------------------------------------------------------------


def _resolve_register_ref(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_name: str,
    fallback_offset: int | None = None,
) -> RuntimeRegisterRef:
    peripheral = context.peripheral_by_name.get(peripheral_name)
    if peripheral is None:
        return _invalid_register_ref()
    register = context.register_by_key.get((peripheral_name, register_name.upper()))
    if register is not None:
        return RuntimeRegisterRef(
            register_id=register.register_id,
            base_address=peripheral.base_address,
            offset_bytes=register.offset_bytes,
            valid=True,
        )
    if fallback_offset is None:
        return _invalid_register_ref(peripheral.base_address)
    return RuntimeRegisterRef(
        register_id=None,
        base_address=peripheral.base_address,
        offset_bytes=fallback_offset,
        valid=True,
    )


def _resolve_field_ref(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_name: str,
    field_names: tuple[str, ...],
    fallback_register_offset: int | None = None,
    fallback_bit_offset: int | None = None,
    fallback_bit_width: int | None = None,
) -> RuntimeFieldRef:
    for field_name in field_names:
        field = context.field_by_key.get(
            (peripheral_name, register_name.upper(), field_name.upper())
        )
        if field is None:
            continue
        register_ref = _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
        )
        return RuntimeFieldRef(
            field_id=field.field_id,
            register=register_ref,
            bit_offset=field.bit_offset,
            bit_width=field.bit_width,
            valid=True,
        )

    register_ref = _resolve_register_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_name,
        fallback_offset=fallback_register_offset,
    )
    if not register_ref.valid or fallback_bit_offset is None or fallback_bit_width is None:
        return _invalid_field_ref(register_ref.base_address)
    return RuntimeFieldRef(
        field_id=None,
        register=register_ref,
        bit_offset=fallback_bit_offset,
        bit_width=fallback_bit_width,
        valid=True,
    )


def _resolve_register_ref_any(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_names: tuple[str, ...],
    fallback_offset: int | None = None,
) -> RuntimeRegisterRef:
    for register_name in register_names:
        register_ref = _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
        )
        if register_ref.valid and register_ref.register_id is not None:
            return register_ref
    if not register_names:
        return _invalid_register_ref()
    return _resolve_register_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_names[0],
        fallback_offset=fallback_offset,
    )


def _resolve_field_ref_any(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_names: tuple[str, ...],
    field_names: tuple[str, ...],
    fallback_register_offset: int | None = None,
    fallback_bit_offset: int | None = None,
    fallback_bit_width: int | None = None,
) -> RuntimeFieldRef:
    for register_name in register_names:
        field_ref = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
        )
        if field_ref.valid and field_ref.field_id is not None:
            return field_ref
    if not register_names:
        return _invalid_field_ref()
    return _resolve_field_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_names[0],
        field_names=field_names,
        fallback_register_offset=fallback_register_offset,
        fallback_bit_offset=fallback_bit_offset,
        fallback_bit_width=fallback_bit_width,
    )


def _manual_field_ref(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_name: str,
    register_offset: int,
    bit_offset: int,
    bit_width: int = 1,
) -> RuntimeFieldRef:
    register_ref = _resolve_register_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_name,
        fallback_offset=register_offset,
    )
    if not register_ref.valid:
        return _invalid_field_ref(register_ref.base_address)
    return RuntimeFieldRef(
        field_id=None,
        register=register_ref,
        bit_offset=bit_offset,
        bit_width=bit_width,
        valid=True,
    )


def _resolve_field_ref_by_id(
    context: _SemanticContext,
    *,
    field_id: str | None,
) -> RuntimeFieldRef:
    """Resolve a ``register_field_id`` like ``field:rcc:apbenr2:usart1en``
    to a ``RuntimeFieldRef``.

    The ID format is ``field:<peripheral>:<register>:<field>`` with
    lowercase identifiers.  We re-case to upper and run the standard
    ``_resolve_field_ref`` lookup so the returned record carries the
    same shape every other field-ref in the trait surface uses.
    Returns ``kInvalidFieldRef`` when the ID is missing or unparseable.
    """
    if field_id is None or not field_id.startswith("field:"):
        return _invalid_field_ref()
    parts = field_id.split(":")
    if len(parts) < 4:
        return _invalid_field_ref()
    _, peripheral, register, field_name = parts[0], parts[1], parts[2], ":".join(parts[3:])
    return _resolve_field_ref(
        context,
        peripheral_name=peripheral.upper(),
        register_name=register.upper(),
        field_names=(field_name.upper(),),
        fallback_register_offset=0,
        fallback_bit_offset=0,
        fallback_bit_width=1,
    )


# ---------------------------------------------------------------------------
# C++ expression helpers
# ---------------------------------------------------------------------------


def _field_ref_expr(field_ref: RuntimeFieldRef) -> str:
    if not field_ref.valid:
        return "kInvalidFieldRef"
    register_expr = _register_ref_expr(field_ref.register)
    field_id = (
        "FieldId::none"
        if field_ref.field_id is None
        else f"FieldId::{_enum_identifier(field_ref.field_id)}"
    )
    return (
        f"RuntimeFieldRef{{{field_id}, {register_expr}, "
        f"{field_ref.bit_offset}u, {field_ref.bit_width}u, true}}"
    )


def _indexed_field_ref_expr(field_ref: RuntimeIndexedFieldRef) -> str:
    if not field_ref.valid:
        return "kInvalidIndexedFieldRef"
    return (
        "RuntimeIndexedFieldRef{"
        f"0x{field_ref.base_address:08X}u, "
        f"{field_ref.base_offset_bytes}u, "
        f"{field_ref.stride_bytes}u, "
        f"{field_ref.bit_offset}u, "
        f"{field_ref.bit_width}u, "
        f"{field_ref.bit_stride_bits}u, "
        "true}"
    )


def _register_ref_expr(register_ref: RuntimeRegisterRef) -> str:
    if not register_ref.valid:
        return "kInvalidRegisterRef"
    register_id = (
        "RegisterId::none"
        if register_ref.register_id is None
        else f"RegisterId::{_enum_identifier(register_ref.register_id)}"
    )
    return (
        f"RuntimeRegisterRef{{{register_id}, "
        f"0x{register_ref.base_address:08X}u, {register_ref.offset_bytes}u, true}}"
    )


# ---------------------------------------------------------------------------
# Common emission helpers
# ---------------------------------------------------------------------------


def _irq_numbers_lines(irq_numbers: tuple[int, ...]) -> list[str]:
    """Render the ``kIrqNumbers`` constexpr array for a peripheral
    specialisation.  Added by ``add-irq-vector-traits``.

    Empty tuple yields ``std::array<std::uint32_t, 0>{}`` so consumer
    code that branches on ``kIrqNumbers.size() > 0`` stays valid.
    """
    n = len(irq_numbers)
    if n == 0:
        return [
            "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
        ]
    joined = ", ".join(f"{v}u" for v in irq_numbers)
    return [
        f"  static constexpr std::array<std::uint32_t, {n}> kIrqNumbers = {{{{{joined}}}}};",
    ]


def _schema_ref_expr(context: _SemanticContext, schema_id: str | None) -> str:
    return _semantic_enum_ref(
        "BackendSchemaId",
        context.semantics_catalog["backend_schema_enum_map"],
        schema_id,
    )


def _peripheral_ref(peripheral_name: str | None) -> str:
    if peripheral_name is None:
        return "PeripheralId::none"
    return f"PeripheralId::{_enum_identifier(peripheral_name)}"


def _pin_ref(pin_name: str) -> str:
    return f"PinId::{_enum_identifier(pin_name)}"


def _line_index_from_candidate(
    context: _SemanticContext, candidate: ConnectionCandidate
) -> int | None:
    pin = context.pin_by_name.get(candidate.pin)
    if pin is not None and pin.number >= 0:
        return pin.number
    match = _IO_SIGNAL_PATTERN.match(candidate.signal)
    if match is not None:
        return int(match.group("index"), 10)
    return None


__all__ = [
    "_IO_SIGNAL_PATTERN",
    "RuntimeFieldRef",
    "RuntimeIndexedFieldRef",
    "RuntimeRegisterRef",
    "_SemanticContext",
    "_context",
    "_field_ref_expr",
    "_indexed_field_ref",
    "_indexed_field_ref_expr",
    "_invalid_field_ref",
    "_invalid_indexed_field_ref",
    "_invalid_register_ref",
    "_irq_numbers_lines",
    "_line_index_from_candidate",
    "_manual_field_ref",
    "_peripheral_ref",
    "_pin_ref",
    "_register_ref_expr",
    "_resolve_field_ref",
    "_resolve_field_ref_any",
    "_resolve_field_ref_by_id",
    "_resolve_register_ref",
    "_resolve_register_ref_any",
    "_schema_ref_expr",
]
