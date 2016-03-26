#ifndef __EBISU_ENVIRONMENT_ENVIRONMENT_HPP__
#define __EBISU_ENVIRONMENT_ENVIRONMENT_HPP__

#include "ebisu/utils/streamers/map.hpp"
#include "ebisu/utils/streamers/vector.hpp"
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <exception>
#include <iosfwd>
#include <sstream>
#include <unistd.h>
#include <vector>

namespace ebisu {
namespace environment {
/**
 Singleton that when initialized churns through various environment variables
 like LD_LIBRARY_PATH, MANPATH, PATH, etc...
 The purpose is to make the paths those variables refer to available to code.
*/
class Environment {
 public:
  using Environment_map_t = std::map<std::string, std::string>;
  using Path_variable_set_t = std::set<std::string>;
  using Path_t = boost::filesystem::path;
  using Path_list_t = std::vector<Path_t>;
  using Path_variable_map_t = std::map<std::string, Path_list_t>;

  Environment(Environment const& other) = delete;

  Environment(Environment&& other) = delete;

  Environment& operator=(Environment const&) = delete;

  Environment& operator=(Environment&&) = delete;

  friend inline std::ostream& operator<<(std::ostream& out,
                                         Environment const& item) {
    using ebisu::utils::streamers::operator<<;
    out << "Environment(" << &item << ") {";
    out << "\n  environment:" << item.environment_;
    out << "\n  path_variable_map:" << item.path_variable_map_;
    out << "\n}\n";
    return out;
  }

  static Environment& instance() {
    static Environment instance_s;
    return instance_s;
  }

  //! getter for environment_ (access is Ro)
  Environment_map_t const& environment() const { return environment_; }

  //! getter for path_variable_map_ (access is Ro)
  Path_variable_map_t const& path_variable_map() const {
    return path_variable_map_;
  }

 private:
  // custom <ClsPrivate Environment>

  void read_environment() {
    char** env(environ);
    if (env) {
      if (!environment_.empty()) {
        std::ostringstream msg;
        msg << "Environment::parse_from_envp can only be called once on "
               "singleton";
        throw std::runtime_error(msg.str());
      } else {
        for (; env && *env; ++env) {
          std::string key_value(*env);
          size_t equal_pos(key_value.find_first_of('='));
          if (equal_pos != std::string::npos) {
            environment_[key_value.substr(0, equal_pos)] =
                key_value.substr(equal_pos + 1);
          }
        }
      }
    }

    char const* common_paths[] = {"LD_LIBRARY_PATH", "MANPATH",    "PATH",
                                  "PERLPATH",        "PYTHONPATH", "RUBYLIB"};

    size_t end(sizeof(common_paths) / sizeof(char const*));
    boost::regex const path_split_regex(":");
    for (size_t i(0); i < end; ++i) {
      Environment_map_t::const_iterator found(
          environment_.find(common_paths[i]));
      if (environment_.end() != found) {
        std::string const& path_variable(found->first);
        std::string path_list_text(found->second);
        typedef std::vector<std::string> Tokens_t;
        Tokens_t tokens;
        boost::regex_split(std::back_inserter(tokens), path_list_text,
                           path_split_regex);
        Tokens_t::const_iterator path_end(tokens.end());
        Path_list_t& path_list(path_variable_map_[path_variable]);
        for (Tokens_t::const_iterator path_it(tokens.begin());
             path_it != path_end; ++path_it) {
          path_list.push_back(*path_it);
        }
      }
    }
  }

  // end <ClsPrivate Environment>

  Environment() { read_environment(); }

  Environment_map_t environment_{};
  Path_variable_map_t path_variable_map_{};
};

}  // namespace environment
}  // namespace ebisu

#endif  // __EBISU_ENVIRONMENT_ENVIRONMENT_HPP__
