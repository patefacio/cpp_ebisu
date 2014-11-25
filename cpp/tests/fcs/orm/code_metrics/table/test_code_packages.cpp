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
    (Random_source &source, Code_packages_pkey &obj) {
    source >> obj.id;
    return source;
  }

  template< >
  inline Random_source & operator>>
    (Random_source &source, Code_packages_value &obj) {
    source >> obj.name
      >> obj.descr;
    return source;
  }


  template< >
  inline Random_source & operator>>
    (Random_source &source, Code_packages<>::Row_t &row) {
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
    auto code_packages_gw = Code_packages<>::instance();
    Code_packages<>::Row_list_t code_packages_rows;
    {
      code_packages_gw.delete_all_rows();
      auto rows = code_packages_gw.select_all_rows();
      BOOST_REQUIRE(rows.empty());
    }

    // create some records with random data
    int const num_rows = 20;
    Random_source random_source;

    for(int i=0; i<num_rows; ++i) {

      // Declare all rows
      Code_packages<>::Row_t code_packages_row;

      // Generate random data for all rows
      random_source >> code_packages_row;


      // Link up reference ids

      // Push related records
      code_packages_rows.push_back(code_packages_row);

    }

    // insert those records, select back and validate
    code_packages_gw.insert(code_packages_rows);
    auto post_insert_code_packages_rows =
      code_packages_gw.select_all_rows();
    BOOST_REQUIRE(post_insert_code_packages_rows.size() == num_rows);

    for(size_t i=0; i<num_rows; i++) {
      BOOST_REQUIRE(code_packages_rows[i].second ==
                    post_insert_code_packages_rows[i].second)
      std::swap(code_packages_rows, post_insert_code_packages_rows);
    }

    // now update all values in memory with new random data
    auto updated_code_packages_rows = code_packages_rows;
    for(size_t i=0; i<num_rows; i++) {
      ramdon_source >> updated_code_packages_rows[i].second;
      BOOST_REQUIRE(updated_code_packages_rows[i].second !=
                    code_packages_rows[i].second);

    }

    if(false) {
      Code_packages<>::print_recordset_as_table(
        updated_code_packages_rows, std::cout);
    }

    // push updates to database via update
    code_packages_gw.update(updated_code_packages_rows);

    // verify the updates
    for(size_t i=0; i<num_rows; i++) {
      {
        Code_packages<>::Value_t value;
        bool found = code_packages_gw.find_row_by_key(
          updated_code_packages_rows[i].first, value);
        BOOST_REQUIRE(found);
        BOOST_REQUIRE(value == updated_code_packages_rows[i].second);
      }
    }

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
  return test;
}
