#ifndef __EBISU_LINUX_SPECIFIC_LINUX_EXCEPTIONS_HPP__
#define __EBISU_LINUX_SPECIFIC_LINUX_EXCEPTIONS_HPP__

#include "ebisu/linux_specific/linux_specific_logging.hpp"
#include <boost/exception/error_info.hpp>
#include <boost/exception/exception.hpp>
#include <exception>
#include <string>

namespace ebisu {
namespace linux_specific {
/**
 Indicates parsing of system file failed
*/
class System_file_parse_exception : public virtual boost::exception,
                                    public virtual std::exception {
 public:
  using Filename_tag_t =
      boost::error_info<struct tag_filename_tag, std::string>;
};

}  // namespace linux_specific
}  // namespace ebisu

#endif  // __EBISU_LINUX_SPECIFIC_LINUX_EXCEPTIONS_HPP__
