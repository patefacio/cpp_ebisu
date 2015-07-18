#ifndef __EBISU_LINUX_SPECIFIC_SIGNAL_HANDLER_HPP__
#define __EBISU_LINUX_SPECIFIC_SIGNAL_HANDLER_HPP__

#include "ebisu/linux_specific/linux_specific_initialization.hpp"
#include "ebisu/linux_specific/linux_specific_logging.hpp"
#include <csignal>
#include <mutex>

namespace ebisu {
namespace linux_specific {
/**
 A singleton class to allow registration of common interrupting signal handlers.

   - SIGHUP
   - SIGINT
   - SIGTERM
   - SIGUSR1

 The singleton creates a thread which waits for signals. Clients can register
 handlers with [Application_signal_handler::add_handler]. When a signal is
 caught, the handlers are all called in turn. If any of the registered handlers
 returns true, the signal handler loop carries on as before. If all handlers
 return true, the [Application_signal_handler] is done and the thread will
 complete.

 A typical use case would be an application that you might not want to be killed
 with Ctrl-C. To achieve this include the header in the file with
 *main*. Register a handler to deal with the signal. Prior to exiting the *main*
 call Application_signal_handler::stop_handler_thread.

*/
template <typename LOCK_TYPE = std::mutex,
          typename GUARD_TYPE = std::lock_guard<LOCK_TYPE> >
class Application_signal_handler {
 public:
  using Thread_t = std::thread;
  using Thread_uptr_t = std::unique_ptr<Thread_t>;
  using Lock_type_t = LOCK_TYPE;
  using Guard_type_t = GUARD_TYPE;
  using Handler_function_t = std::function<bool(int)>;
  using Handler_function_list_t = std::vector<Handler_function_t>;

  ~Application_signal_handler() {
    // custom <Application_signal_handler dtor>
    linux_specific_logger->info(
        "Destroyed application signal handler singleton");
    // end <Application_signal_handler dtor>
  }

  static Application_signal_handler& instance() {
    static Application_signal_handler instance_s;
    return instance_s;
  }

  // custom <ClsPublic Application_signal_handler>

  void add_handler(Handler_function_t const& handler) {
    Guard_type_t guard(instance_lock_);
    handler_function_list_.push_back(handler);
  }

  void stop_handler_thread() {
    linux_specific_logger->info("Sending message to stop handler thread");
    exit_requested_ = true;
    kill(::getpid(), SIGINT);
    handler_thread_->join();
  }

  // end <ClsPublic Application_signal_handler>

 private:
  // custom <ClsPrivate Application_signal_handler>

  static inline void signal_handler_thread(sigset_t selected_signals) {
    linux_specific_logger->info("Signal handler thread running");
    while (!Application_signal_handler::instance().exit_requested_) {
      int signal{0};
      int rc{sigwait(&selected_signals, &signal)};
      linux_specific_logger->info(
          "Completed sigwait call with rc: {} and signal 0x{:x}", rc, signal);
      if (rc) {
        throw std::runtime_error("Unable to wait for signals");
      } else {
        linux_specific_logger->info("Calling user handlers");
        if (!Application_signal_handler::instance().call_handlers(signal)) {
          break;
        }
      }
    }
    linux_specific_logger->info("Singal handlers done");
  }

  bool call_handlers(int signal) {
    bool keep_running(false);
    for (auto& signal_handler : handler_function_list_) {
      keep_running |= signal_handler(signal);
    }
    return keep_running;
  }

  // end <ClsPrivate Application_signal_handler>

  Application_signal_handler() {
    // custom <Application_signal_handler defaultCtor>

    linux_specific_logger->info("Created application signal handler singleton");
    sigset_t selected_signals;
    sigemptyset(&selected_signals);
    sigaddset(&selected_signals, SIGHUP);
    sigaddset(&selected_signals, SIGINT);
    sigaddset(&selected_signals, SIGTERM);
    sigaddset(&selected_signals, SIGUSR1);
    int rc(pthread_sigmask(SIG_BLOCK, &selected_signals, 0));
    if (rc) {
      throw std::runtime_error("Unable to mask signals");
    } else {
      linux_specific_logger->info(
          "Masked signals, creating signal handler thread");

      try {
        handler_thread_ = std::move(Thread_uptr_t(
            new Thread_t(std::bind(&signal_handler_thread, selected_signals))));
      } catch (std::exception const& e) {
        linux_specific_logger->warn("Caught excp {}", e.what());
        throw;
      }
      linux_specific_logger->info("Handler thread created");
    }

    // end <Application_signal_handler defaultCtor>
  }

  /**
   User defined handler functions registered with [add_handler]
  */
  Handler_function_list_t handler_function_list_{};

  /**
   Lock protecting access to [handler_function_list_t]
  */
  Lock_type_t instance_lock_{};

  /**
   Thread that calls sigwait to process signals
  */
  Thread_uptr_t handler_thread_{};

  /**
   Used to cleanly exit via signal
  */
  bool exit_requested_{false};
};

}  // namespace linux_specific
}  // namespace ebisu

#endif  // __EBISU_LINUX_SPECIFIC_SIGNAL_HANDLER_HPP__
