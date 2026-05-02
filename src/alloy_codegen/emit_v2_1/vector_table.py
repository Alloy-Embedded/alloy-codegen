"""Emit a Cortex-M / AVR vector table from the synthesised IR.

Walks the :class:`SynthesisedDevice`'s ``vector_slots`` (already
classified by kind) and produces a C array suitable for inclusion
in the chip's startup file.

For matrix-style chips (ESP32) the function returns a stub that
documents the runtime-routed model — the actual matrix routing is
emitted by a different code path.
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised import SynthesisedDevice, VectorSlot
from alloy_codegen.ir.v2_1 import CanonicalDevice


def _slot_constant(slot: VectorSlot) -> str:
    """The C constexpr value to place in the vector table for one slot."""
    if slot.kind == "initial-stack-pointer":
        return "(uint32_t)&_estack"
    return slot.symbol_name


def _emit_nvic_priority_setup(device: CanonicalDevice) -> list[str]:
    """Emit the typed ``alloy_nvic_priority_setup[]`` table + apply
    helper.

    The table carries one row per ``InterruptVector`` whose
    ``priority`` field is set; vectors at the chip's reset default
    (``priority is None``) are omitted entirely.  ``priority`` is
    already pre-encoded for the device's
    ``core.nvic_priority_bits`` (left-shifted into the upper bits
    of ``NVIC->IPR[n]``) so the runtime helper does not need to
    know the bit count.

    For families with no `priority` data yet, the table degrades
    to a zero-length array and ``alloy_nvic_apply_priorities()``
    becomes a no-op — consumers can call it unconditionally.
    """
    interrupts = device.interrupts
    rows: list[tuple[int, int]] = []
    if isinstance(interrupts, tuple):
        for v in interrupts:
            if v.priority is not None:
                rows.append((v.num, v.priority))
    n = len(rows)
    out: list[str] = [
        "",
        "/* ---- NVIC priority setup ----",
        " *",
        " * One row per InterruptVector.priority that was explicitly set",
        " * in the canonical IR.  Vectors at reset default are omitted.",
        " * The priority value is already shifted into the upper bits of",
        f" * NVIC->IPR[n] for the chip's nvic_priority_bits = {device.identity.core.nvic_priority_bits}.",
        " */",
        "struct alloy_nvic_priority_setup_row {",
        "    uint8_t irqn;",
        "    uint8_t priority;",
        "};",
    ]
    if n == 0:
        out.extend([
            "static const struct alloy_nvic_priority_setup_row * const "
            "alloy_nvic_priority_setup = (void *)0;",
            "static const unsigned alloy_nvic_priority_setup_count = 0;",
        ])
    else:
        out.append(
            f"static const struct alloy_nvic_priority_setup_row "
            f"alloy_nvic_priority_setup[{n}] = {{"
        )
        for irqn, prio in rows:
            out.append(f"    {{ {irqn:3}u, {prio:3}u }},")
        out.append("};")
        out.append(f"static const unsigned alloy_nvic_priority_setup_count = {n};")
    out.extend([
        "",
        "/* Apply every entry in alloy_nvic_priority_setup[] via",
        " * NVIC_SetPriority.  Safe to call before any IRQ is enabled. */",
        "extern void NVIC_SetPriority(int irqn, unsigned priority);",
        "",
        "void alloy_nvic_apply_priorities(void) {",
        "    for (unsigned i = 0; i < alloy_nvic_priority_setup_count; ++i) {",
        "        NVIC_SetPriority((int)alloy_nvic_priority_setup[i].irqn,",
        "                         alloy_nvic_priority_setup[i].priority);",
        "    }",
        "}",
    ])
    return out


def emit_vector_table(
    device: CanonicalDevice,
    synthesised: SynthesisedDevice,
) -> str:
    """Render a C source string with the vector table."""
    if not synthesised.vector_slots:
        return f"/* No vector table for {device.identity.device}. */\n"

    # Matrix chips: emit a placeholder + extern decls for each source.
    if all(s.kind == "matrix-source" for s in synthesised.vector_slots):
        body = "\n".join(
            f"extern void {s.symbol_name}(void);  /* IRQ source #{s.slot} */"
            for s in synthesised.vector_slots
        )
        return (
            f"/* {device.identity.device} uses a runtime interrupt matrix.\n"
            f" * The vector table is populated by the matrix router on boot;\n"
            f" * this file only declares the candidate handlers.\n"
            f" */\n"
            f"{body}\n"
        )

    # Fixed-table chips (Cortex-M, AVR, RP2040): emit the C array.
    extern_decls: list[str] = []
    for slot in synthesised.vector_slots:
        if slot.kind == "initial-stack-pointer":
            continue
        extern_decls.append(f"extern void {slot.symbol_name}(void);")

    by_slot = {s.slot: s for s in synthesised.vector_slots}
    max_slot = max(by_slot)
    table_rows: list[str] = []
    for i in range(max_slot + 1):
        slot = by_slot.get(i)
        if slot is None:
            table_rows.append(f"    [{i:3}] = 0,")
        else:
            table_rows.append(
                f"    [{i:3}] = (void *){_slot_constant(slot)},"
                f"  /* {slot.kind} */"
            )

    return (
        f"/* Vector table for {device.identity.device}\n"
        f" *\n"
        f" * Generated by alloy-codegen v2.1 from\n"
        f" *   schema: {device.schema}\n"
        f" *   primary provenance: {device.provenance.primary}\n"
        f" */\n"
        f"#include <stdint.h>\n\n"
        + "\n".join(extern_decls)
        + "\n\n"
        + "__attribute__((section(\".isr_vector\"), used))\n"
        + f"void * const _vector_table[{max_slot + 1}] = {{\n"
        + "\n".join(table_rows)
        + "\n};\n"
        + "\n"
        + "\n".join(_emit_nvic_priority_setup(device))
        + "\n"
    )
