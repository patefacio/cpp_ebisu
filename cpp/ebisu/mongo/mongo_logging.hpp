#ifndef __EBISU_MONGO_MONGO_LOGGING_HPP__
#define __EBISU_MONGO_MONGO_LOGGING_HPP__

#include "ebisu/logger/logger.hpp"

namespace ebisu {
namespace mongo {

/// Establishes logger for library mongo
template <typename T>
struct Mongo_logger {};

/// Establishes logger using spdlog as implementation
template <>
struct Mongo_logger<spdlog::logger> {
  using Logger_impl_t = std::shared_ptr<spdlog::logger>;
  static Logger_impl_t& logger() {
    static Logger_impl_t logger = spdlog::stdout_logger_mt("mongo");
    return logger;
  }
};

/// Establishes *null logger* that does no logging but satisfies the
/// requirements
template <>
struct Mongo_logger<ebisu::logger::Null_logger_impl> {
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
using Mongo_logger_t = Mongo_logger<spdlog::logger>;
#define MONGO_TRACE(...) mongo_logger->trace(__VA_ARGS__)
#else
using Mongo_logger_t = Mongo_logger<ebisu::logger::Null_logger_impl>;
Mongo_logger_t mongo_logger_impl;
#define MONGO_TRACE(...) (void)0
#endif

Mongo_logger_t::Logger_impl_t mongo_logger = Mongo_logger_t::logger();
}

}  // namespace mongo
}  // namespace ebisu

#endif  // __EBISU_MONGO_MONGO_LOGGING_HPP__
