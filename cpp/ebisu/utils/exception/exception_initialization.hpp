#ifndef __EBISU_UTILS_EXCEPTION_EXCEPTION_INITIALIZATION_HPP__
#define __EBISU_UTILS_EXCEPTION_EXCEPTION_INITIALIZATION_HPP__

#include "ebisu/raii/api_initializer.hpp"
#include "ebisu/utils/exception/exception_logging.hpp"

namespace ebisu {
namespace utils {
namespace exception {
/// Initialization function for exception
inline void exception_init() {
  exception_logger->info("init of exception (version 0.0.0)");
}

/// Uninitialization function for exception
inline void exception_uninit() {
  exception_logger->info("uninit of exception (version 0.0.0)");
}

/// Singleton for exception initializer
inline ebisu::raii::Api_initializer<> exception_initializer_() {
  static ebisu::raii::Api_initializer<> exception_initializer{exception_init,
                                                              exception_uninit};
  return exception_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for exception
namespace {
ebisu::raii::Api_initializer<> exception_initializer{exception_initializer_()};
}

}  // namespace exception
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_EXCEPTION_EXCEPTION_INITIALIZATION_HPP__
