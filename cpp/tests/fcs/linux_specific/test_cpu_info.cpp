#include "fcs/linux_specific/cpu_info.hpp"
#include <boost/test/included/unit_test.hpp>
#include <iostream>

namespace fcs {
namespace linux_specific {
enum Side { Bid_side_e, Ask_side_e };

void test_cpu_info() {
  // custom <cpu_info>

  Cpu_info cpu_info{Cpu_info::instance()};

  // end <cpu_info>
}

}  // namespace linux_specific
}  // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int, char* []) {
  using namespace fcs::linux_specific;
  using namespace boost::unit_test;
  test_suite* test = BOOST_TEST_SUITE("<cpu_info>");
  test->add(BOOST_TEST_CASE(&test_cpu_info));
  return test;
}
