#ifndef __EBISU_UTILS_STREAMERS_SET_HPP__
#define __EBISU_UTILS_STREAMERS_SET_HPP__

#include "ebisu/utils/streamers/streamers.hpp"
#include "ebisu/utils/streamers/streamers_initialization.hpp"
#include "ebisu/utils/streamers/streamers_logging.hpp"
#include <iosfwd>
#include <set>

namespace ebisu {
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
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_SET_HPP__
