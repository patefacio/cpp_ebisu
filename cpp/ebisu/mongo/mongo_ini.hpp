#ifndef __EBISU_MONGO_MONGO_INI_HPP__
#define __EBISU_MONGO_MONGO_INI_HPP__

#include "ebisu/mongo/mongo_logging.hpp"
#include <boost/program_options.hpp>
#include <boost/program_options/parsers.hpp>
#include <string>

namespace ebisu {
namespace mongo {
class Mongo_database_config {
 public:
  Mongo_database_config(std::string const& server, std::string const& user,
                        std::string const& password)
      : server_(server), user_(user), password_(password) {}

  //! getter for server_ (access is Ro)
  std::string const& server() const { return server_; }

  //! getter for user_ (access is Ro)
  std::string const& user() const { return user_; }

  //! getter for password_ (access is Ro)
  std::string const& password() const { return password_; }

 private:
  std::string const server_;
  std::string const user_;
  std::string const password_;
};

class Mongo_ini_parser {
 public:
  using Database_configuration_map_t =
      std::map<std::string, Mongo_database_config>;

  Mongo_ini_parser() {
    // custom <Mongo_ini_parser defaultCtor>
    // end <Mongo_ini_parser defaultCtor>
  }

 private:
  Database_configuration_map_t database_configuration_map_{};
  boost::program_options::options_description mongo_options_description_{};
};

}  // namespace mongo
}  // namespace ebisu

#endif  // __EBISU_MONGO_MONGO_INI_HPP__
