#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/performance/block_timers.hpp"

// custom <custom includes>

#include <thread>
#include <sstream>
#include "ebisu/performance/block_timers.hpp"

// end <custom includes>

namespace ebisu {
namespace performance {
// custom <block_timer begin namespace>
// end <block_timer begin namespace>

SCENARIO("block timer") {
  // custom <(755589436)>
  // end <(755589436)>
  GIVEN("a block timer") {
    // custom <(827648022)>
    using namespace ebisu::performance;
    // end <(827648022)>
    WHEN("work is done in the block") {
      // custom <(543342078)>

      Block_timer<>::Duration_t duration{};
      {
        Block_timer<> block_timer{duration};
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }

      // end <(543342078)>
      THEN("that work is timed") {
        // custom <(1073354778)>

        /// Require the duration to be somewhere around 1 second in nanos
        REQUIRE(duration.count() > 990000000);
        REQUIRE(duration.count() < 1200000000);

        {
          Block_timer<> block_timer{duration};
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // end <(1073354778)>
      }
    }
  }
}

}  // namespace performance
}  // namespace ebisu
