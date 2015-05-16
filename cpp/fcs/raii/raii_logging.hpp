#ifndef __FCS_RAII_RAII_LOGGING_HPP__
#define __FCS_RAII_RAII_LOGGING_HPP__

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
/// Accessor to the logger for (Lib:raii)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> raii_logger{Raii_logger<int>().logger()};
}

}  // namespace raii
}  // namespace fcs

#endif  // __FCS_RAII_RAII_LOGGING_HPP__
