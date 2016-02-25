#ifndef __EBISU_PERFORMANCE_PERFORMANCE_LOGGING_HPP__
#define __EBISU_PERFORMANCE_PERFORMANCE_LOGGING_HPP__

#include "ebisu/logger/logger.hpp"

namespace ebisu {
namespace performance {

/// Establishes logger for library performance
template <typename T>
struct Performance_logger {};

/// Establishes logger using spdlog as implementation
template <>
struct Performance_logger<spdlog::logger> {
  using Logger_impl_t = std::shared_ptr<spdlog::logger>;
  static Logger_impl_t& logger() {
    static Logger_impl_t logger = spdlog::stdout_logger_mt("performance");
    return logger;
  }
};

/// Establishes *null logger* that does no logging but satisfies the
/// requirements
template <>
struct Performance_logger<ebisu::logger::Null_logger_impl> {
  using Impl_t = ebisu::logger::Null_logger_impl;
  using Logger_impl_t = ebisu::logger::Logger<Impl_t>*;
  static Logger_impl_t logger() {
    static ebisu::logger::Logger<Impl_t> logger{Impl_t()};
    return &logger;
  }
};

namespace {

////////////////////////////////////////////////////////////////////////////////
// Logging takes place by default in DEBUG mode only
// If logging is desired for *release* mode, define RELEASE_HAS_LOGGING
#if !defined(NDEBUG) || defined(RELEASE_HAS_LOGGING)
using Performance_logger_t = Performance_logger<spdlog::logger>;
#define PERFORMANCE_TRACE(...) performance_logger->trace(__VA_ARGS__)
#else
using Performance_logger_t =
    Performance_logger<ebisu::logger::Null_logger_impl>;
#define PERFORMANCE_TRACE(...) (void)0
#endif

Performance_logger_t::Logger_impl_t performance_logger =
    Performance_logger_t::logger();
}

}  // namespace performance
}  // namespace ebisu

#endif  // __EBISU_PERFORMANCE_PERFORMANCE_LOGGING_HPP__
