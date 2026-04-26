// Compile-time invariants for the structured PIO topology emitted by
// ``define-pio-semantic-struct``.  This file is compiled headers-only by
// ``test_compile_invariants.py``; if it builds, every ``static_assert`` below
// held at compile time on the RP2040 device-runtime headers.
//
// Driven by ALLOY_CODEGEN_RP2040_PIO_HEADER which the harness defines via
// ``-D``; the path resolves to
// ``raspberrypi/rp2040/generated/runtime/devices/rp2040/driver_semantics/pio.hpp``
// inside the test fixture tree.

#ifndef ALLOY_CODEGEN_RP2040_PIO_HEADER
#error "ALLOY_CODEGEN_RP2040_PIO_HEADER must be defined by the harness"
#endif

#include <array>
#include <cstdint>

#include ALLOY_CODEGEN_RP2040_PIO_HEADER

namespace ds = raspberrypi::rp2040::generated::runtime::devices::rp2040::driver_semantics;

// PIO topology — populated from patches/raspberrypi/rp2040/pio.json.
static_assert(ds::PioSemanticTraits<ds::PioId::Pio0>::kPresent);
static_assert(ds::PioSemanticTraits<ds::PioId::Pio0>::kStateMachineCount == 4u);
static_assert(ds::PioSemanticTraits<ds::PioId::Pio0>::kInstructionMemoryDepth == 32u);
static_assert(ds::PioSemanticTraits<ds::PioId::Pio0>::kBaseAddress == 0x50200000u);
static_assert(ds::PioSemanticTraits<ds::PioId::Pio1>::kBaseAddress == 0x50300000u);
static_assert(ds::PioSemanticTraits<ds::PioId::Pio1>::kDreqTx == 8u);
static_assert(ds::PioSemanticTraits<ds::PioId::Pio1>::kDreqRx == 12u);

// Per-state-machine specializations: kDreqTx = dreq_tx_base + sm_index.
static_assert(ds::StateMachineSemanticTraits<ds::PioId::Pio0, 0>::kDreqTx == 0u);
static_assert(ds::StateMachineSemanticTraits<ds::PioId::Pio0, 3>::kDreqTx == 3u);
static_assert(ds::StateMachineSemanticTraits<ds::PioId::Pio1, 2>::kDreqTx == 10u);
static_assert(ds::StateMachineSemanticTraits<ds::PioId::Pio1, 3>::kDreqRx == 15u);

// Non-PIO PioId values fall back to the primary template.
static_assert(!ds::PioSemanticTraits<static_cast<ds::PioId>(99)>::kPresent);

int main() {}
