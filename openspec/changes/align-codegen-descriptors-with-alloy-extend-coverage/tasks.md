# Tasks — align-codegen-descriptors-with-alloy-extend-coverage

## Phase 1: CAN

- [ ] 1.1 Add `CanControllerDescriptor` dataclass to
      `ir/model.py` with fields covering controller index,
      nominal/data bitrate ceiling, mailbox count, RX FIFO
      count, filter bank count, CAN-FD support, classic-CAN
      support, TX/RX pin ids, clock source.
- [ ] 1.2 Promote `_build_can_rows()` from stub to full.
- [ ] 1.3 Per-device YAML migration: stm32g0b1re,
      stm32f405rg, atsame70q21b, mimxrt1062.
- [ ] 1.4 `tests/test_can_semantic_coverage.py` regression
      test against alloy's `extend-can-coverage` field
      expectations.

## Phase 2: USB Host

- [ ] 2.1 Add `UsbHostDescriptor` dataclass (separate from
      existing `UsbControllerDescriptor` which carries the
      Device-mode silicon facts).
- [ ] 2.2 Promote `_build_usb_host_rows()` from stub to full.
- [ ] 2.3 YAML migration: stm32f405rg (OTG_HS),
      atsame70q21b (USBHS), mimxrt1062 (USB1/USB2 host).
- [ ] 2.4 Regression test.

## Phase 3: Ethernet MAC

- [ ] 3.1 Add `EthernetMacDescriptor` dataclass.
- [ ] 3.2 Promote `_build_eth_rows()` from stub to full.
- [ ] 3.3 YAML migration: atsame70q21b (GMAC),
      mimxrt1062 (ENET).
- [ ] 3.4 Regression test against
      `alloy/extend-eth-coverage` expectations.

## Phase 4: QSPI / OctoSPI

- [ ] 4.1 Add `QspiControllerDescriptor` dataclass with
      `controller_kind` enum (`qspi | octospi | hyperbus`).
- [ ] 4.2 Promote `_build_qspi_rows()` from stub to full.
- [ ] 4.3 YAML migration: stm32f405rg (QUADSPI),
      atsame70q21b (QSPI), mimxrt1062 (FlexSPI A+B).
- [ ] 4.4 Regression test against
      `alloy/extend-qspi-coverage` expectations.

## Phase 5: SDMMC

- [ ] 5.1 Add `SdmmcControllerDescriptor` dataclass.
- [ ] 5.2 Promote `_build_sdmmc_rows()` from stub to full.
- [ ] 5.3 YAML migration: atsame70q21b (HSMCI),
      mimxrt1062 (uSDHC1/2).
- [ ] 5.4 Regression test against
      `alloy/extend-sdmmc-coverage` expectations.

## Phase 6: RTC

- [ ] 6.1 Add `RtcControllerDescriptor` dataclass with
      alarm_count, wakeup_capable, oscillator options.
- [ ] 6.2 Promote `_build_rtc_rows()` from stub to full on
      every admitted device with an RTC.
- [ ] 6.3 Regression test.

## Phase 7: Watchdog

- [ ] 7.1 Add `WatchdogControllerDescriptor` dataclass with
      window-mode flag, max timeout, prescaler options,
      reset-vs-interrupt behaviour.
- [ ] 7.2 Promote `_build_watchdog_rows()` from stub to full.
- [ ] 7.3 Regression test.

## Phase 8: Spec + final checks

- [ ] 8.1 MODIFIED `artifact-contract` requirement listing
      the 7 promoted classes.
- [ ] 8.2 `openspec validate
      align-codegen-descriptors-with-alloy-extend-coverage
      --strict` passes.
- [ ] 8.3 Coverage dashboard shows all 17 driver-semantics
      classes at FULL tier on every admitted device that
      owns the peripheral.
- [ ] 8.4 Cross-repo CI gate: alloy's `extend-*-coverage`
      smoke matrix compiles green against the bumped
      alloy-devices artifact.
