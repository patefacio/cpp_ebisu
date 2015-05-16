#include "fcs/timestamp/timestamp.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include "fcs/utils/streamers/random.hpp"
#include <boost/test/included/unit_test.hpp>

namespace fcs {
namespace utils {
namespace streamers {
void test_random_source() {
  // custom <random_source>

  using namespace std;
  using namespace fcs::timestamp;

  Random_source rs;
  int int_;
  long long_;
  long long long_long_;
  float float_;
  double double_;
  uint8_t uint8_;
  uint16_t uint16_;
  uint32_t uint32_;
  uint64_t uint64_;
  string string_;

  rs >> int_ >> long_ >> long_long_ >> float_ >> double_ >> uint8_ >> uint16_ >>
      uint32_ >> uint64_ >> string_;

  cout << "int_: " << int_ << '\n' << "long_: " << long_ << '\n'
       << "long_long_: " << long_long_ << '\n' << "float_: " << float_ << '\n'
       << "double_: " << double_ << '\n' << "uint8_: " << uint8_ << '\n'
       << "uint16_: " << uint16_ << '\n' << "uint32_: " << uint32_ << '\n'
       << "uint64_: " << uint64_ << '\n' << "string_: " << string_ << '\n';
  rs >> string_;
  cout << "string_: " << string_ << '\n';
  rs >> string_;
  cout << "string_: " << string_ << '\n';

  std::vector<int> v;
  rs >> v;
  std::cout << "v => " << v;

  Fixed_size_char_array<10> fsca;
  rs >> fsca;
  std::cout << "fsca: " << fsca << std::endl;

  Timestamp_t ts;
  for (int i = 0; i < 100; ++i) {
    rs >> ts;
    std::cout << "random generated: " << ts << std::endl;
  }

  Date_t d;
  for (int i = 0; i < 100; ++i) {
    rs >> d;
    std::cout << "random generated date: " << d << std::endl;
  }

  // end <random_source>
}

}  // namespace streamers
}  // namespace utils
}  // namespace fcs

boost::unit_test::test_suite* init_unit_test_suite(int, char* []) {
  using namespace fcs::utils::streamers;
  using namespace boost::unit_test;
  test_suite* test = BOOST_TEST_SUITE("<random>");
  test->add(BOOST_TEST_CASE(&test_random_source));
  return test;
}
