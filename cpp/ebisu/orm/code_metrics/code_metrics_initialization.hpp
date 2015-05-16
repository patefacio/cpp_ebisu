#ifndef __EBISU_ORM_CODE_METRICS_CODE_METRICS_INITIALIZATION_HPP__
#define __EBISU_ORM_CODE_METRICS_CODE_METRICS_INITIALIZATION_HPP__

#include "ebisu/orm/code_metrics/code_metrics_logging.hpp"
#include "ebisu/raii/api_initializer.hpp"

namespace ebisu {
namespace orm {
namespace code_metrics {
/// Initialization function for code_metrics
inline void code_metrics_init() {
  code_metrics_logger->info("init of code_metrics (version 0.0.0)");
}

/// Uninitialization function for code_metrics
inline void code_metrics_uninit() {
  code_metrics_logger->info("uninit of code_metrics (version 0.0.0)");
}

/// Singleton for code_metrics initializer
inline ebisu::raii::Api_initializer<> code_metrics_initializer_() {
  static ebisu::raii::Api_initializer<> code_metrics_initializer{
      code_metrics_init, code_metrics_uninit};
  return code_metrics_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for code_metrics
namespace {
ebisu::raii::Api_initializer<> code_metrics_initializer{
    code_metrics_initializer_()};
}

}  // namespace code_metrics
}  // namespace orm
}  // namespace ebisu

#endif  // __EBISU_ORM_CODE_METRICS_CODE_METRICS_INITIALIZATION_HPP__
