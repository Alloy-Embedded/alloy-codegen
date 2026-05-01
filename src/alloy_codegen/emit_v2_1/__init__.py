"""Codegen emitters that consume the v2.1 IR.

This package will grow as Phase 4 rewrites land.  Today (post-Phase
3) it ships one proof-of-life emitter: :func:`emit_linker_script`,
which produces a GNU LD script from a :class:`CanonicalDevice`.
"""

from __future__ import annotations

from alloy_codegen.emit_v2_1.linker_script import emit_linker_script
from alloy_codegen.emit_v2_1.vector_table import emit_vector_table

__all__ = ["emit_linker_script", "emit_vector_table"]
