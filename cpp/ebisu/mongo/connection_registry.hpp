#ifndef __EBISU_MONGO_CONNECTION_REGISTRY_HPP__
#define __EBISU_MONGO_CONNECTION_REGISTRY_HPP__

#include "ebisu/mongo/mongo_ini.hpp"
#include "ebisu/mongo/mongo_logging.hpp"
#include "mongo/client/dbclient.h"
#include <mutex>

namespace ebisu {
namespace mongo {
template <typename LOCK = std::mutex, typename GUARD = std::lock_guard<LOCK> >
class Connection_registry {
 public:
  using Lock_t = LOCK;
  using Guard_t = GUARD;
  using Database_configuration_map_t =
      Mongo_ini_parser::Database_configuration_map_t;
  using Tss_connection_ptr_t =
      boost::thread_specific_ptr< ::mongo::DBClientConnection>*;
  using Thread_connection_map_t = std::map<std::string, Tss_connection_ptr_t>;

  Connection_registry(Connection_registry const& other) = delete;

  Connection_registry(Connection_registry&& other) = delete;

  Connection_registry& operator=(Connection_registry const&) = delete;

  Connection_registry& operator=(Connection_registry&&) = delete;

  static Connection_registry& instance() {
    static Connection_registry instance_s;
    return instance_s;
  }

 private:
  Connection_registry() {}

  Database_configuration_map_t database_configuration_map_{};
  Lock_t lock_{};
  Thread_connection_map_t thread_connection_map_{};
};

}  // namespace mongo
}  // namespace ebisu

#endif  // __EBISU_MONGO_CONNECTION_REGISTRY_HPP__
