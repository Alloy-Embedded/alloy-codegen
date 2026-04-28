"""Vendor adapter registry — emptied by
``consume-alloy-devices-yml-as-canonical-input``.

The original module side-effect-registered one ``VendorAdapter``
per family so ``stages.fetch`` / ``stages.normalize`` could look
up family-specific source-parsing entry points.  Every admitted
device's IR now comes from the ``alloy-devices-yml`` data repo,
so no per-family adapter code lives here anymore — the registry
is permanently empty.

The public surface (``VendorAdapter`` / ``register_vendor_adapter``
/ ``resolve_vendor_adapter`` / ``list_registered_adapters``) is
preserved as a no-op compatibility layer:
``resolve_vendor_adapter`` always raises with an actionable
message pointing the contributor at the data repo, and
``register_vendor_adapter`` is a no-op decorator so any
out-of-tree caller fails loudly the moment it tries to dispatch.
"""

from __future__ import annotations

from collections.abc import Callable
from dataclasses import dataclass
from typing import Protocol

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.scope import PipelineScope


class _FetchFn(Protocol):
    def __call__(
        self,
        execution_context: ExecutionContext,
        scope: PipelineScope,
    ) -> tuple[dict[str, str], ...]: ...


class _NormalizeFn(Protocol):
    def __call__(
        self,
        *,
        execution_context: ExecutionContext,
        device_name: str,
        vendor: str,
        family: str,
    ) -> CanonicalDeviceIR: ...


@dataclass(frozen=True, slots=True)
class VendorAdapter:
    """Legacy bundle — no instances are registered after
    ``consume-alloy-devices-yml-as-canonical-input``."""

    vendor: str
    family: str
    fetch: _FetchFn
    normalize: _NormalizeFn


def register_vendor_adapter(
    vendor: str, family: str
) -> Callable[[Callable[[], VendorAdapter]], Callable[[], VendorAdapter]]:
    """No-op compat shim.  Vendor adapters were removed when device
    admission moved to the ``alloy-devices-yml`` data repo."""

    def _decorator(builder: Callable[[], VendorAdapter]) -> Callable[[], VendorAdapter]:
        return builder

    return _decorator


def resolve_vendor_adapter(vendor: str, family: str) -> VendorAdapter:
    """Always raises — admission goes through the canonical YAML
    data repo, not this registry."""
    raise StageExecutionError(
        f"vendor adapter registry is empty after "
        f"consume-alloy-devices-yml-as-canonical-input "
        f"(asked for vendor={vendor!r}, family={family!r}).  "
        "Admit the device by committing its YAML to the "
        "alloy-devices-yml data repo; this codegen repo no longer "
        "parses raw vendor sources."
    )


def list_registered_adapters() -> tuple[tuple[str, str], ...]:
    """Always returns the empty tuple — kept for test/diagnostic
    callers that snapshot the registry."""
    return ()
