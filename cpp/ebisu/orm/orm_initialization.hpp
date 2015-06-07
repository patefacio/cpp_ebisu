#ifndef __EBISU_ORM_ORM_INITIALIZATION_HPP__
#define __EBISU_ORM_ORM_INITIALIZATION_HPP__

#include "ebisu/orm/orm_logging.hpp"
#include "ebisu/raii/api_initializer.hpp"

namespace ebisu {
namespace orm {
/// Initialization function for orm
inline void orm_init() {
#if defined(LIB_INIT_LOGGING)
  orm_logger->info("init of orm (version 0.0.0)");
#endif
}

/// Uninitialization function for orm
inline void orm_uninit() {
#if defined(LIB_INIT_LOGGING)
  orm_logger->info("uninit of orm (version 0.0.0)");
#endif
}

/// Singleton for orm initializer
inline ebisu::raii::Api_initializer<> orm_initializer_() {
  static ebisu::raii::Api_initializer<> orm_initializer{orm_init, orm_uninit};
  return orm_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for orm
namespace {
ebisu::raii::Api_initializer<> orm_initializer{orm_initializer_()};
}

}  // namespace orm
}  // namespace ebisu

#endif  // __EBISU_ORM_ORM_INITIALIZATION_HPP__
