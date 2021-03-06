#ifndef __EBISU_UTILS_STREAMERS_STREAMERS_HPP__
#define __EBISU_UTILS_STREAMERS_STREAMERS_HPP__

#include <iosfwd>
#include <memory>
#include <sstream>

namespace ebisu {
namespace utils {
namespace streamers {
// custom <FcbBeginNamespace streamers>

template <typename T1, typename T2>
inline std::ostream& operator<<(std::ostream& out, std::pair<T1, T2> const& p);
template <typename T>
inline std::ostream& operator<<(std::ostream& out, std::shared_ptr<T> const& p);

template <typename T1, typename T2>
inline std::ostream& print_key_value_pair(std::ostream& out,
                                          std::pair<T1, T2> const& p) {
  out << '(' << p.first << ',' << p.second << ")";
  return out;
}

//! Support for streaming std::pair
template <typename T1, typename T2>
inline std::ostream& operator<<(std::ostream& out, std::pair<T1, T2> const& p) {
  return print_key_value_pair<T1, T2>(out, p);
}

template <typename T>
inline std::ostream& print_scalar_collection(std::ostream& out,
                                             T const& collection) {
  out << '[';
  for (typename T::const_reference elm : collection) {
    out << elm << ',';
  }
  out << "]";
  return out;
}

template <typename ForwardIterator, typename T>
inline std::ostream& print_associative_collection(std::ostream& out,
                                                  ForwardIterator begin,
                                                  ForwardIterator end) {
  out << "[";
  for (; begin != end; ++begin) {
    T const& key_value(*begin);
    out << '(' << key_value.first << "=>" << key_value.second << "),";
  }
  out << "]";
  return out;
}

//! Support for streaming std::shared_ptr
template <typename T>
inline std::ostream& operator<<(std::ostream& out,
                                std::shared_ptr<T> const& p) {
  T* item(p.get());
  if (item) {
    T const& i(*item);
    out << i;
  } else {
    out << "(null)";
  }
  return out;
}

//! Support for streaming std::unique_ptr
template <typename T>
inline std::ostream& operator<<(std::ostream& out,
                                std::unique_ptr<T> const& p) {
  T* item(p.get());
  if (item) {
    T const& i(*item);
    out << i;
  } else {
    out << "(null)";
  }
  return out;
}

template <typename T>
inline std::string stream_to_string(T const& t) {
  std::ostringstream out;
  out << t;
  return out.str();
}

inline std::ostream& operator<<(std::ostream& out, std::uint8_t i) {
  out << static_cast<unsigned int>(i);
  return out;
}

inline std::ostream& operator<<(std::ostream& out, std::int8_t i) {
  out << static_cast<int>(i);
  return out;
}

// end <FcbBeginNamespace streamers>

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_STREAMERS_HPP__
