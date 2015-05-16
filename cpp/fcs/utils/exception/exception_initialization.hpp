#ifndef __FCS_UTILS_EXCEPTION_EXCEPTION_INITIALIZATION_HPP__
#define __FCS_UTILS_EXCEPTION_EXCEPTION_INITIALIZATION_HPP__

#include "fcs/raii/api_initializer.hpp"
#include "fcs/utils/exception/exception_logging.hpp"

namespace fcs {
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
inline fcs::raii::Api_initializer<> exception_initializer_() {
  static fcs::raii::Api_initializer<> exception_initializer{exception_init,
                                                            exception_uninit};
  return exception_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for exception
namespace {
fcs::raii::Api_initializer<> exception_initializer{exception_initializer_()};
}

}  // namespace exception
}  // namespace utils
}  // namespace fcs

#endif  // __FCS_UTILS_EXCEPTION_EXCEPTION_INITIALIZATION_HPP__
