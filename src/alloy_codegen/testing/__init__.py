"""Test-side helpers reusable across alloy-codegen test
modules.  Added by ``add-codegen-yaml-parity-gate`` (Phase 0.3
of the alloy-data-extractor roadmap).
"""

from alloy_codegen.testing.ir_diff import IRDiffEntry, ir_diff

__all__ = ["IRDiffEntry", "ir_diff"]
