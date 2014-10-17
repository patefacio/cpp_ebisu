#ifndef __FCS_RAII_CHANGE_TRACKER_HPP__
#define __FCS_RAII_CHANGE_TRACKER_HPP__

namespace fcs {
namespace raii {
  class Change_tracker
  {
  private:
    T saved_value_ {};
    T target_ {};

  };


  class Change_tracker_next_value
  {
  };


} // namespace raii
} // namespace fcs
#endif // __FCS_RAII_CHANGE_TRACKER_HPP__
