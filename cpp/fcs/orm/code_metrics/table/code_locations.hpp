#ifndef __FCS_ORM_CODE_METRICS_TABLE_CODE_LOCATIONS_HPP__
#define __FCS_ORM_CODE_METRICS_TABLE_CODE_LOCATIONS_HPP__

#include "fcs/orm/code_metrics/code_metrics.hpp"
#include "fcs/orm/orm_to_string_table.hpp"
#include "fcs/orm/otl_utils.hpp"
#include <boost/any.hpp>
#include <cstdint>
#include <sstream>
#include <vector>

namespace fcs {
namespace orm {
namespace code_metrics {
namespace table {
  struct Code_locations_pkey
  {
  public:
    bool operator==(Code_locations_pkey const& rhs) {
      return this == &rhs ||
        (id_ == rhs.id_);
    }

    bool operator<(Code_locations_pkey const& rhs) {
      return id_ != rhs.id_? id_ < rhs.id_ : (
        false);
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("id");
    }

    inline
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(id_));
    }

    int32_t id_;

    friend inline std::ostream& operator<<(std::ostream& out, Code_locations_pkey const& item) {
      out << '\n' << "id:" << item.id_;
      return out;
    }

  };

  inline otl_stream& operator<<(otl_stream &out, Code_locations_pkey const& value) {
    out << value.id_;
    return out;
  }

  inline otl_stream& operator>>(otl_stream &out, Code_locations_pkey & value) {
    out >> value.id_;
    return out;
  }


  struct Code_locations_value
  {
  public:
    bool operator==(Code_locations_value const& rhs) {
      return this == &rhs ||
        (code_packages_id_ == rhs.code_packages_id_ &&
        label_ == rhs.label_ &&
        file_name_ == rhs.file_name_ &&
        line_number_ == rhs.line_number_ &&
        git_commit_ == rhs.git_commit_);
    }

    bool operator<(Code_locations_value const& rhs) {
      return code_packages_id_ != rhs.code_packages_id_? code_packages_id_ < rhs.code_packages_id_ : (
        label_ != rhs.label_? label_ < rhs.label_ : (
        file_name_ != rhs.file_name_? file_name_ < rhs.file_name_ : (
        line_number_ != rhs.line_number_? line_number_ < rhs.line_number_ : (
        git_commit_ != rhs.git_commit_? git_commit_ < rhs.git_commit_ : (
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

    inline
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(code_packages_id_));
      out.push_back(boost::lexical_cast< std::string >(label_));
      out.push_back(boost::lexical_cast< std::string >(file_name_));
      out.push_back(boost::lexical_cast< std::string >(line_number_));
      out.push_back(boost::lexical_cast< std::string >(git_commit_));
    }

    int32_t code_packages_id_;
    fcs::utils::Fixed_size_char_array< 256 > label_;
    fcs::utils::Fixed_size_char_array< 256 > file_name_;
    int32_t line_number_;
    fcs::utils::Fixed_size_char_array< 40 > git_commit_;

    friend inline std::ostream& operator<<(std::ostream& out, Code_locations_value const& item) {
      out << '\n' << "code_packages_id:" << item.code_packages_id_;
      out << '\n' << "label:" << item.label_;
      out << '\n' << "file_name:" << item.file_name_;
      out << '\n' << "line_number:" << item.line_number_;
      out << '\n' << "git_commit:" << item.git_commit_;
      return out;
    }

  };

  inline otl_stream& operator<<(otl_stream &out, Code_locations_value const& value) {
    out << value.code_packages_id_
      << value.label_
      << value.file_name_
      << value.line_number_
      << value.git_commit_;
    return out;
  }

  inline otl_stream& operator>>(otl_stream &out, Code_locations_value & value) {
    out >> value.code_packages_id_
      >> value.label_
      >> value.file_name_
      >> value.line_number_
      >> value.git_commit_;
    return out;
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

    static void print_recordset_as_table(Row_list_t const& recordset, std::ostream &out) {
      fcs::orm::print_recordset_as_table< Code_locations >(recordset, out);
    }

    static void print_values_as_table(Value_list_t const& values, std::ostream &out) {
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
      long rows_deleted { otl_cursor::direct_exec(*connection_, "DELETE FROM code_locations") };
      return size_t(rows_deleted);
    }

  private:
    otl_connect * connection_ { Connection_code_metrics::instance().connection() };

  };


} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // __FCS_ORM_CODE_METRICS_TABLE_CODE_LOCATIONS_HPP__
