#ifndef __FCS_UTILS_UTILS_LOGGING_HPP__
#define __FCS_UTILS_UTILS_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace fcs {
namespace utils {
/// Provide for single logger for (Lib:utils)
template <typename T>
struct Utils_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("utils");
    return logger;
  }
};

namespace {
/// Accessor to the logger for (Lib:utils)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> utils_logger{Utils_logger<int>().logger()};
}

}  // namespace utils
}  // namespace fcs

#endif  // __FCS_UTILS_UTILS_LOGGING_HPP__
