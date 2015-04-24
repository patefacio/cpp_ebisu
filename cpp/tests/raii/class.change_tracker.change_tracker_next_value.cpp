#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "fcs/raii/change_tracker.hpp"

// custom <custom includes>
// end <custom includes>

namespace test {
SCENARIO("change tracker next value") {
  GIVEN("an int change tracker assigned to one") {
    // custom <(542814227) an int change tracker assigned to one>

    using namespace fcs::raii;

    Change_tracker ct{1};

    // end <(542814227) an int change tracker assigned to one>
    WHEN("a block sets current value to one and next value to three") {
      // custom <(794311972) a block sets current value to one and next value to
      // three>
      // end <(794311972) a block sets current value to one and next value to
      // three>
      THEN("when leaving block the values revert") {
        // custom <(455146511) when leaving block the values revert>
        // end <(455146511) when leaving block the values revert>
      }
    }
  }
}

}  // namespace test
