#ifndef __EBISU_UTILS_FIXED_SIZE_CHAR_ARRAY_HPP__
#define __EBISU_UTILS_FIXED_SIZE_CHAR_ARRAY_HPP__

#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

namespace ebisu {
namespace utils {
template <int ARRAY_SIZE>
class Fixed_size_char_array {
 public:
  using Array_t = std::array<char, ARRAY_SIZE>;

  static constexpr int BUFFER_SIZE{ARRAY_SIZE};

  static constexpr int LAST_INDEX{ARRAY_SIZE - 1};

  // custom <ClsPublic Fixed_size_char_array>

  Fixed_size_char_array() { data_[LAST_INDEX] = data_[0] = 0; }

  explicit Fixed_size_char_array(char const* s) { this->operator=(s); }

  explicit Fixed_size_char_array(std::string const& s) { this->operator=(s); }

  Fixed_size_char_array(Fixed_size_char_array const& other) {
    this->operator=(other.operator char const*());
  }

  void operator=(char const* s) {
    if (this->operator const char*() != s) {
      std::strncpy(&data_[0], s, ARRAY_SIZE);
    }
  }

  void operator=(std::string const& s) {
    if (!s.empty()) {
      std::memcpy(&data_[0], s.c_str(), ARRAY_SIZE);
    }
  }

  operator char const*() const { return &data_[0]; }

  operator char*() { return &data_[0]; }

  char& operator[](int i) { return get_char_ref(i); }

  char const& operator[](int i) const { return get_char_ref(i); }

  operator std::string() const { return str(); }

  std::string str() const {
    return std::string(&data_[0], strnlen(&data_[0], ARRAY_SIZE));
  }

  void clear() { data_[0] = 0; }

  void clean() { std::memset(&data_[0], 0, ARRAY_SIZE); }

  bool operator==(Fixed_size_char_array const& other) const {
    return *this == other.operator char const*();
  }

  bool operator==(char const* other) const {
    if (&data_[0] == other) {
      return true;
    } else {
      return (0 == std::strncmp(const_cast<char*>(this->operator char const*()),
                                other, ARRAY_SIZE));
    }
  }

  bool operator==(std::string const& s) const {
    return 0 == std::strncmp(s.c_str(), &data_[0],
                             std::min(s.size(), size_t(ARRAY_SIZE)));
  }

  bool operator<(Fixed_size_char_array const& other) const {
    return (std::strncmp(const_cast<char*>(this->operator char const*()), other,
                         ARRAY_SIZE) < 0);
  }

  bool operator!=(Fixed_size_char_array const& other) const {
    return !(*this == other);
  }

  void nassign(char const* c, size_t num) {
    assert(num <= ARRAY_SIZE);
    std::memcpy(&data_[0], c, num);
  }

  // end <ClsPublic Fixed_size_char_array>

 private:
  // custom <ClsPrivate Fixed_size_char_array>

  char& get_char_ref(int i) {
    assert(i < BUFFER_SIZE);
    return data_[i];
  }

  // end <ClsPrivate Fixed_size_char_array>

  Array_t data_{};
};

// custom <ClsPostDecl Fixed_size_char_array>

template <int ARRAY_SIZE>
inline std::ostream& operator<<(std::ostream& out,
                                Fixed_size_char_array<ARRAY_SIZE> const& item) {
  out.write(item.operator char const*(), ARRAY_SIZE);
  return out;
}

template <int ARRAY_SIZE>
inline std::istream& operator>>(std::istream& in,
                                Fixed_size_char_array<ARRAY_SIZE>& item) {
  in.read(item.operator char*(), ARRAY_SIZE);
  return in;
}

// end <ClsPostDecl Fixed_size_char_array>

}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_FIXED_SIZE_CHAR_ARRAY_HPP__
