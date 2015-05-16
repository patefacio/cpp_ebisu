#ifndef __FCS_ORM_CODE_METRICS_CODE_METRICS_INITIALIZATION_HPP__
#define __FCS_ORM_CODE_METRICS_CODE_METRICS_INITIALIZATION_HPP__

#include "fcs/orm/code_metrics/code_metrics_logging.hpp"
#include "fcs/raii/api_initializer.hpp"

namespace fcs {
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
inline fcs::raii::Api_initializer<> code_metrics_initializer_() {
  static fcs::raii::Api_initializer<> code_metrics_initializer{
      code_metrics_init, code_metrics_uninit};
  return code_metrics_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for code_metrics
namespace {
fcs::raii::Api_initializer<> code_metrics_initializer{
    code_metrics_initializer_()};
}

}  // namespace code_metrics
}  // namespace orm
}  // namespace fcs

#endif  // __FCS_ORM_CODE_METRICS_CODE_METRICS_INITIALIZATION_HPP__
