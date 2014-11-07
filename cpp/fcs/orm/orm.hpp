#ifndef __FCS_ORM_ORM_HPP__
#define __FCS_ORM_ORM_HPP__

#include <boost/date_time/gregorian/gregorian.hpp>
#include <mutex>
#include <set>
#include <vector>

// custom <FcbCustomIncludes orm>

class otl_connect;

// end <FcbCustomIncludes orm>

namespace fcs {
namespace orm {
  using String_list_t = std::vector< std::string >;
  using String_table_t = std::vector< String_list_t >;
  using Date_t = boost::gregorian::date;
  using Date_set_t = std::set< Date_t >;

  class Connection_info
  {
  public:
    Connection_info(
      std::string user_id,
      std::string password,
      std::string dsn) :
      user_id_ { user_id },
      password_ { password },
      dsn_ { dsn } {
    }

    // custom <ClsPublic Connection_info>

    std::string connection_string() {
      std::string result;
      if(!user_id_.empty()) {
        result = "UID=";
        result += user_id_;
      }
      if(!password_.empty()) {
        result += "PWD=";
        result += password_;
      }
      if(!dsn_.empty()) {
        result += "DSN=";
        result += dsn_;
      }
      return result;
    }

    // end <ClsPublic Connection_info>

    //! getter for user_id_ (access is Ro)
    std::string user_id() const { return user_id_; }

    //! getter for password_ (access is Ro)
    std::string password() const { return password_; }

    //! getter for dsn_ (access is Ro)
    std::string dsn() const { return dsn_; }
  private:
    std::string user_id_ {};
    std::string password_ {};
    std::string dsn_ {};

  };


  template< typename LOCK_TYPE = std::mutex,
            typename GUARD_TYPE = std::lock_guard< LOCK_TYPE > >
  class Connection_registry
  {
  public:
    using Lock_t = LOCK_TYPE;
    using Guard_t = GUARD_TYPE;
    using Connection_info_map_t = std::map< std::string, Connection_info >;
    using Thread_connection_ptr = boost::thread_specific_ptr< otl_connect >;
    using Thread_connection_map_t = std::map< std::string, Thread_connection_ptr >;

    static Connection_registry & instance() {
      static Connection_registry instance_s;
      return instance_s;
    }

    // custom <ClsPublic Connection_registry>

    void register_connection_info(std::string const& connection_name,
                                  Connection_info const& connection_info) {
      Guard_t guard = { lock_ };
      connection_info_map_[connection_name] = connection_info;
    }

    Connection_info retrieve_connection_info(std::string const& connection_name) {
      Guard_t guard { lock_ };
      Connection_info_map_t::iterator found =
        connection_info_map_.find(connection_name);
      if(found == connection_info_map_.end()) {
        std::string msg = "Connection name is not in connection repository: ";
        msg += connection_name;
        throw std::invalid_argument(msg);
      }

      return found->second;
    }

    // end <ClsPublic Connection_registry>

  private:
    Connection_info_map_t connection_info_map_ {};
    Lock_t lock_ {};
    Thread_connection_map_t thread_connection_map_ {};

  };


  template< int OTL_LOG_LEVEL = 0 >
  class Otl_log_level
  {
  public:
    // custom <ClsPublic Otl_log_level>

    static int get_otl_log_level() {
      return level_;
    }

    static void set_otl_log_level(int level) {
      level_ = level;
    }

    // end <ClsPublic Otl_log_level>

  private:
    static int level_;

  };

  // custom <ClsPostDecl Otl_log_level>

  template< int OTL_LOG_LEVEL >
  int Otl_log_level< OTL_LOG_LEVEL >::level_ = OTL_LOG_LEVEL;

  inline
  void set_otl_log_level(int level) {
    Otl_log_level<>::set_otl_log_level(level);
  }

// end <ClsPostDecl Otl_log_level>


} // namespace orm
} // namespace fcs
// custom <FcbPostNamespace orm>


#if defined (_MSC_VER)
#define OTL_ODBC
#endif

typedef long long otl_bigint;
#define OTL_BIGINT otl_bigint
#define OTL_STREAM_NO_PRIVATE_BOOL_OPERATORS
#define OTL_TRACE_LEVEL fcs::orm::Otl_log_level< 0 >::get_otl_log_level()
#define OTL_TRACE_STREAM std::cerr
#define OTL_TRACE_LINE_PREFIX "OTL => "

#include <iostream>
#include "otlv4.h"

// end <FcbPostNamespace orm>

#endif // __FCS_ORM_ORM_HPP__
