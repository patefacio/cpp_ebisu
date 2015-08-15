#ifndef __EBISU_UTILS_STREAMERS_DEQUE_HPP__
#define __EBISU_UTILS_STREAMERS_DEQUE_HPP__

#include "ebisu/utils/streamers/streamers.hpp"
#include <deque>
#include <iosfwd>

namespace ebisu {
namespace utils {
namespace streamers {
// custom <FcbBeginNamespace deque>

//! Support for streaming std::deque
template <typename T, typename ALLOC>
inline std::ostream& operator<<(std::ostream& out,
                                std::deque<T, ALLOC> const& d) {
  return print_scalar_collection(out, d);
}

// end <FcbBeginNamespace deque>

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_DEQUE_HPP__
