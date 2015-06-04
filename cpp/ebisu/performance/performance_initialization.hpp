#ifndef __EBISU_PERFORMANCE_PERFORMANCE_INITIALIZATION_HPP__
#define __EBISU_PERFORMANCE_PERFORMANCE_INITIALIZATION_HPP__

#include "ebisu/performance/performance_logging.hpp"
#include "ebisu/raii/api_initializer.hpp"

namespace ebisu {
namespace performance {
/// Initialization function for performance
inline void performance_init() {
  performance_logger->info("init of performance (version 0.0.1)");
}

/// Uninitialization function for performance
inline void performance_uninit() {
  performance_logger->info("uninit of performance (version 0.0.1)");
}

/// Singleton for performance initializer
inline ebisu::raii::Api_initializer<> performance_initializer_() {
  static ebisu::raii::Api_initializer<> performance_initializer{
      performance_init, performance_uninit};
  return performance_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for performance
namespace {
ebisu::raii::Api_initializer<> performance_initializer{
    performance_initializer_()};
}

}  // namespace performance
}  // namespace ebisu

#endif  // __EBISU_PERFORMANCE_PERFORMANCE_INITIALIZATION_HPP__
