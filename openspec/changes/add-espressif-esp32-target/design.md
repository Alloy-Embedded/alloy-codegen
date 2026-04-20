## Context

ESP32 é o primeiro caso em que o pipeline precisa provar três coisas ao mesmo tempo:

1. o contrato runtime não depende implicitamente de Cortex-M
2. o source-of-truth pode combinar SVD + fonte suplementar com proveniência clara
3. uma topologia de pin routing não-AF cabe no mesmo boundary tipado

O bootstrap correto é `esp32c3`. `esp32s3` entra no mesmo change como follow-on controlado,
mas não deve forçar uma modelagem prematura de multi-core.

## Goals / Non-Goals

Goals:
- admitir `esp32c3` no pipeline sem fallback ARM implícito
- formalizar artefatos architecture-scoped no contract validator
- publicar IO Matrix com proveniência explícita de `gpio_sig_map.h`
- deixar `esp32s3` preparado como extensão incremental, sem esconder seu risco de topologia

Non-Goals:
- modelar a execução dual-core completa do `esp32s3`
- gerar código específico de FreeRTOS/IDF
- suportar periféricos Wi-Fi/BLE/USB fora do contrato runtime principal

## Decisions

### Decision 1: `esp32c3` é o bootstrap obrigatório; `esp32s3` é follow-on com perspectiva single-core

**Chosen**: `esp32c3` entra primeiro. `esp32s3` só entra depois do bootstrap RISC-V estabilizar
e é explicitamente documentado como uma descrição do plano de controle de um core.

**Rationale**: isso evita contaminar o IR agora com modelagem multi-core incompleta.

### Decision 2: SVD é a fonte primária; `gpio_sig_map.h` é fonte suplementar obrigatoriamente versionada

**Chosen**:
- registradores, interrupções e base addresses vêm de `github.com/espressif/svd`
- IO Matrix vem de `gpio_sig_map.h`

**Rationale**: o SVD sozinho não fecha a roteabilidade do ESP32. A fonte suplementar precisa
ser tratada como dado oficial do pipeline, não como detalhe solto de patch.

**Consequence**: source manifest, docs de licença e proveniência precisam registrar:
- origem
- revisão/tag
- arquivo consumido
- papel semântico da fonte suplementar

### Decision 3: `systick.hpp` e startup são artefatos architecture-scoped

**Chosen**: o contract validator deixa explícito que:
- `systick.hpp` é obrigatório só para Cortex-M
- startup é validado por família de arquitetura (`cortex-m`, `riscv`, `xtensa`)

**Rationale**: isso evita que o contrato público continue carregando um viés ARM invisível.

### Decision 4: IO Matrix usa schema próprio e `af_number` continua schema-local

**Chosen**: `alloy.pinmux.espressif-iomatrix-v1`.

`af_number` guarda o índice numérico do sinal da IO Matrix, mas só é interpretado assim
quando o `backend_schema_id` for o schema Espressif.

### Decision 5: unknown core falha explicitamente

**Chosen**: remover o fallback para `cortex-m4` e lançar erro explícito para core não reconhecido.

**Rationale**: a pior coisa aqui é um IR “válido” semanticamente errado.

## Risks / Trade-offs

- **SVD incompleto**: clock/reset coverage pode exigir patch
- **fonte suplementar driftar**: `gpio_sig_map.h` pode variar entre releases do IDF
- **Xtensa dual-core**: `esp32s3` não deve fingir que resolve afinidade/ownership de dois cores

## Migration Plan

Nenhum device existente muda de comportamento. O que muda é o contract validator, que passa
a reconhecer artefatos opcionais por arquitetura.

## Open Questions

- `esp32s3` deve entrar neste change ou virar subchange separado quando `esp32c3` publicar?
  Resposta provisória: manter aqui, mas como fase posterior e explicitamente opcional.
- O source manifest já comporta múltiplas fontes por family com revisão independente?
  Se não, essa é a primeira extensão obrigatória antes do parse do IO Matrix.
