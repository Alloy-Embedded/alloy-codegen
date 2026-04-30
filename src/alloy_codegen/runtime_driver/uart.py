"""UART driver-semantic emitter (STM32 / Microchip / NXP).

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass
from typing import Any

from alloy_codegen.ir.model import CanonicalDeviceIR, PeripheralInstance
from alloy_codegen.peripheral_traits import (
    PeripheralTemplate,
    load_all_templates,
    resolve_template,
    template_provenance_tag,
)
from alloy_codegen.reporting import EmittedArtifact

from ..emission import (
    _enum_identifier,
)
from ..runtime_lite_emission import (
    _runtime_lite_dma_bindings,
)
from .common import (
    KernelClockSourceOption,
    RuntimeFieldRef,
    RuntimeRegisterRef,
    UartDmaBindingRow,
    _context,
    _dma_binding_ref_array_lines,
    _emit_peripheral_semantics_header,
    _field_ref_expr,
    _invalid_field_ref,
    _invalid_register_ref,
    _irq_numbers_for_peripheral,
    _irq_numbers_lines,
    _kernel_clock_for_peripheral,
    _kernel_clock_lines,
    _register_ref_expr,
    _render_typed_option_enum_block,
    _resolve_field_ref,
    _resolve_register_ref,
    _schema_ref_expr,
    _SemanticContext,
)

UART_DRIVER_HEADER = "driver_semantics/uart.hpp"


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
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented
    # Tier 2/3/4 (added by add-uart-spi-tier-2-3-4-data).  Empty tuples /
    # invalid mode-flags block / 0 max baud for families that don't carry
    # the data; the rendered C++ defaults to empty std::array<X, 0>{} so
    # existing goldens stay byte-stable until the specific family's
    # builder populates these fields.
    baud_clock_sources: tuple[UartBaudClockSource, ...] = ()
    baud_oversampling_options: tuple[UartBaudOversamplingOption, ...] = ()
    fifo_trigger_options: tuple[UartFifoTriggerOption, ...] = ()
    data_bits_options: tuple[UartDataBitsOption, ...] = ()
    parity_options: tuple[UartParityOption, ...] = ()
    stop_bits_options: tuple[UartStopBitsOption, ...] = ()
    mode_flags: UartModeFlags | None = None
    max_baud_hz: int = 0
    dma_bindings: tuple[UartDmaBindingRow, ...] = ()
    # NVIC vector lines bound to this peripheral (added by
    # ``add-irq-vector-traits``).  Empty on chips whose
    # ``interrupt_bindings`` haven't surfaced this peripheral yet
    # (e.g. AVR-DA — its vectors aren't modelled as NVIC lines).
    irq_numbers: tuple[int, ...] = ()
    # Kernel-clock traits (added by ``add-kernel-clock-traits``).
    # ``None`` field-refs render as ``kInvalidFieldRef``.
    kernel_clock_selector_field: RuntimeFieldRef | None = None
    kernel_clock_source_options: tuple[KernelClockSourceOption, ...] = ()
    max_clock_hz: int = 0
    clock_gate_field: RuntimeFieldRef | None = None
    # Provenance tag pinned by the peripheral-trait template library when
    # a ``(ip_name, ip_version)`` template was applied during the trait
    # build.  ``None`` means no template matched and the row was built
    # from device-patch values alone.  Added by
    # ``migrate-uart-emitter-to-template-library``.
    template_provenance: str | None = None


# I2cSemanticRow → runtime_driver/i2c.py


# SpiSemanticRow → runtime_driver/spi.py


@dataclass(frozen=True, slots=True)
class UartBaudClockSource:
    """One baud-rate clock source + the field value that selects it."""

    source: str  # "pclk" | "sysclk" | "hsi16" | "lse" | "apb" | "ref_tick" | ...
    field_value: int


@dataclass(frozen=True, slots=True)
class UartBaudOversamplingOption:
    """8x or 16x oversampling option + the field value that selects it."""

    ratio: int  # 8 or 16
    field_value: int


@dataclass(frozen=True, slots=True)
class UartFifoTriggerOption:
    """One FIFO trigger level (Q8.8 fraction) + the field value that selects it."""

    fraction_q8: int  # Q8(1/4)=64, Q8(1/2)=128, Q8(3/4)=192, Q8(1)=256
    field_value: int


@dataclass(frozen=True, slots=True)
class UartDataBitsOption:
    """One supported data-bits option + the M0/M1 field combination."""

    bits: int
    m0_value: int = 0
    m1_value: int = 0


@dataclass(frozen=True, slots=True)
class UartParityOption:
    """One parity option + the PCE/PS field combination."""

    parity: str  # "none" | "even" | "odd" | "mark" | "space"
    pce_value: int
    ps_value: int = 0


@dataclass(frozen=True, slots=True)
class UartStopBitsOption:
    """One stop-bits option (Q8.8 fixed-point) + the field value."""

    stop_bits_q8: int  # Q8(0.5)=128, Q8(1)=256, Q8(1.5)=384, Q8(2)=512
    field_value: int


@dataclass(frozen=True, slots=True)
class UartModeFlags:
    """Per-UART mode capability flags (one block per peripheral)."""

    supports_lin: bool = False
    supports_irda: bool = False
    supports_smartcard: bool = False
    supports_half_duplex: bool = False
    supports_synchronous: bool = False
    supports_auto_baud: bool = False
    supports_wake_from_stop: bool = False
    valid: bool = False  # True when the patch overlay actually populated this


# SpiBaudPrescalerOption → runtime_driver/spi.py


# SpiFrameSizeOption → runtime_driver/spi.py


# SpiFifoThresholdOption → runtime_driver/spi.py


# SpiModeFlags → runtime_driver/spi.py


_UART_PARITY_NAME: dict[str, str] = {
    "none": "none",
    "even": "even",
    "odd": "odd",
    "mark": "mark",
    "space": "space",
}

_UART_PARITY_CANONICAL_ORDER: tuple[str, ...] = ("none", "even", "odd", "mark", "space")

_UART_STOP_BITS_NAME: dict[int, str] = {
    128: "half",  # 0.5 stop bits
    256: "one",  # 1.0
    384: "one_and_half",  # 1.5
    512: "two",  # 2.0
}

_UART_FIFO_TRIGGER_NAME: dict[int, str] = {
    32: "one_eighth",  # 1/8
    64: "quarter",  # 1/4 = 2/8
    128: "half",  # 1/2 = 4/8
    192: "three_quarters",  # 3/4 = 6/8
    224: "seven_eighths",  # 7/8
    256: "full",  # 1 (8/8)
}

# _I2C_SPEED_MODE_NAME → runtime_driver/i2c.py


def _build_uart_typed_enum_blocks(rows: tuple[UartSemanticRow, ...]) -> list[str]:
    """Render UART typed-option enum blocks.  Added by
    ``add-typed-peripheral-enums-everywhere``.

    Emits per-peripheral typed enums for parity, stop bits,
    oversampling, baud-clock source, data bits, and FIFO trigger
    fraction.  Each enum specialisation is paired with a
    ``std::array<std::string_view, N>`` name table so consumers can
    stringify values without a switch statement.
    """
    parity_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    stop_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    over_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    baud_clk_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    data_bits_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    fifo_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    for row in rows:
        if row.is_stub:
            continue
        peripheral_id = _enum_identifier(row.peripheral_name)
        # Parity: canonical positional ordering matches kSupportedParityRaw.
        parity_present = {opt.parity for opt in row.parity_options}
        parity = tuple(
            (_UART_PARITY_NAME[name], idx)
            for idx, name in enumerate(_UART_PARITY_CANONICAL_ORDER)
            if name in parity_present
        )
        if parity:
            parity_entries.append((peripheral_id, parity))
        # Stop bits: positional, indexed in row order (matches kSupportedStopBitsQ8).
        stop = tuple(
            (_UART_STOP_BITS_NAME[opt.stop_bits_q8], idx)
            for idx, opt in enumerate(row.stop_bits_options)
            if opt.stop_bits_q8 in _UART_STOP_BITS_NAME
        )
        if stop:
            stop_entries.append((peripheral_id, stop))
        # Oversampling: 8x or 16x.
        over = tuple(
            (f"over_{opt.ratio}x", idx) for idx, opt in enumerate(row.baud_oversampling_options)
        )
        if over:
            over_entries.append((peripheral_id, over))
        # Baud clock source: classifier strings already canonicalised.
        baud_clk = tuple((str(opt.source), idx) for idx, opt in enumerate(row.baud_clock_sources))
        if baud_clk:
            baud_clk_entries.append((peripheral_id, baud_clk))
        # Data bits.
        data_bits = tuple(
            (f"bits_{opt.bits}", idx) for idx, opt in enumerate(row.data_bits_options)
        )
        if data_bits:
            data_bits_entries.append((peripheral_id, data_bits))
        # FIFO trigger fractions.
        fifo = tuple(
            (_UART_FIFO_TRIGGER_NAME[opt.fraction_q8], idx)
            for idx, opt in enumerate(row.fifo_trigger_options)
            if opt.fraction_q8 in _UART_FIFO_TRIGGER_NAME
        )
        if fifo:
            fifo_entries.append((peripheral_id, fifo))

    lines: list[str] = []
    for spec in (
        ("UartParityOf", "UartParity", parity_entries),
        ("UartStopBitsOf", "UartStopBits", stop_entries),
        ("UartOversamplingOf", "UartOversampling", over_entries),
        ("UartBaudClockSourceOf", "UartBaudClockSource", baud_clk_entries),
        ("UartDataBitsOf", "UartDataBits", data_bits_entries),
        ("UartFifoTriggerOf", "UartFifoTrigger", fifo_entries),
    ):
        template_name, alias_name, entries = spec
        if not any(e for _, e in entries):
            continue
        lines.append(
            f"// add-typed-peripheral-enums-everywhere: typed {template_name} per peripheral."
        )
        lines.extend(
            _render_typed_option_enum_block(
                template_name=template_name,
                alias_name=alias_name,
                peripheral_entries=tuple(entries),
            )
        )
    return lines


# _build_spi_typed_enum_blocks → runtime_driver/spi.py


# _build_i2c_typed_enum_blocks → runtime_driver/i2c.py


def _microchip_uart_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
    usart_prefix: str = "",
    template: PeripheralTemplate | None = None,
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
        **_uart_extension_for_peripheral(
            context, peripheral_name=peripheral_name, template=template
        ),
    )


def _st_uart_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
    f4_layout: bool,
    template: PeripheralTemplate | None = None,
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
        **_uart_extension_for_peripheral(
            context, peripheral_name=peripheral_name, template=template
        ),
    )


def _nxp_uart_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
    template: PeripheralTemplate | None = None,
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
        **_uart_extension_for_peripheral(
            context, peripheral_name=peripheral_name, template=template
        ),
    )


def _uart_template_mode_flags(template: PeripheralTemplate) -> UartModeFlags | None:
    """Project a template's ``mode_flags = [...]`` list into a
    :class:`UartModeFlags` block.  Added by
    ``migrate-uart-emitter-to-template-library``.

    Names recognised: ``has_lin``, ``has_irda``, ``has_smartcard``,
    ``has_auto_baud``, ``has_half_duplex``, ``has_synchronous``,
    ``has_wake_from_stop``.  Other tokens (``has_fifo`` / ``has_dma`` /
    ``has_modbus``) are accepted but do not project — they are
    surfaced via separate IR fields.
    """
    flags = template.values.get("mode_flags")
    if not flags:
        return None
    flag_set = set(flags) if isinstance(flags, (list, tuple, set)) else set()
    return UartModeFlags(
        supports_lin="has_lin" in flag_set,
        supports_irda="has_irda" in flag_set,
        supports_smartcard="has_smartcard" in flag_set,
        supports_half_duplex="has_half_duplex" in flag_set,
        supports_synchronous="has_synchronous" in flag_set,
        supports_auto_baud="has_auto_baud" in flag_set,
        supports_wake_from_stop="has_wake_from_stop" in flag_set,
        valid=True,
    )


def _uart_template_data_bits(template: PeripheralTemplate) -> tuple[UartDataBitsOption, ...]:
    raw = template.values.get("data_bits_options") or ()
    return tuple(UartDataBitsOption(bits=int(b), m0_value=0, m1_value=0) for b in raw)


_UART_PARITY_PCE_PS = {
    "none": (0, 0),
    "even": (1, 0),
    "odd": (1, 1),
    "mark": (1, 0),
    "space": (1, 1),
}


def _uart_template_parity(template: PeripheralTemplate) -> tuple[UartParityOption, ...]:
    raw = template.values.get("parity_options") or ()
    out: list[UartParityOption] = []
    for token in raw:
        name = str(token).lower()
        pce, ps = _UART_PARITY_PCE_PS.get(name, (0, 0))
        out.append(UartParityOption(parity=name, pce_value=pce, ps_value=ps))
    return tuple(out)


_UART_STOP_BITS_Q8: dict[str, int] = {
    "0.5": 4,
    "1": 8,
    "1.5": 12,
    "2": 16,
}


def _uart_template_stop_bits(template: PeripheralTemplate) -> tuple[UartStopBitsOption, ...]:
    raw = template.values.get("stop_bits_options") or ()
    out: list[UartStopBitsOption] = []
    for token in raw:
        key = str(token)
        q8 = _UART_STOP_BITS_Q8.get(key, 0)
        if q8 == 0:
            continue
        out.append(UartStopBitsOption(stop_bits_q8=q8, field_value=0))
    return tuple(out)


def _uart_template_oversampling(
    template: PeripheralTemplate,
) -> tuple[UartBaudOversamplingOption, ...]:
    raw = template.values.get("oversampling_options") or ()
    return tuple(UartBaudOversamplingOption(ratio=int(r), field_value=0) for r in raw)


def _uart_template_fifo_triggers(
    template: PeripheralTemplate,
) -> tuple[UartFifoTriggerOption, ...]:
    raw = template.values.get("fifo_trigger_options") or ()
    # Template integers are field values; fraction_q8 left as 0
    # placeholder unless a device patch supplies the q8 measurement.
    return tuple(UartFifoTriggerOption(fraction_q8=0, field_value=int(v)) for v in raw)


def _uart_extension_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    template: PeripheralTemplate | None = None,
) -> dict[str, Any]:
    """Build the Tier 2/3/4 kwargs for ``UartSemanticRow``.

    Reads the device IR's UART patch tuples (forwarded by
    ``stages/normalize.run``) and returns a dict suitable for ``**``
    unpacking into the row constructor.  DMA bindings are derived
    automatically from ``device.dma_requests``.  Mirrors the ADC
    Tier 2/3/4 extension helper added by ``add-adc-tier-2-3-4-data``.
    """
    device = context.device
    baud_clock_sources = tuple(
        UartBaudClockSource(source=p.source, field_value=p.field_value)
        for p in device.uart_baud_clock_sources
        if getattr(p, "peripheral", None) == peripheral_name
    )
    baud_oversampling_options = tuple(
        UartBaudOversamplingOption(ratio=p.ratio, field_value=p.field_value)
        for p in device.uart_baud_oversampling_options
        if getattr(p, "peripheral", None) == peripheral_name
    )
    fifo_trigger_options = tuple(
        UartFifoTriggerOption(fraction_q8=p.fraction_q8, field_value=p.field_value)
        for p in device.uart_fifo_trigger_options
        if getattr(p, "peripheral", None) == peripheral_name
    )
    data_bits_options = tuple(
        UartDataBitsOption(bits=p.bits, m0_value=p.m0_value, m1_value=p.m1_value)
        for p in device.uart_data_bits_options
        if getattr(p, "peripheral", None) == peripheral_name
    )
    parity_options = tuple(
        UartParityOption(parity=p.parity, pce_value=p.pce_value, ps_value=p.ps_value)
        for p in device.uart_parity_options
        if getattr(p, "peripheral", None) == peripheral_name
    )
    stop_bits_options = tuple(
        UartStopBitsOption(stop_bits_q8=p.stop_bits_q8, field_value=p.field_value)
        for p in device.uart_stop_bits_options
        if getattr(p, "peripheral", None) == peripheral_name
    )
    flags_patch = next(
        (p for p in device.uart_mode_flags if getattr(p, "peripheral", None) == peripheral_name),
        None,
    )
    if flags_patch is not None:
        mode_flags = UartModeFlags(
            supports_lin=flags_patch.supports_lin,
            supports_irda=flags_patch.supports_irda,
            supports_smartcard=flags_patch.supports_smartcard,
            supports_half_duplex=flags_patch.supports_half_duplex,
            supports_synchronous=flags_patch.supports_synchronous,
            supports_auto_baud=flags_patch.supports_auto_baud,
            supports_wake_from_stop=flags_patch.supports_wake_from_stop,
            valid=True,
        )
    else:
        mode_flags = None
    dma_bindings = _uart_dma_bindings_for_peripheral(context, peripheral_name=peripheral_name)
    irq_numbers = _irq_numbers_for_peripheral(context, peripheral_name=peripheral_name)
    kernel_clock = _kernel_clock_for_peripheral(context, peripheral_name=peripheral_name)
    max_clock_hz = next(
        (
            int(p.max_clock_hz)
            for p in device.peripheral_max_clock_hz
            if getattr(p, "peripheral", None) == peripheral_name
        ),
        0,
    )
    max_baud_hz = device.uart_max_baud_hz
    # Template fallback layer (added by
    # ``migrate-uart-emitter-to-template-library``).  Merge order is
    # ``template ← device-patch``: the patch always wins; the template
    # fills only fields the patch left empty so admitted goldens stay
    # byte-stable when their patches already populate every Tier
    # 2/3/4 field, but devices with empty patches inherit the IP-level
    # defaults instead of emitting empty arrays.
    if template is not None:
        if not data_bits_options:
            data_bits_options = _uart_template_data_bits(template)
        if not parity_options:
            parity_options = _uart_template_parity(template)
        if not stop_bits_options:
            stop_bits_options = _uart_template_stop_bits(template)
        if not baud_oversampling_options:
            baud_oversampling_options = _uart_template_oversampling(template)
        if not fifo_trigger_options:
            fifo_trigger_options = _uart_template_fifo_triggers(template)
        if mode_flags is None:
            mode_flags = _uart_template_mode_flags(template)
        if not max_baud_hz:
            template_baud = template.values.get("max_baud_hz")
            if isinstance(template_baud, int):
                max_baud_hz = template_baud
    return {
        "baud_clock_sources": baud_clock_sources,
        "baud_oversampling_options": baud_oversampling_options,
        "fifo_trigger_options": fifo_trigger_options,
        "data_bits_options": data_bits_options,
        "parity_options": parity_options,
        "stop_bits_options": stop_bits_options,
        "mode_flags": mode_flags,
        "max_baud_hz": max_baud_hz,
        "dma_bindings": dma_bindings,
        "irq_numbers": irq_numbers,
        **kernel_clock,
        "max_clock_hz": max_clock_hz,
    }


# _spi_extension_for_peripheral → runtime_driver/spi.py


# _i2c_extension_for_peripheral → runtime_driver/i2c.py


def _build_uart_rows(context: _SemanticContext) -> tuple[UartSemanticRow, ...]:
    # Hardware-feature lookup added by ``fill-espressif-semantic-gaps``: a
    # stub row whose peripheral has a ``UartPeripheralDescriptor`` is
    # promoted out of stub status so it lands in ``kUartSemanticPeripherals``
    # (consumers iterating the array see hardware-feature-only entries).
    uart_hw_ids = {u.peripheral_id for u in context.device.uart_peripherals}

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

    # Load the peripheral-trait template catalog once and resolve a
    # template per UART instance via ``(ip_name, ip_version)``.  Added
    # by ``migrate-uart-emitter-to-template-library``.
    _trait_catalog = load_all_templates()

    def _template_for(peripheral: PeripheralInstance) -> PeripheralTemplate | None:
        return resolve_template(
            _trait_catalog,
            peripheral_class="uart",
            ip_name=peripheral.ip_name or "",
            ip_version=peripheral.ip_version,
        )

    rows: list[UartSemanticRow] = []
    candidate_peripherals = list(context.candidate_peripherals_by_class.get("uart", ()))
    candidate_names = {p.name for p in candidate_peripherals}
    for peripheral in sorted(context.device.peripherals, key=lambda item: item.name):
        if peripheral.name in uart_hw_ids and peripheral.name not in candidate_names:
            candidate_peripherals.append(peripheral)
    for peripheral in candidate_peripherals:
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        template = _template_for(peripheral)
        provenance = template_provenance_tag(template) if template is not None else None
        if schema_id.startswith("alloy.uart.st-"):
            row = _st_uart_row(
                context,
                peripheral_name=peripheral.name,
                schema_id=schema_id,
                f4_layout=_st_uart_uses_f4_layout(peripheral),
                template=template,
            )
            rows.append(_with_template_provenance(row, provenance))
        elif schema_id == "alloy.uart.microchip-uart-r":
            row = _microchip_uart_row(
                context,
                peripheral_name=peripheral.name,
                schema_id=schema_id,
                template=template,
            )
            rows.append(_with_template_provenance(row, provenance))
        elif schema_id == "alloy.uart.microchip-usart-zw":
            row = _microchip_uart_row(
                context,
                peripheral_name=peripheral.name,
                schema_id=schema_id,
                usart_prefix="US_",
                template=template,
            )
            rows.append(_with_template_provenance(row, provenance))
        elif schema_id == "alloy.uart.nxp-lpuart-v1":
            row = _nxp_uart_row(
                context,
                peripheral_name=peripheral.name,
                schema_id=schema_id,
                template=template,
            )
            rows.append(_with_template_provenance(row, provenance))
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (UartSemanticTraits<PeripheralId::) is satisfied for devices whose
            # UART IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            rows.append(
                UartSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    cr1_reg=invalid_reg,
                    cr2_reg=invalid_reg,
                    brr_reg=invalid_reg,
                    isr_reg=invalid_reg,
                    rdr_reg=invalid_reg,
                    tdr_reg=invalid_reg,
                    sr_reg=invalid_reg,
                    dr_reg=invalid_reg,
                    cr_reg=invalid_reg,
                    mr_reg=invalid_reg,
                    brgr_reg=invalid_reg,
                    thr_reg=invalid_reg,
                    us_cr_reg=invalid_reg,
                    us_mr_reg=invalid_reg,
                    us_brgr_reg=invalid_reg,
                    us_thr_reg=invalid_reg,
                    ue_field=invalid_field,
                    re_field=invalid_field,
                    te_field=invalid_field,
                    pce_field=invalid_field,
                    ps_field=invalid_field,
                    m0_field=invalid_field,
                    m1_field=invalid_field,
                    m_field=invalid_field,
                    stop_field=invalid_field,
                    tdr_field=invalid_field,
                    rdr_field=invalid_field,
                    txe_isr_field=invalid_field,
                    rxne_isr_field=invalid_field,
                    tc_isr_field=invalid_field,
                    txe_sr_field=invalid_field,
                    rxne_sr_field=invalid_field,
                    tc_sr_field=invalid_field,
                    dr_field=invalid_field,
                    rstrx_field=invalid_field,
                    rsttx_field=invalid_field,
                    rxdis_field=invalid_field,
                    txdis_field=invalid_field,
                    rststa_field=invalid_field,
                    par_field=invalid_field,
                    chmode_field=invalid_field,
                    cd_field=invalid_field,
                    rxen_field=invalid_field,
                    txen_field=invalid_field,
                    txrdy_field=invalid_field,
                    rxrdy_field=invalid_field,
                    txempty_field=invalid_field,
                    txchr_field=invalid_field,
                    rxchr_field=invalid_field,
                    us_rstrx_field=invalid_field,
                    us_rsttx_field=invalid_field,
                    us_rxdis_field=invalid_field,
                    us_txdis_field=invalid_field,
                    us_rststa_field=invalid_field,
                    us_usart_mode_field=invalid_field,
                    us_usclks_field=invalid_field,
                    us_chrl_field=invalid_field,
                    us_cd_field=invalid_field,
                    us_rxen_field=invalid_field,
                    us_txen_field=invalid_field,
                    us_txrdy_field=invalid_field,
                    us_rxrdy_field=invalid_field,
                    us_txempty_field=invalid_field,
                    us_txchr_field=invalid_field,
                    us_rxchr_field=invalid_field,
                    is_stub=peripheral.name not in uart_hw_ids,
                    template_provenance=provenance,
                    **_uart_extension_for_peripheral(
                        context, peripheral_name=peripheral.name, template=template
                    ),
                )
            )
    return tuple(rows)


# _st_i2c_v1_row → runtime_driver/i2c.py


# _st_i2c_v2_row → runtime_driver/i2c.py


# _microchip_i2c_row → runtime_driver/i2c.py


# _nxp_i2c_row → runtime_driver/i2c.py


# _build_i2c_rows → runtime_driver/i2c.py


# _st_spi_row → runtime_driver/spi.py


# _microchip_spi_row → runtime_driver/spi.py


# _nxp_spi_row → runtime_driver/spi.py


# _build_spi_rows → runtime_driver/spi.py


def _uart_dma_bindings_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[UartDmaBindingRow, ...]:
    """Derive UartDmaBinding rows from `device.dma_requests` filtered by
    UART peripheral.  Added by ``add-uart-spi-tier-2-3-4-data``.

    UART always transfers single bytes — even when 9-bit data uses a 16-bit
    register, DMA stride stays 8-bit on every admitted family — so the
    transfer width is hardcoded to 8 here.
    """
    bindings: list[UartDmaBindingRow] = []
    for binding in _runtime_lite_dma_bindings(context.device):
        if binding.peripheral != peripheral_name:
            continue
        signal = (binding.signal or "").upper()
        if signal not in {"TX", "RX"}:
            continue
        bindings.append(
            UartDmaBindingRow(
                controller_peripheral=binding.controller,
                controller_id=_enum_identifier(binding.controller),
                binding_id=_enum_identifier(binding.binding_id),
                request_value=int(binding.request_value or 0),
                signal=signal,
                transfer_width_bits=8,
            )
        )
    return tuple(bindings)


# _irq_numbers_for_peripheral → runtime_driver/common.py


def _uart_specialization_builder(context: _SemanticContext):
    # Hardware-feature lookup added by ``fill-espressif-semantic-gaps``: when
    # the device IR carries a ``UartPeripheralDescriptor`` for a peripheral
    # whose register-level schema isn't admitted yet, the stub
    # specialization promotes ``kPresent`` to ``true`` and emits the
    # silicon facts (base address, FIFO depth, GPIO-matrix signal indices,
    # DMA support).  This keeps the alloy HAL's ``UartController<T>`` concept
    # workable on Espressif targets even before full register schemas land.
    uart_hw_by_id = {u.peripheral_id: u for u in context.device.uart_peripherals}

    def _hw_lines(row: UartSemanticRow) -> list[str]:
        hw = uart_hw_by_id.get(row.peripheral_name)
        if hw is None:
            base_address = 0
            peripheral = context.peripheral_by_name.get(row.peripheral_name)
            if peripheral is not None:
                base_address = peripheral.base_address
            return [
                "  static constexpr bool kHardwarePresent = false;",
                f"  static constexpr std::uintptr_t kBaseAddress = 0x{base_address:08X}u;",
                "  static constexpr std::uint16_t kFifoDepth = 0u;",
                "  static constexpr std::int16_t kTxSignalIdx = -1;",
                "  static constexpr std::int16_t kRxSignalIdx = -1;",
                "  static constexpr bool kSupportsDma = false;",
            ]
        # ``kBaseAddress`` is sourced from the peripheral IR (which mirrors
        # the SVD/ATDF) rather than the patch overlay so hand-typed patch
        # base addresses can never disagree with the silicon spec.  The
        # patch only carries hardware-feature facts the SVD doesn't
        # encode (FIFO depth, GPIO-matrix signal indices, DMA support).
        peripheral = context.peripheral_by_name.get(row.peripheral_name)
        base_address = peripheral.base_address if peripheral is not None else hw.base_address
        return [
            "  static constexpr bool kHardwarePresent = true;",
            f"  static constexpr std::uintptr_t kBaseAddress = 0x{base_address:08X}u;",
            f"  static constexpr std::uint16_t kFifoDepth = {hw.fifo_depth}u;",
            f"  static constexpr std::int16_t kTxSignalIdx = {hw.tx_signal_idx if hw.tx_signal_idx is not None else -1};",
            f"  static constexpr std::int16_t kRxSignalIdx = {hw.rx_signal_idx if hw.rx_signal_idx is not None else -1};",
            f"  static constexpr bool kSupportsDma = {'true' if hw.supports_dma else 'false'};",
        ]

    def _u8_arr(name: str, values: tuple[int, ...]) -> str:
        n = len(values)
        joined = ", ".join(f"{v}u" for v in values)
        return f"  static constexpr std::array<std::uint8_t, {n}> {name} = {{{{{joined}}}}};"

    def _u16_arr(name: str, values: tuple[int, ...]) -> str:
        n = len(values)
        joined = ", ".join(f"{v}u" for v in values)
        return f"  static constexpr std::array<std::uint16_t, {n}> {name} = {{{{{joined}}}}};"

    def _tier234_lines(row: UartSemanticRow) -> list[str]:
        # Tier 2/3/4 constexprs (added by ``add-uart-spi-tier-2-3-4-data``).
        # Empty arrays / falsy flags by default until per-family device
        # patches populate the row's tier-2/3/4 tuples.  See the Tier 2/3/4
        # data dataclasses (UartBaudClockSource, UartParityOption, …) for
        # field semantics.
        data_bits = tuple(o.bits for o in row.data_bits_options)
        # Parity raw: 0=N, 1=E, 2=O, 3=M, 4=S
        parity_map = {"none": 0, "even": 1, "odd": 2, "mark": 3, "space": 4}
        parity_raw = tuple(parity_map.get(o.parity, 0) for o in row.parity_options)
        stop_bits_q8 = tuple(o.stop_bits_q8 for o in row.stop_bits_options)
        oversampling = tuple(o.ratio for o in row.baud_oversampling_options)
        baud_clock_raw = tuple(o.field_value for o in row.baud_clock_sources)
        fifo_trig_q8 = tuple(o.fraction_q8 for o in row.fifo_trigger_options)
        flags = row.mode_flags
        return [
            _u8_arr("kSupportedDataBits", data_bits),
            _u8_arr("kSupportedParityRaw", parity_raw),
            _u16_arr("kSupportedStopBitsQ8", stop_bits_q8),
            _u8_arr("kBaudOversamplingOptions", oversampling),
            _u8_arr("kBaudClockSourceRaw", baud_clock_raw),
            _u16_arr("kFifoTriggerFractionsQ8", fifo_trig_q8),
            f"  static constexpr std::uint32_t kMaxBaudHz = {row.max_baud_hz}u;",
            f"  static constexpr bool kSupportsLin = {'true' if flags and flags.supports_lin else 'false'};",
            f"  static constexpr bool kSupportsIrda = {'true' if flags and flags.supports_irda else 'false'};",
            f"  static constexpr bool kSupportsSmartcard = {'true' if flags and flags.supports_smartcard else 'false'};",
            f"  static constexpr bool kSupportsHalfDuplex = {'true' if flags and flags.supports_half_duplex else 'false'};",
            f"  static constexpr bool kSupportsSynchronous = {'true' if flags and flags.supports_synchronous else 'false'};",
            f"  static constexpr bool kSupportsAutoBaud = {'true' if flags and flags.supports_auto_baud else 'false'};",
            f"  static constexpr bool kSupportsWakeFromStop = {'true' if flags and flags.supports_wake_from_stop else 'false'};",
            f"  static constexpr std::uint8_t kDmaBindingCount = {len(row.dma_bindings)}u;",
            *_dma_binding_ref_array_lines(row.dma_bindings),
        ]

    def _provenance_lines(row: UartSemanticRow) -> list[str]:
        # Per-peripheral template provenance comment (added by
        # ``migrate-uart-emitter-to-template-library``).  Reviewers
        # see at a glance which template revision the device pinned
        # against.  Empty when no template matched.
        if row.template_provenance:
            return [f"  // {row.template_provenance}"]
        return []

    def _build(row: UartSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented.
            # ``kPresent`` flips to ``true`` when the device carries a
            # ``UartPeripheralDescriptor`` (added by
            # ``fill-espressif-semantic-gaps``) so the alloy HAL can drive
            # the controller via the hardware-feature constexprs even
            # without the register-level schema.
            kpresent = "true" if row.peripheral_name in uart_hw_by_id else "false"
            return [
                *_provenance_lines(row),
                f"  static constexpr bool kPresent = {kpresent};",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                *_hw_lines(row),
                *_tier234_lines(row),
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
                *_irq_numbers_lines(row.irq_numbers),
                *_kernel_clock_lines(
                    selector_field=row.kernel_clock_selector_field,
                    options=row.kernel_clock_source_options,
                    max_clock_hz=row.max_clock_hz,
                    gate_field=row.clock_gate_field,
                ),
            ]
        return [
            *_provenance_lines(row),
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            *_hw_lines(row),
            *_tier234_lines(row),
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
            *_irq_numbers_lines(row.irq_numbers),
            *_kernel_clock_lines(
                selector_field=row.kernel_clock_selector_field,
                options=row.kernel_clock_source_options,
                max_clock_hz=row.max_clock_hz,
                gate_field=row.clock_gate_field,
            ),
        ]

    return _build


# _i2c_specialization_builder → runtime_driver/i2c.py


# _spi_specialization_builder → runtime_driver/spi.py


def _uart_peripheral_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """Emit the per-controller UART trait struct + array contributed by
    ``complete-rp2040-semantics`` Phase B.  When `device.rp2040_uart_peripherals`
    is empty (every family except RP2040 today) only the primary template
    is emitted with zero defaults — non-RP2040 specializations are not
    affected."""
    lines = [
        "// complete-rp2040-semantics Phase B: per-controller UART facts.",
        "enum class RuntimeUartId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.rp2040_uart_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeUartId Id>",
            "struct UartPeripheralTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint8_t kFifoDepth = 0u;",
            "  static constexpr std::uint8_t kDreqTx = 0u;",
            "  static constexpr std::uint8_t kDreqRx = 0u;",
            "  static constexpr std::array<std::uint8_t, 0> kValidTxPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidRxPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidCtsPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidRtsPins = {};",
            "};",
            "",
        ]
    )
    for ctrl in device.rp2040_uart_peripherals:

        def _arr(pads: tuple[int, ...]) -> str:
            if not pads:
                return "  static constexpr std::array<std::uint8_t, 0> kPads = {};"
            return ", ".join(f"{p}u" for p in pads)

        lines.extend(
            [
                "template<>",
                f"struct UartPeripheralTraits<RuntimeUartId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint8_t kFifoDepth = {ctrl.fifo_depth}u;",
                f"  static constexpr std::uint8_t kDreqTx = {ctrl.dreq_tx}u;",
                f"  static constexpr std::uint8_t kDreqRx = {ctrl.dreq_rx}u;",
                (
                    f"  static constexpr std::array<std::uint8_t, {len(ctrl.valid_tx_pins)}>"
                    f" kValidTxPins = {{{{{_arr(ctrl.valid_tx_pins)}}}}};"
                    if ctrl.valid_tx_pins
                    else "  static constexpr std::array<std::uint8_t, 0> kValidTxPins = {};"
                ),
                (
                    f"  static constexpr std::array<std::uint8_t, {len(ctrl.valid_rx_pins)}>"
                    f" kValidRxPins = {{{{{_arr(ctrl.valid_rx_pins)}}}}};"
                    if ctrl.valid_rx_pins
                    else "  static constexpr std::array<std::uint8_t, 0> kValidRxPins = {};"
                ),
                (
                    f"  static constexpr std::array<std::uint8_t, {len(ctrl.valid_cts_pins)}>"
                    f" kValidCtsPins = {{{{{_arr(ctrl.valid_cts_pins)}}}}};"
                    if ctrl.valid_cts_pins
                    else "  static constexpr std::array<std::uint8_t, 0> kValidCtsPins = {};"
                ),
                (
                    f"  static constexpr std::array<std::uint8_t, {len(ctrl.valid_rts_pins)}>"
                    f" kValidRtsPins = {{{{{_arr(ctrl.valid_rts_pins)}}}}};"
                    if ctrl.valid_rts_pins
                    else "  static constexpr std::array<std::uint8_t, 0> kValidRtsPins = {};"
                ),
                "};",
                "",
            ]
        )
    return lines


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
        # Hardware-feature defaults (added by ``fill-espressif-semantic-gaps``).
        "  static constexpr bool kHardwarePresent = false;",
        "  static constexpr std::uintptr_t kBaseAddress = 0u;",
        "  static constexpr std::uint16_t kFifoDepth = 0u;",
        "  static constexpr std::int16_t kTxSignalIdx = -1;",
        "  static constexpr std::int16_t kRxSignalIdx = -1;",
        "  static constexpr bool kSupportsDma = false;",
        # Tier 2/3/4 defaults (added by ``add-uart-spi-tier-2-3-4-data``).
        "  static constexpr std::array<std::uint8_t, 0> kSupportedDataBits = {};",
        "  static constexpr std::array<std::uint8_t, 0> kSupportedParityRaw = {};",
        "  static constexpr std::array<std::uint16_t, 0> kSupportedStopBitsQ8 = {};",
        "  static constexpr std::array<std::uint8_t, 0> kBaudOversamplingOptions = {};",
        "  static constexpr std::array<std::uint8_t, 0> kBaudClockSourceRaw = {};",
        "  static constexpr std::array<std::uint16_t, 0> kFifoTriggerFractionsQ8 = {};",
        "  static constexpr std::uint32_t kMaxBaudHz = 0u;",
        "  static constexpr bool kSupportsLin = false;",
        "  static constexpr bool kSupportsIrda = false;",
        "  static constexpr bool kSupportsSmartcard = false;",
        "  static constexpr bool kSupportsHalfDuplex = false;",
        "  static constexpr bool kSupportsSynchronous = false;",
        "  static constexpr bool kSupportsAutoBaud = false;",
        "  static constexpr bool kSupportsWakeFromStop = false;",
        "  static constexpr std::uint8_t kDmaBindingCount = 0u;",
        "  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};",
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
        # NVIC vector lines (added by ``add-irq-vector-traits``).
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
        # Kernel-clock defaults (added by ``add-kernel-clock-traits``).
        "  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;",
        "  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};",
        "  static constexpr std::uint32_t kKernelMaxClockHz = 0u;",
        "  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;",
    ]
    extra_body: list[str] = list(_uart_peripheral_traits_block(device))
    typed_blocks = _build_uart_typed_enum_blocks(rows)
    if typed_blocks:
        if extra_body:
            extra_body.append("")
        extra_body.extend(typed_blocks)
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=UART_DRIVER_HEADER,
        trait_name="UartSemanticTraits",
        array_name="kUartSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_uart_specialization_builder(context),
        extra_body_lines=extra_body,
    )


# emit_runtime_driver_i2c_semantics_header → runtime_driver/i2c.py


# _compose_i2c_extra_body → runtime_driver/i2c.py


# emit_runtime_driver_spi_semantics_header → runtime_driver/spi.py


def _with_template_provenance(row: UartSemanticRow, provenance: str | None) -> UartSemanticRow:
    """Stamp ``template_provenance`` onto a freshly-built UART row.
    Frozen-dataclass copy added by
    ``migrate-uart-emitter-to-template-library``."""
    if provenance is None:
        return row
    from dataclasses import replace

    return replace(row, template_provenance=provenance)


# _build_uart_rows → runtime_driver/uart.py


__all__ = [
    "UART_DRIVER_HEADER",
    "UartBaudClockSource",
    "UartBaudOversamplingOption",
    "UartDataBitsOption",
    "UartFifoTriggerOption",
    "UartModeFlags",
    "UartParityOption",
    "UartSemanticRow",
    "UartStopBitsOption",
    "emit_runtime_driver_uart_semantics_header",
]
