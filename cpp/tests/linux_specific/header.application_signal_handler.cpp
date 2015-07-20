#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/linux_specific/application_signal_handler.hpp"

// custom <custom includes>
// end <custom includes>

namespace ebisu {
namespace linux_specific {
SCENARIO("catching signal") {
  GIVEN("registered handler") {
    // custom <(810705097)>

    using namespace ebisu::linux_specific;

    auto& signal_handler = Application_signal_handler<>::instance();

    bool signal_processed = false;
    signal_handler.add_handler([&signal_processed](int signal) {
      signal_processed = true;
      linux_specific_logger->info("Client processed {:x} returning true",
                                  signal);
      return true;
    });

    // end <(810705097)>
    WHEN("signal sent") {
      // custom <(529500824)>

      REQUIRE(signal_processed == false);

      /// Send the signal
      kill(::getpid(), SIGUSR1);

      /// Give some time to deliver the signal
      ::sleep(1);

      // end <(529500824)>
      THEN("signal handled") {
        // custom <(723572258)>

        REQUIRE(signal_processed == true);

        //// Following is required to cleanly exit handler thread
        Application_signal_handler<>::instance().stop_handler_thread();

        // end <(723572258)>
      }
    }
  }
}

}  // namespace linux_specific
}  // namespace ebisu
