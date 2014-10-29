#ifndef __FCS_ORM_ORM_HPP__
#define __FCS_ORM_ORM_HPP__

#include <vector>

namespace fcs {
namespace orm {
  using String_list_t = std::vector< std::string >;
  using String_table_t = std::vector< String_list_t >;

} // namespace orm
} // namespace fcs
#endif // __FCS_ORM_ORM_HPP__
