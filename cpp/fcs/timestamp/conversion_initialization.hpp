#ifndef __FCS_TIMESTAMP_CONVERSION_INITIALIZATION_HPP__
#define __FCS_TIMESTAMP_CONVERSION_INITIALIZATION_HPP__

#include "fcs/raii/api_initializer.hpp"
#include "fcs/timestamp/conversion_logging.hpp"

namespace fcs {
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
inline fcs::raii::Api_initializer<> conversion_initializer_() {
  static fcs::raii::Api_initializer<> conversion_initializer{conversion_init,
                                                             conversion_uninit};
  return conversion_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for conversion
namespace {
fcs::raii::Api_initializer<> conversion_initializer{conversion_initializer_()};
}

}  // namespace timestamp
}  // namespace fcs

#endif  // __FCS_TIMESTAMP_CONVERSION_INITIALIZATION_HPP__
