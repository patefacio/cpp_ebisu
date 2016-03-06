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
  friend class SampleH5Dss;
  class SampleH5Dss;
  using Char10BytesT = std::array<char, 10>;
  using Unrecognizable = int;
  using Buffer = std::array<char, 16>;
  using H5Dss = SampleH5Dss;

  Sample() = default;

  Sample(char mChar, unsigned char mUnsignedChar, signed char mSignedChar,
         short mShort, int mInt, long mLong, long long mLongLong,
         Buffer_t bogus, unsigned int mUnsignedInt, unsigned long mUnsignedLong,
         unsigned long long mUnsignedLongLong, double mDouble,
         long double mLongDouble, char mSentinal,
         Char_10_bytes_t const& mStr10Bytes)
      : mChar_(mChar),
        mUnsignedChar_(mUnsignedChar),
        mSignedChar_(mSignedChar),
        mShort_(mShort),
        mInt_(mInt),
        mLong_(mLong),
        mLongLong_(mLongLong),
        bogus_(bogus),
        mUnsignedInt_(mUnsignedInt),
        mUnsignedLong_(mUnsignedLong),
        mUnsignedLongLong_(mUnsignedLongLong),
        mDouble_(mDouble),
        mLongDouble_(mLongDouble),
        mSentinal_(mSentinal),
        mStr10Bytes_(mStr10Bytes) {}

  friend inline std::ostream& operator<<(std::ostream& out,
                                         Sample const& item) {
    using ebisu::utils::streamers::operator<<;
    out << "Sample(" << &item << ") {";
    out << "\n  mChar:" << item.mChar_;
    out << "\n  mUnsignedChar:" << item.mUnsignedChar_;
    out << "\n  mSignedChar:" << item.mSignedChar_;
    out << "\n  mShort:" << item.mShort_;
    out << "\n  mInt:" << item.mInt_;
    out << "\n  mLong:" << item.mLong_;
    out << "\n  mLongLong:" << item.mLongLong_;
    out << "\n  bogus:" << item.bogus_;
    out << "\n  mUnsignedInt:" << item.mUnsignedInt_;
    out << "\n  mUnsignedLong:" << item.mUnsignedLong_;
    out << "\n  mUnsignedLongLong:" << item.mUnsignedLongLong_;
    out << "\n  mDouble:" << item.mDouble_;
    out << "\n  mLongDouble:" << item.mLongDouble_;
    out << "\n  mSentinal:" << item.mSentinal_;
    out << "\n  mStr10Bytes:" << item.mStr10Bytes_;
    out << "\n}\n";
    return out;
  }

  //! getter for mChar_ (access is Ro)
  char mChar() const { return mChar_; }

  //! getter for mUnsignedChar_ (access is Ro)
  unsigned char mUnsignedChar() const { return mUnsignedChar_; }

  //! getter for mSignedChar_ (access is Ro)
  signed char mSignedChar() const { return mSignedChar_; }

  //! getter for mShort_ (access is Ro)
  short mShort() const { return mShort_; }

  //! getter for mInt_ (access is Ro)
  int mInt() const { return mInt_; }

  //! getter for mLong_ (access is Ro)
  long mLong() const { return mLong_; }

  //! getter for mLongLong_ (access is Ro)
  long long mLongLong() const { return mLongLong_; }

  //! getter for bogus_ (access is Ro)
  Buffer_t bogus() const { return bogus_; }

  //! getter for mUnsignedInt_ (access is Ro)
  unsigned int mUnsignedInt() const { return mUnsignedInt_; }

  //! getter for mUnsignedLong_ (access is Ro)
  unsigned long mUnsignedLong() const { return mUnsignedLong_; }

  //! getter for mUnsignedLongLong_ (access is Ro)
  unsigned long long mUnsignedLongLong() const { return mUnsignedLongLong_; }

  //! getter for mDouble_ (access is Ro)
  double mDouble() const { return mDouble_; }

  //! getter for mLongDouble_ (access is Ro)
  long double mLongDouble() const { return mLongDouble_; }

  //! getter for mSentinal_ (access is Ro)
  char mSentinal() const { return mSentinal_; }

  //! getter for mStr10Bytes_ (access is Ro)
  Char_10_bytes_t const& mStr10Bytes() const { return mStr10Bytes_; }

 private:
  char const mChar_{0};
  unsigned char const mUnsignedChar_{0};
  signed char const mSignedChar_{0};
  short const mShort_{0};
  int const mInt_{0};
  long const mLong_{0};
  long long const mLongLong_{0};

  /**
   Should be ignored for hdf5
  */
  Buffer_t const bogus_{};
  unsigned int const mUnsignedInt_{0};
  unsigned long const mUnsignedLong_{0};
  unsigned long long const mUnsignedLongLong_{0};
  double const mDouble_{0};
  long double const mLongDouble_{0};
  char const mSentinal_{0};
  Char_10_bytes_t const mStr10Bytes_{};
};

class SampleH5Dss {
 public:
  using Record = Sample;

  static constexpr char const* DATA_SET_NAME{"/sample"};

  SampleH5Dss(SampleH5Dss const& other) = delete;

  static SampleH5Dss& instance() {
    static SampleH5Dss instance_s;
    return instance_s;
  }

  //! getter for compoundDataTypeId_ (access is Ro)
  hid_t compoundDataTypeId() const { return compoundDataTypeId_; }

 private:
  SampleH5Dss() {
    compound_data_type_id_ = H5Tcreate(H5T_COMPOUND, sizeof(Sample));
    H5Tinsert(compound_data_type_id_, "mChar", HOFFSET(Sample, mChar_),
              H5T_NATIVE_CHAR);
    H5Tinsert(compound_data_type_id_, "mUnsignedChar",
              HOFFSET(Sample, mUnsignedChar_), H5T_NATIVE_UCHAR);
    H5Tinsert(compound_data_type_id_, "mSignedChar",
              HOFFSET(Sample, mSignedChar_), H5T_NATIVE_SCHAR);
    H5Tinsert(compound_data_type_id_, "mShort", HOFFSET(Sample, mShort_),
              H5T_NATIVE_SHORT);
    H5Tinsert(compound_data_type_id_, "mInt", HOFFSET(Sample, mInt_),
              H5T_NATIVE_INT);
    H5Tinsert(compound_data_type_id_, "mLong", HOFFSET(Sample, mLong_),
              H5T_NATIVE_LONG);
    H5Tinsert(compound_data_type_id_, "mLongLong", HOFFSET(Sample, mLongLong_),
              H5T_NATIVE_LLONG);
    auto bogus__type = H5Tcreate(H5T_OPAQUE, sizeof(Sample::bogus_));
    H5Tinsert(compound_data_type_id_, "bogus", HOFFSET(Sample, bogus_),
              bogus__type);
    H5Tinsert(compound_data_type_id_, "mUnsignedInt",
              HOFFSET(Sample, mUnsignedInt_), H5T_NATIVE_UINT);
    H5Tinsert(compound_data_type_id_, "mUnsignedLong",
              HOFFSET(Sample, mUnsignedLong_), H5T_NATIVE_ULONG);
    H5Tinsert(compound_data_type_id_, "mUnsignedLongLong",
              HOFFSET(Sample, mUnsignedLongLong_), H5T_NATIVE_ULLONG);
    H5Tinsert(compound_data_type_id_, "mDouble", HOFFSET(Sample, mDouble_),
              H5T_NATIVE_DOUBLE);
    H5Tinsert(compound_data_type_id_, "mLongDouble",
              HOFFSET(Sample, mLongDouble_), H5T_NATIVE_LDOUBLE);
    H5Tinsert(compound_data_type_id_, "mSentinal", HOFFSET(Sample, mSentinal_),
              H5T_NATIVE_CHAR);
    auto mStr10Bytes_type = H5Tcopy(H5T_C_S1);
    H5Tset_size(mStr10Bytes_type, 10);
    H5Tset_strpad(mStr10Bytes_type, H5T_STR_NULLPAD);
    H5Tinsert(compound_data_type_id_, "mStr10Bytes",
              HOFFSET(Sample, mStr10Bytes_), mStr10Bytes_type);
  }

  hid_t compoundDataTypeId_{};
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
