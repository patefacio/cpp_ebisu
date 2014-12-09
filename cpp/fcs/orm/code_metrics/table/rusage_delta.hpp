#ifndef __FCS_ORM_CODE_METRICS_TABLE_RUSAGE_DELTA_HPP__
#define __FCS_ORM_CODE_METRICS_TABLE_RUSAGE_DELTA_HPP__

#include "code_locations.hpp"
#include "fcs/orm/code_metrics/code_metrics.hpp"
#include "fcs/orm/orm_to_string_table.hpp"
#include "fcs/orm/otl_utils.hpp"
#include <boost/any.hpp>
#include <cstdint>
#include <iosfwd>
#include <sstream>
#include <utility>
#include <vector>

namespace fcs {
namespace orm {
namespace code_metrics {
namespace table {
  struct Rusage_delta_pkey
  {
    bool operator==(Rusage_delta_pkey const& rhs) const {
      return this == &rhs ||
        (id == rhs.id);
    }

    bool operator!=(Rusage_delta_pkey const& rhs) const {
      return !(*this == rhs);
    }

    bool operator<(Rusage_delta_pkey const& rhs) const {
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
                             Rusage_delta_pkey const& item) {
      out << '\n' << "id:" << item.id;
      return out;
    }

  };

  inline otl_stream&
  operator<<(otl_stream &out,
             Rusage_delta_pkey const& value) {
    out << value.id;
    return out;
  }

  inline otl_stream&
  operator>>(otl_stream &src,
             Rusage_delta_pkey & value) {
    src >> value.id;
    return src;
  }


  struct Rusage_delta_value
  {
    bool operator==(Rusage_delta_value const& rhs) const {
      return this == &rhs ||
        (code_locations_id == rhs.code_locations_id &&
        created == rhs.created &&
        start_processor == rhs.start_processor &&
        end_processor == rhs.end_processor &&
        cpu_mhz == rhs.cpu_mhz &&
        debug == rhs.debug &&
        user_time_sec == rhs.user_time_sec &&
        user_time_usec == rhs.user_time_usec &&
        system_time_sec == rhs.system_time_sec &&
        system_time_usec == rhs.system_time_usec &&
        ru_maxrss == rhs.ru_maxrss &&
        ru_ixrss == rhs.ru_ixrss &&
        ru_idrss == rhs.ru_idrss &&
        ru_isrss == rhs.ru_isrss &&
        ru_minflt == rhs.ru_minflt &&
        ru_majflt == rhs.ru_majflt &&
        ru_nswap == rhs.ru_nswap &&
        ru_inblock == rhs.ru_inblock &&
        ru_oublock == rhs.ru_oublock &&
        ru_msgsnd == rhs.ru_msgsnd &&
        ru_msgrcv == rhs.ru_msgrcv &&
        ru_nsignals == rhs.ru_nsignals &&
        ru_nvcsw == rhs.ru_nvcsw &&
        ru_nivcsw == rhs.ru_nivcsw);
    }

    bool operator!=(Rusage_delta_value const& rhs) const {
      return !(*this == rhs);
    }

    bool operator<(Rusage_delta_value const& rhs) const {
      return code_locations_id != rhs.code_locations_id? code_locations_id < rhs.code_locations_id : (
        created != rhs.created? created < rhs.created : (
        start_processor != rhs.start_processor? start_processor < rhs.start_processor : (
        end_processor != rhs.end_processor? end_processor < rhs.end_processor : (
        cpu_mhz != rhs.cpu_mhz? cpu_mhz < rhs.cpu_mhz : (
        debug != rhs.debug? debug < rhs.debug : (
        user_time_sec != rhs.user_time_sec? user_time_sec < rhs.user_time_sec : (
        user_time_usec != rhs.user_time_usec? user_time_usec < rhs.user_time_usec : (
        system_time_sec != rhs.system_time_sec? system_time_sec < rhs.system_time_sec : (
        system_time_usec != rhs.system_time_usec? system_time_usec < rhs.system_time_usec : (
        ru_maxrss != rhs.ru_maxrss? ru_maxrss < rhs.ru_maxrss : (
        ru_ixrss != rhs.ru_ixrss? ru_ixrss < rhs.ru_ixrss : (
        ru_idrss != rhs.ru_idrss? ru_idrss < rhs.ru_idrss : (
        ru_isrss != rhs.ru_isrss? ru_isrss < rhs.ru_isrss : (
        ru_minflt != rhs.ru_minflt? ru_minflt < rhs.ru_minflt : (
        ru_majflt != rhs.ru_majflt? ru_majflt < rhs.ru_majflt : (
        ru_nswap != rhs.ru_nswap? ru_nswap < rhs.ru_nswap : (
        ru_inblock != rhs.ru_inblock? ru_inblock < rhs.ru_inblock : (
        ru_oublock != rhs.ru_oublock? ru_oublock < rhs.ru_oublock : (
        ru_msgsnd != rhs.ru_msgsnd? ru_msgsnd < rhs.ru_msgsnd : (
        ru_msgrcv != rhs.ru_msgrcv? ru_msgrcv < rhs.ru_msgrcv : (
        ru_nsignals != rhs.ru_nsignals? ru_nsignals < rhs.ru_nsignals : (
        ru_nvcsw != rhs.ru_nvcsw? ru_nvcsw < rhs.ru_nvcsw : (
        ru_nivcsw != rhs.ru_nivcsw? ru_nivcsw < rhs.ru_nivcsw : (
        false))))))))))))))))))))))));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("code_locations_id");
      out.push_back("created");
      out.push_back("start_processor");
      out.push_back("end_processor");
      out.push_back("cpu_mhz");
      out.push_back("debug");
      out.push_back("user_time_sec");
      out.push_back("user_time_usec");
      out.push_back("system_time_sec");
      out.push_back("system_time_usec");
      out.push_back("ru_maxrss");
      out.push_back("ru_ixrss");
      out.push_back("ru_idrss");
      out.push_back("ru_isrss");
      out.push_back("ru_minflt");
      out.push_back("ru_majflt");
      out.push_back("ru_nswap");
      out.push_back("ru_inblock");
      out.push_back("ru_oublock");
      out.push_back("ru_msgsnd");
      out.push_back("ru_msgrcv");
      out.push_back("ru_nsignals");
      out.push_back("ru_nvcsw");
      out.push_back("ru_nivcsw");
    }

    inline void
    to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(code_locations_id));
      out.push_back(boost::lexical_cast< std::string >(created));
      out.push_back(boost::lexical_cast< std::string >(start_processor));
      out.push_back(boost::lexical_cast< std::string >(end_processor));
      out.push_back(boost::lexical_cast< std::string >(cpu_mhz));
      out.push_back(boost::lexical_cast< std::string >(debug));
      out.push_back(boost::lexical_cast< std::string >(user_time_sec));
      out.push_back(boost::lexical_cast< std::string >(user_time_usec));
      out.push_back(boost::lexical_cast< std::string >(system_time_sec));
      out.push_back(boost::lexical_cast< std::string >(system_time_usec));
      out.push_back(boost::lexical_cast< std::string >(ru_maxrss));
      out.push_back(boost::lexical_cast< std::string >(ru_ixrss));
      out.push_back(boost::lexical_cast< std::string >(ru_idrss));
      out.push_back(boost::lexical_cast< std::string >(ru_isrss));
      out.push_back(boost::lexical_cast< std::string >(ru_minflt));
      out.push_back(boost::lexical_cast< std::string >(ru_majflt));
      out.push_back(boost::lexical_cast< std::string >(ru_nswap));
      out.push_back(boost::lexical_cast< std::string >(ru_inblock));
      out.push_back(boost::lexical_cast< std::string >(ru_oublock));
      out.push_back(boost::lexical_cast< std::string >(ru_msgsnd));
      out.push_back(boost::lexical_cast< std::string >(ru_msgrcv));
      out.push_back(boost::lexical_cast< std::string >(ru_nsignals));
      out.push_back(boost::lexical_cast< std::string >(ru_nvcsw));
      out.push_back(boost::lexical_cast< std::string >(ru_nivcsw));
    }

    int32_t code_locations_id;
    otl_datetime created;
    int32_t start_processor;
    int32_t end_processor;
    double cpu_mhz;
    int32_t debug;
    int64_t user_time_sec;
    int64_t user_time_usec;
    int64_t system_time_sec;
    int64_t system_time_usec;
    int64_t ru_maxrss;
    int64_t ru_ixrss;
    int64_t ru_idrss;
    int64_t ru_isrss;
    int64_t ru_minflt;
    int64_t ru_majflt;
    int64_t ru_nswap;
    int64_t ru_inblock;
    int64_t ru_oublock;
    int64_t ru_msgsnd;
    int64_t ru_msgrcv;
    int64_t ru_nsignals;
    int64_t ru_nvcsw;
    int64_t ru_nivcsw;

    friend inline
    std::ostream& operator<<(std::ostream& out,
                             Rusage_delta_value const& item) {
      out << '\n' << "code_locations_id:" << item.code_locations_id;
      out << '\n' << "created:" << item.created;
      out << '\n' << "start_processor:" << item.start_processor;
      out << '\n' << "end_processor:" << item.end_processor;
      out << '\n' << "cpu_mhz:" << item.cpu_mhz;
      out << '\n' << "debug:" << item.debug;
      out << '\n' << "user_time_sec:" << item.user_time_sec;
      out << '\n' << "user_time_usec:" << item.user_time_usec;
      out << '\n' << "system_time_sec:" << item.system_time_sec;
      out << '\n' << "system_time_usec:" << item.system_time_usec;
      out << '\n' << "ru_maxrss:" << item.ru_maxrss;
      out << '\n' << "ru_ixrss:" << item.ru_ixrss;
      out << '\n' << "ru_idrss:" << item.ru_idrss;
      out << '\n' << "ru_isrss:" << item.ru_isrss;
      out << '\n' << "ru_minflt:" << item.ru_minflt;
      out << '\n' << "ru_majflt:" << item.ru_majflt;
      out << '\n' << "ru_nswap:" << item.ru_nswap;
      out << '\n' << "ru_inblock:" << item.ru_inblock;
      out << '\n' << "ru_oublock:" << item.ru_oublock;
      out << '\n' << "ru_msgsnd:" << item.ru_msgsnd;
      out << '\n' << "ru_msgrcv:" << item.ru_msgrcv;
      out << '\n' << "ru_nsignals:" << item.ru_nsignals;
      out << '\n' << "ru_nvcsw:" << item.ru_nvcsw;
      out << '\n' << "ru_nivcsw:" << item.ru_nivcsw;
      return out;
    }

  };

  inline otl_stream&
  operator<<(otl_stream &out,
             Rusage_delta_value const& value) {
    out << value.code_locations_id
      << value.created
      << value.start_processor
      << value.end_processor
      << value.cpu_mhz
      << value.debug
      << value.user_time_sec
      << value.user_time_usec
      << value.system_time_sec
      << value.system_time_usec
      << value.ru_maxrss
      << value.ru_ixrss
      << value.ru_idrss
      << value.ru_isrss
      << value.ru_minflt
      << value.ru_majflt
      << value.ru_nswap
      << value.ru_inblock
      << value.ru_oublock
      << value.ru_msgsnd
      << value.ru_msgrcv
      << value.ru_nsignals
      << value.ru_nvcsw
      << value.ru_nivcsw;
    return out;
  }

  inline otl_stream&
  operator>>(otl_stream &src,
             Rusage_delta_value & value) {
    src >> value.code_locations_id
      >> value.created
      >> value.start_processor
      >> value.end_processor
      >> value.cpu_mhz
      >> value.debug
      >> value.user_time_sec
      >> value.user_time_usec
      >> value.system_time_sec
      >> value.system_time_usec
      >> value.ru_maxrss
      >> value.ru_ixrss
      >> value.ru_idrss
      >> value.ru_isrss
      >> value.ru_minflt
      >> value.ru_majflt
      >> value.ru_nswap
      >> value.ru_inblock
      >> value.ru_oublock
      >> value.ru_msgsnd
      >> value.ru_msgrcv
      >> value.ru_nsignals
      >> value.ru_nvcsw
      >> value.ru_nivcsw;
    return src;
  }


  template< typename PKEY_LIST_TYPE = std::vector< Rusage_delta_pkey >,
            typename VALUE_LIST_TYPE = std::vector< Rusage_delta_value > >
  class Rusage_delta
  {
  public:
    using Pkey_t = Rusage_delta_pkey;
    using Value_t = Rusage_delta_value;
    using Pkey_list_t = PKEY_LIST_TYPE;
    using Value_list_t = VALUE_LIST_TYPE;
    using Row_t = std::pair< Pkey_t, Value_t >;
    using Row_list_t = std::vector< Row_t >;

    static Rusage_delta & instance() {
      static Rusage_delta instance_s;
      return instance_s;
    }

    static void
    print_recordset_as_table(Row_list_t const& recordset,
                             std::ostream &out) {
      fcs::orm::print_recordset_as_table< Rusage_delta >(recordset, out);
    }

    static void
    print_values_as_table(Value_list_t const& values,
                          std::ostream &out) {
      fcs::orm::print_values_as_table< Rusage_delta >(values, out);
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
      otl_stream stream { 1, "SELECT COUNT(*) FROM rusage_delta", *connection_ };
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
          user_time_sec,
          user_time_usec,
          system_time_sec,
          system_time_usec,
          ru_maxrss,
          ru_ixrss,
          ru_idrss,
          ru_isrss,
          ru_minflt,
          ru_majflt,
          ru_nswap,
          ru_inblock,
          ru_oublock,
          ru_msgsnd,
          ru_msgrcv,
          ru_nsignals,
          ru_nvcsw,
          ru_nivcsw
        from
          rusage_delta
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
          user_time_sec,
          user_time_usec,
          system_time_sec,
          system_time_usec,
          ru_maxrss,
          ru_ixrss,
          ru_idrss,
          ru_isrss,
          ru_minflt,
          ru_majflt,
          ru_nswap,
          ru_inblock,
          ru_oublock,
          ru_msgsnd,
          ru_msgrcv,
          ru_nsignals,
          ru_nvcsw,
          ru_nivcsw
        from
          rusage_delta
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
          rusage_delta
        where
          code_locations_id=:code_locations_id<int> AND
          created=:created<timestamp> AND
          start_processor=:start_processor<int> AND
          end_processor=:end_processor<int> AND
          cpu_mhz=:cpu_mhz<double> AND
          debug=:debug<int> AND
          user_time_sec=:user_time_sec<bigint> AND
          user_time_usec=:user_time_usec<bigint> AND
          system_time_sec=:system_time_sec<bigint> AND
          system_time_usec=:system_time_usec<bigint> AND
          ru_maxrss=:ru_maxrss<bigint> AND
          ru_ixrss=:ru_ixrss<bigint> AND
          ru_idrss=:ru_idrss<bigint> AND
          ru_isrss=:ru_isrss<bigint> AND
          ru_minflt=:ru_minflt<bigint> AND
          ru_majflt=:ru_majflt<bigint> AND
          ru_nswap=:ru_nswap<bigint> AND
          ru_inblock=:ru_inblock<bigint> AND
          ru_oublock=:ru_oublock<bigint> AND
          ru_msgsnd=:ru_msgsnd<bigint> AND
          ru_msgrcv=:ru_msgrcv<bigint> AND
          ru_nsignals=:ru_nsignals<bigint> AND
          ru_nvcsw=:ru_nvcsw<bigint> AND
          ru_nivcsw=:ru_nivcsw<bigint>
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
        insert into rusage_delta (
          code_locations_id,
          created,
          start_processor,
          end_processor,
          cpu_mhz,
          debug,
          user_time_sec,
          user_time_usec,
          system_time_sec,
          system_time_usec,
          ru_maxrss,
          ru_ixrss,
          ru_idrss,
          ru_isrss,
          ru_minflt,
          ru_majflt,
          ru_nswap,
          ru_inblock,
          ru_oublock,
          ru_msgsnd,
          ru_msgrcv,
          ru_nsignals,
          ru_nvcsw,
          ru_nivcsw
        )
        values (
          :code_locations_id<int>,
          :created<timestamp>,
          :start_processor<int>,
          :end_processor<int>,
          :cpu_mhz<double>,
          :debug<int>,
          :user_time_sec<bigint>,
          :user_time_usec<bigint>,
          :system_time_sec<bigint>,
          :system_time_usec<bigint>,
          :ru_maxrss<bigint>,
          :ru_ixrss<bigint>,
          :ru_idrss<bigint>,
          :ru_isrss<bigint>,
          :ru_minflt<bigint>,
          :ru_majflt<bigint>,
          :ru_nswap<bigint>,
          :ru_inblock<bigint>,
          :ru_oublock<bigint>,
          :ru_msgsnd<bigint>,
          :ru_msgrcv<bigint>,
          :ru_nsignals<bigint>,
          :ru_nvcsw<bigint>,
          :ru_nivcsw<bigint>
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
        update rusage_delta
        set
          code_locations_id=:code_locations_id<int>,
          created=:created<timestamp>,
          start_processor=:start_processor<int>,
          end_processor=:end_processor<int>,
          cpu_mhz=:cpu_mhz<double>,
          debug=:debug<int>,
          user_time_sec=:user_time_sec<bigint>,
          user_time_usec=:user_time_usec<bigint>,
          system_time_sec=:system_time_sec<bigint>,
          system_time_usec=:system_time_usec<bigint>,
          ru_maxrss=:ru_maxrss<bigint>,
          ru_ixrss=:ru_ixrss<bigint>,
          ru_idrss=:ru_idrss<bigint>,
          ru_isrss=:ru_isrss<bigint>,
          ru_minflt=:ru_minflt<bigint>,
          ru_majflt=:ru_majflt<bigint>,
          ru_nswap=:ru_nswap<bigint>,
          ru_inblock=:ru_inblock<bigint>,
          ru_oublock=:ru_oublock<bigint>,
          ru_msgsnd=:ru_msgsnd<bigint>,
          ru_msgrcv=:ru_msgrcv<bigint>,
          ru_nsignals=:ru_nsignals<bigint>,
          ru_nvcsw=:ru_nvcsw<bigint>,
          ru_nivcsw=:ru_nivcsw<bigint>
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
        from rusage_delta
        where
      id=:id<int>

      )";
      otl_stream stream { 50, delete_stmt, *connection_ };
      stream << moribund;
    }

    size_t delete_all_rows() {
      long rows_deleted {
        otl_cursor::direct_exec(*connection_, "DELETE FROM rusage_delta")
      };
      return size_t(rows_deleted);
    }

  private:
    otl_connect * connection_ { Connection_code_metrics::instance().connection() };

  };

  // Establish link from Rusage_delta to Code_locations
  // across foreign key rusage_delta.`rusage_delta_ibfk_1`
  inline void
  link_rows(Rusage_delta<>::Row_t & from_row,
            Code_locations<>::Row_t const& to_row) {
    from_row.second.code_locations_id = to_row.first.id;
  }

} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // __FCS_ORM_CODE_METRICS_TABLE_RUSAGE_DELTA_HPP__
