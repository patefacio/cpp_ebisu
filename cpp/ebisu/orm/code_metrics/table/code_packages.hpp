#ifndef __EBISU_ORM_CODE_METRICS_TABLE_CODE_PACKAGES_HPP__
#define __EBISU_ORM_CODE_METRICS_TABLE_CODE_PACKAGES_HPP__

#include "ebisu/orm/code_metrics/code_metrics_common.hpp"
#include "ebisu/orm/orm_to_string_table.hpp"
#include "ebisu/orm/otl_utils.hpp"
#include "ebisu/utils/block_indenter.hpp"
#include "ebisu/utils/streamers/random.hpp"
#include <boost/any.hpp>
#include <cstdint>
#include <iosfwd>
#include <sstream>
#include <utility>
#include <vector>

namespace ebisu {
namespace orm {
namespace code_metrics {
namespace table {
struct Code_packages_pkey {
  bool operator==(Code_packages_pkey const& rhs) const {
    return this == &rhs || (id == rhs.id);
  }

  bool operator!=(Code_packages_pkey const& rhs) const {
    return !(*this == rhs);
  }

  bool operator<(Code_packages_pkey const& rhs) const {
    return id != rhs.id ? id < rhs.id : (false);
  }

  friend inline std::ostream& operator<<(std::ostream& out,
                                         Code_packages_pkey const& item) {
    out << "Code_packages_pkey(" << &item << ") {";
    out << "\n  id:" << item.id;
    out << "\n}\n";
    return out;
  }

  /// Access to list of names of members
  static inline void member_names_list(String_list_t& out) {
    out.push_back("id");
  }

  /// The values of the members as list of strings
  inline void to_string_list(String_list_t& out) const {
    out.push_back(boost::lexical_cast<std::string>(id));
  }

  int32_t id;
};

inline otl_stream& operator<<(otl_stream& out,
                              Code_packages_pkey const& value) {
  out << value.id;
  return out;
}

inline otl_stream& operator>>(otl_stream& src, Code_packages_pkey& value) {
  src >> value.id;
  return src;
}

struct Code_packages_value {
  bool operator==(Code_packages_value const& rhs) const {
    return this == &rhs || (name == rhs.name && descr == rhs.descr);
  }

  bool operator!=(Code_packages_value const& rhs) const {
    return !(*this == rhs);
  }

  bool operator<(Code_packages_value const& rhs) const {
    return name != rhs.name
               ? name < rhs.name
               : (descr != rhs.descr ? descr < rhs.descr : (false));
  }

  friend inline std::ostream& operator<<(std::ostream& out,
                                         Code_packages_value const& item) {
    out << "Code_packages_value(" << &item << ") {";
    out << "\n  name:" << item.name;
    out << "\n  descr:" << item.descr;
    out << "\n}\n";
    return out;
  }

  /// Access to list of names of members
  static inline void member_names_list(String_list_t& out) {
    out.push_back("name");
    out.push_back("descr");
  }

  /// The values of the members as list of strings
  inline void to_string_list(String_list_t& out) const {
    out.push_back(boost::lexical_cast<std::string>(name));
    out.push_back(boost::lexical_cast<std::string>(descr));
  }

  ebisu::utils::Fixed_size_char_array<64> name;
  ebisu::utils::Fixed_size_char_array<256> descr;
};

inline otl_stream& operator<<(otl_stream& out,
                              Code_packages_value const& value) {
  out << value.name << value.descr;
  return out;
}

inline otl_stream& operator>>(otl_stream& src, Code_packages_value& value) {
  src >> value.name >> value.descr;
  return src;
}

template <typename PKEY_LIST_TYPE = std::vector<Code_packages_pkey>,
          typename VALUE_LIST_TYPE = std::vector<Code_packages_value> >
class Code_packages {
 public:
  using Pkey_t = Code_packages_pkey;
  using Value_t = Code_packages_value;
  using Pkey_list_t = PKEY_LIST_TYPE;
  using Value_list_t = VALUE_LIST_TYPE;
  using Row_t = std::pair<Pkey_t, Value_t>;
  using Row_list_t = std::vector<Row_t>;

  Code_packages(Code_packages const& other) = delete;

  static Code_packages& instance() {
    static Code_packages instance_s;
    return instance_s;
  }

  static void print_recordset_as_table(Row_list_t const& recordset,
                                       std::ostream& out) {
    ebisu::orm::print_recordset_as_table<Code_packages>(recordset, out);
  }

  static void print_values_as_table(Value_list_t const& values,
                                    std::ostream& out) {
    ebisu::orm::print_values_as_table<Code_packages>(values, out);
  }

  int select_last_insert_id() {
    int result{};
    otl_stream stream{1, "SELECT LAST_INSERT_ID()", *connection_};
    if (!stream.eof()) {
      stream >> result;
    }
    return result;
  }

  int select_affected_row_count() {
    int result{};
    otl_stream stream{1, "SELECT ROW_COUNT()", *connection_};
    if (!stream.eof()) {
      int signed_result(0);
      stream >> signed_result;
      result = (signed_result < 0) ? 0 : signed_result;
    }
    return result;
  }

  int select_table_row_count() {
    int result(0);
    otl_stream stream{1, "SELECT COUNT(*) FROM code_packages", *connection_};
    if (!stream.eof()) {
      stream >> result;
    }
    return result;
  }

  Row_list_t select_all_rows(std::string const& where_clause = "") {
    Row_list_t found;
    char const* select_stmt = R"(
      select
        id,
        name,
        descr
      from
        code_packages
    )";

    otl_stream stream{50,
                      where_clause.empty()
                          ? select_stmt
                          : (std::string(select_stmt) + where_clause).c_str(),
                      *connection_};

    while (!stream.eof()) {
      Row_t row;
      stream >> row.first >> row.second;
      found.push_back(row);
    }
    return found;
  }

  bool find_row_by_key(Pkey_t const& desideratum, Value_t& found) {
    char const* select_stmt = R"(
      select
        name,
        descr
      from
        code_packages
      where
        id=:id<int>
    )";

    otl_stream stream{50, select_stmt, *connection_};
    stream << desideratum;
    if (!stream.eof()) {
      stream >> found;
      return true;
    }
    return false;
  }

  bool find_row_by_value(Row_t& desideratum) {
    char const* select_stmt = R"(
      select
        id
      from
        code_packages
      where
        name=:name<char[64]> AND
        descr=:descr<char[256]>
    )";
    otl_stream stream{50, select_stmt, *connection_};
    stream << desideratum.second;
    if (!stream.eof()) {
      stream >> desideratum.first;
      return true;
    }
    return false;
  }

  void insert(Row_list_t const& nascent, int stream_buffer_size = 1) {
    if (nascent.empty()) {
      return;
    }
    char const* insert_stmt = R"(
      insert into code_packages (
        name,
        descr
      )
      values (
        :name<char[64]>,
        :descr<char[256]>
      )
    )";
    otl_stream stream{50, insert_stmt, *connection_};
    for (auto const& row : nascent) {
      stream << row.second;
    }
  }

  void update(Row_list_t const& changing) {
    if (changing.empty()) {
      return;
    }

    char const* update_stmt = R"(
      update code_packages
      set
        name=:name<char[64]>,
        descr=:descr<char[256]>
      where
        id=:id<int>
    )";

    otl_stream stream(1, update_stmt, *connection_);
    for (auto const& row : changing) {
      stream << row.second << row.first;
    }
  }

  void delete_row(Pkey_t const& moribund) {
    char const* delete_stmt = R"(
      delete
      from code_packages
      where
    id=:id<int>

    )";
    otl_stream stream{50, delete_stmt, *connection_};
    stream << moribund;
  }

  size_t delete_all_rows() {
    long rows_deleted{
        otl_cursor::direct_exec(*connection_, "DELETE FROM code_packages")};
    return size_t(rows_deleted);
  }

 private:
  Code_packages() {}

  otl_connect* connection_{Connection_code_metrics::instance().connection()};
};

}  // namespace table
}  // namespace code_metrics
}  // namespace orm
}  // namespace ebisu

#endif  // __EBISU_ORM_CODE_METRICS_TABLE_CODE_PACKAGES_HPP__
