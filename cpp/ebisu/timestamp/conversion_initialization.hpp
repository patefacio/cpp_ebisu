#ifndef __EBISU_TIMESTAMP_CONVERSION_INITIALIZATION_HPP__
#define __EBISU_TIMESTAMP_CONVERSION_INITIALIZATION_HPP__

#include "ebisu/raii/api_initializer.hpp"
#include "ebisu/timestamp/conversion_logging.hpp"

namespace ebisu {
namespace timestamp {
/// Initialization function for conversion
inline void conversion_init() {
  conversion_logger->info("init of conversion (version 0.0.0)");
}

/// Uninitialization function for conversion
inline void conversion_uninit() {
  conversion_logger->info("uninit of conversion (version 0.0.0)");
}

/// Singleton for conversion initializer
inline ebisu::raii::Api_initializer<> conversion_initializer_() {
  static ebisu::raii::Api_initializer<> conversion_initializer{
      conversion_init, conversion_uninit};
  return conversion_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for conversion
namespace {
ebisu::raii::Api_initializer<> conversion_initializer{
    conversion_initializer_()};
}

}  // namespace timestamp
}  // namespace ebisu

#endif  // __EBISU_TIMESTAMP_CONVERSION_INITIALIZATION_HPP__
