"""C++ compile-time invariant tests.

Drives a host C++ compiler over the ``tests/compile_tests/*.cpp`` smoke
sources, building each one against the regenerated fixtures under
``tests/fixtures/emitted/``.  When the host has no usable C++20 compiler,
each test is skipped gracefully — the goal of this harness is to upgrade
``static_assert`` coverage when CI workers (and developer machines) have
``c++`` / ``clang++`` / ``g++`` available, not to harden the unit-test
matrix against missing tooling.

Picks up the previously-deferred ``define-pio-semantic-struct`` task 5.2
plus the ``fill-gpio-semantic-gaps`` Phase A compile gate.
"""

from __future__ import annotations

import shutil
import subprocess
from pathlib import Path

import pytest

REPO_ROOT = Path(__file__).resolve().parents[1]
COMPILE_TESTS_DIR = REPO_ROOT / "tests" / "compile_tests"
FIXTURES_EMITTED = REPO_ROOT / "tests" / "fixtures" / "emitted"


def _find_cxx() -> str | None:
    for candidate in ("c++", "clang++", "g++"):
        path = shutil.which(candidate)
        if path is not None:
            return path
    return None


def _compile(*, source: Path, defines: dict[str, str], include_dirs: list[Path]) -> None:
    cxx = _find_cxx()
    if cxx is None:
        pytest.skip("no host C++ compiler available (c++/clang++/g++)")
    cmd = [cxx, "-std=c++20", "-Werror", "-Wall", "-Wextra", "-pedantic", "-c", str(source), "-o", "/dev/null"]
    for key, value in defines.items():
        cmd.append(f"-D{key}={value}")
    for include in include_dirs:
        cmd.extend(["-I", str(include)])
    completed = subprocess.run(cmd, capture_output=True, text=True, check=False)
    if completed.returncode != 0:
        pytest.fail(
            f"compile failure ({source.name}):\n"
            f"command: {' '.join(cmd)}\n"
            f"stdout: {completed.stdout}\n"
            f"stderr: {completed.stderr}"
        )


def test_rp2040_pio_traits_compile_invariants() -> None:
    """Compile-test for ``define-pio-semantic-struct`` task 5.2.

    Asserts that the regenerated rp2040 ``pio.hpp`` exposes the topology
    fields that downstream alloy concept checks rely on at compile time
    (state-machine count, instruction memory depth, base address, DREQ
    derivation).
    """
    source = COMPILE_TESTS_DIR / "test_rp2040_pio_traits.cpp"
    rp2040_root = (
        FIXTURES_EMITTED
        / "rp2040"
        / "generated"
        / "runtime"
        / "devices"
        / "rp2040"
        / "driver_semantics"
    )
    pio_header = rp2040_root / "pio.hpp"
    assert pio_header.exists(), pio_header
    # The pio.hpp `#include "common.hpp"` references the per-device sibling.
    common_header = rp2040_root / "common.hpp"
    if not common_header.exists():
        # Generate a minimal common.hpp shim so the include resolves; the smoke
        # only references types declared inline in pio.hpp itself.
        common_header.write_text(
            "#pragma once\n",
            encoding="utf-8",
        )
    _compile(
        source=source,
        defines={"ALLOY_CODEGEN_RP2040_PIO_HEADER": f'"{pio_header}"'},
        include_dirs=[rp2040_root],
    )


def test_rp2040_peripheral_traits_compile_invariants() -> None:
    """Aggregated compile-test for ``complete-rp2040-semantics`` Phases A–D.

    Asserts the new RP2040 trait specializations compile and carry the
    documented constants — GPIO FUNCSEL set, UART/SPI base addresses +
    pin sets + DREQs, ADC channel mapping (incl. sentinel 255 for the
    internal temperature sensor), and DMA / Timer / PWM HW topology.
    """
    source = COMPILE_TESTS_DIR / "test_rp2040_peripheral_traits.cpp"
    rp2040_root = (
        FIXTURES_EMITTED
        / "rp2040"
        / "generated"
        / "runtime"
        / "devices"
        / "rp2040"
    )
    driver_root = rp2040_root / "driver_semantics"
    headers = {
        "ALLOY_CODEGEN_RP2040_GPIO_HEADER":  driver_root / "gpio.hpp",
        "ALLOY_CODEGEN_RP2040_UART_HEADER":  driver_root / "uart.hpp",
        "ALLOY_CODEGEN_RP2040_SPI_HEADER":   driver_root / "spi.hpp",
        "ALLOY_CODEGEN_RP2040_ADC_HEADER":   driver_root / "adc.hpp",
        "ALLOY_CODEGEN_RP2040_TIMER_HEADER": driver_root / "timer.hpp",
        "ALLOY_CODEGEN_RP2040_PWM_HEADER":   driver_root / "pwm.hpp",
        "ALLOY_CODEGEN_RP2040_DMA_HEADER":   driver_root / "dma.hpp",
    }
    for path in headers.values():
        assert path.exists(), path
    common_header = driver_root / "common.hpp"
    if not common_header.exists():
        common_header.write_text("#pragma once\n", encoding="utf-8")
    _compile(
        source=source,
        defines={key: f'"{path}"' for key, path in headers.items()},
        include_dirs=[driver_root, rp2040_root],
    )


def test_stm32g0_gpio_traits_compile_invariants() -> None:
    """Compile-test for ``fill-gpio-semantic-gaps`` Phase A.

    Asserts the four new AF fields (``kPortOffset``, ``kPinIndex``,
    ``kMaxAltFunction``, ``kValidAltFunctions``) plus ``kIsInputOnly``
    are visible at compile time for the populated stm32g071rb fixture.
    """
    source = COMPILE_TESTS_DIR / "test_stm32g0_gpio_traits.cpp"
    stm32g0_root = (
        FIXTURES_EMITTED
        / "stm32g0"
        / "generated"
        / "runtime"
        / "devices"
        / "stm32g071rb"
    )
    driver_root = stm32g0_root / "driver_semantics"
    gpio_header = driver_root / "gpio.hpp"
    pins_header = stm32g0_root / "pins.hpp"
    assert gpio_header.exists(), gpio_header
    assert pins_header.exists(), pins_header
    common_header = driver_root / "common.hpp"
    if not common_header.exists():
        common_header.write_text("#pragma once\n", encoding="utf-8")
    _compile(
        source=source,
        defines={
            "ALLOY_CODEGEN_STM32G0_GPIO_HEADER": f'"{gpio_header}"',
            "ALLOY_CODEGEN_STM32G0_PINS_HEADER": f'"{pins_header}"',
        },
        include_dirs=[driver_root, stm32g0_root],
    )
