#ifndef __EBISU_UTILS_VERSION_CONTROL_COMMIT_HPP__
#define __EBISU_UTILS_VERSION_CONTROL_COMMIT_HPP__

namespace ebisu {
namespace utils {
/**
 Provide static data with git commit for quickly identifying contents of build
 with linux strings program
*/
class Version_control_commit {
 public:
  static Version_control_commit& instance() {
    static Version_control_commit instance_s;
    return instance_s;
  }

 private:
  Version_control_commit() {}

  char const* const git_commit_{};
  char const* const search_string_{};
};

}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_VERSION_CONTROL_COMMIT_HPP__
