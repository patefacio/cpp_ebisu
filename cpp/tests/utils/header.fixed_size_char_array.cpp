#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/utils/fixed_size_char_array.hpp"

// custom <custom includes>
// end <custom includes>

namespace ebisu {
namespace utils {
// custom <fixed_size_char_array begin namespace>
// end <fixed_size_char_array begin namespace>

SCENARIO("sizeof matches array size") {
  // custom <(696307170)>
  // end <(696307170)>
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
  // custom <(989281246)>
  // end <(989281246)>
  GIVEN("array size six inited with cstr size three") {
    // custom <(558622143)>
    Fixed_size_char_array<3> arr{"ottff"};

    // end <(558622143)>
    THEN("result has two chars and null") {
      // custom <(415599617)>
      CHECK(arr.operator std::string() == "ott");
      // end <(415599617)>
    }
  }
}
SCENARIO("array size initialized with larger cstr") {
  // custom <(811121160)>
  // end <(811121160)>
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
  // custom <(220485648)>
  // end <(220485648)>
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
SCENARIO("no null char") {
  // custom <(669588362)>
  // end <(669588362)>
  GIVEN("array with no null chars") {
    // custom <(939678555)>

    char const chars[] = "abcdeg";
    Fixed_size_char_array<5> const& arr =
        reinterpret_cast<Fixed_size_char_array<5> const&>(*chars);

    // end <(939678555)>
    THEN("streamer stops at array size") {
      // custom <(51789331)>

      REQUIRE(arr.str() == "abcde");

      // end <(51789331)>
    }
  }
}
SCENARIO("nassign") {
  // custom <(374273580)>
  // end <(374273580)>
  GIVEN("array of size eight") {
    // custom <(846450443)>

    std::string const s{"12345678"};
    Fixed_size_char_array<8> arr{s.c_str()};

    // end <(846450443)>
    WHEN("nassign on first four") {
      // custom <(544959022)>

      arr.nassign("abc", 3);

      // end <(544959022)>
      THEN("first four only assigned") {
        // custom <(429009704)>

        REQUIRE(arr.str() == "abc45678");

        // end <(429009704)>
      }
    }
  }
}
SCENARIO("equality operator works") {
  // custom <(25788391)>
  // end <(25788391)>
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
SCENARIO("streaming") {
  // custom <(172526230)>

  using Buffer_t = Fixed_size_char_array<10>;
  Buffer_t buff{"0123456789"};
  std::ostringstream out;
  out << buff;
  REQUIRE(out.str() == "0123456789");

  std::istringstream in("0123456789");
  in >> buff;
  REQUIRE(in.str() == "0123456789");

  // end <(172526230)>
}

}  // namespace utils
}  // namespace ebisu
