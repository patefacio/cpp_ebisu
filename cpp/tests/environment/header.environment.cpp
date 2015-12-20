#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/environment/environment.hpp"

// custom <custom includes>
// end <custom includes>

namespace ebisu {
namespace environment {
// custom <environment begin namespace>
// end <environment begin namespace>

SCENARIO("read environment") {
  // custom <(585124688)>

  setenv("PATH", "/foo:/goo", 1);
  auto& env = Environment::instance();
  auto& env_map = env.environment();
  auto &path_variable_map = env.path_variable_map();

  REQUIRE(env_map.find("HOME")->second == getenv("HOME"));
  Environment::Path_list_t paths = path_variable_map.find("PATH")->second;
  REQUIRE(paths[0].string() == "/foo");
  REQUIRE(paths[1].string() == "/goo");

  // end <(585124688)>
}

}  // namespace environment
}  // namespace ebisu
