"""Validation helpers for the generated runtime artifact contract."""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact
from alloy_codegen.runtime_capabilities import (
    runtime_capabilities_required_paths,
    runtime_capability_rows,
)
from alloy_codegen.runtime_clock_graph import runtime_clock_graph_required_paths
from alloy_codegen.runtime_driver_semantics import (
    runtime_driver_semantics_required_paths,
)
from alloy_codegen.runtime_enable_domains import runtime_enable_domains_required_paths
from alloy_codegen.runtime_interrupts import runtime_interrupts_required_paths
from alloy_codegen.runtime_lite_emission import (
    RUNTIME_LITE_PERIPHERAL_CLASSES,
    _runtime_lite_gate_ids,
    runtime_lite_peripheral_class_name,
    runtime_lite_required_paths,
)
from alloy_codegen.runtime_resets import runtime_resets_required_paths
from alloy_codegen.runtime_startup import runtime_startup_required_paths
from alloy_codegen.runtime_system_clock import runtime_system_clock_required_paths
from alloy_codegen.runtime_system_sequences import runtime_system_sequences_required_paths
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
    required_paths = required_paths + runtime_startup_required_paths(
        family_dir=family_dir,
        devices=devices,
    )
    required_paths = required_paths + runtime_systick_required_paths(
        family_dir=family_dir,
        devices=devices,
    )
    required_paths = required_paths + runtime_interrupts_required_paths(
        family_dir=family_dir,
        devices=devices,
    )
    required_paths = required_paths + runtime_resets_required_paths(
        family_dir=family_dir,
        devices=devices,
    )
    required_paths = required_paths + runtime_enable_domains_required_paths(
        family_dir=family_dir,
        devices=devices,
    )
    required_paths = required_paths + runtime_clock_graph_required_paths(
        family_dir=family_dir,
        devices=devices,
    )
    required_paths = required_paths + runtime_capabilities_required_paths(
        family_dir=family_dir,
        devices=devices,
    )
    required_paths = required_paths + runtime_system_sequences_required_paths(
        family_dir=family_dir,
        devices=devices,
    )
    for path in required_paths:
        if path not in artifacts_by_path:
            violations.append(f"missing runtime-lite artifact: {path}")

    for artifact in artifacts:
        if artifact.artifact_kind != "generated-cpp":
            continue
        if f"/{family_dir}/generated/" not in f"/{artifact.path}":
            continue
        if f"/{family_dir}/generated/runtime/" in f"/{artifact.path}":
            continue
        if artifact.path.endswith("/startup.cpp") or artifact.path.endswith("/startup_vectors.cpp"):
            continue
        violations.append(f"{artifact.path} is a legacy generated C++ artifact outside runtime/")

    forbidden_reflection_headers = (
        "connector_tables.hpp",
        "clock_tree_lite.hpp",
        "runtime_refs.hpp",
        "runtime_semantics.hpp",
        "startup_descriptors.hpp",
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
            "adc_semantics": f"{device_runtime_root}/driver_semantics/adc.hpp",
            "dac_semantics": f"{device_runtime_root}/driver_semantics/dac.hpp",
            "can_semantics": f"{device_runtime_root}/driver_semantics/can.hpp",
            "rtc_semantics": f"{device_runtime_root}/driver_semantics/rtc.hpp",
            "watchdog_semantics": f"{device_runtime_root}/driver_semantics/watchdog.hpp",
            "timer_semantics": f"{device_runtime_root}/driver_semantics/timer.hpp",
            "pwm_semantics": f"{device_runtime_root}/driver_semantics/pwm.hpp",
            "systick": f"{device_runtime_root}/systick.hpp",
            "startup": f"{device_runtime_root}/startup.hpp",
            "system_clock": f"{device_runtime_root}/system_clock.hpp",
            "interrupts": f"{device_runtime_root}/interrupts.hpp",
            "resets": f"{device_runtime_root}/resets.hpp",
            "enable_domains": f"{device_runtime_root}/enable_domains.hpp",
            "clock_graph": f"{device_runtime_root}/clock_graph.hpp",
            "capabilities": f"{device_runtime_root}/capabilities.hpp",
            "system_sequences": f"{device_runtime_root}/system_sequences.hpp",
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
            content_by_key["startup"]
            and "struct VectorSlotDescriptor" not in content_by_key["startup"]
        ):
            violations.append(
                f"{device_runtime_paths['startup']} does not emit vector slot descriptors"
            )
        if content_by_key["startup"] and "kVectorSlots" not in content_by_key["startup"]:
            violations.append(
                f"{device_runtime_paths['startup']} does not emit startup vector slots"
            )
        if content_by_key["startup"] and "kStartupDescriptors" not in content_by_key["startup"]:
            violations.append(
                f"{device_runtime_paths['startup']} does not emit startup descriptors"
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

        if (
            content_by_key["interrupts"]
            and "enum class InterruptId" not in content_by_key["interrupts"]
        ):
            violations.append(
                f"{device_runtime_paths['interrupts']} does not emit InterruptId enum"
            )
        if (
            content_by_key["interrupts"]
            and "kInterruptDescriptors" not in content_by_key["interrupts"]
        ):
            violations.append(
                f"{device_runtime_paths['interrupts']} does not emit kInterruptDescriptors"
            )
        if content_by_key["resets"] and "kResetDescriptors" not in content_by_key["resets"]:
            violations.append(f"{device_runtime_paths['resets']} does not emit kResetDescriptors")
        if _runtime_lite_gate_ids(device):
            enable_domains_content = content_by_key["enable_domains"]
            if enable_domains_content is None:
                violations.append(
                    "missing runtime enable-domain header: "
                    f"{device_runtime_paths['enable_domains']}"
                )
            elif "kEnableDomains" not in enable_domains_content:
                violations.append(
                    f"{device_runtime_paths['enable_domains']} does not emit kEnableDomains"
                )
            elif "EnableDomainTraits<EnableDomainId::" not in enable_domains_content:
                violations.append(
                    f"{device_runtime_paths['enable_domains']} does not emit enable-domain traits"
                )
            elif "PeripheralEnableDomainTraits<PeripheralId::" not in enable_domains_content:
                violations.append(
                    f"{device_runtime_paths['enable_domains']} does not emit per-peripheral "
                    "enable-domain traits"
                )
        if (
            content_by_key["clock_graph"]
            and "enum class ClockNodeId" not in content_by_key["clock_graph"]
        ):
            violations.append(
                f"{device_runtime_paths['clock_graph']} does not emit ClockNodeId enum"
            )
        if (
            content_by_key["clock_graph"]
            and "kClockDependencies" not in content_by_key["clock_graph"]
        ):
            violations.append(
                f"{device_runtime_paths['clock_graph']} does not emit kClockDependencies"
            )
        if (
            content_by_key["capabilities"]
            and "enum class CapabilityId" not in content_by_key["capabilities"]
        ):
            violations.append(
                f"{device_runtime_paths['capabilities']} does not emit CapabilityId enum"
            )
        if content_by_key["capabilities"] and "kCapabilities" not in content_by_key["capabilities"]:
            violations.append(f"{device_runtime_paths['capabilities']} does not emit kCapabilities")
        if (
            content_by_key["capabilities"]
            and "PeripheralCapabilityTraits<PeripheralId::" not in content_by_key["capabilities"]
        ):
            violations.append(
                f"{device_runtime_paths['capabilities']} does not emit peripheral capability traits"
            )
        if (
            content_by_key["capabilities"]
            and "PeripheralClassCapabilityTraits<PeripheralClassId::"
            not in content_by_key["capabilities"]
        ):
            violations.append(
                f"{device_runtime_paths['capabilities']} does not emit class capability traits"
            )
        if (
            content_by_key["system_sequences"]
            and "enum class SystemSequenceId" not in content_by_key["system_sequences"]
        ):
            violations.append(
                f"{device_runtime_paths['system_sequences']} does not emit SystemSequenceId enum"
            )
        if (
            content_by_key["system_sequences"]
            and "kSystemSequenceSteps" not in content_by_key["system_sequences"]
        ):
            violations.append(
                f"{device_runtime_paths['system_sequences']} does not emit kSystemSequenceSteps"
            )
        if (
            content_by_key["system_sequences"]
            and "SystemSequenceTraits<SystemSequenceId::default_bringup>"
            not in content_by_key["system_sequences"]
        ):
            violations.append(
                f"{device_runtime_paths['system_sequences']} does not emit default bring-up traits"
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

        adc_peripherals = tuple(
            peripheral
            for peripheral in runtime_peripherals
            if runtime_lite_peripheral_class_name(peripheral.ip_name) == "adc"
        )
        if adc_peripherals:
            adc_content = content_by_key["adc_semantics"]
            if adc_content is None:
                violations.append(
                    f"missing adc driver semantics header: {device_runtime_paths['adc_semantics']}"
                )
            elif "AdcSemanticTraits<PeripheralId::" not in adc_content:
                violations.append(
                    f"{device_runtime_paths['adc_semantics']} does not emit adc semantic traits"
                )

        dac_peripherals = tuple(
            peripheral
            for peripheral in runtime_peripherals
            if runtime_lite_peripheral_class_name(peripheral.ip_name) == "dac"
        )
        if dac_peripherals:
            dac_content = content_by_key["dac_semantics"]
            if dac_content is None:
                violations.append(
                    f"missing dac driver semantics header: {device_runtime_paths['dac_semantics']}"
                )
            elif "DacSemanticTraits<PeripheralId::" not in dac_content:
                violations.append(
                    f"{device_runtime_paths['dac_semantics']} does not emit dac semantic traits"
                )
            elif "DacChannelSemanticTraits<PeripheralId::" not in dac_content:
                violations.append(
                    f"{device_runtime_paths['dac_semantics']} does not emit dac channel traits"
                )

        can_peripherals = tuple(
            peripheral
            for peripheral in runtime_peripherals
            if runtime_lite_peripheral_class_name(peripheral.ip_name) == "can"
        )
        if can_peripherals:
            can_content = content_by_key["can_semantics"]
            if can_content is None:
                violations.append(
                    f"missing can driver semantics header: {device_runtime_paths['can_semantics']}"
                )
            elif "CanSemanticTraits<PeripheralId::" not in can_content:
                violations.append(
                    f"{device_runtime_paths['can_semantics']} does not emit can semantic traits"
                )

        rtc_peripherals = tuple(
            peripheral
            for peripheral in runtime_peripherals
            if runtime_lite_peripheral_class_name(peripheral.ip_name) == "rtc"
        )
        if rtc_peripherals:
            rtc_content = content_by_key["rtc_semantics"]
            if rtc_content is None:
                violations.append(
                    f"missing rtc driver semantics header: {device_runtime_paths['rtc_semantics']}"
                )
            elif "RtcSemanticTraits<PeripheralId::" not in rtc_content:
                violations.append(
                    f"{device_runtime_paths['rtc_semantics']} does not emit rtc semantic traits"
                )

        watchdog_peripherals = tuple(
            peripheral
            for peripheral in runtime_peripherals
            if runtime_lite_peripheral_class_name(peripheral.ip_name) == "watchdog"
        )
        if watchdog_peripherals:
            watchdog_content = content_by_key["watchdog_semantics"]
            if watchdog_content is None:
                violations.append(
                    "missing watchdog driver semantics header: "
                    f"{device_runtime_paths['watchdog_semantics']}"
                )
            elif "WatchdogSemanticTraits<PeripheralId::" not in watchdog_content:
                violations.append(
                    f"{device_runtime_paths['watchdog_semantics']} does not emit "
                    "watchdog semantic traits"
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
        runtime_capabilities = runtime_capability_rows(device)
        class_capabilities = {capability.peripheral_class for capability in runtime_capabilities}
        peripheral_capabilities = {
            capability.peripheral for capability in runtime_capabilities if capability.peripheral
        }
        for peripheral in runtime_peripherals:
            class_name = runtime_lite_peripheral_class_name(peripheral.ip_name)
            if peripheral.name in peripheral_capabilities:
                continue
            if class_name in class_capabilities:
                continue
            violations.append(
                f"{device.identity.device} runtime peripheral {peripheral.name} "
                "has no published capability coverage"
            )
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
