#ifndef __EBISU_LINUX_SPECIFIC_UMASK_SCOPED_SET_HPP__
#define __EBISU_LINUX_SPECIFIC_UMASK_SCOPED_SET_HPP__

#include "ebisu/linux_specific/linux_specific_initialization.hpp"
#include "ebisu/linux_specific/linux_specific_logging.hpp"
#include <sys/stat.h>
#include <sys/types.h>

namespace ebisu {
namespace linux_specific {
/**
 A typical use of this is to set the umask for a process to provide
 settings of system resources (files, mutexes, mappings,...)  to allow
 group members in. For instance, an app may create shared memory, and
 therefore an entry in /dev/shm, but to share it the permissions must
 work. umask settings play a role.
*/
class Umask_scoped_set {
 public:
  explicit Umask_scoped_set(mode_t new_mode)
      : previous_mode_{umask(new_mode)} {}

  // custom <ClsPublic Umask_scoped_set>

  ~Umask_scoped_set() { umask(previous_mode_); }

  // end <ClsPublic Umask_scoped_set>

  //! getter for previous_mode_ (access is Ro)
  mode_t previous_mode() const { return previous_mode_; }

 private:
  /**
   Original mode, restored to on destruction
  */
  mode_t previous_mode_;
};

}  // namespace linux_specific
}  // namespace ebisu

#endif  // __EBISU_LINUX_SPECIFIC_UMASK_SCOPED_SET_HPP__
