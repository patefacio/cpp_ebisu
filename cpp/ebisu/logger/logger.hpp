#ifndef __EBISU_LOGGER_LOGGER_HPP__
#define __EBISU_LOGGER_LOGGER_HPP__

#include "spdlog/spdlog.h"
#include <memory>

namespace ebisu {
namespace logger {
template <typename LOGGER_IMPL = std::shared_ptr<spdlog::logger> >
class Logger {
 public:
  using Logger_impl_t = LOGGER_IMPL;

  Logger(Logger_impl_t impl) : impl_(impl) {}

  // custom <ClsPublic Logger>

  template <typename... Args>
  void set_level(Args... args) {
    impl_->set_level(args...);
  }
  template <typename... Args>
  void trace(Args... args) {
    impl_->trace(args...);
  }
  template <typename... Args>
  void debug(Args... args) {
    impl_->debug(args...);
  }
  template <typename... Args>
  void info(Args... args) {
    impl_->info(args...);
  }
  template <typename... Args>
  void notice(Args... args) {
    impl_->notice(args...);
  }
  template <typename... Args>
  void warn(Args... args) {
    impl_->warn(args...);
  }
  template <typename... Args>
  void error(Args... args) {
    impl_->error(args...);
  }
  template <typename... Args>
  void critical(Args... args) {
    impl_->critical(args...);
  }
  template <typename... Args>
  void alert(Args... args) {
    impl_->alert(args...);
  }
  template <typename... Args>
  void emerg(Args... args) {
    impl_->emerg(args...);
  }

  // end <ClsPublic Logger>

 private:
  Logger_impl_t impl_{};
};

class Null_logger_impl {
 public:
  // custom <ClsPublic Null_logger_impl>

  template <typename... Args>
  void set_level(Args... args) {}
  template <typename... Args>
  void trace(Args... args) {}
  template <typename... Args>
  void debug(Args... args) {}
  template <typename... Args>
  void info(Args... args) {}
  template <typename... Args>
  void notice(Args... args) {}
  template <typename... Args>
  void warn(Args... args) {}
  template <typename... Args>
  void error(Args... args) {}
  template <typename... Args>
  void critical(Args... args) {}
  template <typename... Args>
  void alert(Args... args) {}
  template <typename... Args>
  void emerg(Args... args) {}

  Null_logger_impl* operator->() { return this; }

  // end <ClsPublic Null_logger_impl>
};

// custom <FcbEndNamespace logger>

using Null_logger_t = Logger<Null_logger_impl>;

// end <FcbEndNamespace logger>

}  // namespace logger
}  // namespace ebisu

#endif  // __EBISU_LOGGER_LOGGER_HPP__
