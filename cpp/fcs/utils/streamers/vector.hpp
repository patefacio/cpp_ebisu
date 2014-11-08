#ifndef __FCS_UTILS_STREAMERS_VECTOR_HPP__
#define __FCS_UTILS_STREAMERS_VECTOR_HPP__

#include "fcs/utils/streamers/streamers.hpp"
#include <iosfwd>
#include <vector>

namespace fcs {
namespace utils {
namespace streamers {
  // custom <FcbBeginNamespace vector>

  //! Support for streaming std::vector
  template < typename T, typename ALLOC >
  inline std::ostream& operator<<(std::ostream& out, std::vector< T, ALLOC > const& v) {
    return fcs::utils::streamers::print_scalar_collection(out, v);
  }

  // end <FcbBeginNamespace vector>

} // namespace streamers
} // namespace utils
} // namespace fcs
#endif // __FCS_UTILS_STREAMERS_VECTOR_HPP__
