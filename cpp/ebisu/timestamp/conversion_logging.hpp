#ifndef __EBISU_TIMESTAMP_CONVERSION_LOGGING_HPP__
#define __EBISU_TIMESTAMP_CONVERSION_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace ebisu {
namespace timestamp {
/// Provide for single logger for (Lib:conversion)
template <typename T>
struct Conversion_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("conversion");
    return logger;
  }
};

namespace {
/// Accessor to the logger for (Lib:conversion)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> conversion_logger{
    Conversion_logger<int>().logger()};
}

}  // namespace timestamp
}  // namespace ebisu

#endif  // __EBISU_TIMESTAMP_CONVERSION_LOGGING_HPP__
