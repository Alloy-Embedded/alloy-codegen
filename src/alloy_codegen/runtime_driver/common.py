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

from typing import Any

from alloy_codegen.reporting import EmittedArtifact

from ..emission import (
    _collect_runtime_semantics_catalog,
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _semantic_enum_ref,
    _std_array_lines,
)
from ..runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_dma_bindings,
    runtime_lite_peripheral_class_name,
)

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


@dataclass(frozen=True, slots=True)
class UartDmaBindingRow:
    """One DMA route for UART data.  Derived from ``device.dma_requests``.

    Added by ``add-uart-spi-tier-2-3-4-data``.  ``signal`` is "TX" or "RX".
    ``transfer_width_bits`` is always 8 on every admitted family — even
    9-bit data on STM32 uses an 8-bit DMA stride from the data register's
    low byte; 16-bit register access is a CPU concern, not DMA.
    """

    controller_peripheral: str
    controller_id: str
    binding_id: str
    request_value: int
    signal: str  # "TX" | "RX"
    transfer_width_bits: int = 8


@dataclass(frozen=True, slots=True)
class KernelClockSourceOption:
    """One kernel-clock source option for a peripheral.  Added by
    ``add-kernel-clock-traits``.

    ``source`` is a normalised classifier string ("pclk1", "sysclk",
    "hsi16", "lse", "xtal", "apb", "peri_clk", "clk_per", ...) mapped
    to the ``KernelClockSource`` enum at emit time.  ``field_value`` is
    the bit-pattern the consumer writes into the RCC mux; on chips where
    the source is hard-wired or the IR doesn't yet carry an explicit
    enumeration, ``field_value`` falls back to the option's positional
    index in the parent-options list.
    """

    source: str
    field_value: int


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


# ---------------------------------------------------------------------------
# Generic rendering helpers (typed-option enum blocks, array lines)
# ---------------------------------------------------------------------------


def _render_typed_option_enum_block(
    *,
    template_name: str,
    alias_name: str,
    peripheral_entries: tuple[tuple[str, tuple[tuple[str, int], ...]], ...],
    leading_comment: str | None = None,
) -> list[str]:
    """Render a per-peripheral typed-option ``enum class`` block.

    Mirrors the ``AdcChannelOf<P>`` pattern established by
    ``add-adc-channel-typed-enum`` and lifted out by
    ``add-typed-peripheral-enums-everywhere``: emits a primary
    template ``struct <template_name>`` carrying an empty ``enum
    class type : std::uint8_t {};``, plus one specialisation per
    populated peripheral with named ``(enumerator, field_value)``
    pairs.  Trails with a ``using <alias_name> = typename ...::type;``
    convenience alias.

    ``peripheral_entries`` is a tuple of
    ``(peripheral_id_enum, ((name, field_value), ...))`` pairs.
    Peripherals carrying no entries are skipped — consumers reach
    for the alias via ``if constexpr (kPresent)`` gates and the
    primary template's empty enum keeps that branch compilable.
    """
    lines: list[str] = []
    if leading_comment:
        lines.append(f"// {leading_comment}")
    lines.extend(
        [
            "template<PeripheralId Id>",
            f"struct {template_name} {{",
            "  enum class type : std::uint8_t {};",
            "};",
            "",
        ]
    )
    for peripheral_id, entries in peripheral_entries:
        if not entries:
            continue
        lines.extend(
            [
                "template<>",
                f"struct {template_name}<PeripheralId::{peripheral_id}> {{",
                "  enum class type : std::uint8_t {",
            ]
        )
        for name, field_value in entries:
            lines.append(f"    {name} = {field_value}u,")
        lines.extend(
            [
                "  };",
                "};",
                "",
            ]
        )
    lines.extend(
        [
            "template<PeripheralId Id>",
            f"using {alias_name} = typename {template_name}<Id>::type;",
            "",
        ]
    )
    return lines


def _render_array_lines(
    *,
    cpp_type: str,
    array_name: str,
    count_name: str,
    items: tuple[object, ...],
    expr_fn,  # type: ignore[no-untyped-def]
) -> list[str]:
    """Render a paired ``static constexpr std::uint32_t kCount`` +
    ``static constexpr std::array<T, N> kArray = { ... };`` declaration."""
    lines: list[str] = [
        f"  static constexpr std::uint32_t {count_name} = {len(items)}u;",
    ]
    if not items:
        lines.append(f"  static constexpr std::array<{cpp_type}, 0> {array_name} = {{}};")
        return lines
    item_lines = [f"    {expr_fn(item)}," for item in items]
    lines.append(f"  static constexpr std::array<{cpp_type}, {len(items)}> {array_name} = {{{{")
    lines.extend(item_lines)
    lines.append("  }};")
    return lines


# ---------------------------------------------------------------------------
# DMA / IRQ / kernel-clock helpers (shared across multiple driver classes)
# ---------------------------------------------------------------------------


def _peripheral_has_dma_binding(context: _SemanticContext, peripheral_name: str) -> bool:
    return any(
        binding.peripheral == peripheral_name
        for binding in _runtime_lite_dma_bindings(context.device)
    )


def _generic_dma_bindings_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    transfer_width_bits: int = 8,
) -> tuple[UartDmaBindingRow, ...]:
    """Generic DMA-binding helper used by I2C/TIMER/DAC/SDMMC/QSPI/ETH.

    Mirrors the UART/SPI helper shape but does not filter by signal —
    every binding admitted for the peripheral is surfaced.  ``signal``
    falls back to an empty string when the IR carries ``None`` so the
    typed ``DmaBindingDirection`` enum maps to ``::none`` (the
    direction is meaningful for UART/SPI; for the other peripherals it
    is informational).
    """
    bindings: list[UartDmaBindingRow] = []
    for binding in _runtime_lite_dma_bindings(context.device):
        if binding.peripheral != peripheral_name:
            continue
        bindings.append(
            UartDmaBindingRow(
                controller_peripheral=binding.controller,
                controller_id=_enum_identifier(binding.controller),
                binding_id=_enum_identifier(binding.binding_id),
                request_value=int(binding.request_value or 0),
                signal=(binding.signal or "").upper(),
                transfer_width_bits=transfer_width_bits,
            )
        )
    return tuple(bindings)


def _enrich_with_dma_bindings(
    context: _SemanticContext,
    rows: tuple[Any, ...],
    *,
    transfer_width_bits: int = 8,
) -> tuple[Any, ...]:
    """Thread `dma_bindings` onto each row that exposes a
    `peripheral_name` and `dma_bindings` attribute.  Used by the
    I2C/TIMER/DAC/SDMMC/QSPI/ETH builders so consumer headers see
    the populated `kDmaBindings` array on every specialisation."""
    import dataclasses as _dc

    enriched: list[Any] = []
    for row in rows:
        if not hasattr(row, "peripheral_name") or not hasattr(row, "dma_bindings"):
            enriched.append(row)
            continue
        bindings = _generic_dma_bindings_for_peripheral(
            context,
            peripheral_name=row.peripheral_name,
            transfer_width_bits=transfer_width_bits,
        )
        if not bindings:
            enriched.append(row)
            continue
        enriched.append(_dc.replace(row, dma_bindings=bindings))
    return tuple(enriched)


def _irq_numbers_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[int, ...]:
    """Return NVIC vector lines bound to ``peripheral_name``, sorted.

    Walks ``device.interrupt_bindings`` filtered by exact peripheral
    match.  De-duplicates lines (a peripheral that shares a vector with
    another peripheral still surfaces the line once) and yields them in
    ascending numerical order so goldens stay deterministic across runs.
    Added by ``add-irq-vector-traits``.
    """
    seen: set[int] = set()
    for binding in context.device.interrupt_bindings:
        if binding.peripheral != peripheral_name:
            continue
        seen.add(int(binding.line))
    return tuple(sorted(seen))


def _classify_kernel_clock_source(node_id: str) -> str:
    """Map a clock-tree node ID (e.g. ``clock-node:rcc-apbenr2``,
    ``clock-node:hsi16``) to a ``KernelClockSource`` enum identifier.

    Returns ``"none"`` for unrecognised IDs so the emitter still
    surfaces the option (with the positional field value) without
    crashing.
    """
    nid = node_id.lower()
    if nid.startswith("clock-node:"):
        nid = nid[len("clock-node:") :]
    # Order matters: more specific suffixes first.
    if "lse" in nid:
        return "lse"
    if "lsi" in nid:
        return "lsi"
    if "hsi16" in nid:
        return "hsi16"
    if nid == "hsi" or nid.endswith("-hsi"):
        return "hsi"
    if "hse" in nid:
        return "hse"
    if "sysclk" in nid:
        return "sysclk"
    if "pclk1" in nid or "rcc-apbenr1" in nid or "apb1" in nid:
        return "pclk1"
    if "pclk2" in nid or "rcc-apbenr2" in nid or "apb2" in nid:
        return "pclk2"
    if "pclk" in nid or "rcc-apbenr" in nid:
        return "pclk"
    if "hclk" in nid:
        return "hclk"
    if nid == "xtal" or "xtal" in nid:
        return "xtal"
    if "rc_fast" in nid or "rcfast" in nid:
        return "rc_fast"
    if "ref_tick" in nid or "reftick" in nid:
        return "ref_tick"
    if nid == "apb" or nid.endswith("-apb"):
        return "apb"
    if "peri" in nid:
        return "peri_clk"
    if "clk_per" in nid or nid == "clk_per":
        return "clk_per"
    if "lpuart_clk_root" in nid or "lpuartclk" in nid:
        return "lpuart_clk_root"
    return "none"


def _kernel_clock_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> dict[str, Any]:
    """Return the kernel-clock kwargs for a UART/SPI/I2C/QSPI/SDMMC row.

    Walks ``device.peripheral_clock_bindings`` for the named peripheral,
    follows the ``selector_id`` (when present) into ``clock_selectors``
    to pull the parent-options list, and resolves the ``register_field_id``
    on both the selector and the gate to typed ``RuntimeFieldRef``
    records.  Empty options + ``kInvalidFieldRef`` when the IR doesn't
    surface the data (e.g. peripherals on SoCs whose clock-tree
    normalizer hasn't been wired yet).  Added by
    ``add-kernel-clock-traits``.
    """
    device = context.device
    invalid_field = _invalid_field_ref()
    selector_field = invalid_field
    gate_field = invalid_field
    options: tuple[KernelClockSourceOption, ...] = ()

    binding = next(
        (b for b in device.peripheral_clock_bindings if b.peripheral == peripheral_name),
        None,
    )
    if binding is not None:
        # Selector → kKernelClockSourceOptions.
        if binding.selector_id is not None:
            selector = next(
                (s for s in device.clock_selectors if s.selector_id == binding.selector_id),
                None,
            )
            if selector is not None:
                options = tuple(
                    KernelClockSourceOption(
                        source=_classify_kernel_clock_source(opt),
                        field_value=index,
                    )
                    for index, opt in enumerate(selector.parent_options)
                )
                selector_field = _resolve_field_ref_by_id(
                    context, field_id=selector.register_field_id
                )
        # Gate → kClockGateField.
        if binding.clock_gate_id is not None:
            gate = next(
                (g for g in device.clock_gates if g.gate_id == binding.clock_gate_id),
                None,
            )
            if gate is not None:
                gate_field = _resolve_field_ref_by_id(context, field_id=gate.register_field_id)

    return {
        "kernel_clock_selector_field": selector_field,
        "kernel_clock_source_options": options,
        "clock_gate_field": gate_field,
    }


def _kernel_clock_lines(
    *,
    selector_field: RuntimeFieldRef | None,
    options: tuple[KernelClockSourceOption, ...],
    max_clock_hz: int,
    gate_field: RuntimeFieldRef | None,
) -> list[str]:
    """Render the four kernel-clock constexprs for a peripheral
    specialisation.  Added by ``add-kernel-clock-traits``.

    ``None`` field-refs render as ``kInvalidFieldRef``.  Empty option
    tuple renders as ``std::array<KernelClockSourceOption, 0>{}``.
    """
    selector = selector_field if selector_field is not None else _invalid_field_ref()
    gate = gate_field if gate_field is not None else _invalid_field_ref()
    n = len(options)
    if n == 0:
        options_line = (
            "  static constexpr std::array<KernelClockSourceOption, 0> "
            "kKernelClockSourceOptions = {};"
        )
    else:
        items = ", ".join(
            f"{{KernelClockSource::{opt.source}, {opt.field_value}u, true}}" for opt in options
        )
        options_line = (
            f"  static constexpr std::array<KernelClockSourceOption, {n}> "
            f"kKernelClockSourceOptions = {{{{{items}}}}};"
        )
    return [
        f"  static constexpr RuntimeFieldRef kKernelClockSelectorField = "
        f"{_field_ref_expr(selector)};",
        options_line,
        # Renamed from ``kMaxClockHz`` to avoid colliding with the SPI
        # ``kMaxClockHz`` constexpr already added by
        # ``fill-espressif-semantic-gaps`` (which describes the SPI's *own*
        # max output frequency, not its kernel-clock input).
        f"  static constexpr std::uint32_t kKernelMaxClockHz = {int(max_clock_hz)}u;",
        f"  static constexpr RuntimeFieldRef kClockGateField = {_field_ref_expr(gate)};",
    ]


# ---------------------------------------------------------------------------
# DMA binding ref helpers (shared across UART / SPI / I2C / Timer / etc.)
# ---------------------------------------------------------------------------


def _dma_binding_direction_token(signal: str) -> str:
    """Map a UART/SPI/etc. ``signal`` field to the typed
    ``DmaBindingDirection`` enum used by the shared ``DmaBindingRef``
    record (add-peripheral-dma-cross-references)."""
    upper = signal.upper()
    if upper == "TX":
        return "DmaBindingDirection::Tx"
    if upper == "RX":
        return "DmaBindingDirection::Rx"
    return "DmaBindingDirection::none"


def _dma_binding_ref_expr(
    *,
    controller_id: str,
    binding_id: str,
    request_value: int,
    signal: str,
    transfer_width_bits: int,
) -> str:
    return (
        "DmaBindingRef{"
        f"DmaControllerId::{controller_id}, "
        f"DmaBindingId::{binding_id}, "
        f"{request_value}u, "
        f"{_dma_binding_direction_token(signal)}, "
        f"{transfer_width_bits}u, true}}"
    )


def _dma_binding_ref_array_lines(bindings: tuple[Any, ...]) -> list[str]:
    """Render `kDmaBindings` as a `std::array<DmaBindingRef, N>`.

    UartDmaBindingRow and SpiDmaBindingRow expose the same field
    names (`controller_id`, `binding_id`, `request_value`, `signal`,
    `transfer_width_bits`) so a single duck-typed helper covers them.
    """
    if not bindings:
        return ["  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};"]
    item_lines = [
        "    "
        + _dma_binding_ref_expr(
            controller_id=binding.controller_id,
            binding_id=binding.binding_id,
            request_value=binding.request_value,
            signal=binding.signal,
            transfer_width_bits=binding.transfer_width_bits,
        )
        + ","
        for binding in bindings
    ]
    return [
        f"  static constexpr std::array<DmaBindingRef, {len(bindings)}> kDmaBindings = {{{{",
        *item_lines,
        "  }};",
    ]


# ---------------------------------------------------------------------------
# Common emitter — used by UART / I2C / SPI / ADC / DAC / RTC / Watchdog /
# CAN / ETH / USB / QSPI / SDMMC.  Per-class row type is duck-typed via
# ``Any`` so this module avoids importing the per-class row dataclasses.
# ---------------------------------------------------------------------------


def _emit_peripheral_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
    header_name: str,
    trait_name: str,
    array_name: str,
    rows: tuple[Any, ...],
    default_lines: list[str],
    specialization_builder,
    extra_body_lines: list[str] | None = None,
) -> EmittedArtifact:
    trait_lines = [
        "template<PeripheralId Id>",
        f"struct {trait_name} {{",
        *default_lines,
        "};",
        "",
    ]
    peripheral_rows: list[str] = []
    for row in rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        # add-peripheral-dma-cross-references: append kDmaBindings to every
        # specialisation that exposes a `dma_bindings` tuple.  UART/SPI/ADC
        # already emit this inline via their tier 2/3/4 helpers; the other
        # peripherals (I2C/TIMER/DAC/SDMMC/QSPI/ETH) get it appended here
        # so the unspecialised primary template's `kDmaBindings` field is
        # always shadowed by a real array in each specialisation.
        row_lines = list(specialization_builder(row))
        bindings = getattr(row, "dma_bindings", None)
        if bindings is not None and not any("kDmaBindings = " in line for line in row_lines):
            row_lines.extend(_dma_binding_ref_array_lines(bindings))
        trait_lines.extend(
            [
                "template<>",
                f"struct {trait_name}<PeripheralId::{peripheral_id}> {{",
                *row_lines,
                "};",
                "",
            ]
        )
        if not getattr(row, "is_stub", False):
            peripheral_rows.append(f"  PeripheralId::{peripheral_id},")
    body_parts: list[str] = [
        *trait_lines,
        *_std_array_lines(
            type_name="PeripheralId",
            variable_name=array_name,
            row_lines=peripheral_rows,
        ),
    ]
    if extra_body_lines:
        body_parts.append("")
        body_parts.extend(extra_body_lines)
    body = "\n".join(body_parts)
    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        body,
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "common.hpp"',
            # ``../pins.hpp`` provides the typed ``PinId`` enum referenced by
            # USB ``kDmPin`` / ``kDpPin`` traits (added by
            # ``add-usb-semantic-traits``).  Other driver semantics headers
            # never use ``PinId`` so the include is a harmless extra but is
            # uniformly available across this layer.
            '#include "../pins.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, header_name),
        content=content,
    )


__all__ = [
    "_IO_SIGNAL_PATTERN",
    "KernelClockSourceOption",
    "RuntimeFieldRef",
    "RuntimeIndexedFieldRef",
    "RuntimeRegisterRef",
    "UartDmaBindingRow",
    "_SemanticContext",
    "_context",
    "_dma_binding_direction_token",
    "_dma_binding_ref_array_lines",
    "_dma_binding_ref_expr",
    "_emit_peripheral_semantics_header",
    "_enrich_with_dma_bindings",
    "_field_ref_expr",
    "_generic_dma_bindings_for_peripheral",
    "_irq_numbers_for_peripheral",
    "_kernel_clock_lines",
    "_peripheral_has_dma_binding",
    "_classify_kernel_clock_source",
    "_kernel_clock_for_peripheral",
    "_render_array_lines",
    "_render_typed_option_enum_block",
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
