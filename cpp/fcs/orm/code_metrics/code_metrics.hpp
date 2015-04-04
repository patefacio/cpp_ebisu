#ifndef __FCS_ORM_CODE_METRICS_CODE_METRICS_HPP__
#define __FCS_ORM_CODE_METRICS_CODE_METRICS_HPP__

#include "fcs/orm/orm.hpp"

namespace fcs {
namespace orm {
namespace code_metrics {
class Connection_code_metrics {
 public:
  static Connection_code_metrics &instance() {
    static Connection_code_metrics instance_s;
    return instance_s;
  }

  otl_connect *connection() { return tss_connection_.get(); }

 private:
  Connection_code_metrics() {
    otl_connect *connection = new otl_connect;
    connection->rlogon("DSN=code_metrics", 0);
    tss_connection_.reset(connection);
  }

  boost::thread_specific_ptr<otl_connect> tss_connection_{};
};

}  // namespace code_metrics
}  // namespace orm
}  // namespace fcs

#endif  // __FCS_ORM_CODE_METRICS_CODE_METRICS_HPP__
