#ifndef __EBISU_UTILS_UTILS_INITIALIZATION_HPP__
#define __EBISU_UTILS_UTILS_INITIALIZATION_HPP__

#include "ebisu/raii/api_initializer.hpp"
#include "ebisu/utils/utils_logging.hpp"

namespace ebisu {
namespace utils {
/// Initialization function for utils
inline void utils_init() {
#if defined(LIB_INIT_LOGGING)
  utils_logger->info("init of utils (version 0.0.0)");
#endif
}

/// Uninitialization function for utils
inline void utils_uninit() {
#if defined(LIB_INIT_LOGGING)
  utils_logger->info("uninit of utils (version 0.0.0)");
#endif
}

/// Singleton for utils initializer
inline ebisu::raii::Api_initializer<> utils_initializer_() {
  static ebisu::raii::Api_initializer<> utils_initializer{utils_init,
                                                          utils_uninit};
  return utils_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for utils
namespace {
ebisu::raii::Api_initializer<> utils_initializer{utils_initializer_()};
}

}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_UTILS_INITIALIZATION_HPP__
