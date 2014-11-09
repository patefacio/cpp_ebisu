#ifndef __FCS_TIMESTAMP_TIMESTAMP_HPP__
#define __FCS_TIMESTAMP_TIMESTAMP_HPP__

#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/microsec_time_clock.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace fcs {
namespace timestamp {
  using Timestamp_t = boost::posix_time::ptime;
  using Time_duration_t = boost::posix_time::time_duration;
  using Date_t = boost::gregorian::date;

  // custom <FcbEndNamespace timestamp>

  inline
  Timestamp_t current_time() {
    return boost::posix_time::microsec_clock::universal_time();
  }

  inline
  Timestamp_t utc_to_local_time(Timestamp_t t) {
    typedef boost::date_time::c_local_adjustor< boost::posix_time::ptime > local_adj;
    return local_adj::utc_to_local(t);
  }

  inline
  Time_duration_t::tick_type ticks(Timestamp_t t) {
    Timestamp_t const zero(Timestamp_t::time_rep_type(0LL));
    return (t - zero).ticks();
  }

  // end <FcbEndNamespace timestamp>

} // namespace timestamp
} // namespace fcs
#endif // __FCS_TIMESTAMP_TIMESTAMP_HPP__
