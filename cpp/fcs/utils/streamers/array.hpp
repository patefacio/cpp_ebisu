#ifndef __FCS_UTILS_STREAMERS_ARRAY_HPP__
#define __FCS_UTILS_STREAMERS_ARRAY_HPP__

#include "fcs/utils/streamers/streamers.hpp"
#include <array>
#include <iosfwd>

namespace fcs {
namespace utils {
namespace streamers {
// custom <FcbBeginNamespace array>

//! Support for streaming std::list
template <typename T, size_t N>
inline std::ostream& operator<<(std::ostream& out,
                                std::array<T, N> const& arr) {
  return print_scalar_collection(out, arr);
}

// end <FcbBeginNamespace array>

}  // namespace streamers
}  // namespace utils
}  // namespace fcs

#endif  // __FCS_UTILS_STREAMERS_ARRAY_HPP__
