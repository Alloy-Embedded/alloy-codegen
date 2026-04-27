## ADDED Requirements

### Requirement: The pipeline SHALL ingest Zephyr DTS as a vendor source adapter

The pipeline SHALL ship `src/alloy_codegen/sources/zephyr_dts.py`,
a vendor source adapter that consumes a Zephyr checkout and
produces the same intermediate objects (peripherals, interrupts,
clocks, dma_requests, pins, signals, connection_candidates) that
existing adapters emit.  The adapter SHALL use Zephyr's own
`edtlib` to fully resolve `.dts` + `.dtsi` overlays rather than
parsing DTS by hand.  The adapter SHALL register itself through
the central vendor-adapter registry, not through a hard-coded
`if vendor == ...` branch in pipeline modules.

#### Scenario: nRF52 device admitted via Zephyr DTS produces a valid canonical IR

- **WHEN** the pipeline runs for a Nordic nRF52 device whose
  fixture points at a snapshotted Zephyr DTS tree
- **THEN** the adapter SHALL produce a canonical IR with
  peripheral instances, IRQ numbers, clock parents (best-effort),
  and pinctrl-derived connection candidates
- **AND** the IR SHALL pass the standard validation stage without
  vendor-specific exceptions

#### Scenario: Unsupported compatible strings do not crash the adapter

- **WHEN** the adapter encounters a DTS node whose `compatible`
  string is not in its vendor mapping table
- **THEN** the adapter SHALL log the skip and continue
- **AND** it SHALL NOT raise — DTS is intentionally permissive
  about new compatibles

#### Scenario: Adapter registers through the vendor registry

- **WHEN** the adapter module is imported
- **THEN** it SHALL register itself via
  `@register_vendor_adapter(vendor, family)` for each Zephyr
  family it covers
- **AND** the pipeline's normalize/fetch stages SHALL resolve the
  adapter through `resolve_vendor_adapter(...)` rather than a
  hard-coded branch
