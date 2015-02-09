#include "fcs/timestamp/timestamp.hpp"
#include "fcs/utils/random.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace utils {
  void test_random_source() {
    // custom <random_source>
    // end <random_source>
  }

} // namespace utils
} // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  using namespace fcs::utils;
  using namespace boost::unit_test;
  test_suite* test= BOOST_TEST_SUITE( "<random>" );
  test->add( BOOST_TEST_CASE( &test_random_source ) );
  return test;
}
