#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/utils/buffer.hpp"

// custom <custom includes>
#include <cstring>
// end <custom includes>

namespace ebisu {
namespace utils {
// custom <buffer begin namespace>
// end <buffer begin namespace>

SCENARIO("binary data to literal") {
  // custom <(560410815)>

  // end <(560410815)>
  GIVEN("buffer with data") {
    // custom <(425426083)>

    using namespace utils;
    char const *buff_start = "this is a test";
    char const *buff_end = buff_start + std::strlen(buff_start);

    // end <(425426083)>
    WHEN("binary data to literal is called") {
      // custom <(375209117)>

      auto literal = binary_data_to_literal(buff_start, buff_end);

      // end <(375209117)>
      THEN("data is written correctly") {
        // custom <(547326495)>

        REQUIRE(
            literal ==
            R"("\x74\x68\x69\x73\x20\x69\x73\x20\x61\x20\x74\x65\x73\x74")");

        // end <(547326495)>
      }
    }
  }
}

}  // namespace utils
}  // namespace ebisu
