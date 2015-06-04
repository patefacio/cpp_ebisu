#ifndef __EBISU_PERFORMANCE_PERFORMANCE_LOGGING_HPP__
#define __EBISU_PERFORMANCE_PERFORMANCE_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace ebisu {
namespace performance {
/// Provide for single logger for (Lib:performance)
template <typename T>
struct Performance_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("performance");
    return logger;
  }
};

namespace {
/// Accessor to the logger for (Lib:performance)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> performance_logger{
    Performance_logger<int>().logger()};
}

}  // namespace performance
}  // namespace ebisu

#endif  // __EBISU_PERFORMANCE_PERFORMANCE_LOGGING_HPP__
