#ifndef __EBISU_MONGO_CONNECTION_REGISTRY_HPP__
#define __EBISU_MONGO_CONNECTION_REGISTRY_HPP__

#include "ebisu/mongo/mongo_logging.hpp"
#include <mutex>

namespace ebisu {
namespace mongo {
template <typename LOCK = std::mutex, typename GUARD = std::lock_guard<LOCK> >
class Connection_registry {
 public:
  using Lock_t = LOCK;
  using Guard_t = GUARD;

  Connection_registry(Connection_registry const& other) = delete;

  static Connection_registry& instance() {
    static Connection_registry instance_s;
    return instance_s;
  }

 private:
  Connection_registry() {}
};

}  // namespace mongo
}  // namespace ebisu

#endif  // __EBISU_MONGO_CONNECTION_REGISTRY_HPP__
