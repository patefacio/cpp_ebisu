#ifndef __EBISU_RAII_RAII_LOGGING_HPP__
#define __EBISU_RAII_RAII_LOGGING_HPP__

#include "ebisu/logger/logger.hpp"

namespace ebisu {
namespace raii {

/// Establishes logger for library raii
template <typename T>
struct Raii_logger {};

/// Establishes logger using spdlog as implementation
template <>
struct Raii_logger<spdlog::logger> {
  using Logger_impl_t = std::shared_ptr<spdlog::logger>;
  static Logger_impl_t& logger() {
    static Logger_impl_t logger = spdlog::stdout_logger_mt("raii");
    return logger;
  }
};

/// Establishes *null logger* that does no logging but satisfies the
/// requirements
template <>
struct Raii_logger<ebisu::logger::Null_logger_impl> {
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
using Raii_logger_t = Raii_logger<spdlog::logger>;
#else
using Raii_logger_t = Raii_logger<ebisu::logger::Null_logger_impl>;
Raii_logger_t raii_logger_impl;
#endif

Raii_logger_t::Logger_impl_t raii_logger = Raii_logger_t::logger();
}

}  // namespace raii
}  // namespace ebisu

#endif  // __EBISU_RAII_RAII_LOGGING_HPP__
