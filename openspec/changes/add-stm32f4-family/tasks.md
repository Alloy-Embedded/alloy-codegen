## Phase 5.1: Multi-family registry and scope generalisation

- [x] 5.1.1 Replace `BOOTSTRAP_DEVICE_NAMES` in `bootstrap.py` with `DEVICE_REGISTRY` dict keyed
      by `(vendor, family)` and add `registered_device_names(vendor, family)` +
      `resolve_device_family(device_name)` helpers; keep `bootstrap_device_names()` as a
      compatibility shim over the registry
- [x] 5.1.2 Update `scope.py` `validate_supported()` to look up `DEVICE_REGISTRY` and auto-resolve
      `vendor`/`family` from device name via `resolve_device_family()`
- [x] 5.1.3 Update `scope.py` `resolved_device_names()` to call `registered_device_names(vendor,
      family)` when no device is pinned
- [x] 5.1.4 Update `patches.py` `family_patch_file_path()` and `patch_file_path()` to accept
      `vendor: str` and `family: str` keyword parameters and remove the module-level constant
      dependency for path construction
- [x] 5.1.5 Update `patches.py` `load_family_patch_catalog()` and `load_device_patch()` to
      accept and forward `vendor`/`family` to the path helpers
- [x] 5.1.6 Update `normalize.py` `run()` to pass `scope.resolved_vendor()` /
      `scope.resolved_family()` through to `load_device_patch()` and provenance strings
- [x] 5.1.7 Update `emit.py` to derive `family_dir` from `scope.resolved_vendor()` /
      `scope.resolved_family()` rather than hardcoded constants (already uses scope for path,
      verify no residual constant usage)
- [x] 5.1.8 Update `sources/cmsis_svd.py` `fetch_records()` to derive the vendor subtree path
      dynamically from the scope (STMicro subtree constant remains; vendor routing added later
      if a non-ST vendor appears)

## Phase 5.2: STM32F4 patch data

- [x] 5.2.1 Create `patches/st/stm32f4/family.json` with peripherals, packages (LQFP64), pins,
      and DMA catalog entries common to F4 devices
- [x] 5.2.2 Create `patches/st/stm32f4/devices/stm32f401re.json` device overlay
- [x] 5.2.3 Create `patches/st/stm32f4/devices/stm32f405rg.json` device overlay

## Phase 5.3: Source fixtures for F4 devices

- [x] 5.3.1 Add minimal SVD fixture `tests/fixtures/svd/STM32F401.svd` (subset: key peripherals,
      base addresses, interrupts)
- [x] 5.3.2 Add minimal SVD fixture `tests/fixtures/svd/STM32F405.svd`
- [x] 5.3.3 Add MCU XML fixture `tests/fixtures/stm32-open-pin-data/mcu/STM32F401R(B-C-D-E)Tx.xml`
- [x] 5.3.4 Add MCU XML fixture `tests/fixtures/stm32-open-pin-data/mcu/STM32F405R(B-C-D)Tx.xml`
- [x] 5.3.5 Add GPIO modes XML fixtures for F4 if the source adapter requires them

## Phase 5.4: Canonical fixtures and golden tests

- [x] 5.4.1 Generate and commit `tests/fixtures/stm32f4/stm32f401re.canonical.json`
- [x] 5.4.2 Generate and commit `tests/fixtures/stm32f4/stm32f405rg.canonical.json`
- [x] 5.4.3 Extend `test_normalize.py` parametric test to cover F4 device names
- [x] 5.4.4 Extend `test_emit.py` golden test to cover F4 emitted artifacts
- [x] 5.4.5 Extend `test_validation.py` to run the validation stage against F4 devices
- [x] 5.4.6 Add cross-family regression guard: assert G0 canonical fixtures are unchanged after
      adding F4 support

## Phase 5.5: Gate checks

- [x] 5.5.1 Confirm tasks 5.1–5.4 pass CI with `make test` green
- [x] 5.5.2 Mark Gate E.6 complete in `add-codegen-platform-foundation/tasks.md`
- [x] 5.5.3 Mark tasks 5.1–5.4 in `add-codegen-platform-foundation/tasks.md` complete
