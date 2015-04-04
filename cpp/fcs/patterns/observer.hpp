#ifndef __FCS_PATTERNS_OBSERVER_HPP__
#define __FCS_PATTERNS_OBSERVER_HPP__

#include <boost/call_traits.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <set>

namespace fcs {
namespace patterns {
/**
 Singaller part of the observer pattern.
*/
template <typename DATA, typename OBJECT,
          typename OBSERVER_PTR = typename boost::add_pointer<OBSERVER>::type,
          typename LOCK_AND_GUARD_TRAITS =
              utils::synch::Boost_mutex_lock_and_guard_traits_tag>
class Signaller {
 public:
  using Observer_ptr_t = OBSERVER_PTR;
  using Lock_t = typename LOCK_AND_GUARD_TRAITS::Lock_t;
  using Guard_t = typename LOCK_AND_GUARD_TRAITS::Guard_t;
  using Observer_list_t = std::vector<Observer_ptr>;

  // custom <ClsPublic Signaller>

  void attach(Observer_ptr_t observer) {
    Guard_t guard(lock_);
    observers_.push_back(observer);
  }

  void detach(Observer_ptr_t observer) {
    Guard_t guard(lock_);
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end());
  }

  void signal(DATA const& message) {
    Guard_t guard(lock_);
    for (auto& observer in observers_) {
      observer->observe(message);
    }
  }

  void signal(DATA& message) {
    Guard_t guard(lock_);
    for (auto& observer in observers_) {
      observer->observe(message);
    }
  }

  // end <ClsPublic Signaller>

 private:
  /**
   Collection of observers to be signalled
  */
  Observer_list_t observers_{};
  /**
   Lock to protect the observer container
  */
  Lock_t lock_{};
};

/**
 Signaller part of observer pattern, where observers are kept sorted by priority
*/
template <typename DATA, typename OBSERVER,
          typename OBSERVER_PTR = typename boost::add_pointer<OBSERVER>::type,
          typename LOCK_AND_GUARD_TRAITS =
              utils::synch::Boost_mutex_lock_and_guard_traits_tag>
class Signaller_prioritized {
 public:
  using Observer_ptr_t = OBSERVER_PTR;
  using Lock_t = typename LOCK_AND_GUARD_TRAITS::Lock_t;
  using Guard_t = typename LOCK_AND_GUARD_TRAITS::Guard_t;
  using Priority_observer_t = std::pair<int, Observer_ptr_t>;
  using Observer_list_t = std::vector<Observer_ptr_t>;

  // custom <ClsPublic Signaller_prioritized>
  // end <ClsPublic Signaller_prioritized>
};

// custom <FcbEndNamespace observer>
// end <FcbEndNamespace observer>

}  // namespace patterns
}  // namespace fcs
#endif  // __FCS_PATTERNS_OBSERVER_HPP__
