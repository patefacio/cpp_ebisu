#ifndef __EBISU_H5_UTILS_H5_RANDOM_ACCESS_STORE_HPP__
#define __EBISU_H5_UTILS_H5_RANDOM_ACCESS_STORE_HPP__

#include "H5Cpp.h"
#include "H5File.h"
#include "H5PacketTable.h"
#include <memory>
#include <string>

namespace ebisu {
namespace h5 {
namespace utils {
enum Store_open_type { Open_create_e, Open_read_e };

inline char const* to_c_str(Store_open_type e) {
  switch (e) {
    case Store_open_type::Open_create_e:
      return "Open_create_e";
    case Store_open_type::Open_read_e:
      return "Open_read_e";
    default: { return "Invalid Store_open_type"; }
  }
}

inline std::ostream& operator<<(std::ostream& out, Store_open_type e) {
  return out << to_c_str(e);
}

/**
 Stores objects of type TYPE_STORED in an hdf5 data_set for basic random access
 whose hdf5 data_set type (when used for creation) is specified by
 H5_DATA_SET_SPECIFIER.

*/
template <typename TYPE_STORED, typename H5_DATA_SET_SPECIFIER = TYPE_STORED>
class H5_random_access_store {
 public:
  using Packet_table_sptr_t = std::shared_ptr<FL_PacketTable>;
  using H5_file_sptr_t = std::shared_ptr<H5::H5File>;
  using H5_data_set_specifier_t = H5_DATA_SET_SPECIFIER;
  using Group_id_list_t = std::vector<hid_t>;

  H5_random_access_store(H5_file_sptr_t const& file, Store_open_type open_type,
                         std::string const& group)
      : file_(file), open_type_(open_type), group_(group) {
    // custom <H5_random_access_store(create packet table)>
    // end <H5_random_access_store(create packet table)>
  }

 private:
  H5_file_sptr_t const file_{};
  Store_open_type const open_type_{};
  std::string const group_{};
  Packet_table_sptr_t packet_table_{};
};

// custom <FcbEndNamespace h5_random_access_store>
// end <FcbEndNamespace h5_random_access_store>

}  // namespace utils
}  // namespace h5
}  // namespace ebisu

#endif  // __EBISU_H5_UTILS_H5_RANDOM_ACCESS_STORE_HPP__
