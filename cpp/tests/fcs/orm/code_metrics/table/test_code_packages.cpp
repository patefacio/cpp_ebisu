#include "fcs/orm/code_metrics/table/code_packages.hpp"
#include "fcs/utils/streamers/random.hpp"
#include <boost/test/included/unit_test.hpp>


using namespace fcs::orm::code_metrics::table;
using namespace fcs::utils::streamers;
using fcs::utils::streamers::operator<<;

namespace fcs {
namespace utils {
namespace streamers {
  // random row generation

  template< >
  inline Random_source & operator>>
    (Random_source &source,
     Code_packages_pkey &obj) {
    source >> obj.id;
    return source;
  }

  template< >
  inline Random_source & operator>>
    (Random_source &source,
     Code_packages_value &obj) {
    source >> obj.name
      >> obj.descr;
    return source;
  }


  template< >
  inline Random_source & operator>>
    (Random_source &source,
     Code_packages<>::Row_t &row) {
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
  void test_code_packages() {
    // custom <code_packages>
    // end <code_packages>
  }

  void test_insert_update_delete_rows() {
    // testing insertion and deletion
    auto gw = Code_packages<>::instance();
    // first clear out any existing rows and ensure empty
    gw.delete_all_rows();
    auto all_rows = gw.select_all_rows();
    BOOST_REQUIRE(all_rows.empty());

    // create some records with random data
    int const num_rows = 20;
    Random_source random_source;
    Code_packages<>::Row_t row;
    for(int i=0; i<num_rows; ++i) {
      random_source >> row;
      all_rows.push_back(row);
    }

    // insert those records, select back and validate
    gw.insert(all_rows);
    {
      auto again = gw.select_all_rows();
      BOOST_REQUIRE(again.size() == num_rows);
      for(size_t i=0; i<num_rows; i++) {
        BOOST_REQUIRE(again[i].second == all_rows[i].second);

      }
      std::swap(again, all_rows);
    }

    // now update all values in memory with new random data
    auto updated_rows = all_rows;
    BOOST_REQUIRE(updated_rows == all_rows);
    for(auto & row : updated_rows) {
      size_t index = std::distance(&updated_rows.front(), &row);
      random_source >> row.second;
      BOOST_REQUIRE(row.second != all_rows[index].second);
    }
    Code_packages<>::print_recordset_as_table(updated_rows, std::cout);
    // push updates to database via update
    gw.update(updated_rows);
    {
      for(size_t i=0; i<num_rows; i++) {
        Code_packages<>::Value_t value;
        bool found = gw.find_row_by_key(updated_rows[i].first, value);
        BOOST_REQUIRE(found);
        BOOST_REQUIRE(value == updated_rows[i].second);
      }
    }

  }

  void test_query_rows() {
    // test queries
    auto gw = Code_packages<>::instance();
    auto rows = gw.select_all_rows();
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
  test_suite* test= BOOST_TEST_SUITE( "<code_packages>" );
  test->add( BOOST_TEST_CASE( &test_code_packages ) );
  test->add( BOOST_TEST_CASE( &test_insert_update_delete_rows ) );
  test->add( BOOST_TEST_CASE( &test_query_rows ) );
  test->add( BOOST_TEST_CASE( &test_update_rows ) );
  return test;
}
