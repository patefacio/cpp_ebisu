#ifndef __FCS_RAII_CHANGE_TRACKER_HPP__
#define __FCS_RAII_CHANGE_TRACKER_HPP__

#include "fcs/raii/raii_common.hpp"
#include "fcs/raii/raii_initialization.hpp"
#include "fcs/raii/raii_logging.hpp"
#include <boost/call_traits.hpp>

namespace fcs {
namespace raii {
//! Track updates to variable.

/**
 Tracks current/previous values of the given type of data. For some
 algorithms it is useful to be able to examine/perform logic on
 current value and compare or evalutate how it has changed since
 previous value.
*/
template <typename T>
class Change_tracker {
 public:
  // custom <ClsPublic Change_tracker>

  Change_tracker(T current) : current_{current}, previous_{} {}

  Change_tracker(T current, T previous)
      : current_{current}, previous_{previous} {}

  void next_value(T next_value) {
    previous_ = current_;
    current_ = next_value;
  }

  // end <ClsPublic Change_tracker>

  //! getter for current_ (access is Ro)
  T current() const { return current_; }

  //! getter for previous_ (access is Ro)
  T previous() const { return previous_; }

 private:
  T current_{};
  T previous_{};
};

//! Work with current value, ensure next value is applied on scope exit.

/**
 Uses a ChangeTracker to track current/previous values of a type and
 ensures that on destruction the previous value becomes the current
 value and the current value will be assigned the next value.
*/
template <typename T>
class Change_tracker_next_value {
 public:
  using Change_tracker_t = Change_tracker<T>;

  // custom <ClsPublic Change_tracker_next_value>

  Change_tracker_next_value(Change_tracker_t &tracker, T next_value)
      : tracker_(tracker), next_value_(next_value) {}

  ~Change_tracker_next_value() { tracker_.next_value(next_value_); }

  // end <ClsPublic Change_tracker_next_value>

  //! getter for tracker_ (access is Ro)
  Change_tracker_t const &tracker() const { return tracker_; }

  //! getter for next_value_ (access is Ro)
  T next_value() const { return next_value_; }

 private:
  Change_tracker_t &tracker_;
  T next_value_{};
};

//! Change and use value within block, revert to original on scope exit.

/**
 Stores the current state, changes that state to a new value and on
 destruction restores the original state.
*/
template <typename T>
class Change_until_end_of_block {
 public:
  // custom <ClsPublic Change_until_end_of_block>

  Change_until_end_of_block(
      T &target, typename boost::call_traits<T>::param_type new_value)
      : target_{target}, saved_value_{target} {
    target_ = new_value;
  }

  ~Change_until_end_of_block() { target_ = saved_value_; }

  // end <ClsPublic Change_until_end_of_block>

  //! getter for target_ (access is Ro)
  T target() const { return target_; }

  //! getter for saved_value_ (access is Ro)
  T saved_value() const { return saved_value_; }

 private:
  /**
   Reference to the item being changed for duration of block
  */
  T &target_;

  /**
   Value saved on construction and used to reset on block exit
  */
  T saved_value_{};
};

}  // namespace raii
}  // namespace fcs

#endif  // __FCS_RAII_CHANGE_TRACKER_HPP__
