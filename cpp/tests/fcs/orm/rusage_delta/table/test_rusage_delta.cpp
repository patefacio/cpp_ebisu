#include "fcs/orm/rusage_delta/table/rusage_delta.hpp"
#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace orm {
namespace rusage_delta {
namespace table {
  void test_rusage_delta() {
    // custom <rusage_delta>
    // end <rusage_delta>
  }

} // namespace table
} // namespace rusage_delta
} // namespace orm
} // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  using namespace fcs::orm::rusage_delta::table;
  using namespace boost::unit_test;
  test_suite* test= BOOST_TEST_SUITE( "<rusage_delta>" );
  test->add( BOOST_TEST_CASE( &test_rusage_delta ) );
  return test;
}
