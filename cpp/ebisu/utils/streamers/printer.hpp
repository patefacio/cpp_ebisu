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
 Printer specification passed to print_instance methods, supporting
 more controlled/advanced print functions.  For example, some times it
 is helpful to print some [N] bytes from an instance of an object
 coming off the wire.

*/
class Printer_spec {
 public:
  Printer_spec(int max_bytes_accessed, bool name_types, bool name_members,
               std::string const& member_separator,
               std::string const& name_value_separator,
               std::string const& instance_separator,
               std::string const& final_separator)
      : max_bytes_accessed_(max_bytes_accessed),
        name_types_(name_types),
        name_members_(name_members),
        member_separator_(member_separator),
        name_value_separator_(name_value_separator),
        instance_separator_(instance_separator),
        final_separator_(final_separator) {}

  //! getter for max_bytes_accessed_ (access is Ro)
  int max_bytes_accessed() const { return max_bytes_accessed_; }

  //! getter for name_types_ (access is Ro)
  bool name_types() const { return name_types_; }

  //! getter for name_members_ (access is Ro)
  bool name_members() const { return name_members_; }

  //! getter for member_separator_ (access is Ro)
  std::string const& member_separator() const { return member_separator_; }

  //! getter for name_value_separator_ (access is Ro)
  std::string const& name_value_separator() const {
    return name_value_separator_;
  }

  //! getter for instance_separator_ (access is Ro)
  std::string const& instance_separator() const { return instance_separator_; }

  //! getter for final_separator_ (access is Ro)
  std::string const& final_separator() const { return final_separator_; }

 private:
  /**
   Ensure that at most [max_bytes] of *instance* are accessed during printing
  */
  int const max_bytes_accessed_;
  bool const name_types_;
  bool const name_members_;
  std::string const member_separator_;
  std::string const name_value_separator_;
  std::string const instance_separator_;
  std::string const final_separator_;
};

/**
 Combines the immutable spec witht the mutable state which together
 propogate through a call stack on a [print_instance] request.

*/
class Printer_descriptor {
 private:
  Printer_spec printer_spec_{};
  Printer_state printer_state_{};
};

}  // namespace streamers
}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_STREAMERS_PRINTER_HPP__
