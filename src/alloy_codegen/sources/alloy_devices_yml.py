"""Consumer for the ``alloy-devices-yml`` data repository.

After ``adopt-canonical-device-v2-1`` the legacy v1 IR loader is
gone.  This module exposes a single typed entry-point that returns a
:class:`CanonicalDevice` (and, optionally, the matching
:class:`SynthesisedDevice`).
"""

from __future__ import annotations

from pathlib import Path

from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.synthesised import SynthesisedDevice, build_synthesised
from alloy_codegen.ir.v2_1 import CanonicalDevice

# Submodule root resolution: this module lives at
# ``src/alloy_codegen/sources/alloy_devices_yml.py``.
_REPO_ROOT = Path(__file__).resolve().parents[3]
DATA_REPO_ROOT = _REPO_ROOT / "data" / "devices"


def device_yaml_path(*, vendor: str, family: str, device: str) -> Path:
    """Compute the canonical YAML path inside the submodule."""
    return DATA_REPO_ROOT / "vendors" / vendor / family / "devices" / f"{device}.yml"


def resolve_device_yaml(*, vendor: str, family: str, device: str) -> Path | None:
    """Return the YAML path if it exists in the submodule, else ``None``."""
    candidate = device_yaml_path(vendor=vendor, family=family, device=device)
    return candidate if candidate.exists() else None


def is_available(*, vendor: str, family: str, device: str) -> bool:
    """Soft predicate the bootstrap registry can poll."""
    return resolve_device_yaml(vendor=vendor, family=family, device=device) is not None


def load_canonical_device(
    *,
    vendor: str,
    family: str,
    device: str,
) -> CanonicalDevice:
    """Parse a v2.1 device YAML into a :class:`CanonicalDevice`.

    Raises :class:`StageExecutionError` when the file is missing or
    its ``schema:`` key does not match the v2.1 lock-string.
    """
    from alloy_codegen.canonical_device_v2_1 import parse_device

    path = resolve_device_yaml(vendor=vendor, family=family, device=device)
    if path is None:
        raise StageExecutionError(
            f"alloy-devices-yml has no entry for {vendor}/{family}/{device}.  "
            f"Expected at {device_yaml_path(vendor=vendor, family=family, device=device)}"
        )
    return parse_device(path.read_text(encoding="utf-8"))


def load_with_synthesis(
    *,
    vendor: str,
    family: str,
    device: str,
) -> tuple[CanonicalDevice, SynthesisedDevice]:
    """Convenience wrapper: load + synthesise in one call."""
    canonical = load_canonical_device(vendor=vendor, family=family, device=device)
    return canonical, build_synthesised(canonical)


def submodule_revision() -> str | None:
    """Return the git SHA the data submodule is pinned at, or None.

    Best-effort — returns None if the submodule isn't initialised or
    git is unavailable.
    """
    head = DATA_REPO_ROOT / ".git"
    if not head.exists():
        return None
    try:
        if head.is_file():
            gitdir_line = head.read_text(encoding="utf-8").strip()
            relative = gitdir_line.split(": ", 1)[1]
            gitdir = (DATA_REPO_ROOT / relative).resolve()
        else:
            gitdir = head
        head_ref = (gitdir / "HEAD").read_text(encoding="utf-8").strip()
        if head_ref.startswith("ref: "):
            ref_path = gitdir / head_ref[len("ref: ") :]
            return ref_path.read_text(encoding="utf-8").strip()[:40]
        return head_ref[:40]
    except (FileNotFoundError, IndexError, OSError):
        return None


__all__ = [
    "DATA_REPO_ROOT",
    "device_yaml_path",
    "is_available",
    "load_canonical_device",
    "load_with_synthesis",
    "resolve_device_yaml",
    "submodule_revision",
]
