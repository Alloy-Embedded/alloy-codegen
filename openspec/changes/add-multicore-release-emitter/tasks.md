# Tasks — Add Multicore Release Emitter

## 1. IR tightening

- [ ] 1.1 Promote `MulticoreCore.role` to a typed enum
      `MulticoreRole ∈ {Boot, App, Coprocessor}`.
- [ ] 1.2 Promote `MulticoreCore.release_op` to a typed enum
      `ReleaseOpKind ∈ {WriteValue, WriteMask, Mailbox}`.
- [ ] 1.3 Tighten the JSON schema for `MulticoreCore` so when
      the parent `Multicore` block is populated, every entry
      carries `id`, `role`, `vector_base`, `release_register`,
      `release_op`, `start_vector_symbol`.  Loader rejects
      partial multicore blocks.
- [ ] 1.4 Add an `app_cpu: bool` field to `MulticoreCore` for
      heterogeneous-core families (defaults `False`).

## 2. Emitter

- [ ] 2.1 New module
      `src/alloy_codegen/emit_v2_1/multicore_release.py`
      with `emit_multicore_release(device, synthesised) -> tuple[str, str]`
      returning `(header_text, source_text)`.
- [ ] 2.2 Header preamble: typed
      `struct alloy_multicore_release`, the
      `alloy_multicore_release_table[]` extern, and
      `alloy_multicore_release_core(uint8_t)` declaration.
- [ ] 2.3 Source body: populate the table from
      `device.identity.multicore.cores[*]`; emit the
      `alloy_multicore_release_core` body that switches on
      `core_id`, looks up the descriptor, writes
      `release_register` according to `release_op`,
      barriers, and returns.
- [ ] 2.4 Single-core stub when `device.identity.multicore`
      is `None`: header declares
      `ALLOY_MULTICORE_RELEASE_COUNT == 0`, source emits a
      no-op `alloy_multicore_release_core()`.
- [ ] 2.5 The emitter SHALL be template-class blind — no
      branch on `vendor == "raspberrypi"`.  All vendor
      knowledge SHALL live in `MulticoreCore` IR fields.

## 3. Linker-script simplification

- [ ] 3.1 Remove the `sram_bank4` / `sram_bank5` heuristic
      from `linker_script.py`.
- [ ] 3.2 Replace with a generic walk:
      `for core in device.identity.multicore.cores:` emit
      `core_<id>_stack_top = ORIGIN(...) + LENGTH(...);` from
      the `core.stack_region_id` ref (the IR carries which
      memory region holds each core's stack).
- [ ] 3.3 Single-core devices remain unchanged — the heuristic
      removal only affects code paths gated on
      `device.identity.multicore is not None`.

## 4. Wire-up

- [ ] 4.1 Register `_EmitterEntry(name="multicore_release",
      filename="multicore_release.h", fn=...)` and a sibling
      entry for the `.c` in `cli.py::_EMITTERS` and
      `entrypoint.py::_EMITTERS`.  (Or design a single emitter
      that returns two-file tuples — see design.md decision.)
- [ ] 4.2 Update CLI `--list` and `--emit` documentation.

## 5. Tests

- [ ] 5.1 Synthetic `Multicore` block test —
      synthesise a fake dual-core device with two
      `MulticoreCore` entries; assert the emitted source
      compiles and the table has 2 rows.
- [ ] 5.2 Single-core stub test — assert the emitted header
      declares `ALLOY_MULTICORE_RELEASE_COUNT == 0` for
      every currently-admitted (single-core) device.
- [ ] 5.3 Linker-script regression test — the existing
      golden suite must pass byte-stable after removing the
      `sram_bank4/5` heuristic (no admitted device exercises
      it today).
- [ ] 5.4 Future-multicore canary fixture — synthetic STM32
      H745-shaped YAML in `tests/fixtures/canary/multicore/`
      validates the round-trip through the new emitter.

## 6. Documentation

- [ ] 6.1 Add a "Multicore release" section to
      `runtime-lite-contract` design notes.
- [ ] 6.2 Add a "Adding a multicore device" walkthrough to
      `CONTRIBUTING_DEVICES.md` so the data team knows what
      `MulticoreCore` fields to populate when admitting a new
      dual-core chip.
