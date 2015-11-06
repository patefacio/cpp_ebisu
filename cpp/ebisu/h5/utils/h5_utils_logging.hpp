#ifndef __EBISU_H5_UTILS_H5_UTILS_LOGGING_HPP__
#define __EBISU_H5_UTILS_H5_UTILS_LOGGING_HPP__

#include "ebisu/logger/logger.hpp"

namespace ebisu {
namespace h5 {
namespace utils {

/// Establishes logger for library h5_utils
template <typename T>
struct H5_utils_logger {};

/// Establishes logger using spdlog as implementation
template <>
struct H5_utils_logger<spdlog::logger> {
  using Logger_impl_t = std::shared_ptr<spdlog::logger>;
  static Logger_impl_t& logger() {
    static Logger_impl_t logger = spdlog::stdout_logger_mt("h5_utils");
    return logger;
  }
};

/// Establishes *null logger* that does no logging but satisfies the
/// requirements
template <>
struct H5_utils_logger<ebisu::logger::Null_logger_impl> {
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
#if defined(DEBUG) || defined(RELEASE_HAS_LOGGING)
using H5_utils_logger_t = H5_utils_logger<spdlog::logger>;
#define H5_UTILS_TRACE(...) h5_utils_logger->trace(__VA_ARGS__)
#else
using H5_utils_logger_t = H5_utils_logger<ebisu::logger::Null_logger_impl>;
H5_utils_logger_t h5_utils_logger_impl;
#define H5_UTILS_TRACE(...) (void)0
#endif

H5_utils_logger_t::Logger_impl_t h5_utils_logger = H5_utils_logger_t::logger();
}

}  // namespace utils
}  // namespace h5
}  // namespace ebisu

#endif  // __EBISU_H5_UTILS_H5_UTILS_LOGGING_HPP__
