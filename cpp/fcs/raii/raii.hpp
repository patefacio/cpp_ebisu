#ifndef __FCS_RAII_RAII_HPP__
#define __FCS_RAII_RAII_HPP__

#include "spdlog/spdlog.h"

namespace fcs {
namespace raii {
/// Provide for single logger for (Lib:raii)
template <typename T>
struct Raii_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("raii");
    return logger;
  }
};

namespace {

/// Accessor for the logger for (Lib:raii)
inline std::shared_ptr<spdlog::logger>& raii_logger() {
  return Raii_logger<int>().logger();
}
}

}  // namespace raii
}  // namespace fcs

#endif  // __FCS_RAII_RAII_HPP__
