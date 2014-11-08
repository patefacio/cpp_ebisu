#ifndef __FCS_ORM_ORM_HPP__
#define __FCS_ORM_ORM_HPP__

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/thread/tss.hpp>
#include <map>
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
//#define OTL_TRACE_LEVEL fcs::orm::Otl_log_level< 0 >::get_otl_log_level()
      unsigned int my_trace_level=
        0x1 | // 1st level of tracing
        0x2 | // 2nd level of tracing
        0x4 | // 3rd level of tracing
        0x8 | // 4th level of tracing
        0x10| // 5th level of tracing
        0x20; // 6th level of tracing
#define OTL_TRACE_LEVEL my_trace_level
#define OTL_TRACE_STREAM std::cerr
#define OTL_TRACE_LINE_PREFIX "OTL => "

#include <iostream>
#include "otlv4.h"

// end <FcbPostNamespace orm>

#endif // __FCS_ORM_ORM_HPP__
