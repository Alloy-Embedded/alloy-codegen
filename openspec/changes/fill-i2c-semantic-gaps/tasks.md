# Tasks: Fill I2C Semantic Gaps

## 1. IR model extension

- [ ] 1.1 Add `I2cPeripheralDescriptor` to `src/alloy_codegen/ir/model.py`:
      `peripheral_id`, `base_address`, `clock_source: str`, `dma_req_tx: int | None`,
      `dma_req_rx: int | None`, `valid_sda_pins: list[str] | Literal["any"]`,
      `valid_scl_pins: list[str] | Literal["any"]`, `supports_fast_mode_plus: bool`.
- [ ] 1.2 Add `Device.i2c_peripherals: list[I2cPeripheralDescriptor] = []` field.
      Existing fixtures validate (empty list = backward-compatible).
- [ ] 1.3 Update JSON schema and round-trip tests.

## 2. STM32G0 I2C traits

- [ ] 2.1 Extend `STM32GpioNormalizer` (or new `STM32I2cNormalizer`) to resolve
      I2C SDA/SCL pin assignments from `pin_data.json` (AF entries with signal
      matching `I2Cx_SDA` / `I2Cx_SCL` patterns).
- [ ] 2.2 Extract DMA request line indices for I2C1/I2C2 from the STM32G0
      reference manual DMA MUX table (hardcode in `patches/st/stm32g0/dma_mux.json`).
- [ ] 2.3 Implement `STM32I2cSemanticEmitter.emit(device)` for G0: emits
      `I2cSemanticTraits<I2cId::I2c1>` and `I2cSemanticTraits<I2cId::I2c2>`.
      `kClockSource` defaults to `I2cClockSource::Pclk`.
- [ ] 2.4 Golden: `tests/fixtures/emitted/stm32g071rb/driver_semantics/i2c.hpp`.
      Assert I2c1 has `kPresent=true`, `kBaseAddress=0x40005400`, correct valid pins.
- [ ] 2.5 Compile test: `test_stm32g0_i2c_traits.cpp`.

## 3. STM32F4 I2C traits

- [ ] 3.1 Create `patches/st/stm32f401re/dma_mux.json` (F4 uses DMA streams, not
      DMAMUX — record stream + channel per I2C direction).
- [ ] 3.2 Extend emitter for F4 family. F4 has I2C1/I2C2/I2C3 on F401.
      `kDmaStream`, `kDmaChannel` instead of `kDmaRequestTx/Rx` (F4 specific;
      use conditional compile via `ALLOY_HAL_STM32F4`).
- [ ] 3.3 Golden + compile test for `stm32f401re`.

## 4. ESP32 classic I2C traits

- [ ] 4.1 Parse I2C GPIO matrix signal indices from `gpio_sig_map.h` in
      `esp_idf.py`: `I2CEXT0_SDA_IN`, `I2CEXT0_SDA_OUT`, etc.
- [ ] 4.2 Implement `EspressifI2cSemanticEmitter` for ESP32 classic. Two
      peripherals: I2C0 (`kPeripheralIndex=0`, `kBaseAddress=0x3FF53000`) and
      I2C1 (`kPeripheralIndex=1`, `kBaseAddress=0x3FF67000`). `kValidSdaPins =
      AllGpios{}` sentinel. `kSupportsFastModePlus=false`.
- [ ] 4.3 Golden + compile test.

## 5. ESP32-C3 I2C traits

- [ ] 5.1 C3 has I2C0 only (`kBaseAddress=0x60013000`). No I2C1.
      `kSupportsFastModePlus=false`. Use C3 `gpio_sig_map.h` signal indices.
- [ ] 5.2 Golden + compile test.

## 6. ESP32-S3 I2C traits

- [ ] 6.1 S3 has I2C0 + I2C1 (`kBaseAddress=0x60013000`, `0x60027000`).
      `kSupportsFastModePlus=true`.
- [ ] 6.2 Golden + compile test.

## 7. RP2040 I2C traits

- [ ] 7.1 Add RP2040 I2C pin constraint table to
      `patches/raspberrypi/rp2040/i2c_pins.json`: I2C0 valid SDA pins = {0, 4, 8,
      12, 16, 20, 24, 28}, valid SCL pins = {1, 5, 9, 13, 17, 21, 25, 29};
      I2C1 valid SDA = {2, 6, 10, 14, 18, 26}, valid SCL = {3, 7, 11, 15, 19, 27}.
      (From RP2040 datasheet Table 2-5.)
- [ ] 7.2 Implement `RP2040I2cSemanticEmitter`. DREQs: I2C0_TX=32, I2C0_RX=33,
      I2C1_TX=34, I2C1_RX=35 (from RP2040 datasheet Table 2-7).
- [ ] 7.3 Golden + compile test.

## 8. AVR-DA I2C traits

- [ ] 8.1 Implement `AvrDaI2cNormalizer` in `atdf_avr.py`: parse
      `<module name="TWI">` from ATDF. Extract base addresses for TWI0 (and TWI1
      if present). Read PORTMUX signal to find alternate pin assignment.
- [ ] 8.2 Implement `AvrDaI2cSemanticEmitter`. Default pins: TWI0 SDA=PA2, SCL=PA3;
      alternate: PC2/PC3. TWI1 (DA48+) SDA=PF2, SCL=PF3.
- [ ] 8.3 Golden + compile test.

## 9. CI gate

- [ ] 9.1 Add `i2c-semantic-coverage` to the `gpio-semantic-coverage` CI job
      (extend the same job to also check `i2c.hpp` non-empty per admitted family).
- [ ] 9.2 Update `docs/COVERAGE_MATRIX.md`: add `i2c_traits` column, mark all
      families ✓ after this change.
