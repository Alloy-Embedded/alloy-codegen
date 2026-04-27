"""Per-board BSP header emitter (add-board-support-package-emitter).

Renders a ``<vendor>/<family>/generated/runtime/boards/<board_id>/board.hpp``
artifact for every admitted board.  Names on-board pin functions
(LEDs, buttons, debug UART/SPI/I2C) as typed ``PinId`` constexpr
constants grouped by category, plus the default ``ClockProfile``
reference.  Each named pin embeds a
``static_assert(GpioSemanticTraits<PinId::*>::kPresent)`` so consumer
typos fail at ``#include``-time.
"""

from __future__ import annotations

from collections import defaultdict

from .emission import _cpp_artifact, _cpp_namespace_block, _enum_identifier, _text_artifact
from .ir.model import BoardDescriptor, CanonicalDeviceIR, NamedPinDescriptor
from .reporting import EmittedArtifact
from .runtime_lite_emission import _runtime_namespace_components


def _board_namespace_components(
    device: CanonicalDeviceIR, board: BoardDescriptor
) -> tuple[str, str, str, str, str, str]:
    return (
        *_runtime_namespace_components(device),
        "boards",
        _enum_identifier(board.board_id).lower(),
    )


def _board_path(family_dir: str, board: BoardDescriptor) -> str:
    return (
        f"{family_dir}/generated/runtime/boards/"
        f"{_enum_identifier(board.board_id).lower()}/board.hpp"
    )


def _category_for(named: NamedPinDescriptor) -> str:
    """Map a named-pin label to a logical category (Leds, Buttons,
    DebugUart, DebugSpi, DebugI2c, Pins).  The category drives which
    ``struct`` the constexpr is grouped under in the emitted header."""
    upper = named.name.upper()
    if upper.startswith("LED"):
        return "Leds"
    if upper.startswith("BUTTON") or upper.startswith("BTN"):
        return "Buttons"
    if upper.startswith("UART_DBG") or upper.startswith("DEBUG_UART"):
        return "DebugUart"
    if upper.startswith("SPI_DBG") or upper.startswith("DEBUG_SPI"):
        return "DebugSpi"
    if upper.startswith("I2C_DBG") or upper.startswith("DEBUG_I2C"):
        return "DebugI2c"
    return "Pins"


def _short_name(named: NamedPinDescriptor) -> str:
    """Strip the category prefix and convert SHOUTING_SNAKE to PascalCase
    suffix (LED_GREEN -> Green, BUTTON_USER -> User, UART_DBG_TX -> Tx)."""
    upper = named.name.upper()
    for prefix in (
        "LED_",
        "BUTTON_",
        "BTN_",
        "UART_DBG_",
        "DEBUG_UART_",
        "SPI_DBG_",
        "DEBUG_SPI_",
        "I2C_DBG_",
        "DEBUG_I2C_",
    ):
        if upper.startswith(prefix):
            stripped = upper[len(prefix) :]
            break
    else:
        stripped = upper
    return "".join(part.capitalize() for part in stripped.split("_") if part) or "Pin"


def emit_runtime_board_header(
    *, family_dir: str, device: CanonicalDeviceIR, board: BoardDescriptor
) -> EmittedArtifact:
    """Render one ``board.hpp`` artifact for the given board overlay."""
    by_category: dict[str, list[NamedPinDescriptor]] = defaultdict(list)
    for named in board.named_pins:
        by_category[_category_for(named)].append(named)

    static_asserts: list[str] = []
    body_blocks: list[str] = []

    for category, items in sorted(by_category.items()):
        block_lines = [f"struct {category} {{"]
        debug_peripheral: str | None = None
        for named in items:
            short = _short_name(named)
            pin_id = _enum_identifier(named.pin)
            block_lines.append(f"  static constexpr PinId k{short} = PinId::{pin_id};")
            polarity_value = "true" if named.polarity == "active_high" else "false"
            block_lines.append(f"  static constexpr bool k{short}ActiveHigh = {polarity_value};")
            if named.peripheral and debug_peripheral is None and category.startswith("Debug"):
                debug_peripheral = named.peripheral
            if named.signal:
                block_lines.append(f"  // {named.name} signal = {named.signal}")
            static_asserts.append(
                f"static_assert(::{_runtime_namespace_components(device)[0]}::"
                f"{_runtime_namespace_components(device)[1]}::generated::runtime::"
                f"devices::{_enum_identifier(device.identity.device)}::driver_semantics::"
                f"GpioSemanticTraits<PinId::{pin_id}>::kPresent, "
                f'"board pin {named.name} ({named.pin}) not present on '
                f'{device.identity.device}");'
            )
        if debug_peripheral is not None:
            block_lines.insert(
                1,
                f"  static constexpr PeripheralId kPeripheral = "
                f"PeripheralId::{_enum_identifier(debug_peripheral)};",
            )
        block_lines.append("};")
        body_blocks.append("\n".join(block_lines))

    if board.default_clock_profile:
        clock_profile_line = (
            f"// Default clock profile: {board.default_clock_profile}\n"
            "// (consumer wires this via clock_profiles header)"
        )
    else:
        clock_profile_line = "// No default clock profile declared."

    body = "\n\n".join([*body_blocks, clock_profile_line])

    namespace_block = _cpp_namespace_block(_board_namespace_components(device, board), body)

    device_id = _enum_identifier(device.identity.device)
    content = "\n".join(
        [
            "#pragma once",
            "",
            '#include "../../devices/' + device_id + '/pins.hpp"',
            '#include "../../devices/' + device_id + '/peripheral_instances.hpp"',
            '#include "../../devices/' + device_id + '/driver_semantics/gpio.hpp"',
            "",
            namespace_block,
            "",
            *static_asserts,
            "",
        ]
    )
    return _cpp_artifact(path=_board_path(family_dir, board), content=content)


def emit_boards_manifest(
    *, family_dir: str, devices: tuple[CanonicalDeviceIR, ...]
) -> EmittedArtifact:
    """Top-level ``metadata/boards.json`` manifest enumerating every
    admitted board across the family scope (add-board-support-package-emitter).
    Each entry carries ``board_id``, ``device``, ``vendor``, ``family``,
    ``package``, and ``summary`` so tooling (CLI, docs site, IDE
    integrations) can list available boards without parsing every
    per-device sidecar."""
    entries: list[dict[str, str]] = []
    for device in devices:
        for board in device.boards:
            entries.append(
                {
                    "board_id": board.board_id,
                    "device": device.identity.device,
                    "vendor": device.identity.vendor,
                    "family": device.identity.family,
                    "package": board.package,
                    "summary": board.summary,
                }
            )
    payload = {
        "manifest_kind": "boards-manifest-v1",
        "boards": sorted(entries, key=lambda e: e["board_id"]),
    }
    return _text_artifact(
        path=f"{family_dir}/metadata/boards.json",
        artifact_kind="canonical-metadata",
        payload=payload,
    )
