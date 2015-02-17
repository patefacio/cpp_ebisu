#include "fcs/linux_specific/umask_scoped_set.hpp"
#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace linux_specific {
void test_umask_scoped_set() {
  // custom <umask_scoped_set>

  { Umask_scoped_set{0}; }

  // end <umask_scoped_set>
}

}  // namespace linux_specific
}  // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int, char* []) {
  using namespace fcs::linux_specific;
  using namespace boost::unit_test;
  test_suite* test = BOOST_TEST_SUITE("<umask_scoped_set>");
  test->add(BOOST_TEST_CASE(&test_umask_scoped_set));
  return test;
}
