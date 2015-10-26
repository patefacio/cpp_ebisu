#ifndef __EBISU_UTILS_STREAMERS_ARRAY_HPP__
#define __EBISU_UTILS_STREAMERS_ARRAY_HPP__

#include "ebisu/utils/streamers/streamers.hpp"
#include <array>
#include <iosfwd>

namespace ebisu {
namespace utils {
namespace streamers {
// custom <FcbBeginNamespace array>

//! Streams an std::array of objects
template <typename T, size_t N>
inline std::ostream& operator<<(std::ostream& out,
                                std::array<T, N> const& arr) {
  return print_scalar_collection(out, arr);
}

//! Streams std::array as character string instead of array of chars
template <size_t N>
inline std::ostream& operator<<(std::ostream& out,
                                std::array<char, N> const& arr) {
  return out.write(&arr[0], N);
}


// end <FcbBeginNamespace array>

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_ARRAY_HPP__
