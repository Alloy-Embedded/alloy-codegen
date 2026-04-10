#pragma once

namespace nxp {
namespace imxrt1060 {
namespace generated {
struct RccDescriptor {
  const char* peripheral;
  const char* enable_signal;
  const char* reset_signal;
};
inline constexpr RccDescriptor kRccMap[] = {
  {"GPIO1", "CCM_CCGR1.CG13", ""},
  {"GPIO4", "CCM_CCGR3.CG13", ""},
  {"LPI2C1", "CCM_CCGR2.CG2", ""},
  {"LPSPI1", "CCM_CCGR1.CG0", ""},
  {"LPUART1", "CCM_CCGR5.CG12", ""},
  {"LPUART3", "CCM_CCGR0.CG6", ""},
};
}
}
}
