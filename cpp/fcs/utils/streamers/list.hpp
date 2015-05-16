#ifndef __FCS_UTILS_STREAMERS_LIST_HPP__
#define __FCS_UTILS_STREAMERS_LIST_HPP__

#include "fcs/utils/streamers/streamers.hpp"
#include "fcs/utils/streamers/streamers_initialization.hpp"
#include "fcs/utils/streamers/streamers_logging.hpp"
#include <iosfwd>
#include <list>

namespace fcs {
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
}  // namespace fcs

#endif  // __FCS_UTILS_STREAMERS_LIST_HPP__
