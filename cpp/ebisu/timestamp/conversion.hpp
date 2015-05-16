#ifndef __EBISU_TIMESTAMP_CONVERSION_HPP__
#define __EBISU_TIMESTAMP_CONVERSION_HPP__

#include "ebisu/timestamp/conversion_initialization.hpp"
#include "ebisu/timestamp/conversion_logging.hpp"
#include "ebisu/timestamp/timestamp.hpp"
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/regex.hpp>

namespace ebisu {
namespace timestamp {
// custom <FcbEndNamespace conversion>

inline bool convert_to_timestamp_from_ticks(std::string const& timestamp,
                                            Timestamp_t& result) {
  static boost::regex const timestamp_ticks_re("\\d+");
  try {
    if (boost::regex_match(timestamp, timestamp_ticks_re)) {
      long long ticks(boost::lexical_cast<long long>(timestamp));
      result = Timestamp_t(Timestamp_t::time_rep_type(ticks));
      return true;
    }
  } catch (std::exception const&) {
  }
  return false;
}

inline bool convert_to_timestamp_from_iso(std::string const& timestamp,
                                          Timestamp_t& result) {
  static boost::regex const timestamp_re("\\d+T[\\d\\.]+");
  try {
    std::string excp_text;
    if (boost::regex_match(timestamp, timestamp_re)) {
      result = boost::posix_time::from_iso_string(timestamp);
      return true;
    }
  } catch (std::exception const&) {
  }
  return false;
}

inline bool convert_to_timestamp_from_string(std::string const& timestamp,
                                             Timestamp_t& result) {
  try {
    result = boost::posix_time::time_from_string(timestamp);
    return true;
  } catch (std::exception const&) {
  }
  return false;
}

inline bool convert_to_date_from_undelimited_string(
    std::string const& timestamp, Date_t& result) {
  try {
    result = boost::gregorian::from_undelimited_string(timestamp);
    return true;
  } catch (std::exception const&) {
  }
  return false;
}

inline bool convert_to_date_from_julian(std::string const& timestamp,
                                        Date_t& result) {
  static boost::regex const julian_re("\\d+");
  try {
    if (boost::regex_match(timestamp, julian_re)) {
      Date_t d(2000, 1, 1);
      long d_julian(d.julian_day());
      long prospective_date(boost::lexical_cast<long>(timestamp));
      d += boost::gregorian::date_duration(prospective_date - d_julian);
      result = d;
      return true;
    }
  } catch (std::exception const&) {
  }
  return false;
}

inline bool convert_to_date_from_modjulian(std::string const& timestamp,
                                           Date_t& result) {
  static boost::regex const modjulian_re("\\d+");
  try {
    if (boost::regex_match(timestamp, modjulian_re)) {
      Date_t d(2000, 1, 1);
      long d_modjulian(d.modjulian_day());
      long prospective_date(boost::lexical_cast<long>(timestamp));
      d += boost::gregorian::date_duration(prospective_date - d_modjulian);
      result = d;
      return true;
    }
  } catch (std::exception const&) {
  }
  return false;
}

time_t to_time_t(Timestamp_t t) {
  Timestamp_t epoch{boost::gregorian::date(1970, 1, 1)};
  auto secs = (t - epoch).total_seconds();
  return time_t{secs};
}

// end <FcbEndNamespace conversion>

}  // namespace timestamp
}  // namespace ebisu

#endif  // __EBISU_TIMESTAMP_CONVERSION_HPP__
