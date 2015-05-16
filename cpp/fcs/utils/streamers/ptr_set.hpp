#ifndef __FCS_UTILS_STREAMERS_PTR_SET_HPP__
#define __FCS_UTILS_STREAMERS_PTR_SET_HPP__

#include "fcs/utils/streamers/streamers.hpp"
#include "fcs/utils/streamers/streamers_initialization.hpp"
#include "fcs/utils/streamers/streamers_logging.hpp"
#include <boost/ptr_container/ptr_set.hpp>
#include <iosfwd>

namespace fcs {
namespace utils {
namespace streamers {
// custom <FcbBeginNamespace ptr_set>

//! Support for streaming boost::ptr_set
template <typename K, typename V, typename PR, typename ALLOC>
inline std::ostream& operator<<(std::ostream& out,
                                boost::ptr_set<K, V, PR, ALLOC> const& s) {
  return print_scalar_collection(out, s);
}
// end <FcbBeginNamespace ptr_set>

}  // namespace streamers
}  // namespace utils
}  // namespace fcs

#endif  // __FCS_UTILS_STREAMERS_PTR_SET_HPP__
