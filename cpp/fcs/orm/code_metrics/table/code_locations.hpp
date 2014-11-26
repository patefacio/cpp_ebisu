#ifndef __FCS_ORM_CODE_METRICS_TABLE_CODE_LOCATIONS_HPP__
#define __FCS_ORM_CODE_METRICS_TABLE_CODE_LOCATIONS_HPP__

#include "code_packages.hpp"
#include "fcs/orm/code_metrics/code_metrics.hpp"
#include "fcs/orm/orm_to_string_table.hpp"
#include "fcs/orm/otl_utils.hpp"
#include <boost/any.hpp>
#include <cstdint>
#include <sstream>
#include <utility>
#include <vector>

namespace fcs {
namespace orm {
namespace code_metrics {
namespace table {
  struct Code_locations_pkey
  {
  public:
    bool operator==(Code_locations_pkey const& rhs) const {
      return this == &rhs ||
        (id == rhs.id);
    }

    bool operator!=(Code_locations_pkey const& rhs) const {
      return !(*this == rhs);
    }

    bool operator<(Code_locations_pkey const& rhs) const {
      return id != rhs.id? id < rhs.id : (
        false);
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("id");
    }

    inline void
    to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(id));
    }

    int32_t id;

    friend inline
    std::ostream& operator<<(std::ostream& out,
                             Code_locations_pkey const& item) {
      out << '\n' << "id:" << item.id;
      return out;
    }

  };

  inline otl_stream&
  operator<<(otl_stream &out,
             Code_locations_pkey const& value) {
    out << value.id;
    return out;
  }

  inline otl_stream&
  operator>>(otl_stream &src,
             Code_locations_pkey & value) {
    src >> value.id;
    return src;
  }


  struct Code_locations_value
  {
  public:
    bool operator==(Code_locations_value const& rhs) const {
      return this == &rhs ||
        (code_packages_id == rhs.code_packages_id &&
        label == rhs.label &&
        file_name == rhs.file_name &&
        line_number == rhs.line_number &&
        git_commit == rhs.git_commit);
    }

    bool operator!=(Code_locations_value const& rhs) const {
      return !(*this == rhs);
    }

    bool operator<(Code_locations_value const& rhs) const {
      return code_packages_id != rhs.code_packages_id? code_packages_id < rhs.code_packages_id : (
        label != rhs.label? label < rhs.label : (
        file_name != rhs.file_name? file_name < rhs.file_name : (
        line_number != rhs.line_number? line_number < rhs.line_number : (
        git_commit != rhs.git_commit? git_commit < rhs.git_commit : (
        false)))));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("code_packages_id");
      out.push_back("label");
      out.push_back("file_name");
      out.push_back("line_number");
      out.push_back("git_commit");
    }

    inline void
    to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(code_packages_id));
      out.push_back(boost::lexical_cast< std::string >(label));
      out.push_back(boost::lexical_cast< std::string >(file_name));
      out.push_back(boost::lexical_cast< std::string >(line_number));
      out.push_back(boost::lexical_cast< std::string >(git_commit));
    }

    int32_t code_packages_id;
    fcs::utils::Fixed_size_char_array< 256 > label;
    fcs::utils::Fixed_size_char_array< 256 > file_name;
    int32_t line_number;
    fcs::utils::Fixed_size_char_array< 40 > git_commit;

    friend inline
    std::ostream& operator<<(std::ostream& out,
                             Code_locations_value const& item) {
      out << '\n' << "code_packages_id:" << item.code_packages_id;
      out << '\n' << "label:" << item.label;
      out << '\n' << "file_name:" << item.file_name;
      out << '\n' << "line_number:" << item.line_number;
      out << '\n' << "git_commit:" << item.git_commit;
      return out;
    }

  };

  inline otl_stream&
  operator<<(otl_stream &out,
             Code_locations_value const& value) {
    out << value.code_packages_id
      << value.label
      << value.file_name
      << value.line_number
      << value.git_commit;
    return out;
  }

  inline otl_stream&
  operator>>(otl_stream &src,
             Code_locations_value & value) {
    src >> value.code_packages_id
      >> value.label
      >> value.file_name
      >> value.line_number
      >> value.git_commit;
    return src;
  }


  template< typename PKEY_LIST_TYPE = std::vector< Code_locations_pkey >,
            typename VALUE_LIST_TYPE = std::vector< Code_locations_value > >
  class Code_locations
  {
  public:
    using Pkey_t = Code_locations_pkey;
    using Value_t = Code_locations_value;
    using Pkey_list_t = PKEY_LIST_TYPE;
    using Value_list_t = VALUE_LIST_TYPE;
    using Row_t = std::pair< Pkey_t, Value_t >;
    using Row_list_t = std::vector< Row_t >;

    static Code_locations & instance() {
      static Code_locations instance_s;
      return instance_s;
    }

    static void
    print_recordset_as_table(Row_list_t const& recordset,
                             std::ostream &out) {
      fcs::orm::print_recordset_as_table< Code_locations >(recordset, out);
    }

    static void
    print_values_as_table(Value_list_t const& values,
                          std::ostream &out) {
      fcs::orm::print_values_as_table< Code_locations >(values, out);
    }

    int select_last_insert_id() {
      int result {};
      otl_stream stream { 1, "SELECT LAST_INSERT_ID()", *connection_ };
      if(!stream.eof()) {
        stream >> result;
      }
      return result;
    }

    int select_affected_row_count() {
      int result {};
      otl_stream stream { 1, "SELECT ROW_COUNT()", *connection_ };
      if(!stream.eof()) {
        int signed_result(0);
        stream >> signed_result;
        result = (signed_result < 0)? 0 : signed_result;
      }
      return result;
    }

    int select_table_row_count() {
      int result(0);
      otl_stream stream { 1, "SELECT COUNT(*) FROM code_locations", *connection_ };
      if(!stream.eof()) {
        stream >> result;
      }
      return result;
    }

    Row_list_t select_all_rows(std::string const& where_clause = "") {
      Row_list_t found;
      char const* select_stmt = R"(
        select
          id,
          code_packages_id,
          label,
          file_name,
          line_number,
          git_commit
        from
          code_locations
      )";

      otl_stream stream { 50,
        where_clause.empty()?
          select_stmt :
          (std::string(select_stmt) + where_clause).c_str(),
        *connection_ };

      while(!stream.eof()) {
        Row_t row;
        stream >> row.first >> row.second;
        found.push_back(row);
      }
      return found;
    }

    bool find_row_by_key(Pkey_t const& desideratum, Value_t & found) {
      char const* select_stmt = R"(
        select
          code_packages_id,
          label,
          file_name,
          line_number,
          git_commit
        from
          code_locations
        where
          id=:id<int>
      )";

      otl_stream stream { 50, select_stmt, *connection_ };
      stream << desideratum;
      if(!stream.eof()) {
        stream >> found;
        return true;
      }
      return false;
    }

    bool find_row_by_value(Row_t & desideratum) {
      char const* select_stmt = R"(
        select
          id
        from
          code_locations
        where
          code_packages_id=:code_packages_id<int> AND
          label=:label<char[256]> AND
          file_name=:file_name<char[256]> AND
          line_number=:line_number<int> AND
          git_commit=:git_commit<char[40]>
      )";
      otl_stream stream { 50, select_stmt, *connection_ };
      stream << desideratum.second;
      if(!stream.eof()) {
        stream >> desideratum.first;
        return true;
      }
      return false;
    }

    void insert(Row_list_t const& nascent, int stream_buffer_size = 1) {
      if(nascent.empty()) {
        return;
      }
      char const* insert_stmt = R"(
        insert into code_locations (
          code_packages_id,
          label,
          file_name,
          line_number,
          git_commit
        )
        values (
          :code_packages_id<int>,
          :label<char[256]>,
          :file_name<char[256]>,
          :line_number<int>,
          :git_commit<char[40]>
        )
      )";
      otl_stream stream { 50, insert_stmt, *connection_ };
      for(auto const& row : nascent) {
        stream << row.second;
      }
    }

    void update(Row_list_t const& changing) {
      if(changing.empty()) {
        return;
      }

      char const* update_stmt = R"(
        update code_locations
        set
          code_packages_id=:code_packages_id<int>,
          label=:label<char[256]>,
          file_name=:file_name<char[256]>,
          line_number=:line_number<int>,
          git_commit=:git_commit<char[40]>
        where
          id=:id<int>
      )";

      otl_stream stream(1, update_stmt, *connection_);
      for(auto const& row : changing) {
        stream << row.second << row.first;
      }

    }

    void delete_row(Pkey_t const& moribund) {
      char const * delete_stmt = R"(
        delete
        from code_locations
        where
      id=:id<int>

      )";
      otl_stream stream { 50, delete_stmt, *connection_ };
      stream << moribund;
    }

    size_t delete_all_rows() {
      long rows_deleted {
        otl_cursor::direct_exec(*connection_, "DELETE FROM code_locations")
      };
      return size_t(rows_deleted);
    }

  private:
    otl_connect * connection_ { Connection_code_metrics::instance().connection() };

  };

  // Establish link from Code_locations to Code_packages
  // across foreign key code_locations.`code_locations_ibfk_1`
  inline void
  link_rows(Code_locations<>::Row_t & from_row,
            Code_packages<>::Row_t const& to_row) {
    from_row.second.code_packages_id = to_row.first.id;
  }

} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // __FCS_ORM_CODE_METRICS_TABLE_CODE_LOCATIONS_HPP__
