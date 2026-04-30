"""SPI driver-semantic emitter (STM32 / Microchip / NXP).

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR
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

SPI_DRIVER_HEADER = "driver_semantics/spi.hpp"


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
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented
    # Tier 2/3/4 (added by add-uart-spi-tier-2-3-4-data).  Default-empty
    # tuples / invalid mode-flags block; populated by per-family builders.
    baud_prescaler_options: tuple[SpiBaudPrescalerOption, ...] = ()
    frame_size_options: tuple[SpiFrameSizeOption, ...] = ()
    fifo_threshold_options: tuple[SpiFifoThresholdOption, ...] = ()
    mode_flags: SpiModeFlags | None = None
    spi_dma_bindings: tuple[SpiDmaBindingRow, ...] = ()
    # NVIC vector lines (added by ``add-irq-vector-traits``).
    irq_numbers: tuple[int, ...] = ()
    # Kernel-clock traits (added by ``add-kernel-clock-traits``).
    # ``None`` field-refs render as ``kInvalidFieldRef``.
    kernel_clock_selector_field: RuntimeFieldRef | None = None
    kernel_clock_source_options: tuple[KernelClockSourceOption, ...] = ()
    max_clock_hz: int = 0
    clock_gate_field: RuntimeFieldRef | None = None


@dataclass(frozen=True, slots=True)
class SpiDmaBindingRow:
    """One DMA route for SPI data.  Derived from ``device.dma_requests``.

    Added by ``add-uart-spi-tier-2-3-4-data``.  ``signal`` is "TX" or "RX".
    ``transfer_width_bits`` follows the largest admitted ``frame_size``:
    ≤8 bits → 8, 9..16 → 16, 17..32 → 32 (iMXRT LPSPI, ESP32 SPI).
    """

    controller_peripheral: str
    controller_id: str
    binding_id: str
    request_value: int
    signal: str  # "TX" | "RX"
    transfer_width_bits: int = 8


@dataclass(frozen=True, slots=True)
class SpiBaudPrescalerOption:
    """One SPI baud prescaler divisor + the BR field value that selects it."""

    divisor: int  # 2, 4, 8, 16, 32, 64, 128, 256
    field_value: int


@dataclass(frozen=True, slots=True)
class SpiFrameSizeOption:
    """One supported SPI frame size in bits + the DS / DFF field value."""

    bits: int
    field_value: int


@dataclass(frozen=True, slots=True)
class SpiFifoThresholdOption:
    """One SPI FIFO threshold (8-bit / 16-bit on STM32 FRXTH)."""

    threshold_bits: int  # 8 or 16
    field_value: int


@dataclass(frozen=True, slots=True)
class SpiModeFlags:
    """Per-SPI mode capability flags (one block per peripheral)."""

    supports_crc: bool = False
    supports_ti_frame: bool = False
    supports_motorola_frame: bool = True
    supports_i2s_submode: bool = False
    supports_bidirectional_3wire: bool = False
    supports_lsb_first: bool = False
    supports_nss_hw_management: bool = False
    valid: bool = False


def _build_spi_typed_enum_blocks(rows: tuple[SpiSemanticRow, ...]) -> list[str]:
    """Render SPI typed-option enum blocks (prescaler / frame size /
    FIFO threshold)."""
    prescaler_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    frame_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    fifo_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    for row in rows:
        if row.is_stub:
            continue
        peripheral_id = _enum_identifier(row.peripheral_name)
        prescaler = tuple(
            (f"div_{opt.divisor}", idx) for idx, opt in enumerate(row.baud_prescaler_options)
        )
        if prescaler:
            prescaler_entries.append((peripheral_id, prescaler))
        frame = tuple((f"bits_{opt.bits}", idx) for idx, opt in enumerate(row.frame_size_options))
        if frame:
            frame_entries.append((peripheral_id, frame))
        fifo = tuple(
            (f"threshold_{opt.threshold_bits}bit", idx)
            for idx, opt in enumerate(row.fifo_threshold_options)
        )
        if fifo:
            fifo_entries.append((peripheral_id, fifo))

    lines: list[str] = []
    for spec in (
        ("SpiPrescalerOf", "SpiPrescaler", prescaler_entries),
        ("SpiFrameSizeOf", "SpiFrameSize", frame_entries),
        ("SpiFifoThresholdOf", "SpiFifoThreshold", fifo_entries),
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


def _spi_extension_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> dict[str, object]:
    """Build the Tier 2/3/4 kwargs for ``SpiSemanticRow``."""
    device = context.device
    baud_prescaler_options = tuple(
        SpiBaudPrescalerOption(divisor=p.divisor, field_value=p.field_value)
        for p in device.spi_baud_prescaler_options
        if getattr(p, "peripheral", None) == peripheral_name
    )
    frame_size_options = tuple(
        SpiFrameSizeOption(bits=p.bits, field_value=p.field_value)
        for p in device.spi_frame_size_options
        if getattr(p, "peripheral", None) == peripheral_name
    )
    fifo_threshold_options = tuple(
        SpiFifoThresholdOption(threshold_bits=p.threshold_bits, field_value=p.field_value)
        for p in device.spi_fifo_threshold_options
        if getattr(p, "peripheral", None) == peripheral_name
    )
    flags_patch = next(
        (p for p in device.spi_mode_flags if getattr(p, "peripheral", None) == peripheral_name),
        None,
    )
    if flags_patch is not None:
        mode_flags = SpiModeFlags(
            supports_crc=flags_patch.supports_crc,
            supports_ti_frame=flags_patch.supports_ti_frame,
            supports_motorola_frame=flags_patch.supports_motorola_frame,
            supports_i2s_submode=flags_patch.supports_i2s_submode,
            supports_bidirectional_3wire=flags_patch.supports_bidirectional_3wire,
            supports_lsb_first=flags_patch.supports_lsb_first,
            supports_nss_hw_management=flags_patch.supports_nss_hw_management,
            valid=True,
        )
    else:
        mode_flags = None
    max_frame_bits = max((p.bits for p in frame_size_options), default=8)
    spi_dma_bindings = _spi_dma_bindings_for_peripheral(
        context, peripheral_name=peripheral_name, max_frame_bits=max_frame_bits
    )
    irq_numbers = _irq_numbers_for_peripheral(context, peripheral_name=peripheral_name)
    kernel_clock = _kernel_clock_for_peripheral(context, peripheral_name=peripheral_name)
    max_clock_hz = next(
        (
            int(p.max_clock_hz)
            for p in context.device.peripheral_max_clock_hz
            if getattr(p, "peripheral", None) == peripheral_name
        ),
        0,
    )
    return {
        "baud_prescaler_options": baud_prescaler_options,
        "frame_size_options": frame_size_options,
        "fifo_threshold_options": fifo_threshold_options,
        "mode_flags": mode_flags,
        "spi_dma_bindings": spi_dma_bindings,
        "irq_numbers": irq_numbers,
        **kernel_clock,
        "max_clock_hz": max_clock_hz,
    }


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
        **_spi_extension_for_peripheral(context, peripheral_name=peripheral_name),
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
        **_spi_extension_for_peripheral(context, peripheral_name=peripheral_name),
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
        **_spi_extension_for_peripheral(context, peripheral_name=peripheral_name),
    )


def _build_spi_rows(context: _SemanticContext) -> tuple[SpiSemanticRow, ...]:
    spi_hw_ids = {s.peripheral_id for s in context.device.spi_peripherals}
    rows: list[SpiSemanticRow] = []
    # Hardware-feature-only peripherals — admitted by ``device.spi_peripherals``
    # (added by ``fill-espressif-semantic-gaps``) but missing connection
    # candidates because the family overlay doesn't yet ship SPI pin
    # signal mappings.  Synthesize stub rows so the trait specialization
    # surfaces ``kPresent = true`` plus the hardware-feature constexprs.
    candidate_peripherals = list(context.candidate_peripherals_by_class.get("spi", ()))
    candidate_names = {p.name for p in candidate_peripherals}
    for peripheral in sorted(context.device.peripherals, key=lambda item: item.name):
        if peripheral.name in spi_hw_ids and peripheral.name not in candidate_names:
            candidate_peripherals.append(peripheral)
    for peripheral in candidate_peripherals:
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
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (SpiSemanticTraits<PeripheralId::) is satisfied for devices whose
            # SPI IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            rows.append(
                SpiSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    cr1_reg=invalid_reg,
                    cr2_reg=invalid_reg,
                    sr_reg=invalid_reg,
                    dr_reg=invalid_reg,
                    cr_reg=invalid_reg,
                    mr_reg=invalid_reg,
                    csr_reg=invalid_reg,
                    tdr_reg=invalid_reg,
                    rdr_reg=invalid_reg,
                    cpha_field=invalid_field,
                    cpol_field=invalid_field,
                    mstr_field=invalid_field,
                    br_field=invalid_field,
                    spe_field=invalid_field,
                    lsbfirst_field=invalid_field,
                    ssi_field=invalid_field,
                    ssm_field=invalid_field,
                    dff_field=invalid_field,
                    ds_field=invalid_field,
                    frxth_field=invalid_field,
                    txe_field=invalid_field,
                    rxne_field=invalid_field,
                    bsy_field=invalid_field,
                    dr_data_field=invalid_field,
                    spien_field=invalid_field,
                    spidis_field=invalid_field,
                    swrst_field=invalid_field,
                    ps_field=invalid_field,
                    pcsdec_field=invalid_field,
                    modfdis_field=invalid_field,
                    pcs_field=invalid_field,
                    dlybcs_field=invalid_field,
                    ncpha_field=invalid_field,
                    bits_field=invalid_field,
                    scbr_field=invalid_field,
                    dlybs_field=invalid_field,
                    dlybct_field=invalid_field,
                    tdre_field=invalid_field,
                    rdrf_field=invalid_field,
                    txempty_field=invalid_field,
                    td_field=invalid_field,
                    tdr_pcs_field=invalid_field,
                    rd_field=invalid_field,
                    is_stub=peripheral.name not in spi_hw_ids,
                    **_spi_extension_for_peripheral(context, peripheral_name=peripheral.name),
                )
            )
    return tuple(rows)


def _spi_dma_bindings_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    max_frame_bits: int = 8,
) -> tuple[SpiDmaBindingRow, ...]:
    """Derive SpiDmaBinding rows from `device.dma_requests` filtered by
    SPI peripheral.  Added by ``add-uart-spi-tier-2-3-4-data``.

    ``transfer_width_bits`` defaults from the largest admitted frame size:
    ≤8 → 8, 9..16 → 16, 17..32 → 32 (iMXRT LPSPI / ESP32 SPI).
    """
    if max_frame_bits <= 8:
        width = 8
    elif max_frame_bits <= 16:
        width = 16
    else:
        width = 32
    bindings: list[SpiDmaBindingRow] = []
    for binding in _runtime_lite_dma_bindings(context.device):
        if binding.peripheral != peripheral_name:
            continue
        signal = (binding.signal or "").upper()
        if signal not in {"TX", "RX"}:
            continue
        bindings.append(
            SpiDmaBindingRow(
                controller_peripheral=binding.controller,
                controller_id=_enum_identifier(binding.controller),
                binding_id=_enum_identifier(binding.binding_id),
                request_value=int(binding.request_value or 0),
                signal=signal,
                transfer_width_bits=width,
            )
        )
    return tuple(bindings)


def _spi_specialization_builder(context: _SemanticContext):
    # Hardware-feature lookup added by ``fill-espressif-semantic-gaps``.
    spi_hw_by_id = {s.peripheral_id: s for s in context.device.spi_peripherals}

    def _spi_hw_lines(row: SpiSemanticRow) -> list[str]:
        hw = spi_hw_by_id.get(row.peripheral_name)
        peripheral = context.peripheral_by_name.get(row.peripheral_name)
        base_address = peripheral.base_address if peripheral is not None else 0
        if hw is None:
            return [
                "  static constexpr bool kHardwarePresent = false;",
                f"  static constexpr std::uintptr_t kBaseAddress = 0x{base_address:08X}u;",
                "  static constexpr std::uint32_t kMaxClockHz = 0u;",
                "  static constexpr std::int16_t kMosiOutSignal = -1;",
                "  static constexpr std::int16_t kMisoInSignal = -1;",
                "  static constexpr std::int16_t kClkOutSignal = -1;",
                "  static constexpr std::int16_t kCsOutSignal = -1;",
                "  static constexpr bool kHasIomuxFastPath = false;",
                "  static constexpr std::int16_t kIomuxMosiPin = -1;",
                "  static constexpr std::int16_t kIomuxMisoPin = -1;",
                "  static constexpr std::int16_t kIomuxClkPin = -1;",
                "  static constexpr std::int16_t kIomuxCsPin = -1;",
                "  static constexpr bool kSupportsDma = false;",
            ]
        return [
            "  static constexpr bool kHardwarePresent = true;",
            f"  static constexpr std::uintptr_t kBaseAddress = 0x{base_address:08X}u;",
            f"  static constexpr std::uint32_t kMaxClockHz = {hw.max_clock_hz}u;",
            f"  static constexpr std::int16_t kMosiOutSignal = {hw.mosi_out_signal if hw.mosi_out_signal is not None else -1};",
            f"  static constexpr std::int16_t kMisoInSignal = {hw.miso_in_signal if hw.miso_in_signal is not None else -1};",
            f"  static constexpr std::int16_t kClkOutSignal = {hw.clk_out_signal if hw.clk_out_signal is not None else -1};",
            f"  static constexpr std::int16_t kCsOutSignal = {hw.cs_out_signal if hw.cs_out_signal is not None else -1};",
            f"  static constexpr bool kHasIomuxFastPath = {'true' if hw.has_iomux_fast_path else 'false'};",
            f"  static constexpr std::int16_t kIomuxMosiPin = {hw.iomux_mosi_pin if hw.iomux_mosi_pin is not None else -1};",
            f"  static constexpr std::int16_t kIomuxMisoPin = {hw.iomux_miso_pin if hw.iomux_miso_pin is not None else -1};",
            f"  static constexpr std::int16_t kIomuxClkPin = {hw.iomux_clk_pin if hw.iomux_clk_pin is not None else -1};",
            f"  static constexpr std::int16_t kIomuxCsPin = {hw.iomux_cs_pin if hw.iomux_cs_pin is not None else -1};",
            f"  static constexpr bool kSupportsDma = {'true' if hw.supports_dma else 'false'};",
        ]

    def _spi_u8_arr(name: str, values: tuple[int, ...]) -> str:
        n = len(values)
        joined = ", ".join(f"{v}u" for v in values)
        return f"  static constexpr std::array<std::uint8_t, {n}> {name} = {{{{{joined}}}}};"

    def _spi_u16_arr(name: str, values: tuple[int, ...]) -> str:
        n = len(values)
        joined = ", ".join(f"{v}u" for v in values)
        return f"  static constexpr std::array<std::uint16_t, {n}> {name} = {{{{{joined}}}}};"

    def _spi_tier234_lines(row: SpiSemanticRow) -> list[str]:
        # Tier 2/3/4 SPI constexprs (added by ``add-uart-spi-tier-2-3-4-data``).
        prescaler_divs = tuple(o.divisor for o in row.baud_prescaler_options)
        frame_sizes = tuple(o.bits for o in row.frame_size_options)
        fifo_thresholds = tuple(o.threshold_bits for o in row.fifo_threshold_options)
        flags = row.mode_flags
        return [
            _spi_u16_arr("kBaudPrescalerDivisors", prescaler_divs),
            _spi_u8_arr("kSupportedFrameSizes", frame_sizes),
            _spi_u8_arr("kFifoThresholdBits", fifo_thresholds),
            f"  static constexpr bool kSupportsCrc = {'true' if flags and flags.supports_crc else 'false'};",
            f"  static constexpr bool kSupportsTiFrame = {'true' if flags and flags.supports_ti_frame else 'false'};",
            f"  static constexpr bool kSupportsMotorolaFrame = {'true' if flags and flags.supports_motorola_frame else 'false'};",
            f"  static constexpr bool kSupportsI2sSubmode = {'true' if flags and flags.supports_i2s_submode else 'false'};",
            f"  static constexpr bool kSupportsBidirectional3Wire = {'true' if flags and flags.supports_bidirectional_3wire else 'false'};",
            f"  static constexpr bool kSupportsLsbFirst = {'true' if flags and flags.supports_lsb_first else 'false'};",
            f"  static constexpr bool kSupportsNssHwManagement = {'true' if flags and flags.supports_nss_hw_management else 'false'};",
            f"  static constexpr std::uint8_t kSpiDmaBindingCount = {len(row.spi_dma_bindings)}u;",
            *_dma_binding_ref_array_lines(row.spi_dma_bindings),
        ]

    def _build(row: SpiSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented.
            # ``kPresent`` flips to ``true`` when the device IR carries an
            # ``SpiPeripheralDescriptor`` (added by
            # ``fill-espressif-semantic-gaps``).
            kpresent = "true" if row.peripheral_name in spi_hw_by_id else "false"
            return [
                f"  static constexpr bool kPresent = {kpresent};",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                *_spi_hw_lines(row),
                *_spi_tier234_lines(row),
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
                *_irq_numbers_lines(row.irq_numbers),
                *_kernel_clock_lines(
                    selector_field=row.kernel_clock_selector_field,
                    options=row.kernel_clock_source_options,
                    max_clock_hz=row.max_clock_hz,
                    gate_field=row.clock_gate_field,
                ),
            ]
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
            *_spi_hw_lines(row),
            *_spi_tier234_lines(row),
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        lines.extend(_irq_numbers_lines(row.irq_numbers))
        lines.extend(
            _kernel_clock_lines(
                selector_field=row.kernel_clock_selector_field,
                options=row.kernel_clock_source_options,
                max_clock_hz=row.max_clock_hz,
                gate_field=row.clock_gate_field,
            )
        )
        return lines

    return _build


def _spi_peripheral_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """Phase B sibling for SPI."""
    lines = [
        "// complete-rp2040-semantics Phase B: per-controller SPI facts.",
        "enum class RuntimeSpiId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.rp2040_spi_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeSpiId Id>",
            "struct SpiPeripheralTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint32_t kMaxClockHz = 0u;",
            "  static constexpr std::uint8_t kDreqTx = 0u;",
            "  static constexpr std::uint8_t kDreqRx = 0u;",
            "  static constexpr std::array<std::uint8_t, 0> kValidMosiPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidMisoPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidClkPins = {};",
            "  static constexpr std::array<std::uint8_t, 0> kValidCsPins = {};",
            "};",
            "",
        ]
    )

    def _arr(pads: tuple[int, ...]) -> str:
        return ", ".join(f"{p}u" for p in pads)

    for ctrl in device.rp2040_spi_peripherals:

        def _pad_line(name: str, pads: tuple[int, ...]) -> str:
            if not pads:
                return f"  static constexpr std::array<std::uint8_t, 0> {name} = {{}};"
            return (
                f"  static constexpr std::array<std::uint8_t, {len(pads)}> "
                f"{name} = {{{{{_arr(pads)}}}}};"
            )

        lines.extend(
            [
                "template<>",
                f"struct SpiPeripheralTraits<RuntimeSpiId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint32_t kMaxClockHz = {ctrl.max_clock_hz}u;",
                f"  static constexpr std::uint8_t kDreqTx = {ctrl.dreq_tx}u;",
                f"  static constexpr std::uint8_t kDreqRx = {ctrl.dreq_rx}u;",
                _pad_line("kValidMosiPins", ctrl.valid_mosi_pins),
                _pad_line("kValidMisoPins", ctrl.valid_miso_pins),
                _pad_line("kValidClkPins", ctrl.valid_clk_pins),
                _pad_line("kValidCsPins", ctrl.valid_cs_pins),
                "};",
                "",
            ]
        )
    return lines


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
        # Hardware-feature defaults (added by ``fill-espressif-semantic-gaps``).
        "  static constexpr bool kHardwarePresent = false;",
        "  static constexpr std::uintptr_t kBaseAddress = 0u;",
        "  static constexpr std::uint32_t kMaxClockHz = 0u;",
        "  static constexpr std::int16_t kMosiOutSignal = -1;",
        "  static constexpr std::int16_t kMisoInSignal = -1;",
        "  static constexpr std::int16_t kClkOutSignal = -1;",
        "  static constexpr std::int16_t kCsOutSignal = -1;",
        "  static constexpr bool kHasIomuxFastPath = false;",
        "  static constexpr std::int16_t kIomuxMosiPin = -1;",
        "  static constexpr std::int16_t kIomuxMisoPin = -1;",
        "  static constexpr std::int16_t kIomuxClkPin = -1;",
        "  static constexpr std::int16_t kIomuxCsPin = -1;",
        "  static constexpr bool kSupportsDma = false;",
        # Tier 2/3/4 defaults (added by ``add-uart-spi-tier-2-3-4-data``).
        "  static constexpr std::array<std::uint16_t, 0> kBaudPrescalerDivisors = {};",
        "  static constexpr std::array<std::uint8_t, 0> kSupportedFrameSizes = {};",
        "  static constexpr std::array<std::uint8_t, 0> kFifoThresholdBits = {};",
        "  static constexpr bool kSupportsCrc = false;",
        "  static constexpr bool kSupportsTiFrame = false;",
        "  static constexpr bool kSupportsMotorolaFrame = false;",
        "  static constexpr bool kSupportsI2sSubmode = false;",
        "  static constexpr bool kSupportsBidirectional3Wire = false;",
        "  static constexpr bool kSupportsLsbFirst = false;",
        "  static constexpr bool kSupportsNssHwManagement = false;",
        "  static constexpr std::uint8_t kSpiDmaBindingCount = 0u;",
        "  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};",
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
        # NVIC vector lines (added by ``add-irq-vector-traits``).
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
        # Kernel-clock defaults (added by ``add-kernel-clock-traits``).
        "  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;",
        "  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};",
        "  static constexpr std::uint32_t kKernelMaxClockHz = 0u;",
        "  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;",
    ]
    extra_body: list[str] = list(_spi_peripheral_traits_block(device))
    typed_blocks = _build_spi_typed_enum_blocks(rows)
    if typed_blocks:
        if extra_body:
            extra_body.append("")
        extra_body.extend(typed_blocks)
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=SPI_DRIVER_HEADER,
        trait_name="SpiSemanticTraits",
        array_name="kSpiSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_spi_specialization_builder(context),
        extra_body_lines=extra_body,
    )




__all__ = [
    "SPI_DRIVER_HEADER",
    "SpiDmaBindingRow",
    "SpiSemanticRow",
    "emit_runtime_driver_spi_semantics_header",
]
