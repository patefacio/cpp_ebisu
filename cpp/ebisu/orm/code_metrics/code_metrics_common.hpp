#ifndef __EBISU_ORM_CODE_METRICS_CODE_METRICS_COMMON_HPP__
#define __EBISU_ORM_CODE_METRICS_CODE_METRICS_COMMON_HPP__

#include "ebisu/orm/orm_common.hpp"

namespace ebisu {
namespace orm {
namespace code_metrics {
class Connection_code_metrics {
 public:
  Connection_code_metrics(Connection_code_metrics const& other) = delete;

  static Connection_code_metrics& instance() {
    static Connection_code_metrics instance_s;
    return instance_s;
  }

  otl_connect* connection() { return tss_connection_.get(); }

 private:
  Connection_code_metrics() {
    otl_connect* connection = new otl_connect;
    connection->rlogon("DSN=code_metrics", 0);
    tss_connection_.reset(connection);
  }

  boost::thread_specific_ptr<otl_connect> tss_connection_{};
};

}  // namespace code_metrics
}  // namespace orm
}  // namespace ebisu

#endif  // __EBISU_ORM_CODE_METRICS_CODE_METRICS_COMMON_HPP__
