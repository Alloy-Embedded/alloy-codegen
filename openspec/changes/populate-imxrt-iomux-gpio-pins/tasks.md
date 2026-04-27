# Tasks — populate-imxrt-iomux-gpio-pins

## Phase 1: IOMUX parser

- [ ] 1.1 New `src/alloy_codegen/sources/nxp_iomux.py` exposing
      `parse_fsl_iomuxc_header(path) -> tuple[ImxrtPinMux, ...]`.
- [ ] 1.2 `ImxrtPinMux` dataclass: pin name, peripheral, signal,
      selector index, daisy register address (or None), daisy
      value (or None).
- [ ] 1.3 Regex-based extractor for `IOMUXC_<PIN>_<MODE>(...)`
      preprocessor macros (the format is regular and stable
      across MCUXpresso versions).
- [ ] 1.4 Decoder for the `<MODE>` suffix → `(peripheral_name,
      signal_name)` via a small curated map (LPUART_TX → LPUARTn
      / TX, FLEXSPI_A_DATA0 → FLEXSPIn / DATA0, …).

## Phase 2: Adapter integration

- [ ] 2.1 `nxp_mcux.py` resolves the IOMUX header path and
      calls the new parser.
- [ ] 2.2 The adapter exposes a `iomux_pinmux` field on its
      intermediate document so the normalize stage can consume
      it.

## Phase 3: Normalize integration

- [ ] 3.1 `_build_imxrt1060_device_ir` extends `gpio_pins`
      with one entry per IOMUX pin name (deduplicated against
      the family-catalog pin list).
- [ ] 3.2 `connection_candidates` projects every IOMUX
      `(pin, peripheral, signal)` triple via the existing
      `connector_model.assemble_connection_candidates`
      machinery.  `route_kind="iomuxc-mux"`,
      `route_selector="selector:<n>"`.
- [ ] 3.3 Daisy register/value, when present, attached to the
      candidate via existing `RouteRequirement` /
      `RouteOperation` records so the runtime layer can resolve
      them.

## Phase 4: Tests

- [ ] 4.1 Parser unit test on a snapshotted `fsl_iomuxc.h`
      excerpt: covers LPUART1_TX, FLEXSPI A0, GPIO1_IO00.
- [ ] 4.2 Pipeline test: `mimxrt1062` IR has non-empty
      `gpio_pins` (at least 100 entries) and non-empty
      `connection_candidates` (at least one per admitted
      LPUART instance).
- [ ] 4.3 `pin_validation.hpp` emitted for `mimxrt1062` and
      `mimxrt1064`.
- [ ] 4.4 `--runtime-cpp-smoke` stays green.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/canonical-device-ir/spec.md`.
- [ ] 5.2 `openspec validate populate-imxrt-iomux-gpio-pins
      --strict` passes.
- [ ] 5.3 Goldens regen for iMXRT1062 + iMXRT1064 (expected;
      `connectors.hpp`, `pin_validation.hpp` are the new
      surfaces).
