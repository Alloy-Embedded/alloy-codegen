"""CMake package-config emitter (added by ``add-cmake-package-config``).

Emits, alongside the existing per-device runtime artifacts, a CMake
``find_package(AlloyDevice REQUIRED COMPONENTS <device>)`` integration
that exposes each admitted device as an ``INTERFACE IMPORTED`` target
``AlloyDevice::<device>`` carrying every flag the consumer needs to
compile + link a firmware image:

  - ``target_include_directories`` for runtime + device-specific dirs
  - ``target_compile_features INTERFACE cxx_std_20``
  - per-core compile options (``-mcpu=...``, ``-mthumb``, ABI flags)
  - linker-script reference (``device.ld``) via ``target_link_options``
  - startup translation unit via ``target_sources``

A separate per-core ``toolchain-<core>.cmake`` fragment is emitted as
opt-in: consumers using their own toolchain skip it; consumers
starting from scratch load it via
``-DCMAKE_TOOLCHAIN_FILE=...`` to get the standard cross-compiler
triple (arm-none-eabi-gcc, riscv32-unknown-elf-gcc, etc.).

Path references anchor on ``${ALLOY_DEVICE_ROOT}`` (default:
package-relative) so consumers can override the artifact root for
custom layouts.
"""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import _cmake_artifact

CMAKE_ROOT_DIR = "cmake"


# Per-core compile + link flag tables.  Sourced from the standard
# arm-none-eabi-gcc / riscv32-unknown-elf-gcc / avr-gcc / xtensa-esp*-elf-gcc
# invocation patterns.  Consumers wanting different ABIs (e.g. soft
# float on a Cortex-M4F) override per-target via standard CMake hooks.
_CORE_COMPILE_FLAGS: dict[str, tuple[str, ...]] = {
    "cortex-m0": ("-mcpu=cortex-m0", "-mthumb", "-mfloat-abi=soft"),
    "cortex-m0plus": ("-mcpu=cortex-m0plus", "-mthumb", "-mfloat-abi=soft"),
    # RP2040 carries the "-dual" suffix; flag-wise it's the same as cortex-m0plus.
    "cortex-m0plus-dual": ("-mcpu=cortex-m0plus", "-mthumb", "-mfloat-abi=soft"),
    "cortex-m3": ("-mcpu=cortex-m3", "-mthumb", "-mfloat-abi=soft"),
    "cortex-m4": ("-mcpu=cortex-m4", "-mthumb", "-mfloat-abi=soft"),
    "cortex-m4f": (
        "-mcpu=cortex-m4",
        "-mthumb",
        "-mfloat-abi=hard",
        "-mfpu=fpv4-sp-d16",
    ),
    "cortex-m7": ("-mcpu=cortex-m7", "-mthumb", "-mfloat-abi=soft"),
    "cortex-m7f": (
        "-mcpu=cortex-m7",
        "-mthumb",
        "-mfloat-abi=hard",
        "-mfpu=fpv5-d16",
    ),
    "avr8": ("-mmcu=avr",),  # device-specific -mmcu may override at consumer side
    "rv32imc": ("-march=rv32imc", "-mabi=ilp32"),
    "rv32imac": ("-march=rv32imac", "-mabi=ilp32"),
    "xtensa-lx6": ("-mlongcalls",),
    "xtensa-lx7": ("-mlongcalls",),
}


# Linker options derived from the same core map.  Most cores reuse the
# compile flags (the toolchain re-applies `-mcpu`/`-march` at link), and
# every device adds ``-T<device.ld>`` + ``-nostartfiles``.
def _core_link_flags(core: str) -> tuple[str, ...]:
    flags = _CORE_COMPILE_FLAGS.get(core, ())
    return (*flags, "-nostartfiles")


# Per-core toolchain triple + system-processor mapping.  Drives the
# opt-in toolchain fragment.
_CORE_TOOLCHAIN: dict[str, tuple[str, str, str, str]] = {
    # core → (CMAKE_SYSTEM_PROCESSOR, C compiler, C++ compiler, AR)
    "cortex-m0": ("arm", "arm-none-eabi-gcc", "arm-none-eabi-g++", "arm-none-eabi-ar"),
    "cortex-m0plus": ("arm", "arm-none-eabi-gcc", "arm-none-eabi-g++", "arm-none-eabi-ar"),
    "cortex-m0plus-dual": (
        "arm",
        "arm-none-eabi-gcc",
        "arm-none-eabi-g++",
        "arm-none-eabi-ar",
    ),
    "cortex-m3": ("arm", "arm-none-eabi-gcc", "arm-none-eabi-g++", "arm-none-eabi-ar"),
    "cortex-m4": ("arm", "arm-none-eabi-gcc", "arm-none-eabi-g++", "arm-none-eabi-ar"),
    "cortex-m4f": ("arm", "arm-none-eabi-gcc", "arm-none-eabi-g++", "arm-none-eabi-ar"),
    "cortex-m7": ("arm", "arm-none-eabi-gcc", "arm-none-eabi-g++", "arm-none-eabi-ar"),
    "cortex-m7f": ("arm", "arm-none-eabi-gcc", "arm-none-eabi-g++", "arm-none-eabi-ar"),
    "avr8": ("avr", "avr-gcc", "avr-g++", "avr-ar"),
    "rv32imc": (
        "riscv32",
        "riscv32-unknown-elf-gcc",
        "riscv32-unknown-elf-g++",
        "riscv32-unknown-elf-ar",
    ),
    "rv32imac": (
        "riscv32",
        "riscv32-unknown-elf-gcc",
        "riscv32-unknown-elf-g++",
        "riscv32-unknown-elf-ar",
    ),
    "xtensa-lx6": (
        "xtensa",
        "xtensa-esp32-elf-gcc",
        "xtensa-esp32-elf-g++",
        "xtensa-esp32-elf-ar",
    ),
    "xtensa-lx7": (
        "xtensa",
        "xtensa-esp32s3-elf-gcc",
        "xtensa-esp32s3-elf-g++",
        "xtensa-esp32s3-elf-ar",
    ),
}


def core_compile_flags(core: str) -> tuple[str, ...]:
    """Public accessor — used by the regression test."""
    return _CORE_COMPILE_FLAGS.get(core, ())


def core_toolchain_triple(core: str) -> tuple[str, str, str, str] | None:
    return _CORE_TOOLCHAIN.get(core)


def _vendor_family_path(device: CanonicalDeviceIR) -> tuple[str, str]:
    return device.identity.vendor, device.identity.family


def _device_dir_relative(device: CanonicalDeviceIR) -> str:
    """Path under ``${ALLOY_DEVICE_ROOT}`` to this device's runtime root."""
    vendor, family = _vendor_family_path(device)
    return f"{vendor}/{family}/generated/runtime/devices/{device.identity.device}"


def _family_runtime_dir_relative(device: CanonicalDeviceIR) -> str:
    vendor, family = _vendor_family_path(device)
    return f"{vendor}/{family}/generated/runtime"


def _startup_source_relative(device: CanonicalDeviceIR) -> str:
    """Pick the right startup translation unit per core.  AVR / Xtensa
    targets emit ``startup.cpp``; ARM Cortex-M and RISC-V default the
    same.  Some pipeline variants emit ``startup_vectors.cpp`` instead
    — consumer linker invocation pulls in whichever exists."""
    vendor, family = _vendor_family_path(device)
    return f"{vendor}/{family}/generated/devices/{device.identity.device}/startup.cpp"


def _linker_script_relative(device: CanonicalDeviceIR) -> str:
    vendor, family = _vendor_family_path(device)
    return f"{vendor}/{family}/generated/devices/{device.identity.device}/device.ld"


def emit_cmake_device_module(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit the per-device ``AlloyDevice-<device>.cmake`` module.

    Declares an ``INTERFACE IMPORTED`` target named
    ``AlloyDevice::<device>`` carrying every flag the consumer needs.
    """
    core = device.identity.core
    compile_flags = _CORE_COMPILE_FLAGS.get(core, ())
    link_flags = _core_link_flags(core)
    toolchain = _CORE_TOOLCHAIN.get(core)

    target = f"AlloyDevice::{device.identity.device}"
    runtime_dir = _family_runtime_dir_relative(device)
    device_dir = _device_dir_relative(device)
    startup = _startup_source_relative(device)
    linker_script = _linker_script_relative(device)

    lines = [
        "# Auto-generated by alloy-codegen — do not edit.",
        "# Per-device CMake INTERFACE library (added by ``add-cmake-package-config``).",
        f"# Device: {device.identity.device} (vendor={device.identity.vendor},"
        f" family={device.identity.family}, core={core})",
        "",
        "if(NOT DEFINED ALLOY_DEVICE_ROOT)",
        "  # Default to the package-relative layout: this .cmake file lives",
        "  # under <root>/cmake/, so the artifact root is the parent dir.",
        '  get_filename_component(ALLOY_DEVICE_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)',
        "endif()",
        "",
        f"if(NOT TARGET {target})",
        f"  add_library({target} INTERFACE IMPORTED)",
        "",
        f"  target_compile_features({target} INTERFACE cxx_std_20)",
        "",
    ]

    if compile_flags:
        lines.append(f"  target_compile_options({target} INTERFACE")
        for flag in compile_flags:
            lines.append(f"    {flag}")
        lines.append("  )")
        lines.append("")

    lines.extend(
        [
            f"  target_include_directories({target} INTERFACE",
            f'    "${{ALLOY_DEVICE_ROOT}}/{runtime_dir}"',
            f'    "${{ALLOY_DEVICE_ROOT}}/{device_dir}"',
            "  )",
            "",
            f"  target_link_options({target} INTERFACE",
        ]
    )
    for flag in link_flags:
        lines.append(f"    {flag}")
    lines.append(f'    "-T${{ALLOY_DEVICE_ROOT}}/{linker_script}"')
    lines.extend(
        [
            "  )",
            "",
            f"  target_sources({target} INTERFACE",
            f'    "${{ALLOY_DEVICE_ROOT}}/{startup}"',
            "  )",
            "endif()",
            "",
        ]
    )

    if toolchain is not None:
        lines.extend(
            [
                "# Opt-in toolchain fragment for this core lives at:",
                f"#   ${{CMAKE_CURRENT_LIST_DIR}}/toolchain-{core}.cmake",
                "# Load via -DCMAKE_TOOLCHAIN_FILE=<path> to pick up the",
                "# standard cross-compiler triple; consumers with their",
                "# own toolchain ignore it.",
                "",
            ]
        )

    content = "\n".join(lines)
    vendor, family = _vendor_family_path(device)
    artifact_path = f"{vendor}/{family}/generated/cmake/AlloyDevice-{device.identity.device}.cmake"
    return _cmake_artifact(path=artifact_path, content=content)


def emit_cmake_toolchain_fragment(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact | None:
    """Emit the opt-in per-core toolchain fragment.

    Returns ``None`` for cores without a registered triple — those
    devices skip the toolchain artifact (consumers must bring their
    own).
    """
    core = device.identity.core
    toolchain = _CORE_TOOLCHAIN.get(core)
    if toolchain is None:
        return None
    processor, c_compiler, cxx_compiler, ar = toolchain
    lines = [
        "# Auto-generated by alloy-codegen — do not edit.",
        "# Opt-in toolchain fragment (added by ``add-cmake-package-config``).",
        f"# Core: {core}",
        "",
        "set(CMAKE_SYSTEM_NAME Generic)",
        f"set(CMAKE_SYSTEM_PROCESSOR {processor})",
        "",
        f"set(CMAKE_C_COMPILER {c_compiler})",
        f"set(CMAKE_CXX_COMPILER {cxx_compiler})",
        f"set(CMAKE_AR {ar})",
        "",
        "# Skip the default compiler-detection link checks (they fail",
        "# without a libc available for the target).",
        "set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)",
        "",
        "set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)",
        "set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)",
        "set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)",
        "set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)",
        "",
    ]
    content = "\n".join(lines)
    vendor, family = _vendor_family_path(device)
    artifact_path = f"{vendor}/{family}/generated/cmake/toolchain-{core}.cmake"
    return _cmake_artifact(path=artifact_path, content=content)


def emit_cmake_meta_package(
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[EmittedArtifact, EmittedArtifact]:
    """Emit the top-level meta-package
    (``cmake/AlloyDeviceConfig.cmake`` + ``AlloyDeviceConfigVersion.cmake``).

    The config file resolves ``find_package(AlloyDevice REQUIRED
    COMPONENTS ...)`` calls by including the matching per-device
    ``AlloyDevice-<device>.cmake`` from the right vendor/family
    sub-directory.
    """
    config_lines = [
        "# Auto-generated by alloy-codegen — do not edit.",
        "# Top-level CMake meta-package (added by ``add-cmake-package-config``).",
        "#",
        "# Resolves find_package(AlloyDevice REQUIRED COMPONENTS <device>...)",
        "# by including the per-device AlloyDevice-<device>.cmake module from",
        "# the matching vendor/family sub-directory.",
        "",
        "if(NOT DEFINED ALLOY_DEVICE_ROOT)",
        '  get_filename_component(ALLOY_DEVICE_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)',
        "endif()",
        "",
        "set(_ALLOY_DEVICE_COMPONENT_PATHS",
    ]
    # Build a flat lookup table mapping component name → relative .cmake path.
    for device in devices:
        vendor = device.identity.vendor
        family = device.identity.family
        component = device.identity.device
        rel = f"{vendor}/{family}/generated/cmake/AlloyDevice-{component}.cmake"
        config_lines.append(f'  "{component}={rel}"')
    config_lines.extend(
        [
            ")",
            "",
            "foreach(component ${AlloyDevice_FIND_COMPONENTS})",
            "  set(_alloy_found FALSE)",
            "  foreach(entry ${_ALLOY_DEVICE_COMPONENT_PATHS})",
            '    string(REPLACE "=" ";" parts ${entry})',
            "    list(GET parts 0 _name)",
            "    list(GET parts 1 _path)",
            "    if(_name STREQUAL component)",
            '      include("${ALLOY_DEVICE_ROOT}/${_path}")',
            "      set(_alloy_found TRUE)",
            "      break()",
            "    endif()",
            "  endforeach()",
            "  if(NOT _alloy_found)",
            "    set(AlloyDevice_${component}_FOUND FALSE)",
            "    if(AlloyDevice_FIND_REQUIRED_${component})",
            '      message(FATAL_ERROR "AlloyDevice: unknown component \\"${component}\\"")',
            "    endif()",
            "  else()",
            "    set(AlloyDevice_${component}_FOUND TRUE)",
            "  endif()",
            "endforeach()",
            "",
            "set(AlloyDevice_FOUND TRUE)",
            "",
        ]
    )

    version_lines = [
        "# Auto-generated by alloy-codegen — do not edit.",
        "# CMake package version file (added by ``add-cmake-package-config``).",
        "",
        'set(PACKAGE_VERSION "0.1.0")',
        "",
        "if(PACKAGE_FIND_VERSION VERSION_LESS PACKAGE_VERSION)",
        "  set(PACKAGE_VERSION_COMPATIBLE TRUE)",
        "  if(PACKAGE_FIND_VERSION VERSION_EQUAL PACKAGE_VERSION)",
        "    set(PACKAGE_VERSION_EXACT TRUE)",
        "  endif()",
        "else()",
        "  set(PACKAGE_VERSION_COMPATIBLE FALSE)",
        "endif()",
        "",
    ]

    config = _cmake_artifact(
        path=f"{CMAKE_ROOT_DIR}/AlloyDeviceConfig.cmake",
        content="\n".join(config_lines),
    )
    version = _cmake_artifact(
        path=f"{CMAKE_ROOT_DIR}/AlloyDeviceConfigVersion.cmake",
        content="\n".join(version_lines),
    )
    return config, version


__all__ = (
    "core_compile_flags",
    "core_toolchain_triple",
    "emit_cmake_device_module",
    "emit_cmake_toolchain_fragment",
    "emit_cmake_meta_package",
)
