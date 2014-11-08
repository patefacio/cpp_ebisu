#include "fcs/orm/code_metrics/table/code_tick_timings.hpp"
#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace orm {
namespace code_metrics {
namespace table {
  void test_code_tick_timings() {
    // custom <code_tick_timings>
    // end <code_tick_timings>
  }

  void test_query_rows() {
    // test queries
    auto gw = Code_tick_timings<>::instance();
    auto rows = gw.select_all_rows();
    Code_tick_timings<>::print_recordset_as_table(rows, std::cout);
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
  test_suite* test= BOOST_TEST_SUITE( "<code_tick_timings>" );
  test->add( BOOST_TEST_CASE( &test_code_tick_timings ) );
  test->add( BOOST_TEST_CASE( &test_query_rows ) );
  test->add( BOOST_TEST_CASE( &test_create_rows ) );
  test->add( BOOST_TEST_CASE( &test_insert_rows ) );
  test->add( BOOST_TEST_CASE( &test_update_rows ) );
  test->add( BOOST_TEST_CASE( &test_delete_rows ) );
  return test;
}
