#ifndef __EBISU_TIMESTAMP_CEREAL_HPP__
#define __EBISU_TIMESTAMP_CEREAL_HPP__

#include "ebisu/timestamp/timestamp.hpp"
#include <cstdint>

namespace ebisu {
namespace timestamp {}  // namespace timestamp
}  // namespace ebisu

// custom <FcbPostNamespace cereal>

namespace cereal {

template <class Archive>
int64_t save_minimal(Archive const&, ebisu::timestamp::Timestamp_t const& ts) {
  return ebisu::timestamp::ticks(ts);
}

template <class Archive>
void load_minimal(Archive const&, ebisu::timestamp::Timestamp_t& ts,
                  int64_t const& ticks) {
  using namespace ebisu::timestamp;
  ts = Timestamp_t(Timestamp_t::time_rep_type(ticks));
}
}

// end <FcbPostNamespace cereal>

#endif  // __EBISU_TIMESTAMP_CEREAL_HPP__
