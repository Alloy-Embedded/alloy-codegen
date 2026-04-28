"""Consumer for the ``alloy-devices-yml`` data repository.

Added by ``extract-alloy-devices-data-repo``.

The data repo holds the canonical YAML form of every admitted
:class:`CanonicalDeviceIR`.  This module short-circuits the
normalize stage when a device's YAML is present in the
submodule at ``data/devices/`` — parsing the YAML into an IR
directly, bypassing the legacy SVD + patch path.

Devices whose YAML is **absent** from the submodule fall through
to the legacy adapter, so families that haven't migrated yet
keep working unchanged.

Public surface:

* :func:`resolve_device_yaml(vendor, family, device)` —
  filesystem lookup; returns ``None`` if absent.
* :func:`load_canonical_device(vendor, family, device)` —
  parses the YAML into a :class:`CanonicalDeviceIR`.  Raises if
  not present (use :func:`resolve_device_yaml` first if you
  need a soft check).
* :func:`is_available(vendor, family, device)` — boolean
  short-circuit predicate for the normalize stage.
"""

from __future__ import annotations

from pathlib import Path

from alloy_codegen.canonical_device_yaml import parse_device, validate_device
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.model import CanonicalDeviceIR

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
    """Soft predicate for the normalize stage's short-circuit."""
    return resolve_device_yaml(vendor=vendor, family=family, device=device) is not None


def load_canonical_device(
    *, vendor: str, family: str, device: str, validate: bool = True
) -> CanonicalDeviceIR:
    """Parse the device YAML into a :class:`CanonicalDeviceIR`.

    When ``validate`` is True (default), schema-validates the
    YAML before parsing — catches a malformed pin in the data
    repo at the boundary instead of inside normalize.
    """
    path = resolve_device_yaml(vendor=vendor, family=family, device=device)
    if path is None:
        raise StageExecutionError(
            f"alloy-devices-yml has no entry for {vendor}/{family}/{device}.  "
            f"Expected at {device_yaml_path(vendor=vendor, family=family, device=device)}"
        )
    text = path.read_text(encoding="utf-8")
    if validate:
        try:
            validate_device(text)
        except StageExecutionError as exc:
            raise StageExecutionError(
                f"alloy-devices-yml entry for {vendor}/{family}/{device} "
                f"({path}) failed schema validation: {exc}"
            ) from None
    return parse_device(text)


def submodule_revision() -> str | None:
    """Return the git SHA the submodule is pinned at, or None.

    Used by the bump tool + provenance reports.  Best-effort —
    returns None if the submodule isn't initialised or git is
    unavailable.
    """
    head = DATA_REPO_ROOT / ".git"
    if not head.exists():
        return None
    # ``.git`` inside a submodule is a file pointing at the real
    # gitdir under ``../.git/modules/<path>``.  Reading
    # ``HEAD`` from the resolved gitdir gives the SHA.
    try:
        if head.is_file():
            gitdir_line = head.read_text(encoding="utf-8").strip()
            # ``gitdir: <relative-path>``
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
    "resolve_device_yaml",
    "submodule_revision",
]
