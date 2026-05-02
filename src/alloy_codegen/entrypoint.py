"""Top-level Python entrypoint consumed by alloy-cli + agents.

The CLI under ``alloy_codegen.cli`` is the canonical command-line
surface; this module is the canonical *Python* surface.  Both are
thin shells over :mod:`alloy_codegen.emit_v2_1` — the emitters
are the single source of truth.

The ``generate(config, out_dir)`` callable is intentionally
duck-typed so alloy-cli (or any future consumer) can pass its own
config dataclass without dragging alloy-codegen into a circular
dependency.
"""

from __future__ import annotations

from collections.abc import Callable
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Protocol, runtime_checkable

from alloy_codegen.emit_v2_1 import (
    emit_linker_script,
    emit_peripheral_id,
    emit_peripheral_traits,
    emit_pin_router,
    emit_runtime_init,
    emit_system_init,
    emit_vector_table,
)
from alloy_codegen.errors import ConfigError
from alloy_codegen.ir.synthesised import SynthesisedDevice
from alloy_codegen.ir.v2_1 import CanonicalDevice
from alloy_codegen.sources.alloy_devices_yml import load_with_synthesis


@runtime_checkable
class _ChipRef(Protocol):
    """Protocol matching ``alloy_cli.core.project.ChipRef`` byte-for-byte."""

    vendor: str
    family: str
    device: str


@runtime_checkable
class _BoardRef(Protocol):
    """Protocol matching ``alloy_cli.core.project.BoardRef``."""

    id: str


@runtime_checkable
class _Config(Protocol):
    """Duck-typed shape for the project config alloy-cli passes us.

    We only depend on the two attributes that disambiguate the
    target — never on alloy-cli's full ``ProjectConfig`` shape.
    """

    chip: _ChipRef | None
    board: _BoardRef | None


@dataclass(frozen=True, slots=True)
class _EmitterEntry:
    name: str
    filename: str
    fn: Callable[[CanonicalDevice, SynthesisedDevice], str]


# Mirrors ``alloy_codegen.cli._EMITTERS`` — duplicated rather
# than imported so the CLI can keep its own ordering / docs.
_EMITTERS: tuple[_EmitterEntry, ...] = (
    _EmitterEntry(
        name="linker_script",
        filename="linker.ld",
        fn=lambda d, _s: emit_linker_script(d),
    ),
    _EmitterEntry(
        name="vector_table",
        filename="vector_table.c",
        fn=emit_vector_table,
    ),
    _EmitterEntry(
        name="peripheral_id",
        filename="peripheral_id.hpp",
        fn=emit_peripheral_id,
    ),
    _EmitterEntry(
        name="peripheral_traits",
        filename="peripheral_traits.h",
        fn=emit_peripheral_traits,
    ),
    _EmitterEntry(
        name="runtime_init",
        filename="runtime_init.c",
        fn=emit_runtime_init,
    ),
    _EmitterEntry(
        name="pin_router",
        filename="pins.h",
        fn=emit_pin_router,
    ),
    _EmitterEntry(
        name="system_init",
        filename="system_init.c",
        fn=emit_system_init,
    ),
)


def _resolve_target(config: Any) -> tuple[str, str, str]:
    """Pull ``(vendor, family, device)`` out of ``config``.

    Raises :class:`ConfigError` when neither ``chip`` nor a
    ready-resolved chip-via-board target is available.  alloy-cli
    is expected to call its own ``core.boards.lookup`` upstream so
    by the time we get the config the chip triple is already
    populated; we keep the board branch only to surface a clean
    error message instead of an attribute lookup explosion.
    """
    chip = getattr(config, "chip", None)
    if chip is not None and all(
        getattr(chip, attr, "") for attr in ("vendor", "family", "device")
    ):
        return chip.vendor, chip.family, chip.device

    board = getattr(config, "board", None)
    if board is not None and getattr(board, "id", ""):
        raise ConfigError(
            f"alloy-codegen.generate received a board-only config "
            f"(board.id={board.id!r}); resolve the board to a "
            f"(vendor, family, device) triple in your own layer "
            f"(e.g. alloy_cli.core.boards.lookup) before calling."
        )
    raise ConfigError(
        "alloy-codegen.generate needs config.chip "
        "(or a chip resolved upstream from config.board); both "
        "are missing or empty."
    )


def _validate_registry(vendor: str, family: str, device: str) -> None:
    """Confirm ``(vendor, family, device)`` is in ``DEVICE_REGISTRY``.

    The registry walks ``data/devices`` lazily on first access;
    missing entries usually mean alloy-devices-yml hasn't admitted
    the chip yet, while a missing submodule is the wheel-install
    case.  Either way, we raise :class:`ConfigError` (the canonical
    pre-pipeline error) so callers don't see a stray
    ``UnsupportedScopeError`` they can't catch.
    """
    # Lazy import — bootstrap walks the data submodule, which may
    # not be mounted in a wheel install.  We delay until the user
    # actually asks for the registry.  ``from … import …`` triggers
    # the module-level ``__getattr__`` so the submodule walk runs
    # *during* the import statement; catch the error there too.
    from alloy_codegen.errors import UnsupportedScopeError

    try:
        from alloy_codegen.bootstrap import DEVICE_REGISTRY  # noqa: F401
        registry = DEVICE_REGISTRY
    except UnsupportedScopeError as exc:
        raise ConfigError(str(exc)) from exc

    devices = registry.get((vendor, family))
    if devices and device in devices:
        return
    if devices:
        raise ConfigError(
            f"device {vendor}/{family}/{device!r} is not admitted; "
            f"closest matches under {vendor}/{family}: "
            f"{', '.join(sorted(devices))}"
        )
    families = sorted(f for v, f in registry if v == vendor)
    if families:
        raise ConfigError(
            f"family {vendor}/{family!r} is not admitted; "
            f"known families for {vendor}: {', '.join(families)}"
        )
    raise ConfigError(
        f"vendor {vendor!r} is not admitted in the canonical "
        "device registry"
    )


def generate(config: Any, out_dir: Path) -> tuple[Path, ...]:
    """Run every emitter against ``config`` and write artifacts.

    Returns the sorted tuple of files written so callers (alloy-cli
    today, MCP tools tomorrow) can log them or feed a stamp cache.

    Raises:
        ConfigError: when the config is missing the target chip.
        StageExecutionError: when the YAML load / synthesis fails.
    """
    vendor, family, device = _resolve_target(config)
    _validate_registry(vendor, family, device)

    canonical, synthesised = load_with_synthesis(
        vendor=vendor, family=family, device=device,
    )

    out_dir = Path(out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    written: list[Path] = []
    for emitter in _EMITTERS:
        text = emitter.fn(canonical, synthesised)
        target = out_dir / emitter.filename
        target.write_text(text, encoding="utf-8")
        written.append(target)

    return tuple(sorted(written))


__all__ = ["generate"]
