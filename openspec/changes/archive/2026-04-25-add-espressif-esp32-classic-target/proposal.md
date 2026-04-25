## Why

A admissão prévia do `espressif/esp32c3` (RISC-V mononúcleo) e `espressif/esp32s3`
(Xtensa LX7 dual-core, modelado como single-core-perspective) provou o pipeline
architecture-neutral.  Falta admitir o ESP32 clássico — o membro mais antigo e mais
distribuído da família — e, no mesmo passo, **promover o contrato Xtensa para
dual-core-aware**.

A motivação para tratar dual-core como parte deste change é direta: assim que o ESP32
clássico entra, dois targets dual-core convivem (LX6 + LX7), e manter ambos com a
postura single-core-perspective herdada da Decision 4 do `add-espressif-esp32-target`
deixaria os usuários sem qualquer caminho gerado para o APP_CPU.  Ao mesmo tempo, o
contrato dual-core mínimo é pequeno o bastante para caber neste change: emitir as
duas vector tables, dois `Reset_Handler*`, surfacing de `INTERRUPT_CORE1` e uma
primitiva de bring-up do APP_CPU.  Affinity/IPC continuam como concern de aplicação.

A infraestrutura non-runtime (source adapter `espressif-svd`, normalize, validation,
publication) é reaproveitada quase 100%: o `esp32.svd` já é vendorizado pelo adapter
existente, o threshold de host-linker (`0x10000`) admite o ESP32 sem skip, e o
emitter Xtensa apenas precisa generalizar para emitir o segundo core.

## What Changes

### Adicionar família ESP32 clássica

- **New family**: `espressif/esp32` em `DEVICE_REGISTRY` e `SOURCE_BUNDLES`
- **New patches**:
  - `patches/espressif/esp32/family.json` — peripheral allowlist, pin catalog
    (GPIO0–GPIO39), system clock profiles
  - `patches/espressif/esp32/devices/esp32.json` — chip nu QFN48
  - `patches/espressif/esp32/devices/esp32-wroom32.json` — módulo WROOM-32
- **Manual register patches**: `DPORT.PERIP_CLK_EN` + `DPORT.PERIP_RST_EN` (equivalente
  do `SYSTEM.PERIP_CLK_EN0/1` do S3, traduzido para o naming do clássico)

### Promover contrato Xtensa para dual-core (atinge S3 e ESP32 clássico)

- **Runtime emitter dual-core**: `runtime_xtensa_startup.py` passa a emitir:
  - `_vectors_cpu0[]` e `_vectors_cpu1[]` (tabelas separadas, VECBASE independentes)
  - `Reset_Handler` (PRO_CPU) + `Reset_Handler_CPU1` (APP_CPU)
  - Função `bring_up_app_cpu()` que toca `DPORT.APPCPU_CTRL_B` (ESP32) ou
    `SYSTEM.CORE_1_CONTROL_*` (ESP32-S3) para liberar o segundo core
  - Comentário explícito de que affinity/IPC ficam fora do contrato bootstrap
- **IR muda**: o filtro de `INTERRUPT_CORE1` em `_build_esp32_device_ir` é **removido**;
  os dois interrupt-matrix peripherals (`INTERRUPT_CORE0`, `INTERRUPT_CORE1` no S3;
  blocos PRO_INTR_*/APP_INTR_* dentro de `DPORT` no clássico) ficam no canonical IR
- **Connector model**: `VectorSlotDescriptor` ganha campo `core_affinity` (`"cpu0" |
  "cpu1" | "shared"`) para permitir distinguir a quem pertence cada vetor.  Default
  `"cpu0"` mantém compatibilidade para targets non-Xtensa
- **ESP32-S3 patch**: `patches/espressif/esp32s3/family.json` é atualizado para admitir
  `INTERRUPT_CORE1` (hoje filtrado pela allowlist)

### Plumbing administrativo

- **CI publish matrix**: nova entrada `vendor: espressif, family: esp32` em
  `.github/workflows/publish-alloy-devices.yml`
- **Bootstrap matrix**: `esp32` e `esp32-wroom32` em
  `.github/workflows/bootstrap-family.yml`
- **Consumer smoke**: `tests/test_foundational_families.py` cobre os novos devices E
  re-valida o `esp32s3` agora que ele emite os dois cores
- **Spec updates**: `vendor-admission` admite `espressif/esp32`; `canonical-device-ir`
  ganha um novo requisito de dual-core Xtensa que supersede a postura single-core
  herdada do change anterior

## Impact

- Affected specs: `vendor-admission`, `canonical-device-ir`
- Affected code:
  - `src/alloy_codegen/bootstrap.py` (registro novo)
  - `src/alloy_codegen/runtime_xtensa_startup.py` (rewrite para dual-core)
  - `src/alloy_codegen/stages/normalize.py` (`_build_esp32_device_ir` deixa de filtrar
    `INTERRUPT_CORE1`)
  - `src/alloy_codegen/connector_model.py` (campo `core_affinity` em `VectorSlotDescriptor`)
  - `src/alloy_codegen/emission.py` (comentário "Single-core-perspective" removido para
    Xtensa)
  - `patches/espressif/esp32/` (novo)
  - `patches/espressif/esp32s3/` (allowlist estendida com INTERRUPT_CORE1)
  - `tests/test_espressif.py`, `tests/test_foundational_families.py`
  - `.github/workflows/publish-alloy-devices.yml`,
    `.github/workflows/bootstrap-family.yml`
- **Sem mudanças** em: `sources/esp_idf.py`, `consumer_verification.py`,
  `artifact_contract.py`, runtime emitter de RISC-V/AVR/Cortex-M

## Implementation Phases

| Phase | Scope | Deliverable |
|-------|-------|-------------|
| 0 | Bootstrap + admission | `("espressif", "esp32")` em `DEVICE_REGISTRY`/`SOURCE_BUNDLES`; SVD resolve via adapter existente |
| 1 | Xtensa dual-core runtime contract | `runtime_xtensa_startup.py` reescrito; `core_affinity` em `VectorSlotDescriptor`; ESP32-S3 atualizado para emitir dois cores; goldens existentes do S3 atualizados |
| 2 | ESP32 clássico — family catalog | `family.json` com peripheral allowlist + pin catalog GPIO0–39 + clock profiles |
| 3 | ESP32 clássico — device patches | `esp32.json` (QFN48) + `esp32-wroom32.json` com memórias DRAM/IRAM/RTC e DPORT registers manuais |
| 4 | Validation green | Validation passa para ambos devices sem `draft_system_descriptor_domains` (ou domínio draft documentado, ex: `dma`) |
| 5 | Consumer smoke + publish gate | Pipeline end-to-end verde; nova entrada no publish matrix; CI publica `espressif/esp32/` em `alloy-devices` sem apagar siblings |
| 6 | Goldens & docs | Goldens emitidos para esp32, esp32-wroom32 E esp32s3 (atualizados para dual-core); README atualizado |

## Non-Goals

- Wi-Fi / Bluetooth registers e blobs proprietários
- Affinity metadata além do campo `core_affinity` no `VectorSlotDescriptor` (esp-idf
  faz routing via `esp_intr_alloc` em runtime; replicar isso na geração é fora de escopo)
- Inter-core IPC primitives (semáforos, queues, IPI senders) na runtime header
- Ethernet MAC, SDMMC, SDIO host (deferidos para follow-on)
- ESP32-PICO-D4 (SoC com flash interno) e ESP32-WROVER (módulo com PSRAM)
- ULP coprocessor descriptors
- Suporte às revisões V0/V1/V2 — admitir apenas ECO V3 (silício corrente)
- IO Matrix completo via `gpio_sig_map.h` para o ESP32 clássico — pin catalog vai sem
  signals; ingestão completa fica como follow-on
- ESP32-C3 NÃO é tocado (mononúcleo RISC-V, fora do escopo do dual-core retrofit)
