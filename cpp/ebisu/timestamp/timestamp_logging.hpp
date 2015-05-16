#ifndef __EBISU_TIMESTAMP_TIMESTAMP_LOGGING_HPP__
#define __EBISU_TIMESTAMP_TIMESTAMP_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace ebisu {
namespace timestamp {
/// Provide for single logger for (Lib:timestamp)
template <typename T>
struct Timestamp_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("timestamp");
    return logger;
  }
};

namespace {
/// Accessor to the logger for (Lib:timestamp)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> timestamp_logger{
    Timestamp_logger<int>().logger()};
}

}  // namespace timestamp
}  // namespace ebisu

#endif  // __EBISU_TIMESTAMP_TIMESTAMP_LOGGING_HPP__
