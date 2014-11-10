#include "fcs/orm/code_metrics/table/code_tick_timings.hpp"
#include "fcs/utils/streamers/random.hpp"
#include <boost/test/included/unit_test.hpp>

// custom <random record generation>
// end <random record generation>

namespace fcs {
namespace utils {
namespace streamers {
  // random row generation
  using namespace fcs::orm::code_metrics::table;

  template< >
  inline Random_source & operator>>
    (Random_source &source,
     Code_tick_timings_pkey &obj) {
    source >> obj.id;
    return source;
  }

  template< >
  inline Random_source & operator>>
    (Random_source &source,
     Code_tick_timings_value &obj) {
    source >> obj.code_locations_id
      >> obj.created
      >> obj.start_processor
      >> obj.end_processor
      >> obj.cpu_mhz
      >> obj.debug
      >> obj.ticks
      >> obj.normalized_ns;
    return source;
  }


  template< >
  inline Random_source & operator>>
    (Random_source &source,
     Code_tick_timings<>::Row_t &row) {
    source >> row.first >> row.second;
    return source;
  }

}
}
}

namespace fcs {
namespace orm {
namespace code_metrics {
namespace table {
  void test_code_tick_timings() {
    // custom <code_tick_timings>
    // end <code_tick_timings>
  }

  void test_insert_delete_rows() {
    // testing insertion and deletion
  }

  void test_query_rows() {
    // test queries
    auto gw = Code_tick_timings<>::instance();
    auto rows = gw.select_all_rows();
    Code_tick_timings<>::print_recordset_as_table(rows, std::cout);
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
  test_suite* test= BOOST_TEST_SUITE( "<code_tick_timings>" );
  test->add( BOOST_TEST_CASE( &test_code_tick_timings ) );
  test->add( BOOST_TEST_CASE( &test_insert_delete_rows ) );
  test->add( BOOST_TEST_CASE( &test_query_rows ) );
  test->add( BOOST_TEST_CASE( &test_update_rows ) );
  return test;
}
