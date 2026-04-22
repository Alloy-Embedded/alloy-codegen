## Context

O RP2040 usa Cortex-M0+ (ISA já suportada pelo G0), mas tem três divergências de modelo
em relação a qualquer vendor já admitido:

1. **Sem flash interno**: firmware roda via XIP (Execute in Place) sobre QSPI externo.
   O boot ROM inicializa o flash, copia o `boot2` (segundo estágio de 256 bytes), que por
   sua vez configura XIP e salta para `main`. O linker script e o startup precisam conhecer
   essa topologia.

2. **FUNCSEL pinmux**: ao invés de alternate-function numbers independentes por pino, cada
   GPIO expõe um campo `FUNCSEL` de 5 bits em `IO_BANK0_GPIO<n>_CTRL`. Os valores 0-9 são
   uma tabela fixa por chip (0=XIP, 1=SPI, 2=UART, 3=I2C, 4=PWM, 5=SIO, 6=PIO0, 7=PIO1,
   8=GPCK, 9=USB). Semanticamente idêntico a ARM AF porém com schema distinto.

3. **PIO**: Periférico sem análogo. Dois blocos (PIO0, PIO1) × 4 state machines. Cada SM
   executa um microprograma de até 32 instruções de 16 bits. Não é modelável com semantic
   traits de UART/SPI/I2C. Primeiro corte admite como presente mas não semanticamente dirigido.

## Goals / Non-Goals

- Goals:
  - RP2040 emite o conjunto completo de artefatos runtime padrão (sem exceções no contract)
  - FUNCSEL routing é distinguível de ARM AF por `backend_schema_id`
  - XIP memory e boot2 são modelados no linker script e startup emitidos
  - PIO aparece em capabilities como presente; semantics stub não bloqueia admission
  - Dual-core é documentado explicitamente como single-core-perspective no primeiro corte

- Non-Goals:
  - Suporte pleno a SMP (inter-core FIFOs, spinlocks, hardware divider por core)
  - PIO driver semantics com campos de instrução, side-set, delay, ou pin mapping
  - RP2350 ou variantes futuras da família

## Decisions

### D1 — FUNCSEL como extensão do modelo AF existente

**Decision**: `af_number` nos `PinSignal` do IR continua representando o valor FUNCSEL
numérico (0-9). O que muda é o `backend_schema_id` do peripheral instance: `alloy.pinmux.rp2040-funcsel-v1`. Consumidores que verificam `backend_schema_id` sabem aplicar a tabela FUNCSEL ao invés de registros AF ARM-padrão.

**Alternatives considered**:
- Novo campo `funcsel_index` no IR — descartado por explosão de schema sem ganho semântico; o
  significado de `af_number` já é "índice de função" que é exatamente o que FUNCSEL é.
- Campo separado no patch — descartado; fonte de verdade já está no SVD + tabela fixa.

**Rationale**: Reutilizar `af_number` com `backend_schema_id` distinguindo é o mesmo padrão
usado para `alloy.pinmux.imxrt-iomuxc-v1` vs `alloy.pinmux.stm32-af-v1`. Consistência.

### D2 — XIP como kind `xip-flash` no MemoryRegion

**Decision**: Introduzir `kind = "xip-flash"` para a região `0x10000000–0x10FFFFFF` (XIP
cache window). O linker script emite seções `BOOT2 (rx)` e `TEXT (rx)` dentro dessa região.
SRAM interno `0x20000000` permanece `kind = "sram"`.

**Alternatives considered**:
- Tratar XIP como `flash` com flag adicional — ambíguo; `flash` implica programável in-circuit
  diretamente pelo MCU, o que não é o caso do RP2040 (flash externo).
- Não modelar XIP, deixar para o usuário — descartado; o linker script gerado seria inválido
  para qualquer projeto Pico.

**Rationale**: Semântica distinta merece kind distinto. `xip-flash` deixa claro que é
memória executável somente-leitura mapeada externamente via controlador XIP.

### D3 — Startup emite placeholder boot2 + XIP init

**Decision**: `startup.cpp` gerado inclui:
1. Um array `__boot2_padding` de 256 bytes na seção `.boot2` como placeholder (o usuário
   substitui pelo `boot2` do pico-sdk para o flash específico).
2. Uma chamada explícita a `xip_init()` antes do copy loop de `.data`.

Sem isso o código não executa de flash externo. Com isso o projeto compila e linka, ainda
que precise do `boot2` correto para rodar em hardware real.

**Alternatives considered**:
- Não emitir startup para RP2040 — descartado; quebra o artifact contract.
- Emitir o `boot2` real para um flash específico — escopo demais; o pico-sdk tem ~20 boot2
  variants por fabricante de flash. Placeholder é o compromisso correto.

### D4 — PIO como capability stub sem semantic traits

**Decision**: `capabilities.hpp` emite `runtime-support:pio` como presente. O arquivo
`driver_semantics/pio.hpp` é emitido como stub vazio (todos os refs como `kInvalidRef`).
`kPioSemanticPeripherals` é um array vazio.

**Alternatives considered**:
- Omitir PIO totalmente — descartado; `capabilities.json` ficaria inconsistente com o SVD
  que lista PIO0/PIO1.
- Modelar PIO com semantic traits neste corte — escopo demais; PIO não mapeia em nenhuma
  das 17 classes existentes. É trabalho de uma mudança futura dedicada.

**Rationale**: Stub explícito é melhor que ausência silenciosa. O alloy pode verificar
`kPio::kPresent == false` antes de tentar usar.

### D5 — Single-core-perspective documentado, não forçado por CI

**Decision**: O IR captura `core = "cortex-m0plus-dual"` como metadado. O emitter de
startup usa core 0 como único core ativo sem tentar sincronizar core 1. Um comentário
gerado explicitamente no `startup.cpp` documenta isso. Não há CI gate bloqueando dual-core
— o patch poderá ser expandido futuramente sem breaking change.

**Rationale**: Consistente com o tratamento do ESP32-S3 (single-core-perspective primeiro,
expansão explícita depois).

## Risks / Trade-offs

- **Boot2 placeholder**: projetos que não substituírem o `boot2` gerado por um específico
  para o flash do hardware não vão rodar. Mitigação: comentário proeminente no `startup.cpp`
  gerado e nota na documentação.
- **XIP kind novo**: se outro vendor futuro usar XIP (ex: alguns NXP com HYPER-Flash), o
  kind `xip-flash` é reusável sem mudança. Baixo risco.
- **PIO semantics stub**: a ausência de campos válidos nos traits vai gerar static_assert
  failures em qualquer código alloy que tentar usar PIO diretamente. Mitigação: o alloy
  verifica `kPresent` antes de usar; stub garante que a check é falsificável.
- **Dual-core futuro**: quando core 1 for suportado, o startup precisará de mudanças.
  O campo `core` no IR já captura `cortex-m0plus-dual`; a expansão não precisará tocar
  o schema.

## Open Questions

- Q1: O pico-sdk tem SVDs separados para RP2040 e RP2350. A source adapter deve resolver
  dinamicamente por `svd_file` no patch, ou deve ser uma lista estática por família?
  → Sugestão: lista estática igual ao padrão STM32/NXP (`svd_file` no device patch).

- Q2: O `boot2` placeholder deve ser emitido como array de zeros ou como um `__attribute__((section(".boot2"))) const uint8_t` que aponta para um símbolo fraco?
  → Símbolo fraco é mais amigável para quem usa o pico-sdk `boot_stage2` como submodule.
