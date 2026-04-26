# Design — add-full-adc-coverage

## Context

`AdcSemanticTraits` foi a primeira semantic-trait emitida pelo pipeline e
seu escopo inicial foi minimalista — start, stop, channel-bit-pattern,
data field.  Hoje, 5 de 9 famílias admitidas emitem só o stub
`kPresent=false`, e mesmo as 4 que populam o trait param na superfície:
faltam canais internos, calibração, valores de configuração válidos
(resolutions, sample times), DMA bindings e external triggers.

O alloy consumer (que faz o codegen high-level estilo modm) precisa desses
fatos pra gerar APIs como `Adc1::readTemperature() -> float celsius`,
`Adc1::Dma<Dma1Channel1>::startTimerTriggered<Tim1::Trgo>(buf)`.  Sem isso,
o consumer fica obrigado a hardcodar constantes vendor-specific.

Esta proposta nivela ADC ao mesmo nível de cobertura que pinmux/connectors
têm hoje (que ficou bom — apps validam pin→peripheral em compile-time via
`ConnectorTraits`).

## Decision 1 — 4 tiers num único change, não fragmentar

**Decisão**: implementar Tier 1 (cobertura), Tier 2 (canais/cal), Tier 3
(value semantics) e Tier 4 (DMA + triggers) num único change.

**Razão**: o objetivo declarado é "100% do ADC".  Se ship Tier 1+2 isolado,
o consumer ainda fica preso em raw counts e `readTemperature()` não pode
ser totalmente compile-time validated.  Coordenação dos 4 tiers num único
change garante que `__readme_caveat` e validação ficam consistentes.

**Consequência**: change cresce pra ~60 tasks em 10 phases, mas evita 3
proposals encadeadas.  O risco é que Tier 4 (DMA) demora mais — mitigamos
emitindo `kDmaBindingCount=0` para famílias sem DMA (AVR-DA, ESP32 classic
ADC1).

## Decision 2 — Schemas distintos por SoC ESP

**Decisão**: três schemas separados pros ESPs:
- `alloy.adc.espressif-esp32-sens-v1`
- `alloy.adc.espressif-esp32c3-saradc-v1`
- `alloy.adc.espressif-esp32s3-saradc-v1`

**Razão**: layouts diferem materialmente — S3 tem 2 ADCs com filtros
independentes; C3 tem 1 ADC com 2 controllers DIG+SAR.  Schema compartilhado
forçaria `kInvalid*` em quase todos os fields opcionais.

## Decision 3 — `kChannelPinMap` REMOVIDO; usar connectors.hpp

**Decisão**: `AdcSemanticTraits` NÃO carrega channel→pin map.  O consumer
deriva via:

```cpp
ConnectorTraits<PinId::PA0, PeripheralId::ADC1, SignalId::IN0>::kPresent
```

já gerado pelo pinmux/connectors.hpp.

**Razão**: a info já existe e está validada compile-time.  Duplicar no ADC
trait é manutenção dupla e propício a drift.

**Consequência**: documentar no design que apps que querem
`Adc1::connect<GpioA0::In0>()` validam via ConnectorTraits, não via
AdcSemanticTraits.

## Decision 4 — Defaults `kInvalid*` / empty arrays preservam goldens

**Decisão**: todos os fields novos no `AdcSemanticTraits` têm defaults
seguros: `kInvalidFieldRef`, `kInvalidRegisterRef`, `0` para counts, arrays
vazios para os tipo `std::array<X, 0>` (renderizado como
`std::array<X, 0>{}` no template default).

**Razão**: famílias sem suporte (ex. ESP32 sem oversampling HW) carregam
arrays vazios honestos.  Goldens existentes para campos antigos não se
movem porque os defaults se serializam consistentemente.

**Consequência**: famílias suportadas precisam regenerar goldens (4 já
suportadas + 5 novas = 9 fixtures).

## Decision 5 — Calibração com **contexto**, não só endereços

**Decisão**: novo struct `CalibrationDataPoint` carrega:
```cpp
struct CalibrationDataPoint {
    AdcCalibrationKind kind;            // ts_cal_30, vrefint_cal, sigrow_sref
    RuntimeRegisterRef location;        // address + size
    std::int32_t       semantic_constant; // 30 (°C) for ts_cal_30; 3300 (mV) for vrefint_cal
};
```

E um `CalibrationContext` per-trait carrega o contexto global:
```cpp
struct CalibrationContext {
    std::int16_t  cal_temp_low_celsius;     // 30 for STM32G0
    std::int16_t  cal_temp_high_celsius;    // 110
    std::uint16_t cal_voltage_mv;           // 3300
    std::uint16_t vrefint_nominal_mv;       // 3000
    bool          valid;
};
```

**Razão**: sem o contexto, o consumer não consegue gerar `readTemperature()`.
Hardcodar "TS_CAL_30 foi medido a 30°C com VREF=3.3V" no consumer é exatamente
o que queremos evitar.  O contexto vem do datasheet — patcheado no device.json.

**Consequência**: device.json para STM32 G0/F4 + AVR-DA precisam declarar
`adc_calibration_context`.  ESP32 carrega `valid=false` (cal via esp-idf).
RP2040 carrega `valid=false` (sem cal de fábrica do ADC; só o temp sensor
tem cal nominal documentada).

## Decision 6 — Valores válidos em arrays paralelos

**Decisão**: para cada campo configurável (resolution, sample time,
oversampling, dma mode, external trigger), emit duas arrays paralelas:

```cpp
// Resolution
static constexpr std::array<std::uint8_t, 4> kSupportedResolutionBits   = {12, 10, 8, 6};
static constexpr std::array<std::uint8_t, 4> kResolutionFieldValues      = {0x0, 0x1, 0x2, 0x3};

// Sample time
static constexpr std::array<float, 8> kSampleTimeCyclesOptions   = {1.5f, 7.5f, 13.5f, 28.5f, 41.5f, 55.5f, 71.5f, 239.5f};
static constexpr std::array<std::uint8_t, 8> kSampleTimeFieldValues = {0, 1, 2, 3, 4, 5, 6, 7};
```

**Razão**: paired arrays são mais simples que `std::variant` ou tuples no
constexpr.  Consumer faz lookup por índice ou linear scan; ambos compile-time
otimizados.

**Consequência**: o tamanho da array é vendor-specific — usamos
`std::array<X, N>` per-specialization.  Defaults zero-sized.

## Decision 7 — DMA bindings derivam do IR existente

**Decisão**: builder ADC walks `device.dma_requests` filtrando por
peripheral (`request.peripheral == "ADC1"`), constrói:

```cpp
struct AdcDmaBinding {
    DmaControllerId controller;
    DmaRequestId    request_id;
    std::uint8_t    request_value;
    RuntimeRegisterRef data_register;       // == kDataRegister
    std::uint8_t       transfer_width_bits; // 16 ou 32
    bool               valid;
};
```

**Razão**: `device.dma_requests` já carrega tudo isso pra DMA controller
bindings.  Não duplicamos no patch — agregamos no builder.

**Consequência**: famílias sem dma_requests pra ADC (AVR-DA, ESP32 SENS
classic) carregam `kDmaBindingCount=0`.  Documentado em caveat.

## Decision 8 — External triggers patcheados

**Decisão**: novo campo `device.json::adc_external_triggers` com:

```json
{
  "adc_external_triggers": [
    { "peripheral": "ADC1", "source": "tim1_trgo",  "extsel_value": 0,  "default_polarity": "rising" },
    { "peripheral": "ADC1", "source": "tim2_trgo",  "extsel_value": 4,  "default_polarity": "rising" },
    { "peripheral": "ADC1", "source": "tim15_trgo", "extsel_value": 14, "default_polarity": "rising" },
    { "peripheral": "ADC1", "source": "exti11",     "extsel_value": 7,  "default_polarity": "rising" }
  ]
}
```

`source` é uma string symbolic id que o emitter mapeia pra valor do
`AdcExternalTriggerSource` enum (gerado em common.hpp com union vendor-aware
de todas as fontes admitidas).

**Razão**: trigger sources são fato per-device do RM (vendor table de 100+
linhas).  Não tem fonte upstream uniforme, então patch é o lugar.

**Consequência**: 5 device patches (G0, F4, SAME70, NXP, RP2040) ganham
trigger tables.  ESP32 carrega tabela mínima (só software trigger) por
ora — os triggers via timer precisam de digital controller config que é
runtime.  AVR-DA é a mesma coisa.

## Decision 9 — Validation rule blocking

**Decisão**: nova rule `<device>-adc-semantics-populated` (gate-c, error):
todo peripheral classificado `adc` no IR DEVE ter row populated com
`kSchemaId != none`.  Falha bloqueia publish.

**Razão**: garante que ninguém adiciona família com ADC e esquece de
implementar builder.  "100% das coisas" só é checável com fail-loud.

## Decision 10 — ESP32 calibração via esp-idf, documentada explicitamente

**Decisão**: para esp32, esp32c3, esp32s3, `kCalibrationContext.valid=false`
e `kCalibrationDataPointCount=0`.  `__readme_caveat` da família diz
explicitamente que cal precisa de `esp_adc_cal_*` runtime.

**Razão**: cal de fábrica via eFuse exige rotina de leitura BLOCK1/BLOCK2
+ characterization curve fitting + bit-packing.  Modelar como register refs
seria mentira.

**Consequência**: apps que querem mV preciso em ESP32 ainda chamam esp-idf;
apps que aceitam raw count com VREF nominal usam só nossos traits.

## Open Questions

Nenhuma — todas as decisões respondem aos inputs do usuário (Tier 1+2+3+4
combinados; schemas distintos por ESP; DMA/trigger via DMA bindings + patch).
