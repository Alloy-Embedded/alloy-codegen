"""Per-class driver-semantics emitter sub-package.

Split from the legacy ``runtime_driver_semantics.py`` monolith
under the ``refactor-runtime-driver-semantics-per-class``
OpenSpec change.  Each peripheral class lives in its own
module here; the legacy ``runtime_driver_semantics.py``
re-exports from this package for backwards compatibility.

Migration contract:

* Each per-class module exposes
  ``emit_runtime_driver_<class>_semantics_header(*, family_dir,
  device) -> EmittedArtifact``.
* Class-specific dataclasses, vendor row-builders, and
  module-level constants live with their class.
* Cross-class shared helpers live in ``runtime_driver/common``
  (currently still in the monolith pending the gradual
  carve-out).
"""

from __future__ import annotations

from .pio import (
    PIO_DRIVER_HEADER,
    emit_runtime_driver_pio_semantics_header,
)

__all__ = [
    "PIO_DRIVER_HEADER",
    "emit_runtime_driver_pio_semantics_header",
]
