#include "fcs/orm/code_packages/table/code_packages.hpp"
#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace orm {
namespace code_packages {
namespace table {
  void test_code_packages() {
    // custom <code_packages>
    // end <code_packages>
  }

} // namespace table
} // namespace code_packages
} // namespace orm
} // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  using namespace fcs::orm::code_packages::table;
  using namespace boost::unit_test;
  test_suite* test= BOOST_TEST_SUITE( "<code_packages>" );
  test->add( BOOST_TEST_CASE( &test_code_packages ) );
  return test;
}
