#include "fcs/orm/code_locations/table/code_locations.hpp"
#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace orm {
namespace code_locations {
namespace table {
  void test_create_rows() {
    // custom <create_rows>
    // end <create_rows>
  }

  void test_insert_rows() {
    // custom <insert_rows>
    // end <insert_rows>
  }

  void test_update_rows() {
    // custom <update_rows>
    // end <update_rows>
  }

  void test_delete_rows() {
    // custom <delete_rows>
    // end <delete_rows>
  }

  void test_code_locations() {
    // custom <code_locations>
    // end <code_locations>
  }

} // namespace table
} // namespace code_locations
} // namespace orm
} // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  using namespace fcs::orm::code_locations::table;
  using namespace boost::unit_test;
  test_suite* test= BOOST_TEST_SUITE( "<code_locations>" );
  test->add( BOOST_TEST_CASE( &test_create_rows ) );
  test->add( BOOST_TEST_CASE( &test_insert_rows ) );
  test->add( BOOST_TEST_CASE( &test_update_rows ) );
  test->add( BOOST_TEST_CASE( &test_delete_rows ) );
  test->add( BOOST_TEST_CASE( &test_code_locations ) );
  return test;
}
