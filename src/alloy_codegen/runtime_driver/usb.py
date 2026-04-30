"""USB driver-semantic emitter (STM32 OTG/USB, Microchip USBHS).

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
from .common import (
    RuntimeFieldRef,
    RuntimeRegisterRef,
    _context,
    _emit_peripheral_semantics_header,
    _field_ref_expr,
    _invalid_field_ref,
    _invalid_register_ref,
    _irq_numbers_lines,
    _register_ref_expr,
    _resolve_field_ref,
    _resolve_field_ref_any,
    _resolve_register_ref,
    _resolve_register_ref_any,
    _schema_ref_expr,
    _SemanticContext,
)

USB_DRIVER_HEADER = "driver_semantics/usb.hpp"


@dataclass(frozen=True, slots=True)
class UsbSemanticRow:
    """USB semantic trait payload keyed by peripheral.

    Hardware-feature fields (added by ``add-usb-semantic-traits``) carry the
    static silicon facts (base address, packet memory, endpoint count,
    speed/host capabilities, fixed pin assignments) sourced from
    ``Device.usb_controllers``.  ``hardware_present`` is ``False`` for rows
    derived only from register inspection — those rows still emit register
    references but the alloy HAL's ``kPresent`` predicate stays ``false``
    until a ``UsbControllerDescriptor`` is admitted for the peripheral.
    """

    peripheral_name: str
    schema_id: str | None
    supports_device_mode: bool
    supports_host_mode: bool
    has_dedicated_endpoint_config: bool
    has_clock_freeze: bool
    control_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    interrupt_status_reg: RuntimeRegisterRef
    interrupt_mask_reg: RuntimeRegisterRef
    device_control_reg: RuntimeRegisterRef
    device_status_reg: RuntimeRegisterRef
    device_interrupt_status_reg: RuntimeRegisterRef
    device_interrupt_mask_reg: RuntimeRegisterRef
    device_interrupt_enable_reg: RuntimeRegisterRef
    device_interrupt_disable_reg: RuntimeRegisterRef
    host_control_reg: RuntimeRegisterRef
    host_status_reg: RuntimeRegisterRef
    host_interrupt_status_reg: RuntimeRegisterRef
    host_interrupt_mask_reg: RuntimeRegisterRef
    host_interrupt_enable_reg: RuntimeRegisterRef
    host_interrupt_disable_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    freeze_clock_field: RuntimeFieldRef
    force_device_mode_field: RuntimeFieldRef
    force_host_mode_field: RuntimeFieldRef
    mode_status_field: RuntimeFieldRef
    soft_disconnect_field: RuntimeFieldRef
    remote_wakeup_field: RuntimeFieldRef
    address_enable_field: RuntimeFieldRef
    address_field: RuntimeFieldRef
    clock_usable_field: RuntimeFieldRef
    hardware_present: bool = False
    base_address: int = 0
    endpoint_count: int = 0
    supports_high_speed: bool = False
    supports_dma: bool = False
    crystalless: bool = False
    dpram_base_address: int | None = None
    dpram_size_bytes: int | None = None
    dma_channel_count: int = 0
    dm_pin: str | None = None
    dp_pin: str | None = None
    clock_source: str | None = None
    # NVIC vector lines (added by ``add-irq-vector-traits``).
    irq_numbers: tuple[int, ...] = ()


def _st_usb_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> UsbSemanticRow:
    peripheral = context.peripheral_by_name[peripheral_name]
    return UsbSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        supports_device_mode=True,
        supports_host_mode=True,
        has_dedicated_endpoint_config=True,
        has_clock_freeze=False,
        control_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GUSBCFG",),
            fallback_offset=0x0C,
        ),
        status_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GINTSTS",),
            fallback_offset=0x14,
        ),
        interrupt_status_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GINTSTS",),
            fallback_offset=0x14,
        ),
        interrupt_mask_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GINTMSK",),
            fallback_offset=0x18,
        ),
        device_control_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("DCTL",),
            fallback_offset=0x804,
        ),
        device_status_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("DSTS",),
            fallback_offset=0x808,
        ),
        device_interrupt_status_reg=_invalid_register_ref(peripheral.base_address),
        device_interrupt_mask_reg=_invalid_register_ref(peripheral.base_address),
        device_interrupt_enable_reg=_invalid_register_ref(peripheral.base_address),
        device_interrupt_disable_reg=_invalid_register_ref(peripheral.base_address),
        host_control_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("HCFG",),
            fallback_offset=0x400,
        ),
        host_status_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("HPRT", "HPRT0"),
            fallback_offset=0x440,
        ),
        host_interrupt_status_reg=_invalid_register_ref(peripheral.base_address),
        host_interrupt_mask_reg=_invalid_register_ref(peripheral.base_address),
        host_interrupt_enable_reg=_invalid_register_ref(peripheral.base_address),
        host_interrupt_disable_reg=_invalid_register_ref(peripheral.base_address),
        enable_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GCCFG",),
            field_names=("PWRDWN",),
            fallback_register_offset=0x38,
            fallback_bit_offset=16,
            fallback_bit_width=1,
        ),
        freeze_clock_field=_invalid_field_ref(peripheral.base_address),
        force_device_mode_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GUSBCFG",),
            field_names=("FDMOD",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=30,
            fallback_bit_width=1,
        ),
        force_host_mode_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GUSBCFG",),
            field_names=("FHMOD",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=29,
            fallback_bit_width=1,
        ),
        mode_status_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("GINTSTS",),
            field_names=("CMOD",),
            fallback_register_offset=0x14,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        soft_disconnect_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("DCTL",),
            field_names=("SDIS",),
            fallback_register_offset=0x804,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        remote_wakeup_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("DCTL",),
            field_names=("RWUSIG",),
            fallback_register_offset=0x804,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        address_enable_field=_invalid_field_ref(peripheral.base_address),
        address_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("DCFG",),
            field_names=("DAD",),
            fallback_register_offset=0x800,
            fallback_bit_offset=4,
            fallback_bit_width=7,
        ),
        clock_usable_field=_invalid_field_ref(peripheral.base_address),
    )


def _microchip_usb_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> UsbSemanticRow:
    peripheral = context.peripheral_by_name[peripheral_name]
    return UsbSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        supports_device_mode=True,
        supports_host_mode=True,
        has_dedicated_endpoint_config=True,
        has_clock_freeze=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL",
            fallback_offset=0x0800,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            fallback_offset=0x0804,
        ),
        interrupt_status_reg=_invalid_register_ref(peripheral.base_address),
        interrupt_mask_reg=_invalid_register_ref(peripheral.base_address),
        device_control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVCTRL",
            fallback_offset=0x0000,
        ),
        device_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVISR",
            fallback_offset=0x0004,
        ),
        device_interrupt_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVISR",
            fallback_offset=0x0004,
        ),
        device_interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVIMR",
            fallback_offset=0x0010,
        ),
        device_interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVIER",
            fallback_offset=0x0018,
        ),
        device_interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVIDR",
            fallback_offset=0x0014,
        ),
        host_control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTCTRL",
            fallback_offset=0x0400,
        ),
        host_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTISR",
            fallback_offset=0x0404,
        ),
        host_interrupt_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTISR",
            fallback_offset=0x0404,
        ),
        host_interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTIMR",
            fallback_offset=0x0410,
        ),
        host_interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTIER",
            fallback_offset=0x0418,
        ),
        host_interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="HSTIDR",
            fallback_offset=0x0414,
        ),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL",
            field_names=("USBE",),
            fallback_register_offset=0x0800,
            fallback_bit_offset=8,
            fallback_bit_width=1,
        ),
        freeze_clock_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL",
            field_names=("FRZCLK",),
            fallback_register_offset=0x0800,
            fallback_bit_offset=14,
            fallback_bit_width=1,
        ),
        force_device_mode_field=_invalid_field_ref(peripheral.base_address),
        force_host_mode_field=_invalid_field_ref(peripheral.base_address),
        mode_status_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL",
            field_names=("UIMOD",),
            fallback_register_offset=0x0800,
            fallback_bit_offset=25,
            fallback_bit_width=1,
        ),
        soft_disconnect_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVCTRL",
            field_names=("DETACH",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=8,
            fallback_bit_width=1,
        ),
        remote_wakeup_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVCTRL",
            field_names=("RMWKUP",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=9,
            fallback_bit_width=1,
        ),
        address_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVCTRL",
            field_names=("ADDEN",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        address_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DEVCTRL",
            field_names=("UADD",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=0,
            fallback_bit_width=7,
        ),
        clock_usable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("CLKUSABLE",),
            fallback_register_offset=0x0804,
            fallback_bit_offset=14,
            fallback_bit_width=1,
        ),
    )


def _build_usb_rows(context: _SemanticContext) -> tuple[UsbSemanticRow, ...]:
    # USB controller hardware-feature lookup (added by
    # ``add-usb-semantic-traits``).  Keyed by ``controller_id`` so the row
    # builder below can enrich each register-level row with the static
    # silicon facts (base address, endpoint count, packet memory, fixed
    # pin assignment) that drive the alloy ``UsbDeviceController<T>`` HAL.
    usb_hw_by_id = {usb.controller_id: usb for usb in context.device.usb_controllers}

    import dataclasses as _dc

    def _enrich(row: UsbSemanticRow) -> UsbSemanticRow:
        hw = usb_hw_by_id.get(row.peripheral_name)
        if hw is None:
            return row
        return _dc.replace(
            row,
            hardware_present=True,
            base_address=hw.base_address,
            endpoint_count=hw.endpoint_count,
            supports_high_speed=hw.supports_high_speed,
            supports_dma=hw.supports_dma,
            crystalless=hw.crystalless,
            dpram_base_address=hw.dpram_base_address,
            dpram_size_bytes=hw.dpram_size_bytes,
            dma_channel_count=hw.dma_channel_count,
            dm_pin=hw.dm_pin,
            dp_pin=hw.dp_pin,
            clock_source=hw.clock_source,
        )

    rows: list[UsbSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("usb", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.usb.st-") or schema_id.startswith("alloy.otg_fs.st-"):
            rows.append(
                _enrich(
                    _st_usb_row(
                        context,
                        peripheral_name=peripheral.name,
                        schema_id=schema_id,
                    )
                )
            )
        elif schema_id.startswith("alloy.usb.microchip-") or schema_id.startswith(
            "alloy.usbhs.microchip-"
        ):
            rows.append(
                _enrich(
                    _microchip_usb_row(
                        context,
                        peripheral_name=peripheral.name,
                        schema_id=schema_id,
                    )
                )
            )
    # Synthesize register-empty rows for hardware that has a USB controller
    # but no register-level schema yet (e.g. RP2040, ESP32-S3 OTG, where the
    # alloy.usb.* schema admission lands in a follow-on change).  These rows
    # surface ``kPresent = true`` to the alloy HAL so consumers see the
    # silicon facts even before the register schema is admitted.
    covered = {row.peripheral_name for row in rows}
    invalid_reg = _invalid_register_ref()
    invalid_field = _invalid_field_ref()
    runtime_peripheral_names = {
        peripheral.name for peripheral in context.runtime_peripherals_by_class.get("usb", ())
    }
    for hw in context.device.usb_controllers:
        if hw.controller_id in covered:
            continue
        # Skip synthesizing a row when the controller's peripheral is not
        # admitted to the runtime-lite ``PeripheralId`` enum — referencing a
        # missing enum value would break the published consumer-smoke build.
        # The USB hardware-feature facts still surface via the IR JSON; the
        # alloy HAL just can't pick them up by ``PeripheralId`` until the
        # peripheral itself is admitted (separate proposal).
        if hw.controller_id not in runtime_peripheral_names:
            continue
        peripheral = context.peripheral_by_name.get(hw.controller_id)
        schema_id = peripheral.backend_schema_id if peripheral is not None else None
        rows.append(
            UsbSemanticRow(
                peripheral_name=hw.controller_id,
                schema_id=schema_id,
                supports_device_mode=True,
                supports_host_mode=hw.supports_host_mode,
                has_dedicated_endpoint_config=False,
                has_clock_freeze=False,
                control_reg=invalid_reg,
                status_reg=invalid_reg,
                interrupt_status_reg=invalid_reg,
                interrupt_mask_reg=invalid_reg,
                device_control_reg=invalid_reg,
                device_status_reg=invalid_reg,
                device_interrupt_status_reg=invalid_reg,
                device_interrupt_mask_reg=invalid_reg,
                device_interrupt_enable_reg=invalid_reg,
                device_interrupt_disable_reg=invalid_reg,
                host_control_reg=invalid_reg,
                host_status_reg=invalid_reg,
                host_interrupt_status_reg=invalid_reg,
                host_interrupt_mask_reg=invalid_reg,
                host_interrupt_enable_reg=invalid_reg,
                host_interrupt_disable_reg=invalid_reg,
                enable_field=invalid_field,
                freeze_clock_field=invalid_field,
                force_device_mode_field=invalid_field,
                force_host_mode_field=invalid_field,
                mode_status_field=invalid_field,
                soft_disconnect_field=invalid_field,
                remote_wakeup_field=invalid_field,
                address_enable_field=invalid_field,
                address_field=invalid_field,
                clock_usable_field=invalid_field,
                hardware_present=True,
                base_address=hw.base_address,
                endpoint_count=hw.endpoint_count,
                supports_high_speed=hw.supports_high_speed,
                supports_dma=hw.supports_dma,
                crystalless=hw.crystalless,
                dpram_base_address=hw.dpram_base_address,
                dpram_size_bytes=hw.dpram_size_bytes,
                dma_channel_count=hw.dma_channel_count,
                dm_pin=hw.dm_pin,
                dp_pin=hw.dp_pin,
                clock_source=hw.clock_source,
            )
        )
    return tuple(rows)


def _usb_pin_ref_expr(pin: str | None, *, known_pins: frozenset[str] | None = None) -> str:
    """Format a USB DM/DP pin reference as a typed ``PinId`` expression.

    Returns ``PinId::none`` for controllers with IO-matrix-routed pads
    (e.g. RP2040, where USB DP/DM are not on a fixed pin), AND when the
    pin is not present in the device's admitted ``PinId`` enum.  The
    latter handles the case where a USB controller's documented DM/DP
    pin is on a package variant that the current target's pin set
    doesn't admit (e.g. STM32F401RE without PA11/PA12 in the QFP
    pinout).
    """
    if pin is None:
        return "PinId::none"
    if known_pins is not None and pin not in known_pins:
        return "PinId::none"
    return f"PinId::{_enum_identifier(pin)}"


def _usb_specialization_builder(context: _SemanticContext):
    known_pins = frozenset(pin.name for pin in context.device.pins)

    def _build(row: UsbSemanticRow) -> list[str]:
        register_members = {
            "kControlRegister": row.control_reg,
            "kStatusRegister": row.status_reg,
            "kInterruptStatusRegister": row.interrupt_status_reg,
            "kInterruptMaskRegister": row.interrupt_mask_reg,
            "kDeviceControlRegister": row.device_control_reg,
            "kDeviceStatusRegister": row.device_status_reg,
            "kDeviceInterruptStatusRegister": row.device_interrupt_status_reg,
            "kDeviceInterruptMaskRegister": row.device_interrupt_mask_reg,
            "kDeviceInterruptEnableRegister": row.device_interrupt_enable_reg,
            "kDeviceInterruptDisableRegister": row.device_interrupt_disable_reg,
            "kHostControlRegister": row.host_control_reg,
            "kHostStatusRegister": row.host_status_reg,
            "kHostInterruptStatusRegister": row.host_interrupt_status_reg,
            "kHostInterruptMaskRegister": row.host_interrupt_mask_reg,
            "kHostInterruptEnableRegister": row.host_interrupt_enable_reg,
            "kHostInterruptDisableRegister": row.host_interrupt_disable_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kFreezeClockField": row.freeze_clock_field,
            "kForceDeviceModeField": row.force_device_mode_field,
            "kForceHostModeField": row.force_host_mode_field,
            "kModeStatusField": row.mode_status_field,
            "kSoftDisconnectField": row.soft_disconnect_field,
            "kRemoteWakeupField": row.remote_wakeup_field,
            "kAddressEnableField": row.address_enable_field,
            "kAddressField": row.address_field,
            "kClockUsableField": row.clock_usable_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            "  static constexpr bool kSupportsDeviceMode = "
            + ("true" if row.supports_device_mode else "false")
            + ";",
            "  static constexpr bool kSupportsHostMode = "
            + ("true" if row.supports_host_mode else "false")
            + ";",
            "  static constexpr bool kHasDedicatedEndpointConfig = "
            + ("true" if row.has_dedicated_endpoint_config else "false")
            + ";",
            "  static constexpr bool kHasClockFreeze = "
            + ("true" if row.has_clock_freeze else "false")
            + ";",
        ]
        # Hardware-feature constexprs (added by ``add-usb-semantic-traits``).
        # ``kHardwarePresent`` is the alloy HAL's ``UsbDeviceController<T>``
        # gate — it stays ``false`` for register-only rows that have no
        # ``UsbControllerDescriptor`` admitted yet.
        lines.append(
            "  static constexpr bool kHardwarePresent = "
            + ("true" if row.hardware_present else "false")
            + ";"
        )
        lines.append(f"  static constexpr std::uintptr_t kBaseAddress = 0x{row.base_address:08X}u;")
        lines.append(f"  static constexpr std::uint16_t kEndpointCount = {row.endpoint_count}u;")
        lines.append(
            "  static constexpr bool kSupportsHighSpeed = "
            + ("true" if row.supports_high_speed else "false")
            + ";"
        )
        lines.append(
            "  static constexpr bool kSupportsDma = "
            + ("true" if row.supports_dma else "false")
            + ";"
        )
        lines.append(
            "  static constexpr bool kCrystalless = "
            + ("true" if row.crystalless else "false")
            + ";"
        )
        dpram_base = (
            f"0x{row.dpram_base_address:08X}u" if row.dpram_base_address is not None else "0u"
        )
        dpram_size = row.dpram_size_bytes if row.dpram_size_bytes is not None else 0
        lines.append(f"  static constexpr std::uintptr_t kDpramBaseAddress = {dpram_base};")
        lines.append(f"  static constexpr std::uint32_t kDpramSizeBytes = {dpram_size}u;")
        lines.append(
            f"  static constexpr std::uint8_t kDmaChannelCount = {row.dma_channel_count}u;"
        )
        lines.append(
            f"  static constexpr PinId kDmPin = {_usb_pin_ref_expr(row.dm_pin, known_pins=known_pins)};"
        )
        lines.append(
            f"  static constexpr PinId kDpPin = {_usb_pin_ref_expr(row.dp_pin, known_pins=known_pins)};"
        )
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        lines.extend(_irq_numbers_lines(row.irq_numbers))
        return lines

    return _build


def emit_runtime_driver_usb_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_usb_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kSupportsDeviceMode = false;",
        "  static constexpr bool kSupportsHostMode = false;",
        "  static constexpr bool kHasDedicatedEndpointConfig = false;",
        "  static constexpr bool kHasClockFreeze = false;",
        # Hardware-feature defaults (added by ``add-usb-semantic-traits``).
        "  static constexpr bool kHardwarePresent = false;",
        "  static constexpr std::uintptr_t kBaseAddress = 0u;",
        "  static constexpr std::uint16_t kEndpointCount = 0u;",
        "  static constexpr bool kSupportsHighSpeed = false;",
        "  static constexpr bool kSupportsDma = false;",
        "  static constexpr bool kCrystalless = false;",
        "  static constexpr std::uintptr_t kDpramBaseAddress = 0u;",
        "  static constexpr std::uint32_t kDpramSizeBytes = 0u;",
        "  static constexpr std::uint8_t kDmaChannelCount = 0u;",
        "  static constexpr PinId kDmPin = PinId::none;",
        "  static constexpr PinId kDpPin = PinId::none;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceInterruptStatusRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceInterruptEnableRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeviceInterruptDisableRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostInterruptStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kHostInterruptDisableRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFreezeClockField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kForceDeviceModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kForceHostModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kModeStatusField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSoftDisconnectField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRemoteWakeupField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAddressEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAddressField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClockUsableField = kInvalidFieldRef;",
        # NVIC vector lines (added by ``add-irq-vector-traits``).
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=USB_DRIVER_HEADER,
        trait_name="UsbSemanticTraits",
        array_name="kUsbSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_usb_specialization_builder(context),
    )


__all__ = [
    "USB_DRIVER_HEADER",
    "UsbSemanticRow",
    "emit_runtime_driver_usb_semantics_header",
]
