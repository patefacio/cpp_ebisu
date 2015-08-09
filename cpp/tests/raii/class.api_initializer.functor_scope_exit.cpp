#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/raii/api_initializer.hpp"

// custom <custom includes>
// end <custom includes>

namespace ebisu {
namespace raii {
// custom <functor_scope_exit begin namespace>
// end <functor_scope_exit begin namespace>

SCENARIO("functor runs on block exit") {
  // custom <(353523639)>
  // end <(353523639)>
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
}  // namespace ebisu
