#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "fcs/utils/fixed_size_char_array.hpp"

// custom <custom includes>
// end <custom includes>

namespace fcs {
namespace utils {
SCENARIO("sizeof matches array size") {
  GIVEN("fixed size char array of size six") {
    // custom <(506041385)>

    Fixed_size_char_array<6> arr;

    // end <(506041385)>
    THEN("sizeof is a match") {
      // custom <(424685196)>

      CHECK(sizeof(arr) == 6);

      // end <(424685196)>
    }
  }
}
SCENARIO("array size initialized with smaller cstr") {
  GIVEN("array size three inited with cstr size six") {
    // custom <(613442107)>

    Fixed_size_char_array<3> arr { "ottff" };

    // end <(613442107)>
    THEN("result has two chars and null") {
      // custom <(174694459)>

      CHECK(arr.operator std::string() == "ot");
      CHECK(arr[2] == 0);

      // end <(174694459)>
    }
  }
}

}  // namespace utils
}  // namespace fcs
