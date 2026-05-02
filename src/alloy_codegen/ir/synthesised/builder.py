"""Build :class:`SynthesisedDevice` from a v2.1 :class:`CanonicalDevice`.

Synthesis rules:

* For every peripheral with ``rcc.en`` set, emit one ``set-bit``
  :class:`RouteOperation` targeting a synthetic clock-gate id.
* For every peripheral with ``rcc.rst`` set, emit one ``clear-bit``
  ``RouteOperation`` targeting a synthetic reset id.
* For every peripheral with one or more IRQ slots, emit one
  :class:`InterruptBinding` per ``(peripheral, irq)`` pair.
* For every IRQ in the top-level ``interrupts:`` vector list, emit one
  :class:`VectorSlot` ``kind="peripheral-irq"``.  System exceptions
  (``__vector_default``, ``Reset_Handler``, etc.) get
  ``kind="reset"`` / ``"system-exception"`` instead.
* For every peripheral signal in ``pin_options``, emit one
  :class:`SignalEndpoint`.

Determinism: builds run in source order (peripheral declaration order
in the YAML, signal order inside ``pin_options``).  No sorting; the
order is the same on every machine.
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised.clock_program import ClockProgramStep
from alloy_codegen.ir.synthesised.device import SynthesisedDevice
from alloy_codegen.ir.synthesised.endpoints import SignalEndpoint
from alloy_codegen.ir.synthesised.interrupts import (
    InterruptBinding,
    VectorSlot,
)
from alloy_codegen.ir.synthesised.pin_routes import PinRoute
from alloy_codegen.ir.synthesised.route_operations import RouteOperation
from alloy_codegen.ir.v2_1 import (
    CanonicalDevice,
    InterruptMatrix,
    InterruptVector,
    PeripheralInstance,
    PeripheralRcc,
)
from alloy_codegen.ir.vendor_tables.espressif_clock_gates import (
    ESPRESSIF_CHIP_GATES,
    ESPRESSIF_PCR_FAMILIES,
    PCR_FIELD_CLK_PATTERN,
    PCR_FIELD_RST_PATTERN,
    PCR_REGISTER_PATTERN,
)
from alloy_codegen.ir.vendor_tables.microchip_sam_gclk import SAM_GCLK_TABLES
from alloy_codegen.ir.vendor_tables.nxp_imxrt_ccgr import IMXRT_CCGR_TABLES

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


def _bus_from_reg(reg: str) -> str | None:
    """Infer APB/AHB bus domain from an RCC register name.

    Handles two STM32 naming conventions:
      * G0 / G4 / H7 style: ``apbenr1``, ``apbrstr2``   (suffix digit)
      * F4 / F1 style:      ``apb1enr``, ``apb2rstr``   (infix digit)
    """
    import re as _re

    r = reg.lower()
    if "ahb" in r:
        return "AHB"
    # F4/F1: digit immediately after "apb" — e.g. apb2enr, apb1rstr
    m = _re.search(r"apb([12])", r)
    if m:
        return f"APB{m.group(1)}"
    # G0/G4/H7: digit at the end — e.g. apbenr1, apbrstr2, apbsmenr1
    m = _re.search(r"apb.*?([12])$", r)
    if m:
        return f"APB{m.group(1)}"
    if "apb" in r:
        return "APB"
    # G0/G4 dedicated GPIO enable register (IOPENR / IOPRSTR) is on AHB.
    # Must be checked before the generic "iop" fallback below.
    if "iopenr" in r or "ioprstr" in r:
        return "AHB"
    if "iop" in r:  # STM32 F1 legacy: IOPx gate is in APB2ENR
        return "APB2"
    return None


def _expand_grouped_peri_ids(token: str, valid_per_ids: set[str]) -> list[str]:
    """Expand a kernel-clock-mux token into the list of peripheral ids
    it covers, using ``valid_per_ids`` to disambiguate single-vs-compound.

    The disambiguator is straightforward: if ``token`` itself names a
    peripheral on this chip, treat it as a singleton.  Only otherwise
    attempt to split it into per-instance ids of the form ``<prefix><n>``.

    Examples (assuming chip has tim1, tim15, spi1, spi2, spi3, sai2, sai3):

      * ``"tim15"``      → ``["tim15"]``                   (token IS valid)
      * ``"tim1"``       → ``["tim1"]``                    (token IS valid)
      * ``"spi123"``     → ``["spi1", "spi2", "spi3"]``    (token NOT valid, split)
      * ``"sai23"``      → ``["sai2", "sai3"]``            (token NOT valid, split)
      * ``"adc"``        → ``["adc"]``                     (no digit suffix)
      * ``"usart234578"``→ ``["usart2","usart3","usart4","usart5","usart7","usart8"]``

    Used by the H7-style ``d2ccip1r.spi123src`` / ``d3ccipr.lptim345src``
    kernel-clock-mux convention where a single field controls multiple
    peripheral instances of the same template.  The split-result is
    further filtered against ``valid_per_ids`` by the caller, so a
    grouped token on a chip missing one of the instances (e.g.
    ``usart234578src`` on a chip with usart2/3/6 only) only links the
    instances actually present.
    """
    import re as _re

    if token in valid_per_ids:
        return [token]
    m = _re.match(r"^([a-z]+)(\d+)$", token)
    if m is None:
        return [token]
    prefix, digits = m.group(1), m.group(2)
    if len(digits) <= 1:
        return [token]
    return [f"{prefix}{d}" for d in digits]


def _build_rcc_lookup(device: CanonicalDevice) -> dict[str, PeripheralRcc]:
    """Cross-link clock-gate / reset / kernel-clock-mux template fields
    to peripheral IDs.

    Returns a map from peripheral_id → :class:`PeripheralRcc`.

    Two vendor conventions are handled:

    **STM32 ('rcc' template)** — fields shaped like
      * **enable:**     ``{reg}.{peripheral_id}en``   (excl. ``smen``/``rdy``)
      * **reset:**      ``{reg}.{peripheral_id}rst``
      * **clock-mux:**  one of
          - ``ccipr*.{peripheral_id}sel``         (G0 / G4 style)
          - ``*ccip*.{peripheral_id}src``         (H7 style, may be grouped:
              ``i2c123src`` → ``i2c1``, ``i2c2``, ``i2c3``)
          - ``dckcfgr*.{peripheral_id}sel|src``   (F4 style)

    **RP2040 ('resets' + 'clocks' templates)** — fields shaped like
      * **reset:**      ``reset.{peripheral_id}``  (also doubles as enable —
        RP2040 has no separate clock-gate; releasing reset implicitly
        enables the peripheral, so we mirror the same path into ``en``)
      * **clock-mux:**  ``clk_{peripheral_id}_ctrl.auxsrc``  (only present
        for the small set of peripherals with a dedicated kernel clock:
        adc, peri, usb, rtc, ref, sys)

    The ``extra`` dict on each PeripheralRcc carries:
      * ``"bus"``       — inferred bus domain string (APB1, APB2, AHB…),
                          empty for vendors without explicit bus tagging.
      * ``"clock_sel"`` — dotted path for kernel-clock mux field.
    """
    templates = device.templates or {}
    valid_per_ids: set[str] = {per.id for per in device.peripherals}

    per_en: dict[str, str] = {}  # per_id → "rcc.reg.field"
    per_rst: dict[str, str] = {}
    per_sel: dict[str, str] = {}
    # Per-peripheral bus tag from non-STM32 vendors (DPORT / SYSTEM /
    # PCR on Espressif, etc.).  STM32 derives bus from register name
    # via ``_bus_from_reg`` at assembly time, so STM32 entries are
    # absent from this map.
    per_bus: dict[str, str] = {}

    # ----- STM32 'rcc' template -----------------------------------------
    rcc_template = templates.get("rcc")
    if rcc_template is not None:
        for field_key in rcc_template.fields:
            parts = field_key.split(".", 1)
            if len(parts) != 2:
                continue
            reg, fld = parts
            reg_lower = reg.lower()

            # Enable: ends with "en" — exclude sleep-mode ("smen") and
            # ready-flag ("rdy") fields which have the same suffix.
            if (
                fld.endswith("en")
                and not fld.endswith("smen")
                and not fld.endswith("rdy")
                and not fld.endswith("cen")
            ):  # "lscoen" etc. are not peri enables
                per_id = fld[:-2]
                per_en[per_id] = f"rcc.{field_key}"
                continue

            # Reset: ends with "rst"
            if fld.endswith("rst"):
                per_id = fld[:-3]
                per_rst[per_id] = f"rcc.{field_key}"
                continue

            # Kernel-clock mux on a CCIPR-style register.  Two suffix
            # conventions exist: G0/G4 use "sel", H7 uses "src".
            # F4's DCKCFGR* uses "src" too on a non-CCIPR register.
            is_ccipr_like = "ccip" in reg_lower or reg_lower.startswith("dckcfgr")
            if is_ccipr_like:
                for suffix in ("sel", "src"):
                    if fld.endswith(suffix):
                        token = fld[: -len(suffix)]
                        for per_id in _expand_grouped_peri_ids(token, valid_per_ids):
                            if per_id in valid_per_ids:
                                per_sel[per_id] = f"rcc.{field_key}"
                        break

    # ----- STM32 GPIO naming alias (G0/F1/F3: iopaen → gpioa) ----------------
    # Several STM32 families name GPIO clock-gate fields with the legacy "IOP"
    # prefix (iopaen, iopben …) while the SVD peripheral id uses "gpio"
    # (gpioa, gpiob …).  Build aliases before final assembly so the map can
    # be looked up by the canonical peripheral id.
    # Match pattern: after stripping "en"/"rst" suffix the result is "iop" +
    # exactly one port letter → 4 chars total.
    for _iop_id, _en_path in list(per_en.items()):
        if len(_iop_id) == 4 and _iop_id.startswith("iop"):
            _gpio_id = "gpio" + _iop_id[3]  # "iopa" → "gpioa"
            if _gpio_id in valid_per_ids and _gpio_id not in per_en:
                per_en[_gpio_id] = _en_path
    for _iop_id, _rst_path in list(per_rst.items()):
        if len(_iop_id) == 4 and _iop_id.startswith("iop"):
            _gpio_id = "gpio" + _iop_id[3]
            if _gpio_id in valid_per_ids and _gpio_id not in per_rst:
                per_rst[_gpio_id] = _rst_path

    # ----- RP2040 'resets' template ------------------------------------
    # On RP2040 the only per-peripheral gate is the reset bit in
    # RESETS.RESET; releasing the bit implicitly enables the
    # peripheral.  We mirror the same dotted path into ``en`` so the
    # alloy HAL can treat ``kRccEnable`` and ``kRccReset`` uniformly
    # across vendors (the same write toggles both).
    resets_template = templates.get("resets")
    if resets_template is not None:
        for field_key in resets_template.fields:
            parts = field_key.split(".", 1)
            if len(parts) != 2:
                continue
            reg, fld = parts
            if reg.lower() != "reset":
                continue  # ignore reset_done / wdsel mirror registers
            per_id = fld
            if per_id not in valid_per_ids:
                continue
            path = f"resets.{field_key}"
            # Don't clobber an inline ``en`` already declared on the
            # peripheral or a more-specific entry from another template
            # (per.rcc is consulted later as the primary source of truth).
            per_en.setdefault(per_id, path)
            per_rst.setdefault(per_id, path)

    # ----- RP2040 'clocks' template (kernel-clock muxes) ---------------
    # Fields like ``clk_adc_ctrl.auxsrc`` carry the kernel-clock
    # source-mux for the small set of RP2040 peripherals with a
    # dedicated clock domain (adc, peri, usb, rtc, ref, sys).  Map
    # them onto kKernelClockMux just like a CCIPR ``sel`` on STM32.
    clocks_template = templates.get("clocks")
    if clocks_template is not None:
        import re as _re

        for field_key in clocks_template.fields:
            parts = field_key.split(".", 1)
            if len(parts) != 2:
                continue
            reg, fld = parts
            if fld != "auxsrc":
                continue
            m = _re.match(r"^clk_(\w+)_ctrl$", reg)
            if m is None:
                continue
            per_id = m.group(1)
            if per_id in valid_per_ids:
                per_sel[per_id] = f"clocks.{field_key}"

    # ----- Microchip SAMx 'mclk' / 'pm' template -----------------------
    # SAMD21 ('pm'), SAMD51 / SAML21 / SAML22 ('mclk') peripherals are
    # gated by per-bus mask registers: ``ahbmask.<peri>_``,
    # ``apbamask.<peri>_``, ``apbbmask.<peri>_``, ``apbcmask.<peri>_``,
    # ``apbdmask.<peri>_``, ``apbemask.<peri>_``.  The trailing ``_``
    # is part of the ATDF field name, not a separator.  No per-peri
    # reset bit on this family — the peripheral's own ``CTRLA.SWRST``
    # does software reset.
    for sam_clock_template in ("mclk", "pm"):
        sam_template = templates.get(sam_clock_template)
        if sam_template is None:
            continue
        import re as _re

        for field_key in sam_template.fields:
            parts = field_key.split(".", 1)
            if len(parts) != 2:
                continue
            reg, fld = parts
            m = _re.match(r"^(ahb|apb[a-e])mask$", reg.lower())
            if m is None:
                continue
            # ``apbamask.hpb0_`` / ``ahbmask.hpb0_`` are bus-bridge gates,
            # not per-peripheral; skip them.  ``pac0_/pac1_/pac2_`` on
            # SAMD21 are bridge-protection slots (not the ``pac``
            # peripheral), filter via the valid_per_ids check below.
            per_id = fld.rstrip("_")
            if per_id.startswith("hpb") or per_id in {"hsram", "lpram"}:
                continue
            if per_id not in valid_per_ids:
                continue
            per_en[per_id] = f"{sam_clock_template}.{field_key}"

    # ----- Microchip SAM (SAME70/SAMV71) 'pmc' template ----------------
    # The Atmel SAM family uses the Power Management Controller's
    # Peripheral Clock Enable Register (PCERn) to gate peripherals,
    # but the bits are PID-indexed: ``pmc_pcer0.pid7`` enables the
    # peripheral that occupies PID slot 7 (which the chip's interrupt
    # vector list maps to UART0).  Cross-link by reading each
    # peripheral's first IRQ vector number and treating it as the PID.
    pmc_template = templates.get("pmc")
    if pmc_template is not None:
        # Build the set of PID fields actually present on the chip so
        # we don't synth gates for peripherals whose PID is reserved.
        pcer_fields: dict[int, str] = {}  # pid → "pmc.pmc_pcerN.pidP"
        pcdr_fields: dict[int, str] = {}  # pid → "pmc.pmc_pcdrN.pidP"
        import re as _re

        for field_key in pmc_template.fields:
            parts = field_key.split(".", 1)
            if len(parts) != 2:
                continue
            reg, fld = parts
            m = _re.match(r"^pid(\d+)$", fld)
            if m is None:
                continue
            pid = int(m.group(1))
            if reg.lower().startswith("pmc_pcer"):
                pcer_fields[pid] = f"pmc.{field_key}"
            elif reg.lower().startswith("pmc_pcdr"):
                pcdr_fields[pid] = f"pmc.{field_key}"

        for per in device.peripherals:
            if not per.irq:
                continue
            pid = per.irq[0].num
            if pid in pcer_fields and per.id in valid_per_ids:
                per_en[per.id] = pcer_fields[pid]
            # PMC has no per-peripheral *reset* register on SAM —
            # peripherals reset via their own CTRLA.SWRST (mirror of
            # the SAMD51/SAML21 model).  Don't synth a reset path.

    # ----- NXP iMXRT 'ccm' template (named kernel-clock muxes) ---------
    # iMXRT CCGR clock-gates are index-based (CCGR0.CG5 means "the
    # peripheral the reference manual table maps to that bit") and
    # require a hand-curated table — they're already populated for
    # ~23 peripherals via the YAML's per-peripheral inline ``rcc:``
    # block, and remain there as the source of truth for now.
    #
    # The kernel-clock muxes inside CCM, however, embed the peripheral
    # name explicitly: ``cscmr1.sai1_clk_sel``, ``cscmr2.can_clk_sel``,
    # ``cdcdr.flexio1_clk_sel`` — extractable cleanly.  Recognise
    # ``<reg>.<peri>_clk_sel`` on cscmr*/cdcdr/cs[12]cdr and link.
    ccm_template = templates.get("ccm")
    if ccm_template is not None:
        import re as _re

        for field_key in ccm_template.fields:
            parts = field_key.split(".", 1)
            if len(parts) != 2:
                continue
            reg, fld = parts
            reg_lower = reg.lower()
            if not (
                reg_lower.startswith("cscmr")
                or reg_lower.startswith("cdcdr")
                or reg_lower.startswith("cs1cdr")
                or reg_lower.startswith("cs2cdr")
            ):
                continue
            m = _re.match(r"^(\w+)_clk_sel$", fld)
            if m is None:
                continue
            per_id = m.group(1)
            if per_id in valid_per_ids:
                per_sel[per_id] = f"ccm.{field_key}"

    # ----- Microchip SAMx GCLK kernel-clock-mux ------------------------
    # SAMD21 (CLKCTRL) and SAMD51/SAML21/SAML22 (PCHCTRL[N]) gate
    # each peripheral's *kernel clock* through the GCLK module.  The
    # peripheral → channel-index map is chip-specific and lives in
    # ``alloy_codegen.ir.vendor_tables.microchip_sam_gclk``; this
    # branch reads the right table by family and writes the
    # ``extra["clock_sel"]`` entry every peripheral in the table.
    if device.identity.family in SAM_GCLK_TABLES:
        sam_id_table, sam_path_tmpl = SAM_GCLK_TABLES[device.identity.family]
        for per_id, channel_idx in sam_id_table.items():
            if per_id not in valid_per_ids:
                continue
            per_sel[per_id] = sam_path_tmpl.format(n=channel_idx)

    # ----- NXP iMXRT CCGR PID table -----------------------------------
    # CCGR0..CCGR6 carry 16 two-bit gate fields each; the (ccgr, cg)
    # → peripheral mapping is defined by the i.MX RT 1060 RM Table
    # 14-5 and lives in ``alloy_codegen.ir.vendor_tables.nxp_imxrt_ccgr``.
    # The CCGR has no separate reset bits (peripherals reset via
    # their own SOFT_RESET register), so we only populate ``en``.
    # Bus tag: ``"CCGR"`` (a synthetic bus name used by the alloy
    # HAL to dispatch to the index-based gate path).
    if device.identity.family in IMXRT_CCGR_TABLES:
        ccgr_table = IMXRT_CCGR_TABLES[device.identity.family]
        for (ccgr_idx, cg_idx), peri_or_tuple in ccgr_table.items():
            if peri_or_tuple is None:
                continue  # slot doesn't map to any admitted peripheral
            path = f"ccm.ccgr{ccgr_idx}.cg{cg_idx}"
            if isinstance(peri_or_tuple, str):
                candidates: tuple[str, ...] = (peri_or_tuple,)
            else:
                candidates = peri_or_tuple
            for per_id in candidates:
                if per_id not in valid_per_ids:
                    continue
                # Don't shadow inline ``rcc:`` blocks already on
                # the YAML; setdefault preserves the YAML's
                # original path while still picking up CCGR for
                # the ~80 peripherals without inline gates.
                per_en.setdefault(per_id, path)
                per_bus[per_id] = "CCGR"

    # ----- Espressif ESP32 / C3 / S3 (DPORT / SYSTEM / PCR) -----------
    # Three Espressif generations, each with its own clock-gate
    # convention.  The vendor table at
    # ``alloy_codegen.ir.vendor_tables.espressif_clock_gates`` carries
    # the per-chip register groups + alias maps; this branch walks
    # them and writes the ``en`` / ``rst`` paths plus the bus tag.
    family = device.identity.family
    chip_id = device.identity.device
    chip_configs = ESPRESSIF_CHIP_GATES.get((family, chip_id), ())
    for cfg in chip_configs:
        tmpl = templates.get(cfg.template)
        if tmpl is None:
            continue
        for group in cfg.groups:
            # Build the (register → field-id-list) index for this group.
            for field_key in tmpl.fields:
                parts = field_key.split(".", 1)
                if len(parts) != 2:
                    continue
                reg, fld = parts
                # Match the field to either the enable or reset
                # register/suffix combination of this group.
                target: dict[str, str] | None = None
                stem: str | None = None
                if reg == group.en_register and not group.prefix_form and fld.endswith(group.en_suffix):
                    target = per_en
                    stem = fld[: -len(group.en_suffix)]
                elif reg == group.rst_register and not group.prefix_form and fld.endswith(group.rst_suffix):
                    target = per_rst
                    stem = fld[: -len(group.rst_suffix)]
                elif reg == group.en_register and group.prefix_form and fld.startswith(group.en_suffix):
                    target = per_en
                    stem = fld[len(group.en_suffix):]
                elif reg == group.rst_register and group.prefix_form and fld.startswith(group.rst_suffix):
                    target = per_rst
                    stem = fld[len(group.rst_suffix):]
                if target is None or stem is None:
                    continue
                if stem in cfg.skip:
                    continue
                # Resolve stem → peripheral id(s) via the alias map
                # (or default to the stem itself).
                resolved = cfg.aliases.get(stem, stem)
                if isinstance(resolved, str):
                    candidates: tuple[str, ...] = (resolved,)
                else:
                    candidates = tuple(resolved)
                path = f"{cfg.template}.{field_key}"
                for per_id in candidates:
                    if per_id not in valid_per_ids:
                        continue
                    if target is per_en:
                        per_en.setdefault(per_id, path)
                    else:
                        per_rst.setdefault(per_id, path)
                    per_bus[per_id] = cfg.bus

    # PCR self-contained group (ESP32-C3 / S3): gates live inside the
    # peripheral's own ``<peri>_conf{,0}_reg`` register.  Field
    # discovery is regex-driven against the ``pcr`` template.
    if family in ESPRESSIF_PCR_FAMILIES:
        pcr_template = templates.get("pcr")
        if pcr_template is not None:
            import re as _re

            for field_key in pcr_template.fields:
                parts = field_key.split(".", 1)
                if len(parts) != 2:
                    continue
                reg, fld = parts
                reg_match = _re.match(PCR_REGISTER_PATTERN, reg)
                if reg_match is None:
                    continue
                reg_peri = reg_match.group("peri")
                # The field name carries its own ``<peri>_clk_en``
                # / ``<peri>_rst_en`` so cross-validate that the
                # field's peripheral matches the register's.
                clk_match = _re.match(PCR_FIELD_CLK_PATTERN, fld)
                rst_match = _re.match(PCR_FIELD_RST_PATTERN, fld)
                target = None
                fld_peri = None
                if clk_match is not None:
                    target = per_en
                    fld_peri = clk_match.group("peri")
                elif rst_match is not None:
                    target = per_rst
                    fld_peri = rst_match.group("peri")
                if target is None or fld_peri is None:
                    continue
                # Trust the register name as the canonical id (UART
                # uses ``uart0_conf0_reg`` so the field-side stem may
                # carry the ``0`` while the register stem already
                # includes it).
                per_id = reg_peri
                if per_id not in valid_per_ids:
                    continue
                path = f"pcr.{field_key}"
                # PCR overrides any earlier SYSTEM-template gate: on
                # ESP32-C3 / S3 the PCR ``<peri>_conf_reg`` is the
                # per-peripheral primary clock-gate; the SYSTEM
                # ``perip_clk_en*.<peri>_clk_en`` field is a legacy
                # mirror.  HAL drivers MUST write PCR for run-mode
                # gating, so the synthesised entry promotes it.
                if target is per_en:
                    per_en[per_id] = path
                else:
                    per_rst[per_id] = path
                per_bus[per_id] = "PCR"

    # ----- assemble the final PeripheralRcc map ------------------------
    # Include peripherals that have ONLY a kernel-clock mux (no enable
    # or reset bit in the templates) — without ``per_sel`` in the union
    # iMXRT's sai1 / can1 etc. would lose their kKernelClockMux just
    # because the CCGR clock-gate table isn't extracted yet.
    all_ids = set(per_en) | set(per_rst) | set(per_sel) | set(per_bus)
    result: dict[str, PeripheralRcc] = {}
    for per_id in all_ids:
        extra: dict[str, object] = {}
        en_path = per_en.get(per_id, "")
        # Bus inference applies only to STM32 ``rcc.`` paths — RP2040's
        # ``resets.`` paths don't carry an APB/AHB domain.
        if en_path.startswith("rcc."):
            bus_reg = en_path.split(".")[1] if en_path else ""
            bus = _bus_from_reg(bus_reg) if bus_reg else None
            if bus:
                extra["bus"] = bus
        # Non-STM32 vendors set their bus tag explicitly during
        # template-walk (DPORT / SYSTEM / PCR for Espressif, etc.).
        if per_id in per_bus:
            extra["bus"] = per_bus[per_id]
        if per_id in per_sel:
            extra["clock_sel"] = per_sel[per_id]
        # Derive ``gate_model`` from the synthesised path shape.
        # Closed five-value enum: always_on / per_peri_en /
        # per_peri_en_rst / index_based / per_peri_pcr.  HAL drivers
        # ``constexpr if`` on this to short-circuit the gate-write
        # path on always-on silicon, dispatch to index-parsing for
        # CCGR-style gates, etc.
        en = per_en.get(per_id)
        rst = per_rst.get(per_id)
        gate_model = _derive_gate_model(en, rst, per_bus.get(per_id))
        if gate_model is not None:
            extra["gate_model"] = gate_model
        result[per_id] = PeripheralRcc(en=en, rst=rst, extra=extra)

    # ----- always-on marker pass for vendors with no per-peri gate ----
    # AVR-Dx and Nordic NRF52 silicon have NO per-peripheral clock
    # gate — peripherals are clocked whenever the bus is alive.  The
    # alloy HAL needs to *know* this to short-circuit the EnableClock
    # path; without an explicit marker, the trait surface looks
    # identical to "synthesis missed this family" (an emitter bug).
    if device.identity.family in {"avr-da", "nrf52"}:
        for per in device.peripherals:
            if per.id in result:
                # Peripheral already carries a gate (rare on these
                # families, but possible if YAML inline declares one).
                # Leave the existing entry alone.
                continue
            result[per.id] = PeripheralRcc(
                en=None,
                rst=None,
                extra={"gate_model": "always_on"},
            )

    return result


def _derive_gate_model(
    en: str | None, rst: str | None, bus: str | None
) -> str | None:
    """Map a synthesised RCC path shape to one of the five
    ``GateModel`` enumerators.

    Returns ``None`` when no gate exists (the always-on pass on
    avr-da / nrf52 fills those entries instead).  Otherwise:

    * ``index_based``    — CCGR-style index path
      (``ccm.ccgr<N>.cg<M>`` on iMXRT).
    * ``per_peri_pcr``   — gate lives inside the peripheral's own
      register block (ESP32-C3 / S3 ``pcr.<peri>_conf_reg.<peri>_clk_en``).
    * ``per_peri_en_rst`` — separate enable + reset bits in
      centralised registers (every STM32 family, Microchip SAMD51
      with explicit rstc, etc.).
    * ``per_peri_en``    — single bit serves as both enable and
      reset release (RP2040 ``resets.reset.<peri>``, SAMD21 with
      no PMC/RSTC reset path).
    * ``always_on``      — silicon has no gate (handled by the
      caller's vendor-family branch, not here).
    """
    if en is None and rst is None:
        return None
    # iMXRT CCGR: bus tag flagged "CCGR" by the CCGR table branch.
    if bus == "CCGR":
        return "index_based"
    # ESP32-C3 / S3 PCR self-contained: bus tag "PCR" + path starts
    # with ``pcr.``.
    if bus == "PCR":
        return "per_peri_pcr"
    # Both en and rst populated → classic STM32-style separate
    # enable/reset.
    if en is not None and rst is not None:
        # RP2040 "resets.reset.<peri>" mirrors the same path into
        # both en and rst — that's a per_peri_en (one bit serves
        # both roles), not a per_peri_en_rst.
        if en == rst and en.startswith("resets."):
            return "per_peri_en"
        return "per_peri_en_rst"
    # Only one of en/rst populated.
    return "per_peri_en"


def _normalize_register_path(reg_path: str | None) -> str | None:
    """Turn a vendor-specific RCC register reference into a canonical
    ``register:<peripheral>:<reg>`` id.

    The input shape varies wildly:

    * STM32 hand-crafted: ``APB2ENR.IOPAEN`` (RCC implicit).
    * STM32 absolute:     ``RCC.APB2ENR.IOPAEN``.
    * ESP32:              ``DPORT.PERIP_CLK_EN.GPIO``.
    * nRF52:              ``ENABLE.UARTE0`` (peripheral-relative).
    * RP2040:             ``RESETS.RESET.uart0``.

    We canonicalise to lower-case + colon-separated; the **last** path
    component is the bit/field name and the rest is the register.
    """
    if not reg_path:
        return None
    parts = reg_path.split(".")
    if len(parts) < 2:
        return None
    if len(parts) == 2:
        # ``REG.BIT`` — peripheral implicit, use REG twice for clarity.
        peripheral, _bit = parts
        return f"register:{peripheral.lower()}:{peripheral.lower()}"
    # Three or more components: ``PERIPH.REG.BIT`` — drop the trailing bit.
    peripheral = parts[0].lower()
    register = parts[1].lower()
    return f"register:{peripheral}:{register}"


def _normalize_field_id(reg_path: str | None) -> str | None:
    """``register:<periph>:<reg>:<field>`` from the dotted form."""
    if not reg_path:
        return None
    parts = reg_path.split(".")
    if len(parts) < 2:
        return None
    if len(parts) == 2:
        peripheral, field = parts
        return f"field:{peripheral.lower()}:{peripheral.lower()}:{field.lower()}"
    return f"field:{parts[0].lower()}:{parts[1].lower()}:{'.'.join(parts[2:]).lower()}"


# ---------------------------------------------------------------------------
# Per-row synthesis
# ---------------------------------------------------------------------------


def _synth_clock_routes(
    per: PeripheralInstance,
    rcc_override: PeripheralRcc | None = None,
) -> list[RouteOperation]:
    """Synthesise clock-enable and reset RouteOperations.

    ``rcc_override`` is the RCC entry from the template cross-link table
    used when the peripheral YAML entry has no inline ``rcc:`` block.
    """
    effective_rcc = per.rcc or rcc_override
    rows: list[RouteOperation] = []
    if effective_rcc and effective_rcc.en:
        rows.append(
            RouteOperation(
                operation_id=f"operation:clock-enable:{per.id}",
                kind="set-bit",
                target_ref_kind="clock-gate",
                target_ref_id=f"gate:{per.id}",
                register_id=_normalize_register_path(effective_rcc.en),
                register_field_id=_normalize_field_id(effective_rcc.en),
                value_ref_kind="int",
                value_int=1,
                subject_kind="peripheral",
                subject_id=per.id,
                schema_id=(
                    f"alloy.{per.template}.{per.ip_version}"
                    if per.ip_version
                    else f"alloy.{per.template}"
                ),
            )
        )
    if effective_rcc and effective_rcc.rst:
        # Reset is a "pulse": set + clear.  Codegen emits one
        # set-bit followed by clear-bit; we emit both rows here so
        # the pipeline can drive each independently.
        rows.append(
            RouteOperation(
                operation_id=f"operation:reset-assert:{per.id}",
                kind="set-bit",
                target_ref_kind="reset",
                target_ref_id=f"reset:{per.id}",
                register_id=_normalize_register_path(effective_rcc.rst),
                register_field_id=_normalize_field_id(effective_rcc.rst),
                value_ref_kind="int",
                value_int=1,
                subject_kind="peripheral",
                subject_id=per.id,
            )
        )
        rows.append(
            RouteOperation(
                operation_id=f"operation:reset-release:{per.id}",
                kind="clear-bit",
                target_ref_kind="reset",
                target_ref_id=f"reset:{per.id}",
                register_id=_normalize_register_path(effective_rcc.rst),
                register_field_id=_normalize_field_id(effective_rcc.rst),
                value_ref_kind="int",
                value_int=0,
                subject_kind="peripheral",
                subject_id=per.id,
            )
        )
    return rows


def _synth_interrupt_bindings(per: PeripheralInstance) -> list[InterruptBinding]:
    out: list[InterruptBinding] = []
    for irq in per.irq:
        out.append(
            InterruptBinding(
                binding_id=f"binding:{per.id}:{irq.name}",
                peripheral=per.id,
                interrupt=irq.name,
                line=irq.num,
                vector_slot=irq.num,
                symbol_name=irq.name,
                shared_group=per.mutex_group,
            )
        )
    return out


def _synth_signal_endpoints(per: PeripheralInstance) -> list[SignalEndpoint]:
    out: list[SignalEndpoint] = []
    for signal in per.pin_options:
        out.append(
            SignalEndpoint(
                endpoint_id=f"endpoint:{per.id}:{signal}",
                peripheral=per.id,
                peripheral_class=per.template,
                signal=signal,
            )
        )
    # Also emit endpoints for ADC / SAADC channels.
    for channel in per.channels:
        out.append(
            SignalEndpoint(
                endpoint_id=f"endpoint:{per.id}:{channel}",
                peripheral=per.id,
                peripheral_class=per.template,
                signal=channel,
                direction="analog",
            )
        )
    return out


def _classify_vector_kind(name: str) -> str:
    """Classify a vector symbol by name pattern.

    AVR's reset slot is ``__vector_default`` (slot 0).  ARM Cortex-M
    uses ``Reset_Handler`` + ``__stack_top`` + system-exception names
    (``NMI_Handler``, ``HardFault_Handler``, …).
    """
    n = name.lower()
    if n in {"__stack_top", "_estack"}:
        return "initial-stack-pointer"
    if n in {"__vector_default", "reset_handler", "_start"}:
        return "reset"
    if n.endswith("_handler") and not n.endswith("_irqhandler"):
        return "system-exception"
    return "peripheral-irq"


def _synth_vector_slots(
    interrupts: tuple[InterruptVector, ...] | InterruptMatrix | None,
) -> list[VectorSlot]:
    if interrupts is None:
        return []
    if isinstance(interrupts, InterruptMatrix):
        # Matrix-style chips don't have fixed vector slots; the runtime
        # router populates them.  Emit one per declared peripheral source.
        return [
            VectorSlot(
                slot=src.id,
                symbol_name=src.name,
                kind="matrix-source",
                interrupt=src.name,
            )
            for src in interrupts.peripheral_sources
        ]
    return [
        VectorSlot(
            slot=v.num,
            symbol_name=v.name,
            kind=_classify_vector_kind(v.name),  # type: ignore[arg-type]
            interrupt=v.name if _classify_vector_kind(v.name) == "peripheral-irq" else None,
        )
        for v in interrupts
    ]


# ---------------------------------------------------------------------------
# Public entry point
# ---------------------------------------------------------------------------


def _synth_pin_routes(device: CanonicalDevice) -> tuple[PinRoute, ...]:
    """Lower every (peripheral, signal, pin_option) triple to a
    canonical :class:`PinRoute` via the family's
    :class:`PinmuxBackend`.

    Returns an empty tuple when no backend ships for the family
    yet — the pin-router emitter then emits a stub
    ``ALLOY_PIN_ROUTE_COUNT == 0`` artifact and consumers compile
    cleanly.

    Sorted by ``(peripheral_id, signal_id, pin_id)`` so the
    regenerated table is byte-stable across runs.

    Local import (deferred) to keep the IR layer free of an
    eager dependency on ``emit_v2_1`` — same pattern as
    :func:`_synth_clock_program_steps`.
    """
    from alloy_codegen.emit_v2_1.pinmux_backends import backend_for

    backend = backend_for(device.identity.vendor, device.identity.family)
    if backend is None:
        return ()
    rows: list[PinRoute] = []
    for per in device.peripherals:
        for signal, options in per.pin_options.items():
            for option in options:
                try:
                    rows.append(backend.encode(per, signal, option))
                except ValueError:
                    # Backend rejected an option type it can't handle
                    # (e.g. STM32 backend seeing a Matrix option from
                    # a future heterogeneous family).  Drop quietly;
                    # the option survives in the IR for diagnostics.
                    continue
    rows.sort(key=lambda r: (r.peripheral_id, r.signal_id, r.pin_id))
    return tuple(rows)


def _synth_clock_program_steps(
    device: CanonicalDevice,
) -> dict[str, tuple[ClockProgramStep, ...]]:
    """Lower every :class:`ClockProfile` to its vendor-agnostic
    program via the per-vendor :class:`ClockBackend`.

    Returns an empty dict for any vendor without a registered
    backend yet — the runtime-init emitter then falls back to
    declaration-only output for those profiles.

    Local import is deliberate: the clock-backend registry lives
    under ``alloy_codegen.emit_v2_1.clock_backends`` because the
    backends carry artifact-adjacent knowledge (FLASH WS tables,
    barrier discipline) that conceptually belongs next to the
    runtime_init emitter rather than the IR layer.  We pay a
    one-time import cost to keep the synthesiser's hot path free
    of circular imports.
    """
    from alloy_codegen.emit_v2_1.clock_backends import backend_for

    backend = backend_for(device.identity.vendor)
    if backend is None:
        return {}
    return {profile.id: backend.emit_profile(profile, device) for profile in device.clock.profiles}


def build_synthesised(device: CanonicalDevice) -> SynthesisedDevice:
    """Walk ``device`` and produce its :class:`SynthesisedDevice`.

    Deterministic — re-running on the same input yields a structurally-
    equal result (every aggregate is built in source order).
    """
    # Build the RCC lookup from the 'rcc' template (STM32-style YAMLs
    # declare clock-enable/reset fields centrally, not per peripheral).
    rcc_lookup = _build_rcc_lookup(device)

    route_ops: list[RouteOperation] = []
    bindings: list[InterruptBinding] = []
    endpoints: list[SignalEndpoint] = []
    per_rcc_map: dict[str, PeripheralRcc] = {}

    for per in device.peripherals:
        # Merge inline ``per.rcc`` with the template-synthesised lookup.
        # Inline en/rst paths (when present) win because they carry
        # vendor-specific casing/conventions the YAML author intended.
        # The synthesised ``extra`` (bus inference + clock-sel mux) is
        # ALWAYS layered on top — those facts come from the templates
        # the YAML doesn't repeat per peripheral, so without merging,
        # an inline rcc block would mask the cross-link entirely (e.g.
        # RP2040 peripherals get reset paths inline but kernel-clock
        # muxes only via the ``clocks`` template).
        synthed = rcc_lookup.get(per.id)
        if per.rcc is None:
            effective_rcc = synthed
        elif synthed is None:
            effective_rcc = per.rcc
        else:
            merged_extra: dict[str, object] = dict(synthed.extra)
            if per.rcc.extra:
                merged_extra.update(per.rcc.extra)
            effective_rcc = PeripheralRcc(
                en=per.rcc.en or synthed.en,
                rst=per.rcc.rst or synthed.rst,
                extra=merged_extra,
            )
        # Backfill ``gate_model`` for peripherals that came in via
        # inline ``rcc:`` only (the synthesised lookup never saw
        # them, so ``_derive_gate_model`` ran with empty paths and
        # never assigned an enumerator).  The inline path shape is
        # the same shape we'd derive from a template, so the same
        # heuristic applies.
        if effective_rcc is not None and "gate_model" not in effective_rcc.extra:
            _bus_val = effective_rcc.extra.get("bus")
            _bus_str: str | None = _bus_val if isinstance(_bus_val, str) else None
            inline_gate_model = _derive_gate_model(
                effective_rcc.en,
                effective_rcc.rst,
                _bus_str,
            )
            if inline_gate_model is not None:
                # Build a new dict so the frozen dataclass doesn't
                # need mutation-in-place.
                new_extra = dict(effective_rcc.extra)
                new_extra["gate_model"] = inline_gate_model
                effective_rcc = PeripheralRcc(
                    en=effective_rcc.en,
                    rst=effective_rcc.rst,
                    extra=new_extra,
                )
        # Pass the *non-inline* part as the override into route_ops so
        # the existing fallback semantics there stay intact.
        rcc_override = None if per.rcc else synthed
        route_ops.extend(_synth_clock_routes(per, rcc_override))
        bindings.extend(_synth_interrupt_bindings(per))
        endpoints.extend(_synth_signal_endpoints(per))
        if effective_rcc:
            per_rcc_map[per.id] = effective_rcc

    return SynthesisedDevice(
        route_operations=tuple(route_ops),
        interrupt_bindings=tuple(bindings),
        vector_slots=tuple(_synth_vector_slots(device.interrupts)),
        signal_endpoints=tuple(endpoints),
        clock_program_steps=_synth_clock_program_steps(device),
        pin_routes=_synth_pin_routes(device),
        per_rcc_map=per_rcc_map,
    )
