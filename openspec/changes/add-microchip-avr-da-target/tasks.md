## Phase 0: Bootstrap & Source Adapter

- [ ] 0.1 Add `("microchip", "avr-da")` to `DEVICE_REGISTRY` and `PACK_CONFIGS`
- [ ] 0.2 Refactor `microchip_dfp.py` to parse all address spaces and carry them through
      `MemoryPatch`
- [ ] 0.3 Normalize upstream `address_space="base"` to `None`
- [ ] 0.4 Add fetch/bootstrap path for `microchip/avr-da`
- [ ] 0.5 Scaffold `patches/microchip/avr-da/family.json` and
      `patches/microchip/avr-da/devices/avr128da32.json`
- [ ] 0.6 Verify fetch produces a non-empty raw document for `avr128da32`

## Phase 1: IR Schema — Harvard Address Space

- [ ] 1.1 Add `address_space: str | None` to `MemoryRegion`
- [ ] 1.2 Thread `address_space` through normalization
- [ ] 1.3 Add `kind="eeprom"` and ensure EEPROM has no startup roles
- [ ] 1.4 Bump `IR_SCHEMA_VERSION` to `1.2.0`
- [ ] 1.5 Regenerate normalized fixtures so unified-space devices keep the field omitted
- [ ] 1.6 Update schema-version assertions in tests

## Phase 2: IR Ingestion — AVR128DA32

- [ ] 2.1 Add explicit `avr8` system-vector baseline
- [ ] 2.2 Ensure unknown cores fail explicitly instead of defaulting to ARM
- [ ] 2.3 Add AVR-DA peripheral aliases:
      `twi -> i2c`, `usart -> uart`, `tca/tcb/tcd -> timer`
- [ ] 2.4 Extend `_typed_register_ref` for `CLKCTRL`
- [ ] 2.5 Populate `family.json` with memory, clocks, packages, DMAC
- [ ] 2.6 Populate `avr128da32.json` with enable/reset/interrupt enrichments
- [ ] 2.7 Add normalized golden fixture and regression tests

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
