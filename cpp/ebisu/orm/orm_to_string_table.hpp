#ifndef __EBISU_ORM_ORM_TO_STRING_TABLE_HPP__
#define __EBISU_ORM_ORM_TO_STRING_TABLE_HPP__

#include "ebisu/orm/orm_common.hpp"
#include "ebisu/utils/streamers/table.hpp"
#include <string>

namespace ebisu {
namespace orm {
// custom <FcbEndNamespace orm_to_string_table>

template <typename Recordset>
inline void recordset_to_string_table(
    typename Recordset::Row_list_t const &recordset, String_list_t &header,
    String_table_t &data) {
  using Pkey_t = typename Recordset::Pkey_t;
  using Value_t = typename Recordset::Value_t;
  Pkey_t::member_names_list(header);
  Value_t::member_names_list(header);
  for (auto const &record : recordset) {
    String_list_t string_list;
    record.first.to_string_list(string_list);
    record.second.to_string_list(string_list);
    data.push_back(string_list);
  }
}

template <typename Recordset>
inline void print_recordset_as_table(
    typename Recordset::Row_list_t const &recordset, std::ostream &out) {
  using ebisu::utils::streamers::operator<<;
  String_list_t header;
  String_table_t data;
  recordset_to_string_table<Recordset>(recordset, header, data);
  out << ebisu::utils::streamers::Table_streamer<String_table_t>(data, header);
}

template <typename Recordset>
inline void values_to_string_table(
    typename Recordset::Value_list_t const &values, String_list_t &header,
    String_table_t &data) {
  typedef typename Recordset::Value_t Value_t;
  typename Recordset::Value_list_t::const_iterator it(values.begin());
  typename Recordset::Value_list_t::const_iterator end(values.end());
  Value_t::member_names_list(header);
  for (; it != end; ++it) {
    String_list_t string_list;
    it->to_string_list(string_list);
    data.push_back(string_list);
  }
}

template <typename Recordset>
inline void print_values_as_table(
    typename Recordset::Value_list_t const &values, std::ostream &out) {
  String_list_t header;
  String_table_t data;
  values_to_string_table<Recordset>(values, header, data);
  out << ebisu::utils::streamers::Table_streamer<String_table_t>(data, header);
}

// end <FcbEndNamespace orm_to_string_table>

}  // namespace orm
}  // namespace ebisu

#endif  // __EBISU_ORM_ORM_TO_STRING_TABLE_HPP__
