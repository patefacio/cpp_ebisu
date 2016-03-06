#ifndef __EBISU_MONGO_CONNECTION_REGISTRY_HPP__
#define __EBISU_MONGO_CONNECTION_REGISTRY_HPP__

#include "ebisu/mongo/mongo_ini.hpp"
#include "ebisu/mongo/mongo_logging.hpp"
#include "mongo/client/dbclient.h"
#include <mutex>

namespace ebisu {
namespace mongo {
template <typename LOCK = std::mutex, typename GUARD = std::lock_guard<LOCK> >
class ConnectionRegistry {
 public:
  using Lock = LOCK;
  using Guard = GUARD;
  using DatabaseConfigurationMap =
      Mongo_ini_parser::Database_configuration_map_t;
  using TssConnectionPtr =
      boost::thread_specific_ptr< ::mongo::DBClientConnection>*;
  using ThreadConnectionMap = std::map<std::string, Tss_connection_ptr_t>;

  ConnectionRegistry(ConnectionRegistry const& other) = delete;

  static ConnectionRegistry& instance() {
    static ConnectionRegistry instance_s;
    return instance_s;
  }

 private:
  ConnectionRegistry() {}

  Database_configuration_map_t database_configuration_map_{};
  Lock_t lock_{};
  Thread_connection_map_t thread_connection_map_{};
};

}  // namespace mongo
}  // namespace ebisu

#endif  // __EBISU_MONGO_CONNECTION_REGISTRY_HPP__
