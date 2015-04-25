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
  GIVEN("array size six inited with cstr size three") {
    // custom <(558622143)>
    Fixed_size_char_array<3> arr{"ottff"};

    // end <(558622143)>
    THEN("result has two chars and null") {
      // custom <(415599617)>
      CHECK(arr.operator std::string() == "ot");
      CHECK(arr[2] == 0);
      // end <(415599617)>
    }
  }
}
SCENARIO("array size initialized with larger cstr") {
  GIVEN("array size three inited with cstr size six") {
    // custom <(995830977)>
    Fixed_size_char_array<6> arr{"ab"};

    // end <(995830977)>
    THEN("result has two chars and null") {
      // custom <(991018705)>

      CHECK(arr.operator std::string() == "ab");
      CHECK(arr[2] == 0);

      // end <(991018705)>
    }
  }
}
SCENARIO("index operator works") {
  GIVEN("array initialized with six chars") {
    // custom <(1022387932)>

    std::string const s{"otff"};
    Fixed_size_char_array<5> arr{s.c_str()};

    // end <(1022387932)>
    THEN("all chars are accessible") {
      // custom <(581427270)>

      for (size_t i = 0; i < 5; i++) {
        REQUIRE(s[i] == arr[i]);
      }

      // end <(581427270)>
    }
  }
}
SCENARIO("equality operator works") {
  GIVEN("array initted with string") {
    // custom <(518352325)>

    char const* sample_cstr{"foobar"};
    Fixed_size_char_array<7> sample{sample_cstr};

    // end <(518352325)>
    THEN("equals that string") {
      // custom <(611697358)>
      REQUIRE(sample == sample_cstr);
      // end <(611697358)>
    }
    THEN("does not equal another string") {
      // custom <(161295243)>
      char const* bogus{"goober"};
      REQUIRE((sample != bogus));
      // end <(161295243)>
    }
    THEN("str accessor works") {
      // custom <(128952914)>
      REQUIRE(sample.str().length() == 6);
      // end <(128952914)>
    }
  }
}

}  // namespace utils
}  // namespace fcs
