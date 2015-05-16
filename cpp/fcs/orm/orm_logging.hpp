#ifndef __FCS_ORM_ORM_LOGGING_HPP__
#define __FCS_ORM_ORM_LOGGING_HPP__

#include "spdlog/spdlog.h"

namespace fcs {
namespace orm {
/// Provide for single logger for (Lib:orm)
template <typename T>
struct Orm_logger {
  std::shared_ptr<spdlog::logger>& logger() {
    static std::shared_ptr<spdlog::logger> logger =
        spdlog::stdout_logger_mt("orm");
    return logger;
  }
};

namespace {
/// Accessor to the logger for (Lib:orm)
///
/// Internal linkage providing one shared pointer per translation unit
std::shared_ptr<spdlog::logger> orm_logger{Orm_logger<int>().logger()};
}

}  // namespace orm
}  // namespace fcs

#endif  // __FCS_ORM_ORM_LOGGING_HPP__
