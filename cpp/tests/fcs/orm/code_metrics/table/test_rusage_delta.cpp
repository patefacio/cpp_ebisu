#include "fcs/orm/code_metrics/table/rusage_delta.hpp"
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
     Rusage_delta_pkey &obj) {
    source >> obj.id;
    return source;
  }

  template< >
  inline Random_source & operator>>
    (Random_source &source,
     Rusage_delta_value &obj) {
    source >> obj.code_locations_id
      >> obj.created
      >> obj.start_processor
      >> obj.end_processor
      >> obj.cpu_mhz
      >> obj.debug
      >> obj.user_time_sec
      >> obj.user_time_usec
      >> obj.system_time_sec
      >> obj.system_time_usec
      >> obj.ru_maxrss
      >> obj.ru_ixrss
      >> obj.ru_idrss
      >> obj.ru_isrss
      >> obj.ru_minflt
      >> obj.ru_majflt
      >> obj.ru_nswap
      >> obj.ru_inblock
      >> obj.ru_oublock
      >> obj.ru_msgsnd
      >> obj.ru_msgrcv
      >> obj.ru_nsignals
      >> obj.ru_nvcsw
      >> obj.ru_nivcsw;
    return source;
  }


  template< >
  inline Random_source & operator>>
    (Random_source &source,
     Rusage_delta<>::Row_t &row) {
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
