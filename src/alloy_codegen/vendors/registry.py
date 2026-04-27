"""Central vendor adapter registry (add-vendor-adapter-registry).

Replaces the hard-coded ``if vendor == ...`` cascades in
``stages/normalize.py`` and ``stages/fetch.py`` with a tiny
decorator + lookup table.  Each adapter registers itself at import
time using ``@register_vendor_adapter(vendor, family)``; pipeline
stages call ``resolve_vendor_adapter(vendor, family)`` to look up
the right ``VendorAdapter`` instance.

Adding a new family is then a single-file change (drop a new
``vendors/_register_<name>.py`` plus the adapter sources) — no
edits to pipeline modules.
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
    """Bundles the per-family fetch + normalize entry points so the
    pipeline can resolve them in a single registry lookup."""

    vendor: str
    family: str
    fetch: _FetchFn
    normalize: _NormalizeFn


_REGISTRY: dict[tuple[str, str], VendorAdapter] = {}


def register_vendor_adapter(
    vendor: str, family: str
) -> Callable[[Callable[[], VendorAdapter]], Callable[[], VendorAdapter]]:
    """Decorator returning the input unchanged after stashing the
    paired ``VendorAdapter`` instance in the global registry.

    The decorator targets a builder factory — a no-argument callable
    that returns a ``VendorAdapter``.  Registering at the factory
    level (vs. on each fetch/normalize pair) keeps the decorated
    object small and avoids reorder-sensitive partials.
    """

    def _decorator(builder: Callable[[], VendorAdapter]) -> Callable[[], VendorAdapter]:
        adapter = builder()
        key = (vendor, family)
        if key in _REGISTRY and _REGISTRY[key] is not adapter:
            raise RuntimeError(
                f"vendor adapter already registered for ({vendor!r}, {family!r}); "
                f"refusing silent override."
            )
        _REGISTRY[key] = adapter
        return builder

    return _decorator


def resolve_vendor_adapter(vendor: str, family: str) -> VendorAdapter:
    """Look up the adapter for ``(vendor, family)``.

    Raises ``StageExecutionError`` with the discoverable list of
    registered adapters on a miss — surfaced so a developer adding
    a family-without-adapter sees the available set.
    """
    key = (vendor, family)
    adapter = _REGISTRY.get(key)
    if adapter is None:
        registered = ", ".join(f"({v!r}, {f!r})" for v, f in sorted(_REGISTRY))
        raise StageExecutionError(
            f"no vendor adapter registered for ({vendor!r}, {family!r}); "
            f"registered adapters: [{registered}]"
        )
    return adapter


def list_registered_adapters() -> tuple[tuple[str, str], ...]:
    """Return a stable-sorted snapshot of registered ``(vendor, family)``
    keys.  Useful for tests + diagnostic logging."""
    return tuple(sorted(_REGISTRY))
