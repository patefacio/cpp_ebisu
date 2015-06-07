#ifndef __EBISU_TIMESTAMP_TIMESTAMP_INITIALIZATION_HPP__
#define __EBISU_TIMESTAMP_TIMESTAMP_INITIALIZATION_HPP__

#include "ebisu/raii/api_initializer.hpp"
#include "ebisu/timestamp/timestamp_logging.hpp"

namespace ebisu {
namespace timestamp {
/// Initialization function for timestamp
inline void timestamp_init() {
#if defined(LIB_INIT_LOGGING)
  timestamp_logger->info("init of timestamp (version 0.0.0)");
#endif
}

/// Uninitialization function for timestamp
inline void timestamp_uninit() {
#if defined(LIB_INIT_LOGGING)
  timestamp_logger->info("uninit of timestamp (version 0.0.0)");
#endif
}

/// Singleton for timestamp initializer
inline ebisu::raii::Api_initializer<> timestamp_initializer_() {
  static ebisu::raii::Api_initializer<> timestamp_initializer{timestamp_init,
                                                              timestamp_uninit};
  return timestamp_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for timestamp
namespace {
ebisu::raii::Api_initializer<> timestamp_initializer{timestamp_initializer_()};
}

}  // namespace timestamp
}  // namespace ebisu

#endif  // __EBISU_TIMESTAMP_TIMESTAMP_INITIALIZATION_HPP__
