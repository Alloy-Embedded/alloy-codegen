# ruff: noqa: E501

"""Runtime-lite driver semantic emission helpers.

This layer sits above runtime-lite facts. It publishes schema-aware semantic
traits that Alloy drivers can consume directly without scanning reflection
tables or rediscovering register meanings in the runtime.
"""

from __future__ import annotations

import re
from dataclasses import dataclass

from alloy_codegen.connector_model import canonical_peripheral_class
from alloy_codegen.ir.model import (
    CanonicalDeviceIR,
    ConnectionCandidate,
    PeripheralInstance,
    PinDefinition,
    RegisterDescriptor,
    RegisterFieldDescriptor,
)
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _collect_runtime_semantics_catalog,
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _semantic_enum_ref,
    _std_array_lines,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_dma_bindings,
)

GPIO_DRIVER_HEADER = "driver_semantics/gpio.hpp"
I2C_DRIVER_HEADER = "driver_semantics/i2c.hpp"
SPI_DRIVER_HEADER = "driver_semantics/spi.hpp"
UART_DRIVER_HEADER = "driver_semantics/uart.hpp"
DMA_DRIVER_HEADER = "driver_semantics/dma.hpp"
COMMON_DRIVER_HEADER = "driver_semantics/common.hpp"

_IO_SIGNAL_PATTERN = re.compile(r"^io(?P<index>\d+)$", re.IGNORECASE)


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
    valid: bool


@dataclass(frozen=True, slots=True)
class GpioSemanticRow:
    """GPIO semantic trait payload keyed by pin."""

    pin_name: str
    peripheral_name: str
    schema_id: str
    line_index: int
    mode_field: RuntimeFieldRef
    direction_field: RuntimeFieldRef
    output_type_field: RuntimeFieldRef
    pull_field: RuntimeFieldRef
    input_field: RuntimeFieldRef
    output_value_field: RuntimeFieldRef
    output_set_field: RuntimeFieldRef
    output_reset_field: RuntimeFieldRef
    pio_enable_field: RuntimeFieldRef
    pio_output_enable_field: RuntimeFieldRef
    pio_output_disable_field: RuntimeFieldRef
    pio_set_field: RuntimeFieldRef
    pio_clear_field: RuntimeFieldRef
    pio_input_state_field: RuntimeFieldRef
    pio_drive_enable_field: RuntimeFieldRef
    pio_drive_disable_field: RuntimeFieldRef
    pio_pull_up_enable_field: RuntimeFieldRef
    pio_pull_up_disable_field: RuntimeFieldRef
    pio_pull_down_enable_field: RuntimeFieldRef
    pio_pull_down_disable_field: RuntimeFieldRef


@dataclass(frozen=True, slots=True)
class UartSemanticRow:
    """UART semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    cr1_reg: RuntimeRegisterRef
    cr2_reg: RuntimeRegisterRef
    brr_reg: RuntimeRegisterRef
    isr_reg: RuntimeRegisterRef
    rdr_reg: RuntimeRegisterRef
    tdr_reg: RuntimeRegisterRef
    sr_reg: RuntimeRegisterRef
    dr_reg: RuntimeRegisterRef
    cr_reg: RuntimeRegisterRef
    mr_reg: RuntimeRegisterRef
    brgr_reg: RuntimeRegisterRef
    thr_reg: RuntimeRegisterRef
    us_cr_reg: RuntimeRegisterRef
    us_mr_reg: RuntimeRegisterRef
    us_brgr_reg: RuntimeRegisterRef
    us_thr_reg: RuntimeRegisterRef
    ue_field: RuntimeFieldRef
    re_field: RuntimeFieldRef
    te_field: RuntimeFieldRef
    pce_field: RuntimeFieldRef
    ps_field: RuntimeFieldRef
    m0_field: RuntimeFieldRef
    m1_field: RuntimeFieldRef
    m_field: RuntimeFieldRef
    stop_field: RuntimeFieldRef
    tdr_field: RuntimeFieldRef
    rdr_field: RuntimeFieldRef
    txe_isr_field: RuntimeFieldRef
    rxne_isr_field: RuntimeFieldRef
    tc_isr_field: RuntimeFieldRef
    txe_sr_field: RuntimeFieldRef
    rxne_sr_field: RuntimeFieldRef
    tc_sr_field: RuntimeFieldRef
    dr_field: RuntimeFieldRef
    rstrx_field: RuntimeFieldRef
    rsttx_field: RuntimeFieldRef
    rxdis_field: RuntimeFieldRef
    txdis_field: RuntimeFieldRef
    rststa_field: RuntimeFieldRef
    par_field: RuntimeFieldRef
    chmode_field: RuntimeFieldRef
    cd_field: RuntimeFieldRef
    rxen_field: RuntimeFieldRef
    txen_field: RuntimeFieldRef
    txrdy_field: RuntimeFieldRef
    rxrdy_field: RuntimeFieldRef
    txempty_field: RuntimeFieldRef
    txchr_field: RuntimeFieldRef
    rxchr_field: RuntimeFieldRef
    us_rstrx_field: RuntimeFieldRef
    us_rsttx_field: RuntimeFieldRef
    us_rxdis_field: RuntimeFieldRef
    us_txdis_field: RuntimeFieldRef
    us_rststa_field: RuntimeFieldRef
    us_usart_mode_field: RuntimeFieldRef
    us_usclks_field: RuntimeFieldRef
    us_chrl_field: RuntimeFieldRef
    us_cd_field: RuntimeFieldRef
    us_rxen_field: RuntimeFieldRef
    us_txen_field: RuntimeFieldRef
    us_txrdy_field: RuntimeFieldRef
    us_rxrdy_field: RuntimeFieldRef
    us_txempty_field: RuntimeFieldRef
    us_txchr_field: RuntimeFieldRef
    us_rxchr_field: RuntimeFieldRef


@dataclass(frozen=True, slots=True)
class I2cSemanticRow:
    """I2C semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    cr1_reg: RuntimeRegisterRef
    cr2_reg: RuntimeRegisterRef
    ccr_reg: RuntimeRegisterRef
    trise_reg: RuntimeRegisterRef
    sr1_reg: RuntimeRegisterRef
    sr2_reg: RuntimeRegisterRef
    dr_reg: RuntimeRegisterRef
    icr_reg: RuntimeRegisterRef
    cr_reg: RuntimeRegisterRef
    mmr_reg: RuntimeRegisterRef
    iadr_reg: RuntimeRegisterRef
    cwgr_reg: RuntimeRegisterRef
    sr_reg: RuntimeRegisterRef
    rhr_reg: RuntimeRegisterRef
    thr_reg: RuntimeRegisterRef
    pe_field: RuntimeFieldRef
    ack_field: RuntimeFieldRef
    start_field: RuntimeFieldRef
    stop_field: RuntimeFieldRef
    freq_field: RuntimeFieldRef
    ccr_field: RuntimeFieldRef
    fs_field: RuntimeFieldRef
    duty_field: RuntimeFieldRef
    trise_field: RuntimeFieldRef
    sb_field: RuntimeFieldRef
    addr_field: RuntimeFieldRef
    txe_field: RuntimeFieldRef
    rxne_field: RuntimeFieldRef
    btf_field: RuntimeFieldRef
    af_field: RuntimeFieldRef
    berr_field: RuntimeFieldRef
    arlo_field: RuntimeFieldRef
    busy_field: RuntimeFieldRef
    dr_data_field: RuntimeFieldRef
    sadd_field: RuntimeFieldRef
    rd_wrn_field: RuntimeFieldRef
    nbytes_field: RuntimeFieldRef
    autoend_field: RuntimeFieldRef
    txis_field: RuntimeFieldRef
    tc_field: RuntimeFieldRef
    stopf_field: RuntimeFieldRef
    txdata_field: RuntimeFieldRef
    rxdata_field: RuntimeFieldRef
    nackf_field: RuntimeFieldRef
    berr_isr_field: RuntimeFieldRef
    arlo_isr_field: RuntimeFieldRef
    stopcf_field: RuntimeFieldRef
    nackcf_field: RuntimeFieldRef
    berrcf_field: RuntimeFieldRef
    arlocf_field: RuntimeFieldRef
    msen_field: RuntimeFieldRef
    msdis_field: RuntimeFieldRef
    svdis_field: RuntimeFieldRef
    swrst_field: RuntimeFieldRef
    iadrsz_field: RuntimeFieldRef
    mread_field: RuntimeFieldRef
    dadr_field: RuntimeFieldRef
    iadr_field: RuntimeFieldRef
    cldiv_field: RuntimeFieldRef
    chdiv_field: RuntimeFieldRef
    ckdiv_field: RuntimeFieldRef
    hold_field: RuntimeFieldRef
    txcomp_field: RuntimeFieldRef
    rxrdy_field: RuntimeFieldRef
    txrdy_field: RuntimeFieldRef
    nack_field: RuntimeFieldRef
    arblst_field: RuntimeFieldRef


@dataclass(frozen=True, slots=True)
class SpiSemanticRow:
    """SPI semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    cr1_reg: RuntimeRegisterRef
    cr2_reg: RuntimeRegisterRef
    sr_reg: RuntimeRegisterRef
    dr_reg: RuntimeRegisterRef
    cr_reg: RuntimeRegisterRef
    mr_reg: RuntimeRegisterRef
    csr_reg: RuntimeRegisterRef
    tdr_reg: RuntimeRegisterRef
    rdr_reg: RuntimeRegisterRef
    cpha_field: RuntimeFieldRef
    cpol_field: RuntimeFieldRef
    mstr_field: RuntimeFieldRef
    br_field: RuntimeFieldRef
    spe_field: RuntimeFieldRef
    lsbfirst_field: RuntimeFieldRef
    ssi_field: RuntimeFieldRef
    ssm_field: RuntimeFieldRef
    dff_field: RuntimeFieldRef
    ds_field: RuntimeFieldRef
    frxth_field: RuntimeFieldRef
    txe_field: RuntimeFieldRef
    rxne_field: RuntimeFieldRef
    bsy_field: RuntimeFieldRef
    dr_data_field: RuntimeFieldRef
    spien_field: RuntimeFieldRef
    spidis_field: RuntimeFieldRef
    swrst_field: RuntimeFieldRef
    ps_field: RuntimeFieldRef
    pcsdec_field: RuntimeFieldRef
    modfdis_field: RuntimeFieldRef
    pcs_field: RuntimeFieldRef
    dlybcs_field: RuntimeFieldRef
    ncpha_field: RuntimeFieldRef
    bits_field: RuntimeFieldRef
    scbr_field: RuntimeFieldRef
    dlybs_field: RuntimeFieldRef
    dlybct_field: RuntimeFieldRef
    tdre_field: RuntimeFieldRef
    rdrf_field: RuntimeFieldRef
    txempty_field: RuntimeFieldRef
    td_field: RuntimeFieldRef
    tdr_pcs_field: RuntimeFieldRef
    rd_field: RuntimeFieldRef


@dataclass(frozen=True, slots=True)
class DmaSemanticRow:
    """DMA semantic trait payload keyed by binding peripheral/signal."""

    peripheral_name: str
    signal_name: str
    binding_id: str
    controller_name: str
    request_line: str
    route_id: str
    conflict_group: str | None
    controller_schema_id: str | None
    router_name: str | None
    router_schema_id: str | None
    channel_index: int | None
    request_value: int | None
    channel_selector: int | None
    route_selector_field: RuntimeIndexedFieldRef


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


def _driver_semantics_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    paths: list[str] = []
    for device in devices:
        device_name = device.identity.device
        paths.extend(
            (
                _device_runtime_generated_path(family_dir, device_name, COMMON_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, GPIO_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, UART_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, I2C_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, SPI_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, DMA_DRIVER_HEADER),
            )
        )
    return tuple(paths)


def runtime_driver_semantics_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return _driver_semantics_paths(family_dir=family_dir, devices=devices)


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
            and canonical_peripheral_class(peripheral_by_name[candidate.peripheral].ip_name)
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
        peripheral_class = canonical_peripheral_class(peripheral.ip_name)
        key = (peripheral_class, peripheral.name)
        if key in seen:
            continue
        seen.add(key)
        candidate_peripherals.setdefault(peripheral_class, []).append(peripheral)
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
    )


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
        valid=False,
    )


def _indexed_field_ref(
    *,
    base_address: int,
    base_offset_bytes: int,
    stride_bytes: int,
    bit_offset: int,
    bit_width: int,
) -> RuntimeIndexedFieldRef:
    return RuntimeIndexedFieldRef(
        base_address=base_address,
        base_offset_bytes=base_offset_bytes,
        stride_bytes=stride_bytes,
        bit_offset=bit_offset,
        bit_width=bit_width,
        valid=True,
    )


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


def _st_gpio_semantics(
    context: _SemanticContext,
    *,
    pin_name: str,
    peripheral_name: str,
    schema_id: str,
    line_index: int,
) -> GpioSemanticRow:
    return GpioSemanticRow(
        pin_name=pin_name,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        line_index=line_index,
        mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MODER",
            field_names=(f"MODE{line_index}", f"MODER{line_index}"),
            fallback_register_offset=0x00,
            fallback_bit_offset=line_index * 2,
            fallback_bit_width=2,
        ),
        direction_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        output_type_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="OTYPER",
            field_names=(f"OT{line_index}", f"OT_{line_index}", f"OT{line_index}"),
            fallback_register_offset=0x04,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        pull_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PUPDR",
            field_names=(f"PUPD{line_index}", f"PUPDR{line_index}"),
            fallback_register_offset=0x0C,
            fallback_bit_offset=line_index * 2,
            fallback_bit_width=2,
        ),
        input_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IDR",
            field_names=(f"IDR{line_index}", f"ID{line_index}"),
            fallback_register_offset=0x10,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_value_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ODR",
            field_names=(f"ODR{line_index}", f"OD{line_index}"),
            fallback_register_offset=0x14,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_set_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BSRR",
            field_names=(f"BS{line_index}",),
            fallback_register_offset=0x18,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_reset_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BSRR",
            field_names=(f"BR{line_index}",),
            fallback_register_offset=0x18,
            fallback_bit_offset=16 + line_index,
            fallback_bit_width=1,
        ),
        pio_enable_field=_invalid_field_ref(),
        pio_output_enable_field=_invalid_field_ref(),
        pio_output_disable_field=_invalid_field_ref(),
        pio_set_field=_invalid_field_ref(),
        pio_clear_field=_invalid_field_ref(),
        pio_input_state_field=_invalid_field_ref(),
        pio_drive_enable_field=_invalid_field_ref(),
        pio_drive_disable_field=_invalid_field_ref(),
        pio_pull_up_enable_field=_invalid_field_ref(),
        pio_pull_up_disable_field=_invalid_field_ref(),
        pio_pull_down_enable_field=_invalid_field_ref(),
        pio_pull_down_disable_field=_invalid_field_ref(),
    )


def _microchip_gpio_semantics(
    context: _SemanticContext,
    *,
    pin_name: str,
    peripheral_name: str,
    schema_id: str,
    line_index: int,
) -> GpioSemanticRow:
    field_name = f"P{line_index}"

    def pio(register_name: str, offset: int) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=offset,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        )

    return GpioSemanticRow(
        pin_name=pin_name,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        line_index=line_index,
        mode_field=_invalid_field_ref(),
        direction_field=_invalid_field_ref(),
        output_type_field=_invalid_field_ref(),
        pull_field=_invalid_field_ref(),
        input_field=_invalid_field_ref(),
        output_value_field=_invalid_field_ref(),
        output_set_field=_invalid_field_ref(),
        output_reset_field=_invalid_field_ref(),
        pio_enable_field=pio("PER", 0x000),
        pio_output_enable_field=pio("OER", 0x010),
        pio_output_disable_field=pio("ODR", 0x014),
        pio_set_field=pio("SODR", 0x030),
        pio_clear_field=pio("CODR", 0x034),
        pio_input_state_field=pio("PDSR", 0x03C),
        pio_drive_enable_field=pio("MDER", 0x050),
        pio_drive_disable_field=pio("MDDR", 0x054),
        pio_pull_up_enable_field=pio("PUER", 0x064),
        pio_pull_up_disable_field=pio("PUDR", 0x060),
        pio_pull_down_enable_field=pio("PPDER", 0x094),
        pio_pull_down_disable_field=pio("PPDDR", 0x090),
    )


def _nxp_gpio_semantics(
    context: _SemanticContext,
    *,
    pin_name: str,
    peripheral_name: str,
    schema_id: str,
    line_index: int,
) -> GpioSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address
    return GpioSemanticRow(
        pin_name=pin_name,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        line_index=line_index,
        mode_field=_invalid_field_ref(base),
        direction_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="GDIR",
            field_names=("DATA", f"IO{line_index:02d}"),
            fallback_register_offset=0x04,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_type_field=_invalid_field_ref(base),
        pull_field=_invalid_field_ref(base),
        input_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PSR",
            field_names=("DATA", f"IO{line_index:02d}"),
            fallback_register_offset=0x08,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_value_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DR",
            field_names=("DATA", f"IO{line_index:02d}"),
            fallback_register_offset=0x00,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_set_field=_invalid_field_ref(base),
        output_reset_field=_invalid_field_ref(base),
        pio_enable_field=_invalid_field_ref(base),
        pio_output_enable_field=_invalid_field_ref(base),
        pio_output_disable_field=_invalid_field_ref(base),
        pio_set_field=_invalid_field_ref(base),
        pio_clear_field=_invalid_field_ref(base),
        pio_input_state_field=_invalid_field_ref(base),
        pio_drive_enable_field=_invalid_field_ref(base),
        pio_drive_disable_field=_invalid_field_ref(base),
        pio_pull_up_enable_field=_invalid_field_ref(base),
        pio_pull_up_disable_field=_invalid_field_ref(base),
        pio_pull_down_enable_field=_invalid_field_ref(base),
        pio_pull_down_disable_field=_invalid_field_ref(base),
    )


def _build_gpio_rows(context: _SemanticContext) -> tuple[GpioSemanticRow, ...]:
    rows: list[GpioSemanticRow] = []
    for pin_name, candidate in sorted(context.gpio_candidate_by_pin.items()):
        peripheral = context.peripheral_by_name.get(candidate.peripheral)
        if peripheral is None or peripheral.backend_schema_id is None:
            continue
        line_index = _line_index_from_candidate(context, candidate)
        if line_index is None:
            continue
        schema_id = peripheral.backend_schema_id
        if schema_id in {
            "alloy.gpio.st-stm32g07x-gpio-v1-0",
            "alloy.gpio.st-stm32f4x-gpio-v1-0",
        }:
            rows.append(
                _st_gpio_semantics(
                    context,
                    pin_name=pin_name,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    line_index=line_index,
                )
            )
        elif schema_id == "alloy.gpio.microchip-pio-v":
            rows.append(
                _microchip_gpio_semantics(
                    context,
                    pin_name=pin_name,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    line_index=line_index,
                )
            )
        elif schema_id == "alloy.gpio.nxp-imxrt-gpio-v1":
            rows.append(
                _nxp_gpio_semantics(
                    context,
                    pin_name=pin_name,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    line_index=line_index,
                )
            )
    return tuple(rows)


def _microchip_uart_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
    usart_prefix: str = "",
) -> UartSemanticRow:
    prefix = usart_prefix

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str, field_name: str, offset: int, bit_offset: int, bit_width: int = 1
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(context.peripheral_by_name[peripheral_name].base_address)
    empty_field = _invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address)
    is_usart = bool(prefix)
    return UartSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=empty_reg,
        brr_reg=empty_reg,
        isr_reg=empty_reg,
        rdr_reg=empty_reg,
        tdr_reg=empty_reg,
        sr_reg=empty_reg,
        dr_reg=empty_reg,
        cr_reg=reg(f"{prefix}CR" if is_usart else "CR", 0x00),
        mr_reg=reg(f"{prefix}MR" if is_usart else "MR", 0x04),
        brgr_reg=reg(f"{prefix}BRGR" if is_usart else "BRGR", 0x20 if is_usart else 0x20),
        thr_reg=reg(f"{prefix}THR" if is_usart else "THR", 0x1C),
        us_cr_reg=reg("US_CR_LIN_MODE", 0x00) if is_usart else empty_reg,
        us_mr_reg=reg("US_MR_SPI_MODE", 0x04) if is_usart else empty_reg,
        us_brgr_reg=reg("US_BRGR", 0x20) if is_usart else empty_reg,
        us_thr_reg=reg("US_THR", 0x1C) if is_usart else empty_reg,
        ue_field=empty_field,
        re_field=empty_field,
        te_field=empty_field,
        pce_field=empty_field,
        ps_field=empty_field,
        m0_field=empty_field,
        m1_field=empty_field,
        m_field=empty_field,
        stop_field=empty_field,
        tdr_field=empty_field,
        rdr_field=empty_field,
        txe_isr_field=empty_field,
        rxne_isr_field=empty_field,
        tc_isr_field=empty_field,
        txe_sr_field=empty_field,
        rxne_sr_field=empty_field,
        tc_sr_field=empty_field,
        dr_field=empty_field,
        rstrx_field=field("CR", "RSTRX", 0x00, 2) if not is_usart else empty_field,
        rsttx_field=field("CR", "RSTTX", 0x00, 3) if not is_usart else empty_field,
        rxdis_field=field("CR", "RXDIS", 0x00, 5) if not is_usart else empty_field,
        txdis_field=field("CR", "TXDIS", 0x00, 7) if not is_usart else empty_field,
        rststa_field=field("CR", "RSTSTA", 0x00, 8) if not is_usart else empty_field,
        par_field=field("MR", "PAR", 0x04, 9, 3) if not is_usart else empty_field,
        chmode_field=field("MR", "CHMODE", 0x04, 14, 2) if not is_usart else empty_field,
        cd_field=field("BRGR", "CD", 0x20, 0, 16) if not is_usart else empty_field,
        rxen_field=field("CR", "RXEN", 0x00, 4) if not is_usart else empty_field,
        txen_field=field("CR", "TXEN", 0x00, 6) if not is_usart else empty_field,
        txrdy_field=field("SR", "TXRDY", 0x14, 1) if not is_usart else empty_field,
        rxrdy_field=field("SR", "RXRDY", 0x14, 0) if not is_usart else empty_field,
        txempty_field=field("SR", "TXEMPTY", 0x14, 9) if not is_usart else empty_field,
        txchr_field=field("THR", "TXCHR", 0x1C, 0, 9) if not is_usart else empty_field,
        rxchr_field=field("RHR", "RXCHR", 0x18, 0, 9) if not is_usart else empty_field,
        us_rstrx_field=field("US_CR_LIN_MODE", "RSTRX", 0x00, 2) if is_usart else empty_field,
        us_rsttx_field=field("US_CR_LIN_MODE", "RSTTX", 0x00, 3) if is_usart else empty_field,
        us_rxdis_field=field("US_CR_LIN_MODE", "RXDIS", 0x00, 5) if is_usart else empty_field,
        us_txdis_field=field("US_CR_LIN_MODE", "TXDIS", 0x00, 7) if is_usart else empty_field,
        us_rststa_field=field("US_CR_LIN_MODE", "RSTSTA", 0x00, 8) if is_usart else empty_field,
        us_usart_mode_field=field("US_MR_SPI_MODE", "USART_MODE", 0x04, 0, 4)
        if is_usart
        else empty_field,
        us_usclks_field=field("US_MR_SPI_MODE", "USCLKS", 0x04, 4, 2) if is_usart else empty_field,
        us_chrl_field=field("US_MR_SPI_MODE", "CHRL", 0x04, 6, 2) if is_usart else empty_field,
        us_cd_field=field("US_BRGR", "CD", 0x20, 0, 16) if is_usart else empty_field,
        us_rxen_field=field("US_CR_LIN_MODE", "RXEN", 0x00, 4) if is_usart else empty_field,
        us_txen_field=field("US_CR_LIN_MODE", "TXEN", 0x00, 6) if is_usart else empty_field,
        us_txrdy_field=field("US_CSR_LIN_MODE", "TXRDY", 0x14, 1) if is_usart else empty_field,
        us_rxrdy_field=field("US_CSR_LIN_MODE", "RXRDY", 0x14, 0) if is_usart else empty_field,
        us_txempty_field=field("US_CSR_LIN_MODE", "TXEMPTY", 0x14, 9) if is_usart else empty_field,
        us_txchr_field=field("US_THR", "TXCHR", 0x1C, 0, 9) if is_usart else empty_field,
        us_rxchr_field=field("US_RHR", "RXCHR", 0x18, 0, 9) if is_usart else empty_field,
    )


def _st_uart_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
    f4_layout: bool,
) -> UartSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return UartSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=reg("CR1", 0x0C if f4_layout else 0x00),
        cr2_reg=reg("CR2", 0x10 if f4_layout else 0x04),
        brr_reg=reg("BRR", 0x08 if f4_layout else 0x0C),
        isr_reg=reg("ISR", 0x1C) if not f4_layout else empty_reg,
        rdr_reg=reg("RDR", 0x24) if not f4_layout else empty_reg,
        tdr_reg=reg("TDR", 0x28) if not f4_layout else empty_reg,
        sr_reg=reg("SR", 0x00) if f4_layout else empty_reg,
        dr_reg=reg("DR", 0x04) if f4_layout else empty_reg,
        cr_reg=empty_reg,
        mr_reg=empty_reg,
        brgr_reg=empty_reg,
        thr_reg=empty_reg,
        us_cr_reg=empty_reg,
        us_mr_reg=empty_reg,
        us_brgr_reg=empty_reg,
        us_thr_reg=empty_reg,
        ue_field=field("CR1", ("UE",), 0x0C if f4_layout else 0x00, 0),
        re_field=field("CR1", ("RE",), 0x0C if f4_layout else 0x00, 2),
        te_field=field("CR1", ("TE",), 0x0C if f4_layout else 0x00, 3),
        pce_field=field("CR1", ("PCE",), 0x0C if f4_layout else 0x00, 10),
        ps_field=field("CR1", ("PS",), 0x0C if f4_layout else 0x00, 9),
        m0_field=field("CR1", ("M0",), 0x00, 12) if not f4_layout else empty_field,
        m1_field=field("CR1", ("M1",), 0x00, 28) if not f4_layout else empty_field,
        m_field=field("CR1", ("M",), 0x0C, 12) if f4_layout else empty_field,
        stop_field=field("CR2", ("STOP",), 0x10 if f4_layout else 0x04, 12, 2),
        tdr_field=field("TDR", ("TDR", "TXDATA"), 0x28, 0, 9) if not f4_layout else empty_field,
        rdr_field=field("RDR", ("RDR", "RXDATA"), 0x24, 0, 9) if not f4_layout else empty_field,
        txe_isr_field=field("ISR", ("TXE_TXFNF", "TXE"), 0x1C, 7) if not f4_layout else empty_field,
        rxne_isr_field=field("ISR", ("RXNE_RXFNE", "RXNE"), 0x1C, 5)
        if not f4_layout
        else empty_field,
        tc_isr_field=field("ISR", ("TC",), 0x1C, 6) if not f4_layout else empty_field,
        txe_sr_field=field("SR", ("TXE",), 0x00, 7) if f4_layout else empty_field,
        rxne_sr_field=field("SR", ("RXNE",), 0x00, 5) if f4_layout else empty_field,
        tc_sr_field=field("SR", ("TC",), 0x00, 6) if f4_layout else empty_field,
        dr_field=field("DR", ("DR",), 0x04, 0, 9) if f4_layout else empty_field,
        rstrx_field=empty_field,
        rsttx_field=empty_field,
        rxdis_field=empty_field,
        txdis_field=empty_field,
        rststa_field=empty_field,
        par_field=empty_field,
        chmode_field=empty_field,
        cd_field=empty_field,
        rxen_field=empty_field,
        txen_field=empty_field,
        txrdy_field=empty_field,
        rxrdy_field=empty_field,
        txempty_field=empty_field,
        txchr_field=empty_field,
        rxchr_field=empty_field,
        us_rstrx_field=empty_field,
        us_rsttx_field=empty_field,
        us_rxdis_field=empty_field,
        us_txdis_field=empty_field,
        us_rststa_field=empty_field,
        us_usart_mode_field=empty_field,
        us_usclks_field=empty_field,
        us_chrl_field=empty_field,
        us_cd_field=empty_field,
        us_rxen_field=empty_field,
        us_txen_field=empty_field,
        us_txrdy_field=empty_field,
        us_rxrdy_field=empty_field,
        us_txempty_field=empty_field,
        us_txchr_field=empty_field,
        us_rxchr_field=empty_field,
    )


def _nxp_uart_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> UartSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return UartSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=empty_reg,
        brr_reg=empty_reg,
        isr_reg=empty_reg,
        rdr_reg=empty_reg,
        tdr_reg=empty_reg,
        sr_reg=empty_reg,
        dr_reg=empty_reg,
        cr_reg=empty_reg,
        mr_reg=empty_reg,
        brgr_reg=empty_reg,
        thr_reg=empty_reg,
        us_cr_reg=empty_reg,
        us_mr_reg=empty_reg,
        us_brgr_reg=empty_reg,
        us_thr_reg=empty_reg,
        ue_field=field("CTRL", ("UARTEN",), 0x18, 0),
        re_field=field("CTRL", ("RE",), 0x18, 18),
        te_field=field("CTRL", ("TE",), 0x18, 19),
        pce_field=field("CTRL", ("PE",), 0x18, 1),
        ps_field=field("CTRL", ("PT",), 0x18, 0),
        m0_field=empty_field,
        m1_field=empty_field,
        m_field=field("CTRL", ("M", "M7"), 0x18, 4),
        stop_field=field("BAUD", ("SBNS",), 0x10, 13),
        tdr_field=field("DATA", ("TDATA", "DATA"), 0x1C, 0, 10),
        rdr_field=field("DATA", ("RDATA", "DATA"), 0x1C, 0, 10),
        txe_isr_field=field("STAT", ("TDRE",), 0x14, 23),
        rxne_isr_field=field("STAT", ("RDRF",), 0x14, 21),
        tc_isr_field=field("STAT", ("TC",), 0x14, 22),
        txe_sr_field=empty_field,
        rxne_sr_field=empty_field,
        tc_sr_field=empty_field,
        dr_field=empty_field,
        rstrx_field=empty_field,
        rsttx_field=empty_field,
        rxdis_field=empty_field,
        txdis_field=empty_field,
        rststa_field=empty_field,
        par_field=empty_field,
        chmode_field=empty_field,
        cd_field=field("BAUD", ("SBR",), 0x10, 0, 13),
        rxen_field=empty_field,
        txen_field=empty_field,
        txrdy_field=empty_field,
        rxrdy_field=empty_field,
        txempty_field=empty_field,
        txchr_field=empty_field,
        rxchr_field=empty_field,
        us_rstrx_field=empty_field,
        us_rsttx_field=empty_field,
        us_rxdis_field=empty_field,
        us_txdis_field=empty_field,
        us_rststa_field=empty_field,
        us_usart_mode_field=empty_field,
        us_usclks_field=empty_field,
        us_chrl_field=empty_field,
        us_cd_field=empty_field,
        us_rxen_field=empty_field,
        us_txen_field=empty_field,
        us_txrdy_field=empty_field,
        us_rxrdy_field=empty_field,
        us_txempty_field=empty_field,
        us_txchr_field=empty_field,
        us_rxchr_field=empty_field,
    )


def _build_uart_rows(context: _SemanticContext) -> tuple[UartSemanticRow, ...]:
    def _has_register(peripheral_name: str, register_name: str) -> bool:
        return (peripheral_name, register_name.upper()) in context.register_by_key

    def _st_uart_uses_f4_layout(peripheral: PeripheralInstance) -> bool:
        schema_id = (peripheral.backend_schema_id or "").lower()
        ip_version = (peripheral.ip_version or "").lower()
        tokens = (schema_id, ip_version)
        if any("sci2" in token or "usart-f4" in token or "usart_f4" in token for token in tokens):
            return True
        if any("sci3" in token or "usart-v3" in token or "usart_v3" in token for token in tokens):
            return False
        has_isr_style = any(
            _has_register(peripheral.name, register_name) for register_name in ("ISR", "RDR", "TDR")
        )
        if has_isr_style:
            return False
        has_sr_style = _has_register(peripheral.name, "SR") and _has_register(peripheral.name, "DR")
        if has_sr_style:
            return True
        return False

    rows: list[UartSemanticRow] = []
    for peripheral in context.candidate_peripherals_by_class.get("uart", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.uart.st-"):
            rows.append(
                _st_uart_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    f4_layout=_st_uart_uses_f4_layout(peripheral),
                )
            )
        elif schema_id == "alloy.uart.microchip-uart-r":
            rows.append(
                _microchip_uart_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id == "alloy.uart.microchip-usart-zw":
            rows.append(
                _microchip_uart_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    usart_prefix="US_",
                )
            )
        elif schema_id == "alloy.uart.nxp-lpuart-v1":
            rows.append(
                _nxp_uart_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
    return tuple(rows)


def _st_i2c_v1_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str, field_name: str, reg_offset: int, bit_offset: int, bit_width: int = 1
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=reg("CR1", 0x00),
        cr2_reg=reg("CR2", 0x04),
        ccr_reg=reg("CCR", 0x1C),
        trise_reg=reg("TRISE", 0x20),
        sr1_reg=reg("SR1", 0x14),
        sr2_reg=reg("SR2", 0x18),
        dr_reg=reg("DR", 0x10),
        icr_reg=empty_reg,
        cr_reg=empty_reg,
        mmr_reg=empty_reg,
        iadr_reg=empty_reg,
        cwgr_reg=empty_reg,
        sr_reg=empty_reg,
        rhr_reg=empty_reg,
        thr_reg=empty_reg,
        pe_field=field("CR1", "PE", 0x00, 0),
        ack_field=field("CR1", "ACK", 0x00, 10),
        start_field=field("CR1", "START", 0x00, 8),
        stop_field=field("CR1", "STOP", 0x00, 9),
        freq_field=field("CR2", "FREQ", 0x04, 0, 6),
        ccr_field=field("CCR", "CCR", 0x1C, 0, 12),
        fs_field=field("CCR", "F_S", 0x1C, 15),
        duty_field=field("CCR", "DUTY", 0x1C, 14),
        trise_field=field("TRISE", "TRISE", 0x20, 0, 6),
        sb_field=field("SR1", "SB", 0x14, 0),
        addr_field=field("SR1", "ADDR", 0x14, 1),
        txe_field=field("SR1", "TxE", 0x14, 7),
        rxne_field=field("SR1", "RxNE", 0x14, 6),
        btf_field=field("SR1", "BTF", 0x14, 2),
        af_field=field("SR1", "AF", 0x14, 10),
        berr_field=field("SR1", "BERR", 0x14, 8),
        arlo_field=field("SR1", "ARLO", 0x14, 9),
        busy_field=field("SR2", "BUSY", 0x18, 1),
        dr_data_field=field("DR", "DR", 0x10, 0, 8),
        sadd_field=empty_field,
        rd_wrn_field=empty_field,
        nbytes_field=empty_field,
        autoend_field=empty_field,
        txis_field=empty_field,
        tc_field=empty_field,
        stopf_field=empty_field,
        txdata_field=empty_field,
        rxdata_field=empty_field,
        nackf_field=empty_field,
        berr_isr_field=empty_field,
        arlo_isr_field=empty_field,
        stopcf_field=empty_field,
        nackcf_field=empty_field,
        berrcf_field=empty_field,
        arlocf_field=empty_field,
        msen_field=empty_field,
        msdis_field=empty_field,
        svdis_field=empty_field,
        swrst_field=empty_field,
        iadrsz_field=empty_field,
        mread_field=empty_field,
        dadr_field=empty_field,
        iadr_field=empty_field,
        cldiv_field=empty_field,
        chdiv_field=empty_field,
        ckdiv_field=empty_field,
        hold_field=empty_field,
        txcomp_field=empty_field,
        rxrdy_field=empty_field,
        txrdy_field=empty_field,
        nack_field=empty_field,
        arblst_field=empty_field,
    )


def _st_i2c_v2_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=reg("CR2", 0x04),
        ccr_reg=empty_reg,
        trise_reg=empty_reg,
        sr1_reg=empty_reg,
        sr2_reg=empty_reg,
        dr_reg=empty_reg,
        icr_reg=reg("ICR", 0x20),
        cr_reg=empty_reg,
        mmr_reg=empty_reg,
        iadr_reg=empty_reg,
        cwgr_reg=empty_reg,
        sr_reg=empty_reg,
        rhr_reg=empty_reg,
        thr_reg=empty_reg,
        pe_field=empty_field,
        ack_field=empty_field,
        start_field=field("CR2", ("START",), 0x04, 13),
        stop_field=empty_field,
        freq_field=empty_field,
        ccr_field=empty_field,
        fs_field=empty_field,
        duty_field=empty_field,
        trise_field=empty_field,
        sb_field=empty_field,
        addr_field=empty_field,
        txe_field=empty_field,
        rxne_field=empty_field,
        btf_field=empty_field,
        af_field=empty_field,
        berr_field=empty_field,
        arlo_field=empty_field,
        busy_field=empty_field,
        dr_data_field=empty_field,
        sadd_field=field("CR2", ("SADD",), 0x04, 0, 10),
        rd_wrn_field=field("CR2", ("RD_WRN",), 0x04, 10),
        nbytes_field=field("CR2", ("NBYTES",), 0x04, 16, 8),
        autoend_field=field("CR2", ("AUTOEND",), 0x04, 25),
        txis_field=field("ISR", ("TXIS",), 0x1C, 1),
        tc_field=field("ISR", ("TC",), 0x1C, 6),
        stopf_field=field("ISR", ("STOPF",), 0x1C, 5),
        txdata_field=field("TXDR", ("TXDATA",), 0x28, 0, 8),
        rxdata_field=field("RXDR", ("RXDATA",), 0x24, 0, 8),
        nackf_field=field("ISR", ("NACKF",), 0x1C, 4),
        berr_isr_field=field("ISR", ("BERR",), 0x1C, 8),
        arlo_isr_field=field("ISR", ("ARLO",), 0x1C, 9),
        stopcf_field=field("ICR", ("STOPCF",), 0x20, 5),
        nackcf_field=field("ICR", ("NACKCF",), 0x20, 4),
        berrcf_field=field("ICR", ("BERRCF",), 0x20, 8),
        arlocf_field=field("ICR", ("ARLOCF",), 0x20, 9),
        msen_field=empty_field,
        msdis_field=empty_field,
        svdis_field=empty_field,
        swrst_field=empty_field,
        iadrsz_field=empty_field,
        mread_field=empty_field,
        dadr_field=empty_field,
        iadr_field=empty_field,
        cldiv_field=empty_field,
        chdiv_field=empty_field,
        ckdiv_field=empty_field,
        hold_field=empty_field,
        txcomp_field=empty_field,
        rxrdy_field=empty_field,
        txrdy_field=empty_field,
        nack_field=empty_field,
        arblst_field=empty_field,
    )


def _microchip_i2c_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str, field_name: str, reg_offset: int, bit_offset: int, bit_width: int = 1
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=empty_reg,
        ccr_reg=empty_reg,
        trise_reg=empty_reg,
        sr1_reg=empty_reg,
        sr2_reg=empty_reg,
        dr_reg=empty_reg,
        icr_reg=empty_reg,
        cr_reg=reg("CR", 0x00),
        mmr_reg=reg("MMR", 0x04),
        iadr_reg=reg("IADR", 0x0C),
        cwgr_reg=reg("CWGR", 0x10),
        sr_reg=reg("SR", 0x20),
        rhr_reg=reg("RHR", 0x30),
        thr_reg=reg("THR", 0x34),
        pe_field=empty_field,
        ack_field=empty_field,
        start_field=empty_field,
        stop_field=empty_field,
        freq_field=empty_field,
        ccr_field=empty_field,
        fs_field=empty_field,
        duty_field=empty_field,
        trise_field=empty_field,
        sb_field=empty_field,
        addr_field=empty_field,
        txe_field=empty_field,
        rxne_field=empty_field,
        btf_field=empty_field,
        af_field=empty_field,
        berr_field=empty_field,
        arlo_field=empty_field,
        busy_field=empty_field,
        dr_data_field=empty_field,
        sadd_field=empty_field,
        rd_wrn_field=empty_field,
        nbytes_field=empty_field,
        autoend_field=empty_field,
        txis_field=empty_field,
        tc_field=empty_field,
        stopf_field=empty_field,
        txdata_field=field("THR", "TXDATA", 0x34, 0, 8),
        rxdata_field=field("RHR", "RXDATA", 0x30, 0, 8),
        nackf_field=empty_field,
        berr_isr_field=empty_field,
        arlo_isr_field=empty_field,
        stopcf_field=empty_field,
        nackcf_field=empty_field,
        berrcf_field=empty_field,
        arlocf_field=empty_field,
        msen_field=field("CR", "MSEN", 0x00, 2),
        msdis_field=field("CR", "MSDIS", 0x00, 3),
        svdis_field=field("CR", "SVDIS", 0x00, 5),
        swrst_field=field("CR", "SWRST", 0x00, 7),
        iadrsz_field=field("MMR", "IADRSZ", 0x04, 8, 2),
        mread_field=field("MMR", "MREAD", 0x04, 12),
        dadr_field=field("MMR", "DADR", 0x04, 16, 7),
        iadr_field=field("IADR", "IADR", 0x0C, 0, 24),
        cldiv_field=field("CWGR", "CLDIV", 0x10, 0, 8),
        chdiv_field=field("CWGR", "CHDIV", 0x10, 8, 8),
        ckdiv_field=field("CWGR", "CKDIV", 0x10, 16, 3),
        hold_field=field("CWGR", "HOLD", 0x10, 24, 5),
        txcomp_field=field("SR", "TXCOMP", 0x20, 0),
        rxrdy_field=field("SR", "RXRDY", 0x20, 1),
        txrdy_field=field("SR", "TXRDY", 0x20, 2),
        nack_field=field("SR", "NACK", 0x20, 8),
        arblst_field=field("SR", "ARBLST", 0x20, 9),
    )


def _nxp_i2c_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=empty_reg,
        ccr_reg=empty_reg,
        trise_reg=empty_reg,
        sr1_reg=empty_reg,
        sr2_reg=empty_reg,
        dr_reg=empty_reg,
        icr_reg=empty_reg,
        cr_reg=reg("MCR", 0x10),
        mmr_reg=reg("MCFGR1", 0x24),
        iadr_reg=empty_reg,
        cwgr_reg=reg("MCCR0", 0x48),
        sr_reg=reg("MSR", 0x14),
        rhr_reg=reg("MRDR", 0x70),
        thr_reg=reg("MTDR", 0x60),
        pe_field=empty_field,
        ack_field=empty_field,
        start_field=field("MTDR", ("CMD",), 0x60, 8, 3),
        stop_field=field("MTDR", ("CMD",), 0x60, 8, 3),
        freq_field=field("MCFGR1", ("PRESCALE",), 0x24, 8, 3),
        ccr_field=empty_field,
        fs_field=empty_field,
        duty_field=empty_field,
        trise_field=empty_field,
        sb_field=empty_field,
        addr_field=empty_field,
        txe_field=empty_field,
        rxne_field=empty_field,
        btf_field=empty_field,
        af_field=empty_field,
        berr_field=empty_field,
        arlo_field=empty_field,
        busy_field=field("MSR", ("BBF",), 0x14, 25),
        dr_data_field=empty_field,
        sadd_field=field("MTDR", ("DATA",), 0x60, 0, 8),
        rd_wrn_field=empty_field,
        nbytes_field=empty_field,
        autoend_field=empty_field,
        txis_field=field("MSR", ("TDF",), 0x14, 0),
        tc_field=field("MSR", ("SDF",), 0x14, 9),
        stopf_field=field("MSR", ("SDF",), 0x14, 9),
        txdata_field=field("MTDR", ("DATA",), 0x60, 0, 8),
        rxdata_field=field("MRDR", ("DATA",), 0x70, 0, 8),
        nackf_field=field("MSR", ("NDF",), 0x14, 10),
        berr_isr_field=field("MSR", ("FEF",), 0x14, 12),
        arlo_isr_field=field("MSR", ("ALF",), 0x14, 11),
        stopcf_field=empty_field,
        nackcf_field=empty_field,
        berrcf_field=empty_field,
        arlocf_field=empty_field,
        msen_field=field("MCR", ("MEN",), 0x10, 0),
        msdis_field=empty_field,
        svdis_field=empty_field,
        swrst_field=field("MCR", ("RST",), 0x10, 1),
        iadrsz_field=empty_field,
        mread_field=empty_field,
        dadr_field=empty_field,
        iadr_field=empty_field,
        cldiv_field=field("MCCR0", ("CLKLO",), 0x48, 0, 6),
        chdiv_field=field("MCCR0", ("CLKHI",), 0x48, 8, 6),
        ckdiv_field=field("MCFGR1", ("PRESCALE",), 0x24, 8, 3),
        hold_field=field("MCCR0", ("SETHOLD",), 0x48, 16, 6),
        txcomp_field=field("MSR", ("SDF",), 0x14, 9),
        rxrdy_field=field("MSR", ("RDF",), 0x14, 1),
        txrdy_field=field("MSR", ("TDF",), 0x14, 0),
        nack_field=field("MSR", ("NDF",), 0x14, 10),
        arblst_field=field("MSR", ("ALF",), 0x14, 11),
    )


def _build_i2c_rows(context: _SemanticContext) -> tuple[I2cSemanticRow, ...]:
    rows: list[I2cSemanticRow] = []
    for peripheral in context.candidate_peripherals_by_class.get("i2c", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.i2c.st-") and "v1-5" in schema_id:
            rows.append(
                _st_i2c_v1_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id.startswith("alloy.i2c.st-"):
            rows.append(
                _st_i2c_v2_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id == "alloy.i2c.microchip-twihs-z":
            rows.append(
                _microchip_i2c_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id == "alloy.lpi2c1.nxp-lpi2c-v1":
            rows.append(_nxp_i2c_row(context, peripheral_name=peripheral.name, schema_id=schema_id))
    return tuple(rows)


def _st_spi_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> SpiSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return SpiSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=reg("CR1", 0x00),
        cr2_reg=reg("CR2", 0x04),
        sr_reg=reg("SR", 0x08),
        dr_reg=reg("DR", 0x0C),
        cr_reg=_invalid_register_ref(base),
        mr_reg=_invalid_register_ref(base),
        csr_reg=_invalid_register_ref(base),
        tdr_reg=_invalid_register_ref(base),
        rdr_reg=_invalid_register_ref(base),
        cpha_field=field("CR1", ("CPHA",), 0x00, 0),
        cpol_field=field("CR1", ("CPOL",), 0x00, 1),
        mstr_field=field("CR1", ("MSTR",), 0x00, 2),
        br_field=field("CR1", ("BR",), 0x00, 3, 3),
        spe_field=field("CR1", ("SPE",), 0x00, 6),
        lsbfirst_field=field("CR1", ("LSBFIRST",), 0x00, 7),
        ssi_field=field("CR1", ("SSI",), 0x00, 8),
        ssm_field=field("CR1", ("SSM",), 0x00, 9),
        dff_field=field("CR1", ("DFF",), 0x00, 11),
        ds_field=field("CR2", ("DS",), 0x04, 8, 4),
        frxth_field=field("CR2", ("FRXTH",), 0x04, 12),
        txe_field=field("SR", ("TXE",), 0x08, 1),
        rxne_field=field("SR", ("RXNE",), 0x08, 0),
        bsy_field=field("SR", ("BSY",), 0x08, 7),
        dr_data_field=field("DR", ("DR",), 0x0C, 0, 16),
        spien_field=_invalid_field_ref(base),
        spidis_field=_invalid_field_ref(base),
        swrst_field=_invalid_field_ref(base),
        ps_field=_invalid_field_ref(base),
        pcsdec_field=_invalid_field_ref(base),
        modfdis_field=_invalid_field_ref(base),
        pcs_field=_invalid_field_ref(base),
        dlybcs_field=_invalid_field_ref(base),
        ncpha_field=_invalid_field_ref(base),
        bits_field=_invalid_field_ref(base),
        scbr_field=_invalid_field_ref(base),
        dlybs_field=_invalid_field_ref(base),
        dlybct_field=_invalid_field_ref(base),
        tdre_field=_invalid_field_ref(base),
        rdrf_field=_invalid_field_ref(base),
        txempty_field=_invalid_field_ref(base),
        td_field=_invalid_field_ref(base),
        tdr_pcs_field=_invalid_field_ref(base),
        rd_field=_invalid_field_ref(base),
    )


def _microchip_spi_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> SpiSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str, field_name: str, reg_offset: int, bit_offset: int, bit_width: int = 1
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return SpiSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=_invalid_register_ref(base),
        cr2_reg=_invalid_register_ref(base),
        sr_reg=reg("SR", 0x10),
        dr_reg=_invalid_register_ref(base),
        cr_reg=reg("CR", 0x00),
        mr_reg=reg("MR", 0x04),
        csr_reg=reg("CSR[%s]", 0x30),
        tdr_reg=reg("TDR", 0x0C),
        rdr_reg=reg("RDR", 0x08),
        cpha_field=_invalid_field_ref(base),
        cpol_field=field("CSR[%s]", "CPOL", 0x30, 0),
        mstr_field=field("MR", "MSTR", 0x04, 0),
        br_field=_invalid_field_ref(base),
        spe_field=_invalid_field_ref(base),
        lsbfirst_field=_invalid_field_ref(base),
        ssi_field=_invalid_field_ref(base),
        ssm_field=_invalid_field_ref(base),
        dff_field=_invalid_field_ref(base),
        ds_field=_invalid_field_ref(base),
        frxth_field=_invalid_field_ref(base),
        txe_field=_invalid_field_ref(base),
        rxne_field=_invalid_field_ref(base),
        bsy_field=_invalid_field_ref(base),
        dr_data_field=_invalid_field_ref(base),
        spien_field=field("CR", "SPIEN", 0x00, 0),
        spidis_field=field("CR", "SPIDIS", 0x00, 1),
        swrst_field=field("CR", "SWRST", 0x00, 7),
        ps_field=field("MR", "PS", 0x04, 1),
        pcsdec_field=field("MR", "PCSDEC", 0x04, 2),
        modfdis_field=field("MR", "MODFDIS", 0x04, 4),
        pcs_field=field("MR", "PCS", 0x04, 16, 4),
        dlybcs_field=field("MR", "DLYBCS", 0x04, 24, 8),
        ncpha_field=field("CSR[%s]", "NCPHA", 0x30, 1),
        bits_field=field("CSR[%s]", "BITS", 0x30, 4, 4),
        scbr_field=field("CSR[%s]", "SCBR", 0x30, 8, 8),
        dlybs_field=field("CSR[%s]", "DLYBS", 0x30, 16, 8),
        dlybct_field=field("CSR[%s]", "DLYBCT", 0x30, 24, 8),
        tdre_field=field("SR", "TDRE", 0x10, 1),
        rdrf_field=field("SR", "RDRF", 0x10, 0),
        txempty_field=field("SR", "TXEMPTY", 0x10, 9),
        td_field=field("TDR", "TD", 0x0C, 0, 16),
        tdr_pcs_field=field("TDR", "PCS", 0x0C, 16, 4),
        rd_field=field("RDR", "RD", 0x08, 0, 16),
    )


def _nxp_spi_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> SpiSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return SpiSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=_invalid_register_ref(base),
        cr2_reg=_invalid_register_ref(base),
        sr_reg=reg("SR", 0x14),
        dr_reg=_invalid_register_ref(base),
        cr_reg=reg("CR", 0x10),
        mr_reg=reg("CFGR1", 0x24),
        csr_reg=reg("CCR", 0x40),
        tdr_reg=reg("TDR", 0x64),
        rdr_reg=reg("RDR", 0x74),
        cpha_field=field("TCR", ("CPHA",), 0x60, 30),
        cpol_field=field("TCR", ("CPOL",), 0x60, 31),
        mstr_field=field("CFGR1", ("MASTER",), 0x24, 0),
        br_field=field("TCR", ("PRESCALE",), 0x60, 27, 3),
        spe_field=field("CR", ("MEN",), 0x10, 0),
        lsbfirst_field=field("TCR", ("LSBF",), 0x60, 23),
        ssi_field=_invalid_field_ref(base),
        ssm_field=_invalid_field_ref(base),
        dff_field=_invalid_field_ref(base),
        ds_field=field("TCR", ("FRAMESZ",), 0x60, 0, 12),
        frxth_field=_invalid_field_ref(base),
        txe_field=field("SR", ("TDF",), 0x14, 0),
        rxne_field=field("SR", ("RDF",), 0x14, 1),
        bsy_field=field("SR", ("MBF",), 0x14, 24),
        dr_data_field=_invalid_field_ref(base),
        spien_field=_invalid_field_ref(base),
        spidis_field=_invalid_field_ref(base),
        swrst_field=field("CR", ("RST",), 0x10, 1),
        ps_field=_invalid_field_ref(base),
        pcsdec_field=_invalid_field_ref(base),
        modfdis_field=_invalid_field_ref(base),
        pcs_field=field("TCR", ("PCS",), 0x60, 24, 2),
        dlybcs_field=_invalid_field_ref(base),
        ncpha_field=_invalid_field_ref(base),
        bits_field=field("TCR", ("FRAMESZ",), 0x60, 0, 12),
        scbr_field=field("CCR", ("SCKDIV",), 0x40, 0, 8),
        dlybs_field=field("CCR", ("PCSSCK",), 0x40, 8, 8),
        dlybct_field=field("CCR", ("DBT",), 0x40, 16, 8),
        tdre_field=_invalid_field_ref(base),
        rdrf_field=_invalid_field_ref(base),
        txempty_field=_invalid_field_ref(base),
        td_field=field("TDR", ("TXDATA",), 0x64, 0, 32),
        tdr_pcs_field=_invalid_field_ref(base),
        rd_field=field("RDR", ("RXDATA",), 0x74, 0, 32),
    )


def _build_spi_rows(context: _SemanticContext) -> tuple[SpiSemanticRow, ...]:
    rows: list[SpiSemanticRow] = []
    for peripheral in context.candidate_peripherals_by_class.get("spi", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.spi.st-"):
            rows.append(_st_spi_row(context, peripheral_name=peripheral.name, schema_id=schema_id))
        elif schema_id == "alloy.spi.microchip-spi-zm":
            rows.append(
                _microchip_spi_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id == "alloy.spi.nxp-lpspi-v1":
            rows.append(_nxp_spi_row(context, peripheral_name=peripheral.name, schema_id=schema_id))
    return tuple(rows)


def _resolve_dma_router_peripheral(context: _SemanticContext) -> PeripheralInstance | None:
    routers = tuple(
        peripheral
        for peripheral in sorted(context.peripheral_by_name.values(), key=lambda item: item.name)
        if canonical_peripheral_class(peripheral.ip_name) == "dma-router"
    )
    if not routers:
        return None
    return routers[0]


def _build_dma_rows(context: _SemanticContext) -> tuple[DmaSemanticRow, ...]:
    runtime_peripheral_names = {
        peripheral.name
        for peripheral in context.peripheral_by_name.values()
        if canonical_peripheral_class(peripheral.ip_name)
        in {"gpio", "uart", "i2c", "spi", "dma", "dma-router"}
    }
    router = _resolve_dma_router_peripheral(context)
    rows: list[DmaSemanticRow] = []
    for binding in _runtime_lite_dma_bindings(context.device):
        if binding.peripheral not in runtime_peripheral_names or binding.signal is None:
            continue
        controller = context.peripheral_by_name.get(binding.controller)
        if controller is None:
            continue
        controller_schema_id = controller.backend_schema_id
        route_selector_field = _invalid_indexed_field_ref(controller.base_address)
        router_name: str | None = None
        router_schema_id: str | None = None
        if controller_schema_id == "alloy.dma.st-bdma-v1-0":
            if router is not None:
                router_name = router.name
                router_schema_id = router.backend_schema_id
                route_selector_field = _indexed_field_ref(
                    base_address=router.base_address,
                    base_offset_bytes=0x00,
                    stride_bytes=0x04,
                    bit_offset=0,
                    bit_width=8,
                )
        elif controller_schema_id == "alloy.dma.st-bdma-f4-v1-0":
            route_selector_field = _indexed_field_ref(
                base_address=controller.base_address,
                base_offset_bytes=0x10,
                stride_bytes=0x18,
                bit_offset=25,
                bit_width=3,
            )
        elif controller_schema_id == "alloy.dma.microchip-xdmac-k":
            route_selector_field = _indexed_field_ref(
                base_address=controller.base_address,
                base_offset_bytes=0x78,
                stride_bytes=0x40,
                bit_offset=24,
                bit_width=7,
            )
        rows.append(
            DmaSemanticRow(
                peripheral_name=binding.peripheral,
                signal_name=binding.signal,
                binding_id=binding.binding_id,
                controller_name=binding.controller,
                request_line=binding.request_line,
                route_id=binding.route_id,
                conflict_group=binding.conflict_group,
                controller_schema_id=controller_schema_id,
                router_name=router_name,
                router_schema_id=router_schema_id,
                channel_index=binding.channel_index,
                request_value=binding.request_value,
                channel_selector=binding.channel_selector,
                route_selector_field=route_selector_field,
            )
        )
    return tuple(rows)


def _emit_driver_semantics_common_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    body = "\n".join(
        [
            "struct RuntimeRegisterRef {",
            "  RegisterId register_id = RegisterId::none;",
            "  std::uintptr_t base_address = 0u;",
            "  std::uint32_t offset_bytes = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct RuntimeFieldRef {",
            "  FieldId field_id = FieldId::none;",
            "  RuntimeRegisterRef reg{};",
            "  std::uint16_t bit_offset = 0u;",
            "  std::uint16_t bit_width = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct RuntimeIndexedFieldRef {",
            "  std::uintptr_t base_address = 0u;",
            "  std::uint32_t base_offset_bytes = 0u;",
            "  std::uint32_t stride_bytes = 0u;",
            "  std::uint16_t bit_offset = 0u;",
            "  std::uint16_t bit_width = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "inline constexpr RuntimeRegisterRef kInvalidRegisterRef{};",
            "inline constexpr RuntimeFieldRef kInvalidFieldRef{};",
            "inline constexpr RuntimeIndexedFieldRef kInvalidIndexedFieldRef{};",
        ]
    )
    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        body,
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <cstdint>",
            '#include "../peripheral_instances.hpp"',
            '#include "../registers.hpp"',
            '#include "../register_fields.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            COMMON_DRIVER_HEADER,
        ),
        content=content,
    )


def _emit_gpio_semantics_header(*, family_dir: str, device: CanonicalDeviceIR) -> EmittedArtifact:
    context = _context(device)
    rows = _build_gpio_rows(context)
    trait_lines = [
        "template<PinId Id>",
        "struct GpioSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr PeripheralId kPeripheralId = PeripheralId::none;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr std::uint32_t kLineIndex = 0u;",
        "  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInputField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputValueField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputSetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputResetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioOutputEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioOutputDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioSetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioClearField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioInputStateField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioDriveEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioDriveDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullUpEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullUpDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullDownEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullDownDisableField = kInvalidFieldRef;",
        "};",
        "",
    ]
    pin_rows: list[str] = []
    for row in rows:
        pin_id = _enum_identifier(row.pin_name)
        trait_lines.extend(
            [
                "template<>",
                f"struct GpioSemanticTraits<PinId::{pin_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr PeripheralId kPeripheralId = {_peripheral_ref(row.peripheral_name)};",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                f"  static constexpr std::uint32_t kLineIndex = {row.line_index}u;",
                f"  static constexpr RuntimeFieldRef kModeField = {_field_ref_expr(row.mode_field)};",
                f"  static constexpr RuntimeFieldRef kDirectionField = {_field_ref_expr(row.direction_field)};",
                f"  static constexpr RuntimeFieldRef kOutputTypeField = {_field_ref_expr(row.output_type_field)};",
                f"  static constexpr RuntimeFieldRef kPullField = {_field_ref_expr(row.pull_field)};",
                f"  static constexpr RuntimeFieldRef kInputField = {_field_ref_expr(row.input_field)};",
                f"  static constexpr RuntimeFieldRef kOutputValueField = {_field_ref_expr(row.output_value_field)};",
                f"  static constexpr RuntimeFieldRef kOutputSetField = {_field_ref_expr(row.output_set_field)};",
                f"  static constexpr RuntimeFieldRef kOutputResetField = {_field_ref_expr(row.output_reset_field)};",
                f"  static constexpr RuntimeFieldRef kPioEnableField = {_field_ref_expr(row.pio_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioOutputEnableField = {_field_ref_expr(row.pio_output_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioOutputDisableField = {_field_ref_expr(row.pio_output_disable_field)};",
                f"  static constexpr RuntimeFieldRef kPioSetField = {_field_ref_expr(row.pio_set_field)};",
                f"  static constexpr RuntimeFieldRef kPioClearField = {_field_ref_expr(row.pio_clear_field)};",
                f"  static constexpr RuntimeFieldRef kPioInputStateField = {_field_ref_expr(row.pio_input_state_field)};",
                f"  static constexpr RuntimeFieldRef kPioDriveEnableField = {_field_ref_expr(row.pio_drive_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioDriveDisableField = {_field_ref_expr(row.pio_drive_disable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullUpEnableField = {_field_ref_expr(row.pio_pull_up_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullUpDisableField = {_field_ref_expr(row.pio_pull_up_disable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullDownEnableField = {_field_ref_expr(row.pio_pull_down_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullDownDisableField = {_field_ref_expr(row.pio_pull_down_disable_field)};",
                "};",
                "",
            ]
        )
        pin_rows.append(f"  PinId::{pin_id},")
    body = "\n".join(
        [
            *trait_lines,
            *_std_array_lines(
                type_name="PinId", variable_name="kGpioSemanticPins", row_lines=pin_rows
            ),
        ]
    )
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
            '#include "../pins.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, GPIO_DRIVER_HEADER),
        content=content,
    )


def _emit_peripheral_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
    header_name: str,
    trait_name: str,
    array_name: str,
    rows: tuple[UartSemanticRow | I2cSemanticRow | SpiSemanticRow, ...],
    default_lines: list[str],
    specialization_builder,
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
        trait_lines.extend(
            [
                "template<>",
                f"struct {trait_name}<PeripheralId::{peripheral_id}> {{",
                *specialization_builder(row),
                "};",
                "",
            ]
        )
        peripheral_rows.append(f"  PeripheralId::{peripheral_id},")
    body = "\n".join(
        [
            *trait_lines,
            *_std_array_lines(
                type_name="PeripheralId",
                variable_name=array_name,
                row_lines=peripheral_rows,
            ),
        ]
    )
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
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, header_name),
        content=content,
    )


def _uart_specialization_builder(context: _SemanticContext):
    def _build(row: UartSemanticRow) -> list[str]:
        return [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr RuntimeRegisterRef kCr1Register = {_register_ref_expr(row.cr1_reg)};",
            f"  static constexpr RuntimeRegisterRef kCr2Register = {_register_ref_expr(row.cr2_reg)};",
            f"  static constexpr RuntimeRegisterRef kBrrRegister = {_register_ref_expr(row.brr_reg)};",
            f"  static constexpr RuntimeRegisterRef kIsrRegister = {_register_ref_expr(row.isr_reg)};",
            f"  static constexpr RuntimeRegisterRef kRdrRegister = {_register_ref_expr(row.rdr_reg)};",
            f"  static constexpr RuntimeRegisterRef kTdrRegister = {_register_ref_expr(row.tdr_reg)};",
            f"  static constexpr RuntimeRegisterRef kSrRegister = {_register_ref_expr(row.sr_reg)};",
            f"  static constexpr RuntimeRegisterRef kDrRegister = {_register_ref_expr(row.dr_reg)};",
            f"  static constexpr RuntimeRegisterRef kCrRegister = {_register_ref_expr(row.cr_reg)};",
            f"  static constexpr RuntimeRegisterRef kMrRegister = {_register_ref_expr(row.mr_reg)};",
            f"  static constexpr RuntimeRegisterRef kBrgrRegister = {_register_ref_expr(row.brgr_reg)};",
            f"  static constexpr RuntimeRegisterRef kThrRegister = {_register_ref_expr(row.thr_reg)};",
            f"  static constexpr RuntimeRegisterRef kUsCrRegister = {_register_ref_expr(row.us_cr_reg)};",
            f"  static constexpr RuntimeRegisterRef kUsMrRegister = {_register_ref_expr(row.us_mr_reg)};",
            f"  static constexpr RuntimeRegisterRef kUsBrgrRegister = {_register_ref_expr(row.us_brgr_reg)};",
            f"  static constexpr RuntimeRegisterRef kUsThrRegister = {_register_ref_expr(row.us_thr_reg)};",
            f"  static constexpr RuntimeFieldRef kUeField = {_field_ref_expr(row.ue_field)};",
            f"  static constexpr RuntimeFieldRef kReField = {_field_ref_expr(row.re_field)};",
            f"  static constexpr RuntimeFieldRef kTeField = {_field_ref_expr(row.te_field)};",
            f"  static constexpr RuntimeFieldRef kPceField = {_field_ref_expr(row.pce_field)};",
            f"  static constexpr RuntimeFieldRef kPsField = {_field_ref_expr(row.ps_field)};",
            f"  static constexpr RuntimeFieldRef kM0Field = {_field_ref_expr(row.m0_field)};",
            f"  static constexpr RuntimeFieldRef kM1Field = {_field_ref_expr(row.m1_field)};",
            f"  static constexpr RuntimeFieldRef kMField = {_field_ref_expr(row.m_field)};",
            f"  static constexpr RuntimeFieldRef kStopField = {_field_ref_expr(row.stop_field)};",
            f"  static constexpr RuntimeFieldRef kTdrField = {_field_ref_expr(row.tdr_field)};",
            f"  static constexpr RuntimeFieldRef kRdrField = {_field_ref_expr(row.rdr_field)};",
            f"  static constexpr RuntimeFieldRef kTxeIsrField = {_field_ref_expr(row.txe_isr_field)};",
            f"  static constexpr RuntimeFieldRef kRxneIsrField = {_field_ref_expr(row.rxne_isr_field)};",
            f"  static constexpr RuntimeFieldRef kTcIsrField = {_field_ref_expr(row.tc_isr_field)};",
            f"  static constexpr RuntimeFieldRef kTxeSrField = {_field_ref_expr(row.txe_sr_field)};",
            f"  static constexpr RuntimeFieldRef kRxneSrField = {_field_ref_expr(row.rxne_sr_field)};",
            f"  static constexpr RuntimeFieldRef kTcSrField = {_field_ref_expr(row.tc_sr_field)};",
            f"  static constexpr RuntimeFieldRef kDrField = {_field_ref_expr(row.dr_field)};",
            f"  static constexpr RuntimeFieldRef kRstrxField = {_field_ref_expr(row.rstrx_field)};",
            f"  static constexpr RuntimeFieldRef kRsttxField = {_field_ref_expr(row.rsttx_field)};",
            f"  static constexpr RuntimeFieldRef kRxdisField = {_field_ref_expr(row.rxdis_field)};",
            f"  static constexpr RuntimeFieldRef kTxdisField = {_field_ref_expr(row.txdis_field)};",
            f"  static constexpr RuntimeFieldRef kRststaField = {_field_ref_expr(row.rststa_field)};",
            f"  static constexpr RuntimeFieldRef kParField = {_field_ref_expr(row.par_field)};",
            f"  static constexpr RuntimeFieldRef kChmodeField = {_field_ref_expr(row.chmode_field)};",
            f"  static constexpr RuntimeFieldRef kCdField = {_field_ref_expr(row.cd_field)};",
            f"  static constexpr RuntimeFieldRef kRxenField = {_field_ref_expr(row.rxen_field)};",
            f"  static constexpr RuntimeFieldRef kTxenField = {_field_ref_expr(row.txen_field)};",
            f"  static constexpr RuntimeFieldRef kTxrdyField = {_field_ref_expr(row.txrdy_field)};",
            f"  static constexpr RuntimeFieldRef kRxrdyField = {_field_ref_expr(row.rxrdy_field)};",
            f"  static constexpr RuntimeFieldRef kTxemptyField = {_field_ref_expr(row.txempty_field)};",
            f"  static constexpr RuntimeFieldRef kTxchrField = {_field_ref_expr(row.txchr_field)};",
            f"  static constexpr RuntimeFieldRef kRxchrField = {_field_ref_expr(row.rxchr_field)};",
            f"  static constexpr RuntimeFieldRef kUsRstrxField = {_field_ref_expr(row.us_rstrx_field)};",
            f"  static constexpr RuntimeFieldRef kUsRsttxField = {_field_ref_expr(row.us_rsttx_field)};",
            f"  static constexpr RuntimeFieldRef kUsRxdisField = {_field_ref_expr(row.us_rxdis_field)};",
            f"  static constexpr RuntimeFieldRef kUsTxdisField = {_field_ref_expr(row.us_txdis_field)};",
            f"  static constexpr RuntimeFieldRef kUsRststaField = {_field_ref_expr(row.us_rststa_field)};",
            f"  static constexpr RuntimeFieldRef kUsUsartModeField = {_field_ref_expr(row.us_usart_mode_field)};",
            f"  static constexpr RuntimeFieldRef kUsUsclksField = {_field_ref_expr(row.us_usclks_field)};",
            f"  static constexpr RuntimeFieldRef kUsChrlField = {_field_ref_expr(row.us_chrl_field)};",
            f"  static constexpr RuntimeFieldRef kUsCdField = {_field_ref_expr(row.us_cd_field)};",
            f"  static constexpr RuntimeFieldRef kUsRxenField = {_field_ref_expr(row.us_rxen_field)};",
            f"  static constexpr RuntimeFieldRef kUsTxenField = {_field_ref_expr(row.us_txen_field)};",
            f"  static constexpr RuntimeFieldRef kUsTxrdyField = {_field_ref_expr(row.us_txrdy_field)};",
            f"  static constexpr RuntimeFieldRef kUsRxrdyField = {_field_ref_expr(row.us_rxrdy_field)};",
            f"  static constexpr RuntimeFieldRef kUsTxemptyField = {_field_ref_expr(row.us_txempty_field)};",
            f"  static constexpr RuntimeFieldRef kUsTxchrField = {_field_ref_expr(row.us_txchr_field)};",
            f"  static constexpr RuntimeFieldRef kUsRxchrField = {_field_ref_expr(row.us_rxchr_field)};",
        ]

    return _build


def _i2c_specialization_builder(context: _SemanticContext):
    def _build(row: I2cSemanticRow) -> list[str]:
        register_members = {
            "kCr1Register": row.cr1_reg,
            "kCr2Register": row.cr2_reg,
            "kCcrRegister": row.ccr_reg,
            "kTriseRegister": row.trise_reg,
            "kSr1Register": row.sr1_reg,
            "kSr2Register": row.sr2_reg,
            "kDrRegister": row.dr_reg,
            "kIcrRegister": row.icr_reg,
            "kCrRegister": row.cr_reg,
            "kMmrRegister": row.mmr_reg,
            "kIadrRegister": row.iadr_reg,
            "kCwgrRegister": row.cwgr_reg,
            "kSrRegister": row.sr_reg,
            "kRhrRegister": row.rhr_reg,
            "kThrRegister": row.thr_reg,
        }
        field_members = {
            "kPeField": row.pe_field,
            "kAckField": row.ack_field,
            "kStartField": row.start_field,
            "kStopField": row.stop_field,
            "kFreqField": row.freq_field,
            "kCcrField": row.ccr_field,
            "kFsField": row.fs_field,
            "kDutyField": row.duty_field,
            "kTriseField": row.trise_field,
            "kSbField": row.sb_field,
            "kAddrField": row.addr_field,
            "kTxeField": row.txe_field,
            "kRxneField": row.rxne_field,
            "kBtfField": row.btf_field,
            "kAfField": row.af_field,
            "kBerrField": row.berr_field,
            "kArloField": row.arlo_field,
            "kBusyField": row.busy_field,
            "kDrDataField": row.dr_data_field,
            "kSaddField": row.sadd_field,
            "kRdWrnField": row.rd_wrn_field,
            "kNbytesField": row.nbytes_field,
            "kAutoendField": row.autoend_field,
            "kTxisField": row.txis_field,
            "kTcField": row.tc_field,
            "kStopfField": row.stopf_field,
            "kTxdataField": row.txdata_field,
            "kRxdataField": row.rxdata_field,
            "kNackfField": row.nackf_field,
            "kBerrIsrField": row.berr_isr_field,
            "kArloIsrField": row.arlo_isr_field,
            "kStopcfField": row.stopcf_field,
            "kNackcfField": row.nackcf_field,
            "kBerrcfField": row.berrcf_field,
            "kArlocfField": row.arlocf_field,
            "kMsenField": row.msen_field,
            "kMsdisField": row.msdis_field,
            "kSvdisField": row.svdis_field,
            "kSwrstField": row.swrst_field,
            "kIadrszField": row.iadrsz_field,
            "kMreadField": row.mread_field,
            "kDadrField": row.dadr_field,
            "kIadrField": row.iadr_field,
            "kCldivField": row.cldiv_field,
            "kChdivField": row.chdiv_field,
            "kCkdivField": row.ckdiv_field,
            "kHoldField": row.hold_field,
            "kTxcompField": row.txcomp_field,
            "kRxrdyField": row.rxrdy_field,
            "kTxrdyField": row.txrdy_field,
            "kNackField": row.nack_field,
            "kArblstField": row.arblst_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        return lines

    return _build


def _spi_specialization_builder(context: _SemanticContext):
    def _build(row: SpiSemanticRow) -> list[str]:
        register_members = {
            "kCr1Register": row.cr1_reg,
            "kCr2Register": row.cr2_reg,
            "kSrRegister": row.sr_reg,
            "kDrRegister": row.dr_reg,
            "kCrRegister": row.cr_reg,
            "kMrRegister": row.mr_reg,
            "kCsrRegister": row.csr_reg,
            "kTdrRegister": row.tdr_reg,
            "kRdrRegister": row.rdr_reg,
        }
        field_members = {
            "kCphaField": row.cpha_field,
            "kCpolField": row.cpol_field,
            "kMstrField": row.mstr_field,
            "kBrField": row.br_field,
            "kSpeField": row.spe_field,
            "kLsbfirstField": row.lsbfirst_field,
            "kSsiField": row.ssi_field,
            "kSsmField": row.ssm_field,
            "kDffField": row.dff_field,
            "kDsField": row.ds_field,
            "kFrxthField": row.frxth_field,
            "kTxeField": row.txe_field,
            "kRxneField": row.rxne_field,
            "kBsyField": row.bsy_field,
            "kDrDataField": row.dr_data_field,
            "kSpienField": row.spien_field,
            "kSpidisField": row.spidis_field,
            "kSwrstField": row.swrst_field,
            "kPsField": row.ps_field,
            "kPcsdecField": row.pcsdec_field,
            "kModfdisField": row.modfdis_field,
            "kPcsField": row.pcs_field,
            "kDlybcsField": row.dlybcs_field,
            "kNcphaField": row.ncpha_field,
            "kBitsField": row.bits_field,
            "kScbrField": row.scbr_field,
            "kDlybsField": row.dlybs_field,
            "kDlybctField": row.dlybct_field,
            "kTdreField": row.tdre_field,
            "kRdrfField": row.rdrf_field,
            "kTxemptyField": row.txempty_field,
            "kTdField": row.td_field,
            "kTdrPcsField": row.tdr_pcs_field,
            "kRdField": row.rd_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        return lines

    return _build


def emit_runtime_driver_semantics_common_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    return _emit_driver_semantics_common_header(family_dir=family_dir, device=device)


def emit_runtime_driver_gpio_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    return _emit_gpio_semantics_header(family_dir=family_dir, device=device)


def emit_runtime_driver_uart_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_uart_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kMrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kBrgrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kUsCrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kUsMrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kUsBrgrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kUsThrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kUeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kReField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPceField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kM0Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kM1Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTdrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRdrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxeIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxneIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTcIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxeSrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxneSrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTcSrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRstrxField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRsttxField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRststaField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kParField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kChmodeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCdField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxenField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxenField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxemptyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxchrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxchrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRstrxField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRsttxField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRxdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsTxdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRststaField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsUsartModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsUsclksField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsChrlField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsCdField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRxenField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsTxenField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsTxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsTxemptyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsTxchrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUsRxchrField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=UART_DRIVER_HEADER,
        trait_name="UartSemanticTraits",
        array_name="kUartSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_uart_specialization_builder(context),
    )


def emit_runtime_driver_i2c_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_i2c_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCcrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTriseRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSr1Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSr2Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kIcrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kMmrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kIadrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCwgrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRhrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kPeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAckField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFreqField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCcrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDutyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTriseField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSbField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAddrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxneField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBtfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBerrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArloField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBusyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDrDataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSaddField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRdWrnField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNbytesField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAutoendField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTcField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxdataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxdataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNackfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBerrIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArloIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopcfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNackcfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBerrcfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArlocfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMsenField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMsdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSvdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSwrstField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kIadrszField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMreadField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDadrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kIadrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCldivField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kChdivField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCkdivField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kHoldField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxcompField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNackField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArblstField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=I2C_DRIVER_HEADER,
        trait_name="I2cSemanticTraits",
        array_name="kI2cSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_i2c_specialization_builder(context),
    )


def emit_runtime_driver_spi_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_spi_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kMrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCsrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kCphaField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCpolField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMstrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSpeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kLsbfirstField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSsiField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSsmField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDffField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFrxthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxneField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBsyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDrDataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSpienField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSpidisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSwrstField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPcsdecField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kModfdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPcsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDlybcsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNcphaField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBitsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kScbrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDlybsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDlybctField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTdreField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRdrfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxemptyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTdField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTdrPcsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRdField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=SPI_DRIVER_HEADER,
        trait_name="SpiSemanticTraits",
        array_name="kSpiSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_spi_specialization_builder(context),
    )


def emit_runtime_driver_dma_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_dma_rows(context)
    trait_lines = [
        "template<PeripheralId Peripheral, SignalId Signal>",
        "struct DmaSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr DmaBindingId kBindingId = DmaBindingId::none;",
        "  static constexpr DmaControllerId kControllerId = DmaControllerId::none;",
        "  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::none;",
        "  static constexpr DmaRouteId kRouteId = DmaRouteId::none;",
        "  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;",
        "  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::none;",
        "  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;",
        "  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::none;",
        "  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;",
        "  static constexpr int kChannelIndex = -1;",
        "  static constexpr int kRequestValue = -1;",
        "  static constexpr int kChannelSelector = -1;",
        "  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;",
        "};",
        "",
    ]
    row_lines: list[str] = []
    for row in rows:
        signal_ref = _semantic_enum_ref(
            "SignalId",
            context.semantics_catalog["signal_enum_map"],
            row.signal_name,
        )
        trait_lines.extend(
            [
                "template<>",
                f"struct DmaSemanticTraits<PeripheralId::{_enum_identifier(row.peripheral_name)}, {signal_ref}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr DmaBindingId kBindingId = DmaBindingId::{_enum_identifier(row.binding_id)};",
                f"  static constexpr DmaControllerId kControllerId = DmaControllerId::{_enum_identifier(row.controller_name)};",
                f"  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::{_enum_identifier(row.request_line)};",
                f"  static constexpr DmaRouteId kRouteId = DmaRouteId::{_enum_identifier(row.route_id)};",
                "  static constexpr DmaConflictGroupId kConflictGroupId = "
                + (
                    "DmaConflictGroupId::none"
                    if row.conflict_group is None
                    else f"DmaConflictGroupId::{_enum_identifier(row.conflict_group)}"
                )
                + ";",
                f"  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::{_enum_identifier(row.controller_name)};",
                "  static constexpr PeripheralId kRouterPeripheralId = "
                + (
                    "PeripheralId::none"
                    if row.router_name is None
                    else f"PeripheralId::{_enum_identifier(row.router_name)}"
                )
                + ";",
                "  static constexpr BackendSchemaId kControllerSchemaId = "
                + _schema_ref_expr(context, row.controller_schema_id)
                + ";",
                "  static constexpr BackendSchemaId kRouterSchemaId = "
                + _schema_ref_expr(context, row.router_schema_id)
                + ";",
                f"  static constexpr int kChannelIndex = {row.channel_index if row.channel_index is not None else -1};",
                f"  static constexpr int kRequestValue = {row.request_value if row.request_value is not None else -1};",
                f"  static constexpr int kChannelSelector = {row.channel_selector if row.channel_selector is not None else -1};",
                "  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = "
                + _indexed_field_ref_expr(row.route_selector_field)
                + ";",
                "};",
                "",
            ]
        )
        row_lines.append(
            f"  PeripheralId::{_enum_identifier(row.peripheral_name)},"
        )

    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        "\n".join(
            [
                *trait_lines,
                *_std_array_lines(
                    type_name="PeripheralId",
                    variable_name="kDmaSemanticPeripherals",
                    row_lines=row_lines,
                ),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "common.hpp"',
            '#include "../dma_bindings.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            DMA_DRIVER_HEADER,
        ),
        content=content,
    )


__all__ = [
    "emit_runtime_driver_dma_semantics_header",
    "emit_runtime_driver_gpio_semantics_header",
    "emit_runtime_driver_i2c_semantics_header",
    "emit_runtime_driver_semantics_common_header",
    "emit_runtime_driver_spi_semantics_header",
    "emit_runtime_driver_uart_semantics_header",
    "runtime_driver_semantics_required_paths",
]
