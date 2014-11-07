#include "fcs/orm/code_metrics/table/code_locations.hpp"
#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace orm {
namespace code_metrics {
namespace table {
  void test_code_locations() {
    // custom <code_locations>
    // end <code_locations>
  }

  void test_create_rows() {
    // testing creation
  }

  void test_insert_rows() {
    // testing insertion
  }

  void test_update_rows() {
    // testing update
  }

  void test_delete_rows() {
    // testing delete
  }

} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  using namespace fcs::orm::code_metrics::table;
  using namespace boost::unit_test;
  test_suite* test= BOOST_TEST_SUITE( "<code_locations>" );
  test->add( BOOST_TEST_CASE( &test_code_locations ) );
  test->add( BOOST_TEST_CASE( &test_create_rows ) );
  test->add( BOOST_TEST_CASE( &test_insert_rows ) );
  test->add( BOOST_TEST_CASE( &test_update_rows ) );
  test->add( BOOST_TEST_CASE( &test_delete_rows ) );
  return test;
}
