#ifndef __FCS_ORM_ORM_INITIALIZATION_HPP__
#define __FCS_ORM_ORM_INITIALIZATION_HPP__

#include "fcs/orm/orm_logging.hpp"
#include "fcs/raii/api_initializer.hpp"

namespace fcs {
namespace orm {
/// Initialization function for orm
inline void orm_init() { orm_logger->info("init of orm (version 0.0.0)"); }

/// Uninitialization function for orm
inline void orm_uninit() { orm_logger->info("uninit of orm (version 0.0.0)"); }

/// Singleton for orm initializer
inline fcs::raii::Api_initializer<> orm_initializer_() {
  static fcs::raii::Api_initializer<> orm_initializer{orm_init, orm_uninit};
  return orm_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for orm
namespace {
fcs::raii::Api_initializer<> orm_initializer{orm_initializer_()};
}

}  // namespace orm
}  // namespace fcs

#endif  // __FCS_ORM_ORM_INITIALIZATION_HPP__
