#ifndef __FCS_UTILS_STREAMERS_PTR_MAP_HPP__
#define __FCS_UTILS_STREAMERS_PTR_MAP_HPP__

#include "fcs/utils/streamers/streamers.hpp"
#include <boost/ptr_container/ptr_map.hpp>
#include <iosfwd>

namespace fcs {
namespace utils {
namespace streamers {
  // custom <FcbBeginNamespace ptr_map>

  //! Support for streaming boost::ptr_map
  template < typename K, typename V, typename PR, typename CLONE_ALLOC, typename ALLOC >
  inline std::ostream& operator<<(std::ostream& out, boost::ptr_map< K,V,PR,CLONE_ALLOC,ALLOC > const& m) {
    typename boost::ptr_map< K,V,PR,CLONE_ALLOC,ALLOC >::const_iterator it(m.begin());
    typename boost::ptr_map< K,V,PR,CLONE_ALLOC,ALLOC >::const_iterator end(m.end());
    out << '[';
    for(; it != end; ++it) {
      out << '(' << it->first << "=>";
      if(it->second) {
        out << *it->second;
      } else {
        out << "<null>";
      }
      out << "),";
    }
    out << ']';
    return out;
  }

  //! Support for streaming boost::ptr_multimap
  template < typename K, typename V, typename PR, typename CLONE_ALLOC, typename ALLOC >
  inline std::ostream& operator<<(std::ostream& out, boost::ptr_multimap< K,V,PR,CLONE_ALLOC,ALLOC > const& m) {
    typename boost::ptr_map< K,V,PR,CLONE_ALLOC,ALLOC >::const_iterator it(m.begin());
    typename boost::ptr_map< K,V,PR,CLONE_ALLOC,ALLOC >::const_iterator end(m.end());
    out << '[';
    for(; it != end; ++it) {
      out << '(' << it->first << "=>";
      if(it->second) {
        out << *it->second;
      } else {
        out << "<null>";
      }
      out << "),";
    }
    out << ']';
    return out;
  }

  // end <FcbBeginNamespace ptr_map>

}  // namespace streamers
}  // namespace utils
}  // namespace fcs
#endif  // __FCS_UTILS_STREAMERS_PTR_MAP_HPP__
