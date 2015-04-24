#define CATCH_CONFIG_MAIN

#include "catch.hpp"

namespace test {
SCENARIO("basics tests") {
  GIVEN("a is ready to ao") {
    // custom <(243607555) a is ready to ao>
    // end <(243607555) a is ready to ao>
    WHEN("b finishes eating") {
      // custom <(955496004) b finishes eating>
      // end <(955496004) b finishes eating>
      THEN("we_ride") {
        // custom <(871402027) we ride>
        // end <(871402027) we ride>
      }
      THEN("we_fly") {
        // custom <(333779757) we fly>
        // end <(333779757) we fly>
      }
    }
    WHEN("c finishes working") {
      // custom <(51212972) c finishes working>
      // end <(51212972) c finishes working>
    }
  }
  GIVEN("we eat fish") {
    // custom <(37755127) we eat fish>
    // end <(37755127) we eat fish>
    WHEN("we get hungry") {
      // custom <(4519149) we get hungry>
      // end <(4519149) we get hungry>
      THEN("we_go_fishing") {
        // custom <(655804033) we go fishing>
        // end <(655804033) we go fishing>
      }
    }
  }
}

}  // namespace test
