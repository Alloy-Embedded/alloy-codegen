"""Codegen emitters that consume the v2.1 IR.

Public surface (post adopt-canonical-device-v2-1 + Phase 4 main):

* :func:`emit_linker_script` — GNU LD script (memory map + stack
  symbols + Harvard / XIP annotations).
* :func:`emit_vector_table` — C source with the ISR vector array
  (or a runtime-router stub for matrix-style chips).
* :func:`emit_peripheral_traits` — C++ header with per-instance
  ``constexpr`` traits + per-template register/field maps.
* :func:`emit_runtime_init` — C source with the synthesised
  ``RouteOperation`` table + clock-profile dispatch shells.
* :func:`emit_pin_router` — C++ header with typed pin id +
  signal→pad route table.
"""

from __future__ import annotations

from alloy_codegen.emit_v2_1.linker_script import emit_linker_script
from alloy_codegen.emit_v2_1.peripheral_traits import emit_peripheral_traits
from alloy_codegen.emit_v2_1.pin_router import emit_pin_router
from alloy_codegen.emit_v2_1.runtime_init import emit_runtime_init
from alloy_codegen.emit_v2_1.system_init import emit_system_init
from alloy_codegen.emit_v2_1.vector_table import emit_vector_table

__all__ = [
    "emit_linker_script",
    "emit_peripheral_traits",
    "emit_pin_router",
    "emit_runtime_init",
    "emit_system_init",
    "emit_vector_table",
]
