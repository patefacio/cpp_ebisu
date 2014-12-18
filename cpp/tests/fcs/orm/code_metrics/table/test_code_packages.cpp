#include "fcs/orm/code_metrics/table/code_packages.hpp"
#include "fcs/utils/streamers/random.hpp"
#include <boost/test/included/unit_test.hpp>

using namespace fcs::orm::code_metrics::table;
using namespace fcs::utils::streamers;
using fcs::utils::streamers::operator<<;

int const num_rows = 20;
Random_source random_source;

template <typename GW>
void delete_rows(GW &gw) {
  gw.delete_all_rows();
  auto rows = gw.select_all_rows();
  BOOST_REQUIRE(rows.empty());
}

template <typename Row_list_t>
void random_rows(Row_list_t &rows) {
  rows.reserve(num_rows);
  rows.clear();
  for (int i = 0; i < num_rows; ++i) {
    typename Row_list_t::value_type row;
    random_source >> row;
    rows.push_back(row);
  }
}

template <typename Row_list_t>
void randomize_row_values(Row_list_t &rows) {
  for (int i = 0; i < num_rows; ++i) {
    random_source >> rows[i].second;
  }
}

template <typename GW>
void insert_rows(GW &gw, typename GW::Row_list_t &rows) {
  gw.insert(rows);
  auto again = gw.select_all_rows();
  BOOST_REQUIRE(again.size() == rows.size());
  for (int i = 0; i < rows.size(); ++i) {
    BOOST_REQUIRE(again[i].second == rows[i].second);
  }
  std::swap(again, rows);
}

template <typename GW>
void update_rows(GW &gw, typename GW::Row_list_t const &rows) {
  gw.update(rows);
  auto again = gw.select_all_rows();
  BOOST_REQUIRE(again.size() == rows.size());
  for (int i = 0; i < rows.size(); ++i) {
    BOOST_REQUIRE(again[i].second == rows[i].second);
  }
}

template <typename GW>
void find_by_key_check(GW &gw, typename GW::Row_list_t const &rows) {
  typename GW::Value_t value;
  for (int i = 0; i < rows.size(); ++i) {
    gw.find_row_by_key(rows[i].first, value);
    BOOST_REQUIRE(rows[i].second == value);
  }
}

namespace fcs {
namespace utils {
namespace streamers {
// random row generation

template <>
inline Random_source &operator>>(Random_source &source,
                                 Code_packages_pkey &obj) {
  source >> obj.id;
  return source;
}

template <>
inline Random_source &operator>>(Random_source &source,
                                 Code_packages_value &obj) {
  source >> obj.name >> obj.descr;
  return source;
}

template <>
inline Random_source &operator>>(Random_source &source,
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
  auto code_packages_gw = Code_packages<>::instance();
  delete_rows(code_packages_gw);
  Code_packages<>::Row_list_t code_packages_rows;

  random_rows(code_packages_rows);
  insert_rows(code_packages_gw, code_packages_rows);

  randomize_row_values(code_packages_rows);
  update_rows(code_packages_gw, code_packages_rows);

  find_by_key_check(code_packages_gw, code_packages_rows);

  if (false) {
    Code_packages<>::print_recordset_as_table(code_packages_rows, std::cout);
  }

  delete_rows(code_packages_gw);
}

}  // namespace table
}  // namespace code_metrics
}  // namespace orm
}  // namespace fcs

boost::unit_test::test_suite *init_unit_test_suite(int, char * []) {
  using namespace fcs::orm::code_metrics::table;
  using namespace boost::unit_test;
  test_suite *test = BOOST_TEST_SUITE("<code_packages>");
  test->add(BOOST_TEST_CASE(&test_code_packages));
  test->add(BOOST_TEST_CASE(&test_insert_update_delete_rows));
  return test;
}
