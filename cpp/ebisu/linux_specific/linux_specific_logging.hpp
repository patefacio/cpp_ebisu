#ifndef __EBISU_LINUX_SPECIFIC_LINUX_SPECIFIC_LOGGING_HPP__
#define __EBISU_LINUX_SPECIFIC_LINUX_SPECIFIC_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace ebisu {
namespace linux_specific {
/// Provide for single logger for (Lib:linux_specific)
template <typename T>
struct Linux_specific_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("linux_specific");
    return logger;
  }
};

namespace {
/// Accessor to the logger for (Lib:linux_specific)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> linux_specific_logger{
    Linux_specific_logger<int>().logger()};
}

}  // namespace linux_specific
}  // namespace ebisu

#endif  // __EBISU_LINUX_SPECIFIC_LINUX_SPECIFIC_LOGGING_HPP__
