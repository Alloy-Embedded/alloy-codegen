## Why

ADC é um dos periféricos mais usados em embedded e o estado atual da geração
deixa lacunas significativas:

**Lacuna de cobertura (5 de 9 famílias)**: ESP32 clássico (SENS), ESP32-C3
(APB_SARADC), ESP32-S3 (APB_SARADC), Microchip AVR-DA (ADC0) e Raspberry Pi
RP2040 (ADC) emitem apenas o stub `kPresent=false`.

**Lacuna de profundidade**: o `AdcSemanticTraits` atual cobre os registers
de controle e fluxo de conversão mas omite informação que apps modm-style
universalmente precisam pra gerar drivers de alto nível:
- canais internos (TempSensor, VrefInt, VBat) — endereços e índices
- registers de calibração de fábrica + **contexto semântico** (em qual
  temperatura/voltagem foram medidos)
- **enums de valores válidos** (resoluções suportadas, sample times,
  oversampling ratios)
- **DMA bindings tipados** (qual DMA channel pode pareiar com este ADC)
- **External trigger sources** com nomes simbólicos (Tim1_Trgo, Exti11)
  e os valores EXTSEL correspondentes

Sem essa profundidade, o alloy consumer pode gerar `readChannel(N)` retornando
raw count, mas **NÃO consegue gerar** `readTemperature() -> celsius`,
`readVdd() -> mV`, `Adc1::Dma<Dma1Channel1>::startTimerTriggered<Tim1::Trgo>(buf)`
sem hardcodar constantes vendor-specific no consumer.

O objetivo é **100% das coisas relacionadas a ADC** — todo fato estático
documentado no silício como typed runtime trait, deixando ao app só decisões
de configuração (qual canal, quando converter).

## What Changes

A change tem 4 camadas (Tier 1+2+3+4) num único OpenSpec change.

### Tier 1 — paridade de cobertura (5 schemas novos)

- **`alloy.adc.espressif-esp32-sens-v1`** — ESP32 clássico SENS
- **`alloy.adc.espressif-esp32c3-saradc-v1`** — ESP32-C3 APB_SARADC
- **`alloy.adc.espressif-esp32s3-saradc-v1`** — ESP32-S3 APB_SARADC (layout
  difere do C3)
- **`alloy.adc.microchip-avr-adc-v1`** — AVR-DA ADC0
- **`alloy.adc.raspberrypi-adc-v1`** — RP2040 ADC

Cada um implementado por um `_<vendor>_<adc>_row` builder em
`runtime_driver_semantics.py`.

### Tier 2 — extensão básica (canais internos + calibração)

| Campo | Tipo | Razão |
|-------|------|-------|
| `kInternalChannelCount` + `kInternalChannels[]` | `std::array<InternalAdcChannel, N>` | TempSensor, VrefInt, VBat — tipo + channel index |
| `kCalibrationDataPointCount` + `kCalibrationDataPoints[]` | `std::array<CalibrationDataPoint, N>` | Carrega register ref + **constante semântica** (cal_temp_30=30, vrefint_nominal_mv=3300) |

> **Mudança vs draft anterior**: `kChannelPinMap` foi REMOVIDO.  O consumer
> pode derivar pin→channel via `ConnectorTraits<PinId, PeripheralId,
> SignalId>::kPresent` que já vem do pinmux/connectors.hpp.  Não duplicamos.

### Tier 3 — configuration value semantics (modm-style enums)

Apps tipo modm escrevem `Adc1::initialize<SystemClock, 12_bit, OversamplingRatio::x16>()`.
Pra gerar isso, traits precisam dos **valores válidos** desses fields:

| Campo | Tipo | Razão |
|-------|------|-------|
| `kSupportedResolutionBits[]` + `kResolutionFieldValues[]` | paired arrays | Ex.: G0 admite 6/8/10/12-bit, valores 0x3/0x2/0x1/0x0 no field RES |
| `kSampleTimeCyclesOptions[]` + `kSampleTimeFieldValues[]` | paired arrays | Ex.: G0 = {1.5, 7.5, 13.5, 28.5, 41.5, 55.5, 71.5, 239.5} cycles |
| `kOversamplingRatios[]` + `kOversamplingFieldValues[]` | paired arrays | Ex.: G0 admite 2x..256x; AVR-DA admite 2x/4x/8x; ESP32 não suporta HW oversampling |
| `kAdcMaxClockHz` | `std::uint32_t` | Constraint pro consumer escolher prescaler |
| `kCalibrationContext` | `CalibrationContext` struct | `cal_temp_low_celsius, cal_temp_high_celsius, cal_voltage_mv, vrefint_nominal_mv` — fórmula completa |

Dados patcheados no `device.json` (datasheet table); famílias sem suporte
declaram empty arrays + `kAdcMaxClockHz = 0`.

### Tier 4 — DMA + external trigger (modm-style DMA-driven ADC)

Apps modm fazem
`AdcDma::startTimerTriggered<Tim1::Trgo, DmaMode::Circular>(buffer)` — exige
DMA channel + trigger source resolvidos em compile-time:

| Campo | Tipo | Razão |
|-------|------|-------|
| `kDmaBindingCount` + `kDmaBindings[]` | `std::array<AdcDmaBinding, N>` | Carrega `(controller, request_id, request_value, data_register, transfer_width_bits)` |
| `kExternalTriggerCount` + `kExternalTriggers[]` | `std::array<AdcExternalTrigger, N>` | Carrega `(source, extsel_value, exten_polarity_default)` |
| `kDmaModeOptions[]` + `kDmaModeFieldValues[]` | paired arrays | Enumera OneShot/Circular |

Onde os dados vêm:
- **DMA bindings** — derivados do IR via `device.dma_requests` filtrado por
  peripheral.  AVR-DA e ESP32 classic ADC1 sem DMA carregam `kDmaBindingCount=0`
- **External triggers** — patcheados via novo `device.json::adc_external_triggers[]`
  (RM table 100+ por família)

Resultado: o consumer pode gerar template completo
`AdcDma<DmaController, DmaChannel>::startTimerTriggered<TriggerSource>(...)`
com validação compile-time end-to-end.

### Validation rule

Nova rule `<device>-adc-semantics-populated` (gate-c, blocking): para todo
peripheral com `peripheral_class == "adc"` admitido, o `AdcSemanticRow`
correspondente DEVE ter `kPresent=true` e `kSchemaId != none`.  Falha
bloqueia publish.

## Impact

- Affected specs: `artifact-contract`
- Affected code:
  - `src/alloy_codegen/runtime_driver_semantics.py` (5 builders novos +
    schema extension; existing 4 builders ganham fields novos)
  - `src/alloy_codegen/connector_model.py` (5 schema IDs novos)
  - `src/alloy_codegen/ir/model.py` (`InternalAdcChannel`,
    `CalibrationDataPoint`, `AdcDmaBinding`, `AdcExternalTrigger` structs +
    `CalibrationContext`)
  - `src/alloy_codegen/patches.py` (parsers dos novos campos device.json:
    `adc_internal_channels`, `adc_calibration_data_points`,
    `adc_resolution_options`, `adc_sample_time_options`,
    `adc_oversampling_options`, `adc_external_triggers`,
    `adc_max_clock_hz`, `adc_calibration_context`)
  - `src/alloy_codegen/validation.py` (nova rule
    `adc-semantics-populated`)
  - `src/alloy_codegen/emission.py` (common.hpp ganha novos enums +
    structs)
  - 9 device.json patches expandidos com os novos blocos ADC
  - `tests/test_runtime_driver_semantics.py` — testes per-vendor + cross-family
  - `tests/fixtures/emitted/*/.../driver_semantics/adc.hpp` — regenerar
    todos os goldens

## Implementation Phases

| Phase | Scope | Deliverable |
|-------|-------|-------------|
| 1 | Schema extension (Tier 2+3+4) — todos os fields novos no `AdcSemanticTraits` com defaults `kInvalid*`/empty arrays; novos structs em `common.hpp`; novos enums (`InternalAdcChannelKind`, `AdcCalibrationKind`, `AdcExternalTriggerSource`, `AdcDmaMode`) |
| 2 | IR + patch parser plumbing (`adc_internal_channels`, `adc_calibration_data_points`, `adc_resolution_options`, `adc_sample_time_options`, `adc_oversampling_options`, `adc_external_triggers`, `adc_max_clock_hz`, `adc_calibration_context`) — `DevicePatch` + `CanonicalDeviceIR` ganham os tuples opcionais |
| 3 | Existing builders (ST, NXP, AFEC) populam todos os fields novos a partir dos patches expandidos; STM32 G0/F4 device.json ganha cal context completo + resolution/sample-time tables; SAME70 / iMXRT1060 ganham seus equivalents |
| 4 | ESP32 family ADC builders (3 schemas distintos: SENS, C3-SARADC, S3-SARADC) + device.json updates (canais internos via SVD; cal **deferred a esp-idf** documentado em caveat) |
| 5 | AVR-DA + RP2040 builders + device patches (AVR-DA ganha SIGROW.SREF/TEMPSENSE; RP2040 ganha temp sensor channel 4) |
| 6 | DMA bindings derivation: builder agrega `device.dma_requests` filtrado por peripheral, populando `kDmaBindings[]` para ST/NXP/SAME70/RP2040; AVR-DA e ESP32 SENS sem DMA carregam empty array |
| 7 | External triggers: device patches expandidos com `adc_external_triggers` (RM table refs); builders preenchem `kExternalTriggers[]` |
| 8 | Validation rule `adc-semantics-populated` (gate-c blocking) + tests |
| 9 | Tests + goldens (per-vendor populated, cross-family parametrised, regression tests pra cal context + DMA bindings + trigger enums) — regenerar todos os 9 goldens |
| 10 | Spec deltas + docs (`artifact-contract` ganha 3 ADDED requirements: ADC populated, ADC config-value semantics, ADC DMA + trigger bindings) + caveats por família |

## Non-Goals

- **Differential mode pairs** — STM32G4/H7, ESP32-S3 suportam; modelar dual-channel
  measurements precisaria duplo channel-id; deferido para follow-on
- **Injected vs regular conversion groups** — STM32 tem dois grupos
  independentes de sequencer; consumer usa `kSequenceRegister` direto, dois
  grupos separados ficam follow-on
- **Conversion math impl** (mV/temperatura/Vdd computations) — fica no
  alloy consumer, não no alloy-codegen.  Nossos traits dão **constantes** e
  **register refs**; o **algoritmo** vive em alloy
- **Per-channel attenuation enum** (ESP32-specific 0/2.5/6/11 dB) — fica
  follow-on Espressif-only com schema extension dedicada
- **DMAMUX runtime reconfiguration** — `kDmaBindings[]` traz a tabela
  estática; trocar request_id em runtime é capability separada
- **eFuse calibration runtime read** (ESP32) — esp-idf
  `esp_adc_cal_*` continua o caminho; carregamos `kCalibrationContext`
  zerado pra ESP32 com caveat explicit
