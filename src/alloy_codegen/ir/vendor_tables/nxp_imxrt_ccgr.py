"""NXP i.MX RT 1060 CCGR PID → peripheral mapping.

The i.MX RT clock-gate registers ``CCGR0..CCGR6`` use 16 two-bit
fields per register (one per peripheral).  Which peripheral lives
at which (ccgr, cg) slot is defined by the i.MX RT 1060 Reference
Manual §14.7.x, Table 14-5 ("Clock Gating Register Bits Mapping")
— i.e., it cannot be derived from the register/field name alone.

This module hand-curates the table.  Each row is a
``(ccgr_idx, cg_idx, peripheral_id)`` tuple.  ``peripheral_id`` is
the canonical id used by the alloy-codegen IR (e.g. ``"lpuart1"``,
``"gpio2"``, ``"tmr3"``); for shared gates (``usboh3`` covers both
``usb1`` and ``usb2``) the value is a tuple of ids.

Slots without a peripheral on the chip we admit (``mqs``,
``flexspi_exsc``, ``sim_*``, ``ipmux*``, ``trace``, ``anadig``,
infrastructure-only gates) carry the special id ``None`` so the
synthesiser silently skips them.

The :mod:`alloy_codegen.ir.synthesised.builder` reads this table in
``_synthesise_imxrt_ccgr`` and writes
``per_en[per_id] = "ccm.ccgr<N>.cg<M>"`` (no separate reset path —
i.MX RT peripherals reset via their own SOFT_RESET register, not
CCM).

Sources:
    * i.MX RT 1060 RM (IMXRT1060RM Rev 3), §14.7 "CCM Clock Gating
      Register N" + Table 14-5.
    * Cross-checked against NXP CMSIS-DEVICE_MIMXRT1062 headers
      (``MIMXRT1062.h``, ``CCGR_MASK`` macros).
"""

from __future__ import annotations

# (ccgr, cg) → peripheral_id (or tuple of ids for shared gates,
# or None for slots that don't map to any admitted peripheral).
IMXRT1060_CCGR_TABLE: dict[tuple[int, int], str | tuple[str, ...] | None] = {
    # ---- CCGR0 (0x68) -------------------------------------------------
    (0, 0): "aipstz1",            # aips_tz1 clock
    (0, 1): "aipstz2",            # aips_tz2 clock
    (0, 2): None,                 # mqs clock — no peripheral on RT1062
    (0, 3): None,                 # flexspi_exsc — RT106x only
    (0, 4): None,                 # sim_m_mainclk_r infrastructure
    (0, 5): "dcp",                # data co-processor
    (0, 6): "lpuart3",
    (0, 7): "can1",
    (0, 8): "can1",               # can1 serial — same peripheral, shared bit
    (0, 9): "can2",
    (0, 10): "can2",              # can2 serial — same peripheral
    (0, 11): None,                # trace clock
    (0, 12): "gpt2",              # gpt2 bus
    (0, 13): "gpt2",              # gpt2 serial — same peripheral
    (0, 14): "lpuart2",
    (0, 15): "gpio2",

    # ---- CCGR1 (0x6C) -------------------------------------------------
    (1, 0): "lpspi1",
    (1, 1): "lpspi2",
    (1, 2): "lpspi3",
    (1, 3): "lpspi4",
    (1, 4): "adc2",
    (1, 5): "enet",
    (1, 6): "pit",
    (1, 7): "aoi2",
    (1, 8): "adc1",
    (1, 9): None,                 # semc_exsc — bus bridge, no peripheral
    (1, 10): "gpt1",              # gpt1 bus
    (1, 11): "gpt1",              # gpt1 serial — same peripheral
    (1, 12): "lpuart4",
    (1, 13): "gpio1",
    (1, 14): "csu",
    (1, 15): "gpio5",

    # ---- CCGR2 (0x70) -------------------------------------------------
    (2, 0): None,                 # ocram_exsc
    (2, 1): "csi",
    # Bits CG2..CG5 follow the NEWER RM revision convention used by
    # the YAML inline rcc blocks: lpi2c1..3 occupy CG2..CG4 (older
    # MCUXpresso enums put them at CG3..CG5; we defer to the inline
    # paths for these three peripherals via setdefault).
    (2, 2): "lpi2c1",
    (2, 3): "lpi2c2",
    (2, 4): "lpi2c3",
    (2, 5): None,                 # reserved / iomuxc_snvs varies by RM rev
    (2, 6): "ocotp",
    (2, 7): "xbarb3",             # xbar3
    (2, 8): None,                 # ipmux1
    (2, 9): None,                 # ipmux2
    (2, 10): None,                # ipmux3
    (2, 11): "xbara1",            # xbar1
    (2, 12): "xbarb2",            # xbar2
    (2, 13): "gpio3",
    (2, 14): "lcdif",             # "lcd" in RM is lcdif
    (2, 15): "pxp",

    # ---- CCGR3 (0x74) -------------------------------------------------
    (3, 0): "flexio2",
    (3, 1): "lpuart5",
    (3, 2): "semc",
    (3, 3): "lpuart6",
    (3, 4): "aoi1",
    (3, 5): "lcdif",              # lcdif_pix — same peripheral as lcdif
    (3, 6): "gpio4",
    (3, 7): "ewm",
    (3, 8): "wdog1",
    (3, 9): "flexram",
    (3, 10): "cmp1",              # acmp1 in RM = cmp1 canonical id
    (3, 11): "cmp2",
    (3, 12): "cmp3",
    (3, 13): "cmp4",
    (3, 14): None,                # ocram
    (3, 15): "iomuxc_snvs_gpr",

    # ---- CCGR4 (0x78) -------------------------------------------------
    (4, 0): None,                 # sim_m7_clk_r — core clock, no peri
    (4, 1): "iomuxc",
    (4, 2): "iomuxc_gpr",
    (4, 3): "bee",
    (4, 4): None,                 # sim_m7
    (4, 5): "tsc",                # tsc_dig
    (4, 6): None,                 # sim_m
    (4, 7): None,                 # sim_ems
    (4, 8): "pwm1",
    (4, 9): "pwm2",
    (4, 10): "pwm3",
    (4, 11): "pwm4",
    (4, 12): "enc1",
    (4, 13): "enc2",
    (4, 14): "enc3",
    (4, 15): "enc4",

    # ---- CCGR5 (0x7C) -------------------------------------------------
    (5, 0): "romc",               # rom_clk_enable
    (5, 1): "flexio1",
    (5, 2): "rtwdog",             # wdog3 in RM is the RTWDOG block
    (5, 3): "dma0",                # dma_clk_enable (only one DMA)
    (5, 4): "kpp",
    (5, 5): "wdog2",
    (5, 6): "aipstz4",
    (5, 7): "spdif",
    (5, 8): None,                 # sim_main
    (5, 9): "sai1",
    (5, 10): "sai2",
    (5, 11): "sai3",
    (5, 12): "lpuart1",
    (5, 13): "lpuart7",
    (5, 14): "snvs",              # snvs_hp_clk_enable — covers snvs block
    (5, 15): "snvs",              # snvs_lp — same peripheral

    # ---- CCGR6 (0x80) -------------------------------------------------
    (6, 0): ("usb1", "usb2"),     # usboh3 covers BOTH OTG instances
    (6, 1): "usdhc1",
    (6, 2): "usdhc2",
    (6, 3): "dcdc",
    (6, 4): None,                 # ipmux4
    (6, 5): "flexspi",
    (6, 6): "trng",
    (6, 7): "lpuart8",
    (6, 8): "tmr4",               # timer4
    (6, 9): "aipstz3",
    (6, 10): None,                # sim_per
    (6, 11): None,                # anadig — analog infrastructure
    (6, 12): "lpi2c4",            # lpi2c4_serial — only gate for lpi2c4
    (6, 13): "tmr1",              # timer1
    (6, 14): "tmr2",              # timer2
    (6, 15): "tmr3",              # timer3

    # ---- CCGR7 (0x84) — RT1062 / RT1064 extras ------------------------
    # CCGR7 only has CG0..CG6 populated on RT1062; the rest are
    # reserved.  flexspi2 anchors here per the inline YAML.
    (7, 0): "enet2",
    (7, 1): "enet2",              # enet2 pll clock — same peripheral
    (7, 2): "can3",
    (7, 3): "flexspi2",           # confirmed via inline YAML
    (7, 4): "can3",               # can3 serial — same peripheral
    (7, 5): None,                 # reserved / axbs on RT1064
    (7, 6): "adc_etc",
}


# Family → CCGR table dispatch.  RT1064 reuses the same map (silicon
# matches the 1062 layout); future RT11xx / RT11xx will need their
# own entries.
IMXRT_CCGR_TABLES: dict[str, dict[tuple[int, int], str | tuple[str, ...] | None]] = {
    "imxrt1060": IMXRT1060_CCGR_TABLE,
}


__all__ = ["IMXRT1060_CCGR_TABLE", "IMXRT_CCGR_TABLES"]
