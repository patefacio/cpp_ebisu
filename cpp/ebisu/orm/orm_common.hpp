#ifndef __EBISU_ORM_ORM_COMMON_HPP__
#define __EBISU_ORM_ORM_COMMON_HPP__

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/thread/tss.hpp>
#include <map>
#include <mutex>
#include <set>
#include <vector>

// custom <FcbCustomIncludes orm_common>

class otl_connect;

// end <FcbCustomIncludes orm_common>

namespace ebisu {
namespace orm {

/**
 List of strings
*/
using StringList = std::vector<std::string>;

/**
 Standard table of strings
*/
using StringTable = std::vector<String_list_t>;
using DateT = boost::gregorian::date;
using DateSetT = std::set<Date_t>;

template <int OTL_LOG_LEVEL = 0>
class OtlLogLevel {
 public:
  // custom <ClsPublic Otl_log_level>

  static int get_otl_log_level() { return level_; }

  static void set_otl_log_level(int level) { level_ = level; }

  // end <ClsPublic Otl_log_level>

 private:
  static int level_;
};

// custom <ClsPostDecl Otl_log_level>

template <int OTL_LOG_LEVEL>
int Otl_log_level<OTL_LOG_LEVEL>::level_ = OTL_LOG_LEVEL;

inline void set_otl_log_level(int level) {
  Otl_log_level<>::set_otl_log_level(level);
}

// end <ClsPostDecl Otl_log_level>

}  // namespace orm
}  // namespace ebisu

// custom <FcbPostNamespace orm_common>

#if defined(_MSC_VER)
#define OTL_ODBC
#endif

//#define OTL_MAP_LONG_TO_SQL_C_SBIGINT

#define OTL_BIGINT long long
#define OTL_STREAM_NO_PRIVATE_BOOL_OPERATORS
#define OTL_TRACE_LEVEL ebisu::orm::Otl_log_level<0>::get_otl_log_level()
unsigned int my_trace_level = 0x1 |   // 1st level of tracing
                              0x2 |   // 2nd level of tracing
                              0x4 |   // 3rd level of tracing
                              0x8 |   // 4th level of tracing
                              0x10 |  // 5th level of tracing
                              0x20;   // 6th level of tracing
//#define OTL_TRACE_LEVEL my_trace_level
#define OTL_TRACE_STREAM std::cerr
#if !defined(OTL_TRACE_LINE_PREFIX)
#define OTL_TRACE_LINE_PREFIX "OTL => "
#endif

#include <iostream>
using Orm_bigint_t = long long;

// end <FcbPostNamespace orm_common>

#endif  // __EBISU_ORM_ORM_COMMON_HPP__
