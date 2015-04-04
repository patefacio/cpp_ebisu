#include "fcs/orm/code_metrics/table/code_tick_timings.hpp"
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

void patch_rows(Code_locations<>::Row_list_t &rows) {
  auto code_packages_rows = Code_packages<>::instance().select_all_rows();
  BOOST_ASSERT(code_packages_rows.size() == num_rows);
  for (int i = 0; i < num_rows; ++i) {
    link_rows(rows[i], code_packages_rows[i]);
  }
}
void patch_rows(Code_tick_timings<>::Row_list_t &rows) {
  auto code_locations_rows = Code_locations<>::instance().select_all_rows();
  BOOST_ASSERT(code_locations_rows.size() == num_rows);
  for (int i = 0; i < num_rows; ++i) {
    link_rows(rows[i], code_locations_rows[i]);
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

template <>
inline Random_source &operator>>(Random_source &source,
                                 Code_locations_pkey &obj) {
  source >> obj.id;
  return source;
}

template <>
inline Random_source &operator>>(Random_source &source,
                                 Code_locations_value &obj) {
  source >> obj.code_packages_id >> obj.label >> obj.file_name >>
      obj.line_number >> obj.git_commit;
  return source;
}

template <>
inline Random_source &operator>>(Random_source &source,
                                 Code_locations<>::Row_t &row) {
  source >> row.first >> row.second;
  return source;
}

template <>
inline Random_source &operator>>(Random_source &source,
                                 Code_tick_timings_pkey &obj) {
  source >> obj.id;
  return source;
}

template <>
inline Random_source &operator>>(Random_source &source,
                                 Code_tick_timings_value &obj) {
  source >> obj.code_locations_id >> obj.created >> obj.start_processor >>
      obj.end_processor >> obj.cpu_mhz >> obj.debug >> obj.ticks >>
      obj.normalized_ns;
  return source;
}

template <>
inline Random_source &operator>>(Random_source &source,
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
void test_insert_update_delete_rows() {
  // testing insertion and deletion
  auto code_tick_timings_gw = Code_tick_timings<>::instance();
  delete_rows(code_tick_timings_gw);
  Code_tick_timings<>::Row_list_t code_tick_timings_rows;
  auto code_locations_gw = Code_locations<>::instance();
  delete_rows(code_locations_gw);
  Code_locations<>::Row_list_t code_locations_rows;
  auto code_packages_gw = Code_packages<>::instance();
  delete_rows(code_packages_gw);
  Code_packages<>::Row_list_t code_packages_rows;

  random_rows(code_packages_rows);
  insert_rows(code_packages_gw, code_packages_rows);
  random_rows(code_locations_rows);
  patch_rows(code_locations_rows);
  insert_rows(code_locations_gw, code_locations_rows);
  random_rows(code_tick_timings_rows);
  patch_rows(code_tick_timings_rows);
  insert_rows(code_tick_timings_gw, code_tick_timings_rows);

  randomize_row_values(code_packages_rows);
  update_rows(code_packages_gw, code_packages_rows);
  randomize_row_values(code_locations_rows);
  patch_rows(code_locations_rows);
  update_rows(code_locations_gw, code_locations_rows);
  randomize_row_values(code_tick_timings_rows);
  patch_rows(code_tick_timings_rows);
  update_rows(code_tick_timings_gw, code_tick_timings_rows);

  find_by_key_check(code_packages_gw, code_packages_rows);
  find_by_key_check(code_locations_gw, code_locations_rows);
  find_by_key_check(code_tick_timings_gw, code_tick_timings_rows);

  if (false) {
    Code_packages<>::print_recordset_as_table(code_packages_rows, std::cout);
    Code_locations<>::print_recordset_as_table(code_locations_rows, std::cout);
    Code_tick_timings<>::print_recordset_as_table(code_tick_timings_rows,
                                                  std::cout);
  }

  delete_rows(code_tick_timings_gw);
  delete_rows(code_locations_gw);
  delete_rows(code_packages_gw);
}

}  // namespace table
}  // namespace code_metrics
}  // namespace orm
}  // namespace fcs

boost::unit_test::test_suite *init_unit_test_suite(int, char *[]) {
  using namespace fcs::orm::code_metrics::table;
  using namespace boost::unit_test;
  test_suite *test = BOOST_TEST_SUITE("<code_tick_timings>");
  test->add(BOOST_TEST_CASE(&test_insert_update_delete_rows));
  return test;
}
