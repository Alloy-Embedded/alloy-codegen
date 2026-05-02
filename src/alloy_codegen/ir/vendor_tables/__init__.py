"""Vendor-specific lookup tables consumed by the RCC synthesiser.

Each module here exports a *pure-data* mapping that
:mod:`alloy_codegen.ir.synthesised.builder` consumes to cross-link
clock-gate / reset / kernel-clock-mux template fields to canonical
peripheral IDs.  The data lives separately from the builder so that
adding a new chip family doesn't require touching the synthesiser
itself.
"""
