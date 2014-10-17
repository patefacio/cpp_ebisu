#ifndef __FCS_ORM_CODE_TICK_TIMINGS_TABLE_CODE_TICK_TIMINGS_HPP__
#define __FCS_ORM_CODE_TICK_TIMINGS_TABLE_CODE_TICK_TIMINGS_HPP__

#include "fcs/orm/orm_to_string_table.hpp"
#include "fcs/orm/otl_config.hpp"
#include "fcs/orm/otl_utils.hpp"
#include <boost/any.hpp>
#include <cstdint>
#include <sstream>
#include <vector>

namespace fcs {
namespace orm {
namespace code_tick_timings {
namespace table {
  struct Code_tick_timings_pkey
  {
  public:
    bool operator==(Code_tick_timings_pkey const& rhs) {
      return this == &rhs ||
        (id_ == rhs.id_);
    }

    bool operator<(Code_tick_timings_pkey const& rhs) {
      return id_ != rhs.id_? id_ < rhs.id_ : (
        false);
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("id_");
    }

    inline
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(id_));
    }

    int32_t id_;

    friend inline std::ostream& operator<<(std::ostream& out, Code_tick_timings_pkey const& item) {
      out << '\n' << "id:" << item.id_;
      return out;
    }

  };

  inline otl_stream& operator<<(otl_stream &out, Code_tick_timings_pkey const& value) {
    out << value.id_;
  }

  inline otl_stream& operator>>(otl_stream &out, Code_tick_timings_pkey & value) {
    out >> value.id_;
  }


  struct Code_tick_timings_value
  {
  public:
    bool operator==(Code_tick_timings_value const& rhs) {
      return this == &rhs ||
        (code_locations_id_ == rhs.code_locations_id_ &&
        created_ == rhs.created_ &&
        start_processor_ == rhs.start_processor_ &&
        end_processor_ == rhs.end_processor_ &&
        cpu_mhz_ == rhs.cpu_mhz_ &&
        debug_ == rhs.debug_ &&
        ticks_ == rhs.ticks_ &&
        normalized_ns_ == rhs.normalized_ns_);
    }

    bool operator<(Code_tick_timings_value const& rhs) {
      return code_locations_id_ != rhs.code_locations_id_? code_locations_id_ < rhs.code_locations_id_ : (
        created_ != rhs.created_? created_ < rhs.created_ : (
        start_processor_ != rhs.start_processor_? start_processor_ < rhs.start_processor_ : (
        end_processor_ != rhs.end_processor_? end_processor_ < rhs.end_processor_ : (
        cpu_mhz_ != rhs.cpu_mhz_? cpu_mhz_ < rhs.cpu_mhz_ : (
        debug_ != rhs.debug_? debug_ < rhs.debug_ : (
        ticks_ != rhs.ticks_? ticks_ < rhs.ticks_ : (
        normalized_ns_ != rhs.normalized_ns_? normalized_ns_ < rhs.normalized_ns_ : (
        false))))))));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("code_locations_id_");
      out.push_back("created_");
      out.push_back("start_processor_");
      out.push_back("end_processor_");
      out.push_back("cpu_mhz_");
      out.push_back("debug_");
      out.push_back("ticks_");
      out.push_back("normalized_ns_");
    }

    inline
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(code_locations_id_));
      out.push_back(boost::lexical_cast< std::string >(created_));
      out.push_back(boost::lexical_cast< std::string >(start_processor_));
      out.push_back(boost::lexical_cast< std::string >(end_processor_));
      out.push_back(boost::lexical_cast< std::string >(cpu_mhz_));
      out.push_back(boost::lexical_cast< std::string >(debug_));
      out.push_back(boost::lexical_cast< std::string >(ticks_));
      out.push_back(boost::lexical_cast< std::string >(normalized_ns_));
    }

    int32_t code_locations_id_;
    otl_datetime created_;
    int32_t start_processor_;
    int32_t end_processor_;
    double cpu_mhz_;
    int32_t debug_;
    int64_t ticks_;
    int64_t normalized_ns_;

    friend inline std::ostream& operator<<(std::ostream& out, Code_tick_timings_value const& item) {
      out << '\n' << "code_locations_id:" << item.code_locations_id_;
      out << '\n' << "created:" << item.created_;
      out << '\n' << "start_processor:" << item.start_processor_;
      out << '\n' << "end_processor:" << item.end_processor_;
      out << '\n' << "cpu_mhz:" << item.cpu_mhz_;
      out << '\n' << "debug:" << item.debug_;
      out << '\n' << "ticks:" << item.ticks_;
      out << '\n' << "normalized_ns:" << item.normalized_ns_;
      return out;
    }

  };

  inline otl_stream& operator<<(otl_stream &out, Code_tick_timings_value const& value) {
    out << value.code_locations_id_
      << value.created_
      << value.start_processor_
      << value.end_processor_
      << value.cpu_mhz_
      << value.debug_
      << value.ticks_
      << value.normalized_ns_;
  }

  inline otl_stream& operator>>(otl_stream &out, Code_tick_timings_value & value) {
    out >> value.code_locations_id_
      >> value.created_
      >> value.start_processor_
      >> value.end_processor_
      >> value.cpu_mhz_
      >> value.debug_
      >> value.ticks_
      >> value.normalized_ns_;
  }


  template< typename PKEY_LIST_TYPE = std::vector< CodeTickTimingsPkey >,
            typename VALUE_LIST_TYPE = std::vector< CodeTickTimingsValue > >
  class Code_tick_timings
  {
  public:
    using Pkey_t = CodeTickTimingsPkey;
    using Value_t = CodeTickTimingsValue;
    using Pkey_list_t = PKEY_LIST_TYPE;
    using Value_list_t = VALUE_LIST_TYPE;
    using Row_t = std::pair< PKey_t, Value_t >;
    using Row_list_t = std::vector< Row_t >;

    static Code_tick_timings & instance() {
      static Code_tick_timings instance_s;
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
      otl_stream stream { 1, "SELECT COUNT(*) FROM code_tick_timings", *connection_ };
      if(!stream.eof()) {
        stream >> result;
      }
      return result;
    }

    void select_all_rows(Row_list_t &found, std::string const& where_clause = "") {
      char const* select_stmt = R"(
        select
          id,
          code_locations_id,
          created,
          start_processor,
          end_processor,
          cpu_mhz,
          debug,
          ticks,
          normalized_ns
        from
          code_tick_timings
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
    }

    bool find_row_by_key(Pkey_t const& desideratum, Value_t & found) {
      char const* select_stmt = R"(
        select
          code_locations_id,
          created,
          start_processor,
          end_processor,
          cpu_mhz,
          debug,
          ticks,
          normalized_ns
        from
          code_tick_timings
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
          code_tick_timings
        where
          code_locations_id=:code_locations_id<int> AND
          created=:created<timestamp> AND
          start_processor=:start_processor<int> AND
          end_processor=:end_processor<int> AND
          cpu_mhz=:cpu_mhz<double> AND
          debug=:debug<int> AND
          ticks=:ticks<bigint> AND
          normalized_ns=:normalized_ns<bigint>
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
        insert into code_tick_timings (
          code_locations_id,
          created,
          start_processor,
          end_processor,
          cpu_mhz,
          debug,
          ticks,
          normalized_ns
        )
        values (
          :code_locations_id<int>,
          :created<timestamp>,
          :start_processor<int>,
          :end_processor<int>,
          :cpu_mhz<double>,
          :debug<int>,
          :ticks<bigint>,
          :normalized_ns<bigint>
        )
      )";

      for(auto const& row : nascent) {
        stream << row.second;
      }
    }

    void delete_row(Pkey_t const& moribund) {
      char const * delete_stmt = R"(
        delete
        from code_tick_timings
        where
      id=:id<int>

      )";
      otl_stream stream { 50, delete_stmt, *connection_ };
      stream << moribund;
    }

    size_t delete_all_rows() {
      long rows_deleted { otl_cursor::direct_exec(*connection_, "DELETE FROM code_tick_timings") };
      return size_t(rows_deleted);
    }

  };


} // namespace table
} // namespace code_tick_timings
} // namespace orm
} // namespace fcs
#endif // __FCS_ORM_CODE_TICK_TIMINGS_TABLE_CODE_TICK_TIMINGS_HPP__
