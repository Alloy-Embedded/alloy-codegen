## Why

O RP2040 é o SoC mais popular da Raspberry Pi Foundation e a base do Pico, um dos boards
de desenvolvimento mais vendidos do mundo. É um Cortex-M0+ — mesma ISA que o STM32G0 já
suportado — mas tem três características únicas que pedem cuidado antes de mergear:

1. **Sem flash interno**: toda execução de firmware usa XIP (Execute in Place) via QSPI
   externo, o que muda a estrutura do linker script e do startup completamente.
2. **Pinmux por FUNCSEL**: ao invés de alternate-function numbers ARM-padrão, o RP2040
   usa registradores `IO_BANK0_GPIO<n>_CTRL.FUNCSEL` de 5 bits mapeados em uma tabela fixa.
   Precisa de um novo backend schema (`alloy.pinmux.rp2040-funcsel-v1`).
3. **PIO (Programmable I/O)**: dois blocos PIO com 4 state machines cada — periférico sem
   análogo nos vendors já suportados. Primeiro corte documenta como capability presente mas
   semanticamente não dirigida.

Do ponto de vista de admission, é o caminho mais fácil depois do G0: mesma ISA, SVD de
qualidade (BSD-3-Clause no pico-sdk oficial), e sem complexidade de multi-vendor string glue.
O dual-core é tratado como single-core-perspective no primeiro corte, com nota explícita.

## What Changes

- **New vendor**: `raspberrypi` entra em `DEVICE_REGISTRY` e `SOURCE_BUNDLES`
- **New source adapter**: `sources/pico_sdk.py` ingere o SVD publicado em
  `github.com/raspberrypi/pico-sdk` (`src/rp2040/hardware_regs/rp2040.svd`)
- **New family**: `rp2040` como bootstrap family, com device único `rp2040`
  (package `qfn56`, core `cortex-m0plus-dual`, tratado como single-core-perspective)
- **New pinmux schema**: `alloy.pinmux.rp2040-funcsel-v1` para FUNCSEL routing
- **XIP memory model**: IR passa a distinguir memória `xip-flash` (externa, `rx`) de
  `sram`; o linker script emite seções `BOOT2` e `XIP_MAIN` além do padrão
- **Startup divergence**: `startup.cpp` gerado emite inicialização de flash/XIP antes de
  copiar `.data`; `device.ld` precisa de símbolos `__boot2_start` / `__boot2_end`
- **PIO capability stub**: `capabilities.hpp` registra `runtime-support:pio` como presente;
  driver semantics de PIO fica como stub sem campos de register/field por enquanto
- **Clock topology**: clock generator blocks (ROSC, XOSC, PLL_SYS, PLL_USB, CLK_REF,
  CLK_SYS, CLK_PERI, CLK_USB, CLK_ADC) são modelados no IR com divisores fracionários
- **Runtime contract**: emite o conjunto completo padrão incluindo `systick.hpp`
  (Cortex-M0+ tem SysTick per core, core 0 é o usado)
- **CI/vendor admission**: gates passam a validar `raspberrypi/rp2040`

## Impact

- Affected specs: `vendor-admission`, `canonical-device-ir`, `artifact-contract`
- Affected code:
  - `bootstrap.py`
  - `stages/fetch.py`
  - `sources/pico_sdk.py` (novo)
  - `connector_model.py`
  - `stages/emit.py`
  - `artifact_contract.py`
  - `runtime_linker_script.py`
  - `patches/raspberrypi/rp2040/`
  - `tests/fixtures/cmsis-svd-data/` (stub SVD para testes)
  - `tests/fixtures/emitted/rp2040/`
  - `.github/workflows/publish-alloy-devices.yml`

## Non-Goals

- RP2350 (Pico 2) — chip separado, admissão futura
- Suporte full dual-core (SMP, inter-core FIFOs, spinlocks) neste corte
- PIO driver semantics completo (estado das SMs, side-set, delays)
- Wi-Fi / Bluetooth (requer CYW43439 companion chip, fora do escopo de SoC)
- Suporte a flash externo customizado além da camada XIP genérica

## Implementation Phases

| Phase | Scope | Deliverable |
|-------|-------|-------------|
| 0 | Bootstrap & source manifests | pico-sdk SVD buscado com provenance; scaffold de patches |
| 1 | IR ingestion | `CanonicalDeviceIR` válido para `rp2040` com FUNCSEL, clock e XIP |
| 2 | XIP startup & linker script | `device.ld` com BOOT2 + XIP; `startup.cpp` com flash init |
| 3 | Runtime contract | Headers runtime completos passando artifact contract gates |
| 4 | PIO capability stub | `capabilities.hpp` com `runtime-support:pio`; semantics stub |
| 5 | CI & publication gates | `raspberrypi/rp2040` no publication matrix; gates passando |
| 6 | Fixtures & docs | Goldens, licensing note, project.md atualizado |
