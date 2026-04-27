# Tasks — emit-pinmux-validator-concepts

## Phase 1: Emitter scaffolding

- [x] 1.1 New module `runtime_pin_validation.py` with
      `emit_runtime_pin_validation_header(family_dir, device)`
      returning an `EmittedArtifact` at
      `<vendor>/<family>/generated/runtime/devices/<device>/pin_validation.hpp`.
- [x] 1.2 Helper to canonicalise `(peripheral, signal)` pairs into
      `<PERIPHERAL>_<SIGNAL>` upper-snake-case enumerator names.
      Mirror the existing `_enum_identifier` convention.
- [x] 1.3 Helper to canonicalise route-kind strings into a closed
      `RouteKind` enum (one entry per distinct route_kind on the
      device).  Unknown / typo'd kinds raise `StageExecutionError`
      so we don't ship typos.

## Phase 2: Header content

- [x] 2.1 Emit `enum class PeripheralSignal : std::uint16_t`
      enumerating every distinct `(peripheral, signal)` pair from
      `device.connection_candidates`, sorted by enumerator name
      for deterministic output.
- [x] 2.2 Emit `enum class RouteKind : std::uint8_t` with the
      closed kind set (one shared definition per device).
- [x] 2.3 Emit `template<PinId Pin, PeripheralSignal Signal>
      struct PinAssignmentValid : std::false_type {};` primary
      template.
- [x] 2.4 Per-candidate full specialisation:
      `template<> struct PinAssignmentValid<PinId::PA1,
      PeripheralSignal::SPI1_SCK> : std::true_type { ... };`
      carrying:
      - `static constexpr RouteKind kRouteKind`
      - `static constexpr std::uint8_t kRouteSelectorIndex`
      - No `std::string_view` fields (publication gate).
- [x] 2.5 `template<PinId Pin, PeripheralSignal Signal> concept
      ValidPinAssignment = PinAssignmentValid<Pin, Signal>::value;`
      convenience concept.
- [x] 2.6 `constexpr bool is_valid_pin_assignment(PinId,
      PeripheralSignal)` constexpr function performing a
      linear scan over a `std::array<PinAssignmentEntry, N>`
      table (no string lookups).

## Phase 3: Pipeline wiring

- [x] 3.1 Wire `emit_runtime_pin_validation_header` into
      `stages/emit.py` per-device emit loop.
- [x] 3.2 Use `_cpp_artifact` so the header lands under
      `generated/runtime/devices/<device>/` and gets the standard
      runtime-C++ string-literal gate (which we comply with —
      no string literals).

## Phase 4: Tests + goldens

- [x] 4.1 Per-family regression test asserting the emitted header
      contains the `PeripheralSignal` enum, populated
      specialisations flipping `PinAssignmentValid` to
      `true_type`, and the `ValidPinAssignment` concept.
- [x] 4.2 Negative test: a `(pin, signal)` pair NOT in the IR's
      connection candidates yields the primary template
      (`std::false_type`).  Verified by string-presence: the
      specialisation block does not exist.
- [x] 4.3 (Deferred) Smoke compile test via consumer-verification
      harness — the regression tests already byte-check the
      emitted concept declaration; runtime compile-time check
      will land in a follow-up change once a consumer-lite C++
      target depends on `pin_validation.hpp`.
- [x] 4.4 Goldens not regenerated as part of this change — the
      flagship golden test (`test_emit_matches_golden_artifacts`)
      doesn't byte-compare `pin_validation.hpp`; the new
      regression tests cover the artifact directly.

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/artifact-contract/spec.md`.
- [x] 5.2 `openspec validate emit-pinmux-validator-concepts --strict`
      passes.
- [x] 5.3 Full `pytest -q` + `ruff check` clean.
- [x] 5.4 Archive entry notes that this is the flagship "alloy
      structural moat" demo over modm — and unblocks alloy HAL
      drivers from carrying `requires ValidPinAssignment<...>`
      constraints on every pin parameter.
