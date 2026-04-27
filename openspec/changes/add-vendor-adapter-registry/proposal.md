# Add Vendor Adapter Registry

## Why

Adding a new vendor or family today requires editing hard-coded
``if vendor == ...`` cascades in `stages/normalize.py:3207` and
`stages/fetch.py`.  This scales O(vendors) and turns the pipeline
modules into churn magnets — every new family touches the same
files, creating merge-conflict pressure and review fatigue.

Replacing the cascade with a tiny registry/decorator pattern lets
new families register themselves without editing pipeline code.
Pure dependency injection — no logic change, just where the
dispatch table lives.

## What Changes

- New module `alloy_codegen.vendors.registry` exposing
  `register_vendor_adapter(vendor, family)` (decorator) and
  `resolve_vendor_adapter(vendor, family)` (lookup).
- Each existing vendor adapter (`sources/cmsis_svd.py`,
  `sources/microchip_dfp.py`, …) registers itself via the
  decorator at import time.
- `stages/normalize.py` replaces the hard-coded cascade with one
  registry lookup call per device.
- `stages/fetch.py` likewise migrates to registry lookup.
- Unknown `(vendor, family)` raises a `StageExecutionError` with
  a list of registered adapters in the message — discoverable
  failure mode.
- Existing adapters keep their public function signatures; this
  is a pure refactor with zero behaviour change.

## Impact

Admitting a new family stops requiring edits to pipeline modules.
Reviewers stop seeing 6-way `if-elif` cascades grow.  Foundation
for the Sprint 2 ``ingest-zephyr-dts-as-source`` change — Zephyr
DTS adapter just registers itself, no `normalize.py` patch.
