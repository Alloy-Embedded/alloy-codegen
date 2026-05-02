"""Microchip SAM family GCLK kernel-clock-mux index tables.

The Microchip SAMD21 / SAMD51 / SAML21 / SAML22 families gate each
peripheral's *kernel clock* via a single GCLK register array
(``GCLK->PCHCTRL[N]`` on D51/L21/L22, ``GCLK->CLKCTRL`` with an ``ID``
field on D21).  The mapping ``peripheral_id → channel_index N`` is
chip-specific (driven by the silicon's interrupt vector layout) and
not derivable from the template fields alone — the template carries
only the *shape* of the register, not the per-channel binding.

This module hand-curates the per-chip index tables, sourced from the
SAMD21 / SAMD51 / SAML21 datasheets (Section 15 / 19 "GCLK – Generic
Clock Generator").  The synthesiser reads the table and writes
``extra["clock_sel"] = "gclk.pchctrl<N>.gen"`` (D51/L21/L22) or
``extra["clock_sel"] = "gclk.clkctrl.id<N>"`` (D21) on every
peripheral instance with a kernel clock channel.

Reference manuals consulted:
    * SAMD21 datasheet (Atmel-42181) §15.8.4 "GCLK_PCHCTRL — Peripheral
      Channel Control" (table of ID values).
    * SAMD51 datasheet (DS60001507) §15.8.5 (same table, renamed
      ``PCHCTRL[n]``).
    * SAML21 datasheet (DS60001477) §17.7.x.
"""

from __future__ import annotations


# ----------------------------------------------------------------------
# SAMD21 — single ``CLKCTRL`` register with a 6-bit ``ID`` field.
# Each peripheral channel is selected by writing ``CLKCTRL.ID = N``
# before ``CLKCTRL.GEN`` is set.  We model this as
# ``gclk.clkctrl.id<N>`` for path uniformity with the array-style
# variants on later chips.
# ----------------------------------------------------------------------

# Peripheral id → CLKCTRL ID value (from SAMD21 datasheet table 15-3).
SAMD21_CLKCTRL_IDS: dict[str, int] = {
    # 0..2: DFLL/DPLL — internal to sysctrl, no per-peri channel.
    "wdt": 3,
    "rtc": 4,
    "eic": 5,
    "usb": 6,
    # 7..18: EVSYS channels 0..11 — handled by the EVSYS driver
    # itself, not a peripheral kernel-clock entry.
    "sercom0": 20,   # SERCOM0_CORE
    "sercom1": 21,
    "sercom2": 22,
    "sercom3": 23,
    "sercom4": 24,
    "sercom5": 25,
    "tcc0": 26,
    "tcc1": 26,      # TCC0_TCC1 — same channel
    "tcc2": 27,
    "tc3": 27,       # TCC2_TC3
    "tc4": 28,
    "tc5": 28,       # TC4_TC5
    "tc6": 29,
    "tc7": 29,       # TC6_TC7
    "adc": 30,
    "ac": 31,        # AC_DIG (digital side)
    "dac": 33,
    "i2s": 35,       # I2S channel 0 (channel 1 is at id 36)
}


# ----------------------------------------------------------------------
# SAMD51 — array-style ``PCHCTRL[N]`` register, with N defined by the
# datasheet table 15-2 "PCHCTRL Mapping".
# ----------------------------------------------------------------------

# Common PCHCTRL indices shared across the SAMD51 family.  Variant-
# specific indices (USB, SDHC, GMAC etc.) layered on top in subset
# tables below.
SAMD51_PCHCTRL_IDS: dict[str, int] = {
    "osc32kctrl": 0,    # OSCCTRL_DFLL48
    "oscctrl": 1,       # OSCCTRL_FDPLL0
    # 2 -> OSCCTRL_FDPLL1 (same peri)
    # 3 -> OSCCTRL_FDPLL0_32K, 4 -> FDPLL1_32K (sub-channels)
    "eic": 4,
    "freqm": 5,         # FREQM_MSR (then 6 = FREQM_REF)
    "sercom0": 7,
    "sercom1": 8,
    "tc0": 9,
    "tc1": 9,           # TC0_TC1
    "usb": 10,
    "evsys": 11,        # base channel (0..11 are 11 sub-channels)
    "sercom2": 23,
    "sercom3": 24,
    "tcc0": 25,
    "tcc1": 25,         # TCC0_TCC1
    "tc2": 26,
    "tc3": 26,          # TC2_TC3
    "can0": 27,
    "can1": 28,
    "tcc2": 29,
    "tcc3": 29,         # TCC2_TCC3
    "tc4": 30,
    "tc5": 30,          # TC4_TC5
    "pdec": 31,
    "ac": 32,
    "ccl": 33,
    "sercom4": 34,
    "sercom5": 35,
    "sercom6": 36,
    "sercom7": 37,
    "tcc4": 38,
    "tc6": 39,
    "tc7": 39,          # TC6_TC7
    "adc0": 40,
    "adc1": 41,
    "dac": 42,
    "i2s": 43,          # I2S channel 0; ch1 at 44
    "sdhc0": 45,
    "sdhc1": 46,
    "cm4_trace": 47,    # CM4_TRACE
}


# ----------------------------------------------------------------------
# SAML21 — array-style ``PCHCTRL[N]`` like SAMD51 but with a smaller
# peripheral set.  Indices from SAML21 datasheet table 17-3.
# ----------------------------------------------------------------------

SAML21_PCHCTRL_IDS: dict[str, int] = {
    "oscctrl": 0,       # DFLL48
    # 1 -> FDPLL96M, 2 -> FDPLL96M_32K (sub-channels)
    "wdt": 3,
    "rtc": 4,
    "eic": 5,
    "usb": 6,
    "evsys": 7,         # 11 channels: 7..17
    "sercom0": 18,      # SERCOMx_SLOW shared (18); CORE at 19+
    "sercom1": 20,
    "sercom2": 21,
    "sercom3": 22,
    "sercom4": 23,
    "sercom5": 24,
    "tcc0": 25,
    "tcc1": 25,         # TCC0_TCC1
    "tcc2": 26,
    "tc0": 27,          # TC0_TC1 -- mapped to TC0
    "tc1": 27,
    "tc2": 28,          # TC2_TC3
    "tc3": 28,
    "tc4": 29,
    "adc": 30,
    "ac": 31,
    "dac": 32,
    "ptc": 33,
    "ccl": 34,
}


# ----------------------------------------------------------------------
# SAML22 — almost identical to SAML21 but without USB / DAC / CCL.
# ----------------------------------------------------------------------

SAML22_PCHCTRL_IDS: dict[str, int] = {
    "oscctrl": 0,
    "wdt": 3,
    "rtc": 4,
    "eic": 5,
    "evsys": 7,
    "sercom0": 18,
    "sercom1": 20,
    "sercom2": 21,
    "sercom3": 22,
    "sercom4": 23,
    "sercom5": 24,
    "tcc0": 25,
    "tc0": 27,
    "tc1": 27,
    "tc2": 28,
    "tc3": 28,
    "adc": 30,
    "ac": 31,
}


# ----------------------------------------------------------------------
# Family → (id_table, register_path_template) dispatch.
# ----------------------------------------------------------------------

# Each entry maps a family to the per-peri index table and the
# template string used to format the resulting ``clock_sel`` path.
SAM_GCLK_TABLES: dict[str, tuple[dict[str, int], str]] = {
    "samd21": (SAMD21_CLKCTRL_IDS, "gclk.clkctrl.id{n}"),
    "samd51": (SAMD51_PCHCTRL_IDS, "gclk.pchctrl{n}.gen"),
    "saml21": (SAML21_PCHCTRL_IDS, "gclk.pchctrl{n}.gen"),
    "saml22": (SAML22_PCHCTRL_IDS, "gclk.pchctrl{n}.gen"),
}


__all__ = [
    "SAMD21_CLKCTRL_IDS",
    "SAMD51_PCHCTRL_IDS",
    "SAML21_PCHCTRL_IDS",
    "SAML22_PCHCTRL_IDS",
    "SAM_GCLK_TABLES",
]
