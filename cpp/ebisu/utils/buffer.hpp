#ifndef __EBISU_UTILS_BUFFER_HPP__
#define __EBISU_UTILS_BUFFER_HPP__

namespace ebisu {
namespace utils {
using Buffer_cptr_t = char const*;

// custom <FcbEndNamespace buffer>

inline std::string binary_data_to_literal(Buffer_cptr_t start,
                                          Buffer_cptr_t end) {
  assert(start <= end);
  size_t length = end - start;
  std::ostringstream out;
  out << '"' << std::hex;
  for (; start < end; ++start) {
    out << "\\x" << int(*start);
  }
  out << '"';
  return out.str();
}

// end <FcbEndNamespace buffer>

}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_BUFFER_HPP__
