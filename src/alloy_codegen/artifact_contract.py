"""Validation helpers for the generated runtime artifact contract."""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact
from alloy_codegen.runtime_driver_semantics import (
    runtime_driver_semantics_required_paths,
)
from alloy_codegen.runtime_lite_emission import (
    RUNTIME_LITE_PERIPHERAL_CLASSES,
    runtime_lite_peripheral_class_name,
    runtime_lite_required_paths,
)
from alloy_codegen.runtime_system_clock import runtime_system_clock_required_paths
from alloy_codegen.runtime_systick import runtime_systick_required_paths


def find_runtime_cpp_string_violations(
    artifacts: tuple[EmittedArtifact, ...],
) -> tuple[str, ...]:
    """Return violations for generated runtime artifacts that still carry string literals."""

    violations: list[str] = []
    for artifact in artifacts:
        if artifact.artifact_kind != "generated-cpp":
            continue
        if "/generated/" not in f"/{artifact.path}":
            continue
        if artifact.path.endswith("/startup.cpp") or artifact.path.endswith("/startup_vectors.cpp"):
            continue
        if artifact.content is None:
            continue
        for lineno, line in enumerate(artifact.content.splitlines(), start=1):
            stripped = line.strip()
            if stripped.startswith("#include") or stripped.startswith("#pragma once"):
                continue
            if '"' in line:
                violations.append(
                    f"{artifact.path}:{lineno} contains a string literal in runtime C++ output"
                )
    return tuple(violations)


def find_runtime_lite_contract_violations(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
    artifacts: tuple[EmittedArtifact, ...],
) -> tuple[str, ...]:
    """Return runtime-lite contract violations for foundational runtime consumers."""

    artifacts_by_path = {artifact.path: artifact for artifact in artifacts}
    violations: list[str] = []
    required_paths = runtime_lite_required_paths(family_dir=family_dir, devices=devices)
    required_paths = required_paths + runtime_driver_semantics_required_paths(
        family_dir=family_dir,
        devices=devices,
    )
    required_paths = required_paths + runtime_system_clock_required_paths(
        family_dir=family_dir,
        devices=devices,
    )
    required_paths = required_paths + runtime_systick_required_paths(
        family_dir=family_dir,
        devices=devices,
    )
    for path in required_paths:
        if path not in artifacts_by_path:
            violations.append(f"missing runtime-lite artifact: {path}")

    forbidden_reflection_headers = (
        "connector_tables.hpp",
        "clock_tree_lite.hpp",
        "runtime_refs.hpp",
        "runtime_semantics.hpp",
        "rcc_map.hpp",
        "dma_map.hpp",
        "interrupt_map.hpp",
        "memory_map.hpp",
        "package_map.hpp",
    )
    forbidden_reflection_tokens = (
        "kConnectionCandidates",
        "kConnectionGroups",
        "kClockNodes",
        "kClockGates",
        "kPeripheralClockBindings",
    )
    for artifact in artifacts:
        if artifact.content is None:
            continue
        if f"/{family_dir}/generated/runtime/" not in f"/{artifact.path}":
            continue
        for lineno, line in enumerate(artifact.content.splitlines(), start=1):
            stripped = line.strip()
            if stripped.startswith("#include"):
                for header_name in forbidden_reflection_headers:
                    if header_name in stripped:
                        violations.append(
                            f"{artifact.path}:{lineno} depends on reflection header {header_name}"
                        )
            for token in forbidden_reflection_tokens:
                if token in line:
                    violations.append(
                        f"{artifact.path}:{lineno} leaks reflection payload token {token}"
                    )

    for device in devices:
        runtime_peripherals = tuple(
            peripheral
            for peripheral in device.peripherals
            if runtime_lite_peripheral_class_name(peripheral.ip_name)
            in RUNTIME_LITE_PERIPHERAL_CLASSES
        )
        if not runtime_peripherals:
            continue

        device_runtime_root = f"{family_dir}/generated/runtime/devices/{device.identity.device}"
        runtime_candidates = tuple(
            candidate
            for candidate in device.connection_candidates
            if candidate.peripheral in {peripheral.name for peripheral in runtime_peripherals}
        )
        device_runtime_paths = {
            "peripheral_instances": f"{device_runtime_root}/peripheral_instances.hpp",
            "pins": f"{device_runtime_root}/pins.hpp",
            "registers": f"{device_runtime_root}/registers.hpp",
            "register_fields": f"{device_runtime_root}/register_fields.hpp",
            "clock_bindings": f"{device_runtime_root}/clock_bindings.hpp",
            "dma_bindings": f"{device_runtime_root}/dma_bindings.hpp",
            "routes": f"{device_runtime_root}/routes.hpp",
            "driver_common": f"{device_runtime_root}/driver_semantics/common.hpp",
            "gpio_semantics": f"{device_runtime_root}/driver_semantics/gpio.hpp",
            "uart_semantics": f"{device_runtime_root}/driver_semantics/uart.hpp",
            "i2c_semantics": f"{device_runtime_root}/driver_semantics/i2c.hpp",
            "spi_semantics": f"{device_runtime_root}/driver_semantics/spi.hpp",
            "dma_semantics": f"{device_runtime_root}/driver_semantics/dma.hpp",
            "timer_semantics": f"{device_runtime_root}/driver_semantics/timer.hpp",
            "pwm_semantics": f"{device_runtime_root}/driver_semantics/pwm.hpp",
            "systick": f"{device_runtime_root}/systick.hpp",
            "system_clock": f"{device_runtime_root}/system_clock.hpp",
        }
        content_by_key = {
            key: artifacts_by_path[path].content if path in artifacts_by_path else None
            for key, path in device_runtime_paths.items()
        }

        if (
            content_by_key["peripheral_instances"]
            and "PeripheralInstanceTraits<PeripheralId::"
            not in content_by_key["peripheral_instances"]
        ):
            violations.append(
                f"{device_runtime_paths['peripheral_instances']} does not emit per-instance traits"
            )
        if content_by_key["pins"] and "PinTraits<PinId::" not in content_by_key["pins"]:
            violations.append(f"{device_runtime_paths['pins']} does not emit pin traits")
        if (
            content_by_key["registers"]
            and "RegisterTraits<RegisterId::" not in content_by_key["registers"]
        ):
            violations.append(f"{device_runtime_paths['registers']} does not emit register traits")
        if (
            content_by_key["register_fields"]
            and "RegisterFieldTraits<FieldId::" not in content_by_key["register_fields"]
        ):
            violations.append(
                f"{device_runtime_paths['register_fields']} does not emit register field traits"
            )
        if (
            content_by_key["clock_bindings"]
            and "PeripheralClockBindingTraits<PeripheralId::"
            not in content_by_key["clock_bindings"]
        ):
            violations.append(
                f"{device_runtime_paths['clock_bindings']} does not emit "
                "peripheral clock binding traits"
            )
        if (
            content_by_key["dma_bindings"]
            and "BindingTraits<PeripheralId" not in content_by_key["dma_bindings"]
            and "struct BindingTraits {" not in content_by_key["dma_bindings"]
        ):
            violations.append(
                f"{device_runtime_paths['dma_bindings']} does not emit DMA binding traits"
            )
        if (
            content_by_key["dma_bindings"]
            and "ControllerTraits<DmaControllerId::" not in content_by_key["dma_bindings"]
            and "kDmaControllers" not in content_by_key["dma_bindings"]
        ):
            violations.append(
                f"{device_runtime_paths['dma_bindings']} does not emit DMA controller traits"
            )
        if runtime_candidates:
            routes_content = content_by_key["routes"]
            if routes_content is None:
                violations.append(
                    f"missing runtime-lite routes header: {device_runtime_paths['routes']}"
                )
            elif "RouteTraits<" not in routes_content:
                violations.append(f"{device_runtime_paths['routes']} does not emit route traits")

        if (
            content_by_key["driver_common"]
            and "struct RuntimeRegisterRef" not in content_by_key["driver_common"]
        ):
            violations.append(
                f"{device_runtime_paths['driver_common']} does not emit runtime register refs"
            )
        if content_by_key["systick"] and "struct SysTickTraits" not in content_by_key["systick"]:
            violations.append(f"{device_runtime_paths['systick']} does not emit SysTick traits")
        if content_by_key["systick"] and "configure_for_tick_hz" not in content_by_key["systick"]:
            violations.append(
                f"{device_runtime_paths['systick']} does not emit SysTick configuration helpers"
            )
        if (
            content_by_key["system_clock"]
            and "SystemClockProfileTraits<SystemClockProfileId::"
            not in content_by_key["system_clock"]
        ):
            violations.append(
                f"{device_runtime_paths['system_clock']} does not emit system clock profile traits"
            )
        if (
            content_by_key["system_clock"]
            and "apply_default_system_clock" not in content_by_key["system_clock"]
        ):
            violations.append(
                f"{device_runtime_paths['system_clock']} does not emit default bring-up helper"
            )
        if (
            device.identity.vendor == "microchip"
            and device.identity.family == "same70"
            and content_by_key["system_clock"]
            and "return SystemClockProfileTraits<Id>::kPresent;" in content_by_key["system_clock"]
        ):
            violations.append(
                f"{device_runtime_paths['system_clock']} still emits the generic metadata-only "
                "system-clock fallback for foundational SAME70"
            )
        if (
            device.identity.vendor == "nxp"
            and device.identity.family == "imxrt1060"
            and content_by_key["system_clock"]
            and "return SystemClockProfileTraits<Id>::kPresent;" in content_by_key["system_clock"]
        ):
            violations.append(
                f"{device_runtime_paths['system_clock']} still emits the generic metadata-only "
                "system-clock fallback for foundational IMXRT1060"
            )

        gpio_candidates = tuple(
            candidate
            for candidate in runtime_candidates
            if runtime_lite_peripheral_class_name(
                next(
                    peripheral.ip_name
                    for peripheral in runtime_peripherals
                    if peripheral.name == candidate.peripheral
                )
            )
            == "gpio"
        )
        if gpio_candidates:
            gpio_content = content_by_key["gpio_semantics"]
            if gpio_content is None:
                violations.append(
                    "missing GPIO driver semantics header: "
                    f"{device_runtime_paths['gpio_semantics']}"
                )
            elif "GpioSemanticTraits<PinId::" not in gpio_content:
                violations.append(
                    f"{device_runtime_paths['gpio_semantics']} does not emit GPIO semantic traits"
                )

        for class_name, key, token in (
            ("uart", "uart_semantics", "UartSemanticTraits<PeripheralId::"),
            ("i2c", "i2c_semantics", "I2cSemanticTraits<PeripheralId::"),
            ("spi", "spi_semantics", "SpiSemanticTraits<PeripheralId::"),
        ):
            class_candidates = tuple(
                peripheral
                for peripheral in runtime_peripherals
                if runtime_lite_peripheral_class_name(peripheral.ip_name) == class_name
                and any(candidate.peripheral == peripheral.name for candidate in runtime_candidates)
            )
            if not class_candidates:
                continue
            content = content_by_key[key]
            if content is None:
                violations.append(
                    f"missing {class_name} driver semantics header: {device_runtime_paths[key]}"
                )
            elif token not in content:
                violations.append(
                    f"{device_runtime_paths[key]} does not emit {class_name} semantic traits"
                )

        timer_peripherals = tuple(
            peripheral
            for peripheral in runtime_peripherals
            if runtime_lite_peripheral_class_name(peripheral.ip_name) == "timer"
        )
        if timer_peripherals:
            timer_content = content_by_key["timer_semantics"]
            if timer_content is None:
                violations.append(
                    "missing timer driver semantics header: "
                    f"{device_runtime_paths['timer_semantics']}"
                )
            elif "TimerSemanticTraits<PeripheralId::" not in timer_content:
                violations.append(
                    f"{device_runtime_paths['timer_semantics']} does not emit timer semantic traits"
                )
            elif "TimerChannelSemanticTraits<PeripheralId::" not in timer_content:
                violations.append(
                    f"{device_runtime_paths['timer_semantics']} does not emit timer channel traits"
                )

        pwm_capable_peripherals = tuple(
            peripheral
            for peripheral in runtime_peripherals
            if runtime_lite_peripheral_class_name(peripheral.ip_name) in {"timer", "pwm"}
        )
        if pwm_capable_peripherals:
            pwm_content = content_by_key["pwm_semantics"]
            if pwm_content is None:
                violations.append(
                    f"missing pwm driver semantics header: {device_runtime_paths['pwm_semantics']}"
                )
            elif "PwmSemanticTraits<PeripheralId::" not in pwm_content:
                violations.append(
                    f"{device_runtime_paths['pwm_semantics']} does not emit pwm semantic traits"
                )
            elif "PwmChannelSemanticTraits<PeripheralId::" not in pwm_content:
                violations.append(
                    f"{device_runtime_paths['pwm_semantics']} does not emit pwm channel traits"
                )

        runtime_peripheral_names = {peripheral.name for peripheral in runtime_peripherals}
        runtime_dma_bindings = tuple(
            binding
            for binding in device.dma_bindings
            if binding.peripheral in runtime_peripheral_names
        )
        dma_content = content_by_key["dma_semantics"]
        if dma_content is None:
            violations.append(
                f"missing dma driver semantics header: {device_runtime_paths['dma_semantics']}"
            )
        elif (
            "DmaSemanticTraits<PeripheralId" not in dma_content
            and "struct DmaSemanticTraits {" not in dma_content
        ):
            violations.append(
                f"{device_runtime_paths['dma_semantics']} does not emit dma semantic traits"
            )
        if runtime_dma_bindings and "kDmaSemanticPeripherals" not in (dma_content or ""):
            violations.append(
                f"{device_runtime_paths['dma_semantics']} does not publish DMA semantic rows"
            )

        if device.identity.vendor == "st" and device.identity.family == "stm32g0":
            for binding in runtime_dma_bindings:
                if binding.channel_index is None or binding.request_value is None:
                    violations.append(
                        f"{device.identity.device} DMA binding {binding.binding_id} "
                        "is missing channel_index/request_value"
                    )
        if device.identity.vendor == "st" and device.identity.family == "stm32f4":
            for binding in runtime_dma_bindings:
                if binding.channel_index is None or binding.channel_selector is None:
                    violations.append(
                        f"{device.identity.device} DMA binding {binding.binding_id} "
                        "is missing channel_index/channel_selector"
                    )
        if device.identity.vendor == "microchip" and device.identity.family == "same70":
            for binding in runtime_dma_bindings:
                if binding.request_value is None:
                    violations.append(
                        f"{device.identity.device} DMA binding {binding.binding_id} "
                        "is missing request_value"
                    )
    return tuple(violations)
