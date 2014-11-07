#ifndef __FCS_ORM_CODE_METRICS_TABLE_RUSAGE_DELTA_HPP__
#define __FCS_ORM_CODE_METRICS_TABLE_RUSAGE_DELTA_HPP__

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
  struct Rusage_delta_pkey
  {
  public:
    bool operator==(Rusage_delta_pkey const& rhs) {
      return this == &rhs ||
        (id_ == rhs.id_);
    }

    bool operator<(Rusage_delta_pkey const& rhs) {
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

    friend inline std::ostream& operator<<(std::ostream& out, Rusage_delta_pkey const& item) {
      out << '\n' << "id:" << item.id_;
      return out;
    }

  };

  inline otl_stream& operator<<(otl_stream &out, Rusage_delta_pkey const& value) {
    out << value.id_;
    return out;
  }

  inline otl_stream& operator>>(otl_stream &out, Rusage_delta_pkey & value) {
    out >> value.id_;
    return out;
  }


  struct Rusage_delta_value
  {
  public:
    bool operator==(Rusage_delta_value const& rhs) {
      return this == &rhs ||
        (code_locations_id_ == rhs.code_locations_id_ &&
        created_ == rhs.created_ &&
        start_processor_ == rhs.start_processor_ &&
        end_processor_ == rhs.end_processor_ &&
        cpu_mhz_ == rhs.cpu_mhz_ &&
        debug_ == rhs.debug_ &&
        user_time_sec_ == rhs.user_time_sec_ &&
        user_time_usec_ == rhs.user_time_usec_ &&
        system_time_sec_ == rhs.system_time_sec_ &&
        system_time_usec_ == rhs.system_time_usec_ &&
        ru_maxrss_ == rhs.ru_maxrss_ &&
        ru_ixrss_ == rhs.ru_ixrss_ &&
        ru_idrss_ == rhs.ru_idrss_ &&
        ru_isrss_ == rhs.ru_isrss_ &&
        ru_minflt_ == rhs.ru_minflt_ &&
        ru_majflt_ == rhs.ru_majflt_ &&
        ru_nswap_ == rhs.ru_nswap_ &&
        ru_inblock_ == rhs.ru_inblock_ &&
        ru_oublock_ == rhs.ru_oublock_ &&
        ru_msgsnd_ == rhs.ru_msgsnd_ &&
        ru_msgrcv_ == rhs.ru_msgrcv_ &&
        ru_nsignals_ == rhs.ru_nsignals_ &&
        ru_nvcsw_ == rhs.ru_nvcsw_ &&
        ru_nivcsw_ == rhs.ru_nivcsw_);
    }

    bool operator<(Rusage_delta_value const& rhs) {
      return code_locations_id_ != rhs.code_locations_id_? code_locations_id_ < rhs.code_locations_id_ : (
        created_ != rhs.created_? created_ < rhs.created_ : (
        start_processor_ != rhs.start_processor_? start_processor_ < rhs.start_processor_ : (
        end_processor_ != rhs.end_processor_? end_processor_ < rhs.end_processor_ : (
        cpu_mhz_ != rhs.cpu_mhz_? cpu_mhz_ < rhs.cpu_mhz_ : (
        debug_ != rhs.debug_? debug_ < rhs.debug_ : (
        user_time_sec_ != rhs.user_time_sec_? user_time_sec_ < rhs.user_time_sec_ : (
        user_time_usec_ != rhs.user_time_usec_? user_time_usec_ < rhs.user_time_usec_ : (
        system_time_sec_ != rhs.system_time_sec_? system_time_sec_ < rhs.system_time_sec_ : (
        system_time_usec_ != rhs.system_time_usec_? system_time_usec_ < rhs.system_time_usec_ : (
        ru_maxrss_ != rhs.ru_maxrss_? ru_maxrss_ < rhs.ru_maxrss_ : (
        ru_ixrss_ != rhs.ru_ixrss_? ru_ixrss_ < rhs.ru_ixrss_ : (
        ru_idrss_ != rhs.ru_idrss_? ru_idrss_ < rhs.ru_idrss_ : (
        ru_isrss_ != rhs.ru_isrss_? ru_isrss_ < rhs.ru_isrss_ : (
        ru_minflt_ != rhs.ru_minflt_? ru_minflt_ < rhs.ru_minflt_ : (
        ru_majflt_ != rhs.ru_majflt_? ru_majflt_ < rhs.ru_majflt_ : (
        ru_nswap_ != rhs.ru_nswap_? ru_nswap_ < rhs.ru_nswap_ : (
        ru_inblock_ != rhs.ru_inblock_? ru_inblock_ < rhs.ru_inblock_ : (
        ru_oublock_ != rhs.ru_oublock_? ru_oublock_ < rhs.ru_oublock_ : (
        ru_msgsnd_ != rhs.ru_msgsnd_? ru_msgsnd_ < rhs.ru_msgsnd_ : (
        ru_msgrcv_ != rhs.ru_msgrcv_? ru_msgrcv_ < rhs.ru_msgrcv_ : (
        ru_nsignals_ != rhs.ru_nsignals_? ru_nsignals_ < rhs.ru_nsignals_ : (
        ru_nvcsw_ != rhs.ru_nvcsw_? ru_nvcsw_ < rhs.ru_nvcsw_ : (
        ru_nivcsw_ != rhs.ru_nivcsw_? ru_nivcsw_ < rhs.ru_nivcsw_ : (
        false))))))))))))))))))))))));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("code_locations_id_");
      out.push_back("created_");
      out.push_back("start_processor_");
      out.push_back("end_processor_");
      out.push_back("cpu_mhz_");
      out.push_back("debug_");
      out.push_back("user_time_sec_");
      out.push_back("user_time_usec_");
      out.push_back("system_time_sec_");
      out.push_back("system_time_usec_");
      out.push_back("ru_maxrss_");
      out.push_back("ru_ixrss_");
      out.push_back("ru_idrss_");
      out.push_back("ru_isrss_");
      out.push_back("ru_minflt_");
      out.push_back("ru_majflt_");
      out.push_back("ru_nswap_");
      out.push_back("ru_inblock_");
      out.push_back("ru_oublock_");
      out.push_back("ru_msgsnd_");
      out.push_back("ru_msgrcv_");
      out.push_back("ru_nsignals_");
      out.push_back("ru_nvcsw_");
      out.push_back("ru_nivcsw_");
    }

    inline
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(code_locations_id_));
      out.push_back(boost::lexical_cast< std::string >(created_));
      out.push_back(boost::lexical_cast< std::string >(start_processor_));
      out.push_back(boost::lexical_cast< std::string >(end_processor_));
      out.push_back(boost::lexical_cast< std::string >(cpu_mhz_));
      out.push_back(boost::lexical_cast< std::string >(debug_));
      out.push_back(boost::lexical_cast< std::string >(user_time_sec_));
      out.push_back(boost::lexical_cast< std::string >(user_time_usec_));
      out.push_back(boost::lexical_cast< std::string >(system_time_sec_));
      out.push_back(boost::lexical_cast< std::string >(system_time_usec_));
      out.push_back(boost::lexical_cast< std::string >(ru_maxrss_));
      out.push_back(boost::lexical_cast< std::string >(ru_ixrss_));
      out.push_back(boost::lexical_cast< std::string >(ru_idrss_));
      out.push_back(boost::lexical_cast< std::string >(ru_isrss_));
      out.push_back(boost::lexical_cast< std::string >(ru_minflt_));
      out.push_back(boost::lexical_cast< std::string >(ru_majflt_));
      out.push_back(boost::lexical_cast< std::string >(ru_nswap_));
      out.push_back(boost::lexical_cast< std::string >(ru_inblock_));
      out.push_back(boost::lexical_cast< std::string >(ru_oublock_));
      out.push_back(boost::lexical_cast< std::string >(ru_msgsnd_));
      out.push_back(boost::lexical_cast< std::string >(ru_msgrcv_));
      out.push_back(boost::lexical_cast< std::string >(ru_nsignals_));
      out.push_back(boost::lexical_cast< std::string >(ru_nvcsw_));
      out.push_back(boost::lexical_cast< std::string >(ru_nivcsw_));
    }

    int32_t code_locations_id_;
    otl_datetime created_;
    int32_t start_processor_;
    int32_t end_processor_;
    double cpu_mhz_;
    int32_t debug_;
    int64_t user_time_sec_;
    int64_t user_time_usec_;
    int64_t system_time_sec_;
    int64_t system_time_usec_;
    int64_t ru_maxrss_;
    int64_t ru_ixrss_;
    int64_t ru_idrss_;
    int64_t ru_isrss_;
    int64_t ru_minflt_;
    int64_t ru_majflt_;
    int64_t ru_nswap_;
    int64_t ru_inblock_;
    int64_t ru_oublock_;
    int64_t ru_msgsnd_;
    int64_t ru_msgrcv_;
    int64_t ru_nsignals_;
    int64_t ru_nvcsw_;
    int64_t ru_nivcsw_;

    friend inline std::ostream& operator<<(std::ostream& out, Rusage_delta_value const& item) {
      out << '\n' << "code_locations_id:" << item.code_locations_id_;
      out << '\n' << "created:" << item.created_;
      out << '\n' << "start_processor:" << item.start_processor_;
      out << '\n' << "end_processor:" << item.end_processor_;
      out << '\n' << "cpu_mhz:" << item.cpu_mhz_;
      out << '\n' << "debug:" << item.debug_;
      out << '\n' << "user_time_sec:" << item.user_time_sec_;
      out << '\n' << "user_time_usec:" << item.user_time_usec_;
      out << '\n' << "system_time_sec:" << item.system_time_sec_;
      out << '\n' << "system_time_usec:" << item.system_time_usec_;
      out << '\n' << "ru_maxrss:" << item.ru_maxrss_;
      out << '\n' << "ru_ixrss:" << item.ru_ixrss_;
      out << '\n' << "ru_idrss:" << item.ru_idrss_;
      out << '\n' << "ru_isrss:" << item.ru_isrss_;
      out << '\n' << "ru_minflt:" << item.ru_minflt_;
      out << '\n' << "ru_majflt:" << item.ru_majflt_;
      out << '\n' << "ru_nswap:" << item.ru_nswap_;
      out << '\n' << "ru_inblock:" << item.ru_inblock_;
      out << '\n' << "ru_oublock:" << item.ru_oublock_;
      out << '\n' << "ru_msgsnd:" << item.ru_msgsnd_;
      out << '\n' << "ru_msgrcv:" << item.ru_msgrcv_;
      out << '\n' << "ru_nsignals:" << item.ru_nsignals_;
      out << '\n' << "ru_nvcsw:" << item.ru_nvcsw_;
      out << '\n' << "ru_nivcsw:" << item.ru_nivcsw_;
      return out;
    }

  };

  inline otl_stream& operator<<(otl_stream &out, Rusage_delta_value const& value) {
    out << value.code_locations_id_
      << value.created_
      << value.start_processor_
      << value.end_processor_
      << value.cpu_mhz_
      << value.debug_
      << value.user_time_sec_
      << value.user_time_usec_
      << value.system_time_sec_
      << value.system_time_usec_
      << value.ru_maxrss_
      << value.ru_ixrss_
      << value.ru_idrss_
      << value.ru_isrss_
      << value.ru_minflt_
      << value.ru_majflt_
      << value.ru_nswap_
      << value.ru_inblock_
      << value.ru_oublock_
      << value.ru_msgsnd_
      << value.ru_msgrcv_
      << value.ru_nsignals_
      << value.ru_nvcsw_
      << value.ru_nivcsw_;
    return out;
  }

  inline otl_stream& operator>>(otl_stream &out, Rusage_delta_value & value) {
    out >> value.code_locations_id_
      >> value.created_
      >> value.start_processor_
      >> value.end_processor_
      >> value.cpu_mhz_
      >> value.debug_
      >> value.user_time_sec_
      >> value.user_time_usec_
      >> value.system_time_sec_
      >> value.system_time_usec_
      >> value.ru_maxrss_
      >> value.ru_ixrss_
      >> value.ru_idrss_
      >> value.ru_isrss_
      >> value.ru_minflt_
      >> value.ru_majflt_
      >> value.ru_nswap_
      >> value.ru_inblock_
      >> value.ru_oublock_
      >> value.ru_msgsnd_
      >> value.ru_msgrcv_
      >> value.ru_nsignals_
      >> value.ru_nvcsw_
      >> value.ru_nivcsw_;
    return out;
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

    static void print_recordset_as_table(Row_list_t const& recordset, std::ostream &out) {
      fcs::orm::print_recordset_as_table< Rusage_delta >(recordset, out);
    }

    static void print_values_as_table(Value_list_t const& values, std::ostream &out) {
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
      long rows_deleted { otl_cursor::direct_exec(*connection_, "DELETE FROM rusage_delta") };
      return size_t(rows_deleted);
    }

  private:
    otl_connect * connection_ {};

  };


} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // __FCS_ORM_CODE_METRICS_TABLE_RUSAGE_DELTA_HPP__
