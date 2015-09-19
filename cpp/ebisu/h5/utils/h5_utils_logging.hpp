#ifndef __EBISU_H5_UTILS_H5_UTILS_LOGGING_HPP__
#define __EBISU_H5_UTILS_H5_UTILS_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace ebisu {
namespace h5 {
namespace utils {
/// Provide for single logger for (Lib:h5_utils)
template <typename T>
struct H5_utils_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("h5_utils");
    return logger;
  }
};

namespace {
/// Accessor to the logger for (Lib:h5_utils)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> h5_utils_logger{
    H5_utils_logger<int>().logger()};
}

}  // namespace utils
}  // namespace h5
}  // namespace ebisu

#endif  // __EBISU_H5_UTILS_H5_UTILS_LOGGING_HPP__
