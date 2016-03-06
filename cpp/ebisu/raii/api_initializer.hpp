#ifndef __EBISU_RAII_API_INITIALIZER_HPP__
#define __EBISU_RAII_API_INITIALIZER_HPP__

#include "ebisu/logger/logger.hpp"
#include "ebisu/raii/raii_common.hpp"
#include "ebisu/raii/raii_logging.hpp"
#include <list>
#include <map>
#include <memory>
#include <vector>

namespace ebisu {
namespace raii {
using VoidFunc = void (*)(void);

//! Ensure functor is run on obect destruction

template <typename FUNCTOR = Void_func_t>
class FunctorScopeExit {
 public:
  using Functor = FUNCTOR;

  explicit FunctorScopeExit(Functor_t functor) : functor_(functor) {}

  // custom <ClsPublic Functor_scope_exit>

  ~Functor_scope_exit() {
    if (functor_) {
      functor_();
    }
  }

  // end <ClsPublic Functor_scope_exit>

  //! getter for functor_ (access is Ro)
  Functor_t functor() const { return functor_; }

 private:
  /**
   Function object to run on exit
  */
  Functor_t functor_;
};

//! Singleton registry for Apis requiring consistent init/uninit behavior

/**
 For APIs that need some form of initialization/uninitialization to be
 performed.

*/
template <typename INIT_FUNC = Void_func_t, typename UNINIT_FUNC = Void_func_t>
class ApiInitializerRegistry {
 public:
  using InitFunc = INIT_FUNC;
  using UninitFunc = UNINIT_FUNC;
  using FunctorScopeExit = Functor_scope_exit<Uninit_func_t>;
  using UninitWrapperPtr = std::shared_ptr<Functor_scope_exit_t>;
  using UninitList = std::list<Uninit_wrapper_ptr_t>;
  using Registry = std::map<Init_func_t, Uninit_wrapper_ptr_t>;

  ApiInitializerRegistry(ApiInitializerRegistry const& other) = delete;

  static ApiInitializerRegistry& instance() {
    static ApiInitializerRegistry instance_s;
    return instance_s;
  }

  // custom <ClsPublic Api_initializer_registry>

  ~Api_initializer_registry() {
    registry_.clear();
    while (!registry_ordered_.empty()) {
      registry_ordered_.pop_back();
    }
  }

  void register_initializer(Init_func_t init, Uninit_func_t uninit) {
    typedef std::pair<typename Registry_t::iterator, bool> Insert_result_t;

    Insert_result_t insert_result(registry_.insert(
        typename Registry_t::value_type(init, Uninit_wrapper_ptr_t())));

    if (insert_result.second) {
      insert_result.first->second =
          Uninit_wrapper_ptr_t(new Functor_scope_exit_t(uninit));

      registry_ordered_.push_back(insert_result.first->second);
      if (init) {
        init();
      }
    } else {
      if (insert_result.first->second->functor() != uninit) {
        throw std::logic_error(
            "Uninit functions must be consistent across translation units");
      }
    }
  }

  // end <ClsPublic Api_initializer_registry>

 private:
  ApiInitializerRegistry() {}

  Registry_t registry_{};
  Uninit_list_t registryOrdered_{};
};

//! Provide consistent *init*/*uninit* behavior

template <typename INIT_FUNC = Void_func_t, typename UNINIT_FUNC = Void_func_t>
class ApiInitializer {
 public:
  using ApiInitializerRegistryT =
      Api_initializer_registry<INIT_FUNC, UNINIT_FUNC>;

  // custom <ClsPublic Api_initializer>

  Api_initializer(INIT_FUNC init, UNINIT_FUNC uninit) {
    Api_initializer_registry<INIT_FUNC, UNINIT_FUNC>::instance()
        .register_initializer(init, uninit);
  }

  // end <ClsPublic Api_initializer>
};

}  // namespace raii
}  // namespace ebisu

#endif  // __EBISU_RAII_API_INITIALIZER_HPP__
