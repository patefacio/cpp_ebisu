#ifndef __FCS_TIMESTAMP_CEREAL_HPP__
#define __FCS_TIMESTAMP_CEREAL_HPP__

#include "fcs/timestamp/timestamp.hpp"

namespace fcs {
namespace timestamp {}  // namespace timestamp
}  // namespace fcs
// custom <FcbPostNamespace cereal>

namespace cereal {

// template<class Archive>
// void save(Archive & archive,
//           fcs::timestamp::Timestamp_t const& ts)
// {
//   archive( fcs::timestamp::ticks(ts) );
// }

// template<class Archive>
// void load(Archive & archive,
//           fcs::timestamp::Timestamp_t & ts)
// {
//   using namespace fcs::timestamp;
//   long long ticks;
//   archive( ticks );
//   ts = Timestamp_t(Timestamp_t::time_rep_type(ticks));
// }

template <class Archive>
long long save_minimal(Archive const &, fcs::timestamp::Timestamp_t const &ts) {
  return fcs::timestamp::ticks(ts);
}

template <class Archive>
void load_minimal(Archive const &, fcs::timestamp::Timestamp_t &ts,
                  long long const &ticks) {
  using namespace fcs::timestamp;
  ts = Timestamp_t(Timestamp_t::time_rep_type(ticks));
}
}

// end <FcbPostNamespace cereal>

#endif  // __FCS_TIMESTAMP_CEREAL_HPP__
