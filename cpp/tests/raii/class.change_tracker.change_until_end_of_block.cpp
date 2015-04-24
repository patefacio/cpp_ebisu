#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "fcs/raii/change_tracker.hpp"

// custom <custom includes>
// end <custom includes>

namespace test {
SCENARIO("change until end of block") {
  GIVEN("an int initialized to one") {
    // custom <(841661806) an int initialized to one>
    int x{1};
    // end <(841661806) an int initialized to one>
    WHEN("a block changes the value to three") {
      // custom <(485840119) a block changes the value to three>
      {
        fcs::raii::Change_until_end_of_block<int> change_until_end_of_block{x,
                                                                            3};
        CHECK(x == 3);
      }
      // end <(485840119) a block changes the value to three>
      THEN("after the block exits it reverts to one") {
        // custom <(1040340518) after the block exits it reverts to one>
        CHECK(x == 1);
        // end <(1040340518) after the block exits it reverts to one>
      }
    }
  }
}

}  // namespace test
