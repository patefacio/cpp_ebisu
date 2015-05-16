#ifndef __FCS_TIMESTAMP_TIMESTAMP_LOGGING_HPP__
#define __FCS_TIMESTAMP_TIMESTAMP_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace fcs {
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
}  // namespace fcs

#endif  // __FCS_TIMESTAMP_TIMESTAMP_LOGGING_HPP__
