#ifndef __FCS_UTILS_STREAMERS_STREAMERS_INITIALIZATION_HPP__
#define __FCS_UTILS_STREAMERS_STREAMERS_INITIALIZATION_HPP__

#include "fcs/raii/api_initializer.hpp"
#include "fcs/utils/streamers/streamers_logging.hpp"

namespace fcs {
namespace utils {
namespace streamers {
/// Initialization function for streamers
inline void streamers_init() {
  streamers_logger->info("init of streamers (version 0.0.0)");
}

/// Uninitialization function for streamers
inline void streamers_uninit() {
  streamers_logger->info("uninit of streamers (version 0.0.0)");
}

/// Singleton for streamers initializer
inline fcs::raii::Api_initializer<> streamers_initializer_() {
  static fcs::raii::Api_initializer<> streamers_initializer{streamers_init,
                                                            streamers_uninit};
  return streamers_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for streamers
namespace {
fcs::raii::Api_initializer<> streamers_initializer{streamers_initializer_()};
}

}  // namespace streamers
}  // namespace utils
}  // namespace fcs

#endif  // __FCS_UTILS_STREAMERS_STREAMERS_INITIALIZATION_HPP__
