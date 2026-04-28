# ruff: noqa: E501

"""Normalize stage — YAML-only consumer.

After ``consume-alloy-devices-yml-as-canonical-input`` every
admitted device's ``CanonicalDeviceIR`` is read directly from the
``alloy-devices-yml`` submodule mounted at ``data/devices/``.
The pre-pivot vendor source parsers, family-specific
``_build_*_device_ir`` builders, and the adapter-registry
fallback have all been removed — admission is now "commit YAML
to the data repo or fail loudly".

Two enrichments still happen post-load:

1. **Family patch overlay** — pulls hardware-feature blocks
   (USB controllers, multicore topology, ESP32 UART/SPI/ADC/
   timer/LEDC/DMA descriptors) from
   ``patches/<vendor>/<family>/family.json`` onto the device
   IR.  Idempotent against YAML that already carries those
   fields.  This whole layer is removed in
   ``consume-alloy-devices-yml-as-canonical-input`` Phase 3.
2. **Device patch tier 2/3/4 forwarding** — re-applies
   ``patches/<vendor>/<family>/devices/<device>.json`` to fill
   ADC/UART/SPI/timer/PWM/I2C tier-2/3/4 tuples.  Also removed
   in Phase 3.
3. **Board pack validation** — ``_load_and_validate_boards``
   reads board JSON next to the device patch and emits typed
   ``BoardDescriptor`` rows; this stays.
"""

from __future__ import annotations

import dataclasses

from alloy_codegen.connector_model import ensure_connector_descriptors
from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.model import (
    AdcUnitDescriptor,
    AppCpuControlPlane,
    BoardDescriptor,
    CanonicalDeviceIR,
    DmaChannelDescriptor,
    ExternalOscillatorDescriptor,
    LedcDescriptor,
    NamedPinDescriptor,
    RegisterDescriptor,
    SpiPeripheralDescriptor,
    TimerUnitDescriptor,
    UartPeripheralDescriptor,
    UsbControllerDescriptor,
)
from alloy_codegen.patches import (
    load_board_patches,
    load_device_patch,
    load_family_patch_catalog,
)
from alloy_codegen.reporting import NormalizationBundle
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.patch import run as run_patch


def _resolve_register_id(
    registers: tuple[RegisterDescriptor, ...],
    qualified_name: str,
) -> str | None:
    """Resolve a ``"PERIPHERAL.REGISTER"`` string to a typed
    ``register_id``.

    Used by the multicore-topology enrichment to lift the APP_CPU
    control register naming out of patch JSON and into the typed
    IR.  Returns the canonical ``register_id`` (e.g.
    ``"register:dport:appcpu-ctrl-b"``) when the named register
    is present in the device's filtered register set, or
    ``None`` when it is not — callers raise a
    ``StageExecutionError`` so a dropped register surfaces fast
    instead of silently disappearing.
    """
    if "." not in qualified_name:
        return None
    peripheral_part, register_part = qualified_name.split(".", 1)
    peripheral_target = peripheral_part.strip()
    register_target = register_part.strip()
    for register in registers:
        if register.peripheral == peripheral_target and register.name == register_target:
            return register.register_id
    return None


def _load_and_validate_boards(
    execution_context: ExecutionContext,
    *,
    device: CanonicalDeviceIR,
) -> tuple[BoardDescriptor, ...]:
    """``add-board-support-package-emitter``: load every board JSON
    that targets ``device.identity.device`` and validate each
    ``named_pin`` against the device's admitted ``pin_definitions``.
    A board file referencing a non-existent pin raises a
    ``StageExecutionError`` so a BSP header that would
    ``static_assert`` at the consumer's ``#include`` is rejected at
    codegen time."""
    boards = load_board_patches(
        execution_context,
        vendor=device.identity.vendor,
        family=device.identity.family,
        device=device.identity.device,
    )
    if not boards:
        return ()
    admitted_pin_names = {pin.name for pin in device.pins}
    descriptors: list[BoardDescriptor] = []
    for board in boards:
        for named in board.named_pins:
            if named.pin not in admitted_pin_names:
                raise StageExecutionError(
                    f"board '{board.board_id}' named pin '{named.name}' "
                    f"references unknown pin '{named.pin}' "
                    f"(device {device.identity.device} admits "
                    f"{sorted(admitted_pin_names)[:8]}…)"
                )
        descriptors.append(
            BoardDescriptor(
                board_id=board.board_id,
                device=board.device,
                package=board.package,
                summary=board.summary,
                named_pins=tuple(
                    NamedPinDescriptor(
                        name=p.name,
                        pin=p.pin,
                        polarity=p.polarity,
                        peripheral=p.peripheral,
                        signal=p.signal,
                    )
                    for p in board.named_pins
                ),
                default_clock_profile=board.default_clock_profile,
                external_oscillators=tuple(
                    ExternalOscillatorDescriptor(
                        kind=o.kind,
                        frequency_hz=o.frequency_hz,
                        source=o.source,
                    )
                    for o in board.external_oscillators
                ),
            )
        )
    return tuple(descriptors)


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the normalize stage.

    Loads every device's ``CanonicalDeviceIR`` from the
    ``alloy-devices-yml`` submodule and applies the family/device
    patch enrichment passes (still in flight; removed in Phase 3
    of ``consume-alloy-devices-yml-as-canonical-input``).
    """
    execution_context = context or ExecutionContext.default()
    patch_result = run_patch(scope, execution_context)
    devices: list[CanonicalDeviceIR] = []
    vendor = patch_result.scope.resolved_vendor()
    family = patch_result.scope.resolved_family()

    from alloy_codegen.sources import alloy_devices_yml as _adyml

    for device_name in patch_result.scope.resolved_device_names():
        if not _adyml.is_available(vendor=vendor, family=family, device=device_name):
            yaml_path = _adyml.device_yaml_path(
                vendor=vendor, family=family, device=device_name
            )
            raise StageExecutionError(
                f"canonical device YAML missing at {yaml_path}.  "
                "Admit the device by committing its YAML to the "
                "alloy-devices-yml data repo (this codegen repo is "
                "consumer-only after consume-alloy-devices-yml-as-canonical-input)."
            )
        devices.append(
            _adyml.load_canonical_device(vendor=vendor, family=family, device=device_name)
        )

    enriched_devices: list[CanonicalDeviceIR] = []
    for device in devices:
        try:
            patch = load_device_patch(
                execution_context,
                device.identity.device,
                vendor=device.identity.vendor,
                family=device.identity.family,
            )
        except StageExecutionError:
            enriched_devices.append(device)
            continue
        topology_value: str = device.multicore_topology
        app_cpu_plane: AppCpuControlPlane | None = device.app_cpu_control_plane
        registers = device.registers
        usb_controllers: tuple[UsbControllerDescriptor, ...] = device.usb_controllers
        try:
            family_catalog = load_family_patch_catalog(
                execution_context,
                vendor=device.identity.vendor,
                family=device.identity.family,
            )
        except StageExecutionError:
            family_catalog = None
        if family_catalog is not None and family_catalog.usb_controllers:
            usb_controllers = tuple(
                UsbControllerDescriptor(
                    controller_id=patch_usb.controller_id,
                    base_address=patch_usb.base_address,
                    endpoint_count=patch_usb.endpoint_count,
                    supports_high_speed=patch_usb.supports_high_speed,
                    supports_host_mode=patch_usb.supports_host_mode,
                    supports_dma=patch_usb.supports_dma,
                    crystalless=patch_usb.crystalless,
                    dpram_base_address=patch_usb.dpram_base_address,
                    dpram_size_bytes=patch_usb.dpram_size_bytes,
                    dma_channel_count=patch_usb.dma_channel_count,
                    dm_pin=patch_usb.dm_pin,
                    dp_pin=patch_usb.dp_pin,
                    clock_source=patch_usb.clock_source,
                )
                for patch_usb in family_catalog.usb_controllers
            )
        if family_catalog is not None and family_catalog.multicore_topology is not None:
            mc_patch = family_catalog.multicore_topology
            topology_map = {
                "single-core": "single_core",
                "symmetric-dual-core": "symmetric_dual_core",
                "xtensa-asymmetric-dual-core": "xtensa_asymmetric_dual_core",
            }
            mapped = topology_map.get(mc_patch.topology)
            if mapped is not None:
                topology_value = mapped
            if mc_patch.app_cpu_control_plane is not None:
                primary_id = _resolve_register_id(
                    registers, mc_patch.app_cpu_control_plane.register
                )
                if primary_id is None:
                    raise StageExecutionError(
                        "multicore_topology.app_cpu_control_plane.register "
                        f"'{mc_patch.app_cpu_control_plane.register}' not "
                        f"present in {device.identity.device} register set."
                    )
                secondary_id: str | None = None
                if mc_patch.app_cpu_control_plane.register_secondary is not None:
                    secondary_id = _resolve_register_id(
                        registers, mc_patch.app_cpu_control_plane.register_secondary
                    )
                    if secondary_id is None:
                        raise StageExecutionError(
                            "multicore_topology.app_cpu_control_plane."
                            "register_secondary "
                            f"'{mc_patch.app_cpu_control_plane.register_secondary}'"
                            f" not present in {device.identity.device} register set."
                        )
                app_cpu_plane = AppCpuControlPlane(
                    release_register=primary_id,
                    operation=mc_patch.app_cpu_control_plane.operation,
                    start_vector_symbol=mc_patch.app_cpu_control_plane.start_vector_symbol,
                    release_register_secondary=secondary_id,
                )
                role_targets = {primary_id}
                if secondary_id is not None:
                    role_targets.add(secondary_id)
                registers = tuple(
                    dataclasses.replace(reg, role="secondary_core_release")
                    if reg.register_id in role_targets
                    else reg
                    for reg in registers
                )
        uart_peripherals: tuple[UartPeripheralDescriptor, ...] = device.uart_peripherals
        spi_peripherals: tuple[SpiPeripheralDescriptor, ...] = device.spi_peripherals
        adc_units: tuple[AdcUnitDescriptor, ...] = device.adc_units
        timer_units: tuple[TimerUnitDescriptor, ...] = device.timer_units
        ledc_descriptor: LedcDescriptor | None = device.ledc
        dma_channels: tuple[DmaChannelDescriptor, ...] = device.dma_channels
        if family_catalog is not None:
            if family_catalog.uart_peripherals:
                uart_peripherals = tuple(
                    UartPeripheralDescriptor(
                        peripheral_id=u.peripheral_id,
                        base_address=u.base_address,
                        fifo_depth=u.fifo_depth,
                        tx_signal_idx=u.tx_signal_idx,
                        rx_signal_idx=u.rx_signal_idx,
                        supports_dma=u.supports_dma,
                    )
                    for u in family_catalog.uart_peripherals
                )
            if family_catalog.spi_peripherals:
                spi_peripherals = tuple(
                    SpiPeripheralDescriptor(
                        peripheral_id=s.peripheral_id,
                        base_address=s.base_address,
                        max_clock_hz=s.max_clock_hz,
                        mosi_out_signal=s.mosi_out_signal,
                        miso_in_signal=s.miso_in_signal,
                        clk_out_signal=s.clk_out_signal,
                        cs_out_signal=s.cs_out_signal,
                        has_iomux_fast_path=s.has_iomux_fast_path,
                        iomux_mosi_pin=s.iomux_mosi_pin,
                        iomux_miso_pin=s.iomux_miso_pin,
                        iomux_clk_pin=s.iomux_clk_pin,
                        iomux_cs_pin=s.iomux_cs_pin,
                        supports_dma=s.supports_dma,
                    )
                    for s in family_catalog.spi_peripherals
                )
            if family_catalog.adc_units:
                adc_units = tuple(
                    AdcUnitDescriptor(
                        unit_id=a.unit_id,
                        channel_count=a.channel_count,
                        resolution_bits=a.resolution_bits,
                        conflicts_with_wifi=a.conflicts_with_wifi,
                        channel_pins=a.channel_pins,
                    )
                    for a in family_catalog.adc_units
                )
            if family_catalog.timer_units:
                timer_units = tuple(
                    TimerUnitDescriptor(
                        timer_id=t.timer_id,
                        group_idx=t.group_idx,
                        timer_idx=t.timer_idx,
                        base_address=t.base_address,
                        bits=t.bits,
                        clock_sources=t.clock_sources,
                    )
                    for t in family_catalog.timer_units
                )
            if family_catalog.ledc is not None:
                ledc_descriptor = LedcDescriptor(
                    base_address=family_catalog.ledc.base_address,
                    channel_count=family_catalog.ledc.channel_count,
                    resolution_bits=family_catalog.ledc.resolution_bits,
                    clock_sources=family_catalog.ledc.clock_sources,
                    output_signals=family_catalog.ledc.output_signals,
                )
            if family_catalog.dma_channels:
                dma_channels = tuple(
                    DmaChannelDescriptor(
                        channel_id=d.channel_id,
                        channel_index=d.channel_index,
                        is_gdma=d.is_gdma,
                        max_transfer_bytes=d.max_transfer_bytes,
                        peripheral_requests=d.peripheral_requests,
                    )
                    for d in family_catalog.dma_channels
                )
        enriched_devices.append(
            dataclasses.replace(
                device,
                registers=registers,
                adc_internal_channels=patch.adc_internal_channels,
                adc_calibration_data_points=patch.adc_calibration_data_points,
                adc_calibration_context=patch.adc_calibration_context,
                adc_resolution_options=patch.adc_resolution_options,
                adc_sample_time_options=patch.adc_sample_time_options,
                adc_oversampling_options=patch.adc_oversampling_options,
                adc_external_triggers=patch.adc_external_triggers,
                adc_max_clock_hz=patch.adc_max_clock_hz,
                uart_baud_clock_sources=patch.uart_baud_clock_sources,
                uart_baud_oversampling_options=patch.uart_baud_oversampling_options,
                uart_fifo_trigger_options=patch.uart_fifo_trigger_options,
                uart_data_bits_options=patch.uart_data_bits_options,
                uart_parity_options=patch.uart_parity_options,
                uart_stop_bits_options=patch.uart_stop_bits_options,
                uart_mode_flags=patch.uart_mode_flags,
                uart_max_baud_hz=patch.uart_max_baud_hz,
                spi_baud_prescaler_options=patch.spi_baud_prescaler_options,
                spi_frame_size_options=patch.spi_frame_size_options,
                spi_fifo_threshold_options=patch.spi_fifo_threshold_options,
                spi_mode_flags=patch.spi_mode_flags,
                timer_prescaler_options=patch.timer_prescaler_options,
                timer_trigger_sources=patch.timer_trigger_sources,
                timer_master_outputs=patch.timer_master_outputs,
                timer_mode_flags=patch.timer_mode_flags,
                pwm_deadtime_options=patch.pwm_deadtime_options,
                pwm_alignment_options=patch.pwm_alignment_options,
                pwm_break_inputs=patch.pwm_break_inputs,
                pwm_mode_flags=patch.pwm_mode_flags,
                peripheral_max_clock_hz=patch.peripheral_max_clock_hz,
                i2c_speed_options=patch.i2c_speed_options,
                i2c_timing_presets=patch.i2c_timing_presets,
                i2c_mode_flags=patch.i2c_mode_flags,
                boards=_load_and_validate_boards(
                    execution_context,
                    device=device,
                ),
                multicore_topology=topology_value,
                app_cpu_control_plane=app_cpu_plane,
                usb_controllers=usb_controllers,
                uart_peripherals=uart_peripherals,
                spi_peripherals=spi_peripherals,
                adc_units=adc_units,
                timer_units=timer_units,
                ledc=ledc_descriptor,
                dma_channels=dma_channels,
            )
        )
    return StageResult(
        stage="normalize",
        scope=patch_result.scope,
        status="completed",
        payload=NormalizationBundle(
            source_manifest=patch_result.payload.source_manifest,
            patch_manifest=patch_result.payload.patch_manifest,
            devices=tuple(ensure_connector_descriptors(device) for device in enriched_devices),
        ),
    )
