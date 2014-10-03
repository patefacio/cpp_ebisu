#ifndef __FCS_UTILS_STREAMERS_DEQUE_HPP__
#define __FCS_UTILS_STREAMERS_DEQUE_HPP__

#include "fcs/utils/streamers/streamers.hpp"
#include <deque>
#include <iosfwd>

namespace fcs {
namespace utils {
namespace streamers {
  // custom <FcbBeginNamespace deque>

  //! Support for streaming std::deque
  template < typename T, typename ALLOC >
  inline std::ostream& operator<<(std::ostream& out, std::deque< T, ALLOC > const& d) {
    return print_scalar_collection(out, d);
  }

  // end <FcbBeginNamespace deque>

} // namespace streamers
} // namespace utils
} // namespace fcs
#endif // __FCS_UTILS_STREAMERS_DEQUE_HPP__
