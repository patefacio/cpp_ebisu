#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "fcs/raii/change_tracker.hpp"

// custom <custom includes>
// end <custom includes>

namespace fcs {
namespace raii {
SCENARIO("change tracker next value") {
  GIVEN("an int change tracker assigned to one") {
    // custom <(542814227)>

    using namespace fcs::raii;
    Change_tracker<int> change_tracker{1};

    // end <(542814227)>
    WHEN("a block sets current value to one and next value to three") {
      // custom <(794311972)>

      {
        Change_tracker_next_value<int> next_value{change_tracker, 3};
        CHECK(change_tracker.current() == 1);
        CHECK(next_value.next_value() == 3);
      }

      // end <(794311972)>
      THEN("when leaving block previous is one and current is three") {
        // custom <(25132442)>

        CHECK(change_tracker.previous() == 1);
        CHECK(change_tracker.current() == 3);

        // end <(25132442)>
      }
    }
  }
}

}  // namespace raii
}  // namespace fcs
