#ifndef __FCS_UTILS_STREAMERS_SET_HPP__
#define __FCS_UTILS_STREAMERS_SET_HPP__

#include "fcs/utils/streamers/streamers.hpp"
#include <iosfwd>
#include <set>

namespace fcs {
namespace utils {
namespace streamers {
// custom <FcbBeginNamespace set>

//! Support for streaming std::list
template <typename T, typename PR, typename ALLOC>
inline std::ostream& operator<<(std::ostream& out,
                                std::set<T, PR, ALLOC> const& l) {
  return print_scalar_collection(out, l);
}

// end <FcbBeginNamespace set>

}  // namespace streamers
}  // namespace utils
}  // namespace fcs
#endif  // __FCS_UTILS_STREAMERS_SET_HPP__
