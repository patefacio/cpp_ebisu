#ifndef __EBISU_UTILS_EXCEPTION_EXCEPTION_LOGGING_HPP__
#define __EBISU_UTILS_EXCEPTION_EXCEPTION_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace ebisu {
namespace utils {
namespace exception {
/// Provide for single logger for (Lib:exception)
template <typename T>
struct Exception_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("exception");
    return logger;
  }
};

namespace {
/// Accessor to the logger for (Lib:exception)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> exception_logger{
    Exception_logger<int>().logger()};
}

}  // namespace exception
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_EXCEPTION_EXCEPTION_LOGGING_HPP__
