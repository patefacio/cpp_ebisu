#include "fcs/utils/fixed_size_char_array.hpp"
#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace utils {
void test_fixed_size_char_array() {
  // custom <fixed_size_char_array>

  std::string const s1{"test"};
  {
    Fixed_size_char_array<2> sample{s1.c_str()};
    BOOST_REQUIRE(sample.operator std::string() == "t");
  }
  {
    Fixed_size_char_array<4> sample{s1.c_str()};
    BOOST_REQUIRE(sample.operator std::string() == "tes");
  }
  {
    Fixed_size_char_array<5> sample{s1.c_str()};
    BOOST_REQUIRE(sample.operator std::string() == "test");
    for (size_t i{0}; i < s1.size(); ++i) {
      BOOST_REQUIRE(s1[i] == sample[i]);
    }

    sample[0] = 'T';
    BOOST_REQUIRE(sample.operator std::string() == "Test");
    BOOST_REQUIRE(sample.str() == "Test");
    BOOST_REQUIRE(sample == "Test");
    BOOST_REQUIRE(!(sample == "Tester"));
    BOOST_REQUIRE(!(sample == "Tes"));
    BOOST_REQUIRE(sample[1] == 'e');
  }
  {
    Fixed_size_char_array<50> sample{s1.c_str()};
    BOOST_REQUIRE(sample.operator std::string() == "test");
  }

  // end <fixed_size_char_array>
}

}  // namespace utils
}  // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int, char* []) {
  using namespace fcs::utils;
  using namespace boost::unit_test;
  test_suite* test = BOOST_TEST_SUITE("<fixed_size_char_array>");
  test->add(BOOST_TEST_CASE(&test_fixed_size_char_array));
  return test;
}
