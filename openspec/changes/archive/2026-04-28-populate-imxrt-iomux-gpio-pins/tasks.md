# Tasks — populate-imxrt-iomux-gpio-pins

## Phase 1: IOMUX parser

- [x] 1.1 The IOMUX parser already lives in
      `src/alloy_codegen/sources/nxp_mcux.py` as
      `parse_iomuxc_entries` + `NxpIomuxcEntry` (shipped under
      a previous change).  It extracts pad_name, signal_name,
      mux_mode, and pad_number from `IOMUXC_<PAD>_<SIGNAL>`
      macros.
- [x] 1.2 Audit confirmed: `_build_nxp_pins` already projects
      IOMUX entries into `PinDefinition` tuples (4 pins on the
      fixture).  `_build_nxp_package_pads` populates
      `package_pads`.
- [x] 1.3 `connection_candidates` populated post-normalize via
      `connector_model.ensure_connector_descriptors` — 10
      candidates for mimxrt1062 with `route_kind="iomuxc-mux"`
      and proper `route_selector="selector:<n>"`.

## Phase 2: gpio_pins extraction (the gap)

- [x] 2.1 New helper `_build_imxrt_gpio_pins(pins, provenance)`
      in `stages/normalize.py`.  For each pad, finds the
      `GPIO<N>.IO<XX>` signal entry and emits a
      `GpioPinDescriptor` with port=`GPIO<N>`, pin_index=`<XX>`,
      port_offset=`(N-1) * 0x4000`.
- [x] 2.2 Alt-functions table excludes the GPIO self-entry —
      the pad's identity is the GPIO bit, not an alternate.
- [x] 2.3 Wired into `build_nxp_canonical_ir`: the IR's
      `gpio_pins` tuple is now populated for iMXRT (was empty
      before).

## Phase 3: pin_validation.hpp emission

- [x] 3.1 Already emitted by the existing
      `emit-pinmux-validator-concepts` machinery — no emitter
      changes needed.  Verified end-to-end:
      `pin_validation.hpp` for mimxrt1062 contains
      `PinAssignmentValid<PinId::GPIO_AD_B0_00,
      PeripheralSignal::LPI2C1_SCL> : std::true_type`
      specialisations and `RouteKind::iomuxc_mux`.
- [x] 3.2 Daisy-chain register/value plumbing is exercised on
      the LPI2C1_SCL entry (the IOMUX header carries the daisy
      register reference; the parser captures it for runtime
      consumers).

## Phase 4: Tests

- [x] 4.1 Unit tests for `_build_imxrt_gpio_pins`: skips pads
      without GPIO signal, extracts port + index from
      GPIO<N>.IO<XX>, computes `port_offset` correctly,
      excludes GPIO self-entry from alt_functions, sorts
      alt_functions by (af_number, signal_name).
- [x] 4.2 End-to-end: the mimxrt1062 fixture pipeline produces
      a non-empty `gpio_pins` tuple with sane shape (port
      starts with `GPIO`, pin_index < 32).
- [x] 4.3 6 tests pass.

## Phase 5: Data repo update

- [x] 5.1 Re-emitted canonical YAMLs for mimxrt1062 + mimxrt1064
      via `_build_nxp_device_ir + ensure_connector_descriptors
      + serialize_device`, pushed to `alloy-devices-yml`
      (SHA `0f3b116`).  Submodule pin bumped.
- [x] 5.2 YAMLs now carry `gpio_pins=4` + `connection_candidates=10`
      + the standard iMXRT fields downstream emitters consume.

## Phase 6: Spec + final checks

- [x] 6.1 Spec delta in `specs/canonical-device-ir/spec.md`.
- [x] 6.2 `openspec validate populate-imxrt-iomux-gpio-pins
      --strict` passes.
- [x] 6.3 `pin_validation.hpp` for mimxrt1062 still emits
      cleanly through the YAML short-circuit; iomuxc-mux
      RouteKind preserved.
- [ ] 6.4 Goldens regen for iMXRT — **deferred** to a follow-up
      cleanup pass; the YAMLs in alloy-devices-yml are now the
      source of truth, and goldens for iMXRT C++ artifacts
      will be regenerated when the next emitter change lands.
