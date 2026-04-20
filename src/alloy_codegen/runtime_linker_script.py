"""Generated device-scoped linker scripts."""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR, MemoryRegion
from alloy_codegen.reporting import EmittedArtifact
from alloy_codegen.serialization import canonical_json_sha256

from .emission import _device_generated_path

LINKER_SCRIPT_NAME = "device.ld"
_EXCLUDED_MEMORY_KINDS = frozenset({"io"})


def runtime_linker_script_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_generated_path(family_dir, device.identity.device, LINKER_SCRIPT_NAME)
        for device in devices
    )


def _text_artifact(*, path: str, content: str) -> EmittedArtifact:
    content_bytes = len(content.encode("utf-8"))
    content_sha256 = canonical_json_sha256({"content": content})
    return EmittedArtifact(
        path=path,
        artifact_kind="generated-linker-script",
        content=content,
        content_sha256=content_sha256,
        content_bytes=content_bytes,
    )


def _memory_sort_key(memory: MemoryRegion) -> tuple[str, int, int, str]:
    return (memory.address_space or "", memory.base_address, memory.size_bytes, memory.name.lower())


def _memory_region_name(memory: MemoryRegion) -> str:
    raw_name = memory.name
    if memory.address_space:
        raw_name = f"{memory.address_space}_{raw_name}"
    name = "".join(ch if ch.isalnum() else "_" for ch in raw_name.upper())
    if not name:
        name = "REGION"
    if name[0].isdigit():
        name = f"REGION_{name}"
    return name


def _memory_flags(memory: MemoryRegion) -> str:
    access = memory.access.lower()
    flags = "".join(flag for flag in "rwx" if flag in access)
    return flags or "r"


def _text_region_rank(memory: MemoryRegion) -> tuple[int, int, int, str]:
    roles = set(memory.startup_roles)
    kind = memory.kind.lower()
    access = memory.access.lower()
    if "vector-source" in roles and kind == "flash":
        priority = 0
    elif "vector-source" in roles:
        priority = 1
    elif "copy-source" in roles and kind == "flash":
        priority = 2
    elif kind == "flash":
        priority = 3
    elif "copy-source" in roles:
        priority = 4
    elif "x" in access:
        priority = 5
    elif kind == "rom":
        priority = 6
    else:
        priority = 9
    return (priority, -memory.size_bytes, memory.base_address, memory.name.lower())


def _data_region_rank(memory: MemoryRegion) -> tuple[int, int, int, str]:
    roles = set(memory.startup_roles)
    kind = memory.kind.lower()
    if {"stack-target", "copy-target", "zero-target"} <= roles:
        priority = 0
    elif "stack-target" in roles:
        priority = 1
    elif {"copy-target", "zero-target"} <= roles:
        priority = 2
    elif kind in {"sram", "ram"}:
        priority = 3
    else:
        priority = 9
    return (priority, -memory.size_bytes, memory.base_address, memory.name.lower())


def _publishable_memories(device: CanonicalDeviceIR) -> tuple[MemoryRegion, ...]:
    return tuple(
        memory
        for memory in sorted(device.memories, key=_memory_sort_key)
        if memory.kind.lower() not in _EXCLUDED_MEMORY_KINDS
    )


def _select_text_region(memories: tuple[MemoryRegion, ...]) -> MemoryRegion:
    ranked = sorted(memories, key=_text_region_rank)
    if ranked and _text_region_rank(ranked[0])[0] < 9:
        return ranked[0]
    return memories[0]


def _select_data_region(
    memories: tuple[MemoryRegion, ...],
    *,
    fallback: MemoryRegion,
) -> MemoryRegion:
    ranked = sorted(memories, key=_data_region_rank)
    if ranked and _data_region_rank(ranked[0])[0] < 9:
        return ranked[0]
    return fallback


def emit_runtime_linker_script(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    memories = _publishable_memories(device)
    if not memories:
        raise ValueError(f"{device.identity.device} has no publishable memories for device.ld")

    text_region = _select_text_region(memories)
    data_region = _select_data_region(memories, fallback=text_region)
    region_name_map = {memory.name: _memory_region_name(memory) for memory in memories}
    text_region_name = region_name_map[text_region.name]
    data_region_name = region_name_map[data_region.name]

    memory_lines = []
    for memory in memories:
        memory_lines.append(
            "  "
            f"{region_name_map[memory.name]} ({_memory_flags(memory)}) : "
            f"ORIGIN = 0x{memory.base_address:08X}, LENGTH = 0x{memory.size_bytes:X}"
        )

    address_space_note = []
    for memory in memories:
        address_space = getattr(memory, "address_space", None)
        if address_space:
            address_space_note.append(
                f"  {region_name_map[memory.name]} -> address_space={address_space}"
            )

    comment_lines = [
        f"/* Generated linker script for {device.identity.device}. */",
        f"/* REGION_TEXT={text_region_name}; REGION_DATA={data_region_name} */",
    ]
    if address_space_note:
        comment_lines.append("/* Harvard address-space notes:")
        comment_lines.extend(address_space_note)
        comment_lines.append("*/")

    content = "\n".join(
        [
            *comment_lines,
            "",
            "MEMORY",
            "{",
            *memory_lines,
            "}",
            "",
            f'REGION_ALIAS("REGION_TEXT", {text_region_name});',
            f'REGION_ALIAS("REGION_DATA", {data_region_name});',
            f'REGION_ALIAS("REGION_BSS", {data_region_name});',
            f'REGION_ALIAS("REGION_STACK", {data_region_name});',
            "",
            "__stack_size = DEFINED(__stack_size) ? __stack_size : 0x1000;",
            "",
            "SECTIONS",
            "{",
            "  .vectors :",
            "  {",
            "    KEEP(*(.vectors))",
            "    KEEP(*(.isr_vector))",
            "    KEEP(*(.interrupt_vectors))",
            "  } > REGION_TEXT",
            "",
            "  .text :",
            "  {",
            "    *(.text*)",
            "    *(.rodata*)",
            "    *(.glue_7*)",
            "    *(.glue_7t*)",
            "    KEEP(*(.init))",
            "    KEEP(*(.fini))",
            "  } > REGION_TEXT",
            "",
            "  .init_array :",
            "  {",
            "    __init_array_start = .;",
            "    KEEP(*(SORT(.init_array.*)))",
            "    KEEP(*(.init_array))",
            "    __init_array_end = .;",
            "  } > REGION_TEXT",
            "",
            "  .fini_array :",
            "  {",
            "    __fini_array_start = .;",
            "    KEEP(*(SORT(.fini_array.*)))",
            "    KEEP(*(.fini_array))",
            "    __fini_array_end = .;",
            "  } > REGION_TEXT",
            "",
            "  .data :",
            "  {",
            "    . = ALIGN(4);",
            "    __data_start__ = .;",
            "    *(.data*)",
            "    . = ALIGN(4);",
            "    __data_end__ = .;",
            "  } > REGION_DATA AT> REGION_TEXT",
            "  __data_load_start__ = LOADADDR(.data);",
            "",
            "  .bss (NOLOAD) :",
            "  {",
            "    . = ALIGN(4);",
            "    __bss_start__ = .;",
            "    *(.bss*)",
            "    *(COMMON)",
            "    . = ALIGN(4);",
            "    __bss_end__ = .;",
            "  } > REGION_BSS",
            "",
            "  .stack ORIGIN(REGION_STACK) + LENGTH(REGION_STACK) - __stack_size (NOLOAD) :",
            "  {",
            "    . = ALIGN(8);",
            "    __stack_limit = .;",
            "    . += __stack_size;",
            "    __stack_top = .;",
            "  } > REGION_STACK",
            "}",
            "",
            'ASSERT(__stack_limit >= __bss_end__, "RAM overflow: .bss/.data overlap stack");',
            "",
        ]
    )
    return _text_artifact(
        path=_device_generated_path(family_dir, device.identity.device, LINKER_SCRIPT_NAME),
        content=content,
    )


__all__ = [
    "emit_runtime_linker_script",
    "runtime_linker_script_required_paths",
]
