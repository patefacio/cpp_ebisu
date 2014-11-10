#include "fcs/orm/code_metrics/table/code_locations.hpp"
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
     Code_locations_pkey &obj) {
    source >> obj.id;
    return source;
  }

  template< >
  inline Random_source & operator>>
    (Random_source &source,
     Code_locations_value &obj) {
    source >> obj.code_packages_id
      >> obj.label
      >> obj.file_name
      >> obj.line_number
      >> obj.git_commit;
    return source;
  }


  template< >
  inline Random_source & operator>>
    (Random_source &source,
     Code_locations<>::Row_t &row) {
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
  void test_code_locations() {
    // custom <code_locations>
    // end <code_locations>
  }

  void test_insert_delete_rows() {
    // testing insertion and deletion
  }

  void test_query_rows() {
    // test queries
    auto gw = Code_locations<>::instance();
    auto rows = gw.select_all_rows();
    Code_locations<>::print_recordset_as_table(rows, std::cout);
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
  test_suite* test= BOOST_TEST_SUITE( "<code_locations>" );
  test->add( BOOST_TEST_CASE( &test_code_locations ) );
  test->add( BOOST_TEST_CASE( &test_insert_delete_rows ) );
  test->add( BOOST_TEST_CASE( &test_query_rows ) );
  test->add( BOOST_TEST_CASE( &test_update_rows ) );
  return test;
}
