#ifndef __EBISU_H5_UTILS_H5_UTILS_LOGGING_HPP__
#define __EBISU_H5_UTILS_H5_UTILS_LOGGING_HPP__

#include "ebisu/logger/logger.hpp"

namespace ebisu {
namespace h5 {
namespace utils {
/// Provide for single logger for (Lib:h5_utils)
namespace {

  template <typename T>
  struct H5_utils_logger {};

  template <>
  struct H5_utils_logger<spdlog::logger> {
    using Logger_impl_t = std::shared_ptr<spdlog::logger>;
    static Logger_impl_t& logger() {
      static Logger_impl_t logger = spdlog::stdout_logger_mt("h5_utils");
      return logger;
    }
  };

  template <>
  struct H5_utils_logger<ebisu::logger::Null_logger_impl> {
    using Impl_t = ebisu::logger::Null_logger_impl;
    using Logger_impl_t = ebisu::logger::Logger< Impl_t >*;
    static Logger_impl_t logger() {
      static ebisu::logger::Logger< Impl_t > logger { Impl_t() } ;
      return &logger;
    }
  };


#if defined(DEBUG) || defined(RELEASE_HAS_LOGGING)
  using H5_utils_logger_t = H5_utils_logger<spdlog::logger>;
#else
  using H5_utils_logger_t = H5_utils_logger< ebisu::logger::Null_logger_impl >;
  H5_utils_logger_t h5_utils_logger_impl;
#endif

  H5_utils_logger_t::Logger_impl_t h5_utils_logger =  H5_utils_logger_t::logger();

}

}  // namespace utils
}  // namespace h5
}  // namespace ebisu

#endif  // __EBISU_H5_UTILS_H5_UTILS_LOGGING_HPP__
