#ifndef __EBISU_UTILS_STREAMERS_VECTOR_HPP__
#define __EBISU_UTILS_STREAMERS_VECTOR_HPP__

#include "ebisu/utils/streamers/streamers.hpp"
#include "ebisu/utils/streamers/streamers_initialization.hpp"
#include "ebisu/utils/streamers/streamers_logging.hpp"
#include <iosfwd>
#include <vector>

namespace ebisu {
namespace utils {
namespace streamers {
// custom <FcbBeginNamespace vector>

//! Support for streaming std::vector
template <typename T, typename ALLOC>
inline std::ostream& operator<<(std::ostream& out,
                                std::vector<T, ALLOC> const& v) {
  return print_scalar_collection(out, v);
}

// end <FcbBeginNamespace vector>

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_VECTOR_HPP__
