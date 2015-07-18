#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/linux_specific/signal_handler.hpp"

// custom <custom includes>
// end <custom includes>

namespace ebisu {
namespace linux_specific {
SCENARIO("catching signal") {
  GIVEN("registered handler") {
    // custom <(557956174)>

    using namespace ebisu::linux_specific;

    auto& signal_handler = Application_signal_handler<>::instance();

    bool signal_processed = false;
    signal_handler.add_handler([&signal_processed](int signal) {
      if (!signal_processed) {
        signal_processed = true;
        return true;
      } else {
        return false;
      }
    });

    // end <(557956174)>
    WHEN("signal sent") {
      // custom <(374031612)>

      REQUIRE(signal_processed == false);

      /// Send the signal
      kill(::getpid(), SIGUSR1);

      /// Give some time to deliver the signal
      ::sleep(1);

      REQUIRE(signal_processed == true);

      //// Following is required to cleanly exit handler thread
      Application_signal_handler<>::instance().stop_handler_thread();

      // end <(374031612)>
      THEN("signal handled") {
        // custom <(806700410)>
        // end <(806700410)>
      }
    }
  }
}

}  // namespace linux_specific
}  // namespace ebisu
