#ifndef __FCS_ORM_CODE_METRICS_TABLE_CODE_PACKAGES_HPP__
#define __FCS_ORM_CODE_METRICS_TABLE_CODE_PACKAGES_HPP__

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
  struct Code_packages_pkey
  {
  public:
    bool operator==(Code_packages_pkey const& rhs) {
      return this == &rhs ||
        (id_ == rhs.id_);
    }

    bool operator<(Code_packages_pkey const& rhs) {
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

    friend inline std::ostream& operator<<(std::ostream& out, Code_packages_pkey const& item) {
      out << '\n' << "id:" << item.id_;
      return out;
    }

  };

  inline otl_stream& operator<<(otl_stream &out, Code_packages_pkey const& value) {
    out << value.id_;
    return out;
  }

  inline otl_stream& operator>>(otl_stream &src, Code_packages_pkey & value) {
    src >> value.id_;
    return src;
  }


  struct Code_packages_value
  {
  public:
    bool operator==(Code_packages_value const& rhs) {
      return this == &rhs ||
        (name_ == rhs.name_ &&
        descr_ == rhs.descr_);
    }

    bool operator<(Code_packages_value const& rhs) {
      return name_ != rhs.name_? name_ < rhs.name_ : (
        descr_ != rhs.descr_? descr_ < rhs.descr_ : (
        false));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("name");
      out.push_back("descr");
    }

    inline
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(name_));
      out.push_back(boost::lexical_cast< std::string >(descr_));
    }

    fcs::utils::Fixed_size_char_array< 64 > name_;
    fcs::utils::Fixed_size_char_array< 256 > descr_;

    friend inline std::ostream& operator<<(std::ostream& out, Code_packages_value const& item) {
      out << '\n' << "name:" << item.name_;
      out << '\n' << "descr:" << item.descr_;
      return out;
    }

  };

  inline otl_stream& operator<<(otl_stream &out, Code_packages_value const& value) {
    out << value.name_
      << value.descr_;
    return out;
  }

  inline otl_stream& operator>>(otl_stream &src, Code_packages_value & value) {
    src >> value.name_
      >> value.descr_;
    return src;
  }


  template< typename PKEY_LIST_TYPE = std::vector< Code_packages_pkey >,
            typename VALUE_LIST_TYPE = std::vector< Code_packages_value > >
  class Code_packages
  {
  public:
    using Pkey_t = Code_packages_pkey;
    using Value_t = Code_packages_value;
    using Pkey_list_t = PKEY_LIST_TYPE;
    using Value_list_t = VALUE_LIST_TYPE;
    using Row_t = std::pair< Pkey_t, Value_t >;
    using Row_list_t = std::vector< Row_t >;

    static Code_packages & instance() {
      static Code_packages instance_s;
      return instance_s;
    }

    static void print_recordset_as_table(Row_list_t const& recordset, std::ostream &out) {
      fcs::orm::print_recordset_as_table< Code_packages >(recordset, out);
    }

    static void print_values_as_table(Value_list_t const& values, std::ostream &out) {
      fcs::orm::print_values_as_table< Code_packages >(values, out);
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
      otl_stream stream { 1, "SELECT COUNT(*) FROM code_packages", *connection_ };
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
          name,
          descr
        from
          code_packages
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
          name,
          descr
        from
          code_packages
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
          code_packages
        where
          name=:name<char[64]> AND
          descr=:descr<char[256]>
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
        insert into code_packages (
          name,
          descr
        )
        values (
          :name<char[64]>,
          :descr<char[256]>
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
        from code_packages
        where
      id=:id<int>

      )";
      otl_stream stream { 50, delete_stmt, *connection_ };
      stream << moribund;
    }

    size_t delete_all_rows() {
      long rows_deleted { otl_cursor::direct_exec(*connection_, "DELETE FROM code_packages") };
      return size_t(rows_deleted);
    }

  private:
    otl_connect * connection_ { Connection_code_metrics::instance().connection() };

  };


} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // __FCS_ORM_CODE_METRICS_TABLE_CODE_PACKAGES_HPP__
