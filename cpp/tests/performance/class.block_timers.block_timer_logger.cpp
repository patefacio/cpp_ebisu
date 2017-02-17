#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/performance/block_timers.hpp"

// custom <custom includes>

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <cstdint>
#include <regex>

// end <custom includes>

namespace ebisu {
namespace performance {
// custom <block_timer_logger begin namespace>
// end <block_timer_logger begin namespace>

SCENARIO("block timer logger") {
  // custom <(594809812)>
  // end <(594809812)>
  GIVEN("a block timer") {
    // custom <(1053450319)>

    using namespace ebisu::performance;

    // end <(1053450319)>
    WHEN("work is done in the block") {
      // custom <(649598421)>

      std::ostringstream s;
      {
        Block_timer_logger<> btl{s, "test_block"};
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }

      // end <(649598421)>
      THEN("the timed values are logged") {
        // custom <(72524096)>

        boost::regex timing_re{"Block\\(test_block\\):\\s*(\\d+)"};
        boost::smatch match;
        auto matched = boost::regex_search(s.str(), match, timing_re);
        REQUIRE(matched == true);
        int64_t duration = boost::lexical_cast<int64_t>(match[1]);
        REQUIRE(duration > 990000000);
        REQUIRE(duration < 1200000000);

        std::cout << s.str();

        // end <(72524096)>
      }
    }
  }
}

}  // namespace performance
}  // namespace ebisu
