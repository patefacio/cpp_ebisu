#ifndef __EBISU_UTILS_STREAMERS_PTR_VECTOR_HPP__
#define __EBISU_UTILS_STREAMERS_PTR_VECTOR_HPP__

#include "ebisu/utils/streamers/streamers.hpp"
#include <boost/ptr_container/ptr_vector.hpp>
#include <iosfwd>

namespace ebisu {
namespace utils {
namespace streamers {
// custom <FcbBeginNamespace ptr_vector>

//! Support for streaming boost::ptr_vector
template <typename T, typename ALLOC>
inline std::ostream& operator<<(std::ostream& out,
                                boost::ptr_vector<T, ALLOC> const& v) {
  return print_scalar_collection(out, v);
}

// end <FcbBeginNamespace ptr_vector>

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_PTR_VECTOR_HPP__
