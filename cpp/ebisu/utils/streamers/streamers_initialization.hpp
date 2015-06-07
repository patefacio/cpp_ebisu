#ifndef __EBISU_UTILS_STREAMERS_STREAMERS_INITIALIZATION_HPP__
#define __EBISU_UTILS_STREAMERS_STREAMERS_INITIALIZATION_HPP__

#include "ebisu/raii/api_initializer.hpp"
#include "ebisu/utils/streamers/streamers_logging.hpp"

namespace ebisu {
namespace utils {
namespace streamers {
/// Initialization function for streamers
inline void streamers_init() {
#if defined(LIB_INIT_LOGGING)
  streamers_logger->info("init of streamers (version 0.0.0)");
#endif
}

/// Uninitialization function for streamers
inline void streamers_uninit() {
#if defined(LIB_INIT_LOGGING)
  streamers_logger->info("uninit of streamers (version 0.0.0)");
#endif
}

/// Singleton for streamers initializer
inline ebisu::raii::Api_initializer<> streamers_initializer_() {
  static ebisu::raii::Api_initializer<> streamers_initializer{streamers_init,
                                                              streamers_uninit};
  return streamers_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for streamers
namespace {
ebisu::raii::Api_initializer<> streamers_initializer{streamers_initializer_()};
}

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_STREAMERS_INITIALIZATION_HPP__
