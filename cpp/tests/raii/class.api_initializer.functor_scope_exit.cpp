#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "fcs/raii/api_initializer.hpp"

// custom <custom includes>
// end <custom includes>

namespace fcs {
namespace raii {
SCENARIO("functor runs on block exit") {
  GIVEN("functor in block") {
    // custom <(300063598)>
    std::cout << "Foo" << std::endl;
    // end <(300063598)>
    WHEN("block has exited") {
      // custom <(557460478)>
      // end <(557460478)>
      THEN("functor runs") {
        // custom <(224732472)>
        // end <(224732472)>
      }
    }
  }
}

}  // namespace raii
}  // namespace fcs
