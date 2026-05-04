# Tasks — drop-bulk-pipeline-add-connector-emitter

---

## Phase 1 — Remove Bulk Pipeline Artifacts

- [x] 1.1 Delete `tools/bump_devices_yml.py`.
      It bumped the `alloy-devices-yml` submodule pin and detected drift in the
      now-deleted pre-generated alloy-devices C++ artifacts.  Not needed.

- [x] 1.2 Delete `tools/runtime_cpp_smoke.py`.
      Ran clang++ smoke compile over ALL admitted devices — pipeline-scale tool.
      Replaced by the per-device compile test in Phase 5.

- [x] 1.3 Delete `tests/codegen/published_runtime_lite_contract_smoke.cpp`.
      Was the smoke template for the pre-generated alloy-devices artifacts.
      Replaced by a generated-output smoke in Phase 5.

- [x] 1.4 Remove `tests/codegen/` directory (was empty after 1.3).

- [x] 1.5 `tools/__init__.py` is empty; `pyproject.toml` has no `[project.scripts]`
      entries for the deleted tools.  No further changes needed.

---

## Phase 2 — Derive `route_kind` from `backend_schema_id`

`connectors.hpp` needs a `RouteKindId` per route.  The synthesised
`PinRoute.backend_schema_id` already encodes this implicitly.

- [x] 2.1 In `alloy_codegen/ir/synthesised/pin_routes.py`, added property
      (backend_schema_id → `route_kind_*` name via `_MAP`; falls back to
      `"route_kind_unknown"`).  Also fixed `_route_kind_for()` in
      `connector_traits.py` — was matching against wrong constant `"stm32_af"`;
      now uses full `"alloy.pinmux.stm32-af-v1"` key.
      Original spec for reference:
      ```python
      @property
      def route_kind(self) -> str:
          """Mapped RouteKindId name for the connectors emitter."""
          _MAP = {
              "stm32_af": "route_kind_alternate_function",
              "sam_matrix_function": "route_kind_matrix_function",
              "rp2040_funcsel": "route_kind_funcsel",
              "esp32_io_matrix": "route_kind_io_matrix",
              "nordic_psel": "route_kind_psel",
          }
          return _MAP.get(self.backend_schema_id, "route_kind_unknown")
      ```

- [x] 2.2 Add `RouteKindId` values to the same mapping in `emit_connector_traits`
      (Phase 4).  No new IR fields needed — derived on emission.

---

## Phase 3 — Connection Group Support

`ConnectionGroupId` groups pins that must be activated together (e.g.,
`group_usart1_lqfp64_tx_rx` for USART1 TX+RX on LQFP64).  Currently not in
the synthesised IR.

- [ ] 3.1 Add optional `group` field to `PinOptionFixed` in the canonical v2.1
      YAML schema:
      ```yaml
      pin_options:
        - signal: tx
          pin: PB6
          af: 0
          group: usart1_lqfp64_tx_rx   # optional
      ```

- [ ] 3.2 Parse `group` in `alloy_codegen/canonical_device_v2_1.py` into the IR.

- [ ] 3.3 Thread `group: str | None` through `PinRoute` dataclass.

- [ ] 3.4 Update `alloy_codegen/ir/synthesised/pin_routes.py` to populate
      `PinRoute.group` from the canonical IR.

- [ ] 3.5 Add `group` field to `stm32g0/stm32g071rb.yml` entries (or the
      relevant family YAML) to exercise it in tests.

---

## Phase 4 — Implement `emit_connector_traits`

Generates `connectors.hpp`:
- `ConnectorId` enum
- `ConnectorDescriptor` struct
- `ConnectorTraits<Pin, Peripheral, Signal>` base template
- Full specialisations (valid combinations) with `kConnectorId`, `kRouteId`, etc.
- Guard A partial specs — `ConnectorTraits<Pin, Peripheral, Signal>` keyed on
  `(*, Peripheral, Signal)`: fires "Invalid connector for USART1 tx. Valid pins: PB6."
- Guard B partial specs — `ConnectorTraits<PinId::Pxy, Peripheral, Signal>` keyed on
  `(Pin, *, Signal)`: fires "PB6 can only serve signal_tx on: USART1." (modm-style)
- `ConnectorSignalTraits<Peripheral, Signal>` — lists valid pins per (peripheral, signal)
- `kConnectors` constexpr array

- [x] 4.1 Create `src/alloy_codegen/emit_v2_1/connector_traits.py`.
      Input: `SynthesisedDevice.pin_routes`.
      Output: `connectors.hpp` string. 522 lines. Smoke-tested.

- [x] 4.2 Register in `cli.py` `_EMITTERS` tuple:
      ```python
      _EmitterEntry(
          name="connector_traits",
          filename="connectors.hpp",
          fn=emit_connector_traits,
          description="ConnectorTraits + Guard A/B + kConnectors table.",
      ),
      ```

- [x] 4.3 Register in `entrypoint.py` `_EMITTERS` tuple (mirrors cli.py).

- [x] 4.4 Golden fixture superseded — structural tests cover the same
      regressions without a 550 KB committed binary.  Seeding a golden file
      deferred; content tested via `test_emit_connector_traits.py`.

- [x] 4.5 Add test in `tests/test_emit_connector_traits.py` (24 tests):
      - Header guard, namespace, enums, ConnectorDescriptor, detail namespace
      - Full spec for PB6 / USART1 / signal_tx (kPresent=true, ConnectorId)
      - RouteKindId::route_kind_alternate_function in full spec + kConnectors
      - Guard A for (*, USART1, signal_tx) with "PB6" in message
      - Guard B for (PB6, *, signal_tx) with "USART1" in message
      - ConnectorSignalTraits full spec for USART1/signal_tx
      - kConnectors size matches pin_routes count
      - Determinism + generate() integration

---

## Phase 5 — Implement `emit_routes`

Generates `routes.hpp`:
- `RouteId` enum
- `RouteKindId` enum
- `RouteDescriptor` struct
- `kRoutes` constexpr array

- [x] 5.1 Create `src/alloy_codegen/emit_v2_1/routes.py`.
      Derives `RouteId` names as `candidate_<pin>_<peripheral>_<signal>` (snake_case).
      Emits RouteId, RouteKindId, RouteDescriptor, kRoutes (728 lines / 42 KB for G071RB).

- [x] 5.2 Register in `cli.py` and `entrypoint.py` `_EMITTERS`.

- [x] 5.3 Add test in `tests/test_emit_routes.py` (10 tests):
      header guard, enums, struct, kRoutes size, PB6 entry, sentinel,
      determinism, generate() integration.

---

## Phase 6 — Replace Smoke with Generated-Output Test

- [x] 6.1 Created `tests/compile_tests/smoke_connector_routes.cpp` — tests
      `connectors.hpp` + `routes.hpp` together (`peripheral_id.hpp` excluded
      from same TU — ODR conflict: both define `PeripheralId`; they serve
      different subsystems and are included in separate TUs).
      Exercises: `ConnectorTraits` full spec, base template, `kConnectors`,
      `kRoutes` size equality, `RouteDescriptor` field access.

- [x] 6.2 Created `tests/test_compile_smoke.py`:
      - Uses `alloy_codegen.generate()` to produce artifacts in `tmp_path`
      - Runs `clang++ -std=c++20 -ffreestanding -nostdlib -Wall -Werror -c`
      - Skipped when `clang++` not on PATH (or `ALLOY_CLANGPP` not set)
      - Gated by `--compile-smoke` pytest flag (skips by default)
      - Also fixed two bugs discovered during smoke:
        * Duplicate full specialisations — alternate_pin variants created
          duplicate (pin,peri,signal) triples; deduplicated in `_emit_k_connectors`
          and full-spec loop in `connector_traits.py`
        * `routes.hpp` redefined `RouteId`/`RouteKindId` — fixed by having
          `routes.hpp` include `connectors.hpp` instead

- [x] 6.3 Added `--compile-smoke` flag + `compile_smoke` fixture to `conftest.py`.
      Registered `compile_smoke` mark in `pyproject.toml` to silence warnings.

---

## Notes

- Phase 1 is safe to do immediately — deleting pipeline tools does not affect any
  end-user workflow (alloy-cli uses `core/codegen.py` → `generate()` directly).

- Phase 3 (connection groups) is optional for initial connector emitter launch.
  The emitter can emit `ConnectionGroupId::none` for all routes until Phase 3 lands.
  Guard A and Guard B work correctly without group data.

- `regen_canonical_yamls.py`, `clean_orphan_yaml_references.py`,
  `bake_tier_data_into_yaml.py` are KEPT — they maintain `alloy-devices-yml` YAML
  data, not the deleted C++ artifact store.
