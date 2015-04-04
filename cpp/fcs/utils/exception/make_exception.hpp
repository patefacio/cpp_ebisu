#ifndef __FCS_UTILS_EXCEPTION_MAKE_EXCEPTION_HPP__
#define __FCS_UTILS_EXCEPTION_MAKE_EXCEPTION_HPP__

#include <boost/exception/all.hpp>
#include <exception>

namespace fcs {
namespace utils {
namespace exception {
// custom <FcbBeginNamespace make_exception>
template <typename EXCEPTION>
inline EXCEPTION make_exception(int line_number, char const* file) {
  return EXCEPTION() << boost::errinfo_at_line(line_number)
                     << boost::errinfo_file_name(file);
}

template <typename EXCEPTION>
inline EXCEPTION make_exception(char const* function_name, int line_number,
                                char const* file) {
  return EXCEPTION() << boost::errinfo_api_function(function_name)
                     << boost::errinfo_at_line(line_number)
                     << boost::errinfo_file_name(file);
}
// end <FcbBeginNamespace make_exception>

}  // namespace exception
}  // namespace utils
}  // namespace fcs

#endif  // __FCS_UTILS_EXCEPTION_MAKE_EXCEPTION_HPP__
