#include "fcs/raii/change_tracker.hpp"
#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace raii {
void test_change_tracker_next_value() {
  // custom <change_tracker_next_value>

  Change_tracker<int> change_tracker{1};
  BOOST_REQUIRE(change_tracker.current() == 1);
  {
    Change_tracker_next_value<int> next_value{change_tracker, 3};
    BOOST_REQUIRE(change_tracker.current() == 1);
    BOOST_REQUIRE(next_value.next_value() == 3);
  }
  BOOST_REQUIRE(change_tracker.previous() == 1);
  BOOST_REQUIRE(change_tracker.current() == 3);
  {
    Change_tracker_next_value<int> next_value{change_tracker, 4};
    BOOST_REQUIRE(next_value.next_value() == 4);
  }
  BOOST_REQUIRE(change_tracker.previous() == 3);
  BOOST_REQUIRE(change_tracker.current() == 4);

  // end <change_tracker_next_value>
}

void test_change_until_end_of_block() {
  // custom <change_until_end_of_block>
  int x{1};
  {
    fcs::raii::Change_until_end_of_block<int> change_until_end_of_block{x, 3};
    BOOST_REQUIRE(x == 3);
  }
  BOOST_REQUIRE(x == 1);
  {
    int y{4};
    fcs::raii::Change_until_end_of_block<int> change_until_end_of_block{x, y};
    BOOST_REQUIRE(x == y && x == 4);
  }
  BOOST_REQUIRE(x == 1);
  // end <change_until_end_of_block>
}

}  // namespace raii
}  // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int, char * []) {
  using namespace fcs::raii;
  using namespace boost::unit_test;
  test_suite* test = BOOST_TEST_SUITE("<change_tracker>");
  test->add(BOOST_TEST_CASE(&test_change_tracker_next_value));
  test->add(BOOST_TEST_CASE(&test_change_until_end_of_block));
  return test;
}
