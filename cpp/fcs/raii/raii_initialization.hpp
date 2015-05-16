#ifndef __FCS_RAII_RAII_INITIALIZATION_HPP__
#define __FCS_RAII_RAII_INITIALIZATION_HPP__

#include "fcs/raii/api_initializer.hpp"
#include "fcs/raii/raii_logging.hpp"

namespace fcs {
namespace raii {
/// Initialization function for raii
inline void raii_init() { raii_logger->info("init of raii (version 0.0.1)"); }

/// Uninitialization function for raii
inline void raii_uninit() {
  raii_logger->info("uninit of raii (version 0.0.1)");
}

/// Singleton for raii initializer
inline fcs::raii::Api_initializer<> raii_initializer_() {
  static fcs::raii::Api_initializer<> raii_initializer{raii_init, raii_uninit};
  return raii_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for raii
namespace {
fcs::raii::Api_initializer<> raii_initializer{raii_initializer_()};
}

}  // namespace raii
}  // namespace fcs

#endif  // __FCS_RAII_RAII_INITIALIZATION_HPP__
