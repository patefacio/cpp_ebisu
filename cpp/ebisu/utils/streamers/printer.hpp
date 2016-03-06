#ifndef __EBISU_UTILS_STREAMERS_PRINTER_HPP__
#define __EBISU_UTILS_STREAMERS_PRINTER_HPP__

#include <ostream>
#include <string>

namespace ebisu {
namespace utils {
namespace streamers {
/**
 State of current print_instance request as propogated down a call stack.
*/
struct PrinterState {
  PrinterState() = default;

  PrinterState(int bytesAccessed, int frame)
      : bytesAccessed(bytesAccessed), frame(frame) {}

  /**
   Current number of bytes accessed
  */
  int bytesAccessed{0};

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
 more controlled/advanced print capabilities.  For example, sometimes
 it is helpful to print the first [max_bytes] bytes from an instance of
 an object coming off the wire.
*/
class PrinterSpec {
 public:
  PrinterSpec(int maxBytes = 0, bool nameTypes = false, bool nameMembers = true,
              bool nestedIndent = false,
              std::string const& memberSeparator = ",",
              std::string const& nameValueSeparator = "=",
              std::string const& finalSeparator = "\n")
      : maxBytes(maxBytes),
        nameTypes(nameTypes),
        nameMembers(nameMembers),
        nestedIndent(nestedIndent),
        memberSeparator(memberSeparator),
        nameValueSeparator(nameValueSeparator),
        finalSeparator(finalSeparator) {}

  /**
   Ensure that at most [max_bytes] of *instance* are accessed during printing
  */
  int maxBytes{};
  bool nameTypes{};
  bool nameMembers{};
  bool nestedIndent{};
  std::string memberSeparator{};
  std::string nameValueSeparator{};
  std::string instanceSeparator{};
  std::string finalSeparator{};
};

/**
 Combines the immutable spec with the mutable state which together
 propogate through a call stack on a [print_instance] request.
*/
class PrinterDescriptor {
 public:
  PrinterDescriptor(Printer_spec const& printerSpec)
      : printerSpec(printerSpec) {}

  // custom <ClsPublic Printer_descriptor>
  // end <ClsPublic Printer_descriptor>

  Printer_spec const printerSpec;
  Printer_state printerState{};
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
    std::ostream& out, std::string const& item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}

inline std::ostream& print_instance(
    std::ostream& out, short item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}

inline std::ostream& print_instance(
    std::ostream& out, long item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}
inline std::ostream& print_instance(
    std::ostream& out, long long item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}
inline std::ostream& print_instance(
    std::ostream& out, unsigned int item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}
inline std::ostream& print_instance(
    std::ostream& out, unsigned long item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}
inline std::ostream& print_instance(
    std::ostream& out, unsigned long long item,
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
    std::ostream& out, long double item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}
inline std::ostream& print_instance(
    std::ostream& out, char item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}
inline std::ostream& print_instance(
    std::ostream& out, signed char item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}
inline std::ostream& print_instance(
    std::ostream& out, unsigned char item,
    ebisu::utils::streamers::Printer_descriptor& printer_descriptor) {
  out << item;
  return out;
}

// end <FcbEndNamespace printer>

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_PRINTER_HPP__
