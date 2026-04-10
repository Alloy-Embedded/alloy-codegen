// Generated startup metadata bootstrap unit.
#include <cstdint>

namespace nxp {
namespace imxrt1060 {
namespace mimxrt1062 {
struct InterruptDescriptor {
  const char* name;
  int line;
  const char* peripheral;
};
inline constexpr InterruptDescriptor kInterruptTable[] = {
  {"LPUART1", 20, "LPUART1"},
  {"LPUART3", 22, "LPUART3"},
  {"LPI2C1", 28, "LPI2C1"},
  {"LPSPI1", 32, "LPSPI1"},
};
}
}
}
