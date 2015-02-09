#include "fcs/raii/api_initializer.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <boost/test/included/unit_test.hpp>
#include <vector>

// custom <FcbPreNamespace api_initializer>

using fcs::utils::streamers::operator<<;
using namespace std;

vector<string> init_strings;

void my_init1() { init_strings.emplace_back("my_init1"); }

void my_init2() { init_strings.emplace_back("my_init2"); }

void my_uninit1() {
  auto back = init_strings.back();
  init_strings.pop_back();
  assert(back == "my_init1" && init_strings.size() == 0);
  cout << "Finished final uninit" << endl;
}

void my_uninit2() {
  auto back = init_strings.back();
  init_strings.pop_back();
  assert(back == "my_init2");
}

void my_uninit3() {
  auto back = init_strings.back();
  init_strings.pop_back();
  assert(back == "my_init3");
}

// end <FcbPreNamespace api_initializer>

namespace fcs {
namespace raii {
void test_functor_scope_exit() {
  // custom <functor_scope_exit>

  // In general, api_initializers are intended to be used as global static
  // objects to initialize data specific to an api. Here we are only
  // checking the initialization functions. Uninitialization functions end
  // up running in proper order after main completes when the
  // api_initializer_registry is destructed.

  {
    Api_initializer<> registry{&my_init1, &my_uninit1};

    BOOST_REQUIRE(init_strings == vector<string>{"my_init1"});

    // In the example below the registry2 object should not trigger a call
    // to my_init1 since it should have already been initialized. The
    // Api_initializer_registry ensures this.

    Api_initializer<> registry2 = {&my_init1, &my_uninit1};

    BOOST_REQUIRE(init_strings == (vector<string>{"my_init1"}));

    Api_initializer<> registry3 = {&my_init2, &my_uninit2};

    BOOST_REQUIRE(init_strings == (vector<string>{"my_init1", "my_init2"}));

    // Null passed in causes no initialization function to be run
    Api_initializer<> registry4 = {0, &my_uninit3};

    BOOST_REQUIRE(init_strings == (vector<string>{"my_init1", "my_init2"}));

    // Add the third one here for symmetry
    init_strings.emplace_back("my_init3");
  }

  BOOST_REQUIRE(init_strings ==
                (vector<string>{"my_init1", "my_init2", "my_init3"}));

  // end <functor_scope_exit>
}

}  // namespace raii
}  // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int, char* []) {
  using namespace fcs::raii;
  using namespace boost::unit_test;
  test_suite* test = BOOST_TEST_SUITE("<api_initializer>");
  test->add(BOOST_TEST_CASE(&test_functor_scope_exit));
  return test;
}
