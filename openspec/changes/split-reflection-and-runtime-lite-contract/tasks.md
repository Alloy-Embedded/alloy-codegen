## 1. OpenSpec

- [x] 1.1 Add `runtime-lite-contract` deltas defining the new generated contract split
- [x] 1.2 Add artifact-boundary deltas stating that reflection and runtime-lite are distinct
- [x] 1.3 Add validation deltas that fail foundational publication when runtime-lite is missing

## 2. Artifact Split

- [x] 2.1 Define the runtime-lite generated header layout
- [x] 2.2 Reclassify current family-wide tables as reflection artifacts
- [x] 2.3 Keep metadata/report outputs unchanged unless needed for the split

## 3. Runtime-Lite Emission

- [x] 3.1 Emit per-device runtime-lite peripheral instance traits
- [x] 3.2 Emit per-device runtime-lite register and field refs suitable for direct use
- [x] 3.3 Emit runtime-lite clock/reset bindings for runtime-owned peripherals
- [x] 3.4 Emit runtime-lite route specializations or operation packs for foundational connector
      paths
- [x] 3.5 Emit runtime-lite pin and connector aliases that do not require reflection-table
      lookup at runtime

## 4. Validation And Gates

- [x] 4.1 Add validation proving foundational families provide runtime-lite coverage for
      GPIO/UART/SPI/I2C bring-up
- [x] 4.2 Add a gate proving runtime-lite artifacts contain no reflection-only payloads
- [x] 4.3 Fail vendor admission when a new family cannot reuse the runtime-lite contract

## 5. Regression Coverage

- [x] 5.1 Add smoke coverage for runtime-lite artifacts separate from reflection smoke
- [x] 5.2 Refresh foundational emitted fixtures
- [x] 5.3 Validate with `python3 -m ruff check src tests`
- [x] 5.4 Validate with `python3 -m pytest tests -q`
- [x] 5.5 Validate with `openspec validate split-reflection-and-runtime-lite-contract --strict`
