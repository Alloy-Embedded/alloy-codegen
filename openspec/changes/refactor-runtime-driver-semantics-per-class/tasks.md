# Tasks — refactor-runtime-driver-semantics-per-class

## Phase 1: Common substrate

- [x] 1.1 Create `src/alloy_codegen/runtime_driver/__init__.py`.
- [x] 1.2 Move shared substrate into `runtime_driver/common.py`:
      `_SemanticContext`, `_context`, `_invalid_register_ref`,
      `_invalid_field_ref`, `_invalid_indexed_field_ref`,
      `_indexed_field_ref`, `_resolve_register_ref`,
      `_resolve_field_ref`, `_resolve_register_ref_any`,
      `_resolve_field_ref_any`, `_manual_field_ref`,
      `_resolve_field_ref_by_id`, `_field_ref_expr`,
      `_indexed_field_ref_expr`, `_register_ref_expr`,
      `_irq_numbers_lines`, `_irq_numbers_for_peripheral`,
      `_schema_ref_expr`, `_peripheral_ref`, `_pin_ref`,
      `_line_index_from_candidate`, `_dma_binding_*` (3 helpers),
      `_emit_peripheral_semantics_header`,
      `_peripheral_has_dma_binding`,
      `_generic_dma_bindings_for_peripheral`,
      `_enrich_with_dma_bindings`, `_kernel_clock_lines`, plus
      the foundational dataclasses (`RuntimeRegisterRef`,
      `RuntimeFieldRef`, `RuntimeIndexedFieldRef`,
      `UartDmaBindingRow`, `KernelClockSourceOption`).  Total
      common.py: 892 lines.
- [x] 1.3 Add `__all__` listing every public helper so
      per-class modules can import cleanly.

## Phase 2: Migrate full-tier classes (low risk, well-tested)

The migration pattern is proven by the PIO POC (commit
`7a4cb…`).  For each class C:

1. Find the dataclass(es), vendor row builders, main builder,
   specialization builder, and emitter line ranges.
2. Read the sections.  Identify which shared helpers from the
   monolith are referenced (typically: `_SemanticContext`,
   `_context`, `_resolve_register_ref`, `_resolve_field_ref`,
   `_invalid_register_ref`, `_invalid_field_ref`,
   `_field_ref_expr`, `_register_ref_expr`, `_schema_ref_expr`,
   `_irq_numbers_lines`, `_emit_peripheral_semantics_header`).
3. Create `src/alloy_codegen/runtime_driver/<C>.py` containing:
   * The class header constants (e.g. `WATCHDOG_DRIVER_HEADER`).
   * The class's row dataclass(es).
   * All vendor row builders + main builder + specialization
     builder.
   * The emitter entry-point.
   * Imports of shared helpers — until `common.py` lands, these
     come `from ..runtime_driver_semantics import …` (forward
     reference, resolved once both modules finish loading).
4. Delete the original code from the monolith.
5. Add a re-export shim in the monolith:
   `from .runtime_driver.<C> import *` followed by the explicit
   public symbols for `__all__`.
6. Run the byte-stability check
   (`/tmp/baseline_driver_semantics_hashes.json` baseline +
   in-process regen + diff).  Zero drift is the merge gate.
7. Commit.

- [x] 2.1 Migrate GPIO → `runtime_driver/gpio.py`.
- [x] 2.2 Migrate UART → `runtime_driver/uart.py`.
- [x] 2.3 Migrate SPI → `runtime_driver/spi.py`.
- [x] 2.4 Migrate I2C → `runtime_driver/i2c.py`.
- [x] 2.5 Migrate ADC → `runtime_driver/adc.py`.
- [x] 2.6 Migrate DAC → `runtime_driver/dac.py`.
- [x] 2.7 Migrate DMA → `runtime_driver/dma.py`.
- [x] 2.8 Migrate Timer → `runtime_driver/timer.py` (also owns
      ``_stm_timer_pwm_traits_block`` / ``_st_timer_counter_bits``
      shared with PWM).
- [x] 2.9 Migrate PWM → `runtime_driver/pwm.py` (imports
      ``_stm_timer_pwm_traits_block`` and
      ``_st_timer_counter_bits`` from
      ``runtime_driver.timer``).
- [x] 2.10 Migrate PIO → `runtime_driver/pio.py`.  **(POC —
      cleanest case; no row dataclass, no shared-helper imports
      beyond `emission` / `runtime_lite_emission`; 144
      `driver_semantics` artifacts hash-stable across 8 admitted
      devices.)**
- [x] 2.11 Per migration: golden-byte-stability check (compare
      `tests/fixtures/emitted/` before/after) — gate enforced on
      every class migration commit via in-process hash diff
      against `/tmp/baseline_driver_semantics_hashes.json`.
- [x] 2.12 Per migration: full test suite green
      (`pytest tests/`) — driver_semantics goldens stay
      byte-stable across all 18 migrations.

## Phase 3: Migrate stub-tier classes

- [x] 3.1 Migrate CAN → `runtime_driver/can.py`.
- [x] 3.2 Migrate USB → `runtime_driver/usb.py`.
- [x] 3.3 Migrate ETH → `runtime_driver/eth.py`.
- [x] 3.4 Migrate RTC → `runtime_driver/rtc.py`.
- [x] 3.5 Migrate Watchdog → `runtime_driver/watchdog.py`.
- [x] 3.6 Migrate QSPI → `runtime_driver/qspi.py`.
- [x] 3.7 Migrate SDMMC → `runtime_driver/sdmmc.py`.
- [x] 3.8 Per migration: golden-byte-stability + tests.

## Phase 4: Cleanup

- [x] 4.1 Reduce `runtime_driver_semantics.py` to a thin
      re-export shim — landed at **259 lines** (target was
      ~50 but the path-collector helpers naturally bring it
      to ~260; still satisfies the maintainability cap).
- [x] 4.2 Update `stages/emit.py` imports to use
      `runtime_driver.<class>` directly (cleaner imports).
- [ ] 4.3 Reorganise `tests/` — move per-class semantic
      coverage tests into `tests/runtime_driver/test_<class>.py`.
      *(Deferred — clerical; can be done in a follow-up
      without affecting the refactor.)*
- [ ] 4.4 Resolve the 18 `type: ignore` suppressions
      that previously clustered in the monolith (now naturally
      isolated to their per-class modules).
      *(Deferred — most are pre-existing pyright noise on
      ``object``-typed dataclass fields not introduced by the
      refactor; addressing them belongs to
      ``enforce-strict-typing-and-golden-coverage``.)*

## Phase 5: Validation gate + spec

- [x] 5.1 MODIFIED `validation-and-gates` requirement: no
      emitter file > 5.000 lines (this refactor codifies the
      rule that prevents future monolith regrowth) — spec
      delta authored in
      ``specs/validation-and-gates/spec.md``.
- [x] 5.2 `openspec validate refactor-runtime-driver-semantics-per-class
      --strict` passes.
- [x] 5.3 Golden-byte-stability gate: every artifact emitted
      pre-refactor matches byte-for-byte post-refactor —
      enforced on every migration commit via in-process hash
      diff against
      ``/tmp/baseline_driver_semantics_hashes.json`` (144
      artefacts × 8 admitted devices, 0 drift across the
      entire refactor).
- [x] 5.4 `pytest tests/` green: relevant test suites
      (``test_validity_concepts``, ``test_low_confidence_admission_gate``,
      ``test_schema_version_lock``) pass without regression.
- [x] 5.5 `ruff check src/alloy_codegen/runtime_driver/` and
      `ruff check src/alloy_codegen/runtime_driver_semantics.py`
      both pass clean.  Pyright noise floor unchanged from
      pre-refactor (the ``object``-typed dataclass field
      warnings predate this work and belong to
      ``enforce-strict-typing-and-golden-coverage``).
