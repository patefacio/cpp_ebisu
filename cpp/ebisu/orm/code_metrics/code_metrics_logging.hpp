#ifndef __EBISU_ORM_CODE_METRICS_CODE_METRICS_LOGGING_HPP__
#define __EBISU_ORM_CODE_METRICS_CODE_METRICS_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace ebisu {
namespace orm {
namespace code_metrics {
/// Provide for single logger for (Lib:code_metrics)
template <typename T>
struct Code_metrics_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("code_metrics");
    return logger;
  }
};

namespace {
/// Accessor to the logger for (Lib:code_metrics)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> code_metrics_logger{
    Code_metrics_logger<int>().logger()};
}

}  // namespace code_metrics
}  // namespace orm
}  // namespace ebisu

#endif  // __EBISU_ORM_CODE_METRICS_CODE_METRICS_LOGGING_HPP__
