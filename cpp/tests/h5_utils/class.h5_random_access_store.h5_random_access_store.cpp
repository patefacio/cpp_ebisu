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

class Sample {
 public:
  friend class H5_data_set_specifier;

  class H5_data_set_specifier {
   public:
    H5_data_set_specifier(H5_data_set_specifier const& other) = delete;

    static H5_data_set_specifier& instance() {
      static H5_data_set_specifier instance_s;
      return instance_s;
    }

   private:
    H5_data_set_specifier() {
      compound_data_type_id_ = H5Tcreate(H5T_COMPOUND, sizeof(Sample));
      H5Tinsert(compound_data_type_id_, "age_in_years",
                HOFFSET(Sample, age_in_years_), TODO_TYPE);
      H5Tinsert(compound_data_type_id_, "height_in_inches",
                HOFFSET(Sample, height_in_inches_), TODO_TYPE);
    }

    std::string const data_set_name_{"/h5_data_set_specifier"};
    hid_t compound_data_type_id_{};
  };

  /// hdf5 goodness added here

 private:
  int age_in_years_{0};
  double height_in_inches_{0.0};
};
SCENARIO("simple h5 data set random access") {
  // custom <(632911136)>
  // end <(632911136)>
  GIVEN("simple data set") {
    // custom <(569757557)>
    // end <(569757557)>
  }
}

}  // namespace utils
}  // namespace h5
}  // namespace ebisu
