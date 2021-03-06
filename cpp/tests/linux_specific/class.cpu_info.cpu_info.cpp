#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/linux_specific/cpu_info.hpp"

// custom <custom includes>
// end <custom includes>

namespace ebisu {
namespace linux_specific {
// custom <cpu_info begin namespace>
// end <cpu_info begin namespace>

SCENARIO("cpu info") {
  // custom <(28060639)>
  // end <(28060639)>
  GIVEN("the single cpu info instance") {
    // custom <(954218043)>
    using namespace std;
    using namespace ebisu::linux_specific;

    Cpu_info& cpu_info = Cpu_info::instance();

    // end <(954218043)>
    WHEN("accessing processors") {
      // custom <(1016472630)>
      auto processors = cpu_info.processors();
      // end <(1016472630)>
      THEN("some processors are found") {
        // custom <(536932337)>
        CHECK(processors.size() > 0);
        // end <(536932337)>
      }
      THEN("the first processor has flags") {
        // custom <(456414906)>
        CHECK(processors.front().flags().size() > 0);
        // end <(456414906)>
      }
      THEN("the fpu flag is yes") {
        // custom <(328318562)>
        CHECK(processors.front().fpu() == "yes");
        // end <(328318562)>
      }
    }
  }
}

}  // namespace linux_specific
}  // namespace ebisu
