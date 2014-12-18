#ifndef __FCS_UTILS_VERSION_CONTROL_COMMIT_HPP__
#define __FCS_UTILS_VERSION_CONTROL_COMMIT_HPP__

namespace fcs {
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
  char const* const git_commit_{};
  char const* const search_string_{};
};

}  // namespace utils
}  // namespace fcs
#endif  // __FCS_UTILS_VERSION_CONTROL_COMMIT_HPP__
