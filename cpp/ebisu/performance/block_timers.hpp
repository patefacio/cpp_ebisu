#ifndef __EBISU_PERFORMANCE_BLOCK_TIMERS_HPP__
#define __EBISU_PERFORMANCE_BLOCK_TIMERS_HPP__

#include "ebisu/performance/performance_common.hpp"
#include "ebisu/performance/performance_initialization.hpp"
#include "ebisu/performance/performance_logging.hpp"
#include <boost/call_traits.hpp>
#include <chrono>
#include <string>

namespace ebisu {
namespace performance {
//! Times a block of code

/**
 Uses RIIA to start a timer on construction, stop the timer on
 destruction and calculate the difference. To be useful, the duration
 needs to exist beyond the timing, so it is passed in by reference.

 Rather than simply assign the timing to the duration, it is added so
 the duration can be used with multiple timers.

*/
template <typename CLOCK = std::chrono::high_resolution_clock>
class Block_timer {
 public:
  using Clock_t = CLOCK;
  using Time_point_t = typename Clock_t::time_point;
  using Duration_t = typename Clock_t::duration;

  Block_timer(Duration_t& duration) : duration_(duration) {}

  // custom <ClsPublic Block_timer>

  ~Block_timer() {
    stop_ = Clock_t::now();
    duration_ += (stop_ - start_);
    performance_logger->info("Duration {} ticks where {} tick = {} seconds",
                             duration_.count(), Duration_t::period::num,
                             Duration_t::period::den);
  }

  // end <ClsPublic Block_timer>

 private:
  /**
   Start of timing - stamped on construction
  */
  Time_point_t start_{Clock_t::now()};

  /**
   Stop of timing - stamped on destruction
  */
  Time_point_t stop_{};
  Duration_t& duration_;
};

//! Logs the results of timing a block of code

template <typename CLOCK = std::chrono::high_resolution_clock>
class Block_timer_logger {
 public:
  using Clock_t = CLOCK;
  using Time_point_t = typename Clock_t::time_point;
  using Duration_t = typename Clock_t::duration;

  Block_timer_logger(std::ostream& out, std::string const& description = "")
      : out_(out), description_(description) {}

  // custom <ClsPublic Block_timer_logger>

  ~Block_timer_logger() {
    stop_ = Clock_t::now();
    duration_ = stop_ - start_;
    out_ << "Block(" << description_ << "): " << duration_.count() << " ticks ("
         << Duration_t::period::num << " ticks = " << Duration_t::period::den
         << " seconds)\n";
  }

  // end <ClsPublic Block_timer_logger>

 private:
  /**
   Text describing block being timed
  */
  std::string description_{};

  /**
   Stream to log results
  */
  std::ostream& out_;

  /**
   Start of timing - stamped on construction
  */
  Time_point_t start_{Clock_t::now()};

  /**
   Stop of timing - stamped on destruction
  */
  Time_point_t stop_{};

  /**
   Duration of a timed block - value to be logged at destruction
  */
  Duration_t duration_{};
};

}  // namespace performance
}  // namespace ebisu

#endif  // __EBISU_PERFORMANCE_BLOCK_TIMERS_HPP__
