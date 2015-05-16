#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/linux_specific/umask_scoped_set.hpp"

// custom <custom includes>
#include <iostream>
// end <custom includes>

namespace ebisu {
namespace linux_specific {
SCENARIO("unit test umask scoped set") {
  GIVEN("current umask is something") {
    // custom <(851442918)>

    auto current_mask{umask(0)};
    REQUIRE(umask(0) == 0);

    // end <(851442918)>
    WHEN("setting umask to something else") {
      // custom <(394125197)>

      {
        /// *At this point mask is 0 - so here we set it*
        Umask_scoped_set scoped{S_IRUSR | S_IWUSR | S_IRGRP};
        REQUIRE(umask(S_IRUSR | S_IWUSR | S_IRGRP) ==
                (S_IRUSR | S_IWUSR | S_IRGRP));
      }

      // end <(394125197)>
      THEN("it is set and reverted on exit") {
        // custom <(975142741)>

        /// Since the block containing Umask_scoped_set has exited its raii
        /// dtor will revert mask to 0
        REQUIRE(umask(S_IRUSR) == 0);

        // end <(975142741)>
      }
    }
  }
}

}  // namespace linux_specific
}  // namespace ebisu
