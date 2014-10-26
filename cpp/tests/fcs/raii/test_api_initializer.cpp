#include "fcs/raii/api_initializer.hpp"
#include <boost/test/included/unit_test.hpp>
#include <vector>

// custom <FcbPreNamespace api_initializer>

using namespace std;
vector< string > strings;


void my_init() {
  strings.emplace_back("my_init");
}

void my_init2() {
  strings.emplace_back("my_init2");
}

void my_uninit() {
  strings.emplace_back("my_uninit");
  cout << "Running my_uninit uninitializer" << endl;
}

void my_uninit2() {
  strings.emplace_back("my_uninit2");
  cout << "Running my_uninit2 uninitializer" << endl;
}

void foobar() {
  strings.emplace_back("foobar");
  cout << "Running foobar uninitializer" << endl;
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
      Api_initializer<> registry { &my_init, &foobar };

      BOOST_REQUIRE(strings == vector< string > { "my_init" });

      // In the example below the registry2 object should not trigger a call
      // to my_init since it should have already been initialized. The
      // Api_initializer_registry ensures this.

      Api_initializer<> registry2 = { &my_init, &foobar };

      BOOST_REQUIRE(strings == (vector< string > { "my_init" }));

      Api_initializer<> registry3 = { &my_init2, &my_uninit2 };

      BOOST_REQUIRE(strings == (vector< string > { "my_init", "my_init2" }));

      Api_initializer<> registry4 = { 0, &my_uninit };

    }

    BOOST_REQUIRE(strings == (vector< string > { "my_init", "my_init2" }));

    // end <functor_scope_exit>
  }

} // namespace raii
} // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  using namespace fcs::raii;
  using namespace boost::unit_test;
  test_suite* test= BOOST_TEST_SUITE( "<api_initializer>" );
  test->add( BOOST_TEST_CASE( &test_functor_scope_exit ) );
  return test;
}
