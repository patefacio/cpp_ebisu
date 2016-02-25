#ifndef __EBISU_LINUX_SPECIFIC_LINUX_SPECIFIC_LOGGING_HPP__
#define __EBISU_LINUX_SPECIFIC_LINUX_SPECIFIC_LOGGING_HPP__

#include "ebisu/logger/logger.hpp"

namespace ebisu {
namespace linux_specific {

/// Establishes logger for library linux_specific
template <typename T>
struct Linux_specific_logger {};

/// Establishes logger using spdlog as implementation
template <>
struct Linux_specific_logger<spdlog::logger> {
  using Logger_impl_t = std::shared_ptr<spdlog::logger>;
  static Logger_impl_t& logger() {
    static Logger_impl_t logger = spdlog::stdout_logger_mt("linux_specific");
    return logger;
  }
};

/// Establishes *null logger* that does no logging but satisfies the
/// requirements
template <>
struct Linux_specific_logger<ebisu::logger::Null_logger_impl> {
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
using Linux_specific_logger_t = Linux_specific_logger<spdlog::logger>;
#define LINUX_SPECIFIC_TRACE(...) linux_specific_logger->trace(__VA_ARGS__)
#else
using Linux_specific_logger_t =
    Linux_specific_logger<ebisu::logger::Null_logger_impl>;
#define LINUX_SPECIFIC_TRACE(...) (void)0
#endif

Linux_specific_logger_t::Logger_impl_t linux_specific_logger =
    Linux_specific_logger_t::logger();
}

}  // namespace linux_specific
}  // namespace ebisu

#endif  // __EBISU_LINUX_SPECIFIC_LINUX_SPECIFIC_LOGGING_HPP__
