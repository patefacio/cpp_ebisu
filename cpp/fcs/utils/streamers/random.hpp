#ifndef __FCS_UTILS_STREAMERS_RANDOM_HPP__
#define __FCS_UTILS_STREAMERS_RANDOM_HPP__

#include "fcs/orm/otl_utils.hpp"
#include "fcs/timestamp/timestamp.hpp"
#include "fcs/utils/fixed_size_char_array.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include "fcs/utils/streamers/streamers_initialization.hpp"
#include "fcs/utils/streamers/streamers_logging.hpp"
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>

namespace fcs {
namespace utils {
namespace streamers {
class Random_source {
 public:
  // custom <ClsPublic Random_source>

  Random_source(std::uint_fast32_t seed = 42) : engine{seed} {}

  // end <ClsPublic Random_source>

  std::mt19937 engine;
};

// custom <ClsPostDecl Random_source>

template <typename T>
void generate_integer(T &t, std::mt19937 &engine) {
  std::uniform_int_distribution<T> dist{std::numeric_limits<T>::min(),
                                        std::numeric_limits<T>::max()};
  t = dist(engine);
}

template <typename T>
void generate_real(T &t, std::mt19937 &engine) {
  std::uniform_real_distribution<T> dist{std::numeric_limits<T>::min(),
                                         std::numeric_limits<T>::max()};
  t = dist(engine);
}

template <class T>
Random_source &operator>>(Random_source &source, T &t);

template <>
Random_source &operator>>(Random_source &source, int &t) {
  generate_integer(t, source.engine);
  return source;
}
template <>
Random_source &operator>>(Random_source &source, long &t) {
  generate_integer(t, source.engine);
  return source;
}
template <>
Random_source &operator>>(Random_source &source, long long &t) {
  generate_integer(t, source.engine);
  return source;
}

template <>
Random_source &operator>>(Random_source &source, float &t) {
  generate_real(t, source.engine);
  return source;
}
template <>
Random_source &operator>>(Random_source &source, double &t) {
  generate_real(t, source.engine);
  return source;
}
template <>
Random_source &operator>>(Random_source &source, uint8_t &t) {
  generate_integer(t, source.engine);
  return source;
}
template <>
Random_source &operator>>(Random_source &source, uint16_t &t) {
  generate_integer(t, source.engine);
  return source;
}
template <>
Random_source &operator>>(Random_source &source, uint32_t &t) {
  generate_integer(t, source.engine);
  return source;
}
template <>
Random_source &operator>>(Random_source &source, uint64_t &t) {
  generate_integer(t, source.engine);
  return source;
}

template <>
Random_source &operator>>(Random_source &source, char &c) {
  static const char alphanum[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";
  std::uniform_int_distribution<int> alpha_dist{0, sizeof(alphanum) - 2};
  c = alphanum[alpha_dist(source.engine)];
  return source;
}

template <>
Random_source &operator>>(Random_source &source, std::string &s) {
  std::uniform_int_distribution<int> dist{3, 15};
  int len{dist(source.engine)};
  s.clear();
  s.reserve(len);
  for (int i = 0; i < len; ++i) {
    char c;
    source >> c;
    s += c;
  }
  return source;
}

template <template <typename, typename> class Container, class V, class A>
Random_source &generate_push_back_data(Random_source &source,
                                       Container<V, A> &container) {
  std::uniform_int_distribution<int> dist{3, 15};
  int len{dist(source.engine)};
  container.clear();
  for (int i = 0; i < len; ++i) {
    V elm;
    source >> elm;
    container.push_back(elm);
  }
  return source;
}

template <typename T, typename ALLOC>
inline Random_source &operator>>(Random_source &source,
                                 std::vector<T, ALLOC> &v) {
  return generate_push_back_data(source, v);
}

template <typename T, typename ALLOC>
inline Random_source &operator>>(Random_source &source,
                                 std::deque<T, ALLOC> &v) {
  return generate_push_back_data(source, v);
}

template <int ARRAY_SIZE>
inline Random_source &operator>>(Random_source &source,
                                 Fixed_size_char_array<ARRAY_SIZE> &fsca) {
  const int end = ARRAY_SIZE - 1;
  for (int i = 0; i < end; ++i) {
    source >> fsca[i];
  }
  if (ARRAY_SIZE > 0) {
    fsca[end] = 0;
  }
  return source;
}

template <>
inline Random_source &operator>>(Random_source &source,
                                 fcs::timestamp::Timestamp_t &ts) {
  using namespace boost::posix_time;
  using namespace fcs::timestamp;
  ptime end{max_date_time};
  ptime start{min_date_time};
  time_duration max_diff{end - start};
  std::uniform_int_distribution<long long> dist{
      0, max_diff.total_milliseconds() - 1};

  auto random_offset = dist(source.engine);
  ts = start + milliseconds(random_offset);
  return source;
}

template <>
inline Random_source &operator>>(Random_source &source,
                                 fcs::timestamp::Date_t &date) {
  fcs::timestamp::Timestamp_t ts;
  source >> ts;
  date = ts.date();
  return source;
}

template <>
inline Random_source &operator>>(Random_source &source, otl_datetime &date) {
  fcs::timestamp::Timestamp_t ts;
  source >> ts;
  fcs::orm::boost_ptime_to_otl_type(ts, date);
  return source;
}

// end <ClsPostDecl Random_source>

}  // namespace streamers
}  // namespace utils
}  // namespace fcs

#endif  // __FCS_UTILS_STREAMERS_RANDOM_HPP__
