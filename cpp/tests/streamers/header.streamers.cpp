#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/utils/streamers/streamers.hpp"

// custom <custom includes>
// end <custom includes>

namespace ebisu {
namespace utils {
namespace streamers {
// custom <streamers begin namespace>
// end <streamers begin namespace>

SCENARIO("int 8s show as numbers") {
  // custom <(958958940)>

  {
    std::int8_t i = 42;
    char x = '*';
    REQUIRE(x == i);
    {
      std::ostringstream s;
      s << i << std::endl;
      REQUIRE(s.str() == "42\n");
    }
    {
      std::ostringstream s;
      s << x << std::endl;
      REQUIRE(s.str() == "*\n");
    }
  }

  // end <(958958940)>
}

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu
