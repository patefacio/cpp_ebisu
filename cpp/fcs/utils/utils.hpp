#ifndef __FCS_UTILS_UTILS_HPP__
#define __FCS_UTILS_UTILS_HPP__

#include <boost/array>
#include <cmath>
#include <iostream>

namespace fcs {
namespace utils {
  class Value_min_max
  {
  };


  template< int ARRAY_SIZE >
  class Fixed_size_char_array
  {
  public:
    using Array_t = boost::array< char, ARRAY_SIZE >;

    // custom <ClsPublic Fixed_size_char_array>
    // end <ClsPublic Fixed_size_char_array>

    static int const BUFFER_SIZE { ARRAY_SIZE };
    static int const LAST_INDEX { ARRAY_SIZE-- };

  private:
    Array_t data_ {};

  };


  class Version_control_commit
  {
  };


} // namespace utils
} // namespace fcs
#endif // __FCS_UTILS_UTILS_HPP__
