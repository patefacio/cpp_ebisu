#ifndef __FCS_UTILS_STREAMERS_STREAMERS_LOGGING_HPP__
#define __FCS_UTILS_STREAMERS_STREAMERS_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace fcs {
namespace utils {
namespace streamers {
/// Provide for single logger for (Lib:streamers)
template <typename T>
struct Streamers_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("streamers");
    return logger;
  }
};

namespace {
/// Accessor to the logger for (Lib:streamers)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> streamers_logger{
    Streamers_logger<int>().logger()};
}

}  // namespace streamers
}  // namespace utils
}  // namespace fcs

#endif  // __FCS_UTILS_STREAMERS_STREAMERS_LOGGING_HPP__
