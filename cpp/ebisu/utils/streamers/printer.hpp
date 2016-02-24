#ifndef __EBISU_UTILS_STREAMERS_PRINTER_HPP__
#define __EBISU_UTILS_STREAMERS_PRINTER_HPP__

#include <string>

namespace ebisu {
namespace utils {
namespace streamers {
/**
 State of current print_instance request as propogated down a call stack.

*/
struct Printer_state {
  Printer_state() = default;

  Printer_state(int bytes_accessed, int frame)
      : bytes_accessed(bytes_accessed), frame(frame) {}

  /**
   Current number of bytes accessed
  */
  int bytes_accessed{0};

  /**
   Current frame for the printer.

   Used to determine if the current frame is the original opening frame
   (ie frame 0) and therefore on completion should append a
   [final_separator].

  */
  int frame{0};
};

/**
 Printer specification passed to [print_instance] methods, supporting
 more controlled/advanced print capabilities.  For example, some times
 it is helpful to print some [max_bytes] bytes from an instance of an
 object coming off the wire.

*/
class Printer_spec {
 public:
  Printer_spec(int max_bytes = 0, bool name_types = false,
               bool name_members = true, bool nested_indent = false,
               std::string const& member_separator = ",",
               std::string const& name_value_separator = "=",
               std::string const& final_separator = "\n")
      : max_bytes(max_bytes),
        name_types(name_types),
        name_members(name_members),
        nested_indent(nested_indent),
        member_separator(member_separator),
        name_value_separator(name_value_separator),
        final_separator(final_separator) {}

  /**
   Ensure that at most [max_bytes] of *instance* are accessed during printing
  */
  int max_bytes{};
  bool name_types{};
  bool name_members{};
  bool nested_indent{};
  std::string member_separator{};
  std::string name_value_separator{};
  std::string instance_separator{};
  std::string final_separator{};
};

/**
 Combines the immutable spec with the mutable state which together
 propogate through a call stack on a [print_instance] request.

*/
class Printer_descriptor {
 public:
  Printer_descriptor(Printer_spec const& printer_spec)
      : printer_spec(printer_spec) {}

  // custom <ClsPublic Printer_descriptor>
  // end <ClsPublic Printer_descriptor>

  Printer_spec const printer_spec;
  Printer_state printer_state{};
};

// custom <FcbEndNamespace printer>

inline Printer_spec const& dense_printer_spec() {
  static Printer_spec const printer_spec;
  return printer_spec;
}

inline Printer_spec const& terse_printer_spec() {
  static Printer_spec const printer_spec{0, false, false};
  return printer_spec;
}

inline Printer_spec const& sparse_printer_spec() {
  static Printer_spec const printer_spec{0, true, true, true, ",\n", ":", "\n"};
  return printer_spec;
}

inline std::ostream& print_instance(
    std::ostream& out, int item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}

inline std::ostream& print_instance(
    std::ostream& out, double item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}

inline std::ostream& print_instance(
    std::ostream& out, std::string const& item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}

// end <FcbEndNamespace printer>

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_PRINTER_HPP__
