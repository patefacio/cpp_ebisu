#include "fcs/orm/code_metrics/table/rusage_delta.hpp"
#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace orm {
namespace code_metrics {
namespace table {
  void test_rusage_delta() {
    // custom <rusage_delta>
    // end <rusage_delta>
  }

  void test_insert_delete_rows() {
    // testing insertion and deletion
  }

  void test_query_rows() {
    // test queries
    auto gw = Rusage_delta<>::instance();
    auto rows = gw.select_all_rows();
    Rusage_delta<>::print_recordset_as_table(rows, std::cout);
  }

  void test_update_rows() {
    // testing update
  }

} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  using namespace fcs::orm::code_metrics::table;
  using namespace boost::unit_test;
  test_suite* test= BOOST_TEST_SUITE( "<rusage_delta>" );
  test->add( BOOST_TEST_CASE( &test_rusage_delta ) );
  test->add( BOOST_TEST_CASE( &test_insert_delete_rows ) );
  test->add( BOOST_TEST_CASE( &test_query_rows ) );
  test->add( BOOST_TEST_CASE( &test_update_rows ) );
  return test;
}
