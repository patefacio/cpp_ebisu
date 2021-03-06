#ifndef __EBISU_UTILS_STREAMERS_MAP_HPP__
#define __EBISU_UTILS_STREAMERS_MAP_HPP__

#include "ebisu/utils/streamers/streamers.hpp"
#include <iosfwd>
#include <map>

namespace ebisu {
namespace utils {
namespace streamers {
// custom <FcbBeginNamespace map>

//! Support for streaming std::map
template <typename K, typename V, typename PR, typename ALLOC>
inline std::ostream& operator<<(std::ostream& out,
                                std::map<K, V, PR, ALLOC> const& m) {
  return print_associative_collection<
      typename std::map<K, V, PR, ALLOC>::const_iterator,
      typename std::map<K, V, PR, ALLOC>::value_type>(out, m.begin(), m.end());
}

//! Support for streaming std::multimap
template <typename K, typename V, typename PR, typename ALLOC>
inline std::ostream& operator<<(std::ostream& out,
                                std::multimap<K, V, PR, ALLOC> const& m) {
  return print_associative_collection<
      typename std::multimap<K, V, PR, ALLOC>::const_iterator,
      typename std::multimap<K, V, PR, ALLOC>::value_type>(out, m.begin(),
                                                           m.end());
}

// end <FcbBeginNamespace map>

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_MAP_HPP__
