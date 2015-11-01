#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/logger/logger.hpp"

// custom <custom includes>
// end <custom includes>

namespace ebisu {
namespace logger {
// custom <logger begin namespace>
// end <logger begin namespace>

SCENARIO("default logger") {
  // custom <(621264441)>

  std::shared_ptr<spdlog::logger> spdlogger =
      spdlog::stdout_logger_mt("logger");

  spdlog::set_level(spdlog::level::debug);
  spdlogger->set_level(spdlog::level::debug);
  Logger<> logger{spdlogger};

  logger.debug("This is working {}", 3.14);

  spdlogger->debug("Baddabing");

  // end <(621264441)>
}
SCENARIO("null logger") {
  // custom <(671142183)>

  Null_logger_t logger{Null_logger_impl()};

  logger.debug("This is working {}", 3.14);

  // end <(671142183)>
}

}  // namespace logger
}  // namespace ebisu
