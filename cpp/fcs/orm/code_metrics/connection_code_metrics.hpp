#ifndef __FCS_ORM_CODE_METRICS_CONNECTION_CODE_METRICS_HPP__
#define __FCS_ORM_CODE_METRICS_CONNECTION_CODE_METRICS_HPP__

namespace fcs {
namespace orm {
namespace code_metrics {
  class Connection_code_metrics
  {
  public:
    static Connection_code_metrics & instance() {
      static Connection_code_metrics instance_s;
      return instance_s;
    }

  };


} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // __FCS_ORM_CODE_METRICS_CONNECTION_CODE_METRICS_HPP__
