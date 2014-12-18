#ifndef __FCS_UTILS_FIXED_SIZE_CHAR_ARRAY_HPP__
#define __FCS_UTILS_FIXED_SIZE_CHAR_ARRAY_HPP__

#include <boost/array.hpp>
#include <cassert>
#include <cstring>
#include <string>

namespace fcs {
namespace utils {
template <int ARRAY_SIZE>
class Fixed_size_char_array {
 public:
  using Array_t = boost::array<char, ARRAY_SIZE>;

  static int const BUFFER_SIZE{ARRAY_SIZE};
  static int const LAST_INDEX{ARRAY_SIZE - 1};

    // custom <ClsPublic Fixed_size_char_array>

    Fixed_size_char_array() {
      data_[LAST_INDEX] = data_[0] = 0;
    }

    Fixed_size_char_array(char const* s) {
      this->operator=(s);
    }

    Fixed_size_char_array(Fixed_size_char_array const& other) {
      this->operator=(other.operator char const*());
    }

    void operator=(char const* s) {
      if(this->operator const char*() != s) {
        std::strncpy(&data_[0], s, LAST_INDEX);
        data_[LAST_INDEX] = 0;
      }
    }

    operator char const* () const {
      return &data_[0];
    }

    operator char * () {
      return &data_[0];
    }

    char & operator[](int i) {
      return get_char_ref(i);
    }

    char const& operator[](int i) const {
      return get_char_ref(i);
    }

    operator std::string () const {
      return std::string(&data_[0]);
    }

    std::string str() const {
      return std::string(&data_[0]);
    }

    void clear() {
      data_[0] = 0;
    }

    void clean() {
      std::memset(&data_[0], 0, ARRAY_SIZE);
    }

    bool operator==(Fixed_size_char_array const& other) const {
      return *this == other.operator char const* ();
    }

    bool operator==(char const* other) const {
      if(&data_[0] == other) {
        return true;
      } else {
        return (0 == std::strncmp(const_cast<char *>(this->operator char const*()), other, ARRAY_SIZE));
      }
    }

    bool operator<(Fixed_size_char_array const& other) const {
      return (std::strncmp(const_cast<char *>(this->operator char const*()), other, ARRAY_SIZE) < 0);
    }

    bool operator!=(Fixed_size_char_array const& other) const {
      return !(*this == other);
    }

    // end <ClsPublic Fixed_size_char_array>

 private:
    // custom <ClsPrivate Fixed_size_char_array>

    char & get_char_ref(int i) {
      assert(i < BUFFER_SIZE);
      return data_[i];
    }

    // end <ClsPrivate Fixed_size_char_array>

  Array_t data_{};
};

  // custom <ClsPostDecl Fixed_size_char_array>

  template < int ARRAY_SIZE >
  inline
  std::ostream& operator<<(std::ostream &out,
                           Fixed_size_char_array< ARRAY_SIZE > const& item) {
    out << item.operator char const *();
    return out;
  }

  // end <ClsPostDecl Fixed_size_char_array>

}  // namespace utils
}  // namespace fcs
#endif  // __FCS_UTILS_FIXED_SIZE_CHAR_ARRAY_HPP__
