#ifndef __EBISU_MONGO_MONGO_LOGGING_HPP__
#define __EBISU_MONGO_MONGO_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace ebisu {
namespace mongo {
/// Provide for single logger for (Lib:mongo)
template <typename T>
struct Mongo_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("mongo");
    return logger;
  }
};

namespace {
/// Accessor to the logger for (Lib:mongo)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> mongo_logger{Mongo_logger<int>().logger()};
}

}  // namespace mongo
}  // namespace ebisu

#endif  // __EBISU_MONGO_MONGO_LOGGING_HPP__
