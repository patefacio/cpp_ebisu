#ifndef __EBISU_UTILS_VERSION_CONTROL_COMMIT_HPP__
#define __EBISU_UTILS_VERSION_CONTROL_COMMIT_HPP__

namespace ebisu {
namespace utils {
/**
 Provide static data with git commit for quickly identifying contents of build
 with linux strings program
*/
class VersionControlCommit {
 public:
  VersionControlCommit(VersionControlCommit const& other) = delete;

  static VersionControlCommit& instance() {
    static VersionControlCommit instance_s;
    return instance_s;
  }

 private:
  VersionControlCommit() {}

  char const* const git_commit_{};
  char const* const search_string_{};
};

}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_VERSION_CONTROL_COMMIT_HPP__
