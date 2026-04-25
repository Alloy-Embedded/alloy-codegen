# Design — add-espressif-esp32-classic-target

## Context

Esta proposta combina dois movimentos:

1. **Adicionar** o ESP32 clássico (Xtensa LX6 dual-core) como nova família admitida
2. **Retrofit** do contrato Xtensa para dual-core, atingindo retroativamente o
   ESP32-S3 (Xtensa LX7 dual-core) que hoje é modelado como single-core-perspective

Por que combinar? Porque o emitter Xtensa é o mesmo (`runtime_xtensa_startup.py` aceita
qualquer `core` que comece com `xtensa`), e qualquer mudança nele atinge S3 e clássico
simultaneamente.  Manter o S3 single-core enquanto o clássico já nasce dual-core
geraria duas semânticas para o mesmo emitter — pior do que migrar os dois juntos.

A infraestrutura non-runtime já está pronta:
- `espressif-svd` source adapter vendoriza `esp32.svd` (47 periféricos),
  confirmado em `.cache/sources/espressif-svd/svd/esp32.svd`
- `_build_esp32_device_ir` é genérico por família
- `_HOST_LINKER_LOW_ADDRESS_THRESHOLD = 0x10000` admite ESP32 (flash em `0x40000000`)
- O contrato architecture-scoped (systick.hpp opcional fora de Cortex-M) está consolidado

## Decision 1 — Dual-core control plane (supersede do single-core-perspective Xtensa)

**Decisão**: o contrato Xtensa passa a modelar dual-core no nível mínimo:

- **Vector tables independentes**: emitir `_vectors_cpu0[]` e `_vectors_cpu1[]`
  separadamente.  Cada core tem seu próprio VECBASE register; ROM do PRO_CPU já está
  setado quando entramos, e `bring_up_app_cpu()` configura o do APP_CPU antes de
  unholdá-lo
- **Dois entry points**: `Reset_Handler` (PRO_CPU, executa BSS/data init + ctors +
  main), `Reset_Handler_CPU1` (APP_CPU, pula init estático e entra em loop de espera
  ou chama `app_main_cpu1()` se a aplicação fornecer)
- **Bring-up emitido**: função `bring_up_app_cpu()` — toca
  `DPORT.APPCPU_CTRL_B = 1` (ESP32 clássico) ou
  `SYSTEM.CORE_1_CONTROL_0.CONTROL_CORE_1_CLKGATE_EN = 1` +
  `SYSTEM.CORE_1_CONTROL_1.CONTROL_CORE_1_RUNSTALL = 0` (ESP32-S3) — para liberar o
  segundo core
- **Inter-core IPI peripheral admitido**: o filtro de `INTERRUPT_CORE1` em
  `_build_esp32_device_ir` é removido; os dois interrupt-matrix peripherals
  (`INTERRUPT_CORE0` e `INTERRUPT_CORE1` no S3; PRO_INTR_*/APP_INTR_* dentro de
  `DPORT` no clássico) ficam no canonical IR

**O que NÃO é emitido** (delegado a esp-idf ou aplicação):
- Affinity routing além do `core_affinity` que já será preenchido
- IPI senders / receivers
- Spinlocks, mutexes, queues inter-core
- Shared memory cache invalidation policies

**Razão**:
- Sem `bring_up_app_cpu` emitido, aplicações que não usam esp-idf ficam sem caminho
  para iniciar o segundo core
- A separação clara entre "control plane primitives" (emitido) e "synchronization
  primitives" (delegado) mantém o escopo do alloy-codegen consistente
- ESP32 clássico e S3 compartilham 95% deste contrato; só os registradores específicos
  de bring-up diferem

**Consequência**: a Decision 4 do `add-espressif-esp32-target` é efetivamente revogada
para Xtensa.  Os goldens emitidos do ESP32-S3 precisam ser regerados.  Aplicações
existentes que linkavam só `Reset_Handler` continuam funcionando — `Reset_Handler_CPU1`
é um símbolo novo, não substitui o existente.

## Decision 2 — `core_affinity` no VectorSlotDescriptor

**Decisão**: adicionar campo `core_affinity: Literal["cpu0", "cpu1", "shared"] = "cpu0"`
em `VectorSlotDescriptor`.  Default `"cpu0"` mantém compatibilidade para Cortex-M /
RISC-V / AVR (single-core).  Para Xtensa dual-core:
- vetores roteados via `INTERRUPT_CORE0` → `core_affinity = "cpu0"`
- vetores roteados via `INTERRUPT_CORE1` → `core_affinity = "cpu1"`
- system exceptions (NMI, double-fault) → `core_affinity = "shared"`

**Razão**:
- Sem essa anotação, não é possível particionar `_vectors_cpu0[]` vs `_vectors_cpu1[]`
  na emissão
- Default `"cpu0"` é o que todo target single-core já assume implicitamente — zero
  impacto fora do Xtensa

**Consequência**: o `connector_model.py` constrói `VectorSlotDescriptor` em um lugar
só (já visto no fix do AVR-DA); a mudança é localizada.  Os emitters Cortex-M/RISC-V/AVR
continuam consumindo a mesma estrutura, ignorando o campo novo.

## Decision 3 — Packages admitidos no ESP32 clássico (QFN48 + WROOM-32)

**Decisão**: admitir os dois packages, **compartilhando o `family.json`** e divergindo
apenas no `device.json`:

- `esp32.json` — chip nu QFN48 (40 GPIOs visíveis, mas GPIO34–39 input-only)
- `esp32-wroom32.json` — módulo WROOM-32 (subset; GPIO6–11 reservados para flash interno)

ESP32-PICO-D4 e ESP32-WROVER ficam fora.

**Razão**:
- WROOM-32 é o vehicle real de 95% das placas (DevKitC, NodeMCU, Heltec)
- Padrão existente: `same70` admite `atsame70n21b` + `atsame70q21b` no mesmo padrão
- ESP32-PICO-D4 tem flash interno + restrições de roteamento que exigiriam um package
  separado e gerariam casos sem cobertura de teste

**Consequência**: o `peripheral_allowlist` é o mesmo para os dois; restrições físicas
do módulo entram via `package_pads.bonding_state`.

## Decision 4 — DPORT vs SYSTEM register naming

**Decisão**: ESP32 clássico usa `DPORT` como nome do bloco de clock-enable/reset (não
`SYSTEM` como o S3).  Os registradores manualmente patcheados serão:

- `DPORT.PERIP_CLK_EN` (offset `0x0C0`, base `0x3FF00000`) com `register_fields` por bit
- `DPORT.PERIP_RST_EN` (offset `0x0C4`)
- `DPORT.APPCPU_CTRL_B` (offset `0x030`) — usado pelo `bring_up_app_cpu()` no clássico

derivados do TRM Espressif §5.5 (Peripheral Clock Gate) e §3.3 (CPU Control).

**Razão**:
- `DPORT` é o naming canônico no SVD e no esp-idf — não inventar alias
- Manter paridade com o que esp-idf chama de `DPORT_PERIP_CLK_EN_REG`

**Consequência**: o connector model gera `clock-bindings` apontando para
`DPORT.PERIP_CLK_EN.<bit>` em vez de `SYSTEM.*`; o emitter typed-runtime resolve via
`_typed_register_ref` sem código novo.

## Decision 5 — Revisão de silício (ECO V3 only)

**Decisão**: o `device.json` declara `revision: "v3"` em metadata.  Revisões V0/V1/V2
NÃO são admitidas no bootstrap.

**Razão**:
- ECO V3 é o silício corrente desde 2020 e o que esp-idf trata como baseline
- Revisões antigas têm errata (SPI flash boot bug, GPIO glitch) que exigiria workarounds

**Consequência**: aplicações com chips V0–V2 declaram explicitamente em código de
aplicação; não é responsabilidade do alloy-codegen.

## Decision 6 — Wi-Fi/BT/Ethernet/SDMMC fora do escopo

**Decisão**: o `peripheral_allowlist` cobre apenas:

```
UART0, UART1, UART2,
SPI2, SPI3,
I2C0, I2C1,
TIMG0, TIMG1,
GPIO,
LEDC,
RMT,
ADC1,
DPORT (system control),
INTERRUPT_CORE1 (apenas para S3 — o clássico tem o IPI integrado em DPORT)
```

Wi-Fi (`WIFI_*`), Bluetooth (`BT_*`), Ethernet (`EMAC`), SDMMC, DAC, AES/SHA, ADC2, ULP
são excluídos.

**Razão**:
- ADC2 compartilha hardware com Wi-Fi e tem caveats de coexistência — fora do bootstrap
- Wi-Fi/BT registers são essencialmente undocumented; toda interação é via blobs
- Mantém catálogo enxuto e foca no que tem cobertura real de teste

**Consequência**: o domínio `dma` provavelmente fica em `draft` no primeiro corte (GDMA
do clássico é per-peripheral, não centralizado como no S3).  Tratado pelo gate de
`draft_system_descriptor_domains` que já existe e não bloqueia publicação.

## Open Questions

Nenhuma — todas as decisões respondem aos inputs do usuário (dual-core, ambos packages,
peripherals sugeridos, sem PICO-D4) e replicam patterns já provados.
