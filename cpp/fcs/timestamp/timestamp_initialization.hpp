#ifndef __FCS_TIMESTAMP_TIMESTAMP_INITIALIZATION_HPP__
#define __FCS_TIMESTAMP_TIMESTAMP_INITIALIZATION_HPP__

#include "fcs/raii/api_initializer.hpp"
#include "fcs/timestamp/timestamp_logging.hpp"

namespace fcs {
namespace timestamp {
/// Initialization function for timestamp
inline void timestamp_init() {
  timestamp_logger->info("init of timestamp (version 0.0.0)");
}

/// Uninitialization function for timestamp
inline void timestamp_uninit() {
  timestamp_logger->info("uninit of timestamp (version 0.0.0)");
}

/// Singleton for timestamp initializer
inline fcs::raii::Api_initializer<> timestamp_initializer_() {
  static fcs::raii::Api_initializer<> timestamp_initializer{timestamp_init,
                                                            timestamp_uninit};
  return timestamp_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for timestamp
namespace {
fcs::raii::Api_initializer<> timestamp_initializer{timestamp_initializer_()};
}

}  // namespace timestamp
}  // namespace fcs

#endif  // __FCS_TIMESTAMP_TIMESTAMP_INITIALIZATION_HPP__
