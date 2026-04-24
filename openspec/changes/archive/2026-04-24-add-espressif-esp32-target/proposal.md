## Why

`alloy-codegen` hoje prova bem o caminho multi-vendor dentro do universo Cortex-M. Isso ainda
não prova que o pipeline é realmente architecture-neutral. Espressif é o teste certo porque
combina:

- um vendor novo
- um bootstrap RISC-V (`esp32c3`)
- um follow-on Xtensa (`esp32s3`)
- uma topologia de GPIO diferente do modelo AF/IOMUXC (`IO Matrix`)

Esta proposta admite Espressif como o primeiro vendor não-ARM, mas faz isso sem fingir que
o impacto é só em startup. O contrato público precisa passar a distinguir artefatos
architecture-scoped, e a ingestão precisa formalizar a proveniência de dados suplementares
como `gpio_sig_map.h`.

## What Changes

- **New vendor**: `espressif` entra em `DEVICE_REGISTRY` e `SOURCE_BUNDLES`
- **New source adapter**: `sources/esp_idf.py` consome os SVDs publicados em
  `github.com/espressif/svd`
- **Supplementary source ingestion**: o pipeline passa a consumir `gpio_sig_map.h` como
  fonte suplementar versionada para IO Matrix; isso entra no source manifest e na proveniência
- **New families**:
  - `esp32c3` como bootstrap family obrigatória
  - `esp32s3` como follow-on family, documentada explicitamente como
    perspectiva de controle de um único core no primeiro corte
- **Architecture-scoped runtime contract**:
  - `systick.hpp` continua existindo só para Cortex-M
  - startup/runtime artifacts passam a ser validados por arquitetura, não por suposição ARM
- **New pinmux schema**: `alloy.pinmux.espressif-iomatrix-v1`
- **Explicit vector baselines**: `connector_model.py` ganha entradas explícitas para
  `riscv` e `xtensa-lx7`; o fallback silencioso para `cortex-m4` é removido
- **Runtime emission**:
  - `interrupts.hpp`, `clock_graph.hpp`, `peripheral_instances.hpp` e semânticas de driver
    continuam no contrato padrão
  - `startup` diverge por arquitetura
  - `systick.hpp` torna-se explicitamente opcional fora de Cortex-M
- **CI/vendor admission**: os gates passam a validar `espressif` e o contrato runtime-only
  completo para arquitetura não-Cortex

## Impact

- Affected specs: `vendor-admission`, `canonical-device-ir`, `artifact-contract`
- Affected code:
  - `bootstrap.py`
  - `stages/fetch.py`
  - `sources/esp_idf.py`
  - `connector_model.py`
  - `stages/emit.py`
  - `artifact_contract.py`
  - `consumer_verification.py`
  - `patches/espressif/esp32c3/`
  - `patches/espressif/esp32s3/`
  - `tests/`
  - `.github/workflows/publish-alloy-devices.yml`

## Implementation Phases

| Phase | Scope | Deliverable |
|-------|-------|-------------|
| 0 | Bootstrap & source manifests | Espressif SVD + IO Matrix supplementary source are fetched with provenance |
| 1 | IR ingestion (ESP32-C3) | Valid `CanonicalDeviceIR` for `esp32c3` |
| 2 | IO Matrix routing | `iomatrix-v1` schema published with signal-index provenance |
| 3 | Runtime contract | ESP32-C3 runtime headers + architecture-scoped startup pass contract gates |
| 4 | Xtensa follow-on | ESP32-S3 pipeline runs with single-core control-plane perspective documented |
| 5 | CI & publication gates | `espressif/esp32c3` publishes under the same runtime-only completeness rules |
| 6 | Fixtures & docs | Goldens, docs, and licensing/provenance notes updated |

## Non-Goals

- ESP32 original dual-core LX6
- ESP32-C6 / H2 / P4
- FreeRTOS / ESP-IDF HAL code generation
- Wi-Fi / Bluetooth runtime semantics
- full multi-core ownership or interrupt-routing semantics for Xtensa in this change
