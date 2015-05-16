#ifndef __FCS_UTILS_UTILS_INITIALIZATION_HPP__
#define __FCS_UTILS_UTILS_INITIALIZATION_HPP__

#include "fcs/raii/api_initializer.hpp"
#include "fcs/utils/utils_logging.hpp"

namespace fcs {
namespace utils {
/// Initialization function for utils
inline void utils_init() {
  utils_logger->info("init of utils (version 0.0.0)");
}

/// Uninitialization function for utils
inline void utils_uninit() {
  utils_logger->info("uninit of utils (version 0.0.0)");
}

/// Singleton for utils initializer
inline fcs::raii::Api_initializer<> utils_initializer_() {
  static fcs::raii::Api_initializer<> utils_initializer{utils_init,
                                                        utils_uninit};
  return utils_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for utils
namespace {
fcs::raii::Api_initializer<> utils_initializer{utils_initializer_()};
}

}  // namespace utils
}  // namespace fcs

#endif  // __FCS_UTILS_UTILS_INITIALIZATION_HPP__
