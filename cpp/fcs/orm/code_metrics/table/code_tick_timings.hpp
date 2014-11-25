#ifndef __FCS_ORM_CODE_METRICS_TABLE_CODE_TICK_TIMINGS_HPP__
#define __FCS_ORM_CODE_METRICS_TABLE_CODE_TICK_TIMINGS_HPP__

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
  struct Code_tick_timings_pkey
  {
  public:
    bool operator==(Code_tick_timings_pkey const& rhs) const {
      return this == &rhs ||
        (id == rhs.id);
    }

    bool operator!=(Code_tick_timings_pkey const& rhs) const {
      return !(*this == rhs);
    }

    bool operator<(Code_tick_timings_pkey const& rhs) const {
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
                             Code_tick_timings_pkey const& item) {
      out << '\n' << "id:" << item.id;
      return out;
    }

  };

  inline otl_stream&
  operator<<(otl_stream &out,
             Code_tick_timings_pkey const& value) {
    out << value.id;
    return out;
  }

  inline otl_stream&
  operator>>(otl_stream &src,
             Code_tick_timings_pkey & value) {
    src >> value.id;
    return src;
  }


  struct Code_tick_timings_value
  {
  public:
    bool operator==(Code_tick_timings_value const& rhs) const {
      return this == &rhs ||
        (code_locations_id == rhs.code_locations_id &&
        created == rhs.created &&
        start_processor == rhs.start_processor &&
        end_processor == rhs.end_processor &&
        cpu_mhz == rhs.cpu_mhz &&
        debug == rhs.debug &&
        ticks == rhs.ticks &&
        normalized_ns == rhs.normalized_ns);
    }

    bool operator!=(Code_tick_timings_value const& rhs) const {
      return !(*this == rhs);
    }

    bool operator<(Code_tick_timings_value const& rhs) const {
      return code_locations_id != rhs.code_locations_id? code_locations_id < rhs.code_locations_id : (
        created != rhs.created? created < rhs.created : (
        start_processor != rhs.start_processor? start_processor < rhs.start_processor : (
        end_processor != rhs.end_processor? end_processor < rhs.end_processor : (
        cpu_mhz != rhs.cpu_mhz? cpu_mhz < rhs.cpu_mhz : (
        debug != rhs.debug? debug < rhs.debug : (
        ticks != rhs.ticks? ticks < rhs.ticks : (
        normalized_ns != rhs.normalized_ns? normalized_ns < rhs.normalized_ns : (
        false))))))));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("code_locations_id");
      out.push_back("created");
      out.push_back("start_processor");
      out.push_back("end_processor");
      out.push_back("cpu_mhz");
      out.push_back("debug");
      out.push_back("ticks");
      out.push_back("normalized_ns");
    }

    inline void
    to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(code_locations_id));
      out.push_back(boost::lexical_cast< std::string >(created));
      out.push_back(boost::lexical_cast< std::string >(start_processor));
      out.push_back(boost::lexical_cast< std::string >(end_processor));
      out.push_back(boost::lexical_cast< std::string >(cpu_mhz));
      out.push_back(boost::lexical_cast< std::string >(debug));
      out.push_back(boost::lexical_cast< std::string >(ticks));
      out.push_back(boost::lexical_cast< std::string >(normalized_ns));
    }

    int32_t code_locations_id;
    otl_datetime created;
    int32_t start_processor;
    int32_t end_processor;
    double cpu_mhz;
    int32_t debug;
    int64_t ticks;
    int64_t normalized_ns;

    friend inline
    std::ostream& operator<<(std::ostream& out,
                             Code_tick_timings_value const& item) {
      out << '\n' << "code_locations_id:" << item.code_locations_id;
      out << '\n' << "created:" << item.created;
      out << '\n' << "start_processor:" << item.start_processor;
      out << '\n' << "end_processor:" << item.end_processor;
      out << '\n' << "cpu_mhz:" << item.cpu_mhz;
      out << '\n' << "debug:" << item.debug;
      out << '\n' << "ticks:" << item.ticks;
      out << '\n' << "normalized_ns:" << item.normalized_ns;
      return out;
    }

  };

  inline otl_stream&
  operator<<(otl_stream &out,
             Code_tick_timings_value const& value) {
    out << value.code_locations_id
      << value.created
      << value.start_processor
      << value.end_processor
      << value.cpu_mhz
      << value.debug
      << value.ticks
      << value.normalized_ns;
    return out;
  }

  inline otl_stream&
  operator>>(otl_stream &src,
             Code_tick_timings_value & value) {
    src >> value.code_locations_id
      >> value.created
      >> value.start_processor
      >> value.end_processor
      >> value.cpu_mhz
      >> value.debug
      >> value.ticks
      >> value.normalized_ns;
    return src;
  }


  template< typename PKEY_LIST_TYPE = std::vector< Code_tick_timings_pkey >,
            typename VALUE_LIST_TYPE = std::vector< Code_tick_timings_value > >
  class Code_tick_timings
  {
  public:
    using Pkey_t = Code_tick_timings_pkey;
    using Value_t = Code_tick_timings_value;
    using Pkey_list_t = PKEY_LIST_TYPE;
    using Value_list_t = VALUE_LIST_TYPE;
    using Row_t = std::pair< Pkey_t, Value_t >;
    using Row_list_t = std::vector< Row_t >;

    static Code_tick_timings & instance() {
      static Code_tick_timings instance_s;
      return instance_s;
    }

    static void
    print_recordset_as_table(Row_list_t const& recordset,
                             std::ostream &out) {
      fcs::orm::print_recordset_as_table< Code_tick_timings >(recordset, out);
    }

    static void
    print_values_as_table(Value_list_t const& values,
                          std::ostream &out) {
      fcs::orm::print_values_as_table< Code_tick_timings >(values, out);
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

    Row_list_t select_all_rows(std::string const& where_clause = "") {
      Row_list_t found;
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
      return found;
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
        update code_tick_timings
        set
          code_locations_id=:code_locations_id<int>,
          created=:created<timestamp>,
          start_processor=:start_processor<int>,
          end_processor=:end_processor<int>,
          cpu_mhz=:cpu_mhz<double>,
          debug=:debug<int>,
          ticks=:ticks<bigint>,
          normalized_ns=:normalized_ns<bigint>
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
        from code_tick_timings
        where
      id=:id<int>

      )";
      otl_stream stream { 50, delete_stmt, *connection_ };
      stream << moribund;
    }

    size_t delete_all_rows() {
      long rows_deleted {
        otl_cursor::direct_exec(*connection_, "DELETE FROM code_tick_timings")
      };
      return size_t(rows_deleted);
    }

  private:
    otl_connect * connection_ { Connection_code_metrics::instance().connection() };

  };

  // Link to Code_packages
  inline void
  link_rows(Code_tick_timings<>::Row_t & from_row,
            Code_packages<>::Row_t const& to_row) {

  }

  // Link to Code_locations
  inline void
  link_rows(Code_tick_timings<>::Row_t & from_row,
            Code_locations<>::Row_t const& to_row) {

  }


} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // __FCS_ORM_CODE_METRICS_TABLE_CODE_TICK_TIMINGS_HPP__
