#ifndef __FCS_TIMESTAMP_CONVERSION_HPP__
#define __FCS_TIMESTAMP_CONVERSION_HPP__

#include "fcs/timestamp/timestamp.hpp"
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <regex>

namespace fcs {
namespace timestamp {
  // custom <FcbEndNamespace conversion>

  inline
  bool convert_to_timestamp_from_ticks(std::string const& timestamp, Timestamp_t &result) {
    static std::regex const timestamp_ticks_re("\\d+");
    try {
      if(std::regex_match(timestamp, timestamp_ticks_re)) {
        long long ticks(boost::lexical_cast< long long >(timestamp));
        result = Timestamp_t(Timestamp_t::time_rep_type(ticks));
        return true;
      }
    } catch(std::exception const&) {
    }
    return false;
  }

  inline
  bool convert_to_timestamp_from_iso(std::string const& timestamp, Timestamp_t &result) {
    static std::regex const timestamp_re("\\d+T[\\d\\.]+");
    try {
      std::string excp_text;
      if(std::regex_match(timestamp, timestamp_re)) {
        result = boost::posix_time::from_iso_string(timestamp);
        return true;
      }
    } catch(std::exception const&) {
    }
    return false;
  }

  inline
  bool convert_to_timestamp_from_string(std::string const& timestamp, Timestamp_t &result) {
    try {
      result = boost::posix_time::time_from_string(timestamp);
      return true;
    } catch(std::exception const&) {
    }
    return false;
  }

  inline
  bool convert_to_date_from_undelimited_string(std::string const& timestamp, Date_t &result) {
    try {
      result = boost::gregorian::from_undelimited_string(timestamp);
      return true;
    } catch(std::exception const&) {
    }
    return false;
  }

  inline
  bool convert_to_date_from_julian(std::string const& timestamp, Date_t &result) {
    static std::regex const julian_re("\\d+");
    try {
      if(std::regex_match(timestamp, julian_re)) {
        Date_t d(2000, 1, 1);
        long d_julian(d.julian_day());
        long prospective_date(boost::lexical_cast< long >(timestamp));
        d += boost::gregorian::date_duration(prospective_date - d_julian);
        result = d;
        return true;
      }
    } catch(std::exception const&) {
    }
    return false;
  }

  inline
  bool convert_to_date_from_modjulian(std::string const& timestamp, Date_t &result) {
    static std::regex const modjulian_re("\\d+");
    try {
      if(std::regex_match(timestamp, modjulian_re)) {
        Date_t d(2000, 1, 1);
        long d_modjulian(d.modjulian_day());
        long prospective_date(boost::lexical_cast< long >(timestamp));
        d += boost::gregorian::date_duration(prospective_date - d_modjulian);
        result = d;
        return true;
      }
    } catch(std::exception const&) {
    }
    return false;
  }

  // end <FcbEndNamespace conversion>

} // namespace timestamp
} // namespace fcs
#endif // __FCS_TIMESTAMP_CONVERSION_HPP__
