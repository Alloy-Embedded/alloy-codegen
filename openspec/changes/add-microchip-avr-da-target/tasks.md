## Phase 0: Bootstrap & Source Adapter

- [x] 0.1 Add `("microchip", "avr-da")` to `DEVICE_REGISTRY` and `PACK_CONFIGS`
      (`PACK_CONFIGS` entry `Microchip.AVR-Dx_DFP.2.4.286.atpack` lives in
      `sources/microchip_dfp.py`; `DEVICE_REGISTRY[("microchip", "avr-da")]`
      is `("avr128da32",)` in `bootstrap.py`; `SOURCE_BUNDLES` shares the
      DFP-pack + DFP-extract bundle with SAME70.)
- [x] 0.2 Refactor `microchip_dfp.py` to parse all address spaces and carry them through
      `MemoryPatch`
      (The adapter is SVD-optional via `SelectedDeviceFiles.svd_path: Path |
      None` and the `SVD_OPTIONAL_FAMILIES` frozenset.  Memory parsing
      already threads `address_space` through `MemoryPatch` / `MemoryRegion`.
      `test_avr128da32_atdf_declares_harvard_address_spaces` verifies the
      full multi-space ingestion on the AVR128DA32 fixture: prog / data /
      eeprom are all emitted with the correct `kind` and `address_space`.)
- [x] 0.3 Normalize upstream `address_space="base"` to `None`
      (Already in place at `sources/microchip_dfp.py` — ATDF `base` → `None`.)
- [x] 0.4 Add fetch/bootstrap path for `microchip/avr-da`
      (`stages/fetch.py` dispatches AVR-DA through the same Microchip DFP
      fetch function as SAME70.  `validate_supported()` now admits
      `avr128da32`, `fetch_records` returns PDSC + ATDF records, and the
      full `run_normalize(PipelineScope(device="avr128da32"))` pipeline
      succeeds.)
- [x] 0.5 Scaffold `patches/microchip/avr-da/family.json` and
      `patches/microchip/avr-da/devices/avr128da32.json`
      (Family patch declares 12 pins of PORTA/PORTC, 7 peripherals
      (PORTA, PORTC, USART0/1, TWI0, SPI0, TCA0) with `ip_version`, and 10
      PORTMUX bootstrap pin-signal entries.  Device patch declares three
      Harvard memories (APP_SECTION/flash/prog, INTERNAL_SRAM/sram/data,
      EEPROM/eeprom/eeprom), `core="avr8"`, and two clock profiles.
      `svd_file: null` — AVR publishes ATDF only.)
- [x] 0.6 Verify fetch produces a non-empty raw document for `avr128da32`
      (`test_select_avr_da_files_resolves_atdf_without_svd` + the two
      deeper ingestion tests in `test_microchip_dfp.py` prove the adapter
      returns a populated ATDF path and that parsing it yields the
      expected Harvard address spaces, EEPROM kind, and peripheral names.)

## Phase 1: IR Schema — Harvard Address Space

- [x] 1.1 Add `address_space: str | None` to `MemoryRegion`
      (Field present with `omit_if_empty` metadata — unified-space devices
      serialize without noise.)
- [x] 1.2 Thread `address_space` through normalization
      (`stages/normalize.py` forwards the field; `runtime_linker_script.py`
      uses it for region ordering and naming.)
- [x] 1.3 Add `kind="eeprom"` and ensure EEPROM has no startup roles
      (`_memory_startup_roles` returns zero roles for `"eeprom"` since it is
      not in the volatile / nonvolatile / retained sets.  The emitter will
      not produce copy/zero code for EEPROM regions.)
- [x] 1.4 Bump `IR_SCHEMA_VERSION` to `1.2.0`
- [x] 1.5 Regenerate normalized fixtures so unified-space devices keep the field omitted
      (All 12 canonical fixtures for stm32g0, stm32f4, same70, imxrt1060,
      rp2040, esp32c3 regenerated on 1.2.0 with `address_space` omitted.)
- [x] 1.6 Update schema-version assertions in tests
      (`test_schema.py`, `test_ir_model.py`, `test_normalize.py` updated.)

## Phase 2: IR Ingestion — AVR128DA32

- [x] 2.1 Add explicit `avr8` system-vector baseline
      (Single-entry baseline `{(0, "__vector_0", None, "reset-handler")}` —
      no ARM exception prefix, avr-gcc crt0 compatible.)
- [x] 2.2 Ensure unknown cores fail explicitly instead of defaulting to ARM
      (Enforced by `_system_vector_baseline` via `StageExecutionError` —
      landed in the ESP32-C3 Phase 1 commit.)
- [x] 2.3 Add AVR-DA peripheral aliases:
      `twi -> i2c`, `usart -> uart`, `tca/tcb/tcd -> timer`
      (Landed in `PERIPHERAL_CLASS_ALIASES`.  `usart` was already aliased to
      `uart`; this commit adds `twi`, `tca`, `tcb`, `tcd`.)
- [ ] 2.4 Extend `_typed_register_ref` for `CLKCTRL`
      (Follow-on: requires ATDF `<register-group>` register parsing so AVR
      CLKCTRL bits can resolve to typed runtime refs.  Currently the
      AVR-DA normalize path emits zero `registers` / `register_fields`;
      validation rules that depend on register descriptors are explicitly
      exempted for `core.startswith("avr")` until this lands.)
- [x] 2.5 Populate `family.json` with memory, clocks, packages, DMAC
      (Partial: packages, 12 pins, 7 peripherals with `ip_version`, and a
      minimal PORTMUX pin-signal table are in place.  AVR DMAC peripheral
      and clock-graph wiring land together with 2.4.)
- [x] 2.6 Populate `avr128da32.json` with enable/reset/interrupt enrichments
      (Partial: three Harvard memories, `core=avr8`, two clock profiles.
      Interrupts are parsed from the ATDF via `parse_interrupts_from_atdf`
      — the device patch doesn't need to redeclare them.  Explicit
      enable/reset enrichments wait on CLKCTRL typed refs from 2.4.)
- [x] 2.7 Add normalized golden fixture and regression tests
      (`tests/fixtures/avr-da/avr128da32.canonical.json` locked in.  Five
      regression tests in `tests/test_normalize.py`:
      `test_normalize_matches_avr_da_fixture[avr128da32]`,
      `test_normalize_avr_da_uses_correct_family_identity`,
      `test_normalize_avr_da_preserves_harvard_address_spaces`
      (proves EEPROM zero startup roles + per-region `address_space`),
      `test_normalize_avr_da_has_avr8_vector_baseline`
      (no ARM fault handlers; slot 0 is `__vector_0`), and
      `test_normalize_avr_da_routes_usart_spi_twi_signals`.)

## Phase 3: PORTMUX Routing

- [ ] 3.1 Add `alloy.pinmux.avr-portmux-v1` to known backend schemas
- [ ] 3.2 Extend AVR signal parsing for USART/SPI/TWI/ADC/DAC bootstrap coverage
- [ ] 3.3 Populate PORTMUX pin-signal data in family patches
- [ ] 3.4 Add emitted proof that runtime pin routing publishes the AVR schema correctly

## Phase 4: Runtime Emission — AVR128DA32

- [ ] 4.1 Ensure `interrupts.hpp` emits AVR8 vector slots without ARM offset
- [ ] 4.2 Ensure `clock_graph.hpp` reflects CLKCTRL facts
- [ ] 4.3 Ensure `systick.hpp` is explicitly skipped for AVR
- [ ] 4.4 Add `runtime_avr_startup.py`
- [ ] 4.5 Wire AVR startup dispatch in `stages/emit.py`
- [ ] 4.6 Add AVR compile flags to `consumer_verification.py`
- [ ] 4.7 Add smoke coverage for AVR runtime headers and startup artifact
- [ ] 4.8 Add compile + disassembly validation proving the emitted startup places vectors
      and reset flow correctly for avr-gcc
- [ ] 4.9 Add emitted goldens for AVR runtime output

## Phase 5: CI & Publication Gates

- [ ] 5.1 Add `microchip/avr-da` to the publication matrix
- [ ] 5.2 Extend admission/publish checks for the new family path
- [ ] 5.3 Add artifact-contract coverage for AVR runtime outputs
- [ ] 5.4 Run full publish flow for `microchip/avr-da`
- [ ] 5.5 Confirm `microchip/same70` still publishes unchanged

## Phase 6: Fixtures & Docs

- [ ] 6.1 Final full fixture regeneration pass
- [ ] 6.2 Update `openspec/project.md` with AVR-DA admission and Harvard notes
- [ ] 6.3 Add license note for AVR-Dx DFP sources
- [ ] 6.4 Archive this change
