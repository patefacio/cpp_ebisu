#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/performance/block_rusage.hpp"

// custom <custom includes>

void use_data(char* data) { data[0] = 0; }

// end <custom includes>

namespace ebisu {
namespace performance {
// custom <block_rusage begin namespace>
// end <block_rusage begin namespace>

SCENARIO("block rusage") {
  // custom <(845463434)>
  // end <(845463434)>
  GIVEN("a block rusage") {
    // custom <(711407587)>

    char* data;
    Rusage_delta rusage_delta;

    // end <(711407587)>
    WHEN("work is done in the block") {
      // custom <(200334017)>

      {
        Block_rusage block_rusage{rusage_delta};
        for (size_t i = 1; i < 1000000; i++) {
          data = new char[i];
          use_data(data);
          delete[] data;
        }
      }

      // end <(200334017)>
      THEN("the rusage delta is captured") {
        // custom <(515695535)>

        std::cout << rusage_delta;

        // end <(515695535)>
      }
    }
  }
}

}  // namespace performance
}  // namespace ebisu
