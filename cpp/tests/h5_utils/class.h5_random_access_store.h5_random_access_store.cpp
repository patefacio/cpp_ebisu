#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ebisu/h5/utils/h5_random_access_store.hpp"

// custom <custom includes>
// end <custom includes>

namespace ebisu {
namespace h5 {
namespace utils {
// custom <h5_random_access_store begin namespace>
// end <h5_random_access_store begin namespace>

namespace scoped {
class Sample {
 public:
  friend class Sample_h5_dss;
  class Sample_h5_dss;
  using Char_10_bytes_t = std::array<char, 10>;
  using Unrecognizable_t = int;
  using Buffer_t = std::array<char, 16>;
  using H5_dss_t = Sample_h5_dss;

  Sample() = default;

  Sample(char m_char, unsigned char m_unsigned_char, signed char m_signed_char,
         short m_short, int m_int, long m_long, long long m_long_long,
         Buffer_t bogus, unsigned int m_unsigned_int,
         unsigned long m_unsigned_long, unsigned long long m_unsigned_long_long,
         double m_double, long double m_long_double, char m_sentinal,
         Char_10_bytes_t const& m_str_10_bytes)
      : m_char_(m_char),
        m_unsigned_char_(m_unsigned_char),
        m_signed_char_(m_signed_char),
        m_short_(m_short),
        m_int_(m_int),
        m_long_(m_long),
        m_long_long_(m_long_long),
        bogus_(bogus),
        m_unsigned_int_(m_unsigned_int),
        m_unsigned_long_(m_unsigned_long),
        m_unsigned_long_long_(m_unsigned_long_long),
        m_double_(m_double),
        m_long_double_(m_long_double),
        m_sentinal_(m_sentinal),
        m_str_10_bytes_(m_str_10_bytes) {}

  friend inline std::ostream& operator<<(std::ostream& out,
                                         Sample const& item) {
    using ebisu::utils::streamers::operator<<;
    out << "Sample(" << &item << ") {";
    out << "\n  m_char:" << item.m_char_;
    out << "\n  m_unsigned_char:" << item.m_unsigned_char_;
    out << "\n  m_signed_char:" << item.m_signed_char_;
    out << "\n  m_short:" << item.m_short_;
    out << "\n  m_int:" << item.m_int_;
    out << "\n  m_long:" << item.m_long_;
    out << "\n  m_long_long:" << item.m_long_long_;
    out << "\n  bogus:" << item.bogus_;
    out << "\n  m_unsigned_int:" << item.m_unsigned_int_;
    out << "\n  m_unsigned_long:" << item.m_unsigned_long_;
    out << "\n  m_unsigned_long_long:" << item.m_unsigned_long_long_;
    out << "\n  m_double:" << item.m_double_;
    out << "\n  m_long_double:" << item.m_long_double_;
    out << "\n  m_sentinal:" << item.m_sentinal_;
    out << "\n  m_str_10_bytes:" << item.m_str_10_bytes_;
    out << "\n}\n";
    return out;
  }

  //! getter for m_char_ (access is Ro)
  char m_char() const { return m_char_; }

  //! getter for m_unsigned_char_ (access is Ro)
  unsigned char m_unsigned_char() const { return m_unsigned_char_; }

  //! getter for m_signed_char_ (access is Ro)
  signed char m_signed_char() const { return m_signed_char_; }

  //! getter for m_short_ (access is Ro)
  short m_short() const { return m_short_; }

  //! getter for m_int_ (access is Ro)
  int m_int() const { return m_int_; }

  //! getter for m_long_ (access is Ro)
  long m_long() const { return m_long_; }

  //! getter for m_long_long_ (access is Ro)
  long long m_long_long() const { return m_long_long_; }

  //! getter for bogus_ (access is Ro)
  Buffer_t bogus() const { return bogus_; }

  //! getter for m_unsigned_int_ (access is Ro)
  unsigned int m_unsigned_int() const { return m_unsigned_int_; }

  //! getter for m_unsigned_long_ (access is Ro)
  unsigned long m_unsigned_long() const { return m_unsigned_long_; }

  //! getter for m_unsigned_long_long_ (access is Ro)
  unsigned long long m_unsigned_long_long() const {
    return m_unsigned_long_long_;
  }

  //! getter for m_double_ (access is Ro)
  double m_double() const { return m_double_; }

  //! getter for m_long_double_ (access is Ro)
  long double m_long_double() const { return m_long_double_; }

  //! getter for m_sentinal_ (access is Ro)
  char m_sentinal() const { return m_sentinal_; }

  //! getter for m_str_10_bytes_ (access is Ro)
  Char_10_bytes_t const& m_str_10_bytes() const { return m_str_10_bytes_; }

 private:
  char const m_char_{0};
  unsigned char const m_unsigned_char_{0};
  signed char const m_signed_char_{0};
  short const m_short_{0};
  int const m_int_{0};
  long const m_long_{0};
  long long const m_long_long_{0};

  /**
   Should be ignored for hdf5
  */
  Buffer_t const bogus_{};
  unsigned int const m_unsigned_int_{0};
  unsigned long const m_unsigned_long_{0};
  unsigned long long const m_unsigned_long_long_{0};
  double const m_double_{0};
  long double const m_long_double_{0};
  char const m_sentinal_{0};
  Char_10_bytes_t const m_str_10_bytes_{};
};

class Sample_h5_dss {
 public:
  using Record_t = Sample;

  static constexpr char const* DATA_SET_NAME{"/sample"};

  Sample_h5_dss(Sample_h5_dss const& other) = delete;

  Sample_h5_dss(Sample_h5_dss&& other) = delete;

  Sample_h5_dss& operator=(Sample_h5_dss const&) = delete;

  Sample_h5_dss& operator=(Sample_h5_dss&&) = delete;

  static Sample_h5_dss& instance() {
    static Sample_h5_dss instance_s;
    return instance_s;
  }

  //! getter for compound_data_type_id_ (access is Ro)
  hid_t compound_data_type_id() const { return compound_data_type_id_; }

 private:
  Sample_h5_dss() {
    compound_data_type_id_ = H5Tcreate(H5T_COMPOUND, sizeof(Sample));
    H5Tinsert(compound_data_type_id_, "m_char", HOFFSET(Sample, m_char_),
              H5T_NATIVE_CHAR);
    H5Tinsert(compound_data_type_id_, "m_unsigned_char",
              HOFFSET(Sample, m_unsigned_char_), H5T_NATIVE_UCHAR);
    H5Tinsert(compound_data_type_id_, "m_signed_char",
              HOFFSET(Sample, m_signed_char_), H5T_NATIVE_SCHAR);
    H5Tinsert(compound_data_type_id_, "m_short", HOFFSET(Sample, m_short_),
              H5T_NATIVE_SHORT);
    H5Tinsert(compound_data_type_id_, "m_int", HOFFSET(Sample, m_int_),
              H5T_NATIVE_INT);
    H5Tinsert(compound_data_type_id_, "m_long", HOFFSET(Sample, m_long_),
              H5T_NATIVE_LONG);
    H5Tinsert(compound_data_type_id_, "m_long_long",
              HOFFSET(Sample, m_long_long_), H5T_NATIVE_LLONG);
    auto bogus__type = H5Tcreate(H5T_OPAQUE, sizeof(Sample::bogus_));
    H5Tinsert(compound_data_type_id_, "bogus", HOFFSET(Sample, bogus_),
              bogus__type);
    H5Tinsert(compound_data_type_id_, "m_unsigned_int",
              HOFFSET(Sample, m_unsigned_int_), H5T_NATIVE_UINT);
    H5Tinsert(compound_data_type_id_, "m_unsigned_long",
              HOFFSET(Sample, m_unsigned_long_), H5T_NATIVE_ULONG);
    H5Tinsert(compound_data_type_id_, "m_unsigned_long_long",
              HOFFSET(Sample, m_unsigned_long_long_), H5T_NATIVE_ULLONG);
    H5Tinsert(compound_data_type_id_, "m_double", HOFFSET(Sample, m_double_),
              H5T_NATIVE_DOUBLE);
    H5Tinsert(compound_data_type_id_, "m_long_double",
              HOFFSET(Sample, m_long_double_), H5T_NATIVE_LDOUBLE);
    H5Tinsert(compound_data_type_id_, "m_sentinal",
              HOFFSET(Sample, m_sentinal_), H5T_NATIVE_CHAR);
    auto m_str_10_bytes_type = H5Tcopy(H5T_C_S1);
    H5Tset_size(m_str_10_bytes_type, 10);
    H5Tset_strpad(m_str_10_bytes_type, H5T_STR_NULLPAD);
    H5Tinsert(compound_data_type_id_, "m_str_10_bytes",
              HOFFSET(Sample, m_str_10_bytes_), m_str_10_bytes_type);
  }

  hid_t compound_data_type_id_{};
};
}
SCENARIO("simple h5 data set random access") {
  // custom <(632911136)>

  using namespace ebisu::h5::utils;
  // end <(632911136)>
  GIVEN("simple data set") {
    // custom <(569757557)>

    using namespace scoped;
    const int num_records{1};

    {
      auto file = std::make_shared<H5::H5File>("sample.hdf5", H5F_ACC_TRUNC);
      auto store =
          H5_random_access_store<Sample_h5_dss>(file, Open_create_e, "/");
      const Sample::Unrecognizable_t bogus = 42;

      for (int i = 0; i < num_records; ++i) {
        auto sample = Sample{static_cast<char>(i),
                             static_cast<unsigned char>(i),
                             static_cast<signed char>(i),
                             static_cast<short>(i),
                             i,
                             i,
                             i,
                             {},
                             static_cast<unsigned>(i),
                             static_cast<unsigned long>(i),
                             static_cast<unsigned long long>(i),
                             static_cast<double>(i + 0.5),
                             static_cast<long double>(i + 0.5),
                             static_cast<char>(i),
                             {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'}};

        std::cout << sample;
        store.append(sample);
      }
      REQUIRE(store.size() == num_records);
    }

    {
      auto file = std::make_shared<H5::H5File>("sample.hdf5", H5F_ACC_RDONLY);
      auto store =
          H5_random_access_store<Sample_h5_dss>(file, Open_read_e, "/");
      REQUIRE(store.size() == num_records);
      std::cout << "About to read " << std::endl;
      Sample s;
      for (int i = 0; i < num_records; ++i) {
        store.get(i, s);
        std::cout << s;

        REQUIRE(static_cast<char>(i) == s.m_char());
        REQUIRE(static_cast<unsigned char>(i) == s.m_unsigned_char());
        REQUIRE(static_cast<signed char>(i) == s.m_signed_char());
        REQUIRE(static_cast<short>(i) == s.m_short());
        REQUIRE(static_cast<int>(i) == s.m_int());
        REQUIRE(static_cast<long>(i) == s.m_long());
        REQUIRE(static_cast<long long>(i) == s.m_long_long());
        // REQUIRE(static_cast<int>(i) == s.bogus());
        REQUIRE(static_cast<unsigned int>(i) == s.m_unsigned_int());
        REQUIRE(static_cast<unsigned long>(i) == s.m_unsigned_long());
        REQUIRE(static_cast<unsigned long long>(i) == s.m_unsigned_long_long());
        REQUIRE(static_cast<double>(i + 0.5) == s.m_double());
        REQUIRE(static_cast<long double>(i + 0.5) == s.m_long_double());
        REQUIRE(std::string("abcdefghi") == &s.m_str_10_bytes()[0]);

        if (i == 42) {
          std::cout << s;
        }
      }
    }

    std::ostringstream msg;
    auto lev = h5_utils_logger->level();
    msg << "log level is " << lev;
    h5_utils_logger->info("Writing a cool log ({}!) level {}", "super cool",
                          msg.str());

    H5_UTILS_TRACE("Writing a cool log ({}!) level {}", "super cooler", lev);

    // end <(569757557)>
  }
}

}  // namespace utils
}  // namespace h5
}  // namespace ebisu
