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

template <typename CLOCK = std::chrono::high_resolution_clock,
          typename TIME_POINT = typename CLOCK::time_point,
          typename DURATION = typename CLOCK::duration>
class Block_timer {
 public:
  using Clock_t = CLOCK;
  using Time_point_t = TIME_POINT;
  using Duration_t = DURATION;

  Block_timer(Duration_t& duration) : duration_{duration} {}

  // custom <ClsPublic Block_timer>

  ~Block_timer() {
    stop_ = Clock_t::now();
    duration_ = stop_ - start_;
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

template <typename BLOCK_TIMER = Block_timer<> >
class Block_timer_logger {
 public:
  using Block_timer_t = BLOCK_TIMER;
  using Duration_t = typename Block_timer_t::Duration_t;

  Block_timer_logger(std::ostream& out, std::string const& description = "")
      : out_{out}, description_{description} {}

  // custom <ClsPublic Block_timer_logger>

  ~Block_timer_logger() {
    out_ << "Block (" << description_ << ") took " << duration.count() << " ticks where "
         << Duration_t::period::num << " ticks = " << Duration_t::period::den
         << " seconds\n";
  }

  // end <ClsPublic Block_timer_logger>

  /**
   Duration of a timed block - value to be logged at destruction
  */
  Duration_t duration{};

 private:
  /**
   Text describing block being timed
  */
  std::string description_{};

  /**
   Stream to log results
  */
  std::ostream& out_;
};

//! Times a block of code and via RIIA logs results

/**
 Times a block and logs results

*/
template <typename T>
class Streaming_block_timer {
 public:
  // custom <ClsPublic Streaming_block_timer>
  // end <ClsPublic Streaming_block_timer>
};

}  // namespace performance
}  // namespace ebisu

#endif  // __EBISU_PERFORMANCE_BLOCK_TIMERS_HPP__
