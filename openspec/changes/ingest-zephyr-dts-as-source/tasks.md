# Tasks — ingest-zephyr-dts-as-source

## Phase 1: Adapter scaffolding

- [x] 1.1 Created `src/alloy_codegen/sources/zephyr_dts.py`.
- [x] 1.2 Added `devicetree>=0.0.2` to `pyproject.toml`
      `[project.dependencies]` (ships `dtlib` for low-level DTS
      parsing).  ``edtlib`` is also available for binding-aware
      passes in follow-up changes.
- [x] 1.3 Vendor adapter registers via
      `@register_vendor_adapter("nordic", "nrf52")` in
      `src/alloy_codegen/vendors/_register_nordic_nrf52.py`.

## Phase 2: Resolve DTS into IR objects

- [x] 2.1 `parse_zephyr_device_document(...)` resolves a `.dts`
      file via `devicetree.dtlib.DT(...)` and walks every node.
- [x] 2.2 Peripheral instances extracted from compatible-matching
      nodes via the per-vendor `COMPATIBLE_MAPS["nordic"]` table
      (`nordic,nrf-uart` → `uart`, etc.).
- [x] 2.3 IRQ numbers extracted from `interrupts` properties as
      `(line, priority)` pairs; one `RawInterrupt` per peripheral.
- [x] 2.4 Clock parents — **deferred to a follow-up
      `extend-zephyr-dts-coverage` change**.  The proposal calls
      clocks out as best-effort and Zephyr clock-controller graphs
      are vendor-specific and partial.
- [x] 2.5 DMA channels — **deferred** for the same reason.
- [x] 2.6 Pinctrl groups — **deferred** to follow-up.  The
      pinctrl decoder needs vendor-specific pin-encoding tables
      (Nordic's `NRF_PSEL` macros differ from STM32's AF tuples).

Memory regions (bonus over the proposal): the adapter recognises
`mmio-sram`, `soc-nv-flash`, `zephyr,memory-region`, and any node
named `*memory*`/`*flash*` and projects them as
`ZephyrDtsMemoryRegion` for downstream use.

## Phase 3: ExecutionContext integration

- [x] 3.1 `zephyr-dts` source override resolved through the
      generic `ALLOY_CODEGEN_SOURCE_<ID>_ROOT` env-var mechanism
      (no special-casing in `context.py`).  The adapter
      explicitly refuses to clone the multi-hundred-MB Zephyr
      repo on demand — caller must point the override at a
      checkout.
- [x] 3.2 `stages/fetch.py` and `stages/normalize.py` resolve the
      adapter via the central registry (no hard-coded
      `if vendor == "nordic"` branches).

## Phase 4: Tests + fixture

- [x] 4.1 Snapshotted minimal Nordic DTS at
      `tests/fixtures/zephyr-dts/nordic/nrf52840.dts` carrying
      UART / SPI / I2C (TWI) / TIMER / RTC / GPIO / WDT / clock.
- [x] 4.2 Pipeline test
      (`test_normalize_nrf52840_produces_canonical_ir`) asserts
      identity, memories, peripherals (with family-catalog
      `ip_version` attribution), IRQs, and per-peripheral
      filtering.
- [x] 4.3 Negative test
      (`test_unsupported_compatible_strings_are_skipped_not_raised`)
      verifies an unmapped Renesas-style compatible is silently
      skipped and recorded in
      `ZephyrDeviceDocument.skipped_compatibles`.
- [x] 4.4 `pytest -q` + `ruff check` clean (all 514 tests pass
      after Nordic admission, including the
      `affected_families.py` ISA classifier — extended to
      include Cortex-M4F for nordic/nrf52 — and the
      devices-README golden, regenerated in the same commit).

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/vendor-admission/spec.md`.
- [x] 5.2 `openspec validate ingest-zephyr-dts-as-source --strict`
      passes.
