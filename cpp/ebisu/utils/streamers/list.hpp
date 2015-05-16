#ifndef __EBISU_UTILS_STREAMERS_LIST_HPP__
#define __EBISU_UTILS_STREAMERS_LIST_HPP__

#include "ebisu/utils/streamers/streamers.hpp"
#include "ebisu/utils/streamers/streamers_initialization.hpp"
#include "ebisu/utils/streamers/streamers_logging.hpp"
#include <iosfwd>
#include <list>

namespace ebisu {
namespace utils {
namespace streamers {
// custom <FcbBeginNamespace list>

//! Support for streaming std::list
template <typename T, typename ALLOC>
inline std::ostream& operator<<(std::ostream& out,
                                std::list<T, ALLOC> const& l) {
  return print_scalar_collection(out, l);
}

// end <FcbBeginNamespace list>

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_LIST_HPP__
