#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace raii {
  void api_initializer() {
  }



} // namespace raii
} // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  using namespace fcs::raii;
  using namespace boost::unit_test;
  test_suite* test= BOOST_TEST_SUITE( "Unit test <api_initializer>" );
  test->add( BOOST_TEST_CASE( &test_api_initializer ) );
  return test;
}
